#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "spvm_csource_builder_exe.h"

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

void SPVM_CSOURCE_BUILDER_EXE_add_native_headers(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer) {
  SPVM_RUNTIME* runtime = env->runtime;
  
  for (int32_t sub_id = 0; sub_id < runtime->subs_length; sub_id++) {
    SPVM_RUNTIME_SUB* sub = &runtime->subs[sub_id];
    if (sub->flag & SPVM_SUB_C_FLAG_HAVE_NATIVE_DESC) {
      SPVM_RUNTIME_PACKAGE* sub_package = &runtime->packages[sub->package_id];
      const char* sub_name = runtime->symbols[sub->name_id];
      const char* sub_package_name = runtime->symbols[sub_package->name_id];
      
      SPVM_STRING_BUFFER_add(string_buffer, "int32_t SPVM_NATIVE_");
      SPVM_STRING_BUFFER_add_package_name(string_buffer, sub_package_name);
      SPVM_STRING_BUFFER_add(string_buffer, "__");
      SPVM_STRING_BUFFER_add(string_buffer, (char*)sub_name);
      SPVM_STRING_BUFFER_add(string_buffer, "(SPVM_ENV* env, SPVM_VALUE* stack);\n");
    }
  }
}

void SPVM_CSOURCE_BUILDER_EXE_add_precompile_headers(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer) {
  SPVM_RUNTIME* runtime = env->runtime;
  
  for (int32_t sub_id = 0; sub_id < runtime->subs_length; sub_id++) {
    SPVM_RUNTIME_SUB* sub = &runtime->subs[sub_id];
    if (sub->flag & SPVM_SUB_C_FLAG_HAVE_PRECOMPILE_DESC) {
      SPVM_RUNTIME_PACKAGE* sub_package = &runtime->packages[sub->package_id];
      const char* sub_name = runtime->symbols[sub->name_id];
      const char* sub_package_name = runtime->symbols[sub_package->name_id];
      
      SPVM_STRING_BUFFER_add(string_buffer, "int32_t SPVM_PRECOMPILE_");
      SPVM_STRING_BUFFER_add_package_name(string_buffer, sub_package_name);
      SPVM_STRING_BUFFER_add(string_buffer, "__");
      SPVM_STRING_BUFFER_add(string_buffer, (char*)sub_name);
      SPVM_STRING_BUFFER_add(string_buffer, "(SPVM_ENV* env, SPVM_VALUE* stack);\n");
    }
  }
}

void SPVM_CSOURCE_BUILDER_EXE_add_set_sub_native_addresses(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer) {

  SPVM_RUNTIME* runtime = env->runtime;
  
  for (int32_t sub_id = 0; sub_id < runtime->subs_length; sub_id++) {
    SPVM_RUNTIME_SUB* sub = &runtime->subs[sub_id];
    if (sub->flag & SPVM_SUB_C_FLAG_HAVE_NATIVE_DESC) {
      SPVM_RUNTIME_PACKAGE* sub_package = &runtime->packages[sub->package_id];
      const char* sub_name = runtime->symbols[sub->name_id];
      const char* sub_package_name = runtime->symbols[sub_package->name_id];
      
      {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    const char* package_name = \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)sub_package_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    const char* sub_name = \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)sub_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_RUNTIME_PACKAGE* package = SPVM_HASH_fetch(runtime->package_symtable, package_name, strlen(package_name));\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_RUNTIME_SUB* sub = SPVM_HASH_fetch(package->sub_symtable, sub_name, strlen(sub_name));\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    runtime->sub_native_addresses[sub->id] = SPVM_NATIVE_");
        SPVM_STRING_BUFFER_add_package_name(string_buffer, sub_package_name);
        SPVM_STRING_BUFFER_add(string_buffer, "__");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)sub_name);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
      }
    }
  }
}

void SPVM_CSOURCE_BUILDER_EXE_add_set_sub_precompile_addresses(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer) {

  SPVM_RUNTIME* runtime = env->runtime;
  
  for (int32_t sub_id = 0; sub_id < runtime->subs_length; sub_id++) {
    SPVM_RUNTIME_SUB* sub = &runtime->subs[sub_id];
    if (sub->flag & SPVM_SUB_C_FLAG_HAVE_PRECOMPILE_DESC) {
      SPVM_RUNTIME_PACKAGE* sub_package = &runtime->packages[sub->package_id];
      const char* sub_name = runtime->symbols[sub->name_id];
      const char* sub_package_name = runtime->symbols[sub_package->name_id];
      
      {
        SPVM_STRING_BUFFER_add(string_buffer, "  {\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    const char* package_name = \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)sub_package_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    const char* sub_name = \"");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)sub_name);
        SPVM_STRING_BUFFER_add(string_buffer, "\";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_RUNTIME_PACKAGE* package = SPVM_HASH_fetch(runtime->package_symtable, package_name, strlen(package_name));\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    SPVM_RUNTIME_SUB* sub = SPVM_HASH_fetch(package->sub_symtable, sub_name, strlen(sub_name));\n");
        SPVM_STRING_BUFFER_add(string_buffer, "    runtime->sub_precompile_addresses[sub->id] = SPVM_PRECOMPILE_");
        SPVM_STRING_BUFFER_add_package_name(string_buffer, sub_package_name);
        SPVM_STRING_BUFFER_add(string_buffer, "__");
        SPVM_STRING_BUFFER_add(string_buffer, (char*)sub_name);
        SPVM_STRING_BUFFER_add(string_buffer, ";\n");
        SPVM_STRING_BUFFER_add(string_buffer, "  }\n");
      }
    }
  }
}

void SPVM_CSOURCE_BUILDER_EXE_build_exe_csource(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, SPVM_PORTABLE* portable, const char* package_name) {
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
  SPVM_STRING_BUFFER_add(string_buffer, "#include \"spvm_runtime_basic_type.h\"\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#include \"spvm_runtime_package.h\"\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#include \"spvm_runtime_sub.h\"\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#include \"spvm_runtime_field.h\"\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#include \"spvm_runtime_package_var.h\"\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#include \"spvm_runtime_my.h\"\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#include \"spvm_runtime_info_type.h\"\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#include \"spvm_runtime_info_switch_info.h\"\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#include \"spvm_runtime_info_case_info.h\"\n");

  // Add native sub headers
  SPVM_CSOURCE_BUILDER_EXE_add_native_headers(env, string_buffer);

  // Add precompile sub headers
  SPVM_CSOURCE_BUILDER_EXE_add_precompile_headers(env, string_buffer);
  
  SPVM_STRING_BUFFER_add(string_buffer, "int32_t main(int32_t argc, const char *argv[]) {\n");
  
  SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_PORTABLE* portable = SPVM_PORTABLE_new();\n");

  SPVM_STRING_BUFFER_add(string_buffer, "  portable->is_static = 1;\n");

  // basic_types
  SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_RUNTIME_BASIC_TYPE basic_types[");
  SPVM_STRING_BUFFER_add_int(string_buffer, portable->basic_types_length + 1);
  SPVM_STRING_BUFFER_add(string_buffer, "] = {\n");
  for (int32_t basic_type_id = 0; basic_type_id < portable->basic_types_length; basic_type_id++) {
    SPVM_STRING_BUFFER_add(string_buffer, "    {");
    SPVM_RUNTIME_BASIC_TYPE* runtime_basic_type = &portable->basic_types[basic_type_id];
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_basic_type->name_id);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_basic_type->id);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_basic_type->package_id);
    SPVM_STRING_BUFFER_add(string_buffer, "}");

    SPVM_STRING_BUFFER_add(string_buffer, ",\n");
  }
  SPVM_STRING_BUFFER_add(string_buffer, "  };\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  portable->basic_types = basic_types;\n");
  
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
  SPVM_STRING_BUFFER_add(string_buffer, "  portable->opcodes = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(int64_t) * ");
  SPVM_STRING_BUFFER_add_int(string_buffer, portable->opcodes_length + 1);
  SPVM_STRING_BUFFER_add(string_buffer, ");\n");
  for (int32_t i = 0; i < portable->opcodes_length; i++) {
    SPVM_STRING_BUFFER_add(string_buffer, "  portable->opcodes[");
    SPVM_STRING_BUFFER_add_int(string_buffer, i);
    SPVM_STRING_BUFFER_add(string_buffer, "] = ");
    SPVM_STRING_BUFFER_add_long(string_buffer, portable->opcodes[i]);
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

  // info_long_values
  SPVM_STRING_BUFFER_add(string_buffer, "  int64_t info_long_values[");
  SPVM_STRING_BUFFER_add_int(string_buffer, portable->info_long_values_length + 1);
  SPVM_STRING_BUFFER_add(string_buffer, "] = {\n");
  for (int32_t info_long_value_id = 0; info_long_value_id < portable->info_long_values_length; info_long_value_id++) {
    SPVM_STRING_BUFFER_add(string_buffer, "    ");
    SPVM_STRING_BUFFER_add_long(string_buffer, portable->info_long_values[info_long_value_id]);
    SPVM_STRING_BUFFER_add(string_buffer, ",\n");
  }
  SPVM_STRING_BUFFER_add(string_buffer, "  };\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  portable->info_long_values = info_long_values;\n");

  // info_double_values
  SPVM_STRING_BUFFER_add(string_buffer, "  double info_double_values[");
  SPVM_STRING_BUFFER_add_int(string_buffer, portable->info_double_values_length + 1);
  SPVM_STRING_BUFFER_add(string_buffer, "] = {\n");
  for (int32_t info_double_value_id = 0; info_double_value_id < portable->info_double_values_length; info_double_value_id++) {
    SPVM_STRING_BUFFER_add(string_buffer, "    ");
    SPVM_STRING_BUFFER_add_double(string_buffer, portable->info_double_values[info_double_value_id]);
    SPVM_STRING_BUFFER_add(string_buffer, ",\n");
  }
  SPVM_STRING_BUFFER_add(string_buffer, "  };\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  portable->info_double_values = info_double_values;\n");

  // info_string_values
  SPVM_STRING_BUFFER_add(string_buffer, "  char* info_string_values[");
  SPVM_STRING_BUFFER_add_int(string_buffer, portable->info_string_values_length + 1);
  SPVM_STRING_BUFFER_add(string_buffer, "] = {\n");
  for (int32_t info_string_value_id = 0; info_string_value_id < portable->info_string_values_length; info_string_value_id++) {
    SPVM_STRING_BUFFER_add(string_buffer, "    \"");
    {
      int32_t string_length = strlen(portable->info_string_values[info_string_value_id]);
      for (int32_t j = 0; j < string_length; j++) {
        SPVM_STRING_BUFFER_add_hex_char(string_buffer,  portable->info_string_values[info_string_value_id][j]);
      }
    }
    SPVM_STRING_BUFFER_add(string_buffer, "\",\n");
  }
  SPVM_STRING_BUFFER_add(string_buffer, "  };\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  portable->info_string_values = info_string_values;\n");

  // symbols
  SPVM_STRING_BUFFER_add(string_buffer, "  char* symbols[");
  SPVM_STRING_BUFFER_add_int(string_buffer, portable->symbols_length + 1);
  SPVM_STRING_BUFFER_add(string_buffer, "] = {\n");
  for (int32_t symbol_id = 0; symbol_id < portable->symbols_length; symbol_id++) {
    SPVM_STRING_BUFFER_add(string_buffer, "    \"");
    {
      int32_t string_length = strlen(portable->symbols[symbol_id]);
      for (int32_t j = 0; j < string_length; j++) {
        SPVM_STRING_BUFFER_add_hex_char(string_buffer,  portable->symbols[symbol_id][j]);
      }
    }
    SPVM_STRING_BUFFER_add(string_buffer, "\",\n");
  }
  SPVM_STRING_BUFFER_add(string_buffer, "  };\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  portable->symbols = symbols;\n");
  
  // symbols_length
  SPVM_STRING_BUFFER_add(string_buffer, "  portable->symbols_length = ");
  SPVM_STRING_BUFFER_add_int(string_buffer, portable->symbols_length);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");

  // Create run-time
  SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_ENV* env = SPVM_RUNTIME_build_runtime_env(portable);\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_RUNTIME* runtime = env->runtime;\n");

  SPVM_CSOURCE_BUILDER_EXE_add_set_sub_native_addresses(env, string_buffer);

  SPVM_CSOURCE_BUILDER_EXE_add_set_sub_precompile_addresses(env, string_buffer);

  SPVM_STRING_BUFFER_add(string_buffer, "  const char* package_name = \"");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)package_name);
  SPVM_STRING_BUFFER_add(string_buffer, "\";\n");
  
  
  SPVM_STRING_BUFFER_add(string_buffer, "  int32_t status_code = SPVM_RUNTIME_API_call_entry_point_sub(env, package_name, argc, argv);\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_RUNTIME_free(env);\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  return status_code;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "}\n");
}
