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
#include "spvm_opcode_list.h"
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
#include "spvm_string.h"
#include "spvm_module_file.h"

#include "spvm_api.h"
#include "spvm_runtime.h"
#include "spvm_runtime_basic_type.h"
#include "spvm_runtime_class_var.h"
#include "spvm_runtime_field.h"
#include "spvm_runtime_arg.h"
#include "spvm_runtime.h"
#include "spvm_runtime_method.h"
#include "spvm_runtime_string.h"
#include "spvm_runtime_arg.h"

SPVM_COMPILER* SPVM_COMPILER_new() {
  SPVM_COMPILER* compiler = SPVM_ALLOCATOR_alloc_memory_block_unmanaged(sizeof(SPVM_COMPILER));
  
  // Allocator
  SPVM_ALLOCATOR* allocator = SPVM_ALLOCATOR_new();
  compiler->allocator = allocator;
  
  compiler->ch_ptr = "";
  
  compiler->constant_string_symtable = SPVM_HASH_new_hash_permanent(compiler->allocator, 128);
  
  // Eternal information
  compiler->include_dirs = SPVM_LIST_new_list_permanent(compiler->allocator, 0);
  compiler->basic_types = SPVM_LIST_new_list_permanent(compiler->allocator, 0);
  compiler->basic_type_symtable = SPVM_HASH_new_hash_permanent(compiler->allocator, 0);
  compiler->module_file_symtable = SPVM_HASH_new_hash_permanent(compiler->allocator, 0);
  compiler->if_require_not_found_module_name_symtable = SPVM_HASH_new_hash_permanent(compiler->allocator, 0);
  
  return compiler;
}

SPVM_COMPILER* SPVM_COMPILER_new_with_runtime(SPVM_RUNTIME* runtime) {
  SPVM_COMPILER* compiler = SPVM_COMPILER_new();
  
  for (int32_t basic_type_id = 0; basic_type_id < runtime->basic_types_length; basic_type_id++) {
    SPVM_RUNTIME_BASIC_TYPE* runtime_basic_type = &runtime->basic_types[basic_type_id];
    
    for (int32_t constant_string_index = 0; constant_string_index < runtime_basic_type->constant_strings_length; constant_string_index++) {
      SPVM_RUNTIME_STRING* runtime_constant_string = &runtime_basic_type->constant_strings[constant_string_index];
      
      const char* constant_string_value = runtime_constant_string->value;
      int32_t constant_string_length = runtime_constant_string->length;
      SPVM_STRING* constant_string = SPVM_STRING_new(compiler, constant_string_value, constant_string_length);
      
      SPVM_STRING* found_constant_string = SPVM_HASH_get(compiler->constant_string_symtable, constant_string_value, constant_string_length);
      if (!found_constant_string) {
        SPVM_HASH_set(compiler->constant_string_symtable, constant_string_value, constant_string_length, constant_string);
      }
    }
  }
  
  for (int32_t basic_type_id = 0; basic_type_id < runtime->basic_types_length; basic_type_id++) {
    SPVM_RUNTIME_BASIC_TYPE* runtime_basic_type = &runtime->basic_types[basic_type_id];
    SPVM_BASIC_TYPE* basic_type = SPVM_BASIC_TYPE_new(compiler);
    
    basic_type->name = SPVM_HASH_get(compiler->constant_string_symtable, runtime_basic_type->name, strlen(runtime_basic_type->name));
    
    SPVM_LIST_push(compiler->basic_types, basic_type);
    SPVM_HASH_set(compiler->basic_type_symtable, basic_type->name, strlen(basic_type->name), basic_type);
  }
  
  for (int32_t basic_type_id = 0; basic_type_id < runtime->basic_types_length; basic_type_id++) {
    SPVM_RUNTIME_BASIC_TYPE* runtime_basic_type = &runtime->basic_types[basic_type_id];
    SPVM_BASIC_TYPE* basic_type = SPVM_BASIC_TYPE_new(compiler);
    
    for (int32_t constant_string_index = 0; constant_string_index < runtime_basic_type->constant_strings_length; constant_string_index++) {
      SPVM_RUNTIME_STRING* runtime_constant_string = &runtime_basic_type->constant_strings[constant_string_index];
      
      const char* constant_string_value = runtime_constant_string->value;
      int32_t constant_string_length = runtime_constant_string->length;
      SPVM_STRING* constant_string = SPVM_STRING_new(compiler, constant_string_value, constant_string_length);
      
      SPVM_STRING* found_constant_string = SPVM_HASH_get(compiler->constant_string_symtable, constant_string_value, constant_string_length);
      if (!found_constant_string) {
        SPVM_HASH_set(compiler->constant_string_symtable, constant_string_value, constant_string_length, constant_string);
      }
    }
    
    basic_type->id = runtime_basic_type->id;
    basic_type->category = runtime_basic_type->category;
    
    if (runtime_basic_type->module_rel_file) {
      basic_type->module_rel_file = SPVM_HASH_get(compiler->constant_string_symtable, runtime_basic_type->module_rel_file, strlen(runtime_basic_type->module_rel_file));
    }
    
    if (runtime_basic_type->module_dir) {
      basic_type->module_dir = SPVM_HASH_get(compiler->constant_string_symtable, runtime_basic_type->module_dir, strlen(runtime_basic_type->module_dir));
    }
    
    if (runtime_basic_type->version_string) {
      basic_type->version_string = SPVM_HASH_get(compiler->constant_string_symtable, runtime_basic_type->version_string, strlen(runtime_basic_type->version_string));
    }
    
    basic_type->is_anon = runtime_basic_type->is_anon;
    
    basic_type->is_pointer = runtime_basic_type->is_pointer;
    
    if (runtime_basic_type->parent) {
      basic_type->parent = SPVM_LIST_get(compiler->basic_types, runtime_basic_type->parent->id);
    }
    
    basic_type->fields_size = runtime_basic_type->fields_size;
    
    for (int32_t class_var_index = 0; class_var_index < runtime_basic_type->class_vars_length; class_var_index++) {
      SPVM_RUNTIME_CLASS_VAR* runtime_class_var = &runtime_basic_type->class_vars[class_var_index];
      SPVM_CLASS_VAR* class_var = SPVM_CLASS_VAR_new(compiler);
      SPVM_TYPE* class_var_type = SPVM_TYPE_new_uninitialized(compiler);
      
      class_var->index = runtime_class_var->index;
      class_var->type = class_var_type;
      class_var->type->basic_type = SPVM_LIST_get(compiler->basic_types, runtime_class_var->basic_type->id);
      class_var->type->dimension = runtime_class_var->type_dimension;
      class_var->type->flag = runtime_class_var->type_flag;
      class_var->current_basic_type = SPVM_LIST_get(compiler->basic_types, runtime_class_var->current_basic_type->id);
      class_var->name = SPVM_HASH_get(compiler->constant_string_symtable, runtime_class_var->name, strlen(runtime_class_var->name));
    }
    
    /*
    
    if (basic_type->fields->length > 0) {
      SPVM_RUNTIME_FIELD* runtime_fields = SPVM_ALLOCATOR_alloc_memory_block_permanent(runtime->allocator, sizeof(SPVM_RUNTIME_FIELD) * basic_type->fields->length);
      for (int32_t field_index = 0; field_index < basic_type->fields->length; field_index++) {
        SPVM_FIELD* field = SPVM_LIST_get(basic_type->fields, field_index);
        SPVM_RUNTIME_FIELD* runtime_field = &runtime_fields[field_index];
        
        runtime_field->index = field->index;
        runtime_field->offset = field->offset;
        runtime_field->basic_type = &runtime_basic_types[field->type->basic_type->id];
        runtime_field->type_dimension = field->type->dimension;
        runtime_field->type_flag = field->type->flag;
        runtime_field->current_basic_type = &runtime_basic_types[field->current_basic_type->id];
        
        SPVM_STRING* field_name_string = SPVM_HASH_get(basic_type->constant_string_symtable, field->name, strlen(field->name));
        runtime_field->name = runtime_basic_type->constant_strings[field_name_string->index].value;
      }
      runtime_basic_type->fields = runtime_fields;
      runtime_basic_type->fields_length = basic_type->fields->length;
    }
    
    if (basic_type->methods->length > 0) {
      SPVM_RUNTIME_METHOD* runtime_methods = SPVM_ALLOCATOR_alloc_memory_block_permanent(runtime->allocator, sizeof(SPVM_RUNTIME_METHOD) * basic_type->methods->length);
      for (int32_t method_index = 0; method_index < basic_type->methods->length; method_index++) {
        
        SPVM_METHOD* method = SPVM_LIST_get(basic_type->methods, method_index);
        SPVM_RUNTIME_METHOD* runtime_method = &runtime_methods[method_index];
        
        assert(method->opcode_list->length > 0);
        
        runtime_method->opcodes = SPVM_ALLOCATOR_alloc_memory_block_permanent(runtime->allocator, sizeof(SPVM_OPCODE) * method->opcode_list->length);
        memcpy(runtime_method->opcodes, method->opcode_list->values, sizeof(SPVM_OPCODE) * method->opcode_list->length);
        runtime_method->opcodes_length = method->opcode_list->length;
        
        runtime_method->index = method->index;
        runtime_method->current_basic_type = &runtime_basic_types[method->current_basic_type->id];
        runtime_method->is_class_method = method->is_class_method;
        runtime_method->is_init = method->is_init;
        runtime_method->is_anon = method->is_anon;
        runtime_method->byte_vars_width  = method->byte_vars_width;
        runtime_method->short_vars_width  = method->short_vars_width;
        runtime_method->int_vars_width  = method->int_vars_width;
        runtime_method->long_vars_width  = method->long_vars_width;
        runtime_method->float_vars_width  = method->float_vars_width;
        runtime_method->double_vars_width  = method->double_vars_width;
        runtime_method->object_vars_width = method->object_vars_width;
        runtime_method->ref_vars_width = method->ref_vars_width;
        runtime_method->mortal_stack_length  = method->mortal_stack_length;
        runtime_method->return_basic_type = &runtime_basic_types[method->return_type->basic_type->id];
        runtime_method->return_type_dimension = method->return_type->dimension;
        runtime_method->return_type_flag = method->return_type->flag;
        runtime_method->is_native = method->is_native;
        runtime_method->is_precompile = method->is_precompile;
        runtime_method->is_destructor = method->is_destructor;
        runtime_method->is_required = method->is_required;
        runtime_method->is_enum = method->is_enum;
        
        SPVM_STRING* method_name_string = SPVM_HASH_get(basic_type->constant_string_symtable, method->name, strlen(method->name));
        runtime_method->name = runtime_basic_type->constant_strings[method_name_string->index].value;
        
        if (method->args_length > 0) {
          runtime_method->args = SPVM_ALLOCATOR_alloc_memory_block_permanent(runtime->allocator, sizeof(SPVM_RUNTIME_ARG) * method->args_length);
          runtime_method->args_length = method->args_length;
          for (int32_t arg_index = 0; arg_index < method->args_length; arg_index++) {
            SPVM_VAR_DECL* arg_var_decl = SPVM_LIST_get(method->var_decls, arg_index);
            SPVM_RUNTIME_ARG* runtime_arg = &runtime_method->args[arg_index];
            
            runtime_arg->index = arg_index;
            runtime_arg->basic_type = &runtime_basic_types[arg_var_decl->type->basic_type->id];
            runtime_arg->type_dimension = arg_var_decl->type->dimension;
            runtime_arg->type_flag = arg_var_decl->type->flag;
          }
        }
        
        runtime_method->required_args_length = method->required_args_length;
      }
      runtime_basic_type->methods = runtime_methods;
      runtime_basic_type->methods_length = basic_type->methods->length;
    }
    
    if (basic_type->init_method) {
      runtime_basic_type->init_method = &runtime_basic_type->methods[basic_type->init_method->index];
    }
    
    if (basic_type->destructor_method) {
      runtime_basic_type->destructor_method = &runtime_basic_type->methods[basic_type->destructor_method->index];
    }
    
    if (basic_type->required_method) {
      runtime_basic_type->required_method = &runtime_basic_type->methods[basic_type->required_method->index];
    }
    
    if (basic_type->anon_basic_types->length > 0) {
      SPVM_RUNTIME_BASIC_TYPE* runtime_anon_basic_types = SPVM_ALLOCATOR_alloc_memory_block_permanent(runtime->allocator, sizeof(SPVM_RUNTIME_BASIC_TYPE) * basic_type->anon_basic_types->length);      
      for (int32_t anon_basic_type_index = 0; anon_basic_type_index < basic_type->anon_basic_types->length; anon_basic_type_index++) {
        SPVM_BASIC_TYPE* anon_basic_type = SPVM_LIST_get(basic_type->anon_basic_types, anon_basic_type_index);
        runtime_anon_basic_types[anon_basic_type_index] = runtime_basic_types[anon_basic_type->id];
      }
      runtime_basic_type->anon_basic_types = runtime_anon_basic_types;
      runtime_basic_type->anon_basic_types_length = basic_type->anon_basic_types->length;
    }
    
    */
  }
  
  compiler->current_runtime = runtime;
  
  return compiler;
}

SPVM_MODULE_FILE* SPVM_COMPILER_get_module_file(SPVM_COMPILER* compiler, const char* module_name) {
  SPVM_MODULE_FILE* module_file = SPVM_HASH_get(compiler->module_file_symtable, module_name, strlen(module_name));
  
  return module_file;
}

void SPVM_COMPILER_add_module_file(SPVM_COMPILER* compiler, const char* module_name, SPVM_MODULE_FILE* module_file) {
  
  SPVM_MODULE_FILE* found_module_file = SPVM_COMPILER_get_module_file(compiler, module_name);
  
  if (!found_module_file) {
    SPVM_HASH_set(compiler->module_file_symtable, module_name, strlen(module_name), (void*)module_file);
  }
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
     SPVM_STRING* basic_type_name_string = SPVM_STRING_new(compiler, basic_type_name, strlen(basic_type_name));
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

const char* SPVM_COMPILER_get_runtime_name(SPVM_HASH* runtime_constant_string_symtable, const char* name) {
  
  SPVM_RUNTIME_STRING* string = SPVM_HASH_get(runtime_constant_string_symtable, name, strlen(name));
  
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
    
    // Add Bool module file
    {
      SPVM_MODULE_FILE* module_file = SPVM_MODULE_FILE_new(compiler);
      module_file->module_name = "Bool";
      module_file->rel_file = "Bool.spvm";
      module_file->content = "class Bool {\n  INIT {\n    $TRUE = new Bool;\n    $TRUE->{value} = 1;\n    $FALSE = new Bool;\n    $FALSE->{value} = 0;\n  }\n  \n  our $TRUE : ro Bool;\n  our $FALSE : ro Bool;\n  has value : ro int;\n}";
      module_file->content_length = strlen(module_file->content);
      SPVM_COMPILER_add_module_file(compiler, module_file->module_name, module_file);
    }
    
    // Add Error module file
    {
      SPVM_MODULE_FILE* module_file = SPVM_MODULE_FILE_new(compiler);
      module_file->module_name = "Error";
      module_file->rel_file = "Error.spvm";
      module_file->content = "class Error;";
      module_file->content_length = strlen(module_file->content);
      SPVM_COMPILER_add_module_file(compiler, module_file->module_name, module_file);
    }
    
    // Add Error::System module file
    {
      SPVM_MODULE_FILE* module_file = SPVM_MODULE_FILE_new(compiler);
      module_file->module_name = "Error::System";
      module_file->rel_file = "Error/System.spvm";
      module_file->content = "class Error::System extends Error;";
      module_file->content_length = strlen(module_file->content);
      SPVM_COMPILER_add_module_file(compiler, module_file->module_name, module_file);
    }
    
    // Add Error::NotSupported module file
    {
      SPVM_MODULE_FILE* module_file = SPVM_MODULE_FILE_new(compiler);
      module_file->module_name = "Error::NotSupported";
      module_file->rel_file = "Error/NotSupported.spvm";
      module_file->content = "class Error::NotSupported extends Error;";
      module_file->content_length = strlen(module_file->content);
      SPVM_COMPILER_add_module_file(compiler, module_file->module_name, module_file);
    }
    
    // Add Byte module file
    {
      SPVM_MODULE_FILE* module_file = SPVM_MODULE_FILE_new(compiler);
      module_file->module_name = "Byte";
      module_file->rel_file = "Byte.spvm";
      module_file->content = "class Byte {\n  has value : ro byte;\n  static method new : Byte ($value : int) {\n    my $self = new Byte;\n    $self->{value} = (byte)$value;\n    return $self;\n  }\n}";
      module_file->content_length = strlen(module_file->content);
      SPVM_COMPILER_add_module_file(compiler, module_file->module_name, module_file);
    }
    
    // Add Short module file
    {
      SPVM_MODULE_FILE* module_file = SPVM_MODULE_FILE_new(compiler);
      module_file->module_name = "Short";
      module_file->rel_file = "Short.spvm";
      module_file->content = "class Short {\n  has value : ro short;\n  static method new : Short ($value : int) {\n    my $self = new Short;\n    $self->{value} = (short)$value;\n    return $self;\n  }\n}";
      module_file->content_length = strlen(module_file->content);
      SPVM_COMPILER_add_module_file(compiler, module_file->module_name, module_file);
    }
    
    // Add Int module file
    {
      SPVM_MODULE_FILE* module_file = SPVM_MODULE_FILE_new(compiler);
      module_file->module_name = "Int";
      module_file->rel_file = "Int.spvm";
      module_file->content = "class Int {\n  has value : ro int;\n  static method new : Int ($value : int) {\n    my $self = new Int;\n    $self->{value} = $value;\n    return $self;\n  }\n}";
      module_file->content_length = strlen(module_file->content);
      SPVM_COMPILER_add_module_file(compiler, module_file->module_name, module_file);
    }
    
    // Add Long module file
    {
      SPVM_MODULE_FILE* module_file = SPVM_MODULE_FILE_new(compiler);
      module_file->module_name = "Long";
      module_file->rel_file = "Long.spvm";
      module_file->content = "class Long {\n  has value : ro long;\n  static method new : Long ($value : long) {\n    my $self = new Long;\n    $self->{value} = $value;\n    return $self;\n  }\n}";
      module_file->content_length = strlen(module_file->content);
      SPVM_COMPILER_add_module_file(compiler, module_file->module_name, module_file);
    }
    
    // Add Float module file
    {
      SPVM_MODULE_FILE* module_file = SPVM_MODULE_FILE_new(compiler);
      module_file->module_name = "Float";
      module_file->rel_file = "Float.spvm";
      module_file->content = "class Float {\n  has value : ro float;\n  static method new : Float ($value : float) {\n    my $self = new Float;\n    $self->{value} = $value;\n    return $self;\n  }\n}";
      module_file->content_length = strlen(module_file->content);
      SPVM_COMPILER_add_module_file(compiler, module_file->module_name, module_file);
    }
    
    // Add Double module file
    {
      SPVM_MODULE_FILE* module_file = SPVM_MODULE_FILE_new(compiler);
      module_file->module_name = "Double";
      module_file->rel_file = "Double.spvm";
      module_file->content = "class Double {\n  has value : ro double;\n  static method new : Double ($value : double) {\n    my $self = new Double;\n    $self->{value} = $value;\n    return $self;\n  }\n}";
      module_file->content_length = strlen(module_file->content);
      SPVM_COMPILER_add_module_file(compiler, module_file->module_name, module_file);
    }
    
    // Add CommandInfo module file
    {
      SPVM_MODULE_FILE* module_file = SPVM_MODULE_FILE_new(compiler);
      module_file->module_name = "CommandInfo";
      module_file->rel_file = "CommandInfo.spvm";
      module_file->content = "class CommandInfo {\n  our $PROGRAM_NAME : ro string;\n  our $ARGV : ro string[];\n  our $BASE_TIME : ro long;\n  }";
      module_file->content_length = strlen(module_file->content);
      SPVM_COMPILER_add_module_file(compiler, module_file->module_name, module_file);
    }
    
    // Add Address module file
    {
      SPVM_MODULE_FILE* module_file = SPVM_MODULE_FILE_new(compiler);
      module_file->module_name = "Address";
      module_file->rel_file = "Address.spvm";
      module_file->content = "class Address : pointer {\n  static method new : Address () {\n    my $self = new Address;\n    return $self;\n  }\n}";
      module_file->content_length = strlen(module_file->content);
      SPVM_COMPILER_add_module_file(compiler, module_file->module_name, module_file);
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
    SPVM_STRING* basic_type_name_string = SPVM_STRING_new(compiler, basic_type_name, strlen(basic_type_name));
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
        int32_t build_opcode_list_start_memory_blocks_count_tmp = compiler->allocator->memory_blocks_count_tmp;
        SPVM_OPCODE_BUILDER_build_opcode_list(compiler);
        assert(compiler->allocator->memory_blocks_count_tmp == build_opcode_list_start_memory_blocks_count_tmp);
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

SPVM_RUNTIME* SPVM_COMPILER_build_runtime(SPVM_COMPILER* compiler) {
  
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_new();
  
  SPVM_COMPILER_compile(compiler, NULL);
  
  SPVM_RUNTIME_BASIC_TYPE* runtime_basic_types = SPVM_ALLOCATOR_alloc_memory_block_permanent(runtime->allocator, sizeof(SPVM_RUNTIME_BASIC_TYPE) * compiler->basic_types->length);
  int32_t runtime_basic_types_length = compiler->basic_types->length;
  
  for (int32_t basic_type_id = 0; basic_type_id < compiler->basic_types->length; basic_type_id++) {
    SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, basic_type_id);
    SPVM_RUNTIME_BASIC_TYPE* runtime_basic_type = &runtime_basic_types[basic_type_id];
    
    const char* runtime_string_pool = SPVM_ALLOCATOR_alloc_memory_block_permanent(runtime->allocator, basic_type->string_pool->length);
    memcpy((char*)runtime_string_pool, basic_type->string_pool->string, basic_type->string_pool->length);
    runtime_basic_type->string_pool = runtime_string_pool;
    runtime_basic_type->string_pool_length = basic_type->string_pool->length;
    
    SPVM_RUNTIME_STRING* runtime_constant_strings = SPVM_ALLOCATOR_alloc_memory_block_permanent(runtime->allocator, sizeof(SPVM_RUNTIME_STRING) * basic_type->constant_strings->length);
    for (int32_t constant_string_index = 0; constant_string_index < basic_type->constant_strings->length; constant_string_index++) {
      SPVM_STRING* constant_string = SPVM_LIST_get(basic_type->constant_strings, constant_string_index);
      SPVM_RUNTIME_STRING* runtime_constant_string = &runtime_constant_strings[constant_string_index];
      runtime_constant_string->value = &runtime_basic_type->string_pool[constant_string->string_pool_index];
      runtime_constant_string->length = constant_string->length;
    }
    runtime_basic_type->constant_strings = runtime_constant_strings;
    runtime_basic_type->constant_strings_length = basic_type->constant_strings->length;
    
    if (basic_type->class_vars->length > 0) {
      SPVM_RUNTIME_CLASS_VAR* runtime_class_vars = SPVM_ALLOCATOR_alloc_memory_block_permanent(runtime->allocator, sizeof(SPVM_RUNTIME_CLASS_VAR) * basic_type->class_vars->length);
      for (int32_t class_var_index = 0; class_var_index < basic_type->class_vars->length; class_var_index++) {
        SPVM_CLASS_VAR* class_var = SPVM_LIST_get(basic_type->class_vars, class_var_index);
        SPVM_RUNTIME_CLASS_VAR* runtime_class_var = &runtime_class_vars[class_var_index];
        
        runtime_class_var->index = class_var->index;
        runtime_class_var->basic_type = &runtime_basic_types[class_var->type->basic_type->id];
        runtime_class_var->type_dimension = class_var->type->dimension;
        runtime_class_var->type_flag = class_var->type->flag;
        runtime_class_var->current_basic_type = &runtime_basic_types[class_var->current_basic_type->id];
        
        SPVM_STRING* class_var_name_string = SPVM_HASH_get(basic_type->constant_string_symtable, class_var->name, strlen(class_var->name));
        runtime_class_var->name = runtime_basic_type->constant_strings[class_var_name_string->index].value;
      }
      runtime_basic_type->class_vars = runtime_class_vars;
      runtime_basic_type->class_vars_length = basic_type->class_vars->length;
    }
    
    if (basic_type->fields->length > 0) {
      SPVM_RUNTIME_FIELD* runtime_fields = SPVM_ALLOCATOR_alloc_memory_block_permanent(runtime->allocator, sizeof(SPVM_RUNTIME_FIELD) * basic_type->fields->length);
      for (int32_t field_index = 0; field_index < basic_type->fields->length; field_index++) {
        SPVM_FIELD* field = SPVM_LIST_get(basic_type->fields, field_index);
        SPVM_RUNTIME_FIELD* runtime_field = &runtime_fields[field_index];
        
        runtime_field->index = field->index;
        runtime_field->offset = field->offset;
        runtime_field->basic_type = &runtime_basic_types[field->type->basic_type->id];
        runtime_field->type_dimension = field->type->dimension;
        runtime_field->type_flag = field->type->flag;
        runtime_field->current_basic_type = &runtime_basic_types[field->current_basic_type->id];
        
        SPVM_STRING* field_name_string = SPVM_HASH_get(basic_type->constant_string_symtable, field->name, strlen(field->name));
        runtime_field->name = runtime_basic_type->constant_strings[field_name_string->index].value;
      }
      runtime_basic_type->fields = runtime_fields;
      runtime_basic_type->fields_length = basic_type->fields->length;
    }
    
    if (basic_type->methods->length > 0) {
      SPVM_RUNTIME_METHOD* runtime_methods = SPVM_ALLOCATOR_alloc_memory_block_permanent(runtime->allocator, sizeof(SPVM_RUNTIME_METHOD) * basic_type->methods->length);
      for (int32_t method_index = 0; method_index < basic_type->methods->length; method_index++) {
        
        SPVM_METHOD* method = SPVM_LIST_get(basic_type->methods, method_index);
        SPVM_RUNTIME_METHOD* runtime_method = &runtime_methods[method_index];
        
        assert(method->opcode_list->length > 0);
        
        runtime_method->opcodes = SPVM_ALLOCATOR_alloc_memory_block_permanent(runtime->allocator, sizeof(SPVM_OPCODE) * method->opcode_list->length);
        memcpy(runtime_method->opcodes, method->opcode_list->values, sizeof(SPVM_OPCODE) * method->opcode_list->length);
        runtime_method->opcodes_length = method->opcode_list->length;
        
        runtime_method->index = method->index;
        runtime_method->current_basic_type = &runtime_basic_types[method->current_basic_type->id];
        runtime_method->is_class_method = method->is_class_method;
        runtime_method->is_init = method->is_init;
        runtime_method->is_anon = method->is_anon;
        runtime_method->byte_vars_width  = method->byte_vars_width;
        runtime_method->short_vars_width  = method->short_vars_width;
        runtime_method->int_vars_width  = method->int_vars_width;
        runtime_method->long_vars_width  = method->long_vars_width;
        runtime_method->float_vars_width  = method->float_vars_width;
        runtime_method->double_vars_width  = method->double_vars_width;
        runtime_method->object_vars_width = method->object_vars_width;
        runtime_method->ref_vars_width = method->ref_vars_width;
        runtime_method->mortal_stack_length  = method->mortal_stack_length;
        runtime_method->return_basic_type = &runtime_basic_types[method->return_type->basic_type->id];
        runtime_method->return_type_dimension = method->return_type->dimension;
        runtime_method->return_type_flag = method->return_type->flag;
        runtime_method->is_native = method->is_native;
        runtime_method->is_precompile = method->is_precompile;
        runtime_method->is_destructor = method->is_destructor;
        runtime_method->is_required = method->is_required;
        runtime_method->is_enum = method->is_enum;
        
        SPVM_STRING* method_name_string = SPVM_HASH_get(basic_type->constant_string_symtable, method->name, strlen(method->name));
        runtime_method->name = runtime_basic_type->constant_strings[method_name_string->index].value;
        
        if (method->args_length > 0) {
          runtime_method->args = SPVM_ALLOCATOR_alloc_memory_block_permanent(runtime->allocator, sizeof(SPVM_RUNTIME_ARG) * method->args_length);
          runtime_method->args_length = method->args_length;
          for (int32_t arg_index = 0; arg_index < method->args_length; arg_index++) {
            SPVM_VAR_DECL* arg_var_decl = SPVM_LIST_get(method->var_decls, arg_index);
            SPVM_RUNTIME_ARG* runtime_arg = &runtime_method->args[arg_index];
            
            runtime_arg->index = arg_index;
            runtime_arg->basic_type = &runtime_basic_types[arg_var_decl->type->basic_type->id];
            runtime_arg->type_dimension = arg_var_decl->type->dimension;
            runtime_arg->type_flag = arg_var_decl->type->flag;
          }
        }
        
        runtime_method->required_args_length = method->required_args_length;
      }
      runtime_basic_type->methods = runtime_methods;
      runtime_basic_type->methods_length = basic_type->methods->length;
    }
    
    if (basic_type->anon_basic_types->length > 0) {
      SPVM_RUNTIME_BASIC_TYPE* runtime_anon_basic_types = SPVM_ALLOCATOR_alloc_memory_block_permanent(runtime->allocator, sizeof(SPVM_RUNTIME_BASIC_TYPE) * basic_type->anon_basic_types->length);      
      for (int32_t anon_basic_type_index = 0; anon_basic_type_index < basic_type->anon_basic_types->length; anon_basic_type_index++) {
        SPVM_BASIC_TYPE* anon_basic_type = SPVM_LIST_get(basic_type->anon_basic_types, anon_basic_type_index);
        runtime_anon_basic_types[anon_basic_type_index] = runtime_basic_types[anon_basic_type->id];
      }
      runtime_basic_type->anon_basic_types = runtime_anon_basic_types;
      runtime_basic_type->anon_basic_types_length = basic_type->anon_basic_types->length;
    }
    
    runtime_basic_type->id = basic_type->id;
    runtime_basic_type->category = basic_type->category;
    
    SPVM_STRING* basic_type_string = SPVM_HASH_get(basic_type->constant_string_symtable, basic_type->name, strlen(basic_type->name));
    assert(basic_type_string->index >= 0);
    runtime_basic_type->name = runtime_basic_type->constant_strings[basic_type_string->index].value;
    
    if (basic_type->module_rel_file) {
      SPVM_STRING* basic_type_rel_file_string = SPVM_HASH_get(basic_type->constant_string_symtable, basic_type->module_rel_file, strlen(basic_type->module_rel_file));
      runtime_basic_type->module_rel_file = runtime_basic_type->constant_strings[basic_type_rel_file_string->index].value;
    }
    
    if (basic_type->module_dir) {
      SPVM_STRING* basic_type_dir_string = SPVM_HASH_get(basic_type->constant_string_symtable, basic_type->module_dir, strlen(basic_type->module_dir));
      runtime_basic_type->module_dir = runtime_basic_type->constant_strings[basic_type_dir_string->index].value;
    }
    
    if (basic_type->version_string) {
      SPVM_STRING* basic_type_version_string = SPVM_HASH_get(basic_type->constant_string_symtable, basic_type->version_string, strlen(basic_type->version_string));
      runtime_basic_type->version_string = runtime_basic_type->constant_strings[basic_type_version_string->index].value;
    }
    
    runtime_basic_type->is_anon = basic_type->is_anon;
    
    runtime_basic_type->is_pointer = basic_type->is_pointer;
    
    if (basic_type->parent) {
      SPVM_BASIC_TYPE* parent_basic_type = SPVM_HASH_get(compiler->basic_type_symtable, basic_type->parent->name, strlen(basic_type->parent->name));
      runtime_basic_type->parent = &runtime_basic_types[parent_basic_type->id];
    }
    
    runtime_basic_type->fields_size = basic_type->fields_size;
    
    if (basic_type->init_method) {
      runtime_basic_type->init_method = &runtime_basic_type->methods[basic_type->init_method->index];
    }
    
    if (basic_type->destructor_method) {
      runtime_basic_type->destructor_method = &runtime_basic_type->methods[basic_type->destructor_method->index];
    }
    
    if (basic_type->required_method) {
      runtime_basic_type->required_method = &runtime_basic_type->methods[basic_type->required_method->index];
    }
  }
  
  // basic_types length
  runtime->basic_types_length = runtime_basic_types_length;
  
  // basic_types
  runtime->basic_types = runtime_basic_types;
  
  // Runtime basic type symtable
  runtime->basic_type_symtable = SPVM_HASH_new_hash_permanent(runtime->allocator, runtime->basic_types_length);
  for (int32_t basic_type_id = 0; basic_type_id < runtime->basic_types_length; basic_type_id++) {
    SPVM_RUNTIME_BASIC_TYPE* basic_type = &runtime->basic_types[basic_type_id];
    SPVM_HASH_set(runtime->basic_type_symtable, basic_type->name, strlen(basic_type->name), basic_type);
  }
  
  SPVM_ENV* env = SPVM_API_new_env();
  
  env->runtime = runtime;
  
  return runtime;
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
