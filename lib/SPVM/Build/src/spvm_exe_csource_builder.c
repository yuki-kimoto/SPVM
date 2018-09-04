#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "spvm_exe_csource_builder.h"

#include "spvm_compiler.h"
#include "spvm_type.h"
#include "spvm_package.h"
#include "spvm_type.h"
#include "spvm_op.h"
#include "spvm_hash.h"
#include "spvm_list.h"
#include "spvm_util_allocator.h"
#include "spvm_compiler_allocator.h"
#include "spvm_yacc_util.h"
#include "spvm_list.h"
#include "spvm_opcode_array.h"
#include "spvm_sub.h"
#include "spvm_runtime.h"
#include "spvm_runtime_api.h"
#include "spvm_sub.h"
#include "spvm_field.h"
#include "spvm_package_var.h"
#include "spvm_native.h"
#include "spvm_opcode.h"
#include "spvm_basic_type.h"
#include "spvm_use.h"
#include "spvm_op_checker.h"
#include "spvm_opcode_builder.h"
#include "spvm_object.h"
#include "spvm_runtime_basic_type.h"
#include "spvm_runtime_package.h"
#include "spvm_runtime_field.h"
#include "spvm_runtime_package_var.h"
#include "spvm_runtime_sub.h"
#include "spvm_runtime_my.h"
#include "spvm_runtime_info_type.h"
#include "spvm_runtime_info_switch_info.h"
#include "spvm_runtime_info_case_info.h"
#include "spvm_my.h"

#include "spvm_string_buffer.h"
#include "spvm_portable.h"

void SPVM_EXE_CSOURCE_BUILDER_build_exe_csource(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, SPVM_PORTABLE* portable, const char* package_name) {
  SPVM_RUNTIME* runtime = env->runtime;
  
  SPVM_STRING_BUFFER_add(string_buffer, "#include <stdlib.h>\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#include <string.h>\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#include \"spvm_hash.h\"\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#include \"spvm_list.h\"\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#include \"spvm_native.h\"\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#include \"spvm_util_allocator.h\"\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#include \"spvm_native.h\"\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#include \"spvm_portable.h\"\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#include \"spvm_runtime.h\"\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#include \"spvm_runtime_api.h\"\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#include \"spvm_runtime_builder.h\"\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#include \"spvm_runtime_package.h\"\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#include \"spvm_runtime_sub.h\"\n");
  SPVM_STRING_BUFFER_add(string_buffer, "int32_t main(int argc, char *argv[]) {\n");
  
  SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_PORTABLE* portable = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(SPVM_PORTABLE));\n");

  // basic_types
  SPVM_STRING_BUFFER_add(string_buffer, "  portable->basic_types = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * ");
  SPVM_STRING_BUFFER_add_int(string_buffer, portable->basic_types_unit * portable->basic_types_length + 1);
  SPVM_STRING_BUFFER_add(string_buffer, ");\n");
  for (int32_t i = 0; i < portable->basic_types_unit * portable->basic_types_length; i++) {
    SPVM_STRING_BUFFER_add(string_buffer, "  portable->basic_types[");
    SPVM_STRING_BUFFER_add_int(string_buffer, i);
    SPVM_STRING_BUFFER_add(string_buffer, "] = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, portable->basic_types[i]);
    SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  }
  
  // basic_types_length
  SPVM_STRING_BUFFER_add(string_buffer, "  portable->basic_types_length = ");
  SPVM_STRING_BUFFER_add_int(string_buffer, portable->basic_types_length);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");

  // fields
  SPVM_STRING_BUFFER_add(string_buffer, "  portable->fields = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * ");
  SPVM_STRING_BUFFER_add_int(string_buffer, portable->fields_unit * portable->fields_length + 1);
  SPVM_STRING_BUFFER_add(string_buffer, ");\n");
  for (int32_t i = 0; i < portable->fields_unit * portable->fields_length; i++) {
    SPVM_STRING_BUFFER_add(string_buffer, "  portable->fields[");
    SPVM_STRING_BUFFER_add_int(string_buffer, i);
    SPVM_STRING_BUFFER_add(string_buffer, "] = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, portable->fields[i]);
    SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  }

  // fields_length
  SPVM_STRING_BUFFER_add(string_buffer, "  portable->fields_length = ");
  SPVM_STRING_BUFFER_add_int(string_buffer, portable->fields_length);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");

  // package_vars
  SPVM_STRING_BUFFER_add(string_buffer, "  portable->package_vars = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * ");
  SPVM_STRING_BUFFER_add_int(string_buffer, portable->package_vars_unit * portable->package_vars_length + 1);
  SPVM_STRING_BUFFER_add(string_buffer, ");\n");
  for (int32_t i = 0; i < portable->package_vars_unit * portable->package_vars_length; i++) {
    SPVM_STRING_BUFFER_add(string_buffer, "  portable->package_vars[");
    SPVM_STRING_BUFFER_add_int(string_buffer, i);
    SPVM_STRING_BUFFER_add(string_buffer, "] = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, portable->package_vars[i]);
    SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  }

  // package_vars_length
  SPVM_STRING_BUFFER_add(string_buffer, "  portable->package_vars_length = ");
  SPVM_STRING_BUFFER_add_int(string_buffer, portable->package_vars_length);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");

  // subs
  SPVM_STRING_BUFFER_add(string_buffer, "  portable->subs = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * ");
  SPVM_STRING_BUFFER_add_int(string_buffer, portable->subs_unit * portable->subs_length + 1);
  SPVM_STRING_BUFFER_add(string_buffer, ");\n");
  for (int32_t i = 0; i < portable->subs_unit * portable->subs_length; i++) {
    SPVM_STRING_BUFFER_add(string_buffer, "  portable->subs[");
    SPVM_STRING_BUFFER_add_int(string_buffer, i);
    SPVM_STRING_BUFFER_add(string_buffer, "] = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, portable->subs[i]);
    SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  }

  // subs_length
  SPVM_STRING_BUFFER_add(string_buffer, "  portable->subs_length = ");
  SPVM_STRING_BUFFER_add_int(string_buffer, portable->subs_length);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");

  // packages
  SPVM_STRING_BUFFER_add(string_buffer, "  portable->packages = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * ");
  SPVM_STRING_BUFFER_add_int(string_buffer, portable->packages_unit * portable->packages_length + 1);
  SPVM_STRING_BUFFER_add(string_buffer, ");\n");
  for (int32_t i = 0; i < portable->packages_unit * portable->packages_length; i++) {
    SPVM_STRING_BUFFER_add(string_buffer, "  portable->packages[");
    SPVM_STRING_BUFFER_add_int(string_buffer, i);
    SPVM_STRING_BUFFER_add(string_buffer, "] = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, portable->packages[i]);
    SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  }

  // packages_length
  SPVM_STRING_BUFFER_add(string_buffer, "  portable->packages_length = ");
  SPVM_STRING_BUFFER_add_int(string_buffer, portable->packages_length);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");

  // args
  SPVM_STRING_BUFFER_add(string_buffer, "  portable->args = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * ");
  SPVM_STRING_BUFFER_add_int(string_buffer, portable->args_unit * portable->args_length + 1);
  SPVM_STRING_BUFFER_add(string_buffer, ");\n");
  for (int32_t i = 0; i < portable->args_unit * portable->args_length; i++) {
    SPVM_STRING_BUFFER_add(string_buffer, "  portable->args[");
    SPVM_STRING_BUFFER_add_int(string_buffer, i);
    SPVM_STRING_BUFFER_add(string_buffer, "] = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, portable->args[i]);
    SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  }

  // mys
  SPVM_STRING_BUFFER_add(string_buffer, "  portable->mys = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * ");
  SPVM_STRING_BUFFER_add_int(string_buffer, portable->mys_unit * portable->mys_length + 1);
  SPVM_STRING_BUFFER_add(string_buffer, ");\n");
  for (int32_t i = 0; i < portable->mys_unit * portable->mys_length; i++) {
    SPVM_STRING_BUFFER_add(string_buffer, "  portable->mys[");
    SPVM_STRING_BUFFER_add_int(string_buffer, i);
    SPVM_STRING_BUFFER_add(string_buffer, "] = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, portable->mys[i]);
    SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  }

  // info_types
  SPVM_STRING_BUFFER_add(string_buffer, "  portable->info_types = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * ");
  SPVM_STRING_BUFFER_add_int(string_buffer, portable->info_types_unit * portable->info_types_length + 1);
  SPVM_STRING_BUFFER_add(string_buffer, ");\n");
  for (int32_t i = 0; i < portable->info_types_unit * portable->info_types_length; i++) {
    SPVM_STRING_BUFFER_add(string_buffer, "  portable->info_types[");
    SPVM_STRING_BUFFER_add_int(string_buffer, i);
    SPVM_STRING_BUFFER_add(string_buffer, "] = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, portable->info_types[i]);
    SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  }

  // info_field_ids
  SPVM_STRING_BUFFER_add(string_buffer, "  portable->info_field_ids = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * ");
  SPVM_STRING_BUFFER_add_int(string_buffer, portable->info_field_ids_length + 1);
  SPVM_STRING_BUFFER_add(string_buffer, ");\n");
  for (int32_t i = 0; i < portable->info_field_ids_length; i++) {
    SPVM_STRING_BUFFER_add(string_buffer, "  portable->info_field_ids[");
    SPVM_STRING_BUFFER_add_int(string_buffer, i);
    SPVM_STRING_BUFFER_add(string_buffer, "] = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, portable->info_field_ids[i]);
    SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  }

  // info_package_var_ids
  SPVM_STRING_BUFFER_add(string_buffer, "  portable->info_package_var_ids = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * ");
  SPVM_STRING_BUFFER_add_int(string_buffer, portable->info_package_var_ids_length + 1);
  SPVM_STRING_BUFFER_add(string_buffer, ");\n");
  for (int32_t i = 0; i < portable->info_package_var_ids_length; i++) {
    SPVM_STRING_BUFFER_add(string_buffer, "  portable->info_package_var_ids[");
    SPVM_STRING_BUFFER_add_int(string_buffer, i);
    SPVM_STRING_BUFFER_add(string_buffer, "] = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, portable->info_package_var_ids[i]);
    SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  }

  // info_sub_ids
  SPVM_STRING_BUFFER_add(string_buffer, "  portable->info_sub_ids = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * ");
  SPVM_STRING_BUFFER_add_int(string_buffer, portable->info_sub_ids_length + 1);
  SPVM_STRING_BUFFER_add(string_buffer, ");\n");
  for (int32_t i = 0; i < portable->info_sub_ids_length; i++) {
    SPVM_STRING_BUFFER_add(string_buffer, "  portable->info_sub_ids[");
    SPVM_STRING_BUFFER_add_int(string_buffer, i);
    SPVM_STRING_BUFFER_add(string_buffer, "] = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, portable->info_sub_ids[i]);
    SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  }

  // opcodes
  SPVM_STRING_BUFFER_add(string_buffer, "  portable->opcodes = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * ");
  SPVM_STRING_BUFFER_add_int(string_buffer, portable->opcodes_length + 1);
  SPVM_STRING_BUFFER_add(string_buffer, ");\n");
  for (int32_t i = 0; i < portable->opcodes_length; i++) {
    SPVM_STRING_BUFFER_add(string_buffer, "  portable->opcodes[");
    SPVM_STRING_BUFFER_add_int(string_buffer, i);
    SPVM_STRING_BUFFER_add(string_buffer, "] = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, portable->opcodes[i]);
    SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  }

  // info_string_lengths
  SPVM_STRING_BUFFER_add(string_buffer, "  portable->info_string_lengths = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * ");
  SPVM_STRING_BUFFER_add_int(string_buffer, portable->info_string_lengths_length + 1);
  SPVM_STRING_BUFFER_add(string_buffer, ");\n");
  for (int32_t i = 0; i < portable->info_string_lengths_length; i++) {
    SPVM_STRING_BUFFER_add(string_buffer, "  portable->info_string_lengths[");
    SPVM_STRING_BUFFER_add_int(string_buffer, i);
    SPVM_STRING_BUFFER_add(string_buffer, "] = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, portable->info_string_lengths[i]);
    SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  }

  // info_switch_infos
  SPVM_STRING_BUFFER_add(string_buffer, "  portable->info_switch_info_ints = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * ");
  SPVM_STRING_BUFFER_add_int(string_buffer, portable->info_switch_info_ints_length + 1);
  SPVM_STRING_BUFFER_add(string_buffer, ");\n");
  for (int32_t i = 0; i < portable->info_switch_info_ints_length; i++) {
    SPVM_STRING_BUFFER_add(string_buffer, "  portable->info_switch_info_ints[");
    SPVM_STRING_BUFFER_add_int(string_buffer, i);
    SPVM_STRING_BUFFER_add(string_buffer, "] = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, portable->info_switch_info_ints[i]);
    SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  }

  // info_sub_ids
  SPVM_STRING_BUFFER_add(string_buffer, "  portable->info_sub_ids = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int32_t) * ");
  SPVM_STRING_BUFFER_add_int(string_buffer, portable->info_sub_ids_length + 1);
  SPVM_STRING_BUFFER_add(string_buffer, ");\n");
  for (int32_t i = 0; i < portable->info_sub_ids_length; i++) {
    SPVM_STRING_BUFFER_add(string_buffer, "  portable->info_sub_ids[");
    SPVM_STRING_BUFFER_add_int(string_buffer, i);
    SPVM_STRING_BUFFER_add(string_buffer, "] = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, portable->info_sub_ids[i]);
    SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  }

  // info_long_values
  SPVM_STRING_BUFFER_add(string_buffer, "  portable->info_long_values = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int64_t) * ");
  SPVM_STRING_BUFFER_add_int(string_buffer, portable->info_long_values_length + 1);
  SPVM_STRING_BUFFER_add(string_buffer, ");\n");
  for (int32_t i = 0; i < portable->info_long_values_length; i++) {
    SPVM_STRING_BUFFER_add(string_buffer, "  portable->info_long_values[");
    SPVM_STRING_BUFFER_add_int(string_buffer, i);
    SPVM_STRING_BUFFER_add(string_buffer, "] = ");
    SPVM_STRING_BUFFER_add_long(string_buffer, portable->info_long_values[i]);
    SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  }

  // info_double_values
  SPVM_STRING_BUFFER_add(string_buffer, "  portable->info_double_values = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(double) * ");
  SPVM_STRING_BUFFER_add_int(string_buffer, portable->info_double_values_length + 1);
  SPVM_STRING_BUFFER_add(string_buffer, ");\n");
  for (int32_t i = 0; i < portable->info_double_values_length; i++) {
    SPVM_STRING_BUFFER_add(string_buffer, "  portable->info_double_values[");
    SPVM_STRING_BUFFER_add_int(string_buffer, i);
    SPVM_STRING_BUFFER_add(string_buffer, "] = ");
    SPVM_STRING_BUFFER_add_double(string_buffer, portable->info_double_values[i]);
    SPVM_STRING_BUFFER_add(string_buffer, ";\n");
  }

  // info_string_values
  SPVM_STRING_BUFFER_add(string_buffer, "  portable->info_string_values = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(char*) * ");
  SPVM_STRING_BUFFER_add_int(string_buffer, portable->info_string_values_length + 1);
  SPVM_STRING_BUFFER_add(string_buffer, ");\n");
  for (int32_t i = 0; i < portable->info_string_values_length; i++) {
    SPVM_STRING_BUFFER_add(string_buffer, "  portable->info_string_values[");
    SPVM_STRING_BUFFER_add_int(string_buffer, i);
    SPVM_STRING_BUFFER_add(string_buffer, "] = \"");
    {
      for (int32_t j = 0; j < portable->info_string_lengths_length; j++) {
        SPVM_STRING_BUFFER_add_hex_char(string_buffer,  portable->info_string_values[i][j]);
      }
    }
    SPVM_STRING_BUFFER_add(string_buffer, "\";\n");
  }

  // symbols
  SPVM_STRING_BUFFER_add(string_buffer, "  portable->symbols = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(char*) * ");
  SPVM_STRING_BUFFER_add_int(string_buffer, portable->symbols_length + 1);
  SPVM_STRING_BUFFER_add(string_buffer, ");\n");
  for (int32_t i = 0; i < portable->symbols_length; i++) {
    SPVM_STRING_BUFFER_add(string_buffer, "  portable->symbols[");
    SPVM_STRING_BUFFER_add_int(string_buffer, i);
    SPVM_STRING_BUFFER_add(string_buffer, "] = \"");
    {
      int32_t string_length = strlen(portable->symbols[i]);
      for (int32_t j = 0; j < string_length; j++) {
        SPVM_STRING_BUFFER_add_hex_char(string_buffer,  portable->symbols[i][j]);
      }
    }
    SPVM_STRING_BUFFER_add(string_buffer, "\";\n");
  }

  // Create run-time
  SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_ENV* env = SPVM_RUNTIME_BUILDER_build_runtime_env(portable);\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_RUNTIME* runtime = env->runtime;\n");

  
  // Package
  SPVM_STRING_BUFFER_add(string_buffer, "  int32_t sub_id = -1;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "const char* package_name = \"");
  SPVM_STRING_BUFFER_add(string_buffer, package_name);
  SPVM_STRING_BUFFER_add(string_buffer, "\";\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_RUNTIME_PACKAGE* package = SPVM_HASH_fetch(runtime->package_symtable, package_name, strlen(package_name));\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  if (package) {\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    const char* sub_name = \"main\";\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_RUNTIME_SUB* sub = SPVM_HASH_fetch(package->sub_symtable, sub_name, strlen(sub_name));\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    if (sub) {\n");
  SPVM_STRING_BUFFER_add(string_buffer, "      sub_id = sub->id;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    else {\n");
  SPVM_STRING_BUFFER_add(string_buffer, "      fprintf(stderr, \"Can't find entry point subroutine %s\\n\", sub_name);\n");
  SPVM_STRING_BUFFER_add(string_buffer, "      exit(EXIT_FAILURE);\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    }\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  else {\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    fprintf(stderr, \"Can't find entry point package %s\\n\", package_name);\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  int32_t scope_id = env->enter_scope(env);\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  int32_t arg_type_basic_id = env->get_basic_type_id(env, \"byte\");\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  void* cmd_args_obj = env->new_multi_array(env, arg_type_basic_id, 1, argc);\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  for (int32_t arg_index = 0; arg_index < argc; arg_index++) {\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    void* cmd_arg_obj = env->new_string(env, argv[arg_index], strlen(argv[arg_index]));\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    env->set_object_array_element(env, cmd_args_obj, arg_index, cmd_arg_obj);\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_VALUE stack[255];\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  stack[0].oval = cmd_args_obj;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  int32_t exception_flag = env->call_sub(env, sub_id, stack);\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  int32_t status_code;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  if (exception_flag) {\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_RUNTIME_API_print(env, runtime->exception);\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    printf(\"\\n\");\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    status_code = 255;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  else {\n");
  SPVM_STRING_BUFFER_add(string_buffer, "    status_code = stack[0].ival;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  env->leave_scope(env, scope_id);\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_RUNTIME_free(env);\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  return status_code;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "}\n");
}
