#ifndef SPVM_API_RUNTIME_H
#define SPVM_API_RUNTIME_H

#include "spvm_typedecl.h"
#include "spvm_native.h"

SPVM_RUNTIME* SPVM_API_RUNTIME_new_runtime();
void SPVM_API_RUNTIME_prepare(SPVM_RUNTIME* runtime);
SPVM_OPCODE* SPVM_API_RUNTIME_get_opcodes(SPVM_RUNTIME* runtime);
int32_t SPVM_API_RUNTIME_get_opcode_ids_length(SPVM_RUNTIME* runtime);
void SPVM_API_RUNTIME_free_runtime(SPVM_RUNTIME* runtime);

int32_t SPVM_API_RUNTIME_get_basic_type_id(SPVM_RUNTIME* runtime, const char* basic_type_name);
int32_t SPVM_API_RUNTIME_get_basic_type_category(SPVM_RUNTIME* runtime, int32_t basic_type_id);
const char* SPVM_API_RUNTIME_get_basic_type_name(SPVM_RUNTIME* runtime, int32_t basic_type_id);
int32_t SPVM_API_RUNTIME_get_basic_type_name_id(SPVM_RUNTIME* runtime, int32_t basic_type_id);
int32_t SPVM_API_RUNTIME_get_basic_type_class_id(SPVM_RUNTIME* runtime, int32_t basic_type_id);
SPVM_RUNTIME_BASIC_TYPE* SPVM_API_RUNTIME_get_basic_type_with_name(SPVM_RUNTIME* runtime,  const char* basic_type_name);
SPVM_RUNTIME_BASIC_TYPE* SPVM_API_RUNTIME_get_basic_type(SPVM_RUNTIME* runtime, int32_t basic_type_id);

SPVM_RUNTIME_TYPE* SPVM_API_RUNTIME_get_type(SPVM_RUNTIME* runtime, int32_t type_id);
int32_t SPVM_API_RUNTIME_get_type_basic_type_id(SPVM_RUNTIME* runtime, int32_t type_id);
int32_t SPVM_API_RUNTIME_get_type_dimension(SPVM_RUNTIME* runtime, int32_t type_id);
int32_t SPVM_API_RUNTIME_get_type_width(SPVM_RUNTIME* runtime, int32_t type_id);
int32_t SPVM_API_RUNTIME_get_type_is_ref(SPVM_RUNTIME* runtime, int32_t type_id);
int32_t SPVM_API_RUNTIME_get_type_is_object(SPVM_RUNTIME* runtime, int32_t type_id);

int32_t SPVM_API_RUNTIME_get_class_id(SPVM_RUNTIME* runtime, const char* class_name);
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
SPVM_RUNTIME_CLASS* SPVM_API_RUNTIME_get_class(SPVM_RUNTIME* runtime, int32_t class_id);

#endif
