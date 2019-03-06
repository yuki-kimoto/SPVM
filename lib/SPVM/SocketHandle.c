#include "spvm_native.h"

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

int32_t SPNATIVE__SPVM__SocketHandle__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {

  struct sockaddr_in server;
  char buf[32];
  char *deststr;
  unsigned int **addrptr;
 
  // Socket handle
  void* ofh = stack[0].oval;
  assert(ofh != NULL);
  
  int32_t sock = (intptr_t)env->pointer(env, ofh);
  assert(sock >= 0);
  
  close(sock);
  env->set_pointer(env, ofh, (void*)(intptr_t)-1);
  
  return SPVM_SUCCESS;
}
