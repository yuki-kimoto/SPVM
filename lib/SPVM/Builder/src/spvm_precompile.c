#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stddef.h>

#include "spvm_precompile.h"

#include "spvm_native.h"
#include "spvm_api.h"
#include "spvm_api_runtime.h"
#include "spvm_string_buffer.h"
#include "spvm_opcode.h"

void SPVM_PRECOMPILE_create_precompile_source(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, const char* class_name) {
  
  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Class
  int32_t class_id = SPVM_API_RUNTIME_get_class_id_by_name(env->runtime, class_name);
  int32_t class_is_anon = SPVM_API_RUNTIME_get_class_is_anon(env->runtime, class_id);
  int32_t class_module_file_id = SPVM_API_RUNTIME_get_class_module_file_id(env->runtime, class_id);
  const char* class_module_file = SPVM_API_RUNTIME_get_name(env->runtime, class_module_file_id);
  int32_t class_method_ids_base = SPVM_API_RUNTIME_get_class_method_ids_base(env->runtime, class_id);
  int32_t class_method_ids_length = SPVM_API_RUNTIME_get_class_method_ids_length(env->runtime, class_id);
  
  // Head part - include and define
  SPVM_PRECOMPILE_build_head(env, string_buffer);
  
  // Constant strings
  if (!class_is_anon) {
    SPVM_STRING_BUFFER_add(string_buffer,"static const char* CURRENT_CLASS_FILE = \"");
    SPVM_STRING_BUFFER_add(string_buffer, class_module_file);
    SPVM_STRING_BUFFER_add(string_buffer, "\";\n");
    
    SPVM_STRING_BUFFER_add(string_buffer, "static const char* CURRENT_CLASS_NAME = \"");
    SPVM_STRING_BUFFER_add(string_buffer, class_name);
    SPVM_STRING_BUFFER_add(string_buffer, "\";\n");
  }
  
  // Method decrations
  SPVM_STRING_BUFFER_add(string_buffer, "// Method declarations\n");
  {
    int32_t method_index;
    for (method_index = 0; method_index < class_method_ids_length; method_index++) {
      int32_t method_id = class_method_ids_base + method_index;

      int32_t method_name_id = SPVM_API_RUNTIME_get_method_name_id(env->runtime, method_id);
      const char* method_name = SPVM_API_RUNTIME_get_name(env->runtime, method_name_id);
      int32_t method_signature_id = SPVM_API_RUNTIME_get_method_signature_id(env->runtime, method_id);
      const char* method_signature = SPVM_API_RUNTIME_get_name(env->runtime, method_signature_id);
      int32_t method_has_precompile_flag = SPVM_API_RUNTIME_get_method_has_precompile_flag(env->runtime, method_id);

      if (method_has_precompile_flag) {
        SPVM_PRECOMPILE_build_method_declaration(env, string_buffer, class_name, method_name);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
      }
    }
  }
  SPVM_STRING_BUFFER_add(string_buffer, "\n");
  
  // Method implementations
  SPVM_STRING_BUFFER_add(string_buffer, "// Method implementations\n");
  {
    int32_t method_index;
    for (method_index = 0; method_index < class_method_ids_length; method_index++) {
      int32_t method_id = class_method_ids_base + method_index;
      int32_t method_name_id = SPVM_API_RUNTIME_get_method_name_id(env->runtime, method_id);
      const char* method_name = SPVM_API_RUNTIME_get_name(env->runtime, method_name_id);
      int32_t method_has_precompile_flag = SPVM_API_RUNTIME_get_method_has_precompile_flag(env->runtime, method_id);
      if (method_has_precompile_flag) {
        SPVM_PRECOMPILE_build_method_implementation(env, string_buffer, class_name, method_name);
      }
    }
  }
  SPVM_STRING_BUFFER_add(string_buffer, "\n");
  
  // If the class has anon methods, the anon methods is merged to this class
  int32_t class_anon_method_ids_length = SPVM_API_RUNTIME_get_class_anon_method_ids_length(env->runtime, class_id);
  if (class_anon_method_ids_length > 0) {
    int32_t class_anon_method_ids_base = SPVM_API_RUNTIME_get_class_anon_method_ids_base(env->runtime, class_id);
    for (int32_t anon_method_id = class_anon_method_ids_base; anon_method_id < class_anon_method_ids_length; anon_method_id++) {
      int32_t anon_method_method_id = SPVM_API_RUNTIME_get_anon_method_method_id(env->runtime, anon_method_id);
      int32_t anon_method_class_id = SPVM_API_RUNTIME_get_method_class_id(env->runtime, anon_method_method_id);
      int32_t anon_method_class_name_id = SPVM_API_RUNTIME_get_class_name_id(env->runtime, anon_method_class_id);
      const char* anon_method_class_name = SPVM_API_RUNTIME_get_name(env->runtime, anon_method_class_name_id);
      SPVM_PRECOMPILE_create_precompile_source(env, string_buffer, anon_method_class_name);
    }
  }
}

void SPVM_PRECOMPILE_build_head(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer) {
  
  // Include headers and define macros
  SPVM_STRING_BUFFER_add(string_buffer,
    "#ifndef SPVM_PRECOMPILE_H\n"
    "#define SPVM_PRECOMPILE_H\n"
    "#include <spvm_native.h>\n"
    "\n"
    "#include <stdlib.h>\n"
    "#include <string.h>\n"
    "#include <stdio.h>\n"
    "#include <inttypes.h>\n"
    "#define SPVM_API_GET_OBJECT_NO_WEAKEN_ADDRESS(object) ((void*)((intptr_t)object & ~(intptr_t)1))\n"
    "#define SPVM_API_GET_REF_COUNT(object) ((*(int32_t*)((intptr_t)object + (intptr_t)env->object_ref_count_offset)))\n"
    "#define SPVM_API_INC_REF_COUNT_ONLY(object) ((*(int32_t*)((intptr_t)object + (intptr_t)env->object_ref_count_offset))++)\n"
    "#define SPVM_API_INC_REF_COUNT(object)\\\n"
    "do {\\\n"
    "  if (object != NULL) {\\\n"
    "    SPVM_API_INC_REF_COUNT_ONLY(object);\\\n"
    "  }\\\n"
    "} while (0)\\\n"
    "\n"
    "#define SPVM_API_DEC_REF_COUNT_ONLY(object) ((*(int32_t*)((intptr_t)object + (intptr_t)env->object_ref_count_offset))--)\n"
    "#define SPVM_API_DEC_REF_COUNT(object)\\\n"
    "do {\\\n"
    "  if (object != NULL) {\\\n"
    "    if (SPVM_API_GET_REF_COUNT(object) > 1) { SPVM_API_DEC_REF_COUNT_ONLY(object); }\\\n"
    "    else { env->dec_ref_count(env, object); }\\\n"
    "  }\\\n"
    "} while (0)\\\n"
    "\n"
    "#define SPVM_API_ISWEAK(dist_address) (((intptr_t)*(void**)dist_address) & 1)\n"
    "\n"
    "#define SPVM_API_OBJECT_ASSIGN(dist_address, src_object) \\\n"
    "do {\\\n"
    "  void* tmp_object = SPVM_API_GET_OBJECT_NO_WEAKEN_ADDRESS(src_object);\\\n"
    "  if (tmp_object != NULL) {\\\n"
    "    SPVM_API_INC_REF_COUNT_ONLY(tmp_object);\\\n"
    "  }\\\n"
    "  if (*(void**)(dist_address) != NULL) {\\\n"
    "    if (__builtin_expect(SPVM_API_ISWEAK(dist_address), 0)) { env->unweaken(env, dist_address); }\\\n"
    "    if (SPVM_API_GET_REF_COUNT(*(void**)(dist_address)) > 1) { SPVM_API_DEC_REF_COUNT_ONLY(*(void**)(dist_address)); }\\\n"
    "    else { env->dec_ref_count(env, *(void**)(dist_address)); }\\\n"
    "  }\\\n"
    "  *(void**)(dist_address) = tmp_object;\\\n"
    "} while (0)\\\n"
    "\n"
    "#endif\n"
  );
}

void SPVM_PRECOMPILE_build_method_declaration(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, const char* class_name, const char* method_name) {
  
  // Method declaration
  SPVM_STRING_BUFFER_add(string_buffer, "int32_t SPVMPRECOMPILE__");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)class_name);
  SPVM_STRING_BUFFER_add(string_buffer, (char*)"__");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)method_name);
  {
    int32_t index = string_buffer->length - (strlen(class_name) + 2 + strlen(method_name));
    
    while (index < string_buffer->length) {
      if (string_buffer->value[index] == ':') {
        string_buffer->value[index] = '_';
      }
      index++;
    }
  }
  SPVM_STRING_BUFFER_add(string_buffer, "(SPVM_ENV* env, SPVM_VALUE* stack)");
}

void SPVM_PRECOMPILE_build_method_implementation(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, const char* class_name, const char* method_name) {

  // Runtime
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Class
  int32_t class_id = SPVM_API_RUNTIME_get_class_id_by_name(env->runtime, class_name);
  int32_t class_module_file_id = SPVM_API_RUNTIME_get_class_module_file_id(env->runtime, class_id);
  const char* class_module_file = SPVM_API_RUNTIME_get_name(env->runtime, class_module_file_id);
  int32_t class_is_anon = SPVM_API_RUNTIME_get_class_is_anon(env->runtime, class_id);
  
  // Method
  int32_t method_id = SPVM_API_RUNTIME_get_method_id_by_name(env->runtime, class_name, method_name);
  int32_t method_return_type_id = SPVM_API_RUNTIME_get_method_return_type_id(env->runtime, method_id);

  // Method declaration
  SPVM_PRECOMPILE_build_method_declaration(env, string_buffer, class_name, method_name);

  // Block start
  SPVM_STRING_BUFFER_add(string_buffer, " {\n");

  if (class_is_anon) {
    SPVM_STRING_BUFFER_add(string_buffer,"    const char* CURRENT_CLASS_NAME = \"");
    SPVM_STRING_BUFFER_add(string_buffer, class_name);
    SPVM_STRING_BUFFER_add(string_buffer, "\";\n");
  }

  // Current method name
  SPVM_STRING_BUFFER_add(string_buffer, "  const char* CURRENT_METHOD_NAME = \"");
  SPVM_STRING_BUFFER_add(string_buffer, method_name);
  SPVM_STRING_BUFFER_add(string_buffer, "\";\n");
  
  // Object header byte size
  SPVM_STRING_BUFFER_add(string_buffer, "  int32_t object_header_byte_size = (intptr_t)env->object_header_byte_size;\n");
  
  // Call method argument stack top
  int32_t stack_index = 0;

  // object variable declarations
  int32_t call_stack_object_vars_length = SPVM_API_RUNTIME_get_method_call_stack_object_vars_length(env->runtime, method_id);
  if (call_stack_object_vars_length > 0) {
    SPVM_STRING_BUFFER_add(string_buffer, "  void* object_vars[");
    SPVM_STRING_BUFFER_add_int(string_buffer, call_stack_object_vars_length);
    SPVM_STRING_BUFFER_add(string_buffer, "] = {0};\n");
  }

  // ref variable declarations
  int32_t call_stack_ref_vars_length = SPVM_API_RUNTIME_get_method_call_stack_ref_vars_length(env->runtime, method_id);
  if (call_stack_ref_vars_length > 0) {
    SPVM_STRING_BUFFER_add(string_buffer, "  void* ref_vars[");
    SPVM_STRING_BUFFER_add_int(string_buffer, call_stack_ref_vars_length);
    SPVM_STRING_BUFFER_add(string_buffer, "] = {0};\n");
  }

  // double variable declarations
  int32_t call_stack_double_vars_length = SPVM_API_RUNTIME_get_method_call_stack_double_vars_length(env->runtime, method_id);
  if (call_stack_double_vars_length > 0) {
    SPVM_STRING_BUFFER_add(string_buffer, "  double double_vars[");
    SPVM_STRING_BUFFER_add_int(string_buffer, call_stack_double_vars_length);
    SPVM_STRING_BUFFER_add(string_buffer, "];\n");
  }

  // float variable declarations
  int32_t call_stack_float_vars_length = SPVM_API_RUNTIME_get_method_call_stack_float_vars_length(env->runtime, method_id);
  if (call_stack_float_vars_length > 0) {
    SPVM_STRING_BUFFER_add(string_buffer, "  float float_vars[");
    SPVM_STRING_BUFFER_add_int(string_buffer, call_stack_float_vars_length);
    SPVM_STRING_BUFFER_add(string_buffer, "];\n");
  }

  // long variable declarations
  int32_t call_stack_long_vars_length = SPVM_API_RUNTIME_get_method_call_stack_long_vars_length(env->runtime, method_id);
  if (call_stack_long_vars_length > 0) {
    SPVM_STRING_BUFFER_add(string_buffer, "  int64_t long_vars[");
    SPVM_STRING_BUFFER_add_int(string_buffer, call_stack_long_vars_length);
    SPVM_STRING_BUFFER_add(string_buffer, "];\n");
  }

  // int variable declarations
  int32_t call_stack_int_vars_length = SPVM_API_RUNTIME_get_method_call_stack_int_vars_length(env->runtime, method_id);
  if (call_stack_int_vars_length > 0) {
    SPVM_STRING_BUFFER_add(string_buffer, "  int32_t int_vars[");
    SPVM_STRING_BUFFER_add_int(string_buffer, call_stack_int_vars_length);
    SPVM_STRING_BUFFER_add(string_buffer, "];\n");
  }

  // Exception
  SPVM_STRING_BUFFER_add(string_buffer, "  int32_t exception_flag = 0;\n");
  
  int32_t method_mortal_stack_length = SPVM_API_RUNTIME_get_method_mortal_stack_length(env->runtime, method_id);
  if (method_mortal_stack_length > 0) {
    SPVM_STRING_BUFFER_add(string_buffer, "  int32_t mortal_stack[");
    SPVM_STRING_BUFFER_add_int(string_buffer, method_mortal_stack_length);
    SPVM_STRING_BUFFER_add(string_buffer, "];\n");
    SPVM_STRING_BUFFER_add(string_buffer, "  int32_t mortal_stack_top = 0;\n");
  }
  
  // short variable declarations
  int32_t call_stack_short_vars_length = SPVM_API_RUNTIME_get_method_call_stack_short_vars_length(env->runtime, method_id);
  if (call_stack_short_vars_length > 0) {
    SPVM_STRING_BUFFER_add(string_buffer, "  int16_t short_vars[");
    SPVM_STRING_BUFFER_add_int(string_buffer, call_stack_short_vars_length);
    SPVM_STRING_BUFFER_add(string_buffer, "];\n");
  }

  // byte variable declarations
  int32_t call_stack_byte_vars_length = SPVM_API_RUNTIME_get_method_call_stack_byte_vars_length(env->runtime, method_id);
  if (call_stack_byte_vars_length > 0) {
    SPVM_STRING_BUFFER_add(string_buffer, "  int8_t byte_vars[");
    SPVM_STRING_BUFFER_add_int(string_buffer, call_stack_byte_vars_length);
    SPVM_STRING_BUFFER_add(string_buffer, "];\n");
  }

  // Convert string
  SPVM_STRING_BUFFER_add(string_buffer, "  char convert_string_buffer[21];\n");
  
  SPVM_OPCODE* opcodes = SPVM_API_RUNTIME_get_opcodes(runtime);
  int32_t method_opcode_ids_base = SPVM_API_RUNTIME_get_method_opcode_ids_base(env->runtime, method_id);
  int32_t opcode_ids_length = SPVM_API_RUNTIME_get_method_opcode_ids_length(env->runtime, method_id);
  int32_t opcode_index = 0;
  
  SPVM_OPCODE* opcode = NULL;

  while (opcode_index < opcode_ids_length) {

    // Line label
    SPVM_STRING_BUFFER_add(string_buffer, "L");
    SPVM_STRING_BUFFER_add_int(string_buffer, opcode_index);
    SPVM_STRING_BUFFER_add(string_buffer, ": ");
    
    opcode = &(opcodes[method_opcode_ids_base + opcode_index]);

    int32_t opcode_id = opcode->id;

    SPVM_STRING_BUFFER_add(string_buffer, "// ");
    SPVM_STRING_BUFFER_add(string_buffer, (char*)(SPVM_OPCODE_C_ID_NAMES())[opcode_id]);
    SPVM_STRING_BUFFER_add(string_buffer, "\n");
    
    switch (opcode_id) {
      case SPVM_OPCODE_C_ID_GET_ARG_BYTE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                              "    int32_t arg_mem_id = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "    int32_t stack_index = ");
        SPVM_STRING_BUFFER_add_int( string_buffer, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "    byte_vars[arg_mem_id] = *(int8_t*)&stack[stack_index];\n"
                                              "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ARG_SHORT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                              "    int32_t arg_mem_id = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "    int32_t stack_index = ");
        SPVM_STRING_BUFFER_add_int( string_buffer, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "    short_vars[arg_mem_id] = *(int16_t*)&stack[stack_index];\n"
                                              "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ARG_INT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                              "    int32_t arg_mem_id = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "    int32_t stack_index = ");
        SPVM_STRING_BUFFER_add_int( string_buffer, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "    int_vars[arg_mem_id] = *(int32_t*)&stack[stack_index];\n"
                                              "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ARG_LONG: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                              "    int32_t arg_mem_id = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "    int32_t stack_index = ");
        SPVM_STRING_BUFFER_add_int( string_buffer, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "    long_vars[arg_mem_id] = *(int64_t*)&stack[stack_index];\n"
                                              "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ARG_FLOAT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                              "    int32_t arg_mem_id = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "    int32_t stack_index = ");
        SPVM_STRING_BUFFER_add_int( string_buffer, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "    float_vars[arg_mem_id] = *(float*)&stack[stack_index];\n"
                                              "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ARG_DOUBLE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                              "    int32_t arg_mem_id = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "    int32_t stack_index = ");
        SPVM_STRING_BUFFER_add_int( string_buffer, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "    double_vars[arg_mem_id] = *(double*)&stack[stack_index];\n"
                                              "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ARG_OBJECT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                              "    int32_t arg_mem_id = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "    int32_t stack_index = ");
        SPVM_STRING_BUFFER_add_int( string_buffer, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "    object_vars[arg_mem_id] = *(void**)&stack[stack_index];\n"
                                              "    void* object = *(void**)&object_vars[arg_mem_id];\n"
                                              "    if (object != NULL) {\n"
                                              "      SPVM_API_INC_REF_COUNT_ONLY(object);\n"
                                              "    }\n"
                                              "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ARG_REF: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                              "    int32_t arg_mem_id = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "    int32_t stack_index = ");
        SPVM_STRING_BUFFER_add_int( string_buffer, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "    ref_vars[arg_mem_id] = *(void**)&stack[stack_index];\n"
                                              "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ARG_MULNUM_BYTE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                              "    int32_t arg_mem_id = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "    int32_t stack_index = ");
        SPVM_STRING_BUFFER_add_int( string_buffer, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "    int32_t type_width = ");
        SPVM_STRING_BUFFER_add_int( string_buffer, opcode->operand3);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "    for (int32_t field_index = 0; field_index < type_width; field_index++) {\n"
                                              "      byte_vars[arg_mem_id + field_index] = *(int8_t*)&stack[stack_index + field_index];\n"
                                              "    }\n"
                                              "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ARG_MULNUM_SHORT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                              "    int32_t arg_mem_id = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "    int32_t stack_index = ");
        SPVM_STRING_BUFFER_add_int( string_buffer, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "    int32_t type_width = ");
        SPVM_STRING_BUFFER_add_int( string_buffer, opcode->operand3);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "    for (int32_t field_index = 0; field_index < type_width; field_index++) {\n"
                                              "      short_vars[arg_mem_id + field_index] = *(int16_t*)&stack[stack_index + field_index];\n"
                                              "    }\n"
                                              "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ARG_MULNUM_INT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                              "    int32_t arg_mem_id = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "    int32_t stack_index = ");
        SPVM_STRING_BUFFER_add_int( string_buffer, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "    int32_t type_width = ");
        SPVM_STRING_BUFFER_add_int( string_buffer, opcode->operand3);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "    for (int32_t field_index = 0; field_index < type_width; field_index++) {\n"
                                              "      int_vars[arg_mem_id + field_index] = *(int32_t*)&stack[stack_index + field_index];\n"
                                              "    }\n"
                                              "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ARG_MULNUM_LONG: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                              "    int32_t arg_mem_id = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "    int32_t stack_index = ");
        SPVM_STRING_BUFFER_add_int( string_buffer, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "    int32_t type_width = ");
        SPVM_STRING_BUFFER_add_int( string_buffer, opcode->operand3);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "    for (int32_t field_index = 0; field_index < type_width; field_index++) {\n"
                                              "      long_vars[arg_mem_id + field_index] = *(int64_t*)&stack[stack_index + field_index];\n"
                                              "    }\n"
                                              "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ARG_MULNUM_FLOAT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                              "    int32_t arg_mem_id = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "    int32_t stack_index = ");
        SPVM_STRING_BUFFER_add_int( string_buffer, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "    int32_t type_width = ");
        SPVM_STRING_BUFFER_add_int( string_buffer, opcode->operand3);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "    for (int32_t field_index = 0; field_index < type_width; field_index++) {\n"
                                              "      float_vars[arg_mem_id + field_index] = *(float*)&stack[stack_index + field_index];\n"
                                              "    }\n"
                                              "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ARG_MULNUM_DOUBLE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                              "    int32_t arg_mem_id = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "    int32_t stack_index = ");
        SPVM_STRING_BUFFER_add_int( string_buffer, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "    int32_t type_width = ");
        SPVM_STRING_BUFFER_add_int( string_buffer, opcode->operand3);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "    for (int32_t field_index = 0; field_index < type_width; field_index++) {\n"
                                              "      double_vars[arg_mem_id + field_index] = *(double*)&stack[stack_index + field_index];\n"
                                              "    }\n"
                                              "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_BOOL_INT: {
        SPVM_PRECOMPILE_add_bool(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_BOOL_LONG: {
        SPVM_PRECOMPILE_add_bool(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_BOOL_FLOAT: {
        SPVM_PRECOMPILE_add_bool(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_BOOL_DOUBLE: {
        SPVM_PRECOMPILE_add_bool(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_BOOL_BOOL_OBJECT: {
        SPVM_PRECOMPILE_add_bool(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BOOL_OBJECT, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_BOOL_OBJECT: {
        SPVM_PRECOMPILE_add_bool(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_IS_UNDEF: {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, 0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, " == NULL;\n");
        break;
      }
      case SPVM_OPCODE_C_ID_IS_NOT_UNDEF: {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, 0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, " != NULL;\n");
        break;
      }
      case SPVM_OPCODE_C_ID_EQ_INT: {
        SPVM_PRECOMPILE_add_numeric_eq(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_EQ_LONG: {
        SPVM_PRECOMPILE_add_numeric_eq(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_EQ_FLOAT: {
        SPVM_PRECOMPILE_add_numeric_eq(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_EQ_DOUBLE: {
        SPVM_PRECOMPILE_add_numeric_eq(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_EQ_OBJECT: {
        SPVM_PRECOMPILE_add_numeric_eq(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_NE_INT: {
        SPVM_PRECOMPILE_add_numeric_ne(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_NE_LONG: {
        SPVM_PRECOMPILE_add_numeric_ne(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_NE_FLOAT: {
        SPVM_PRECOMPILE_add_numeric_ne(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_NE_DOUBLE: {
        SPVM_PRECOMPILE_add_numeric_ne(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_NE_OBJECT: {
        SPVM_PRECOMPILE_add_numeric_ne(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_GT_INT: {
        SPVM_PRECOMPILE_add_numeric_gt(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_GT_LONG: {
        SPVM_PRECOMPILE_add_numeric_gt(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_GT_FLOAT: {
        SPVM_PRECOMPILE_add_numeric_gt(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_GT_DOUBLE: {
        SPVM_PRECOMPILE_add_numeric_gt(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_GE_INT: {
        SPVM_PRECOMPILE_add_numeric_ge(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_GE_LONG: {
        SPVM_PRECOMPILE_add_numeric_ge(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_GE_FLOAT: {
        SPVM_PRECOMPILE_add_numeric_ge(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_GE_DOUBLE: {
        SPVM_PRECOMPILE_add_numeric_ge(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_LT_INT: {
        SPVM_PRECOMPILE_add_numeric_lt(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_LT_LONG: {
        SPVM_PRECOMPILE_add_numeric_lt(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_LT_FLOAT: {
        SPVM_PRECOMPILE_add_numeric_lt(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_LT_DOUBLE: {
        SPVM_PRECOMPILE_add_numeric_lt(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_LE_INT: {
        SPVM_PRECOMPILE_add_numeric_le(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_LE_LONG: {
        SPVM_PRECOMPILE_add_numeric_le(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_LE_FLOAT: {
        SPVM_PRECOMPILE_add_numeric_le(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_LE_DOUBLE: {
        SPVM_PRECOMPILE_add_numeric_le(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_CMP_INT: {
        SPVM_PRECOMPILE_add_numeric_cmp(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_CMP_LONG: {
        SPVM_PRECOMPILE_add_numeric_cmp(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_CMP_FLOAT: {
        SPVM_PRECOMPILE_add_numeric_cmp(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_CMP_DOUBLE: {
        SPVM_PRECOMPILE_add_numeric_cmp(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_IS_TYPE:
      {
        int32_t check_basic_type_id = opcode->operand2;
        int32_t check_type_dimension = opcode->operand3;
        int32_t basic_type_name_id = SPVM_API_RUNTIME_get_basic_type_name_id(env->runtime, check_basic_type_id);
        const char* basic_type_name = SPVM_API_RUNTIME_get_name(env->runtime, basic_type_name_id);
        int32_t dimension = check_type_dimension;
        
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                              "    int32_t access_basic_type_id = env->get_basic_type_id(env, \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (access_basic_type_id < 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* exception = env->new_string_nolen_raw(env, \"Basic type not found:");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, ":Is type\");\n"
                                              "      env->set_exception(env, exception);\n"
                                              "      exception_flag = 1;\n"
                                              "    }\n"
                                              "    if (!exception_flag) {\n"
                                              "      int32_t check_basic_type_id = "
                                              "access_basic_type_id"
                                              ";\n"
                                              "      int32_t check_type_dimension = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, dimension);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "      void* object = ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "      if (object) {\n"
                                              "        int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_offset);\n"
                                              "        int32_t object_type_dimension = *(uint8_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_offset);\n");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, 0);
        SPVM_STRING_BUFFER_add(string_buffer, " = env->is_type(env, object, check_basic_type_id, check_type_dimension);\n"
                                              "      }\n"
                                              "      else {\n");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, 0);
        SPVM_STRING_BUFFER_add(string_buffer, " = 0;\n"
                                              "      }\n"
                                              "    }\n"
                                              "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_HAS_CALLBACK:
      {
        int32_t check_basic_type_id = opcode->operand2;
        int32_t check_type_dimension = opcode->operand3;
        int32_t basic_type_name_id = SPVM_API_RUNTIME_get_basic_type_name_id(env->runtime, check_basic_type_id);
        const char* basic_type_name = SPVM_API_RUNTIME_get_name(env->runtime, basic_type_name_id);
        int32_t dimension = check_type_dimension;
        
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                              "    int32_t access_basic_type_id = env->get_basic_type_id(env, \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n"
                                              "    if (access_basic_type_id < 0) {\n"
                                              "      void* exception = env->new_string_nolen_raw(env, \"Basic type not found:");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, ":Has callback\");\n"
                                              "      env->set_exception(env, exception);\n"
                                              "      exception_flag = 1;\n"
                                              "    }\n"
                                              "    if (!exception_flag) {\n"
                                              "      int32_t callback_basic_type_id = access_basic_type_id;\n"
                                              "      int32_t callback_type_dimension = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, dimension);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "      void* object = ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "      if (object) {\n"
                                              "        int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_offset);\n");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, 0);
        SPVM_STRING_BUFFER_add(string_buffer, " = env->has_callback(env, object, callback_basic_type_id);\n"
                                              "      }\n"
                                              "      else {\n");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, 0);
        SPVM_STRING_BUFFER_add(string_buffer, " = 0;\n"
                                              "      }\n"
                                              "    }\n"
                                              "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_HAS_INTERFACE:
      {
        int32_t check_basic_type_id = opcode->operand2;
        int32_t check_type_dimension = opcode->operand3;
        int32_t basic_type_name_id = SPVM_API_RUNTIME_get_basic_type_name_id(env->runtime, check_basic_type_id);
        const char* basic_type_name = SPVM_API_RUNTIME_get_name(env->runtime, basic_type_name_id);
        int32_t dimension = check_type_dimension;
        
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                              "    int32_t access_basic_type_id = env->get_basic_type_id(env, \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n"
                                              "    if (access_basic_type_id < 0) {\n"
                                              "      void* exception = env->new_string_nolen_raw(env, \"Basic type not found:");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, ":Has interface\");\n"
                                              "      env->set_exception(env, exception);\n"
                                              "      exception_flag = 1;\n"
                                              "    }\n"
                                              "    if (!exception_flag) {\n"
                                              "      int32_t interface_basic_type_id = "
                                              "access_basic_type_id"
                                              ";\n"
                                              "      int32_t interface_type_dimension = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, dimension);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "      void* object = ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "      if (object) {\n"
                                              "        int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_offset);\n");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, 0);
        SPVM_STRING_BUFFER_add(string_buffer, "      = env->has_interface(env, object, interface_basic_type_id);\n"
                                              "      }\n"
                                              "      else {\n");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, 0);
        SPVM_STRING_BUFFER_add(string_buffer, " = 0;\n"
                                              "      }\n"
                                              "    }\n"
                                              "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_STRING_EQ:
      case SPVM_OPCODE_C_ID_STRING_NE:
      case SPVM_OPCODE_C_ID_STRING_GT:
      case SPVM_OPCODE_C_ID_STRING_GE:
      case SPVM_OPCODE_C_ID_STRING_LT:
      case SPVM_OPCODE_C_ID_STRING_LE:
      case SPVM_OPCODE_C_ID_STRING_CMP:
      {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                              "    void* object1 = ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* object2 = ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (object1 == NULL && object2 == NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, 0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        switch (opcode_id) {
          case SPVM_OPCODE_C_ID_STRING_EQ: {
            SPVM_STRING_BUFFER_add(string_buffer, "1;\n");
            break;
          }
          case SPVM_OPCODE_C_ID_STRING_NE: {
            SPVM_STRING_BUFFER_add(string_buffer, "0;\n");
            break;
          }
          case SPVM_OPCODE_C_ID_STRING_GT: {
            SPVM_STRING_BUFFER_add(string_buffer, "0;\n");
            break;
          }
          case SPVM_OPCODE_C_ID_STRING_GE: {
            SPVM_STRING_BUFFER_add(string_buffer, "1;\n");
            break;
          }
          case SPVM_OPCODE_C_ID_STRING_LT: {
            SPVM_STRING_BUFFER_add(string_buffer, "0;\n");
            break;
          }
          case SPVM_OPCODE_C_ID_STRING_LE: {
            SPVM_STRING_BUFFER_add(string_buffer, "1;\n");
            break;
          }
          case SPVM_OPCODE_C_ID_STRING_CMP: {
            SPVM_STRING_BUFFER_add(string_buffer, "0;\n");
            break;
          }
        }
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n"
                                              "    else if (object1 != NULL && object2 == NULL) {\n"
                                              "      ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, 0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        switch (opcode_id) {
          case SPVM_OPCODE_C_ID_STRING_EQ: {
            SPVM_STRING_BUFFER_add(string_buffer, "0;\n");
            break;
          }
          case SPVM_OPCODE_C_ID_STRING_NE: {
            SPVM_STRING_BUFFER_add(string_buffer, "1;\n");
            break;
          }
          case SPVM_OPCODE_C_ID_STRING_GT: {
            SPVM_STRING_BUFFER_add(string_buffer, "1;\n");
            break;
          }
          case SPVM_OPCODE_C_ID_STRING_GE: {
            SPVM_STRING_BUFFER_add(string_buffer, "1;\n");
            break;
          }
          case SPVM_OPCODE_C_ID_STRING_LT: {
            SPVM_STRING_BUFFER_add(string_buffer, "0;\n");
            break;
          }
          case SPVM_OPCODE_C_ID_STRING_LE: {
            SPVM_STRING_BUFFER_add(string_buffer, "0;\n");
            break;
          }
          case SPVM_OPCODE_C_ID_STRING_CMP: {
            SPVM_STRING_BUFFER_add(string_buffer, "1;\n");
            break;
          }
        }
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n"
                                              "    else if (object1 == NULL && object2 != NULL) {\n"
                                              "      ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, 0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        switch (opcode_id) {
          case SPVM_OPCODE_C_ID_STRING_EQ: {
            SPVM_STRING_BUFFER_add(string_buffer, "0;\n");
            break;
          }
          case SPVM_OPCODE_C_ID_STRING_NE: {
            SPVM_STRING_BUFFER_add(string_buffer, "1;\n");
            break;
          }
          case SPVM_OPCODE_C_ID_STRING_GT: {
            SPVM_STRING_BUFFER_add(string_buffer, "0;\n");
            break;
          }
          case SPVM_OPCODE_C_ID_STRING_GE: {
            SPVM_STRING_BUFFER_add(string_buffer, "0;\n");
            break;
          }
          case SPVM_OPCODE_C_ID_STRING_LT: {
            SPVM_STRING_BUFFER_add(string_buffer, "1;\n");
            break;
          }
          case SPVM_OPCODE_C_ID_STRING_LE: {
            SPVM_STRING_BUFFER_add(string_buffer, "1;\n");
            break;
          }
          case SPVM_OPCODE_C_ID_STRING_CMP: {
            SPVM_STRING_BUFFER_add(string_buffer, "-1;\n");
            break;
          }
        }
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n"
                                              "    else {\n"
                                              "      int32_t length1 = *(int32_t*)((intptr_t)object1 + (intptr_t)env->object_length_offset);\n"
                                              "      int32_t lenght2 = *(int32_t*)((intptr_t)object2 + (intptr_t)env->object_length_offset);\n"
                                              "      const char* bytes1 = env->get_chars(env, object1);\n"
                                              "      const char* bytes2 = env->get_chars(env, object2);\n"
                                              "      int32_t short_string_length = length1 < lenght2 ? length1 : lenght2;\n"
                                              "      int32_t retval = memcmp(bytes1, bytes2, short_string_length);\n"
                                              "      int32_t cmp;\n"
                                              "      if (retval) {\n"
                                              "        cmp = retval < 0 ? -1 : 1;\n"
                                              "      } else if (length1 == lenght2) {\n"
                                              "        cmp = 0;\n"
                                              "      } else {\n"
                                              "        cmp = length1 < lenght2 ? -1 : 1;\n"
                                              "      }\n"
                                              "      ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, 0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        switch (opcode_id) {
          case SPVM_OPCODE_C_ID_STRING_EQ: {
            SPVM_STRING_BUFFER_add(string_buffer, "(cmp == 0);\n");
            break;
          }
          case SPVM_OPCODE_C_ID_STRING_NE: {
            SPVM_STRING_BUFFER_add(string_buffer, "(cmp != 0);\n");
            break;
          }
          case SPVM_OPCODE_C_ID_STRING_GT: {
            SPVM_STRING_BUFFER_add(string_buffer, "(cmp == 1);\n");
            break;
          }
          case SPVM_OPCODE_C_ID_STRING_GE: {
            SPVM_STRING_BUFFER_add(string_buffer, "(cmp >= 0);\n");
            break;
          }
          case SPVM_OPCODE_C_ID_STRING_LT: {
            SPVM_STRING_BUFFER_add(string_buffer, "(cmp == -1);\n");
            break;
          }
          case SPVM_OPCODE_C_ID_STRING_LE: {
            SPVM_STRING_BUFFER_add(string_buffer, "(cmp <= 0);\n");
            break;
          }
          case SPVM_OPCODE_C_ID_STRING_CMP: {
            SPVM_STRING_BUFFER_add(string_buffer, "cmp;\n");
            break;
          }
        }
        
        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");

        break;
      }
      case SPVM_OPCODE_C_ID_ADD_INT: {
        SPVM_PRECOMPILE_add_add(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_ADD_LONG: {
        SPVM_PRECOMPILE_add_add(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_ADD_FLOAT: {
        SPVM_PRECOMPILE_add_add(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_ADD_DOUBLE: {
        SPVM_PRECOMPILE_add_add(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_SUBTRACT_INT: {
        SPVM_PRECOMPILE_add_subtract(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_SUBTRACT_LONG: {
        SPVM_PRECOMPILE_add_subtract(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_SUBTRACT_FLOAT: {
        SPVM_PRECOMPILE_add_subtract(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_SUBTRACT_DOUBLE: {
        SPVM_PRECOMPILE_add_subtract(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_MULTIPLY_INT: {
        SPVM_PRECOMPILE_add_multiply(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_MULTIPLY_LONG: {
        SPVM_PRECOMPILE_add_multiply(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_MULTIPLY_FLOAT: {
        SPVM_PRECOMPILE_add_multiply(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_MULTIPLY_DOUBLE: {
        SPVM_PRECOMPILE_add_multiply(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_DIVIDE_INT: {
        SPVM_PRECOMPILE_add_divide_integral(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_DIVIDE_LONG: { 
        SPVM_PRECOMPILE_add_divide_integral(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_DIVIDE_FLOAT: {
        SPVM_PRECOMPILE_add_divide_floating_point(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_DIVIDE_DOUBLE: {
        SPVM_PRECOMPILE_add_divide_floating_point(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_DIVIDE_UNSIGNED_INT: {
        SPVM_PRECOMPILE_add_divide_unsigned_int(env, string_buffer, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_DIVIDE_UNSIGNED_LONG: {
        SPVM_PRECOMPILE_add_divide_unsigned_long(env, string_buffer, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_REMAINDER_INT: {
        SPVM_PRECOMPILE_add_remainder_integral(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_REMAINDER_LONG: { 
        SPVM_PRECOMPILE_add_remainder_integral(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_LEFT_SHIFT_INT: {
        SPVM_PRECOMPILE_add_left_shift(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_LEFT_SHIFT_LONG: {
        SPVM_PRECOMPILE_add_left_shift(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_REMAINDER_UNSIGNED_INT: {
        SPVM_PRECOMPILE_add_remainder_unsigned_int(env, string_buffer, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_REMAINDER_UNSIGNED_LONG: {
        SPVM_PRECOMPILE_add_remainder_unsigned_long(env, string_buffer, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_RIGHT_ARITHMETIC_SHIFT_INT: {
        SPVM_PRECOMPILE_add_right_arithmetic_shift(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_RIGHT_ARITHMETIC_SHIFT_LONG: {
        SPVM_PRECOMPILE_add_right_arithmetic_shift(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_RIGHT_LOGICAL_SHIFT_INT: {
        SPVM_PRECOMPILE_add_right_logical_shift(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_RIGHT_LOGICAL_SHIFT_LONG: {
        SPVM_PRECOMPILE_add_right_logical_shift(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_BIT_AND_INT: {
        SPVM_PRECOMPILE_add_bit_and(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_BIT_AND_LONG: {
        SPVM_PRECOMPILE_add_bit_and(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_BIT_OR_INT: {
        SPVM_PRECOMPILE_add_bit_or(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_BIT_OR_LONG: {
        SPVM_PRECOMPILE_add_bit_or(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_BIT_XOR_INT: {
        SPVM_PRECOMPILE_add_bit_xor(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_BIT_XOR_LONG: {
        SPVM_PRECOMPILE_add_bit_xor(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_NEGATE_INT: {
        SPVM_PRECOMPILE_add_negate(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_NEGATE_LONG: {
        SPVM_PRECOMPILE_add_negate(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_NEGATE_FLOAT: {
        SPVM_PRECOMPILE_add_negate(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_NEGATE_DOUBLE: {
        SPVM_PRECOMPILE_add_negate(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_BIT_NOT_INT: {
        SPVM_PRECOMPILE_add_complement(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_BIT_NOT_LONG: {
        SPVM_PRECOMPILE_add_complement(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_BYTE: {
        SPVM_PRECOMPILE_add_convert(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_INT_TO_BYTE: {
        SPVM_PRECOMPILE_add_convert(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_LONG_TO_BYTE: {
        SPVM_PRECOMPILE_add_convert(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_BYTE: {
        SPVM_PRECOMPILE_add_convert(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_BYTE: {
        SPVM_PRECOMPILE_add_convert(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_SHORT: {
        SPVM_PRECOMPILE_add_convert(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_INT_TO_SHORT: {
        SPVM_PRECOMPILE_add_convert(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_LONG_TO_SHORT: {
        SPVM_PRECOMPILE_add_convert(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_SHORT: {
        SPVM_PRECOMPILE_add_convert(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_SHORT: {
        SPVM_PRECOMPILE_add_convert(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_INT: {
        SPVM_PRECOMPILE_add_convert(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_INT: {
        SPVM_PRECOMPILE_add_convert(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_LONG_TO_INT: {
        SPVM_PRECOMPILE_add_convert(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_INT: {
        SPVM_PRECOMPILE_add_convert(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_INT: {
        SPVM_PRECOMPILE_add_convert(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_LONG: {
        SPVM_PRECOMPILE_add_convert(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_LONG: {
        SPVM_PRECOMPILE_add_convert(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_INT_TO_LONG: {
        SPVM_PRECOMPILE_add_convert(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_LONG: {
        SPVM_PRECOMPILE_add_convert(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_LONG: {
        SPVM_PRECOMPILE_add_convert(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_FLOAT: {
        SPVM_PRECOMPILE_add_convert(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_FLOAT: {
        SPVM_PRECOMPILE_add_convert(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_INT_TO_FLOAT: {
        SPVM_PRECOMPILE_add_convert(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_LONG_TO_FLOAT: {
        SPVM_PRECOMPILE_add_convert(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_FLOAT: {
        SPVM_PRECOMPILE_add_convert(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_DOUBLE: {
        SPVM_PRECOMPILE_add_convert(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_DOUBLE: {
        SPVM_PRECOMPILE_add_convert(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_INT_TO_DOUBLE: {
        SPVM_PRECOMPILE_add_convert(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_LONG_TO_DOUBLE: {
        SPVM_PRECOMPILE_add_convert(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_DOUBLE: {
        SPVM_PRECOMPILE_add_convert(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_STRING_TO_BYTE_ARRAY: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                              "    void* src_string = ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "    int32_t src_string_length = env->length(env, src_string);"
                                              "    const char* src_string_data = env->get_chars(env, src_string);"
                                              "    void* byte_array = env->new_byte_array_raw(env, src_string_length);"
                                              "    int8_t* byte_array_data = env->get_elems_byte(env, byte_array);"
                                              "    memcpy(byte_array_data, src_string_data, src_string_length);"
                                              "    SPVM_API_OBJECT_ASSIGN(&");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", byte_array);\n"
                                              "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_BYTE_ARRAY_TO_STRING: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                              "    void* src_byte_array = ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "    int32_t src_byte_array_length = env->length(env, src_byte_array);"
                                              "    int8_t* src_byte_array_data = env->get_elems_byte(env, src_byte_array);"
                                              "    void* string = env->new_string_raw(env, (const char*)src_byte_array_data, src_byte_array_length);"
                                              "    SPVM_API_OBJECT_ASSIGN(&");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", string);\n"
                                              "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_STRING:
      case SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_STRING:
      case SPVM_OPCODE_C_ID_CONVERT_INT_TO_STRING:
      case SPVM_OPCODE_C_ID_CONVERT_LONG_TO_STRING:
      case SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_STRING:
      case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_STRING:
      {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        switch (opcode_id) {
          case SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_STRING:
            SPVM_STRING_BUFFER_add(string_buffer, "    sprintf(convert_string_buffer, \"%\" PRId8, ");
            SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand1);
            SPVM_STRING_BUFFER_add(string_buffer, ");\n");
            break;
          case SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_STRING:
            SPVM_STRING_BUFFER_add(string_buffer, "    sprintf(convert_string_buffer, \"%\" PRId16, ");
            SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand1);
            SPVM_STRING_BUFFER_add(string_buffer, ");\n");
            break;
          case SPVM_OPCODE_C_ID_CONVERT_INT_TO_STRING:
            SPVM_STRING_BUFFER_add(string_buffer, "    sprintf(convert_string_buffer, \"%\" PRId32, ");
            SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
            SPVM_STRING_BUFFER_add(string_buffer, ");\n");
            break;
          case SPVM_OPCODE_C_ID_CONVERT_LONG_TO_STRING:
            SPVM_STRING_BUFFER_add(string_buffer, "    sprintf(convert_string_buffer, \"%\" PRId64, ");
            SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1);
            SPVM_STRING_BUFFER_add(string_buffer, ");\n");
            break;
          case SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_STRING:
            SPVM_STRING_BUFFER_add(string_buffer, "    sprintf(convert_string_buffer, \"%g\", ");
            SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand1);
            SPVM_STRING_BUFFER_add(string_buffer, ");\n");
            break;
          case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_STRING:
            SPVM_STRING_BUFFER_add(string_buffer, "    sprintf(convert_string_buffer, \"%g\", ");
            SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand1);
            SPVM_STRING_BUFFER_add(string_buffer, ");\n");
            break;
        }
        
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t string_length = strlen(convert_string_buffer);\n"
                                              "    void* string = env->new_string_raw(env, convert_string_buffer, string_length);\n"
                                              "    SPVM_API_OBJECT_ASSIGN(&");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", string);\n"
                                              "  }\n");

        break;
      }
      case SPVM_OPCODE_C_ID_INIT_BYTE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = 0;\n");
        break;
      }
      case SPVM_OPCODE_C_ID_INIT_SHORT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = 0;\n");
        break;
      }
      case SPVM_OPCODE_C_ID_INIT_INT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = 0;\n");
        break;
      }
      case SPVM_OPCODE_C_ID_INIT_LONG: {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = 0;\n");
        break;
      }
      case SPVM_OPCODE_C_ID_INIT_FLOAT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = 0;\n");
        break;
      }
      case SPVM_OPCODE_C_ID_INIT_DOUBLE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = 0;\n");
        break;
      }
      case SPVM_OPCODE_C_ID_INIT_UNDEF: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_API_OBJECT_ASSIGN(&");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", NULL);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_INIT_MULNUM_BYTE: {
        int32_t fields_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_PRECOMPILE_add_operand_value(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = 0;\n");
        }
        break;
      }
      case SPVM_OPCODE_C_ID_INIT_MULNUM_SHORT: {
        int32_t fields_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_PRECOMPILE_add_operand_value(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = 0;\n");
        }
        break;
      }
      case SPVM_OPCODE_C_ID_INIT_MULNUM_INT: {
        int32_t fields_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_PRECOMPILE_add_operand_value(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = 0;\n");
        }
        break;
      }
      case SPVM_OPCODE_C_ID_INIT_MULNUM_LONG: {
        int32_t fields_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_PRECOMPILE_add_operand_value(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = 0;\n");
        }
        break;
      }
      case SPVM_OPCODE_C_ID_INIT_MULNUM_FLOAT: {
        int32_t fields_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_PRECOMPILE_add_operand_value(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = 0;\n");
        }
        break;
      }
      case SPVM_OPCODE_C_ID_INIT_MULNUM_DOUBLE: {
        int32_t fields_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_PRECOMPILE_add_operand_value(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = 0;\n");
        }
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_CONSTANT_BYTE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_STRING_BUFFER_add_char(string_buffer, (int8_t)opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_CONSTANT_INT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, (int32_t)opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_CONSTANT_LONG: {
        int64_t long_value = *(int64_t*)&opcode->operand1;
        
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_STRING_BUFFER_add_long(string_buffer, long_value);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_CONSTANT_FLOAT: {
        SPVM_VALUE value;
        value.ival = (int32_t)opcode->operand1;
        
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                              "    SPVM_VALUE tmp_constant;\n"
                                              "    ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = (tmp_constant.ival = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, value.ival);
        SPVM_STRING_BUFFER_add(string_buffer, ", tmp_constant.fval);\n"
                                              "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_CONSTANT_DOUBLE: {
        double double_value = *(double*)&opcode->operand1;

        SPVM_VALUE value;
        value.dval = double_value;

        SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                              "    SPVM_VALUE tmp_constant;\n"
                                              "    ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = (tmp_constant.lval = ");
        SPVM_STRING_BUFFER_add_long(string_buffer, value.lval);
        SPVM_STRING_BUFFER_add(string_buffer, ", tmp_constant.dval);\n"
                                              "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ARRAY_ELEMENT_BYTE:
        SPVM_PRECOMPILE_add_array_fetch(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_GET_ARRAY_ELEMENT_SHORT:
        SPVM_PRECOMPILE_add_array_fetch(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_GET_ARRAY_ELEMENT_INT:
        SPVM_PRECOMPILE_add_array_fetch(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_GET_ARRAY_ELEMENT_LONG:
        SPVM_PRECOMPILE_add_array_fetch(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_GET_ARRAY_ELEMENT_FLOAT:
        SPVM_PRECOMPILE_add_array_fetch(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_GET_ARRAY_ELEMENT_DOUBLE:
        SPVM_PRECOMPILE_add_array_fetch(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_BYTE: {
        int32_t fields_length = opcode->operand3;
        SPVM_PRECOMPILE_add_mulnum_array_fetch(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, opcode->operand1, opcode->operand2, fields_length);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_SHORT: {
        int32_t fields_length = opcode->operand3;
        SPVM_PRECOMPILE_add_mulnum_array_fetch(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, opcode->operand1, opcode->operand2, fields_length);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_INT: {
        int32_t fields_length = opcode->operand3;
        SPVM_PRECOMPILE_add_mulnum_array_fetch(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, opcode->operand2, fields_length);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_LONG: {
        int32_t fields_length = opcode->operand3;
        SPVM_PRECOMPILE_add_mulnum_array_fetch(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, opcode->operand2, fields_length);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_FLOAT: {
        int32_t fields_length = opcode->operand3;
        SPVM_PRECOMPILE_add_mulnum_array_fetch(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1, opcode->operand2, fields_length);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_DOUBLE: {
        int32_t fields_length = opcode->operand3;
        SPVM_PRECOMPILE_add_mulnum_array_fetch(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1, opcode->operand2, fields_length);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_ARRAY_ELEMENT_OBJECT:
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                              "    void* array = ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "    int32_t index = ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "    if (__builtin_expect(array == NULL, 0)) { \n"
                                              "      env->set_exception(env, env->new_string_nolen_raw(env, \"Array must not be undef\")); \n"
                                              "      exception_flag = 1;\n"
                                              "    } \n"
                                              "    else { \n"
                                              "      if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) { \n"
                                              "        env->set_exception(env, env->new_string_nolen_raw(env, \"Index is out of range\")); \n"
                                              "        exception_flag = 1;\n"
                                              "      } \n"
                                              "      else { \n"
                                              "        void* object = ((void**)((intptr_t)array + object_header_byte_size))[index];\n"
                                              "        SPVM_API_OBJECT_ASSIGN(&");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object); \n"
                                              "      } \n"
                                              "    } \n"
                                              "  } \n");
        break;
      case SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_FIELD_BYTE: {
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        SPVM_PRECOMPILE_add_mulnum_array_field_fetch(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, opcode->operand1, opcode->operand2, fields_length, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_FIELD_SHORT: {
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        SPVM_PRECOMPILE_add_mulnum_array_field_fetch(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, opcode->operand1, opcode->operand2, fields_length, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_FIELD_INT: {
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        SPVM_PRECOMPILE_add_mulnum_array_field_fetch(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, opcode->operand2, fields_length, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_FIELD_LONG: {
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        SPVM_PRECOMPILE_add_mulnum_array_field_fetch(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, opcode->operand2, fields_length, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_FIELD_FLOAT: {
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        SPVM_PRECOMPILE_add_mulnum_array_field_fetch(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1, opcode->operand2, fields_length, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_FIELD_DOUBLE: {
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        SPVM_PRECOMPILE_add_mulnum_array_field_fetch(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1, opcode->operand2, fields_length, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_BYTE:
        SPVM_PRECOMPILE_add_array_store(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_SHORT:
        SPVM_PRECOMPILE_add_array_store(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_INT:
        SPVM_PRECOMPILE_add_array_store(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_LONG:
        SPVM_PRECOMPILE_add_array_store(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_FLOAT:
        SPVM_PRECOMPILE_add_array_store(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_DOUBLE:
        SPVM_PRECOMPILE_add_array_store(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_OBJECT:
      {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                              "    void* array = ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "    int32_t index = ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "    if (__builtin_expect(array == NULL, 0)) { \n"
                                              "      env->set_exception(env, env->new_string_nolen_raw(env, \"Array must not be undef\")); \n"
                                              "      exception_flag = 1;\n"
                                              "    } \n"
                                              "    else { \n"
                                              "      if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) { \n"
                                              "          env->set_exception(env, env->new_string_nolen_raw(env, \"Index is out of range\")); \n"
                                              "          exception_flag = 1;\n"
                                              "      } \n"
                                              "      else {\n"
                                              "        void** element_address = &((void**)((intptr_t)array + object_header_byte_size))[index];\n"
                                              "        SPVM_API_OBJECT_ASSIGN(\n"
                                              "          element_address, "
                                              "        ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, "\n"
                                              "        );\n"
                                              "      }\n"
                                              "    }\n"
                                              "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_OBJECT_CHECK_TYPE:
      {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                              "    void* array = ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t index = ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "    if (__builtin_expect(array == NULL, 0)) { \n"
                                              "      env->set_exception(env, env->new_string_nolen_raw(env, \"Array must not be undef\")); \n"
                                              "      exception_flag = 1;\n"
                                              "    } \n"
                                              "    else { \n"
                                              "      if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) { \n"
                                              "          env->set_exception(env, env->new_string_nolen_raw(env, \"Index is out of range\")); \n"
                                              "          exception_flag = 1;\n"
                                              "      } \n"
                                              "      else {\n"
                                              "        void** element_address = &((void**)((intptr_t)array + object_header_byte_size))[index];\n"
                                              "        void* object = ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "        int32_t can_assign = env->can_assign_array_element(env, array, object);\n"
                                              "        if (can_assign) {\n"
                                              "          SPVM_API_OBJECT_ASSIGN(element_address, object);\n"
                                              "        }\n"
                                              "        else {\n"
                                              "          void* exception = env->new_string_nolen_raw(env, \"Assigned element type is invalid\");\n"
                                              "          env->set_exception(env, exception);\n"
                                              "          exception_flag = 1;\n"
                                              "        }\n"
                                              "      }\n"
                                              "    }\n"
                                              "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_UNDEF:
      {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* array = ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t index = ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (__builtin_expect(");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " == NULL, 0)) { \n"
                                              "      env->set_exception(env, env->new_string_nolen_raw(env, \"Array must not be undef\")); \n"
                                              "      exception_flag = 1;\n"
                                              "    } \n"
                                              "    else { \n"
                                              "      if (__builtin_expect(");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, " < 0 || ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, "  >= *(int32_t*)((intptr_t)");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " + (intptr_t)env->object_length_offset), 0)) { \n"
                                              "        env->set_exception(env, env->new_string_nolen_raw(env, \"Index is out of range\")); \n"
                                              "        exception_flag = 1;\n"
                                              "      } \n"
                                              "      else {\n"
                                              "        void* object_address = &((void**)((intptr_t)array + object_header_byte_size))[index];\n"
                                              "        SPVM_API_OBJECT_ASSIGN(\n"
                                              "          object_address,\n"
                                              "          NULL"
                                              "        );\n"
                                              "      }\n"
                                              "    }\n"
                                              "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_BYTE: {
        int32_t fields_length = opcode->operand3;
        SPVM_PRECOMPILE_add_mulnum_array_store(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, opcode->operand1, opcode->operand2, fields_length);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_SHORT: {
        int32_t fields_length = opcode->operand3;
        SPVM_PRECOMPILE_add_mulnum_array_store(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, opcode->operand1, opcode->operand2, fields_length);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_INT: {
        int32_t fields_length = opcode->operand3;
        SPVM_PRECOMPILE_add_mulnum_array_store(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, opcode->operand2, fields_length);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_LONG: {
        int32_t fields_length = opcode->operand3;
        SPVM_PRECOMPILE_add_mulnum_array_store(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, opcode->operand2, fields_length);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_FLOAT: {
        int32_t fields_length = opcode->operand3;
        SPVM_PRECOMPILE_add_mulnum_array_store(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1, opcode->operand2, fields_length);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_DOUBLE: {
        int32_t fields_length = opcode->operand3;
        SPVM_PRECOMPILE_add_mulnum_array_store(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1, opcode->operand2, fields_length);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_FIELD_BYTE: {
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        SPVM_PRECOMPILE_add_mulnum_array_field_store(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, opcode->operand1, opcode->operand2, fields_length, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_FIELD_SHORT: {
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        SPVM_PRECOMPILE_add_mulnum_array_field_store(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, opcode->operand1, opcode->operand2, fields_length, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_FIELD_INT: {
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        SPVM_PRECOMPILE_add_mulnum_array_field_store(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, opcode->operand2, fields_length, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_FIELD_LONG: {
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        SPVM_PRECOMPILE_add_mulnum_array_field_store(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, opcode->operand2, fields_length, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_FIELD_FLOAT: {
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        SPVM_PRECOMPILE_add_mulnum_array_field_store(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1, opcode->operand2, fields_length, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_FIELD_DOUBLE: {
        int32_t fields_length = (opcode->operand3 & 0xFF) + 1;
        int32_t field_index = opcode->operand3 >> 8;
        SPVM_PRECOMPILE_add_mulnum_array_field_store(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1, opcode->operand2, fields_length, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_BYTE: {
        SPVM_PRECOMPILE_add_move(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_SHORT: {
        SPVM_PRECOMPILE_add_move(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_INT: {
        SPVM_PRECOMPILE_add_move(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_LONG: {
        SPVM_PRECOMPILE_add_move(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_FLOAT: {
        SPVM_PRECOMPILE_add_move(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_DOUBLE: {
        SPVM_PRECOMPILE_add_move(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_OBJECT: {
          SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_API_OBJECT_ASSIGN(&");
          SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
          SPVM_STRING_BUFFER_add(string_buffer, ", ");
          SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
          SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_OBJECT_CHECK_READ_ONLY: {
          SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                                "    void* string = ");
          SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                                "    if (env->is_read_only(env, string)) {\n"
                                                "      void* exception = env->new_string_nolen_raw(env, \"Read-only strings can't be converted to mutable strings.\");\n"
                                                "      env->set_exception(env, exception);\n"
                                                "      exception_flag = 1;\n"
                                                "    }\n"
                                                "    else {\n"
                                                "  SPVM_API_OBJECT_ASSIGN(&");
          SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
          SPVM_STRING_BUFFER_add(string_buffer, ", string);\n"
                                                "    }\n"
                                                "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_COPY: {
          SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                                "    void* object = ");
          SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                                "    if (object) {\n"
                                                "      if (!(env->is_string(env, object) || env->is_numeric_array(env, object) || env->is_mulnum_array(env, object))) {\n"
                                                "        void* exception = env->new_string_nolen_raw(env, \"The operand of the copy operator must be a string type, a numeric type, or a multi numeric type\");\n"
                                                "        env->set_exception(env, exception);\n"
                                                "        exception_flag = 1;\n"
                                                "      }\n"
                                                "      else {\n"
                                                "        void* new_object_raw = env->copy_raw(env, object);\n"
                                                "  SPVM_API_OBJECT_ASSIGN(&");
          SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
          SPVM_STRING_BUFFER_add(string_buffer, ", new_object_raw);\n"
                                                  "    }\n"
                                                  "  }\n"
                                                  "  else {\n"
                                                "      SPVM_API_OBJECT_ASSIGN(&");
          SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
          SPVM_STRING_BUFFER_add(string_buffer, ", NULL);\n"
                                                  "  }\n"
                                                "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_UNDEF: {
          SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_API_OBJECT_ASSIGN(&");
          SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
          SPVM_STRING_BUFFER_add(string_buffer, ", NULL);");
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_REF: {
        SPVM_PRECOMPILE_add_move(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_REF, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_MULNUM_BYTE: {
        int32_t fields_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_PRECOMPILE_add_operand_value(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_PRECOMPILE_add_operand_value(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand1, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        }
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_MULNUM_SHORT: {
        int32_t fields_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_PRECOMPILE_add_operand_value(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_PRECOMPILE_add_operand_value(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand1, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        }
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_MULNUM_INT: {
        int32_t fields_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_PRECOMPILE_add_operand_value(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_PRECOMPILE_add_operand_value(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        }
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_MULNUM_LONG: {
        int32_t fields_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_PRECOMPILE_add_operand_value(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_PRECOMPILE_add_operand_value(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        }
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_MULNUM_FLOAT: {
        int32_t fields_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_PRECOMPILE_add_operand_value(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_PRECOMPILE_add_operand_value(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand1, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        }
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_MULNUM_DOUBLE: {
        int32_t fields_length = opcode->operand2;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_PRECOMPILE_add_operand_value(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_PRECOMPILE_add_operand_value(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand1, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        }
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_BYTE: {
        int32_t field_index = opcode->operand2;
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_PRECOMPILE_add_operand_value(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand1, field_index);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_SHORT: {
        int32_t field_index = opcode->operand2;
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_PRECOMPILE_add_operand_value(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand1, field_index);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_INT: {
        int32_t field_index = opcode->operand2;
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_PRECOMPILE_add_operand_value(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1, field_index);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_LONG: {
        int32_t field_index = opcode->operand2;
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_PRECOMPILE_add_operand_value(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1, field_index);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_FLOAT: {
        int32_t field_index = opcode->operand2;
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_PRECOMPILE_add_operand_value(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand1, field_index);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_DOUBLE: {
        int32_t field_index = opcode->operand2;
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_PRECOMPILE_add_operand_value(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand1, field_index);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_BYTE: {
        int32_t field_index = opcode->operand2;
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_PRECOMPILE_add_operand_value(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, field_index);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_SHORT: {
        int32_t field_index = opcode->operand2;
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_PRECOMPILE_add_operand_value(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, field_index);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_INT: {
        int32_t field_index = opcode->operand2;
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_PRECOMPILE_add_operand_value(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, field_index);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_LONG: {
        int32_t field_index = opcode->operand2;
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_PRECOMPILE_add_operand_value(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, field_index);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_FLOAT: {
        int32_t field_index = opcode->operand2;
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_PRECOMPILE_add_operand_value(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, field_index);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_DOUBLE: {
        int32_t field_index = opcode->operand2;
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_PRECOMPILE_add_operand_value(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, field_index);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_MORTAL: {
        SPVM_STRING_BUFFER_add(string_buffer, "  mortal_stack[mortal_stack_top] = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "  mortal_stack_top++;\n");
        break;
      }
      case SPVM_OPCODE_C_ID_LEAVE_SCOPE: {
        int32_t original_mortal_stack_top = opcode->operand0;
        if (method_mortal_stack_length > 0) {
          SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                                "    int32_t original_mortal_stack_top = ");
          SPVM_STRING_BUFFER_add_int(string_buffer, original_mortal_stack_top);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                                "    {\n"
                                                "      int32_t mortal_stack_index;\n"
                                                "      for (mortal_stack_index = original_mortal_stack_top; mortal_stack_index < mortal_stack_top; mortal_stack_index++) {\n"
                                                "        int32_t var_index = mortal_stack[mortal_stack_index];\n"
                                                "        void** object_address = (void**)&object_vars[var_index];\n"
                                                "        if (*object_address != NULL) {\n"
                                                "          if (SPVM_API_GET_REF_COUNT(*object_address) > 1) { SPVM_API_DEC_REF_COUNT_ONLY(*object_address); }\n"
                                                "          else { env->dec_ref_count(env, *object_address); }\n"
                                                "          *object_address = NULL;\n"
                                                "        }\n"
                                                "      }\n"
                                                "    }\n"
                                                "    mortal_stack_top = original_mortal_stack_top;\n"
                                                "  }\n");
        }
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_OBJECT: {
        int32_t basic_type_id = opcode->operand1;
        int32_t basic_type_name_id = SPVM_API_RUNTIME_get_basic_type_name_id(env->runtime, basic_type_id);
        const char* basic_type_name = SPVM_API_RUNTIME_get_name(env->runtime, basic_type_name_id);

        SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                              "    int32_t access_basic_type_id = env->get_basic_type_id(env, \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n"
                                              "    if (access_basic_type_id < 0) {\n"
                                              "      void* exception = env->new_string_nolen_raw(env, \"Basic type not found:");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, ":New object\");\n"
                                              "      env->set_exception(env, exception);\n"
                                              "      exception_flag = 1;\n"
                                              "    }\n"
                                              "    if (!exception_flag) {\n"
                                              "      int32_t basic_type_id = access_basic_type_id;\n"
                                              "      void* object = env->new_object_raw(env, basic_type_id);\n"
                                              "      if (object == NULL) {\n"
                                              "        void* exception = env->new_string_nolen_raw(env, \"Can't allocate memory for object\");\n"
                                              "        env->set_exception(env, exception);\n"
                                              "        exception_flag = 1;\n"
                                              "      }\n"
                                              "      else {\n"
                                              "        SPVM_API_OBJECT_ASSIGN(&");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object);\n"
                                              "      }\n"
                                              "    }\n"
                                              "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_BYTE_ARRAY: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                              "    int32_t length = *(int32_t*)&");
        SPVM_PRECOMPILE_add_var(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "    if (length >= 0) {\n"
                                              "      void* object = env->new_byte_array_raw(env, length);\n"
                                              "      if (object == NULL) {\n"
                                              "        void* exception = env->new_string_nolen_raw(env, \"Can't allocate memory for byte array\");\n"
                                              "        env->set_exception(env, exception);\n"
                                              "        exception_flag = 1;\n"
                                              "      }\n"
                                              "      else {\n"
                                              "        SPVM_API_OBJECT_ASSIGN((void**)&");
        SPVM_PRECOMPILE_add_var(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object);\n"
                                              "      }\n"
                                              "    }\n"
                                              "    else {\n"
                                              "      void* exception = env->new_string_nolen_raw(env, \"Array length must be more than or equal to 0\");\n"
                                              "      env->set_exception(env, exception);\n"
                                              "      exception_flag = 1;\n"
                                              "    }\n"
                                              "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_SHORT_ARRAY: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                              "    int32_t length = *(int32_t*)&");
        SPVM_PRECOMPILE_add_var(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "    if (length >= 0) {\n"
                                              "      void* object = env->new_short_array_raw(env, length);\n"
                                              "      if (object == NULL) {\n"
                                              "        void* exception = env->new_string_nolen_raw(env, \"Can't allocate memory for short array\");\n"
                                              "        env->set_exception(env, exception);\n"
                                              "        exception_flag = 1;\n"
                                              "      }\n"
                                              "      else {\n"
                                              "        SPVM_API_OBJECT_ASSIGN((void**)&");
        SPVM_PRECOMPILE_add_var(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object);\n"
                                              "      }\n"
                                              "    }\n"
                                              "    else {\n"
                                              "      void* exception = env->new_string_nolen_raw(env, \"Array length must be more than or equal to 0\");\n"
                                              "      env->set_exception(env, exception);\n"
                                              "      exception_flag = 1;\n"
                                              "    }\n"
                                              "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_INT_ARRAY: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                              "    int32_t length = *(int32_t*)&");
        SPVM_PRECOMPILE_add_var(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "    if (length >= 0) {\n"
                                              "      void* object = env->new_int_array_raw(env, length);\n"
                                              "      if (object == NULL) {\n"
                                              "        void* exception = env->new_string_nolen_raw(env, \"Can't allocate memory for int array\");\n"
                                              "        env->set_exception(env, exception);\n"
                                              "        exception_flag = 1;\n"
                                              "      }\n"
                                              "      else {\n"
                                              "        SPVM_API_OBJECT_ASSIGN((void**)&");
        SPVM_PRECOMPILE_add_var(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object);\n"
                                              "      }\n"
                                              "    }\n"
                                              "    else {\n"
                                              "      void* exception = env->new_string_nolen_raw(env, \"Array length must be more than or equal to 0\");\n"
                                              "      env->set_exception(env, exception);\n"
                                              "      exception_flag = 1;\n"
                                              "    }\n"
                                              "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_LONG_ARRAY: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                              "    int32_t length = *(int32_t*)&");
        SPVM_PRECOMPILE_add_var(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "    if (length >= 0) {\n"
                                              "      void* object = env->new_long_array_raw(env, length);\n"
                                              "      if (object == NULL) {\n"
                                              "        void* exception = env->new_string_nolen_raw(env, \"Can't allocate memory for long array\");\n"
                                              "        env->set_exception(env, exception);\n"
                                              "        exception_flag = 1;\n"
                                              "      }\n"
                                              "      else {\n"
                                              "        SPVM_API_OBJECT_ASSIGN((void**)&");
        SPVM_PRECOMPILE_add_var(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object);\n"
                                              "      }\n"
                                              "    }\n"
                                              "    else {\n"
                                              "      void* exception = env->new_string_nolen_raw(env, \"Array length must be more than or equal to 0\");\n"
                                              "      env->set_exception(env, exception);\n"
                                              "      exception_flag = 1;\n"
                                              "    }\n"
                                              "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_FLOAT_ARRAY: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                              "    int32_t length = *(int32_t*)&");
        SPVM_PRECOMPILE_add_var(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "    if (length >= 0) {\n"
                                              "      void* object = env->new_float_array_raw(env, length);\n"
                                              "      if (object == NULL) {\n"
                                              "        void* exception = env->new_string_nolen_raw(env, \"Can't allocate memory for float array\");\n"
                                              "        env->set_exception(env, exception);\n"
                                              "        exception_flag = 1;\n"
                                              "      }\n"
                                              "      else {\n"
                                              "        SPVM_API_OBJECT_ASSIGN((void**)&");
        SPVM_PRECOMPILE_add_var(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object);\n"
                                              "      }\n"
                                              "    }\n"
                                              "    else {\n"
                                              "      void* exception = env->new_string_nolen_raw(env, \"Array length must be more than or equal to 0\");\n"
                                              "      env->set_exception(env, exception);\n"
                                              "      exception_flag = 1;\n"
                                              "    }\n"
                                              "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_DOUBLE_ARRAY: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                              "    int32_t length = *(int32_t*)&");
        SPVM_PRECOMPILE_add_var(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "    if (length >= 0) {\n"
                                              "      void* object = env->new_double_array_raw(env, length);\n"
                                              "      if (object == NULL) {\n"
                                              "        void* exception = env->new_string_nolen_raw(env, \"Can't allocate memory for double array\");\n"
                                              "        env->set_exception(env, exception);\n"
                                              "        exception_flag = 1;\n"
                                              "      }\n"
                                              "      else {\n"
                                              "        SPVM_API_OBJECT_ASSIGN((void**)&");
        SPVM_PRECOMPILE_add_var(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object);\n"
                                              "      }\n"
                                              "    }\n"
                                              "    else {\n"
                                              "      void* exception = env->new_string_nolen_raw(env, \"Array length must be more than or equal to 0\");\n"
                                              "      env->set_exception(env, exception);\n"
                                              "      exception_flag = 1;\n"
                                              "    }\n"
                                              "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_OBJECT_ARRAY: {
        int32_t basic_type_id = opcode->operand1;
        int32_t basic_type_name_id = SPVM_API_RUNTIME_get_basic_type_name_id(env->runtime, basic_type_id);
        const char* basic_type_name = SPVM_API_RUNTIME_get_name(env->runtime, basic_type_name_id);

        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t access_basic_type_id = env->get_basic_type_id(env, \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (");
        SPVM_STRING_BUFFER_add(string_buffer, "access_basic_type_id");
        SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* exception = env->new_string_nolen_raw(env, \"Basic type not found:");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, ":New object array\");\n"
                                              "      env->set_exception(env, exception);\n"
                                              "      exception_flag = 1;\n"
                                              "    }\n"
                                              "    if (!exception_flag) {\n"
                                              "      int32_t basic_type_id = "
                                              "access_basic_type_id"
                                              ";\n"
                                              "      int32_t length = *(int32_t*)&");
        SPVM_PRECOMPILE_add_var(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "      if (length >= 0) {\n"
                                              "        void* object = env->new_object_array_raw(env, basic_type_id, length);\n"
                                              "        if (object == NULL) {\n"
                                              "          void* exception = env->new_string_nolen_raw(env, \"Can't allocate memory for object array\");\n"
                                              "          env->set_exception(env, exception);\n"
                                              "          exception_flag = 1;\n"
                                              "        }\n"
                                              "        else {\n"
                                              "          SPVM_API_OBJECT_ASSIGN((void**)&");
        SPVM_PRECOMPILE_add_var(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object);\n"
                                              "        }\n"
                                              "      }\n"
                                              "      else {\n"
                                              "        void* exception = env->new_string_nolen_raw(env, \"Array length must be more than or equal to 0\");\n"
                                              "        env->set_exception(env, exception);\n"
                                              "        exception_flag = 1;\n"
                                              "      }\n"
                                              "    }\n"
                                              "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_MULTI_ARRAY: {
        int32_t basic_type_id = opcode->operand1;
        int32_t basic_type_name_id = SPVM_API_RUNTIME_get_basic_type_name_id(env->runtime, basic_type_id);
        const char* basic_type_name = SPVM_API_RUNTIME_get_name(env->runtime, basic_type_name_id);
        int32_t element_dimension = opcode->operand3;
        
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                              "    int32_t access_basic_type_id = env->get_basic_type_id(env, \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n"
                                              "    if (access_basic_type_id < 0) {\n"
                                              "      void* exception = env->new_string_nolen_raw(env, \"Basic type not found:");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, ":New multi dimentional array\");\n"
                                              "      env->set_exception(env, exception);\n"
                                              "      exception_flag = 1;\n"
                                              "    }\n"
                                              "    if (!exception_flag) {\n"
                                              "      int32_t basic_type_id = "
                                              "access_basic_type_id"
                                              ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      int32_t length = *(int32_t*)&");
        SPVM_PRECOMPILE_add_var(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "      if (length >= 0) {\n"
                                              "        void* object = env->new_muldim_array_raw(env, basic_type_id, ");
        SPVM_STRING_BUFFER_add_int(string_buffer, element_dimension);
        SPVM_STRING_BUFFER_add(string_buffer, ", length);\n"
                                              "        if (object == NULL) {\n"
                                              "          void* exception = env->new_string_nolen_raw(env, \"Can't allocate memory for multi dimention array\");\n"
                                              "          env->set_exception(env, exception);\n"
                                              "          exception_flag = 1;\n"
                                              "        }\n"
                                              "        else {\n"
                                              "          SPVM_API_OBJECT_ASSIGN((void**)&");
        SPVM_PRECOMPILE_add_var(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object);\n"
                                              "        }\n"
                                              "      }\n"
                                              "      else {\n"
                                              "        void* exception = env->new_string_nolen_raw(env, \"Array length must be more than or equal to 0\");\n"
                                              "        env->set_exception(env, exception);\n"
                                              "        exception_flag = 1;\n"
                                              "      }\n"
                                              "    }\n"
                                              "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_MULNUM_ARRAY: {
        int32_t basic_type_id = opcode->operand1;
        int32_t basic_type_name_id = SPVM_API_RUNTIME_get_basic_type_name_id(env->runtime, basic_type_id);
        const char* basic_type_name = SPVM_API_RUNTIME_get_name(env->runtime, basic_type_name_id);

        SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                              "    int32_t access_basic_type_id = env->get_basic_type_id(env, \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n"
                                              "    if (access_basic_type_id < 0) {\n"
                                              "      void* exception = env->new_string_nolen_raw(env, \"Basic type not found:");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, "New multi numeric array\");\n"
                                              "      env->set_exception(env, exception);\n"
                                              "      exception_flag = 1;\n"
                                              "    }\n"
                                              "    if (!exception_flag) {\n"
                                              "      int32_t basic_type_id = "
                                              "access_basic_type_id"
                                              ";\n"
                                              "      int32_t length = *(int32_t*)&");
        SPVM_PRECOMPILE_add_var(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "      if (length >= 0) {\n"
                                              "        void* object = env->new_mulnum_array_raw(env, basic_type_id, length);\n"
                                              "        if (object == NULL) {\n"
                                              "          void* exception = env->new_string_nolen_raw(env, \"Can't allocate memory for multi dimention array\");\n"
                                              "          env->set_exception(env, exception);\n"
                                              "          exception_flag = 1;\n"
                                              "        }\n"
                                              "        else {\n"
                                              "          SPVM_API_OBJECT_ASSIGN((void**)&");
        SPVM_PRECOMPILE_add_var(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object);\n"
                                              "        }\n"
                                              "      }\n"
                                              "      else {\n"
                                              "        void* exception = env->new_string_nolen_raw(env, \"Array length must be more than or equal to 0\");\n"
                                              "        env->set_exception(env, exception);\n"
                                              "        exception_flag = 1;\n"
                                              "      }\n"
                                              "    }\n"
                                              "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_STRING: {
        int32_t constant_string_id = opcode->operand1;
        
        int32_t constant_string_length;
        const char* constant_string_value = SPVM_API_RUNTIME_get_constant_string_value(env->runtime, constant_string_id, &constant_string_length);

        SPVM_STRING_BUFFER_add(string_buffer,
          "  {\n"
          "    void* string = env->new_string_raw(env, \""
        );
        for (int32_t i = 0; i < constant_string_length; i++) {
          SPVM_STRING_BUFFER_add_hex_char(string_buffer, constant_string_value[i]);
        }
        SPVM_STRING_BUFFER_add(string_buffer,
          "\", "
        );
        SPVM_STRING_BUFFER_add_int(string_buffer, constant_string_length);
        SPVM_STRING_BUFFER_add(string_buffer,
          ");\n"
          "    if (string == NULL) {\n"
          "      void* exception = env->new_string_nolen_raw(env, \"Can't allocate memory for string\");\n"
          "      env->set_exception(env, exception);\n"
          "      exception_flag = 1;\n"
          "    }\n"
          "    else {\n"
          "      env->make_read_only(env, string);\n"
          "      SPVM_API_OBJECT_ASSIGN(&"
        );
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer,
          ", string);\n"
          "    }\n"
          "  }\n"
        );

        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_LENGTH: {
        SPVM_STRING_BUFFER_add(string_buffer, "  if (");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, " == NULL) {\n"
                                              "    env->set_exception(env, env->new_string_nolen_raw(env, \"Can't get array length of undef value.\"));\n"
                                              "    exception_flag = 1;\n"
                                              "  }\n"
                                              "  else {\n"
                                              "    ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = *(int32_t*)((intptr_t)");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, " + (intptr_t)env->object_length_offset);\n"
                                              "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_IS_READ_ONLY: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                              "    void* string = ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "    int32_t is_read_only = env->is_read_only(env, string);\n");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, 0);
        SPVM_STRING_BUFFER_add(string_buffer, " = is_read_only;\n"
                                              "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_WEAKEN_FIELD: {
        int32_t field_id = opcode->operand1;
        
        int32_t field_class_id = SPVM_API_RUNTIME_get_field_class_id(env->runtime, field_id);
        int32_t field_class_name_id = SPVM_API_RUNTIME_get_class_name_id(env->runtime, field_class_id);
        const char* field_class_name = SPVM_API_RUNTIME_get_name(env->runtime, field_class_name_id);
        int32_t field_name_id = SPVM_API_RUNTIME_get_field_name_id(env->runtime, field_id);
        const char* field_name = SPVM_API_RUNTIME_get_name(env->runtime, field_name_id);
        int32_t field_signature_id = SPVM_API_RUNTIME_get_field_signature_id(env->runtime, field_id);
        const char* field_signature = SPVM_API_RUNTIME_get_name(env->runtime, field_signature_id);

        SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                              "    int32_t access_field_id = env->get_field_id(env, \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_class_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_signature);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n"
                                              "    if (access_field_id < 0) {\n"
                                              "      void* exception = env->new_string_nolen_raw(env, \"Field not found ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_class_name);
        SPVM_STRING_BUFFER_add(string_buffer, " ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n"
                                              "      env->set_exception(env, exception);\n"
                                              "      exception_flag = 1;\n"
                                              "    }\n"
                                              "    if (!exception_flag) {\n"
                                              "      int32_t access_field_offset = env->get_field_offset(env, access_field_id);\n"
                                              "      void* object = ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "      if (object == NULL) {\n"
                                              "        void* exception = env->new_string_nolen_raw(env, \"Object to weaken an object field must not be undefined.\");\n"
                                              "        env->set_exception(env, exception);\n"
                                              "        exception_flag = 1;\n"
                                              "      }\n"
                                              "      else {\n"
                                              "        void** get_field_object_address = (void**)((intptr_t)object + object_header_byte_size + access_field_offset);\n"
                                              "        int32_t status = env->weaken(env, get_field_object_address);\n"
                                              "        if (status != 0) {\n"
                                              "          void* exception = env->new_string_nolen_raw(env, \"Can't allocate memory for weaken back reference\");\n"
                                              "          env->set_exception(env, exception);\n"
                                              "          exception_flag = 1;\n"
                                              "        }\n"
                                              "      }\n"
                                              "    }\n"
                                              "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_UNWEAKEN_FIELD: {
        int32_t field_id = opcode->operand1;
        
        int32_t field_class_id = SPVM_API_RUNTIME_get_field_class_id(env->runtime, field_id);
        int32_t field_class_name_id = SPVM_API_RUNTIME_get_class_name_id(env->runtime, field_class_id);
        const char* field_class_name = SPVM_API_RUNTIME_get_name(env->runtime, field_class_name_id);
        int32_t field_name_id = SPVM_API_RUNTIME_get_field_name_id(env->runtime, field_id);
        const char* field_name = SPVM_API_RUNTIME_get_name(env->runtime, field_name_id);
        int32_t field_signature_id = SPVM_API_RUNTIME_get_field_signature_id(env->runtime, field_id);
        const char* field_signature = SPVM_API_RUNTIME_get_name(env->runtime, field_signature_id);

        SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                              "    int32_t access_field_id = env->get_field_id(env, \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_class_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_signature);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n"
                                              "    if (access_field_id < 0) {\n"
                                              "      void* exception = env->new_string_nolen_raw(env, \"Field not found ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_class_name);
        SPVM_STRING_BUFFER_add(string_buffer, " ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n"
                                              "      env->set_exception(env, exception);\n"
                                              "      exception_flag = 1;\n"
                                              "    }\n"
                                              "    if (!exception_flag) {\n"
                                              "      int32_t access_field_offset"
                                              " = env->get_field_offset(env, "
                                              "access_field_id"
                                              ");\n"
                                              "      void* object = ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "      if (object == NULL) {\n"
                                              "        void* exception = env->new_string_nolen_raw(env, \"Object to weaken an object field must not be undefined.\");\n"
                                              "        env->set_exception(env, exception);\n"
                                              "        exception_flag = 1;\n"
                                              "      }\n"
                                              "      else {\n"
                                              "        void** get_field_object_address = (void**)((intptr_t)object + object_header_byte_size + access_field_offset);\n"
                                              "        env->unweaken(env, get_field_object_address);\n"
                                              "      }\n"
                                              "    }\n"
                                              "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_ISWEAK_FIELD: {
        int32_t field_id = opcode->operand2;
        
        int32_t field_class_id = SPVM_API_RUNTIME_get_field_class_id(env->runtime, field_id);
        int32_t field_class_name_id = SPVM_API_RUNTIME_get_class_name_id(env->runtime, field_class_id);
        const char* field_class_name = SPVM_API_RUNTIME_get_name(env->runtime, field_class_name_id);
        int32_t field_name_id = SPVM_API_RUNTIME_get_field_name_id(env->runtime, field_id);
        const char* field_name = SPVM_API_RUNTIME_get_name(env->runtime, field_name_id);
        int32_t field_signature_id = SPVM_API_RUNTIME_get_field_signature_id(env->runtime, field_id);
        const char* field_signature = SPVM_API_RUNTIME_get_name(env->runtime, field_signature_id);

        SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                              "    int32_t access_field_id = env->get_field_id(env, \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_class_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_signature);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n"
                                              "    if (access_field_id < 0) {\n"
                                              "      void* exception = env->new_string_nolen_raw(env, \"Field not found ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_class_name);
        SPVM_STRING_BUFFER_add(string_buffer, " ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n"
                                              "      env->set_exception(env, exception);\n"
                                              "      exception_flag = 1;\n"
                                              "    }\n"
                                              "    if (!exception_flag) {\n"
                                              "      int32_t access_field_offset = env->get_field_offset(env, access_field_id);\n"
                                              "      void* object = ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "      if (object == NULL) {\n"
                                              "        void* exception = env->new_string_nolen_raw(env, \"Object to weaken an object field must not be undefined.\");\n"
                                              "        env->set_exception(env, exception);\n"
                                              "        exception_flag = 1;\n"
                                              "      }\n"
                                              "      else {\n"
                                              "        void** get_field_object_address = (void**)((intptr_t)object + object_header_byte_size + "
                                              "access_field_offset"
                                              ");\n");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, 0);
        SPVM_STRING_BUFFER_add(string_buffer, " = env->isweak(env, get_field_object_address);\n"
                                              "      }\n"
                                              "    }\n"
                                              "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_REFCNT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                              "    void* object = ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (object == NULL) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = 0;\n"
                                              "    }\n"
                                              "    else {\n"
                                              "      ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, "    = env->get_ref_count(env, object);\n"
                                              "    }\n"
                                              "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_CONCAT:
      {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                              "    void* string1 = ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "    void* string2 = ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "    if (string1 == NULL) {\n"
                                              "      void* exception = env->new_string_nolen_raw(env, \"\\\".\\\" operater left value must be defined\");\n"
                                              "      env->set_exception(env, exception);\n"
                                              "      exception_flag = 1;\n"
                                              "    }\n"
                                              "    else if (string2 == NULL) {\n"
                                              "      void* exception = env->new_string_nolen_raw(env, \"\\\".\\\" operater right value must be defined\");\n"
                                              "      env->set_exception(env, exception);\n"
                                              "      exception_flag = 1;\n"
                                              "    }\n"
                                              "    else {\n"
                                              "      void* string3 = env->concat_raw(env, string1, string2);\n"
                                              "      SPVM_API_OBJECT_ASSIGN(&");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", string3);\n"
                                              "    }\n"
                                              "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_REFOP: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                              "    void* object = ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "    if (object == NULL) {\n"
                                              "      ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = NULL;\n"
                                              "    }\n"
                                              "    else {\n"
                                              "      void* type_name = env->get_type_name_raw(env, object);\n"
                                              "      SPVM_API_OBJECT_ASSIGN(&");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", type_name);\n"
                                              "    }\n"
                                              "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_DUMP: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                              "    void* object = ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "    void* dump = env->dump_raw(env, object);\n"
                                              "    SPVM_API_OBJECT_ASSIGN(&");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", dump);\n"
                                              "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_STRING_LEN: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                              "    int32_t length = *(int32_t*)&");
        SPVM_PRECOMPILE_add_var(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "    if (length >= 0) {\n"
                                              "      void* object = env->new_string_raw(env, NULL, length);\n"
                                              "      if (object == NULL) {\n"
                                              "        void* exception = env->new_string_nolen_raw(env, \"The new_string_len operator can't allocate enough memory\");\n"
                                              "        env->set_exception(env, exception);\n"
                                              "        exception_flag = 1;\n"
                                              "      }\n"
                                              "      else {\n"
                                              "        SPVM_API_OBJECT_ASSIGN((void**)&");
        SPVM_PRECOMPILE_add_var(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object);\n"
                                              "      }\n"
                                              "    }\n"
                                              "    else {\n"
                                              "      void* exception = env->new_string_nolen_raw(env, \"The length of the new_string_len operator must be a positive number\");\n"
                                              "      env->set_exception(env, exception);\n"
                                              "      exception_flag = 1;\n"
                                              "    }\n"
                                              "  }\n");
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
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, 0);
        SPVM_STRING_BUFFER_add(string_buffer, " == 0) { goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, "; }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_IF_NE_ZERO: {
        SPVM_STRING_BUFFER_add(string_buffer, "  if (");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, 0);
        SPVM_STRING_BUFFER_add(string_buffer, ") { goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, "; }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_BYTE:
      {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_PRECOMPILE_add_stack(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, stack_index);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        stack_index++;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_SHORT:
      {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_PRECOMPILE_add_stack(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, stack_index);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        stack_index++;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_INT:
      {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_PRECOMPILE_add_stack(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, stack_index);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        stack_index++;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_LONG:
      {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_PRECOMPILE_add_stack(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, stack_index);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        stack_index++;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_FLOAT:
      {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_PRECOMPILE_add_stack(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, stack_index);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        stack_index++;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_DOUBLE:
      {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_PRECOMPILE_add_stack(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, stack_index);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        stack_index++;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_OBJECT:
      {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_PRECOMPILE_add_stack(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, stack_index);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        stack_index++;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_REF:
      {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_PRECOMPILE_add_stack(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_REF, stack_index);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_REF, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        stack_index++;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_UNDEF:
      {
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_PRECOMPILE_add_stack(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, stack_index);
        SPVM_STRING_BUFFER_add(string_buffer, " = NULL;\n");
        stack_index++;
        
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_MULNUM_BYTE: {
        int32_t fields_length = opcode->operand1;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_PRECOMPILE_add_stack(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, stack_index + field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_PRECOMPILE_add_operand_value(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        }
        stack_index += fields_length;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_MULNUM_SHORT: {
        int32_t fields_length = opcode->operand1;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_PRECOMPILE_add_stack(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, stack_index + field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_PRECOMPILE_add_operand_value(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        }
        stack_index += fields_length;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_MULNUM_INT: {
        int32_t fields_length = opcode->operand1;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_PRECOMPILE_add_stack(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, stack_index + field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_PRECOMPILE_add_operand_value(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        }
        stack_index += fields_length;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_MULNUM_LONG: {
        int32_t fields_length = opcode->operand1;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_PRECOMPILE_add_stack(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, stack_index + field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_PRECOMPILE_add_operand_value(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        }
        stack_index += fields_length;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_MULNUM_FLOAT: {
        int32_t fields_length = opcode->operand1;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_PRECOMPILE_add_stack(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, stack_index + field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_PRECOMPILE_add_operand_value(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        }
        stack_index += fields_length;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_MULNUM_DOUBLE: {
        int32_t fields_length = opcode->operand1;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_PRECOMPILE_add_stack(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, stack_index + field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_PRECOMPILE_add_operand_value(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        }
        stack_index += fields_length;
        break;
      }
      case SPVM_OPCODE_C_ID_CHECK_OBJECT_TYPE: {
        int32_t check_basic_type_id = opcode->operand2;
        int32_t check_type_dimension = opcode->operand3;

        int32_t cast_basic_type_name_id = SPVM_API_RUNTIME_get_basic_type_name_id(env->runtime, check_basic_type_id);
        const char* cast_basic_type_name = SPVM_API_RUNTIME_get_name(env->runtime, cast_basic_type_name_id);
        
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                              "    int32_t access_basic_type_id = env->get_basic_type_id(env, \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)cast_basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n"
                                              "    if (access_basic_type_id < 0) {\n"
                                              "        void* exception = env->new_string_nolen_raw(env, \"Basic type not found:");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)cast_basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, "Checking object type\");\n"
                                              "      env->set_exception(env, exception);\n"
                                              "      exception_flag = 1;\n"
                                              "    }\n"
                                              "    if (!exception_flag) {\n"
                                              "      int32_t check_basic_type_id = access_basic_type_id;\n"
                                              "      int32_t check_type_dimension = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, check_type_dimension);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* object = ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "      if (object != NULL) {\n"
                                              "        int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_offset);\n"
                                              "        int32_t object_type_dimension_id = *(uint8_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_offset);\n"
                                              "        if (object_basic_type_id == check_basic_type_id && object_type_dimension_id == check_type_dimension) {\n"
                                              "          SPVM_API_OBJECT_ASSIGN(&");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n"
                                              "        }\n"
                                              "        else {\n"
                                              "          void* exception = env->new_string_nolen_raw(env, \"Can't cast uncompatible type.\");\n"
                                              "          env->set_exception(env, exception);\n"
                                              "          exception_flag = 1;\n"
                                              "        }\n"
                                              "      }\n"
                                              "    }\n"
                                              "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_CHECK_CALLBACK: {
        int32_t check_basic_type_id = opcode->operand2;

        int32_t cast_basic_type_name_id = SPVM_API_RUNTIME_get_basic_type_name_id(env->runtime, check_basic_type_id);
        const char* cast_basic_type_name = SPVM_API_RUNTIME_get_name(env->runtime, cast_basic_type_name_id);
        
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                              "    int32_t access_basic_type_id = env->get_basic_type_id(env, \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)cast_basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n"
                                              "    if (access_basic_type_id < 0) {\n"
                                              "        void* exception = env->new_string_nolen_raw(env, \"Basic type not found:");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)cast_basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, ":Checking callback\");\n"
                                              "      env->set_exception(env, exception);\n"
                                              "      exception_flag = 1;\n"
                                              "    }\n"
                                              "    if (!exception_flag) {\n"
                                              "      int32_t callback_basic_type_id = "
                                              "access_basic_type_id"
                                              ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "      void* object = ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "      if (object != NULL) {\n"
                                              "        int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_offset);\n"
                                              "        if (env->has_callback(env, object, callback_basic_type_id)) {\n"
                                              "          SPVM_API_OBJECT_ASSIGN(&");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n"
                                              "        }\n"
                                              "        else {\n"
                                              "          void* exception = env->new_string_nolen_raw(env, \"Can't cast uncompatible type.\");\n"
                                              "          env->set_exception(env, exception);\n"
                                              "          exception_flag = 1;\n"
                                              "        }\n"
                                              "      }\n"
                                              "    }\n"
                                              "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_CHECK_INTERFACE: {
        int32_t check_basic_type_id = opcode->operand2;

        int32_t cast_basic_type_name_id = SPVM_API_RUNTIME_get_basic_type_name_id(env->runtime, check_basic_type_id);
        const char* cast_basic_type_name = SPVM_API_RUNTIME_get_name(env->runtime, cast_basic_type_name_id);
        
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                              "    int32_t access_basic_type_id = env->get_basic_type_id(env, \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)cast_basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    if (access_basic_type_id < 0) {\n"
                                              "      void* exception = env->new_string_nolen_raw(env, \"Basic type not found:");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)cast_basic_type_name);
        SPVM_STRING_BUFFER_add(string_buffer, ":Checking interface\");\n"
                                              "      env->set_exception(env, exception);\n"
                                              "      exception_flag = 1;\n"
                                              "    }\n"
                                              "    if (!exception_flag) {\n"
                                              "      int32_t interface_basic_type_id = "
                                              "access_basic_type_id"
                                              ";\n"
                                              "      void* object = ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "      if (object != NULL) {\n"
                                              "        int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_offset);\n"
                                              "        if (env->has_interface(env, object, interface_basic_type_id)) {\n"
                                              "          SPVM_API_OBJECT_ASSIGN(&");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n"
                                              "        }\n"
                                              "        else {\n"
                                              "          void* exception = env->new_string_nolen_raw(env, \"Can't cast uncompatible type.\");\n"
                                              "          env->set_exception(env, exception);\n"
                                              "          exception_flag = 1;\n"
                                              "        }\n"
                                              "      }\n"
                                              "    }\n"
                                              "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_CLASS_METHOD_BY_ID:
      case SPVM_OPCODE_C_ID_CALL_INSTANCE_METHOD_BY_ID:
      case SPVM_OPCODE_C_ID_CALL_INSTANCE_METHOD_BY_SIGNATURE:
      {
        int32_t var_id = opcode->operand0;
        int32_t decl_method_id = opcode->operand1;

        int32_t decl_method_name_id = SPVM_API_RUNTIME_get_method_name_id(env->runtime, decl_method_id);
        const char* decl_method_name = SPVM_API_RUNTIME_get_name(env->runtime, decl_method_name_id);
        int32_t decl_method_signature_id = SPVM_API_RUNTIME_get_method_signature_id(env->runtime, decl_method_id);
        const char* decl_method_signature = SPVM_API_RUNTIME_get_name(env->runtime, decl_method_signature_id);
        int32_t decl_method_class_id = SPVM_API_RUNTIME_get_method_class_id(env->runtime, decl_method_id);
        int32_t decl_method_class_name_id = SPVM_API_RUNTIME_get_class_name_id(env->runtime, decl_method_class_id);
        const char* decl_method_class_name = SPVM_API_RUNTIME_get_name(env->runtime, decl_method_class_name_id);
        int32_t decl_method_has_precompile_flag = SPVM_API_RUNTIME_get_method_has_precompile_flag(env->runtime, decl_method_id);
        int32_t decl_method_return_type_id = SPVM_API_RUNTIME_get_method_return_type_id(env->runtime, decl_method_id);
        int32_t decl_method_return_type_dimension = SPVM_API_RUNTIME_get_type_dimension(env->runtime, decl_method_return_type_id);
        int32_t decl_method_return_basic_type_id = SPVM_API_RUNTIME_get_type_basic_type_id(env->runtime, decl_method_return_type_id);
        int32_t decl_method_return_basic_type_category = SPVM_API_RUNTIME_get_basic_type_category(env->runtime, decl_method_return_basic_type_id);
        
        SPVM_STRING_BUFFER_add(string_buffer, "  // ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)decl_method_class_name);
        SPVM_STRING_BUFFER_add(string_buffer, "->");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)decl_method_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\n"
                                              "  {\n");
        
        // Method inline expantion in same class
        if (decl_method_class_id == class_id && decl_method_has_precompile_flag) {
          
          SPVM_STRING_BUFFER_add(string_buffer, "    exception_flag = SPVMPRECOMPILE__");
          SPVM_STRING_BUFFER_add(string_buffer, (char*)decl_method_class_name);
          SPVM_STRING_BUFFER_add(string_buffer, (char*)"__");
          SPVM_STRING_BUFFER_add(string_buffer, (char*)decl_method_name);
          {
            int32_t index = string_buffer->length - (strlen(decl_method_class_name) + 2 + strlen(decl_method_name));
            
            while (index < string_buffer->length) {
              if (string_buffer->value[index] == ':') {
                string_buffer->value[index] = '_';
              }
              index++;
            }
          }
          SPVM_STRING_BUFFER_add(string_buffer, "(env, stack);\n");
        }
        // Call method
        else {
          switch (opcode_id) {
            case SPVM_OPCODE_C_ID_CALL_CLASS_METHOD_BY_ID: {
              SPVM_STRING_BUFFER_add(string_buffer, "    int32_t access_method_id = env->get_class_method_id(env, \"");
              SPVM_STRING_BUFFER_add(string_buffer, (char*)decl_method_class_name);
              SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
              SPVM_STRING_BUFFER_add(string_buffer, (char*)decl_method_name);
              SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
              SPVM_STRING_BUFFER_add(string_buffer, (char*)decl_method_signature);
              SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
              SPVM_STRING_BUFFER_add(string_buffer, "    int32_t call_method_id = access_method_id;\n");
              
              break;
            }
            case SPVM_OPCODE_C_ID_CALL_INSTANCE_METHOD_BY_ID: {
              SPVM_STRING_BUFFER_add(string_buffer, "    int32_t access_method_id = env->get_instance_method_id_static(env, \"");
              SPVM_STRING_BUFFER_add(string_buffer, (char*)decl_method_class_name);
              SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
              SPVM_STRING_BUFFER_add(string_buffer, (char*)decl_method_name);
              SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
              SPVM_STRING_BUFFER_add(string_buffer, (char*)decl_method_signature);
              SPVM_STRING_BUFFER_add(string_buffer, "\");\n"
                                                    "    int32_t call_method_id = access_method_id;\n");
              
              break;
            }
            case SPVM_OPCODE_C_ID_CALL_INSTANCE_METHOD_BY_SIGNATURE: {
              SPVM_STRING_BUFFER_add(string_buffer, "    void* object = stack[0].oval;\n"
                                                    "    int32_t call_method_id = env->get_instance_method_id(env, object, \"");
              SPVM_STRING_BUFFER_add(string_buffer, (char*)decl_method_name);
              SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
              SPVM_STRING_BUFFER_add(string_buffer, (char*)decl_method_signature);
              SPVM_STRING_BUFFER_add(string_buffer, "\");\n");
              
              break;
            }
            default: {
              assert(0);
            }
          }
          

          SPVM_STRING_BUFFER_add(string_buffer, "    if (call_method_id < 0) {\n"
                                                "      void* exception = env->new_string_nolen_raw(env, \"Can't find the \\\"");
          SPVM_STRING_BUFFER_add(string_buffer, (char*)decl_method_name);
          SPVM_STRING_BUFFER_add(string_buffer, "\\\" method with the signature \\\"");
          SPVM_STRING_BUFFER_add(string_buffer, (char*)decl_method_signature);
          SPVM_STRING_BUFFER_add(string_buffer, "\\\" that is declared in \\\"");
          SPVM_STRING_BUFFER_add(string_buffer, (char*)decl_method_class_name);
          SPVM_STRING_BUFFER_add(string_buffer, "\\\"\");\n"
                                                "      env->set_exception(env, exception);"
                                                "      exception_flag = 1;\n"
                                                "    }\n");

          SPVM_STRING_BUFFER_add(string_buffer, "    if (!exception_flag) { exception_flag = env->call_spvm_method(env, call_method_id, stack); }\n");
        }
        
        // Call method
        SPVM_STRING_BUFFER_add(string_buffer, "    if (!exception_flag) {\n");
        if (decl_method_return_type_dimension == 0) {
          switch (decl_method_return_basic_type_category) {
            case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_VOID: {
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_NUMERIC: {
              switch (decl_method_return_basic_type_id) {
                case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                  SPVM_STRING_BUFFER_add(string_buffer, "      ");
                  SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, var_id);
                  SPVM_STRING_BUFFER_add(string_buffer, " = ");
                  SPVM_PRECOMPILE_add_stack(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, 0);
                  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
                  break;
                }
                case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                  SPVM_STRING_BUFFER_add(string_buffer, "      ");
                  SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, var_id);
                  SPVM_STRING_BUFFER_add(string_buffer, " = ");
                  SPVM_PRECOMPILE_add_stack(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, 0);
                  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
                  break;
                }
                case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                  SPVM_STRING_BUFFER_add(string_buffer, "      ");
                  SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, var_id);
                  SPVM_STRING_BUFFER_add(string_buffer, " = ");
                  SPVM_PRECOMPILE_add_stack(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, 0);
                  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
                  break;
                }
                case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                  SPVM_STRING_BUFFER_add(string_buffer, "      ");
                  SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, var_id);
                  SPVM_STRING_BUFFER_add(string_buffer, " = ");
                  SPVM_PRECOMPILE_add_stack(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, 0);
                  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
                  break;
                }
                case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                  SPVM_STRING_BUFFER_add(string_buffer, "      ");
                  SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, var_id);
                  SPVM_STRING_BUFFER_add(string_buffer, " = ");
                  SPVM_PRECOMPILE_add_stack(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, 0);
                  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
                  break;
                }
                case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                  SPVM_STRING_BUFFER_add(string_buffer, "      ");
                  SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, var_id);
                  SPVM_STRING_BUFFER_add(string_buffer, " = ");
                  SPVM_PRECOMPILE_add_stack(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, 0);
                  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
                  break;
                }
                default: {
                  assert(0);
                }
              }
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_MULNUM:
            {
              int32_t decl_method_return_class_id = SPVM_API_RUNTIME_get_basic_type_class_id(env->runtime, decl_method_return_basic_type_id);
              int32_t decl_method_return_class_field_ids_length = SPVM_API_RUNTIME_get_class_field_ids_length(env->runtime, decl_method_return_class_id);
              int32_t decl_method_return_class_field_ids_base = SPVM_API_RUNTIME_get_class_field_ids_base(env->runtime, decl_method_return_class_id);
              int32_t decl_method_return_class_field_type_id = SPVM_API_RUNTIME_get_field_type_id(env->runtime, decl_method_return_class_field_ids_base);
              int32_t decl_method_return_class_field_type_basic_type_id = SPVM_API_RUNTIME_get_type_basic_type_id(env->runtime, decl_method_return_class_field_type_id);
              assert(decl_method_return_class_field_type_basic_type_id >= 0);
              
              switch (decl_method_return_class_field_type_basic_type_id) {
                case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
                  int32_t decl_method_return_type_width = opcode->operand3;
                  for (int32_t field_index = 0; field_index < decl_method_return_type_width; field_index++) {
                    SPVM_STRING_BUFFER_add(string_buffer, "      ");
                    SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, var_id + field_index);
                    SPVM_STRING_BUFFER_add(string_buffer, " = ");
                    SPVM_PRECOMPILE_add_stack(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, field_index);
                    SPVM_STRING_BUFFER_add(string_buffer, ";\n");
                  }
                  break;
                }
                case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
                  int32_t decl_method_return_type_width = opcode->operand3;
                  for (int32_t field_index = 0; field_index < decl_method_return_type_width; field_index++) {
                    SPVM_STRING_BUFFER_add(string_buffer, "      ");
                    SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, var_id + field_index);
                    SPVM_STRING_BUFFER_add(string_buffer, " = ");
                    SPVM_PRECOMPILE_add_stack(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, field_index);
                    SPVM_STRING_BUFFER_add(string_buffer, ";\n");
                  }
                  break;
                }
                case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
                  int32_t decl_method_return_type_width = opcode->operand3;
                  for (int32_t field_index = 0; field_index < decl_method_return_type_width; field_index++) {
                    SPVM_STRING_BUFFER_add(string_buffer, "      ");
                    SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, var_id + field_index);
                    SPVM_STRING_BUFFER_add(string_buffer, " = ");
                    SPVM_PRECOMPILE_add_stack(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, field_index);
                    SPVM_STRING_BUFFER_add(string_buffer, ";\n");
                  }
                  break;
                }
                case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
                  int32_t decl_method_return_type_width = opcode->operand3;
                  for (int32_t field_index = 0; field_index < decl_method_return_type_width; field_index++) {
                    SPVM_STRING_BUFFER_add(string_buffer, "      ");
                    SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, var_id + field_index);
                    SPVM_STRING_BUFFER_add(string_buffer, " = ");
                    SPVM_PRECOMPILE_add_stack(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, field_index);
                    SPVM_STRING_BUFFER_add(string_buffer, ";\n");
                  }
                  break;
                }
                case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
                  int32_t decl_method_return_type_width = opcode->operand3;
                  for (int32_t field_index = 0; field_index < decl_method_return_type_width; field_index++) {
                    SPVM_STRING_BUFFER_add(string_buffer, "      ");
                    SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, var_id + field_index);
                    SPVM_STRING_BUFFER_add(string_buffer, " = ");
                    SPVM_PRECOMPILE_add_stack(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, field_index);
                    SPVM_STRING_BUFFER_add(string_buffer, ";\n");
                  }
                  break;
                }
                case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
                  int32_t decl_method_return_type_width = opcode->operand3;
                  for (int32_t field_index = 0; field_index < decl_method_return_type_width; field_index++) {
                    SPVM_STRING_BUFFER_add(string_buffer, "      ");
                    SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, var_id + field_index);
                    SPVM_STRING_BUFFER_add(string_buffer, " = ");
                    SPVM_PRECOMPILE_add_stack(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, field_index);
                    SPVM_STRING_BUFFER_add(string_buffer, ";\n");
                  }
                  break;
                }
                default: {
                  assert(0);
                }
              }
              break;
            }
            case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_STRING:
            case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_CLASS:
            case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_INTERFACE:
            case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_CALLBACK:
            case SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_ANY_OBJECT:
            {
              SPVM_STRING_BUFFER_add(string_buffer, "      SPVM_API_OBJECT_ASSIGN(&");
              SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, var_id);
              SPVM_STRING_BUFFER_add(string_buffer, ", stack[0].oval);\n");
              break;
            }
            default: {
              assert(0);
            }
          }
        }
        else if (decl_method_return_type_dimension > 0) {
          SPVM_STRING_BUFFER_add(string_buffer, "      SPVM_API_OBJECT_ASSIGN(&");
          SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, var_id);
          SPVM_STRING_BUFFER_add(string_buffer, ", stack[0].oval);\n");
        }
        else {
          assert(0);
        }

        SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");

        stack_index = 0;
        
        break;
      }
      case SPVM_OPCODE_C_ID_IF_EXCEPTION_CATCH: {
        int32_t line = opcode->operand2;
        
        SPVM_STRING_BUFFER_add(string_buffer, "  if (exception_flag) {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t line = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, line);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "    exception_flag = 0;\n"
                                              "    env->set_exception(env, env->new_stack_trace_raw(env, env->get_exception(env), CURRENT_CLASS_NAME, CURRENT_METHOD_NAME, CURRENT_CLASS_FILE, line));\n"
                                              "    goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer,  opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_IF_EXCEPTION_RETURN: {
        int32_t line = opcode->operand2;
        
        SPVM_STRING_BUFFER_add(string_buffer, "  if (exception_flag) {\n"
                                              "    int32_t line = ");
        SPVM_STRING_BUFFER_add_int(string_buffer, line);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    env->set_exception(env, env->new_stack_trace_raw(env, env->get_exception(env), CURRENT_CLASS_NAME, CURRENT_METHOD_NAME, CURRENT_CLASS_FILE, line));\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_DIE_FLAG_TRUE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  exception_flag = 1;\n");
        break;
      }
      case SPVM_OPCODE_C_ID_PRINT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                              "    void* object = ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "    if (object) {\n"
                                              "      const char* bytes = env->get_chars(env, object);\n"
                                              "      int32_t string_length = env->length(env, object);\n"
                                              "      if (string_length > 0) {\n"
                                              "        size_t ret = fwrite(bytes, 1, string_length, stdout);\n"
                                              "      }\n"
                                              "    }\n"
                                              "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_MAKE_READ_ONLY: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                              "    void* string = ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "    env->make_read_only(env, string);\n"
                                              "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_WARN: {
        int32_t line = opcode->operand1;
        
        const char* file = class_module_file;
        
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                              "    void* object = ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "    int32_t empty_or_undef = 0;\n"
                                              "    if (object) {\n"
                                              "      const char* bytes = env->get_chars(env, object);\n"
                                              "      int32_t string_length = env->length(env, object);\n"
                                              "      if (string_length > 0) {\n"
                                              "        size_t ret = fwrite(bytes, 1, string_length, stderr);\n"
                                              "        int32_t add_line_file;\n"
                                              "        if (bytes[string_length - 1] != '\\n') {\n"
                                              "          fprintf(stderr, \" at %s line %d\\n\", \"");
        SPVM_STRING_BUFFER_add(string_buffer, file);
        SPVM_STRING_BUFFER_add(string_buffer, "\", ");
        SPVM_STRING_BUFFER_add_int(string_buffer, line);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n"
                                              "        }\n"
                                              "      }\n"
                                              "      else {\n"
                                              "        empty_or_undef = 1;\n"
                                              "      }\n"
                                              "    }\n"
                                              "    else {\n"
                                              "      empty_or_undef = 1;\n"
                                              "    }\n"
                                              "    if (empty_or_undef) {\n"
                                              "        fprintf(stderr, \"Warning: something's wrong at %s line %d\\n\", \"");
        SPVM_STRING_BUFFER_add(string_buffer, file);
        SPVM_STRING_BUFFER_add(string_buffer, "\", ");
        SPVM_STRING_BUFFER_add_int(string_buffer, line);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n"
                                              "    }\n"
                                              "  }\n");
        
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
        int32_t var_id = opcode->operand0;
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_PRECOMPILE_add_stack(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, 0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, var_id);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_RETURN_SHORT: {
        int32_t var_id = opcode->operand0;
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_PRECOMPILE_add_stack(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, 0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, var_id);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_RETURN_INT: {
        int32_t var_id = opcode->operand0;
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_PRECOMPILE_add_stack(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, 0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, var_id);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_RETURN_LONG: {
        int32_t var_id = opcode->operand0;
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_PRECOMPILE_add_stack(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, 0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, var_id);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_RETURN_FLOAT: {
        int32_t var_id = opcode->operand0;
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_PRECOMPILE_add_stack(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, 0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, var_id);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_RETURN_DOUBLE: {
        int32_t var_id = opcode->operand0;
        SPVM_STRING_BUFFER_add(string_buffer, "  ");
        SPVM_PRECOMPILE_add_stack(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, 0);
        SPVM_STRING_BUFFER_add(string_buffer, " = ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, var_id);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_RETURN_MULNUM_BYTE:
      {
        int32_t var_id = opcode->operand0;
        int32_t method_return_type_width = opcode->operand2;
        
        // Multi numeric type
        for (int32_t field_index = 0; field_index < method_return_type_width; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_PRECOMPILE_add_stack(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, var_id + field_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        }
        SPVM_STRING_BUFFER_add(string_buffer, "  goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_RETURN_MULNUM_SHORT:
      {
        int32_t var_id = opcode->operand0;
        int32_t method_return_type_width = opcode->operand2;
        for (int32_t field_index = 0; field_index < method_return_type_width; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_PRECOMPILE_add_stack(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, var_id + field_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        }
        SPVM_STRING_BUFFER_add(string_buffer, "  goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_RETURN_MULNUM_INT:
      {
        int32_t var_id = opcode->operand0;
        int32_t method_return_type_width = opcode->operand2;
        for (int32_t field_index = 0; field_index < method_return_type_width; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_PRECOMPILE_add_stack(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, var_id + field_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        }
        SPVM_STRING_BUFFER_add(string_buffer, "  goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_RETURN_MULNUM_LONG:
      {
        int32_t var_id = opcode->operand0;
        int32_t method_return_type_width = opcode->operand2;
        
        // Multi numeric type
        for (int32_t field_index = 0; field_index < method_return_type_width; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_PRECOMPILE_add_stack(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, var_id + field_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        }
        SPVM_STRING_BUFFER_add(string_buffer, "  goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_RETURN_MULNUM_FLOAT:
      {
        int32_t var_id = opcode->operand0;
        int32_t method_return_type_width = opcode->operand2;
        for (int32_t field_index = 0; field_index < method_return_type_width; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_PRECOMPILE_add_stack(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, var_id + field_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        }
        SPVM_STRING_BUFFER_add(string_buffer, "  goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_RETURN_MULNUM_DOUBLE:
      {
        int32_t var_id = opcode->operand0;
        int32_t method_return_type_width = opcode->operand2;
        for (int32_t field_index = 0; field_index < method_return_type_width; field_index++) {
          SPVM_STRING_BUFFER_add(string_buffer, "  ");
          SPVM_PRECOMPILE_add_stack(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, field_index);
          SPVM_STRING_BUFFER_add(string_buffer, " = ");
          SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, var_id + field_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        }
        SPVM_STRING_BUFFER_add(string_buffer, "  goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_RETURN_OBJECT:
      {
        SPVM_STRING_BUFFER_add(string_buffer, "  *(void**)&stack[0] = ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "  if (*(void**)&stack[0] != NULL) {\n"
                                              "    SPVM_API_INC_REF_COUNT_ONLY(*(void**)&stack[0]);\n"
                                              "  }\n"
                                              "  goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_RETURN_UNDEF:
      {
        SPVM_STRING_BUFFER_add(string_buffer, "  *(void**)&stack[0] = NULL;\n"
                                              "  goto L");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_LOOKUP_SWITCH: {
        int32_t switch_id = opcode->operand1;
        
        // Default branch
        int32_t default_opcode_rel_index = opcode->operand2;
        
        // Cases length
        int32_t case_infos_length = opcode->operand3;

        SPVM_STRING_BUFFER_add(string_buffer, "  switch(");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ") {\n");
        for (int32_t case_index = 0; case_index < case_infos_length; case_index++) {
          SPVM_OPCODE* opcode_case_info = &(opcodes[method_opcode_ids_base + opcode_index + 1 + case_index]);

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
      case SPVM_OPCODE_C_ID_REF_BYTE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  *(void**)&");
        SPVM_PRECOMPILE_add_var(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_REF, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = &byte_vars[");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, "];\n");
        break;
      }
      case SPVM_OPCODE_C_ID_REF_SHORT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  *(void**)&");
        SPVM_PRECOMPILE_add_var(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_REF, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = &short_vars[");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, "];\n");
        break;
      }
      case SPVM_OPCODE_C_ID_REF_INT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  *(void**)&");
        SPVM_PRECOMPILE_add_var(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_REF, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = &int_vars[");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, "];\n");
        break;
      }
      case SPVM_OPCODE_C_ID_REF_LONG: {
        SPVM_STRING_BUFFER_add(string_buffer, "  *(void**)&");
        SPVM_PRECOMPILE_add_var(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_REF, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = &long_vars[");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, "];\n");
        break;
      }
      case SPVM_OPCODE_C_ID_REF_FLOAT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  *(void**)&");
        SPVM_PRECOMPILE_add_var(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_REF, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = &float_vars[");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, "];\n");
        break;
      }
      case SPVM_OPCODE_C_ID_REF_DOUBLE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  *(void**)&");
        SPVM_PRECOMPILE_add_var(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_REF, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = &double_vars[");
        SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, "];\n");
        break;
      }
      case SPVM_OPCODE_C_ID_DEREF_MULNUM_BYTE: {
        int32_t fields_length = opcode->operand3;
        SPVM_PRECOMPILE_add_mulnum_deref(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, opcode->operand1, fields_length);
        break;
      }
      case SPVM_OPCODE_C_ID_DEREF_MULNUM_SHORT: {
        int32_t fields_length = opcode->operand3;
        SPVM_PRECOMPILE_add_mulnum_deref(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, opcode->operand1, fields_length);
        break;
      }
      case SPVM_OPCODE_C_ID_DEREF_MULNUM_INT: {
        int32_t fields_length = opcode->operand3;
        SPVM_PRECOMPILE_add_mulnum_deref(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, fields_length);
        break;
      }
      case SPVM_OPCODE_C_ID_DEREF_MULNUM_LONG: {
        int32_t fields_length = opcode->operand3;
        SPVM_PRECOMPILE_add_mulnum_deref(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, fields_length);
        break;
      }
      case SPVM_OPCODE_C_ID_DEREF_MULNUM_FLOAT: {
        int32_t fields_length = opcode->operand3;
        SPVM_PRECOMPILE_add_mulnum_deref(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1, fields_length);
        break;
      }
      case SPVM_OPCODE_C_ID_DEREF_MULNUM_DOUBLE: {
        int32_t fields_length = opcode->operand3;
        SPVM_PRECOMPILE_add_mulnum_deref(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1, fields_length);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_DEREF_BYTE: {
        int32_t field_index = opcode->operand2;
        SPVM_PRECOMPILE_add_mulnum_deref_get_field(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, opcode->operand1, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_DEREF_SHORT: {
        int32_t field_index = opcode->operand2;
        SPVM_PRECOMPILE_add_mulnum_deref_get_field(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, opcode->operand1, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_DEREF_INT: {
        int32_t field_index = opcode->operand2;
        SPVM_PRECOMPILE_add_mulnum_deref_get_field(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_DEREF_LONG: {
        int32_t field_index = opcode->operand2;
        SPVM_PRECOMPILE_add_mulnum_deref_get_field(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_DEREF_FLOAT: {
        int32_t field_index = opcode->operand2;
        SPVM_PRECOMPILE_add_mulnum_deref_get_field(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_DEREF_DOUBLE: {
        int32_t field_index = opcode->operand2;
        SPVM_PRECOMPILE_add_mulnum_deref_get_field(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_DEREF_BYTE: {
        int32_t field_index = opcode->operand2;
        SPVM_PRECOMPILE_add_mulnum_deref_set_field(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, opcode->operand1, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_DEREF_SHORT: {
        int32_t field_index = opcode->operand2;
        SPVM_PRECOMPILE_add_mulnum_deref_set_field(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, opcode->operand1, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_DEREF_INT: {
        int32_t field_index = opcode->operand2;
        SPVM_PRECOMPILE_add_mulnum_deref_set_field(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_DEREF_LONG: {
        int32_t field_index = opcode->operand2;
        SPVM_PRECOMPILE_add_mulnum_deref_set_field(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_DEREF_FLOAT: {
        int32_t field_index = opcode->operand2;
        SPVM_PRECOMPILE_add_mulnum_deref_set_field(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_DEREF_DOUBLE: {
        int32_t field_index = opcode->operand2;
        SPVM_PRECOMPILE_add_mulnum_deref_set_field(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1, field_index);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_BYTE: {
        int32_t field_id = opcode->operand2;
        SPVM_PRECOMPILE_add_get_field(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, opcode->operand1, field_id);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_SHORT: {
        int32_t field_id = opcode->operand2;
        SPVM_PRECOMPILE_add_get_field(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, opcode->operand1, field_id);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_INT: {
        int32_t field_id = opcode->operand2;
        SPVM_PRECOMPILE_add_get_field(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1, field_id);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_LONG: {
        int32_t field_id = opcode->operand2;
        SPVM_PRECOMPILE_add_get_field(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1, field_id);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_FLOAT: {
        int32_t field_id = opcode->operand2;
        SPVM_PRECOMPILE_add_get_field(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1, field_id);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_DOUBLE: {
        int32_t field_id = opcode->operand2;
        SPVM_PRECOMPILE_add_get_field(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1, field_id);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_OBJECT: {
        int32_t field_id = opcode->operand2;
        
        int32_t field_class_id = SPVM_API_RUNTIME_get_field_class_id(env->runtime, field_id);
        int32_t field_class_name_id = SPVM_API_RUNTIME_get_class_name_id(env->runtime, field_class_id);
        const char* field_class_name = SPVM_API_RUNTIME_get_name(env->runtime, field_class_name_id);
        int32_t field_name_id = SPVM_API_RUNTIME_get_field_name_id(env->runtime, field_id);
        const char* field_name = SPVM_API_RUNTIME_get_name(env->runtime, field_name_id);
        int32_t field_signature_id = SPVM_API_RUNTIME_get_field_signature_id(env->runtime, field_id);
        const char* field_signature = SPVM_API_RUNTIME_get_name(env->runtime, field_signature_id);

        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t access_field_id = env->get_field_id(env, \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_class_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_signature);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n"
                                              "    if (access_field_id < 0) {\n"
                                              "      void* exception = env->new_string_nolen_raw(env, \"Field not found ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_class_name);
        SPVM_STRING_BUFFER_add(string_buffer, " ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n"
                                              "      env->set_exception(env, exception);\n"
                                              "      exception_flag = 1;\n"
                                              "    }\n"
                                              "    if (!exception_flag) {\n"
                                              "      int32_t access_field_offset"
                                              " = env->get_field_offset(env, access_field_id);\n"
                                              "      void* object = ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "      if (__builtin_expect(object == NULL, 0)) {\n"
                                              "        env->set_exception(env, env->new_string_nolen_raw(env, \"Object must be not undef.\"));\n"
                                              "        exception_flag = 1;\n"
                                              "      }\n"
                                              "      else {\n"
                                              "        void* get_field_object = *(void**)((intptr_t)object + object_header_byte_size + "
                                              "access_field_offset"
                                              ");\n"
                                              "        SPVM_API_OBJECT_ASSIGN(&");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", get_field_object);\n"
                                              "      }\n"
                                              "    }\n"
                                              "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_BYTE: {
        int32_t field_id = opcode->operand1;
        SPVM_PRECOMPILE_add_set_field(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, field_id, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_SHORT: {
        int32_t field_id = opcode->operand1;
        SPVM_PRECOMPILE_add_set_field(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, field_id, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_INT: {
        int32_t field_id = opcode->operand1;
        SPVM_PRECOMPILE_add_set_field(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, field_id, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_LONG: {
        int32_t field_id = opcode->operand1;
        SPVM_PRECOMPILE_add_set_field(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, field_id, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_FLOAT: {
        int32_t field_id = opcode->operand1;
        SPVM_PRECOMPILE_add_set_field(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, field_id, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_DOUBLE: {
        int32_t field_id = opcode->operand1;
        SPVM_PRECOMPILE_add_set_field(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, field_id, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_OBJECT:
      {
        int32_t field_id = opcode->operand1;
        
        int32_t field_class_id = SPVM_API_RUNTIME_get_field_class_id(env->runtime, field_id);
        int32_t field_class_name_id = SPVM_API_RUNTIME_get_class_name_id(env->runtime, field_class_id);
        const char* field_class_name = SPVM_API_RUNTIME_get_name(env->runtime, field_class_name_id);
        int32_t field_name_id = SPVM_API_RUNTIME_get_field_name_id(env->runtime, field_id);
        const char* field_name = SPVM_API_RUNTIME_get_name(env->runtime, field_name_id);
        int32_t field_signature_id = SPVM_API_RUNTIME_get_field_signature_id(env->runtime, field_id);
        const char* field_signature = SPVM_API_RUNTIME_get_name(env->runtime, field_signature_id);

        SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                              "    int32_t access_field_id = env->get_field_id(env, \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_class_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_signature);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n"
                                              "    if (access_field_id < 0) {\n"
                                              "      void* exception = env->new_string_nolen_raw(env, \"Field not found ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_class_name);
        SPVM_STRING_BUFFER_add(string_buffer, " ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n"
                                              "      env->set_exception(env, exception);\n"
                                              "      exception_flag = 1;\n"
                                              "    }\n"
                                              "    if (!exception_flag) {\n"
                                              "      int32_t access_field_offset"
                                              " = env->get_field_offset(env, "
                                              "access_field_id"
                                              ");\n"
                                              "      void* object = ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";"
                                              "      if (__builtin_expect(object == NULL, 0)) {\n"
                                              "        env->set_exception(env, env->new_string_nolen_raw(env, \"Object must be not undef.\"));\n"
                                              "        exception_flag = 1;\n"
                                              "      }\n"
                                              "      else {\n"
                                              "        void* get_field_object_address = (void**)((intptr_t)object + object_header_byte_size + "
                                              "access_field_offset"
                                              ");\n"
                                              "        SPVM_API_OBJECT_ASSIGN("
                                              "get_field_object_address,");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand2);
        SPVM_STRING_BUFFER_add(string_buffer, "    );\n"
                                              "      }\n"
                                              "    }\n"
                                              "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_UNDEF:
      {
        int32_t field_id = opcode->operand1;
        
        int32_t field_class_id = SPVM_API_RUNTIME_get_field_class_id(env->runtime, field_id);
        int32_t field_class_name_id = SPVM_API_RUNTIME_get_class_name_id(env->runtime, field_class_id);
        const char* field_class_name = SPVM_API_RUNTIME_get_name(env->runtime, field_class_name_id);
        int32_t field_name_id = SPVM_API_RUNTIME_get_field_name_id(env->runtime, field_id);
        const char* field_name = SPVM_API_RUNTIME_get_name(env->runtime, field_name_id);
        int32_t field_signature_id = SPVM_API_RUNTIME_get_field_signature_id(env->runtime, field_id);
        const char* field_signature = SPVM_API_RUNTIME_get_name(env->runtime, field_signature_id);

        SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                              "    int32_t access_field_id = env->get_field_id(env, \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_class_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_signature);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n"
                                              "    if (access_field_id < 0) {\n"
                                              "      void* exception = env->new_string_nolen_raw(env, \"Field not found ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_class_name);
        SPVM_STRING_BUFFER_add(string_buffer, " ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)field_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n"
                                              "      env->set_exception(env, exception);\n"
                                              "      exception_flag = 1;\n"
                                              "    }\n"
                                              "    if (!exception_flag) {\n"
                                              "      int32_t access_field_offset"
                                              " = env->get_field_offset(env, "
                                              "access_field_id"
                                              ");\n"
                                              "      void* object = ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ";"
                                              "      if (__builtin_expect(object == NULL, 0)) {\n"
                                              "      env->set_exception(env, env->new_string_nolen_raw(env, \"Object must be not undef.\"));\n"
                                              "        exception_flag = 1;\n"
                                              "      }\n"
                                              "      else {\n"
                                              "        void* get_field_object_address = (void**)((intptr_t)object + object_header_byte_size + "
                                              "access_field_offset"
                                              ");\n"
                                              "        SPVM_API_OBJECT_ASSIGN(get_field_object_address, NULL);"
                                              "      }\n"
                                              "    }\n"
                                              "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_GET_DEREF_BYTE: {
        SPVM_PRECOMPILE_add_get_deref(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_DEREF_SHORT: {
        SPVM_PRECOMPILE_add_get_deref(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_DEREF_INT: {
        SPVM_PRECOMPILE_add_get_deref(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_DEREF_LONG: {
        SPVM_PRECOMPILE_add_get_deref(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_DEREF_FLOAT: {
        SPVM_PRECOMPILE_add_get_deref(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_DEREF_DOUBLE: {
        SPVM_PRECOMPILE_add_get_deref(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_DEREF_BYTE: {
        SPVM_PRECOMPILE_add_set_deref(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_DEREF_SHORT: {
        SPVM_PRECOMPILE_add_set_deref(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_DEREF_INT: {
        SPVM_PRECOMPILE_add_set_deref(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_DEREF_LONG: {
        SPVM_PRECOMPILE_add_set_deref(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_DEREF_FLOAT: {
        SPVM_PRECOMPILE_add_set_deref(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_DEREF_DOUBLE: {
        SPVM_PRECOMPILE_add_set_deref(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0, opcode->operand1);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_CLASS_VAR_BYTE:
      case SPVM_OPCODE_C_ID_GET_CLASS_VAR_SHORT:
      case SPVM_OPCODE_C_ID_GET_CLASS_VAR_INT:
      case SPVM_OPCODE_C_ID_GET_CLASS_VAR_LONG:
      case SPVM_OPCODE_C_ID_GET_CLASS_VAR_FLOAT:
      case SPVM_OPCODE_C_ID_GET_CLASS_VAR_DOUBLE:
      {
        int32_t class_var_id = opcode->operand1;
        
        int32_t class_var_class_id = SPVM_API_RUNTIME_get_class_var_class_id(env->runtime, class_var_id);
        int32_t class_var_class_name_id = SPVM_API_RUNTIME_get_class_name_id(env->runtime, class_var_class_id);
        const char* class_var_class_name = SPVM_API_RUNTIME_get_name(env->runtime, class_var_class_name_id);
        int32_t class_var_name_id = SPVM_API_RUNTIME_get_class_var_name_id(env->runtime, class_var_id);
        const char* class_var_name = SPVM_API_RUNTIME_get_name(env->runtime, class_var_name_id);
        int32_t class_var_signature_id = SPVM_API_RUNTIME_get_class_var_signature_id(env->runtime, class_var_id);
        const char* class_var_signature = SPVM_API_RUNTIME_get_name(env->runtime, class_var_signature_id);

        int32_t class_var_access_ctype_id;
        switch (opcode_id) {
          case SPVM_OPCODE_C_ID_GET_CLASS_VAR_BYTE:
            class_var_access_ctype_id = SPVM_PRECOMPILE_C_CTYPE_ID_BYTE;
            break;
          case SPVM_OPCODE_C_ID_GET_CLASS_VAR_SHORT:
            class_var_access_ctype_id = SPVM_PRECOMPILE_C_CTYPE_ID_SHORT;
            break;
          case SPVM_OPCODE_C_ID_GET_CLASS_VAR_INT:
            class_var_access_ctype_id = SPVM_PRECOMPILE_C_CTYPE_ID_INT;
            break;
          case SPVM_OPCODE_C_ID_GET_CLASS_VAR_LONG:
            class_var_access_ctype_id = SPVM_PRECOMPILE_C_CTYPE_ID_LONG;
            break;
          case SPVM_OPCODE_C_ID_GET_CLASS_VAR_FLOAT:
            class_var_access_ctype_id = SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT;
            break;
          case SPVM_OPCODE_C_ID_GET_CLASS_VAR_DOUBLE:
            class_var_access_ctype_id = SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE;
            break;
          default:
            assert(0);
        }
        
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t access_class_var_id = env->get_class_var_id(env, \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)class_var_class_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)class_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)class_var_signature);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n"
                                              "    if (access_class_var_id < 0) {\n"
                                              "      void* exception = env->new_string_nolen_raw(env, \"Class variable not found ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)class_var_class_name);
        SPVM_STRING_BUFFER_add(string_buffer, " ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)class_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n"
                                              "      env->set_exception(env, exception);\n"
                                              "      exception_flag = 1;\n"
                                              "    }\n"
                                              "    if (!exception_flag) {\n"
                                              "      ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, class_var_access_ctype_id, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = *(");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_PRECOMPILE_get_ctype_name(env, class_var_access_ctype_id));
        SPVM_STRING_BUFFER_add(string_buffer, "*)&((SPVM_VALUE*)env->class_vars_heap)[access_class_var_id];\n"
                                              "    }\n"
                                              "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_GET_CLASS_VAR_OBJECT: {
        int32_t class_var_id = opcode->operand1;
        
        int32_t class_var_class_id = SPVM_API_RUNTIME_get_class_var_class_id(env->runtime, class_var_id);
        int32_t class_var_class_name_id = SPVM_API_RUNTIME_get_class_name_id(env->runtime, class_var_class_id);
        const char* class_var_class_name = SPVM_API_RUNTIME_get_name(env->runtime, class_var_class_name_id);
        int32_t class_var_name_id = SPVM_API_RUNTIME_get_class_var_name_id(env->runtime, class_var_id);
        const char* class_var_name = SPVM_API_RUNTIME_get_name(env->runtime, class_var_name_id);
        int32_t class_var_signature_id = SPVM_API_RUNTIME_get_class_var_signature_id(env->runtime, class_var_id);
        const char* class_var_signature = SPVM_API_RUNTIME_get_name(env->runtime, class_var_signature_id);

        SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                              "    int32_t access_class_var_id = env->get_class_var_id(env, \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)class_var_class_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)class_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)class_var_signature);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n"
                                              "    if (access_class_var_id < 0) {\n"
                                              "      void* exception = env->new_string_nolen_raw(env, \"Class variable not found ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)class_var_class_name);
        SPVM_STRING_BUFFER_add(string_buffer, " ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)class_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n"
                                              "      env->set_exception(env, exception);\n"
                                              "      exception_flag = 1;\n"
                                              "    }\n"
                                              "    if (!exception_flag) {\n"
                                              "      SPVM_API_OBJECT_ASSIGN(&");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", *(void**)&((SPVM_VALUE*)env->class_vars_heap)[access_class_var_id]);\n"
                                              "    }\n"
                                              "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_SET_CLASS_VAR_BYTE:
      case SPVM_OPCODE_C_ID_SET_CLASS_VAR_SHORT:
      case SPVM_OPCODE_C_ID_SET_CLASS_VAR_INT:
      case SPVM_OPCODE_C_ID_SET_CLASS_VAR_LONG:
      case SPVM_OPCODE_C_ID_SET_CLASS_VAR_FLOAT:
      case SPVM_OPCODE_C_ID_SET_CLASS_VAR_DOUBLE:
      {
        int32_t class_var_id = opcode->operand0;
        
        int32_t class_var_class_id = SPVM_API_RUNTIME_get_class_var_class_id(env->runtime, class_var_id);
        int32_t class_var_class_name_id = SPVM_API_RUNTIME_get_class_name_id(env->runtime, class_var_class_id);
        const char* class_var_class_name = SPVM_API_RUNTIME_get_name(env->runtime, class_var_class_name_id);
        int32_t class_var_name_id = SPVM_API_RUNTIME_get_class_var_name_id(env->runtime, class_var_id);
        const char* class_var_name = SPVM_API_RUNTIME_get_name(env->runtime, class_var_name_id);
        int32_t class_var_signature_id = SPVM_API_RUNTIME_get_class_var_signature_id(env->runtime, class_var_id);
        const char* class_var_signature = SPVM_API_RUNTIME_get_name(env->runtime, class_var_signature_id);

        int32_t class_var_access_ctype_id;
        switch (opcode_id) {
          case SPVM_OPCODE_C_ID_SET_CLASS_VAR_BYTE:
            class_var_access_ctype_id = SPVM_PRECOMPILE_C_CTYPE_ID_BYTE;
            break;
          case SPVM_OPCODE_C_ID_SET_CLASS_VAR_SHORT:
            class_var_access_ctype_id = SPVM_PRECOMPILE_C_CTYPE_ID_SHORT;
            break;
          case SPVM_OPCODE_C_ID_SET_CLASS_VAR_INT:
            class_var_access_ctype_id = SPVM_PRECOMPILE_C_CTYPE_ID_INT;
            break;
          case SPVM_OPCODE_C_ID_SET_CLASS_VAR_LONG:
            class_var_access_ctype_id = SPVM_PRECOMPILE_C_CTYPE_ID_LONG;
            break;
          case SPVM_OPCODE_C_ID_SET_CLASS_VAR_FLOAT:
            class_var_access_ctype_id = SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT;
            break;
          case SPVM_OPCODE_C_ID_SET_CLASS_VAR_DOUBLE:
            class_var_access_ctype_id = SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE;
            break;
          default:
            class_var_access_ctype_id = SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT;
        }
        
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    int32_t access_class_var_id = env->get_class_var_id(env, \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)class_var_class_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)class_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)class_var_signature);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n"
                                              "    if ("
                                              "access_class_var_id"
                                              " < 0) {\n"
                                              "      void* exception = env->new_string_nolen_raw(env, \"Class variable not found ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)class_var_class_name);
        SPVM_STRING_BUFFER_add(string_buffer, " ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)class_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n"
                                              "      env->set_exception(env, exception);\n"
                                              "      exception_flag = 1;\n"
                                              "    }\n"
                                              "    if (!exception_flag) {\n"
                                              "      *(");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_PRECOMPILE_get_ctype_name(env, class_var_access_ctype_id));
        SPVM_STRING_BUFFER_add(string_buffer, "*)&((SPVM_VALUE*)env->class_vars_heap)[access_class_var_id] = ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, class_var_access_ctype_id, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "    }\n"
                                              "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_SET_CLASS_VAR_OBJECT: {
        int32_t class_var_id = opcode->operand0;
        
        int32_t class_var_class_id = SPVM_API_RUNTIME_get_class_var_class_id(env->runtime, class_var_id);
        int32_t class_var_class_name_id = SPVM_API_RUNTIME_get_class_name_id(env->runtime, class_var_class_id);
        const char* class_var_class_name = SPVM_API_RUNTIME_get_name(env->runtime, class_var_class_name_id);
        int32_t class_var_name_id = SPVM_API_RUNTIME_get_class_var_name_id(env->runtime, class_var_id);
        const char* class_var_name = SPVM_API_RUNTIME_get_name(env->runtime, class_var_name_id);
        int32_t class_var_signature_id = SPVM_API_RUNTIME_get_class_var_signature_id(env->runtime, class_var_id);
        const char* class_var_signature = SPVM_API_RUNTIME_get_name(env->runtime, class_var_signature_id);

        SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                              "    int32_t access_class_var_id = env->get_class_var_id(env, \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)class_var_class_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)class_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)class_var_signature);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n"
                                              "    if ("
                                              "access_class_var_id"
                                              " < 0) {\n"
                                              "      void* exception = env->new_string_nolen_raw(env, \"Class variable not found ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)class_var_class_name);
        SPVM_STRING_BUFFER_add(string_buffer, " ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)class_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n"
                                              "      env->set_exception(env, exception);\n"
                                              "      exception_flag = 1;\n"
                                              "    }\n"
                                              "    if (!exception_flag) {\n"
                                              "      SPVM_API_OBJECT_ASSIGN((void**)&((SPVM_VALUE*)env->class_vars_heap)["
                                              "access_class_var_id"
                                              "],\n");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ");"
                                              "    }\n"
                                              "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_SET_CLASS_VAR_UNDEF: {
        int32_t class_var_id = opcode->operand0;
        
        int32_t class_var_class_id = SPVM_API_RUNTIME_get_class_var_class_id(env->runtime, class_var_id);
        int32_t class_var_class_name_id = SPVM_API_RUNTIME_get_class_name_id(env->runtime, class_var_class_id);
        const char* class_var_class_name = SPVM_API_RUNTIME_get_name(env->runtime, class_var_class_name_id);
        int32_t class_var_name_id = SPVM_API_RUNTIME_get_class_var_name_id(env->runtime, class_var_id);
        const char* class_var_name = SPVM_API_RUNTIME_get_name(env->runtime, class_var_name_id);
        int32_t class_var_signature_id = SPVM_API_RUNTIME_get_class_var_signature_id(env->runtime, class_var_id);
        const char* class_var_signature = SPVM_API_RUNTIME_get_name(env->runtime, class_var_signature_id);
        
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                              "    int32_t access_class_var_id = env->get_class_var_id(env, \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)class_var_class_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)class_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)class_var_signature);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n"
                                              "    if ("
                                              "access_class_var_id"
                                              " < 0) {\n"
                                              "      void* exception = env->new_string_nolen_raw(env, \"Class variable not found ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)class_var_class_name);
        SPVM_STRING_BUFFER_add(string_buffer, " ");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)class_var_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\");\n"
                                              "      env->set_exception(env, exception);\n"
                                              "      exception_flag = 1;\n"
                                              "    }\n"
                                              "    if (!exception_flag) {\n"
                                              "      SPVM_API_OBJECT_ASSIGN((void**)&((SPVM_VALUE*)env->class_vars_heap)["
                                              "access_class_var_id"
                                              "], NULL);\n"
                                              "    }\n"
                                              "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_GET_EXCEPTION_VAR: {
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_API_OBJECT_ASSIGN(&");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", env->get_exception(env));\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_EXCEPTION_VAR: {
        SPVM_STRING_BUFFER_add(string_buffer, "  env->set_exception(env, ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_EXCEPTION_VAR_UNDEF: {
        SPVM_STRING_BUFFER_add(string_buffer, "  env->set_exception(env, NULL);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_END_METHOD: {
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_BYTE_OBJECT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                              "    int8_t value = ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "    int32_t basic_type_id = (intptr_t)(void*)env->byte_object_basic_type_id;\n"
                                              "    void* object = env->new_object_raw(env, basic_type_id);\n"
                                              "    SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_byte_size);\n"
                                              "    *(int8_t*)&fields[0] = value;\n"
                                              "    SPVM_API_OBJECT_ASSIGN(&");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object);\n"
                                              "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_SHORT_OBJECT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                              "    int16_t value = ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "    int32_t basic_type_id = (intptr_t)(void*)env->short_object_basic_type_id;\n"
                                              "    void* object = env->new_object_raw(env, basic_type_id);\n"
                                              "    SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_byte_size);\n"
                                              "    *(int16_t*)&fields[0] = value;\n"
                                              "    SPVM_API_OBJECT_ASSIGN(&");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object);\n"
                                              "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_INT_TO_INT_OBJECT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                              "    int32_t value = ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "    int32_t basic_type_id = (intptr_t)(void*)env->int_object_basic_type_id;\n"
                                              "    void* object = env->new_object_raw(env, basic_type_id);\n"
                                              "    SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_byte_size);\n"
                                              "    *(int32_t*)&fields[0] = value;\n"
                                              "    SPVM_API_OBJECT_ASSIGN(&");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object);\n"
                                              "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_LONG_TO_LONG_OBJECT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                              "    int64_t value = ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "    int32_t basic_type_id = (intptr_t)(void*)env->long_object_basic_type_id;\n"
                                              "    void* object = env->new_object_raw(env, basic_type_id);\n"
                                              "    SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_byte_size);\n"
                                              "    *(int64_t*)&fields[0] = value;\n"
                                              "    SPVM_API_OBJECT_ASSIGN(&");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_FLOAT_OBJECT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                              "    float value = ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "    int32_t basic_type_id = (intptr_t)(void*)env->float_object_basic_type_id;\n"
                                              "    void* object = env->new_object_raw(env, basic_type_id);\n"
                                              "    SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_byte_size);\n"
                                              "    *(float*)&fields[0] = value;\n"
                                              "    SPVM_API_OBJECT_ASSIGN(&");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object);\n"
                                              "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_DOUBLE_OBJECT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    double value = ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "    int32_t basic_type_id = (intptr_t)(void*)env->double_object_basic_type_id;\n"
                                              "    void* object = env->new_object_raw(env, basic_type_id);\n"
                                              "    SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_byte_size);\n"
                                              "    *(double*)&fields[0] = value;\n"
                                              "    SPVM_API_OBJECT_ASSIGN(&");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, ", object);\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_BYTE_OBJECT_TO_BYTE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    void* object = ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "    if (object == NULL) {\n"
                                              "      void* exception = env->new_string_nolen_raw(env, \"Can't convert undef value.\");\n"
                                              "      env->set_exception(env, exception);\n"
                                              "      exception_flag = 1;\n"
                                              "    }\n"
                                              "    else {\n"
                                              "      int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_offset);\n"
                                              "      int32_t object_type_dimension_id = *(uint8_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_offset);\n"
                                              "      if (object_basic_type_id == (intptr_t)(void*)env->byte_object_basic_type_id && object_type_dimension_id == 0) {\n"
                                              "        SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_byte_size);\n"
                                              "        \n");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_BYTE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = *(int8_t*)&fields[0];\n"
                                              "      }\n"
                                              "      else {\n"
                                              "        void* exception = env->new_string_nolen_raw(env, \"The source type must be Byte.\");\n"
                                              "        env->set_exception(env, exception);\n"
                                              "        exception_flag = 1;\n"
                                              "      }\n"
                                              "    }\n"
                                              "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_SHORT_OBJECT_TO_SHORT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                              "    void* object = ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "    if (object == NULL) {\n"
                                              "      void* exception = env->new_string_nolen_raw(env, \"Can't convert undef value.\");\n"
                                              "      env->set_exception(env, exception);\n"
                                              "      exception_flag = 1;\n"
                                              "    }\n"
                                              "    else {\n"
                                              "      int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_offset);\n"
                                              "      int32_t object_type_dimension_id = *(uint8_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_offset);\n"
                                              "      if (object_basic_type_id == (intptr_t)(void*)env->short_object_basic_type_id && object_type_dimension_id == 0) {\n"
                                              "        SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_byte_size);\n"
                                              "        \n");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_SHORT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = *(int16_t*)&fields[0];\n"
                                              "      }\n"
                                              "      else {\n"
                                              "        void* exception = env->new_string_nolen_raw(env, \"The source type must be Short.\");\n"
                                              "        env->set_exception(env, exception);\n"
                                              "        exception_flag = 1;\n"
                                              "      }\n"
                                              "    }\n"
                                              "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_INT_OBJECT_TO_INT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                              "    void* object = ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "    if (object == NULL) {\n"
                                              "      void* exception = env->new_string_nolen_raw(env, \"Can't convert undef value.\");\n"
                                              "      env->set_exception(env, exception);\n"
                                              "      exception_flag = 1;\n"
                                              "    }\n"
                                              "    else {\n"
                                              "      int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_offset);\n"
                                              "      int32_t object_type_dimension_id = *(uint8_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_offset);\n"
                                              "      if (object_basic_type_id == (intptr_t)(void*)env->int_object_basic_type_id && object_type_dimension_id == 0) {\n"
                                              "        SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_byte_size);\n"
                                              "        \n");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = *(int32_t*)&fields[0];\n"
                                              "      }\n"
                                              "      else {\n"
                                              "        void* exception = env->new_string_nolen_raw(env, \"The source type must be Int.\");\n"
                                              "        env->set_exception(env, exception);\n"
                                              "        exception_flag = 1;\n"
                                              "      }\n"
                                              "    }\n"
                                              "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_LONG_OBJECT_TO_LONG: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                              "    void* object = ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "    if (object == NULL) {\n"
                                              "      void* exception = env->new_string_nolen_raw(env, \"Can't convert undef value.\");\n"
                                              "      env->set_exception(env, exception);\n"
                                              "      exception_flag = 1;\n"
                                              "    }\n"
                                              "    else {\n"
                                              "      int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_offset);\n"
                                              "      int32_t object_type_dimension_id = *(uint8_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_offset);\n"
                                              "      if (object_basic_type_id == (intptr_t)(void*)env->long_object_basic_type_id && object_type_dimension_id == 0) {\n"
                                              "        SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_byte_size);\n"
                                              "        \n");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = *(int64_t*)&fields[0];\n"
                                              "      }\n"
                                              "      else {\n"
                                              "        void* exception = env->new_string_nolen_raw(env, \"The source type must be Long.\");\n"
                                              "        env->set_exception(env, exception);\n"
                                              "        exception_flag = 1;\n"
                                              "      }\n"
                                              "    }\n"
                                              "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_FLOAT_OBJECT_TO_FLOAT: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                              "    void* object = ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "    if (object == NULL) {\n"
                                              "      void* exception = env->new_string_nolen_raw(env, \"Can't convert undef value.\");\n"
                                              "      env->set_exception(env, exception);\n"
                                              "      exception_flag = 1;\n"
                                              "    }\n"
                                              "    else {\n"
                                              "      int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_offset);\n"
                                              "      int32_t object_type_dimension_id = *(uint8_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_offset);\n"
                                              "      if (object_basic_type_id == (intptr_t)(void*)env->float_object_basic_type_id && object_type_dimension_id == 0) {\n"
                                              "        SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_byte_size);\n"
                                              "        \n");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = *(float*)&fields[0];\n"
                                              "      }\n"
                                              "      else {\n"
                                              "        void* exception = env->new_string_nolen_raw(env, \"The source type must be Float.\");\n"
                                              "        env->set_exception(env, exception);\n"
                                              "        exception_flag = 1;\n"
                                              "      }\n"
                                              "    }\n"
                                              "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_OBJECT_TO_DOUBLE: {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                              "    void* object = ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "    if (object == NULL) {\n"
                                              "      void* exception = env->new_string_nolen_raw(env, \"Can't convert undef value.\");\n"
                                              "      env->set_exception(env, exception);\n"
                                              "      exception_flag = 1;\n"
                                              "    }\n"
                                              "    else {\n"
                                              "      int32_t object_basic_type_id = *(int32_t*)((intptr_t)object + (intptr_t)env->object_basic_type_id_offset);\n"
                                              "      int32_t object_type_dimension_id = *(uint8_t*)((intptr_t)object + (intptr_t)env->object_type_dimension_offset);\n"
                                              "      if (object_basic_type_id == (intptr_t)(void*)env->double_object_basic_type_id && object_type_dimension_id == 0) {\n"
                                              "        SPVM_VALUE* fields = (SPVM_VALUE*)((intptr_t)object + object_header_byte_size);\n"
                                              "        \n");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE, opcode->operand0);
        SPVM_STRING_BUFFER_add(string_buffer, " = *(double*)&fields[0];\n"
                                              "      }\n"
                                              "      else {\n"
                                              "        void* exception = env->new_string_nolen_raw(env, \"The source type must be Double.\");\n"
                                              "        env->set_exception(env, exception);\n"
                                              "        exception_flag = 1;\n"
                                              "      }\n"
                                              "    }\n"
                                              "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_HAS_IMPLEMENT: {
        int32_t implement_method_id = opcode->operand2;
        int32_t implement_method_name_id = SPVM_API_RUNTIME_get_method_name_id(env->runtime, implement_method_id);
        const char* implement_method_name = SPVM_API_RUNTIME_get_name(env->runtime, implement_method_name_id);

        int32_t interface_basic_type_id = opcode->operand3;
        int32_t interface_basic_type_class_id = SPVM_API_RUNTIME_get_basic_type_class_id(env->runtime, interface_basic_type_id);

        int32_t interface_class_id = SPVM_API_RUNTIME_get_basic_type_class_id(env->runtime, interface_basic_type_class_id);
        int32_t interface_class_name_id = SPVM_API_RUNTIME_get_class_name_id(env->runtime, interface_class_id);
        const char* interface_class_name = SPVM_API_RUNTIME_get_name(env->runtime, interface_class_name_id);
        
        int32_t interface_method_id = SPVM_API_RUNTIME_get_method_id_by_name(env->runtime, interface_class_name, implement_method_name);
        int32_t interface_method_signature_id = SPVM_API_RUNTIME_get_method_signature_id(env->runtime, interface_method_id);
        const char* interface_method_signature = SPVM_API_RUNTIME_get_name(env->runtime, interface_method_signature_id);

        const char* implement_method_signature = interface_method_signature;
        
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                              "    void* object = ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, opcode->operand1);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                              "    int32_t call_method_id = env->get_instance_method_id(env, object, ");
        SPVM_STRING_BUFFER_add(string_buffer, implement_method_name);
        SPVM_STRING_BUFFER_add(string_buffer, ", ");
        SPVM_STRING_BUFFER_add(string_buffer, implement_method_signature);
        SPVM_STRING_BUFFER_add(string_buffer, ");"
                                              "    ");
        SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, 0);
        SPVM_STRING_BUFFER_add(string_buffer, "  call_method_id >= 0;\n"
                                              "  }\n");

        break;
      }
      default:
        assert(0);
    }
    opcode_index++;
  }
  
  // No exception
  SPVM_STRING_BUFFER_add(string_buffer, "  if (!exception_flag) {\n");
  int32_t method_return_type_can_assign_to_any_object = SPVM_API_RUNTIME_get_type_is_object(env->runtime, method_return_type_id);
  if (method_return_type_can_assign_to_any_object) {
    SPVM_STRING_BUFFER_add(string_buffer, "    if (stack[0].oval != NULL) { SPVM_API_DEC_REF_COUNT_ONLY(stack[0].oval); }\n");
  }
  SPVM_STRING_BUFFER_add(string_buffer, "  }\n"
  "  return exception_flag;\n"
                                        "}\n"
                                        "\n");
}

const char* SPVM_PRECOMPILE_get_ctype_name(SPVM_ENV* env, int32_t ctype_id) {
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

void SPVM_PRECOMPILE_add_var(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t index) {
  
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
    case SPVM_PRECOMPILE_C_CTYPE_ID_BOOL_OBJECT:
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

void SPVM_PRECOMPILE_add_var_value(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t index, int32_t field_index) {
  switch (ctype_id) {
    case SPVM_PRECOMPILE_C_CTYPE_ID_BYTE: {
      SPVM_STRING_BUFFER_add(string_buffer, "byte_vars[");
      SPVM_STRING_BUFFER_add_int(string_buffer, index + field_index);
      SPVM_STRING_BUFFER_add(string_buffer, "]");
      break;
    }
    case SPVM_PRECOMPILE_C_CTYPE_ID_SHORT: {
      SPVM_STRING_BUFFER_add(string_buffer, "short_vars[");
      SPVM_STRING_BUFFER_add_int(string_buffer, index + field_index);
      SPVM_STRING_BUFFER_add(string_buffer, "]");
      break;
    }
    case SPVM_PRECOMPILE_C_CTYPE_ID_INT: {
      SPVM_STRING_BUFFER_add(string_buffer, "int_vars[");
      SPVM_STRING_BUFFER_add_int(string_buffer, index + field_index);
      SPVM_STRING_BUFFER_add(string_buffer, "]");
      break;
    }
    case SPVM_PRECOMPILE_C_CTYPE_ID_LONG: {
      SPVM_STRING_BUFFER_add(string_buffer, "long_vars[");
      SPVM_STRING_BUFFER_add_int(string_buffer, index + field_index);
      SPVM_STRING_BUFFER_add(string_buffer, "]");
      break;
    }
    case SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT: {
      SPVM_STRING_BUFFER_add(string_buffer, "float_vars[");
      SPVM_STRING_BUFFER_add_int(string_buffer, index + field_index);
      SPVM_STRING_BUFFER_add(string_buffer, "]");
      break;
    }
    case SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE: {
      SPVM_STRING_BUFFER_add(string_buffer, "double_vars[");
      SPVM_STRING_BUFFER_add_int(string_buffer, index + field_index);
      SPVM_STRING_BUFFER_add(string_buffer, "]");
      break;
    }
    default:
      assert(0);
  }
}

void SPVM_PRECOMPILE_add_operand(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t var_index) {
  SPVM_PRECOMPILE_add_var(env, string_buffer, ctype_id, var_index);
}

void SPVM_PRECOMPILE_add_operand_deref(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t var_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "*(");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_PRECOMPILE_get_ctype_name(env, ctype_id));
  SPVM_STRING_BUFFER_add(string_buffer, "*)*(void**)&");
  SPVM_PRECOMPILE_add_var(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_REF, var_index);
}

void SPVM_PRECOMPILE_add_stack(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t var_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "*(");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_PRECOMPILE_get_ctype_name(env, ctype_id));
  SPVM_STRING_BUFFER_add(string_buffer, "*)&");
  SPVM_STRING_BUFFER_add(string_buffer, "stack[");
  SPVM_STRING_BUFFER_add_int(string_buffer, var_index);
  SPVM_STRING_BUFFER_add(string_buffer, "]");
}

void SPVM_PRECOMPILE_add_operand_value(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t var_index, int32_t field_index) {
  SPVM_PRECOMPILE_add_var_value(env, string_buffer, ctype_id, var_index, field_index);
}

void SPVM_PRECOMPILE_add_bool(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t in_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, 0);
  if (ctype_id == SPVM_PRECOMPILE_C_CTYPE_ID_INT) {
    SPVM_STRING_BUFFER_add(string_buffer, " = ");
    SPVM_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in_index);
    SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  }
  else if (ctype_id == SPVM_PRECOMPILE_C_CTYPE_ID_BOOL_OBJECT) {
    SPVM_STRING_BUFFER_add(string_buffer, " = !!env->get_bool_object_value(env, ");
    SPVM_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in_index);
    SPVM_STRING_BUFFER_add(string_buffer, ");\n");
  }
  else {
    SPVM_STRING_BUFFER_add(string_buffer, " = !!");
    SPVM_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in_index);
    SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  }
}

void SPVM_PRECOMPILE_add_numeric_eq(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, 0);
  SPVM_STRING_BUFFER_add(string_buffer, " = (");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " == ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, ");\n");
}

void SPVM_PRECOMPILE_add_numeric_ne(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, 0);
  SPVM_STRING_BUFFER_add(string_buffer, " = (");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " != ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, ");\n");
}

void SPVM_PRECOMPILE_add_numeric_gt(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, 0);
  SPVM_STRING_BUFFER_add(string_buffer, " = (");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " > ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, ");\n");
}

void SPVM_PRECOMPILE_add_numeric_ge(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, 0);
  SPVM_STRING_BUFFER_add(string_buffer, " = (");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " >= ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, ");\n");
}

void SPVM_PRECOMPILE_add_numeric_lt(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, 0);
  SPVM_STRING_BUFFER_add(string_buffer, " = (");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " < ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, ");\n");
}

void SPVM_PRECOMPILE_add_numeric_le(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, 0);
  SPVM_STRING_BUFFER_add(string_buffer, " = (");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " <= ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, ");\n");
}

void SPVM_PRECOMPILE_add_numeric_cmp(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t in1_index, int32_t in2_index) {

  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, 0);
  SPVM_STRING_BUFFER_add(string_buffer, " = ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " > ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, " ? 1\n");
  SPVM_STRING_BUFFER_add(string_buffer, "            : ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " < ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, " ? -1\n");
  SPVM_STRING_BUFFER_add(string_buffer, "            : 0;\n");
}

void SPVM_PRECOMPILE_add_add(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " + ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_PRECOMPILE_add_subtract(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " - ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_PRECOMPILE_add_multiply(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " * ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_PRECOMPILE_add_divide_integral(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  if (__builtin_expect(");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, " == 0, 0)) { \n"
                                        "    env->set_exception(env, env->new_string_nolen_raw(env, \"0 division\"));\n"
                                        "    exception_flag = 1;\n"
                                        "  } else {\n"
                                        "    ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " / ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  } \n");
}

void SPVM_PRECOMPILE_add_divide_unsigned_int(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  if (__builtin_expect(");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, " == 0, 0)) { \n"
                                        "    env->set_exception(env, env->new_string_nolen_raw(env, \"0 division\"));\n"
                                        "    exception_flag = 1;\n"
                                        "  } else {\n"
                                        "    ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = (uint32_t)");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " / (uint32_t)");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  } \n");
}

void SPVM_PRECOMPILE_add_divide_unsigned_long(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  if (__builtin_expect(");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, " == 0, 0)) { \n"
                                        "    env->set_exception(env, env->new_string_nolen_raw(env, \"0 division\"));\n"
                                        "    exception_flag = 1;\n"
                                        "  } else {\n"
                                        "    ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = (uint64_t)");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " / (uint64_t)");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  } \n");
}

void SPVM_PRECOMPILE_add_divide_floating_point(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " / ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_PRECOMPILE_add_remainder_integral(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  if (__builtin_expect(");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, " == 0, 0)) {\n"
                                        "    void* exception = env->new_string_nolen_raw(env, \"0 division\");\n"
                                        "    env->set_exception(env, exception);\n"
                                        "    exception_flag = 1;\n"
                                        "  }\n"
                                        "  else {\n"
                                        "    ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " % /* REMAINDER */ "); // % have undarstandable bug.
  SPVM_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
}

void SPVM_PRECOMPILE_add_remainder_unsigned_int(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  if (__builtin_expect(");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, " == 0, 0)) {\n"
                                        "    void* exception = env->new_string_nolen_raw(env, \"0 division\");\n"
                                        "    env->set_exception(env, exception);\n"
                                        "    exception_flag = 1;\n"
                                        "  }\n"
                                        "  else {\n"
                                        "    ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = (uint32_t)");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " % /* REMAINDER */ (uint32_t)"); // % have undarstandable bug.
  SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                        "  }\n");
}

void SPVM_PRECOMPILE_add_remainder_unsigned_long(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  if (__builtin_expect(");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, " == 0, 0)) {\n"
                                        "    void* exception = env->new_string_nolen_raw(env, \"0 division\");\n"
                                        "    env->set_exception(env, exception);\n"
                                        "    exception_flag = 1;\n"
                                        "  }\n"
                                        "  else {\n"
                                        "    ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = (uint64_t)");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " % /* REMAINDER */ (uint64_t)"); // % have undarstandable bug.
  SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_LONG, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
}

void SPVM_PRECOMPILE_add_left_shift(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = (");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " << ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, in2_index);
  if (ctype_id == SPVM_PRECOMPILE_C_CTYPE_ID_INT) {
    SPVM_STRING_BUFFER_add(string_buffer, ")");
  }
  else if (ctype_id == SPVM_PRECOMPILE_C_CTYPE_ID_LONG) {
    SPVM_STRING_BUFFER_add(string_buffer, ")");
  }
  else {
    assert(0);
  }
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_PRECOMPILE_add_right_logical_shift(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = ((");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_PRECOMPILE_get_ctype_name(env, ctype_id));
  SPVM_STRING_BUFFER_add(string_buffer, ")((u");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_PRECOMPILE_get_ctype_name(env, ctype_id));
  SPVM_STRING_BUFFER_add(string_buffer, ")");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " >> ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, in2_index);
  if (ctype_id == SPVM_PRECOMPILE_C_CTYPE_ID_INT) {
    SPVM_STRING_BUFFER_add(string_buffer, ")");
  }
  else if (ctype_id == SPVM_PRECOMPILE_C_CTYPE_ID_LONG) {
    SPVM_STRING_BUFFER_add(string_buffer, ")");
  }
  else {
    assert(0);
  }
  SPVM_STRING_BUFFER_add(string_buffer, ");\n");
}

void SPVM_PRECOMPILE_add_right_arithmetic_shift(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = (");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " >> ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, in2_index);
  if (ctype_id == SPVM_PRECOMPILE_C_CTYPE_ID_INT) {
    SPVM_STRING_BUFFER_add(string_buffer, ")");
  }
  else if (ctype_id == SPVM_PRECOMPILE_C_CTYPE_ID_LONG) {
    SPVM_STRING_BUFFER_add(string_buffer, ")");
  }
  else {
    assert(0);
  }
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_PRECOMPILE_add_bit_and(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " & ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_PRECOMPILE_add_bit_or(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " | ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_PRECOMPILE_add_bit_xor(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in1_index);
  SPVM_STRING_BUFFER_add(string_buffer, " ^ ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in2_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_PRECOMPILE_add_negate(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = -");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_PRECOMPILE_add_plus(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_PRECOMPILE_add_complement(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = ~");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_PRECOMPILE_add_inc(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t number) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " += ");
  SPVM_STRING_BUFFER_add_int(string_buffer, number);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_PRECOMPILE_add_convert(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t out_ctype_id, int32_t in_ctype_id, int32_t out_index, int32_t in_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, out_ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = (");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_PRECOMPILE_get_ctype_name(env, out_ctype_id));
  SPVM_STRING_BUFFER_add(string_buffer, ")");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, in_ctype_id, in_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_PRECOMPILE_add_array_fetch(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t element_ctype_id, int32_t out_index, int32_t array_index, int32_t index_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                        "    void* array = ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, array_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                        "    int32_t index = ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, index_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                        "    if (__builtin_expect(array == NULL, 0)) { \n"
                                        "      env->set_exception(env, env->new_string_nolen_raw(env, \"Array must not be undef\")); \n"
                                        "      exception_flag = 1;\n"
                                        "    } \n"
                                        "    else { \n"
                                        "      if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) { \n"
                                        "        env->set_exception(env, env->new_string_nolen_raw(env, \"Index is out of range\")); \n"
                                        "        exception_flag = 1;\n"
                                        "      } \n"
                                        "      else { \n"
                                        "        ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, element_ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = ((");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_PRECOMPILE_get_ctype_name(env, element_ctype_id));
  SPVM_STRING_BUFFER_add(string_buffer, "*)((intptr_t)array + object_header_byte_size))[index];\n"
                                        "      } \n"
                                        "    } \n"
                                        "  } \n");
}

void SPVM_PRECOMPILE_add_array_store(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t element_ctype_id, int32_t array_index, int32_t index_index, int32_t in_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                        "    void* array = ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, array_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                        "    int32_t index = ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, index_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                        "    if (__builtin_expect(array == NULL, 0)) { \n"
                                        "      env->set_exception(env, env->new_string_nolen_raw(env, \"Array must not be undef\")); \n"
                                        "      exception_flag = 1;\n"
                                        "    } \n"
                                        "    else { \n"
                                        "      if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) { \n"
                                        "        env->set_exception(env, env->new_string_nolen_raw(env, \"Index is out of range\")); \n"
                                        "        exception_flag = 1;\n"
                                        "      } \n"
                                        "      else { \n"
                                        "((");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_PRECOMPILE_get_ctype_name(env, element_ctype_id));
  SPVM_STRING_BUFFER_add(string_buffer, "*)((intptr_t)array + object_header_byte_size))[index] = ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, element_ctype_id, in_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                        "      } \n"
                                        "    } \n"
                                        "  } \n");
}

void SPVM_PRECOMPILE_add_mulnum_array_fetch(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t element_ctype_id, int32_t out_index, int32_t array_index, int32_t index_index, int32_t fields_length) {
  SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                        "    void* array = ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, array_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                        "    int32_t index = ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, index_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                        "    if (__builtin_expect(array == NULL, 0)) { \n"
                                        "      env->set_exception(env, env->new_string_nolen_raw(env, \"Array must not be undef\")); \n"
                                        "      exception_flag = 1;\n"
                                        "    } \n"
                                        "    else { \n"
                                        "      if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) { \n"
                                        "        env->set_exception(env, env->new_string_nolen_raw(env, \"Index is out of range\")); \n"
                                        "        exception_flag = 1;\n"
                                        "      } \n"
                                        "      else { \n");
  {
    int32_t field_index;
    for (field_index = 0; field_index < fields_length; field_index++) {
      SPVM_STRING_BUFFER_add(string_buffer, "        ");
      SPVM_PRECOMPILE_add_operand_value(env, string_buffer, element_ctype_id, out_index, field_index);
      SPVM_STRING_BUFFER_add(string_buffer, " = ((");
      SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_PRECOMPILE_get_ctype_name(env, element_ctype_id));
      SPVM_STRING_BUFFER_add(string_buffer, "*)((intptr_t)array + object_header_byte_size))[");
      SPVM_STRING_BUFFER_add_int(string_buffer, fields_length);
      SPVM_STRING_BUFFER_add(string_buffer, " * index + ");
      SPVM_STRING_BUFFER_add_int(string_buffer, field_index);
      SPVM_STRING_BUFFER_add(string_buffer, "]; \n");
    }
  }
  SPVM_STRING_BUFFER_add(string_buffer, "      } \n"
                                        "    } \n"
                                        "  } \n");
}

void SPVM_PRECOMPILE_add_mulnum_array_field_fetch(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t element_ctype_id, int32_t out_index, int32_t array_index, int32_t index_index, int32_t fields_length, int32_t field_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                        "    void* array = ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, array_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    int32_t index = ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, index_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                        "    if (__builtin_expect(array == NULL, 0)) { \n"
                                        "      env->set_exception(env, env->new_string_nolen_raw(env, \"Array must not be undef\")); \n"
                                        "      exception_flag = 1;\n"
                                        "    } \n"
                                        "    else { \n"
                                        "      if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) { \n"
                                        "        env->set_exception(env, env->new_string_nolen_raw(env, \"Index is out of range\")); \n"
                                        "        exception_flag = 1;\n"
                                        "      } \n"
                                        "      else { \n"
                                        "        ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, element_ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = ((");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_PRECOMPILE_get_ctype_name(env, element_ctype_id));
  SPVM_STRING_BUFFER_add(string_buffer, "*)((intptr_t)array + object_header_byte_size))[");
  SPVM_STRING_BUFFER_add_int(string_buffer, fields_length);
  SPVM_STRING_BUFFER_add(string_buffer, " * index + ");
  SPVM_STRING_BUFFER_add_int(string_buffer, field_index);
  SPVM_STRING_BUFFER_add(string_buffer, "]; \n"
                                        "      } \n"
                                        "    } \n"
                                        "  } \n");
}

void SPVM_PRECOMPILE_add_mulnum_array_store(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t element_ctype_id, int32_t array_index, int32_t index_index, int32_t in_index, int32_t fields_length) {
  SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                        "    void* array = ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, array_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                        "    int32_t index = ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, index_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                        "    if (__builtin_expect(array == NULL, 0)) { \n"
                                        "      env->set_exception(env, env->new_string_nolen_raw(env, \"Array must not be undef\")); \n"
                                        "      exception_flag = 1;\n"
                                        "    } \n"
                                        "    else { \n"
                                        "      if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) { \n"
                                        "        env->set_exception(env, env->new_string_nolen_raw(env, \"Index is out of range\")); \n"
                                        "        exception_flag = 1;\n"
                                        "      } \n"
                                        "      else { \n");
  
  {
    int32_t field_index;
    for (field_index = 0; field_index < fields_length; field_index++) {
      SPVM_STRING_BUFFER_add(string_buffer, "      ((");
      SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_PRECOMPILE_get_ctype_name(env, element_ctype_id));
      SPVM_STRING_BUFFER_add(string_buffer, "*)((intptr_t)array + object_header_byte_size))[");
      SPVM_STRING_BUFFER_add_int(string_buffer, fields_length);
      SPVM_STRING_BUFFER_add(string_buffer, " * index + ");
      SPVM_STRING_BUFFER_add_int(string_buffer, field_index);
      SPVM_STRING_BUFFER_add(string_buffer, "] = ");
      SPVM_PRECOMPILE_add_operand_value(env, string_buffer, element_ctype_id, in_index, field_index);
      SPVM_STRING_BUFFER_add(string_buffer, ";\n");
    }
  }

  SPVM_STRING_BUFFER_add(string_buffer, "      } \n"
                                        "    } \n"
                                        "  } \n");
}

void SPVM_PRECOMPILE_add_mulnum_array_field_store(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t element_ctype_id, int32_t array_index, int32_t index_index, int32_t in_index, int32_t fields_length, int32_t field_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                        "    void* array = ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, array_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                        "    int32_t index = ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_INT, index_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                        "    if (__builtin_expect(array == NULL, 0)) { \n"
                                        "      env->set_exception(env, env->new_string_nolen_raw(env, \"Array must not be undef\")); \n"
                                        "      exception_flag = 1;\n"
                                        "    } \n"
                                        "    else { \n"
                                        "      if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_length_offset), 0)) { \n"
                                        "        env->set_exception(env, env->new_string_nolen_raw(env, \"Index is out of range\")); \n"
                                        "        exception_flag = 1;\n"
                                        "      } \n"
                                        "      else { \n"
                                        "        ((");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_PRECOMPILE_get_ctype_name(env, element_ctype_id));
  SPVM_STRING_BUFFER_add(string_buffer, "*)((intptr_t)array + object_header_byte_size))[");
  SPVM_STRING_BUFFER_add_int(string_buffer, fields_length);
  SPVM_STRING_BUFFER_add(string_buffer, " * index + ");
  SPVM_STRING_BUFFER_add_int(string_buffer, field_index);
  SPVM_STRING_BUFFER_add(string_buffer, "] = ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, element_ctype_id, in_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                        "      }\n"
                                        "    }\n"
                                        "  }\n");
}

void SPVM_PRECOMPILE_add_mulnum_deref(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t element_ctype_id, int32_t out_var_id, int32_t ref_var_id, int32_t fields_length) {

  SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
  switch (element_ctype_id) {
    case SPVM_PRECOMPILE_C_CTYPE_ID_BYTE: {
      SPVM_STRING_BUFFER_add(string_buffer, "    int8_t* value_ref = *(int8_t**)&ref_vars[");
      break;
    }
    case SPVM_PRECOMPILE_C_CTYPE_ID_SHORT: {
      SPVM_STRING_BUFFER_add(string_buffer, "    int16_t* value_ref = *(int16_t**)&ref_vars[");
      break;
    }
    case SPVM_PRECOMPILE_C_CTYPE_ID_INT: {
      SPVM_STRING_BUFFER_add(string_buffer, "    int32_t* value_ref = *(int32_t**)&ref_vars[");
      break;
    }
    case SPVM_PRECOMPILE_C_CTYPE_ID_LONG: {
      SPVM_STRING_BUFFER_add(string_buffer, "    int64_t* value_ref = *(int64_t**)&ref_vars[");
      break;
    }
    case SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT: {
      SPVM_STRING_BUFFER_add(string_buffer, "    float* value_ref = *(float**)&ref_vars[");
      break;
    }
    case SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE: {
      SPVM_STRING_BUFFER_add(string_buffer, "    double* value_ref = *(double**)&ref_vars[");
      break;
    }
  }
  SPVM_STRING_BUFFER_add_int(string_buffer, ref_var_id);
  SPVM_STRING_BUFFER_add(string_buffer, "];\n");
  for (int32_t field_index = 0; field_index < fields_length; field_index++) {
    SPVM_STRING_BUFFER_add(string_buffer, "    *(");
    SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_PRECOMPILE_get_ctype_name(env, element_ctype_id));
    SPVM_STRING_BUFFER_add(string_buffer, "*)&");
    switch (element_ctype_id) {
      case SPVM_PRECOMPILE_C_CTYPE_ID_BYTE: {
        SPVM_STRING_BUFFER_add(string_buffer, "byte_vars");
        break;
      }
      case SPVM_PRECOMPILE_C_CTYPE_ID_SHORT: {
        SPVM_STRING_BUFFER_add(string_buffer, "short_vars");
        break;
      }
      case SPVM_PRECOMPILE_C_CTYPE_ID_INT: {
        SPVM_STRING_BUFFER_add(string_buffer, "int_vars");
        break;
      }
      case SPVM_PRECOMPILE_C_CTYPE_ID_LONG: {
        SPVM_STRING_BUFFER_add(string_buffer, "long_vars");
        break;
      }
      case SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT: {
        SPVM_STRING_BUFFER_add(string_buffer, "float_vars");
        break;
      }
      case SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE: {
        SPVM_STRING_BUFFER_add(string_buffer, "double_vars");
        break;
      }
    }
    SPVM_STRING_BUFFER_add(string_buffer, "[");
    SPVM_STRING_BUFFER_add_int(string_buffer, out_var_id);
    SPVM_STRING_BUFFER_add(string_buffer, " + ");
    SPVM_STRING_BUFFER_add_int(string_buffer, field_index);
    SPVM_STRING_BUFFER_add(string_buffer, "]  = *(");
    SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_PRECOMPILE_get_ctype_name(env, element_ctype_id));
    SPVM_STRING_BUFFER_add(string_buffer, "*)&value_ref[");
    SPVM_STRING_BUFFER_add_int(string_buffer, field_index);
    SPVM_STRING_BUFFER_add(string_buffer, "];\n");
  }
  SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
}

void SPVM_PRECOMPILE_add_mulnum_deref_get_field(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t element_ctype_id, int32_t out_var_id, int32_t ref_var_id, int32_t field_index) {

  SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
  switch (element_ctype_id) {
    case SPVM_PRECOMPILE_C_CTYPE_ID_BYTE: {
      SPVM_STRING_BUFFER_add(string_buffer, "    int8_t* value_ref = *(int8_t**)&ref_vars[");
      break;
    }
    case SPVM_PRECOMPILE_C_CTYPE_ID_SHORT: {
      SPVM_STRING_BUFFER_add(string_buffer, "    int16_t* value_ref = *(int16_t**)&ref_vars[");
      break;
    }
    case SPVM_PRECOMPILE_C_CTYPE_ID_INT: {
      SPVM_STRING_BUFFER_add(string_buffer, "    int32_t* value_ref = *(int32_t**)&ref_vars[");
      break;
    }
    case SPVM_PRECOMPILE_C_CTYPE_ID_LONG: {
      SPVM_STRING_BUFFER_add(string_buffer, "    int64_t* value_ref = *(int64_t**)&ref_vars[");
      break;
    }
    case SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT: {
      SPVM_STRING_BUFFER_add(string_buffer, "    float* value_ref = *(float**)&ref_vars[");
      break;
    }
    case SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE: {
      SPVM_STRING_BUFFER_add(string_buffer, "    double* value_ref = *(double**)&ref_vars[");
      break;
    }
  }
  SPVM_STRING_BUFFER_add_int(string_buffer, ref_var_id);
  SPVM_STRING_BUFFER_add(string_buffer, "];\n"
                                        "    *(");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_PRECOMPILE_get_ctype_name(env, element_ctype_id));
  SPVM_STRING_BUFFER_add(string_buffer, "*)&");
  switch (element_ctype_id) {
    case SPVM_PRECOMPILE_C_CTYPE_ID_BYTE: {
      SPVM_STRING_BUFFER_add(string_buffer, "byte_vars");
      break;
    }
    case SPVM_PRECOMPILE_C_CTYPE_ID_SHORT: {
      SPVM_STRING_BUFFER_add(string_buffer, "short_vars");
      break;
    }
    case SPVM_PRECOMPILE_C_CTYPE_ID_INT: {
      SPVM_STRING_BUFFER_add(string_buffer, "int_vars");
      break;
    }
    case SPVM_PRECOMPILE_C_CTYPE_ID_LONG: {
      SPVM_STRING_BUFFER_add(string_buffer, "long_vars");
      break;
    }
    case SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT: {
      SPVM_STRING_BUFFER_add(string_buffer, "float_vars");
      break;
    }
    case SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE: {
      SPVM_STRING_BUFFER_add(string_buffer, "double_vars");
      break;
    }
  }
  SPVM_STRING_BUFFER_add(string_buffer, "[");
  SPVM_STRING_BUFFER_add_int(string_buffer, out_var_id);
  SPVM_STRING_BUFFER_add(string_buffer, "] = *(");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_PRECOMPILE_get_ctype_name(env, element_ctype_id));
  SPVM_STRING_BUFFER_add(string_buffer, "*)&value_ref[");
  SPVM_STRING_BUFFER_add_int(string_buffer, field_index);
  SPVM_STRING_BUFFER_add(string_buffer, "];\n"
                                        "  }\n");
}

void SPVM_PRECOMPILE_add_mulnum_deref_set_field(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t element_ctype_id, int32_t ref_var_id, int32_t in_var_id, int32_t field_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
  switch (element_ctype_id) {
    case SPVM_PRECOMPILE_C_CTYPE_ID_BYTE: {
      SPVM_STRING_BUFFER_add(string_buffer, "    int8_t* value_ref = *(int8_t**)&ref_vars[");
      break;
    }
    case SPVM_PRECOMPILE_C_CTYPE_ID_SHORT: {
      SPVM_STRING_BUFFER_add(string_buffer, "    int16_t* value_ref = *(int16_t**)&ref_vars[");
      break;
    }
    case SPVM_PRECOMPILE_C_CTYPE_ID_INT: {
      SPVM_STRING_BUFFER_add(string_buffer, "    int32_t* value_ref = *(int32_t**)&ref_vars[");
      break;
    }
    case SPVM_PRECOMPILE_C_CTYPE_ID_LONG: {
      SPVM_STRING_BUFFER_add(string_buffer, "    int64_t* value_ref = *(int64_t**)&ref_vars[");
      break;
    }
    case SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT: {
      SPVM_STRING_BUFFER_add(string_buffer, "    float* value_ref = *(float**)&ref_vars[");
      break;
    }
    case SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE: {
      SPVM_STRING_BUFFER_add(string_buffer, "    double* value_ref = *(double**)&ref_vars[");
      break;
    }
  }
  SPVM_STRING_BUFFER_add_int(string_buffer, ref_var_id);
  SPVM_STRING_BUFFER_add(string_buffer, "];\n"
                                        "    *(");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_PRECOMPILE_get_ctype_name(env, element_ctype_id));
  SPVM_STRING_BUFFER_add(string_buffer, "*)&value_ref[");
  SPVM_STRING_BUFFER_add_int(string_buffer, field_index);
  SPVM_STRING_BUFFER_add(string_buffer, "] = *(");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_PRECOMPILE_get_ctype_name(env, element_ctype_id));
  SPVM_STRING_BUFFER_add(string_buffer, "*)&");
  switch (element_ctype_id) {
    case SPVM_PRECOMPILE_C_CTYPE_ID_BYTE: {
      SPVM_STRING_BUFFER_add(string_buffer, "byte_vars");
      break;
    }
    case SPVM_PRECOMPILE_C_CTYPE_ID_SHORT: {
      SPVM_STRING_BUFFER_add(string_buffer, "short_vars");
      break;
    }
    case SPVM_PRECOMPILE_C_CTYPE_ID_INT: {
      SPVM_STRING_BUFFER_add(string_buffer, "int_vars");
      break;
    }
    case SPVM_PRECOMPILE_C_CTYPE_ID_LONG: {
      SPVM_STRING_BUFFER_add(string_buffer, "long_vars");
      break;
    }
    case SPVM_PRECOMPILE_C_CTYPE_ID_FLOAT: {
      SPVM_STRING_BUFFER_add(string_buffer, "float_vars");
      break;
    }
    case SPVM_PRECOMPILE_C_CTYPE_ID_DOUBLE: {
      SPVM_STRING_BUFFER_add(string_buffer, "double_vars");
      break;
    }
  }
  SPVM_STRING_BUFFER_add(string_buffer, "[");
  SPVM_STRING_BUFFER_add_int(string_buffer, in_var_id);
  SPVM_STRING_BUFFER_add(string_buffer, "];\n"
                                        "  }\n");
}

void SPVM_PRECOMPILE_add_move(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_PRECOMPILE_add_get_deref(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = ");
  SPVM_PRECOMPILE_add_operand_deref(env, string_buffer, ctype_id, in_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_PRECOMPILE_add_set_deref(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t ctype_id, int32_t out_index, int32_t in_index) {
  SPVM_STRING_BUFFER_add(string_buffer, "  ");
  SPVM_PRECOMPILE_add_operand_deref(env, string_buffer, ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, ctype_id, in_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
}

void SPVM_PRECOMPILE_add_get_field(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t field_ctype_id, int32_t out_index, int32_t object_index, int32_t field_id) {
  
  int32_t field_class_id = SPVM_API_RUNTIME_get_field_class_id(env->runtime, field_id);
  int32_t field_class_name_id = SPVM_API_RUNTIME_get_class_name_id(env->runtime, field_class_id);
  const char* field_class_name = SPVM_API_RUNTIME_get_name(env->runtime, field_class_name_id);
  int32_t field_name_id = SPVM_API_RUNTIME_get_field_name_id(env->runtime, field_id);
  const char* field_name = SPVM_API_RUNTIME_get_name(env->runtime, field_name_id);
  int32_t field_signature_id = SPVM_API_RUNTIME_get_field_signature_id(env->runtime, field_id);
  const char* field_signature = SPVM_API_RUNTIME_get_name(env->runtime, field_signature_id);

  SPVM_STRING_BUFFER_add(string_buffer, "  {\n"
                                        "    int32_t access_field_id = env->get_field_id(env, \"");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)field_class_name);
  SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)field_name);
  SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)field_signature);
  SPVM_STRING_BUFFER_add(string_buffer, "\");\n"
                                        "    if ("
                                        "access_field_id");
  SPVM_STRING_BUFFER_add(string_buffer, " < 0) {\n");
  SPVM_STRING_BUFFER_add(string_buffer, "      void* exception = env->new_string_nolen_raw(env, \"Field not found ");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)field_class_name);
  SPVM_STRING_BUFFER_add(string_buffer, " ");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)field_name);
  SPVM_STRING_BUFFER_add(string_buffer, "\");\n"
                                        "      env->set_exception(env, exception);\n"
                                        "      exception_flag = 1;\n"
                                        "    }\n"
                                        "    if (!exception_flag) {\n"
                                        "      int32_t access_field_offset"
                                        " = env->get_field_offset(env, "
                                        "access_field_id"
                                        ");\n"
                                        "      void* object = ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, object_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                        "      if (__builtin_expect(object == NULL, 0)) {\n"
                                        "        env->set_exception(env, env->new_string_nolen_raw(env, \"The invocants of getting fields must not be undefined values\"));\n"
                                        "        exception_flag = 1;\n"
                                        "      }\n"
                                        "      else {\n"
                                        "        ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, field_ctype_id, out_index);
  SPVM_STRING_BUFFER_add(string_buffer, " = *(");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_PRECOMPILE_get_ctype_name(env, field_ctype_id));
  SPVM_STRING_BUFFER_add(string_buffer, "*)((intptr_t)object + object_header_byte_size + "
                                        "access_field_offset"
                                        ");\n"
                                        "      }\n"
                                        "    }\n"
                                        "  }\n");
}

void SPVM_PRECOMPILE_add_set_field(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, int32_t field_ctype_id, int32_t object_index, int32_t field_id, int32_t in_index) {
  
  int32_t field_class_id = SPVM_API_RUNTIME_get_field_class_id(env->runtime, field_id);
  int32_t field_class_name_id = SPVM_API_RUNTIME_get_class_name_id(env->runtime, field_class_id);
  const char* field_class_name = SPVM_API_RUNTIME_get_name(env->runtime, field_class_name_id);
  int32_t field_name_id = SPVM_API_RUNTIME_get_field_name_id(env->runtime, field_id);
  const char* field_name = SPVM_API_RUNTIME_get_name(env->runtime, field_name_id);
  int32_t field_signature_id = SPVM_API_RUNTIME_get_field_signature_id(env->runtime, field_id);
  const char* field_signature = SPVM_API_RUNTIME_get_name(env->runtime, field_signature_id);

  SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    int32_t access_field_id = env->get_field_id(env, \"");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)field_class_name);
  SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)field_name);
  SPVM_STRING_BUFFER_add(string_buffer, "\", \"");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)field_signature);
  SPVM_STRING_BUFFER_add(string_buffer, "\");\n"
                                        "    if ("
                                        "access_field_id"
                                        " < 0) {\n"
                                        "      void* exception = env->new_string_nolen_raw(env, \"Field not found ");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)field_class_name);
  SPVM_STRING_BUFFER_add(string_buffer, " ");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)field_name);
  SPVM_STRING_BUFFER_add(string_buffer, "\");\n"
                                        "      env->set_exception(env, exception);\n"
                                        "      exception_flag = 1;\n"
                                        "    }\n"
                                        "    if (!exception_flag) {\n"
                                        "      int32_t access_field_offset"
                                        " = env->get_field_offset(env, "
                                        "access_field_id"
                                        ");\n"
                                        "      void* object = ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, SPVM_PRECOMPILE_C_CTYPE_ID_OBJECT, object_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                        "      if (__builtin_expect(object == NULL, 0)) {\n"
                                        "        env->set_exception(env, env->new_string_nolen_raw(env, \"Invocants of setting fields must not be undefined values\"));\n"
                                        "        exception_flag = 1;\n"
                                        "      }\n"
                                        "      else {\n"
                                        "        *(");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)SPVM_PRECOMPILE_get_ctype_name(env, field_ctype_id));
  SPVM_STRING_BUFFER_add(string_buffer, "*)((intptr_t)object + object_header_byte_size + access_field_offset) = ");
  SPVM_PRECOMPILE_add_operand(env, string_buffer, field_ctype_id, in_index);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n"
                                        "      }\n"
                                        "    }\n"
                                        "  }\n");
}

