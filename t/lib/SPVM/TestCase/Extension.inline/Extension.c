#include <stdlib.h>
#include <string.h>

#include <spvm_api.h>

int8_t SPVM__TestCase__Extension__native_use_strlen(SPVM_API* api, const SPVM_VALUE* args) {
  (void)api;
  (void)args;
  
  SPVM_object* string = args[0].oval;
  
  int8_t* bytes = api->get_byte_array_elements(api, string);
  
  int8_t length = (int8_t)strlen((char*)bytes);
  
  return length;
}

int8_t SPVM__TestCase__Extension__native_api_get_byte_field(SPVM_API* api, const SPVM_VALUE* args) {
  (void)api;
  (void)args;
  
  SPVM_object* test_case = args[0].oval;
  
  int32_t field_id = api->get_field_id(api, test_case, "x_byte");
  
  int8_t value = api->get_byte_field(api, test_case, field_id);
  
  return value;
}

int16_t SPVM__TestCase__Extension__native_api_get_short_field(SPVM_API* api, const SPVM_VALUE* args) {
  (void)api;
  (void)args;
  
  SPVM_object* test_case = args[0].oval;
  
  int32_t field_id = api->get_field_id(api, test_case, "x_short");
  
  int16_t value = api->get_short_field(api, test_case, field_id);
  
  return value;
}

int32_t SPVM__TestCase__Extension__native_api_get_int_field(SPVM_API* api, const SPVM_VALUE* args) {
  (void)api;
  (void)args;
  
  SPVM_object* test_case = args[0].oval;
  
  int32_t field_id = api->get_field_id(api, test_case, "x_int");
  
  int32_t value = api->get_int_field(api, test_case, field_id);
  
  return value;
}

int64_t SPVM__TestCase__Extension__native_api_get_long_field(SPVM_API* api, const SPVM_VALUE* args) {
  (void)api;
  (void)args;
  
  SPVM_object* test_case = args[0].oval;
  
  int32_t field_id = api->get_field_id(api, test_case, "x_long");
  
  int64_t value = api->get_long_field(api, test_case, field_id);
  
  return value;
}

float SPVM__TestCase__Extension__native_api_get_float_field(SPVM_API* api, const SPVM_VALUE* args) {
  (void)api;
  (void)args;
  
  SPVM_object* test_case = args[0].oval;
  
  int32_t field_id = api->get_field_id(api, test_case, "x_float");
  
  float value = api->get_float_field(api, test_case, field_id);
  
  return value;
}

int32_t SPVM__TestCase__Extension__native_api_get_double_field(SPVM_API* api, const SPVM_VALUE* args) {
  (void)api;
  (void)args;
  
  SPVM_object* test_case = args[0].oval;
  
  int32_t field_id = api->get_field_id(api, test_case, "x_double");
  
  double value = api->get_double_field(api, test_case, field_id);
  
  return value;
}

SPVM_object* SPVM__TestCase__Extension__native_api_get_object_field(SPVM_API* api, const SPVM_VALUE* args) {
  (void)api;
  (void)args;
  
  SPVM_object* test_case = args[0].oval;
  
  int32_t field_id = api->get_field_id(api, test_case, "minimal");
  
  SPVM_object* value = api->get_object_field(api, test_case, field_id);
  
  return value;
}

int32_t SPVM__TestCase__Extension__sum(SPVM_API* api, const SPVM_VALUE* args) {
  (void)api;
  (void)args;
  
  int32_t total = args[0].ival + args[1].ival;
  
  return total;
}

SPVM_object* SPVM__TestCase__Extension__add_int_array(SPVM_API* api, const SPVM_VALUE* args) {
  (void)api;
  (void)args;
  
  SPVM_object* obj_nums1 = args[0].oval;
  SPVM_object* obj_nums2 = args[1].oval;
  
  int32_t length = api->get_array_length(api, obj_nums1);
  
  int32_t* nums1 = api->get_int_array_elements(api, obj_nums1);
  int32_t* nums2 = api->get_int_array_elements(api, obj_nums2);
  
  SPVM_object* obj_nums3 = api->new_int_array(api, length);
  int32_t* nums3 = api->get_int_array_elements(api, obj_nums3);
  
  {
    int32_t i;
    for (i = 0; i < length; i++) {
      nums3[i] = nums1[i] + nums2[i];
    }
  }
  
  return obj_nums3;
}

void SPVM__TestCase__Extension__call_void_sub_exception_native(SPVM_API* api, const SPVM_VALUE* args) {
  (void)api;
  (void)args;
  
  SPVM_object* exception = api->new_string(api, "Exception", 0);
  api->set_exception(api, exception);
  return;
}

int8_t SPVM__TestCase__Extension__call_byte_sub_exception_native(SPVM_API* api, const SPVM_VALUE* args) {
  (void)api;
  (void)args;
  
  SPVM_object* exception = api->new_string(api, "Exception", 0);
  api->set_exception(api, exception);
  return 0;
}

int16_t SPVM__TestCase__Extension__call_short_sub_exception_native(SPVM_API* api, const SPVM_VALUE* args) {
  (void)api;
  (void)args;

  SPVM_object* exception = api->new_string(api, "Exception", 0);
  api->set_exception(api, exception);
  return 0;
}

int32_t SPVM__TestCase__Extension__call_int_sub_exception_native(SPVM_API* api, const SPVM_VALUE* args) {
  (void)api;
  (void)args;
  
  SPVM_object* exception = api->new_string(api, "Exception", 0);
  api->set_exception(api, exception);
  return 0;
}

int64_t SPVM__TestCase__Extension__call_long_sub_exception_native(SPVM_API* api, const SPVM_VALUE* args) {
  (void)api;
  (void)args;
  
  SPVM_object* exception = api->new_string(api, "Exception", 0);
  api->set_exception(api, exception);
  return 0;
}

float SPVM__TestCase__Extension__call_float_sub_exception_native(SPVM_API* api, const SPVM_VALUE* args) {
  (void)api;
  (void)args;
  
  SPVM_object* exception = api->new_string(api, "Exception", 0);
  api->set_exception(api, exception);
  return 0;
}

double SPVM__TestCase__Extension__call_double_sub_exception_native(SPVM_API* api, const SPVM_VALUE* args) {
  (void)api;
  (void)args;
  
  SPVM_object* exception = api->new_string(api, "Exception", 0);
  api->set_exception(api, exception);
  return 0;
}

SPVM_object* SPVM__TestCase__Extension__call_object_sub_exception_native(SPVM_API* api, const SPVM_VALUE* args) {
  (void)api;
  (void)args;
  
  SPVM_object* exception = api->new_string(api, "Exception", 0);
  api->set_exception(api, exception);
  return NULL;
}
