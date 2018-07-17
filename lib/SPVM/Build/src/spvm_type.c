#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "spvm_compiler.h"
#include "spvm_type.h"
#include "spvm_list.h"
#include "spvm_op.h"
#include "spvm_compiler_allocator.h"
#include "spvm_hash.h"
#include "spvm_yacc_util.h"
#include "spvm_package.h"
#include "spvm_limit.h"
#include "spvm_basic_type.h"

int32_t SPVM_TYPE_get_type_name_length(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension) {
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_fetch(compiler->basic_types, basic_type_id);
  assert(basic_type);
  
  int32_t length = strlen(basic_type->name) + dimension * 2;
  
  return length;
}

void SPVM_TYPE_fprint_type_name(SPVM_COMPILER* compiler, FILE* fh, int32_t basic_type_id, int32_t dimension) {
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_fetch(compiler->basic_types, basic_type_id);
  assert(basic_type);
  
  fprintf(fh, "%s", basic_type->name);
  int32_t dim_index;
  for (dim_index = 0; dim_index < dimension; dim_index++) {
    fprintf(fh, "[]");
  }
}

void SPVM_TYPE_sprint_type_name(SPVM_COMPILER* compiler, char* buffer, int32_t basic_type_id, int32_t dimension) {
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_fetch(compiler->basic_types, basic_type_id);
  assert(basic_type);
  
  char* cur = buffer;
  
  sprintf(cur, "%s", basic_type->name);
  cur += strlen(basic_type->name);
  
  int32_t dim_index;
  for (dim_index = 0; dim_index < dimension; dim_index++) {
    sprintf(cur, "[]");
    cur += 2;
  }
  
  *cur = '\0';
  cur++;
}

SPVM_TYPE* SPVM_TYPE_new(SPVM_COMPILER* compiler) {
  SPVM_TYPE* type = SPVM_COMPILER_ALLOCATOR_safe_malloc_zero(compiler, sizeof(SPVM_TYPE));
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_create_void_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_TYPE* type = SPVM_TYPE_new(compiler);
  type->basic_type = SPVM_LIST_fetch(compiler->basic_types, SPVM_BASIC_TYPE_C_ID_VOID);
  type->dimension = 0;
  
  assert(type);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_create_undef_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_TYPE* type = SPVM_TYPE_new(compiler);
  type->basic_type = SPVM_LIST_fetch(compiler->basic_types, SPVM_BASIC_TYPE_C_ID_UNDEF);
  type->dimension = 0;
  
  assert(type);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_create_byte_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_TYPE* type = SPVM_TYPE_new(compiler);
  type->basic_type = SPVM_HASH_fetch(compiler->basic_type_symtable, "byte", strlen("byte"));
  type->dimension = 0;
  
  assert(type);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_create_short_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_TYPE* type = SPVM_TYPE_new(compiler);
  type->basic_type = SPVM_LIST_fetch(compiler->basic_types, SPVM_BASIC_TYPE_C_ID_SHORT);
  type->dimension = 0;
  
  assert(type);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_create_int_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_TYPE* type = SPVM_TYPE_new(compiler);
  type->basic_type = SPVM_LIST_fetch(compiler->basic_types, SPVM_BASIC_TYPE_C_ID_INT);
  type->dimension = 0;
  
  assert(type);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_create_long_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_TYPE* type = SPVM_TYPE_new(compiler);
  type->basic_type = SPVM_LIST_fetch(compiler->basic_types, SPVM_BASIC_TYPE_C_ID_LONG);
  type->dimension = 0;
  
  assert(type);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_create_float_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_TYPE* type = SPVM_TYPE_new(compiler);
  type->basic_type = SPVM_LIST_fetch(compiler->basic_types, SPVM_BASIC_TYPE_C_ID_FLOAT);
  type->dimension = 0;
  
  assert(type);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_create_double_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_TYPE* type = SPVM_TYPE_new(compiler);
  type->basic_type = SPVM_LIST_fetch(compiler->basic_types, SPVM_BASIC_TYPE_C_ID_DOUBLE);
  type->dimension = 0;
  
  assert(type);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_create_string_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_TYPE* type = SPVM_TYPE_new(compiler);
  type->basic_type = SPVM_LIST_fetch(compiler->basic_types, SPVM_BASIC_TYPE_C_ID_BYTE);
  type->dimension = 1;
  type->is_const = 1;
  
  assert(type);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_create_object_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_TYPE* type = SPVM_TYPE_new(compiler);
  type->basic_type = SPVM_LIST_fetch(compiler->basic_types, SPVM_BASIC_TYPE_C_ID_ANY_OBJECT);
  type->dimension = 0;
  
  assert(type);
  
  return type;
}

_Bool SPVM_TYPE_equal(SPVM_COMPILER* compiler, SPVM_TYPE* type1, SPVM_TYPE* type2) {
  (void)compiler;
  
  if (type1->basic_type->id == type2->basic_type->id && type1->dimension == type2->dimension) {
    return 1;
  }
  else {
    return 0;
  }
}

_Bool SPVM_TYPE_is_numeric(SPVM_COMPILER* compiler, SPVM_TYPE* type) {
  (void)compiler;
  
  assert(type);
  
  if (type->dimension == 0 && (type->basic_type->id >= SPVM_BASIC_TYPE_C_ID_BYTE && type->basic_type->id <= SPVM_BASIC_TYPE_C_ID_DOUBLE)) {
    return 1;
  }
  else {
    return 0;
  }
}

_Bool SPVM_TYPE_is_integral(SPVM_COMPILER* compiler, SPVM_TYPE* type) {
  (void)compiler;
  
  assert(type);
  
  if (type->dimension == 0 && (type->basic_type->id >= SPVM_BASIC_TYPE_C_ID_BYTE && type->basic_type->id <= SPVM_BASIC_TYPE_C_ID_LONG)) {
    return 1;
  }
  else {
    return 0;
  }
}

_Bool SPVM_TYPE_is_object(SPVM_COMPILER* compiler, SPVM_TYPE* type) {
  (void)compiler;
  
  if (type->dimension > 0 || (type->dimension == 0 && type->basic_type->id > SPVM_BASIC_TYPE_C_ID_DOUBLE)) {
    return 1;
  }
  else {
    return 0;
  }
}

_Bool SPVM_TYPE_is_any_object(SPVM_COMPILER* compiler, SPVM_TYPE* type) {
  (void)compiler;
  
  return type && type->dimension == 0 && type->basic_type->id == SPVM_BASIC_TYPE_C_ID_ANY_OBJECT;
}

_Bool SPVM_TYPE_is_package(SPVM_COMPILER* compiler, SPVM_TYPE* type) {
  (void)compiler;
  
  _Bool is_package = (type->dimension == 0 && type->basic_type->id >= SPVM_BASIC_TYPE_C_ID_ANY_OBJECT);
  
  return is_package;
}

_Bool SPVM_TYPE_is_string(SPVM_COMPILER* compiler, SPVM_TYPE* type) {
  (void)compiler;
  
  return type && type->dimension == 1 && type->basic_type->id == SPVM_BASIC_TYPE_C_ID_BYTE;
}

_Bool SPVM_TYPE_is_array(SPVM_COMPILER* compiler, SPVM_TYPE* type) {
  (void)compiler;
  
  return type->dimension > 0;
}

_Bool SPVM_TYPE_is_array_numeric(SPVM_COMPILER* compiler, SPVM_TYPE* type) {
  (void)compiler;
  
  assert(type);
  
  if (type->dimension == 1 && (type->basic_type->id >= SPVM_BASIC_TYPE_C_ID_BYTE && type->basic_type->id <= SPVM_BASIC_TYPE_C_ID_DOUBLE))
  {
    return 1;
  }
  else {
    return 0;
  }
}

_Bool SPVM_TYPE_is_int(SPVM_COMPILER* compiler, SPVM_TYPE* type) {
  (void)compiler;
  
  if (type->dimension == 0 && type->basic_type->id == SPVM_BASIC_TYPE_C_ID_INT) {
    return 1;
  }
  else {
    return 0;
  }
}

_Bool SPVM_TYPE_is_undef(SPVM_COMPILER* compiler, SPVM_TYPE* type) {
  (void)compiler;
  
  if (type->dimension == 0 && type->basic_type->id == SPVM_BASIC_TYPE_C_ID_UNDEF) {
    return 1;
  }
  else {
    return 0;
  }
}

_Bool SPVM_TYPE_is_value_t(SPVM_COMPILER* compiler, SPVM_TYPE* type) {
  (void)compiler;
  
  int32_t is_value_t;
  if (type->dimension == 0) {
    const char* basic_type_name = type->basic_type->name;
    SPVM_OP* op_package = SPVM_HASH_fetch(compiler->op_package_symtable, basic_type_name, strlen(basic_type_name));
    // Package
    if (op_package) {
      SPVM_PACKAGE* package = op_package->uv.package;
      if (package->category == SPVM_PACKAGE_C_CATEGORY_VALUE_T) {
        is_value_t = 1;
      }
      else {
        is_value_t = 0;
      }
    }
    // Numeric type
    else {
      is_value_t = 0;
    }
  }
  // Array
  else {
    is_value_t = 0;
  }
  
  return is_value_t;
}

_Bool SPVM_TYPE_is_basic_type_value_t(SPVM_COMPILER* compiler, SPVM_TYPE* type) {
  (void)compiler;
  
  int32_t is_basic_type_value_t;
  const char* basic_type_name = type->basic_type->name;
  SPVM_OP* op_package = SPVM_HASH_fetch(compiler->op_package_symtable, basic_type_name, strlen(basic_type_name));
  
  // Package
  if (op_package) {
    SPVM_PACKAGE* package = op_package->uv.package;
    if (package->category == SPVM_PACKAGE_C_CATEGORY_VALUE_T) {
      is_basic_type_value_t = 1;
    }
    else {
      is_basic_type_value_t = 0;
    }
  }
  // Numeric type
  else {
    is_basic_type_value_t = 0;
  }
  
  return is_basic_type_value_t;
}

int32_t SPVM_TYPE_get_width(SPVM_COMPILER* compiler, SPVM_TYPE* type) {
  
  int32_t width;
  if (type->dimension == 0) {
    const char* basic_type_name = type->basic_type->name;
    SPVM_OP* op_package = SPVM_HASH_fetch(compiler->op_package_symtable, basic_type_name, strlen(basic_type_name));
    // Package
    if (op_package) {
      SPVM_PACKAGE* package = op_package->uv.package;
      if (package->category == SPVM_PACKAGE_C_CATEGORY_VALUE_T) {
        width = package->op_fields->length;
      }
      else {
        width = 1;
      }
    }
    // Numeric type
    else {
      width = 1;
    }
  }
  // Array
  else {
    width = 1;
  }
  
  return width;
}
