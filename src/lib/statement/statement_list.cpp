/*
   +----------------------------------------------------------------------+
   | HipHop for PHP                                                       |
   +----------------------------------------------------------------------+
   | Copyright (c) 2010 Facebook, Inc. (http://www.facebook.com)          |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
*/

#include <lib/statement/statement_list.h>
#include <lib/analysis/analysis_result.h>
#include <lib/analysis/function_scope.h>
#include <lib/analysis/file_scope.h>
#include <lib/analysis/class_scope.h>
#include <lib/statement/scope_statement.h>
#include <lib/analysis/code_error.h>
#include <lib/statement/exp_statement.h>
#include <lib/statement/method_statement.h>
#include <lib/statement/class_statement.h>
#include <lib/parser/hphp.tab.h>
#include <lib/expression/binary_op_expression.h>
#include <lib/expression/assignment_expression.h>
#include <lib/expression/simple_variable.h>
#include <lib/expression/constant_expression.h>

using namespace HPHP;
using namespace std;
using namespace boost;

///////////////////////////////////////////////////////////////////////////////
// constructors/destructors

StatementList::StatementList
(STATEMENT_CONSTRUCTOR_PARAMETERS)
  : Statement(STATEMENT_CONSTRUCTOR_PARAMETER_VALUES), m_included(false) {
}

StatementPtr StatementList::clone() {
  StatementListPtr stmt(new StatementList(*this));
  stmt->m_stmts.clear();
  for (unsigned int i = 0; i < m_stmts.size(); i++) {
    stmt->m_stmts.push_back(Clone(m_stmts[i]));
  }
  return stmt;
}

///////////////////////////////////////////////////////////////////////////////
// parser functions

void StatementList::addElement(StatementPtr stmt) {
  m_stmts.push_back(stmt);
}

void StatementList::insertElement(StatementPtr stmt, int index /* = 0 */) {
  ASSERT(index >= 0 && index <= (int)m_stmts.size());
  m_stmts.insert(m_stmts.begin() + index, stmt);
}

void StatementList::removeElement(int index) {
  m_stmts.erase(m_stmts.begin() + index, m_stmts.begin() + index + 1);
}

void StatementList::shift(int from, int to) {
  ASSERT(from >= 0 && from <= (int)m_stmts.size());
  ASSERT(to >= 0 && to <= (int)m_stmts.size());
  StatementPtr stmt = m_stmts[from];
  for (int i = from; i < to; i++) {
    m_stmts[i] = m_stmts[i+1];
  }
  m_stmts[to] = stmt;
}

///////////////////////////////////////////////////////////////////////////////
// static analysis functions

StatementPtr StatementList::operator[](int index) {
  ASSERT(index >= 0 && index < getCount());
  return m_stmts[index];
}

bool StatementList::hasEffect() const {
  for (unsigned int i = 0; i < m_stmts.size(); i++) {
    if (m_stmts[i]->hasEffect()) return true;
  }
  return !m_stmts.empty();
}

bool StatementList::hasDecl() const {
  for (unsigned int i = 0; i < m_stmts.size(); i++) {
    if (m_stmts[i]->hasDecl()) return true;
  }
  return false;
}

bool StatementList::hasImpl() const {
  for (unsigned int i = 0; i < m_stmts.size(); i++) {
    if (m_stmts[i]->hasImpl()) return true;
  }
  return false;
}

bool StatementList::hasRetExp() const {
  for (unsigned int i = 0; i < m_stmts.size(); i++) {
    if (m_stmts[i]->hasRetExp()) return true;
  }
  return false;
}

void StatementList::analyzeProgram(AnalysisResultPtr ar) {
  m_included = true;
  for (unsigned int i = 0; i < m_stmts.size(); i++) {
    StatementPtr stmt = m_stmts[i];

    // effect testing
    if (ar->isFirstPass() && !stmt->hasEffect() &&
        !stmt->is(Statement::KindOfStatementList)) {
      ar->getCodeError()->record(shared_from_this(),
                                 CodeError::StatementHasNoEffect, stmt);
    }

    // changing AUTOLOAD to includes
    if (ar->getPhase() == AnalysisResult::AnalyzeInclude &&
        stmt->is(Statement::KindOfExpStatement)) {
      ExpStatementPtr expStmt = dynamic_pointer_cast<ExpStatement>(stmt);
      if (stmt->isFileLevel()) {
        expStmt->analyzeAutoload(ar);
      }
      expStmt->analyzeShortCircuit(ar);
    }

    bool scopeStmt = stmt->is(Statement::KindOfFunctionStatement) ||
      stmt->is(Statement::KindOfClassStatement) ||
      stmt->is(Statement::KindOfInterfaceStatement);
    if (ar->getPhase() != AnalysisResult::AnalyzeTopLevel || !scopeStmt) {
      /* Recurse when analyzing include/all OR when not a scope */
      stmt->analyzeProgram(ar);
    }
  }
}

bool StatementList::mergeConcatAssign(AnalysisResultPtr ar) {
  // check for vector string concat assignment such as
  //   $space = " ";
  //   $a .= "hello";
  //   $a .= $space;
  //   $a .= "world!";
  // turn into (for constant folding and concat sequence)
  //   $a .= " " . "hello " . $space . "world!";
  unsigned int i = 0;
  bool merged = false;
  do {
    std::string lhsName;
    int length = 0;
    for (; i < m_stmts.size(); i++) {
      StatementPtr stmt = m_stmts[i];
      if (!stmt->is(Statement::KindOfExpStatement)) break;
      ExpStatementPtr expStmt = dynamic_pointer_cast<ExpStatement>(stmt);
      ExpressionPtr exp = expStmt->getExpression();

      // check the first assignment
      if (exp->is(Expression::KindOfAssignmentExpression)) {
        AssignmentExpressionPtr assignment_exp =
          dynamic_pointer_cast<AssignmentExpression>(exp);
        ExpressionPtr variable = assignment_exp->getVariable();
        ExpressionPtr value = assignment_exp->getValue();
        std::string variableName = variable->getText();
        if (variableName.find("->") != std::string::npos) break;
        if (value->hasEffect()) break;
        // cannot turn $a .= $b; a .= $a into $a .= $b . $a;
        if (value->getText().find(variableName) != std::string::npos) break;
        if (lhsName.empty()) {
          lhsName = variable->getText();
          length++;
          continue;
        } else {
          break;
        }
      } else if (!exp->is(Expression::KindOfBinaryOpExpression)) {
        break;
      }
      BinaryOpExpressionPtr binaryOpExp =
        dynamic_pointer_cast<BinaryOpExpression>(exp);
      if (binaryOpExp->getOp() != T_CONCAT_EQUAL) break;
      ExpressionPtr exp1 = binaryOpExp->getExp1();
      std::string exp1Text = exp1->getText();
      if (exp1Text.find("->") != std::string::npos) break;
      ExpressionPtr exp2 = binaryOpExp->getExp2();
      if (exp2->hasEffect()) break;
      if (exp2->getText().find(exp1Text) != std::string::npos) break;
      if (lhsName.empty()) {
        lhsName = exp1Text;
        length++;
      } else if (lhsName == exp1Text) {
        length++;
      } else {
        break;
      }
    }
    if (length > 1) {
      // replace m_stmts[j] to m_stmts[i - 1] with a new statement
      unsigned j = i - length;
      ExpStatementPtr expStmt;
      ExpressionPtr exp;
      BinaryOpExpressionPtr binaryOpExp;
      ExpressionPtr var;
      ExpressionPtr exp1;
      ExpressionPtr exp2;
      bool isAssignment = false;
      expStmt = dynamic_pointer_cast<ExpStatement>(m_stmts[j++]);
      exp = expStmt->getExpression();
      if (exp->is(Expression::KindOfAssignmentExpression)) {
        isAssignment = true;
        AssignmentExpressionPtr assignment_exp =
          dynamic_pointer_cast<AssignmentExpression>(exp);
        var = assignment_exp->getVariable();
        exp1 = assignment_exp->getValue();
      } else {
        binaryOpExp = dynamic_pointer_cast<BinaryOpExpression>(exp);
        var = binaryOpExp->getExp1();
        exp1 = binaryOpExp->getExp2();
      }

      for (; j < i; j++) {
        expStmt = dynamic_pointer_cast<ExpStatement>(m_stmts[j]);
        exp = expStmt->getExpression();
        binaryOpExp = dynamic_pointer_cast<BinaryOpExpression>(exp);
        exp2 = binaryOpExp->getExp2();
        exp1 = BinaryOpExpressionPtr(new BinaryOpExpression(getLocation(),
                 Expression::KindOfBinaryOpExpression,
                 exp1, exp2, '.'));
      }
      if (isAssignment) {
        exp = AssignmentExpressionPtr
          (new AssignmentExpression(exp->getLocation(),
                                    Expression::KindOfAssignmentExpression,
                                    var, exp1,
                                    false));
      } else {
        exp = BinaryOpExpressionPtr(new BinaryOpExpression(getLocation(),
                Expression::KindOfBinaryOpExpression,
                var, exp1, T_CONCAT_EQUAL));
      }
      expStmt = ExpStatementPtr(new ExpStatement(getLocation(),
                Statement::KindOfExpStatement, exp));
      m_stmts[i - length] = expStmt;
      for (j = i - (length - 1); i > j; i--) removeElement(j);
      merged = true;
    } else if (length == 0) {
      i++;
    }
  } while (i < m_stmts.size());
  return merged;
}

StatementPtr StatementList::preOptimize(AnalysisResultPtr ar) {
  for (unsigned int i = 0; i < m_stmts.size(); i++) {
    ar->preOptimize(m_stmts[i]);
  }
  if (mergeConcatAssign(ar)) ar->incOptCounter();
  return StatementPtr();
}

StatementPtr StatementList::postOptimize(AnalysisResultPtr ar) {
  for (unsigned int i = 0; i < m_stmts.size(); i++) {
    ar->postOptimize(m_stmts[i]);
  }
  return StatementPtr();
}

void StatementList::inferTypes(AnalysisResultPtr ar) {
  for (unsigned int i = 0; i < m_stmts.size(); i++) {
    m_stmts[i]->inferTypes(ar);
  }
}

///////////////////////////////////////////////////////////////////////////////
// code generation functions

void StatementList::outputPHP(CodeGenerator &cg, AnalysisResultPtr ar) {
  for (unsigned int i = 0; i < m_stmts.size(); i++) {
    StatementPtr stmt = m_stmts[i];

    switch (cg.getContext()) {
    case CodeGenerator::NoContext:
      stmt->outputPHP(cg, ar);
      break;
    case CodeGenerator::PhpDeclaration:
      if (stmt->is(Statement::KindOfFunctionStatement) ||
          stmt->is(Statement::KindOfClassStatement) ||
          stmt->is(Statement::KindOfInterfaceStatement)) {
        cg.setContext(CodeGenerator::PhpImplementation);
        stmt->outputPHP(cg, ar);
        cg.setContext(CodeGenerator::PhpDeclaration);
      }
      break;
    case CodeGenerator::PhpImplementation:
      if (!stmt->is(Statement::KindOfFunctionStatement) &&
          !stmt->is(Statement::KindOfClassStatement) &&
          !stmt->is(Statement::KindOfInterfaceStatement)) {
        stmt->outputPHP(cg, ar);
      }
      break;
    default:
      ASSERT(false);
    }
  }
}

void StatementList::outputCPP(CodeGenerator &cg, AnalysisResultPtr ar) {
  FunctionScopePtr func = ar->getFunctionScope();
  bool inPseudoMain = func && func->inPseudoMain();
  if (inPseudoMain) {
    // We need these declarations to go first, because PHP allows top level
    // function and class declarations to appear after usage.
    for (unsigned int i = 0; i < m_stmts.size(); i++) {
      StatementPtr stmt = m_stmts[i];
      if (stmt->is(Statement::KindOfFunctionStatement) ||
          stmt->is(Statement::KindOfClassStatement) ||
          stmt->is(Statement::KindOfInterfaceStatement)) {
        stmt->outputCPP(cg,ar);
      }
    }
  }

  for (unsigned int i = 0; i < m_stmts.size(); i++) {
    StatementPtr stmt = m_stmts[i];
    if (stmt->is(Statement::KindOfClassStatement)) {
      if (!inPseudoMain) stmt->outputCPP(cg, ar);
    } else if (!(stmt->is(Statement::KindOfFunctionStatement) ||
                 stmt->is(Statement::KindOfInterfaceStatement)) ||
               !inPseudoMain) {
      stmt->outputCPP(cg, ar);
      if (stmt->is(Statement::KindOfMethodStatement)) {
        MethodStatementPtr methodStmt =
          dynamic_pointer_cast<MethodStatement>(stmt);
        std::string methodName = methodStmt->getName();
        if (methodName == "__get") {
          FunctionScopePtr funcScope = methodStmt->getFunctionScope();
          std::string name = funcScope->getName();
          funcScope->setName("__lval");
          methodStmt->setName("__lval");
          methodStmt->outputCPP(cg, ar);
          funcScope->setName(name);
          methodStmt->setName("__get");
        } else if (methodName == "offsetget") {
          ClassScopePtr cls = ar->getClassScope();
          std::string arrayAccess("arrayaccess");
          if (cls->derivesFrom(ar, arrayAccess)) {
            FunctionScopePtr funcScope = methodStmt->getFunctionScope();
            std::string name = funcScope->getName();
            funcScope->setName("__offsetget_lval");
            methodStmt->setName("__offsetget_lval");
            methodStmt->outputCPP(cg, ar);
            funcScope->setName(name);
            methodStmt->setName("offsetget");
          }
        }
      }
    }
  }
}