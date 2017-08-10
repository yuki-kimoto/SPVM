#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "spvm_compiler.h"
#include "spvm_type.h"
#include "spvm_dynamic_array.h"
#include "spvm_op.h"
#include "spvm_compiler_allocator.h"
#include "spvm_hash.h"
#include "spvm_yacc_util.h"
#include "spvm_package.h"
#include "spvm_limit.h"
#include "spvm_package.h"

const char* const SPVM_TYPE_C_CORE_NAMES[] = {
  "void",
  "byte",
  "short",
  "int",
  "long",
  "float",
  "double",
  "string",
  "byte[]",
  "short[]",
  "int[]",
  "long[]",
  "float[]",
  "double[]",
  "string[]",
};

const char* const SPVM_TYPE_C_CODE_NAMES[] = {
  "name",
  "array",
};

SPVM_TYPE* SPVM_TYPE_new(SPVM_COMPILER* compiler) {
  SPVM_TYPE* type = SPVM_COMPILER_ALLOCATOR_alloc_memory_pool(compiler, compiler->allocator, sizeof(SPVM_TYPE));
  
  type->code = 0;
  type->id = -1;
  type->name = NULL;
  type->name_length = 0;
  type->is_array = 0;
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_get_byte_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_TYPE* type = SPVM_DYNAMIC_ARRAY_fetch(compiler->types, SPVM_TYPE_C_ID_BYTE);
  
  assert(type);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_get_short_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_TYPE* type = SPVM_DYNAMIC_ARRAY_fetch(compiler->types, SPVM_TYPE_C_ID_SHORT);
  
  assert(type);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_get_int_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_TYPE* type = SPVM_DYNAMIC_ARRAY_fetch(compiler->types, SPVM_TYPE_C_ID_INT);
  
  assert(type);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_get_long_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_TYPE* type = SPVM_DYNAMIC_ARRAY_fetch(compiler->types, SPVM_TYPE_C_ID_LONG);
  
  assert(type);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_get_float_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_TYPE* type = SPVM_DYNAMIC_ARRAY_fetch(compiler->types, SPVM_TYPE_C_ID_FLOAT);
  
  assert(type);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_get_double_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_TYPE* type = SPVM_DYNAMIC_ARRAY_fetch(compiler->types, SPVM_TYPE_C_ID_DOUBLE);
  
  assert(type);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_get_string_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_TYPE* type = SPVM_DYNAMIC_ARRAY_fetch(compiler->types, SPVM_TYPE_C_ID_STRING);
  
  assert(type);
  
  return type;
}

// Resolve type and index type
_Bool SPVM_TYPE_resolve_name(SPVM_COMPILER* compiler, SPVM_OP* op_type, int32_t name_length) {
  
  SPVM_TYPE* type = op_type->uv.type;
  
  if (type->name) {
    return 1;
  }
  else {
    SPVM_DYNAMIC_ARRAY* type_part_names = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
    
    SPVM_DYNAMIC_ARRAY* parts = SPVM_COMPILER_ALLOCATOR_alloc_array(compiler, compiler->allocator, 0);
    SPVM_TYPE_build_parts(compiler, type, parts);
    type->parts = parts;
    
    {
      int32_t i;
      for (i = 0; i < parts->length; i++) {
        const char* part_name = SPVM_DYNAMIC_ARRAY_fetch(parts, i);
        
        SPVM_DYNAMIC_ARRAY_push(type_part_names, (void*)part_name);
        
        name_length += strlen(part_name);
      }
    }
    char* type_name = SPVM_COMPILER_ALLOCATOR_alloc_string(compiler, compiler->allocator, name_length);
    
    int32_t cur_pos = 0;
    {
      int32_t i;
      for (i = 0; i < type_part_names->length; i++) {
        const char* type_part_name = (const char*) SPVM_DYNAMIC_ARRAY_fetch(type_part_names, i);
        int32_t type_part_name_length = (int32_t)strlen(type_part_name);
        memcpy(type_name + cur_pos, type_part_name, type_part_name_length);
        cur_pos += type_part_name_length;
      }
    }
    type_name[cur_pos] = '\0';
    type->name = type_name;
  }
  
  return 1;
}

// Resolve type and index type
_Bool SPVM_TYPE_resolve_id(SPVM_COMPILER* compiler, SPVM_OP* op_type, int32_t name_length) {
  
  SPVM_TYPE* type = op_type->uv.type;
  
  assert(type->name);
  
  if (type->id >= 0) {
    return 1;
  }
  else {
    SPVM_DYNAMIC_ARRAY* parts = type->parts;
    
    {
      int32_t i;
      for (i = 0; i < parts->length; i++) {
        const char* part_name = SPVM_DYNAMIC_ARRAY_fetch(parts, i);
          
        // Core type or array
        if (strcmp(part_name, "void") == 0 || strcmp(part_name, "boolean") == 0 || strcmp(part_name, "byte") == 0 || strcmp(part_name, "short") == 0 || strcmp(part_name, "int") == 0
          || strcmp(part_name, "long") == 0 || strcmp(part_name, "float") == 0 || strcmp(part_name, "double") == 0
          || strcmp(part_name, "string") == 0 || strcmp(part_name, "[]") == 0)
        {
          // Nothing
        }
        else {
          // Package
          SPVM_HASH* op_package_symtable = compiler->op_package_symtable;
          SPVM_OP* op_found_package = SPVM_HASH_search(op_package_symtable, part_name, strlen(part_name));
          if (op_found_package) {
            // Nothing
          }
          else {
            SPVM_yyerror_format(compiler, "unknown package \"%s\" at %s line %d\n", part_name, op_type->file, op_type->line);
            return 0;
          }
        }
        name_length += strlen(part_name);
      }
    }
    
    // Create resolved type id
    SPVM_TYPE* found_type = SPVM_HASH_search(compiler->type_symtable, type->name, strlen(type->name));
    if (found_type) {
      type->id = found_type->id;
    }
    else {
      SPVM_TYPE* new_type = SPVM_TYPE_new(compiler);
      new_type->id = compiler->types->length;
      new_type->name = type->name;
      SPVM_DYNAMIC_ARRAY_push(compiler->types, new_type);
      SPVM_HASH_insert(compiler->type_symtable, type->name, strlen(type->name), new_type);
      
      type->id = new_type->id;
    }
  }
  
  return 1;
}

void SPVM_TYPE_build_parts(SPVM_COMPILER* compiler, SPVM_TYPE* type, SPVM_DYNAMIC_ARRAY* parts) {
  
  if (type->code == SPVM_TYPE_C_CODE_NAME) {
    const char* part = type->uv.op_name->uv.name;
    SPVM_DYNAMIC_ARRAY_push(parts, (void*)part);
  }
  else if (type->code == SPVM_TYPE_C_CODE_ARRAY) {
    SPVM_TYPE_build_parts(compiler, type->uv.op_type->uv.type, parts);
    const char* part = "[]";
    SPVM_DYNAMIC_ARRAY_push(parts, (void*)part);
  }
}

_Bool SPVM_TYPE_is_array(SPVM_COMPILER* compiler, SPVM_TYPE* type) {
  (void)compiler;
  
  return type->is_array;
}

_Bool SPVM_TYPE_is_array_numeric(SPVM_COMPILER* compiler, SPVM_TYPE* type) {
  (void)compiler;
  
  if (type && type->id >= SPVM_TYPE_C_ID_BYTE_ARRAY && type->id <= SPVM_TYPE_C_ID_DOUBLE_ARRAY)
  {
    return 1;
  }
  else {
    return 0;
  }
}

_Bool SPVM_TYPE_is_integral(SPVM_COMPILER* compiler, SPVM_TYPE* type) {
  (void)compiler;
  
  if (type && type->id >= SPVM_TYPE_C_ID_BYTE && type->id <= SPVM_TYPE_C_ID_LONG) {
    return 1;
  }
  else {
    return 0;
  }
}

_Bool SPVM_TYPE_is_numeric(SPVM_COMPILER* compiler, SPVM_TYPE* type) {
  (void)compiler;
  
  if (type && type->id >= SPVM_TYPE_C_ID_BYTE && type->id <= SPVM_TYPE_C_ID_DOUBLE) {
    return 1;
  }
  else {
    return 0;
  }
}
