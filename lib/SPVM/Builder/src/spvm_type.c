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
#include "spvm_field.h"
#include "spvm_limit.h"
#include "spvm_basic_type.h"
#include "spvm_sub.h"

const char* const SPVM_TYPE_TYPE_CATEGORY_C_ID_NAMES[] = {
  "UNKNOWN",
  "BYTE",
  "SHORT",
  "INT",
  "LONG",
  "FLOAT",
  "DOUBLE",
  "MULNUM_BYTE",
  "MULNUM_SHORT",
  "MULNUM_INT",
  "MULNUM_LONG",
  "MULNUM_FLOAT",
  "MULNUM_DOUBLE",
  "ANY_OBJECT",
  "PACKAGE",
  "NUMERIC_ARRAY",
  "MULNUM_ARRAY",
  "OBJECT_ARRAY",
  "REF_BYTE",
  "REF_SHORT",
  "REF_INT",
  "REF_LONG",
  "REF_FLOAT",
  "REF_DOUBLE",
  "REF_MULNUM_BYTE",
  "REF_MULNUM_SHORT",
  "REF_MULNUM_INT",
  "REF_MULNUM_LONG",
  "REF_MULNUM_FLOAT",
  "REF_MULNUM_DOUBLE",
  "VOID",
  "STRING",
};

int32_t SPVM_TYPE_get_type_category(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  
  int32_t type_category;
  if (SPVM_TYPE_is_string_type(compiler, basic_type_id, dimension, flag)) {
    type_category = SPVM_TYPE_C_TYPE_CATEGORY_STRING;
  }
  else if (SPVM_TYPE_is_numeric_type(compiler, basic_type_id, dimension, flag)) {
    switch (basic_type_id) {
      case SPVM_BASIC_TYPE_C_ID_BYTE: {
        type_category = SPVM_TYPE_C_TYPE_CATEGORY_BYTE;
        break;
      }
      case SPVM_BASIC_TYPE_C_ID_SHORT: {
        type_category = SPVM_TYPE_C_TYPE_CATEGORY_SHORT;
        break;
      }
      case SPVM_BASIC_TYPE_C_ID_INT: {
        type_category = SPVM_TYPE_C_TYPE_CATEGORY_INT;
        break;
      }
      case SPVM_BASIC_TYPE_C_ID_LONG: {
        type_category = SPVM_TYPE_C_TYPE_CATEGORY_LONG;
        break;
      }
      case SPVM_BASIC_TYPE_C_ID_FLOAT: {
        type_category = SPVM_TYPE_C_TYPE_CATEGORY_FLOAT;
        break;
      }
      case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
        type_category = SPVM_TYPE_C_TYPE_CATEGORY_DOUBLE;
        break;
      }
      default: {
        assert(0);
        break;
      }
    }
  }
  else if (SPVM_TYPE_is_multi_numeric_type(compiler, basic_type_id, dimension, flag)) {
    SPVM_BASIC_TYPE* basic_type = SPVM_LIST_fetch(compiler->basic_types, basic_type_id);
    SPVM_PACKAGE* value_package = basic_type->package;
    
    SPVM_FIELD* first_field = SPVM_LIST_fetch(value_package->fields, 0);
    
    SPVM_TYPE* field_type = first_field->type;

    switch (field_type->basic_type->id) {
      case SPVM_BASIC_TYPE_C_ID_BYTE: {
        type_category = SPVM_TYPE_C_TYPE_CATEGORY_MULNUM_BYTE;
        break;
      }
      case SPVM_BASIC_TYPE_C_ID_SHORT: {
        type_category = SPVM_TYPE_C_TYPE_CATEGORY_MULNUM_SHORT;
        break;
      }
      case SPVM_BASIC_TYPE_C_ID_INT: {
        type_category = SPVM_TYPE_C_TYPE_CATEGORY_MULNUM_INT;
        break;
      }
      case SPVM_BASIC_TYPE_C_ID_LONG: {
        type_category = SPVM_TYPE_C_TYPE_CATEGORY_MULNUM_LONG;
        break;
      }
      case SPVM_BASIC_TYPE_C_ID_FLOAT: {
        type_category = SPVM_TYPE_C_TYPE_CATEGORY_MULNUM_FLOAT;
        break;
      }
      case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
        type_category = SPVM_TYPE_C_TYPE_CATEGORY_MULNUM_DOUBLE;
        break;
      }
      default: {
        assert(0);
      }
    }
  }
  else if (SPVM_TYPE_is_object_type(compiler, basic_type_id, dimension, flag)) {
    if (SPVM_TYPE_is_string_type(compiler, basic_type_id, dimension, flag)) {
      type_category = SPVM_TYPE_C_TYPE_CATEGORY_NUMERIC_ARRAY;
    }
    else if (SPVM_TYPE_is_any_object_type(compiler, basic_type_id, dimension, flag)) {
      type_category = SPVM_TYPE_C_TYPE_CATEGORY_ANY_OBJECT;
    }
    else if (SPVM_TYPE_is_package_type(compiler, basic_type_id, dimension, flag)) {
      type_category = SPVM_TYPE_C_TYPE_CATEGORY_PACKAGE;
    }
    else if (SPVM_TYPE_is_numeric_array_type(compiler, basic_type_id, dimension, flag)) {
      type_category = SPVM_TYPE_C_TYPE_CATEGORY_NUMERIC_ARRAY;
    }
    else if (SPVM_TYPE_is_value_array_type(compiler, basic_type_id, dimension, flag)) {
      type_category = SPVM_TYPE_C_TYPE_CATEGORY_MULNUM_ARRAY;
    }
    else if (SPVM_TYPE_is_array_type(compiler, basic_type_id, dimension, flag)) {
      type_category = SPVM_TYPE_C_TYPE_CATEGORY_OBJECT_ARRAY;
    }
    else {
      assert(0);
    }
  }
  else if (SPVM_TYPE_is_ref_type(compiler, basic_type_id, dimension, flag)) {
    switch (basic_type_id) {
      case SPVM_BASIC_TYPE_C_ID_BYTE: {
        type_category = SPVM_TYPE_C_TYPE_CATEGORY_REF_BYTE;
        break;
      }
      case SPVM_BASIC_TYPE_C_ID_SHORT: {
        type_category = SPVM_TYPE_C_TYPE_CATEGORY_REF_SHORT;
        break;
      }
      case SPVM_BASIC_TYPE_C_ID_INT: {
        type_category = SPVM_TYPE_C_TYPE_CATEGORY_REF_INT;
        break;
      }
      case SPVM_BASIC_TYPE_C_ID_LONG: {
        type_category = SPVM_TYPE_C_TYPE_CATEGORY_REF_LONG;
        break;
      }
      case SPVM_BASIC_TYPE_C_ID_FLOAT: {
        type_category = SPVM_TYPE_C_TYPE_CATEGORY_REF_FLOAT;
        break;
      }
      case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
        type_category = SPVM_TYPE_C_TYPE_CATEGORY_REF_DOUBLE;
        break;
      }
      default: {
        SPVM_BASIC_TYPE* basic_type = SPVM_LIST_fetch(compiler->basic_types, basic_type_id);
        SPVM_PACKAGE* value_package = basic_type->package;
        
        SPVM_FIELD* first_field = SPVM_LIST_fetch(value_package->fields, 0);
        
        SPVM_TYPE* field_type = first_field->type;

        switch (field_type->basic_type->id) {
          case SPVM_BASIC_TYPE_C_ID_BYTE: {
            type_category = SPVM_TYPE_C_TYPE_CATEGORY_REF_MULNUM_BYTE;
            break;
          }
          case SPVM_BASIC_TYPE_C_ID_SHORT: {
            type_category = SPVM_TYPE_C_TYPE_CATEGORY_REF_MULNUM_SHORT;
            break;
          }
          case SPVM_BASIC_TYPE_C_ID_INT: {
            type_category = SPVM_TYPE_C_TYPE_CATEGORY_REF_MULNUM_INT;
            break;
          }
          case SPVM_BASIC_TYPE_C_ID_LONG: {
            type_category = SPVM_TYPE_C_TYPE_CATEGORY_REF_MULNUM_LONG;
            break;
          }
          case SPVM_BASIC_TYPE_C_ID_FLOAT: {
            type_category = SPVM_TYPE_C_TYPE_CATEGORY_REF_MULNUM_FLOAT;
            break;
          }
          case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
            type_category = SPVM_TYPE_C_TYPE_CATEGORY_REF_MULNUM_DOUBLE;
            break;
          }
          default: {
            assert(0);
          }
        }
        break;
      }
    }
  }
  else if (SPVM_TYPE_is_void_type(compiler, basic_type_id, dimension, flag)) {
    type_category = SPVM_TYPE_C_TYPE_CATEGORY_VOID;
  }
  else {
    assert(0);
  }
  
  return type_category;
}

int32_t SPVM_TYPE_has_callback(
  SPVM_COMPILER* compiler,
  int32_t package_basic_type_id, int32_t package_type_dimension, int32_t package_type_flag,
  int32_t callback_basic_type_id, int32_t callback_type_dimension, int32_t callback_type_flag)
{
  (void)compiler;

  assert(
    SPVM_TYPE_is_class_type(compiler, package_basic_type_id, package_type_dimension, package_type_flag)
    || SPVM_TYPE_is_callback_type(compiler, callback_basic_type_id, callback_type_dimension, callback_type_flag)
  );

  SPVM_BASIC_TYPE* package_basic_type = SPVM_LIST_fetch(compiler->basic_types, package_basic_type_id);
  SPVM_BASIC_TYPE* callback_basic_type = SPVM_LIST_fetch(compiler->basic_types, callback_basic_type_id);
  
  SPVM_PACKAGE* package = package_basic_type->package;
  SPVM_PACKAGE* callback = callback_basic_type->package;
  
  // Package which have only anon sub
  if (package->flag & SPVM_PACKAGE_C_FLAG_ANON_SUB_PACKAGE) {
    assert(package->subs->length == 1);
    assert(callback->subs->length == 1);
    SPVM_SUB* sub_callback = SPVM_LIST_fetch(callback->subs, 0);
    SPVM_SUB* found_sub = SPVM_LIST_fetch(package->subs, 0);
    
    if (strcmp(sub_callback->signature, found_sub->signature) == 0) {
      return 1;
    }
    else {
      return 0;
    }
  }
  // Normal package
  else {
    assert(callback->subs->length == 1);
    SPVM_SUB* sub_callback = SPVM_LIST_fetch(callback->subs, 0);
    
    SPVM_SUB* found_sub = SPVM_HASH_fetch(package->sub_symtable, sub_callback->name, strlen(sub_callback->name));
    if (!found_sub) {
      return 0;
    }
    
    if (strcmp(sub_callback->signature, found_sub->signature) == 0) {
      return 1;
    }
    else {
      return 0;
    }
  }
}

SPVM_TYPE* SPVM_TYPE_clone_type(SPVM_COMPILER* compiler, SPVM_TYPE* type) {
  SPVM_TYPE* new_type = SPVM_TYPE_new(compiler);
  new_type->basic_type = type->basic_type;
  new_type->dimension = type->dimension;
  new_type->flag = type->flag;
  new_type->is_self = type->is_self;
  
  return new_type;
}

int32_t SPVM_TYPE_get_type_name_length(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_fetch(compiler->basic_types, basic_type_id);
  assert(basic_type);
  
  int32_t length = 0;
  
  // Basic type
  length += strlen(basic_type->name);
  
  // []
  length += dimension * 2;
  
  // Back slash
  if (flag & SPVM_TYPE_C_FLAG_REF) {
    length += 1;
  }
  
  return length;
}

const char* SPVM_TYPE_new_type_name(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_fetch(compiler->basic_types, basic_type_id);
  assert(basic_type);
  
  int32_t type_name_length = SPVM_TYPE_get_type_name_length(compiler, basic_type_id, dimension, flag);
  
  char* type_name = SPVM_COMPILER_ALLOCATOR_safe_malloc_zero(compiler, type_name_length + 1);
  char* cur = type_name;

  sprintf(cur, "%s", basic_type->name);
  cur += strlen(basic_type->name);
  
  int32_t dim_index;
  for (dim_index = 0; dim_index < dimension; dim_index++) {
    sprintf(cur, "[]");
    cur += 2;
  }

  // Back slash
  if (flag & SPVM_TYPE_C_FLAG_REF) {
    sprintf(cur, "&");
    cur += 1;
  }
  
  *cur = '\0';
  cur++;
  
  return type_name;
}

SPVM_TYPE* SPVM_TYPE_new(SPVM_COMPILER* compiler) {
  SPVM_TYPE* type = SPVM_COMPILER_ALLOCATOR_safe_malloc_zero(compiler, sizeof(SPVM_TYPE));
  
  return type;
}

int32_t SPVM_TYPE_is_ref_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  (void)basic_type_id;
  (void)dimension;
  
  return flag & SPVM_TYPE_C_FLAG_REF;
}

SPVM_TYPE* SPVM_TYPE_create_void_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_TYPE* type = SPVM_TYPE_new(compiler);
  type->basic_type = SPVM_LIST_fetch(compiler->basic_types, SPVM_BASIC_TYPE_C_ID_VOID);
  type->dimension = 0;
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_create_oarray_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_TYPE* type = SPVM_TYPE_new(compiler);
  type->basic_type = SPVM_LIST_fetch(compiler->basic_types, SPVM_BASIC_TYPE_C_ID_OARRAY);
  type->dimension = 0;
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_create_undef_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_TYPE* type = SPVM_TYPE_new(compiler);
  type->basic_type = SPVM_LIST_fetch(compiler->basic_types, SPVM_BASIC_TYPE_C_ID_UNDEF);
  type->dimension = 0;
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_create_byte_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_TYPE* type = SPVM_TYPE_new(compiler);
  type->basic_type = SPVM_HASH_fetch(compiler->basic_type_symtable, "byte", strlen("byte"));
  type->dimension = 0;
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_create_short_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_TYPE* type = SPVM_TYPE_new(compiler);
  type->basic_type = SPVM_LIST_fetch(compiler->basic_types, SPVM_BASIC_TYPE_C_ID_SHORT);
  type->dimension = 0;
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_create_int_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_TYPE* type = SPVM_TYPE_new(compiler);
  type->basic_type = SPVM_LIST_fetch(compiler->basic_types, SPVM_BASIC_TYPE_C_ID_INT);
  type->dimension = 0;
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_create_long_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_TYPE* type = SPVM_TYPE_new(compiler);
  type->basic_type = SPVM_LIST_fetch(compiler->basic_types, SPVM_BASIC_TYPE_C_ID_LONG);
  type->dimension = 0;
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_create_float_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_TYPE* type = SPVM_TYPE_new(compiler);
  type->basic_type = SPVM_LIST_fetch(compiler->basic_types, SPVM_BASIC_TYPE_C_ID_FLOAT);
  type->dimension = 0;
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_create_double_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_TYPE* type = SPVM_TYPE_new(compiler);
  type->basic_type = SPVM_LIST_fetch(compiler->basic_types, SPVM_BASIC_TYPE_C_ID_DOUBLE);
  type->dimension = 0;
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_create_string_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_TYPE* type = SPVM_TYPE_new(compiler);
  type->basic_type = SPVM_LIST_fetch(compiler->basic_types, SPVM_BASIC_TYPE_C_ID_STRING);
  type->dimension = 0;
  
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

SPVM_TYPE* SPVM_TYPE_create_byte_object_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_TYPE* type = SPVM_TYPE_new(compiler);
  type->basic_type = SPVM_LIST_fetch(compiler->basic_types, SPVM_BASIC_TYPE_C_ID_BYTE_OBJECT);
  type->dimension = 0;
  
  assert(type);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_create_short_object_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_TYPE* type = SPVM_TYPE_new(compiler);
  type->basic_type = SPVM_LIST_fetch(compiler->basic_types, SPVM_BASIC_TYPE_C_ID_SHORT_OBJECT);
  type->dimension = 0;
  
  assert(type);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_create_int_object_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_TYPE* type = SPVM_TYPE_new(compiler);
  type->basic_type = SPVM_LIST_fetch(compiler->basic_types, SPVM_BASIC_TYPE_C_ID_INT_OBJECT);
  type->dimension = 0;
  
  assert(type);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_create_long_object_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_TYPE* type = SPVM_TYPE_new(compiler);
  type->basic_type = SPVM_LIST_fetch(compiler->basic_types, SPVM_BASIC_TYPE_C_ID_LONG_OBJECT);
  type->dimension = 0;
  
  assert(type);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_create_float_object_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_TYPE* type = SPVM_TYPE_new(compiler);
  type->basic_type = SPVM_LIST_fetch(compiler->basic_types, SPVM_BASIC_TYPE_C_ID_FLOAT_OBJECT);
  type->dimension = 0;
  
  assert(type);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_create_double_object_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_TYPE* type = SPVM_TYPE_new(compiler);
  type->basic_type = SPVM_LIST_fetch(compiler->basic_types, SPVM_BASIC_TYPE_C_ID_DOUBLE_OBJECT);
  type->dimension = 0;
  
  assert(type);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_create_byte_ref_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_TYPE* type = SPVM_TYPE_new(compiler);
  type->basic_type = SPVM_LIST_fetch(compiler->basic_types, SPVM_BASIC_TYPE_C_ID_BYTE);
  type->dimension = 0;
  type->flag |= SPVM_TYPE_C_FLAG_REF;
  
  assert(type);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_create_short_ref_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_TYPE* type = SPVM_TYPE_new(compiler);
  type->basic_type = SPVM_LIST_fetch(compiler->basic_types, SPVM_BASIC_TYPE_C_ID_SHORT);
  type->dimension = 0;
  type->flag |= SPVM_TYPE_C_FLAG_REF;
  
  assert(type);
  
  return type;
}


SPVM_TYPE* SPVM_TYPE_create_int_ref_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_TYPE* type = SPVM_TYPE_new(compiler);
  type->basic_type = SPVM_LIST_fetch(compiler->basic_types, SPVM_BASIC_TYPE_C_ID_INT);
  type->dimension = 0;
  type->flag |= SPVM_TYPE_C_FLAG_REF;
  
  assert(type);
  
  return type;
}


SPVM_TYPE* SPVM_TYPE_create_long_ref_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_TYPE* type = SPVM_TYPE_new(compiler);
  type->basic_type = SPVM_LIST_fetch(compiler->basic_types, SPVM_BASIC_TYPE_C_ID_LONG);
  type->dimension = 0;
  type->flag |= SPVM_TYPE_C_FLAG_REF;
  
  assert(type);
  
  return type;
}


SPVM_TYPE* SPVM_TYPE_create_float_ref_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_TYPE* type = SPVM_TYPE_new(compiler);
  type->basic_type = SPVM_LIST_fetch(compiler->basic_types, SPVM_BASIC_TYPE_C_ID_FLOAT);
  type->dimension = 0;
  type->flag |= SPVM_TYPE_C_FLAG_REF;
  
  assert(type);
  
  return type;
}


SPVM_TYPE* SPVM_TYPE_create_double_ref_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_TYPE* type = SPVM_TYPE_new(compiler);
  type->basic_type = SPVM_LIST_fetch(compiler->basic_types, SPVM_BASIC_TYPE_C_ID_DOUBLE);
  type->dimension = 0;
  type->flag |= SPVM_TYPE_C_FLAG_REF;
  
  assert(type);
  
  return type;
}

SPVM_TYPE* SPVM_TYPE_create_any_object_type(SPVM_COMPILER* compiler) {
  (void)compiler;
  
  SPVM_TYPE* type = SPVM_TYPE_new(compiler);
  type->basic_type = SPVM_LIST_fetch(compiler->basic_types, SPVM_BASIC_TYPE_C_ID_ANY_OBJECT);
  type->dimension = 0;
  
  assert(type);
  
  return type;
}

int32_t SPVM_TYPE_is_byte_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  if (dimension == 0 && (basic_type_id == SPVM_BASIC_TYPE_C_ID_BYTE) && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_void_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  if (dimension == 0 && (basic_type_id == SPVM_BASIC_TYPE_C_ID_VOID) && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_short_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  if (dimension == 0 && (basic_type_id == SPVM_BASIC_TYPE_C_ID_SHORT) && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_int_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  if (dimension == 0 && (basic_type_id == SPVM_BASIC_TYPE_C_ID_INT) && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_long_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  if (dimension == 0 && (basic_type_id == SPVM_BASIC_TYPE_C_ID_LONG) && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_float_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  if (dimension == 0 && (basic_type_id == SPVM_BASIC_TYPE_C_ID_FLOAT) && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_double_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  if (dimension == 0 && (basic_type_id == SPVM_BASIC_TYPE_C_ID_DOUBLE) && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_numeric_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  if (dimension == 0 && (basic_type_id >= SPVM_BASIC_TYPE_C_ID_BYTE && basic_type_id <= SPVM_BASIC_TYPE_C_ID_DOUBLE) && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_numeric_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  if (dimension == 0 && (basic_type_id >= SPVM_BASIC_TYPE_C_ID_BYTE_OBJECT && basic_type_id <= SPVM_BASIC_TYPE_C_ID_DOUBLE_OBJECT) && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_byte_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  if (dimension == 0 && (basic_type_id == SPVM_BASIC_TYPE_C_ID_BYTE_OBJECT) && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_short_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  if (dimension == 0 && (basic_type_id == SPVM_BASIC_TYPE_C_ID_SHORT_OBJECT) && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_int_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  if (dimension == 0 && (basic_type_id == SPVM_BASIC_TYPE_C_ID_INT_OBJECT) && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_long_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  if (dimension == 0 && (basic_type_id == SPVM_BASIC_TYPE_C_ID_LONG_OBJECT) && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_float_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  if (dimension == 0 && (basic_type_id == SPVM_BASIC_TYPE_C_ID_FLOAT_OBJECT) && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_double_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  if (dimension == 0 && (basic_type_id == SPVM_BASIC_TYPE_C_ID_DOUBLE_OBJECT) && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_numeric_ref_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  if (dimension == 0 && (basic_type_id >= SPVM_BASIC_TYPE_C_ID_BYTE && basic_type_id <= SPVM_BASIC_TYPE_C_ID_DOUBLE) && (flag & SPVM_TYPE_C_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_integral_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  if (dimension == 0 && (basic_type_id >= SPVM_BASIC_TYPE_C_ID_BYTE && basic_type_id <= SPVM_BASIC_TYPE_C_ID_LONG) && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  if (SPVM_TYPE_is_ref_type(compiler, basic_type_id, dimension, flag)) {
    return 0;
  }
  else if (SPVM_TYPE_is_multi_numeric_type(compiler, basic_type_id, dimension, flag)) {
    return 0;
  }
  else if (SPVM_TYPE_is_array_type(compiler, basic_type_id, dimension, flag)) {
    return 1;
  }
  else if (SPVM_TYPE_is_string_type(compiler, basic_type_id, dimension, flag)) {
    return 1;
  }
  else if (SPVM_TYPE_is_class_type(compiler, basic_type_id, dimension, flag)) {
    return 1;
  }
  else if (SPVM_TYPE_is_callback_type(compiler, basic_type_id, dimension, flag)) {
    return 1;
  }
  else if (SPVM_TYPE_is_any_object_type(compiler, basic_type_id, dimension, flag)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_object_array_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  if (SPVM_TYPE_is_array_type(compiler, basic_type_id, dimension, flag)) {
    if (SPVM_TYPE_is_oarray_type(compiler, basic_type_id, dimension, flag)) {
      return 1;
    }
    else {
      int32_t element_dimension = dimension - 1;
      if (SPVM_TYPE_is_ref_type(compiler, basic_type_id, element_dimension, flag)) {
        return 0;
      }
      else if (SPVM_TYPE_is_multi_numeric_type(compiler, basic_type_id, element_dimension, flag)) {
        return 0;
      }
      else if (SPVM_TYPE_is_array_type(compiler, basic_type_id, element_dimension, flag)) {
        return 1;
      }
      else if (SPVM_TYPE_is_string_type(compiler, basic_type_id, element_dimension, flag)) {
        return 1;
      }
      else if (SPVM_TYPE_is_class_type(compiler, basic_type_id, element_dimension, flag)) {
        return 1;
      }
      else if (SPVM_TYPE_is_callback_type(compiler, basic_type_id, element_dimension, flag)) {
        return 1;
      }
      else if (SPVM_TYPE_is_any_object_type(compiler, basic_type_id, element_dimension, flag)) {
        return 1;
      }
      else {
        return 0;
      }
    }
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_any_object_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  return dimension == 0 && basic_type_id == SPVM_BASIC_TYPE_C_ID_ANY_OBJECT && !(flag & SPVM_TYPE_C_FLAG_REF);
}

int32_t SPVM_TYPE_is_package_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_fetch(compiler->basic_types, basic_type_id);
  
  int32_t is_package_type;
  if (dimension == 0 && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    const char* basic_type_name = basic_type->name;
    SPVM_PACKAGE* package = SPVM_HASH_fetch(compiler->package_symtable, basic_type_name, strlen(basic_type_name));
    // Package
    if (package) {
      is_package_type = 1;
    }
    // Numeric type
    else {
      is_package_type = 0;
    }
  }
  // Array
  else {
    is_package_type = 0;
  }
  
  return is_package_type;
}

int32_t SPVM_TYPE_is_class_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  if (SPVM_TYPE_is_package_type(compiler, basic_type_id, dimension, flag)) {
    SPVM_BASIC_TYPE* basic_type = SPVM_LIST_fetch(compiler->basic_types, basic_type_id);
    const char* basic_type_name = basic_type->name;
    SPVM_PACKAGE* package = SPVM_HASH_fetch(compiler->package_symtable, basic_type_name, strlen(basic_type_name));
    if (package->category == SPVM_PACKAGE_C_CATEGORY_CLASS) {
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

int32_t SPVM_TYPE_is_callback_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  if (SPVM_TYPE_is_package_type(compiler, basic_type_id, dimension, flag)) {
    SPVM_BASIC_TYPE* basic_type = SPVM_LIST_fetch(compiler->basic_types, basic_type_id);
    const char* basic_type_name = basic_type->name;
    SPVM_PACKAGE* package = SPVM_HASH_fetch(compiler->package_symtable, basic_type_name, strlen(basic_type_name));
    if (package->category == SPVM_PACKAGE_C_CATEGORY_CALLBACK) {
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

int32_t SPVM_TYPE_is_string_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  return dimension == 0 && basic_type_id == SPVM_BASIC_TYPE_C_ID_STRING && !(flag & SPVM_TYPE_C_FLAG_REF);
}

int32_t SPVM_TYPE_is_byte_array_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  return dimension == 1 && basic_type_id == SPVM_BASIC_TYPE_C_ID_BYTE && !(flag & SPVM_TYPE_C_FLAG_REF);
}

int32_t SPVM_TYPE_is_array_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  if (SPVM_TYPE_is_oarray_type(compiler, basic_type_id, dimension, flag)) {
    return 1;
  }
  else {
    return dimension > 0 && !(flag & SPVM_TYPE_C_FLAG_REF);
  }
}

int32_t SPVM_TYPE_is_oarray_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  if (basic_type_id == SPVM_BASIC_TYPE_C_ID_OARRAY && dimension == 0 && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_numeric_array_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  if (dimension == 1 && (basic_type_id >= SPVM_BASIC_TYPE_C_ID_BYTE && basic_type_id <= SPVM_BASIC_TYPE_C_ID_DOUBLE) && !(flag & SPVM_TYPE_C_FLAG_REF))
  {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_undef_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  if (dimension == 0 && basic_type_id == SPVM_BASIC_TYPE_C_ID_UNDEF && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    return 1;
  }
  else {
    return 0;
  }
}

int32_t SPVM_TYPE_is_multi_numeric_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_fetch(compiler->basic_types, basic_type_id);
  
  int32_t is_mulnum_t;
  if (dimension == 0 && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    const char* basic_type_name = basic_type->name;
    SPVM_PACKAGE* package = SPVM_HASH_fetch(compiler->package_symtable, basic_type_name, strlen(basic_type_name));
    // Package
    if (package) {
      if (package->category == SPVM_PACKAGE_C_CATEGORY_VALUE) {
        is_mulnum_t = 1;
      }
      else {
        is_mulnum_t = 0;
      }
    }
    // Numeric type
    else {
      is_mulnum_t = 0;
    }
  }
  // Array
  else {
    is_mulnum_t = 0;
  }
  
  return is_mulnum_t;
}

int32_t SPVM_TYPE_is_value_ref_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_fetch(compiler->basic_types, basic_type_id);
  
  int32_t is_value_ref_type;
  if (dimension == 0 && (flag & SPVM_TYPE_C_FLAG_REF)) {
    const char* basic_type_name = basic_type->name;
    SPVM_PACKAGE* package = SPVM_HASH_fetch(compiler->package_symtable, basic_type_name, strlen(basic_type_name));
    // Package
    if (package) {
      if (package->category == SPVM_PACKAGE_C_CATEGORY_VALUE) {
        is_value_ref_type = 1;
      }
      else {
        is_value_ref_type = 0;
      }
    }
    // Numeric type
    else {
      is_value_ref_type = 0;
    }
  }
  // Array
  else {
    is_value_ref_type = 0;
  }
  
  return is_value_ref_type;
}

int32_t SPVM_TYPE_is_value_array_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;

  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_fetch(compiler->basic_types, basic_type_id);
  
  int32_t is_value_array_type;
  if (dimension == 1 && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    const char* basic_type_name = basic_type->name;
    SPVM_PACKAGE* package = SPVM_HASH_fetch(compiler->package_symtable, basic_type_name, strlen(basic_type_name));
    // Package
    if (package) {
      if (package->category == SPVM_PACKAGE_C_CATEGORY_VALUE) {
        is_value_array_type = 1;
      }
      else {
        is_value_array_type = 0;
      }
    }
    // Numeric type
    else {
      is_value_array_type = 0;
    }
  }
  // Array
  else {
    is_value_array_type = 0;
  }
  
  return is_value_array_type;
}

int32_t SPVM_TYPE_basic_type_is_multi_numeric_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  (void)dimension;

  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_fetch(compiler->basic_types, basic_type_id);
  
  int32_t is_basic_type_mulnum_t;
  const char* basic_type_name = basic_type->name;
  SPVM_PACKAGE* package = SPVM_HASH_fetch(compiler->package_symtable, basic_type_name, strlen(basic_type_name));
  
  // Package
  if (package) {
    if (package->category == SPVM_PACKAGE_C_CATEGORY_VALUE) {
      is_basic_type_mulnum_t = 1;
    }
    else {
      is_basic_type_mulnum_t = 0;
    }
  }
  // Numeric type
  else {
    is_basic_type_mulnum_t = 0;
  }
  
  return is_basic_type_mulnum_t;
}

int32_t SPVM_TYPE_get_width(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  
  int32_t is_multi_numeric_type = SPVM_TYPE_is_multi_numeric_type(compiler, basic_type_id, dimension, flag);
  
  int32_t width;
  if (is_multi_numeric_type) {
    
    SPVM_BASIC_TYPE* basic_type = SPVM_LIST_fetch(compiler->basic_types, basic_type_id);
    assert(basic_type);
    
    SPVM_PACKAGE* package = basic_type->package;
    
    assert(package);
    
    width = package->fields->length;
  }
  else {
    width = 1;
  }
  
  return width;
}
