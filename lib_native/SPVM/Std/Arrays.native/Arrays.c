#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "spvm_api.h"

SPVM_API_int SPVM__Std__Arrays__equals_byte(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  SPVM_API_OBJECT* x1 = args[0].object_value;
  SPVM_API_OBJECT* x2 = args[1].object_value;
  
  if (x1 == NULL && x2 == NULL) {
    return 1;
  }
  else if (x1 == NULL) {
    return 0;
  }
  else if (x2 == NULL) {
    return 0;
  }
  else {
    SPVM_API_int x1_length = api->get_array_length(api, x1);
    SPVM_API_int x2_length = api->get_array_length(api, x2);
    
    if (x1_length == x2_length) {
      SPVM_API_OBJECT* x1_elements = api->get_byte_array_elements(api, x1);
      SPVM_API_OBJECT* x2_elements = api->get_byte_array_elements(api, x2);
      
      if (memcmp(x1_elements, x2_elements, sizeof(SPVM_API_byte) * x1_length) == 0) {
        return 1;
      }
      else {
        return 0;
      }
    }
    else {
      return 0;
    }
  }
}

SPVM_API_int SPVM__Std__Arrays__equals_short(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  SPVM_API_OBJECT* x1 = args[0].object_value;
  SPVM_API_OBJECT* x2 = args[1].object_value;
  
  if (x1 == NULL && x2 == NULL) {
    return 1;
  }
  else if (x1 == NULL) {
    return 0;
  }
  else if (x2 == NULL) {
    return 0;
  }
  else {
    SPVM_API_int x1_length = api->get_array_length(api, x1);
    SPVM_API_int x2_length = api->get_array_length(api, x2);
    
    if (x1_length == x2_length) {
      SPVM_API_OBJECT* x1_elements = api->get_short_array_elements(api, x1);
      SPVM_API_OBJECT* x2_elements = api->get_short_array_elements(api, x2);
      
      if (memcmp(x1_elements, x2_elements, sizeof(SPVM_API_short) * x1_length) == 0) {
        return 1;
      }
      else {
        return 0;
      }
    }
    else {
      return 0;
    }
  }
}

SPVM_API_int SPVM__Std__Arrays__equals_int(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  SPVM_API_OBJECT* x1 = args[0].object_value;
  SPVM_API_OBJECT* x2 = args[1].object_value;
  
  if (x1 == NULL && x2 == NULL) {
    return 1;
  }
  else if (x1 == NULL) {
    return 0;
  }
  else if (x2 == NULL) {
    return 0;
  }
  else {
    SPVM_API_int x1_length = api->get_array_length(api, x1);
    SPVM_API_int x2_length = api->get_array_length(api, x2);
    
    if (x1_length == x2_length) {
      SPVM_API_OBJECT* x1_elements = api->get_int_array_elements(api, x1);
      SPVM_API_OBJECT* x2_elements = api->get_int_array_elements(api, x2);
      
      if (memcmp(x1_elements, x2_elements, sizeof(SPVM_API_int) * x1_length) == 0) {
        return 1;
      }
      else {
        return 0;
      }
    }
    else {
      return 0;
    }
  }
}

SPVM_API_int SPVM__Std__Arrays__equals_long(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  SPVM_API_OBJECT* x1 = args[0].object_value;
  SPVM_API_OBJECT* x2 = args[1].object_value;
  
  if (x1 == NULL && x2 == NULL) {
    return 1;
  }
  else if (x1 == NULL) {
    return 0;
  }
  else if (x2 == NULL) {
    return 0;
  }
  else {
    SPVM_API_int x1_length = api->get_array_length(api, x1);
    SPVM_API_int x2_length = api->get_array_length(api, x2);
    
    if (x1_length == x2_length) {
      SPVM_API_OBJECT* x1_elements = api->get_long_array_elements(api, x1);
      SPVM_API_OBJECT* x2_elements = api->get_long_array_elements(api, x2);
      
      if (memcmp(x1_elements, x2_elements, sizeof(SPVM_API_long) * x1_length) == 0) {
        return 1;
      }
      else {
        return 0;
      }
    }
    else {
      return 0;
    }
  }
}

SPVM_API_int SPVM__Std__Arrays__equals_float(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  SPVM_API_OBJECT* x1 = args[0].object_value;
  SPVM_API_OBJECT* x2 = args[1].object_value;
  
  if (x1 == NULL && x2 == NULL) {
    return 1;
  }
  else if (x1 == NULL) {
    return 0;
  }
  else if (x2 == NULL) {
    return 0;
  }
  else {
    SPVM_API_int x1_length = api->get_array_length(api, x1);
    SPVM_API_int x2_length = api->get_array_length(api, x2);
    
    if (x1_length == x2_length) {
      SPVM_API_OBJECT* x1_elements = api->get_float_array_elements(api, x1);
      SPVM_API_OBJECT* x2_elements = api->get_float_array_elements(api, x2);
      
      if (memcmp(x1_elements, x2_elements, sizeof(SPVM_API_float) * x1_length) == 0) {
        return 1;
      }
      else {
        return 0;
      }
    }
    else {
      return 0;
    }
  }
}

SPVM_API_int SPVM__Std__Arrays__equals_double(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  SPVM_API_OBJECT* x1 = args[0].object_value;
  SPVM_API_OBJECT* x2 = args[1].object_value;
  
  if (x1 == NULL && x2 == NULL) {
    return 1;
  }
  else if (x1 == NULL) {
    return 0;
  }
  else if (x2 == NULL) {
    return 0;
  }
  else {
    SPVM_API_int x1_length = api->get_array_length(api, x1);
    SPVM_API_int x2_length = api->get_array_length(api, x2);
    
    if (x1_length == x2_length) {
      SPVM_API_OBJECT* x1_elements = api->get_double_array_elements(api, x1);
      SPVM_API_OBJECT* x2_elements = api->get_double_array_elements(api, x2);
      
      if (memcmp(x1_elements, x2_elements, sizeof(SPVM_API_double) * x1_length) == 0) {
        return 1;
      }
      else {
        return 0;
      }
    }
    else {
      return 0;
    }
  }
}

SPVM_API_OBJECT* SPVM__Std__Arrays__copy_of_byte(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  SPVM_API_OBJECT* original = args[0].object_value;
  
  if (!original) {
    SPVM_API_OBJECT* exception = api->new_string_chars(api, "First argument must be not undef");
    api->set_exception(api, exception);
    return NULL;
  }
  
  int32_t new_length = args[1].int_value;
  
  if (new_length < 0) {
    SPVM_API_OBJECT* exception = api->new_string_chars(api, "Second argument must be not negative value");
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

SPVM_API_OBJECT* SPVM__Std__Arrays__copy_of_short(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  SPVM_API_OBJECT* original = args[0].object_value;
  
  if (!original) {
    SPVM_API_OBJECT* exception = api->new_string_chars(api, "First argument must be not undef");
    api->set_exception(api, exception);
    return NULL;
  }
  
  int32_t new_length = args[1].int_value;
  
  if (new_length < 0) {
    SPVM_API_OBJECT* exception = api->new_string_chars(api, "Second argument must be not negative value");
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

SPVM_API_OBJECT* SPVM__Std__Arrays__copy_of_int(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  SPVM_API_OBJECT* original = args[0].object_value;
  
  if (!original) {
    SPVM_API_OBJECT* exception = api->new_string_chars(api, "First argument must be not undef");
    api->set_exception(api, exception);
    return NULL;
  }
  
  int32_t new_length = args[1].int_value;
  
  if (new_length < 0) {
    SPVM_API_OBJECT* exception = api->new_string_chars(api, "Second argument must be not negative value");
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

SPVM_API_OBJECT* SPVM__Std__Arrays__copy_of_long(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  SPVM_API_OBJECT* original = args[0].object_value;
  
  if (!original) {
    SPVM_API_OBJECT* exception = api->new_string_chars(api, "First argument must be not undef");
    api->set_exception(api, exception);
    return NULL;
  }
  
  int32_t new_length = args[1].int_value;
  
  if (new_length < 0) {
    SPVM_API_OBJECT* exception = api->new_string_chars(api, "Second argument must be not negative value");
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

SPVM_API_OBJECT* SPVM__Std__Arrays__copy_of_float(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  SPVM_API_OBJECT* original = args[0].object_value;
  
  if (!original) {
    SPVM_API_OBJECT* exception = api->new_string_chars(api, "First argument must be not undef");
    api->set_exception(api, exception);
    return NULL;
  }
  
  int32_t new_length = args[1].int_value;
  
  if (new_length < 0) {
    SPVM_API_OBJECT* exception = api->new_string_chars(api, "Second argument must be not negative value");
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

SPVM_API_OBJECT* SPVM__Std__Arrays__copy_of_double(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  SPVM_API_OBJECT* original = args[0].object_value;
  
  if (!original) {
    SPVM_API_OBJECT* exception = api->new_string_chars(api, "First argument must be not undef");
    api->set_exception(api, exception);
    return NULL;
  }
  
  int32_t new_length = args[1].int_value;
  
  if (new_length < 0) {
    SPVM_API_OBJECT* exception = api->new_string_chars(api, "Second argument must be not negative value");
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
