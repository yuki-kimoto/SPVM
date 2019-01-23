#include "spvm_native.h"
#include <stdio.h>

int32_t SPVM_NATIVE_SPVM__FileHandle__DESTROY(SPVM_ENV* env, SPVM_VALUE* stack) {

  // File handle
  void* ofh = stack[0].oval;
  if (ofh != NULL) {
    FILE* fh = (FILE*)env->pointer(env, ofh);
    if (fh) {
      int32_t ret = fclose(fh);
      env->set_pointer(env, ofh, NULL);
      
      if (ret == EOF) {
        SPVM_CARP("Can't close file handle", "SPVM/FileHandle", __LINE__);
      }
    }
  }
  
  return SPVM_SUCCESS;
}
