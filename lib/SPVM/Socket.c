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

int32_t SPNATIVE__SPVM__Socket__socket(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  return SPVM_SUCCESS;
}
