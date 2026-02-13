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
#include "spvm_class_file.h"
#include "spvm_mutex.h"
#include "spvm_version_from.h"
#include "spvm_version.h"

#include "spvm_api.h"
#include "spvm_api_runtime.h"
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
  
  compiler->global_allocator = SPVM_ALLOCATOR_new();
  compiler->each_compile_allocators = SPVM_LIST_new_list_permanent(compiler->global_allocator, 0);
  compiler->error_message_allocator = SPVM_ALLOCATOR_new();
  compiler->class_file_allocator = SPVM_ALLOCATOR_new();
  
  compiler->ch_ptr = "";
  
  compiler->constant_strings = SPVM_LIST_new_list_permanent(compiler->global_allocator, 0);
  compiler->constant_string_symtable = SPVM_HASH_new_hash_permanent(compiler->global_allocator, 0);
  
  compiler->global_strings = SPVM_LIST_new_list_permanent(compiler->global_allocator, 0);
  compiler->global_string_symtable = SPVM_HASH_new_hash_permanent(compiler->global_allocator, 0);
  
  compiler->basic_types = SPVM_LIST_new_list_permanent(compiler->global_allocator, 0);
  compiler->basic_type_symtable = SPVM_HASH_new_hash_permanent(compiler->global_allocator, 0);
  
  compiler->class_files = SPVM_LIST_new_list_permanent(compiler->global_allocator, 0);
  compiler->class_file_class_names = SPVM_LIST_new_list_permanent(compiler->global_allocator, 0);
  
  compiler->include_dirs = SPVM_LIST_new_list_permanent(compiler->global_allocator, 0);
  
  compiler->error_messages = SPVM_LIST_new_list_permanent(compiler->global_allocator, 0);
  
  compiler->ops = SPVM_LIST_new_list_permanent(compiler->global_allocator, 0);
  compiler->op_use_stack = SPVM_LIST_new_list_permanent(compiler->global_allocator, 0);
  compiler->op_types = SPVM_LIST_new_list_permanent(compiler->global_allocator, 0);
  
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_new();
  
  compiler->runtime = runtime;
  
  runtime->compiler = compiler;
  
  int32_t compiler_mutex_compile_size = SPVM_MUTEX_size();
  void* compiler_mutex_compile = SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->global_allocator, compiler_mutex_compile_size);
  
  SPVM_MUTEX_init(compiler_mutex_compile);
  
  compiler->mutex_compile = compiler_mutex_compile;
  
  return compiler;
}

void SPVM_COMPILER_free(SPVM_COMPILER* compiler) {
  
  SPVM_COMPILER_clear_error_messages(compiler);
  
  SPVM_COMPILER_set_start_file(compiler, NULL);
  
  SPVM_COMPILER_clear_include_dirs(compiler);
  
  if (compiler->runtime) {
    SPVM_RUNTIME_free(compiler->runtime);
    compiler->runtime = NULL;
  }
  
  for (int32_t i = 0; i < compiler->each_compile_allocators->length; i++) {
    SPVM_ALLOCATOR* each_compile_allocator = SPVM_LIST_get(compiler->each_compile_allocators, i);
    SPVM_ALLOCATOR_free(each_compile_allocator);
  }
  
  SPVM_ALLOCATOR_free(compiler->error_message_allocator);
  compiler->error_message_allocator = NULL;
  
  int32_t found = 0;
  for (int32_t i = 0; i < compiler->class_file_class_names->length; i++) {
    SPVM_CLASS_FILE* class_file_class_name = SPVM_LIST_get(compiler->class_file_class_names, i);
    if (class_file_class_name) {
      SPVM_ALLOCATOR_free_memory_block_tmp(compiler->class_file_allocator, compiler->class_file_class_names->values[i]);
      compiler->class_file_class_names->values[i] = NULL;
    }
  }
  for (int32_t i = 0; i < compiler->class_files->length; i++) {
    SPVM_CLASS_FILE* class_file = SPVM_LIST_get(compiler->class_files, i);
    if (class_file) {
      SPVM_COMPILER_free_class_file(compiler, compiler->class_files->values[i]);
      compiler->class_files->values[i] = NULL;
    }
  }
  
  SPVM_ALLOCATOR_free(compiler->class_file_allocator);
  compiler->class_file_allocator = NULL;
  
  SPVM_MUTEX_destroy(compiler->mutex_compile);
  
  SPVM_ALLOCATOR_free(compiler->global_allocator);
  compiler->global_allocator = NULL;
}

int32_t SPVM_COMPILER_compile_script(SPVM_COMPILER* compiler, const char* source, const char** anon_basic_type_name_ptr) {
  return SPVM_COMPILER_compile_anon_class(compiler, source, anon_basic_type_name_ptr);
}

int32_t SPVM_COMPILER_compile_anon_class(SPVM_COMPILER* compiler, const char* source, const char** anon_basic_type_name_ptr) {
  return SPVM_COMPILER_compile_common(compiler, NULL, source, anon_basic_type_name_ptr);
}

int32_t SPVM_COMPILER_compile(SPVM_COMPILER* compiler, const char* basic_type_name) {
  int32_t is_script = 0;
  return SPVM_COMPILER_compile_common(compiler, basic_type_name, NULL, NULL);
}

int32_t SPVM_COMPILER_compile_common(SPVM_COMPILER* compiler, const char* basic_type_name, const char* source, const char** anon_basic_type_name_ptr) {
  
  SPVM_MUTEX* compiler_mutex_compile = compiler->mutex_compile;
  
  SPVM_MUTEX_lock(compiler_mutex_compile);
  
  compiler->current_each_compile_allocator = SPVM_ALLOCATOR_new();
  
  SPVM_COMPILER_clear_error_messages(compiler);
  
  int32_t compile_start_memory_blocks_count_tmp = compiler->current_each_compile_allocator->memory_blocks_count_tmp;
  
  compiler->if_require_not_found_basic_type_name_symtable = SPVM_HASH_new(compiler->current_each_compile_allocator, 0, SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP);
  
  int32_t compiler_basic_types_base_id = compiler->basic_types->length;
  
  compiler->basic_types_base_id = compiler_basic_types_base_id;
  
  int32_t compiler_constant_strings_base_id = compiler->constant_strings->length;
  
  compiler->constant_strings_base_id = compiler_constant_strings_base_id;
  
  if (compiler->basic_types->length == 0) {
    SPVM_COMPILER_add_basic_types(compiler);
    
    SPVM_COMPILER_set_default_loaded_class_files(compiler);
  }
  
  SPVM_COMPILER_use_default_loaded_classes(compiler);
  
  int32_t original_eval_anon_classes_length = compiler->eval_anon_classes_length;
  
  // Anon class
  if (source) {
    int32_t int32_max_length = 10;
    int32_t anon_method_basic_type_name_length = 4 + 2 + 4 + 2 + int32_max_length;
    
    char* anon_basic_type_name = SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->current_each_compile_allocator, anon_method_basic_type_name_length + 1);
    sprintf(anon_basic_type_name, "eval::anon_class::%d", compiler->eval_anon_classes_length);
    
    char* rel_file = SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->current_each_compile_allocator, anon_method_basic_type_name_length + 1);
    sprintf(rel_file, "eval/anon_class/%d.spvm", compiler->eval_anon_classes_length);
    
    compiler->eval_anon_classes_length++;
    
    SPVM_COMPILER_set_class_file_with_members(compiler, anon_basic_type_name, rel_file, source);
    
    basic_type_name = anon_basic_type_name;
  }
  
  if (basic_type_name) {
    SPVM_STRING_new(compiler, basic_type_name, strlen(basic_type_name));
    
    const char* start_file = SPVM_COMPILER_get_start_file(compiler);
    
    int32_t start_line = SPVM_COMPILER_get_start_line(compiler);
    
    SPVM_COMPILER_use(compiler, basic_type_name, start_file, start_line);
  }
  
#ifdef SPVM_DEBUG_YACC
  SPVM_yydebug = 1;
#else
  SPVM_yydebug = 0;
#endif

  compiler->end_of_file = 1;
  
  int32_t yyparse_error_id = SPVM_yyparse(compiler);
  
  SPVM_COMPILER_assert_check_basic_type_ids(compiler);
  
  int32_t error_id = 0;
  
  if (yyparse_error_id) {
    error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
  }
  else {
    if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
      error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
    }
    else {
      SPVM_CHECK_check(compiler);
      if (SPVM_COMPILER_get_error_messages_length(compiler) > 0) {
        error_id = SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS;
      }
      else {
        int32_t build_opcode_list_start_memory_blocks_count_tmp = compiler->current_each_compile_allocator->memory_blocks_count_tmp;
        SPVM_OPCODE_BUILDER_build_opcodes(compiler);
        assert(compiler->current_each_compile_allocator->memory_blocks_count_tmp == build_opcode_list_start_memory_blocks_count_tmp);
        assert(SPVM_COMPILER_get_error_messages_length(compiler) == 0);
      }
    }
  }
  
  SPVM_COMPILER_free_memory_tmp_each_compile(compiler);
  
  assert(compiler->current_each_compile_allocator->memory_blocks_count_tmp == compile_start_memory_blocks_count_tmp);
  
  if (error_id) {
    for (int32_t basic_type_id = compiler_basic_types_base_id; basic_type_id < compiler->basic_types->length; basic_type_id++) {
      SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, basic_type_id);
      
      SPVM_CLASS_FILE* found_class_file = SPVM_COMPILER_get_class_file(compiler, basic_type->name);
      if (found_class_file) {
        SPVM_COMPILER_delete_class_file(compiler, basic_type->name);
      }
      
      SPVM_HASH_set(compiler->basic_type_symtable, basic_type->name, strlen(basic_type->name), NULL);
    }
    
    compiler->eval_anon_classes_length = original_eval_anon_classes_length;
    
    compiler->basic_types->length = compiler_basic_types_base_id;
     
    for (int32_t constant_string_id = compiler_constant_strings_base_id; constant_string_id < compiler->constant_strings->length; constant_string_id++) {
      SPVM_BASIC_TYPE* constant_string = SPVM_LIST_get(compiler->constant_strings, constant_string_id);
      SPVM_HASH_set(compiler->constant_string_symtable, constant_string->name, strlen(constant_string->name), NULL);
    }
    compiler->constant_strings->length = compiler_constant_strings_base_id;
    
    SPVM_ALLOCATOR_free(compiler->current_each_compile_allocator);
    compiler->current_each_compile_allocator = NULL;
  }
  else {
    // Anon class
    if (source) {
      *anon_basic_type_name_ptr = basic_type_name;
    }
    
    SPVM_LIST_push(compiler->each_compile_allocators, compiler->current_each_compile_allocator);
    compiler->current_each_compile_allocator = NULL;
    
    SPVM_COMPILER_build_runtime(compiler);
  }
  
  SPVM_MUTEX_unlock(compiler_mutex_compile);
  
  return error_id;
}

void SPVM_COMPILER_clear_error_messages(SPVM_COMPILER* compiler) {
  
  SPVM_LIST* error_messages = compiler->error_messages;
  
  for (int32_t i = 0; i < error_messages->length; i++) {
    const char* error_message = SPVM_LIST_get(error_messages, i);
    
    SPVM_ALLOCATOR_free_memory_block_tmp(compiler->error_message_allocator, (void*)error_message);
    error_message = NULL;
  }
  
  error_messages->length = 0;
}

void SPVM_COMPILER_add_class_file(SPVM_COMPILER* compiler, const char* class_name) {
  
  SPVM_CLASS_FILE* class_file = SPVM_COMPILER_get_class_file(compiler, class_name);
  
  if (!class_file) {
    class_file = SPVM_ALLOCATOR_alloc_memory_block_tmp(compiler->class_file_allocator, sizeof(SPVM_CLASS_FILE));
    class_file->class_name = class_name;
    SPVM_COMPILER_set_class_file(compiler, class_name, class_file);
  }
}

void SPVM_COMPILER_delete_class_file(SPVM_COMPILER* compiler, const char* class_name) {
  
  int32_t found = 0;
  int32_t found_index = -1;
  for (int32_t i = 0; i < compiler->class_file_class_names->length; i++) {
    const char* class_file_class_name = SPVM_LIST_get(compiler->class_file_class_names, i);
    if (strcmp(class_name, class_file_class_name) == 0) {
      if (compiler->class_files->values[i]) {
        
        SPVM_ALLOCATOR_free_memory_block_tmp(compiler->class_file_allocator, compiler->class_file_class_names->values[i]);
        compiler->class_file_class_names->values[i] = NULL;
        
        SPVM_COMPILER_free_class_file(compiler, compiler->class_files->values[i]);
        compiler->class_files->values[i] = NULL;
      }
      found_index = i;
      found = 1;
      break;
    }
  }
  
  if (found_index >= 0) {
    if (found_index < compiler->class_file_class_names->length - 1) {
      int32_t move_length = compiler->class_file_class_names->length - 1 - found_index;
      memmove(compiler->class_file_class_names->values + found_index, compiler->class_file_class_names->values + found_index + 1, sizeof(void*) * move_length);
      memmove(compiler->class_files->values + found_index, compiler->class_files->values + found_index + 1, sizeof(void*) * move_length);
    }
    
    compiler->class_file_class_names->length--;
    compiler->class_files->length--;
  }
}

void SPVM_COMPILER_set_class_file(SPVM_COMPILER* compiler, const char* class_name, SPVM_CLASS_FILE* class_file) {
  
  int32_t found = 0;
  for (int32_t i = 0; i < compiler->class_file_class_names->length; i++) {
    const char* class_file_class_name = SPVM_LIST_get(compiler->class_file_class_names, i);
    if (strcmp(class_name, class_file_class_name) == 0) {
      if (compiler->class_files->values[i]) {
        
        SPVM_COMPILER_free_class_file(compiler, compiler->class_files->values[i]);
        compiler->class_files->values[i] = NULL;
      }
      compiler->class_files->values[i] = class_file;
      found = 1;
      break;
    }
  }
  
  if (!found) {
    const char* class_name_clone = SPVM_ALLOCATOR_alloc_memory_block_tmp(compiler->class_file_allocator, strlen(class_name) + 1);
    memcpy((void*)class_name_clone, class_name, strlen(class_name));
    SPVM_LIST_push(compiler->class_file_class_names, (void*)class_name_clone);
    SPVM_LIST_push(compiler->class_files, (void*)class_file);
  }
}

SPVM_CLASS_FILE* SPVM_COMPILER_get_class_file(SPVM_COMPILER* compiler, const char* class_name) {
  
  SPVM_CLASS_FILE* found_class_file = NULL;
  for (int32_t i = 0; i < compiler->class_file_class_names->length; i++) {
    const char* class_file_class_name = SPVM_LIST_get(compiler->class_file_class_names, i);
    
    if (strcmp(class_name, class_file_class_name) == 0) {
      found_class_file = SPVM_LIST_get(compiler->class_files, i);
      break;
    }
  }
  
  return found_class_file;
}

void SPVM_COMPILER_free_class_file(SPVM_COMPILER* compiler, SPVM_CLASS_FILE* class_file) {
  
  assert(class_file);
  
  SPVM_CLASS_FILE_set_file(compiler, class_file, NULL);
  
  SPVM_CLASS_FILE_set_dir(compiler, class_file, NULL);
  
  SPVM_CLASS_FILE_set_rel_file(compiler, class_file, NULL);
  
  SPVM_CLASS_FILE_set_content(compiler, class_file, NULL);
  
  SPVM_ALLOCATOR_free_memory_block_tmp(compiler->class_file_allocator, class_file);
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

void SPVM_COMPILER_use(SPVM_COMPILER* compiler, const char* basic_type_name, const char* file, int32_t line) {
  SPVM_OP* op_name_basic_type = SPVM_OP_new_op_name(compiler, basic_type_name, file, line);
  SPVM_OP* op_type_class = SPVM_OP_build_basic_type(compiler, op_name_basic_type);
  SPVM_OP* op_use = SPVM_OP_new_op_use(compiler, op_name_basic_type->file, op_name_basic_type->line);
  SPVM_OP* op_name_alias = NULL;
  int32_t is_require = 0;
  SPVM_OP_build_use(compiler, op_use, op_type_class, op_name_alias, is_require);
  SPVM_LIST_push(compiler->op_use_stack, op_use);
}

const char* SPVM_COMPILER_get_runtime_name(SPVM_HASH* runtime_constant_string_symtable, const char* name) {
  
  SPVM_RUNTIME_STRING* string = SPVM_HASH_get(runtime_constant_string_symtable, name, strlen(name));
  
  const char* new_name = string->value;
  
  return new_name;
}

void SPVM_COMPILER_use_default_loaded_classes(SPVM_COMPILER* compiler) {
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
  SPVM_COMPILER_use(compiler, "Error::Compile", "Error::Compile", 0);
  SPVM_COMPILER_use(compiler, "SPVM", "SPVM", 0);
  SPVM_COMPILER_use(compiler, "Error::MethodCallNotPermitted", "Error::MethodCallNotPermitted", 0);
  SPVM_COMPILER_use(compiler, "Stringable", "Stringable", 0);
  SPVM_COMPILER_use(compiler, "Countable", "Countable", 0);
  SPVM_COMPILER_use(compiler, "CallerInfo", "CallerInfo", 0);
  SPVM_COMPILER_use(compiler, "Cloneable", "Cloneable", 0);
}

void SPVM_COMPILER_set_default_loaded_class_files(SPVM_COMPILER* compiler) {
  
  // Add Byte class file
  {
    const char* class_name = "Byte";
    const char* rel_file = "Byte.spvm";
    const char* content = 
      "class Byte {\n"
      "  interface Stringable;\n"
      "  interface Cloneable;\n"
      "  version_from SPVM;\n"
      "  has value : rw byte\n"
      "    get {\n"
      "      my $value = $self->{unsigned} ? (int)$self->{value} & 0xFF : (int)$self->{value};\n"
      "      return $value;\n"
      "    }\n"
      "    set {\n"
      "      if ($self->{is_read_only}) {\n"
      "        die \"The object is read-only and its value cannot be changed.\";\n"
      "      }\n"
      "      $self->{value} = (byte)$_;\n"
      "    };\n"
      "  has is_read_only : ro byte;\n"
      "  has unsigned : rw byte;\n"
      "  static method new : Byte ($value : int) {\n"
      "    my $self = new Byte;\n"
      "    $self->{value} = (byte)$value;\n"
      "    return $self;\n"
      "  }\n"
      "  static method new_unsigned : Byte ($value : int) {\n"
      "    my $self = new Byte;\n"
      "    $self->{value} = (byte)$value;\n"
      "    $self->{unsigned} = 1;\n"
      "    return $self;\n"
      "  }\n"
      "  method make_read_only : void () {\n"
      "    $self->{is_read_only} = 1;\n"
      "  }\n"
      "  method clone : Byte () {\n"
      "    my $clone = Byte->new($self->{value});\n"
      "    $clone->{unsigned} = $self->{unsigned};\n"
      "    return $clone;\n"
      "  }\n"
      "  method to_string : string () {\n"
      "    return (string)$self;\n"
      "  }\n"
      "}";
    SPVM_COMPILER_set_class_file_with_members(compiler, class_name, rel_file, content);
  }

  // Add Short class file
  {
    const char* class_name = "Short";
    const char* rel_file = "Short.spvm";
    const char* content = 
      "class Short {\n"
      "  interface Stringable;\n"
      "  interface Cloneable;\n"
      "  version_from SPVM;\n"
      "  has value : rw short\n"
      "    get {\n"
      "      my $value = $self->{unsigned} ? (int)$self->{value} & 0xFFFF : (int)$self->{value};\n"
      "      return $value;\n"
      "    }\n"
      "    set {\n"
      "      if ($self->{is_read_only}) {\n"
      "        die \"The object is read-only and its value cannot be changed.\";\n"
      "      }\n"
      "      $self->{value} = (short)$_;\n"
      "    };\n"
      "  has is_read_only : ro byte;\n"
      "  has unsigned : rw byte;\n"
      "  static method new : Short ($value : int) {\n"
      "    my $self = new Short;\n"
      "    $self->{value} = (short)$value;\n"
      "    return $self;\n"
      "  }\n"
      "  static method new_unsigned : Short ($value : int) {\n"
      "    my $self = new Short;\n"
      "    $self->{value} = (short)$value;\n"
      "    $self->{unsigned} = 1;\n"
      "    return $self;\n"
      "  }\n"
      "  method make_read_only : void () {\n"
      "    $self->{is_read_only} = 1;\n"
      "  }\n"
      "  method clone : Short () {\n"
      "    my $clone = Short->new($self->{value});\n"
      "    $clone->{unsigned} = $self->{unsigned};\n"
      "    return $clone;\n"
      "  }\n"
      "  method to_string : string () {\n"
      "    return (string)$self;\n"
      "  }\n"
      "}";
    SPVM_COMPILER_set_class_file_with_members(compiler, class_name, rel_file, content);
  }

  // Add Int class file
  {
    const char* class_name = "Int";
    const char* rel_file = "Int.spvm";
    const char* content = 
      "class Int {\n"
      "  interface Stringable;\n"
      "  interface Cloneable;\n"
      "  version_from SPVM;\n"
      "  has value : rw int\n"
      "    set {\n"
      "      if ($self->{is_read_only}) {\n"
      "        die \"The object is read-only and its value cannot be changed.\";\n"
      "      }\n"
      "      $self->{value} = $_;\n"
      "    };\n"
      "  has is_read_only : ro byte;\n"
      "  has unsigned : rw byte;\n"
      "  static method new : Int ($value : int) {\n"
      "    my $self = new Int;\n"
      "    $self->{value} = $value;\n"
      "    return $self;\n"
      "  }\n"
      "  static method new_unsigned : Int ($value : int) {\n"
      "    my $self = new Int;\n"
      "    $self->{value} = $value;\n"
      "    $self->{unsigned} = 1;\n"
      "    return $self;\n"
      "  }\n"
      "  method make_read_only : void () {\n"
      "    $self->{is_read_only} = 1;\n"
      "  }\n"
      "  method clone : Int () {\n"
      "    my $clone = Int->new($self->{value});\n"
      "    $clone->{unsigned} = $self->{unsigned};\n"
      "    return $clone;\n"
      "  }\n"
      "  method to_string : string () {\n"
      "    return (string)$self;\n"
      "  }\n"
      "}";
    SPVM_COMPILER_set_class_file_with_members(compiler, class_name, rel_file, content);
  }

  // Add Long class file
  {
    const char* class_name = "Long";
    const char* rel_file = "Long.spvm";
    const char* content = 
      "class Long {\n"
      "  interface Stringable;\n"
      "  interface Cloneable;\n"
      "  version_from SPVM;\n"
      "  has value : rw long\n"
      "    set {\n"
      "      if ($self->{is_read_only}) {\n"
      "        die \"The object is read-only and its value cannot be changed.\";\n"
      "      }\n"
      "      $self->{value} = $_;\n"
      "    };\n"
      "  has is_read_only : ro byte;\n"
      "  has unsigned : rw byte;\n"
      "  static method new : Long ($value : long) {\n"
      "    my $self = new Long;\n"
      "    $self->{value} = $value;\n"
      "    return $self;\n"
      "  }\n"
      "  static method new_unsigned : Long ($value : long) {\n"
      "    my $self = new Long;\n"
      "    $self->{value} = $value;\n"
      "    $self->{unsigned} = 1;\n"
      "    return $self;\n"
      "  }\n"
      "  method make_read_only : void () {\n"
      "    $self->{is_read_only} = 1;\n"
      "  }\n"
      "  method clone : Long () {\n"
      "    my $clone = Long->new($self->{value});\n"
      "    $clone->{unsigned} = $self->{unsigned};\n"
      "    return $clone;\n"
      "  }\n"
      "  method to_string : string () {\n"
      "    return (string)$self;\n;\n"
      "  }\n"
      "}";
    SPVM_COMPILER_set_class_file_with_members(compiler, class_name, rel_file, content);
  }

  // Add Float class file
  {
    const char* class_name = "Float";
    const char* rel_file = "Float.spvm";
    const char* content = 
      "class Float {\n"
      "  interface Stringable;\n"
      "  interface Cloneable;\n"
      "  version_from SPVM;\n"
      "  has value : rw float\n"
      "  set {\n"
      "    if ($self->{is_read_only}) {\n"
      "      die \"The object is read-only and its value cannot be changed.\";\n"
      "    }\n"
      "    $self->{value} = $_;\n"
      "  };\n"
      "  has is_read_only : ro byte;\n"
      "  has unsigned : rw byte;\n"
      "  static method new : Float ($value : float) {\n"
      "    my $self = new Float;\n"
      "    $self->{value} = $value;\n"
      "    return $self;\n"
      "  }\n"
      "  static method new_unsigned : Float ($value : float) {\n"
      "    my $self = new Float;\n"
      "    $self->{value} = $value;\n"
      "    $self->{unsigned} = 1;\n"
      "    return $self;\n"
      "  }\n"
      "  method make_read_only : void () {\n"
      "    $self->{is_read_only} = 1;\n"
      "  }\n"
      "  method clone : Float () {\n"
      "    my $clone = Float->new($self->{value});\n"
      "    $clone->{unsigned} = $self->{unsigned};\n"
      "    return $clone;\n"
      "  }\n"
      "  method to_string : string () {\n"
      "    return (string)$self->{value};\n"
      "  }\n"
      "  method update_from_object : void ($object : object) {\n"
      "    $self->{value} = (float)$object;\n"
      "  }\n"
      "}";
    SPVM_COMPILER_set_class_file_with_members(compiler, class_name, rel_file, content);
  }

  // Add Double class file
  {
    const char* class_name = "Double";
    const char* rel_file = "Double.spvm";
    const char* content = 
      "class Double {\n"
      "  interface Stringable;\n"
      "  interface Cloneable;\n"
      "  version_from SPVM;\n"
      "  has value : rw double\n"
      "  set {\n"
      "    if ($self->{is_read_only}) {\n"
      "      die \"The object is read-only and its value cannot be changed.\";\n"
      "    }\n"
      "    $self->{value} = $_;\n"
      "  };\n"
      "  has is_read_only : ro byte;\n"
      "  has unsigned : rw byte;\n"
      "  static method new : Double ($value : double) {\n"
      "    my $self = new Double;\n"
      "    $self->{value} = $value;\n"
      "    return $self;\n"
      "  }\n"
      "  static method new_unsigned : Double ($value : double) {\n"
      "    my $self = new Double;\n"
      "    $self->{value} = $value;\n"
      "    $self->{unsigned} = 1;\n"
      "    return $self;\n"
      "  }\n"
      "  method make_read_only : void () {\n"
      "    $self->{is_read_only} = 1;\n"
      "  }\n"
      "  method clone : Double () {\n"
      "    my $clone = Double->new($self->{value});\n"
      "    $clone->{unsigned} = $self->{unsigned};\n"
      "    return $clone;\n"
      "  }\n"
      "  method to_string : string () {\n"
      "    return (string)$self->{value};\n"
      "  }\n"
      "  method update_from_object : void ($object : object) {\n"
      "    $self->{value} = (double)$object;\n"
      "  }\n"
      "}";
    SPVM_COMPILER_set_class_file_with_members(compiler, class_name, rel_file, content);
  }
  
  // Add Bool class file
  {
    const char* class_name = "Bool";
    const char* rel_file = "Bool.spvm";
    const char* content = 
      "class Bool {\n"
      "  version_from SPVM;\n"
      "  INIT {\n"
      "    $TRUE = new Bool;\n"
      "    $TRUE->{value} = 1;\n"
      "    $FALSE = new Bool;\n"
      "    $FALSE->{value} = 0;\n"
      "  }\n"
      "  \n"
      "  our $TRUE : ro Bool;\n"
      "  our $FALSE : ro Bool;\n"
      "  has value : ro byte;\n"
      "}";
    SPVM_COMPILER_set_class_file_with_members(compiler, class_name, rel_file, content);
  }
  
  // Add Error class file
  {
    const char* class_name = "Error";
    const char* rel_file = "Error.spvm";
    const char* content = 
      "class Error {\n"
      "  version_from SPVM;\n"
      "}";
    SPVM_COMPILER_set_class_file_with_members(compiler, class_name, rel_file, content);
  }
  
  // Add Error::System class file
  {
    const char* class_name = "Error::System";
    const char* rel_file = "Error/System.spvm";
    const char* content = 
      "class Error::System extends Error {\n"
      "  version_from SPVM;\n"
      "}";
    SPVM_COMPILER_set_class_file_with_members(compiler, class_name, rel_file, content);
  }
  
  // Add Error::NotSupported class file
  {
    const char* class_name = "Error::NotSupported";
    const char* rel_file = "Error/NotSupported.spvm";
    const char* content = 
      "class Error::NotSupported extends Error {\n"
      "  version_from SPVM;\n"
      "}";
    SPVM_COMPILER_set_class_file_with_members(compiler, class_name, rel_file, content);
  }
  
  // Add CommandInfo class file
  {
    const char* class_name = "CommandInfo";
    const char* rel_file = "CommandInfo.spvm";
    const char* content = 
      "class CommandInfo {\n"
      "  version_from SPVM;\n"
      "  our $PROGRAM_NAME : ro string;\n"
      "  our $ARGV : ro string[];\n"
      "  our $BASETIME : ro long;\n"
      "  our $WARNING : ro byte;\n"
      "}";
    SPVM_COMPILER_set_class_file_with_members(compiler, class_name, rel_file, content);
  }
  
  // Add Address class file
  {
    const char* class_name = "Address";
    const char* rel_file = "Address.spvm";
    const char* content = 
      "class Address : pointer {\n"
      "  version_from SPVM;\n"
      "  static method new : Address () {\n"
      "    my $self = new Address;\n"
      "    return $self;\n"
      "  }\n"
      "}";
    SPVM_COMPILER_set_class_file_with_members(compiler, class_name, rel_file, content);
  }
  
  // Add Error::Compile class file
  {
    const char* class_name = "Error::Compile";
    const char* rel_file = "Error/Compile.spvm";
    const char* content = 
      "class Error::Compile extends Error {\n"
      "  version_from SPVM;\n"
      "}";
    SPVM_COMPILER_set_class_file_with_members(compiler, class_name, rel_file, content);
  }
  
  // Add SPVM class file
  {
    const char* class_name = "SPVM";
    const char* rel_file = "SPVM.spvm";
    char content[512] = {0};
    snprintf(content, 512, 
      "class SPVM {\n"
      "  version \"%s\";\n"
      "}", 
      SPVM_NATIVE_VERSION_STRING);
    SPVM_COMPILER_set_class_file_with_members(compiler, class_name, rel_file, content);
  }
  
  // Add Error::MethodCallNotPermitted class file
  {
    const char* class_name = "Error::MethodCallNotPermitted";
    const char* rel_file = "Error/MethodCallNotPermitted.spvm";
    const char* content = 
      "class Error::MethodCallNotPermitted extends Error {\n"
      "  version_from SPVM;\n"
      "}";
    SPVM_COMPILER_set_class_file_with_members(compiler, class_name, rel_file, content);
  }
  
  // Add Stringable class file
  {
    const char* class_name = "Stringable";
    const char* rel_file = "Stringable.spvm";
    const char* content = 
      "class Stringable : interface_t {\n"
      "  version_from SPVM;\n"
      "  required method to_string : string ();\n"
      "}";
    SPVM_COMPILER_set_class_file_with_members(compiler, class_name, rel_file, content);
  }
  
  // Add Countable class file
  {
    const char* class_name = "Countable";
    const char* rel_file = "Countable.spvm";
    const char* content = 
      "class Countable : interface_t {\n"
      "  version_from SPVM;\n"
      "  required method length : int ();\n"
      "}";
    SPVM_COMPILER_set_class_file_with_members(compiler, class_name, rel_file, content);
  }
  
  // Add CallerInfo class file
  {
    const char* class_name = "CallerInfo";
    const char* rel_file = "CallerInfo.spvm";
    const char* content = 
      "class CallerInfo {\n"
      "  version_from SPVM;\n"
      "  has method_abs_name : rw string;\n"
      "  has file : rw string;\n"
      "  has line : rw int;\n"
      "  static method new : CallerInfo () {\n"
      "    return new CallerInfo;\n"
      "  }\n"
      "}";
    SPVM_COMPILER_set_class_file_with_members(compiler, class_name, rel_file, content);
  }
  
  // Add Cloneable class file
  {
    const char* class_name = "Cloneable";
    const char* rel_file = "Cloneable.spvm";
    const char* content = 
      "class Cloneable : interface_t {\n"
      "  version_from SPVM;\n"
      "  required method clone : object ();\n"
      "}";
    SPVM_COMPILER_set_class_file_with_members(compiler, class_name, rel_file, content);
  }
  
}

void SPVM_COMPILER_set_class_file_with_members(SPVM_COMPILER* compiler, const char* class_name, const char* rel_file, const char* content) {
  SPVM_COMPILER_add_class_file(compiler, class_name);
  
  SPVM_CLASS_FILE* class_file = SPVM_COMPILER_get_class_file(compiler, class_name);
  SPVM_CLASS_FILE_set_rel_file(compiler, class_file, rel_file);
  SPVM_CLASS_FILE_set_content(compiler, class_file, content);
  SPVM_CLASS_FILE_set_content_length(compiler, class_file, strlen(content));
}

void SPVM_COMPILER_assert_check_basic_type_ids(SPVM_COMPILER* compiler) {
  
  SPVM_COMPILER_assert_check_basic_type_id(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_UNKNOWN);
  SPVM_COMPILER_assert_check_basic_type_id(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_UNDEF);
  SPVM_COMPILER_assert_check_basic_type_id(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_VOID);
  SPVM_COMPILER_assert_check_basic_type_id(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE);
  SPVM_COMPILER_assert_check_basic_type_id(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT);
  SPVM_COMPILER_assert_check_basic_type_id(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_INT);
  SPVM_COMPILER_assert_check_basic_type_id(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_LONG);
  SPVM_COMPILER_assert_check_basic_type_id(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT);
  SPVM_COMPILER_assert_check_basic_type_id(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE);
  SPVM_COMPILER_assert_check_basic_type_id(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_STRING);
  SPVM_COMPILER_assert_check_basic_type_id(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_ANY_OBJECT);
  SPVM_COMPILER_assert_check_basic_type_id(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE_CLASS);
  SPVM_COMPILER_assert_check_basic_type_id(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT_CLASS);
  SPVM_COMPILER_assert_check_basic_type_id(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_INT_CLASS);
  SPVM_COMPILER_assert_check_basic_type_id(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_LONG_CLASS);
  SPVM_COMPILER_assert_check_basic_type_id(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT_CLASS);
  SPVM_COMPILER_assert_check_basic_type_id(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE_CLASS);
  SPVM_COMPILER_assert_check_basic_type_id(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_BOOL_CLASS);
  SPVM_COMPILER_assert_check_basic_type_id(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_CLASS);
  SPVM_COMPILER_assert_check_basic_type_id(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_SYSTEM_CLASS);
  SPVM_COMPILER_assert_check_basic_type_id(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_NOT_SUPPORTED_CLASS);
  SPVM_COMPILER_assert_check_basic_type_id(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_COMMAND_INFO_CLASS);
  SPVM_COMPILER_assert_check_basic_type_id(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_ADDRESS_CLASS);
  SPVM_COMPILER_assert_check_basic_type_id(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_SPVM_CLASS);
  SPVM_COMPILER_assert_check_basic_type_id(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_ERROR_METHOD_CALL_NOT_PERMITTED_CLASS);
  SPVM_COMPILER_assert_check_basic_type_id(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_STRINGABLE_CLASS);
  SPVM_COMPILER_assert_check_basic_type_id(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_COUNTABLE_CLASS);
  SPVM_COMPILER_assert_check_basic_type_id(compiler, SPVM_NATIVE_C_BASIC_TYPE_ID_CALLER_INFO_CLASS);
}

void SPVM_COMPILER_assert_check_basic_type_id(SPVM_COMPILER* compiler, int32_t basic_type_id) {
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, basic_type_id);
  const char* basic_type_name_expected = SPVM_BASIC_TYPE_get_basic_type_name(compiler, basic_type_id);
  
  if (!(basic_type_name_expected && strcmp(basic_type->name, basic_type_name_expected) == 0)) {
    fprintf(stderr, "[Unexpected Error]Basic Type ID:%d, Basic Type Name:%s, Expected Basic Type Name: %s\n", basic_type_id, basic_type->name, basic_type_name_expected);
    assert(0);
  }
}

void SPVM_COMPILER_free_memory_tmp_each_compile(SPVM_COMPILER* compiler) {
  for (int32_t i = 0; i < compiler->ops->length; i++) {
    SPVM_OP* op = SPVM_LIST_get(compiler->ops, i);
    int32_t op_id = op->id;
    switch(op_id) {
      case SPVM_OP_C_ID_BLOCK: {
        SPVM_ALLOCATOR_free_memory_block_tmp(compiler->current_each_compile_allocator, op->uv.block);
        break;
      }
      case SPVM_OP_C_ID_ATTRIBUTE: {
        SPVM_ALLOCATOR_free_memory_block_tmp(compiler->current_each_compile_allocator, op->uv.attribute);
        break;
      }
      case SPVM_OP_C_ID_USE: {
        SPVM_USE* use = op->uv.use;
        use->alias_name = NULL;
        SPVM_ALLOCATOR_free_memory_block_tmp(compiler->current_each_compile_allocator, use);
        break;
      }
      case SPVM_OP_C_ID_ALLOW: {
        SPVM_ALLOW* allow = op->uv.allow;
        SPVM_ALLOCATOR_free_memory_block_tmp(compiler->current_each_compile_allocator, allow);
        break;
      }
      case SPVM_OP_C_ID_VERSION_FROM: {
        SPVM_VERSION_FROM* version_from = op->uv.version_from;
        SPVM_ALLOCATOR_free_memory_block_tmp(compiler->current_each_compile_allocator, version_from);
        break;
      }
      case SPVM_OP_C_ID_INTERFACE: {
        SPVM_INTERFACE* interface = op->uv.interface;
        SPVM_ALLOCATOR_free_memory_block_tmp(compiler->current_each_compile_allocator, interface);
        break;
      }
      case SPVM_OP_C_ID_CLASS_VAR_ACCESS: {
        SPVM_CLASS_VAR_ACCESS* class_var_access = op->uv.class_var_access;
        class_var_access->op_name = NULL;
        class_var_access->class_var = NULL;
        SPVM_ALLOCATOR_free_memory_block_tmp(compiler->current_each_compile_allocator, class_var_access);
        break;
      }
      case SPVM_OP_C_ID_CONSTANT: {
        SPVM_CONSTANT* constant = op->uv.constant;
        constant->op_constant = NULL;
        constant->type = NULL;
        SPVM_ALLOCATOR_free_memory_block_tmp(compiler->current_each_compile_allocator, constant);
        break;
      }
      case SPVM_OP_C_ID_ARRAY_FIELD_ACCESS: {
        SPVM_ARRAY_FIELD_ACCESS* array_field_access = op->uv.array_field_access;
        array_field_access->field = NULL;
        SPVM_ALLOCATOR_free_memory_block_tmp(compiler->current_each_compile_allocator, array_field_access);
        break;
      }
      case SPVM_OP_C_ID_FIELD_ACCESS: {
        SPVM_FIELD_ACCESS* field_access = op->uv.field_access;
        field_access->op_name = NULL;
        field_access->field = NULL;
        SPVM_ALLOCATOR_free_memory_block_tmp(compiler->current_each_compile_allocator, field_access);
        break;
      }
      case SPVM_OP_C_ID_CALL_METHOD: {
        SPVM_CALL_METHOD* call_method = op->uv.call_method;
        call_method->op_name = NULL;
        call_method->method = NULL;
        SPVM_ALLOCATOR_free_memory_block_tmp(compiler->current_each_compile_allocator, call_method);
        break;
      }
      case SPVM_OP_C_ID_VAR: {
        SPVM_VAR* var = op->uv.var;
        var->op_name = NULL;
        var->name = NULL;
        var->var_decl = NULL;
        var->call_method = NULL;
        SPVM_ALLOCATOR_free_memory_block_tmp(compiler->current_each_compile_allocator, var);
        break;
      }
      case SPVM_OP_C_ID_VAR_DECL: {
        SPVM_VAR_DECL* var_decl = op->uv.var_decl;
        if (!var_decl->is_arg) {
          var_decl->op_var_decl = NULL;
          var_decl->type = NULL;
          var_decl->var = NULL;
          SPVM_ALLOCATOR_free_memory_block_tmp(compiler->current_each_compile_allocator, var_decl);
        }
        break;
      }
    }
    SPVM_ALLOCATOR_free_memory_block_tmp(compiler->current_each_compile_allocator, op);
  }
  
  for (int32_t basic_type_id = compiler->basic_types_base_id; basic_type_id < compiler->basic_types->length; basic_type_id++) {
    SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, basic_type_id);
    
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
  
  compiler->op_use_stack->length = 0;
  
  compiler->op_types->length = 0;
  
  compiler->ops->length = 0;
  
  SPVM_HASH_free(compiler->if_require_not_found_basic_type_name_symtable);
}

SPVM_RUNTIME* SPVM_COMPILER_build_runtime(SPVM_COMPILER* compiler) {
  
  SPVM_RUNTIME* current_runtime = compiler->runtime;
  
  int32_t current_runtime_basic_types_length = current_runtime->basic_types_length;
  
  SPVM_RUNTIME* runtime = current_runtime;
  
  SPVM_RUNTIME_BASIC_TYPE** current_runtime_basic_types = current_runtime->basic_types;
  
  runtime->basic_types = SPVM_ALLOCATOR_alloc_memory_block_tmp(runtime->allocator, sizeof(SPVM_RUNTIME_BASIC_TYPE*) * compiler->basic_types->length);
  if (current_runtime_basic_types_length > 0) {
    memcpy(runtime->basic_types, current_runtime_basic_types, sizeof(SPVM_RUNTIME_BASIC_TYPE*) * current_runtime_basic_types_length);
    SPVM_ALLOCATOR_free_memory_block_tmp(runtime->allocator, current_runtime_basic_types);
  }
  
  runtime->basic_types_length = compiler->basic_types->length;
  
  for (int32_t basic_type_id = current_runtime_basic_types_length; basic_type_id < compiler->basic_types->length; basic_type_id++) {
    SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, basic_type_id);
    SPVM_RUNTIME_BASIC_TYPE* runtime_basic_type = SPVM_ALLOCATOR_alloc_memory_block_permanent(runtime->allocator, sizeof(SPVM_RUNTIME_BASIC_TYPE));
    
    runtime->basic_types[basic_type_id] = runtime_basic_type;
  }
  
  assert(runtime->basic_types[0]);
  
  for (int32_t basic_type_id = current_runtime_basic_types_length; basic_type_id < compiler->basic_types->length; basic_type_id++) {
    
    SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, basic_type_id);
    SPVM_RUNTIME_BASIC_TYPE* runtime_basic_type = SPVM_API_RUNTIME_get_basic_type_by_id(runtime, basic_type_id);
    
    SPVM_HASH_set(runtime->basic_type_symtable, basic_type->name, strlen(basic_type->name), runtime_basic_type);
    
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
        runtime_class_var->basic_type = SPVM_API_RUNTIME_get_basic_type_by_id(runtime, class_var->type->basic_type->id);
        runtime_class_var->type_dimension = class_var->type->dimension;
        runtime_class_var->type_flag = class_var->type->flag;
        runtime_class_var->current_basic_type = SPVM_API_RUNTIME_get_basic_type_by_id(runtime, class_var->current_basic_type->id);
        runtime_class_var->is_cache = class_var->is_cache;
        
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
        runtime_field->basic_type = SPVM_API_RUNTIME_get_basic_type_by_id(runtime, field->type->basic_type->id);
        runtime_field->type_dimension = field->type->dimension;
        runtime_field->type_flag = field->type->flag;
        runtime_field->current_basic_type = SPVM_API_RUNTIME_get_basic_type_by_id(runtime, field->current_basic_type->id);
        if (field->exists_field) {
          runtime_field->exists_offset = field->exists_field->offset;
        }
        else {
          runtime_field->exists_offset = -1;
        }
        
        runtime_field->exists_bit = field->exists_bit;
        
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
        runtime_method->current_basic_type = SPVM_API_RUNTIME_get_basic_type_by_id(runtime, method->current_basic_type->id);
        runtime_method->is_class_method = method->is_class_method;
        runtime_method->is_init_method = method->is_init_method;
        runtime_method->is_end_method = method->is_end_method;
        runtime_method->byte_vars_width = method->byte_vars_width;
        runtime_method->short_vars_width  = method->short_vars_width;
        runtime_method->int_vars_width = method->int_vars_width;
        runtime_method->long_vars_width  = method->long_vars_width;
        runtime_method->float_vars_width  = method->float_vars_width;
        runtime_method->double_vars_width  = method->double_vars_width;
        runtime_method->object_vars_width = method->object_vars_width;
        runtime_method->ref_vars_width = method->ref_vars_width;
        runtime_method->mortal_stack_length  = method->mortal_stack_length;
        runtime_method->mortal_stack_tops_length  = method->mortal_stack_tops_length;
        runtime_method->return_basic_type = SPVM_API_RUNTIME_get_basic_type_by_id(runtime, method->return_type->basic_type->id);
        runtime_method->return_type_dimension = method->return_type->dimension;
        runtime_method->return_type_flag = method->return_type->flag;
        runtime_method->is_native = method->is_native;
        runtime_method->is_precompile = method->is_precompile;
        runtime_method->is_destroy_method = method->is_destroy_method;
        runtime_method->is_required = method->is_required;
        runtime_method->is_enum = method->is_enum;
        
        SPVM_STRING* method_name_string = SPVM_HASH_get(basic_type->constant_string_symtable, method->name, strlen(method->name));
        runtime_method->name = runtime_basic_type->constant_strings[method_name_string->index].value;
        
        SPVM_STRING* method_abs_name_string = SPVM_HASH_get(basic_type->constant_string_symtable, method->abs_name, strlen(method->abs_name));
        runtime_method->abs_name = runtime_basic_type->constant_strings[method_abs_name_string->index].value;
        
        SPVM_STRING* method_args_signature_string = SPVM_HASH_get(basic_type->constant_string_symtable, method->args_signature, strlen(method->args_signature));
        runtime_method->args_signature = runtime_basic_type->constant_strings[method_args_signature_string->index].value;
        
        if (method->args_length > 0) {
          runtime_method->args = SPVM_ALLOCATOR_alloc_memory_block_permanent(runtime->allocator, sizeof(SPVM_RUNTIME_ARG) * method->args_length);
          runtime_method->args_length = method->args_length;
          for (int32_t arg_index = 0; arg_index < method->args_length; arg_index++) {
            SPVM_VAR_DECL* arg_var_decl = SPVM_LIST_get(method->var_decls, arg_index);
            SPVM_RUNTIME_ARG* runtime_arg = &runtime_method->args[arg_index];
            
            SPVM_STRING* arg_name_string = SPVM_HASH_get(basic_type->constant_string_symtable, arg_var_decl->name, strlen(arg_var_decl->name));
            
            runtime_arg->name = runtime_basic_type->constant_strings[arg_name_string->index].value;
            runtime_arg->index = arg_index;
            runtime_arg->basic_type = SPVM_API_RUNTIME_get_basic_type_by_id(runtime, arg_var_decl->type->basic_type->id);
            runtime_arg->type_dimension = arg_var_decl->type->dimension;
            runtime_arg->type_flag = arg_var_decl->type->flag;
            runtime_arg->stack_index = arg_var_decl->stack_index;
            runtime_arg->current_method = runtime_method;
            runtime_arg->default_value = arg_var_decl->arg_default_value;
            runtime_arg->is_optional = arg_var_decl->is_optional_arg;
            if (SPVM_TYPE_is_object_type(compiler, arg_var_decl->type->basic_type->id, arg_var_decl->type->dimension, arg_var_decl->type->flag)) {
              runtime_method->has_object_args = 1;
            }
          }
          
        }
        
        runtime_method->required_args_length = method->required_args_length;
        
        if (SPVM_TYPE_is_object_type(compiler, method->return_type->basic_type->id, method->return_type->dimension, method->return_type->flag)) {
          runtime_method->return_type_is_object = 1;
        }
        
        if (SPVM_TYPE_is_void_type(compiler, method->return_type->basic_type->id, method->return_type->dimension, method->return_type->flag)) {
          runtime_method->return_type_is_void = 1;
        }
        
        runtime_method->call_stack_frame_size = SPVM_API_get_call_stack_frame_size(runtime_method);
      }
      runtime_basic_type->methods = runtime_methods;
      runtime_basic_type->methods_length = basic_type->methods->length;
    }
    
    if (basic_type->anon_basic_types->length > 0) {
      SPVM_RUNTIME_BASIC_TYPE** runtime_anon_basic_types = SPVM_ALLOCATOR_alloc_memory_block_permanent(runtime->allocator, sizeof(SPVM_RUNTIME_BASIC_TYPE*) * basic_type->anon_basic_types->length);           
      for (int32_t anon_basic_type_index = 0; anon_basic_type_index < basic_type->anon_basic_types->length; anon_basic_type_index++) {
        SPVM_BASIC_TYPE* anon_basic_type = SPVM_LIST_get(basic_type->anon_basic_types, anon_basic_type_index);
        runtime_anon_basic_types[anon_basic_type_index] = SPVM_API_RUNTIME_get_basic_type_by_id(runtime, anon_basic_type->id);
      }
      runtime_basic_type->anon_basic_types = runtime_anon_basic_types;
      runtime_basic_type->anon_basic_types_length = basic_type->anon_basic_types->length;
    }
    
    runtime_basic_type->id = basic_type->id;
    runtime_basic_type->category = basic_type->category;
    
    SPVM_STRING* basic_type_string = SPVM_HASH_get(basic_type->constant_string_symtable, basic_type->name, strlen(basic_type->name));
    assert(basic_type_string->index >= 0);
    runtime_basic_type->name = runtime_basic_type->constant_strings[basic_type_string->index].value;
    
    if (basic_type->file) {
      SPVM_STRING* basic_type_file_string = SPVM_HASH_get(basic_type->constant_string_symtable, basic_type->file, strlen(basic_type->file));
      runtime_basic_type->file = runtime_basic_type->constant_strings[basic_type_file_string->index].value;
    }
    
    if (basic_type->class_dir) {
      SPVM_STRING* basic_type_dir_string = SPVM_HASH_get(basic_type->constant_string_symtable, basic_type->class_dir, strlen(basic_type->class_dir));
      runtime_basic_type->class_dir = runtime_basic_type->constant_strings[basic_type_dir_string->index].value;
    }
    
    if (basic_type->class_rel_file) {
      SPVM_STRING* basic_type_rel_file_string = SPVM_HASH_get(basic_type->constant_string_symtable, basic_type->class_rel_file, strlen(basic_type->class_rel_file));
      runtime_basic_type->class_rel_file = runtime_basic_type->constant_strings[basic_type_rel_file_string->index].value;
    }
    
    if (basic_type->version_string) {
      SPVM_STRING* basic_type_version_string = SPVM_HASH_get(basic_type->constant_string_symtable, basic_type->version_string, strlen(basic_type->version_string));
      runtime_basic_type->version_string = runtime_basic_type->constant_strings[basic_type_version_string->index].value;
    }
    
    if (basic_type->basic_type_name_in_version_from) {
      SPVM_BASIC_TYPE* basic_type_in_version_from = SPVM_HASH_get(compiler->basic_type_symtable, basic_type->basic_type_name_in_version_from, strlen(basic_type->basic_type_name_in_version_from));
      runtime_basic_type->basic_type_in_version_from = SPVM_API_RUNTIME_get_basic_type_by_id(runtime, basic_type_in_version_from->id);
    }
    
    runtime_basic_type->is_anon = basic_type->is_anon;
    
    runtime_basic_type->is_pointer = basic_type->is_pointer;
    
    runtime_basic_type->is_object_type = SPVM_BASIC_TYPE_is_object_type(compiler, basic_type->id);
    
    if (basic_type->parent) {
      SPVM_BASIC_TYPE* parent_basic_type = SPVM_HASH_get(compiler->basic_type_symtable, basic_type->parent->name, strlen(basic_type->parent->name));
      runtime_basic_type->parent = SPVM_API_RUNTIME_get_basic_type_by_id(runtime, parent_basic_type->id);
    }
    
    runtime_basic_type->fields_size = basic_type->fields_size;
    
    if (basic_type->init_method) {
      runtime_basic_type->init_method = &runtime_basic_type->methods[basic_type->init_method->index];
    }
    
    if (basic_type->end_method) {
      runtime_basic_type->end_method = &runtime_basic_type->methods[basic_type->end_method->index];
    }
    
    if (basic_type->monitor_var_type) {
      runtime_basic_type->has_monitor_var = 1;
      runtime_basic_type->monitor_var_basic_type = SPVM_API_RUNTIME_get_basic_type_by_id(runtime, basic_type->monitor_var_type->basic_type->id);
      runtime_basic_type->monitor_var_type_dimension = basic_type->monitor_var_type->dimension;
      runtime_basic_type->monitor_var_type_flag = basic_type->monitor_var_type->flag;
    }
    
    runtime_basic_type->current_runtime = runtime;
  }
  
  for (int32_t basic_type_id = current_runtime_basic_types_length; basic_type_id < compiler->basic_types->length; basic_type_id++) {
    
    SPVM_BASIC_TYPE* basic_type = SPVM_LIST_get(compiler->basic_types, basic_type_id);
    SPVM_RUNTIME_BASIC_TYPE* runtime_basic_type = SPVM_API_RUNTIME_get_basic_type_by_id(runtime, basic_type_id);
    
    if (basic_type->destroy_method) {
      SPVM_RUNTIME_BASIC_TYPE* destroy_method_runtime_basic_type = SPVM_API_RUNTIME_get_basic_type_by_id(runtime, basic_type->destroy_method->current_basic_type->id);
      
      runtime_basic_type->destroy_method = &destroy_method_runtime_basic_type->methods[basic_type->destroy_method->index];
    }
  }
  
  compiler->runtime = runtime;
  
  return runtime;
}

SPVM_RUNTIME* SPVM_COMPILER_get_runtime(SPVM_COMPILER* compiler) {
  return compiler->runtime;
}

void SPVM_COMPILER_error(SPVM_COMPILER* compiler, const char* error_message_template, ...) {
  
  int32_t error_message_length = 0;
  
  // Message template
  int32_t error_message_template_length = (int32_t)strlen(error_message_template);
  
  va_list args;
  va_start(args, error_message_template);
  
  error_message_length += error_message_template_length;
  
  // Argument count
  char* found_ptr = (char*)error_message_template;
  while (1) {
    found_ptr = strchr(found_ptr, '%');
    if (found_ptr) {
      if (*(found_ptr + 1) == 'c') {
        int arg = va_arg(args, int);
        error_message_length++;
      }
      else if (*(found_ptr + 1) == 's') {
        char* arg = va_arg(args, char*);
        error_message_length += strlen(arg);
      }
      else if (*(found_ptr + 1) == 'd' || *(found_ptr + 1) == 'X') {
        (void) va_arg(args, int);
        error_message_length += 30;
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
  
  char* error_message = SPVM_ALLOCATOR_alloc_memory_block_tmp(compiler->error_message_allocator, error_message_length + 1);
  
  va_start(args, error_message_template);
  vsprintf(error_message, error_message_template, args);
  va_end(args);
  
  SPVM_LIST_push(compiler->error_messages, error_message);
}

const char* SPVM_COMPILER_get_start_file(SPVM_COMPILER* compiler) {
  return compiler->start_file;
}

void SPVM_COMPILER_set_start_file(SPVM_COMPILER* compiler, const char* start_file) {
  if (compiler->start_file) {
    SPVM_ALLOCATOR_free_memory_block_tmp(compiler->global_allocator, (void*)compiler->start_file);
    compiler->start_file = NULL;
  }
  
  if (start_file) {
    int32_t start_file_length = strlen(start_file);
    compiler->start_file = SPVM_ALLOCATOR_alloc_memory_block_tmp(compiler->global_allocator, start_file_length + 1);
    memcpy((void*)compiler->start_file, start_file, start_file_length);
  }
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
  char* compiler_include_dir = SPVM_ALLOCATOR_alloc_memory_block_tmp(compiler->global_allocator, include_dir_length + 1);
  memcpy(compiler_include_dir, include_dir, include_dir_length);
  SPVM_LIST_push(compiler->include_dirs, (void*)compiler_include_dir);
}

void SPVM_COMPILER_prepend_include_dir(SPVM_COMPILER* compiler, const char* include_dir) {  
  int32_t include_dir_length = strlen(include_dir);
  char* compiler_include_dir = SPVM_ALLOCATOR_alloc_memory_block_tmp(compiler->global_allocator, include_dir_length + 1);
  memcpy(compiler_include_dir, include_dir, include_dir_length);
  
  SPVM_LIST_unshift(compiler->include_dirs, (void*)compiler_include_dir);
}

void SPVM_COMPILER_clear_include_dirs(SPVM_COMPILER* compiler) {
  int32_t include_dirs_length = SPVM_COMPILER_get_include_dirs_length(compiler);
  
  for (int32_t i = 0; i < include_dirs_length; i++) {
    const char* include_dir = SPVM_COMPILER_get_include_dir(compiler, i);
    SPVM_ALLOCATOR_free_memory_block_tmp(compiler->global_allocator, (void*)include_dir);
    include_dir = NULL;
  }
  
  SPVM_LIST_clear(compiler->include_dirs);
}

const char* SPVM_COMPILER_get_include_dir (SPVM_COMPILER* compiler, int32_t include_dir_id) {
  const char* include_dir = SPVM_LIST_get(compiler->include_dirs, include_dir_id);
  return include_dir;
}
