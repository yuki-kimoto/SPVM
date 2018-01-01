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

void SPVM_JITCODE_BUILDER_add_string_buffer_croak(SPVM_STRING_BUFFER* string_buffer, int32_t sub_opcode_base, int32_t* eval_stack, int32_t* eval_stack_top) {
  
  // Catch exception
  if (eval_stack_top > -1) {
    int32_t jump_offset_abs = eval_stack[*eval_stack_top];
    *eval_stack_top--;
    int32_t jump_line = sub_opcode_base + jump_offset_abs;
    
    SPVM_STRING_BUFFER_add(string_buffer, "      goto L");
    SPVM_STRING_BUFFER_add_int(string_buffer, jump_line);
    SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  }
  // Throw exception
  else {
    SPVM_STRING_BUFFER_add(string_buffer, "      throw_exception = 1;\n");
    SPVM_STRING_BUFFER_add(string_buffer, "      return_value = 0;\n");
    SPVM_STRING_BUFFER_add(string_buffer, "      goto label_SPVM_OPCODE_C_CODE_RETURN;\n");
  }
}

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

      // Is void
      int32_t sub_is_void = constant_pool_sub->is_void;

      // Subroutine object args length
      int32_t sub_object_args_length = constant_pool_sub->object_args_length;

      // Subroutine object args length
      int32_t sub_object_args_base = constant_pool_sub->object_args_base;

      // Subroutine object my base index
      int32_t sub_object_mys_base = constant_pool_sub->object_mys_base;

      // Subroutine object my length
      int32_t sub_object_mys_length = constant_pool_sub->object_mys_length;
      
      // Return type code
      int32_t return_type_id = constant_pool_sub->return_type_id;
      SPVM_CONSTANT_POOL_TYPE* return_type = (SPVM_CONSTANT_POOL_TYPE*)&constant_pool[return_type_id];
      int32_t return_type_code = return_type->code;
      
      // Mys length
      int32_t mys_length = constant_pool_sub->mys_length;
      
      // My type ids base
      int32_t my_type_ids_base = constant_pool_sub->my_type_ids_base;
      
      // Call subroutine argument stack top
      int32_t call_sub_arg_stack_top = -1;
      
      // Call subroutine argument stack
      SPVM_API_VALUE call_sub_arg_stack[255];

      // Eval stack
      int32_t eval_stack[255];
      
      // Eval stack top
      int32_t eval_stack_top = -1;
      
      // Opcode base
      int32_t sub_opcode_base = constant_pool_sub->opcode_base;
      
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

      // Current line
      if (runtime->debug) {
        SPVM_STRING_BUFFER_add(string_buffer, "  int32_t current_line = 0;\n");
      }
      
      // Native subroutine
      if (constant_pool_sub->is_native) {
        // Set exception to NULL
        SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_JITCODE_INLINE_SET_EXCEPTION_NULL();\n");
        SPVM_STRING_BUFFER_add(string_buffer, "\n");

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
      }
      // Normal subroutine
      else {
        // Condition flag
        SPVM_STRING_BUFFER_add(string_buffer, "  register int32_t condition_flag;\n");

        SPVM_OPCODE* opcodes = runtime->opcodes;
        int32_t opcode_base = constant_pool_sub->opcode_base;
        int32_t opcode_length = constant_pool_sub->opcode_length;
        int32_t opcode_index = opcode_base;
        
        SPVM_OPCODE* opcode;
        while (opcode_index < opcode_base + opcode_length) {

          // Line label
          SPVM_STRING_BUFFER_add(string_buffer, "L");
          SPVM_STRING_BUFFER_add_int(string_buffer, opcode_index);
          SPVM_STRING_BUFFER_add(string_buffer, ":\n");

          opcode = &(opcodes[opcode_index]);
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
              
              SPVM_JITCODE_BUILDER_add_string_buffer_croak(string_buffer, sub_opcode_base, eval_stack, &eval_stack_top);
              
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
            case SPVM_OPCODE_C_CODE_LOAD_CONSTANT_BYTE_0:
            case SPVM_OPCODE_C_CODE_LOAD_CONSTANT_SHORT_0:
            case SPVM_OPCODE_C_CODE_LOAD_CONSTANT_INT_0:
            case SPVM_OPCODE_C_CODE_LOAD_CONSTANT_LONG_0:
            case SPVM_OPCODE_C_CODE_LOAD_CONSTANT_FLOAT_0:
            case SPVM_OPCODE_C_CODE_LOAD_CONSTANT_DOUBLE_0: {
              SPVM_STRING_BUFFER_add(string_buffer, "  // LOAD_CONSTANT_0\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
              switch (opcode->code) {
                case SPVM_OPCODE_C_CODE_LOAD_CONSTANT_BYTE_0:
                  SPVM_STRING_BUFFER_add(string_buffer, " = (int8_t)");
                  break;
                case SPVM_OPCODE_C_CODE_LOAD_CONSTANT_SHORT_0:
                  SPVM_STRING_BUFFER_add(string_buffer, " = (int16_t)");
                  break;
                case SPVM_OPCODE_C_CODE_LOAD_CONSTANT_INT_0:
                  SPVM_STRING_BUFFER_add(string_buffer, " = (int32_t)");
                  break;
                case SPVM_OPCODE_C_CODE_LOAD_CONSTANT_LONG_0:
                  SPVM_STRING_BUFFER_add(string_buffer, " = (int64_t)");
                  break;
                case SPVM_OPCODE_C_CODE_LOAD_CONSTANT_FLOAT_0:
                  SPVM_STRING_BUFFER_add(string_buffer, " = (float)");
                  break;
                case SPVM_OPCODE_C_CODE_LOAD_CONSTANT_DOUBLE_0:
                  SPVM_STRING_BUFFER_add(string_buffer, " = (double)");
                  break;
              }
              SPVM_STRING_BUFFER_add(string_buffer, "0;\n");
              break;
            }
            case SPVM_OPCODE_C_CODE_LOAD_CONSTANT_BYTE:
            case SPVM_OPCODE_C_CODE_LOAD_CONSTANT_SHORT:
            case SPVM_OPCODE_C_CODE_LOAD_CONSTANT_INT:
            case SPVM_OPCODE_C_CODE_LOAD_CONSTANT_LONG:
            case SPVM_OPCODE_C_CODE_LOAD_CONSTANT_FLOAT:
            case SPVM_OPCODE_C_CODE_LOAD_CONSTANT_DOUBLE: {
              SPVM_STRING_BUFFER_add(string_buffer, "  // LOAD_CONSTANT\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
              switch (opcode->code) {
                case SPVM_OPCODE_C_CODE_LOAD_CONSTANT_BYTE:
                  SPVM_STRING_BUFFER_add(string_buffer, " = (int8_t)");
                  SPVM_STRING_BUFFER_add_byte(string_buffer, *(int8_t*)&constant_pool[opcode->operand1]);
                  break;
                case SPVM_OPCODE_C_CODE_LOAD_CONSTANT_SHORT:
                  SPVM_STRING_BUFFER_add(string_buffer, " = (int16_t)");
                  SPVM_STRING_BUFFER_add_byte(string_buffer, *(int16_t*)&constant_pool[opcode->operand1]);
                  break;
                case SPVM_OPCODE_C_CODE_LOAD_CONSTANT_INT:
                  SPVM_STRING_BUFFER_add(string_buffer, " = (int32_t)");
                  SPVM_STRING_BUFFER_add_byte(string_buffer, *(int32_t*)&constant_pool[opcode->operand1]);
                  break;
                case SPVM_OPCODE_C_CODE_LOAD_CONSTANT_LONG:
                  SPVM_STRING_BUFFER_add(string_buffer, " = (int64_t)");
                  SPVM_STRING_BUFFER_add_byte(string_buffer, *(int64_t*)&constant_pool[opcode->operand1]);
                  SPVM_STRING_BUFFER_add(string_buffer, "L");
                  break;
                case SPVM_OPCODE_C_CODE_LOAD_CONSTANT_FLOAT:
                  SPVM_STRING_BUFFER_add(string_buffer, " = (float)");
                  SPVM_STRING_BUFFER_add_float(string_buffer, *(float*)&constant_pool[opcode->operand1]);
                  SPVM_STRING_BUFFER_add(string_buffer, "f");
                  break;
                case SPVM_OPCODE_C_CODE_LOAD_CONSTANT_DOUBLE:
                  SPVM_STRING_BUFFER_add(string_buffer, " = (double)");
                  SPVM_STRING_BUFFER_add_double(string_buffer, *(double*)&constant_pool[opcode->operand1]);
                  break;
              }
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              break;
            }
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
              SPVM_JITCODE_BUILDER_add_string_buffer_croak(string_buffer, sub_opcode_base, eval_stack, &eval_stack_top);
              SPVM_STRING_BUFFER_add(string_buffer, "    } \n");
              SPVM_STRING_BUFFER_add(string_buffer, "    else { \n");
              SPVM_STRING_BUFFER_add(string_buffer, "      if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + SPVM_INFO_OBJECT_LENGTH_BYTE_OFFSET), 0)) { \n");
              SPVM_STRING_BUFFER_add(string_buffer, "        SPVM_API_OBJECT* exception = api->new_string(api, \"Index is out of range\", 0); \n");
              SPVM_STRING_BUFFER_add(string_buffer, "        api->set_exception(api, exception); \n");
              SPVM_JITCODE_BUILDER_add_string_buffer_croak(string_buffer, sub_opcode_base, eval_stack, &eval_stack_top);
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
              SPVM_JITCODE_BUILDER_add_string_buffer_croak(string_buffer, sub_opcode_base, eval_stack, &eval_stack_top);
              SPVM_STRING_BUFFER_add(string_buffer, "    } \n");
              SPVM_STRING_BUFFER_add(string_buffer, "    else { \n");
              SPVM_STRING_BUFFER_add(string_buffer, "      if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + SPVM_INFO_OBJECT_LENGTH_BYTE_OFFSET), 0)) { \n");
              SPVM_STRING_BUFFER_add(string_buffer, "        SPVM_API_OBJECT* exception = api->new_string(api, \"Index is out of range\", 0); \n");
              SPVM_STRING_BUFFER_add(string_buffer, "        api->set_exception(api, exception); \n");
              SPVM_JITCODE_BUILDER_add_string_buffer_croak(string_buffer, sub_opcode_base, eval_stack, &eval_stack_top);
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
              SPVM_JITCODE_BUILDER_add_string_buffer_croak(string_buffer, sub_opcode_base, eval_stack, &eval_stack_top);
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
              SPVM_JITCODE_BUILDER_add_string_buffer_croak(string_buffer, sub_opcode_base, eval_stack, &eval_stack_top);
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
              SPVM_JITCODE_BUILDER_add_string_buffer_croak(string_buffer, sub_opcode_base, eval_stack, &eval_stack_top);
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
              SPVM_JITCODE_BUILDER_add_string_buffer_croak(string_buffer, sub_opcode_base, eval_stack, &eval_stack_top);
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
              SPVM_JITCODE_BUILDER_add_string_buffer_croak(string_buffer, sub_opcode_base, eval_stack, &eval_stack_top);
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
              
              int32_t jump_offset_abs = opcode->operand0;
              eval_stack_top++;
              eval_stack[eval_stack_top] = jump_offset_abs;
              
              break;
            }
            case SPVM_OPCODE_C_CODE_POP_EVAL: {
              SPVM_STRING_BUFFER_add(string_buffer, "  // POP_EVAL\n");
              
              eval_stack_top--;
              
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
              SPVM_STRING_BUFFER_add(string_buffer, "  api->set_exception(api, var");
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
              
              SPVM_API_VALUE* package_vars = runtime->package_vars;
              int32_t package_var_id = opcode->operand1;
              SPVM_API_VALUE** package_var_address = &package_vars[package_var_id];
              
              SPVM_STRING_BUFFER_add(string_buffer, "  // LOAD_PACKAGE_VAR\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
              SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_API_OBJECT** package_var_address = ");
              SPVM_STRING_BUFFER_add_address(string_buffer, package_var_address);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              SPVM_STRING_BUFFER_add(string_buffer, "    var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, " = *(");
              SPVM_STRING_BUFFER_add(string_buffer, package_var_type);
              SPVM_STRING_BUFFER_add(string_buffer, "*)package_var_address;\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
              
              break;
            }
            case SPVM_OPCODE_C_CODE_STORE_PACKAGE_VAR_BYTE:
            case SPVM_OPCODE_C_CODE_STORE_PACKAGE_VAR_SHORT:
            case SPVM_OPCODE_C_CODE_STORE_PACKAGE_VAR_INT:
            case SPVM_OPCODE_C_CODE_STORE_PACKAGE_VAR_LONG:
            case SPVM_OPCODE_C_CODE_STORE_PACKAGE_VAR_FLOAT:
            case SPVM_OPCODE_C_CODE_STORE_PACKAGE_VAR_DOUBLE:
            {
              char* package_var_type = NULL;
              switch (opcode->code) {
                case SPVM_OPCODE_C_CODE_STORE_PACKAGE_VAR_BYTE:
                  package_var_type = "int8_t";
                  break;
                case SPVM_OPCODE_C_CODE_STORE_PACKAGE_VAR_SHORT:
                  package_var_type = "int16_t";
                  break;
                case SPVM_OPCODE_C_CODE_STORE_PACKAGE_VAR_INT:
                  package_var_type = "int32_t";
                  break;
                case SPVM_OPCODE_C_CODE_STORE_PACKAGE_VAR_LONG:
                  package_var_type = "int64_t";
                  break;
                case SPVM_OPCODE_C_CODE_STORE_PACKAGE_VAR_FLOAT:
                  package_var_type = "float";
                  break;
                case SPVM_OPCODE_C_CODE_STORE_PACKAGE_VAR_DOUBLE:
                  package_var_type = "double";
                  break;
              }
              
              SPVM_API_VALUE* package_vars = runtime->package_vars;
              int32_t package_var_id = opcode->operand0;
              SPVM_API_VALUE** package_var_address = &package_vars[package_var_id];
              
              SPVM_STRING_BUFFER_add(string_buffer, "  // STORE_PACKAGE_VAR\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
              SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_API_OBJECT** package_var_address = ");
              SPVM_STRING_BUFFER_add_address(string_buffer, package_var_address);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              SPVM_STRING_BUFFER_add(string_buffer, "    *(");
              SPVM_STRING_BUFFER_add(string_buffer, package_var_type);
              SPVM_STRING_BUFFER_add(string_buffer, "*)");
              SPVM_STRING_BUFFER_add_address(string_buffer, package_var_address);
              SPVM_STRING_BUFFER_add(string_buffer, " = var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
              
              break;
            }
            case SPVM_OPCODE_C_CODE_STORE_PACKAGE_VAR_OBJECT: {
              int32_t package_var_id = opcode->operand0;
              SPVM_API_VALUE* package_vars = runtime->package_vars;
              SPVM_API_OBJECT** package_var_address = &package_vars[package_var_id];
              
              SPVM_STRING_BUFFER_add(string_buffer, "  // STORE_PACKAGE_VAR_OBJECT\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
              SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_API_OBJECT** package_var_address = ");
              SPVM_STRING_BUFFER_add_address(string_buffer, package_var_address);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              SPVM_STRING_BUFFER_add(string_buffer, "    if (*(SPVM_API_OBJECT**)package_var_address != NULL) {\n");
              SPVM_STRING_BUFFER_add(string_buffer, "      if (SPVM_INLINE_GET_REF_COUNT(*(SPVM_API_OBJECT**)package_var_address) > 1) {\n");
              SPVM_STRING_BUFFER_add(string_buffer, "        SPVM_INLINE_DEC_REF_COUNT_ONLY(*(SPVM_API_OBJECT**)package_var_address);\n");
              SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
              SPVM_STRING_BUFFER_add(string_buffer, "      else {\n");
              SPVM_STRING_BUFFER_add(string_buffer, "        api->dec_ref_count(api, *(SPVM_API_OBJECT**)package_var_address);\n");
              SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
              SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
              SPVM_STRING_BUFFER_add(string_buffer, "    *(SPVM_API_OBJECT**)package_var_address = var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              SPVM_STRING_BUFFER_add(string_buffer, "    if (package_vars[package_var_id].object_value != NULL) {;\n");
              SPVM_STRING_BUFFER_add(string_buffer, "      SPVM_INLINE_INC_REF_COUNT(*(SPVM_API_OBJECT**)package_var_address);\n");
              SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
              
              break;
            }
            case SPVM_OPCODE_C_CODE_PUSH_ARG: {
              call_sub_arg_stack_top++;
              call_sub_arg_stack[call_sub_arg_stack_top].int_value = opcode->operand0;
              
              SPVM_STRING_BUFFER_add(string_buffer, "  // PUSH_ARG\n");
              
              break;
            }
            case SPVM_OPCODE_C_CODE_CURRENT_LINE:
              if (runtime->debug) {
                SPVM_STRING_BUFFER_add(string_buffer, "  // CURRENT_LINE");
                SPVM_STRING_BUFFER_add(string_buffer, "  current_line = ");
                SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
                SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              }
              break;
            case SPVM_OPCODE_C_CODE_CALL_SUB:
            {
              // Get subroutine ID
              int32_t call_sub_id = opcode->operand1;
              
              // Constant pool sub
              SPVM_CONSTANT_POOL_SUB* constant_pool_sub_call_sub = (SPVM_CONSTANT_POOL_SUB*)&constant_pool[call_sub_id];
              
              // Call subroutine return type id
              int32_t call_sub_return_type_id = constant_pool_sub_call_sub->return_type_id;
              
              // Constant pool type
              SPVM_CONSTANT_POOL_TYPE* call_sub_return_type = (SPVM_CONSTANT_POOL_TYPE*)&constant_pool[call_sub_return_type_id];
              
              // Return type code
              int32_t call_sub_return_type_code = call_sub_return_type->code;
              
              // Subroutine argument length
              int32_t call_sub_args_length = constant_pool_sub_call_sub->args_length;
              
              // Subroutine argument length
              int32_t call_sub_is_void = constant_pool_sub_call_sub->is_void;

              int32_t call_sub_abs_name_id = constant_pool_sub_call_sub->abs_name_id;
              int32_t call_sub_abs_name_length = constant_pool[call_sub_abs_name_id];
              
              // Subroutine name
              const char* call_sub_abs_name = (char*)&constant_pool[call_sub_abs_name_id + 1];
              
              SPVM_STRING_BUFFER_add(string_buffer, "  // CALL_SUB\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  ");
              if (!call_sub_is_void) {
                SPVM_STRING_BUFFER_add(string_buffer, "var");
                SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
                SPVM_STRING_BUFFER_add(string_buffer, " = ");
              }
              
              // Subroutine name. Replace : to _
              SPVM_STRING_BUFFER_add(string_buffer, "SPVM_JITCODE_");
              SPVM_STRING_BUFFER_add(string_buffer, (char*)call_sub_abs_name);
              {
                int32_t index = string_buffer->length - strlen(call_sub_abs_name);
                while (index < string_buffer->length) {
                  if (string_buffer->buffer[index] == ':') {
                    string_buffer->buffer[index] = '_';
                  }
                  index++;
                }
              }
              SPVM_STRING_BUFFER_add(string_buffer, "(");
              call_sub_arg_stack_top -= call_sub_args_length;
              {
                int32_t i;
                for (i = 0; i < call_sub_args_length; i++) {
                  SPVM_STRING_BUFFER_add(string_buffer, "var");
                  int32_t var_index = call_sub_arg_stack[call_sub_arg_stack_top + 1 + i].int_value;
                  SPVM_STRING_BUFFER_add_int(string_buffer, var_index);
                  if (i != call_sub_args_length - 1) {
                    SPVM_STRING_BUFFER_add(string_buffer, ", ");
                  }
                }
              }
              SPVM_STRING_BUFFER_add(string_buffer, ");\n");
              
              SPVM_STRING_BUFFER_add(string_buffer, "  if (SPVM_INLINE_GET_EXCEPTION()) {\n");
              SPVM_JITCODE_BUILDER_add_string_buffer_croak(string_buffer, sub_opcode_base, eval_stack, &eval_stack_top);
              SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
              
              break;
            }
            case SPVM_OPCODE_C_CODE_CROAK:
              SPVM_STRING_BUFFER_add(string_buffer, "  // CRAOK\n");
              SPVM_JITCODE_BUILDER_add_string_buffer_croak(string_buffer, sub_opcode_base, eval_stack, &eval_stack_top);
              
              goto label_RETURN;
            case SPVM_OPCODE_C_CODE_RETURN:
            {
              SPVM_STRING_BUFFER_add(string_buffer, "  // RETURN\n");

              // Get return value
              if (!constant_pool_sub->is_void) {
                SPVM_STRING_BUFFER_add(string_buffer, "  return_value = var");
                SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
                SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              }
              SPVM_STRING_BUFFER_add(string_buffer, "  goto label_SPVM_OPCODE_C_CODE_RETURN;\n");
              
              goto label_RETURN;
            }
            case SPVM_OPCODE_C_CODE_TABLE_SWITCH:
              // TABLE_SWITCH is no longer used
              assert(0);
            case SPVM_OPCODE_C_CODE_LOOKUP_SWITCH: {
              // 1  default
              // 5  npare
              // 9  match1 offset1 // min
              // 17 match2 offset2
              // 25 match3 offset3 // max
              
              // default offset
              int32_t default_offset = opcode->operand1;
              
              // case count
              int32_t case_count = opcode->operand2;
              
              SPVM_STRING_BUFFER_add(string_buffer, "  switch(var");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
              SPVM_STRING_BUFFER_add(string_buffer, ") {\n");
              {
                int32_t case_index;
                for (case_index = 0; case_index < case_count; case_index++) {
                  int32_t match = (opcode + 1 + case_index)->operand0;
                  int32_t branch_offset = (opcode + 1 + case_index)->operand1;
                  
                  SPVM_STRING_BUFFER_add(string_buffer, "    case ");
                  SPVM_STRING_BUFFER_add_int(string_buffer, match);
                  SPVM_STRING_BUFFER_add(string_buffer, ": goto L");
                  SPVM_STRING_BUFFER_add_int(string_buffer, opcode_index + branch_offset);
                  SPVM_STRING_BUFFER_add(string_buffer, ";\n");
                }
              }
              SPVM_STRING_BUFFER_add(string_buffer, "    default: goto L");
              SPVM_STRING_BUFFER_add_int(string_buffer, opcode_index + default_offset);
              SPVM_STRING_BUFFER_add(string_buffer, ";\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  }\n");

              opcode_index += (1 + case_count);
              continue;
            }
          }
          opcode_index++;
        }

        label_RETURN: {
          char* return_type_name = NULL;
          switch (return_type->code) {
            case SPVM_TYPE_C_CODE_VOID:
              break;
            case SPVM_TYPE_C_CODE_BYTE:
              return_type_name = "int8_t";
              break;
            case SPVM_TYPE_C_CODE_SHORT:
              return_type_name = "int16_t";
              break;
            case SPVM_TYPE_C_CODE_INT:
              return_type_name = "int32_t";
              break;
            case SPVM_TYPE_C_CODE_LONG:
              return_type_name = "int64_t";
              break;
            case SPVM_TYPE_C_CODE_FLOAT:
              return_type_name = "float";
              break;
            case SPVM_TYPE_C_CODE_DOUBLE:
              return_type_name = "double";
              break;
            default:
              return_type_name = "SPVM_API_OBJECT*";
          }
          
          SPVM_STRING_BUFFER_add(string_buffer, "  // RETURN_PROCESS\n");
          SPVM_STRING_BUFFER_add(string_buffer, "  label_SPVM_OPCODE_C_CODE_RETURN:\n");
          SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
          
          // Decrement my vars which is arguments - decrement only
          {
            int32_t i;
            for (i = 0; i < sub_object_args_length; i++) {
              // Decrement if not return variable
              int32_t my_var_index = constant_pool[sub_object_mys_base + i];
              if (my_var_index != opcode->operand0) {
                SPVM_STRING_BUFFER_add(string_buffer, "    {\n");
                SPVM_STRING_BUFFER_add(string_buffer, "      SPVM_API_OBJECT* object = var");
                SPVM_STRING_BUFFER_add_int(string_buffer, my_var_index);
                SPVM_STRING_BUFFER_add(string_buffer, ";\n");
                SPVM_STRING_BUFFER_add(string_buffer, "      if (object != NULL) { SPVM_INLINE_DEC_REF_COUNT_ONLY(object); }\n");
                SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
              }
            }
          }
          // Decrement my vars which is not arguments - decrement and if reference count is 0, free object
          {
            int32_t i;
            for (i = sub_object_args_length; i < sub_object_mys_length; i++) {
              int32_t my_var_index = constant_pool[sub_object_mys_base + i];
              // Decrement if not return variable
              if (my_var_index != opcode->operand0) {
                SPVM_STRING_BUFFER_add(string_buffer, "    {\n");
                SPVM_STRING_BUFFER_add(string_buffer, "      SPVM_API_OBJECT* object = var");
                SPVM_STRING_BUFFER_add_int(string_buffer, my_var_index);
                SPVM_STRING_BUFFER_add(string_buffer, ";\n");
                SPVM_STRING_BUFFER_add(string_buffer, "      if (object != NULL) {\n");
                SPVM_STRING_BUFFER_add(string_buffer, "        if (SPVM_INLINE_GET_REF_COUNT(object) > 1) {\n");
                SPVM_STRING_BUFFER_add(string_buffer, "          SPVM_INLINE_DEC_REF_COUNT_ONLY(object);\n");
                SPVM_STRING_BUFFER_add(string_buffer, "        }\n");
                SPVM_STRING_BUFFER_add(string_buffer, "        else { api->dec_ref_count(api, object); }\n");
                SPVM_STRING_BUFFER_add(string_buffer, "      }\n");
                SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
              }
            }
          }

          if (opcode->code == SPVM_OPCODE_C_CODE_CROAK) {
            if (runtime->debug) {
              SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_API_OBJECT* new_exception = api->create_exception_stack_trace(api, sub_id, api->get_exception(api), current_line);\n");
              SPVM_STRING_BUFFER_add(string_buffer, "  api->set_exception(api, new_exception);\n");
            }
          }
          else {
            SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_INLINE_SET_EXCEPTION_NULL();\n");
          }
          
          if (sub_is_void) {
            SPVM_STRING_BUFFER_add(string_buffer, "    return;");
          }
          else {
            SPVM_STRING_BUFFER_add(string_buffer, "    return return_value;\n");
          }
          SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
        }
      }
      
      // Close subroutine
      SPVM_STRING_BUFFER_add(string_buffer, "}\n");
      SPVM_STRING_BUFFER_add(string_buffer, "\n");
    }
  }

  SPVM_STRING_BUFFER_add(string_buffer, "\n");
  
  // Define call_sub
  SPVM_STRING_BUFFER_add(string_buffer, "SPVM_API_VALUE SPVM_JITCODE_call_sub(SPVM_API* api, int32_t sub_id, SPVM_API_VALUE* args) {\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_API_VALUE return_value;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  switch(sub_id) {\n");
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
      
      SPVM_STRING_BUFFER_add(string_buffer, "    case ");
      SPVM_STRING_BUFFER_add_int(string_buffer, sub_id);
      SPVM_STRING_BUFFER_add(string_buffer, ":\n");

      SPVM_STRING_BUFFER_add(string_buffer, "      ");

      // Return type
      switch (return_type->code) {
        case SPVM_TYPE_C_CODE_VOID:
          break;
        case SPVM_TYPE_C_CODE_BYTE:
          SPVM_STRING_BUFFER_add(string_buffer, "return_value.byte_value = ");
          break;
        case SPVM_TYPE_C_CODE_SHORT:
          SPVM_STRING_BUFFER_add(string_buffer, "return_value.short_value = ");
          break;
        case SPVM_TYPE_C_CODE_INT:
          SPVM_STRING_BUFFER_add(string_buffer, "return_value.int_value = ");
          break;
        case SPVM_TYPE_C_CODE_LONG:
          SPVM_STRING_BUFFER_add(string_buffer, "return_value.long_value = ");
          break;
        case SPVM_TYPE_C_CODE_FLOAT:
          SPVM_STRING_BUFFER_add(string_buffer, "return_value.float_value = ");
          break;
        case SPVM_TYPE_C_CODE_DOUBLE:
          SPVM_STRING_BUFFER_add(string_buffer, "return_value.double_value = ");
          break;
        default:
          SPVM_STRING_BUFFER_add(string_buffer, "return_value.object_value = ");
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

          SPVM_STRING_BUFFER_add(string_buffer, "args[");
          SPVM_STRING_BUFFER_add_int(string_buffer, arg_index);
          SPVM_STRING_BUFFER_add(string_buffer, "]");
          
          switch (arg_type_code) {
            case SPVM_TYPE_C_CODE_BYTE : {
              SPVM_STRING_BUFFER_add(string_buffer, ".byte_value");
              break;
            }
            case  SPVM_TYPE_C_CODE_SHORT : {
              SPVM_STRING_BUFFER_add(string_buffer, ".short_value");
              break;
            }
            case  SPVM_TYPE_C_CODE_INT : {
              SPVM_STRING_BUFFER_add(string_buffer, ".int_value");
              break;
            }
            case  SPVM_TYPE_C_CODE_LONG : {
              SPVM_STRING_BUFFER_add(string_buffer, ".long_value");
              break;
            }
            case  SPVM_TYPE_C_CODE_FLOAT : {
              SPVM_STRING_BUFFER_add(string_buffer, ".float_value");
              break;
            }
            case  SPVM_TYPE_C_CODE_DOUBLE : {
              SPVM_STRING_BUFFER_add(string_buffer, ".double_value");
              break;
            }
            default : {
              SPVM_STRING_BUFFER_add(string_buffer, ".object_value");
            }
          }
          if (arg_index != args_length - 1) {
            SPVM_STRING_BUFFER_add(string_buffer, ", ");
          }
        }
      }
      SPVM_STRING_BUFFER_add(string_buffer, ");\n");
      SPVM_STRING_BUFFER_add(string_buffer, "      break;\n");
    }
  }
  SPVM_STRING_BUFFER_add(string_buffer, "    default:\n");
  SPVM_STRING_BUFFER_add(string_buffer, "      fprintf(stderr, \"Unknown subroutine(SPVM_JITCODE_call_sub())\");\n");
  SPVM_STRING_BUFFER_add(string_buffer, "      abort();\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  return return_value;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "}\n");
  
  warn("%s", string_buffer->buffer);
}
