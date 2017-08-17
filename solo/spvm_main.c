#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include "../spvm_compiler.h"
#include "../spvm_hash.h"
#include "../spvm_dynamic_array.h"
#include "../spvm_util_allocator.h"
#include "../spvm_constant_pool.h"
#include "../spvm_constant_pool_sub.h"
#include "../spvm_bytecode_array.h"
#include "../spvm_runtime.h"
#include "../spvm_runtime_allocator.h"
#include "../spvm_op.h"
#include "../spvm_sub.h"
#include "../spvm_dumper.h"
#include "../spvm_api.h"

int32_t SPVM__stdout__sum_int(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  SPVM_API_OBJECT* array = args[0].object_value;
  
  int32_t length = api->get_array_length(api, array);
  
  int32_t* values = api->get_int_array_elements(api, array);
  
  int64_t total = 0;
  {
    int32_t i;
    for (i = 0; i < length; i++) {
      total += values[i];
    }
  }
  
  return total;
}

int32_t SPVM__stdout__test1(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  int32_t num1 = args[0].int_value;
  int32_t num2 = args[1].int_value;
  
  int32_t sub_id = api->get_sub_id(api, "stdout::test2");
  
  SPVM_API_VALUE new_args[2];
  new_args[0].int_value = 5;
  new_args[1].int_value = 3;
  
  int32_t ret = api->call_int_sub(api, sub_id, new_args);
  
  int32_t num3 = num1 + num2 + ret;
  
  return num3;
}

int32_t SPVM__stdout__test2(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  int32_t num1 = args[0].int_value;
  int32_t num2 = args[1].int_value;
  
  int32_t num3 = num1 * num2;
  
  return num3;
}

void SPVM__stdout__print(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  SPVM_API_OBJECT* array = args[0].object_value;

  int8_t* string = api->get_byte_array_elements(api, array);
  
  printf("%s\n", (char*)string);
}

void SPVM__stdout__println(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  SPVM_API_OBJECT* array = args[0].object_value;

  int8_t* string = api->get_byte_array_elements(api, array);

  printf("%s\n", (char*)string);
}

void SPVM__stdout__println_byte(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  int8_t value = args[0].byte_value;
  
  printf("%" PRId8 "\n", value);
}

void SPVM__stdout__println_short(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  int16_t value = args[0].short_value;
  
  printf("%" PRId16 "\n", value);
}

void SPVM__stdout__println_int(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  int32_t value = args[0].int_value;
  
  printf("%" PRId32 "\n", value);
}

void SPVM__stdout__println_long(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  int64_t value = args[0].long_value;
  
  printf("%" PRId64 "\n", value);
}

void SPVM__stdout__println_float(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  float value = args[0].float_value;

  printf("%f\n", value);
}

void SPVM__stdout__println_double(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  double value = args[0].double_value;
  
  printf("%f\n", value);
}

void SPVM__stdout__print_byte(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  int8_t value = args[0].byte_value;
  
  printf("%" PRId8, value);
}

void SPVM__stdout__print_short(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  int16_t value = args[0].short_value;
  
  printf("%" PRId16, value);
}

void SPVM__stdout__print_int(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  int32_t value = args[0].int_value;
  
  printf("%" PRId32, value);
}

void SPVM__stdout__print_long(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  int64_t value = args[0].long_value;
  
  printf("%" PRId64, value);
}

void SPVM__stdout__print_float(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  float value = args[0].float_value;
  
  printf("%f", value);
}

void SPVM__stdout__print_double(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  double value = args[0].double_value;
  
  printf("%f", value);
}

int main(int argc, char *argv[])
{
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
      int32_t sub_id = native_sub->constant_pool_index;
      
      // Set native address
      SPVM_CONSTANT_POOL_SUB constant_pool_sub;
      memcpy(&constant_pool_sub, &compiler->constant_pool->values[sub_id], sizeof(SPVM_CONSTANT_POOL_SUB));
      
      if (strcmp(sub_abs_name, "stdout::println_byte") == 0) {
        constant_pool_sub.native_address = SPVM__stdout__println_byte;
      }
      else if (strcmp(sub_abs_name, "stdout::println_short") == 0) {
        constant_pool_sub.native_address = SPVM__stdout__println_short;
      }
      else if (strcmp(sub_abs_name, "stdout::println_int") == 0) {
        constant_pool_sub.native_address = SPVM__stdout__println_int;
      }
      else if (strcmp(sub_abs_name, "stdout::println_long") == 0) {
        constant_pool_sub.native_address = SPVM__stdout__println_long;
      }
      else if (strcmp(sub_abs_name, "stdout::println_float") == 0) {
        constant_pool_sub.native_address = SPVM__stdout__println_float;
      }
      else if (strcmp(sub_abs_name, "stdout::println_double") == 0) {
        constant_pool_sub.native_address = SPVM__stdout__println_double;
      }
      else if (strcmp(sub_abs_name, "stdout::print_byte") == 0) {
        constant_pool_sub.native_address = SPVM__stdout__print_byte;
      }
      else if (strcmp(sub_abs_name, "stdout::print_short") == 0) {
        constant_pool_sub.native_address = SPVM__stdout__print_short;
      }
      else if (strcmp(sub_abs_name, "stdout::print_int") == 0) {
        constant_pool_sub.native_address = SPVM__stdout__print_int;
      }
      else if (strcmp(sub_abs_name, "stdout::print_long") == 0) {
        constant_pool_sub.native_address = SPVM__stdout__print_long;
      }
      else if (strcmp(sub_abs_name, "stdout::print_float") == 0) {
        constant_pool_sub.native_address = SPVM__stdout__print_float;
      }
      else if (strcmp(sub_abs_name, "stdout::print_double") == 0) {
        constant_pool_sub.native_address = SPVM__stdout__print_double;
      }
      else if (strcmp(sub_abs_name, "stdout::println") == 0) {
        constant_pool_sub.native_address = SPVM__stdout__println;
      }
      else if (strcmp(sub_abs_name, "stdout::sum_int") == 0) {
        constant_pool_sub.native_address = SPVM__stdout__sum_int;
      }
      else if (strcmp(sub_abs_name, "stdout::test1") == 0) {
        constant_pool_sub.native_address = SPVM__stdout__test1;
      }
      else if (strcmp(sub_abs_name, "stdout::test2") == 0) {
        constant_pool_sub.native_address = SPVM__stdout__test2;
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
  int32_t sub_constant_pool_index;
  if (entry_point_sub_name) {
    op_sub_start = SPVM_HASH_search(compiler->op_sub_symtable, entry_point_sub_name, strlen(entry_point_sub_name));
    if (op_sub_start) {
      sub_constant_pool_index = op_sub_start->uv.sub->constant_pool_index;
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
  int32_t return_value = api->call_int_sub(api, sub_constant_pool_index, args);
  
#ifdef DEBUG
  if (runtime->exception) {
    void* message_object = runtime->exception;
    int8_t* message = api->get_byte_array_elements(api, message_object);
    
    printf("%s", (char*)message);
    printf("\n");
  }
  else {
    printf("TEST return_value: %" PRId32 "\n", return_value);
  }
#endif
  
  SPVM_RUNTIME_free(runtime);
  
  return 0;
}
