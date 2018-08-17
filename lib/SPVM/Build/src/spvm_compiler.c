#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "spvm_compiler.h"
#include "spvm_type.h"
#include "spvm_package.h"
#include "spvm_type.h"
#include "spvm_op.h"
#include "spvm_hash.h"
#include "spvm_list.h"
#include "spvm_util_allocator.h"
#include "spvm_compiler_allocator.h"
#include "spvm_yacc_util.h"
#include "spvm_list.h"
#include "spvm_opcode_array.h"
#include "spvm_sub.h"
#include "spvm_runtime.h"
#include "spvm_runtime_api.h"
#include "spvm_sub.h"
#include "spvm_field.h"
#include "spvm_native.h"
#include "spvm_opcode.h"
#include "spvm_basic_type.h"
#include "spvm_use.h"
#include "spvm_op_checker.h"
#include "spvm_opcode_builder.h"
#include "spvm_object.h"
#include "spvm_runtime_basic_type.h"
#include "spvm_runtime_field.h"

SPVM_COMPILER* SPVM_COMPILER_new() {
  SPVM_COMPILER* compiler = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(SPVM_COMPILER));
  
  // Allocator
  compiler->allocator = SPVM_COMPILER_ALLOCATOR_new(compiler);

  compiler->bufptr = "";

  compiler->name_symtable = SPVM_COMPILER_ALLOCATOR_alloc_hash(compiler, 0);

  // Parser information
  compiler->op_use_stack = SPVM_COMPILER_ALLOCATOR_alloc_list(compiler, 0);
  compiler->op_types = SPVM_COMPILER_ALLOCATOR_alloc_list(compiler, 0);
  compiler->basic_types = SPVM_COMPILER_ALLOCATOR_alloc_list(compiler, 0);
  compiler->basic_type_symtable = SPVM_COMPILER_ALLOCATOR_alloc_hash(compiler, 0);
  compiler->subs = SPVM_COMPILER_ALLOCATOR_alloc_list(compiler, 0);
  compiler->sub_symtable = SPVM_COMPILER_ALLOCATOR_alloc_hash(compiler, 0);
  compiler->fields = SPVM_COMPILER_ALLOCATOR_alloc_list(compiler, 0);
  compiler->field_symtable = SPVM_COMPILER_ALLOCATOR_alloc_hash(compiler, 0);
  compiler->packages = SPVM_COMPILER_ALLOCATOR_alloc_list(compiler, 0);
  compiler->package_symtable = SPVM_COMPILER_ALLOCATOR_alloc_hash(compiler, 0);
  compiler->package_vars = SPVM_COMPILER_ALLOCATOR_alloc_list(compiler, 0);
  compiler->package_var_symtable = SPVM_COMPILER_ALLOCATOR_alloc_hash(compiler, 0);
  compiler->op_constants = SPVM_COMPILER_ALLOCATOR_alloc_list(compiler, 0);
  compiler->module_include_pathes = SPVM_COMPILER_ALLOCATOR_alloc_list(compiler, 0);
  compiler->opcode_array = SPVM_OPCODE_ARRAY_new(compiler);

  // Add basic types
  SPVM_COMPILER_add_basic_types(compiler);

  // use SPVM::CORE module
  SPVM_OP* op_name_core = SPVM_OP_new_op_name(compiler, "SPVM::CORE", "SPVM::CORE", 0);
  SPVM_OP* op_type_core = SPVM_OP_build_basic_type(compiler, op_name_core);
  SPVM_OP* op_use_core = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_USE, op_name_core->file, op_name_core->line);
  SPVM_OP_build_use(compiler, op_use_core, op_type_core);
  SPVM_LIST_push(compiler->op_use_stack, op_use_core);

  return compiler;
}

int32_t SPVM_COMPILER_push_runtime_string(SPVM_COMPILER* compiler, SPVM_RUNTIME* runtime, const char* string) {
  
  
  int32_t id = runtime->strings_length;
  if (runtime->strings_length >= runtime->strings_capacity) {
    int32_t new_strings_capacity = runtime->strings_capacity * 2;
    char** new_strings = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(char*) * new_strings_capacity);
    memcpy(new_strings, runtime->strings, sizeof(char*) * runtime->strings_length);
    free(runtime->strings);
    runtime->strings = new_strings;
    runtime->strings_capacity = new_strings_capacity;
  }
  
  runtime->strings[runtime->strings_length] = string;
  runtime->strings_length++;
  
  return id;
}

void SPVM_COMPILER_push_portable_basic_type(SPVM_COMPILER* compiler, SPVM_RUNTIME* runtime, SPVM_BASIC_TYPE* basic_type) {
  
  if (runtime->portable_basic_types_length >= runtime->portable_basic_types_capacity) {
    int32_t new_portable_basic_types_capacity = runtime->portable_basic_types_capacity * 2;
    int32_t* new_portable_basic_types = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * runtime->portable_basic_types_unit * new_portable_basic_types_capacity);
    memcpy(new_portable_basic_types, runtime->portable_basic_types, sizeof(int32_t) * runtime->portable_basic_types_unit * runtime->portable_basic_types_length);
    free(runtime->portable_basic_types);
    runtime->portable_basic_types = new_portable_basic_types;
    runtime->portable_basic_types_capacity = new_portable_basic_types_capacity;
  }
  
  int32_t* new_portable_basic_type = (int32_t*)&runtime->portable_basic_types[runtime->portable_basic_types_unit * runtime->portable_basic_types_length];
  new_portable_basic_type[0] = SPVM_COMPILER_push_runtime_string(compiler, runtime, basic_type->name);
  new_portable_basic_type[1] = basic_type->id;
  new_portable_basic_type[2] = basic_type->category;
  if (basic_type->package) {
    new_portable_basic_type[3] = basic_type->package->id;
  }
  else {
    new_portable_basic_type[3] = -1;
  }
  runtime->portable_basic_types_length++;
}

void SPVM_COMPILER_build_runtime_basic_types(SPVM_COMPILER* compiler, SPVM_RUNTIME* runtime) {
  for (size_t i = 0; i < runtime->portable_basic_types_unit * runtime->portable_basic_types_length; i += runtime->portable_basic_types_unit) {
    int32_t* portable_basic_type = (int32_t*)&runtime->portable_basic_types[i];
    
    SPVM_RUNTIME_BASIC_TYPE* runtime_basic_type = SPVM_RUNTIME_BASIC_TYPE_new();
    runtime_basic_type->name = runtime->strings[portable_basic_type[0]];
    runtime_basic_type->id = portable_basic_type[1];
    runtime_basic_type->category = portable_basic_type[2];
    int32_t package_id = portable_basic_type[3];
    if (package_id < 0) {
      runtime_basic_type->package = NULL;
    }
    else {
      SPVM_PACKAGE* package = SPVM_LIST_fetch(compiler->packages, package_id);
      runtime_basic_type->package = package;
    }
    
    SPVM_LIST_push(runtime->runtime_basic_types, runtime_basic_type);
  }
}

void SPVM_COMPILER_push_portable_field(SPVM_COMPILER* compiler, SPVM_RUNTIME* runtime, SPVM_FIELD* field) {
  
  if (runtime->portable_fields_length >= runtime->portable_fields_capacity) {
    int32_t new_portable_fields_capacity = runtime->portable_fields_capacity * 2;
    int32_t* new_portable_fields = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * runtime->portable_fields_unit * new_portable_fields_capacity);
    memcpy(new_portable_fields, runtime->portable_fields, sizeof(int32_t) * runtime->portable_fields_unit * runtime->portable_fields_length);
    free(runtime->portable_fields);
    runtime->portable_fields = new_portable_fields;
    runtime->portable_fields_capacity = new_portable_fields_capacity;
  }
  
  int32_t* new_portable_field = (int32_t*)&runtime->portable_fields[runtime->portable_fields_unit * runtime->portable_fields_length];

  new_portable_field[0] = field->id;
  new_portable_field[1] = field->index;
  new_portable_field[2] = field->flag;
  new_portable_field[3] = SPVM_COMPILER_push_runtime_string(compiler, runtime, field->name);
  new_portable_field[4] = SPVM_COMPILER_push_runtime_string(compiler, runtime, field->abs_name);
  new_portable_field[5] = SPVM_COMPILER_push_runtime_string(compiler, runtime, field->signature);
  if (field->type->basic_type) {
    new_portable_field[6] = field->type->basic_type->id;
  }
  else {
    new_portable_field[6] = -1;
  }
  new_portable_field[7] = field->type->dimension;
  new_portable_field[8] = field->type->flag;
  if (field->package) {
    new_portable_field[9] = field->package->id;
  }
  else {
    new_portable_field[9] = -1;
  }
  
  runtime->portable_fields_length++;
}

void SPVM_COMPILER_build_runtime_basic_type_symtable(SPVM_COMPILER* compiler, SPVM_RUNTIME* runtime) {
  for (int32_t basic_type_id = 0; basic_type_id < runtime->runtime_basic_types->length; basic_type_id++) {
    SPVM_RUNTIME_BASIC_TYPE* runtime_basic_type = SPVM_LIST_fetch(runtime->runtime_basic_types, basic_type_id);
    SPVM_HASH_insert(runtime->runtime_basic_type_symtable, runtime_basic_type->name, strlen(runtime_basic_type->name), runtime_basic_type);
  }
}

void SPVM_COMPILER_build_runtime_fields(SPVM_COMPILER* compiler, SPVM_RUNTIME* runtime) {
  for (size_t i = 0; i < runtime->portable_fields_unit * runtime->portable_fields_length; i += runtime->portable_fields_unit) {
    int32_t* portable_field = (int32_t*)&runtime->portable_fields[i];
    
    SPVM_RUNTIME_FIELD* runtime_field = SPVM_RUNTIME_FIELD_new(compiler);
    runtime_field->id = portable_field[0];
    runtime_field->index = portable_field[1];
    runtime_field->flag = portable_field[2];
    runtime_field->name = runtime->strings[portable_field[3]];
    runtime_field->abs_name = runtime->strings[portable_field[4]];
    runtime_field->signature = runtime->strings[portable_field[5]];
    int32_t basic_type_id = portable_field[6];
    if (basic_type_id < 0) {
      runtime_field->runtime_basic_type = NULL;
    }
    else {
      SPVM_RUNTIME_FIELD* runtime_basic_type = SPVM_LIST_fetch(runtime->runtime_basic_types, basic_type_id);
      runtime_field->runtime_basic_type = runtime_basic_type;
    }
    runtime_field->type_dimension = portable_field[7];
    runtime_field->type_flag = portable_field[8];
    int32_t package_id = portable_field[9];
    if (package_id < 0) {
      runtime_field->package = NULL;
    }
    else {
      SPVM_PACKAGE* package = SPVM_LIST_fetch(compiler->packages, package_id);
      runtime_field->package = package;
    }
    
    SPVM_LIST_push(runtime->runtime_fields, runtime_field);
  }
}

void SPVM_COMPILER_build_runtime_field_symtable(SPVM_COMPILER* compiler, SPVM_RUNTIME* runtime) {
  for (int32_t field_id = 0; field_id < runtime->runtime_fields->length; field_id++) {
    SPVM_RUNTIME_FIELD* runtime_field = SPVM_LIST_fetch(runtime->runtime_fields, field_id);
    SPVM_HASH_insert(runtime->runtime_field_symtable, runtime_field->name, strlen(runtime_field->name), runtime_field);
  }
}

SPVM_RUNTIME* SPVM_COMPILER_new_runtime(SPVM_COMPILER* compiler) {
  
  SPVM_RUNTIME* runtime = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(SPVM_RUNTIME));
  
  SPVM_ENV* env = (SPVM_ENV*)SPVM_RUNTIME_API_get_env_runtime();
  
  runtime->env = env;

  runtime->compiler = compiler;
  
  // Set global runtime
  SPVM_RUNTIME_API_set_runtime(env, runtime);
  
  // Initialize Package Variables
  runtime->package_vars = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(SPVM_VALUE) * (compiler->package_vars->length + 1));

  runtime->mortal_stack_capacity = 1;

  runtime->mortal_stack = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(SPVM_OBJECT*) * runtime->mortal_stack_capacity);
  
  runtime->strings_capacity = 32;
  
  runtime->strings = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(char*) * runtime->strings_capacity);
  
  // Portable basic type
  runtime->portable_basic_types_capacity = 8;
  runtime->portable_basic_types_unit = 4;
  runtime->portable_basic_types = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * runtime->portable_basic_types_unit * runtime->portable_basic_types_capacity);
  for (int32_t basic_type_id = 0; basic_type_id < compiler->basic_types->length; basic_type_id++) {
    SPVM_BASIC_TYPE* basic_type = SPVM_LIST_fetch(compiler->basic_types, basic_type_id);
    SPVM_COMPILER_push_portable_basic_type(compiler, runtime, basic_type);
  }
  
  // Build runtime basic type infos
  runtime->runtime_basic_types = SPVM_COMPILER_ALLOCATOR_alloc_list(compiler, 0);
  runtime->runtime_basic_type_symtable = SPVM_COMPILER_ALLOCATOR_alloc_hash(compiler, 0);
  SPVM_COMPILER_build_runtime_basic_types(compiler, runtime);
  SPVM_COMPILER_build_runtime_basic_type_symtable(compiler, runtime);
  
  // Portable fields
  runtime->portable_fields_capacity = 8;
  runtime->portable_fields_unit = 10;
  runtime->portable_fields = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * runtime->portable_fields_unit * runtime->portable_fields_capacity);
  for (int32_t field_id = 0; field_id < compiler->fields->length; field_id++) {
    SPVM_BASIC_TYPE* field = SPVM_LIST_fetch(compiler->fields, field_id);
    SPVM_COMPILER_push_portable_field(compiler, runtime, field);
  }
  
  
  // Build runtime field infos
  runtime->runtime_fields = SPVM_COMPILER_ALLOCATOR_alloc_list(compiler, 0);
  runtime->runtime_field_symtable = SPVM_COMPILER_ALLOCATOR_alloc_hash(compiler, 0);
  SPVM_COMPILER_build_runtime_fields(compiler, runtime);
  SPVM_COMPILER_build_runtime_field_symtable(compiler, runtime);
  
  return runtime;
}

void SPVM_COMPILER_add_basic_types(SPVM_COMPILER* compiler) {
  // Add unknown basic_type
  {
     SPVM_BASIC_TYPE* basic_type = SPVM_BASIC_TYPE_new(compiler);
     basic_type->id = SPVM_BASIC_TYPE_C_ID_UNKNOWN;
     basic_type->name = SPVM_BASIC_TYPE_C_ID_NAMES[basic_type->id];
     SPVM_LIST_push(compiler->basic_types, basic_type);
     SPVM_HASH_insert(compiler->basic_type_symtable, basic_type->name, strlen(basic_type->name), basic_type);
  }
  
  // Add undef basic_type
  {
     SPVM_BASIC_TYPE* basic_type = SPVM_BASIC_TYPE_new(compiler);
     basic_type->id = SPVM_BASIC_TYPE_C_ID_UNDEF;
     basic_type->name = SPVM_BASIC_TYPE_C_ID_NAMES[basic_type->id];
     SPVM_LIST_push(compiler->basic_types, basic_type);
     SPVM_HASH_insert(compiler->basic_type_symtable, basic_type->name, strlen(basic_type->name), basic_type);
  }

  // Add void basic_type
  {
     SPVM_BASIC_TYPE* basic_type = SPVM_BASIC_TYPE_new(compiler);
     basic_type->id = SPVM_BASIC_TYPE_C_ID_VOID;
     basic_type->name = SPVM_BASIC_TYPE_C_ID_NAMES[basic_type->id];
     SPVM_LIST_push(compiler->basic_types, basic_type);
     SPVM_HASH_insert(compiler->basic_type_symtable, basic_type->name, strlen(basic_type->name), basic_type);
  }
  
  // Add byte basic_type
  {
     SPVM_BASIC_TYPE* basic_type = SPVM_BASIC_TYPE_new(compiler);
     basic_type->id = SPVM_BASIC_TYPE_C_ID_BYTE;
     basic_type->name = SPVM_BASIC_TYPE_C_ID_NAMES[basic_type->id];
     SPVM_LIST_push(compiler->basic_types, basic_type);
     SPVM_HASH_insert(compiler->basic_type_symtable, basic_type->name, strlen(basic_type->name), basic_type);
  }

  // Add short basic_type
  {
     SPVM_BASIC_TYPE* basic_type = SPVM_BASIC_TYPE_new(compiler);
     basic_type->id = SPVM_BASIC_TYPE_C_ID_SHORT;
     basic_type->name = SPVM_BASIC_TYPE_C_ID_NAMES[basic_type->id];
     SPVM_LIST_push(compiler->basic_types, basic_type);
     SPVM_HASH_insert(compiler->basic_type_symtable, basic_type->name, strlen(basic_type->name), basic_type);
  }

  // Add int basic_type
  {
     SPVM_BASIC_TYPE* basic_type = SPVM_BASIC_TYPE_new(compiler);
     basic_type->id = SPVM_BASIC_TYPE_C_ID_INT;
     basic_type->name = SPVM_BASIC_TYPE_C_ID_NAMES[basic_type->id];
     SPVM_LIST_push(compiler->basic_types, basic_type);
     SPVM_HASH_insert(compiler->basic_type_symtable, basic_type->name, strlen(basic_type->name), basic_type);
  }

  // Add long basic_type
  {
     SPVM_BASIC_TYPE* basic_type = SPVM_BASIC_TYPE_new(compiler);
     basic_type->id = SPVM_BASIC_TYPE_C_ID_LONG;
     basic_type->name = SPVM_BASIC_TYPE_C_ID_NAMES[basic_type->id];
     SPVM_LIST_push(compiler->basic_types, basic_type);
     SPVM_HASH_insert(compiler->basic_type_symtable, basic_type->name, strlen(basic_type->name), basic_type);
  }

  // Add float basic_type
  {
     SPVM_BASIC_TYPE* basic_type = SPVM_BASIC_TYPE_new(compiler);
     basic_type->id = SPVM_BASIC_TYPE_C_ID_FLOAT;
     basic_type->name = SPVM_BASIC_TYPE_C_ID_NAMES[basic_type->id];
     SPVM_LIST_push(compiler->basic_types, basic_type);
     SPVM_HASH_insert(compiler->basic_type_symtable, basic_type->name, strlen(basic_type->name), basic_type);
  }

  // Add double basic_type
  {
     SPVM_BASIC_TYPE* basic_type = SPVM_BASIC_TYPE_new(compiler);
     basic_type->id = SPVM_BASIC_TYPE_C_ID_DOUBLE;
     basic_type->name = SPVM_BASIC_TYPE_C_ID_NAMES[basic_type->id];
     SPVM_LIST_push(compiler->basic_types, basic_type);
     SPVM_HASH_insert(compiler->basic_type_symtable, basic_type->name, strlen(basic_type->name), basic_type);
  }

  // Add Object basic_type
  {
     SPVM_BASIC_TYPE* basic_type = SPVM_BASIC_TYPE_new(compiler);
     basic_type->id = SPVM_BASIC_TYPE_C_ID_ANY_OBJECT;
     basic_type->name = SPVM_BASIC_TYPE_C_ID_NAMES[basic_type->id];
     SPVM_LIST_push(compiler->basic_types, basic_type);
     SPVM_HASH_insert(compiler->basic_type_symtable, basic_type->name, strlen(basic_type->name), basic_type);
  }
}

void SPVM_COMPILER_compile(SPVM_COMPILER* compiler) {

  // If this is set to 1, you can see yacc parsing result
#ifdef SPVM_DEBUG_YACC
  SPVM_yydebug = 1;
#else
  SPVM_yydebug = 0;
#endif
  
  /* call SPVM_yyparse */
  int32_t parse_error_flag = SPVM_yyparse(compiler);
  if (parse_error_flag) {
    compiler->error_count++;
  }
  
  if (compiler->error_count == 0) {
    // Check syntax
    SPVM_OP_CHECKER_check(compiler);

    // Build bytecode
    if (compiler->error_count == 0) {
      SPVM_OPCODE_BUILDER_build_opcode_array(compiler);
    }
  }
}

void SPVM_COMPILER_free(SPVM_COMPILER* compiler) {
  
  // Free allocator
  SPVM_COMPILER_ALLOCATOR_free(compiler);
  
  // Free opcode array
  SPVM_OPCODE_ARRAY_free(compiler, compiler->opcode_array);
  
  free(compiler);
}
