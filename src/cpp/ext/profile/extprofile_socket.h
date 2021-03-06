/*
   +----------------------------------------------------------------------+
   | HipHop for PHP                                                       |
   +----------------------------------------------------------------------+
   | Copyright (c) 2010 Facebook, Inc. (http://www.facebook.com)          |
   | Copyright (c) 1997-2010 The PHP Group                                |
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

#ifndef __EXTPROFILE_SOCKET_H__
#define __EXTPROFILE_SOCKET_H__

// >>>>>> Generated by idl.php. Do NOT modify. <<<<<<

#include <cpp/ext/ext_socket.h>

namespace HPHP {
///////////////////////////////////////////////////////////////////////////////

inline Variant x_socket_create(int domain, int type, int protocol) {
  FUNCTION_INJECTION_BUILTIN(socket_create);
  return f_socket_create(domain, type, protocol);
}

inline Variant x_socket_create_listen(int port, int backlog = 128) {
  FUNCTION_INJECTION_BUILTIN(socket_create_listen);
  return f_socket_create_listen(port, backlog);
}

inline bool x_socket_create_pair(int domain, int type, int protocol, Variant fd) {
  FUNCTION_INJECTION_BUILTIN(socket_create_pair);
  return f_socket_create_pair(domain, type, protocol, ref(fd));
}

inline Variant x_socket_get_option(CObjRef socket, int level, int optname) {
  FUNCTION_INJECTION_BUILTIN(socket_get_option);
  return f_socket_get_option(socket, level, optname);
}

inline bool x_socket_getpeername(CObjRef socket, Variant address, Variant port = null) {
  FUNCTION_INJECTION_BUILTIN(socket_getpeername);
  return f_socket_getpeername(socket, ref(address), ref(port));
}

inline bool x_socket_getsockname(CObjRef socket, Variant address, Variant port = null) {
  FUNCTION_INJECTION_BUILTIN(socket_getsockname);
  return f_socket_getsockname(socket, ref(address), ref(port));
}

inline bool x_socket_set_block(CObjRef socket) {
  FUNCTION_INJECTION_BUILTIN(socket_set_block);
  return f_socket_set_block(socket);
}

inline bool x_socket_set_nonblock(CObjRef socket) {
  FUNCTION_INJECTION_BUILTIN(socket_set_nonblock);
  return f_socket_set_nonblock(socket);
}

inline bool x_socket_set_option(CObjRef socket, int level, int optname, CVarRef optval) {
  FUNCTION_INJECTION_BUILTIN(socket_set_option);
  return f_socket_set_option(socket, level, optname, optval);
}

inline bool x_socket_connect(CObjRef socket, CStrRef address, int port = 0) {
  FUNCTION_INJECTION_BUILTIN(socket_connect);
  return f_socket_connect(socket, address, port);
}

inline bool x_socket_bind(CObjRef socket, CStrRef address, int port = 0) {
  FUNCTION_INJECTION_BUILTIN(socket_bind);
  return f_socket_bind(socket, address, port);
}

inline bool x_socket_listen(CObjRef socket, int backlog = 0) {
  FUNCTION_INJECTION_BUILTIN(socket_listen);
  return f_socket_listen(socket, backlog);
}

inline Variant x_socket_select(Variant read, Variant write, Variant except, CVarRef vtv_sec, int tv_usec = 0) {
  FUNCTION_INJECTION_BUILTIN(socket_select);
  return f_socket_select(ref(read), ref(write), ref(except), vtv_sec, tv_usec);
}

inline Variant x_socket_server(CStrRef hostname, int port = -1, Variant errnum = null, Variant errstr = null) {
  FUNCTION_INJECTION_BUILTIN(socket_server);
  return f_socket_server(hostname, port, ref(errnum), ref(errstr));
}

inline Variant x_socket_accept(CObjRef socket) {
  FUNCTION_INJECTION_BUILTIN(socket_accept);
  return f_socket_accept(socket);
}

inline Variant x_socket_read(CObjRef socket, int length, int type = 0) {
  FUNCTION_INJECTION_BUILTIN(socket_read);
  return f_socket_read(socket, length, type);
}

inline Variant x_socket_write(CObjRef socket, CStrRef buffer, int length = 0) {
  FUNCTION_INJECTION_BUILTIN(socket_write);
  return f_socket_write(socket, buffer, length);
}

inline Variant x_socket_send(CObjRef socket, CStrRef buf, int len, int flags) {
  FUNCTION_INJECTION_BUILTIN(socket_send);
  return f_socket_send(socket, buf, len, flags);
}

inline Variant x_socket_sendto(CObjRef socket, CStrRef buf, int len, int flags, CStrRef addr, int port = 0) {
  FUNCTION_INJECTION_BUILTIN(socket_sendto);
  return f_socket_sendto(socket, buf, len, flags, addr, port);
}

inline Variant x_socket_recv(CObjRef socket, Variant buf, int len, int flags) {
  FUNCTION_INJECTION_BUILTIN(socket_recv);
  return f_socket_recv(socket, ref(buf), len, flags);
}

inline Variant x_socket_recvfrom(CObjRef socket, Variant buf, int len, int flags, Variant name, Variant port = 0) {
  FUNCTION_INJECTION_BUILTIN(socket_recvfrom);
  return f_socket_recvfrom(socket, ref(buf), len, flags, ref(name), ref(port));
}

inline bool x_socket_shutdown(CObjRef socket, int how = 0) {
  FUNCTION_INJECTION_BUILTIN(socket_shutdown);
  return f_socket_shutdown(socket, how);
}

inline void x_socket_close(CObjRef socket) {
  FUNCTION_INJECTION_BUILTIN(socket_close);
  f_socket_close(socket);
}

inline String x_socket_strerror(int errnum) {
  FUNCTION_INJECTION_BUILTIN(socket_strerror);
  return f_socket_strerror(errnum);
}

inline int x_socket_last_error(CObjRef socket = null_object) {
  FUNCTION_INJECTION_BUILTIN(socket_last_error);
  return f_socket_last_error(socket);
}

inline void x_socket_clear_error(CObjRef socket = null_object) {
  FUNCTION_INJECTION_BUILTIN(socket_clear_error);
  f_socket_clear_error(socket);
}


///////////////////////////////////////////////////////////////////////////////
}

#endif // __EXTPROFILE_SOCKET_H__
