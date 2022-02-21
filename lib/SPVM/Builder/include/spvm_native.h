#ifndef SPVM_NATIVE_H
#define SPVM_NATIVE_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>

struct spvm_env;
typedef struct spvm_env SPVM_ENV;

typedef union spvm_value SPVM_VALUE;

union spvm_value {
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







































































struct spvm_env {
  void* class_vars_heap;
  void* object_header_byte_size;
  void* object_weaken_backref_head_offset;
  void* object_ref_count_offset;
  void* object_basic_type_id_offset;
  void* object_type_dimension_offset;
  void* object_type_category_offset;
  void* object_flag_offset;
  void* object_length_offset;
  void* byte_object_basic_type_id;
  void* short_object_basic_type_id;
  void* int_object_basic_type_id;
  void* long_object_basic_type_id;
  void* float_object_basic_type_id;
  void* double_object_basic_type_id;
  void* compiler;
  void* exception_object;
  void* native_mortal_stack;
  void* native_mortal_stack_top;
  void* native_mortal_stack_capacity;
  int32_t (*get_basic_type_id)(SPVM_ENV* env, const char* basic_type_name);
  int32_t (*get_field_id)(SPVM_ENV* env, const char* class_name, const char* field_name, const char* signature);
  int32_t (*get_field_offset)(SPVM_ENV* env, int32_t field_id);
  int32_t (*get_class_var_id)(SPVM_ENV* env, const char* class_name, const char* class_var_name, const char* signature);
  int32_t (*get_class_method_id)(SPVM_ENV* env, const char* class_name, const char* method_name, const char* signature);
  int32_t (*get_instance_method_id)(SPVM_ENV* env, void* object, const char* method_name, const char* signature);
  void* (*new_object_raw)(SPVM_ENV* env, int32_t basic_type_id);
  void* (*new_object)(SPVM_ENV* env, int32_t basic_type_id);
  void* (*new_byte_array_raw)(SPVM_ENV* env, int32_t length);
  void* (*new_byte_array)(SPVM_ENV* env, int32_t length);
  void* (*new_short_array_raw)(SPVM_ENV* env, int32_t length);
  void* (*new_short_array)(SPVM_ENV* env, int32_t length);
  void* (*new_int_array_raw)(SPVM_ENV* env, int32_t length);
  void* (*new_int_array)(SPVM_ENV* env, int32_t length);
  void* (*new_long_array_raw)(SPVM_ENV* env, int32_t length);
  void* (*new_long_array)(SPVM_ENV* env, int32_t length);
  void* (*new_float_array_raw)(SPVM_ENV* env, int32_t length);
  void* (*new_float_array)(SPVM_ENV* env, int32_t length);
  void* (*new_double_array_raw)(SPVM_ENV* env, int32_t length);
  void* (*new_double_array)(SPVM_ENV* env, int32_t length);
  void* (*new_object_array_raw)(SPVM_ENV* env, int32_t basic_type_id, int32_t length);
  void* (*new_object_array)(SPVM_ENV* env, int32_t basic_type_id, int32_t length);
  void* (*new_muldim_array_raw)(SPVM_ENV* env, int32_t basic_type_id, int32_t element_dimension, int32_t length);
  void* (*new_muldim_array)(SPVM_ENV* env, int32_t basic_type_id, int32_t element_dimension, int32_t length);
  void* (*new_mulnum_array_raw)(SPVM_ENV* env, int32_t basic_type_id, int32_t length);
  void* (*new_mulnum_array)(SPVM_ENV* env, int32_t basic_type_id, int32_t length);
  void* (*new_string_nolen_raw)(SPVM_ENV* env, const char* bytes);
  void* (*new_string_nolen)(SPVM_ENV* env, const char* bytes);
  void* (*new_string_raw)(SPVM_ENV* env, const char* bytes, int32_t length);
  void* (*new_string)(SPVM_ENV* env, const char* bytes, int32_t length);
  void* (*new_pointer_raw)(SPVM_ENV* env, int32_t basic_type_id, void* pointer);
  void* (*new_pointer)(SPVM_ENV* env, int32_t basic_type_id, void* pointer);
  void* (*concat_raw)(SPVM_ENV* env, void* string1, void* string2);
  void* (*concat)(SPVM_ENV* env, void* string1, void* string2);
  void* (*new_stack_trace_raw)(SPVM_ENV* env, void* exception, const char* class_name, const char* method_name, const char* file, int32_t line);
  void* (*new_stack_trace)(SPVM_ENV* env, void* exception, const char* class_name, const char* method_name, const char* file, int32_t line);
  int32_t (*length)(SPVM_ENV* env, void* array);
  int8_t* (*get_elems_byte)(SPVM_ENV* env, void* array);
  int16_t* (*get_elems_short)(SPVM_ENV* env, void* array);
  int32_t* (*get_elems_int)(SPVM_ENV* env, void* array);
  int64_t* (*get_elems_long)(SPVM_ENV* env, void* array);
  float* (*get_elems_float)(SPVM_ENV* env, void* array);
  double* (*get_elems_double)(SPVM_ENV* env, void* array);
  void* (*get_elem_object)(SPVM_ENV* env, void* array, int32_t index);
  void (*set_elem_object)(SPVM_ENV* env, void* array, int32_t index, void* value);
  int8_t (*get_field_byte)(SPVM_ENV* env, void* object, int32_t field_id);
  int16_t (*get_field_short)(SPVM_ENV* env, void* object, int32_t field_id);
  int32_t (*get_field_int)(SPVM_ENV* env, void* object, int32_t field_id);
  int64_t (*get_field_long)(SPVM_ENV* env, void* object, int32_t field_id);
  float (*get_field_float)(SPVM_ENV* env, void* object, int32_t field_id);
  double (*get_field_double)(SPVM_ENV* env, void* object, int32_t field_id);
  void* (*get_field_object)(SPVM_ENV* env, void* object, int32_t field_id);
  void (*set_field_byte)(SPVM_ENV* env, void* object, int32_t field_id, int8_t value);
  void (*set_field_short)(SPVM_ENV* env, void* object, int32_t field_id, int16_t value);
  void (*set_field_int)(SPVM_ENV* env, void* object, int32_t field_id, int32_t value);
  void (*set_field_long)(SPVM_ENV* env, void* object, int32_t field_id, int64_t value);
  void (*set_field_float)(SPVM_ENV* env, void* object, int32_t field_id, float value);
  void (*set_field_double)(SPVM_ENV* env, void* object, int32_t field_id, double value);
  void (*set_field_object)(SPVM_ENV* env, void* object, int32_t field_id, void* value);
  int8_t (*get_class_var_byte)(SPVM_ENV* env, int32_t pkgvar_id);
  int16_t (*get_class_var_short)(SPVM_ENV* env, int32_t pkgvar_id);
  int32_t (*get_class_var_int)(SPVM_ENV* env, int32_t pkgvar_id);
  int64_t (*get_class_var_long)(SPVM_ENV* env, int32_t pkgvar_id);
  float (*get_class_var_float)(SPVM_ENV* env, int32_t pkgvar_id);
  double (*get_class_var_double)(SPVM_ENV* env, int32_t pkgvar_id);
  void* (*get_class_var_object)(SPVM_ENV* env, int32_t pkgvar_id);
  void (*set_class_var_byte)(SPVM_ENV* env, int32_t pkgvar_id, int8_t value);
  void (*set_class_var_short)(SPVM_ENV* env, int32_t pkgvar_id, int16_t value);
  void (*set_class_var_int)(SPVM_ENV* env, int32_t pkgvar_id, int32_t value);
  void (*set_class_var_long)(SPVM_ENV* env, int32_t pkgvar_id, int64_t value);
  void (*set_class_var_float)(SPVM_ENV* env, int32_t pkgvar_id, float value);
  void (*set_class_var_double)(SPVM_ENV* env, int32_t pkgvar_id, double value);
  void (*set_class_var_object)(SPVM_ENV* env, int32_t pkgvar_id, void* value);
  void* (*get_pointer)(SPVM_ENV* env, void* pointer_object);
  void (*set_pointer)(SPVM_ENV* env, void* pointer_object, void* pointer);
  int32_t (*call_spvm_method)(SPVM_ENV* env, int32_t method_id, SPVM_VALUE* args);
  void* (*get_exception)(SPVM_ENV* env);
  int32_t (*set_exception)(SPVM_ENV* env, void* exception);
  int32_t (*get_ref_count)(SPVM_ENV* env, void* object);
  void (*inc_ref_count)(SPVM_ENV* env, void* object);
  void (*dec_ref_count)(SPVM_ENV* env, void* object);
  int32_t (*enter_scope)(SPVM_ENV* env);
  int32_t (*push_mortal)(SPVM_ENV* env, void* object);
  void (*leave_scope)(SPVM_ENV* env, int32_t scope_id);
  int32_t (*remove_mortal)(SPVM_ENV* env, int32_t scope_id, void* remove_object);
  int32_t (*is_type)(SPVM_ENV* env, void* object, int32_t basic_type_id, int32_t type_dimension);
  int32_t (*has_callback)(SPVM_ENV* env, void* object, int32_t callback_basic_type_id);
  int32_t (*get_object_basic_type_id)(SPVM_ENV* env, void* object);
  int32_t (*get_object_type_dimension)(SPVM_ENV* env, void* object);
  int32_t (*weaken)(SPVM_ENV* env, void** object_address);
  int32_t (*isweak)(SPVM_ENV* env, void** object);
  void (*unweaken)(SPVM_ENV* env, void** object_address);
  void* (*alloc_memory_block_zero)(SPVM_ENV* env, size_t byte_size);
  void (*free_memory_block)(SPVM_ENV* env, void* block);
  int32_t (*get_memory_blocks_count)(SPVM_ENV* env);
  void* (*get_type_name_raw)(SPVM_ENV* env, void* object);
  void* (*get_type_name)(SPVM_ENV* env, void* object);
  SPVM_ENV* (*new_env_raw)(SPVM_ENV* env);
  void (*free_env_raw)(SPVM_ENV* env);
  void* memory_blocks_count;
  const char* (*get_chars)(SPVM_ENV* env, void* string_object);
  int32_t (*die)(SPVM_ENV* env, const char* message, ...);
  void* (*new_object_by_name)(SPVM_ENV* env, const char* class_name, int32_t* exception_flag, const char* file, int32_t line);
  void* (*new_pointer_by_name)(SPVM_ENV* env, const char* class_name, void* pointer, int32_t* exception_flag, const char* file, int32_t line);
  void (*set_field_byte_by_name)(SPVM_ENV* env, void* object, const char* class_name, const char* field_name, int8_t value, int32_t* exception_flag, const char* file, int32_t line);
  void (*set_field_short_by_name)(SPVM_ENV* env, void* object, const char* class_name, const char* field_name, int16_t value, int32_t* exception_flag, const char* file, int32_t line);
  void (*set_field_int_by_name)(SPVM_ENV* env, void* object, const char* class_name, const char* field_name, int32_t value, int32_t* exception_flag, const char* file, int32_t line);
  void (*set_field_long_by_name)(SPVM_ENV* env, void* object, const char* class_name, const char* field_name, int64_t value, int32_t* exception_flag, const char* file, int32_t line);
  void (*set_field_float_by_name)(SPVM_ENV* env, void* object, const char* class_name, const char* field_name, float value, int32_t* exception_flag, const char* file, int32_t line);
  void (*set_field_double_by_name)(SPVM_ENV* env, void* object, const char* class_name, const char* field_name, double value, int32_t* exception_flag, const char* file, int32_t line);
  void (*set_field_object_by_name)(SPVM_ENV* env, void* object, const char* class_name, const char* field_name, const char* signature, void* value, int32_t* exception_flag, const char* file, int32_t line);
  int8_t (*get_field_byte_by_name)(SPVM_ENV* env, void* object, const char* class_name, const char* field_name, int32_t* exception_flag, const char* file, int32_t line);
  int16_t (*get_field_short_by_name)(SPVM_ENV* env, void* object, const char* class_name, const char* field_name, int32_t* exception_flag, const char* file, int32_t line);
  int32_t (*get_field_int_by_name)(SPVM_ENV* env, void* object, const char* class_name, const char* field_name, int32_t* exception_flag, const char* file, int32_t line);
  int64_t (*get_field_long_by_name)(SPVM_ENV* env, void* object, const char* class_name, const char* field_name, int32_t* exception_flag, const char* file, int32_t line);
  float (*get_field_float_by_name)(SPVM_ENV* env, void* object, const char* class_name, const char* field_name, int32_t* exception_flag, const char* file, int32_t line);
  double (*get_field_double_by_name)(SPVM_ENV* env, void* object, const char* class_name, const char* field_name, int32_t* exception_flag, const char* file, int32_t line);
  void* (*get_field_object_by_name)(SPVM_ENV* env, void* object, const char* class_name, const char* field_name, const char* signature, int32_t* exception_flag, const char* file, int32_t line);
  void (*set_class_var_byte_by_name)(SPVM_ENV* env, const char* class_name, const char* class_var_name, int8_t value, int32_t* exception_flag, const char* file, int32_t line);
  void (*set_class_var_short_by_name)(SPVM_ENV* env, const char* class_name, const char* class_var_name, int16_t value, int32_t* exception_flag, const char* file, int32_t line);
  void (*set_class_var_int_by_name)(SPVM_ENV* env, const char* class_name, const char* class_var_name, int32_t value, int32_t* exception_flag, const char* file, int32_t line);
  void (*set_class_var_long_by_name)(SPVM_ENV* env, const char* class_name, const char* class_var_name, int64_t value, int32_t* exception_flag, const char* file, int32_t line);
  void (*set_class_var_float_by_name)(SPVM_ENV* env, const char* class_name, const char* class_var_name, float value, int32_t* exception_flag, const char* file, int32_t line);
  void (*set_class_var_double_by_name)(SPVM_ENV* env, const char* class_name, const char* class_var_name, double value, int32_t* exception_flag, const char* file, int32_t line);
  void (*set_class_var_object_by_name)(SPVM_ENV* env, const char* class_name, const char* class_var_name, const char* signature, void* value, int32_t* exception_flag, const char* file, int32_t line);
  int8_t (*get_class_var_byte_by_name)(SPVM_ENV* env, const char* class_name, const char* class_var_name, int32_t* exception_flag, const char* file, int32_t line);
  int16_t (*get_class_var_short_by_name)(SPVM_ENV* env, const char* class_name, const char* class_var_name, int32_t* exception_flag, const char* file, int32_t line);
  int32_t (*get_class_var_int_by_name)(SPVM_ENV* env, const char* class_name, const char* class_var_name, int32_t* exception_flag, const char* file, int32_t line);
  int64_t (*get_class_var_long_by_name)(SPVM_ENV* env, const char* class_name, const char* class_var_name, int32_t* exception_flag, const char* file, int32_t line);
  float (*get_class_var_float_by_name)(SPVM_ENV* env, const char* class_name, const char* class_var_name, int32_t* exception_flag, const char* file, int32_t line);
  double (*get_class_var_double_by_name)(SPVM_ENV* env, const char* class_name, const char* class_var_name, int32_t* exception_flag, const char* file, int32_t line);
  void* (*get_class_var_object_by_name)(SPVM_ENV* env, const char* class_name, const char* class_var_name, const char* signature, int32_t* exception_flag, const char* file, int32_t line);
  int32_t (*call_class_method_by_name)(SPVM_ENV* env, const char* class_name, const char* method_name, const char* signature, SPVM_VALUE* stack, const char* file, int32_t line);
  int32_t (*call_instance_method_by_name)(SPVM_ENV* env, void* object, const char* method_name, const char* signature, SPVM_VALUE* stack, const char* file, int32_t line);
  const char* (*get_field_string_chars_by_name)(SPVM_ENV* env, void* obj, const char* class_name, const char* field_name, int32_t* exception_flag, const char* file, int32_t line);
  void* any_object_basic_type_id;
  void* (*dump_raw)(SPVM_ENV* env, void* object);
  void* (*dump)(SPVM_ENV* env, void* object);
  int32_t (*call_class_method)(SPVM_ENV* env, int32_t method_id, SPVM_VALUE* args);
  int32_t (*call_instance_method)(SPVM_ENV* env, int32_t method_id, SPVM_VALUE* args);
  int32_t (*get_instance_method_id_static)(SPVM_ENV* env, const char* class_name, const char* method_name, const char* signature);
  int32_t (*get_bool_object_value)(SPVM_ENV* env, void* bool_object);
  void* string_basic_type_id;
  void (*make_read_only)(SPVM_ENV* env, void* string);
  int32_t (*is_read_only)(SPVM_ENV* env, void* string);
  int32_t (*is_array)(SPVM_ENV* env, void* object);
  int32_t (*is_string)(SPVM_ENV* env, void* object);
  int32_t (*is_numeric_array)(SPVM_ENV* env, void* object);
  int32_t (*is_mulnum_array)(SPVM_ENV* env, void* object);
  int32_t (*get_elem_byte_size)(SPVM_ENV* env, void* array);
  void* (*new_array_proto_raw)(SPVM_ENV* env, void* array, int32_t length);
  void* (*new_array_proto)(SPVM_ENV* env, void* array, int32_t length);
  void* (*copy_raw)(SPVM_ENV* env, void* object);
  void* (*copy)(SPVM_ENV* env, void* object);
  void (*shorten)(SPVM_ENV* env, void* string, int32_t new_length);
  int32_t (*has_interface)(SPVM_ENV* env, void* object, int32_t interface_basic_type_id);
  void* no_symbol_cache_flag;
  void (*set_no_symbol_cache_flag)(SPVM_ENV* env, int32_t flag);
  int32_t (*get_no_symbol_cache_flag)(SPVM_ENV* env);
  void (*print)(SPVM_ENV* env, void* string);
  void (*print_stderr)(SPVM_ENV* env, void* string);
  int32_t (*init_env)(SPVM_ENV* env);
  void (*call_init_blocks)(SPVM_ENV* env);
  void (*cleanup_global_vars)(SPVM_ENV* env);
  void* (*new_compiler)(SPVM_ENV* env);
  void (*compiler_free)(SPVM_ENV* env, void* compiler);
  void (*compiler_set_start_line)(SPVM_ENV* env, void* compiler, int32_t start_line);
  int32_t (*compiler_get_start_line)(SPVM_ENV* env, void* compiler);
  void (*compiler_set_start_file)(SPVM_ENV* env, void* compiler, const char* start_file);
  const char* (*compiler_get_start_file)(SPVM_ENV* env, void* compiler);
  void (*compiler_add_module_dir)(SPVM_ENV* env, void* compiler, const char* module_dir);
  int32_t (*compiler_get_module_dirs_length )(SPVM_ENV* env, void* compiler);
  const char* (*compiler_get_module_dir )(SPVM_ENV* env, void* compiler, int32_t module_dir_id);
  int32_t (*compiler_compile_spvm)(SPVM_ENV* env, void* compiler, const char* class_name);
  int32_t (*compiler_get_error_messages_length)(SPVM_ENV* env, void* compiler);
  const char* (*compiler_get_error_message)(SPVM_ENV* env, void* compiler, int32_t index);
  int32_t (*compiler_get_classes_length)(SPVM_ENV* env, void* compiler);
  const char* (*compiler_get_class_name)(SPVM_ENV* env, void* compiler, int32_t class_id);
  int32_t (*compiler_is_anon_class)(SPVM_ENV* env, void* compiler, int32_t class_id);
  int32_t (*compiler_get_methods_length)(SPVM_ENV* env, void* compiler, int32_t class_id);
  int32_t (*compiler_get_method_id)(SPVM_ENV* env, void* compiler, int32_t class_id, int32_t method_index_of_class);
  int32_t (*compiler_get_method_id_by_name)(SPVM_ENV* env, void* compiler, const char* class_name, const char* method_name);
  const char* (*compiler_get_method_name)(SPVM_ENV* env, void* compiler, int32_t method_id);
  int32_t (*compiler_is_anon_method)(SPVM_ENV* env, void* compiler, int32_t method_id);
  int32_t (*compiler_is_init_method)(SPVM_ENV* env, void* compiler, int32_t method_id);
  int32_t (*compiler_is_native_method)(SPVM_ENV* env, void* compiler, int32_t method_id);
  int32_t (*compiler_is_precompile_method)(SPVM_ENV* env, void* compiler, int32_t method_id);
  void* (*compiler_get_native_method_address)(SPVM_ENV* env, void* compiler, int32_t method_id);
  void* (*compiler_get_precompile_method_address)(SPVM_ENV* env, void* compiler, int32_t method_id);
  void (*compiler_set_native_method_address)(SPVM_ENV* env, void* compiler, int32_t method_id, void* address);
  void (*compiler_set_precompile_method_address)(SPVM_ENV* env, void* compiler, int32_t method_id, void* address);
  const char* (*compiler_get_method_signature)(SPVM_ENV* env, void* compiler, int32_t method_id);
};
#endif
