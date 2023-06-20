// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stddef.h>

#include "spvm_precompile.h"

#include "spvm_allocator.h"
#include "spvm_native.h"
#include "spvm_api.h"
#include "spvm_api_runtime.h"
#include "spvm_string_buffer.h"
#include "spvm_opcode.h"

SPVM_PRECOMPILE* SPVM_PRECOMPILE_new() {
  SPVM_PRECOMPILE* precompile = SPVM_ALLOCATOR_alloc_memory_block_unmanaged(sizeof(SPVM_PRECOMPILE));
  
  return precompile;
}

void SPVM_PRECOMPILE_free(SPVM_PRECOMPILE* precompile) {
  
  SPVM_ALLOCATOR_free_memory_block_unmanaged(precompile);
  precompile = NULL;
}

void SPVM_PRECOMPILE_set_runtime(SPVM_PRECOMPILE* precompile, SPVM_RUNTIME* runtime) {
  
  precompile->runtime = runtime;
}

SPVM_RUNTIME* SPVM_PRECOMPILE_get_runtime(SPVM_PRECOMPILE* precompile) {
  
  return precompile->runtime;
}

void SPVM_PRECOMPILE_build_source(SPVM_PRECOMPILE* precompile, SPVM_STRING_BUFFER* string_buffer, const char* basic_type_name) {
  SPVM_RUNTIME* runtime = precompile->runtime;
  
  int32_t basic_type_id = SPVM_API_RUNTIME_get_basic_type_id_by_name(runtime, basic_type_name);
  int32_t basic_type_methods_base_address_id = SPVM_API_RUNTIME_get_basic_type_methods_base_address_id(runtime, basic_type_id);
  int32_t basic_type_methods_length = SPVM_API_RUNTIME_get_basic_type_methods_length(runtime, basic_type_id);

  // Method implementations
  for (int32_t method_index = 0; method_index < basic_type_methods_length; method_index++) {
    int32_t method_address_id = basic_type_methods_base_address_id + method_index;
    int32_t method_name_id = SPVM_API_RUNTIME_get_method_name_id(runtime, SPVM_API_RUNTIME_get_method_by_address_id(runtime, method_address_id));
    const char* method_name = SPVM_API_RUNTIME_get_name(runtime, method_name_id);
    int32_t method_has_precompile_flag = SPVM_API_RUNTIME_get_method_is_precompile(runtime, SPVM_API_RUNTIME_get_method_by_address_id(runtime, method_address_id));
    if (method_has_precompile_flag) {
      SPVM_PRECOMPILE_build_method_source(precompile, string_buffer, basic_type_name, method_name);
    }
  }
  
  // If the basic type has anon methods, the anon methods is merged to this basic type
  int32_t basic_type_anon_basic_types_length = SPVM_API_RUNTIME_get_basic_type_anon_basic_types_length(runtime, basic_type_id);
  if (basic_type_anon_basic_types_length > 0) {
    int32_t basic_type_anon_basic_types_base_address_id = SPVM_API_RUNTIME_get_basic_type_anon_basic_types_base_address_id(runtime, basic_type_id);
    for (int32_t anon_basic_type_address_id = basic_type_anon_basic_types_base_address_id; anon_basic_type_address_id < basic_type_anon_basic_types_length; anon_basic_type_address_id++) {
      int32_t anon_basic_type_id = SPVM_API_RUNTIME_get_anon_basic_type_id(runtime, anon_basic_type_address_id);
      int32_t anon_basic_type_name_id = SPVM_API_RUNTIME_get_basic_type_name_id(runtime, anon_basic_type_id);
      const char* anon_basic_type_name = SPVM_API_RUNTIME_get_name(runtime, anon_basic_type_name_id);
      SPVM_PRECOMPILE_build_source(precompile, string_buffer, anon_basic_type_name);
    }
  }
  
  SPVM_STRING_BUFFER_add(string_buffer, "\n");
}

void SPVM_PRECOMPILE_build_header(SPVM_PRECOMPILE* precompile, SPVM_STRING_BUFFER* string_buffer) {
  SPVM_RUNTIME* runtime = precompile->runtime;
  
  // Include headers and define macros
  SPVM_STRING_BUFFER_add(string_buffer,
    "#include \"spvm_native.h\"\n"
    "#include \"spvm_implement.h\"\n"
    "#include <stdlib.h>\n"
    "#include <string.h>\n"
    "#include <stdio.h>\n"
    "#include <inttypes.h>\n"
    "#include <assert.h>\n"
  );
}

void SPVM_PRECOMPILE_build_method_declaration(SPVM_PRECOMPILE* precompile, SPVM_STRING_BUFFER* string_buffer, const char* basic_type_name, const char* method_name) {
  SPVM_RUNTIME* runtime = precompile->runtime;
  
  // Method declaration
  SPVM_STRING_BUFFER_add(string_buffer, "int32_t SPVMPRECOMPILE__");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)basic_type_name);
  SPVM_STRING_BUFFER_add(string_buffer, (char*)"__");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)method_name);
  {
    int32_t index = string_buffer->length - (strlen(basic_type_name) + 2 + strlen(method_name));
    
    while (index < string_buffer->length) {
      if (string_buffer->value[index] == ':') {
        string_buffer->value[index] = '_';
      }
      index++;
    }
  }
  SPVM_STRING_BUFFER_add(string_buffer, "(SPVM_ENV* env, SPVM_VALUE* stack)");
}

void SPVM_PRECOMPILE_build_method_source(SPVM_PRECOMPILE* precompile, SPVM_STRING_BUFFER* string_buffer, const char* current_basic_type_name, const char* current_method_name) {
  SPVM_RUNTIME* runtime = precompile->runtime;
  
  // Headers
  SPVM_PRECOMPILE_build_header(precompile, string_buffer);
  
  // Current basic type id
  int32_t current_basic_type_id = SPVM_API_RUNTIME_get_basic_type_id_by_name(runtime, current_basic_type_name);
  
  // Method
  int32_t current_method_address_id = SPVM_API_RUNTIME_get_method_address_id_by_name(runtime, current_basic_type_name, current_method_name);

  // Method declaration
  SPVM_PRECOMPILE_build_method_declaration(precompile, string_buffer, current_basic_type_name, current_method_name);

  // Block start
  SPVM_STRING_BUFFER_add(string_buffer, " {\n");
  
  // The basic type name
  SPVM_STRING_BUFFER_add(string_buffer,"  const char* current_basic_type_name = \"");
  SPVM_STRING_BUFFER_add(string_buffer, current_basic_type_name);
  SPVM_STRING_BUFFER_add(string_buffer, "\";\n");

  // Current method name
  SPVM_STRING_BUFFER_add(string_buffer, "  const char* current_method_name = \"");
  SPVM_STRING_BUFFER_add(string_buffer, current_method_name);
  SPVM_STRING_BUFFER_add(string_buffer, "\";\n");
  
  // Object header byte size
  SPVM_STRING_BUFFER_add(string_buffer, "  int32_t object_header_size = (intptr_t)env->object_header_size;\n");
  
  // object variable declarations
  int32_t call_stack_object_vars_length = SPVM_API_RUNTIME_get_method_call_stack_object_vars_length(runtime, SPVM_API_RUNTIME_get_method_by_address_id(runtime, current_method_address_id));
  if (call_stack_object_vars_length > 0) {
    SPVM_STRING_BUFFER_add(string_buffer, "  void* object_vars[");
    SPVM_STRING_BUFFER_add_int(string_buffer, call_stack_object_vars_length);
    SPVM_STRING_BUFFER_add(string_buffer, "] = {0};\n");
  }

  // ref variable declarations
  int32_t call_stack_ref_vars_length = SPVM_API_RUNTIME_get_method_call_stack_ref_vars_length(runtime, SPVM_API_RUNTIME_get_method_by_address_id(runtime, current_method_address_id));
  if (call_stack_ref_vars_length > 0) {
    SPVM_STRING_BUFFER_add(string_buffer, "  void* ref_vars[");
    SPVM_STRING_BUFFER_add_int(string_buffer, call_stack_ref_vars_length);
    SPVM_STRING_BUFFER_add(string_buffer, "] = {0};\n");
  }

  // double variable declarations
  int32_t call_stack_double_vars_length = SPVM_API_RUNTIME_get_method_call_stack_double_vars_length(runtime, SPVM_API_RUNTIME_get_method_by_address_id(runtime, current_method_address_id));
  if (call_stack_double_vars_length > 0) {
    SPVM_STRING_BUFFER_add(string_buffer, "  double double_vars[");
    SPVM_STRING_BUFFER_add_int(string_buffer, call_stack_double_vars_length);
    SPVM_STRING_BUFFER_add(string_buffer, "];\n");
  }

  // float variable declarations
  int32_t call_stack_float_vars_length = SPVM_API_RUNTIME_get_method_call_stack_float_vars_length(runtime, SPVM_API_RUNTIME_get_method_by_address_id(runtime, current_method_address_id));
  if (call_stack_float_vars_length > 0) {
    SPVM_STRING_BUFFER_add(string_buffer, "  float float_vars[");
    SPVM_STRING_BUFFER_add_int(string_buffer, call_stack_float_vars_length);
    SPVM_STRING_BUFFER_add(string_buffer, "];\n");
  }

  // long variable declarations
  int32_t call_stack_long_vars_length = SPVM_API_RUNTIME_get_method_call_stack_long_vars_length(runtime, SPVM_API_RUNTIME_get_method_by_address_id(runtime, current_method_address_id));
  if (call_stack_long_vars_length > 0) {
    SPVM_STRING_BUFFER_add(string_buffer, "  int64_t long_vars[");
    SPVM_STRING_BUFFER_add_int(string_buffer, call_stack_long_vars_length);
    SPVM_STRING_BUFFER_add(string_buffer, "];\n");
  }

  // int variable declarations
  int32_t call_stack_int_vars_length = SPVM_API_RUNTIME_get_method_call_stack_int_vars_length(runtime, SPVM_API_RUNTIME_get_method_by_address_id(runtime, current_method_address_id));
  if (call_stack_int_vars_length > 0) {
    SPVM_STRING_BUFFER_add(string_buffer, "  int32_t int_vars[");
    SPVM_STRING_BUFFER_add_int(string_buffer, call_stack_int_vars_length);
    SPVM_STRING_BUFFER_add(string_buffer, "];\n");
  }

  // Exception
  // volatile attribute is not needed, but the environment "FreeBSD 9.1" and "gcc 4.2.1" seems to performe wrong optimisation
  // in double pointer logic. volatile attribute fixed the test "ref.t" "SPVM::TestCase::Ref->test_pass_mulnum_ref_byte".
  // SPVM_STRING_BUFFER_add(string_buffer, "  volatile int32_t error_id = 0;\n");
  
  SPVM_STRING_BUFFER_add(string_buffer, "  int32_t error_id = 0;\n");
  
  SPVM_STRING_BUFFER_add(string_buffer, "  int32_t eval_error_id = 0;\n");

  int32_t method_mortal_stack_length = SPVM_API_RUNTIME_get_method_mortal_stack_length(runtime, SPVM_API_RUNTIME_get_method_by_address_id(runtime, current_method_address_id));
  if (method_mortal_stack_length > 0) {
    SPVM_STRING_BUFFER_add(string_buffer, "  int32_t mortal_stack[");
    SPVM_STRING_BUFFER_add_int(string_buffer, method_mortal_stack_length);
    SPVM_STRING_BUFFER_add(string_buffer, "];\n");
    SPVM_STRING_BUFFER_add(string_buffer, "  int32_t mortal_stack_top = 0;\n");
  }
  
  // short variable declarations
  int32_t call_stack_short_vars_length = SPVM_API_RUNTIME_get_method_call_stack_short_vars_length(runtime, SPVM_API_RUNTIME_get_method_by_address_id(runtime, current_method_address_id));
  if (call_stack_short_vars_length > 0) {
    SPVM_STRING_BUFFER_add(string_buffer, "  int16_t short_vars[");
    SPVM_STRING_BUFFER_add_int(string_buffer, call_stack_short_vars_length);
    SPVM_STRING_BUFFER_add(string_buffer, "];\n");
  }

  // byte variable declarations
  int32_t call_stack_byte_vars_length = SPVM_API_RUNTIME_get_method_call_stack_byte_vars_length(runtime, SPVM_API_RUNTIME_get_method_by_address_id(runtime, current_method_address_id));
  if (call_stack_byte_vars_length > 0) {
    SPVM_STRING_BUFFER_add(string_buffer, "  int8_t byte_vars[");
    SPVM_STRING_BUFFER_add_int(string_buffer, call_stack_byte_vars_length);
    SPVM_STRING_BUFFER_add(string_buffer, "];\n");
  }

  // Convert string
  SPVM_STRING_BUFFER_add(string_buffer, "  char convert_string_buffer[21];\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  char message[256];\n");

  SPVM_STRING_BUFFER_add(string_buffer, "  int32_t original_mortal_stack_top = 0;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  int32_t line = 0;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  int32_t arg_mem_id = 0;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  int32_t stack_index = 0;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  void* object = NULL;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  void* object1 = NULL;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  void* object2 = NULL;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  void* object_address = NULL;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  void* new_object_raw = NULL;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  void* array = NULL;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  int32_t index = 0;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  int32_t args_stack_length = 0;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  int32_t method_address_id = 0;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  int32_t entity_method_id = 0;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  int32_t return_value = 0;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  void* string = NULL;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  void* string1 = NULL;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  void* string2 = NULL;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  void* string3 = NULL;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  void* exception = NULL;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  void* type_name = NULL;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  void* get_field_object = NULL;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  void* dump = NULL;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  void* src_string = NULL;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  void* byte_arra = NULL;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  void** element_address = NULL;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  void** get_field_object_address = NULL;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  void* src_byte_array = NULL;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  void* byte_array = NULL;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  int32_t elem_isa = 0;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  int32_t cast_type_dimension = 0;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  int32_t type_dimension = 0;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  int32_t object_type_dimension_id = 0;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  int32_t object_basic_type_id = 0;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  int32_t runtime_assignability = 0;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_VALUE tmp_constant;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  int32_t field_address_id = 0;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  int8_t* mulnum_ref_byte;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  int16_t* mulnum_ref_short;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  int32_t* mulnum_ref_int;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  int64_t* mulnum_ref_long;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  float* mulnum_ref_float;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  double* mulnum_ref_double;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  int32_t type_stack_length;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  int8_t value_byte;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  int16_t value_short;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  int32_t value_int;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  int64_t value_long;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  float value_float;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  double value_double;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  int32_t src_basic_type_id;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  int32_t basic_type_id;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_VALUE* fields;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  int32_t src_string_length;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  int8_t* src_byte_array_data;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  int32_t src_byte_array_length;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  int8_t* byte_array_data;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  int32_t string_length;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  char* src_string_data;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  int32_t empty_or_undef;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  char* bytes;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  int32_t class_var_address_id;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  char* class_var_name;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  int32_t is_read_only;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  int32_t length;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  int32_t length1;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  int32_t length2;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  char* bytes1;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  char* bytes2;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  int32_t short_string_length;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  int32_t retval;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  int32_t cmp;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  int8_t* element_ptr_byte;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  char* basic_type_name;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  char* field_name;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  char* method_name;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  char* constant_string;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  int32_t constant_string_length;\n");

  SPVM_STRING_BUFFER_add(string_buffer, "  char* include_dir;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  char* include_dir_sep;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  char* module_rel_file;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  int32_t field_index;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  int32_t fields_length;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  char tmp_buffer[256];\n");

  SPVM_OPCODE* opcodes = SPVM_API_RUNTIME_get_opcodes(runtime);
  int32_t method_opcodes_base_address_id = SPVM_API_RUNTIME_get_method_opcodes_base_address_id(runtime, SPVM_API_RUNTIME_get_method_by_address_id(runtime, current_method_address_id));
  int32_t opcodes_length = SPVM_API_RUNTIME_get_method_opcodes_length(runtime, SPVM_API_RUNTIME_get_method_by_address_id(runtime, current_method_address_id));
  int32_t opcode_index = 0;
  
  SPVM_OPCODE* opcode = NULL;

  int32_t string_buffer_begin_offset = string_buffer->length;
  {
    SPVM_STRING_BUFFER_add(string_buffer, "  int32_t ");
    SPVM_PRECOMPILE_add_basic_type_id(precompile, string_buffer, current_basic_type_name);
    SPVM_STRING_BUFFER_add(string_buffer, " = -1;\n");
    
    SPVM_STRING_BUFFER_add(string_buffer, "  if (");
    SPVM_PRECOMPILE_add_basic_type_id(precompile, string_buffer, current_basic_type_name);
    SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
    SPVM_STRING_BUFFER_add(string_buffer, "    ");
    SPVM_PRECOMPILE_add_basic_type_id(precompile, string_buffer, current_basic_type_name);
    SPVM_STRING_BUFFER_add(string_buffer, " = SPVM_IMPLEMENT_GET_BASIC_TYPE_ID_RET(env, stack, \"");
    SPVM_STRING_BUFFER_add(string_buffer, current_basic_type_name);
    SPVM_STRING_BUFFER_add(string_buffer, "\", message, &error_id);\n");
    SPVM_STRING_BUFFER_add(string_buffer, "    if (error_id) {\n"
                                          "      goto END_OF_METHOD;\n"
                                          "    }\n");
    SPVM_STRING_BUFFER_add(string_buffer, "  }\n");

    SPVM_STRING_BUFFER_add(string_buffer, "  int32_t ");
    SPVM_PRECOMPILE_add_method_address_id(precompile, string_buffer, current_basic_type_name, current_method_name);
    SPVM_STRING_BUFFER_add(string_buffer, " = -1;\n");

    SPVM_STRING_BUFFER_add(string_buffer, "  if (");
    SPVM_PRECOMPILE_add_method_address_id(precompile, string_buffer, current_basic_type_name, current_method_name);
    SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
    SPVM_STRING_BUFFER_add(string_buffer, "    ");
    SPVM_PRECOMPILE_add_method_address_id(precompile, string_buffer, current_basic_type_name, current_method_name);
    SPVM_STRING_BUFFER_add(string_buffer, " = SPVM_IMPLEMENT_GET_METHOD_ID(env, stack, \"");
    SPVM_STRING_BUFFER_add(string_buffer, current_basic_type_name);
    SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
    SPVM_STRING_BUFFER_add(string_buffer, current_method_name);
    SPVM_STRING_BUFFER_add(string_buffer, "\", message, &error_id);\n");
    SPVM_STRING_BUFFER_add(string_buffer, "    if (error_id) {\n"
                                          "      goto END_OF_METHOD;\n"
                                          "    }\n");
    SPVM_STRING_BUFFER_add(string_buffer, "  }\n");

    SPVM_STRING_BUFFER_add(string_buffer, "  int32_t current_method_address_id = ");
    SPVM_PRECOMPILE_add_method_address_id(precompile, string_buffer, current_basic_type_name, current_method_name);
    SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  }
  opcode_index = 0;
  while (opcode_index < opcodes_length) {
    opcode = &(opcodes[method_opcodes_base_address_id + opcode_index]);
    int32_t opcode_id = opcode->id;

    int32_t basic_type_id = -1;
    int32_t field_address_id = -1;
    int32_t class_var_address_id = -1;
    int32_t method_address_id = -1;
    int32_t id_set = 1;
    switch(opcode_id) {
      case SPVM_OPCODE_C_ID_MOVE_OBJECT_WITH_TYPE_CHECKING: {
        basic_type_id = opcode->operand2;
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_OBJECT: {
        basic_type_id = opcode->operand1;
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_OBJECT_ARRAY: {
        basic_type_id = opcode->operand1;
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_MULDIM_ARRAY: {
        basic_type_id = opcode->operand1;
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_MULNUM_ARRAY: {
        basic_type_id = opcode->operand1;
        break;
      }
      case SPVM_OPCODE_C_ID_ISA:
      case SPVM_OPCODE_C_ID_ISA_ERROR:
      case SPVM_OPCODE_C_ID_IS_TYPE:
      case SPVM_OPCODE_C_ID_IS_ERROR:
      {
        basic_type_id = opcode->operand2;
        break;
      }
      case SPVM_OPCODE_C_ID_SET_ERROR_ID:
      {
        basic_type_id = opcode->operand0;
        break;
      }
      case SPVM_OPCODE_C_ID_GET_BASIC_TYPE_ID:
      {
        basic_type_id = opcode->operand1;
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_BYTE:
      case SPVM_OPCODE_C_ID_GET_FIELD_SHORT:
      case SPVM_OPCODE_C_ID_GET_FIELD_INT:
      case SPVM_OPCODE_C_ID_GET_FIELD_LONG:
      case SPVM_OPCODE_C_ID_GET_FIELD_FLOAT:
      case SPVM_OPCODE_C_ID_GET_FIELD_DOUBLE:
      case SPVM_OPCODE_C_ID_GET_FIELD_OBJECT:
      {
        field_address_id = opcode->operand2;
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_BYTE:
      case SPVM_OPCODE_C_ID_SET_FIELD_SHORT:
      case SPVM_OPCODE_C_ID_SET_FIELD_INT:
      case SPVM_OPCODE_C_ID_SET_FIELD_LONG:
      case SPVM_OPCODE_C_ID_SET_FIELD_FLOAT:
      case SPVM_OPCODE_C_ID_SET_FIELD_DOUBLE:
      case SPVM_OPCODE_C_ID_SET_FIELD_OBJECT:
      case SPVM_OPCODE_C_ID_SET_FIELD_UNDEF:
      case SPVM_OPCODE_C_ID_WEAKEN_FIELD:
      case SPVM_OPCODE_C_ID_UNWEAKEN_FIELD:
      case SPVM_OPCODE_C_ID_ISWEAK_FIELD:
      {
        field_address_id = opcode->operand1;
        break;
      }
      case SPVM_OPCODE_C_ID_GET_CLASS_VAR_BYTE:
      case SPVM_OPCODE_C_ID_GET_CLASS_VAR_SHORT:
      case SPVM_OPCODE_C_ID_GET_CLASS_VAR_INT:
      case SPVM_OPCODE_C_ID_GET_CLASS_VAR_LONG:
      case SPVM_OPCODE_C_ID_GET_CLASS_VAR_FLOAT:
      case SPVM_OPCODE_C_ID_GET_CLASS_VAR_DOUBLE:
      case SPVM_OPCODE_C_ID_GET_CLASS_VAR_OBJECT:
      {
        class_var_address_id = opcode->operand1;
        break;
      }
      case SPVM_OPCODE_C_ID_SET_CLASS_VAR_BYTE:
      case SPVM_OPCODE_C_ID_SET_CLASS_VAR_SHORT:
      case SPVM_OPCODE_C_ID_SET_CLASS_VAR_INT:
      case SPVM_OPCODE_C_ID_SET_CLASS_VAR_LONG:
      case SPVM_OPCODE_C_ID_SET_CLASS_VAR_FLOAT:
      case SPVM_OPCODE_C_ID_SET_CLASS_VAR_DOUBLE:
      case SPVM_OPCODE_C_ID_SET_CLASS_VAR_OBJECT:
      case SPVM_OPCODE_C_ID_SET_CLASS_VAR_UNDEF:
      {
        class_var_address_id = opcode->operand0;
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_CLASS_METHOD:
      case SPVM_OPCODE_C_ID_CALL_INSTANCE_METHOD_STATIC:
      {
        method_address_id = opcode->operand0;
        break;
      }
      default: {
        id_set = 0;
      }
    }
    
    if (id_set) {
      if (basic_type_id >= 0) {
        int32_t basic_type_name_id = SPVM_API_RUNTIME_get_basic_type_name_id(runtime, basic_type_id);
        const char* basic_type_name = SPVM_API_RUNTIME_get_name(runtime, basic_type_name_id);
        
        int32_t found = SPVM_PRECOMPILE_contains_basic_type_id(precompile, string_buffer->value + string_buffer_begin_offset, basic_type_name);
        if (!found) {
          SPVM_STRING_BUFFER_add(string_buffer, "  int32_t ");
          SPVM_PRECOMPILE_add_basic_type_id(precompile, string_buffer, basic_type_name);
          SPVM_STRING_BUFFER_add(string_buffer, " = -1;\n");
          
          SPVM_STRING_BUFFER_add(string_buffer, "  if (");
          SPVM_PRECOMPILE_add_basic_type_id(precompile, string_buffer, basic_type_name);
          SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
          SPVM_STRING_BUFFER_add(string_buffer, "    ");
          SPVM_PRECOMPILE_add_basic_type_id(precompile, string_buffer, basic_type_name);
          SPVM_STRING_BUFFER_add(string_buffer, " = SPVM_IMPLEMENT_GET_BASIC_TYPE_ID_RET(env, stack, \"");
          SPVM_STRING_BUFFER_add(string_buffer, basic_type_name);
          SPVM_STRING_BUFFER_add(string_buffer, "\", message, &error_id);\n");
          SPVM_STRING_BUFFER_add(string_buffer, "    if (error_id) {\n"
                                                "      goto END_OF_METHOD;\n"
                                                "    }\n");
          SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
          
        }
      }
      else if (field_address_id >= 0) {
        SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field_by_address_id(runtime, field_address_id);

        int32_t current_basic_type_id = SPVM_API_RUNTIME_get_field_current_basic_type_id(runtime, field);
        int32_t basic_type_name_id = SPVM_API_RUNTIME_get_basic_type_name_id(runtime, current_basic_type_id);
        const char* basic_type_name = SPVM_API_RUNTIME_get_name(runtime, basic_type_name_id);
        
        int32_t field_name_id = SPVM_API_RUNTIME_get_field_name_id(runtime, field);
        const char* field_name = SPVM_API_RUNTIME_get_name(runtime, field_name_id);
        int32_t found = SPVM_PRECOMPILE_contains_field_address_id(precompile, string_buffer->value + string_buffer_begin_offset, basic_type_name, field_name);
        if (!found) {
          SPVM_STRING_BUFFER_add(string_buffer, "  int32_t ");
          SPVM_PRECOMPILE_add_field_address_id(precompile, string_buffer, basic_type_name, field_name);
          SPVM_STRING_BUFFER_add(string_buffer, " = -1;\n");

          SPVM_STRING_BUFFER_add(string_buffer, "  if (");
          SPVM_PRECOMPILE_add_field_address_id(precompile, string_buffer, basic_type_name, field_name);
          SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
          SPVM_STRING_BUFFER_add(string_buffer, "    ");
          SPVM_PRECOMPILE_add_field_address_id(precompile, string_buffer, basic_type_name, field_name);
          SPVM_STRING_BUFFER_add(string_buffer, " = SPVM_IMPLEMENT_GET_FIELD_ID_STATIC(env, stack, \"");
          SPVM_STRING_BUFFER_add(string_buffer, basic_type_name);
          SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
          SPVM_STRING_BUFFER_add(string_buffer, field_name);
          SPVM_STRING_BUFFER_add(string_buffer, "\", message, &error_id);\n");
          SPVM_STRING_BUFFER_add(string_buffer, "    if (error_id) {\n"
                                                "      goto END_OF_METHOD;\n"
                                                "    }\n");
          SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        }
      }
      else if (class_var_address_id >= 0) {
        SPVM_RUNTIME_CLASS_VAR* class_var = SPVM_API_RUNTIME_get_class_var_by_address_id(runtime, class_var_address_id);
        
        int32_t current_basic_type_id = SPVM_API_RUNTIME_get_class_var_current_basic_type_id(runtime, class_var);
        int32_t basic_type_name_id = SPVM_API_RUNTIME_get_basic_type_name_id(runtime, current_basic_type_id);
        const char* basic_type_name = SPVM_API_RUNTIME_get_name(runtime, basic_type_name_id);
        int32_t class_var_name_id = SPVM_API_RUNTIME_get_class_var_name_id(runtime, class_var);
        const char* class_var_name = SPVM_API_RUNTIME_get_name(runtime, class_var_name_id);
        int32_t found = SPVM_PRECOMPILE_contains_class_var_address_id(precompile, string_buffer->value + string_buffer_begin_offset, basic_type_name, class_var_name);
        if (!found) {
          SPVM_STRING_BUFFER_add(string_buffer, "  int32_t ");
          SPVM_PRECOMPILE_add_class_var_address_id(precompile, string_buffer, basic_type_name, class_var_name);
          SPVM_STRING_BUFFER_add(string_buffer, " = -1;\n");

          SPVM_STRING_BUFFER_add(string_buffer, "  if (");
          SPVM_PRECOMPILE_add_class_var_address_id(precompile, string_buffer, basic_type_name, class_var_name);
          SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
          SPVM_STRING_BUFFER_add(string_buffer, "    ");
          SPVM_PRECOMPILE_add_class_var_address_id(precompile, string_buffer, basic_type_name, class_var_name);
          SPVM_STRING_BUFFER_add(string_buffer, " = SPVM_IMPLEMENT_GET_CLASS_VAR_ID(env, stack, \"");
          SPVM_STRING_BUFFER_add(string_buffer, basic_type_name);
          SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
          SPVM_STRING_BUFFER_add(string_buffer, class_var_name);
          SPVM_STRING_BUFFER_add(string_buffer, "\", message, &error_id);\n");
          SPVM_STRING_BUFFER_add(string_buffer, "    if (error_id) {\n"
                                                "      goto END_OF_METHOD;\n"
                                                "    }\n");
          SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        }
      }
      else if (method_address_id >= 0) {
        int32_t method_name_id = SPVM_API_RUNTIME_get_method_name_id(runtime, SPVM_API_RUNTIME_get_method_by_address_id(runtime, method_address_id));
        const char* method_name = SPVM_API_RUNTIME_get_name(runtime, method_name_id);
        int32_t method_current_basic_type_id = SPVM_API_RUNTIME_get_method_current_basic_type_id(runtime, SPVM_API_RUNTIME_get_method_by_address_id(runtime, method_address_id));
        int32_t basic_type_name_id = SPVM_API_RUNTIME_get_basic_type_name_id(runtime, method_current_basic_type_id);
        const char* basic_type_name = SPVM_API_RUNTIME_get_name(runtime, basic_type_name_id);
        int32_t found = SPVM_PRECOMPILE_contains_method_address_id(precompile, string_buffer->value + string_buffer_begin_offset, basic_type_name, method_name);
        
        if (!found) {
          SPVM_STRING_BUFFER_add(string_buffer, "  int32_t ");
          SPVM_PRECOMPILE_add_method_address_id(precompile, string_buffer, basic_type_name, method_name);
          SPVM_STRING_BUFFER_add(string_buffer, " = -1;\n");

          SPVM_STRING_BUFFER_add(string_buffer, "  if (");
          SPVM_PRECOMPILE_add_method_address_id(precompile, string_buffer, basic_type_name, method_name);
          SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
          SPVM_STRING_BUFFER_add(string_buffer, "    ");
          SPVM_PRECOMPILE_add_method_address_id(precompile, string_buffer, basic_type_name, method_name);
          SPVM_STRING_BUFFER_add(string_buffer, " = SPVM_IMPLEMENT_GET_METHOD_ID(env, stack, \"");
          SPVM_STRING_BUFFER_add(string_buffer, basic_type_name);
          SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
          SPVM_STRING_BUFFER_add(string_buffer, method_name);
          SPVM_STRING_BUFFER_add(string_buffer, "\", message, &error_id);\n");
          SPVM_STRING_BUFFER_add(string_buffer, "    if (error_id) {\n"
                                                "      goto END_OF_METHOD;\n"
                                                "    }\n");
          SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        }
      }
      else {
        assert(0);
      }
    }
    
    opcode_index++;
  }

  opcode_index = 0;
  while (opcode_index < opcodes_length) {

    // Line label
    SPVM_STRING_BUFFER_add(string_buffer, "L");
    SPVM_STRING_BUFFER_add_int(string_buffer, opcode_index);
    SPVM_STRING_BUFFER_add(string_buffer, ": ");
    
    opcode = &(opcodes[method_opcodes_base_address_id + opcode_index]);

    int32_t opcode_id = opcode->id;

    SPVM_STRING_BUFFER_add(string_buffer, "// ");
    SPVM_STRING_BUFFER_add(string_buffer, (char*)(SPVM_OPCODE_C_ID_NAMES())[opcode_id]);
    SPVM_STRING_BUFFER_add(string_buffer, "\n");
    
    switch (opcode_id) {

      case SPVM_OPCODE_C_ID_END_METHOD: {
        break;
      }
      case SPVM_OPCODE_C_ID_GOTO: {
        SPVM_STRING_BUFFER_add(string_buffer, "  goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_IF_EQ_ZERO: {
        SPVM_STRING_BUFFER_add(string_buffer, "  if (");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, 0);
        SPVM_STRING_BUFFER_add(string_buffer, " == 0) { goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, "; }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_IF_NE_ZERO: {
        SPVM_STRING_BUFFER_add(string_buffer, "  if (");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, 0);
        SPVM_STRING_BUFFER_add(string_buffer, " != 0) { goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, "; }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GOTO_END_OF_EVAL_ON_EXCEPTION: {
        int32_t line = opcode->operand2;
        
        SPVM_STRING_BUFFER_add(string_buffer, "  if (__builtin_expect(error_id, 0)) {\n"
                                              "    eval_error_id = error_id;\n"
                                              "    error_id = 0;\n"
                                              "    env->set_exception(env, stack, env->new_stack_trace_raw(env, stack, env->get_exception(env, stack), current_method_address_id, line = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, line);
        SPVM_STRING_BUFFER_add(string_buffer,  "));\n"
                                              "    goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer,  opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_GOTO_END_OF_METHOD_ON_EXCEPTION: {
        int32_t line = opcode->operand2;
        
        SPVM_STRING_BUFFER_add(string_buffer, "  if (__builtin_expect(error_id, 0)) {\n"
                                              "    env->set_exception(env, stack, env->new_stack_trace_raw(env, stack, env->get_exception(env, stack), current_method_address_id, line = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, line);
        SPVM_STRING_BUFFER_add(string_buffer,  "));\n"
                                              "    goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_LOOKUP_SWITCH: {
        // Default branch
        int32_t default_opcode_rel_index = opcode->operand1;
        
        // Cases length
        int32_t case_infos_length = opcode->operand2;

        SPVM_STRING_BUFFER_add(string_buffer, "  switch(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ") {\n");
        for (int32_t case_index = 0; case_index < case_infos_length; case_index++) {
          SPVM_OPCODE* opcode_case_info = &(opcodes[method_opcodes_base_address_id + opcode_index + 1 + case_index]);

          int32_t match = opcode_case_info->operand1;
          int32_t opcode_rel_index = opcode_case_info->operand2;
          
          SPVM_STRING_BUFFER_add(string_buffer, "    case ");
          SPVM_STRING_BUFFER_add_int(string_buffer, match);
          SPVM_STRING_BUFFER_add(string_buffer, ": goto L");
          SPVM_STRING_BUFFER_add_int(string_buffer, opcode_rel_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        }
        SPVM_STRING_BUFFER_add(string_buffer, "    default: goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, default_opcode_rel_index);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
        
                                              "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_CASE_INFO: {
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_MORTAL: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_PUSH_MORTAL(mortal_stack, mortal_stack_top, ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_LEAVE_SCOPE: {
        int32_t original_mortal_stack_top = opcode->operand0;
        if (method_mortal_stack_length > 0) {
          SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_LEAVE_SCOPE(env, stack, object_vars, mortal_stack, &mortal_stack_top, original_mortal_stack_top = ");
          SPVM_STRING_BUFFER_add_int(string_buffer, original_mortal_stack_top);
          SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        }
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_BYTE_ZERO: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_MOVE_BYTE_ZERO(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_SHORT_ZERO: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_MOVE_SHORT_ZERO(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_INT_ZERO: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_MOVE_INT_ZERO(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_LONG_ZERO: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_MOVE_LONG_ZERO(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_FLOAT_ZERO: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_MOVE_FLOAT_ZERO(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_DOUBLE_ZERO: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_MOVE_DOUBLE_ZERO(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_OBJECT_UNDEF: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_OBJECT_ASSIGN(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", NULL);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_MULNUM_BYTE_ZERO: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_MOVE_MULNUM_BYTE_ZERO(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_MULNUM_SHORT_ZERO: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_MOVE_MULNUM_SHORT_ZERO(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_MULNUM_INT_ZERO: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_MOVE_MULNUM_INT_ZERO(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_MULNUM_LONG_ZERO: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_MOVE_MULNUM_LONG_ZERO(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_MULNUM_FLOAT_ZERO: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_MOVE_MULNUM_FLOAT_ZERO(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_MULNUM_DOUBLE_ZERO: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_MOVE_MULNUM_DOUBLE_ZERO(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_CONSTANT_BYTE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_MOVE_CONSTANT_BYTE(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_STRING_BUFFER_add_byte(string_buffer, (int8_t)opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_CONSTANT_INT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_MOVE_CONSTANT_INT(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_STRING_BUFFER_add_int(string_buffer, (int32_t)opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_CONSTANT_LONG: {
        int64_t long_value = *(int64_t*)&opcode->operand1;
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_MOVE_CONSTANT_LONG(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_STRING_BUFFER_add_long(string_buffer, long_value);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_CONSTANT_FLOAT: {
        SPVM_VALUE value;
        value.ival = (int32_t)opcode->operand1;
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_MOVE_CONSTANT_FLOAT(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", (tmp_constant.ival = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, value.ival);
        SPVM_STRING_BUFFER_add(string_buffer, ", tmp_constant.fval));\n");
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_CONSTANT_DOUBLE: {
        double double_value = *(double*)&opcode->operand1;
        SPVM_VALUE value;
        value.dval = double_value;
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_MOVE_CONSTANT_DOUBLE(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", (tmp_constant.lval = ");
        SPVM_STRING_BUFFER_add_long(string_buffer, value.lval);
        SPVM_STRING_BUFFER_add(string_buffer, ", tmp_constant.dval));\n");
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_BYTE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_MOVE_BYTE(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_SHORT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_MOVE_SHORT(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_INT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_MOVE_INT(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_LONG: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_MOVE_LONG(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_FLOAT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_MOVE_FLOAT(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_DOUBLE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_MOVE_DOUBLE(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_OBJECT: {
          SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_MOVE_OBJECT(env, stack, &");
          SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
          SPVM_STRING_BUFFER_add(string_buffer, ", ");
          SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
          SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_OBJECT_WITH_TYPE_CHECKING: {
        int32_t cast_basic_type = opcode->operand2;
        int32_t cast_type_dimension = opcode->operand3;
        
        int32_t cast_basic_type_name_id = SPVM_API_RUNTIME_get_basic_type_name_id(runtime, cast_basic_type);
        const char* cast_basic_type_name = SPVM_API_RUNTIME_get_name(runtime, cast_basic_type_name_id);
        
        SPVM_STRING_BUFFER_add(string_buffer, "  basic_type_name = \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)cast_basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  basic_type_id = ");
        SPVM_PRECOMPILE_add_basic_type_id(precompile, string_buffer, cast_basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  assert(basic_type_id >= 0);\n");
                                              
        SPVM_STRING_BUFFER_add(string_buffer, "  cast_type_dimension = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_MOVE_OBJECT_WITH_TYPE_CHECKING(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", basic_type_id, cast_type_dimension, &error_id);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_OBJECT_CHECK_READ_ONLY: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_MOVE_OBJECT_CHECK_READ_ONLY(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", &error_id);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_REF: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_MOVE_REF(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_REF, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_REF, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_ADD_INT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_ADD_INT(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_ADD_LONG: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_ADD_LONG(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_ADD_FLOAT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_ADD_FLOAT(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_ADD_DOUBLE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_ADD_DOUBLE(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SUBTRACT_INT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SUBTRACT_INT(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SUBTRACT_LONG: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SUBTRACT_LONG(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SUBTRACT_FLOAT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SUBTRACT_FLOAT(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SUBTRACT_DOUBLE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SUBTRACT_DOUBLE(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_MULTIPLY_INT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_MULTIPLY_INT(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_MULTIPLY_LONG: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_MULTIPLY_LONG(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_MULTIPLY_FLOAT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_MULTIPLY_FLOAT(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_MULTIPLY_DOUBLE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_MULTIPLY_DOUBLE(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_DIVIDE_INT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_DIVIDE_INT(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ", &error_id);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_DIVIDE_LONG: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_DIVIDE_LONG(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ", &error_id);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_DIVIDE_FLOAT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_DIVIDE_FLOAT(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_DIVIDE_DOUBLE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_DIVIDE_DOUBLE(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_DIVIDE_UNSIGNED_INT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_DIVIDE_UNSIGNED_INT(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ", &error_id);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_DIVIDE_UNSIGNED_LONG: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_DIVIDE_UNSIGNED_LONG(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ", &error_id);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_REMAINDER_INT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_REMAINDER_INT(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ", &error_id);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_REMAINDER_LONG: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_REMAINDER_LONG(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ", &error_id);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_REMAINDER_UNSIGNED_INT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_REMAINDER_UNSIGNED_INT(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ", &error_id);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_REMAINDER_UNSIGNED_LONG: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_REMAINDER_UNSIGNED_LONG(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ", &error_id);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_LEFT_SHIFT_INT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_LEFT_SHIFT_INT(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_LEFT_SHIFT_LONG: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_LEFT_SHIFT_LONG(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_RIGHT_ARITHMETIC_SHIFT_INT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_RIGHT_ARITHMETIC_SHIFT_INT(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_RIGHT_ARITHMETIC_SHIFT_LONG: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_RIGHT_ARITHMETIC_SHIFT_LONG(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_RIGHT_LOGICAL_SHIFT_INT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_RIGHT_LOGICAL_SHIFT_INT(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_RIGHT_LOGICAL_SHIFT_LONG: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_RIGHT_LOGICAL_SHIFT_LONG(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_BIT_AND_INT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_BIT_AND_INT(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_BIT_AND_LONG: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_BIT_AND_LONG(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_BIT_OR_INT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_BIT_OR_INT(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_BIT_OR_LONG: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_BIT_OR_LONG(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_BIT_XOR_INT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_BIT_XOR_INT(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_BIT_XOR_LONG: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_BIT_XOR_LONG(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_BIT_NOT_INT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_BIT_NOT_INT(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_BIT_NOT_LONG: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_BIT_NOT_LONG(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_NEGATE_INT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_NEGATE_INT(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_NEGATE_LONG: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_NEGATE_LONG(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_NEGATE_FLOAT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_NEGATE_FLOAT(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_NEGATE_DOUBLE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_NEGATE_DOUBLE(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_CONCAT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_CONCAT(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ", &error_id);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_BOOL_CONVERSION_INT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_BOOL_CONVERSION_INT(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_BOOL_CONVERSION_LONG: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_BOOL_CONVERSION_LONG(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_BOOL_CONVERSION_FLOAT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_BOOL_CONVERSION_FLOAT(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_BOOL_CONVERSION_DOUBLE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_BOOL_CONVERSION_DOUBLE(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_BOOL_CONVERSION_OBJECT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_BOOL_CONVERSION_OBJECT(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_BOOL_CONVERSION_REF: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_BOOL_CONVERSION_REF(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_REF, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_BOOL_CONVERSION_BOOL_OBJECT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_BOOL_CONVERSION_BOOL_OBJECT(env, stack, ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_EQ_INT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_EQ_INT(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_EQ_LONG: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_EQ_LONG(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_EQ_FLOAT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_EQ_FLOAT(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_EQ_DOUBLE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_EQ_DOUBLE(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_EQ_OBJECT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_EQ_OBJECT(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_EQ_REF: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_EQ_REF(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_REF, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_REF, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_NE_INT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_NE_INT(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_NE_LONG: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_NE_LONG(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_NE_FLOAT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_NE_FLOAT(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_NE_DOUBLE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_NE_DOUBLE(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_NE_OBJECT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_NE_OBJECT(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_NE_REF: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_NE_REF(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_REF, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_REF, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GT_INT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GT_INT(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GT_LONG: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GT_LONG(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GT_FLOAT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GT_FLOAT(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GT_DOUBLE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GT_DOUBLE(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GE_INT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GE_INT(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GE_LONG: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GE_LONG(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GE_FLOAT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GE_FLOAT(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GE_DOUBLE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GE_DOUBLE(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_LT_INT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_LT_INT(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_LT_LONG: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_LT_LONG(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_LT_FLOAT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_LT_FLOAT(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_LT_DOUBLE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_LT_DOUBLE(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_LE_INT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_LE_INT(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_LE_LONG: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_LE_LONG(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_LE_FLOAT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_LE_FLOAT(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_LE_DOUBLE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_LE_DOUBLE(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_CMP_INT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_CMP_INT(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_CMP_LONG: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_CMP_LONG(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_CMP_FLOAT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_CMP_FLOAT(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_CMP_DOUBLE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_CMP_DOUBLE(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_IS_UNDEF: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_IS_UNDEF(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_IS_NOT_UNDEF: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_IS_NOT_UNDEF(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_STRING_EQ: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_STRING_EQ(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_STRING_NE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_STRING_NE(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_STRING_GT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_STRING_GT(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_STRING_GE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_STRING_GE(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_STRING_LT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_STRING_LT(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_STRING_LE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_STRING_LE(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_STRING_CMP: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_STRING_CMP(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_OBJECT: {
        int32_t basic_type_id = opcode->operand1;
        int32_t basic_type_name_id = SPVM_API_RUNTIME_get_basic_type_name_id(runtime, basic_type_id);
        const char* basic_type_name = SPVM_API_RUNTIME_get_name(runtime, basic_type_name_id);
        
        SPVM_STRING_BUFFER_add(string_buffer, "  basic_type_name = \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  basic_type_id = ");
        SPVM_PRECOMPILE_add_basic_type_id(precompile, string_buffer, basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  assert(basic_type_id >= 0);\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_NEW_OBJECT(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", basic_type_id, &error_id);");
        
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_OBJECT_ARRAY: {
        int32_t basic_type_id = opcode->operand1;
        int32_t basic_type_name_id = SPVM_API_RUNTIME_get_basic_type_name_id(runtime, basic_type_id);
        const char* basic_type_name = SPVM_API_RUNTIME_get_name(runtime, basic_type_name_id);
        
        SPVM_STRING_BUFFER_add(string_buffer, "  basic_type_name = \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  length = *(int32_t*)&");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  basic_type_id = ");
        SPVM_PRECOMPILE_add_basic_type_id(precompile, string_buffer, basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  assert(basic_type_id >= 0);\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_NEW_OBJECT_ARRAY(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", basic_type_id, length, &error_id);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_MULDIM_ARRAY: {
        int32_t basic_type_id = opcode->operand1;
        int32_t basic_type_name_id = SPVM_API_RUNTIME_get_basic_type_name_id(runtime, basic_type_id);
        const char* basic_type_name = SPVM_API_RUNTIME_get_name(runtime, basic_type_name_id);
        int32_t type_dimension = opcode->operand3;
        
        SPVM_STRING_BUFFER_add(string_buffer, "  basic_type_name = \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  type_dimension = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, type_dimension);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  length = *(int32_t*)&");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  basic_type_id = ");
        SPVM_PRECOMPILE_add_basic_type_id(precompile, string_buffer, basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  assert(basic_type_id >= 0);\n");
                                              
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_NEW_MULDIM_ARRAY(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", basic_type_id, type_dimension, length, &error_id);\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_MULNUM_ARRAY: {
        int32_t basic_type_id = opcode->operand1;
        int32_t basic_type_name_id = SPVM_API_RUNTIME_get_basic_type_name_id(runtime, basic_type_id);
        const char* basic_type_name = SPVM_API_RUNTIME_get_name(runtime, basic_type_name_id);
        
        SPVM_STRING_BUFFER_add(string_buffer, "  basic_type_name = \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  length = *(int32_t*)&");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  basic_type_id = ");
        SPVM_PRECOMPILE_add_basic_type_id(precompile, string_buffer, basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  assert(basic_type_id >= 0);\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_NEW_MULNUM_ARRAY(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", basic_type_id, length, &error_id);\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_BYTE_ARRAY: {
        SPVM_STRING_BUFFER_add(string_buffer, "  length = *(int32_t*)&");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_IMPLEMENT_NEW_BYTE_ARRAY(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", length, &error_id);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_SHORT_ARRAY: {
        SPVM_STRING_BUFFER_add(string_buffer, "  length = *(int32_t*)&");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_IMPLEMENT_NEW_SHORT_ARRAY(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", length, &error_id);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_INT_ARRAY: {
        SPVM_STRING_BUFFER_add(string_buffer, "  length = *(int32_t*)&");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_IMPLEMENT_NEW_INT_ARRAY(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", length, &error_id);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_LONG_ARRAY: {
        SPVM_STRING_BUFFER_add(string_buffer, "  length = *(int32_t*)&");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_IMPLEMENT_NEW_LONG_ARRAY(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", length, &error_id);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_FLOAT_ARRAY: {
        SPVM_STRING_BUFFER_add(string_buffer, "  length = *(int32_t*)&");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_IMPLEMENT_NEW_FLOAT_ARRAY(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", length, &error_id);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_DOUBLE_ARRAY: {
        SPVM_STRING_BUFFER_add(string_buffer, "  length = *(int32_t*)&");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_IMPLEMENT_NEW_DOUBLE_ARRAY(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", length, &error_id);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_STRING: {
        int32_t constant_string_id = opcode->operand1;
        
        int32_t constant_string_length;
        const char* constant_string_value = SPVM_API_RUNTIME_get_constant_string_value(runtime, constant_string_id, &constant_string_length);
        SPVM_STRING_BUFFER_add(string_buffer,
          "  constant_string = \""
        );
        for (int32_t i = 0; i < constant_string_length; i++) {
          SPVM_STRING_BUFFER_add_hex_char(string_buffer, constant_string_value[i]);
        }
        SPVM_STRING_BUFFER_add(string_buffer, "\";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  constant_string_length = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, constant_string_length);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_NEW_STRING(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", constant_string, constant_string_length, &error_id);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_STRING_LEN: {
        SPVM_STRING_BUFFER_add(string_buffer, "  length = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_NEW_STRING_LEN(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", length, &error_id);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_IS_READ_ONLY: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_IS_READ_ONLY(env, stack, ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, 0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_MAKE_READ_ONLY: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_MAKE_READ_ONLY(env, stack, ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ARRAY_ELEMENT_BYTE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  array = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  index = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_ARRAY_ELEMENT_BYTE(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", array, index, &error_id, object_header_size);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ARRAY_ELEMENT_SHORT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  array = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  index = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_ARRAY_ELEMENT_SHORT(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", array, index, &error_id, object_header_size);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ARRAY_ELEMENT_INT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  array = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  index = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_ARRAY_ELEMENT_INT(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", array, index, &error_id, object_header_size);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ARRAY_ELEMENT_LONG: {
        SPVM_STRING_BUFFER_add(string_buffer, "  array = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  index = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_ARRAY_ELEMENT_LONG(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", array, index, &error_id, object_header_size);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ARRAY_ELEMENT_FLOAT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  array = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  index = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_ARRAY_ELEMENT_FLOAT(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", array, index, &error_id, object_header_size);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ARRAY_ELEMENT_DOUBLE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  array = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  index = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_ARRAY_ELEMENT_DOUBLE(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", array, index, &error_id, object_header_size);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ARRAY_ELEMENT_OBJECT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  array = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  index = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_ARRAY_ELEMENT_OBJECT(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", array, index, &error_id, object_header_size);\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_BYTE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  array = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  index = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_ARRAY_ELEMENT_BYTE(env, stack, array, index, ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ", &error_id, object_header_size);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_SHORT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  array = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  index = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_ARRAY_ELEMENT_SHORT(env, stack, array, index, ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ", &error_id, object_header_size);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_INT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  array = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  index = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_ARRAY_ELEMENT_INT(env, stack, array, index, ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ", &error_id, object_header_size);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_LONG: {
        SPVM_STRING_BUFFER_add(string_buffer, "  array = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  index = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_ARRAY_ELEMENT_LONG(env, stack, array, index, ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ", &error_id, object_header_size);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_FLOAT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  array = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  index = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_ARRAY_ELEMENT_FLOAT(env, stack, array, index, ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ", &error_id, object_header_size);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_DOUBLE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  array = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  index = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_ARRAY_ELEMENT_DOUBLE(env, stack, array, index, ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ", &error_id, object_header_size);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_OBJECT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  array = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  index = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_ARRAY_ELEMENT_OBJECT(env, stack, array, index, ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ", &error_id, object_header_size);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_OBJECT_CHECK_TYPE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  array = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  index = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_ARRAY_ELEMENT_OBJECT_CHECK_TYPE(env, stack, array, index, ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ", &error_id, object_header_size);\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_UNDEF: {
        SPVM_STRING_BUFFER_add(string_buffer, "  array = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  index = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_ARRAY_ELEMENT_UNDEF(env, stack, array, index, &error_id, object_header_size);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_LENGTH: {
        SPVM_STRING_BUFFER_add(string_buffer, "  array = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_ARRAY_LENGTH(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", array, &error_id);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_BYTE:
      case SPVM_OPCODE_C_ID_GET_FIELD_SHORT:
      case SPVM_OPCODE_C_ID_GET_FIELD_INT:
      case SPVM_OPCODE_C_ID_GET_FIELD_LONG:
      case SPVM_OPCODE_C_ID_GET_FIELD_FLOAT:
      case SPVM_OPCODE_C_ID_GET_FIELD_DOUBLE:
      case SPVM_OPCODE_C_ID_GET_FIELD_OBJECT:
      {
        int32_t field_address_id = opcode->operand2;
        
        SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field_by_address_id(runtime, field_address_id);
        int32_t field_current_basic_type_id = SPVM_API_RUNTIME_get_field_current_basic_type_id(runtime, field);
        int32_t basic_type_name_id = SPVM_API_RUNTIME_get_basic_type_name_id(runtime, field_current_basic_type_id);
        const char* basic_type_name = SPVM_API_RUNTIME_get_name(runtime, basic_type_name_id);
        int32_t field_name_id = SPVM_API_RUNTIME_get_field_name_id(runtime, field);
        const char* field_name = SPVM_API_RUNTIME_get_name(runtime, field_name_id);
        
        SPVM_STRING_BUFFER_add(string_buffer, "  object = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  basic_type_name = \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  field_name = \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  field_address_id = ");
        SPVM_PRECOMPILE_add_field_address_id(precompile, string_buffer, basic_type_name, field_name);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  assert(field_address_id >= 0);\n");
        
        switch (opcode_id) {
          case SPVM_OPCODE_C_ID_GET_FIELD_BYTE: {
            SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_FIELD_BYTE(env, stack, ");
            SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0);
            SPVM_STRING_BUFFER_add(string_buffer, ", object, field_address_id, &error_id, object_header_size);\n");
            break;
          }
          case SPVM_OPCODE_C_ID_GET_FIELD_SHORT: {
            SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_FIELD_SHORT(env, stack, ");
            SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0);
            SPVM_STRING_BUFFER_add(string_buffer, ", object, field_address_id, &error_id, object_header_size);\n");
            break;
          }
          case SPVM_OPCODE_C_ID_GET_FIELD_INT: {
            SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_FIELD_INT(env, stack, ");
            SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
            SPVM_STRING_BUFFER_add(string_buffer, ", object, field_address_id, &error_id, object_header_size);\n");
            break;
          }
          case SPVM_OPCODE_C_ID_GET_FIELD_LONG: {
            SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_FIELD_LONG(env, stack, ");
            SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0);
            SPVM_STRING_BUFFER_add(string_buffer, ", object, field_address_id, &error_id, object_header_size);\n");
            break;
          }
          case SPVM_OPCODE_C_ID_GET_FIELD_FLOAT: {
            SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_FIELD_FLOAT(env, stack, ");
            SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0);
            SPVM_STRING_BUFFER_add(string_buffer, ", object, field_address_id, &error_id, object_header_size);\n");
            break;
          }
          case SPVM_OPCODE_C_ID_GET_FIELD_DOUBLE: {
            SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_FIELD_DOUBLE(env, stack, ");
            SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0);
            SPVM_STRING_BUFFER_add(string_buffer, ", object, field_address_id, &error_id, object_header_size);\n");
            break;
          }
          case SPVM_OPCODE_C_ID_GET_FIELD_OBJECT: {
            SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_FIELD_OBJECT(env, stack, ");
            SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
            SPVM_STRING_BUFFER_add(string_buffer, ", object, field_address_id, &error_id, object_header_size);\n");
            break;
          }
          default: {
            assert(0);
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_BYTE:
      case SPVM_OPCODE_C_ID_SET_FIELD_SHORT:
      case SPVM_OPCODE_C_ID_SET_FIELD_INT:
      case SPVM_OPCODE_C_ID_SET_FIELD_LONG:
      case SPVM_OPCODE_C_ID_SET_FIELD_FLOAT:
      case SPVM_OPCODE_C_ID_SET_FIELD_DOUBLE:
      case SPVM_OPCODE_C_ID_SET_FIELD_OBJECT:
      case SPVM_OPCODE_C_ID_SET_FIELD_UNDEF:
      {
        int32_t field_address_id = opcode->operand1;
        
        SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field_by_address_id(runtime, field_address_id);
        int32_t field_current_basic_type_id = SPVM_API_RUNTIME_get_field_current_basic_type_id(runtime, field);
        int32_t basic_type_name_id = SPVM_API_RUNTIME_get_basic_type_name_id(runtime, field_current_basic_type_id);
        const char* basic_type_name = SPVM_API_RUNTIME_get_name(runtime, basic_type_name_id);
        int32_t field_name_id = SPVM_API_RUNTIME_get_field_name_id(runtime, field);
        const char* field_name = SPVM_API_RUNTIME_get_name(runtime, field_name_id);
        
        SPVM_STRING_BUFFER_add(string_buffer, "  object = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  basic_type_name = \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  field_name = \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  field_address_id = ");
        SPVM_PRECOMPILE_add_field_address_id(precompile, string_buffer, basic_type_name, field_name);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  assert(field_address_id >= 0);\n");
        
        switch (opcode_id) {
          case SPVM_OPCODE_C_ID_SET_FIELD_BYTE: {
            SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_FIELD_BYTE(env, stack, object, field_address_id, ");
            SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand2);
            SPVM_STRING_BUFFER_add(string_buffer, ", &error_id, object_header_size);\n");
            break;
          }
          case SPVM_OPCODE_C_ID_SET_FIELD_SHORT: {
            SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_FIELD_SHORT(env, stack, object, field_address_id, ");
            SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand2);
            SPVM_STRING_BUFFER_add(string_buffer, ", &error_id, object_header_size);\n");
            break;
          }
          case SPVM_OPCODE_C_ID_SET_FIELD_INT: {
            SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_FIELD_INT(env, stack, object, field_address_id, ");
            SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand2);
            SPVM_STRING_BUFFER_add(string_buffer, ", &error_id, object_header_size);\n");
            break;
          }
          case SPVM_OPCODE_C_ID_SET_FIELD_LONG: {
            SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_FIELD_LONG(env, stack, object, field_address_id, ");
            SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand2);
            SPVM_STRING_BUFFER_add(string_buffer, ", &error_id, object_header_size);\n");
            break;
          }
          case SPVM_OPCODE_C_ID_SET_FIELD_FLOAT: {
            SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_FIELD_FLOAT(env, stack, object, field_address_id, ");
            SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand2);
            SPVM_STRING_BUFFER_add(string_buffer, ", &error_id, object_header_size);\n");
            break;
          }
          case SPVM_OPCODE_C_ID_SET_FIELD_DOUBLE: {
            SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_FIELD_DOUBLE(env, stack, object, field_address_id, ");
            SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand2);
            SPVM_STRING_BUFFER_add(string_buffer, ", &error_id, object_header_size);\n");
            break;
          }
          case SPVM_OPCODE_C_ID_SET_FIELD_OBJECT: {
            SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_FIELD_OBJECT(env, stack, object, field_address_id, ");
            SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand2);
            SPVM_STRING_BUFFER_add(string_buffer, ", &error_id, object_header_size);\n");
            break;
          }
          case SPVM_OPCODE_C_ID_SET_FIELD_UNDEF: {
            SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_FIELD_UNDEF(env, stack, object, field_address_id, &error_id, object_header_size);\n");
            break;
          }
          default: {
            assert(0);
          }
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_CLASS_VAR_BYTE:
      case SPVM_OPCODE_C_ID_GET_CLASS_VAR_SHORT:
      case SPVM_OPCODE_C_ID_GET_CLASS_VAR_INT:
      case SPVM_OPCODE_C_ID_GET_CLASS_VAR_LONG:
      case SPVM_OPCODE_C_ID_GET_CLASS_VAR_FLOAT:
      case SPVM_OPCODE_C_ID_GET_CLASS_VAR_DOUBLE:
      case SPVM_OPCODE_C_ID_GET_CLASS_VAR_OBJECT:
      {
        int32_t class_var_address_id = opcode->operand1;
        
        SPVM_RUNTIME_CLASS_VAR* class_var = SPVM_API_RUNTIME_get_class_var_by_address_id(runtime, class_var_address_id);
        int32_t class_var_current_basic_type_id = SPVM_API_RUNTIME_get_class_var_current_basic_type_id(runtime, class_var);
        int32_t basic_type_name_id = SPVM_API_RUNTIME_get_basic_type_name_id(runtime, class_var_current_basic_type_id);
        const char* basic_type_name = SPVM_API_RUNTIME_get_name(runtime, basic_type_name_id);
        int32_t class_var_name_id = SPVM_API_RUNTIME_get_class_var_name_id(runtime, class_var);
        const char* class_var_name = SPVM_API_RUNTIME_get_name(runtime, class_var_name_id);
        
        SPVM_STRING_BUFFER_add(string_buffer, "  basic_type_name = \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  class_var_name = \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)class_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  class_var_address_id = ");
        SPVM_PRECOMPILE_add_class_var_address_id(precompile, string_buffer, basic_type_name, class_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  assert(class_var_address_id >= 0);\n");
                                              
        switch (opcode_id) {
          case SPVM_OPCODE_C_ID_GET_CLASS_VAR_BYTE: {
            SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_CLASS_VAR_BYTE(env, stack, ");
            SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0);
            SPVM_STRING_BUFFER_add(string_buffer, ", class_var_address_id);\n");
            break;
          }
          case SPVM_OPCODE_C_ID_GET_CLASS_VAR_SHORT: {
            SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_CLASS_VAR_SHORT(env, stack, ");
            SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0);
            SPVM_STRING_BUFFER_add(string_buffer, ", class_var_address_id);\n");
            break;
          }
          case SPVM_OPCODE_C_ID_GET_CLASS_VAR_INT: {
            SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_CLASS_VAR_INT(env, stack, ");
            SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
            SPVM_STRING_BUFFER_add(string_buffer, ", class_var_address_id);\n");
            break;
          }
          case SPVM_OPCODE_C_ID_GET_CLASS_VAR_LONG: {
            SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_CLASS_VAR_LONG(env, stack, ");
            SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0);
            SPVM_STRING_BUFFER_add(string_buffer, ", class_var_address_id);\n");
            break;
          }
          case SPVM_OPCODE_C_ID_GET_CLASS_VAR_FLOAT: {
            SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_CLASS_VAR_FLOAT(env, stack, ");
            SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0);
            SPVM_STRING_BUFFER_add(string_buffer, ", class_var_address_id);\n");
            break;
          }
          case SPVM_OPCODE_C_ID_GET_CLASS_VAR_DOUBLE: {
            SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_CLASS_VAR_DOUBLE(env, stack, ");
            SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0);
            SPVM_STRING_BUFFER_add(string_buffer, ", class_var_address_id);\n");
            break;
          }
          case SPVM_OPCODE_C_ID_GET_CLASS_VAR_OBJECT: {
            SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_CLASS_VAR_OBJECT(env, stack, &");
            SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
            SPVM_STRING_BUFFER_add(string_buffer, ", class_var_address_id);\n");
            break;
          }
          default: {
            assert(0);
          }
        }
        
        break;
      }
      case SPVM_OPCODE_C_ID_SET_CLASS_VAR_BYTE:
      case SPVM_OPCODE_C_ID_SET_CLASS_VAR_SHORT:
      case SPVM_OPCODE_C_ID_SET_CLASS_VAR_INT:
      case SPVM_OPCODE_C_ID_SET_CLASS_VAR_LONG:
      case SPVM_OPCODE_C_ID_SET_CLASS_VAR_FLOAT:
      case SPVM_OPCODE_C_ID_SET_CLASS_VAR_DOUBLE:
      case SPVM_OPCODE_C_ID_SET_CLASS_VAR_OBJECT:
      case SPVM_OPCODE_C_ID_SET_CLASS_VAR_UNDEF:
      {
        int32_t class_var_address_id = opcode->operand0;
        
        SPVM_RUNTIME_CLASS_VAR* class_var = SPVM_API_RUNTIME_get_class_var_by_address_id(runtime, class_var_address_id);
        int32_t class_var_current_basic_type_id = SPVM_API_RUNTIME_get_class_var_current_basic_type_id(runtime, class_var);
        int32_t basic_type_name_id = SPVM_API_RUNTIME_get_basic_type_name_id(runtime, class_var_current_basic_type_id);
        const char* basic_type_name = SPVM_API_RUNTIME_get_name(runtime, basic_type_name_id);
        int32_t class_var_name_id = SPVM_API_RUNTIME_get_class_var_name_id(runtime, class_var);
        const char* class_var_name = SPVM_API_RUNTIME_get_name(runtime, class_var_name_id);
        
        SPVM_STRING_BUFFER_add(string_buffer, "  basic_type_name = \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  class_var_name = \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)class_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  class_var_address_id = ");
        SPVM_PRECOMPILE_add_class_var_address_id(precompile, string_buffer, basic_type_name, class_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  assert(class_var_address_id >= 0);\n");
                                              
        switch (opcode_id) {
          case SPVM_OPCODE_C_ID_SET_CLASS_VAR_BYTE: {
            SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_CLASS_VAR_BYTE(env, stack, class_var_address_id, ");
            SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand1);
            SPVM_STRING_BUFFER_add(string_buffer, ");\n");
            break;
          }
          case SPVM_OPCODE_C_ID_SET_CLASS_VAR_SHORT: {
            SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_CLASS_VAR_SHORT(env, stack, class_var_address_id, ");
            SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand1);
            SPVM_STRING_BUFFER_add(string_buffer, ");\n");
            break;
          }
          case SPVM_OPCODE_C_ID_SET_CLASS_VAR_INT: {
            SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_CLASS_VAR_INT(env, stack, class_var_address_id, ");
            SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
            SPVM_STRING_BUFFER_add(string_buffer, ");\n");
            break;
          }
          case SPVM_OPCODE_C_ID_SET_CLASS_VAR_LONG: {
            SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_CLASS_VAR_LONG(env, stack, class_var_address_id, ");
            SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1);
            SPVM_STRING_BUFFER_add(string_buffer, ");\n");
            break;
          }
          case SPVM_OPCODE_C_ID_SET_CLASS_VAR_FLOAT: {
            SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_CLASS_VAR_FLOAT(env, stack, class_var_address_id, ");
            SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand1);
            SPVM_STRING_BUFFER_add(string_buffer, ");\n");
            break;
          }
          case SPVM_OPCODE_C_ID_SET_CLASS_VAR_DOUBLE: {
            SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_CLASS_VAR_DOUBLE(env, stack, class_var_address_id, ");
            SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand1);
            SPVM_STRING_BUFFER_add(string_buffer, ");\n");
            break;
          }
          case SPVM_OPCODE_C_ID_SET_CLASS_VAR_OBJECT: {
            SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_CLASS_VAR_OBJECT(env, stack, class_var_address_id, ");
            SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
            SPVM_STRING_BUFFER_add(string_buffer, ");\n");
            break;
          }
          case SPVM_OPCODE_C_ID_SET_CLASS_VAR_UNDEF: {
            SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_CLASS_VAR_UNDEF(env, stack, class_var_address_id);\n");
            break;
          }
          default: {
            assert(0);
          }
        }
        
        break;
      }
      case SPVM_OPCODE_C_ID_GET_EXCEPTION_VAR: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_EXCEPTION_VAR(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_EXCEPTION_VAR: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_EXCEPTION_VAR(env, stack, ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_EXCEPTION_VAR_UNDEF: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_EXCEPTION_VAR_UNDEF(env, stack);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_ISA:
      {
        int32_t basic_type_id = opcode->operand2;
        int32_t type_dimension = opcode->operand3;
        int32_t basic_type_name_id = SPVM_API_RUNTIME_get_basic_type_name_id(runtime, basic_type_id);
        const char* basic_type_name = SPVM_API_RUNTIME_get_name(runtime, basic_type_name_id);
        
        SPVM_STRING_BUFFER_add(string_buffer, "  object = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  type_dimension = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, type_dimension);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  basic_type_id = ");
        SPVM_PRECOMPILE_add_basic_type_id(precompile, string_buffer, basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  assert(basic_type_id >= 0);\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_ISA(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, 0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object, basic_type_id, type_dimension);\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_ISA_ERROR:
      {
        int32_t basic_type_id = opcode->operand2;
        int32_t type_dimension = opcode->operand3;
        int32_t basic_type_name_id = SPVM_API_RUNTIME_get_basic_type_name_id(runtime, basic_type_id);
        const char* basic_type_name = SPVM_API_RUNTIME_get_name(runtime, basic_type_name_id);
        
        SPVM_STRING_BUFFER_add(string_buffer, "  src_basic_type_id = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  type_dimension = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, type_dimension);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  basic_type_id = ");
        SPVM_PRECOMPILE_add_basic_type_id(precompile, string_buffer, basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  assert(basic_type_id >= 0);\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_ISA_ERROR(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, 0);
        SPVM_STRING_BUFFER_add(string_buffer, ", src_basic_type_id, basic_type_id, type_dimension);\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_IS_TYPE:
      {
        int32_t basic_type_id = opcode->operand2;
        int32_t type_dimension = opcode->operand3;
        int32_t basic_type_name_id = SPVM_API_RUNTIME_get_basic_type_name_id(runtime, basic_type_id);
        const char* basic_type_name = SPVM_API_RUNTIME_get_name(runtime, basic_type_name_id);
        
        SPVM_STRING_BUFFER_add(string_buffer, "  object = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  type_dimension = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, type_dimension);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  basic_type_id = ");
        SPVM_PRECOMPILE_add_basic_type_id(precompile, string_buffer, basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  assert(basic_type_id >= 0);\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_IS_TYPE(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, 0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object, basic_type_id, type_dimension);\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_IS_ERROR:
      {
        int32_t basic_type_id = opcode->operand2;
        int32_t type_dimension = opcode->operand3;
        int32_t basic_type_name_id = SPVM_API_RUNTIME_get_basic_type_name_id(runtime, basic_type_id);
        const char* basic_type_name = SPVM_API_RUNTIME_get_name(runtime, basic_type_name_id);
        
        SPVM_STRING_BUFFER_add(string_buffer, "  src_basic_type_id = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  type_dimension = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, type_dimension);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  basic_type_id = ");
        SPVM_PRECOMPILE_add_basic_type_id(precompile, string_buffer, basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  assert(basic_type_id >= 0);\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_IS_ERROR(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, 0);
        SPVM_STRING_BUFFER_add(string_buffer, ", src_basic_type_id, basic_type_id, type_dimension);\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_CAN: {
        int32_t method_address_id = opcode->operand1;
        int32_t method_name_id = SPVM_API_RUNTIME_get_method_name_id(runtime, SPVM_API_RUNTIME_get_method_by_address_id(runtime, method_address_id));
        const char* method_name = SPVM_API_RUNTIME_get_name(runtime, method_name_id);

        SPVM_STRING_BUFFER_add(string_buffer, "  object = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  method_name = \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)method_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_CAN(env, stack, ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, 0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object, method_name);\n");

        break;
      }
      case SPVM_OPCODE_C_ID_PRINT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  string = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_IMPLEMENT_PRINT(env, stack, string);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SAY: {
        SPVM_STRING_BUFFER_add(string_buffer, "  string = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_IMPLEMENT_SAY(env, stack, string);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_WARN: {
        int32_t line = opcode->operand1;
        
        int32_t module_rel_file_id = SPVM_API_RUNTIME_get_basic_type_module_rel_file_id(runtime, current_basic_type_id);
        int32_t include_dir_id = SPVM_API_RUNTIME_get_basic_type_module_dir_id(runtime, current_basic_type_id);
        const char* module_rel_file = SPVM_API_RUNTIME_get_constant_string_value(runtime, module_rel_file_id, NULL);
        const char* include_dir = NULL;
        const char* include_dir_sep;
        if (include_dir_id >= 0) {
          include_dir_sep = "/";
          include_dir = SPVM_API_RUNTIME_get_constant_string_value(runtime, include_dir_id, NULL);
        }
        else {
          include_dir_sep = "";
          include_dir = "";
        }

        SPVM_STRING_BUFFER_add(string_buffer, "  string = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  include_dir = \"");
        SPVM_STRING_BUFFER_add(string_buffer, include_dir);
        SPVM_STRING_BUFFER_add(string_buffer, "\";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  include_dir_sep = \"");
        SPVM_STRING_BUFFER_add(string_buffer, include_dir_sep);
        SPVM_STRING_BUFFER_add(string_buffer, "\";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  module_rel_file = \"");
        SPVM_STRING_BUFFER_add(string_buffer, module_rel_file);
        SPVM_STRING_BUFFER_add(string_buffer, "\";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  line = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, line);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_IMPLEMENT_WARN(env, stack, string, include_dir, include_dir_sep, module_rel_file, line);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_CLEAR_EVAL_ERROR_ID: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_CLEAR_EVAL_ERROR_ID(eval_error_id);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_EVAL_ERROR_ID: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_EVAL_ERROR_ID(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", eval_error_id);\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_SET_ERROR_ID: {
        int32_t basic_type_id = opcode->operand0;
        int32_t basic_type_name_id = SPVM_API_RUNTIME_get_basic_type_name_id(runtime, basic_type_id);
        const char* basic_type_name = SPVM_API_RUNTIME_get_name(runtime, basic_type_name_id);

        SPVM_STRING_BUFFER_add(string_buffer, "  basic_type_name = \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  basic_type_id = ");
        SPVM_PRECOMPILE_add_basic_type_id(precompile, string_buffer, basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_ERROR_ID(error_id, basic_type_id);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_ITEMS: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_ITEMS(env, stack, ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_BASIC_TYPE_ID: {
        int32_t basic_type_id = opcode->operand1;
        int32_t basic_type_name_id = SPVM_API_RUNTIME_get_basic_type_name_id(runtime, basic_type_id);
        const char* basic_type_name = SPVM_API_RUNTIME_get_name(runtime, basic_type_name_id);
        
        SPVM_STRING_BUFFER_add(string_buffer, "  basic_type_name = \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  basic_type_id = ");
        SPVM_PRECOMPILE_add_basic_type_id(precompile, string_buffer, basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  assert(basic_type_id >= 0);\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_BASIC_TYPE_ID(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", basic_type_id);\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_NAME: {
        
        SPVM_STRING_BUFFER_add(string_buffer, "  object = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_TYPE_NAME(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " , object);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_DUMP: {
        SPVM_STRING_BUFFER_add(string_buffer, "  object = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_DUMP(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_COPY: {
        SPVM_STRING_BUFFER_add(string_buffer, "  object = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_COPY(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object, &error_id);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_REF_BYTE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_REF_BYTE(*(void**)");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_REF, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_REF_SHORT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_REF_SHORT(*(void**)");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_REF, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_REF_INT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_REF_INT(*(void**)");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_REF, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_REF_LONG: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_REF_LONG(*(void**)");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_REF, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_REF_FLOAT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_REF_FLOAT(*(void**)");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_REF, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_REF_DOUBLE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_REF_DOUBLE(*(void**)");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_REF, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_DEREF_BYTE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_DEREF_BYTE(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_REF, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_DEREF_SHORT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_DEREF_SHORT(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_REF, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_DEREF_INT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_DEREF_INT(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_REF, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_DEREF_LONG: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_DEREF_LONG(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_REF, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_DEREF_FLOAT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_DEREF_FLOAT(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_REF, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_DEREF_DOUBLE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_DEREF_DOUBLE(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_REF, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_DEREF_BYTE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_DEREF_BYTE(");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_REF, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_DEREF_SHORT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_DEREF_SHORT(");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_REF, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_DEREF_INT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_DEREF_INT(");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_REF, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_DEREF_LONG: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_DEREF_LONG(");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_REF, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_DEREF_FLOAT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_DEREF_FLOAT(");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_REF, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_DEREF_DOUBLE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_DEREF_DOUBLE(");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_REF, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_BYTE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  field_index = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_MULNUM_FIELD_BYTE(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", field_index);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_SHORT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  field_index = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_MULNUM_FIELD_SHORT(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", field_index);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_INT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  field_index = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_MULNUM_FIELD_INT(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", field_index);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_LONG: {
        SPVM_STRING_BUFFER_add(string_buffer, "  field_index = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_MULNUM_FIELD_LONG(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", field_index);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_FLOAT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  field_index = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_MULNUM_FIELD_FLOAT(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", field_index);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_DOUBLE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  field_index = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_MULNUM_FIELD_DOUBLE(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", field_index);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_BYTE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  field_index = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_MULNUM_FIELD_BYTE(");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", field_index, ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_SHORT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  field_index = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_MULNUM_FIELD_SHORT(");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", field_index, ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_INT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  field_index = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_MULNUM_FIELD_INT(");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", field_index, ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_LONG: {
        SPVM_STRING_BUFFER_add(string_buffer, "  field_index = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_MULNUM_FIELD_LONG(");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", field_index, ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_FLOAT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  field_index = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_MULNUM_FIELD_FLOAT(");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", field_index, ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_DOUBLE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  field_index = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_MULNUM_FIELD_DOUBLE(");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", field_index, ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_MULNUM_BYTE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  fields_length = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_MOVE_MULNUM_BYTE(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", fields_length);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_MULNUM_SHORT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  fields_length = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_MOVE_MULNUM_SHORT(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", fields_length);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_MULNUM_INT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  fields_length = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_MOVE_MULNUM_INT(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", fields_length);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_MULNUM_LONG: {
        SPVM_STRING_BUFFER_add(string_buffer, "  fields_length = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_MOVE_MULNUM_LONG(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", fields_length);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_MULNUM_FLOAT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  fields_length = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_MOVE_MULNUM_FLOAT(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", fields_length);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_MULNUM_DOUBLE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  fields_length = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_MOVE_MULNUM_DOUBLE(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", fields_length);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_BYTE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  array = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  index = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  fields_length = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_MULNUM_ARRAY_BYTE(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", array, index, fields_length, &error_id, object_header_size);\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_SHORT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  array = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  index = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  fields_length = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_MULNUM_ARRAY_SHORT(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", array, index, fields_length, &error_id, object_header_size);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_INT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  array = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  index = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  fields_length = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_MULNUM_ARRAY_INT(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", array, index, fields_length, &error_id, object_header_size);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_LONG: {
        SPVM_STRING_BUFFER_add(string_buffer, "  array = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  index = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  fields_length = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_MULNUM_ARRAY_LONG(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", array, index, fields_length, &error_id, object_header_size);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_FLOAT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  array = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  index = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  fields_length = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_MULNUM_ARRAY_FLOAT(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", array, index, fields_length, &error_id, object_header_size);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_DOUBLE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  array = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  index = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  fields_length = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_MULNUM_ARRAY_DOUBLE(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", array, index, fields_length, &error_id, object_header_size);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_BYTE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  array = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  index = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  fields_length = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_MULNUM_ARRAY_BYTE(env, stack, array, index, fields_length, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ", &error_id, object_header_size);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_SHORT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  array = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  index = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  fields_length = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_MULNUM_ARRAY_SHORT(env, stack, array, index, fields_length, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ", &error_id, object_header_size);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_INT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  array = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  index = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  fields_length = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_MULNUM_ARRAY_INT(env, stack, array, index, fields_length, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ", &error_id, object_header_size);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_LONG: {
        SPVM_STRING_BUFFER_add(string_buffer, "  array = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  index = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  fields_length = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_MULNUM_ARRAY_LONG(env, stack, array, index, fields_length, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ", &error_id, object_header_size);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_FLOAT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  array = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  index = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  fields_length = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_MULNUM_ARRAY_FLOAT(env, stack, array, index, fields_length, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ", &error_id, object_header_size);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_DOUBLE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  array = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  index = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  fields_length = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_MULNUM_ARRAY_DOUBLE(env, stack, array, index, fields_length, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ", &error_id, object_header_size);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_FIELD_BYTE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  array = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  index = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  fields_length = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, (opcode->operand3 & 0xFF) + 1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  field_index = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3 >> 8);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_MULNUM_ARRAY_FIELD_BYTE(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", array, index, field_index, fields_length, &error_id, object_header_size);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_FIELD_SHORT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  array = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  index = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  fields_length = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, (opcode->operand3 & 0xFF) + 1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  field_index = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3 >> 8);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_MULNUM_ARRAY_FIELD_SHORT(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", array, index, field_index, fields_length, &error_id, object_header_size);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_FIELD_INT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  array = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  index = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  fields_length = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, (opcode->operand3 & 0xFF) + 1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  field_index = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3 >> 8);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_MULNUM_ARRAY_FIELD_INT(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", array, index, field_index, fields_length, &error_id, object_header_size);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_FIELD_LONG: {
        SPVM_STRING_BUFFER_add(string_buffer, "  array = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  index = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  fields_length = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, (opcode->operand3 & 0xFF) + 1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  field_index = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3 >> 8);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_MULNUM_ARRAY_FIELD_LONG(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", array, index, field_index, fields_length, &error_id, object_header_size);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_FIELD_FLOAT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  array = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  index = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  fields_length = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, (opcode->operand3 & 0xFF) + 1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  field_index = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3 >> 8);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_MULNUM_ARRAY_FIELD_FLOAT(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", array, index, field_index, fields_length, &error_id, object_header_size);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_FIELD_DOUBLE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  array = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  index = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  fields_length = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, (opcode->operand3 & 0xFF) + 1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  field_index = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3 >> 8);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_MULNUM_ARRAY_FIELD_DOUBLE(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", array, index, field_index, fields_length, &error_id, object_header_size);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_FIELD_BYTE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  array = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  index = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  fields_length = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, (opcode->operand3 & 0xFF) + 1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  field_index = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3 >> 8);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_MULNUM_ARRAY_FIELD_BYTE(env, stack, array, index, field_index, fields_length, ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ", &error_id, object_header_size);");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_FIELD_SHORT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  array = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  index = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  fields_length = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, (opcode->operand3 & 0xFF) + 1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  field_index = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3 >> 8);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_MULNUM_ARRAY_FIELD_SHORT(env, stack, array, index, field_index, fields_length, ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ", &error_id, object_header_size);");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_FIELD_INT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  array = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  index = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  fields_length = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, (opcode->operand3 & 0xFF) + 1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  field_index = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3 >> 8);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_MULNUM_ARRAY_FIELD_INT(env, stack, array, index, field_index, fields_length, ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ", &error_id, object_header_size);");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_FIELD_LONG: {
        SPVM_STRING_BUFFER_add(string_buffer, "  array = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  index = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  fields_length = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, (opcode->operand3 & 0xFF) + 1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  field_index = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3 >> 8);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_MULNUM_ARRAY_FIELD_LONG(env, stack, array, index, field_index, fields_length, ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ", &error_id, object_header_size);");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_FIELD_FLOAT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  array = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  index = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  fields_length = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, (opcode->operand3 & 0xFF) + 1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  field_index = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3 >> 8);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_MULNUM_ARRAY_FIELD_FLOAT(env, stack, array, index, field_index, fields_length, ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ", &error_id, object_header_size);");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_FIELD_DOUBLE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  array = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  index = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  fields_length = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, (opcode->operand3 & 0xFF) + 1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  field_index = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3 >> 8);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_MULNUM_ARRAY_FIELD_DOUBLE(env, stack, array, index, field_index, fields_length, ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ", &error_id, object_header_size);");
        break;
      }
      case SPVM_OPCODE_C_ID_DEREF_MULNUM_BYTE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  fields_length = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_DEREF_MULNUM_BYTE(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_REF, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", fields_length);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_DEREF_MULNUM_SHORT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  fields_length = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_DEREF_MULNUM_SHORT(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_REF, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", fields_length);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_DEREF_MULNUM_INT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  fields_length = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_DEREF_MULNUM_INT(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_REF, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", fields_length);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_DEREF_MULNUM_LONG: {
        SPVM_STRING_BUFFER_add(string_buffer, "  fields_length = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_DEREF_MULNUM_LONG(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_REF, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", fields_length);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_DEREF_MULNUM_FLOAT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  fields_length = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_DEREF_MULNUM_FLOAT(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_REF, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", fields_length);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_DEREF_MULNUM_DOUBLE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  fields_length = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_DEREF_MULNUM_DOUBLE(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_REF, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", fields_length);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_DEREF_BYTE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  field_index = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_MULNUM_FIELD_DEREF_BYTE(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_REF, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", field_index);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_DEREF_SHORT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  field_index = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_MULNUM_FIELD_DEREF_SHORT(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_REF, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", field_index);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_DEREF_INT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  field_index = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_MULNUM_FIELD_DEREF_INT(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_REF, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", field_index);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_DEREF_LONG: {
        SPVM_STRING_BUFFER_add(string_buffer, "  field_index = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_MULNUM_FIELD_DEREF_LONG(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_REF, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", field_index);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_DEREF_FLOAT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  field_index = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_MULNUM_FIELD_DEREF_FLOAT(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_REF, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", field_index);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_DEREF_DOUBLE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  field_index = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_MULNUM_FIELD_DEREF_DOUBLE(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_REF, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", field_index);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_DEREF_BYTE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  field_index = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_MULNUM_FIELD_DEREF_BYTE(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_REF, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", field_index, ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_DEREF_SHORT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  field_index = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_MULNUM_FIELD_DEREF_SHORT(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_REF, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", field_index, ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_DEREF_INT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  field_index = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_MULNUM_FIELD_DEREF_INT(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_REF, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", field_index, ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_DEREF_LONG: {
        SPVM_STRING_BUFFER_add(string_buffer, "  field_index = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_MULNUM_FIELD_DEREF_LONG(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_REF, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", field_index, ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_DEREF_FLOAT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  field_index = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_MULNUM_FIELD_DEREF_FLOAT(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_REF, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", field_index, ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_DEREF_DOUBLE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  field_index = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_MULNUM_FIELD_DEREF_DOUBLE(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_REF, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", field_index, ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_WEAKEN_FIELD: {
        int32_t field_address_id = opcode->operand1;
        
        SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field_by_address_id(runtime, field_address_id);
        int32_t field_current_basic_type_id = SPVM_API_RUNTIME_get_field_current_basic_type_id(runtime, field);
        int32_t basic_type_name_id = SPVM_API_RUNTIME_get_basic_type_name_id(runtime, field_current_basic_type_id);
        const char* basic_type_name = SPVM_API_RUNTIME_get_name(runtime, basic_type_name_id);
        int32_t field_name_id = SPVM_API_RUNTIME_get_field_name_id(runtime, field);
        const char* field_name = SPVM_API_RUNTIME_get_name(runtime, field_name_id);
        
        SPVM_STRING_BUFFER_add(string_buffer, "  object = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  basic_type_name = \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  field_name = \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  field_address_id = ");
        SPVM_PRECOMPILE_add_field_address_id(precompile, string_buffer, basic_type_name, field_name);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  assert(field_address_id >= 0);\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_WEAKEN_FIELD(env, stack, object, field_address_id, &error_id, object_header_size);\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_UNWEAKEN_FIELD: {
        int32_t field_address_id = opcode->operand1;
        
        SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field_by_address_id(runtime, field_address_id);
        int32_t field_current_basic_type_id = SPVM_API_RUNTIME_get_field_current_basic_type_id(runtime, field);
        int32_t basic_type_name_id = SPVM_API_RUNTIME_get_basic_type_name_id(runtime, field_current_basic_type_id);
        const char* basic_type_name = SPVM_API_RUNTIME_get_name(runtime, basic_type_name_id);
        int32_t field_name_id = SPVM_API_RUNTIME_get_field_name_id(runtime, field);
        const char* field_name = SPVM_API_RUNTIME_get_name(runtime, field_name_id);
        
        SPVM_STRING_BUFFER_add(string_buffer, "  object = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  basic_type_name = \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  field_name = \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  field_address_id = ");
        SPVM_PRECOMPILE_add_field_address_id(precompile, string_buffer, basic_type_name, field_name);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  assert(field_address_id >= 0);\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_UNWEAKEN_FIELD(env, stack, object, field_address_id, &error_id, object_header_size);\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_ISWEAK_FIELD: {
        int32_t field_address_id = opcode->operand2;
        
        SPVM_RUNTIME_FIELD* field = SPVM_API_RUNTIME_get_field_by_address_id(runtime, field_address_id);
        int32_t field_current_basic_type_id = SPVM_API_RUNTIME_get_field_current_basic_type_id(runtime, field);
        int32_t basic_type_name_id = SPVM_API_RUNTIME_get_basic_type_name_id(runtime, field_current_basic_type_id);
        const char* basic_type_name = SPVM_API_RUNTIME_get_name(runtime, basic_type_name_id);
        int32_t field_name_id = SPVM_API_RUNTIME_get_field_name_id(runtime, field);
        const char* field_name = SPVM_API_RUNTIME_get_name(runtime, field_name_id);

        SPVM_STRING_BUFFER_add(string_buffer, "  object = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  basic_type_name = \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  field_name = \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  field_address_id = ");
        SPVM_PRECOMPILE_add_field_address_id(precompile, string_buffer, basic_type_name, field_name);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  assert(field_address_id >= 0);\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_ISWEAK_FIELD(env, stack, &int_vars[0], object, field_address_id, &error_id, object_header_size);\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_BYTE_TO_SHORT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_TYPE_CONVERSION_BYTE_TO_SHORT(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_BYTE_TO_INT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_TYPE_CONVERSION_BYTE_TO_INT(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_BYTE_TO_LONG: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_TYPE_CONVERSION_BYTE_TO_LONG(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_BYTE_TO_FLOAT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_TYPE_CONVERSION_BYTE_TO_FLOAT(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_BYTE_TO_DOUBLE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_TYPE_CONVERSION_BYTE_TO_DOUBLE(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_SHORT_TO_BYTE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_TYPE_CONVERSION_SHORT_TO_BYTE(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_SHORT_TO_INT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_TYPE_CONVERSION_SHORT_TO_INT(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_SHORT_TO_LONG: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_TYPE_CONVERSION_SHORT_TO_LONG(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_SHORT_TO_FLOAT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_TYPE_CONVERSION_SHORT_TO_FLOAT(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_SHORT_TO_DOUBLE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_TYPE_CONVERSION_SHORT_TO_DOUBLE(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_INT_TO_BYTE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_TYPE_CONVERSION_INT_TO_BYTE(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_INT_TO_SHORT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_TYPE_CONVERSION_INT_TO_SHORT(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_INT_TO_LONG: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_TYPE_CONVERSION_INT_TO_LONG(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_INT_TO_FLOAT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_TYPE_CONVERSION_INT_TO_FLOAT(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_INT_TO_DOUBLE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_TYPE_CONVERSION_INT_TO_DOUBLE(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_LONG_TO_BYTE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_TYPE_CONVERSION_LONG_TO_BYTE(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_LONG_TO_SHORT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_TYPE_CONVERSION_LONG_TO_SHORT(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_LONG_TO_INT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_TYPE_CONVERSION_LONG_TO_INT(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_LONG_TO_FLOAT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_TYPE_CONVERSION_LONG_TO_FLOAT(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_LONG_TO_DOUBLE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_TYPE_CONVERSION_LONG_TO_DOUBLE(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_FLOAT_TO_BYTE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_TYPE_CONVERSION_FLOAT_TO_BYTE(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_FLOAT_TO_SHORT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_TYPE_CONVERSION_FLOAT_TO_SHORT(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_FLOAT_TO_INT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_TYPE_CONVERSION_FLOAT_TO_INT(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_FLOAT_TO_LONG: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_TYPE_CONVERSION_FLOAT_TO_LONG(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_FLOAT_TO_DOUBLE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_TYPE_CONVERSION_FLOAT_TO_DOUBLE(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_DOUBLE_TO_BYTE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_TYPE_CONVERSION_DOUBLE_TO_BYTE(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_DOUBLE_TO_SHORT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_TYPE_CONVERSION_DOUBLE_TO_SHORT(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_DOUBLE_TO_INT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_TYPE_CONVERSION_DOUBLE_TO_INT(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_DOUBLE_TO_LONG: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_TYPE_CONVERSION_DOUBLE_TO_LONG(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_DOUBLE_TO_FLOAT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_TYPE_CONVERSION_DOUBLE_TO_FLOAT(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_BYTE_TO_STRING: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_TYPE_CONVERSION_BYTE_TO_STRING(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", tmp_buffer, sizeof(tmp_buffer));\n");
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_SHORT_TO_STRING: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_TYPE_CONVERSION_SHORT_TO_STRING(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", tmp_buffer, sizeof(tmp_buffer));\n");
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_INT_TO_STRING: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_TYPE_CONVERSION_INT_TO_STRING(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", tmp_buffer, sizeof(tmp_buffer));\n");
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_LONG_TO_STRING: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_TYPE_CONVERSION_LONG_TO_STRING(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", tmp_buffer, sizeof(tmp_buffer));\n");
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_FLOAT_TO_STRING: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_TYPE_CONVERSION_FLOAT_TO_STRING(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", tmp_buffer, sizeof(tmp_buffer));\n");
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_DOUBLE_TO_STRING: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_TYPE_CONVERSION_DOUBLE_TO_STRING(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ", tmp_buffer, sizeof(tmp_buffer));\n");
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_STRING_TO_BYTE_ARRAY: {
        SPVM_STRING_BUFFER_add(string_buffer, "  src_string = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_TYPE_CONVERSION_STRING_TO_BYTE_ARRAY(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, "  , src_string);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_BYTE_ARRAY_TO_STRING: {
        SPVM_STRING_BUFFER_add(string_buffer, "  src_byte_array = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_TYPE_CONVERSION_BYTE_ARRAY_TO_STRING(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, "  , src_byte_array);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_BYTE_TO_BYTE_OBJECT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  value_byte = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_TYPE_CONVERSION_BYTE_TO_BYTE_OBJECT(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", value_byte, object_header_size);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_SHORT_TO_SHORT_OBJECT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  value_short = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_TYPE_CONVERSION_SHORT_TO_SHORT_OBJECT(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", value_short, object_header_size);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_INT_TO_INT_OBJECT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  value_int = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_TYPE_CONVERSION_INT_TO_INT_OBJECT(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", value_int, object_header_size);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_LONG_TO_LONG_OBJECT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  value_long = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_TYPE_CONVERSION_LONG_TO_LONG_OBJECT(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", value_long, object_header_size);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_FLOAT_TO_FLOAT_OBJECT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  value_float = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_TYPE_CONVERSION_FLOAT_TO_FLOAT_OBJECT(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", value_float, object_header_size);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_DOUBLE_TO_DOUBLE_OBJECT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  value_double = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_TYPE_CONVERSION_DOUBLE_TO_DOUBLE_OBJECT(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", value_double, object_header_size);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_BYTE_OBJECT_TO_BYTE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  object = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_TYPE_CONVERSION_BYTE_OBJECT_TO_BYTE(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object, &error_id, object_header_size);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_SHORT_OBJECT_TO_SHORT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  object = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_TYPE_CONVERSION_SHORT_OBJECT_TO_SHORT(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object, &error_id, object_header_size);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_INT_OBJECT_TO_INT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  object = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_TYPE_CONVERSION_INT_OBJECT_TO_INT(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object, &error_id, object_header_size);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_LONG_OBJECT_TO_LONG: {
        SPVM_STRING_BUFFER_add(string_buffer, "  object = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_TYPE_CONVERSION_LONG_OBJECT_TO_LONG(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object, &error_id, object_header_size);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_FLOAT_OBJECT_TO_FLOAT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  object = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_TYPE_CONVERSION_FLOAT_OBJECT_TO_FLOAT(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object, &error_id, object_header_size);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_TYPE_CONVERSION_DOUBLE_OBJECT_TO_DOUBLE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  object = ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_TYPE_CONVERSION_DOUBLE_OBJECT_TO_DOUBLE(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object, &error_id, object_header_size);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_STACK_BYTE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_STACK_BYTE(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", stack, ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3 & 0xFF);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_STACK_SHORT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_STACK_SHORT(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", stack, ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3 & 0xFF);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_STACK_INT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_STACK_INT(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", stack, ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3 & 0xFF);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_STACK_LONG: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_STACK_LONG(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", stack, ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3 & 0xFF);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_STACK_FLOAT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_STACK_FLOAT(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", stack, ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3 & 0xFF);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_STACK_DOUBLE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_STACK_DOUBLE(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", stack, ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3 & 0xFF);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_STACK_OBJECT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_STACK_OBJECT(env, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", stack, ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3 & 0xFF);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_STACK_REF: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_STACK_REF(");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_REF, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", stack, ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3 & 0xFF);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_STACK_MULNUM_BYTE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  type_stack_length = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3 >> 8);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_STACK_MULNUM_BYTE(env, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, "  , stack, ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3 & 0xFF);
        SPVM_STRING_BUFFER_add(string_buffer, ", type_stack_length);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_STACK_MULNUM_SHORT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  type_stack_length = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3 >> 8);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_STACK_MULNUM_SHORT(env, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, "  , stack, ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3 & 0xFF);
        SPVM_STRING_BUFFER_add(string_buffer, ", type_stack_length);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_STACK_MULNUM_INT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  type_stack_length = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3 >> 8);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_STACK_MULNUM_INT(env, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, "  , stack, ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3 & 0xFF);
        SPVM_STRING_BUFFER_add(string_buffer, ", type_stack_length);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_STACK_MULNUM_LONG: {
        SPVM_STRING_BUFFER_add(string_buffer, "  type_stack_length = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3 >> 8);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_STACK_MULNUM_LONG(env, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, "  , stack, ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3 & 0xFF);
        SPVM_STRING_BUFFER_add(string_buffer, ", type_stack_length);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_STACK_MULNUM_FLOAT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  type_stack_length = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3 >> 8);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_STACK_MULNUM_FLOAT(env, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, "  , stack, ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3 & 0xFF);
        SPVM_STRING_BUFFER_add(string_buffer, ", type_stack_length);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_STACK_MULNUM_DOUBLE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  type_stack_length = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3 >> 8);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_STACK_MULNUM_DOUBLE(env, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, "  , stack, ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3 & 0xFF);
        SPVM_STRING_BUFFER_add(string_buffer, ", type_stack_length);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_STACK_OPTIONAL_BYTE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  stack_index = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3 & 0xFF);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_STACK_OPTIONAL_BYTE(env, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", stack, stack_index, ");
        SPVM_STRING_BUFFER_add_int(string_buffer, (int8_t)(uint8_t)opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_STACK_OPTIONAL_SHORT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  stack_index = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3 & 0xFF);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_STACK_OPTIONAL_SHORT(env, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", stack, stack_index, ");
        SPVM_STRING_BUFFER_add_int(string_buffer, (int16_t)(uint16_t)opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_STACK_OPTIONAL_INT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  stack_index = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3 & 0xFF);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_STACK_OPTIONAL_INT(env, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", stack, stack_index, ");
        SPVM_STRING_BUFFER_add_int(string_buffer, (int32_t)opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_STACK_OPTIONAL_LONG: {
        SPVM_STRING_BUFFER_add(string_buffer, "  stack_index = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3 & 0xFF);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_STACK_OPTIONAL_LONG(env, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", stack, stack_index, ");
        SPVM_STRING_BUFFER_add_long(string_buffer, *(int64_t*)&opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_STACK_OPTIONAL_FLOAT: {
        SPVM_VALUE value;
        value.ival = (int32_t)opcode->operand1;

        SPVM_STRING_BUFFER_add(string_buffer, "  stack_index = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3 & 0xFF);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_STACK_OPTIONAL_FLOAT(env, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", stack, stack_index, (tmp_constant.ival = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, value.ival);
        SPVM_STRING_BUFFER_add(string_buffer, ", tmp_constant.fval));\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_STACK_OPTIONAL_DOUBLE: {
        double double_value = *(double*)&opcode->operand1;
        SPVM_VALUE value;
        value.dval = double_value;

        SPVM_STRING_BUFFER_add(string_buffer, "  stack_index = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3 & 0xFF);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_STACK_OPTIONAL_DOUBLE(env, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", stack, stack_index, (tmp_constant.lval = ");
       SPVM_STRING_BUFFER_add_long(string_buffer, value.lval);
        SPVM_STRING_BUFFER_add(string_buffer, ", tmp_constant.dval));\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_STACK_OPTIONAL_OBJECT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  stack_index = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3 & 0xFF);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_GET_STACK_OPTIONAL_OBJECT(env, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", stack, stack_index);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_END_ARGS: {
        // Do nothing
        break;
      }
      case SPVM_OPCODE_C_ID_SET_STACK_BYTE:
      {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_STACK_BYTE(stack, ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_STACK_SHORT:
      {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_STACK_SHORT(stack, ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_STACK_INT:
      {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_STACK_INT(stack, ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_STACK_LONG:
      {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_STACK_LONG(stack, ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_STACK_FLOAT:
      {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_STACK_FLOAT(stack, ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_STACK_DOUBLE:
      {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_STACK_DOUBLE(stack, ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_STACK_OBJECT:
      {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_STACK_OBJECT(stack, ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_STACK_REF:
      {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_STACK_REF(stack, ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_REF, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_STACK_UNDEF:
      {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_STACK_UNDEF(stack, ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_STACK_MULNUM_BYTE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  fields_length = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_STACK_MULNUM_BYTE(env, stack, ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3);
        SPVM_STRING_BUFFER_add(string_buffer, ", fields_length, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_STACK_MULNUM_SHORT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  fields_length = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_STACK_MULNUM_SHORT(env, stack, ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3);
        SPVM_STRING_BUFFER_add(string_buffer, ", fields_length, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_STACK_MULNUM_INT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  fields_length = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_STACK_MULNUM_INT(env, stack, ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3);
        SPVM_STRING_BUFFER_add(string_buffer, ", fields_length, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_STACK_MULNUM_LONG: {
        SPVM_STRING_BUFFER_add(string_buffer, "  fields_length = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_STACK_MULNUM_LONG(env, stack, ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3);
        SPVM_STRING_BUFFER_add(string_buffer, ", fields_length, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_STACK_MULNUM_FLOAT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  fields_length = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_STACK_MULNUM_FLOAT(env, stack, ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3);
        SPVM_STRING_BUFFER_add(string_buffer, ", fields_length, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_STACK_MULNUM_DOUBLE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  fields_length = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_SET_STACK_MULNUM_DOUBLE(env, stack, ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3);
        SPVM_STRING_BUFFER_add(string_buffer, ", fields_length, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_RETURN_VOID:
      {
        SPVM_STRING_BUFFER_add(string_buffer, "  goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_RETURN_BYTE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_RETURN_BYTE(stack, ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_RETURN_SHORT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_RETURN_SHORT(stack, ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_RETURN_INT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_RETURN_INT(stack, ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_RETURN_LONG: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_RETURN_LONG(stack, ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_RETURN_FLOAT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_RETURN_FLOAT(stack, ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_RETURN_DOUBLE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_RETURN_DOUBLE(stack, ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_RETURN_OBJECT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_RETURN_OBJECT(env, stack, ");
        SPVM_PRECOMPILE_add_operand(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_RETURN_UNDEF: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_RETURN_UNDEF(stack);\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_RETURN_MULNUM_BYTE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  fields_length = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_RETURN_MULNUM_BYTE(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", fields_length);\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_RETURN_MULNUM_SHORT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  fields_length = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_RETURN_MULNUM_SHORT(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", fields_length);\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_RETURN_MULNUM_INT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  fields_length = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_RETURN_MULNUM_INT(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", fields_length);\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_RETURN_MULNUM_LONG: {
        SPVM_STRING_BUFFER_add(string_buffer, "  fields_length = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_RETURN_MULNUM_LONG(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", fields_length);\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_RETURN_MULNUM_FLOAT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  fields_length = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_RETURN_MULNUM_FLOAT(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", fields_length);\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_RETURN_MULNUM_DOUBLE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  fields_length = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_RETURN_MULNUM_DOUBLE(env, stack, ");
        SPVM_PRECOMPILE_add_operand_address(precompile, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", fields_length);\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_CLASS_METHOD: {
        int32_t method_address_id = opcode->operand0;
        int32_t args_stack_length = opcode->operand1;
        
        int32_t method_name_id = SPVM_API_RUNTIME_get_method_name_id(runtime, SPVM_API_RUNTIME_get_method_by_address_id(runtime, method_address_id));
        const char* method_name = SPVM_API_RUNTIME_get_name(runtime, method_name_id);
        int32_t method_current_basic_type_id = SPVM_API_RUNTIME_get_method_current_basic_type_id(runtime, SPVM_API_RUNTIME_get_method_by_address_id(runtime, method_address_id));
        int32_t basic_type_name_id = SPVM_API_RUNTIME_get_basic_type_name_id(runtime, method_current_basic_type_id);
        const char* basic_type_name = SPVM_API_RUNTIME_get_name(runtime, basic_type_name_id);
        
        SPVM_STRING_BUFFER_add(string_buffer, "  basic_type_name = \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  method_name = \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)method_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  args_stack_length = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, args_stack_length);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  method_address_id = ");
        SPVM_PRECOMPILE_add_method_address_id(precompile, string_buffer, basic_type_name, method_name);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  assert(method_address_id >= 0);\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_CALL_CLASS_METHOD(env, stack, error_id, method_address_id, args_stack_length);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_INSTANCE_METHOD_STATIC: {
        int32_t method_address_id = opcode->operand0;
        int32_t args_stack_length = opcode->operand1;
        
        int32_t method_name_id = SPVM_API_RUNTIME_get_method_name_id(runtime, SPVM_API_RUNTIME_get_method_by_address_id(runtime, method_address_id));
        const char* method_name = SPVM_API_RUNTIME_get_name(runtime, method_name_id);
        int32_t method_current_basic_type_id = SPVM_API_RUNTIME_get_method_current_basic_type_id(runtime, SPVM_API_RUNTIME_get_method_by_address_id(runtime, method_address_id));
        int32_t basic_type_name_id = SPVM_API_RUNTIME_get_basic_type_name_id(runtime, method_current_basic_type_id);
        const char* basic_type_name = SPVM_API_RUNTIME_get_name(runtime, basic_type_name_id);
        
        SPVM_STRING_BUFFER_add(string_buffer, "  basic_type_name = \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  method_name = \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)method_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  args_stack_length = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, args_stack_length);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  method_address_id = ");
        SPVM_PRECOMPILE_add_method_address_id(precompile, string_buffer, basic_type_name, method_name);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  assert(method_address_id >= 0);\n");
        
        SPVM_STRING_BUFFER_add(string_buffer,
                                              "  SPVM_IMPLEMENT_CALL_INSTANCE_METHOD_STATIC(env, stack, error_id, method_address_id, args_stack_length);\n");
    
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_INSTANCE_METHOD: {
        int32_t method_address_id = opcode->operand0;
        int32_t args_stack_length = opcode->operand1;
        
        int32_t method_name_id = SPVM_API_RUNTIME_get_method_name_id(runtime, SPVM_API_RUNTIME_get_method_by_address_id(runtime, method_address_id));
        const char* method_name = SPVM_API_RUNTIME_get_name(runtime, method_name_id);
        int32_t method_current_basic_type_id = SPVM_API_RUNTIME_get_method_current_basic_type_id(runtime, SPVM_API_RUNTIME_get_method_by_address_id(runtime, method_address_id));
        int32_t basic_type_name_id = SPVM_API_RUNTIME_get_basic_type_name_id(runtime, method_current_basic_type_id);
        const char* basic_type_name = SPVM_API_RUNTIME_get_name(runtime, basic_type_name_id);

        SPVM_STRING_BUFFER_add(string_buffer, "  basic_type_name = \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\";\n");

        SPVM_STRING_BUFFER_add(string_buffer, "  method_name = \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)method_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\";\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  args_stack_length = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, args_stack_length);
        SPVM_STRING_BUFFER_add(string_buffer,
                                              ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  object = stack[0].oval;\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_IMPLEMENT_CALL_INSTANCE_METHOD(env, stack, object, basic_type_name, method_name, args_stack_length, &error_id, tmp_buffer, sizeof(tmp_buffer));\n");
        
        break;
      }
      default: {
        spvm_warn("[Unexpected Error]The \"%s\" opcode is not defined", SPVM_OPCODE_get_opcode_name(opcode_id));
        assert(0);
      }
    }
    opcode_index++;
  }
  
  // No exception
  SPVM_STRING_BUFFER_add(string_buffer, "  END_OF_METHOD:\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  if (error_id == 0) {\n");
  int32_t current_method_return_basic_type_id = SPVM_API_RUNTIME_get_method_return_basic_type_id(runtime, SPVM_API_RUNTIME_get_method_by_address_id(runtime, current_method_address_id));
  int32_t current_method_return_type_dimension = SPVM_API_RUNTIME_get_method_return_type_dimension(runtime, SPVM_API_RUNTIME_get_method_by_address_id(runtime, current_method_address_id));
  int32_t current_method_return_type_flag = SPVM_API_RUNTIME_get_method_return_type_flag(runtime, SPVM_API_RUNTIME_get_method_by_address_id(runtime, current_method_address_id));
  int32_t method_return_type_check_runtime_assignability_to_any_object = SPVM_API_RUNTIME_is_object_type(runtime, current_method_return_basic_type_id, current_method_return_type_dimension, current_method_return_type_flag);
  if (method_return_type_check_runtime_assignability_to_any_object) {
    SPVM_STRING_BUFFER_add(string_buffer, "  if (stack[0].oval != NULL) { SPVM_IMPLEMENT_DEC_REF_COUNT_ONLY(env, stack, stack[0].oval); }\n");
  }
  SPVM_STRING_BUFFER_add(string_buffer, "  }\n"
  "  return error_id;\n"
                                        "}\n"
                                        "\n");
}

const char* SPVM_PRECOMPILE_get_ctype_name(SPVM_PRECOMPILE* precompile, int32_t ctype_id) {
  SPVM_RUNTIME* runtime = precompile->runtime;

  
  switch (ctype_id) {
    case SPVM_PRECOMPILE_C_CTYPE_ID_BYTE:
      return "int8_t";
      break;
    case SPVM_PRECOMPILE_C_CTYPE_ID_SHORT:
      return "int16_t";
      break;
    case SPVM_PRECOMPILE_C_CTYPE_ID_INT:
      return "int32_t";
      break;
    case SPVM_PRECOMPILE_C_CTYPE_ID_LONG:
      return "int64_t";
      break;
    case SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT:
      return "float";
      break;
    case SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE:
      return "double";
      break;
    case SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT:
      return "void*";
      break;
    case SPVM_PRECOMPILE_C_CTYPE_ID_REF:
      return "void*";
      break;
  }
  
  return NULL;
}

void SPVM_PRECOMPILE_add_operand(SPVM_PRECOMPILE* precompile, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t index) {
  SPVM_RUNTIME* runtime = precompile->runtime;
  
  switch (ctype_id) {
    case SPVM_PRECOMPILE_C_CTYPE_ID_BYTE: {
      SPVM_STRING_BUFFER_add(string_buffer, "byte_vars[");
      SPVM_STRING_BUFFER_add_int(string_buffer, index);
      SPVM_STRING_BUFFER_add(string_buffer, "]");
      break;
    }
    case SPVM_PRECOMPILE_C_CTYPE_ID_SHORT: {
      SPVM_STRING_BUFFER_add(string_buffer, "short_vars[");
      SPVM_STRING_BUFFER_add_int(string_buffer, index);
      SPVM_STRING_BUFFER_add(string_buffer, "]");
      break;
    }
    case SPVM_PRECOMPILE_C_CTYPE_ID_INT: {
      SPVM_STRING_BUFFER_add(string_buffer, "int_vars[");
      SPVM_STRING_BUFFER_add_int(string_buffer, index);
      SPVM_STRING_BUFFER_add(string_buffer, "]");
      break;
    }
    case SPVM_PRECOMPILE_C_CTYPE_ID_LONG: {
      SPVM_STRING_BUFFER_add(string_buffer, "long_vars[");
      SPVM_STRING_BUFFER_add_int(string_buffer, index);
      SPVM_STRING_BUFFER_add(string_buffer, "]");
      break;
    }
    case SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT: {
      SPVM_STRING_BUFFER_add(string_buffer, "float_vars[");
      SPVM_STRING_BUFFER_add_int(string_buffer, index);
      SPVM_STRING_BUFFER_add(string_buffer, "]");
      break;
    }
    case SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE: {
      SPVM_STRING_BUFFER_add(string_buffer, "double_vars[");
      SPVM_STRING_BUFFER_add_int(string_buffer, index);
      SPVM_STRING_BUFFER_add(string_buffer, "]");
      break;
    }
    case SPVM_PRECOMPILE_C_CTYPE_ID_BOOL_CONVERSION_OBJECT:
    case SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT:
    {
      SPVM_STRING_BUFFER_add(string_buffer, "object_vars[");
      SPVM_STRING_BUFFER_add_int(string_buffer, index);
      SPVM_STRING_BUFFER_add(string_buffer, "]");
      break;
    }
    case SPVM_PRECOMPILE_C_CTYPE_ID_REF: {
      SPVM_STRING_BUFFER_add(string_buffer, "ref_vars[");
      SPVM_STRING_BUFFER_add_int(string_buffer, index);
      SPVM_STRING_BUFFER_add(string_buffer, "]");
      break;
    }
    default:
      assert(0);
  }
}

void SPVM_PRECOMPILE_add_operand_address(SPVM_PRECOMPILE* precompile, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t var_index) {
  SPVM_RUNTIME* runtime = precompile->runtime;
  SPVM_STRING_BUFFER_add(string_buffer, "&");
  SPVM_PRECOMPILE_add_operand(precompile, string_buffer, ctype_id, var_index);
}

void SPVM_PRECOMPILE_add_basic_type_id(SPVM_PRECOMPILE* precompile, SPVM_STRING_BUFFER* string_buffer, const char* basic_type_name) {
  SPVM_STRING_BUFFER_add(string_buffer, "basic_type_id");
  SPVM_STRING_BUFFER_add(string_buffer, "__");
  SPVM_STRING_BUFFER_add(string_buffer, basic_type_name);
  SPVM_PRECOMPILE_replace_colon_with_under_score(precompile, string_buffer->value + string_buffer->length - strlen(basic_type_name));
  SPVM_STRING_BUFFER_add(string_buffer, "__");
}

void SPVM_PRECOMPILE_add_field_address_id(SPVM_PRECOMPILE* precompile, SPVM_STRING_BUFFER* string_buffer, const char* basic_type_name, const char* field_name) {
  SPVM_STRING_BUFFER_add(string_buffer, "field_address_id");
  SPVM_STRING_BUFFER_add(string_buffer, "__");
  SPVM_STRING_BUFFER_add(string_buffer, basic_type_name);
  SPVM_PRECOMPILE_replace_colon_with_under_score(precompile, string_buffer->value + string_buffer->length - strlen(basic_type_name));
  SPVM_STRING_BUFFER_add(string_buffer, "__");
  SPVM_STRING_BUFFER_add(string_buffer, field_name);
  SPVM_PRECOMPILE_replace_colon_with_under_score(precompile, string_buffer->value + string_buffer->length - strlen(field_name));
  SPVM_STRING_BUFFER_add(string_buffer, "__");
}

void SPVM_PRECOMPILE_add_class_var_address_id(SPVM_PRECOMPILE* precompile, SPVM_STRING_BUFFER* string_buffer, const char* basic_type_name, const char* class_var_name) {
  SPVM_STRING_BUFFER_add(string_buffer, "class_var_address_id");
  SPVM_STRING_BUFFER_add(string_buffer, "__");
  SPVM_STRING_BUFFER_add(string_buffer, basic_type_name);
  SPVM_PRECOMPILE_replace_colon_with_under_score(precompile, string_buffer->value + string_buffer->length - strlen(basic_type_name));
  SPVM_STRING_BUFFER_add(string_buffer, "__");
  SPVM_STRING_BUFFER_add(string_buffer, class_var_name);
  SPVM_PRECOMPILE_replace_colon_with_under_score(precompile, string_buffer->value + string_buffer->length - strlen(class_var_name));
  SPVM_STRING_BUFFER_add(string_buffer, "__");
}

void SPVM_PRECOMPILE_add_method_address_id(SPVM_PRECOMPILE* precompile, SPVM_STRING_BUFFER* string_buffer, const char* basic_type_name, const char* method_name) {
  SPVM_STRING_BUFFER_add(string_buffer, "method_address_id");
  SPVM_STRING_BUFFER_add(string_buffer, "__");
  SPVM_STRING_BUFFER_add(string_buffer, basic_type_name);
  SPVM_PRECOMPILE_replace_colon_with_under_score(precompile, string_buffer->value + string_buffer->length - strlen(basic_type_name));
  SPVM_STRING_BUFFER_add(string_buffer, "__");
  SPVM_STRING_BUFFER_add(string_buffer, method_name);
  SPVM_PRECOMPILE_replace_colon_with_under_score(precompile, string_buffer->value + string_buffer->length - strlen(method_name));
  SPVM_STRING_BUFFER_add(string_buffer, "__");
}

int32_t SPVM_PRECOMPILE_contains_basic_type_id(SPVM_PRECOMPILE* precompile, const char* string, const char* basic_type_name) {
  
  // basic_type_id__BASIC_TYPE_NAME__
  const char* label = "basic_type_id";
  int32_t found = SPVM_PRECOMPILE_contains_access_id(precompile,string, label, basic_type_name, NULL);
  
  return found;
}

int32_t SPVM_PRECOMPILE_contains_field_address_id(SPVM_PRECOMPILE* precompile, const char* string, const char* basic_type_name, const char* field_name) {
  
  // field_address_id__BASIC_TYPE_NAME__FIELD_NAME__
  const char* label = "field_address_id";
  int32_t found = SPVM_PRECOMPILE_contains_access_id(precompile,string, label, basic_type_name, field_name);
  
  return found;
}

int32_t SPVM_PRECOMPILE_contains_class_var_address_id(SPVM_PRECOMPILE* precompile, const char* string, const char* basic_type_name, const char* class_var_name) {
  
  // class_var_address_id__CLASS_VAR_NAME__
  const char* label = "class_var_address_id";
  int32_t found = SPVM_PRECOMPILE_contains_access_id(precompile,string, label, basic_type_name, class_var_name);
  
  return found;
}

int32_t SPVM_PRECOMPILE_contains_method_address_id(SPVM_PRECOMPILE* precompile, const char* string, const char* basic_type_name, const char* method_name) {
  
  // method_address_id__BASIC_TYPE_NAME__METHOD_NAME__
  const char* label = "method_address_id";
  int32_t found = SPVM_PRECOMPILE_contains_access_id(precompile,string, label, basic_type_name, method_name);
  
  return found;
}

int32_t SPVM_PRECOMPILE_contains_access_id(SPVM_PRECOMPILE* precompile, const char* string, const char* label, const char* name1, const char* name2) {
  
  int32_t label_length = strlen(label);
  
  const char* separator = "__";
  int32_t separator_length = strlen(separator);
  
  int32_t name1_length = strlen(name1);
  
  int32_t name2_length = 0;
  if (name2) {
    name2_length = strlen(name2);
  }
  
  int32_t length = label_length + separator_length + name1_length + separator_length;
  if (name2) {
    length += separator_length + name2_length + separator_length;
  }
  
  char* name_abs = SPVM_ALLOCATOR_alloc_memory_block_unmanaged(length + 1);
  
  memcpy(name_abs, label, label_length);
  memcpy(name_abs + label_length, separator, separator_length);
  memcpy(name_abs + label_length + separator_length, name1, name1_length);
  memcpy(name_abs + label_length + separator_length + name1_length, separator, separator_length);
  if (name2) {
    memcpy(name_abs + label_length + separator_length + name1_length + separator_length, name2, name2_length);
    memcpy(name_abs + label_length + separator_length + name1_length + separator_length + name2_length, separator, separator_length);
  }
  
  SPVM_PRECOMPILE_replace_colon_with_under_score(precompile, name_abs);
  
  int32_t found = 0;
  const char* found_ptr = strstr(string, name_abs);
  if (found_ptr) {
    char after_ch = *(found_ptr + length);
    if (!(after_ch >= 'A' && after_ch <= 'Z')) {
      found = 1;
    }
  }
  
  SPVM_ALLOCATOR_free_memory_block_unmanaged(name_abs);
  
  return found;
}

void SPVM_PRECOMPILE_replace_colon_with_under_score(SPVM_PRECOMPILE* precompile, char* string) {
  int32_t offset = 0;
  while (string[offset] != '\0') {
    if (string[offset] == ':') {
      string[offset] = '_';
    }
    offset++;
  }
}
