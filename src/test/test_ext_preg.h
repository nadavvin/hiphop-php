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

#ifndef __TEST_EXT_PREG_H__
#define __TEST_EXT_PREG_H__

// >>>>>> Generated by idl.php. Do NOT modify. <<<<<<

#include <test/test_cpp_ext.h>

///////////////////////////////////////////////////////////////////////////////

class TestExtPreg : public TestCppExt {
 public:
  virtual bool RunTests(const std::string &which);

  bool test_preg_grep();
  bool test_preg_match();
  bool test_preg_match_all();
  bool test_preg_replace();
  bool test_preg_replace_callback();
  bool test_preg_split();
  bool test_preg_quote();
  bool test_preg_last_error();
  bool test_ereg_replace();
  bool test_eregi_replace();
  bool test_ereg();
  bool test_eregi();
  bool test_split();
  bool test_spliti();
  bool test_sql_regcase();
};

///////////////////////////////////////////////////////////////////////////////

#endif // __TEST_EXT_PREG_H__