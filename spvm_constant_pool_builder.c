#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include "spvm_constant_pool_builder.h"
#include "spvm_constant_pool.h"
#include "spvm_constant_pool_type.h"
#include "spvm_constant_pool_package.h"
#include "spvm_constant_pool_sub.h"
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
  
  // Push types to constant pool
  {
    int32_t i;
    for (i = 0; i < compiler->types->length; i++) {
      SPVM_TYPE* type = SPVM_LIST_fetch(compiler->types, i);
      type->id = SPVM_CONSTANT_POOL_push_type(compiler, compiler->constant_pool, type);
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
        SPVM_CONSTANT_POOL_TYPE* constant_pool_type = (SPVM_CONSTANT_POOL_TYPE*)&compiler->constant_pool->values[type->id];
        constant_pool_type->parent_type_id = parent_type->id;
      }
      
      // Element type id
      char* element_type_name = SPVM_TYPE_get_element_name(compiler, type->name);
      if (element_type_name) {
        SPVM_TYPE* element_type = (SPVM_TYPE*)SPVM_HASH_search(compiler->type_symtable, element_type_name, strlen(element_type_name));
        if (element_type) {
          SPVM_CONSTANT_POOL_TYPE* constant_pool_type = (SPVM_CONSTANT_POOL_TYPE*)&compiler->constant_pool->values[type->id];
          constant_pool_type->element_type_id = element_type->id;
        }
        else {
          assert(0);
        }
      }
    }
  }
  
  // Push type index to constant pool
  {
    int32_t i;
    for (i = 0; i < compiler->types->length; i++) {
      SPVM_TYPE* type = SPVM_LIST_fetch(compiler->types, i);
      int32_t type_id = type->id;
      int32_t added_id = SPVM_CONSTANT_POOL_push_int(compiler, compiler->constant_pool, type_id);
      if (compiler->types_base == 0) {
        compiler->types_base = added_id;
      }
    }
  }

  // Push type code to id index to constant pool
  {
    int32_t type_code;
    for (type_code = 0; type_code < SPVM_TYPE_C_CORE_LENGTH; type_code++) {
      SPVM_TYPE* type = SPVM_LIST_fetch(compiler->types, type_code);
      int32_t type_id = type->id;
      
      int32_t added_id = SPVM_CONSTANT_POOL_push_int(compiler, compiler->constant_pool, type_id);
      if (!compiler->type_code_to_id_base) {
        compiler->type_code_to_id_base = added_id;
      }
    }
  }
  
  // Push package into constant_pool
  {
    int32_t package_index;
    for (package_index = 0; package_index < op_packages->length; package_index++) {
      SPVM_OP* op_package = SPVM_LIST_fetch(op_packages, package_index);
      SPVM_PACKAGE* package = op_package->uv.package;
      
      // Push field information to constant pool
      {
        int32_t field_index;
        for (field_index = 0; field_index < package->op_fields->length; field_index++) {
          SPVM_OP* op_field = SPVM_LIST_fetch(package->op_fields, field_index);
          SPVM_FIELD* field = op_field->uv.field;
          
          // Add field to constant pool
          field->id = SPVM_CONSTANT_POOL_push_field(compiler, compiler->constant_pool, field);
        }
      }
      package->id = SPVM_CONSTANT_POOL_push_package(compiler, compiler->constant_pool, package);
    }
  }

  // Push package indexes
  {
    int32_t package_index;
    for (package_index = 0; package_index < op_packages->length; package_index++) {
      SPVM_OP* op_package = SPVM_LIST_fetch(op_packages, package_index);
      int32_t package_id = op_package->uv.package->id;
      
      int32_t added_id = SPVM_CONSTANT_POOL_push_int(compiler, compiler->constant_pool, package_id);
      if (!compiler->packages_base) {
        compiler->packages_base = added_id;
      }
    }
  }
  
  // Set package id to type constant pool
  {
    {
      int32_t i;
      for (i = 0; i < compiler->types->length; i++) {
        SPVM_TYPE* type = SPVM_LIST_fetch(compiler->types, i);
        if (type->op_package) {
          SPVM_PACKAGE* package = type->op_package->uv.package;
          int32_t type_id = type->id;
          SPVM_CONSTANT_POOL_TYPE* constant_pool_type = (SPVM_CONSTANT_POOL_TYPE*)&compiler->constant_pool->values[type_id];
          constant_pool_type->package_id = package->id;
        }
      }
    }
  }
  
  // Push subroutine into constant pool
  {
    int32_t sub_index;
    for (sub_index = 0; sub_index < compiler->op_subs->length; sub_index++) {
      SPVM_OP* op_sub = SPVM_LIST_fetch(compiler->op_subs, sub_index);
      SPVM_SUB* sub = op_sub->uv.sub;
      sub->id = SPVM_CONSTANT_POOL_push_sub(compiler, compiler->constant_pool, sub);
      SPVM_CONSTANT_POOL_SUB* constant_pool_sub = (SPVM_CONSTANT_POOL_SUB*)&compiler->constant_pool->values[sub->id];
      constant_pool_sub->op_sub_id = sub_index;
    }
  }

  // Push subroutine index to constant pool
  {
    int32_t sub_index;
    for (sub_index = 0; sub_index < compiler->op_subs->length; sub_index++) {
      
      SPVM_OP* op_sub = SPVM_LIST_fetch(compiler->op_subs, sub_index);
      SPVM_SUB* sub = op_sub->uv.sub;
      int32_t sub_id = sub->id;
      int32_t added_id = SPVM_CONSTANT_POOL_push_int(compiler, compiler->constant_pool, sub_id);
      if (!compiler->subs_base) {
        compiler->subs_base = added_id;
      }
    }
  }

  // Set destcutor sub id to package
  {
    int32_t package_index;
    for (package_index = 0; package_index < op_packages->length; package_index++) {
      SPVM_OP* op_package = SPVM_LIST_fetch(op_packages, package_index);
      SPVM_PACKAGE* package = op_package->uv.package;
      
      int32_t package_id = package->id;
      
      SPVM_CONSTANT_POOL_PACKAGE* constant_pool_package = (SPVM_CONSTANT_POOL_PACKAGE*)&compiler->constant_pool->values[package_id];
      
      if (package->op_sub_destructor) {
        constant_pool_package->destructor_sub_id = package->op_sub_destructor->uv.sub->id;
      }
    }
  }
}
