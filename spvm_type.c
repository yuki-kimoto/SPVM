#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "spvm_compiler.h"
#include "spvm_type.h"
#include "spvm_array.h"
#include "spvm_op.h"
#include "spvm_compiler_allocator.h"
#include "spvm_hash.h"
#include "spvm_yacc_util.h"
#include "spvm_package.h"
#include "spvm_limit.h"

const char* const SPVM_TYPE_C_CODE_NAMES[] = {
  "name",
  "array",
};

SPVM_TYPE* SPVM_TYPE_new(SPVM_COMPILER* compiler) {
  SPVM_TYPE* type = SPVM_COMPILER_ALLOCATOR_alloc_memory_pool(compiler, compiler->allocator, sizeof(SPVM_TYPE));
  
  type->type = NULL;
  type->resolved_type = NULL;
  type->code = 0;
  type->id = -1;
  type->name = NULL;
  type->name_length = 0;
  
  return type;
}

// Resolve type and index type
_Bool SPVM_TYPE_resolve_type_v2(SPVM_COMPILER* compiler, SPVM_OP* op_type, int32_t name_length) {
  
  SPVM_TYPE* type = op_type->uv.type;
  
  if (type->type) {
    return 1;
  }
  else {
    SPVM_ARRAY* type_part_names = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
    
    SPVM_ARRAY* parts = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
    SPVM_TYPE_build_parts(compiler, type, parts);
    
    for (int32_t i = 0; i < parts->length; i++) {
      const char* part_name = SPVM_ARRAY_fetch(parts, i);
        
      // Core type or array
      if (strcmp(part_name, "boolean") == 0 || strcmp(part_name, "byte") == 0 || strcmp(part_name, "short") == 0 || strcmp(part_name, "int") == 0
        || strcmp(part_name, "long") == 0 || strcmp(part_name, "float") == 0 || strcmp(part_name, "double") == 0 || strcmp(part_name, "[]") == 0)
      {
        SPVM_ARRAY_push(type_part_names, (void*)part_name);
      }
      else {
        // Package
        SPVM_HASH* op_package_symtable = compiler->op_package_symtable;
        SPVM_OP* op_found_package = SPVM_HASH_search(op_package_symtable, part_name, strlen(part_name));
        if (op_found_package) {
          SPVM_ARRAY_push(type_part_names, (void*)part_name);
        }
        else {
          SPVM_yyerror_format(compiler, "unknown package \"%s\" at %s line %d\n", part_name, op_type->file, op_type->line);
          return 0;
        }
      }
      name_length += strlen(part_name);
    }
    char* type_name = SPVM_COMPILER_ALLOCATOR_alloc_string(compiler, compiler->allocator, name_length);
    
    int32_t cur_pos = 0;
    for (int32_t i = 0; i < type_part_names->length; i++) {
      const char* type_part_name = (const char*) SPVM_ARRAY_fetch(type_part_names, i);
      int32_t type_part_name_length = (int32_t)strlen(type_part_name);
      memcpy(type_name + cur_pos, type_part_name, type_part_name_length);
      cur_pos += type_part_name_length;
    }
    type_name[cur_pos] = '\0';
    
    // Create resolved type id
    SPVM_TYPE* found_type = SPVM_HASH_search(compiler->type_symtable, type_name, strlen(type_name));
    if (found_type) {
      type->type = found_type;
    }
    else {
      SPVM_TYPE* type_tmp = SPVM_TYPE_new(compiler);
      type_tmp->id = compiler->types->length;
      type_tmp->name = type_name;
      SPVM_ARRAY_push(compiler->types, type_tmp);
      SPVM_HASH_insert(compiler->type_symtable, type_name, strlen(type_name), type_tmp);
      type->type = type_tmp;
    }
  }
  
  return 1;
}

void SPVM_TYPE_build_parts(SPVM_COMPILER* compiler, SPVM_TYPE* type, SPVM_ARRAY* parts) {
  
  if (type->code == SPVM_TYPE_C_CODE_NAME) {
    const char* part = type->uv.op_name->uv.name;
    SPVM_ARRAY_push(parts, part);
  }
  else if (type->code == SPVM_TYPE_C_CODE_ARRAY) {
    SPVM_TYPE_build_parts(compiler, type->uv.op_type->uv.type, parts);
    const char* part = "[]";
    SPVM_ARRAY_push(parts, part);
  }
}















#include "spvm_compiler_allocator.h"
#include "spvm_package.h"
#include "spvm_compiler.h"

const char* const SPVM_TYPE_C_CORE_NAMES[] = {
  "byte",
  "short",
  "int",
  "long",
  "float",
  "double",
  "byte[]",
  "short[]",
  "int[]",
  "long[]",
  "float[]",
  "double[]",
};

_Bool SPVM_TYPE_is_array(SPVM_COMPILER* compiler, SPVM_TYPE* type) {
  (void)compiler;
  
  int32_t length = (int32_t)strlen(type->name);
  
  if (strlen(type->name) >= 2) {
    char char1 = type->name[length - 2];
    char char2 = type->name[length - 1];
    
    if (char1 == '[' && char2 == ']') {
      return 1;
    }
    else {
      return 0;
    }
  }
  else {
    return 0;
  }
}

_Bool SPVM_TYPE_is_array_numeric(SPVM_COMPILER* compiler, SPVM_TYPE* type) {
  (void)compiler;
  
  const char* name = type->name;
  
  if (strcmp(name, "char[]") == 0 || strcmp(name, "byte[]") == 0 || strcmp(name, "short[]") == 0
    || strcmp(name, "int[]") == 0 || strcmp(name, "long[]") == 0 || strcmp(name, "float[]") == 0 || strcmp(name, "double[]") == 0)
  {
    return 1;
  }
  else {
    return 0;
  }
}

_Bool SPVM_TYPE_is_integral(SPVM_COMPILER* compiler, SPVM_TYPE* type) {
  (void)compiler;
  
  if (type->id <= SPVM_TYPE_C_ID_LONG) {
    return 1;
  }
  else {
    return 0;
  }
}

_Bool SPVM_TYPE_is_numeric(SPVM_COMPILER* compiler, SPVM_TYPE* type) {
  (void)compiler;
  
  if (type && type->id <= SPVM_TYPE_C_ID_DOUBLE) {
    return 1;
  }
  else {
    return 0;
  }
}
