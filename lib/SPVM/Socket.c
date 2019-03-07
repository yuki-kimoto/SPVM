#include "spvm_native.h"

#include <stdlib.h>
#include <assert.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int32_t SPNATIVE__SPVM__Socket__socket(SPVM_ENV* env, SPVM_VALUE* stack) {
  
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
}
