#include "spvm_native.h"

#include <stdlib.h>
#include <assert.h>

#ifdef _WIN32

#include <winsock2.h>
#include <ws2tcpip.h>

#else

#include <unistd.h>
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
  
  int32_t handle = socket(AF_INET, SOCK_STREAM, 0);
  
  if (handle < 0) {
    SPVM_DIE_FMT("Can't create socket at %s line %d", "SPVM/Socket.c", __LINE__);
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
        SPVM_DIE_FMT("Exception at %s line %d", "SPVM/Socket.c", __LINE__);
      }
      return 1;
    }
    
    unsigned int **addrptr = (unsigned int **)host->h_addr_list;
    
    while (*addrptr != NULL) {
      server.sin_addr.s_addr = *(*addrptr);
      if (connect(handle,
        (struct sockaddr *)&server,
        sizeof(server)) == 0) {
          break;
      }

      addrptr++;
    }
    if (*addrptr == NULL) {
      SPVM_DIE_FMT("Connect at %s line %d", "SPVM/Socket.c", __LINE__);
    }
  }
  
  // Create SPVM::Socket object
  void* obj_socket;
  {
    int32_t id = env->basic_type_id(env, "SPVM::Socket");
    if (id < 0) { abort(); };
    obj_socket = env->new_obj(env, id);
  }
  
  // Set handle
  {
    int32_t id = env->field_id(env, "SPVM::Socket", "handle", "int");
    if (id < 0) { abort(); };
    env->set_ifield(env, obj_socket, id, handle);
  }
  
  stack[0].oval = obj_socket;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Socket__write(SPVM_ENV* env, SPVM_VALUE* stack) {
  void* obj_socket = stack[0].oval;
  void* obj_buffer = stack[1].oval;
  const char* buffer = (const char*)env->belems(env, obj_buffer);
  int32_t length = stack[2].ival;
  
  int32_t handle;
  {
    int32_t id = env->field_id(env, "SPVM::Socket", "handle", "int");
    assert(id >= 0);
    handle = env->ifield(env, obj_socket, id);
  }
  
  /* HTTPリクエスト送信 */
  int32_t write_length = write(handle, buffer, length);
  if (write_length < 0) {
    SPVM_DIE_FMT("Socket write error at %s line %d", "SPVM/Socket.c", __LINE__);
  }
  
  stack[0].ival = write_length;
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Socket__read(SPVM_ENV* env, SPVM_VALUE* stack) {
  void* obj_socket = stack[0].oval;
  void* obj_buffer = stack[1].oval;
  const char* buffer = (const char*)env->belems(env, obj_buffer);
  int32_t length = env->len(env, obj_buffer);
  
  int32_t handle;
  {
    int32_t id = env->field_id(env, "SPVM::Socket", "handle", "int");
    assert(id >= 0);
    handle = env->ifield(env, obj_socket, id);
  }
  
  /* HTTPリクエスト送信 */
  int32_t read_length = read(handle, (char*)buffer, length);
  if (read_length < 0) {
    SPVM_DIE_FMT("Socket read error at %s line %d", "SPVM/Socket.c", __LINE__);
  }
  
  stack[0].ival = read_length;
  
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
  
  return SPVM_SUCCESS;
}

int32_t SPNATIVE__SPVM__Socket__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {

  // Socket handle
  void* obj_socket = stack[0].oval;

  // Get handle
  int32_t handle;
  {
    int32_t id = env->field_id(env, "SPVM::Socket", "handle", "int");
    if (id < 0) { abort(); };
    handle = env->ifield(env, obj_socket, id);
  }
  
  close(handle);
  
  return SPVM_SUCCESS;
}
