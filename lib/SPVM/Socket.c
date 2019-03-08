#include "spvm_native.h"

#include <stdlib.h>
#include <assert.h>

#ifdef _WIN32

#include <winsock2.h>
#include <ws2tcpip.h>

#else
         
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#endif

int32_t SPNATIVE__SPVM__Socket__socket(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  int32_t domain = stack[0].ival;
  int32_t type = stack[1].ival;
  int32_t proto = stack[2].ival;
  
  int32_t sock = socket(domain, type, proto);
  
  if (sock < 0) {
    SPVM_CROAK("Can't create socket", "SPVM/Socket.c", __LINE__);
  }
  
  void* obj_sh;
  {
    int32_t id = env->basic_type_id(env, "SPVM::SocketHandle");
    if (id < 0) { abort(); };
    obj_sh = env->new_obj(env, id);
  }
  
  env->set_pointer(env, obj_sh, (intptr_t)sock);
  
  stack[0].oval = obj_sh;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Socket__htons(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  stack[0].sval = htons(stack[0].sval);
  
  return SPVM_SUCCESS;
}


int32_t SPNATIVE__SPVM__Socket__inet_addr(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_address = stack[0].oval;
  const char* address = env->belems(env, obj_address);
  
  int32_t iaddress = inet_addr(address);
  
  stack[0].ival = iaddress;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Socket__inet_aton(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_cp = stack[0].oval;
  void* obj_inp = stack[1].oval;

  if (obj_cp == NULL) {
    SPVM_CROAK("Error", "SPVM/Socket.c", __LINE__);
  }
  const char* cp = (const char*)env->belems(env, obj_cp);
  
  if (obj_inp == NULL) {
    SPVM_CROAK("Error", "SPVM/Socket.c", __LINE__);
  }
  struct in_addr* inp = env->pointer(env, obj_inp);
  
  int32_t ret = inet_aton(cp, inp);
  
  stack[0].ival = ret;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Socket__init_native_constants(SPVM_ENV* env, SPVM_VALUE* stack) {

  // AF_UNIX
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Socket", "$AF_UNIX", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, AF_UNIX);
  }

  // AF_INET
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Socket", "$AF_INET", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, AF_INET);
  }

  // AF_INET6
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Socket", "$AF_INET6", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, AF_INET6);
  }

  // SOCK_STREAM
  {
    int32_t pkgvar_id = env->pkgvar_id(env, "SPVM::Socket", "$SOCK_STREAM", "int");
    if (pkgvar_id < 0) { abort(); }
    env->set_ipkgvar(env, pkgvar_id, SOCK_STREAM);
  }
}
