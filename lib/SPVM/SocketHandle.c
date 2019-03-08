#include "spvm_native.h"

#include <assert.h>
#include <stdlib.h>

int32_t SPNATIVE__SPVM__SocketHandle__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {

  // Socket handle
  void* ofh = stack[0].oval;
  assert(ofh != NULL);
  
  int32_t sock = (intptr_t)env->pointer(env, ofh);
  assert(sock >= 0);
  
  close(sock);
  env->set_pointer(env, ofh, (void*)(intptr_t)-1);
  
  return SPVM_SUCCESS;
}
