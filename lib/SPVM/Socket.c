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

int32_t SPNATIVE__SPVM__Socket__new(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* obj_deststr = stack[0].oval;
  const char* deststr = (const char*)env->belems(env, obj_deststr);
  int32_t port = stack[1].ival;
  
  int32_t sock = socket(AF_INET, SOCK_STREAM, 0);
  
  if (sock < 0) {
    SPVM_CROAK("Can't create socket", "SPVM/Socket.c", __LINE__);
  }
  
  struct sockaddr_in server;
  server.sin_addr.s_addr = inet_addr(deststr);
  server.sin_family = AF_INET;
  server.sin_port = htons(port);

  if (server.sin_addr.s_addr == 0xffffffff) {
    struct hostent *host;
    
    host = gethostbyname(deststr);
    if (host == NULL) {
      if (h_errno == HOST_NOT_FOUND) {
        fprintf(stderr, "host not found : %s\n", deststr);
        SPVM_CROAK("Exception", "SPVM/Socket.c", __LINE__);
      }
      return 1;
    }
    
    unsigned int **addrptr = (unsigned int **)host->h_addr_list;
    
    while (*addrptr != NULL) {
      server.sin_addr.s_addr = *(*addrptr);
      if (connect(sock,
        (struct sockaddr *)&server,
        sizeof(server)) == 0) {
          break;
      }

      addrptr++;
    }
    if (*addrptr == NULL) {
      SPVM_CROAK("Connect", "SPVM/Socket.c", __LINE__);
    }
  }
  
  void* obj_sh;
  {
    int32_t id = env->basic_type_id(env, "SPVM::SocketHandle");
    if (id < 0) { abort(); };
    obj_sh = env->new_obj(env, id);
  }
  
  env->set_pointer(env, obj_sh, (void*)(intptr_t)sock);
  
  stack[0].oval = obj_sh;
  
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
