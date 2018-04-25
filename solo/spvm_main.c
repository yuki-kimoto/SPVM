#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include "spvm_compiler.h"
#include "spvm_hash.h"
#include "spvm_list.h"
#include "spvm_util_allocator.h"
#include "spvm_opcode_array.h"
#include "spvm_runtime.h"
#include "spvm_runtime_allocator.h"
#include "spvm_op.h"
#include "spvm_sub.h"
#include "spvm_dumper.h"
#include "spvm_yacc_util.h"
#include "spvm_runtime_api.h"
#include "spvm_opcode_builder.h"
#include "spvm_jitcode_builder.h"

#include "lib_native/SPVM/Std/IO.native/IO.c"
#include "lib_native/SPVM/Std/Time.native/Time.c"

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
  
  SPVM_LIST_push(compiler->include_pathes, "lib");
  SPVM_LIST_push(compiler->include_pathes, "solo");
  
  SPVM_COMPILER_compile(compiler);
  
  if (compiler->error_count > 0) {
    exit(1);
  }
  
  // Build bytecode
  SPVM_OPCODE_BUILDER_build_opcode_array(compiler);

#ifdef DEBUG
    // Dump spvm information
    SPVM_DUMPER_dump_all(compiler);
#endif
  
  // Bind native subroutine
  {
    int32_t i;
    for (i = 0; i < compiler->op_subs->length; i++) {
      SPVM_OP* op_sub = SPVM_LIST_fetch(compiler->op_subs, i);
      SPVM_SUB* sub = op_sub->uv.sub;
      
      if (sub->is_native) {
        // Sub abs name
        const char* sub_abs_name = sub->abs_name;
        
        if (strcmp(sub_abs_name, "Std::IO::print") == 0) {
          sub->native_address = SPVM__Std__IO__print;
        }
        else if (strcmp(sub_abs_name, "Std::IO::warn") == 0) {
          sub->native_address = SPVM__Std__IO__warn;
        }
        else if (strcmp(sub_abs_name, "Std::Time::time") == 0) {
          sub->native_address = SPVM__Std__Time__time;
        }
      }
    }
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

  SPVM_API_VALUE args[1];
  args[0].int_value = 2;
  
  // Run
  int32_t return_value = api->call_int_sub(api, sub_id, args);
  
  if (runtime->exception) {
    SPVM_RUNTIME_API_print(api, runtime->exception);
    printf("\n");
  }
  else {
    printf("TEST return_value: %" PRId32 "\n", return_value);
  }
  
  SPVM_RUNTIME_API_free_runtime(api, runtime);
  
  return 0;
}
