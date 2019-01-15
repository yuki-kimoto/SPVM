#ifndef SPVM_NATIVE_H
#define SPVM_NATIVE_H

#include <stdint.h>

struct SPVM_env;
typedef struct SPVM_env SPVM_ENV;

typedef union SPVM_value SPVM_VALUE;

union SPVM_value {
  int8_t bval;
  int16_t sval;
  int32_t ival;
  int64_t lval;
  float fval;
  double dval;
  void* oval;
  int8_t* bref;
  int16_t* sref;
  int32_t* iref;
  int64_t* lref;
  float* fref;
  double* dref;
};

typedef int8_t SPVM_VALUE_byte;
typedef int16_t SPVM_VALUE_short;
typedef int32_t SPVM_VALUE_int;
typedef int64_t SPVM_VALUE_long;
typedef float SPVM_VALUE_float;
typedef double SPVM_VALUE_double;
typedef void* SPVM_VALUE_object;

#define SPVM_SUCCESS 0
#define SPVM_EXCEPTION 1

#define SPVM_CROAK(message, file, line) do {\
  void* exception = env->new_str_raw(env, message " at " file " line " #line, 0);\
  env->set_exception(env, exception);\
  return SPVM_EXCEPTION;\
} while (0)\


struct SPVM_env {
  void* exception_object;
  void* native_mortal_stack;
  void* native_mortal_stack_top;
  void* native_mortal_stack_capacity;
  void* runtime;
  void* runtime_package_vars_heap_offset;
  void* object_header_byte_size;
  void* object_ref_count_offset;
  void* object_basic_type_id_offset;
  void* object_type_dimension_offset;
  void* object_array_length_offset;
  void* byte_object_basic_type_id;
  void* short_object_basic_type_id;
  void* int_object_basic_type_id;
  void* long_object_basic_type_id;
  void* float_object_basic_type_id;
  void* double_object_basic_type_id;
  int32_t (*memory_blocks_count)(SPVM_ENV* env);
  void* (*new_env)(SPVM_ENV*);
  void (*free_env)(SPVM_ENV*);
  void* (*exception)(SPVM_ENV* env);
  void (*set_exception)(SPVM_ENV* env, void* exception);
  int32_t (*sub_id)(SPVM_ENV*, const char*, const char*, const char*);
  int32_t (*method_sub_id)(SPVM_ENV*, void* object, const char*, const char*);
  int32_t (*basic_type_id)(SPVM_ENV*, const char*);
  int32_t (*pkgvar_id)(SPVM_ENV* env, const char* package_name, const char* pkgvar_name, const char* signature);
  int32_t (*field_offset)(SPVM_ENV*, int32_t);
  int32_t (*call_sub)(SPVM_ENV* env, int32_t sub_id, SPVM_VALUE* args);
  int32_t (*is_type)(SPVM_ENV*, void* object, int32_t basic_type_id, int32_t type_dimension);
  int32_t (*has_interface)(SPVM_ENV*, void* object, int32_t interface_basic_type_id);
  void* (*new_obj_raw)(SPVM_ENV*, int32_t);
  void* (*new_obj)(SPVM_ENV*, int32_t);
  void* (*new_barray_raw)(SPVM_ENV*, int32_t);
  void* (*new_barray)(SPVM_ENV*, int32_t);
  void* (*new_sarray_raw)(SPVM_ENV*, int32_t);
  void* (*new_sarray)(SPVM_ENV*, int32_t);
  void* (*new_iarray_raw)(SPVM_ENV*, int32_t);
  void* (*new_iarray)(SPVM_ENV*, int32_t);
  void* (*new_larray_raw)(SPVM_ENV*, int32_t);
  void* (*new_larray)(SPVM_ENV*, int32_t);
  void* (*new_farray_raw)(SPVM_ENV*, int32_t);
  void* (*new_farray)(SPVM_ENV*, int32_t);
  void* (*new_darray_raw)(SPVM_ENV*, int32_t);
  void* (*new_darray)(SPVM_ENV*, int32_t);
  void* (*new_oarray_raw)(SPVM_ENV*, int32_t, int32_t);
  void* (*new_oarray)(SPVM_ENV*, int32_t, int32_t);
  void* (*new_marray_raw)(SPVM_ENV*, int32_t, int32_t, int32_t);
  void* (*new_marray)(SPVM_ENV*, int32_t, int32_t, int32_t);
  void* (*new_varray_raw)(SPVM_ENV*, int32_t, int32_t);
  void* (*new_varray)(SPVM_ENV*, int32_t, int32_t);
  void* (*new_str_raw)(SPVM_ENV* env, const char* bytes, int32_t length);
  void* (*new_str)(SPVM_ENV* env, const char* bytes, int32_t length);
  void* (*new_pointer_raw)(SPVM_ENV*, int32_t basic_type_id, void* ptr);
  void* (*new_pointer)(SPVM_ENV* env, int32_t basic_type_id, void* ptr);
  void* (*concat_raw)(SPVM_ENV* env, void* string1, void* string2);
  void* (*concat)(SPVM_ENV* env, void* string1, void* string2);
  void* (*i_to_str_raw)(SPVM_ENV* env, int32_t value);
  void* (*i_to_str)(SPVM_ENV* env, int32_t value);
  void* (*l_to_str_raw)(SPVM_ENV* env, int64_t value);
  void* (*l_to_str)(SPVM_ENV* env, int64_t value);
  void* (*f_to_str_raw)(SPVM_ENV* env, float value);
  void* (*f_to_str)(SPVM_ENV* env, float value);
  void* (*d_to_str_raw)(SPVM_ENV* env, double value);
  void* (*d_to_str)(SPVM_ENV* env, double value);
  void* (*new_stack_trace_raw)(SPVM_ENV* env, void* excetpion, const char* package_name, const char* sub_name, const char* file, int32_t line);
  void* (*new_stack_trace)(SPVM_ENV* env, void* excetpion, const char* package_name, const char* sub_name, const char* file, int32_t line);
  int32_t (*len)(SPVM_ENV*, void*);
  int8_t* (*belems)(SPVM_ENV*, void*);
  int16_t* (*selems)(SPVM_ENV*, void*);
  int32_t* (*ielems)(SPVM_ENV*, void*);
  int64_t* (*lelems)(SPVM_ENV*, void*);
  float* (*felems)(SPVM_ENV*, void*);
  double* (*delems)(SPVM_ENV*, void*);
  void* (*oelem)(SPVM_ENV*, void*, int32_t index);
  void (*set_oelem)(SPVM_ENV*, void*, int32_t index, void* value);
  int32_t (*field_id)(SPVM_ENV*, const char*, const char*, const char*);
  int8_t (*bfield)(SPVM_ENV*, void*, int32_t);
  int16_t (*sfield)(SPVM_ENV*, void*, int32_t);
  int32_t (*ifield)(SPVM_ENV*, void*, int32_t);
  int64_t (*lfield)(SPVM_ENV*, void*, int32_t);
  float (*ffield)(SPVM_ENV*, void*, int32_t);
  double (*dfield)(SPVM_ENV*, void*, int32_t);
  void* (*ofield)(SPVM_ENV*, void*, int32_t);
  void (*set_bfield)(SPVM_ENV*, void*, int32_t, int8_t);
  void (*set_sfield)(SPVM_ENV*, void*, int32_t, int16_t);
  void (*set_ifield)(SPVM_ENV*, void*, int32_t, int32_t);
  void (*set_lfield)(SPVM_ENV*, void*, int32_t, int64_t);
  void (*set_ffield)(SPVM_ENV*, void*, int32_t, float);
  void (*set_dfield)(SPVM_ENV*, void*, int32_t, double);
  void (*set_ofield)(SPVM_ENV*, void*, int32_t, void*);
  int8_t (*bpkgvar)(SPVM_ENV* env, int32_t pkgvar_id);
  int16_t (*spkgvar)(SPVM_ENV* env, int32_t pkgvar_id);
  int32_t (*ipkgvar)(SPVM_ENV* env, int32_t pkgvar_id);
  int64_t (*lpkgvar)(SPVM_ENV* env, int32_t pkgvar_id);
  float (*fpkgvar)(SPVM_ENV* env, int32_t pkgvar_id);
  double (*dpkgvar)(SPVM_ENV* env, int32_t pkgvar_id);
  void* (*opkgvar)(SPVM_ENV* env, int32_t pkgvar_id);
  void (*set_bpkgvar)(SPVM_ENV* env, int32_t pkgvar_id, int8_t value);
  void (*set_spkgvar)(SPVM_ENV* env, int32_t pkgvar_id, int16_t value);
  void (*set_ipkgvar)(SPVM_ENV* env, int32_t pkgvar_id, int32_t value);
  void (*set_lpkgvar)(SPVM_ENV* env, int32_t pkgvar_id, int64_t value);
  void (*set_fpkgvar)(SPVM_ENV* env, int32_t pkgvar_id, float value);
  void (*set_dpkgvar)(SPVM_ENV* env, int32_t pkgvar_id, double value);
  void (*set_opkgvar)(SPVM_ENV* env, int32_t pkgvar_id, void* value);
  void* (*pointer)(SPVM_ENV*, void*);
  void (*weaken)(SPVM_ENV* env, void** object_address);
  int32_t (*isweak)(SPVM_ENV* env, void** object);
  void (*unweaken)(SPVM_ENV* env, void** object_address);
  int32_t (*ref_count)(SPVM_ENV* env, void* object);
  void (*inc_ref_count)(SPVM_ENV* env, void* object);
  void (*dec_ref_count)(SPVM_ENV* env, void* object);
  int32_t (*enter_scope)(SPVM_ENV* env);
  void (*push_mortal)(SPVM_ENV* env, void* object);
  void (*leave_scope)(SPVM_ENV* env, int32_t original_mortal_stack_top);
  void* (*type_name_raw)(SPVM_ENV* env, void* object);
  void* (*type_name)(SPVM_ENV* env, void* object);
};
#endif
