#include <assert.h>
#include <stdlib.h>

#include "spvm_api.h"

SPVM_API_OBJECT* SPVM__Arrays__copy_of_byte(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  SPVM_API_OBJECT* original = args[0].object_value;
  
  if (!original) {
    SPVM_API_OBJECT* exception = api->new_byte_array_string(api, "First argument must be not undef(SPVM::Arrays::copy_of_byte())");
    api->set_exception(api, exception);
    return NULL;
  }
  
  int32_t new_length = args[1].int_value;
  
  if (new_length < 0) {
    SPVM_API_OBJECT* exception = api->new_byte_array_string(api, "Second argument must be not negative value(SPVM::Arrays::copy_of_byte())");
    api->set_exception(api, exception);
    return NULL;
  }
  
  int32_t length = api->get_array_length(api, original);
  
  SPVM_API_OBJECT* copy = api->new_byte_array(api, new_length);
  
  int32_t copy_length;
  if (new_length > length) {
    copy_length = length;
  }
  else {
    copy_length = new_length;
  }
  
  int8_t* original_elements = api->get_byte_array_elements(api, original);
  
  int8_t* copy_elements = api->get_byte_array_elements(api, copy);
  
  if (copy_length > 0) {
    memcpy(copy_elements, original_elements, copy_length);
  }
  
  return copy;
}
