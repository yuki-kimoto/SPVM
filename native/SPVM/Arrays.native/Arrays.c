#include <assert.h>
#include <stdlib.h>
#include <string.h>

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
    memcpy(copy_elements, original_elements, copy_length * sizeof(int8_t));
  }
  
  return copy;
}

SPVM_API_OBJECT* SPVM__Arrays__copy_of_short(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  SPVM_API_OBJECT* original = args[0].object_value;
  
  if (!original) {
    SPVM_API_OBJECT* exception = api->new_byte_array_string(api, "First argument must be not undef(SPVM::Arrays::copy_of_short())");
    api->set_exception(api, exception);
    return NULL;
  }
  
  int32_t new_length = args[1].int_value;
  
  if (new_length < 0) {
    SPVM_API_OBJECT* exception = api->new_byte_array_string(api, "Second argument must be not negative value(SPVM::Arrays::copy_of_short())");
    api->set_exception(api, exception);
    return NULL;
  }
  
  int32_t length = api->get_array_length(api, original);
  
  SPVM_API_OBJECT* copy = api->new_short_array(api, new_length);
  
  int32_t copy_length;
  if (new_length > length) {
    copy_length = length;
  }
  else {
    copy_length = new_length;
  }
  
  int16_t* original_elements = api->get_short_array_elements(api, original);
  
  int16_t* copy_elements = api->get_short_array_elements(api, copy);
  
  if (copy_length > 0) {
    memcpy(copy_elements, original_elements, copy_length * sizeof(int16_t));
  }
  
  return copy;
}

SPVM_API_OBJECT* SPVM__Arrays__copy_of_int(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  SPVM_API_OBJECT* original = args[0].object_value;
  
  if (!original) {
    SPVM_API_OBJECT* exception = api->new_byte_array_string(api, "First argument must be not undef(SPVM::Arrays::copy_of_int())");
    api->set_exception(api, exception);
    return NULL;
  }
  
  int32_t new_length = args[1].int_value;
  
  if (new_length < 0) {
    SPVM_API_OBJECT* exception = api->new_byte_array_string(api, "Second argument must be not negative value(SPVM::Arrays::copy_of_int())");
    api->set_exception(api, exception);
    return NULL;
  }
  
  int32_t length = api->get_array_length(api, original);
  
  SPVM_API_OBJECT* copy = api->new_int_array(api, new_length);
  
  int32_t copy_length;
  if (new_length > length) {
    copy_length = length;
  }
  else {
    copy_length = new_length;
  }
  
  int32_t* original_elements = api->get_int_array_elements(api, original);
  
  int32_t* copy_elements = api->get_int_array_elements(api, copy);
  
  if (copy_length > 0) {
    memcpy(copy_elements, original_elements, copy_length * sizeof(int32_t));
  }
  
  return copy;
}

SPVM_API_OBJECT* SPVM__Arrays__copy_of_long(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  SPVM_API_OBJECT* original = args[0].object_value;
  
  if (!original) {
    SPVM_API_OBJECT* exception = api->new_byte_array_string(api, "First argument must be not undef(SPVM::Arrays::copy_of_long())");
    api->set_exception(api, exception);
    return NULL;
  }
  
  int32_t new_length = args[1].int_value;
  
  if (new_length < 0) {
    SPVM_API_OBJECT* exception = api->new_byte_array_string(api, "Second argument must be not negative value(SPVM::Arrays::copy_of_long())");
    api->set_exception(api, exception);
    return NULL;
  }
  
  int32_t length = api->get_array_length(api, original);
  
  SPVM_API_OBJECT* copy = api->new_long_array(api, new_length);
  
  int32_t copy_length;
  if (new_length > length) {
    copy_length = length;
  }
  else {
    copy_length = new_length;
  }
  
  int64_t* original_elements = api->get_long_array_elements(api, original);
  
  int64_t* copy_elements = api->get_long_array_elements(api, copy);
  
  if (copy_length > 0) {
    memcpy(copy_elements, original_elements, copy_length * sizeof(int64_t));
  }
  
  return copy;
}

SPVM_API_OBJECT* SPVM__Arrays__copy_of_float(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  SPVM_API_OBJECT* original = args[0].object_value;
  
  if (!original) {
    SPVM_API_OBJECT* exception = api->new_byte_array_string(api, "First argument must be not undef(SPVM::Arrays::copy_of_float())");
    api->set_exception(api, exception);
    return NULL;
  }
  
  int32_t new_length = args[1].int_value;
  
  if (new_length < 0) {
    SPVM_API_OBJECT* exception = api->new_byte_array_string(api, "Second argument must be not negative value(SPVM::Arrays::copy_of_float())");
    api->set_exception(api, exception);
    return NULL;
  }
  
  int32_t length = api->get_array_length(api, original);
  
  SPVM_API_OBJECT* copy = api->new_float_array(api, new_length);
  
  int32_t copy_length;
  if (new_length > length) {
    copy_length = length;
  }
  else {
    copy_length = new_length;
  }
  
  float* original_elements = api->get_float_array_elements(api, original);
  
  float* copy_elements = api->get_float_array_elements(api, copy);
  
  if (copy_length > 0) {
    memcpy(copy_elements, original_elements, copy_length * sizeof(float));
  }
  
  return copy;
}

SPVM_API_OBJECT* SPVM__Arrays__copy_of_double(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  SPVM_API_OBJECT* original = args[0].object_value;
  
  if (!original) {
    SPVM_API_OBJECT* exception = api->new_byte_array_string(api, "First argument must be not undef(SPVM::Arrays::copy_of_double())");
    api->set_exception(api, exception);
    return NULL;
  }
  
  int32_t new_length = args[1].int_value;
  
  if (new_length < 0) {
    SPVM_API_OBJECT* exception = api->new_byte_array_string(api, "Second argument must be not negative value(SPVM::Arrays::copy_of_double())");
    api->set_exception(api, exception);
    return NULL;
  }
  
  int32_t length = api->get_array_length(api, original);
  
  SPVM_API_OBJECT* copy = api->new_double_array(api, new_length);
  
  int32_t copy_length;
  if (new_length > length) {
    copy_length = length;
  }
  else {
    copy_length = new_length;
  }
  
  double* original_elements = api->get_double_array_elements(api, original);
  
  double* copy_elements = api->get_double_array_elements(api, copy);
  
  if (copy_length > 0) {
    memcpy(copy_elements, original_elements, copy_length * sizeof(double));
  }
  
  return copy;
}
