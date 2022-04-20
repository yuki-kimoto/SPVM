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
  compiler->module_dirs = SPVM_LIST_new_list_permanent(compiler->allocator, 0);
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
  compiler->module_source_symtable = SPVM_HASH_new_hash_permanent(compiler->allocator, 0);
  compiler->switch_infos = SPVM_LIST_new_list_permanent(compiler->allocator, 0);
  compiler->not_found_class_class_symtable = SPVM_HASH_new_hash_permanent(compiler->allocator, 0);

  // Add basic types
  SPVM_COMPILER_add_basic_types(compiler);

  // Add Bool source
  const char* spvm_bool_module_source = "class Bool {\n  INIT {\n    $TRUE = new Bool;\n    $TRUE->{value} = 1;\n    $FALSE = new Bool;\n    $FALSE->{value} = 0;\n  }\n  \n  our $TRUE : ro Bool;\n  our $FALSE : ro Bool;\n  has value : ro int;\n}";
  SPVM_HASH_set(compiler->module_source_symtable, "Bool", strlen("Bool"), (void*)spvm_bool_module_source);

  // Add Byte source
  const char* spvm_byte_module_source = "class Byte {\n  has value : ro byte;\n  static method new : Byte ($value : byte) {\n    my $self = new Byte;\n    $self->{value} = $value;\n    return $self;\n  }\n}";
  SPVM_HASH_set(compiler->module_source_symtable, "Byte", strlen("Byte"), (void*)spvm_byte_module_source);

  // Add Short source
  const char* spvm_short_module_source = "class Short {\n  has value : ro short;\n  static method new : Short ($value : short) {\n    my $self = new Short;\n    $self->{value} = $value;\n    return $self;\n  }\n}";
  SPVM_HASH_set(compiler->module_source_symtable, "Short", strlen("Short"), (void*)spvm_short_module_source);

  // Add Int source
  const char* spvm_int_module_source = "class Int {\n  has value : ro int;\n  static method new : Int ($value : int) {\n    my $self = new Int;\n    $self->{value} = $value;\n    return $self;\n  }\n}";
  SPVM_HASH_set(compiler->module_source_symtable, "Int", strlen("Int"), (void*)spvm_int_module_source);

  // Add Long source
  const char* spvm_long_module_source = "class Long {\n  has value : ro long;\n  static method new : Long ($value : long) {\n    my $self = new Long;\n    $self->{value} = $value;\n    return $self;\n  }\n}";
  SPVM_HASH_set(compiler->module_source_symtable, "Long", strlen("Long"), (void*)spvm_long_module_source);

  // Add Float source
  const char* spvm_float_module_source = "class Float {\n  has value : ro float;\n  static method new : Float ($value : float) {\n    my $self = new Float;\n    $self->{value} = $value;\n    return $self;\n  }\n}";
  SPVM_HASH_set(compiler->module_source_symtable, "Float", strlen("Float"), (void*)spvm_float_module_source);

  // Add Double source
  const char* spvm_double_module_source = "class Double {\n  has value : ro double;\n  static method new : Double ($value : double) {\n    my $self = new Double;\n    $self->{value} = $value;\n    return $self;\n  }\n}";
  SPVM_HASH_set(compiler->module_source_symtable, "Double", strlen("Double"), (void*)spvm_double_module_source);

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
  SPVM_COMPILER_add_basic_type(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE_OBJECT);
  SPVM_COMPILER_add_basic_type(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT_OBJECT);
  SPVM_COMPILER_add_basic_type(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_INT_OBJECT);
  SPVM_COMPILER_add_basic_type(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_LONG_OBJECT);
  SPVM_COMPILER_add_basic_type(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT_OBJECT);
  SPVM_COMPILER_add_basic_type(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE_OBJECT);
  SPVM_COMPILER_add_basic_type(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_BOOL_OBJECT);
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

int32_t SPVM_COMPILER_compile_spvm(SPVM_COMPILER* compiler, const char* class_name) {
  
  SPVM_CONSTANT_STRING* class_name_string = SPVM_CONSTANT_STRING_new(compiler, class_name, strlen(class_name));
  class_name = class_name_string->value;

  compiler->cur_class_base = compiler->classes->length;

  int32_t cur_basic_type_base = compiler->basic_types->length;
  
  const char* start_file = compiler->start_file;
  int32_t start_line = compiler->start_line;
  
  //yacc/bison debug mode. The default is off.
  SPVM_yydebug = 0;

#ifdef SPVM_DEBUG_YACC
  // Turn on yacc/bison debug mode
  SPVM_yydebug = 1;
#endif

  compiler->parse_start = 1;

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
  
  // Use automatically loaded modules
  SPVM_COMPILER_use(compiler, "Bool", "Bool", 0);
  SPVM_COMPILER_use(compiler, "Byte", "Byte", 0);
  SPVM_COMPILER_use(compiler, "Short", "Short", 0);
  SPVM_COMPILER_use(compiler, "Int", "Int", 0);
  SPVM_COMPILER_use(compiler, "Long", "Long", 0);
  SPVM_COMPILER_use(compiler, "Float", "Float", 0);
  SPVM_COMPILER_use(compiler, "Double", "Double", 0);
  
  // Use the module that is specified at the argument
  SPVM_COMPILER_use(compiler, class_name, start_file, start_line);

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
      case SPVM_OP_C_ID_DESCRIPTOR: {
        SPVM_ALLOCATOR_free_memory_block_tmp(compiler->allocator, op->uv.descriptor);
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
      case SPVM_OP_C_ID_IMPLEMENT: {
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
        field_access->op_term = NULL;
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

int32_t SPVM_COMPILER_calculate_runtime_spvm_32bit_codes_length(SPVM_COMPILER* compiler) {

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

void SPVM_COMPILER_build_runtime_spvm_32bit_codes(SPVM_COMPILER* compiler, SPVM_RUNTIME* runtime) {
  
  SPVM_ALLOCATOR* allocator = runtime->allocator;
  
  int32_t spvvm_32bit_codes_length = SPVM_COMPILER_calculate_runtime_spvm_32bit_codes_length(compiler);
  int32_t* spvm_32bit_codes = SPVM_ALLOCATOR_alloc_memory_block_permanent(allocator, sizeof(int32_t) * spvvm_32bit_codes_length);

  int32_t* spvm_32bit_codes_ptr = spvm_32bit_codes;
  
  // opcodes length
  *spvm_32bit_codes_ptr = compiler->opcode_array->length;
  spvm_32bit_codes_ptr++;
  
  // opcodes 32bit length
  int32_t opcodes_32bit_length = (sizeof(SPVM_OPCODE) / sizeof(int32_t)) * (compiler->opcode_array->length + 1);
  *spvm_32bit_codes_ptr = opcodes_32bit_length;
  spvm_32bit_codes_ptr++;
  
  // opcodes
  memcpy(spvm_32bit_codes_ptr, compiler->opcode_array->values, sizeof(int32_t) * opcodes_32bit_length);
  spvm_32bit_codes_ptr += opcodes_32bit_length;
  
  // constant_strings_buffer length
  *spvm_32bit_codes_ptr = compiler->constant_strings_buffer->length;
  spvm_32bit_codes_ptr++;

  // constant_strings_buffer 32bit length
  int32_t constant_strings_buffer_32bit_length = (compiler->constant_strings_buffer->length / sizeof(int32_t)) + 1;
  *spvm_32bit_codes_ptr = opcodes_32bit_length;
  spvm_32bit_codes_ptr++;
  
  // constant_strings_buffer
  memcpy(spvm_32bit_codes_ptr, compiler->constant_strings_buffer->value, sizeof(int32_t) * constant_strings_buffer_32bit_length);
  spvm_32bit_codes_ptr += constant_strings_buffer_32bit_length;
  
  // constant_strings length
  *spvm_32bit_codes_ptr = compiler->constant_strings->length;
  spvm_32bit_codes_ptr++;

  // constant_strings 32bit length
  int32_t constant_strings_32bit_length = (sizeof(SPVM_RUNTIME_CONSTANT_STRING) / sizeof(int32_t)) * (compiler->constant_strings->length + 1);
  *spvm_32bit_codes_ptr = opcodes_32bit_length;
  spvm_32bit_codes_ptr++;

  
  // constant_strings
  int32_t* constant_string_32bit_ptr = spvm_32bit_codes_ptr;
  for (int32_t constant_string_id = 0; constant_string_id < compiler->constant_strings->length; constant_string_id++) {
    SPVM_CONSTANT_STRING* string = SPVM_LIST_get(compiler->constant_strings, constant_string_id);
    SPVM_RUNTIME_CONSTANT_STRING* runtime_string = (SPVM_RUNTIME_CONSTANT_STRING*)constant_string_32bit_ptr;
    
    runtime_string->id = string->id;
    runtime_string->length = string->length;
    runtime_string->string_buffer_id = string->string_buffer_id;
    constant_string_32bit_ptr += sizeof(SPVM_RUNTIME_CONSTANT_STRING) / sizeof(int32_t);
  }
  spvm_32bit_codes_ptr += constant_strings_32bit_length;

  // anon_method_methods length
  *spvm_32bit_codes_ptr = compiler->anon_methods->length;
  spvm_32bit_codes_ptr++;

  // anon_method_methods 32bit length
  int32_t anon_method_32bit_length = (sizeof(int32_t) / sizeof(int32_t)) * (compiler->anon_methods->length + 1);
  *spvm_32bit_codes_ptr = anon_method_32bit_length;
  spvm_32bit_codes_ptr++;

  // anon_method_method_ids
  int32_t* anon_method_32bit_ptr = spvm_32bit_codes_ptr;
  for (int32_t anon_method_id = 0; anon_method_id < compiler->anon_methods->length; anon_method_id++) {
    SPVM_METHOD* anon_method = SPVM_LIST_get(compiler->anon_methods, anon_method_id);
    int32_t anon_method_id = anon_method->anon_method_id;
    *anon_method_32bit_ptr = anon_method->id;
    anon_method_32bit_ptr += sizeof(int32_t) / sizeof(int32_t);
  }
  spvm_32bit_codes_ptr += anon_method_32bit_length;

  // classes length
  *spvm_32bit_codes_ptr = compiler->classes->length;
  spvm_32bit_codes_ptr++;

  // classes 32bit length
  int32_t classes_32bit_length = (sizeof(SPVM_RUNTIME_CLASS) / sizeof(int32_t)) * (compiler->classes->length + 1);
  *spvm_32bit_codes_ptr = opcodes_32bit_length;
  spvm_32bit_codes_ptr++;

  // classes
  int32_t* class_32bit_ptr = spvm_32bit_codes_ptr;
  for (int32_t class_id = 0; class_id < compiler->classes->length; class_id++) {
    SPVM_CLASS* class = SPVM_LIST_get(compiler->classes, class_id);
    SPVM_RUNTIME_CLASS* runtime_class = (SPVM_RUNTIME_CLASS*)class_32bit_ptr;
    
    runtime_class->type_id = class->type->id;
    runtime_class->id = class->id;
    SPVM_CONSTANT_STRING* class_module_rel_file_string = SPVM_HASH_get(compiler->constant_string_symtable, class->module_rel_file, strlen(class->module_rel_file));
    runtime_class->module_rel_file_id = class_module_rel_file_string->id;

    if (class->module_dir) {
      SPVM_CONSTANT_STRING* class_module_dir_string = SPVM_HASH_get(compiler->constant_string_symtable, class->module_dir, strlen(class->module_dir));
      runtime_class->module_dir_id = class_module_dir_string->id;
    }
    else {
      runtime_class->module_dir_id = -1;
    }
    runtime_class->flag = class->flag;
    runtime_class->object_fields_length = class->object_fields_length;
    runtime_class->object_fields_offset = class->object_fields_offset;
    runtime_class->has_init_block = class->has_init_block;
    runtime_class->is_anon = class->is_anon;

    SPVM_CONSTANT_STRING* class_string = SPVM_HASH_get(compiler->constant_string_symtable, class->name, strlen(class->name));
    runtime_class->name_id = class_string->id;
    
    if (class->method_destructor) {
      runtime_class->method_destructor_id = class->method_destructor->id;
    }
    else {
      runtime_class->method_destructor_id = -1;
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

    runtime_class->interface_classes_length = class->interface_classes->length;
    if (class->interface_classes->length > 0) {
      SPVM_CLASS* interface_class = SPVM_LIST_get(class->interface_classes, 0);
      runtime_class->interface_classes_base_id = interface_class->id;
    }
    else {
      runtime_class->interface_classes_base_id = -1;
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
  spvm_32bit_codes_ptr += classes_32bit_length;

  // basic_types length
  *spvm_32bit_codes_ptr = compiler->basic_types->length;
  spvm_32bit_codes_ptr++;

  // basic_types 32bit length
  int32_t basic_types_32bit_length = (sizeof(SPVM_RUNTIME_BASIC_TYPE) / sizeof(int32_t)) * (compiler->basic_types->length + 1);
  *spvm_32bit_codes_ptr = opcodes_32bit_length;
  spvm_32bit_codes_ptr++;

  // basic_types
  int32_t* basic_type_32bit_ptr = spvm_32bit_codes_ptr;
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
  spvm_32bit_codes_ptr += basic_types_32bit_length;

  // types length
  *spvm_32bit_codes_ptr = compiler->types->length;
  spvm_32bit_codes_ptr++;

  // types 32bit length
  int32_t types_32bit_length = (sizeof(SPVM_RUNTIME_TYPE) / sizeof(int32_t)) * (compiler->types->length + 1);
  *spvm_32bit_codes_ptr = opcodes_32bit_length;
  spvm_32bit_codes_ptr++;

  // types
  int32_t* type_32bit_ptr = spvm_32bit_codes_ptr;
  for (int32_t type_id = 0; type_id < compiler->types->length; type_id++) {
    SPVM_TYPE* type = SPVM_LIST_get(compiler->types, type_id);
    SPVM_RUNTIME_TYPE* runtime_type = (SPVM_RUNTIME_TYPE*)type_32bit_ptr;
    
    runtime_type->basic_type_id = type->basic_type->id;
    runtime_type->dimension = type->dimension;
    runtime_type->flag = type->flag;
    runtime_type->width = type->width;
    runtime_type->mulnum_field_basic_type_id = SPVM_TYPE_get_mulnum_field_basic_type_id(compiler, type->basic_type->id, type->dimension, type->flag);

    type_32bit_ptr += sizeof(SPVM_RUNTIME_TYPE) / sizeof(int32_t);
  }
  spvm_32bit_codes_ptr += types_32bit_length;

  // class_vars length
  *spvm_32bit_codes_ptr = compiler->class_vars->length;
  spvm_32bit_codes_ptr++;

  // class_vars 32bit length
  int32_t class_vars_32bit_length = (sizeof(SPVM_RUNTIME_CLASS_VAR) / sizeof(int32_t)) * (compiler->class_vars->length + 1);
  *spvm_32bit_codes_ptr = opcodes_32bit_length;
  spvm_32bit_codes_ptr++;

  // class_vars
  int32_t* class_var_32bit_ptr = spvm_32bit_codes_ptr;
  for (int32_t class_var_id = 0; class_var_id < compiler->class_vars->length; class_var_id++) {
    SPVM_CLASS_VAR* class_var = SPVM_LIST_get(compiler->class_vars, class_var_id);
    SPVM_RUNTIME_CLASS_VAR* runtime_class_var = (SPVM_RUNTIME_CLASS_VAR*)class_var_32bit_ptr;

    runtime_class_var->id = class_var->id;
    runtime_class_var->type_id = class_var->type->id;
    runtime_class_var->class_id = class_var->class->id;

    SPVM_CONSTANT_STRING* class_var_name_string = SPVM_HASH_get(compiler->constant_string_symtable, class_var->name, strlen(class_var->name));
    runtime_class_var->name_id = class_var_name_string->id;

    SPVM_CONSTANT_STRING* class_var_signature_string = SPVM_HASH_get(compiler->constant_string_symtable, class_var->signature, strlen(class_var->signature));
    runtime_class_var->signature_id = class_var_signature_string->id;

    class_var_32bit_ptr += sizeof(SPVM_RUNTIME_CLASS_VAR) / sizeof(int32_t);
  }
  spvm_32bit_codes_ptr += class_vars_32bit_length;

  // methods length
  *spvm_32bit_codes_ptr = compiler->methods->length;
  spvm_32bit_codes_ptr++;

  // methods 32bit length
  int32_t methods_32bit_length = (sizeof(SPVM_RUNTIME_METHOD) / sizeof(int32_t)) * (compiler->methods->length + 1);
  *spvm_32bit_codes_ptr = opcodes_32bit_length;
  spvm_32bit_codes_ptr++;

  // methods
  int32_t* method_32bit_ptr = spvm_32bit_codes_ptr;
  for (int32_t method_id = 0; method_id < compiler->methods->length; method_id++) {
    SPVM_METHOD* method = SPVM_LIST_get(compiler->methods, method_id);
    SPVM_RUNTIME_METHOD* runtime_method = (SPVM_RUNTIME_METHOD*)method_32bit_ptr;

    runtime_method->opcodes_base_id = method->opcodes_base_id;
    runtime_method->opcodes_length = method->opcodes_length;
    runtime_method->id = method->id;
    runtime_method->class_id = method->class->id;
    runtime_method->flag = method->flag;
    runtime_method->is_class_method = method->is_class_method;
    runtime_method->is_init = method->is_init;
    runtime_method->is_anon = method->flag & SPVM_METHOD_C_FLAG_ANON;
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

    SPVM_CONSTANT_STRING* method_name_string = SPVM_HASH_get(compiler->constant_string_symtable, method->name, strlen(method->name));
    runtime_method->name_id = method_name_string->id;

    SPVM_CONSTANT_STRING* method_signature_string = SPVM_HASH_get(compiler->constant_string_symtable, method->signature, strlen(method->signature));
    runtime_method->signature_id = method_signature_string->id;

    runtime_method->args_length = method->args_length;
    if (method->args_length > 0) {
      SPVM_VAR_DECL* arg = SPVM_LIST_get(method->var_decls, 0);
      runtime_method->args_base_id = arg->arg_id;
    }
    else {
      runtime_method->args_base_id = -1;
    }

    method_32bit_ptr += sizeof(SPVM_RUNTIME_METHOD) / sizeof(int32_t);
  }
  spvm_32bit_codes_ptr += methods_32bit_length;

  // arg_type_methods length
  *spvm_32bit_codes_ptr = compiler->args->length;
  spvm_32bit_codes_ptr++;

  // arg_type_methods 32bit length
  int32_t arg_type_id_32bit_length = (sizeof(int32_t) / sizeof(int32_t)) * (compiler->args->length + 1);
  *spvm_32bit_codes_ptr = arg_type_id_32bit_length;
  spvm_32bit_codes_ptr++;

  // arg_type_method_ids
  int32_t* arg_type_id_32bit_ptr = spvm_32bit_codes_ptr;
  for (int32_t arg_id = 0; arg_id < compiler->args->length; arg_id++) {
    SPVM_VAR_DECL* arg_var_decl = SPVM_LIST_get(compiler->args, arg_id);
    int32_t arg_type_id = arg_var_decl->type->id;
    *arg_type_id_32bit_ptr = arg_type_id;
  }
  spvm_32bit_codes_ptr += arg_type_id_32bit_length;

  // fields length
  *spvm_32bit_codes_ptr = compiler->fields->length;
  spvm_32bit_codes_ptr++;

  // fields 32bit length
  int32_t fields_32bit_length = (sizeof(SPVM_RUNTIME_FIELD) / sizeof(int32_t)) * (compiler->fields->length + 1);
  *spvm_32bit_codes_ptr = opcodes_32bit_length;
  spvm_32bit_codes_ptr++;

  // fields
  int32_t* field_32bit_ptr = spvm_32bit_codes_ptr;
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

    SPVM_CONSTANT_STRING* field_signature_string = SPVM_HASH_get(compiler->constant_string_symtable, field->signature, strlen(field->signature));
    runtime_field->signature_id = field_signature_string->id;

    field_32bit_ptr += sizeof(SPVM_RUNTIME_FIELD) / sizeof(int32_t);
  }
  spvm_32bit_codes_ptr += fields_32bit_length;
  
  runtime->spvm_32bit_codes = spvm_32bit_codes;
}

void SPVM_COMPILER_build_runtime(SPVM_COMPILER* compiler, SPVM_RUNTIME* runtime) {

  SPVM_ALLOCATOR* allocator = runtime->allocator;

  SPVM_COMPILER_build_runtime_spvm_32bit_codes(compiler, runtime);
  
  int32_t* spvm_32bit_codes = runtime->spvm_32bit_codes;

  // opcodes length
  runtime->opcodes_length = *spvm_32bit_codes;
  spvm_32bit_codes++;
  
  // opcodes 32bit length
  int32_t opcodes_32bit_length = *spvm_32bit_codes;
  spvm_32bit_codes++;
  
  // opcodes
  runtime->opcodes = (SPVM_OPCODE*)spvm_32bit_codes;
  spvm_32bit_codes += opcodes_32bit_length;
  
  // constant_strings_buffer length

  // constant_strings_buffer 32bit length
  
  // constant_strings_buffer
  
  // constant_strings length

  // constant_strings 32bit length
  
  // constant_strings

  // anon_method_methods length

  // anon_method_methods 32bit length

  // anon_method_method_ids

  // classes length
  
  // classes 32bit length
  
  // classes

  // basic_types length

  // basic_types 32bit length
  
  // basic_types

  // types length

  // types 32bit length
  
  // types

  // class_vars length

  // class_vars 32bit length
  
  // class_vars

  // methods length
  
  // methods 32bit length
  
  // methods

  // arg_types length
  
  // arg_types 32bit length
  
  // arg_type_ids
  
  // fields length

  // fields 32bit length
  
  // fields

  // String buffers
  runtime->constant_strings_buffer_length = compiler->constant_strings_buffer->length;
  runtime->constant_strings_buffer = (const char*)SPVM_ALLOCATOR_alloc_memory_block_permanent(allocator, compiler->constant_strings_buffer->length + 1);
  memcpy((char*)runtime->constant_strings_buffer, compiler->constant_strings_buffer->value, compiler->constant_strings_buffer->length);

  
  // Strings
  runtime->constant_strings_length = compiler->constant_strings->length;
  runtime->constant_strings = SPVM_ALLOCATOR_alloc_memory_block_permanent(allocator, sizeof(SPVM_RUNTIME_CONSTANT_STRING) * (compiler->constant_strings->length + 1));
  for (int32_t constant_string_id = 0; constant_string_id < compiler->constant_strings->length; constant_string_id++) {
    SPVM_CONSTANT_STRING* string = SPVM_LIST_get(compiler->constant_strings, constant_string_id);
    SPVM_RUNTIME_CONSTANT_STRING* runtime_string = &runtime->constant_strings[constant_string_id];
    
    runtime_string->id = string->id;
    runtime_string->length = string->length;
    runtime_string->string_buffer_id = string->string_buffer_id;
  }

  // Runtime classes
  runtime->classes_length = compiler->classes->length;
  runtime->classes = SPVM_ALLOCATOR_alloc_memory_block_permanent(allocator, sizeof(SPVM_RUNTIME_CLASS) * (compiler->classes->length + 1));
  runtime->anon_method_methods_length = compiler->anon_methods->length;
  runtime->anon_method_method_ids = SPVM_ALLOCATOR_alloc_memory_block_permanent(allocator, sizeof(int32_t) * (compiler->anon_methods->length + 1));
  for (int32_t anon_method_id = 0; anon_method_id < compiler->anon_methods->length; anon_method_id++) {
    SPVM_METHOD* anon_method = SPVM_LIST_get(compiler->anon_methods, anon_method_id);
    int32_t anon_method_id = anon_method->anon_method_id;
    runtime->anon_method_method_ids[anon_method_id] = anon_method->id;
  }
  for (int32_t class_id = 0; class_id < compiler->classes->length; class_id++) {
    SPVM_CLASS* class = SPVM_LIST_get(compiler->classes, class_id);
    SPVM_RUNTIME_CLASS* runtime_class = &runtime->classes[class_id];
    
    runtime_class->type_id = class->type->id;
    runtime_class->id = class->id;
    SPVM_CONSTANT_STRING* class_module_rel_file_string = SPVM_HASH_get(compiler->constant_string_symtable, class->module_rel_file, strlen(class->module_rel_file));
    runtime_class->module_rel_file_id = class_module_rel_file_string->id;

    if (class->module_dir) {
      SPVM_CONSTANT_STRING* class_module_dir_string = SPVM_HASH_get(compiler->constant_string_symtable, class->module_dir, strlen(class->module_dir));
      runtime_class->module_dir_id = class_module_dir_string->id;
    }
    else {
      runtime_class->module_dir_id = -1;
    }
    runtime_class->flag = class->flag;
    runtime_class->object_fields_length = class->object_fields_length;
    runtime_class->object_fields_offset = class->object_fields_offset;
    runtime_class->has_init_block = class->has_init_block;
    runtime_class->is_anon = class->is_anon;

    SPVM_CONSTANT_STRING* class_string = SPVM_HASH_get(compiler->constant_string_symtable, class->name, strlen(class->name));
    runtime_class->name_id = class_string->id;
    
    if (class->method_destructor) {
      runtime_class->method_destructor_id = class->method_destructor->id;
    }
    else {
      runtime_class->method_destructor_id = -1;
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

    runtime_class->interface_classes_length = class->interface_classes->length;
    if (class->interface_classes->length > 0) {
      SPVM_CLASS* interface_class = SPVM_LIST_get(class->interface_classes, 0);
      runtime_class->interface_classes_base_id = interface_class->id;
    }
    else {
      runtime_class->interface_classes_base_id = -1;
    }

    runtime_class->anon_methods_length = class->anon_methods->length;
    if (class->anon_methods->length > 0) {
      SPVM_METHOD* anon_method = SPVM_LIST_get(class->anon_methods, 0);
      runtime_class->anon_methods_base_id = anon_method->anon_method_id;
    }
    else {
      runtime_class->anon_methods_base_id = -1;
    }

    SPVM_RUNTIME_CONSTANT_STRING* class_name_string = (SPVM_RUNTIME_CONSTANT_STRING*)&runtime->constant_strings[runtime_class->name_id];
    const char* runtime_class_name = (const char*)&runtime->constant_strings_buffer[class_name_string->string_buffer_id];
  }

  // Runtime basic types
  runtime->basic_types_length = compiler->basic_types->length;
  runtime->basic_types = SPVM_ALLOCATOR_alloc_memory_block_permanent(allocator, sizeof(SPVM_RUNTIME_BASIC_TYPE) * (compiler->basic_types->length + 1));
  for (int32_t basic_type_id = 0; basic_type_id < compiler->basic_types->length; basic_type_id++) {
    SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, basic_type_id);
    SPVM_RUNTIME_BASIC_TYPE* runtime_basic_type = &runtime->basic_types[basic_type_id];
    
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
  }

  // Runtime types
  runtime->types_length = compiler->types->length;
  runtime->types = SPVM_ALLOCATOR_alloc_memory_block_permanent(allocator, sizeof(SPVM_RUNTIME_TYPE) * (compiler->types->length + 1));
  for (int32_t type_id = 0; type_id < compiler->types->length; type_id++) {
    SPVM_TYPE* type = SPVM_LIST_get(compiler->types, type_id);
    SPVM_RUNTIME_TYPE* runtime_type = &runtime->types[type_id];
    
    runtime_type->basic_type_id = type->basic_type->id;
    runtime_type->dimension = type->dimension;
    runtime_type->flag = type->flag;
    runtime_type->width = type->width;
    runtime_type->mulnum_field_basic_type_id = SPVM_TYPE_get_mulnum_field_basic_type_id(compiler, type->basic_type->id, type->dimension, type->flag);
  }

  // Runtime class variables
  runtime->class_vars_length = compiler->class_vars->length;
  runtime->class_vars = SPVM_ALLOCATOR_alloc_memory_block_permanent(allocator, sizeof(SPVM_RUNTIME_CLASS_VAR) * (compiler->class_vars->length + 1));
  for (int32_t class_var_id = 0; class_var_id < compiler->class_vars->length; class_var_id++) {
    SPVM_CLASS_VAR* class_var = SPVM_LIST_get(compiler->class_vars, class_var_id);
    SPVM_RUNTIME_CLASS_VAR* runtime_class_var = &runtime->class_vars[class_var_id];

    runtime_class_var->id = class_var->id;
    runtime_class_var->type_id = class_var->type->id;
    runtime_class_var->class_id = class_var->class->id;

    SPVM_CONSTANT_STRING* class_var_name_string = SPVM_HASH_get(compiler->constant_string_symtable, class_var->name, strlen(class_var->name));
    runtime_class_var->name_id = class_var_name_string->id;

    SPVM_CONSTANT_STRING* class_var_signature_string = SPVM_HASH_get(compiler->constant_string_symtable, class_var->signature, strlen(class_var->signature));
    runtime_class_var->signature_id = class_var_signature_string->id;
  }

  // Runtime methods
  runtime->methods_length = compiler->methods->length;
  runtime->methods = SPVM_ALLOCATOR_alloc_memory_block_permanent(allocator, sizeof(SPVM_RUNTIME_METHOD) * (compiler->methods->length + 1));
  for (int32_t method_id = 0; method_id < compiler->methods->length; method_id++) {
    SPVM_METHOD* method = SPVM_LIST_get(compiler->methods, method_id);
    SPVM_RUNTIME_METHOD* runtime_method = &runtime->methods[method_id];

    runtime_method->opcodes_base_id = method->opcodes_base_id;
    runtime_method->opcodes_length = method->opcodes_length;
    runtime_method->id = method->id;
    runtime_method->class_id = method->class->id;
    runtime_method->flag = method->flag;
    runtime_method->is_class_method = method->is_class_method;
    runtime_method->is_init = method->is_init;
    runtime_method->is_anon = method->flag & SPVM_METHOD_C_FLAG_ANON;
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

    SPVM_CONSTANT_STRING* method_name_string = SPVM_HASH_get(compiler->constant_string_symtable, method->name, strlen(method->name));
    runtime_method->name_id = method_name_string->id;

    SPVM_CONSTANT_STRING* method_signature_string = SPVM_HASH_get(compiler->constant_string_symtable, method->signature, strlen(method->signature));
    runtime_method->signature_id = method_signature_string->id;

    runtime_method->args_length = method->args_length;
    if (method->args_length > 0) {
      SPVM_VAR_DECL* arg = SPVM_LIST_get(method->var_decls, 0);
      runtime_method->args_base_id = arg->arg_id;
    }
    else {
      runtime_method->args_base_id = -1;
    }
  }
  
  // Method native addresses
  runtime->method_native_addresses = SPVM_ALLOCATOR_alloc_memory_block_permanent(allocator, sizeof(void*) * runtime->methods_length);
  
  // Method precompile addresses
  runtime->method_precompile_addresses = SPVM_ALLOCATOR_alloc_memory_block_permanent(allocator, sizeof(void*) * runtime->methods_length);

  // Runtime method argument type ids
  runtime->arg_types_length = compiler->args->length;
  runtime->arg_type_ids = SPVM_ALLOCATOR_alloc_memory_block_permanent(allocator, sizeof(int32_t) * (compiler->args->length + 1));
  for (int32_t arg_id = 0; arg_id < compiler->args->length; arg_id++) {
    SPVM_VAR_DECL* arg_var_decl = SPVM_LIST_get(compiler->args, arg_id);
    int32_t arg_type_id = arg_var_decl->type->id;
    runtime->arg_type_ids[arg_id] = arg_type_id;
  }

  // Runtime fields
  runtime->fields_length = compiler->fields->length;
  runtime->fields = SPVM_ALLOCATOR_alloc_memory_block_permanent(allocator, sizeof(SPVM_RUNTIME_FIELD) * (compiler->fields->length + 1));
  for (int32_t field_id = 0; field_id < compiler->fields->length; field_id++) {
    SPVM_FIELD* field = SPVM_LIST_get(compiler->fields, field_id);
    SPVM_RUNTIME_FIELD* runtime_field = &runtime->fields[field_id];

    runtime_field->id = field->id;
    runtime_field->index = field->index;
    runtime_field->offset = field->offset;
    runtime_field->type_id = field->type->id;
    runtime_field->class_id = field->class->id;
    
    SPVM_CONSTANT_STRING* field_name_string = SPVM_HASH_get(compiler->constant_string_symtable, field->name, strlen(field->name));
    runtime_field->name_id = field_name_string->id;

    SPVM_CONSTANT_STRING* field_signature_string = SPVM_HASH_get(compiler->constant_string_symtable, field->signature, strlen(field->signature));
    runtime_field->signature_id = field_signature_string->id;
  }

#ifdef SPVM_DEBUG_RUNTIME
  fprintf(stderr, "[RUNTIME MEMORY SIZE]\n");
  fprintf(stderr, "opcodes size: %d bytes\n", (int32_t)(sizeof(SPVM_OPCODE) * runtime->opcodes_length));
  fprintf(stderr, "string_buffer size: %d bytes\n", (int32_t)(runtime->constant_strings_buffer_length));
  fprintf(stderr, "strings size: %d bytes\n", (int32_t)(sizeof(SPVM_RUNTIME_CONSTANT_STRING) * runtime->constant_strings_length));
  fprintf(stderr, "classes size: %d bytes\n", (int32_t)(sizeof(SPVM_RUNTIME_CLASS) * runtime->classes_length));
  fprintf(stderr, "basic_types size: %d bytes\n", (int32_t)(sizeof(SPVM_RUNTIME_BASIC_TYPE) * runtime->basic_types_length));
  fprintf(stderr, "types size: %d bytes\n", (int32_t)(sizeof(SPVM_RUNTIME_TYPE) * runtime->types_length));
  fprintf(stderr, "class_vars size: %d bytes\n", (int32_t)(sizeof(SPVM_RUNTIME_CLASS_VAR) * runtime->class_vars_length));
  fprintf(stderr, "methods size: %d bytes\n", (int32_t)(sizeof(SPVM_RUNTIME_METHOD) * runtime->methods_length));
  fprintf(stderr, "method_native_addresses size: %d bytes\n", (int32_t)(sizeof(void*) * runtime->methods_length));
  fprintf(stderr, "method_native_precompile size: %d bytes\n", (int32_t)(sizeof(void*) * runtime->methods_length));
  fprintf(stderr, "arg_type_ids size: %d bytes\n", (int32_t)(sizeof(int32_t) * runtime->arg_types_length));
  fprintf(stderr, "fields size: %d bytes\n", (int32_t)(sizeof(SPVM_RUNTIME_FIELD) * runtime->fields_length));
#endif

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

const char* SPVM_COMPILER_create_method_signature(SPVM_COMPILER* compiler, SPVM_METHOD* method) {
  
  int32_t length = 0;
  
  // Calcurate signature length
  {
    // Return type basic type
    length += strlen(method->return_type->basic_type->name);
    
    // Return type dimension
    length += method->return_type->dimension * 2;
    
    // (
    length += 1;
    
    int32_t arg_index;
    for (arg_index = 0; arg_index < method->args_length; arg_index++) {
      // self
      if (!method->is_class_method && arg_index == 0) {
        length += 4;
      }
      else {
        SPVM_VAR_DECL* arg_var_decl_method = SPVM_LIST_get(method->var_decls, arg_index);
        SPVM_TYPE* type_arg_method = arg_var_decl_method->type;
        
        // Ref
        if (SPVM_TYPE_is_ref_type(compiler, type_arg_method->basic_type->id, type_arg_method->dimension, type_arg_method->flag)) {
          length += 1;
        }
        
        // TYPE
        length += strlen(type_arg_method->basic_type->name);
        
        // Dimension
        length += type_arg_method->dimension * 2;
      }
      // ,
      if (arg_index != method->args_length - 1) {
        length += 1;
      }
    }
    
    // )
    length += 1;
  }
  
  char* method_signature_tmp = SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->allocator, length + 1);
  
  // Calcurate method signature length
  char* bufptr = method_signature_tmp;
  {
    // Return type
    memcpy(bufptr, method->return_type->basic_type->name, strlen(method->return_type->basic_type->name));
    bufptr += strlen(method->return_type->basic_type->name);
    
    int32_t dim_index;
    for (dim_index = 0; dim_index < method->return_type->dimension; dim_index++) {
      memcpy(bufptr, "[]", 2);
      bufptr += 2;
    }
    
    // (
    *bufptr = '(';
    bufptr += 1;
    
    int32_t arg_index;
    for (arg_index = 0; arg_index < method->args_length; arg_index++) {
      // self
      if (!method->is_class_method && arg_index == 0) {
        memcpy(bufptr, "self", 4);
        bufptr += 4;
      }
      else {
        SPVM_VAR_DECL* arg_var_decl_method = SPVM_LIST_get(method->var_decls, arg_index);
        SPVM_TYPE* type_arg_method = arg_var_decl_method->type;
        
        // Ref
        if (SPVM_TYPE_is_ref_type(compiler, type_arg_method->basic_type->id, type_arg_method->dimension, type_arg_method->flag)) {
          *bufptr = '&';
          bufptr += 1;
        }
        
        // TYPE
        memcpy(bufptr, type_arg_method->basic_type->name, strlen(type_arg_method->basic_type->name));
        bufptr += strlen(type_arg_method->basic_type->name);

        int32_t dim_index;
        for (dim_index = 0; dim_index < type_arg_method->dimension; dim_index++) {
          memcpy(bufptr, "[]", 2);
          bufptr += 2;
        }
      }

      // ,
      if (arg_index != method->args_length - 1) {
        memcpy(bufptr, ",", 1);
        bufptr += 1;
      }
    }
    
    // )
    memcpy(bufptr, ")", 1);
    bufptr += 1;
  }
  
  SPVM_CONSTANT_STRING* method_signature_string = SPVM_CONSTANT_STRING_new(compiler, method_signature_tmp, strlen(method_signature_tmp));
  const char* method_signature = method_signature_string->value;
  
  return method_signature;
}

const char* SPVM_COMPILER_create_field_signature(SPVM_COMPILER* compiler, SPVM_FIELD* field) {
  
  int32_t length = 0;
  
  // Calcurate signature length
  {
    // Basic type
    length += strlen(field->type->basic_type->name);
    
    // Type dimension
    length += field->type->dimension * 2;
  }
  
  char* field_signature_tmp = SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->allocator, length + 1);
  
  // Calcurate field signature length
  char* bufptr = field_signature_tmp;
  {
    // Basic type
    memcpy(bufptr, field->type->basic_type->name, strlen(field->type->basic_type->name));
    bufptr += strlen(field->type->basic_type->name);
    
    // Type dimension
    int32_t dim_index;
    for (dim_index = 0; dim_index < field->type->dimension; dim_index++) {
      memcpy(bufptr, "[]", 2);
      bufptr += 2;
    }
  }

  SPVM_CONSTANT_STRING* field_signature_string = SPVM_CONSTANT_STRING_new(compiler, field_signature_tmp, strlen(field_signature_tmp));
  const char* field_signature = field_signature_string->value;

  return field_signature;
}

const char* SPVM_COMPILER_create_class_var_signature(SPVM_COMPILER* compiler, SPVM_CLASS_VAR* class_var) {
  
  int32_t length = 0;
  
  // Calcurate signature length
  {
    // Basic type
    length += strlen(class_var->type->basic_type->name);
    
    // Type dimension
    length += class_var->type->dimension * 2;
  }
  
  char* class_var_signature_tmp = SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->allocator, length + 1);
  
  // Calcurate class_var signature length
  char* bufptr = class_var_signature_tmp;
  {
    // Basic type
    memcpy(bufptr, class_var->type->basic_type->name, strlen(class_var->type->basic_type->name));
    bufptr += strlen(class_var->type->basic_type->name);
    
    // Type dimension
    int32_t dim_index;
    for (dim_index = 0; dim_index < class_var->type->dimension; dim_index++) {
      memcpy(bufptr, "[]", 2);
      bufptr += 2;
    }
  }

  SPVM_CONSTANT_STRING* class_var_signature_string = SPVM_CONSTANT_STRING_new(compiler, class_var_signature_tmp, strlen(class_var_signature_tmp));
  const char* class_var_signature = class_var_signature_string->value;

  return class_var_signature;
}

void SPVM_COMPILER_free(SPVM_COMPILER* compiler) {

  // Free opcode array
  SPVM_OPCODE_ARRAY_free(compiler, compiler->opcode_array);

  // Free allocator
  SPVM_ALLOCATOR_free(compiler->allocator);
  compiler->allocator = NULL;
}
