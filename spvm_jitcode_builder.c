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
  
  // C library
  SPVM_STRING_BUFFER_add(string_buffer, "#include <stdint.h>\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#include <assert.h>\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#include <string.h>\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#include <math.h>\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#include <stdlib.h>\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#include <stdio.h>\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#include <inttypes.h>\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#include <stddef.h>\n");

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
      
      // Block start
      SPVM_STRING_BUFFER_add(string_buffer, ") {\n");
      
      // API
      SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_API* api = ");
      SPVM_STRING_BUFFER_add_address(string_buffer, runtime->api);
      SPVM_STRING_BUFFER_add(string_buffer, ";\n");
      
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
          SPVM_STRING_BUFFER_add(string_buffer, "  (*native_address)(api,");
        }
        else {
          SPVM_STRING_BUFFER_add(string_buffer, "  (*native_address)(api");
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
        SPVM_STRING_BUFFER_add(string_buffer, "  register int32_t condition_flag;\n");

        SPVM_OPCODE* opcodes = runtime->opcodes;
        int32_t opcode_base = constant_pool_sub->opcode_base;
        int32_t opcode_length = constant_pool_sub->opcode_length;
        int32_t opcode_index = opcode_base;
        
        int32_t loop_break = 0;
        while (opcode_index < opcode_base + opcode_length) {

          // Line label
          SPVM_STRING_BUFFER_add(string_buffer, "L");
          SPVM_STRING_BUFFER_add_int(string_buffer, opcode_index);
          SPVM_STRING_BUFFER_add(string_buffer, ":\n");

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
              SPVM_STRING_BUFFER_add(string_buffer, "  // BOOL\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  condition_flag = !!var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              break;
            case SPVM_OPCODE_C_CODE_IS_UNDEF:
              SPVM_STRING_BUFFER_add(string_buffer, "  // IS_UNDEF\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  condition_flag = (var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, " == NULL);\n");
              break;
            case SPVM_OPCODE_C_CODE_IS_NOT_UNDEF:
              SPVM_STRING_BUFFER_add(string_buffer, "  // IS_NOT_UNDEF\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  condition_flag = (var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, " != NULL);\n");
              break;
            case SPVM_OPCODE_C_CODE_EQ_BYTE:
            case SPVM_OPCODE_C_CODE_EQ_SHORT:
            case SPVM_OPCODE_C_CODE_EQ_INT:
            case SPVM_OPCODE_C_CODE_EQ_LONG:
            case SPVM_OPCODE_C_CODE_EQ_FLOAT:
            case SPVM_OPCODE_C_CODE_EQ_DOUBLE:
            case SPVM_OPCODE_C_CODE_EQ_OBJECT:
              SPVM_STRING_BUFFER_add(string_buffer, "  // EQ\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  condition_flag = (var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, " == var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
              SPVM_STRING_BUFFER_add(string_buffer, ");\n");
              break;
            case SPVM_OPCODE_C_CODE_NE_BYTE:
            case SPVM_OPCODE_C_CODE_NE_SHORT:
            case SPVM_OPCODE_C_CODE_NE_INT:
            case SPVM_OPCODE_C_CODE_NE_LONG:
            case SPVM_OPCODE_C_CODE_NE_FLOAT:
            case SPVM_OPCODE_C_CODE_NE_DOUBLE:
            case SPVM_OPCODE_C_CODE_NE_OBJECT:
              SPVM_STRING_BUFFER_add(string_buffer, "  // NE\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  condition_flag = (var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, " != var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
              SPVM_STRING_BUFFER_add(string_buffer, ");\n");
              break;
            case SPVM_OPCODE_C_CODE_GT_BYTE:
            case SPVM_OPCODE_C_CODE_GT_SHORT:
            case SPVM_OPCODE_C_CODE_GT_INT:
            case SPVM_OPCODE_C_CODE_GT_LONG:
            case SPVM_OPCODE_C_CODE_GT_FLOAT:
            case SPVM_OPCODE_C_CODE_GT_DOUBLE:
              SPVM_STRING_BUFFER_add(string_buffer, "  // GT\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  condition_flag = (var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, " > var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
              SPVM_STRING_BUFFER_add(string_buffer, ");\n");
              break;
            case SPVM_OPCODE_C_CODE_GE_BYTE:
            case SPVM_OPCODE_C_CODE_GE_SHORT:
            case SPVM_OPCODE_C_CODE_GE_INT:
            case SPVM_OPCODE_C_CODE_GE_LONG:
            case SPVM_OPCODE_C_CODE_GE_FLOAT:
            case SPVM_OPCODE_C_CODE_GE_DOUBLE:
              SPVM_STRING_BUFFER_add(string_buffer, "  // GE\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  condition_flag = (var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, " <= var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
              SPVM_STRING_BUFFER_add(string_buffer, ");\n");
              break;
            case SPVM_OPCODE_C_CODE_LT_BYTE:
            case SPVM_OPCODE_C_CODE_LT_SHORT:
            case SPVM_OPCODE_C_CODE_LT_INT:
            case SPVM_OPCODE_C_CODE_LT_LONG:
            case SPVM_OPCODE_C_CODE_LT_FLOAT:
            case SPVM_OPCODE_C_CODE_LT_DOUBLE:
              SPVM_STRING_BUFFER_add(string_buffer, "  // LT\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  condition_flag = (var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, " < var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
              SPVM_STRING_BUFFER_add(string_buffer, ");\n");
              break;
            case SPVM_OPCODE_C_CODE_LE_BYTE:
            case SPVM_OPCODE_C_CODE_LE_SHORT:
            case SPVM_OPCODE_C_CODE_LE_INT:
            case SPVM_OPCODE_C_CODE_LE_LONG:
            case SPVM_OPCODE_C_CODE_LE_FLOAT:
            case SPVM_OPCODE_C_CODE_LE_DOUBLE:
              SPVM_STRING_BUFFER_add(string_buffer, "  // LE\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  condition_flag = (var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, " <= var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
              SPVM_STRING_BUFFER_add(string_buffer, ");\n");
              break;
            case SPVM_OPCODE_C_CODE_ADD_BYTE:
            case SPVM_OPCODE_C_CODE_ADD_SHORT:
            case SPVM_OPCODE_C_CODE_ADD_INT:
            case SPVM_OPCODE_C_CODE_ADD_LONG:
            case SPVM_OPCODE_C_CODE_ADD_FLOAT:
            case SPVM_OPCODE_C_CODE_ADD_DOUBLE:
              SPVM_STRING_BUFFER_add(string_buffer, "  // ADD\n");
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
              SPVM_STRING_BUFFER_add(string_buffer, "  // SUBTRACT\n");
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
              SPVM_STRING_BUFFER_add(string_buffer, "  // MULTIPLY\n");
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
            case SPVM_OPCODE_C_CODE_DIVIDE_LONG: {
              SPVM_STRING_BUFFER_add(string_buffer, "  // DIVIDE\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  if (__builtin_expect(var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand2);
              SPVM_STRING_BUFFER_add(string_buffer, " == 0, 0)) { \n");
              SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_API_OBJECT* exception = api->new_string(api, \"0 division\", 0); \n");
              SPVM_STRING_BUFFER_add(string_buffer, "    api->set_exception(api, exception);\n");
              SPVM_STRING_BUFFER_add(string_buffer, "    goto label_SPVM_OPCODE_C_CODE_CROAK;\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  } else { \\\n");
              SPVM_STRING_BUFFER_add(string_buffer, "    \n");
              SPVM_STRING_BUFFER_add(string_buffer, "  var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, " = var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
              SPVM_STRING_BUFFER_add(string_buffer, " / var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand2);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  } \n");
              break;
            }
            case SPVM_OPCODE_C_CODE_DIVIDE_FLOAT:
            case SPVM_OPCODE_C_CODE_DIVIDE_DOUBLE:
              SPVM_STRING_BUFFER_add(string_buffer, "  // DIVIDE\n");
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
              SPVM_STRING_BUFFER_add(string_buffer, "  // REMAINDER\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, " = var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
              SPVM_STRING_BUFFER_add(string_buffer, " % var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand2);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              break;
            case SPVM_OPCODE_C_CODE_REMAINDER_FLOAT:
              SPVM_STRING_BUFFER_add(string_buffer, "  // REMAINDER\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, " = (float)fmod((double)var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
              SPVM_STRING_BUFFER_add(string_buffer, ", (double)var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand2);
              SPVM_STRING_BUFFER_add(string_buffer, ");\n");
              break;
            case SPVM_OPCODE_C_CODE_REMAINDER_DOUBLE:
              SPVM_STRING_BUFFER_add(string_buffer, "  // REMAINDER\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, " = fmod(var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
              SPVM_STRING_BUFFER_add(string_buffer, ", var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand2);
              SPVM_STRING_BUFFER_add(string_buffer, ");\n");
              break;
            case SPVM_OPCODE_C_CODE_LEFT_SHIFT_BYTE:
            case SPVM_OPCODE_C_CODE_LEFT_SHIFT_SHORT:
            case SPVM_OPCODE_C_CODE_LEFT_SHIFT_INT:
            case SPVM_OPCODE_C_CODE_LEFT_SHIFT_LONG:
              SPVM_STRING_BUFFER_add(string_buffer, "  // LEFT_SHIFT\n");
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
              SPVM_STRING_BUFFER_add(string_buffer, "  // RIGHT_SHIFT\n");
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
            {
              char* type = NULL;
              switch (opcode->code) {
                case SPVM_OPCODE_C_CODE_RIGHT_SHIFT_UNSIGNED_BYTE:
                  type = "int8_t";
                  break;
                case SPVM_OPCODE_C_CODE_RIGHT_SHIFT_UNSIGNED_SHORT:
                  type = "int16_t";
                  break;
                case SPVM_OPCODE_C_CODE_RIGHT_SHIFT_UNSIGNED_INT:
                  type = "int32_t";
                  break;
                case SPVM_OPCODE_C_CODE_RIGHT_SHIFT_UNSIGNED_LONG:
                  type = "int64_t";
                  break;
              }
              SPVM_STRING_BUFFER_add(string_buffer, "  // RIGHT_SHIFT_UNSIGNED\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, " = (");
              SPVM_STRING_BUFFER_add(string_buffer, type);
              SPVM_STRING_BUFFER_add(string_buffer, ")((u");
              SPVM_STRING_BUFFER_add(string_buffer, type);
              SPVM_STRING_BUFFER_add(string_buffer, ")var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
              SPVM_STRING_BUFFER_add(string_buffer, " >> var)");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand2);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              break;
            }
            case SPVM_OPCODE_C_CODE_BIT_AND_BYTE:
            case SPVM_OPCODE_C_CODE_BIT_AND_SHORT:
            case SPVM_OPCODE_C_CODE_BIT_AND_INT:
            case SPVM_OPCODE_C_CODE_BIT_AND_LONG:
              SPVM_STRING_BUFFER_add(string_buffer, "  // BIT_AND\n");
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
              SPVM_STRING_BUFFER_add(string_buffer, "  // BIT_OR\n");
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
              SPVM_STRING_BUFFER_add(string_buffer, "  // BIT_XOR\n");
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
              SPVM_STRING_BUFFER_add(string_buffer, "  // NEGATE\n");
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
              SPVM_STRING_BUFFER_add(string_buffer, "  // COMPLEMENT\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, " = ~var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              break;
            case SPVM_OPCODE_C_CODE_INC_BYTE:
            case SPVM_OPCODE_C_CODE_INC_SHORT:
            case SPVM_OPCODE_C_CODE_INC_INT:
            case SPVM_OPCODE_C_CODE_INC_LONG:
              SPVM_STRING_BUFFER_add(string_buffer, "  // INC\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, " += ");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              break;
            case SPVM_OPCODE_C_CODE_CONVERT_BYTE_TO_BYTE:
            case SPVM_OPCODE_C_CODE_CONVERT_SHORT_TO_BYTE:
            case SPVM_OPCODE_C_CODE_CONVERT_INT_TO_BYTE:
            case SPVM_OPCODE_C_CODE_CONVERT_LONG_TO_BYTE:
            case SPVM_OPCODE_C_CODE_CONVERT_FLOAT_TO_BYTE:
            case SPVM_OPCODE_C_CODE_CONVERT_DOUBLE_TO_BYTE:
              SPVM_STRING_BUFFER_add(string_buffer, "  // CONVERT_TO_BYTE\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, " = (int8_t)var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              break;
            case SPVM_OPCODE_C_CODE_CONVERT_BYTE_TO_SHORT:
            case SPVM_OPCODE_C_CODE_CONVERT_SHORT_TO_SHORT:
            case SPVM_OPCODE_C_CODE_CONVERT_INT_TO_SHORT:
            case SPVM_OPCODE_C_CODE_CONVERT_LONG_TO_SHORT:
            case SPVM_OPCODE_C_CODE_CONVERT_FLOAT_TO_SHORT:
            case SPVM_OPCODE_C_CODE_CONVERT_DOUBLE_TO_SHORT:
              SPVM_STRING_BUFFER_add(string_buffer, "  // CONVERT_TO_SHORT\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, " = (int16_t)var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              break;
            case SPVM_OPCODE_C_CODE_CONVERT_BYTE_TO_INT:
            case SPVM_OPCODE_C_CODE_CONVERT_SHORT_TO_INT:
            case SPVM_OPCODE_C_CODE_CONVERT_LONG_TO_INT:
            case SPVM_OPCODE_C_CODE_CONVERT_INT_TO_INT:
            case SPVM_OPCODE_C_CODE_CONVERT_FLOAT_TO_INT:
            case SPVM_OPCODE_C_CODE_CONVERT_DOUBLE_TO_INT:
              SPVM_STRING_BUFFER_add(string_buffer, "  // CONVERT_TO_INT\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, " = (int32_t)var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              break;
            case SPVM_OPCODE_C_CODE_CONVERT_BYTE_TO_LONG:
            case SPVM_OPCODE_C_CODE_CONVERT_SHORT_TO_LONG:
            case SPVM_OPCODE_C_CODE_CONVERT_INT_TO_LONG:
            case SPVM_OPCODE_C_CODE_CONVERT_FLOAT_TO_LONG:
            case SPVM_OPCODE_C_CODE_CONVERT_LONG_TO_LONG:
            case SPVM_OPCODE_C_CODE_CONVERT_DOUBLE_TO_LONG:
              SPVM_STRING_BUFFER_add(string_buffer, "  // CONVERT_TO_LONG\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, " = (int64_t)var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              break;
            case SPVM_OPCODE_C_CODE_CONVERT_BYTE_TO_FLOAT:
            case SPVM_OPCODE_C_CODE_CONVERT_SHORT_TO_FLOAT:
            case SPVM_OPCODE_C_CODE_CONVERT_INT_TO_FLOAT:
            case SPVM_OPCODE_C_CODE_CONVERT_LONG_TO_FLOAT:
            case SPVM_OPCODE_C_CODE_CONVERT_FLOAT_TO_FLOAT:
            case SPVM_OPCODE_C_CODE_CONVERT_DOUBLE_TO_FLOAT:
              SPVM_STRING_BUFFER_add(string_buffer, "  // CONVERT_TO_FLOAT\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, " = (float)var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
            case SPVM_OPCODE_C_CODE_CONVERT_BYTE_TO_DOUBLE:
            case SPVM_OPCODE_C_CODE_CONVERT_SHORT_TO_DOUBLE:
            case SPVM_OPCODE_C_CODE_CONVERT_INT_TO_DOUBLE:
            case SPVM_OPCODE_C_CODE_CONVERT_LONG_TO_DOUBLE:
            case SPVM_OPCODE_C_CODE_CONVERT_DOUBLE_TO_DOUBLE:
            case SPVM_OPCODE_C_CODE_CONVERT_FLOAT_TO_DOUBLE:
              SPVM_STRING_BUFFER_add(string_buffer, "  // CONVERT_TO_DOUBLE\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, " = (double)var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
            case SPVM_OPCODE_C_CODE_LOAD_CONSTANT_0:
            case SPVM_OPCODE_C_CODE_LOAD_CONSTANT2_0:
              SPVM_STRING_BUFFER_add(string_buffer, "  // LOAD_CONSTANT_0\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, " = 0;\n");
              break;
            case SPVM_OPCODE_C_CODE_UNDEF:
              SPVM_STRING_BUFFER_add(string_buffer, "  // UNDEF\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, " = NULL;\n");
              break;
            case SPVM_OPCODE_C_CODE_ARRAY_LOAD_BYTE:
            case SPVM_OPCODE_C_CODE_ARRAY_LOAD_SHORT:
            case SPVM_OPCODE_C_CODE_ARRAY_LOAD_INT:
            case SPVM_OPCODE_C_CODE_ARRAY_LOAD_LONG:
            case SPVM_OPCODE_C_CODE_ARRAY_LOAD_FLOAT:
            case SPVM_OPCODE_C_CODE_ARRAY_LOAD_DOUBLE:
            case SPVM_OPCODE_C_CODE_ARRAY_LOAD_OBJECT:
            {
              SPVM_STRING_BUFFER_add(string_buffer, "  // ARRAY_LOAD\n");
              
              char* element_type = NULL;
              switch (opcode->code) {
                case SPVM_OPCODE_C_CODE_ARRAY_LOAD_BYTE:
                  element_type = "int8_t";
                  break;
                case SPVM_OPCODE_C_CODE_ARRAY_LOAD_SHORT:
                  element_type = "int16_t";
                  break;
                case SPVM_OPCODE_C_CODE_ARRAY_LOAD_INT:
                  element_type = "int32_t";
                  break;
                case SPVM_OPCODE_C_CODE_ARRAY_LOAD_LONG:
                  element_type = "int64_t";
                  break;
                case SPVM_OPCODE_C_CODE_ARRAY_LOAD_FLOAT:
                  element_type = "float";
                  break;
                case SPVM_OPCODE_C_CODE_ARRAY_LOAD_DOUBLE:
                  element_type = "double";
                  break;
                case SPVM_OPCODE_C_CODE_ARRAY_LOAD_OBJECT:
                  element_type = "SPVM_API_OBJECT*";
              }
              
              SPVM_STRING_BUFFER_add(string_buffer, "  { \n");
              SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_API_OBJECT* array = var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
              SPVM_STRING_BUFFER_add(string_buffer, "; \n");
              SPVM_STRING_BUFFER_add(string_buffer, "    int32_t index = var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand2);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              SPVM_STRING_BUFFER_add(string_buffer, "    if (__builtin_expect(array == NULL, 0)) { \n");
              SPVM_STRING_BUFFER_add(string_buffer, "      SPVM_API_OBJECT* exception = api->new_string(api, \"Array must not be undef\", 0); \n");
              SPVM_STRING_BUFFER_add(string_buffer, "      api->set_exception(api, exception); \n");
              SPVM_STRING_BUFFER_add(string_buffer, "      goto label_SPVM_OPCODE_C_CODE_CROAK; \n");
              SPVM_STRING_BUFFER_add(string_buffer, "    } \n");
              SPVM_STRING_BUFFER_add(string_buffer, "    else { \n");
              SPVM_STRING_BUFFER_add(string_buffer, "      if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + SPVM_INFO_OBJECT_LENGTH_BYTE_OFFSET), 0)) { \n");
              SPVM_STRING_BUFFER_add(string_buffer, "        SPVM_API_OBJECT* exception = api->new_string(api, \"Index is out of range\", 0); \n");
              SPVM_STRING_BUFFER_add(string_buffer, "        api->set_exception(api, exception); \n");
              SPVM_STRING_BUFFER_add(string_buffer, "        goto label_SPVM_OPCODE_C_CODE_CROAK; \n");
              SPVM_STRING_BUFFER_add(string_buffer, "      } \n");
              SPVM_STRING_BUFFER_add(string_buffer, "      else { \n");
              SPVM_STRING_BUFFER_add(string_buffer, "        var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, " = *(");
              SPVM_STRING_BUFFER_add(string_buffer, element_type);
              SPVM_STRING_BUFFER_add(string_buffer, "*)((intptr_t)array + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + sizeof(");
              SPVM_STRING_BUFFER_add(string_buffer, element_type);
              SPVM_STRING_BUFFER_add(string_buffer, ") * index); \n");
              SPVM_STRING_BUFFER_add(string_buffer, "      } \n");
              SPVM_STRING_BUFFER_add(string_buffer, "    } \n");
              SPVM_STRING_BUFFER_add(string_buffer, "  } \n");
              break;
            }
            case SPVM_OPCODE_C_CODE_ARRAY_STORE_BYTE:
            case SPVM_OPCODE_C_CODE_ARRAY_STORE_SHORT:
            case SPVM_OPCODE_C_CODE_ARRAY_STORE_INT:
            case SPVM_OPCODE_C_CODE_ARRAY_STORE_LONG:
            case SPVM_OPCODE_C_CODE_ARRAY_STORE_FLOAT:
            case SPVM_OPCODE_C_CODE_ARRAY_STORE_DOUBLE:
            case SPVM_OPCODE_C_CODE_ARRAY_STORE_OBJECT:
            {
              SPVM_STRING_BUFFER_add(string_buffer, "  // ARRAY_STORE\n");

              char* element_type = NULL;
              switch (opcode->code) {
                case SPVM_OPCODE_C_CODE_ARRAY_STORE_BYTE:
                  element_type = "int8_t";
                  break;
                case SPVM_OPCODE_C_CODE_ARRAY_STORE_SHORT:
                  element_type = "int16_t";
                  break;
                case SPVM_OPCODE_C_CODE_ARRAY_STORE_INT:
                  element_type = "int32_t";
                  break;
                case SPVM_OPCODE_C_CODE_ARRAY_STORE_LONG:
                  element_type = "int64_t";
                  break;
                case SPVM_OPCODE_C_CODE_ARRAY_STORE_FLOAT:
                  element_type = "float";
                  break;
                case SPVM_OPCODE_C_CODE_ARRAY_STORE_DOUBLE:
                  element_type = "double";
                  break;
                case SPVM_OPCODE_C_CODE_ARRAY_STORE_OBJECT:
                  element_type = "SPVM_API_OBJECT*";
              }
              
              SPVM_STRING_BUFFER_add(string_buffer, "  { \n");
              SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_API_OBJECT* array = var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              SPVM_STRING_BUFFER_add(string_buffer, "    int32_t index = var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              SPVM_STRING_BUFFER_add(string_buffer, "    if (__builtin_expect(array == NULL, 0)) { \n");
              SPVM_STRING_BUFFER_add(string_buffer, "      SPVM_API_OBJECT* exception = api->new_string(api, \"Array must not be undef\", 0); \n");
              SPVM_STRING_BUFFER_add(string_buffer, "      api->set_exception(api, exception); \n");
              SPVM_STRING_BUFFER_add(string_buffer, "      goto label_SPVM_OPCODE_C_CODE_CROAK; \n");
              SPVM_STRING_BUFFER_add(string_buffer, "    } \n");
              SPVM_STRING_BUFFER_add(string_buffer, "    else { \n");
              SPVM_STRING_BUFFER_add(string_buffer, "      if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + SPVM_INFO_OBJECT_LENGTH_BYTE_OFFSET), 0)) { \n");
              SPVM_STRING_BUFFER_add(string_buffer, "        SPVM_API_OBJECT* exception = api->new_string(api, \"Index is out of range\", 0); \n");
              SPVM_STRING_BUFFER_add(string_buffer, "        api->set_exception(api, exception); \n");
              SPVM_STRING_BUFFER_add(string_buffer, "        goto label_SPVM_OPCODE_C_CODE_CROAK; \n");
              SPVM_STRING_BUFFER_add(string_buffer, "      } \n");
              SPVM_STRING_BUFFER_add(string_buffer, "      else { \n");
              
              if (opcode->code == SPVM_OPCODE_C_CODE_ARRAY_STORE_OBJECT) {
                SPVM_STRING_BUFFER_add(string_buffer, "        SPVM_API_OBJECT** object_address = (SPVM_API_OBJECT**)((intptr_t)array + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + sizeof(void*) * index\n");
                SPVM_STRING_BUFFER_add(string_buffer, "        if (*object_address != NULL) {\n");
                SPVM_STRING_BUFFER_add(string_buffer, "          if (SPVM_INLINE_GET_REF_COUNT(*object_address) > 1) {\n");
                SPVM_STRING_BUFFER_add(string_buffer, "            SPVM_INLINE_DEC_REF_COUNT_ONLY(*object_address);\n");
                SPVM_STRING_BUFFER_add(string_buffer, "          }\n");
                SPVM_STRING_BUFFER_add(string_buffer, "          else {\n");
                SPVM_STRING_BUFFER_add(string_buffer, "            api->dec_ref_count(api, *object_address);\n");
                SPVM_STRING_BUFFER_add(string_buffer, "          }\n");
                SPVM_STRING_BUFFER_add(string_buffer, "        }\n");
                
                SPVM_STRING_BUFFER_add(string_buffer, "        *object_address = var");
                SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand2);
                SPVM_STRING_BUFFER_add(string_buffer, ";\n");
                

                SPVM_STRING_BUFFER_add(string_buffer, "        if (*object_address != NULL) {\n");
                SPVM_STRING_BUFFER_add(string_buffer, "          SPVM_INLINE_INC_REF_COUNT(*object_address);\n");
                SPVM_STRING_BUFFER_add(string_buffer, "        }\n");
              }
              else {
                SPVM_STRING_BUFFER_add(string_buffer, "        *(");
                SPVM_STRING_BUFFER_add(string_buffer, element_type);
                SPVM_STRING_BUFFER_add(string_buffer, "*)((intptr_t)array + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + sizeof(");
                SPVM_STRING_BUFFER_add(string_buffer, element_type);
                SPVM_STRING_BUFFER_add(string_buffer, ") * index) = var");
                SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand2);
                SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              }

              SPVM_STRING_BUFFER_add(string_buffer, "      } \n");
              SPVM_STRING_BUFFER_add(string_buffer, "    } \n");
              SPVM_STRING_BUFFER_add(string_buffer, "  } \n");
              
              break;
            }
            case SPVM_OPCODE_C_CODE_MOVE:
              SPVM_STRING_BUFFER_add(string_buffer, "  // MOVE\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, " = var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              break;
            case SPVM_OPCODE_C_CODE_INC_REF_COUNT: {
              SPVM_STRING_BUFFER_add(string_buffer, "  // INC_REF_COUNT\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  if (var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, " != NULL) {\n");
              SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_INLINE_INC_REF_COUNT(var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, ");\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
              
              break;
            }
            case SPVM_OPCODE_C_CODE_DEC_REF_COUNT: {
              SPVM_STRING_BUFFER_add(string_buffer, "  // DEC_REF_COUNT\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  if (var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, " != NULL) {\n");
              SPVM_STRING_BUFFER_add(string_buffer, "    if (SPVM_INLINE_GET_REF_COUNT(var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, ") > 1) {\n");
              SPVM_STRING_BUFFER_add(string_buffer, "      SPVM_INLINE_DEC_REF_COUNT_ONLY(var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, ");\n");
              SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
              SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
              SPVM_STRING_BUFFER_add(string_buffer, "      api->dec_ref_count(api, var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, ");\n");
              SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
              break;
            }
            case SPVM_OPCODE_C_CODE_NEW_OBJECT: {
              SPVM_STRING_BUFFER_add(string_buffer, "  // NEW_OBJECT\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
              SPVM_STRING_BUFFER_add(string_buffer, "    int32_t type_id = ");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_API_OBJECT* object = api->new_object(api, type_id);\n");
              SPVM_STRING_BUFFER_add(string_buffer, "    var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, " = object;\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
              break;
            }
            case SPVM_OPCODE_C_CODE_NEW_BYTE_ARRAY:
            case SPVM_OPCODE_C_CODE_NEW_SHORT_ARRAY:
            case SPVM_OPCODE_C_CODE_NEW_INT_ARRAY:
            case SPVM_OPCODE_C_CODE_NEW_LONG_ARRAY:
            case SPVM_OPCODE_C_CODE_NEW_FLOAT_ARRAY:
            case SPVM_OPCODE_C_CODE_NEW_DOUBLE_ARRAY:
            {
              SPVM_STRING_BUFFER_add(string_buffer, "  // NEW_NUMERIC_ARRAY\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
              SPVM_STRING_BUFFER_add(string_buffer, "    int32_t length = var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              switch (opcode->code) {
                case SPVM_OPCODE_C_CODE_NEW_BYTE_ARRAY:
                  SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_API_OBJECT* object = api->new_byte_array(api, length);\n");
                  break;
                case SPVM_OPCODE_C_CODE_NEW_SHORT_ARRAY:
                  SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_API_OBJECT* object = api->new_short_array(api, length);\n");
                  break;
                case SPVM_OPCODE_C_CODE_NEW_INT_ARRAY:
                  SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_API_OBJECT* object = api->new_int_array(api, length);\n");
                  break;
                case SPVM_OPCODE_C_CODE_NEW_LONG_ARRAY:
                  SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_API_OBJECT* object = api->new_long_array(api, length);\n");
                  break;
                case SPVM_OPCODE_C_CODE_NEW_FLOAT_ARRAY:
                  SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_API_OBJECT* object = api->new_float_array(api, length);\n");
                  break;
                case SPVM_OPCODE_C_CODE_NEW_DOUBLE_ARRAY:
                  SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_API_OBJECT* object = api->new_double_array(api, length);\n");
                  break;
              }
              SPVM_STRING_BUFFER_add(string_buffer, "    var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, " = object;\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
              break;
            }
            case SPVM_OPCODE_C_CODE_NEW_OBJECT_ARRAY: {
              SPVM_STRING_BUFFER_add(string_buffer, "  // NEW_OBJECT_ARRAY\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  int32_t element_type_id = ");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
              SPVM_STRING_BUFFER_add(string_buffer, "  ;\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  int32_t length = var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand2);
              SPVM_STRING_BUFFER_add(string_buffer, "  ;\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_API_OBJECT* object = api->new_object_array(api, element_type_id, length);\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, "   = object;\n");
              break;
            }
            case SPVM_OPCODE_C_CODE_NEW_STRING: {
              int32_t name_id = opcode->operand1;
              int32_t length = constant_pool[name_id];
              char* name = (char*)&constant_pool[name_id + 1];
              
              SPVM_STRING_BUFFER_add(string_buffer, "  // NEW_STRING\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
              SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_API_OBJECT* string = api->new_string(api, ");
              SPVM_STRING_BUFFER_add_address(string_buffer, name);
              SPVM_STRING_BUFFER_add(string_buffer, ", ");
              SPVM_STRING_BUFFER_add_int(string_buffer, length);
              SPVM_STRING_BUFFER_add(string_buffer, ");\n");
              SPVM_STRING_BUFFER_add(string_buffer, "    var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, " = string;\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
              break;
            }
            case SPVM_OPCODE_C_CODE_ARRAY_LENGTH: {
              SPVM_STRING_BUFFER_add(string_buffer, "  // ARRAY_LENGTH");
              SPVM_STRING_BUFFER_add(string_buffer, "  if (var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
              SPVM_STRING_BUFFER_add(string_buffer, " == NULL) {\n");
              SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_API_OBJECT* exception = api->new_string(api, \"Can't get array length of undef value.\", 0);\n");
              SPVM_STRING_BUFFER_add(string_buffer, "    api->set_exception(api, exception);\n");
              SPVM_STRING_BUFFER_add(string_buffer, "    goto label_SPVM_OPCODE_C_CODE_CROAK;\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  else {\n");
              SPVM_STRING_BUFFER_add(string_buffer, "    var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, " = *(int32_t*)((intptr_t)var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
              SPVM_STRING_BUFFER_add(string_buffer, " + SPVM_INFO_OBJECT_LENGTH_BYTE_OFFSET);\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
              break;
            }
            case SPVM_OPCODE_C_CODE_GET_FIELD_BYTE:
            case SPVM_OPCODE_C_CODE_GET_FIELD_SHORT:
            case SPVM_OPCODE_C_CODE_GET_FIELD_INT:
            case SPVM_OPCODE_C_CODE_GET_FIELD_LONG:
            case SPVM_OPCODE_C_CODE_GET_FIELD_FLOAT:
            case SPVM_OPCODE_C_CODE_GET_FIELD_DOUBLE:
            case SPVM_OPCODE_C_CODE_GET_FIELD_OBJECT:
            {
              char* field_type = NULL;
              switch (opcode->code) {
                case SPVM_OPCODE_C_CODE_GET_FIELD_BYTE:
                  field_type = "int8_t";
                  break;
                case SPVM_OPCODE_C_CODE_GET_FIELD_SHORT:
                  field_type = "int16_t";
                  break;
                case SPVM_OPCODE_C_CODE_GET_FIELD_INT:
                  field_type = "int32_t";
                  break;
                case SPVM_OPCODE_C_CODE_GET_FIELD_LONG:
                  field_type = "int64_t";
                  break;
                case SPVM_OPCODE_C_CODE_GET_FIELD_FLOAT:
                  field_type = "float";
                  break;
                case SPVM_OPCODE_C_CODE_GET_FIELD_DOUBLE:
                  field_type = "double";
                  break;
                case SPVM_OPCODE_C_CODE_GET_FIELD_OBJECT:
                  field_type = "SPVM_API_OBJECT*";
              }
              
              int32_t field_id = opcode->operand2;
              SPVM_CONSTANT_POOL_FIELD* constant_pool_field = (SPVM_CONSTANT_POOL_FIELD*)&constant_pool[field_id];
              int32_t field_byte_offset = constant_pool_field->byte_offset;
              
              SPVM_STRING_BUFFER_add(string_buffer, "  // GET_FIELD\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_API_OBJECT* object = var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
              SPVM_STRING_BUFFER_add(string_buffer, "  ;\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  if (__builtin_expect(object == NULL, 0)) {\n");
              SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_API_OBJECT* exception = api->new_string(api, \"Object must be not undef.\", 0);\n");
              SPVM_STRING_BUFFER_add(string_buffer, "    api->set_exception(api, exception);\n");
              SPVM_STRING_BUFFER_add(string_buffer, "    goto label_SPVM_OPCODE_C_CODE_CROAK;\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  else {\n");
              SPVM_STRING_BUFFER_add(string_buffer, "    var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, " = *(");
              SPVM_STRING_BUFFER_add(string_buffer, field_type);
              SPVM_STRING_BUFFER_add(string_buffer, "*)((intptr_t)object + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + ");
              SPVM_STRING_BUFFER_add_int(string_buffer, field_byte_offset);
              SPVM_STRING_BUFFER_add(string_buffer, ");\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
              
              break;
            }
            case SPVM_OPCODE_C_CODE_SET_FIELD_BYTE:
            case SPVM_OPCODE_C_CODE_SET_FIELD_SHORT:
            case SPVM_OPCODE_C_CODE_SET_FIELD_INT:
            case SPVM_OPCODE_C_CODE_SET_FIELD_LONG:
            case SPVM_OPCODE_C_CODE_SET_FIELD_FLOAT:
            case SPVM_OPCODE_C_CODE_SET_FIELD_DOUBLE:
            {
              int32_t field_id = opcode->operand1;
              SPVM_CONSTANT_POOL_FIELD* constant_pool_field = (SPVM_CONSTANT_POOL_FIELD*)&constant_pool[field_id];
              int32_t field_byte_offset = constant_pool_field->byte_offset;
              
              SPVM_STRING_BUFFER_add(string_buffer, "  // SET_FIELD\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_API_OBJECT* object = var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, "  ;\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  if (__builtin_expect(object == NULL, 0)) {\n");
              SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_API_OBJECT* exception = api->new_string(api, \"Object must be not undef.\", 0);\n");
              SPVM_STRING_BUFFER_add(string_buffer, "    api->set_exception(api, exception);\n");
              SPVM_STRING_BUFFER_add(string_buffer, "    goto label_SPVM_OPCODE_C_CODE_CROAK;\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  else {\n");
              if (opcode->code == SPVM_OPCODE_C_CODE_SET_FIELD_OBJECT) {
                SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_API_OBJECT** field_address = (SPVM_API_OBJECT**)((intptr_t)object + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + field_byte_offset);\n");
                SPVM_STRING_BUFFER_add(string_buffer, "    if(*field_address != NULL) {\n");
                SPVM_STRING_BUFFER_add(string_buffer, "      if (SPVM_INLINE_ISWEAK(*field_address)) {\n");
                SPVM_STRING_BUFFER_add(string_buffer, "        api->unweaken(api, field_address);\n");
                SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
                SPVM_STRING_BUFFER_add(string_buffer, "      if (SPVM_INLINE_GET_REF_COUNT(*field_address) > 1) {\n");
                SPVM_STRING_BUFFER_add(string_buffer, "        SPVM_INLINE_DEC_REF_COUNT_ONLY(*field_address);\n");
                SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
                SPVM_STRING_BUFFER_add(string_buffer, "      else {\n");
                SPVM_STRING_BUFFER_add(string_buffer, "        api->dec_ref_count(api, *field_address);\n");
                SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
                SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
                SPVM_STRING_BUFFER_add(string_buffer, "    *field_address = var\n");
                SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand2);
                SPVM_STRING_BUFFER_add(string_buffer, "    ;\n");
                SPVM_STRING_BUFFER_add(string_buffer, "    if(*field_address != NULL) {\n");
                SPVM_STRING_BUFFER_add(string_buffer, "      SPVM_INLINE_INC_REF_COUNT(*field_address);\n");
                SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
              }
              else {
                char* field_type = NULL;
                switch (opcode->code) {
                  case SPVM_OPCODE_C_CODE_SET_FIELD_BYTE:
                    field_type = "int8_t";
                    break;
                  case SPVM_OPCODE_C_CODE_SET_FIELD_SHORT:
                    field_type = "int16_t";
                    break;
                  case SPVM_OPCODE_C_CODE_SET_FIELD_INT:
                    field_type = "int32_t";
                    break;
                  case SPVM_OPCODE_C_CODE_SET_FIELD_LONG:
                    field_type = "int64_t";
                    break;
                  case SPVM_OPCODE_C_CODE_SET_FIELD_FLOAT:
                    field_type = "float";
                    break;
                  case SPVM_OPCODE_C_CODE_SET_FIELD_DOUBLE:
                    field_type = "double";
                    break;
                }
                SPVM_STRING_BUFFER_add(string_buffer, "    *(");
                SPVM_STRING_BUFFER_add(string_buffer, field_type);
                SPVM_STRING_BUFFER_add(string_buffer, "*)((intptr_t)object + SPVM_INFO_OBJECT_HEADER_BYTE_SIZE + ");
                SPVM_STRING_BUFFER_add_int(string_buffer, field_byte_offset);
                SPVM_STRING_BUFFER_add(string_buffer, ") = ");
                SPVM_STRING_BUFFER_add(string_buffer, "var");
                SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand2);
                SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              }
              SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
              
              break;
            }
            case SPVM_OPCODE_C_CODE_WEAKEN_FIELD_OBJECT: {
              int32_t field_id = opcode->operand1;
              
              SPVM_STRING_BUFFER_add(string_buffer, "  // WEAKEN_FIELD_OBJECT\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_API_OBJECT* object = vars[opcode->operand0].object_value;\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  api->weaken_object_field(api, object, field_id);\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  if (SPVM_INLINE_GET_EXCEPTION()) {\n");
              SPVM_STRING_BUFFER_add(string_buffer, "    goto label_SPVM_OPCODE_C_CODE_CROAK;\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
              break;
            }
            case SPVM_OPCODE_C_CODE_CONCAT_STRING_STRING:
            case SPVM_OPCODE_C_CODE_CONCAT_STRING_BYTE:
            case SPVM_OPCODE_C_CODE_CONCAT_STRING_SHORT:
            case SPVM_OPCODE_C_CODE_CONCAT_STRING_INT:
            case SPVM_OPCODE_C_CODE_CONCAT_STRING_LONG:
            case SPVM_OPCODE_C_CODE_CONCAT_STRING_FLOAT:
            case SPVM_OPCODE_C_CODE_CONCAT_STRING_DOUBLE:
            {
              SPVM_STRING_BUFFER_add(string_buffer, "  // CONCAT_STRING\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
              
              switch (opcode->code) {
                case SPVM_OPCODE_C_CODE_CONCAT_STRING_STRING:
                  SPVM_STRING_BUFFER_add(string_buffer, " = api->concat_string_string(api, var");
                  break;
                case SPVM_OPCODE_C_CODE_CONCAT_STRING_BYTE:
                  SPVM_STRING_BUFFER_add(string_buffer, " = api->concat_string_byte(api, var");
                  break;
                case SPVM_OPCODE_C_CODE_CONCAT_STRING_SHORT:
                  SPVM_STRING_BUFFER_add(string_buffer, " = api->concat_string_short(api, var");
                  break;
                case SPVM_OPCODE_C_CODE_CONCAT_STRING_INT:
                  SPVM_STRING_BUFFER_add(string_buffer, " = api->concat_string_int(api, var");
                  break;
                case SPVM_OPCODE_C_CODE_CONCAT_STRING_LONG:
                  SPVM_STRING_BUFFER_add(string_buffer, " = api->concat_string_long(api, var");
                  break;
                case SPVM_OPCODE_C_CODE_CONCAT_STRING_FLOAT:
                  SPVM_STRING_BUFFER_add(string_buffer, " = api->concat_string_float(api, var");
                  break;
                case SPVM_OPCODE_C_CODE_CONCAT_STRING_DOUBLE:
                  SPVM_STRING_BUFFER_add(string_buffer, " = api->concat_string_double(api, var");
                  break;
              }
              
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
              SPVM_STRING_BUFFER_add(string_buffer, ", var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand2);
              SPVM_STRING_BUFFER_add(string_buffer, ");\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  if (var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, " == NULL) {\n");
              SPVM_STRING_BUFFER_add(string_buffer, "    goto label_SPVM_OPCODE_C_CODE_CROAK;\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
              
              break;
            }
            case SPVM_OPCODE_C_CODE_GOTO: {
              SPVM_STRING_BUFFER_add(string_buffer, "  // GOTO\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  goto L");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode_index + opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              break;
            }
            case SPVM_OPCODE_C_CODE_IF_EQ_ZERO: {
              SPVM_STRING_BUFFER_add(string_buffer, "  // IF_EQ_ZERO\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  if (condition_flag == 0) {\n");
              SPVM_STRING_BUFFER_add(string_buffer, "    goto L");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode_index + opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
              break;
            }
            case SPVM_OPCODE_C_CODE_IF_NE_ZERO: {
              SPVM_STRING_BUFFER_add(string_buffer, "  // IF_NE_ZERO\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  if (condition_flag) {\n");
              SPVM_STRING_BUFFER_add(string_buffer, "    goto L");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode_index + opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, ";");
              SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
              break;
            }
            case SPVM_OPCODE_C_CODE_PUSH_EVAL: {
              SPVM_STRING_BUFFER_add(string_buffer, "  // PUSH_EVAL\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  int16_t jump_offset_abs = \n");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  eval_stack_top++;\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  eval_stack[eval_stack_top] = jump_offset_abs;\n");
              break;
            }
            case SPVM_OPCODE_C_CODE_POP_EVAL: {
              SPVM_STRING_BUFFER_add(string_buffer, "  // POP_EVAL\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  eval_stack_top--;\n");
              break;
            }
            case SPVM_OPCODE_C_CODE_LOAD_EXCEPTION_VAR: {
              SPVM_STRING_BUFFER_add(string_buffer, "  // LOAD_EXCEPTION_VAR\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, "   = SPVM_INLINE_GET_EXCEPTION();\n");
              break;
            }
            case SPVM_OPCODE_C_CODE_STORE_EXCEPTION_VAR: {
              SPVM_STRING_BUFFER_add(string_buffer, "  // STORE_EXCEPTION_VAR\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  api->set_exception(api, var\n");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, ");\n");
              break;
            }
            case SPVM_OPCODE_C_CODE_LOAD_PACKAGE_VAR_BYTE:
            case SPVM_OPCODE_C_CODE_LOAD_PACKAGE_VAR_SHORT:
            case SPVM_OPCODE_C_CODE_LOAD_PACKAGE_VAR_INT:
            case SPVM_OPCODE_C_CODE_LOAD_PACKAGE_VAR_LONG:
            case SPVM_OPCODE_C_CODE_LOAD_PACKAGE_VAR_FLOAT:
            case SPVM_OPCODE_C_CODE_LOAD_PACKAGE_VAR_DOUBLE:
            case SPVM_OPCODE_C_CODE_LOAD_PACKAGE_VAR_OBJECT:
            {
              char* package_var_type = NULL;
              switch (opcode->code) {
                case SPVM_OPCODE_C_CODE_LOAD_PACKAGE_VAR_BYTE:
                  package_var_type = "int8_t";
                  break;
                case SPVM_OPCODE_C_CODE_LOAD_PACKAGE_VAR_SHORT:
                  package_var_type = "int16_t";
                  break;
                case SPVM_OPCODE_C_CODE_LOAD_PACKAGE_VAR_INT:
                  package_var_type = "int32_t";
                  break;
                case SPVM_OPCODE_C_CODE_LOAD_PACKAGE_VAR_LONG:
                  package_var_type = "int64_t";
                  break;
                case SPVM_OPCODE_C_CODE_LOAD_PACKAGE_VAR_FLOAT:
                  package_var_type = "float";
                  break;
                case SPVM_OPCODE_C_CODE_LOAD_PACKAGE_VAR_DOUBLE:
                  package_var_type = "double";
                  break;
                case SPVM_OPCODE_C_CODE_LOAD_PACKAGE_VAR_OBJECT:
                  package_var_type = "SPVM_API_OBJECT*";
              }
              
              /*
              SPVM_API_VALUE* package_vars = runtime->package_vars;
              
              SPVM_STRING_BUFFER_add(string_buffer, "  int32_t package_var_id = 
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
              SPVM_STRING_BUFFER_add(string_buffer, "\n;
              SPVM_STRING_BUFFER_add(string_buffer, "  var
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
              SPVM_STRING_BUFFER_add(string_buffer, "   = package_vars[package_var_id].byte_value;\n");
              */
              
              break;
            }
            case SPVM_OPCODE_C_CODE_RETURN_BYTE:
            case SPVM_OPCODE_C_CODE_RETURN_SHORT:
            case SPVM_OPCODE_C_CODE_RETURN_INT:
            case SPVM_OPCODE_C_CODE_RETURN_LONG:
            case SPVM_OPCODE_C_CODE_RETURN_FLOAT:
            case SPVM_OPCODE_C_CODE_RETURN_DOUBLE:
            case SPVM_OPCODE_C_CODE_RETURN_OBJECT:
            case SPVM_OPCODE_C_CODE_RETURN_VOID:
            case SPVM_OPCODE_C_CODE_CROAK:
              SPVM_STRING_BUFFER_add(string_buffer, "  // RETURN\n");
              break;
            case SPVM_OPCODE_C_CODE_TABLE_SWITCH:
            case SPVM_OPCODE_C_CODE_LOOKUP_SWITCH:
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
  
  // warn("%s", string_buffer->buffer);
}
