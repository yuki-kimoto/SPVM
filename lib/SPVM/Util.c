#include "spvm_native.h"

static const char* MFILE = "SPVM/Util.c";

#define SPRINTF_MAX_RESULT_LEN 256

int32_t SPNATIVE__SPVM__Util___convert_f_to_str(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  void* obj_format = stack[0].oval;
  if (!obj_format) { SPVM_DIE("Format must be defined", MFILE, __LINE__); }

  const char* format = (const char*)env->get_elems_byte(env, obj_format);
  const double value = stack[1].dval;

  char tmp_result[SPRINTF_MAX_RESULT_LEN] = {};

  const int result_len = snprintf(tmp_result, SPRINTF_MAX_RESULT_LEN, format, value);
  if (result_len < 0) { SPVM_DIE("snprintf fail", MFILE, __LINE__); }

  stack[0].oval = env->new_string_len(env, tmp_result, result_len);

  return SPVM_SUCCESS;
}
