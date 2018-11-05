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

int32_t SPVM_TYPE_get_runtime_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  
  int32_t runtime_type;
  if (SPVM_TYPE_is_numeric_type(compiler, basic_type_id, dimension, flag)) {
    switch (basic_type_id) {
      case SPVM_BASIC_TYPE_C_ID_BYTE: {
        runtime_type = SPVM_TYPE_C_RUNTIME_TYPE_BYTE;
        break;
      }
      case SPVM_BASIC_TYPE_C_ID_SHORT: {
        runtime_type = SPVM_TYPE_C_RUNTIME_TYPE_SHORT;
        break;
      }
      case SPVM_BASIC_TYPE_C_ID_INT: {
        runtime_type = SPVM_TYPE_C_RUNTIME_TYPE_INT;
        break;
      }
      case SPVM_BASIC_TYPE_C_ID_LONG: {
        runtime_type = SPVM_TYPE_C_RUNTIME_TYPE_LONG;
        break;
      }
      case SPVM_BASIC_TYPE_C_ID_FLOAT: {
        runtime_type = SPVM_TYPE_C_RUNTIME_TYPE_FLOAT;
        break;
      }
      case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
        runtime_type = SPVM_TYPE_C_RUNTIME_TYPE_DOUBLE;
        break;
      }
      default: {
        assert(0);
        break;
      }
    }
  }
  else if (SPVM_TYPE_is_value_type(compiler, basic_type_id, dimension, flag)) {
    SPVM_BASIC_TYPE* basic_type = SPVM_LIST_fetch(compiler->basic_types, basic_type_id);
    SPVM_PACKAGE* value_package = basic_type->package;
    
    SPVM_FIELD* first_field = SPVM_LIST_fetch(value_package->fields, 0);
    
    SPVM_TYPE* field_type = first_field->type;

    switch (field_type->basic_type->id) {
      case SPVM_BASIC_TYPE_C_ID_BYTE: {
        runtime_type = SPVM_TYPE_C_RUNTIME_TYPE_VALUE_BYTE;
        break;
      }
      case SPVM_BASIC_TYPE_C_ID_SHORT: {
        runtime_type = SPVM_TYPE_C_RUNTIME_TYPE_VALUE_SHORT;
        break;
      }
      case SPVM_BASIC_TYPE_C_ID_INT: {
        runtime_type = SPVM_TYPE_C_RUNTIME_TYPE_VALUE_INT;
        break;
      }
      case SPVM_BASIC_TYPE_C_ID_LONG: {
        runtime_type = SPVM_TYPE_C_RUNTIME_TYPE_VALUE_LONG;
        break;
      }
      case SPVM_BASIC_TYPE_C_ID_FLOAT: {
        runtime_type = SPVM_TYPE_C_RUNTIME_TYPE_VALUE_FLOAT;
        break;
      }
      case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
        runtime_type = SPVM_TYPE_C_RUNTIME_TYPE_VALUE_DOUBLE;
        break;
      }
      default: {
        assert(0);
      }
    }
  }
  else if (SPVM_TYPE_is_object_type(compiler, basic_type_id, dimension, flag)) {
    if (SPVM_TYPE_is_any_object_type(compiler, basic_type_id, dimension, flag)) {
      runtime_type = SPVM_TYPE_C_RUNTIME_TYPE_ANY_OBJECT;
    }
    else if (SPVM_TYPE_is_package_type(compiler, basic_type_id, dimension, flag)) {
      runtime_type = SPVM_TYPE_C_RUNTIME_TYPE_PACKAGE;
    }
    else if (SPVM_TYPE_is_numeric_array_type(compiler, basic_type_id, dimension, flag)) {
      runtime_type = SPVM_TYPE_C_RUNTIME_TYPE_NUMERIC_ARRAY;
    }
    else if (SPVM_TYPE_is_value_array_type(compiler, basic_type_id, dimension, flag)) {
      runtime_type = SPVM_TYPE_C_RUNTIME_TYPE_VALUE_ARRAY;
    }
    else if (SPVM_TYPE_is_array_type(compiler, basic_type_id, dimension, flag)) {
      runtime_type = SPVM_TYPE_C_RUNTIME_TYPE_OBJECT_ARRAY;
    }
    else {
      assert(0);
    }
  }
  else if (SPVM_TYPE_is_ref_type(compiler, basic_type_id, dimension, flag)) {
    switch (basic_type_id) {
      case SPVM_BASIC_TYPE_C_ID_BYTE: {
        runtime_type = SPVM_TYPE_C_RUNTIME_TYPE_REF_BYTE;
        break;
      }
      case SPVM_BASIC_TYPE_C_ID_SHORT: {
        runtime_type = SPVM_TYPE_C_RUNTIME_TYPE_REF_SHORT;
        break;
      }
      case SPVM_BASIC_TYPE_C_ID_INT: {
        runtime_type = SPVM_TYPE_C_RUNTIME_TYPE_REF_INT;
        break;
      }
      case SPVM_BASIC_TYPE_C_ID_LONG: {
        runtime_type = SPVM_TYPE_C_RUNTIME_TYPE_REF_LONG;
        break;
      }
      case SPVM_BASIC_TYPE_C_ID_FLOAT: {
        runtime_type = SPVM_TYPE_C_RUNTIME_TYPE_REF_FLOAT;
        break;
      }
      case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
        runtime_type = SPVM_TYPE_C_RUNTIME_TYPE_REF_DOUBLE;
        break;
      }
      default: {
        SPVM_BASIC_TYPE* basic_type = SPVM_LIST_fetch(compiler->basic_types, basic_type_id);
        SPVM_PACKAGE* value_package = basic_type->package;
        
        SPVM_FIELD* first_field = SPVM_LIST_fetch(value_package->fields, 0);
        
        SPVM_TYPE* field_type = first_field->type;

        switch (field_type->basic_type->id) {
          case SPVM_BASIC_TYPE_C_ID_BYTE: {
            runtime_type = SPVM_TYPE_C_RUNTIME_TYPE_REF_VALUE_BYTE;
            break;
          }
          case SPVM_BASIC_TYPE_C_ID_SHORT: {
            runtime_type = SPVM_TYPE_C_RUNTIME_TYPE_REF_VALUE_SHORT;
            break;
          }
          case SPVM_BASIC_TYPE_C_ID_INT: {
            runtime_type = SPVM_TYPE_C_RUNTIME_TYPE_REF_VALUE_INT;
            break;
          }
          case SPVM_BASIC_TYPE_C_ID_LONG: {
            runtime_type = SPVM_TYPE_C_RUNTIME_TYPE_REF_VALUE_LONG;
            break;
          }
          case SPVM_BASIC_TYPE_C_ID_FLOAT: {
            runtime_type = SPVM_TYPE_C_RUNTIME_TYPE_REF_VALUE_FLOAT;
            break;
          }
          case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
            runtime_type = SPVM_TYPE_C_RUNTIME_TYPE_REF_VALUE_DOUBLE;
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
    runtime_type = SPVM_TYPE_C_RUNTIME_TYPE_VOID;
  }
  else {
    assert(0);
  }
  
  return runtime_type;
}

int32_t SPVM_TYPE_has_interface(
  SPVM_COMPILER* compiler,
  int32_t package_basic_type_id, int32_t package_type_dimension, int32_t package_type_flag,
  int32_t interface_basic_type_id, int32_t interface_type_dimension, int32_t interface_type_flag)
{
  (void)compiler;

  assert(
    SPVM_TYPE_is_class_type(compiler, package_basic_type_id, package_type_dimension, package_type_flag)
    || SPVM_TYPE_is_interface_type(compiler, interface_basic_type_id, interface_type_dimension, interface_type_flag)
  );

  SPVM_BASIC_TYPE* package_basic_type = SPVM_LIST_fetch(compiler->basic_types, package_basic_type_id);
  SPVM_BASIC_TYPE* interface_basic_type = SPVM_LIST_fetch(compiler->basic_types, interface_basic_type_id);
  
  SPVM_PACKAGE* package = package_basic_type->package;
  SPVM_PACKAGE* interface = interface_basic_type->package;
  
  // Package which have only anon sub
  if (package->flag & SPVM_PACKAGE_C_FLAG_IS_HAS_ONLY_ANON_SUB) {
    assert(package->subs->length == 1);
    assert(interface->subs->length == 1);
    SPVM_SUB* sub_interface = SPVM_LIST_fetch(interface->subs, 0);
    SPVM_SUB* found_sub = SPVM_LIST_fetch(package->subs, 0);
    
    if (strcmp(sub_interface->signature, found_sub->signature) == 0) {
      return 1;
    }
    else {
      return 0;
    }
  }
  // Normal package
  else {
    assert(interface->subs->length == 1);
    SPVM_SUB* sub_interface = SPVM_LIST_fetch(interface->subs, 0);
    
    SPVM_SUB* found_sub = SPVM_HASH_fetch(package->sub_symtable, sub_interface->name, strlen(sub_interface->name));
    if (!found_sub) {
      return 0;
    }
    
    if (strcmp(sub_interface->signature, found_sub->signature) == 0) {
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
  
  // "const "
  if (flag & SPVM_TYPE_C_FLAG_CONST) {
    length += strlen("const") + 1;
  }
  
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

void SPVM_TYPE_fprint_type_name(SPVM_COMPILER* compiler, FILE* fh, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_fetch(compiler->basic_types, basic_type_id);
  assert(basic_type);

  // "const "
  if (flag & SPVM_TYPE_C_FLAG_CONST) {
    fprintf(fh, "const ");
  }

  // Basic type
  fprintf(fh, "%s", basic_type->name);
  
  // []
  int32_t dim_index;
  for (dim_index = 0; dim_index < dimension; dim_index++) {
    fprintf(fh, "[]");
  }

  // Back slash
  if (flag & SPVM_TYPE_C_FLAG_REF) {
    fprintf(fh, "&");
  }
}

void SPVM_TYPE_sprint_type_name(SPVM_COMPILER* compiler, char* buffer, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_fetch(compiler->basic_types, basic_type_id);
  assert(basic_type);
  
  char* cur = buffer;

  // "const "
  if (flag & SPVM_TYPE_C_FLAG_CONST) {
    sprintf(cur, "const ");
    cur += strlen("const") + 1;
  }

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
}

SPVM_TYPE* SPVM_TYPE_new(SPVM_COMPILER* compiler) {
  SPVM_TYPE* type = SPVM_COMPILER_ALLOCATOR_safe_malloc_zero(compiler, sizeof(SPVM_TYPE));
  
  return type;
}

int32_t SPVM_TYPE_is_ref_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)basic_type_id;
  (void)dimension;
  
  return flag & SPVM_TYPE_C_FLAG_REF;
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
  type->flag |= SPVM_TYPE_C_FLAG_CONST;
  
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
  else {
    if (SPVM_TYPE_is_value_type(compiler, basic_type_id, dimension, flag)) {
      return 0;
    }
    else {
      if (SPVM_TYPE_is_array_type(compiler, basic_type_id, dimension, flag)) {
        return 1;
      }
      else {
        if (SPVM_TYPE_is_package_type(compiler, basic_type_id, dimension, flag)) {
          return 1;
        }
        else if (SPVM_TYPE_is_any_object_type(compiler, basic_type_id, dimension, flag)) {
          return 1;
        }
        else {
          return 0;
        }
      }
    }
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

int32_t SPVM_TYPE_is_interface_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  if (SPVM_TYPE_is_package_type(compiler, basic_type_id, dimension, flag)) {
    SPVM_BASIC_TYPE* basic_type = SPVM_LIST_fetch(compiler->basic_types, basic_type_id);
    const char* basic_type_name = basic_type->name;
    SPVM_PACKAGE* package = SPVM_HASH_fetch(compiler->package_symtable, basic_type_name, strlen(basic_type_name));
    if (package->category == SPVM_PACKAGE_C_CATEGORY_INTERFACE) {
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
  
  return dimension == 1 && basic_type_id == SPVM_BASIC_TYPE_C_ID_BYTE && !(flag & SPVM_TYPE_C_FLAG_REF);
}

int32_t SPVM_TYPE_is_array_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  return dimension > 0 && !(flag & SPVM_TYPE_C_FLAG_REF);
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

int32_t SPVM_TYPE_is_value_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_fetch(compiler->basic_types, basic_type_id);
  
  int32_t is_value_t;
  if (dimension == 0 && !(flag & SPVM_TYPE_C_FLAG_REF)) {
    const char* basic_type_name = basic_type->name;
    SPVM_PACKAGE* package = SPVM_HASH_fetch(compiler->package_symtable, basic_type_name, strlen(basic_type_name));
    // Package
    if (package) {
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

int32_t SPVM_TYPE_is_value_ref_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;
  
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_fetch(compiler->basic_types, basic_type_id);
  
  int32_t is_value_ref_type;
  if (dimension == 0 && (flag & SPVM_TYPE_C_FLAG_REF)) {
    const char* basic_type_name = basic_type->name;
    SPVM_PACKAGE* package = SPVM_HASH_fetch(compiler->package_symtable, basic_type_name, strlen(basic_type_name));
    // Package
    if (package) {
      if (package->category == SPVM_PACKAGE_C_CATEGORY_VALUE_T) {
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
      if (package->category == SPVM_PACKAGE_C_CATEGORY_VALUE_T) {
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

int32_t SPVM_TYPE_basic_type_is_value_type(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  (void)compiler;

  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_fetch(compiler->basic_types, basic_type_id);
  
  int32_t is_basic_type_value_t;
  const char* basic_type_name = basic_type->name;
  SPVM_PACKAGE* package = SPVM_HASH_fetch(compiler->package_symtable, basic_type_name, strlen(basic_type_name));
  
  // Package
  if (package) {
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

int32_t SPVM_TYPE_get_width(SPVM_COMPILER* compiler, int32_t basic_type_id, int32_t dimension, int32_t flag) {
  
  int32_t is_value_type = SPVM_TYPE_is_value_type(compiler, basic_type_id, dimension, flag);
  
  int32_t width;
  if (is_value_type) {
    
    SPVM_BASIC_TYPE* basic_type = SPVM_LIST_fetch(compiler->basic_types, basic_type_id);
    assert(basic_type);
    
    const char* basic_type_name = basic_type->name;
    SPVM_PACKAGE* package = basic_type->package;
    
    assert(package);
    
    width = package->fields->length;
  }
  else {
    width = 1;
  }
  
  return width;
}
