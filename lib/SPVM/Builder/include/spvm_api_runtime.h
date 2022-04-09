#ifndef SPVM_API_RUNTIME_H
#define SPVM_API_RUNTIME_H

#include "spvm_typedecl.h"
#include "spvm_native.h"

// Private
SPVM_RUNTIME_BASIC_TYPE* SPVM_API_RUNTIME_get_basic_type(SPVM_RUNTIME* runtime, int32_t basic_type_id);
SPVM_RUNTIME_BASIC_TYPE* SPVM_API_RUNTIME_get_basic_type_by_name(SPVM_RUNTIME* runtime, const char* basic_type_name);
const char* SPVM_API_RUNTIME_get_basic_type_name(SPVM_RUNTIME* runtime, int32_t basic_type_id);
SPVM_RUNTIME_TYPE* SPVM_API_RUNTIME_get_type(SPVM_RUNTIME* runtime, int32_t type_id);
SPVM_RUNTIME_CLASS* SPVM_API_RUNTIME_get_class(SPVM_RUNTIME* runtime, int32_t class_id);
SPVM_RUNTIME_CLASS* SPVM_API_RUNTIME_get_class_by_name(SPVM_RUNTIME* runtime, const char* class_name);
SPVM_RUNTIME_CLASS_VAR* SPVM_API_RUNTIME_get_class_var(SPVM_RUNTIME* runtime, int32_t class_var_id);
SPVM_RUNTIME_CLASS_VAR* SPVM_API_RUNTIME_get_class_var_by_class_id_and_class_var_name(SPVM_RUNTIME* runtime, int32_t class_id, const char* search_class_var_name);
SPVM_RUNTIME_FIELD* SPVM_API_RUNTIME_get_field(SPVM_RUNTIME* runtime, int32_t field_id);
SPVM_RUNTIME_FIELD* SPVM_API_RUNTIME_get_field_by_class_id_and_field_name(SPVM_RUNTIME* runtime, int32_t class_id, const char* search_field_name);
SPVM_RUNTIME_METHOD* SPVM_API_RUNTIME_get_method(SPVM_RUNTIME* runtime, int32_t method_id);
SPVM_RUNTIME_METHOD* SPVM_API_RUNTIME_get_method_by_class_id_and_method_name(SPVM_RUNTIME* runtime, int32_t class_id, const char* search_method_name);
int32_t SPVM_API_RUNTIME_has_interface_by_id(SPVM_RUNTIME* runtime, int32_t object_basic_type_id, int32_t object_type_dimension, int32_t interface_basic_type_id, int32_t interface_type_dimension);
int32_t SPVM_API_RUNTIME_has_callback_by_id(SPVM_RUNTIME* runtime, int32_t object_basic_type_id, int32_t object_type_dimension, int32_t callback_basic_type_id, int32_t callback_type_dimension);

// Runtime
SPVM_RUNTIME* SPVM_API_RUNTIME_new_runtime();
void SPVM_API_RUNTIME_prepare(SPVM_RUNTIME* runtime);
void SPVM_API_RUNTIME_free_runtime(SPVM_RUNTIME* runtime);

// OP code
SPVM_OPCODE* SPVM_API_RUNTIME_get_opcodes(SPVM_RUNTIME* runtime);
int32_t SPVM_API_RUNTIME_get_opcode_ids_length(SPVM_RUNTIME* runtime);

// Basic type
int32_t SPVM_API_RUNTIME_get_basic_type_id(SPVM_RUNTIME* runtime, const char* basic_type_name);
int32_t SPVM_API_RUNTIME_get_basic_type_category(SPVM_RUNTIME* runtime, int32_t basic_type_id);
int32_t SPVM_API_RUNTIME_get_basic_type_name_id(SPVM_RUNTIME* runtime, int32_t basic_type_id);
int32_t SPVM_API_RUNTIME_get_basic_type_class_id(SPVM_RUNTIME* runtime, int32_t basic_type_id);

// String
const char* SPVM_API_RUNTIME_get_constant_string_value(SPVM_RUNTIME* runtime, int32_t constant_string_id, int32_t* string_length);
const char* SPVM_API_RUNTIME_get_name(SPVM_RUNTIME* runtime, int32_t constant_string_id);
int32_t SPVM_API_RUNTIME_get_constant_string_id(SPVM_RUNTIME* runtime, const char* string);

// Type
int32_t SPVM_API_RUNTIME_get_type_basic_type_id(SPVM_RUNTIME* runtime, int32_t type_id);
int32_t SPVM_API_RUNTIME_get_type_dimension(SPVM_RUNTIME* runtime, int32_t type_id);
int32_t SPVM_API_RUNTIME_get_type_width(SPVM_RUNTIME* runtime, int32_t type_id);
int32_t SPVM_API_RUNTIME_get_type_is_ref(SPVM_RUNTIME* runtime, int32_t type_id);
int32_t SPVM_API_RUNTIME_get_type_is_object(SPVM_RUNTIME* runtime, int32_t type_id);

// Class
int32_t SPVM_API_RUNTIME_get_class_name_id(SPVM_RUNTIME* runtime, int32_t class_id);
int32_t SPVM_API_RUNTIME_get_class_anon_method_ids_base(SPVM_RUNTIME* runtime, int32_t class_id);
int32_t SPVM_API_RUNTIME_get_class_anon_method_ids_length(SPVM_RUNTIME* runtime, int32_t class_id);
int32_t SPVM_API_RUNTIME_get_class_is_anon(SPVM_RUNTIME* runtime, int32_t class_id);
int32_t SPVM_API_RUNTIME_get_class_module_file_id(SPVM_RUNTIME* runtime, int32_t class_id);
int32_t SPVM_API_RUNTIME_get_class_field_ids_base(SPVM_RUNTIME* runtime, int32_t class_id);
int32_t SPVM_API_RUNTIME_get_class_field_ids_length(SPVM_RUNTIME* runtime, int32_t class_id);
int32_t SPVM_API_RUNTIME_get_class_method_ids_base(SPVM_RUNTIME* runtime, int32_t class_id);
int32_t SPVM_API_RUNTIME_get_class_method_ids_length(SPVM_RUNTIME* runtime, int32_t class_id);
int32_t SPVM_API_RUNTIME_get_class_class_var_ids_base(SPVM_RUNTIME* runtime, int32_t class_id);
int32_t SPVM_API_RUNTIME_get_class_class_var_ids_length(SPVM_RUNTIME* runtime, int32_t class_id);
int32_t SPVM_API_RUNTIME_get_class_id_by_name(SPVM_RUNTIME* runtime, const char* class_name);

// Class variable
int32_t SPVM_API_RUNTIME_get_class_var_name_id(SPVM_RUNTIME* runtime, int32_t class_var_id);
int32_t SPVM_API_RUNTIME_get_class_var_signature_id(SPVM_RUNTIME* runtime, int32_t class_var_id);
int32_t SPVM_API_RUNTIME_get_class_var_class_id(SPVM_RUNTIME* runtime, int32_t class_var_id);
int32_t SPVM_API_RUNTIME_get_class_var_id_by_name(SPVM_RUNTIME* runtime, const char* class_name, const char* class_var_name);

// Field
int32_t SPVM_API_RUNTIME_get_field_class_id(SPVM_RUNTIME* runtime, int32_t field_id);
int32_t SPVM_API_RUNTIME_get_field_type_id(SPVM_RUNTIME* runtime, int32_t field_id);
int32_t SPVM_API_RUNTIME_get_field_name_id(SPVM_RUNTIME* runtime, int32_t field_id);
int32_t SPVM_API_RUNTIME_get_field_signature_id(SPVM_RUNTIME* runtime, int32_t field_id);
int32_t SPVM_API_RUNTIME_get_field_id_by_name(SPVM_RUNTIME* runtime, const char* class_name, const char* field_name);

// Method
int32_t SPVM_API_RUNTIME_get_method_class_id(SPVM_RUNTIME* runtime, int32_t method_id);
int32_t SPVM_API_RUNTIME_get_method_opcode_ids_base(SPVM_RUNTIME* runtime, int32_t method_id);
int32_t SPVM_API_RUNTIME_get_method_opcode_ids_length(SPVM_RUNTIME* runtime, int32_t method_id);
int32_t SPVM_API_RUNTIME_get_method_name_id(SPVM_RUNTIME* runtime, int32_t method_id);
int32_t SPVM_API_RUNTIME_get_method_is_anon(SPVM_RUNTIME* runtime, int32_t method_id);
int32_t SPVM_API_RUNTIME_get_method_has_precompile_flag(SPVM_RUNTIME* runtime, int32_t method_id);
int32_t SPVM_API_RUNTIME_get_method_signature_id(SPVM_RUNTIME* runtime, int32_t method_id);
int32_t SPVM_API_RUNTIME_get_method_arg_ids_length(SPVM_RUNTIME* runtime, int32_t method_id);
int32_t SPVM_API_RUNTIME_get_method_arg_ids_base(SPVM_RUNTIME* runtime, int32_t method_id);
int32_t SPVM_API_RUNTIME_get_method_is_class_method(SPVM_RUNTIME* runtime, int32_t method_id);
int32_t SPVM_API_RUNTIME_get_method_return_type_id(SPVM_RUNTIME* runtime, int32_t method_id);
int32_t SPVM_API_RUNTIME_get_method_call_stack_byte_vars_length(SPVM_RUNTIME* runtime, int32_t method_id);
int32_t SPVM_API_RUNTIME_get_method_call_stack_short_vars_length(SPVM_RUNTIME* runtime, int32_t method_id);
int32_t SPVM_API_RUNTIME_get_method_call_stack_int_vars_length(SPVM_RUNTIME* runtime, int32_t method_id);
int32_t SPVM_API_RUNTIME_get_method_call_stack_long_vars_length(SPVM_RUNTIME* runtime, int32_t method_id);
int32_t SPVM_API_RUNTIME_get_method_call_stack_float_vars_length(SPVM_RUNTIME* runtime, int32_t method_id);
int32_t SPVM_API_RUNTIME_get_method_call_stack_double_vars_length(SPVM_RUNTIME* runtime, int32_t method_id);
int32_t SPVM_API_RUNTIME_get_method_call_stack_object_vars_length(SPVM_RUNTIME* runtime, int32_t method_id);
int32_t SPVM_API_RUNTIME_get_method_call_stack_ref_vars_length(SPVM_RUNTIME* runtime, int32_t method_id);
int32_t SPVM_API_RUNTIME_get_method_mortal_stack_length(SPVM_RUNTIME* runtime, int32_t method_id);
int32_t SPVM_API_RUNTIME_get_method_id_by_name(SPVM_RUNTIME* runtime, const char* class_name, const char* method_name);

// Argument
int32_t SPVM_API_RUNTIME_get_arg_type_id(SPVM_RUNTIME* runtime, int32_t arg_id);

// Anon method
int32_t SPVM_API_RUNTIME_get_anon_method_method_id(SPVM_RUNTIME* runtime, int32_t anon_method_id);

// Native and precompile method
void SPVM_API_RUNTIME_set_native_method_address(SPVM_RUNTIME* runtime, int32_t method_id, void* address);
void SPVM_API_RUNTIME_set_precompile_method_address(SPVM_RUNTIME* runtime, int32_t method_id, void* address);
void* SPVM_API_RUNTIME_get_native_method_address(SPVM_RUNTIME* runtime, int32_t method_id);
void* SPVM_API_RUNTIME_get_precompile_method_address(SPVM_RUNTIME* runtime, int32_t method_id);


#endif
