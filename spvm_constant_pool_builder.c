#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include "spvm_constant_pool_builder.h"
#include "spvm_constant_pool.h"
#include "spvm_list.h"
#include "spvm_compiler.h"
#include "spvm_constant.h"
#include "spvm_op.h"
#include "spvm_type.h"
#include "spvm_package.h"
#include "spvm_field.h"
#include "spvm_sub.h"
#include "spvm_hash.h"

void SPVM_CONSTANT_POOL_BUILDER_build_constant_pool(SPVM_COMPILER* compiler) {
  SPVM_LIST* op_packages = compiler->op_packages;
  
  // Push constant to constant pool
  {
    int32_t i;
    for (i = 0; i < compiler->op_constants->length; i++) {
      SPVM_OP* op_constant = SPVM_LIST_fetch(compiler->op_constants, i);
      
      // Constant
      SPVM_CONSTANT* constant = op_constant->uv.constant;
      
      // Constant pool
      SPVM_CONSTANT_POOL* constant_pool = compiler->constant_pool;
      
      // Push value to constant pool
      switch (constant->type->code) {
        case SPVM_TYPE_C_CODE_BYTE: {
          int8_t value = constant->value.byte_value;
          
          constant->id = SPVM_CONSTANT_POOL_push_byte(compiler, constant_pool, value);
          break;
        }
        case SPVM_TYPE_C_CODE_SHORT: {
          int16_t value = constant->value.short_value;
          
          constant->id = SPVM_CONSTANT_POOL_push_short(compiler, constant_pool, value);
          break;
        }
        case SPVM_TYPE_C_CODE_INT: {
          int32_t value = constant->value.int_value;
          
          constant->id = SPVM_CONSTANT_POOL_push_int(compiler, constant_pool, value);
          break;
        }
        case SPVM_TYPE_C_CODE_LONG: {
          int64_t value = constant->value.long_value;
          
          constant->id = SPVM_CONSTANT_POOL_push_long(compiler, constant_pool, value);
          break;
        }
        case SPVM_TYPE_C_CODE_FLOAT: {
          float value = constant->value.float_value;
          
          constant->id = SPVM_CONSTANT_POOL_push_float(compiler, constant_pool, value);
          break;
        }
        case SPVM_TYPE_C_CODE_DOUBLE: {
          double value = constant->value.double_value;
          
          constant->id = SPVM_CONSTANT_POOL_push_double(compiler, constant_pool, value);
          break;
        }
        case SPVM_TYPE_C_CODE_STRING: {
          const char* value = constant->value.string_value;
          
          constant->id = SPVM_CONSTANT_POOL_push_string(compiler, constant_pool, value);
          
          break;
        }
        default:
          assert(0);
      }
    }
  }
  
  // Set parent type id and element type id
  {
    int32_t i;
    for (i = 0; i < compiler->types->length; i++) {
      SPVM_TYPE* type = SPVM_LIST_fetch(compiler->types, i);
      
      char* parent_type_name = SPVM_TYPE_get_parent_name(compiler, type->name);
      SPVM_TYPE* parent_type = (SPVM_TYPE*)SPVM_HASH_search(compiler->type_symtable, parent_type_name, strlen(parent_type_name));
      if (parent_type) {
        type->parent_type_id = parent_type->id;
      }
      
      // Element type id
      char* element_type_name = SPVM_TYPE_get_element_name(compiler, type->name);
      if (element_type_name) {
        SPVM_TYPE* element_type = (SPVM_TYPE*)SPVM_HASH_search(compiler->type_symtable, element_type_name, strlen(element_type_name));
        if (element_type) {
          type->element_type_id = element_type->id;
        }
        else {
          assert(0);
        }
      }
    }
  }
  
  // Push package into constant_pool
  {
    int32_t package_index;
    for (package_index = 0; package_index < op_packages->length; package_index++) {
      SPVM_OP* op_package = SPVM_LIST_fetch(op_packages, package_index);
      SPVM_PACKAGE* package = op_package->uv.package;
      SPVM_CONSTANT_POOL_push_package(compiler, compiler->constant_pool, package);
    }
  }
}
