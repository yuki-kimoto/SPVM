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
  SPVM_STRING_BUFFER_add(string_buffer, "#include \"spvm_opcode.h\"\n");

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
    SPVM_RUNTIME_BASIC_TYPE* runtime_basic_type = &portable->basic_types[basic_type_id];
    SPVM_STRING_BUFFER_add(string_buffer, "    {");
    SPVM_STRING_BUFFER_add(string_buffer, ".name_id = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_basic_type->name_id);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".id = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_basic_type->id);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".package_id = ");
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
  SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_RUNTIME_FIELD fields[");
  SPVM_STRING_BUFFER_add_int(string_buffer, portable->fields_length + 1);
  SPVM_STRING_BUFFER_add(string_buffer, "] = {\n");
  for (int32_t field_id = 0; field_id < portable->fields_length; field_id++) {
    SPVM_RUNTIME_FIELD* runtime_field = &portable->fields[field_id];
    SPVM_STRING_BUFFER_add(string_buffer, "    {");
    SPVM_STRING_BUFFER_add(string_buffer, ".id = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_field->id);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".index = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_field->index);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".flag = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_field->flag);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".name_id = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_field->abs_name_id);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");    SPVM_STRING_BUFFER_add(string_buffer, ".name_id = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_field->abs_name_id);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".signature_id = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_field->signature_id);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".basic_type_id = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_field->basic_type_id);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".type_dimension = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_field->type_dimension);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".type_flag = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_field->type_flag);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".package_id = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_field->package_id);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".name_id = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_field->name_id);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, "}");

    SPVM_STRING_BUFFER_add(string_buffer, ",\n");
  }
  SPVM_STRING_BUFFER_add(string_buffer, "  };\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  portable->fields = fields;\n");
  
  // fields_length
  SPVM_STRING_BUFFER_add(string_buffer, "  portable->fields_length = ");
  SPVM_STRING_BUFFER_add_int(string_buffer, portable->fields_length);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");

  // package_vars
  SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_RUNTIME_PACKAGE_VAR package_vars[");
  SPVM_STRING_BUFFER_add_int(string_buffer, portable->package_vars_length + 1);
  SPVM_STRING_BUFFER_add(string_buffer, "] = {\n");
  for (int32_t package_var_id = 0; package_var_id < portable->package_vars_length; package_var_id++) {
    SPVM_RUNTIME_PACKAGE_VAR* runtime_package_var = &portable->package_vars[package_var_id];
    SPVM_STRING_BUFFER_add(string_buffer, "    {");
    SPVM_STRING_BUFFER_add(string_buffer, ".id = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_package_var->id);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".name_id = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_package_var->name_id);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".abs_name_id = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_package_var->abs_name_id);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".signature_id = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_package_var->signature_id);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".basic_type_id = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_package_var->basic_type_id);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".type_dimension = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_package_var->type_dimension);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".type_flag = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_package_var->type_flag);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".package_id = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_package_var->package_id);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, "}");

    SPVM_STRING_BUFFER_add(string_buffer, ",\n");
  }
  SPVM_STRING_BUFFER_add(string_buffer, "  };\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  portable->package_vars = package_vars;\n");
  
  // package_vars_length
  SPVM_STRING_BUFFER_add(string_buffer, "  portable->package_vars_length = ");
  SPVM_STRING_BUFFER_add_int(string_buffer, portable->package_vars_length);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");

  // subs
  SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_RUNTIME_SUB subs[");
  SPVM_STRING_BUFFER_add_int(string_buffer, portable->subs_length + 1);
  SPVM_STRING_BUFFER_add(string_buffer, "] = {\n");
  for (int32_t sub_id = 0; sub_id < portable->subs_length; sub_id++) {
    SPVM_RUNTIME_SUB* runtime_sub = &portable->subs[sub_id];

    SPVM_STRING_BUFFER_add(string_buffer, "    {");
    SPVM_STRING_BUFFER_add(string_buffer, ".id = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_sub->id);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".flag = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_sub->flag);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".name_id = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_sub->name_id);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".abs_name_id = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_sub->abs_name_id);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".signature_id = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_sub->signature_id);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".package_id = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_sub->package_id);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".file_id = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_sub->file_id);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".line = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_sub->line);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".args_alloc_length = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_sub->args_alloc_length);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".return_basic_type_id = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_sub->return_basic_type_id);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".return_type_dimension = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_sub->return_type_dimension);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".return_type_flag = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_sub->return_type_flag);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".opcodes_base = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_sub->opcodes_base);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".mortal_stack_length = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_sub->mortal_stack_length);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".arg_ids_base = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_sub->arg_ids_base);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".arg_ids_length = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_sub->arg_ids_length);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".info_package_var_ids_base = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_sub->info_package_var_ids_base);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".info_package_var_ids_length = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_sub->info_package_var_ids_length);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".info_field_ids_base = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_sub->info_field_ids_base);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".info_field_ids_length = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_sub->info_field_ids_length);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".info_sub_ids_base = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_sub->info_sub_ids_base);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".info_field_ids_length = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_sub->info_field_ids_length);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".info_sub_ids_base = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_sub->info_sub_ids_base);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".info_sub_ids_length = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_sub->info_sub_ids_length);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".info_types_base = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_sub->info_types_base);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".info_types_length = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_sub->info_types_length);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".info_switch_infos_base = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_sub->info_switch_infos_base);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".info_switch_infos_length = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_sub->info_switch_infos_length);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".info_long_values_base = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_sub->info_long_values_base);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".info_long_values_length = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_sub->info_long_values_length);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".info_double_values_base = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_sub->info_double_values_base);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".info_double_values_length = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_sub->info_double_values_length);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".info_string_values_base = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_sub->info_string_values_base);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".info_string_values_length = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_sub->info_string_values_length);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".opcodes_length = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_sub->opcodes_length);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".my_ids_base = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_sub->my_ids_base);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".my_ids_length = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_sub->my_ids_length);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".call_type_id = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_sub->call_type_id);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".byte_vars_alloc_length = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_sub->byte_vars_alloc_length);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".short_vars_alloc_length = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_sub->short_vars_alloc_length);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".int_vars_alloc_length = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_sub->int_vars_alloc_length);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".long_vars_alloc_length = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_sub->long_vars_alloc_length);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".float_vars_alloc_length = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_sub->float_vars_alloc_length);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".double_vars_alloc_length = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_sub->double_vars_alloc_length);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".object_vars_alloc_length = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_sub->object_vars_alloc_length);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".ref_vars_alloc_length = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_sub->ref_vars_alloc_length);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, "}");

    SPVM_STRING_BUFFER_add(string_buffer, ",\n");
  }
  SPVM_STRING_BUFFER_add(string_buffer, "  };\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  portable->subs = subs;\n");
  
  // subs_length
  SPVM_STRING_BUFFER_add(string_buffer, "  portable->subs_length = ");
  SPVM_STRING_BUFFER_add_int(string_buffer, portable->subs_length);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");

  // packages
  SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_RUNTIME_PACKAGE packages[");
  SPVM_STRING_BUFFER_add_int(string_buffer, portable->packages_length + 1);
  SPVM_STRING_BUFFER_add(string_buffer, "] = {\n");
  for (int32_t package_id = 0; package_id < portable->packages_length; package_id++) {
    SPVM_RUNTIME_PACKAGE* runtime_package = &portable->packages[package_id];
    SPVM_STRING_BUFFER_add(string_buffer, "    {");
    SPVM_STRING_BUFFER_add(string_buffer, ".id = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_package->id);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".name_id = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_package->name_id);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".destructor_sub_id = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_package->destructor_sub_id);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".category = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_package->category);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".load_path_id = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_package->load_path_id);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".flag = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_package->flag);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, "}");

    SPVM_STRING_BUFFER_add(string_buffer, ",\n");
  }
  SPVM_STRING_BUFFER_add(string_buffer, "  };\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  portable->packages = packages;\n");
  
  // packages_length
  SPVM_STRING_BUFFER_add(string_buffer, "  portable->packages_length = ");
  SPVM_STRING_BUFFER_add_int(string_buffer, portable->packages_length);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");

  // args
  SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_RUNTIME_MY args[");
  SPVM_STRING_BUFFER_add_int(string_buffer, portable->args_length + 1);
  SPVM_STRING_BUFFER_add(string_buffer, "] = {\n");
  for (int32_t arg_id = 0; arg_id < portable->args_length; arg_id++) {
    SPVM_RUNTIME_MY* runtime_arg = &portable->args[arg_id];
    SPVM_STRING_BUFFER_add(string_buffer, "    {");
    SPVM_STRING_BUFFER_add(string_buffer, ".basic_type_id = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_arg->basic_type_id);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".type_dimension = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_arg->type_dimension);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".type_flag = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_arg->type_flag);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".var_id = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_arg->var_id);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".value_field_basic_type_id = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_arg->value_field_basic_type_id);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, "}");

    SPVM_STRING_BUFFER_add(string_buffer, ",\n");
  }
  SPVM_STRING_BUFFER_add(string_buffer, "  };\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  portable->args = args;\n");

  // mys
  SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_RUNTIME_MY mys[");
  SPVM_STRING_BUFFER_add_int(string_buffer, portable->mys_length + 1);
  SPVM_STRING_BUFFER_add(string_buffer, "] = {\n");
  for (int32_t my_id = 0; my_id < portable->mys_length; my_id++) {
    SPVM_RUNTIME_MY* runtime_my = &portable->mys[my_id];
    SPVM_STRING_BUFFER_add(string_buffer, "    {");
    SPVM_STRING_BUFFER_add(string_buffer, ".basic_type_id = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_my->basic_type_id);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".type_dimension = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_my->type_dimension);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".type_flag = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_my->type_flag);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".var_id = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_my->var_id);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".value_field_basic_type_id = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_my->value_field_basic_type_id);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, "}");

    SPVM_STRING_BUFFER_add(string_buffer, ",\n");
  }
  SPVM_STRING_BUFFER_add(string_buffer, "  };\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  portable->mys = mys;\n");

  // info_types
  SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_RUNTIME_INFO_TYPE info_types[");
  SPVM_STRING_BUFFER_add_int(string_buffer, portable->info_types_length + 1);
  SPVM_STRING_BUFFER_add(string_buffer, "] = {\n");
  for (int32_t info_type_id = 0; info_type_id < portable->info_types_length; info_type_id++) {
    SPVM_RUNTIME_INFO_TYPE* runtime_info_type = &portable->info_types[info_type_id];
    SPVM_STRING_BUFFER_add(string_buffer, "    {");
    SPVM_STRING_BUFFER_add(string_buffer, ".basic_type_id = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_info_type->basic_type_id);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".dimension = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_info_type->dimension);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".flag = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_info_type->flag);
    SPVM_STRING_BUFFER_add(string_buffer, "}");

    SPVM_STRING_BUFFER_add(string_buffer, ",\n");
  }
  SPVM_STRING_BUFFER_add(string_buffer, "  };\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  portable->info_types = info_types;\n");
  
  // info_types_length
  SPVM_STRING_BUFFER_add(string_buffer, "  portable->info_types_length = ");
  SPVM_STRING_BUFFER_add_int(string_buffer, portable->info_types_length);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");

  // info_field_ids
  SPVM_STRING_BUFFER_add(string_buffer, "  int32_t info_field_ids[");
  SPVM_STRING_BUFFER_add_int(string_buffer, portable->info_field_ids_length + 1);
  SPVM_STRING_BUFFER_add(string_buffer, "] = {\n");
  for (int32_t info_field_id_id = 0; info_field_id_id < portable->info_field_ids_length; info_field_id_id++) {
    SPVM_STRING_BUFFER_add(string_buffer, "    ");
    SPVM_STRING_BUFFER_add_int(string_buffer, portable->info_field_ids[info_field_id_id]);
    SPVM_STRING_BUFFER_add(string_buffer, ",\n");
  }
  SPVM_STRING_BUFFER_add(string_buffer, "  };\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  portable->info_field_ids = info_field_ids;\n");

  // info_package_var_ids
  SPVM_STRING_BUFFER_add(string_buffer, "  int32_t info_package_var_ids[");
  SPVM_STRING_BUFFER_add_int(string_buffer, portable->info_package_var_ids_length + 1);
  SPVM_STRING_BUFFER_add(string_buffer, "] = {\n");
  for (int32_t info_package_var_id_id = 0; info_package_var_id_id < portable->info_package_var_ids_length; info_package_var_id_id++) {
    SPVM_STRING_BUFFER_add(string_buffer, "    ");
    SPVM_STRING_BUFFER_add_int(string_buffer, portable->info_package_var_ids[info_package_var_id_id]);
    SPVM_STRING_BUFFER_add(string_buffer, ",\n");
  }
  SPVM_STRING_BUFFER_add(string_buffer, "  };\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  portable->info_package_var_ids = info_package_var_ids;\n");

  // info_sub_ids
  SPVM_STRING_BUFFER_add(string_buffer, "  int32_t info_sub_ids[");
  SPVM_STRING_BUFFER_add_int(string_buffer, portable->info_sub_ids_length + 1);
  SPVM_STRING_BUFFER_add(string_buffer, "] = {\n");
  for (int32_t info_sub_id_id = 0; info_sub_id_id < portable->info_sub_ids_length; info_sub_id_id++) {
    SPVM_STRING_BUFFER_add(string_buffer, "    ");
    SPVM_STRING_BUFFER_add_int(string_buffer, portable->info_sub_ids[info_sub_id_id]);
    SPVM_STRING_BUFFER_add(string_buffer, ",\n");
  }
  SPVM_STRING_BUFFER_add(string_buffer, "  };\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  portable->info_sub_ids = info_sub_ids;\n");

  // opcodes
  SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_OPCODE opcodes[");
  SPVM_STRING_BUFFER_add_int(string_buffer, portable->opcodes_length + 1);
  SPVM_STRING_BUFFER_add(string_buffer, "] = {\n");
  for (int32_t opcode_id = 0; opcode_id < portable->opcodes_length; opcode_id++) {
    SPVM_OPCODE* opcode = &portable->opcodes[opcode_id];

    SPVM_STRING_BUFFER_add(string_buffer, "    {");
    SPVM_STRING_BUFFER_add(string_buffer, ".id = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, opcode->id);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".operand3 = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand3);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".operand0 = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand0);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".operand1 = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand1);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".operand2 = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, opcode->operand2);
    SPVM_STRING_BUFFER_add(string_buffer, "}");

    SPVM_STRING_BUFFER_add(string_buffer, ",\n");
  }
  SPVM_STRING_BUFFER_add(string_buffer, "  };\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  portable->opcodes = opcodes;\n");
  
  // opcodes_length
  SPVM_STRING_BUFFER_add(string_buffer, "  portable->opcodes_length = ");
  SPVM_STRING_BUFFER_add_int(string_buffer, portable->opcodes_length);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");

  // info_switch_infos
  SPVM_STRING_BUFFER_add(string_buffer, "  int32_t info_switch_info_ints[");
  SPVM_STRING_BUFFER_add_int(string_buffer, portable->info_switch_info_ints_length + 1);
  SPVM_STRING_BUFFER_add(string_buffer, "] = {\n");
  for (int32_t info_switch_info_int_id = 0; info_switch_info_int_id < portable->info_switch_info_ints_length; info_switch_info_int_id++) {
    SPVM_STRING_BUFFER_add(string_buffer, "    ");
    SPVM_STRING_BUFFER_add_int(string_buffer, portable->info_switch_info_ints[info_switch_info_int_id]);
    SPVM_STRING_BUFFER_add(string_buffer, ",\n");
  }
  SPVM_STRING_BUFFER_add(string_buffer, "  };\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  portable->info_switch_info_ints = info_switch_info_ints;\n");

  // info_string_lengths
  SPVM_STRING_BUFFER_add(string_buffer, "  int32_t info_string_lengths[");
  SPVM_STRING_BUFFER_add_int(string_buffer, portable->info_string_lengths_length + 1);
  SPVM_STRING_BUFFER_add(string_buffer, "] = {\n");
  for (int32_t info_string_length_id = 0; info_string_length_id < portable->info_string_lengths_length; info_string_length_id++) {
    SPVM_STRING_BUFFER_add(string_buffer, "    ");
    SPVM_STRING_BUFFER_add_int(string_buffer, portable->info_string_lengths[info_string_length_id]);
    SPVM_STRING_BUFFER_add(string_buffer, ",\n");
  }
  SPVM_STRING_BUFFER_add(string_buffer, "  };\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  portable->info_string_lengths = info_string_lengths;\n");

  // info_long_values
  SPVM_STRING_BUFFER_add(string_buffer, "  int64_t info_long_values[");
  SPVM_STRING_BUFFER_add_int(string_buffer, portable->info_long_values_length + 1);
  SPVM_STRING_BUFFER_add(string_buffer, "] = {\n");
  for (int32_t info_long_value_id = 0; info_long_value_id < portable->info_long_values_length; info_long_value_id++) {
    SPVM_STRING_BUFFER_add(string_buffer, "    ");
    SPVM_STRING_BUFFER_add_long(string_buffer, portable->info_long_values[info_long_value_id]);
    SPVM_STRING_BUFFER_add(string_buffer, "ULL,\n");
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
