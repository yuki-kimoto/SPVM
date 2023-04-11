// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>

#include "spvm_compiler.h"
#include "spvm_type.h"
#include "spvm_class.h"
#include "spvm_type.h"
#include "spvm_op.h"
#include "spvm_hash.h"
#include "spvm_list.h"
#include "spvm_allocator.h"
#include "spvm_yacc_util.h"
#include "spvm_list.h"
#include "spvm_opcode_array.h"
#include "spvm_method.h"
#include "spvm_field.h"
#include "spvm_class_var.h"
#include "spvm_native.h"
#include "spvm_opcode.h"
#include "spvm_basic_type.h"
#include "spvm_use.h"
#include "spvm_op_checker.h"
#include "spvm_opcode_builder.h"
#include "spvm_object.h"
#include "spvm_var_decl.h"
#include "spvm_string_buffer.h"
#include "spvm_allow.h"
#include "spvm_interface.h"
#include "spvm_class_var_access.h"
#include "spvm_constant.h"
#include "spvm_array_field_access.h"
#include "spvm_field_access.h"
#include "spvm_call_method.h"
#include "spvm_var.h"
#include "spvm_constant_string.h"

#include "spvm_runtime_basic_type.h"
#include "spvm_runtime_class.h"
#include "spvm_runtime_class_var.h"
#include "spvm_runtime_field.h"
#include "spvm_runtime.h"
#include "spvm_runtime_method.h"
#include "spvm_runtime_constant_string.h"
#include "spvm_runtime_type.h"

SPVM_COMPILER* SPVM_COMPILER_new() {
  SPVM_COMPILER* compiler = SPVM_ALLOCATOR_alloc_memory_block_unmanaged(sizeof(SPVM_COMPILER));
  
  // Allocator
  SPVM_ALLOCATOR* allocator = SPVM_ALLOCATOR_new();
  compiler->allocator = allocator;
  
  compiler->bufptr = "";
  
  compiler->constant_strings = SPVM_LIST_new_list_permanent(compiler->allocator, 128);
  compiler->constant_string_symtable = SPVM_HASH_new_hash_permanent(compiler->allocator, 128);
  compiler->constant_strings_buffer = SPVM_STRING_BUFFER_new(compiler->allocator, 8192, SPVM_ALLOCATOR_C_ALLOC_TYPE_PERMANENT);
  
  // Eternal information
  compiler->class_paths = SPVM_LIST_new_list_permanent(compiler->allocator, 0);
  compiler->types = SPVM_LIST_new_list_permanent(compiler->allocator, 0);
  compiler->type_symtable = SPVM_HASH_new_hash_permanent(compiler->allocator, 0);
  compiler->basic_types = SPVM_LIST_new_list_permanent(compiler->allocator, 0);
  compiler->basic_type_symtable = SPVM_HASH_new_hash_permanent(compiler->allocator, 0);
  compiler->methods = SPVM_LIST_new_list_permanent(compiler->allocator, 0);
  compiler->args = SPVM_LIST_new_list_permanent(compiler->allocator, 0);
  compiler->anon_methods = SPVM_LIST_new_list_permanent(compiler->allocator, 0);
  compiler->fields = SPVM_LIST_new_list_permanent(compiler->allocator, 0);
  compiler->classes = SPVM_LIST_new_list_permanent(compiler->allocator, 0);
  compiler->class_symtable = SPVM_HASH_new_hash_permanent(compiler->allocator, 0);
  compiler->class_vars = SPVM_LIST_new_list_permanent(compiler->allocator, 0);
  compiler->opcode_array = SPVM_OPCODE_ARRAY_new(compiler);
  compiler->class_source_symtable = SPVM_HASH_new_hash_permanent(compiler->allocator, 0);
  compiler->switch_infos = SPVM_LIST_new_list_permanent(compiler->allocator, 0);
  compiler->not_found_class_class_symtable = SPVM_HASH_new_hash_permanent(compiler->allocator, 0);
  
  // Add basic types
  SPVM_COMPILER_add_basic_types(compiler);
  
  // Add Bool source
  const char* spvm_bool_class_source = "class Bool {\n  INIT {\n    $TRUE = new Bool;\n    $TRUE->{value} = 1;\n    $FALSE = new Bool;\n    $FALSE->{value} = 0;\n  }\n  \n  our $TRUE : ro Bool;\n  our $FALSE : ro Bool;\n  has value : ro int;\n}";
  SPVM_HASH_set(compiler->class_source_symtable, "Bool", strlen("Bool"), (void*)spvm_bool_class_source);
  
  // Add Error source
  const char* spvm_error_class_source = "class Error;";
  SPVM_HASH_set(compiler->class_source_symtable, "Error", strlen("Error"), (void*)spvm_error_class_source);
  
  // Add Error::System source
  const char* spvm_error_system_class_source = "class Error::System;";
  SPVM_HASH_set(compiler->class_source_symtable, "Error::System", strlen("Error::System"), (void*)spvm_error_system_class_source);
  
  // Add Error::NotSupported source
  const char* spvm_error_not_supported_class_source = "class Error::NotSupported;";
  SPVM_HASH_set(compiler->class_source_symtable, "Error::NotSupported", strlen("Error::NotSupported"), (void*)spvm_error_not_supported_class_source);

  // Add Byte source
  const char* spvm_byte_class_source = "class Byte {\n  has value : rw byte;\n  static method new : Byte ($value : int) {\n    my $self = new Byte;\n    $self->{value} = (byte)$value;\n    return $self;\n  }\n}";
  SPVM_HASH_set(compiler->class_source_symtable, "Byte", strlen("Byte"), (void*)spvm_byte_class_source);
  
  // Add Short source
  const char* spvm_short_class_source = "class Short {\n  has value : rw short;\n  static method new : Short ($value : int) {\n    my $self = new Short;\n    $self->{value} = (short)$value;\n    return $self;\n  }\n}";
  SPVM_HASH_set(compiler->class_source_symtable, "Short", strlen("Short"), (void*)spvm_short_class_source);
  
  // Add Int source
  const char* spvm_int_class_source = "class Int {\n  has value : rw int;\n  static method new : Int ($value : int) {\n    my $self = new Int;\n    $self->{value} = $value;\n    return $self;\n  }\n}";
  SPVM_HASH_set(compiler->class_source_symtable, "Int", strlen("Int"), (void*)spvm_int_class_source);
  
  // Add Long source
  const char* spvm_long_class_source = "class Long {\n  has value : rw long;\n  static method new : Long ($value : long) {\n    my $self = new Long;\n    $self->{value} = $value;\n    return $self;\n  }\n}";
  SPVM_HASH_set(compiler->class_source_symtable, "Long", strlen("Long"), (void*)spvm_long_class_source);
  
  // Add Float source
  const char* spvm_float_class_source = "class Float {\n  has value : rw float;\n  static method new : Float ($value : float) {\n    my $self = new Float;\n    $self->{value} = $value;\n    return $self;\n  }\n}";
  SPVM_HASH_set(compiler->class_source_symtable, "Float", strlen("Float"), (void*)spvm_float_class_source);
  
  // Add Double source
  const char* spvm_double_class_source = "class Double {\n  has value : rw double;\n  static method new : Double ($value : double) {\n    my $self = new Double;\n    $self->{value} = $value;\n    return $self;\n  }\n}";
  SPVM_HASH_set(compiler->class_source_symtable, "Double", strlen("Double"), (void*)spvm_double_class_source);
  
  // Add CommandInfo source
  const char* spvm_command_info_class_source = "class CommandInfo {\n  our $PROGRAM_NAME : ro string;\n  our $ARGV : ro string[];\n  our $BASE_TIME : ro long;\n  }";
  SPVM_HASH_set(compiler->class_source_symtable, "CommandInfo", strlen("CommandInfo"), (void*)spvm_command_info_class_source);

  // Add Address source
  const char* spvm_address_class_source = "class Address : pointer {\n  static method new : Address () {\n    my $self = new Address;\n    return $self;\n  }\n}";
  SPVM_HASH_set(compiler->class_source_symtable, "Address", strlen("Address"), (void*)spvm_address_class_source);
  
  return compiler;
}

void SPVM_COMPILER_add_basic_type(SPVM_COMPILER* compiler, int32_t basic_type_id) {
   SPVM_BASIC_TYPE* basic_type = SPVM_BASIC_TYPE_new(compiler);
   basic_type->id = basic_type_id;
   const char* basic_type_name_tmp = (SPVM_NATIVE_C_BASIC_TYPE_ID_NAMES())[basic_type->id];
   SPVM_CONSTANT_STRING* basic_type_name_string = SPVM_CONSTANT_STRING_new(compiler, basic_type_name_tmp, strlen(basic_type_name_tmp));
   basic_type->name = basic_type_name_string->value;
   SPVM_LIST_push(compiler->basic_types, basic_type);
   SPVM_HASH_set(compiler->basic_type_symtable, basic_type->name, strlen(basic_type->name), basic_type);
}

void SPVM_COMPILER_add_basic_types(SPVM_COMPILER* compiler) {
  // Add basic_types
  SPVM_COMPILER_add_basic_type(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_UNKNOWN);
  SPVM_COMPILER_add_basic_type(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_UNDEF);
  SPVM_COMPILER_add_basic_type(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_VOID);
  SPVM_COMPILER_add_basic_type(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE);
  SPVM_COMPILER_add_basic_type(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT);
  SPVM_COMPILER_add_basic_type(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_INT);
  SPVM_COMPILER_add_basic_type(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_LONG);
  SPVM_COMPILER_add_basic_type(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT);
  SPVM_COMPILER_add_basic_type(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE);
  SPVM_COMPILER_add_basic_type(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_STRING);
  SPVM_COMPILER_add_basic_type(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_ANY_OBJECT);
  SPVM_COMPILER_add_basic_type(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE_CLASS);
  SPVM_COMPILER_add_basic_type(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT_CLASS);
  SPVM_COMPILER_add_basic_type(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_INT_CLASS);
  SPVM_COMPILER_add_basic_type(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_LONG_CLASS);
  SPVM_COMPILER_add_basic_type(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT_CLASS);
  SPVM_COMPILER_add_basic_type(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE_CLASS);
  SPVM_COMPILER_add_basic_type(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_BOOL_CLASS);
  SPVM_COMPILER_add_basic_type(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS);
}

int32_t SPVM_COMPILER_get_error_messages_length(SPVM_COMPILER* compiler) {
  
  return compiler->error_messages->length;
}

const char* SPVM_COMPILER_get_error_message(SPVM_COMPILER* compiler, int32_t index) {
  
  const char* error_message = (const char*)SPVM_LIST_get(compiler->error_messages, index);
  
  return error_message;
}

void SPVM_COMPILER_print_error_messages(SPVM_COMPILER* compiler, FILE* fh) {
  
  for (int32_t i = 0; i < compiler->error_messages->length; i++) {
    const char* error_message = (const char*)SPVM_LIST_get(compiler->error_messages, i);
    fprintf(fh, "[CompileError]%s\n", error_message);
  }
}

void SPVM_COMPILER_use(SPVM_COMPILER* compiler, const char* class_name, const char* file, int32_t line) {
  SPVM_OP* op_name_class = SPVM_OP_new_op_name(compiler, class_name, file, line);
  SPVM_OP* op_use = SPVM_OP_new_op_use(compiler, op_name_class->file, op_name_class->line);
  SPVM_OP* op_name_class_alias = NULL;
  int32_t is_require = 0;
  SPVM_OP_build_use(compiler, op_use, op_name_class, op_name_class_alias, is_require);
  SPVM_LIST_push(compiler->op_use_stack, op_use);
}

const char* SPVM_COMPILER_get_runtime_name(SPVM_HASH* runtime_string_symtable, const char* name) {
  
  SPVM_RUNTIME_CONSTANT_STRING* string = SPVM_HASH_get(runtime_string_symtable, name, strlen(name));
  
  const char* new_name = string->value;
  
  return new_name;
}

int32_t SPVM_COMPILER_use_default_loaded_classes(SPVM_COMPILER* compiler) {
  // Use automatically loaded classes
  SPVM_COMPILER_use(compiler, "Bool", "Bool", 0);
  SPVM_COMPILER_use(compiler, "Error", "Error", 0);
  SPVM_COMPILER_use(compiler, "Error::System", "Error::System", 0);
  SPVM_COMPILER_use(compiler, "Error::NotSupported", "Error::NotSupported", 0);
  SPVM_COMPILER_use(compiler, "Byte", "Byte", 0);
  SPVM_COMPILER_use(compiler, "Short", "Short", 0);
  SPVM_COMPILER_use(compiler, "Int", "Int", 0);
  SPVM_COMPILER_use(compiler, "Long", "Long", 0);
  SPVM_COMPILER_use(compiler, "Float", "Float", 0);
  SPVM_COMPILER_use(compiler, "Double", "Double", 0);
  SPVM_COMPILER_use(compiler, "CommandInfo", "CommandInfo", 0);
  SPVM_COMPILER_use(compiler, "Address", "Address", 0);
}

int32_t SPVM_COMPILER_compile(SPVM_COMPILER* compiler, const char* class_name) {
  
  compiler->cur_class_base = compiler->classes->length;

  int32_t cur_basic_type_base = compiler->basic_types->length;
  
  const char* start_file = SPVM_COMPILER_get_start_file(compiler);
  int32_t start_line = SPVM_COMPILER_get_start_line(compiler);
  
  //yacc/bison debug mode. The default is off.
  SPVM_yydebug = 0;

#ifdef SPVM_DEBUG_YACC
  // Turn on yacc/bison debug mode
  SPVM_yydebug = 1;
#endif

  compiler->parse_not_started = 1;

  // Initialize error messages
  compiler->error_messages = SPVM_LIST_new_list_permanent(compiler->allocator, 0);
  
  int32_t error_code = 0;

  int32_t compile_start_memory_blocks_count_tmp = compiler->allocator->memory_blocks_count_tmp;

  compiler->ops = SPVM_LIST_new(compiler->allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
  compiler->op_use_stack = SPVM_LIST_new(compiler->allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
  compiler->op_types = SPVM_LIST_new(compiler->allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
  compiler->used_class_symtable = SPVM_HASH_new(compiler->allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
  for (int32_t i = 0; i < compiler->classes->length; i++) {
    SPVM_CLASS* class = SPVM_LIST_get(compiler->classes, i);
    const char* class_name = class->name;
    SPVM_HASH_set(compiler->used_class_symtable, class_name, strlen(class_name), (void*)class_name);
  }
  
  SPVM_COMPILER_use_default_loaded_classes(compiler);
   
  // Use the class that is specified at the argument
  if (class_name) {
    SPVM_CONSTANT_STRING* class_name_string = SPVM_CONSTANT_STRING_new(compiler, class_name, strlen(class_name));
    class_name = class_name_string->value;
    SPVM_COMPILER_use(compiler, class_name, start_file, start_line);
  }
  
  /* Tokenize and Parse */
  int32_t parse_error_flag = SPVM_yyparse(compiler);
  if (parse_error_flag) {
    error_code = 1;
  }
  else {
    if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
      error_code = 2;
    }
    else {
      // Check syntax
      SPVM_OP_CHECKER_check(compiler);
      if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
        error_code = 3;
      }
      else {
        // Build operation code
        int32_t build_opcode_array_start_memory_blocks_count_tmp = compiler->allocator->memory_blocks_count_tmp;
        SPVM_OPCODE_BUILDER_build_opcode_array(compiler);
        assert(compiler->allocator->memory_blocks_count_tmp == build_opcode_array_start_memory_blocks_count_tmp);
        if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
          error_code = 4;
        }
      }
    }
  }
  
  // Cleanup ops
  for (int32_t i = 0; i < compiler->ops->length; i++) {
    SPVM_OP* op = SPVM_LIST_get(compiler->ops, i);
    int32_t op_id = op->id;
    switch(op_id) {
      case SPVM_OP_C_ID_BLOCK: {
        SPVM_ALLOCATOR_free_memory_block_tmp(compiler->allocator, op->uv.block);
        break;
      }
      case SPVM_OP_C_ID_ATTRIBUTE: {
        SPVM_ALLOCATOR_free_memory_block_tmp(compiler->allocator, op->uv.attribute);
        break;
      }
      case SPVM_OP_C_ID_USE: {
        SPVM_USE* use = op->uv.use;
        use->class_alias_name = NULL;
        SPVM_ALLOCATOR_free_memory_block_tmp(compiler->allocator, use);
        break;
      }
      case SPVM_OP_C_ID_ALLOW: {
        SPVM_ALLOW* allow = op->uv.allow;
        SPVM_ALLOCATOR_free_memory_block_tmp(compiler->allocator, allow);
        break;
      }
      case SPVM_OP_C_ID_INTERFACE: {
        SPVM_INTERFACE* interface = op->uv.interface;
        SPVM_ALLOCATOR_free_memory_block_tmp(compiler->allocator, interface);
        break;
      }
      case SPVM_OP_C_ID_CLASS_VAR_ACCESS: {
        SPVM_CLASS_VAR_ACCESS* class_var_access = op->uv.class_var_access;
        class_var_access->op_name = NULL;
        class_var_access->class_var = NULL;
        SPVM_ALLOCATOR_free_memory_block_tmp(compiler->allocator, class_var_access);
        break;
      }
      case SPVM_OP_C_ID_CONSTANT: {
        SPVM_CONSTANT* constant = op->uv.constant;
        constant->op_constant = NULL;
        constant->type = NULL;
        SPVM_ALLOCATOR_free_memory_block_tmp(compiler->allocator, constant);
        break;
      }
      case SPVM_OP_C_ID_ARRAY_FIELD_ACCESS: {
        SPVM_ARRAY_FIELD_ACCESS* array_field_access = op->uv.array_field_access;
        array_field_access->field = NULL;
        SPVM_ALLOCATOR_free_memory_block_tmp(compiler->allocator, array_field_access);
        break;
      }
      case SPVM_OP_C_ID_FIELD_ACCESS: {
        SPVM_FIELD_ACCESS* field_access = op->uv.field_access;
        field_access->op_invocant = NULL;
        field_access->op_name = NULL;
        field_access->field = NULL;
        SPVM_ALLOCATOR_free_memory_block_tmp(compiler->allocator, field_access);
        break;
      }
      case SPVM_OP_C_ID_CALL_METHOD: {
        SPVM_CALL_METHOD* call_method = op->uv.call_method;
        call_method->op_invocant = NULL;
        call_method->op_name = NULL;
        call_method->method = NULL;
        SPVM_ALLOCATOR_free_memory_block_tmp(compiler->allocator, call_method);
        break;
      }
      case SPVM_OP_C_ID_VAR: {
        SPVM_VAR* var = op->uv.var;
        var->op_name = NULL;
        var->name = NULL;
        var->var_decl = NULL;
        var->call_method = NULL;
        SPVM_ALLOCATOR_free_memory_block_tmp(compiler->allocator, var);
        break;
      }
      case SPVM_OP_C_ID_MY: {
        SPVM_VAR_DECL* var_decl = op->uv.var_decl;
        if (!var_decl->is_eternal) {
          var_decl->op_var_decl = NULL;
          var_decl->type = NULL;
          var_decl->var = NULL;
          SPVM_ALLOCATOR_free_memory_block_tmp(compiler->allocator, var_decl);
        }
        break;
      }
    }
    SPVM_ALLOCATOR_free_memory_block_tmp(compiler->allocator, op);
  }
  
  // Clear unused pointers
  for (int32_t class_index = compiler->cur_class_base; class_index < compiler->classes->length; class_index++) {
    SPVM_CLASS* class = SPVM_LIST_get(compiler->classes, class_index);
    class->op_class = NULL;
    class->op_name = NULL;
    
    SPVM_LIST_free(class->allows);
    
    SPVM_LIST* methods = class->methods;
    {
      int32_t method_index;
      for (method_index = 0; method_index < methods->length; method_index++) {
        SPVM_METHOD* method = SPVM_LIST_get(methods, method_index);
        method->op_method = NULL;
        method->op_name = NULL;
        method->op_block = NULL;
        method->op_inline = NULL;
      }
    }
  }

  // Free
  SPVM_LIST_free(compiler->op_use_stack);
  compiler->op_use_stack = NULL;
  
  SPVM_LIST_free(compiler->op_types);
  compiler->op_types = NULL;

  SPVM_HASH_free(compiler->used_class_symtable);
  compiler->used_class_symtable = NULL;

  SPVM_LIST_free(compiler->ops);
  compiler->ops = NULL;
  
  assert(compiler->allocator->memory_blocks_count_tmp == compile_start_memory_blocks_count_tmp);
  
  return error_code;
}

int32_t SPVM_COMPILER_calculate_runtime_codes_length(SPVM_COMPILER* compiler) {

  int32_t length = 0;
  
  // opcodes length
  length++;
  
  // opcodes 32bit length
  length++;
  
  // opcodes
  length += (sizeof(SPVM_OPCODE) / sizeof(int32_t)) * (compiler->opcode_array->length + 1);

  // constant_strings_buffer length
  length++;

  // constant_strings_buffer 32bit length
  length++;
  
  // constant_strings_buffer
  length += (compiler->constant_strings_buffer->length / sizeof(int32_t)) + 1;
  
  // constant_strings length
  length++;

  // constant_strings 32bit length
  length++;
  
  // constant_strings
  length += (sizeof(SPVM_RUNTIME_CONSTANT_STRING) / sizeof(int32_t)) * (compiler->constant_strings->length + 1);

  // anon_method_methods length
  length++;

  // anon_method_methods 32bit length
  length++;

  // anon_method_method_ids
  length += (sizeof(int32_t) / sizeof(int32_t)) * (compiler->anon_methods->length + 1);

  // classes length
  length++;
  
  // classes 32bit length
  length++;
  
  // classes
  length += (sizeof(SPVM_RUNTIME_CLASS) / sizeof(int32_t)) * (compiler->classes->length + 1);

  // basic_types length
  length++;

  // basic_types 32bit length
  length++;
  
  // basic_types
  length += (sizeof(SPVM_RUNTIME_BASIC_TYPE) / sizeof(int32_t)) * (compiler->basic_types->length + 1);

  // types length
  length++;

  // types 32bit length
  length++;
  
  // types
  length += (sizeof(SPVM_RUNTIME_TYPE) / sizeof(int32_t)) * (compiler->types->length + 1);

  // class_vars length
  length++;

  // class_vars 32bit length
  length++;
  
  // class_vars
  length += (sizeof(SPVM_RUNTIME_CLASS_VAR) / sizeof(int32_t)) * (compiler->class_vars->length + 1);

  // methods length
  length++;
  
  // methods 32bit length
  length++;
  
  // methods
  length += (sizeof(SPVM_RUNTIME_METHOD) / sizeof(int32_t)) * (compiler->methods->length + 1);

  // arg_types length
  length++;
  
  // arg_types 32bit length
  length++;
  
  // arg_type_ids
  length += (sizeof(int32_t) / sizeof(int32_t)) * (compiler->args->length + 1);
  
  // fields length
  length++;

  // fields 32bit length
  length++;
  
  // fields
  length += (sizeof(SPVM_RUNTIME_FIELD) / sizeof(int32_t)) * (compiler->fields->length + 1);
  
  return length;
}

int32_t* SPVM_COMPILER_create_runtime_codes(SPVM_COMPILER* compiler, SPVM_ALLOCATOR* allocator) {

  SPVM_COMPILER_compile(compiler, NULL);
  
  int32_t runtime_codes_length = SPVM_COMPILER_calculate_runtime_codes_length(compiler);
  int32_t* runtime_codes = SPVM_ALLOCATOR_alloc_memory_block_permanent(allocator, sizeof(int32_t) * runtime_codes_length);

  int32_t* runtime_codes_ptr = runtime_codes;
  
  // Total length
  *runtime_codes_ptr = runtime_codes_length;
  runtime_codes_ptr++;
  
  // opcodes length
  *runtime_codes_ptr = compiler->opcode_array->length;
  runtime_codes_ptr++;
  
  // opcodes 32bit length
  int32_t opcodes_32bit_length = (sizeof(SPVM_OPCODE) / sizeof(int32_t)) * (compiler->opcode_array->length + 1);
  *runtime_codes_ptr = opcodes_32bit_length;
  runtime_codes_ptr++;
  
  // opcodes
  memcpy(runtime_codes_ptr, compiler->opcode_array->values, sizeof(int32_t) * opcodes_32bit_length);
  runtime_codes_ptr += opcodes_32bit_length;
  
  // constant_strings_buffer length
  *runtime_codes_ptr = compiler->constant_strings_buffer->length;
  runtime_codes_ptr++;

  // constant_strings_buffer 32bit length
  int32_t constant_strings_buffer_32bit_length = (compiler->constant_strings_buffer->length / sizeof(int32_t)) + 1;
  *runtime_codes_ptr = constant_strings_buffer_32bit_length;
  runtime_codes_ptr++;
  
  // constant_strings_buffer
  memcpy(runtime_codes_ptr, compiler->constant_strings_buffer->value, sizeof(int32_t) * constant_strings_buffer_32bit_length);
  runtime_codes_ptr += constant_strings_buffer_32bit_length;
  
  // constant_strings length
  *runtime_codes_ptr = compiler->constant_strings->length;
  runtime_codes_ptr++;

  // constant_strings 32bit length
  int32_t constant_strings_32bit_length = (sizeof(SPVM_RUNTIME_CONSTANT_STRING) / sizeof(int32_t)) * (compiler->constant_strings->length + 1);
  *runtime_codes_ptr = constant_strings_32bit_length;
  runtime_codes_ptr++;
  
  // constant_strings
  int32_t* constant_string_32bit_ptr = runtime_codes_ptr;
  for (int32_t constant_string_id = 0; constant_string_id < compiler->constant_strings->length; constant_string_id++) {
    SPVM_CONSTANT_STRING* string = SPVM_LIST_get(compiler->constant_strings, constant_string_id);
    SPVM_RUNTIME_CONSTANT_STRING* runtime_string = (SPVM_RUNTIME_CONSTANT_STRING*)constant_string_32bit_ptr;
    
    runtime_string->id = string->id;
    runtime_string->length = string->length;
    runtime_string->string_buffer_id = string->string_buffer_id;
    constant_string_32bit_ptr += sizeof(SPVM_RUNTIME_CONSTANT_STRING) / sizeof(int32_t);
  }
  runtime_codes_ptr += constant_strings_32bit_length;

  // anon_method_methods length
  *runtime_codes_ptr = compiler->anon_methods->length;
  runtime_codes_ptr++;

  // anon_method_methods 32bit length
  int32_t anon_method_32bit_length = (sizeof(int32_t) / sizeof(int32_t)) * (compiler->anon_methods->length + 1);
  *runtime_codes_ptr = anon_method_32bit_length;
  runtime_codes_ptr++;

  // anon_method_method_ids
  int32_t* anon_method_32bit_ptr = runtime_codes_ptr;
  for (int32_t anon_method_id = 0; anon_method_id < compiler->anon_methods->length; anon_method_id++) {
    SPVM_METHOD* anon_method = SPVM_LIST_get(compiler->anon_methods, anon_method_id);
    int32_t anon_method_id = anon_method->anon_method_id;
    *anon_method_32bit_ptr = anon_method->id;
    anon_method_32bit_ptr += sizeof(int32_t) / sizeof(int32_t);
  }
  runtime_codes_ptr += anon_method_32bit_length;

  // classes length
  *runtime_codes_ptr = compiler->classes->length;
  runtime_codes_ptr++;

  // classes 32bit length
  int32_t classes_32bit_length = (sizeof(SPVM_RUNTIME_CLASS) / sizeof(int32_t)) * (compiler->classes->length + 1);
  *runtime_codes_ptr = classes_32bit_length;
  runtime_codes_ptr++;

  // classes
  int32_t* class_32bit_ptr = runtime_codes_ptr;
  for (int32_t class_id = 0; class_id < compiler->classes->length; class_id++) {
    SPVM_CLASS* class = SPVM_LIST_get(compiler->classes, class_id);
    SPVM_RUNTIME_CLASS* runtime_class = (SPVM_RUNTIME_CLASS*)class_32bit_ptr;
    
    runtime_class->type_id = class->type->id;
    runtime_class->id = class->id;
    SPVM_CONSTANT_STRING* class_class_rel_file_string = SPVM_HASH_get(compiler->constant_string_symtable, class->class_rel_file, strlen(class->class_rel_file));
    runtime_class->class_rel_file_id = class_class_rel_file_string->id;

    if (class->class_path) {
      SPVM_CONSTANT_STRING* class_class_path_string = SPVM_HASH_get(compiler->constant_string_symtable, class->class_path, strlen(class->class_path));
      runtime_class->class_path_id = class_class_path_string->id;
    }
    else {
      runtime_class->class_path_id = -1;
    }
    runtime_class->has_init_block = class->has_init_block;
    runtime_class->is_anon = class->is_anon;
    runtime_class->is_pointer = class->is_pointer;
    if (class->parent_class_name) {
      SPVM_CLASS* parent_class = SPVM_HASH_get(compiler->class_symtable, class->parent_class_name, strlen(class->parent_class_name));
      runtime_class->parent_class_id = parent_class->id;
    }
    else {
      runtime_class->parent_class_id = -1;
    }
    
    runtime_class->fields_size = class->fields_size;

    SPVM_CONSTANT_STRING* class_string = SPVM_HASH_get(compiler->constant_string_symtable, class->name, strlen(class->name));
    runtime_class->name_id = class_string->id;
    
    if (class->destructor_method) {
      runtime_class->destructor_method_id = class->destructor_method->id;
    }
    else {
      runtime_class->destructor_method_id = -1;
    }
    
    if (class->category == SPVM_CLASS_C_CATEGORY_INTERFACE) {
      assert(class->required_method);
    }
  
    if (class->required_method) {
      assert(class->required_method->id >= 0);
      runtime_class->required_method_id = class->required_method->id;
    }
    else {
      runtime_class->required_method_id = -1;
    }
    
    runtime_class->methods_length = class->methods->length;
    if (class->methods->length > 0) {
      SPVM_METHOD* method = SPVM_LIST_get(class->methods, 0);
      runtime_class->methods_base_id = method->id;
    }
    else {
      runtime_class->methods_base_id = -1;
    }

    runtime_class->fields_length = class->fields->length;
    if (class->fields->length > 0) {
      SPVM_FIELD* field = SPVM_LIST_get(class->fields, 0);
      runtime_class->fields_base_id = field->id;
    }
    else {
      runtime_class->fields_base_id = -1;
    }

    runtime_class->class_vars_length = class->class_vars->length;
    if (class->class_vars->length > 0) {
      SPVM_CLASS_VAR* class_var = SPVM_LIST_get(class->class_vars, 0);
      runtime_class->class_vars_base_id = class_var->id;
    }
    else {
      runtime_class->class_vars_base_id = -1;
    }

    runtime_class->interfaces_length = class->interfaces->length;
    if (class->interfaces->length > 0) {
      SPVM_CLASS* interface = SPVM_LIST_get(class->interfaces, 0);
      runtime_class->interfaces_base_id = interface->id;
    }
    else {
      runtime_class->interfaces_base_id = -1;
    }

    runtime_class->anon_methods_length = class->anon_methods->length;
    if (class->anon_methods->length > 0) {
      SPVM_METHOD* anon_method = SPVM_LIST_get(class->anon_methods, 0);
      runtime_class->anon_methods_base_id = anon_method->anon_method_id;
    }
    else {
      runtime_class->anon_methods_base_id = -1;
    }

    class_32bit_ptr += sizeof(SPVM_RUNTIME_CLASS) / sizeof(int32_t);
  }
  runtime_codes_ptr += classes_32bit_length;

  // basic_types length
  *runtime_codes_ptr = compiler->basic_types->length;
  runtime_codes_ptr++;

  // basic_types 32bit length
  int32_t basic_types_32bit_length = (sizeof(SPVM_RUNTIME_BASIC_TYPE) / sizeof(int32_t)) * (compiler->basic_types->length + 1);
  *runtime_codes_ptr = basic_types_32bit_length;
  runtime_codes_ptr++;

  // basic_types
  int32_t* basic_type_32bit_ptr = runtime_codes_ptr;
  for (int32_t basic_type_id = 0; basic_type_id < compiler->basic_types->length; basic_type_id++) {
    SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, basic_type_id);
    SPVM_RUNTIME_BASIC_TYPE* runtime_basic_type = (SPVM_RUNTIME_BASIC_TYPE*)basic_type_32bit_ptr;
    
    runtime_basic_type->id = basic_type->id;
    runtime_basic_type->category = basic_type->category;
    if (basic_type->class) {
      runtime_basic_type->class_id = basic_type->class->id;
    }
    else {
      runtime_basic_type->class_id = -1;
    }
    SPVM_CONSTANT_STRING* basic_type_string = SPVM_HASH_get(compiler->constant_string_symtable, basic_type->name, strlen(basic_type->name));
    runtime_basic_type->name_id = basic_type_string->id;

    basic_type_32bit_ptr += sizeof(SPVM_RUNTIME_BASIC_TYPE) / sizeof(int32_t);
  }
  runtime_codes_ptr += basic_types_32bit_length;

  // types length
  *runtime_codes_ptr = compiler->types->length;
  runtime_codes_ptr++;

  // types 32bit length
  int32_t types_32bit_length = (sizeof(SPVM_RUNTIME_TYPE) / sizeof(int32_t)) * (compiler->types->length + 1);
  *runtime_codes_ptr = types_32bit_length;
  runtime_codes_ptr++;

  // types
  int32_t* type_32bit_ptr = runtime_codes_ptr;
  for (int32_t type_id = 0; type_id < compiler->types->length; type_id++) {
    SPVM_TYPE* type = SPVM_LIST_get(compiler->types, type_id);
    SPVM_RUNTIME_TYPE* runtime_type = (SPVM_RUNTIME_TYPE*)type_32bit_ptr;
    
    runtime_type->basic_type_id = type->basic_type->id;
    runtime_type->dimension = type->dimension;
    runtime_type->flag = type->flag;
    runtime_type->stack_length = type->stack_length;
    runtime_type->mulnum_field_basic_type_id = SPVM_TYPE_get_mulnum_field_basic_type_id(compiler, type->basic_type->id, type->dimension, type->flag);

    type_32bit_ptr += sizeof(SPVM_RUNTIME_TYPE) / sizeof(int32_t);
  }
  runtime_codes_ptr += types_32bit_length;

  // class_vars length
  *runtime_codes_ptr = compiler->class_vars->length;
  runtime_codes_ptr++;

  // class_vars 32bit length
  int32_t class_vars_32bit_length = (sizeof(SPVM_RUNTIME_CLASS_VAR) / sizeof(int32_t)) * (compiler->class_vars->length + 1);
  *runtime_codes_ptr = class_vars_32bit_length;
  runtime_codes_ptr++;

  // class_vars
  int32_t* class_var_32bit_ptr = runtime_codes_ptr;
  for (int32_t class_var_id = 0; class_var_id < compiler->class_vars->length; class_var_id++) {
    SPVM_CLASS_VAR* class_var = SPVM_LIST_get(compiler->class_vars, class_var_id);
    SPVM_RUNTIME_CLASS_VAR* runtime_class_var = (SPVM_RUNTIME_CLASS_VAR*)class_var_32bit_ptr;

    runtime_class_var->id = class_var->id;
    runtime_class_var->type_id = class_var->type->id;
    runtime_class_var->class_id = class_var->class->id;

    SPVM_CONSTANT_STRING* class_var_name_string = SPVM_HASH_get(compiler->constant_string_symtable, class_var->name, strlen(class_var->name));
    runtime_class_var->name_id = class_var_name_string->id;

    class_var_32bit_ptr += sizeof(SPVM_RUNTIME_CLASS_VAR) / sizeof(int32_t);
  }
  runtime_codes_ptr += class_vars_32bit_length;

  // methods length
  *runtime_codes_ptr = compiler->methods->length;
  runtime_codes_ptr++;

  // methods 32bit length
  int32_t methods_32bit_length = (sizeof(SPVM_RUNTIME_METHOD) / sizeof(int32_t)) * (compiler->methods->length + 1);
  *runtime_codes_ptr = methods_32bit_length;
  runtime_codes_ptr++;

  // methods
  int32_t* method_32bit_ptr = runtime_codes_ptr;
  for (int32_t method_id = 0; method_id < compiler->methods->length; method_id++) {
    SPVM_METHOD* method = SPVM_LIST_get(compiler->methods, method_id);
    SPVM_RUNTIME_METHOD* runtime_method = (SPVM_RUNTIME_METHOD*)method_32bit_ptr;

    runtime_method->opcodes_base_id = method->opcodes_base_id;
    runtime_method->opcodes_length = method->opcodes_length;
    runtime_method->id = method->id;
    runtime_method->class_id = method->class->id;
    runtime_method->is_class_method = method->is_class_method;
    runtime_method->is_init = method->is_init;
    runtime_method->is_anon = method->is_anon;
    runtime_method->call_stack_byte_vars_length  = method->call_stack_byte_vars_length;
    runtime_method->call_stack_short_vars_length  = method->call_stack_short_vars_length;
    runtime_method->call_stack_int_vars_length  = method->call_stack_int_vars_length;
    runtime_method->call_stack_long_vars_length  = method->call_stack_long_vars_length;
    runtime_method->call_stack_float_vars_length  = method->call_stack_float_vars_length;
    runtime_method->call_stack_double_vars_length  = method->call_stack_double_vars_length;
    runtime_method->call_stack_object_vars_length = method->call_stack_object_vars_length;
    runtime_method->call_stack_ref_vars_length = method->call_stack_ref_vars_length;
    runtime_method->mortal_stack_length  = method->mortal_stack_length;
    runtime_method->return_type_id = method->return_type->id;
    runtime_method->is_native = method->is_native;
    runtime_method->is_precompile = method->is_precompile;
    runtime_method->is_destructor = method->is_destructor;
    runtime_method->is_required = method->is_required;
    runtime_method->is_enum = method->is_enum;

    SPVM_CONSTANT_STRING* method_name_string = SPVM_HASH_get(compiler->constant_string_symtable, method->name, strlen(method->name));
    runtime_method->name_id = method_name_string->id;

    runtime_method->args_length = method->args_length;
    if (method->args_length > 0) {
      SPVM_VAR_DECL* arg = SPVM_LIST_get(method->var_decls, 0);
      runtime_method->args_base_id = arg->arg_id;
    }
    else {
      runtime_method->args_base_id = -1;
    }
    runtime_method->required_args_length = method->required_args_length;

    method_32bit_ptr += sizeof(SPVM_RUNTIME_METHOD) / sizeof(int32_t);
  }
  runtime_codes_ptr += methods_32bit_length;

  // args length
  *runtime_codes_ptr = compiler->args->length;
  runtime_codes_ptr++;

  // arg_type_method_ids 32bit length
  int32_t arg_type_ids_32bit_length = (sizeof(int32_t) / sizeof(int32_t)) * (compiler->args->length + 1);
  *runtime_codes_ptr = arg_type_ids_32bit_length;
  runtime_codes_ptr++;

  // arg_type_method_ids
  int32_t* arg_type_id_32bit_ptr = runtime_codes_ptr;
  for (int32_t arg_id = 0; arg_id < compiler->args->length; arg_id++) {
    SPVM_VAR_DECL* arg_var_decl = SPVM_LIST_get(compiler->args, arg_id);
    int32_t arg_type_id = arg_var_decl->type->id;
    *arg_type_id_32bit_ptr = arg_type_id;
    
    arg_type_id_32bit_ptr += sizeof(int32_t) / sizeof(int32_t);
  }
  runtime_codes_ptr += arg_type_ids_32bit_length;

  // fields length
  *runtime_codes_ptr = compiler->fields->length;
  runtime_codes_ptr++;

  // fields 32bit length
  int32_t fields_32bit_length = (sizeof(SPVM_RUNTIME_FIELD) / sizeof(int32_t)) * (compiler->fields->length + 1);
  *runtime_codes_ptr = fields_32bit_length;
  runtime_codes_ptr++;

  // fields
  int32_t* field_32bit_ptr = runtime_codes_ptr;
  for (int32_t field_id = 0; field_id < compiler->fields->length; field_id++) {
    SPVM_FIELD* field = SPVM_LIST_get(compiler->fields, field_id);
    SPVM_RUNTIME_FIELD* runtime_field = (SPVM_RUNTIME_FIELD*)field_32bit_ptr;

    runtime_field->id = field->id;
    runtime_field->index = field->index;
    runtime_field->offset = field->offset;
    runtime_field->type_id = field->type->id;
    runtime_field->class_id = field->class->id;
    
    SPVM_CONSTANT_STRING* field_name_string = SPVM_HASH_get(compiler->constant_string_symtable, field->name, strlen(field->name));
    runtime_field->name_id = field_name_string->id;

    field_32bit_ptr += sizeof(SPVM_RUNTIME_FIELD) / sizeof(int32_t);
  }
  runtime_codes_ptr += fields_32bit_length;
  
  return runtime_codes;
}

void SPVM_COMPILER_error(SPVM_COMPILER* compiler, const char* message_template, ...) {
  
  int32_t message_length = 0;
  
  // Message template
  int32_t message_template_length = (int32_t)strlen(message_template);
  
  va_list args;
  va_start(args, message_template);

  message_length += message_template_length;
  
  // Argument count
  char* found_ptr = (char*)message_template;
  while (1) {
    found_ptr = strchr(found_ptr, '%');
    if (found_ptr) {
      if (*(found_ptr + 1) == 'c') {
        int arg = va_arg(args, int);
        message_length++;
      }
      else if (*(found_ptr + 1) == 's') {
        char* arg = va_arg(args, char*);
        message_length += strlen(arg);
      }
      else if (*(found_ptr + 1) == 'd') {
        (void) va_arg(args, int);
        message_length += 30;
      }
      else if (*(found_ptr + 1) == '%') {
        // Nothing
        found_ptr++;
      }
      else {
        assert(0);
      }
      found_ptr++;
    }
    else {
      break;
    }
  }
  va_end(args);
  
  char* message = SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->allocator, message_length + 1);
  
  va_start(args, message_template);
  vsprintf(message, message_template, args);
  va_end(args);

  SPVM_LIST_push(compiler->error_messages, message);
}

void SPVM_COMPILER_free(SPVM_COMPILER* compiler) {

  // Free opcode array
  SPVM_OPCODE_ARRAY_free(compiler, compiler->opcode_array);
  
  const char* start_file = SPVM_COMPILER_get_start_file(compiler);
  
  if (start_file) {
    SPVM_ALLOCATOR_free_memory_block_tmp(compiler->allocator, (void*)start_file);
  }
  
  SPVM_COMPILER_clear_class_paths(compiler);
  
  // Free allocator
  SPVM_ALLOCATOR_free(compiler->allocator);
  compiler->allocator = NULL;
}

const char* SPVM_COMPILER_get_start_file(SPVM_COMPILER* compiler) {
  return compiler->start_file;
}

void SPVM_COMPILER_set_start_file(SPVM_COMPILER* compiler, const char* start_file) {
  
  if (compiler->start_file) {
    SPVM_ALLOCATOR_free_memory_block_tmp(compiler->allocator, (void*)compiler->start_file);
    compiler->start_file = NULL;
  }
  
  char* compiler_start_file = NULL;
  if (start_file) {
    int32_t start_file_length = strlen(start_file);
    compiler_start_file = SPVM_ALLOCATOR_alloc_memory_block_tmp(compiler->allocator, start_file_length + 1);
    memcpy(compiler_start_file, start_file, start_file_length);
  }
  
  compiler->start_file = compiler_start_file;
}

int32_t SPVM_COMPILER_get_start_line(SPVM_COMPILER* compiler) {
  return compiler->start_line;
}

void SPVM_COMPILER_set_start_line(SPVM_COMPILER* compiler, int32_t start_line) {
  compiler->start_line = start_line;
}

int32_t SPVM_COMPILER_get_class_paths_length(SPVM_COMPILER* compiler) {
  SPVM_LIST* class_paths = compiler->class_paths;
  int32_t class_paths_length = class_paths->length;
  return class_paths_length;
}

void SPVM_COMPILER_add_class_path(SPVM_COMPILER* compiler, const char* class_path) {  
  int32_t class_path_length = strlen(class_path);
  char* compiler_class_path = SPVM_ALLOCATOR_alloc_memory_block_tmp(compiler->allocator, class_path_length + 1);
  memcpy(compiler_class_path, class_path, class_path_length);
  SPVM_LIST_push(compiler->class_paths, (void*)compiler_class_path);
}

void SPVM_COMPILER_clear_class_paths(SPVM_COMPILER* compiler) {
  int32_t class_paths_length = SPVM_COMPILER_get_class_paths_length(compiler);
  
  for (int32_t i = 0; i < class_paths_length; i++) {
    const char* class_path = SPVM_COMPILER_get_class_path(compiler, i);
    SPVM_ALLOCATOR_free_memory_block_tmp(compiler->allocator, (void*)class_path);
    class_path = NULL;
  }
  
  SPVM_LIST_clear(compiler->class_paths);
}

const char* SPVM_COMPILER_get_class_path (SPVM_COMPILER* compiler, int32_t class_path_id) {
  const char* class_path = SPVM_LIST_get(compiler->class_paths, class_path_id);
  return class_path;
}
