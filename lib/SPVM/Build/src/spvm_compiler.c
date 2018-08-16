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
  warn("AAAAAAAAA");
    int32_t new_strings_capacity = runtime->strings_capacity * 2;
    char** new_strings = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(char*) * new_strings_capacity);
    memcpy(new_strings, runtime->strings, sizeof(char*) * runtime->strings_length);
  warn("BBBBBBBBBB");
    free(runtime->strings);
  warn("CCCCCCCCCC");
    runtime->strings = new_strings;
    runtime->strings_capacity = new_strings_capacity;
  }
  
  warn("DDDDDDDDD %d", runtime->strings_length);
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
  
  runtime->portable_basic_types_capacity = 8;

  runtime->portable_basic_types_unit = 4;
  
  // Portable basic type
  runtime->portable_basic_types = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * runtime->portable_basic_types_unit * runtime->portable_basic_types_capacity);
  for (int32_t basic_type_id = 0; basic_type_id < compiler->basic_types->length; basic_type_id++) {
    SPVM_BASIC_TYPE* basic_type = SPVM_LIST_fetch(compiler->basic_types, basic_type_id);
    SPVM_COMPILER_push_portable_basic_type(compiler, runtime, basic_type);
  }
  
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
