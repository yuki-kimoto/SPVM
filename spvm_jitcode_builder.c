#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stddef.h>

#include "spvm_compiler.h"
#include "spvm_jitcode_builder.h"
#include "spvm_compiler.h"
#include "spvm_string_buffer.h"
#include "spvm_sub.h"
#include "spvm_op.h"
#include "spvm_dynamic_array.h"
#include "spvm_type.h"
#include "spvm_object.h"
#include "spvm_runtime.h"
#include "spvm_type.h"
#include "spvm_my.h"
#include "spvm_constant_pool.h"
#include "spvm_constant_pool_sub.h"
#include "spvm_constant_pool_package.h"
#include "spvm_constant_pool_field.h"
#include "spvm_constant_pool_type.h"
#include "spvm_opcode.h"
#include "spvm_opcode_array.h"

void SPVM_JITCODE_BUILDER_build_jitcode(SPVM_COMPILER* compiler) {
  (void)compiler;

  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_get_runtime();
  
  SPVM_STRING_BUFFER* string_buffer = SPVM_STRING_BUFFER_new(0);
  
  // API header
  SPVM_STRING_BUFFER_add(string_buffer, "#include <spvm_api.h>\n");
  SPVM_STRING_BUFFER_add(string_buffer, "\n");
  
  // Constant macro
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_JITCODE_C_OBJECT_HEADER_BYTE_SIZE ");
  SPVM_STRING_BUFFER_add_int(string_buffer, sizeof(SPVM_OBJECT));
  SPVM_STRING_BUFFER_add(string_buffer, "\n");
  
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_JITCODE_C_OBJECT_LENGTH_BYTE_OFFSET ");
  SPVM_STRING_BUFFER_add_int(string_buffer, (int32_t)offsetof(SPVM_OBJECT, length));
  SPVM_STRING_BUFFER_add(string_buffer, "\n");
  
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_JITCODE_C_OBJECT_REF_COUNT_BYTE_OFFSET ");
  SPVM_STRING_BUFFER_add_int(string_buffer, (int32_t)offsetof(SPVM_OBJECT, ref_count));
  SPVM_STRING_BUFFER_add(string_buffer, "\n");
  
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_JITCODE_C_RUNTIME_EXCEPTION_BYTE_OFFSET ");
  SPVM_STRING_BUFFER_add_int(string_buffer, (int32_t)offsetof(SPVM_RUNTIME, exception));
  SPVM_STRING_BUFFER_add(string_buffer, "\n");
  SPVM_STRING_BUFFER_add(string_buffer, "\n");
  
  // Inline macro function
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_JITCODE_INLINE_INC_REF_COUNT(object) ((*(int32_t*)((intptr_t)object + SPVM_JITCODE_C_OBJECT_REF_COUNT_BYTE_OFFSET))++)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_JITCODE_INLINE_DEC_REF_COUNT_ONLY(object) ((*(int32_t*)((intptr_t)object + SPVM_JITCODE_C_OBJECT_REF_COUNT_BYTE_OFFSET))--)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_JITCODE_INLINE_GET_EXCEPTION() (*(SPVM_API_OBJECT**)((intptr_t)SPVM_JITCODE_C_RUNTIME + SPVM_JITCODE_C_RUNTIME_EXCEPTION_BYTE_OFFSET)))\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_JITCODE_INLINE_SET_EXCEPTION_NULL()\\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  do { \\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    if ((*(SPVM_API_OBJECT**)((intptr_t)SPVM_JITCODE_C_RUNTIME + SPVM_JITCODE_C_RUNTIME_EXCEPTION_BYTE_OFFSET)) != NULL) { \\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "      api->dec_ref_count(api, (*(SPVM_API_OBJECT**)((intptr_t)SPVM_JITCODE_C_RUNTIME + SPVM_JITCODE_C_RUNTIME_EXCEPTION_BYTE_OFFSET))); \\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    } \\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    (*(SPVM_API_OBJECT**)((intptr_t)SPVM_JITCODE_C_RUNTIME + SPVM_JITCODE_C_RUNTIME_EXCEPTION_BYTE_OFFSET)) = NULL; \\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  } \\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  while (0) \\\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#define SPVM_JITCODE_INLINE_ISWEAK(object) ((intptr_t)object & 1)\n");
  SPVM_STRING_BUFFER_add(string_buffer, "\n");
  
  // Constant pool
  int32_t* constant_pool = compiler->constant_pool->values;

  int32_t subs_base = compiler->subs_base;
  int32_t subs_length = compiler->op_subs->length;

  // Subroutine Declaration
  {
    int32_t sub_index;
    for (sub_index = 0; sub_index < subs_length; sub_index++) {
      int32_t sub_id = constant_pool[subs_base + sub_index];
      
      SPVM_CONSTANT_POOL_SUB* constant_pool_sub = (SPVM_CONSTANT_POOL_SUB*)&constant_pool[sub_id];
      int32_t sub_abs_name_id = constant_pool_sub->abs_name_id;
      int32_t sub_abs_name_length = constant_pool[sub_abs_name_id];
      
      // Subroutine name
      const char* sub_abs_name = (char*)&constant_pool[sub_abs_name_id + 1];

      // Arguments length
      int32_t args_length = constant_pool_sub->args_length;
      
      // Arguments type ids base
      int32_t arg_type_ids_base = constant_pool_sub->arg_type_ids_base;
      
      // Return type code
      int32_t return_type_id = constant_pool_sub->return_type_id;
      SPVM_CONSTANT_POOL_TYPE* return_type = (SPVM_CONSTANT_POOL_TYPE*)&constant_pool[return_type_id];
      int32_t return_type_code = return_type->code;

      // Mys length
      int32_t mys_length = constant_pool_sub->mys_length;

      // My type ids base
      int32_t my_type_ids_base = constant_pool_sub->my_type_ids_base;

      // Return type
      switch (return_type->code) {
        case SPVM_TYPE_C_CODE_VOID:
          SPVM_STRING_BUFFER_add(string_buffer, "void ");
          break;
        case SPVM_TYPE_C_CODE_BYTE:
          SPVM_STRING_BUFFER_add(string_buffer, "int8_t ");
          break;
        case SPVM_TYPE_C_CODE_SHORT:
          SPVM_STRING_BUFFER_add(string_buffer, "int16_t ");
          break;
        case SPVM_TYPE_C_CODE_INT:
          SPVM_STRING_BUFFER_add(string_buffer, "int32_t ");
          break;
        case SPVM_TYPE_C_CODE_LONG:
          SPVM_STRING_BUFFER_add(string_buffer, "int64_t ");
          break;
        case SPVM_TYPE_C_CODE_FLOAT:
          SPVM_STRING_BUFFER_add(string_buffer, "float ");
          break;
        case SPVM_TYPE_C_CODE_DOUBLE:
          SPVM_STRING_BUFFER_add(string_buffer, "double ");
          break;
        default:
          SPVM_STRING_BUFFER_add(string_buffer, "SPVM_API_OBJECT* ");
      }

      // Subroutine name. Replace : to _
      SPVM_STRING_BUFFER_add(string_buffer, "SPVM_JITCODE_");
      SPVM_STRING_BUFFER_add(string_buffer, (char*)sub_abs_name);
      {
        int32_t index = string_buffer->length - strlen(sub_abs_name);
        
        while (index < string_buffer->length) {
          if (string_buffer->buffer[index] == ':') {
            string_buffer->buffer[index] = '_';
          }
          index++;
        }
      }

      // Arguments
      SPVM_STRING_BUFFER_add(string_buffer, "(");
      {
        int32_t arg_index;
        for (arg_index = 0; arg_index < args_length; arg_index++) {
          int32_t arg_type_id = constant_pool[arg_type_ids_base + arg_index];

          // Argument type code
          SPVM_CONSTANT_POOL_TYPE* constant_pool_arg_type = (SPVM_CONSTANT_POOL_TYPE*)&constant_pool[arg_type_id];
          int32_t arg_type_code = constant_pool_arg_type->code;
          
          switch (arg_type_code) {
            case SPVM_TYPE_C_CODE_BYTE : {
              SPVM_STRING_BUFFER_add(string_buffer, "int8_t ");
              break;
            }
            case  SPVM_TYPE_C_CODE_SHORT : {
              SPVM_STRING_BUFFER_add(string_buffer, "int16_t ");
              break;
            }
            case  SPVM_TYPE_C_CODE_INT : {
              SPVM_STRING_BUFFER_add(string_buffer, "int32_t ");
              break;
            }
            case  SPVM_TYPE_C_CODE_LONG : {
              SPVM_STRING_BUFFER_add(string_buffer, "int64_t ");
              break;
            }
            case  SPVM_TYPE_C_CODE_FLOAT : {
              SPVM_STRING_BUFFER_add(string_buffer, "float ");
              break;
            }
            case  SPVM_TYPE_C_CODE_DOUBLE : {
              SPVM_STRING_BUFFER_add(string_buffer, "double ");
              break;
            }
            default : {
              SPVM_STRING_BUFFER_add(string_buffer, "SPVM_API_OBJECT* ");
            }
          }
          SPVM_STRING_BUFFER_add(string_buffer, "arg");
          SPVM_STRING_BUFFER_add_int(string_buffer, arg_index);
          if (arg_index != args_length - 1) {
            SPVM_STRING_BUFFER_add(string_buffer, ", ");
          }
        }
      }
      SPVM_STRING_BUFFER_add(string_buffer, ");\n");
    }
    SPVM_STRING_BUFFER_add(string_buffer, "\n");
  }

  // Subroutine Implementations
  {
    int32_t sub_index;
    for (sub_index = 0; sub_index < subs_length; sub_index++) {
      int32_t sub_id = constant_pool[subs_base + sub_index];
      
      SPVM_CONSTANT_POOL_SUB* constant_pool_sub = (SPVM_CONSTANT_POOL_SUB*)&constant_pool[sub_id];
      int32_t sub_abs_name_id = constant_pool_sub->abs_name_id;
      int32_t sub_abs_name_length = constant_pool[sub_abs_name_id];
      
      // Subroutine name
      const char* sub_abs_name = (char*)&constant_pool[sub_abs_name_id + 1];

      // Arguments length
      int32_t args_length = constant_pool_sub->args_length;
      
      // Arguments type ids base
      int32_t arg_type_ids_base = constant_pool_sub->arg_type_ids_base;
      
      // Return type code
      int32_t return_type_id = constant_pool_sub->return_type_id;
      SPVM_CONSTANT_POOL_TYPE* return_type = (SPVM_CONSTANT_POOL_TYPE*)&constant_pool[return_type_id];
      int32_t return_type_code = return_type->code;

      // Mys length
      int32_t mys_length = constant_pool_sub->mys_length;

      // My type ids base
      int32_t my_type_ids_base = constant_pool_sub->my_type_ids_base;

      // Return type
      switch (return_type->code) {
        case SPVM_TYPE_C_CODE_VOID:
          SPVM_STRING_BUFFER_add(string_buffer, "void ");
          break;
        case SPVM_TYPE_C_CODE_BYTE:
          SPVM_STRING_BUFFER_add(string_buffer, "int8_t ");
          break;
        case SPVM_TYPE_C_CODE_SHORT:
          SPVM_STRING_BUFFER_add(string_buffer, "int16_t ");
          break;
        case SPVM_TYPE_C_CODE_INT:
          SPVM_STRING_BUFFER_add(string_buffer, "int32_t ");
          break;
        case SPVM_TYPE_C_CODE_LONG:
          SPVM_STRING_BUFFER_add(string_buffer, "int64_t ");
          break;
        case SPVM_TYPE_C_CODE_FLOAT:
          SPVM_STRING_BUFFER_add(string_buffer, "float ");
          break;
        case SPVM_TYPE_C_CODE_DOUBLE:
          SPVM_STRING_BUFFER_add(string_buffer, "double ");
          break;
        default:
          SPVM_STRING_BUFFER_add(string_buffer, "SPVM_API_OBJECT* ");
      }

      // Subroutine name. Replace : to _
      SPVM_STRING_BUFFER_add(string_buffer, "SPVM_JITCODE_");
      SPVM_STRING_BUFFER_add(string_buffer, (char*)sub_abs_name);
      {
        int32_t index = string_buffer->length - strlen(sub_abs_name);
        
        while (index < string_buffer->length) {
          if (string_buffer->buffer[index] == ':') {
            string_buffer->buffer[index] = '_';
          }
          index++;
        }
      }

      // Arguments
      SPVM_STRING_BUFFER_add(string_buffer, "(");
      {
        int32_t arg_index;
        for (arg_index = 0; arg_index < args_length; arg_index++) {
          int32_t arg_type_id = constant_pool[arg_type_ids_base + arg_index];

          // Argument type code
          SPVM_CONSTANT_POOL_TYPE* constant_pool_arg_type = (SPVM_CONSTANT_POOL_TYPE*)&constant_pool[arg_type_id];
          int32_t arg_type_code = constant_pool_arg_type->code;
          
          switch (arg_type_code) {
            case SPVM_TYPE_C_CODE_BYTE : {
              SPVM_STRING_BUFFER_add(string_buffer, "int8_t ");
              break;
            }
            case  SPVM_TYPE_C_CODE_SHORT : {
              SPVM_STRING_BUFFER_add(string_buffer, "int16_t ");
              break;
            }
            case  SPVM_TYPE_C_CODE_INT : {
              SPVM_STRING_BUFFER_add(string_buffer, "int32_t ");
              break;
            }
            case  SPVM_TYPE_C_CODE_LONG : {
              SPVM_STRING_BUFFER_add(string_buffer, "int64_t ");
              break;
            }
            case  SPVM_TYPE_C_CODE_FLOAT : {
              SPVM_STRING_BUFFER_add(string_buffer, "float ");
              break;
            }
            case  SPVM_TYPE_C_CODE_DOUBLE : {
              SPVM_STRING_BUFFER_add(string_buffer, "double ");
              break;
            }
            default : {
              SPVM_STRING_BUFFER_add(string_buffer, "SPVM_API_OBJECT* ");
            }
          }
          SPVM_STRING_BUFFER_add(string_buffer, "arg");
          SPVM_STRING_BUFFER_add_int(string_buffer, arg_index);
          if (arg_index != args_length - 1) {
            SPVM_STRING_BUFFER_add(string_buffer, ", ");
          }
        }
      }
      SPVM_STRING_BUFFER_add(string_buffer, ") {\n");

      // Lexical variables
      {
        int32_t my_index;
        for (my_index = args_length; my_index < mys_length; my_index++) {
          int32_t my_type_id = constant_pool[my_type_ids_base + my_index];

          // My type code
          SPVM_CONSTANT_POOL_TYPE* constant_pool_my_type = (SPVM_CONSTANT_POOL_TYPE*)&constant_pool[my_type_id];
          int32_t my_type_code = constant_pool_my_type->code;
          
          switch (my_type_code) {
            case SPVM_TYPE_C_CODE_BYTE : {
              SPVM_STRING_BUFFER_add(string_buffer, "  int8_t ");
              break;
            }
            case  SPVM_TYPE_C_CODE_SHORT : {
              SPVM_STRING_BUFFER_add(string_buffer, "  int16_t ");
              break;
            }
            case  SPVM_TYPE_C_CODE_INT : {
              SPVM_STRING_BUFFER_add(string_buffer, "  int32_t ");
              break;
            }
            case  SPVM_TYPE_C_CODE_LONG : {
              SPVM_STRING_BUFFER_add(string_buffer, "  int64_t ");
              break;
            }
            case  SPVM_TYPE_C_CODE_FLOAT : {
              SPVM_STRING_BUFFER_add(string_buffer, "  float ");
              break;
            }
            case  SPVM_TYPE_C_CODE_DOUBLE : {
              SPVM_STRING_BUFFER_add(string_buffer, "  double ");
              break;
            }
            default : {
              SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_API_OBJECT* ");
            }
          }
          SPVM_STRING_BUFFER_add(string_buffer, "var");
          SPVM_STRING_BUFFER_add_int(string_buffer, my_index);
          SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        }
      }
      
      // Eval stack
      if (constant_pool_sub->eval_stack_max_length > 0) {
        // Eval stack
        SPVM_STRING_BUFFER_add(string_buffer, "  int32_t eval_stack[");
        SPVM_STRING_BUFFER_add_int(string_buffer, constant_pool_sub->eval_stack_max_length);
        SPVM_STRING_BUFFER_add(string_buffer, "];\n");
        
        // Eval stack top
        SPVM_STRING_BUFFER_add(string_buffer, "  int32_t eval_stack_top = -1;\n");
      }

      // If arg is object, increment reference count
      {
        int32_t arg_index;
        for (arg_index = 0; arg_index < args_length; arg_index++) {
          int32_t arg_type_id = constant_pool[arg_type_ids_base + arg_index];

          // Argument type code
          SPVM_CONSTANT_POOL_TYPE* constant_pool_arg_type = (SPVM_CONSTANT_POOL_TYPE*)&constant_pool[arg_type_id];
          
          if (!constant_pool_arg_type->is_numeric) {
            SPVM_STRING_BUFFER_add(string_buffer, "  if (var");
            SPVM_STRING_BUFFER_add_int(string_buffer, arg_index);
            SPVM_STRING_BUFFER_add(string_buffer, " != NULL) {\n");
            
            SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_JITCODE_INLINE_INC_REF_COUNT(var");
            SPVM_STRING_BUFFER_add_int(string_buffer, arg_index);
            SPVM_STRING_BUFFER_add(string_buffer, ");\n");
            
            SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
          }
        }
        SPVM_STRING_BUFFER_add(string_buffer, "\n");
      }

      // Set exception to NULL
      SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_JITCODE_INLINE_SET_EXCEPTION_NULL();\n");
      SPVM_STRING_BUFFER_add(string_buffer, "\n");
      
      // Native subroutine
      if (constant_pool_sub->is_native) {
        // Assign native address
        switch (return_type_code) {
          case SPVM_TYPE_C_CODE_VOID:
            SPVM_STRING_BUFFER_add(string_buffer, "  void ");
            break;
          case SPVM_TYPE_C_CODE_BYTE:
            SPVM_STRING_BUFFER_add(string_buffer, "  int8_t ");
            break;
          case SPVM_TYPE_C_CODE_SHORT:
            SPVM_STRING_BUFFER_add(string_buffer, "  int16_t ");
            break;
          case SPVM_TYPE_C_CODE_INT:
            SPVM_STRING_BUFFER_add(string_buffer, "  int32_t ");
            break;
          case SPVM_TYPE_C_CODE_LONG:
            SPVM_STRING_BUFFER_add(string_buffer, "  int64_t ");
            break;
          case SPVM_TYPE_C_CODE_FLOAT:
            SPVM_STRING_BUFFER_add(string_buffer, "  float ");
            break;
          case SPVM_TYPE_C_CODE_DOUBLE:
            SPVM_STRING_BUFFER_add(string_buffer, "  double ");
            break;
          default:
            SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_API_OBJECT* ");
        }
        if (args_length > 0) {
          SPVM_STRING_BUFFER_add(string_buffer, "(*native_address)(SPVM_API*, ");
        }
        else {
          SPVM_STRING_BUFFER_add(string_buffer, "(*native_address)(SPVM_API*");
        }
        {
          int32_t arg_index;
          for (arg_index = 0; arg_index < args_length; arg_index++) {
            int32_t arg_type_id = constant_pool[arg_type_ids_base + arg_index];

            // Argument type code
            SPVM_CONSTANT_POOL_TYPE* constant_pool_arg_type = (SPVM_CONSTANT_POOL_TYPE*)&constant_pool[arg_type_id];
            int32_t arg_type_code = constant_pool_arg_type->code;
            
            switch (arg_type_code) {
              case SPVM_TYPE_C_CODE_BYTE : {
                SPVM_STRING_BUFFER_add(string_buffer, "int8_t ");
                break;
              }
              case  SPVM_TYPE_C_CODE_SHORT : {
                SPVM_STRING_BUFFER_add(string_buffer, "int16_t ");
                break;
              }
              case  SPVM_TYPE_C_CODE_INT : {
                SPVM_STRING_BUFFER_add(string_buffer, "int32_t ");
                break;
              }
              case  SPVM_TYPE_C_CODE_LONG : {
                SPVM_STRING_BUFFER_add(string_buffer, "int64_t ");
                break;
              }
              case  SPVM_TYPE_C_CODE_FLOAT : {
                SPVM_STRING_BUFFER_add(string_buffer, "float ");
                break;
              }
              case  SPVM_TYPE_C_CODE_DOUBLE : {
                SPVM_STRING_BUFFER_add(string_buffer, "double ");
                break;
              }
              default : {
                SPVM_STRING_BUFFER_add(string_buffer, "SPVM_API_OBJECT* ");
              }
            }
            SPVM_STRING_BUFFER_add(string_buffer, "arg");
            SPVM_STRING_BUFFER_add_int(string_buffer, arg_index);
            if (arg_index != args_length - 1) {
              SPVM_STRING_BUFFER_add(string_buffer, ", ");
            }
          }
        }
        SPVM_STRING_BUFFER_add(string_buffer, ") = ");
        SPVM_STRING_BUFFER_add_address(string_buffer, constant_pool_sub->native_address);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        
        // Call function
        switch (return_type_code) {
          case SPVM_TYPE_C_CODE_VOID:
            break;
          case SPVM_TYPE_C_CODE_BYTE:
            SPVM_STRING_BUFFER_add(string_buffer, "  int8_t ");
            break;
          case SPVM_TYPE_C_CODE_SHORT:
            SPVM_STRING_BUFFER_add(string_buffer, "  int16_t ");
            break;
          case SPVM_TYPE_C_CODE_INT:
            SPVM_STRING_BUFFER_add(string_buffer, "  int32_t ");
            break;
          case SPVM_TYPE_C_CODE_LONG:
            SPVM_STRING_BUFFER_add(string_buffer, "  int64_t ");
            break;
          case SPVM_TYPE_C_CODE_FLOAT:
            SPVM_STRING_BUFFER_add(string_buffer, "  float ");
            break;
          case SPVM_TYPE_C_CODE_DOUBLE:
            SPVM_STRING_BUFFER_add(string_buffer, "  double ");
            break;
          default:
            SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_API_OBJECT* ");
        }
        if (!constant_pool_sub->is_void) {
          SPVM_STRING_BUFFER_add(string_buffer, "return_value_native;\n");
        }
        if (args_length > 0) {
          SPVM_STRING_BUFFER_add(string_buffer, "  (*native_address)(");
          SPVM_STRING_BUFFER_add_address(string_buffer, runtime->api);
          SPVM_STRING_BUFFER_add(string_buffer, ", ");
        }
        else {
          SPVM_STRING_BUFFER_add(string_buffer, "  (*native_address)(");
          SPVM_STRING_BUFFER_add_address(string_buffer, runtime->api);
        }
        {
          int32_t arg_index;
          for (arg_index = 0; arg_index < args_length; arg_index++) {
            int32_t arg_type_id = constant_pool[arg_type_ids_base + arg_index];

            // Argument type code
            SPVM_CONSTANT_POOL_TYPE* constant_pool_arg_type = (SPVM_CONSTANT_POOL_TYPE*)&constant_pool[arg_type_id];
            int32_t arg_type_code = constant_pool_arg_type->code;
            
            switch (arg_type_code) {
              case SPVM_TYPE_C_CODE_BYTE : {
                SPVM_STRING_BUFFER_add(string_buffer, "int8_t ");
                break;
              }
              case  SPVM_TYPE_C_CODE_SHORT : {
                SPVM_STRING_BUFFER_add(string_buffer, "int16_t ");
                break;
              }
              case  SPVM_TYPE_C_CODE_INT : {
                SPVM_STRING_BUFFER_add(string_buffer, "int32_t ");
                break;
              }
              case  SPVM_TYPE_C_CODE_LONG : {
                SPVM_STRING_BUFFER_add(string_buffer, "int64_t ");
                break;
              }
              case  SPVM_TYPE_C_CODE_FLOAT : {
                SPVM_STRING_BUFFER_add(string_buffer, "float ");
                break;
              }
              case  SPVM_TYPE_C_CODE_DOUBLE : {
                SPVM_STRING_BUFFER_add(string_buffer, "double ");
                break;
              }
              default : {
                SPVM_STRING_BUFFER_add(string_buffer, "SPVM_API_OBJECT* ");
              }
            }
            SPVM_STRING_BUFFER_add(string_buffer, "arg");
            SPVM_STRING_BUFFER_add_int(string_buffer, arg_index);
            if (arg_index != args_length - 1) {
              SPVM_STRING_BUFFER_add(string_buffer, ", ");
            }
          }
        }
        SPVM_STRING_BUFFER_add(string_buffer, ");\n");
        if (constant_pool_sub->is_void) {
          SPVM_STRING_BUFFER_add(string_buffer, "  return;\n");
        }
        else {
          SPVM_STRING_BUFFER_add(string_buffer, "  return return_value_native;\n");
        }
        SPVM_STRING_BUFFER_add(string_buffer, "\n");
      }
      // Normal subroutine
      else {
        // Condition flag
        SPVM_STRING_BUFFER_add(string_buffer, "  int32_t condition_flag;\n");

        SPVM_OPCODE* opcodes = runtime->opcodes;
        int32_t opcode_index = constant_pool_sub->opcode_base;
        
        int32_t loop_break = 0;
        while (1) {
          SPVM_OPCODE* opcode = &(opcodes[opcode_index]);
          switch (opcode->code) {
            case SPVM_OPCODE_C_CODE_NOP:
              abort();
            case SPVM_OPCODE_C_CODE_BOOL_BYTE:
            case SPVM_OPCODE_C_CODE_BOOL_SHORT:
            case SPVM_OPCODE_C_CODE_BOOL_INT:
            case SPVM_OPCODE_C_CODE_BOOL_LONG:
            case SPVM_OPCODE_C_CODE_BOOL_FLOAT:
            case SPVM_OPCODE_C_CODE_BOOL_DOUBLE:
            case SPVM_OPCODE_C_CODE_BOOL_OBJECT:
              SPVM_STRING_BUFFER_add(string_buffer, "  condition_flag = !!var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              break;
            case SPVM_OPCODE_C_CODE_IS_UNDEF:
              SPVM_STRING_BUFFER_add(string_buffer, "  condition_flag = var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, " == NULL;\n");
              break;
            case SPVM_OPCODE_C_CODE_IS_NOT_UNDEF:
              SPVM_STRING_BUFFER_add(string_buffer, "  condition_flag = var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, " != NULL;\n");
              break;
            case SPVM_OPCODE_C_CODE_EQ_BYTE:
            case SPVM_OPCODE_C_CODE_EQ_SHORT:
            case SPVM_OPCODE_C_CODE_EQ_INT:
            case SPVM_OPCODE_C_CODE_EQ_LONG:
            case SPVM_OPCODE_C_CODE_EQ_FLOAT:
            case SPVM_OPCODE_C_CODE_EQ_DOUBLE:
            case SPVM_OPCODE_C_CODE_EQ_OBJECT:
              SPVM_STRING_BUFFER_add(string_buffer, "  condition_flag = var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, " == var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              break;
            case SPVM_OPCODE_C_CODE_NE_BYTE:
            case SPVM_OPCODE_C_CODE_NE_SHORT:
            case SPVM_OPCODE_C_CODE_NE_INT:
            case SPVM_OPCODE_C_CODE_NE_LONG:
            case SPVM_OPCODE_C_CODE_NE_FLOAT:
            case SPVM_OPCODE_C_CODE_NE_DOUBLE:
            case SPVM_OPCODE_C_CODE_NE_OBJECT:
              SPVM_STRING_BUFFER_add(string_buffer, "  condition_flag = var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, " != var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              break;
            case SPVM_OPCODE_C_CODE_GT_BYTE:
            case SPVM_OPCODE_C_CODE_GT_SHORT:
            case SPVM_OPCODE_C_CODE_GT_INT:
            case SPVM_OPCODE_C_CODE_GT_LONG:
            case SPVM_OPCODE_C_CODE_GT_FLOAT:
            case SPVM_OPCODE_C_CODE_GT_DOUBLE:
              SPVM_STRING_BUFFER_add(string_buffer, "  condition_flag = var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, " > var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              break;
            case SPVM_OPCODE_C_CODE_GE_BYTE:
            case SPVM_OPCODE_C_CODE_GE_SHORT:
            case SPVM_OPCODE_C_CODE_GE_INT:
            case SPVM_OPCODE_C_CODE_GE_LONG:
            case SPVM_OPCODE_C_CODE_GE_FLOAT:
            case SPVM_OPCODE_C_CODE_GE_DOUBLE:
              SPVM_STRING_BUFFER_add(string_buffer, "  condition_flag = var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, " <= var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              break;
            case SPVM_OPCODE_C_CODE_LT_BYTE:
            case SPVM_OPCODE_C_CODE_LT_SHORT:
            case SPVM_OPCODE_C_CODE_LT_INT:
            case SPVM_OPCODE_C_CODE_LT_LONG:
            case SPVM_OPCODE_C_CODE_LT_FLOAT:
            case SPVM_OPCODE_C_CODE_LT_DOUBLE:
              SPVM_STRING_BUFFER_add(string_buffer, "  condition_flag = var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, " < var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              break;
            case SPVM_OPCODE_C_CODE_LE_BYTE:
            case SPVM_OPCODE_C_CODE_LE_SHORT:
            case SPVM_OPCODE_C_CODE_LE_INT:
            case SPVM_OPCODE_C_CODE_LE_LONG:
            case SPVM_OPCODE_C_CODE_LE_FLOAT:
            case SPVM_OPCODE_C_CODE_LE_DOUBLE:
              SPVM_STRING_BUFFER_add(string_buffer, "  condition_flag = var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, " <= var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              break;
            case SPVM_OPCODE_C_CODE_ADD_BYTE:
            case SPVM_OPCODE_C_CODE_ADD_SHORT:
            case SPVM_OPCODE_C_CODE_ADD_INT:
            case SPVM_OPCODE_C_CODE_ADD_LONG:
            case SPVM_OPCODE_C_CODE_ADD_FLOAT:
            case SPVM_OPCODE_C_CODE_ADD_DOUBLE:
              SPVM_STRING_BUFFER_add(string_buffer, "  var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, " = var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
              SPVM_STRING_BUFFER_add(string_buffer, " + var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand2);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              break;
            case SPVM_OPCODE_C_CODE_SUBTRACT_BYTE:
            case SPVM_OPCODE_C_CODE_SUBTRACT_SHORT:
            case SPVM_OPCODE_C_CODE_SUBTRACT_INT:
            case SPVM_OPCODE_C_CODE_SUBTRACT_LONG:
            case SPVM_OPCODE_C_CODE_SUBTRACT_FLOAT:
            case SPVM_OPCODE_C_CODE_SUBTRACT_DOUBLE:
              SPVM_STRING_BUFFER_add(string_buffer, "  var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, " = var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
              SPVM_STRING_BUFFER_add(string_buffer, " - var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand2);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              break;
            case SPVM_OPCODE_C_CODE_MULTIPLY_BYTE:
            case SPVM_OPCODE_C_CODE_MULTIPLY_SHORT:
            case SPVM_OPCODE_C_CODE_MULTIPLY_INT:
            case SPVM_OPCODE_C_CODE_MULTIPLY_LONG:
            case SPVM_OPCODE_C_CODE_MULTIPLY_FLOAT:
            case SPVM_OPCODE_C_CODE_MULTIPLY_DOUBLE:
              SPVM_STRING_BUFFER_add(string_buffer, "  var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, " = var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
              SPVM_STRING_BUFFER_add(string_buffer, " * var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand2);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              break;
            case SPVM_OPCODE_C_CODE_DIVIDE_BYTE:
            case SPVM_OPCODE_C_CODE_DIVIDE_SHORT:
            case SPVM_OPCODE_C_CODE_DIVIDE_INT:
            case SPVM_OPCODE_C_CODE_DIVIDE_LONG:
              // TODO
              break;
            case SPVM_OPCODE_C_CODE_DIVIDE_FLOAT:
            case SPVM_OPCODE_C_CODE_DIVIDE_DOUBLE:
              SPVM_STRING_BUFFER_add(string_buffer, "  var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, " = var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
              SPVM_STRING_BUFFER_add(string_buffer, " / var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand2);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              break;
            case SPVM_OPCODE_C_CODE_REMAINDER_BYTE:
            case SPVM_OPCODE_C_CODE_REMAINDER_SHORT:
            case SPVM_OPCODE_C_CODE_REMAINDER_INT:
            case SPVM_OPCODE_C_CODE_REMAINDER_LONG:
              SPVM_STRING_BUFFER_add(string_buffer, "  var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, " = var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
              SPVM_STRING_BUFFER_add(string_buffer, " % var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand2);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              break;
            case SPVM_OPCODE_C_CODE_REMAINDER_FLOAT:
            case SPVM_OPCODE_C_CODE_REMAINDER_DOUBLE:
              // TODO
              break;
            case SPVM_OPCODE_C_CODE_LEFT_SHIFT_BYTE:
            case SPVM_OPCODE_C_CODE_LEFT_SHIFT_SHORT:
            case SPVM_OPCODE_C_CODE_LEFT_SHIFT_INT:
            case SPVM_OPCODE_C_CODE_LEFT_SHIFT_LONG:
              SPVM_STRING_BUFFER_add(string_buffer, "  var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, " = var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
              SPVM_STRING_BUFFER_add(string_buffer, " << var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand2);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              break;
            case SPVM_OPCODE_C_CODE_RIGHT_SHIFT_BYTE:
            case SPVM_OPCODE_C_CODE_RIGHT_SHIFT_SHORT:
            case SPVM_OPCODE_C_CODE_RIGHT_SHIFT_INT:
            case SPVM_OPCODE_C_CODE_RIGHT_SHIFT_LONG:
              SPVM_STRING_BUFFER_add(string_buffer, "  var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, " = var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
              SPVM_STRING_BUFFER_add(string_buffer, " >> var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand2);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              break;
            case SPVM_OPCODE_C_CODE_RIGHT_SHIFT_UNSIGNED_BYTE:
            case SPVM_OPCODE_C_CODE_RIGHT_SHIFT_UNSIGNED_SHORT:
            case SPVM_OPCODE_C_CODE_RIGHT_SHIFT_UNSIGNED_INT:
            case SPVM_OPCODE_C_CODE_RIGHT_SHIFT_UNSIGNED_LONG:
              // TODO
              break;
            case SPVM_OPCODE_C_CODE_BIT_AND_BYTE:
            case SPVM_OPCODE_C_CODE_BIT_AND_SHORT:
            case SPVM_OPCODE_C_CODE_BIT_AND_INT:
            case SPVM_OPCODE_C_CODE_BIT_AND_LONG:
              SPVM_STRING_BUFFER_add(string_buffer, "  var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, " = var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
              SPVM_STRING_BUFFER_add(string_buffer, " & var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand2);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              break;
            case SPVM_OPCODE_C_CODE_BIT_OR_BYTE:
            case SPVM_OPCODE_C_CODE_BIT_OR_SHORT:
            case SPVM_OPCODE_C_CODE_BIT_OR_INT:
            case SPVM_OPCODE_C_CODE_BIT_OR_LONG:
              SPVM_STRING_BUFFER_add(string_buffer, "  var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, " = var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
              SPVM_STRING_BUFFER_add(string_buffer, " | var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand2);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              break;
            case SPVM_OPCODE_C_CODE_BIT_XOR_BYTE:
            case SPVM_OPCODE_C_CODE_BIT_XOR_SHORT:
            case SPVM_OPCODE_C_CODE_BIT_XOR_INT:
            case SPVM_OPCODE_C_CODE_BIT_XOR_LONG:
              SPVM_STRING_BUFFER_add(string_buffer, "  var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, " = var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
              SPVM_STRING_BUFFER_add(string_buffer, " ^ var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand2);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              break;
            case SPVM_OPCODE_C_CODE_NEGATE_BYTE:
            case SPVM_OPCODE_C_CODE_NEGATE_SHORT:
            case SPVM_OPCODE_C_CODE_NEGATE_INT:
            case SPVM_OPCODE_C_CODE_NEGATE_LONG:
            case SPVM_OPCODE_C_CODE_NEGATE_FLOAT:
            case SPVM_OPCODE_C_CODE_NEGATE_DOUBLE:
              SPVM_STRING_BUFFER_add(string_buffer, "  var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, " = -var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              break;
            case SPVM_OPCODE_C_CODE_COMPLEMENT_BYTE:
            case SPVM_OPCODE_C_CODE_COMPLEMENT_SHORT:
            case SPVM_OPCODE_C_CODE_COMPLEMENT_INT:
            case SPVM_OPCODE_C_CODE_COMPLEMENT_LONG:
              SPVM_STRING_BUFFER_add(string_buffer, "  var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, " = ~var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              break;
            case SPVM_OPCODE_C_CODE_RETURN_BYTE:
            case SPVM_OPCODE_C_CODE_RETURN_SHORT:
            case SPVM_OPCODE_C_CODE_RETURN_INT:
            case SPVM_OPCODE_C_CODE_RETURN_LONG:
            case SPVM_OPCODE_C_CODE_RETURN_FLOAT:
            case SPVM_OPCODE_C_CODE_RETURN_DOUBLE:
            case SPVM_OPCODE_C_CODE_RETURN_OBJECT:
            case SPVM_OPCODE_C_CODE_RETURN_VOID:
            case SPVM_OPCODE_C_CODE_CROAK:
              loop_break = 1;
              break;
          }
          if (loop_break) {
            break;
          }
          opcode_index++;
        }
      }

      // Close subroutine
      SPVM_STRING_BUFFER_add(string_buffer, "}\n");
      SPVM_STRING_BUFFER_add(string_buffer, "\n");
    }
  }
  
  warn("%s", string_buffer->buffer);
}
