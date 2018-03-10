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
      switch (constant->type->id) {
        case SPVM_TYPE_C_ID_BYTE: {
          int8_t value = constant->value.byte_value;
          
          constant->id = SPVM_CONSTANT_POOL_push_byte(compiler, constant_pool, value);
          break;
        }
        case SPVM_TYPE_C_ID_SHORT: {
          int16_t value = constant->value.short_value;
          
          constant->id = SPVM_CONSTANT_POOL_push_short(compiler, constant_pool, value);
          break;
        }
        case SPVM_TYPE_C_ID_INT: {
          int32_t value = constant->value.int_value;
          
          constant->id = SPVM_CONSTANT_POOL_push_int(compiler, constant_pool, value);
          break;
        }
        case SPVM_TYPE_C_ID_LONG: {
          int64_t value = constant->value.long_value;
          
          constant->id = SPVM_CONSTANT_POOL_push_long(compiler, constant_pool, value);
          break;
        }
        case SPVM_TYPE_C_ID_FLOAT: {
          float value = constant->value.float_value;
          
          constant->id = SPVM_CONSTANT_POOL_push_float(compiler, constant_pool, value);
          break;
        }
        case SPVM_TYPE_C_ID_DOUBLE: {
          double value = constant->value.double_value;
          
          constant->id = SPVM_CONSTANT_POOL_push_double(compiler, constant_pool, value);
          break;
        }
        case SPVM_TYPE_C_ID_STRING: {
          const char* value = constant->value.string_value;
          
          constant->id = SPVM_CONSTANT_POOL_push_string(compiler, constant_pool, value);
          
          break;
        }
        default:
          assert(0);
      }
    }
  }
}
