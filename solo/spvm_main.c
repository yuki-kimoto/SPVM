#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include "spvm_compiler.h"
#include "spvm_hash.h"
#include "spvm_dynamic_array.h"
#include "spvm_util_allocator.h"
#include "spvm_constant_pool.h"
#include "spvm_constant_pool_sub.h"
#include "spvm_bytecode_array.h"
#include "spvm_runtime.h"
#include "spvm_runtime_allocator.h"
#include "spvm_op.h"
#include "spvm_sub.h"
#include "spvm_dumper.h"
#include "spvm_yacc_util.h"
#include "spvm_runtime_api.h"

#include "native/SPVM/std.native/std.c"

#include <spvm_api.h>

int main(int argc, char *argv[])
{
  // If this is set to 1, you can see yacc parsing result
  SPVM_yydebug = 0;

  if (argc < 2) {
    fprintf(stderr, "Not script\n");
    exit(1);
  }
  
  // Package name
  const char* package_name = argv[1];
  
  // Create compiler
  SPVM_COMPILER* compiler = SPVM_COMPILER_new();
  
  // compiler->debug = 1;
  
  compiler->entry_point_package_name = package_name;
  
  SPVM_DYNAMIC_ARRAY_push(compiler->include_pathes, "lib");
  SPVM_DYNAMIC_ARRAY_push(compiler->include_pathes, "solo");
  
  SPVM_COMPILER_compile(compiler);
  
  // Bind native subroutine
  {
    int32_t i;
    for (i = 0; i < compiler->native_subs->length; i++) {
      SPVM_SUB* native_sub = SPVM_DYNAMIC_ARRAY_fetch(compiler->native_subs, i);
      
      // Sub abs name
      const char* sub_abs_name = native_sub->abs_name;
      
      // Sub id
      int32_t sub_id = native_sub->id;
      
      // Set native address
      SPVM_CONSTANT_POOL_SUB constant_pool_sub;
      memcpy(&constant_pool_sub, &compiler->constant_pool->values[sub_id], sizeof(SPVM_CONSTANT_POOL_SUB));
      
      if (strcmp(sub_abs_name, "CORE::say") == 0) {
        constant_pool_sub.native_address = SPVM__std__say;
      }
      else if (strcmp(sub_abs_name, "CORE::say_byte") == 0) {
        constant_pool_sub.native_address = SPVM__std__say_byte;
      }
      else if (strcmp(sub_abs_name, "CORE::say_short") == 0) {
        constant_pool_sub.native_address = SPVM__std__say_short;
      }
      else if (strcmp(sub_abs_name, "CORE::say_int") == 0) {
        constant_pool_sub.native_address = SPVM__std__say_int;
      }
      else if (strcmp(sub_abs_name, "CORE::say_long") == 0) {
        constant_pool_sub.native_address = SPVM__std__say_long;
      }
      else if (strcmp(sub_abs_name, "CORE::say_float") == 0) {
        constant_pool_sub.native_address = SPVM__std__say_float;
      }
      else if (strcmp(sub_abs_name, "CORE::say_double") == 0) {
        constant_pool_sub.native_address = SPVM__std__say_double;
      }
      else if (strcmp(sub_abs_name, "CORE::print") == 0) {
        constant_pool_sub.native_address = SPVM__std__say;
      }
      else if (strcmp(sub_abs_name, "CORE::print_byte") == 0) {
        constant_pool_sub.native_address = SPVM__std__print_byte;
      }
      else if (strcmp(sub_abs_name, "CORE::print_short") == 0) {
        constant_pool_sub.native_address = SPVM__std__print_short;
      }
      else if (strcmp(sub_abs_name, "CORE::print_int") == 0) {
        constant_pool_sub.native_address = SPVM__std__print_int;
      }
      else if (strcmp(sub_abs_name, "CORE::print_long") == 0) {
        constant_pool_sub.native_address = SPVM__std__print_long;
      }
      else if (strcmp(sub_abs_name, "CORE::print_float") == 0) {
        constant_pool_sub.native_address = SPVM__std__print_float;
      }
      else if (strcmp(sub_abs_name, "CORE::print_double") == 0) {
        constant_pool_sub.native_address = SPVM__std__print_double;
      }
      else if (strcmp(sub_abs_name, "CORE::say_err") == 0) {
        constant_pool_sub.native_address = SPVM__std__say_err;
      }
      else if (strcmp(sub_abs_name, "CORE::say_err_byte") == 0) {
        constant_pool_sub.native_address = SPVM__std__say_err_byte;
      }
      else if (strcmp(sub_abs_name, "CORE::say_err_short") == 0) {
        constant_pool_sub.native_address = SPVM__std__say_err_short;
      }
      else if (strcmp(sub_abs_name, "CORE::say_err_int") == 0) {
        constant_pool_sub.native_address = SPVM__std__say_err_int;
      }
      else if (strcmp(sub_abs_name, "CORE::say_err_long") == 0) {
        constant_pool_sub.native_address = SPVM__std__say_err_long;
      }
      else if (strcmp(sub_abs_name, "CORE::say_err_float") == 0) {
        constant_pool_sub.native_address = SPVM__std__say_err_float;
      }
      else if (strcmp(sub_abs_name, "CORE::say_err_double") == 0) {
        constant_pool_sub.native_address = SPVM__std__say_err_double;
      }
      else if (strcmp(sub_abs_name, "CORE::print_err") == 0) {
        constant_pool_sub.native_address = SPVM__std__say;
      }
      else if (strcmp(sub_abs_name, "CORE::print_err_byte") == 0) {
        constant_pool_sub.native_address = SPVM__std__print_err_byte;
      }
      else if (strcmp(sub_abs_name, "CORE::print_err_short") == 0) {
        constant_pool_sub.native_address = SPVM__std__print_err_short;
      }
      else if (strcmp(sub_abs_name, "CORE::print_err_int") == 0) {
        constant_pool_sub.native_address = SPVM__std__print_err_int;
      }
      else if (strcmp(sub_abs_name, "CORE::print_err_long") == 0) {
        constant_pool_sub.native_address = SPVM__std__print_err_long;
      }
      else if (strcmp(sub_abs_name, "CORE::print_err_float") == 0) {
        constant_pool_sub.native_address = SPVM__std__print_err_float;
      }
      else if (strcmp(sub_abs_name, "CORE::print_err_double") == 0) {
        constant_pool_sub.native_address = SPVM__std__print_err_double;
      }
      else if (strcmp(sub_abs_name, "CORE::time") == 0) {
        constant_pool_sub.native_address = SPVM__std__time;
      }
      else if (strcmp(sub_abs_name, "CORE::sum_int") == 0) {
        constant_pool_sub.native_address = SPVM__std__sum_int;
      }
      else if (strcmp(sub_abs_name, "CORE::test1") == 0) {
        constant_pool_sub.native_address = SPVM__std__test1;
      }
      else if (strcmp(sub_abs_name, "CORE::test2") == 0) {
        constant_pool_sub.native_address = SPVM__std__test2;
      }
      memcpy(&compiler->constant_pool->values[sub_id], &constant_pool_sub, sizeof(SPVM_CONSTANT_POOL_SUB));
    }
  }
  
  if (compiler->error_count > 0) {
    return 1;
  }
  else {
#ifdef DEBUG
    // Dump spvm information
    SPVM_DUMPER_dump_all(compiler);
#endif
  }

  
  // Create run-time
  SPVM_RUNTIME* runtime = SPVM_COMPILER_new_runtime(compiler);
  SPVM_API* api = runtime->api;

  // Entry point subroutine address
  const char* entry_point_sub_name = compiler->entry_point_sub_name;
  SPVM_OP* op_sub_start;
  int32_t sub_id;
  if (entry_point_sub_name) {
    op_sub_start = SPVM_HASH_search(compiler->op_sub_symtable, entry_point_sub_name, strlen(entry_point_sub_name));
    if (op_sub_start) {
      sub_id = op_sub_start->uv.sub->id;
    }
    else {
      fprintf(stderr, "Can't find entry point subroutine %s", entry_point_sub_name);
      exit(EXIT_FAILURE);
    }
  }
  else {
    fprintf(stderr, "Can't find entry point subroutine\n");
    exit(EXIT_FAILURE);
  }
  
  // Free compiler
  SPVM_COMPILER_free(compiler);
  
  SPVM_API_VALUE args[1];
  args[0].int_value = 2;
  
  // Run
  int32_t return_value = api->call_int_sub(api, sub_id, args);
  
#ifdef DEBUG
  if (runtime->exception) {
    void* message_object = runtime->exception;
    char* message = api->get_string_chars(api, message_object);
    
    printf("%s", message);
    printf("\n");
  }
  else {
    printf("TEST return_value: %" PRId32 "\n", return_value);
  }
#endif
  
  SPVM_RUNTIME_API_free_runtime(api, runtime);
  
  return 0;
}
