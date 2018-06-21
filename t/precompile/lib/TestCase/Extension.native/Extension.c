#include <stdlib.h>
#include <string.h>

#include <spvm_native.h>

int32_t SPVM_NATIVE_SUB(TestCase__Extension__native_use_strlen) (SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  void* string = args[0].oval;
  
  int8_t* bytes = env->get_byte_array_elements(env, string);
  
  int32_t length = (int32_t)strlen((char*)bytes);
  
  args[0].ival = length;
  
  return 0;
}

int32_t SPVM_NATIVE_SUB(TestCase__Extension__native_env_get_byte_field) (SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  void* test_case = args[0].oval;
  
  int32_t field_rel_id = env->get_field_rel_id(env, test_case, "x_byte");
  
  int8_t value = env->get_byte_field(env, test_case, field_rel_id);
  
  args[0].bval = value;
  
  return 0;
}

int32_t SPVM_NATIVE_SUB(TestCase__Extension__native_env_get_short_field) (SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  void* test_case = args[0].oval;
  
  int32_t field_rel_id = env->get_field_rel_id(env, test_case, "x_short");
  
  int16_t value = env->get_short_field(env, test_case, field_rel_id);
  
  args[0].sval = value;
  
  return 0;
}

int32_t SPVM_NATIVE_SUB(TestCase__Extension__native_env_get_int_field) (SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  void* test_case = args[0].oval;
  
  int32_t field_rel_id = env->get_field_rel_id(env, test_case, "x_int");
  
  int32_t value = env->get_int_field(env, test_case, field_rel_id);
  
  args[0].ival = value;
  
  return 0;
}

int32_t SPVM_NATIVE_SUB(TestCase__Extension__native_env_get_long_field) (SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  void* test_case = args[0].oval;
  
  int32_t field_rel_id = env->get_field_rel_id(env, test_case, "x_long");
  
  int64_t value = env->get_long_field(env, test_case, field_rel_id);
  
  args[0].ival = value;
  
  return 0;
}

int32_t SPVM_NATIVE_SUB(TestCase__Extension__native_env_get_float_field) (SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  void* test_case = args[0].oval;
  
  int32_t field_rel_id = env->get_field_rel_id(env, test_case, "x_float");
  
  float value = env->get_float_field(env, test_case, field_rel_id);
  
  args[0].fval = value;
  
  return 0;
}

int32_t SPVM_NATIVE_SUB(TestCase__Extension__native_env_get_double_field) (SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  void* test_case = args[0].oval;
  
  int32_t field_rel_id = env->get_field_rel_id(env, test_case, "x_double");
  
  double value = env->get_double_field(env, test_case, field_rel_id);
  
  args[0].ival = value;
  
  return 0;
}

int32_t SPVM_NATIVE_SUB(TestCase__Extension__native_env_get_object_field) (SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  void* test_case = args[0].oval;
  
  int32_t field_rel_id = env->get_field_rel_id(env, test_case, "minimal");
  
  void* value = env->get_object_field(env, test_case, field_rel_id);
  
  args[0].oval = value;
  
  return 0;
}

int32_t SPVM_NATIVE_SUB(TestCase__Extension__sum) (SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  int32_t total = args[0].ival + args[1].ival;
  
  args[0].ival = total;
  
  return 0;
}

int32_t SPVM_NATIVE_SUB(TestCase__Extension__add_int_array) (SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  void* obj_nums1 = args[0].oval;
  void* obj_nums2 = args[1].oval;
  
  int32_t length = env->get_array_length(env, obj_nums1);
  
  int32_t* nums1 = env->get_int_array_elements(env, obj_nums1);
  int32_t* nums2 = env->get_int_array_elements(env, obj_nums2);
  
  void* obj_nums3 = env->new_int_array(env, length);
  int32_t* nums3 = env->get_int_array_elements(env, obj_nums3);
  
  {
    int32_t i;
    for (i = 0; i < length; i++) {
      nums3[i] = nums1[i] + nums2[i];
    }
  }
  
  args[0].oval = obj_nums3;
  
  return 0;
}

int32_t SPVM_NATIVE_SUB(TestCase__Extension__call_void_sub_exception_native) (SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  void* exception = env->new_string(env, "Exception", 0);
  env->set_exception(env, exception);
  
  return 0;
}

int32_t SPVM_NATIVE_SUB(TestCase__Extension__call_byte_sub_exception_native) (SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  void* exception = env->new_string(env, "Exception", 0);
  env->set_exception(env, exception);
  args[0].bval = 0;
  
  return 0;
}

int32_t SPVM_NATIVE_SUB(TestCase__Extension__call_short_sub_exception_native) (SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;

  void* exception = env->new_string(env, "Exception", 0);
  env->set_exception(env, exception);
  args[0].sval = 0;
  
  return 0;
}

int32_t SPVM_NATIVE_SUB(TestCase__Extension__call_int_sub_exception_native) (SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  void* exception = env->new_string(env, "Exception", 0);
  env->set_exception(env, exception);
  args[0].ival = 0;
  
  return 0;
}

int32_t SPVM_NATIVE_SUB(TestCase__Extension__call_long_sub_exception_native) (SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  void* exception = env->new_string(env, "Exception", 0);
  env->set_exception(env, exception);
  args[0].lval = 0;
  
  return 0;
}

float SPVM_NATIVE_SUB(TestCase__Extension__call_float_sub_exception_native) (SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  void* exception = env->new_string(env, "Exception", 0);
  env->set_exception(env, exception);
  return 0;
}

int32_t SPVM_NATIVE_SUB(TestCase__Extension__call_double_sub_exception_native) (SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  void* exception = env->new_string(env, "Exception", 0);
  env->set_exception(env, exception);
  args[0].dval = 0;
  
  return 0;
}

int32_t SPVM_NATIVE_SUB(TestCase__Extension__call_object_sub_exception_native) (SPVM_ENV* env, SPVM_VALUE* args) {
  (void)env;
  (void)args;
  
  void* exception = env->new_string(env, "Exception", 0);
  env->set_exception(env, exception);
  args[0].oval = NULL;
  
  return 0;
}
