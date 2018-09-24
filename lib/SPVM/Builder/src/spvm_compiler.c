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
#include "spvm_package_var.h"
#include "spvm_native.h"
#include "spvm_opcode.h"
#include "spvm_basic_type.h"
#include "spvm_use.h"
#include "spvm_op_checker.h"
#include "spvm_opcode_builder.h"
#include "spvm_object.h"
#include "spvm_my.h"

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

#ifndef SPVM_DONT_USE_CORE_LIB
  // use SPVM::CORE module
  {
    SPVM_OP* op_name = SPVM_OP_new_op_name(compiler, "SPVM::CORE", "SPVM::CORE", 0);
    SPVM_OP* op_type = SPVM_OP_build_basic_type(compiler, op_name);
    SPVM_OP* op_use = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_USE, op_name->file, op_name->line);
    SPVM_OP_build_use(compiler, op_use, op_type);
    SPVM_LIST_push(compiler->op_use_stack, op_use);
  }

  // use SPVM::Byte module
  {
    SPVM_OP* op_name = SPVM_OP_new_op_name(compiler, "SPVM::Byte", "SPVM::Byte", 0);
    SPVM_OP* op_type = SPVM_OP_build_basic_type(compiler, op_name);
    SPVM_OP* op_use = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_USE, op_name->file, op_name->line);
    SPVM_OP_build_use(compiler, op_use, op_type);
    SPVM_LIST_push(compiler->op_use_stack, op_use);
  }

  // use SPVM::Short module
  {
    SPVM_OP* op_name = SPVM_OP_new_op_name(compiler, "SPVM::Short", "SPVM::Short", 0);
    SPVM_OP* op_type = SPVM_OP_build_basic_type(compiler, op_name);
    SPVM_OP* op_use = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_USE, op_name->file, op_name->line);
    SPVM_OP_build_use(compiler, op_use, op_type);
    SPVM_LIST_push(compiler->op_use_stack, op_use);
  }

  // use SPVM::Int module
  {
    SPVM_OP* op_name = SPVM_OP_new_op_name(compiler, "SPVM::Int", "SPVM::Int", 0);
    SPVM_OP* op_type = SPVM_OP_build_basic_type(compiler, op_name);
    SPVM_OP* op_use = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_USE, op_name->file, op_name->line);
    SPVM_OP_build_use(compiler, op_use, op_type);
    SPVM_LIST_push(compiler->op_use_stack, op_use);
  }

  // use SPVM::Long module
  {
    SPVM_OP* op_name = SPVM_OP_new_op_name(compiler, "SPVM::Long", "SPVM::Long", 0);
    SPVM_OP* op_type = SPVM_OP_build_basic_type(compiler, op_name);
    SPVM_OP* op_use = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_USE, op_name->file, op_name->line);
    SPVM_OP_build_use(compiler, op_use, op_type);
    SPVM_LIST_push(compiler->op_use_stack, op_use);
  }

  // use SPVM::Float module
  {
    SPVM_OP* op_name = SPVM_OP_new_op_name(compiler, "SPVM::Float", "SPVM::Float", 0);
    SPVM_OP* op_type = SPVM_OP_build_basic_type(compiler, op_name);
    SPVM_OP* op_use = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_USE, op_name->file, op_name->line);
    SPVM_OP_build_use(compiler, op_use, op_type);
    SPVM_LIST_push(compiler->op_use_stack, op_use);
  }

  // use SPVM::Double module
  {
    SPVM_OP* op_name = SPVM_OP_new_op_name(compiler, "SPVM::Double", "SPVM::Double", 0);
    SPVM_OP* op_type = SPVM_OP_build_basic_type(compiler, op_name);
    SPVM_OP* op_use = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_USE, op_name->file, op_name->line);
    SPVM_OP_build_use(compiler, op_use, op_type);
    SPVM_LIST_push(compiler->op_use_stack, op_use);
  }
#endif

  return compiler;
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
  
  // Add SPVM::Byte basic_type
  {
     SPVM_BASIC_TYPE* basic_type = SPVM_BASIC_TYPE_new(compiler);
     basic_type->id = SPVM_BASIC_TYPE_C_ID_BYTE_OBJECT;
     basic_type->name = SPVM_BASIC_TYPE_C_ID_NAMES[basic_type->id];
     SPVM_LIST_push(compiler->basic_types, basic_type);
     SPVM_HASH_insert(compiler->basic_type_symtable, basic_type->name, strlen(basic_type->name), basic_type);
  }

  // Add SPVM::Short basic_type
  {
     SPVM_BASIC_TYPE* basic_type = SPVM_BASIC_TYPE_new(compiler);
     basic_type->id = SPVM_BASIC_TYPE_C_ID_SHORT_OBJECT;
     basic_type->name = SPVM_BASIC_TYPE_C_ID_NAMES[basic_type->id];
     SPVM_LIST_push(compiler->basic_types, basic_type);
     SPVM_HASH_insert(compiler->basic_type_symtable, basic_type->name, strlen(basic_type->name), basic_type);
  }

  // Add SPVM::Int basic_type
  {
     SPVM_BASIC_TYPE* basic_type = SPVM_BASIC_TYPE_new(compiler);
     basic_type->id = SPVM_BASIC_TYPE_C_ID_INT_OBJECT;
     basic_type->name = SPVM_BASIC_TYPE_C_ID_NAMES[basic_type->id];
     SPVM_LIST_push(compiler->basic_types, basic_type);
     SPVM_HASH_insert(compiler->basic_type_symtable, basic_type->name, strlen(basic_type->name), basic_type);
  }

  // Add SPVM::Long basic_type
  {
     SPVM_BASIC_TYPE* basic_type = SPVM_BASIC_TYPE_new(compiler);
     basic_type->id = SPVM_BASIC_TYPE_C_ID_LONG_OBJECT;
     basic_type->name = SPVM_BASIC_TYPE_C_ID_NAMES[basic_type->id];
     SPVM_LIST_push(compiler->basic_types, basic_type);
     SPVM_HASH_insert(compiler->basic_type_symtable, basic_type->name, strlen(basic_type->name), basic_type);
  }

  // Add SPVM::Float basic_type
  {
     SPVM_BASIC_TYPE* basic_type = SPVM_BASIC_TYPE_new(compiler);
     basic_type->id = SPVM_BASIC_TYPE_C_ID_FLOAT_OBJECT;
     basic_type->name = SPVM_BASIC_TYPE_C_ID_NAMES[basic_type->id];
     SPVM_LIST_push(compiler->basic_types, basic_type);
     SPVM_HASH_insert(compiler->basic_type_symtable, basic_type->name, strlen(basic_type->name), basic_type);
  }

  // Add SPVM::Double basic_type
  {
     SPVM_BASIC_TYPE* basic_type = SPVM_BASIC_TYPE_new(compiler);
     basic_type->id = SPVM_BASIC_TYPE_C_ID_DOUBLE_OBJECT;
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
