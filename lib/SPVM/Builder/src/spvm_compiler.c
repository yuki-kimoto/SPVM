// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdarg.h>

#include "spvm_compiler.h"
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
#include "spvm_check.h"
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
#include "spvm_runtime_class_var.h"
#include "spvm_runtime_field.h"
#include "spvm_runtime_arg.h"
#include "spvm_runtime.h"
#include "spvm_runtime_method.h"
#include "spvm_runtime_constant_string.h"
#include "spvm_runtime_arg.h"

SPVM_COMPILER* SPVM_COMPILER_new() {
  SPVM_COMPILER* compiler = SPVM_ALLOCATOR_alloc_memory_block_unmanaged(sizeof(SPVM_COMPILER));
  
  // Allocator
  SPVM_ALLOCATOR* allocator = SPVM_ALLOCATOR_new();
  compiler->allocator = allocator;
  
  compiler->ch_ptr = "";
  
  compiler->global_constant_strings = SPVM_LIST_new_list_permanent(compiler->allocator, 128);
  compiler->global_constant_string_symtable = SPVM_HASH_new_hash_permanent(compiler->allocator, 128);
  compiler->global_string_pool = SPVM_STRING_BUFFER_new(compiler->allocator, 8192, SPVM_ALLOCATOR_C_ALLOC_TYPE_PERMANENT);
  
  compiler->constant_strings = SPVM_LIST_new_list_permanent(compiler->allocator, 128);
  compiler->string_pool = SPVM_STRING_BUFFER_new(compiler->allocator, 8192, SPVM_ALLOCATOR_C_ALLOC_TYPE_PERMANENT);
  
  // Eternal information
  compiler->include_dirs = SPVM_LIST_new_list_permanent(compiler->allocator, 0);
  compiler->basic_types = SPVM_LIST_new_list_permanent(compiler->allocator, 0);
  compiler->basic_type_symtable = SPVM_HASH_new_hash_permanent(compiler->allocator, 0);
  compiler->opcode_array = SPVM_OPCODE_ARRAY_new(compiler);
  compiler->source_symtable = SPVM_HASH_new_hash_permanent(compiler->allocator, 0);
  compiler->if_require_not_found_basic_type_name_symtable = SPVM_HASH_new_hash_permanent(compiler->allocator, 0);
  
  return compiler;
}

void SPVM_COMPILER_add_source(SPVM_COMPILER* compiler, const char* basic_type_name, const char* source, int32_t length) {
  SPVM_STRING_BUFFER* source_buffer = SPVM_STRING_BUFFER_new(compiler->allocator, length, SPVM_ALLOCATOR_C_ALLOC_TYPE_PERMANENT);
  SPVM_STRING_BUFFER_add_len(source_buffer, (char*)source, strlen(source));
  SPVM_HASH_set(compiler->source_symtable, basic_type_name, strlen(basic_type_name), (void*)source_buffer);
}

void SPVM_COMPILER_add_basic_type_core(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t basic_type_category) {
   const char* basic_type_name = SPVM_BASIC_TYPE_get_basic_type_name(compiler, basic_type_id);
   SPVM_BASIC_TYPE* basic_type = SPVM_COMPILER_add_basic_type(compiler, basic_type_name);
   assert(basic_type->id == basic_type_id);
   basic_type->category = basic_type_category;
}

SPVM_BASIC_TYPE* SPVM_COMPILER_add_basic_type(SPVM_COMPILER* compiler, const char* basic_type_name) {
  
   SPVM_BASIC_TYPE* basic_type = SPVM_HASH_get(compiler->basic_type_symtable, basic_type_name, strlen(basic_type_name));
   
   if (!basic_type) {
     basic_type = SPVM_BASIC_TYPE_new(compiler);
     basic_type->id = compiler->basic_types->length;
     SPVM_CONSTANT_STRING* basic_type_name_string = SPVM_CONSTANT_STRING_new(compiler, basic_type_name, strlen(basic_type_name));
     basic_type->name = basic_type_name_string->value;
     SPVM_LIST_push(compiler->basic_types, basic_type);
     SPVM_HASH_set(compiler->basic_type_symtable, basic_type->name, strlen(basic_type->name), basic_type);
  }
  
   return basic_type;
}

void SPVM_COMPILER_add_basic_types(SPVM_COMPILER* compiler) {
  // Add basic_types
  SPVM_COMPILER_add_basic_type_core(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_UNKNOWN, SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_UNKNOWN);
  SPVM_COMPILER_add_basic_type_core(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_UNDEF, SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_UNDEF);
  SPVM_COMPILER_add_basic_type_core(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_VOID, SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_VOID);
  SPVM_COMPILER_add_basic_type_core(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE, SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_NUMERIC);
  SPVM_COMPILER_add_basic_type_core(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT, SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_NUMERIC);
  SPVM_COMPILER_add_basic_type_core(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_INT, SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_NUMERIC);
  SPVM_COMPILER_add_basic_type_core(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_LONG, SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_NUMERIC);
  SPVM_COMPILER_add_basic_type_core(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT, SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_NUMERIC);
  SPVM_COMPILER_add_basic_type_core(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE, SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_NUMERIC);
  SPVM_COMPILER_add_basic_type_core(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_STRING, SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_STRING);
  SPVM_COMPILER_add_basic_type_core(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_ANY_OBJECT, SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_ANY_OBJECT);
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

void SPVM_COMPILER_use(SPVM_COMPILER* compiler, const char* basic_type_name, const char* file, int32_t line) {
  SPVM_OP* op_name_basic_type = SPVM_OP_new_op_name(compiler, basic_type_name, file, line);
  SPVM_OP* op_type_class = SPVM_OP_build_basic_type(compiler, op_name_basic_type);
  SPVM_OP* op_use = SPVM_OP_new_op_use(compiler, op_name_basic_type->file, op_name_basic_type->line);
  SPVM_OP* op_name_alias = NULL;
  int32_t is_require = 0;
  SPVM_OP_build_use(compiler, op_use, op_type_class, op_name_alias, is_require);
  SPVM_LIST_push(compiler->op_use_stack, op_use);
}

void SPVM_COMPILER_check_basic_type_id(SPVM_COMPILER* compiler, int32_t basic_type_id) {
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, basic_type_id);
  const char* basic_type_name_expected = SPVM_BASIC_TYPE_get_basic_type_name(compiler, basic_type_id);
  
  if (strcmp(basic_type->name, basic_type_name_expected) != 0) {
    fprintf(stderr, "[Unexpected Error]Basic Type ID:%d, Basic Type Name:%s, Expected Basic Type Name: %s\n", basic_type_id, basic_type->name, basic_type_name_expected);
    assert(0);
  }
}

const char* SPVM_COMPILER_get_runtime_name(SPVM_HASH* runtime_string_symtable, const char* name) {
  
  SPVM_RUNTIME_CONSTANT_STRING* string = SPVM_HASH_get(runtime_string_symtable, name, strlen(name));
  
  const char* new_name = string->value;
  
  return new_name;
}

int32_t SPVM_COMPILER_use_default_loaded_classes(SPVM_COMPILER* compiler) {
  // Use automatically loaded classes
  SPVM_COMPILER_use(compiler, "Byte", "Byte", 0);
  SPVM_COMPILER_use(compiler, "Short", "Short", 0);
  SPVM_COMPILER_use(compiler, "Int", "Int", 0);
  SPVM_COMPILER_use(compiler, "Long", "Long", 0);
  SPVM_COMPILER_use(compiler, "Float", "Float", 0);
  SPVM_COMPILER_use(compiler, "Double", "Double", 0);
  SPVM_COMPILER_use(compiler, "Bool", "Bool", 0);
  SPVM_COMPILER_use(compiler, "Error", "Error", 0);
  SPVM_COMPILER_use(compiler, "Error::System", "Error::System", 0);
  SPVM_COMPILER_use(compiler, "Error::NotSupported", "Error::NotSupported", 0);
  SPVM_COMPILER_use(compiler, "CommandInfo", "CommandInfo", 0);
  SPVM_COMPILER_use(compiler, "Address", "Address", 0);
}

int32_t SPVM_COMPILER_compile(SPVM_COMPILER* compiler, const char* basic_type_name) {
  
  compiler->basic_types_base_id = compiler->basic_types->length;
  
  if (compiler->basic_types->length == 0) {
    // Add basic types
    SPVM_COMPILER_add_basic_types(compiler);
    
    // Add Bool source
    {
      const char* basic_type_name = "Bool";
      const char* source = "class Bool {\n  INIT {\n    $TRUE = new Bool;\n    $TRUE->{value} = 1;\n    $FALSE = new Bool;\n    $FALSE->{value} = 0;\n  }\n  \n  our $TRUE : ro Bool;\n  our $FALSE : ro Bool;\n  has value : ro int;\n}";
      SPVM_COMPILER_add_source(compiler, basic_type_name, source, strlen(source));
    }
    
    // Add Error source
    {
      const char* basic_type_name = "Error";
      const char* source = "class Error;";
      SPVM_COMPILER_add_source(compiler, basic_type_name, source, strlen(source));
    }
    
    // Add Error::System source
    {
      const char* basic_type_name = "Error::System";
      const char* source = "class Error::System extends Error;";
      SPVM_COMPILER_add_source(compiler, basic_type_name, source, strlen(source));
    }
    
    // Add Error::NotSupported source
    {
      const char* basic_type_name = "Error::NotSupported";
      const char* source = "class Error::NotSupported extends Error;";
      SPVM_COMPILER_add_source(compiler, basic_type_name, source, strlen(source));
    }
    
    // Add Byte source
    {
      const char* basic_type_name = "Byte";
      const char* source = "class Byte {\n  has value : ro byte;\n  static method new : Byte ($value : int) {\n    my $self = new Byte;\n    $self->{value} = (byte)$value;\n    return $self;\n  }\n}";
      SPVM_COMPILER_add_source(compiler, basic_type_name, source, strlen(source));
    }
    
    // Add Short source
    {
      const char* basic_type_name = "Short";
      const char* source = "class Short {\n  has value : ro short;\n  static method new : Short ($value : int) {\n    my $self = new Short;\n    $self->{value} = (short)$value;\n    return $self;\n  }\n}";
      SPVM_COMPILER_add_source(compiler, basic_type_name, source, strlen(source));
    }
    
    // Add Int source
    {
      const char* basic_type_name = "Int";
      const char* source = "class Int {\n  has value : ro int;\n  static method new : Int ($value : int) {\n    my $self = new Int;\n    $self->{value} = $value;\n    return $self;\n  }\n}";
      SPVM_COMPILER_add_source(compiler, basic_type_name, source, strlen(source));
    }
    
    // Add Long source
    {
      const char* basic_type_name = "Long";
      const char* source = "class Long {\n  has value : ro long;\n  static method new : Long ($value : long) {\n    my $self = new Long;\n    $self->{value} = $value;\n    return $self;\n  }\n}";
      SPVM_COMPILER_add_source(compiler, basic_type_name, source, strlen(source));
    }
    
    // Add Float source
    {
      const char* basic_type_name = "Float";
      const char* source = "class Float {\n  has value : ro float;\n  static method new : Float ($value : float) {\n    my $self = new Float;\n    $self->{value} = $value;\n    return $self;\n  }\n}";
      SPVM_COMPILER_add_source(compiler, basic_type_name, source, strlen(source));
    }
    
    // Add Double source
    {
      const char* basic_type_name = "Double";
      const char* source = "class Double {\n  has value : ro double;\n  static method new : Double ($value : double) {\n    my $self = new Double;\n    $self->{value} = $value;\n    return $self;\n  }\n}";
      SPVM_COMPILER_add_source(compiler, basic_type_name, source, strlen(source));
    }
    
    // Add CommandInfo source
    {
      const char* basic_type_name = "CommandInfo";
      const char* source = "class CommandInfo {\n  our $PROGRAM_NAME : ro string;\n  our $ARGV : ro string[];\n  our $BASE_TIME : ro long;\n  }";
      SPVM_COMPILER_add_source(compiler, basic_type_name, source, strlen(source));
    }
    
    // Add Address source
    {
      const char* basic_type_name = "Address";
      const char* source = "class Address : pointer {\n  static method new : Address () {\n    my $self = new Address;\n    return $self;\n  }\n}";
      SPVM_COMPILER_add_source(compiler, basic_type_name, source, strlen(source));
    }
  }
  
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
  
  int32_t die_error_id = 0;
  
  int32_t compile_start_memory_blocks_count_tmp = compiler->allocator->memory_blocks_count_tmp;
  
  compiler->ops = SPVM_LIST_new(compiler->allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
  compiler->op_use_stack = SPVM_LIST_new(compiler->allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
  compiler->op_types = SPVM_LIST_new(compiler->allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
  
  SPVM_COMPILER_use_default_loaded_classes(compiler);
  
  // Use the class that is specified at the argument
  if (basic_type_name) {
    SPVM_CONSTANT_STRING* basic_type_name_string = SPVM_CONSTANT_STRING_new(compiler, basic_type_name, strlen(basic_type_name));
    basic_type_name = basic_type_name_string->value;
    SPVM_COMPILER_use(compiler, basic_type_name, start_file, start_line);
  }
  
  /* Tokenize and Parse */
  int32_t parse_error_flag = SPVM_yyparse(compiler);
  
  {
    SPVM_COMPILER_check_basic_type_id(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_UNKNOWN);
    SPVM_COMPILER_check_basic_type_id(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_UNDEF);
    SPVM_COMPILER_check_basic_type_id(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_VOID);
    SPVM_COMPILER_check_basic_type_id(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE);
    SPVM_COMPILER_check_basic_type_id(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT);
    SPVM_COMPILER_check_basic_type_id(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_INT);
    SPVM_COMPILER_check_basic_type_id(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_LONG);
    SPVM_COMPILER_check_basic_type_id(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT);
    SPVM_COMPILER_check_basic_type_id(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE);
    SPVM_COMPILER_check_basic_type_id(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_STRING);
    SPVM_COMPILER_check_basic_type_id(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_ANY_OBJECT);
    SPVM_COMPILER_check_basic_type_id(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE_CLASS);
    SPVM_COMPILER_check_basic_type_id(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT_CLASS);
    SPVM_COMPILER_check_basic_type_id(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_INT_CLASS);
    SPVM_COMPILER_check_basic_type_id(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_LONG_CLASS);
    SPVM_COMPILER_check_basic_type_id(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT_CLASS);
    SPVM_COMPILER_check_basic_type_id(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE_CLASS);
    SPVM_COMPILER_check_basic_type_id(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_BOOL_CLASS);
    SPVM_COMPILER_check_basic_type_id(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS);
    SPVM_COMPILER_check_basic_type_id(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS);
    SPVM_COMPILER_check_basic_type_id(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS);
    SPVM_COMPILER_check_basic_type_id(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_COMMAND_INFO_CLASS);
    SPVM_COMPILER_check_basic_type_id(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_ADDRESS_CLASS);
  }
  
  if (parse_error_flag) {
    die_error_id = 1;
  }
  else {
    if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
      die_error_id = 2;
    }
    else {
      // Check syntax
      SPVM_CHECK_check(compiler);
      if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
        die_error_id = 3;
      }
      else {
        // Build operation code
        int32_t build_opcode_array_start_memory_blocks_count_tmp = compiler->allocator->memory_blocks_count_tmp;
        SPVM_OPCODE_BUILDER_build_opcode_array(compiler);
        assert(compiler->allocator->memory_blocks_count_tmp == build_opcode_array_start_memory_blocks_count_tmp);
        if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
          die_error_id = 4;
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
        use->alias_name = NULL;
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
        field_access->op_name = NULL;
        field_access->field = NULL;
        SPVM_ALLOCATOR_free_memory_block_tmp(compiler->allocator, field_access);
        break;
      }
      case SPVM_OP_C_ID_CALL_METHOD: {
        SPVM_CALL_METHOD* call_method = op->uv.call_method;
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
        if (!var_decl->is_permanent) {
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
  for (int32_t basic_type_id = compiler->basic_types_base_id; basic_type_id < compiler->basic_types->length; basic_type_id++) {
    SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, basic_type_id);
    
    SPVM_LIST_free(basic_type->allows);
    
    SPVM_LIST* methods = basic_type->methods;
    {
      int32_t method_index;
      for (method_index = 0; method_index < methods->length; method_index++) {
        SPVM_METHOD* method = SPVM_LIST_get(methods, method_index);
        method->op_method = NULL;
        method->op_name = NULL;
        method->op_block = NULL;
      }
    }
  }
  
  // Free
  SPVM_LIST_free(compiler->op_use_stack);
  compiler->op_use_stack = NULL;
  
  SPVM_LIST_free(compiler->op_types);
  compiler->op_types = NULL;
  
  SPVM_LIST_free(compiler->ops);
  compiler->ops = NULL;
  
  assert(compiler->allocator->memory_blocks_count_tmp == compile_start_memory_blocks_count_tmp);
  
  return die_error_id;
}

int32_t SPVM_COMPILER_calculate_runtime_codes_length(SPVM_COMPILER* compiler) {
  
  int32_t length = 0;
  
  // string_pool_runtime_codes_length
  length++;
  
  // string_pool
  length += (compiler->global_string_pool->length / sizeof(int32_t)) + 1;
  
  // constant_strings length
  length++;
  
  // constant_strings_runtime_codes_length
  length++;
  
  // constant_strings
  length += (sizeof(SPVM_RUNTIME_CONSTANT_STRING) / sizeof(int32_t)) * (compiler->global_constant_strings->length + 1);
  
  // basic_types length
  length++;
  
  // basic_types_runtime_codes_length
  length++;
  
  // basic_types
  length += (sizeof(SPVM_RUNTIME_BASIC_TYPE) / sizeof(int32_t)) * (compiler->basic_types->length + 1);
  
  // class_vars_runtime_codes_length
  length++;
  
  // class_vars
  length += (sizeof(SPVM_RUNTIME_CLASS_VAR) / sizeof(int32_t)) * (SPVM_COMPILER_get_class_vars_length(compiler) + 1);
  
  // methods_runtime_codes_length
  length++;
  
  // methods
  length += (sizeof(SPVM_RUNTIME_METHOD) / sizeof(int32_t)) * (SPVM_COMPILER_get_methods_length(compiler) + 1);
  
  // fields_runtime_codes_length
  length++;
  
  // fields
  length += (sizeof(SPVM_RUNTIME_FIELD) / sizeof(int32_t)) * (SPVM_COMPILER_get_fields_length(compiler) + 1);
  
  // args_runtime_codes_length
  length++;
  
  // args
  length += (sizeof(SPVM_RUNTIME_ARG) / sizeof(int32_t)) * (SPVM_COMPILER_get_args_length(compiler) + 1);
  
  // opcodes_runtime_codes_length
  length++;
  
  // opcodes
  length += (sizeof(SPVM_OPCODE) / sizeof(int32_t)) * (compiler->opcode_array->length + 1);
  
  // anon_basic_type_basic_types_runtime_codes_length
  length++;
  
  // anon_basic_type_ids
  length += (sizeof(int32_t) / sizeof(int32_t)) * (SPVM_COMPILER_get_anon_basic_types_length(compiler) + 1);
  
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
  
  // string_pool_runtime_codes_length
  int32_t string_pool_runtime_codes_length = (compiler->global_string_pool->length / sizeof(int32_t)) + 1;
  *runtime_codes_ptr = string_pool_runtime_codes_length;
  runtime_codes_ptr++;
  
  // string_pool
  memcpy(runtime_codes_ptr, compiler->global_string_pool->value, sizeof(int32_t) * string_pool_runtime_codes_length);
  runtime_codes_ptr += string_pool_runtime_codes_length;
  
  // constant_strings length
  *runtime_codes_ptr = compiler->global_constant_strings->length;
  runtime_codes_ptr++;
  
  // constant_strings_runtime_codes_length
  int32_t constant_strings_runtime_codes_length = (sizeof(SPVM_RUNTIME_CONSTANT_STRING) / sizeof(int32_t)) * (compiler->global_constant_strings->length + 1);
  *runtime_codes_ptr = constant_strings_runtime_codes_length;
  runtime_codes_ptr++;
  
  // constant_strings
  int32_t* constant_string_runtime_codes_ptr = runtime_codes_ptr;
  for (int32_t constant_string_id = 0; constant_string_id < compiler->global_constant_strings->length; constant_string_id++) {
    SPVM_CONSTANT_STRING* string = SPVM_LIST_get(compiler->global_constant_strings, constant_string_id);
    SPVM_RUNTIME_CONSTANT_STRING* runtime_string = (SPVM_RUNTIME_CONSTANT_STRING*)constant_string_runtime_codes_ptr;
    
    runtime_string->address_id = string->address_id;
    runtime_string->length = string->length;
    runtime_string->string_pool_address_id = string->string_pool_address_id;
    constant_string_runtime_codes_ptr += sizeof(SPVM_RUNTIME_CONSTANT_STRING) / sizeof(int32_t);
  }
  runtime_codes_ptr += constant_strings_runtime_codes_length;
  
  // basic_types length
  *runtime_codes_ptr = compiler->basic_types->length;
  runtime_codes_ptr++;
  
  // basic_types_runtime_codes_length
  int32_t basic_types_runtime_codes_length = (sizeof(SPVM_RUNTIME_BASIC_TYPE) / sizeof(int32_t)) * (compiler->basic_types->length + 1);
  *runtime_codes_ptr = basic_types_runtime_codes_length;
  runtime_codes_ptr++;
  
  // basic_types
  int32_t class_vars_base = 0;
  int32_t fields_base = 0;
  int32_t methods_base = 0;
  int32_t args_base = 0;
  int32_t* basic_type_runtime_codes_ptr = runtime_codes_ptr;
  for (int32_t basic_type_id = 0; basic_type_id < compiler->basic_types->length; basic_type_id++) {
    SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, basic_type_id);
    SPVM_RUNTIME_BASIC_TYPE* runtime_basic_type = (SPVM_RUNTIME_BASIC_TYPE*)basic_type_runtime_codes_ptr;
    
    runtime_basic_type->id = basic_type->id;
    runtime_basic_type->category = basic_type->category;
    
    SPVM_CONSTANT_STRING* basic_type_string = SPVM_HASH_get(compiler->global_constant_string_symtable, basic_type->name, strlen(basic_type->name));
    runtime_basic_type->name_string_address_id = basic_type_string->address_id;
    
    if (basic_type->module_rel_file) {
      SPVM_CONSTANT_STRING* basic_type_rel_file_string = SPVM_HASH_get(compiler->global_constant_string_symtable, basic_type->module_rel_file, strlen(basic_type->module_rel_file));
      runtime_basic_type->module_rel_file_string_address_id = basic_type_rel_file_string->address_id;
    }
    else {
      runtime_basic_type->module_rel_file_string_address_id = -1;
    }
    
    if (basic_type->module_dir) {
      SPVM_CONSTANT_STRING* basic_type_dir_string = SPVM_HASH_get(compiler->global_constant_string_symtable, basic_type->module_dir, strlen(basic_type->module_dir));
      runtime_basic_type->module_dir_string_address_id = basic_type_dir_string->address_id;
    }
    else {
      runtime_basic_type->module_dir_string_address_id = -1;
    }
    
    runtime_basic_type->is_anon = basic_type->is_anon;
    
    runtime_basic_type->is_pointer = basic_type->is_pointer;
    
    if (basic_type->parent_name) {
      SPVM_BASIC_TYPE* parent_basic_type = SPVM_HASH_get(compiler->basic_type_symtable, basic_type->parent_name, strlen(basic_type->parent_name));
      runtime_basic_type->parent_id = parent_basic_type->id;
    }
    else {
      runtime_basic_type->parent_id = -1;
    }
    
    runtime_basic_type->fields_size = basic_type->fields_size;
    
    if (basic_type->version_string) {
      SPVM_CONSTANT_STRING* basic_type_version_string = SPVM_HASH_get(compiler->global_constant_string_symtable, basic_type->version_string, strlen(basic_type->version_string));
      runtime_basic_type->version_string_string_address_id = basic_type_version_string->address_id;
    }
    else {
      runtime_basic_type->version_string_string_address_id = -1;
    }
    
    if (basic_type->init_method) {
      runtime_basic_type->init_method_index = basic_type->init_method->index;
    }
    else {
      runtime_basic_type->init_method_index = -1;
    }
    
    if (basic_type->destructor_method) {
      runtime_basic_type->destructor_method_index = basic_type->destructor_method->index;
    }
    else {
      runtime_basic_type->destructor_method_index = -1;
    }
    
    if (basic_type->category == SPVM_NATIVE_C_BASIC_TYPE_CATEGORY_INTERFACE) {
      assert(basic_type->required_method);
    }
    
    if (basic_type->required_method) {
      runtime_basic_type->required_method_index = basic_type->required_method->index;
    }
    else {
      runtime_basic_type->required_method_index = -1;
    }
    
    runtime_basic_type->methods_length = basic_type->methods->length;
    if (basic_type->methods->length > 0) {
      runtime_basic_type->methods_base = methods_base;
      methods_base += basic_type->methods->length;
    }
    else {
      runtime_basic_type->methods_base = -1;
    }
    
    runtime_basic_type->fields_length = basic_type->fields->length;
    if (basic_type->fields->length > 0) {
      runtime_basic_type->fields_base = fields_base;
      fields_base += basic_type->fields->length;
    }
    else {
      runtime_basic_type->fields_base = -1;
    }
    
    runtime_basic_type->class_vars_length = basic_type->class_vars->length;
    if (basic_type->class_vars->length > 0) {
      runtime_basic_type->class_vars_base = class_vars_base;
      class_vars_base += basic_type->class_vars->length;
    }
    else {
      runtime_basic_type->class_vars_base = -1;
    }
    
    basic_type_runtime_codes_ptr += sizeof(SPVM_RUNTIME_BASIC_TYPE) / sizeof(int32_t);
  }
  runtime_codes_ptr += basic_types_runtime_codes_length;
  
  // class_vars_runtime_codes_length
  int32_t class_vars_runtime_codes_length = (sizeof(SPVM_RUNTIME_CLASS_VAR) / sizeof(int32_t)) * (SPVM_COMPILER_get_class_vars_length(compiler) + 1);
  *runtime_codes_ptr = class_vars_runtime_codes_length;
  runtime_codes_ptr++;
  
  // class_vars
  int32_t* class_var_runtime_codes_ptr = runtime_codes_ptr;
  for (int32_t basic_type_id = 0; basic_type_id < compiler->basic_types->length; basic_type_id++) {
    SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, basic_type_id);
    for (int32_t class_var_index = 0; class_var_index < basic_type->class_vars->length; class_var_index++) {
      SPVM_CLASS_VAR* class_var = SPVM_LIST_get(basic_type->class_vars, class_var_index);
      SPVM_RUNTIME_CLASS_VAR* runtime_class_var = (SPVM_RUNTIME_CLASS_VAR*)class_var_runtime_codes_ptr;
      
      runtime_class_var->index = class_var->index;
      runtime_class_var->basic_type_id = class_var->type->basic_type->id;
      runtime_class_var->type_dimension = class_var->type->dimension;
      runtime_class_var->type_flag = class_var->type->flag;
      runtime_class_var->current_basic_type_id = class_var->current_basic_type->id;
      
      SPVM_CONSTANT_STRING* class_var_name_string = SPVM_HASH_get(compiler->global_constant_string_symtable, class_var->name, strlen(class_var->name));
      runtime_class_var->name_string_address_id = class_var_name_string->address_id;
      
      class_var_runtime_codes_ptr += sizeof(SPVM_RUNTIME_CLASS_VAR) / sizeof(int32_t);
    }
  }
  runtime_codes_ptr += class_vars_runtime_codes_length;
  
  // fields_runtime_codes_length
  int32_t fields_runtime_codes_length = (sizeof(SPVM_RUNTIME_FIELD) / sizeof(int32_t)) * (SPVM_COMPILER_get_fields_length(compiler) + 1);
  *runtime_codes_ptr = fields_runtime_codes_length;
  runtime_codes_ptr++;
  
  // fields
  int32_t* field_runtime_codes_ptr = runtime_codes_ptr;
  for (int32_t basic_type_id = 0; basic_type_id < compiler->basic_types->length; basic_type_id++) {
    SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, basic_type_id);
    for (int32_t field_index = 0; field_index < basic_type->fields->length; field_index++) {
      SPVM_FIELD* field = SPVM_LIST_get(basic_type->fields, field_index);
      SPVM_RUNTIME_FIELD* runtime_field = (SPVM_RUNTIME_FIELD*)field_runtime_codes_ptr;
      
      runtime_field->index = field->index;
      runtime_field->offset = field->offset;
      runtime_field->basic_type_id = field->type->basic_type->id;
      runtime_field->type_dimension = field->type->dimension;
      runtime_field->type_flag = field->type->flag;
      runtime_field->current_basic_type_id = field->current_basic_type->id;
      
      SPVM_CONSTANT_STRING* field_name_string = SPVM_HASH_get(compiler->global_constant_string_symtable, field->name, strlen(field->name));
      runtime_field->name_string_address_id = field_name_string->address_id;
      
      field_runtime_codes_ptr += sizeof(SPVM_RUNTIME_FIELD) / sizeof(int32_t);
    }
  }
  runtime_codes_ptr += fields_runtime_codes_length;
  
  // opcodes_runtime_codes_length
  int32_t opcodes_runtime_codes_length = (sizeof(SPVM_OPCODE) / sizeof(int32_t)) * (compiler->opcode_array->length + 1);
  *runtime_codes_ptr = opcodes_runtime_codes_length;
  runtime_codes_ptr++;
  
  // opcodes
  memcpy(runtime_codes_ptr, compiler->opcode_array->values, sizeof(int32_t) * opcodes_runtime_codes_length);
  runtime_codes_ptr += opcodes_runtime_codes_length;
  
  // methods_runtime_codes_length
  int32_t methods_runtime_codes_length = (sizeof(SPVM_RUNTIME_METHOD) / sizeof(int32_t)) * (SPVM_COMPILER_get_methods_length(compiler) + 1);
  *runtime_codes_ptr = methods_runtime_codes_length;
  runtime_codes_ptr++;
  
  // methods
  int32_t* method_runtime_codes_ptr = runtime_codes_ptr;
  
  for (int32_t basic_type_id = 0; basic_type_id < compiler->basic_types->length; basic_type_id++) {
    SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, basic_type_id);
    for (int32_t method_index = 0; method_index < basic_type->methods->length; method_index++) {
      
      SPVM_METHOD* method = SPVM_LIST_get(basic_type->methods, method_index);
      SPVM_RUNTIME_METHOD* runtime_method = (SPVM_RUNTIME_METHOD*)method_runtime_codes_ptr;
      
      runtime_method->opcodes_base = method->opcodes_base_address_id;
      runtime_method->opcodes_length = method->opcodes_length;
      runtime_method->index = method->index;
      runtime_method->current_basic_type_id = method->current_basic_type->id;
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
      runtime_method->return_basic_type_id = method->return_type->basic_type->id;
      runtime_method->return_type_dimension = method->return_type->dimension;
      runtime_method->return_type_flag = method->return_type->flag;
      runtime_method->is_native = method->is_native;
      runtime_method->is_precompile = method->is_precompile;
      runtime_method->is_destructor = method->is_destructor;
      runtime_method->is_required = method->is_required;
      runtime_method->is_enum = method->is_enum;
      
      SPVM_CONSTANT_STRING* method_name_string = SPVM_HASH_get(compiler->global_constant_string_symtable, method->name, strlen(method->name));
      runtime_method->name_string_address_id = method_name_string->address_id;
      
      runtime_method->args_length = method->args_length;
      if (method->args_length > 0) {
        runtime_method->args_base = args_base;
        args_base += method->args_length;
      }
      else {
        runtime_method->args_base = -1;
      }
      runtime_method->required_args_length = method->required_args_length;
      
      method_runtime_codes_ptr += sizeof(SPVM_RUNTIME_METHOD) / sizeof(int32_t);
    }
  }
  runtime_codes_ptr += methods_runtime_codes_length;
  
  // args_runtime_codes_length
  int32_t args_runtime_codes_length = (sizeof(SPVM_RUNTIME_ARG) / sizeof(int32_t)) * (SPVM_COMPILER_get_args_length(compiler) + 1);
  *runtime_codes_ptr = args_runtime_codes_length;
  runtime_codes_ptr++;
  
  // args
  int32_t* arg_runtime_codes_ptr = runtime_codes_ptr;
  for (int32_t basic_type_id = 0; basic_type_id < compiler->basic_types->length; basic_type_id++) {
    SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, basic_type_id);
    for (int32_t method_index = 0; method_index < basic_type->methods->length; method_index++) {
      
      SPVM_METHOD* method = SPVM_LIST_get(basic_type->methods, method_index);
      for (int32_t arg_index = 0; arg_index < method->args_length; arg_index++) {
        SPVM_VAR_DECL* arg_var_decl = SPVM_LIST_get(method->var_decls, arg_index);
        SPVM_RUNTIME_ARG* runtime_arg = (SPVM_RUNTIME_ARG*)arg_runtime_codes_ptr;
        
        runtime_arg->index = arg_index;
        runtime_arg->basic_type_id = arg_var_decl->type->basic_type->id;
        runtime_arg->type_dimension = arg_var_decl->type->dimension;
        runtime_arg->type_flag = arg_var_decl->type->flag;
        
        arg_runtime_codes_ptr += sizeof(SPVM_RUNTIME_ARG) / sizeof(int32_t);
      }
    }
  }
  runtime_codes_ptr += args_runtime_codes_length;
  
  // anon_basic_type_basic_types_runtime_codes_length
  int32_t anon_basic_type_runtime_codes_length = (sizeof(int32_t) / sizeof(int32_t)) * (SPVM_COMPILER_get_anon_basic_types_length(compiler) + 1);
  *runtime_codes_ptr = anon_basic_type_runtime_codes_length;
  runtime_codes_ptr++;
  
  // anon_basic_type_ids
  int32_t* anon_basic_type_runtime_codes_ptr = runtime_codes_ptr;
  for (int32_t basic_type_id = 0; basic_type_id < compiler->basic_types->length; basic_type_id++) {
    SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, basic_type_id);
    for (int32_t anon_basic_type_index = 0; anon_basic_type_index < basic_type->anon_basic_types->length; anon_basic_type_index++) {
      SPVM_BASIC_TYPE* anon_basic_type = SPVM_LIST_get(basic_type->anon_basic_types, anon_basic_type_index);
      *anon_basic_type_runtime_codes_ptr = anon_basic_type->id;
      anon_basic_type_runtime_codes_ptr += sizeof(int32_t) / sizeof(int32_t);
    }
  }
  runtime_codes_ptr += anon_basic_type_runtime_codes_length;
  
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
  
  SPVM_COMPILER_clear_include_dirs(compiler);
  
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

int32_t SPVM_COMPILER_get_include_dirs_length(SPVM_COMPILER* compiler) {
  SPVM_LIST* include_dirs = compiler->include_dirs;
  int32_t include_dirs_length = include_dirs->length;
  return include_dirs_length;
}

void SPVM_COMPILER_add_include_dir(SPVM_COMPILER* compiler, const char* include_dir) {  
  int32_t include_dir_length = strlen(include_dir);
  char* compiler_include_dir = SPVM_ALLOCATOR_alloc_memory_block_tmp(compiler->allocator, include_dir_length + 1);
  memcpy(compiler_include_dir, include_dir, include_dir_length);
  SPVM_LIST_push(compiler->include_dirs, (void*)compiler_include_dir);
}

void SPVM_COMPILER_clear_include_dirs(SPVM_COMPILER* compiler) {
  int32_t include_dirs_length = SPVM_COMPILER_get_include_dirs_length(compiler);
  
  for (int32_t i = 0; i < include_dirs_length; i++) {
    const char* include_dir = SPVM_COMPILER_get_include_dir(compiler, i);
    SPVM_ALLOCATOR_free_memory_block_tmp(compiler->allocator, (void*)include_dir);
    include_dir = NULL;
  }
  
  SPVM_LIST_clear(compiler->include_dirs);
}

const char* SPVM_COMPILER_get_include_dir (SPVM_COMPILER* compiler, int32_t include_dir_id) {
  const char* include_dir = SPVM_LIST_get(compiler->include_dirs, include_dir_id);
  return include_dir;
}

int32_t SPVM_COMPILER_get_class_vars_length(SPVM_COMPILER* compiler) {
  
  int32_t class_vars_length = 0;
  for (int32_t basic_type_id = 0; basic_type_id < compiler->basic_types->length; basic_type_id++) {
    SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, basic_type_id);
    class_vars_length += basic_type->class_vars->length;
  }
  
  return class_vars_length;
}

int32_t SPVM_COMPILER_get_fields_length(SPVM_COMPILER* compiler) {
  
  int32_t fields_length = 0;
  for (int32_t basic_type_id = 0; basic_type_id < compiler->basic_types->length; basic_type_id++) {
    SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, basic_type_id);
    fields_length += basic_type->fields->length;
  }
  
  return fields_length;
}

int32_t SPVM_COMPILER_get_methods_length(SPVM_COMPILER* compiler) {
  
  int32_t methods_length = 0;
  for (int32_t basic_type_id = 0; basic_type_id < compiler->basic_types->length; basic_type_id++) {
    SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, basic_type_id);
    methods_length += basic_type->methods->length;
  }
  
  return methods_length;
}

int32_t SPVM_COMPILER_get_anon_basic_types_length(SPVM_COMPILER* compiler) {
  
  int32_t anon_basic_types_length = 0;
  for (int32_t basic_type_id = 0; basic_type_id < compiler->basic_types->length; basic_type_id++) {
    SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, basic_type_id);
    anon_basic_types_length += basic_type->anon_basic_types->length;
  }
  
  return anon_basic_types_length;
}

int32_t SPVM_COMPILER_get_args_length(SPVM_COMPILER* compiler) {
  
  int32_t args_length = 0;
  for (int32_t basic_type_id = 0; basic_type_id < compiler->basic_types->length; basic_type_id++) {
    SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, basic_type_id);
    for (int32_t method_index = 0;method_index < basic_type->methods->length; method_index++) {
      SPVM_METHOD* method = SPVM_LIST_get(basic_type->methods, method_index);
      args_length += method->args_length;
    }
  }
  
  return args_length;
}
