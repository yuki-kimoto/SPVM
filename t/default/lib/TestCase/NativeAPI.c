#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <assert.h>

#include <spvm_native.h>

static const char* MFILE = "TestCase/NativeAPI.c";

int32_t SPNATIVE__TestCase__NativeAPI__get_package_var_byte_by_name_test(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e;
  
  int8_t value = env->get_package_var_byte_by_name(env, "TestCase::NativeAPI", "$BYTE_VALUE", &e, MFILE, __LINE__);
  if (e) { return e; }
  
  stack[0].bval = value;

  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__get_package_var_byte_by_name_test_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e;
  
  int8_t value = env->get_package_var_byte_by_name(env, "TestCase::NativeAPI", "$NOT_FOUND", &e, MFILE, __LINE__);
  if (e) { return e; }
  
  stack[0].bval = value;

  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__get_package_var_short_by_name_test(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e;
  
  int16_t value = env->get_package_var_short_by_name(env, "TestCase::NativeAPI", "$SHORT_VALUE", &e, MFILE, __LINE__);
  if (e) { return e; }

  stack[0].sval = value;

  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__get_package_var_short_by_name_test_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e;
  
  int16_t value = env->get_package_var_short_by_name(env, "TestCase::NativeAPI", "$NOT_FOUND", &e, MFILE, __LINE__);
  if (e) { return e; }
  
  stack[0].sval = value;

  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__get_package_var_int_by_name_test(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e;
  
  int32_t value = env->get_package_var_int_by_name(env, "TestCase::NativeAPI", "$INT_VALUE", &e, MFILE, __LINE__);
  if (e) { return e; }
  
  stack[0].ival = value;

  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__get_package_var_int_by_name_test_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e;
  
  int32_t value = env->get_package_var_int_by_name(env, "TestCase::NativeAPI", "$NOT_FOUND", &e, MFILE, __LINE__);
  if (e) { return e; }
  
  stack[0].ival = value;

  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__get_package_var_long_by_name_test(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e;
  
  int64_t value = env->get_package_var_long_by_name(env, "TestCase::NativeAPI", "$LONG_VALUE", &e, MFILE, __LINE__);
  if (e) { return e; }
  
  stack[0].lval = value;

  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__get_package_var_long_by_name_test_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e;
  
  int64_t value = env->get_package_var_long_by_name(env, "TestCase::NativeAPI", "$NOT_FOUND", &e, MFILE, __LINE__);
  if (e) { return e; }
  
  stack[0].lval = value;

  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__get_package_var_float_by_name_test(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e;
  
  float value = env->get_package_var_float_by_name(env, "TestCase::NativeAPI", "$FLOAT_VALUE", &e, MFILE, __LINE__);
  if (e) { return e; }
  
  stack[0].fval = value;

  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__get_package_var_float_by_name_test_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e;
  
  float value = env->get_package_var_float_by_name(env, "TestCase::NativeAPI", "$NOT_FOUND", &e, MFILE, __LINE__);
  if (e) { return e; }
  
  stack[0].fval = value;

  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__get_package_var_double_by_name_test(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e;
  
  double value = env->get_package_var_double_by_name(env, "TestCase::NativeAPI", "$DOUBLE_VALUE", &e, MFILE, __LINE__);
  if (e) { return e; }
  
  stack[0].dval = value;

  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__get_package_var_double_by_name_test_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e;
  
  double value = env->get_package_var_double_by_name(env, "TestCase::NativeAPI", "$NOT_FOUND", &e, MFILE, __LINE__);
  if (e) { return e; }
  
  stack[0].dval = value;

  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__get_package_var_object_test(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  int32_t e;

  void* value = env->get_package_var_object_by_name(env, "TestCase::NativeAPI", "$MINIMAL_VALUE", "TestCase::Minimal", &e, MFILE, __LINE__);
  if (e) { return e; }
  
  stack[0].oval = value;
  
  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__get_package_var_object_by_name_test_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e;
  
  void* value = env->get_package_var_object_by_name(env, "TestCase::NativeAPI", "$NOT_FOUND", "TestCase::Minimal", &e, MFILE, __LINE__);
  if (e) { return e; }
  
  stack[0].oval = value;

  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__set_package_var_byte_by_name_test(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  int32_t e;

  env->set_package_var_byte_by_name(env, "TestCase::NativeAPI", "$BYTE_VALUE", INT8_MIN, &e, MFILE, __LINE__);
  if (e) { return e; }
  
  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__set_package_var_byte_by_name_test_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  int32_t e;

  env->set_package_var_byte_by_name(env, "TestCase::NativeAPI", "$NOT_FOUND", INT8_MIN, &e, MFILE, __LINE__);
  if (e) { return e; }
  
  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__set_package_var_short_by_name_test(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  int32_t e;

  env->set_package_var_short_by_name(env, "TestCase::NativeAPI", "$SHORT_VALUE", INT16_MIN, &e, MFILE, __LINE__);
  if (e) { return e; }
  
  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__set_package_var_short_by_name_test_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  int32_t e;

  env->set_package_var_short_by_name(env, "TestCase::NativeAPI", "$NOT_FOUND", INT16_MIN, &e, MFILE, __LINE__);
  if (e) { return e; }
  
  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__set_package_var_int_by_name_test(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  int32_t e;

  env->set_package_var_int_by_name(env, "TestCase::NativeAPI", "$INT_VALUE", INT32_MIN, &e, MFILE, __LINE__);
  if (e) { return e; }
  
  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__set_package_var_int_by_name_test_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  int32_t e;

  env->set_package_var_int_by_name(env, "TestCase::NativeAPI", "$NOT_FOUND", INT32_MIN, &e, MFILE, __LINE__);
  if (e) { return e; }
  
  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__set_package_var_long_by_name_test(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  int32_t e;
  
  env->set_package_var_long_by_name(env, "TestCase::NativeAPI", "$LONG_VALUE", INT64_MIN, &e, MFILE, __LINE__);
  if (e) { return e; }
  
  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__set_package_var_long_by_name_test_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  int32_t e;
  
  env->set_package_var_long_by_name(env, "TestCase::NativeAPI", "$NOT_FOUND", INT64_MIN, &e, MFILE, __LINE__);
  if (e) { return e; }
  
  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__set_package_var_float_by_name_test(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  int32_t e;

  env->set_package_var_float_by_name(env, "TestCase::NativeAPI", "$FLOAT_VALUE", FLT_MIN, &e, MFILE, __LINE__);
  if (e) { return e; }
  
  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__set_package_var_float_by_name_test_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  int32_t e;

  env->set_package_var_float_by_name(env, "TestCase::NativeAPI", "$NOT_FOUND", FLT_MIN, &e, MFILE, __LINE__);
  if (e) { return e; }
  
  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__set_package_var_double_by_name_test(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  int32_t e;

  env->set_package_var_double_by_name(env, "TestCase::NativeAPI", "$DOUBLE_VALUE", DBL_MIN, &e, MFILE, __LINE__);
  if (e) { return e; }
  
  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__set_package_var_double_by_name_test_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  int32_t e;

  env->set_package_var_double_by_name(env, "TestCase::NativeAPI", "$NOT_FOUND", DBL_MIN, &e, MFILE, __LINE__);
  if (e) { return e; }
  
  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__set_package_var_object_by_name_test(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  int32_t e;
  
  void* minimal = env->new_object_by_name(env, "TestCase::Minimal", &e, MFILE, __LINE__);
  if (e) { return e; }
  
  env->set_package_var_object_by_name(env, "TestCase::NativeAPI", "$MINIMAL_VALUE", "TestCase::Minimal", minimal, &e, MFILE, __LINE__);
  
  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__set_package_var_object_by_name_test_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e;
  void* minimal = env->new_object_by_name(env, "TestCase::Minimal", &e, MFILE, __LINE__);
  
  env->set_package_var_object_by_name(env, "TestCase::NativeAPI", "$NOT_FOUND", "TestCase::Minimal", minimal, &e, MFILE, __LINE__);
  if (e) { return e; }
  
  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__native_new_object_by_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e;
  void* minimal = env->new_object_by_name(env, "TestCase::Minimal", &e, MFILE, __LINE__);
  if (e) { return e; }
  
  stack[0].oval = minimal;
  
  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__native_new_object_by_name_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e;
  void* minimal = env->new_object_by_name(env, "NotFound", &e, MFILE, __LINE__);
  if (e) { return e; }
  
  stack[0].oval = minimal;
  
  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__native_new_pointer_by_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  void* pointer;
  
  int32_t e;
  void* minimal = env->new_pointer_by_name(env, "TestCase::Pointer", pointer, &e, MFILE, __LINE__);
  if (e) { return e; }
  
  stack[0].oval = minimal;
  
  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__native_new_pointer_by_name_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  void* pointer;
  int32_t e;
  void* minimal = env->new_pointer_by_name(env, "TestCase::NotFound", pointer, &e, MFILE, __LINE__);
  if (e) { return e; }
  
  stack[0].oval = minimal;
  
  return 0;
}


int32_t SPNATIVE__TestCase__NativeAPI__has_callback_test(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  void* object = stack[0].oval;
  
  int32_t basic_type_id = env->get_basic_type_id(env, "TestCase::Callback::Callback");
  if (basic_type_id < 0) {
    assert(0);
  }
  
  int32_t match = env->has_callback(env, object, basic_type_id);
  
  stack[0].ival = match;
  
  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__is_type_test_minimals(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  void* object = stack[0].oval;
  
  int32_t basic_type_id = env->get_basic_type_id(env, "TestCase::Minimal");
  if (basic_type_id < 0) {
    assert(0);
  }
  
  int32_t match = env->is_type(env, object, basic_type_id, 1);
  
  stack[0].ival = match;
  
  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__ref_byte_sum(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int8_t x_in1 = stack[0].bval;
  int8_t x_in2 = stack[1].bval;
  
  *(stack[2].bref) = x_in1 + x_in2;
  
  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__ref_short_sum(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int16_t x_in1 = stack[0].sval;
  int16_t x_in2 = stack[1].sval;
  
  *(stack[2].sref) = x_in1 + x_in2;
  
  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__ref_int_sum(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t x_in1 = stack[0].ival;
  int32_t x_in2 = stack[1].ival;
  
  *(stack[2].iref) = x_in1 + x_in2;
  
  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__ref_long_sum(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int64_t x_in1 = stack[0].lval;
  int64_t x_in2 = stack[1].lval;
  
  *(stack[2].lref) = x_in1 + x_in2;
  
  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__ref_float_sum(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  float x_in1 = stack[0].fval;
  float x_in2 = stack[1].fval;
  
  *(stack[2].fref) = x_in1 + x_in2;
  
  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__ref_double_sum(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  double x_in1 = stack[0].dval;
  double x_in2 = stack[1].dval;
  
  *(stack[2].dref) = x_in1 + x_in2;
  
  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__native_set_field_byte_by_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e;
  
  void* object = stack[0].oval;
  
  env->set_field_byte_by_name(env, object, "TestCase::Simple", "byte_value", INT8_MIN, &e, MFILE, __LINE__);
  if (e) { return e; }
  
  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__native_set_field_byte_by_name_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e;
  
  void* object = stack[0].oval;
  
  env->set_field_byte_by_name(env, object, "TestCase::Simple", "not_found", INT8_MIN, &e, MFILE, __LINE__);
  if (e) { return e; }
  
  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__native_set_field_short_by_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  int32_t e;
  void* object = stack[0].oval;
  
  env->set_field_short_by_name(env, object, "TestCase::Simple", "short_value", INT16_MIN, &e, MFILE, __LINE__);
  if (e) { return e; }
  
  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__native_set_field_short_by_name_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  int32_t e;
  void* object = stack[0].oval;
  
  env->set_field_short_by_name(env, object, "TestCase::Simple", "not_found", INT16_MIN, &e, MFILE, __LINE__);
  if (e) { return e; }
  
  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__native_set_field_int_by_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  int32_t e;
  void* object = stack[0].oval;
  
  env->set_field_int_by_name(env, object, "TestCase::Simple", "int_value", INT32_MIN, &e, MFILE, __LINE__);
  if (e) { return e; }
  
  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__native_set_field_int_by_name_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  int32_t e;
  void* object = stack[0].oval;
  
  env->set_field_int_by_name(env, object, "TestCase::Simple", "not_found", INT32_MIN, &e, MFILE, __LINE__);
  if (e) { return e; }
  
  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__native_set_field_long_by_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  int32_t e;
  void* object = stack[0].oval;
  
  env->set_field_long_by_name(env, object, "TestCase::Simple", "long_value", INT64_MIN, &e, MFILE, __LINE__);
  if (e) { return e; }
  
  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__native_set_field_long_by_name_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  int32_t e;
  void* object = stack[0].oval;
  
  env->set_field_long_by_name(env, object, "TestCase::Simple", "not_found", INT64_MIN, &e, MFILE, __LINE__);
  if (e) { return e; }
  
  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__native_set_field_float_by_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  int32_t e;
  void* object = stack[0].oval;
  
  env->set_field_float_by_name(env, object, "TestCase::Simple", "float_value", FLT_MIN, &e, MFILE, __LINE__);
  if (e) { return e; }
  
  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__native_set_field_float_by_name_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  int32_t e;
  void* object = stack[0].oval;
  
  env->set_field_float_by_name(env, object, "TestCase::Simple", "not_found", FLT_MIN, &e, MFILE, __LINE__);
  if (e) { return e; }
  
  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__native_set_field_double_by_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  int32_t e;
  void* object = stack[0].oval;
  
  env->set_field_double_by_name(env, object, "TestCase::Simple", "double_value", DBL_MIN, &e, MFILE, __LINE__);
  if (e) { return e; }
  
  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__native_set_field_double_by_name_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  int32_t e;
  void* object = stack[0].oval;
  
  env->set_field_double_by_name(env, object, "TestCase::Simple", "not_found", DBL_MIN, &e, MFILE, __LINE__);
  if (e) { return e; }
  
  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__native_set_field_object_by_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e;
  void* object_simple = stack[0].oval;
  
  int32_t basic_type_id = env->get_basic_type_id(env, "TestCase::Minimal");
  if (basic_type_id < 0) {
    return 1;
  }
  void* object_minimal = env->new_object(env, basic_type_id);
  
  int32_t field_id_minimal_x = env->get_field_id(env, "TestCase::Minimal", "x", "int");
  if (field_id_minimal_x < 0) {
    return 1;
  }
  env->set_field_int(env, object_minimal, field_id_minimal_x, 3);
  
  env->set_field_object_by_name(env, object_simple, "TestCase::Simple", "object_value", "TestCase::Minimal", object_minimal, &e, MFILE, __LINE__);
  
  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__native_set_field_object_by_name_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t e;
  void* object_simple = stack[0].oval;
  
  int32_t basic_type_id = env->get_basic_type_id(env, "TestCase::Minimal");
  if (basic_type_id < 0) {
    return 1;
  }
  void* object_minimal = env->new_object(env, basic_type_id);
  
  int32_t field_id_minimal_x = env->get_field_id(env, "TestCase::Minimal", "x", "int");
  if (field_id_minimal_x < 0) {
    return 1;
  }
  env->set_field_int(env, object_minimal, field_id_minimal_x, 3);
  
  env->set_field_object_by_name(env, object_simple, "TestCase::Simple", "not_found", "TestCase::Minimal", object_minimal, &e, MFILE, __LINE__);
  
  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__native_get_field_byte_by_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  int32_t e;
  void* object = stack[0].oval;
  
  int8_t byte_value = env->get_field_byte_by_name(env, object, "TestCase::Simple", "byte_value", &e, MFILE, __LINE__);
  if (e) { return e; }
  
  if (byte_value == INT8_MIN) {
    stack[0].ival = 1;
  }
  else {
    stack[0].ival = 0;
  }
  
  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__native_get_field_byte_by_name_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  int32_t e;
  void* object = stack[0].oval;
  
  int8_t byte_value = env->get_field_byte_by_name(env, object, "TestCase::Simple", "not_found", &e, MFILE, __LINE__);
  if (e) { return e; }
  
  if (byte_value == INT8_MIN) {
    stack[0].ival = 1;
  }
  else {
    stack[0].ival = 0;
  }
  
  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__native_get_field_short_by_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  int32_t e;

  void* object = stack[0].oval;
  
  int16_t short_value = env->get_field_short_by_name(env, object, "TestCase::Simple", "short_value", &e, MFILE, __LINE__);
  if (e) { return e; }
  
  if (short_value == INT16_MIN) {
    stack[0].ival = 1;
  }
  else {
    stack[0].ival = 0;
  }
  
  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__native_get_field_short_by_name_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  int32_t e;

  void* object = stack[0].oval;
  
  int16_t short_value = env->get_field_short_by_name(env, object, "TestCase::Simple", "not_found", &e, MFILE, __LINE__);
  if (e) { return e; }
  
  if (short_value == INT16_MIN) {
    stack[0].ival = 1;
  }
  else {
    stack[0].ival = 0;
  }
  
  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__native_get_field_int_by_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  int32_t e;

  void* object = stack[0].oval;
  
  int32_t int_value = env->get_field_int_by_name(env, object, "TestCase::Simple", "int_value", &e, MFILE, __LINE__);
  if (e) { return e; }
  
  if (int_value == INT32_MIN) {
    stack[0].ival = 1;
  }
  else {
    stack[0].ival = 0;
  }
  
  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__native_get_field_int_by_name_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  int32_t e;

  void* object = stack[0].oval;
  
  int32_t int_value = env->get_field_int_by_name(env, object, "TestCase::Simple", "not_found", &e, MFILE, __LINE__);
  if (e) { return e; }
  
  if (int_value == INT32_MIN) {
    stack[0].ival = 1;
  }
  else {
    stack[0].ival = 0;
  }
  
  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__native_get_field_long_by_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  int32_t e;

  void* object = stack[0].oval;
  
  int64_t long_value = env->get_field_long_by_name(env, object, "TestCase::Simple", "long_value", &e, MFILE, __LINE__);
  if (e) { return e; }
  
  if (long_value == INT64_MIN) {
    stack[0].ival = 1;
  }
  else {
    stack[0].ival = 0;
  }
  
  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__native_get_field_long_by_name_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  int32_t e;

  void* object = stack[0].oval;
  
  int64_t long_value = env->get_field_long_by_name(env, object, "TestCase::Simple", "not_found", &e, MFILE, __LINE__);
  if (e) { return e; }
  
  if (long_value == INT64_MIN) {
    stack[0].ival = 1;
  }
  else {
    stack[0].ival = 0;
  }
  
  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__native_get_field_float_by_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  int32_t e;

  void* object = stack[0].oval;
  
  float float_value = env->get_field_float_by_name(env, object, "TestCase::Simple", "float_value", &e, MFILE, __LINE__);
  if (e) { return e; }
  
  if (float_value == FLT_MIN) {
    stack[0].ival = 1;
  }
  else {
    stack[0].ival = 0;
  }
  
  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__native_get_field_float_by_name_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  int32_t e;

  void* object = stack[0].oval;
  
  float float_value = env->get_field_float_by_name(env, object, "TestCase::Simple", "not_found", &e, MFILE, __LINE__);
  if (e) { return e; }
  
  if (float_value == FLT_MIN) {
    stack[0].ival = 1;
  }
  else {
    stack[0].ival = 0;
  }
  
  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__native_get_field_double_by_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  int32_t e;

  void* object = stack[0].oval;
  
  double double_value = env->get_field_double_by_name(env, object, "TestCase::Simple", "double_value", &e, MFILE, __LINE__);
  if (e) { return e; }
  
  if (double_value == DBL_MIN) {
    stack[0].ival = 1;
  }
  else {
    stack[0].ival = 0;
  }
  
  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__native_get_field_double_by_name_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  int32_t e;

  void* object = stack[0].oval;
  
  double double_value = env->get_field_double_by_name(env, object, "TestCase::Simple", "not_found", &e, MFILE, __LINE__);
  if (e) { return e; }
  
  if (double_value == DBL_MIN) {
    stack[0].ival = 1;
  }
  else {
    stack[0].ival = 0;
  }
  
  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__native_get_field_object_by_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  int32_t e;
  
  void* object_simple = stack[0].oval;
  
  void* object_minimal = env->get_field_object_by_name(env, object_simple, "TestCase::Simple", "object_value", "TestCase::Minimal", &e, MFILE, __LINE__);
  if (e) { return e; }
  
  int32_t field_id_minimal_x = env->get_field_id(env, "TestCase::Minimal", "x", "int");
  if (field_id_minimal_x < 0) {
    return 1;
  }
  
  int32_t x = env->get_field_int(env, object_minimal, field_id_minimal_x);
  
  if (x == 5) {
    stack[0].ival = 1;
  }
  else {
    stack[0].ival = 0;
  }
  
  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__native_get_field_string_chars_by_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  int32_t e;
  
  void* string_chars_simple = stack[0].oval;
  
  const char* string_chars = env->get_field_string_chars_by_name(env, string_chars_simple, "TestCase::Simple", "string_value", &e, MFILE, __LINE__);
  if (e) { return e; };
  
  if (strcmp(string_chars, "abc") == 0) {
    stack[0].ival = 1;
  }
  else {
    stack[0].ival = 0;
  }
  
  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__native_get_field_string_chars_by_name_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  int32_t e;
  
  void* string_chars_simple = stack[0].oval;
  
  const char* string_chars = env->get_field_string_chars_by_name(env, string_chars_simple, "TestCase::Simple", "not_found", &e, MFILE, __LINE__);
  if (e) {
    stack[0].ival = 1;
  }
  else {
    stack[0].ival = 0;
  }
  
  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__native_get_field_object_by_name_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  int32_t e;
  
  void* object_simple = stack[0].oval;
  
  void* object_minimal = env->get_field_object_by_name(env, object_simple, "TestCase::Simple", "not_found", "TestCase::Minimal", &e, MFILE, __LINE__);
  if (e) { return e; }
  
  int32_t field_id_minimal_x = env->get_field_id(env, "TestCase::Minimal", "x", "int");
  if (field_id_minimal_x < 0) {
    return 1;
  }
  
  int32_t x = env->get_field_int(env, object_minimal, field_id_minimal_x);
  
  if (x == 5) {
    stack[0].ival = 1;
  }
  else {
    stack[0].ival = 0;
  }
  
  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__native_use_strlen(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  void* string = stack[0].oval;
  
  int8_t* bytes = env->get_elems_byte(env, string);
  
  int32_t length = (int32_t)strlen((char*)bytes);
  
  stack[0].ival = length;
  
  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__native_env_get_field_byte(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  void* test_case = stack[0].oval;
  
  int32_t field_id = env->get_field_id(env, test_case, "x_byte", "byte");
  if (field_id < 0) {
    return 1;
  }
  
  int8_t value = env->get_field_byte(env, test_case, field_id);
  
  stack[0].bval = value;
  
  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__native_env_get_field_short(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  void* test_case = stack[0].oval;
  
  int32_t field_id = env->get_field_id(env, test_case, "x_short", "short");
  if (field_id < 0) {
    return 1;
  }
  
  int16_t value = env->get_field_short(env, test_case, field_id);
  
  stack[0].sval = value;
  
  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__native_env_get_field_int(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  void* test_case = stack[0].oval;
  
  int32_t field_id = env->get_field_id(env, test_case, "x_int", "int");
  if (field_id < 0) {
    return 1;
  }
  
  int32_t value = env->get_field_int(env, test_case, field_id);
  
  stack[0].ival = value;
  
  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__native_env_get_field_long(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  void* test_case = stack[0].oval;
  
  int32_t field_id = env->get_field_id(env, test_case, "x_long", "long");
  if (field_id < 0) {
    return 1;
  }
  
  int64_t value = env->get_field_long(env, test_case, field_id);
  
  stack[0].ival = value;
  
  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__native_env_get_field_float(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  void* test_case = stack[0].oval;
  
  int32_t field_id = env->get_field_id(env, test_case, "x_float", "float");
  if (field_id < 0) {
    return 1;
  }
  
  float value = env->get_field_float(env, test_case, field_id);
  
  stack[0].fval = value;
  
  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__native_env_get_field_double(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  void* test_case = stack[0].oval;
  
  int32_t field_id = env->get_field_id(env, test_case, "x_double", "double");
  if (field_id < 0) {
    return 1;
  }
  
  double value = env->get_field_double(env, test_case, field_id);
  
  stack[0].ival = value;
  
  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__native_env_get_field_object(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  void* test_case = stack[0].oval;
  
  int32_t field_id = env->get_field_id(env, test_case, "minimal", "TestCase::Minimal");
  if (field_id < 0) {
    return 1;
  }
  
  void* value = env->get_field_object(env, test_case, field_id);
  
  stack[0].oval = value;
  
  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__sum(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t total = stack[0].ival + stack[1].ival;
  
  stack[0].ival = total;
  
  return 0;
}


int32_t SPNATIVE__TestCase__NativeAPI__add_int_array(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  void* obj_nums1 = stack[0].oval;
  void* obj_nums2 = stack[1].oval;
  
  int32_t length = env->length(env, obj_nums1);
  
  int32_t* nums1 = env->get_elems_int(env, obj_nums1);
  int32_t* nums2 = env->get_elems_int(env, obj_nums2);
  
  void* onums3 = env->new_int_array(env, length);
  int32_t* nums3 = env->get_elems_int(env, onums3);
  
  for (int32_t i = 0; i < length; i++) {
    nums3[i] = nums1[i] + nums2[i];
  }
  
  stack[0].oval = onums3;
  
  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__call_void_sub_exception_native(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  return env->die(env, "Exception %s", "ppp", "TestCase/NativeAPI.native/NativeAPI.c", __LINE__);
}

int32_t SPNATIVE__TestCase__NativeAPI__call_byte_sub_exception_native(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  return env->die(env, "Exception", "TestCase/NativeAPI.native/NativeAPI.c", __LINE__);
}

int32_t SPNATIVE__TestCase__NativeAPI__call_short_sub_exception_native(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  return env->die(env, "Exception", "TestCase/NativeAPI.native/NativeAPI.c", __LINE__);
}

int32_t SPNATIVE__TestCase__NativeAPI__call_int_sub_exception_native(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  return env->die(env, "Exception", "TestCase/NativeAPI.native/NativeAPI.c", __LINE__);
}

int32_t SPNATIVE__TestCase__NativeAPI__call_long_sub_exception_native(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  return env->die(env, "Exception", "TestCase/NativeAPI.native/NativeAPI.c", __LINE__);
}

float SPNATIVE__TestCase__NativeAPI__call_float_sub_exception_native(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  return env->die(env, "Exception", "TestCase/NativeAPI.native/NativeAPI.c", __LINE__);
}

int32_t SPNATIVE__TestCase__NativeAPI__call_double_sub_exception_native(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  return env->die(env, "Exception", "TestCase/NativeAPI.native/NativeAPI.c", __LINE__);
}

int32_t SPNATIVE__TestCase__NativeAPI__call_object_sub_exception_native(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  return env->die(env, "Exception", "TestCase/NativeAPI.native/NativeAPI.c", __LINE__);
}

int32_t SPNATIVE__TestCase__NativeAPI__mortal_api(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  // Check if object count is zero in extension.t
  int32_t ref_count = 0;
  
  int32_t length = 10;
  // 1
  {
    void* sp_values = env->new_byte_array(env, length);
    ref_count += env->get_ref_count(env, sp_values);
  }
  // 2
  {
    void* sp_values = env->new_short_array(env, length);
    ref_count += env->get_ref_count(env, sp_values);
  }
  // 3
  {
    void* sp_values = env->new_int_array(env, length);
    ref_count += env->get_ref_count(env, sp_values);
  }
  // 4
  {
    void* sp_values = env->new_long_array(env, length);
    ref_count += env->get_ref_count(env, sp_values);
  }
  // 5
  {
    void* sp_values = env->new_float_array(env, length);
    ref_count += env->get_ref_count(env, sp_values);
  }
  // 6
  {
    void* sp_values = env->new_long_array(env, length);
    ref_count += env->get_ref_count(env, sp_values);
  }
  // 7
  {
    void* sp_values = env->new_string(env, "foo", (int32_t)strlen("foo"));
    ref_count += env->get_ref_count(env, sp_values);
  }
  // 8
  {
    int32_t basic_type_id = env->get_basic_type_id(env, "TestCase::Minimal");
    if (basic_type_id < 0) {
      return 1;
    }
    void* sp_object = env->new_object(env, basic_type_id);
    ref_count += env->get_ref_count(env, sp_object);
  }
  // 9
  {
    int32_t basic_type_id = env->get_basic_type_id(env, "TestCase::Minimal");
    if (basic_type_id < 0) {
      return 1;
    }
    void* sp_objects = env->new_object_array(env, basic_type_id, 3);
    ref_count += env->get_ref_count(env, sp_objects);
  }
  // 10
  {
    int32_t basic_type_id = env->get_basic_type_id(env, "TestCase::Minimal");
    if (basic_type_id < 0) {
      return 1;
    }
    void* sp_objects = env->new_object_array(env, basic_type_id, 3);
    ref_count += env->get_ref_count(env, sp_objects);
  }
  // 11
  {
    int32_t basic_type_id = env->get_basic_type_id(env, "TestCase::Pointer");
    if (basic_type_id < 0) {
      return 1;
    }
    void* sp_objects = env->new_pointer(env, basic_type_id, NULL);
    ref_count += env->get_ref_count(env, sp_objects);
  }
  
  if (ref_count == 11) {
    stack[0].ival = 1;
  }
  else {
    stack[0].ival = 0;
  }
  
  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__enter_scope_leave_scope(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t length = 10;
  int32_t start_memory_blocks_count = env->get_memory_blocks_count(env);
  env->new_int_array(env, length);
  env->new_int_array(env, length);
  int32_t before_enter_memory_blocks_count = env->get_memory_blocks_count(env);
  int32_t before_leave_memory_blocks_count;
  {
    int32_t scope_id = env->enter_scope(env);

    env->new_int_array(env, length);
    env->new_int_array(env, length);
    env->new_int_array(env, length);
    
    before_leave_memory_blocks_count = env->get_memory_blocks_count(env);
    env->leave_scope(env, scope_id);
  }
  
  int32_t after_leave_memory_blocks_counts = env->get_memory_blocks_count(env);
  
  stack[0].ival = 0;
  if ((before_enter_memory_blocks_count - start_memory_blocks_count) == 2) {
    if (before_enter_memory_blocks_count == after_leave_memory_blocks_counts) {
      if ((before_leave_memory_blocks_count - before_enter_memory_blocks_count) == 3) {
        stack[0].ival = 1;
      }
    }
  }
  
  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__native_call_sub(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t sub_id = env->get_sub_id(env, "TestCase::NativeAPI", "my_value", "int(int)");
  if (sub_id < 0) {
    return 1;
  }
  int32_t output;
  {
    stack[0].ival = 5;
    int32_t exception_flag = env->call_sub(env, sub_id, stack);
    if (exception_flag) {
      return 1;
    }
    output = stack[0].ival;
  }
  
  stack[0].ival = 0;
  
  if (output == 5) {
    stack[0].ival = 1;
  }
  
  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__native_call_sub_by_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t output;
  {
    stack[0].ival = 5;
    int32_t exception_flag = env->call_sub_by_name(env, "TestCase::NativeAPI", "my_value", "int(int)", stack, MFILE, __LINE__);
    if (exception_flag) {
      return exception_flag;
    }
    output = stack[0].ival;
  }
  
  stack[0].ival = 0;
  
  if (output == 5) {
    stack[0].ival = 1;
  }
  
  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__native_call_sub_by_name_exception(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  int32_t output;
  {
    stack[0].ival = 5;
    int32_t exception_flag = env->call_sub_by_name(env, "TestCase::NativeAPI", "not_found", "int(int)", stack, MFILE, __LINE__);
    if (exception_flag) {
      return exception_flag;
    }
    output = stack[0].ival;
  }
  
  stack[0].ival = 0;
  
  if (output == 5) {
    stack[0].ival = 1;
  }
  
  return 0;
}

int32_t SPNATIVE__TestCase__NativeAPI__push_mortal_multi(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  void* iarray = env->new_int_array_raw(env, 10);
  
  env->push_mortal(env, iarray);
  env->push_mortal(env, iarray);
  
  return 0;
}
