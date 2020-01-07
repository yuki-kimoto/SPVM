#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "spvm_native.h"

#include "spvm_csource_builder_exe.h"

#include "spvm_sub.h"
#include "spvm_opcode.h"
#include "spvm_basic_type.h"

#include "spvm_runtime.h"
#include "spvm_runtime_api.h"
#include "spvm_runtime_basic_type.h"
#include "spvm_runtime_package.h"
#include "spvm_runtime_field.h"
#include "spvm_runtime_package_var.h"
#include "spvm_runtime_sub.h"
#include "spvm_runtime_arg.h"

#include "spvm_string_buffer.h"
#include "spvm_portable.h"

void SPVM_CSOURCE_BUILDER_EXE_add_native_headers(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer) {
  SPVM_RUNTIME* runtime = env->runtime;
  
  for (int32_t sub_id = 1; sub_id < runtime->subs_length; sub_id++) {
    SPVM_RUNTIME_SUB* sub = &runtime->subs[sub_id];
    if (sub->flag & SPVM_SUB_C_FLAG_NATIVE) {
      SPVM_RUNTIME_PACKAGE* sub_package = &runtime->packages[sub->package_id];
      const char* sub_name = &runtime->string_pool[sub->name_id];
      const char* sub_package_name = &runtime->string_pool[sub_package->name_id];
      
      SPVM_STRING_BUFFER_add(string_buffer, "int32_t SPNATIVE__");
      SPVM_STRING_BUFFER_add_package_name(string_buffer, sub_package_name);
      SPVM_STRING_BUFFER_add(string_buffer, "__");
      SPVM_STRING_BUFFER_add(string_buffer, (char*)sub_name);
      SPVM_STRING_BUFFER_add(string_buffer, "(SPVM_ENV* env, SPVM_VALUE* stack);\n");
    }
  }
}

void SPVM_CSOURCE_BUILDER_EXE_add_precompile_headers(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer) {
  SPVM_RUNTIME* runtime = env->runtime;
  
  for (int32_t sub_id = 1; sub_id < runtime->subs_length; sub_id++) {
    SPVM_RUNTIME_SUB* sub = &runtime->subs[sub_id];
    if (sub->flag & SPVM_SUB_C_FLAG_PRECOMPILE) {
      SPVM_RUNTIME_PACKAGE* sub_package = &runtime->packages[sub->package_id];
      const char* sub_name = &runtime->string_pool[sub->name_id];
      const char* sub_package_name = &runtime->string_pool[sub_package->name_id];
      
      SPVM_STRING_BUFFER_add(string_buffer, "int32_t SPPRECOMPILE__");
      SPVM_STRING_BUFFER_add_package_name(string_buffer, sub_package_name);
      SPVM_STRING_BUFFER_add(string_buffer, "__");
      SPVM_STRING_BUFFER_add(string_buffer, (char*)sub_name);
      SPVM_STRING_BUFFER_add(string_buffer, "(SPVM_ENV* env, SPVM_VALUE* stack);\n");
    }
  }
}

void SPVM_CSOURCE_BUILDER_EXE_add_set_sub_native_addresses(SPVM_ENV* env, SPVM_PORTABLE* portable, SPVM_STRING_BUFFER* string_buffer) {

  SPVM_RUNTIME* runtime = env->runtime;
  
  for (int32_t sub_id = 1; sub_id < runtime->subs_length; sub_id++) {
    SPVM_RUNTIME_SUB* sub = &runtime->subs[sub_id];
    if (sub->flag & SPVM_SUB_C_FLAG_NATIVE) {
      SPVM_RUNTIME_PACKAGE* sub_package = &runtime->packages[sub->package_id];
      const char* sub_name = &runtime->string_pool[sub->name_id];
      const char* sub_package_name = &runtime->string_pool[sub_package->name_id];
      
      SPVM_STRING_BUFFER_add(string_buffer, "  runtime->sub_cfunc_addresses[");
      SPVM_STRING_BUFFER_add_int(string_buffer, sub->id);
      SPVM_STRING_BUFFER_add(string_buffer, "] = SPNATIVE__");
      SPVM_STRING_BUFFER_add_package_name(string_buffer, sub_package_name);
      SPVM_STRING_BUFFER_add(string_buffer, "__");
      SPVM_STRING_BUFFER_add(string_buffer, (char*)sub_name);
      SPVM_STRING_BUFFER_add(string_buffer, ";\n");
    }
  }
}

void SPVM_CSOURCE_BUILDER_EXE_add_set_sub_precompile_addresses(SPVM_ENV* env, SPVM_PORTABLE* portable, SPVM_STRING_BUFFER* string_buffer) {

  SPVM_RUNTIME* runtime = env->runtime;
  
  for (int32_t sub_id = 0; sub_id < runtime->subs_length; sub_id++) {
    SPVM_RUNTIME_SUB* sub = &runtime->subs[sub_id];
    if (sub->flag & SPVM_SUB_C_FLAG_PRECOMPILE) {
      SPVM_RUNTIME_PACKAGE* sub_package = &runtime->packages[sub->package_id];
      const char* sub_name = &runtime->string_pool[sub->name_id];
      const char* sub_package_name = &runtime->string_pool[sub_package->name_id];
      
      SPVM_STRING_BUFFER_add(string_buffer, "  runtime->sub_cfunc_addresses[");
      SPVM_STRING_BUFFER_add_int(string_buffer, sub->id);
      SPVM_STRING_BUFFER_add(string_buffer, "] = SPPRECOMPILE__");
      SPVM_STRING_BUFFER_add_package_name(string_buffer, sub_package_name);
      SPVM_STRING_BUFFER_add(string_buffer, "__");
      SPVM_STRING_BUFFER_add(string_buffer, (char*)sub_name);
      SPVM_STRING_BUFFER_add(string_buffer, ";\n");
    }
  }
}

void SPVM_CSOURCE_BUILDER_EXE_build_exe_csource(SPVM_ENV* env, SPVM_STRING_BUFFER* string_buffer, SPVM_PORTABLE* portable, const char* package_name) {
  SPVM_RUNTIME* runtime = env->runtime;
  
  SPVM_STRING_BUFFER_add(string_buffer, "#include <stdlib.h>\n");
  SPVM_STRING_BUFFER_add(string_buffer, "#include <string.h>\n");
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
  SPVM_STRING_BUFFER_add(string_buffer, "#include \"spvm_runtime_arg.h\"\n");
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
    SPVM_STRING_BUFFER_add(string_buffer, ".name_id = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_field->name_id);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".signature_id = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_field->signature_id);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".basic_type_id = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_field->basic_type_id);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".package_id = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_field->package_id);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".index = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_field->index);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".flag = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_field->flag);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".offset = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_field->offset);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".type_dimension = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_field->type_dimension);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".runtime_type_category = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_field->runtime_type_category);
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
    SPVM_STRING_BUFFER_add(string_buffer, ".flag = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_package->flag);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".constant_pool_base = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_package->constant_pool_base);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".fields_base = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_package->fields_base);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".subs_base = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_package->subs_base);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".package_vars_base = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_package->package_vars_base);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".begin_sub_id = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_package->begin_sub_id);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".no_dup_field_access_field_ids_constant_pool_id = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_package->no_dup_field_access_field_ids_constant_pool_id);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".no_dup_package_var_access_package_var_ids_constant_pool_id = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_package->no_dup_package_var_access_package_var_ids_constant_pool_id);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".no_dup_call_sub_sub_ids_constant_pool_id = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_package->no_dup_call_sub_sub_ids_constant_pool_id);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".no_dup_basic_type_ids_constant_pool_id = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_package->no_dup_basic_type_ids_constant_pool_id);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".fields_length = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_package->fields_length);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".subs_length = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_package->subs_length);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".package_vars_length = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_package->package_vars_length);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".fields_byte_size = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_package->fields_byte_size);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".object_fields_offset = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_package->object_fields_offset);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".object_fields_length = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_package->object_fields_length);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, "}");

    SPVM_STRING_BUFFER_add(string_buffer, ",\n");
  }
  SPVM_STRING_BUFFER_add(string_buffer, "  };\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  portable->packages = packages;\n");

  // subs
  SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_RUNTIME_SUB subs[");
  SPVM_STRING_BUFFER_add_int(string_buffer, portable->subs_length + 1);
  SPVM_STRING_BUFFER_add(string_buffer, "] = {\n");
  for (int32_t sub_index = 0; sub_index < portable->subs_length; sub_index++) {
    SPVM_RUNTIME_SUB* runtime_sub = &portable->subs[sub_index];

    SPVM_STRING_BUFFER_add(string_buffer, "    {");
    SPVM_STRING_BUFFER_add(string_buffer, ".id = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_sub->id);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".name_id = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_sub->name_id);
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
    SPVM_STRING_BUFFER_add(string_buffer, ".return_basic_type_id = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_sub->return_basic_type_id);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".opcodes_base = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_sub->opcodes_base);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".arg_ids_base = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_sub->arg_ids_base);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".opcodes_length = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_sub->opcodes_length);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".return_type_flag = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_sub->return_type_flag);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".flag = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_sub->flag);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".mortal_stack_length = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_sub->mortal_stack_length);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".arg_ids_length = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_sub->arg_ids_length);
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
    SPVM_STRING_BUFFER_add(string_buffer, ".return_type_dimension = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_sub->return_type_dimension);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".call_type_id = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_sub->call_type_id);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".args_alloc_length = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_sub->args_alloc_length);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".return_runtime_type_category = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_sub->return_runtime_type_category);
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

  // packages_length
  SPVM_STRING_BUFFER_add(string_buffer, "  portable->packages_length = ");
  SPVM_STRING_BUFFER_add_int(string_buffer, portable->packages_length);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");

  // args
  SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_RUNTIME_ARG args[");
  SPVM_STRING_BUFFER_add_int(string_buffer, portable->args_length + 1);
  SPVM_STRING_BUFFER_add(string_buffer, "] = {\n");
  for (int32_t arg_id = 0; arg_id < portable->args_length; arg_id++) {
    SPVM_RUNTIME_ARG* runtime_arg = &portable->args[arg_id];
    SPVM_STRING_BUFFER_add(string_buffer, "    {");
    SPVM_STRING_BUFFER_add(string_buffer, ".basic_type_id = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_arg->basic_type_id);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".mem_id = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_arg->mem_id);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".type_flag = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_arg->type_flag);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".type_dimension = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_arg->type_dimension);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".runtime_type_category = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_arg->runtime_type_category);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, ".type_width = ");
    SPVM_STRING_BUFFER_add_int(string_buffer, runtime_arg->type_width);
    SPVM_STRING_BUFFER_add(string_buffer, ", ");
    SPVM_STRING_BUFFER_add(string_buffer, "}");
    SPVM_STRING_BUFFER_add(string_buffer, ",\n");
  }
  SPVM_STRING_BUFFER_add(string_buffer, "  };\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  portable->args = args;\n");

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

  // string_pool
  SPVM_STRING_BUFFER_add(string_buffer, "  char string_pool[/* ");
  SPVM_STRING_BUFFER_add_int(string_buffer, portable->string_pool_length + 1);
  SPVM_STRING_BUFFER_add(string_buffer, " */] = \"");
  for (int32_t string_pool_id = 0; string_pool_id < portable->string_pool_length; string_pool_id++) {
    SPVM_STRING_BUFFER_add_hex_char(string_buffer,  portable->string_pool[string_pool_id]);
  }
  SPVM_STRING_BUFFER_add(string_buffer, "\";\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  portable->string_pool = string_pool;\n");

  // string_pool_length
  SPVM_STRING_BUFFER_add(string_buffer, "  portable->string_pool_length = ");
  SPVM_STRING_BUFFER_add_int(string_buffer, portable->string_pool_length);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");

  // constant_pool
  SPVM_STRING_BUFFER_add(string_buffer, "  int32_t constant_pool[/* ");
  SPVM_STRING_BUFFER_add_int(string_buffer, portable->constant_pool_length + 1);
  SPVM_STRING_BUFFER_add(string_buffer, " */] = {\n");
  for (int32_t constant_pool_id = 0; constant_pool_id < portable->constant_pool_length; constant_pool_id++) {
    SPVM_STRING_BUFFER_add(string_buffer, "    ");
    SPVM_STRING_BUFFER_add_int(string_buffer,  portable->constant_pool[constant_pool_id]);
    SPVM_STRING_BUFFER_add(string_buffer, ",\n");
  }
  SPVM_STRING_BUFFER_add(string_buffer, "};\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  portable->constant_pool = constant_pool;\n");

  // constant_pool_length
  SPVM_STRING_BUFFER_add(string_buffer, "  portable->constant_pool_length = ");
  SPVM_STRING_BUFFER_add_int(string_buffer, portable->constant_pool_length);
  SPVM_STRING_BUFFER_add(string_buffer, ";\n");

  // Build runtime
  SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_RUNTIME* runtime = SPVM_RUNTIME_API_build_runtime(portable);\n");
  
  // Create env
  SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_ENV* env = SPVM_RUNTIME_API_create_env(runtime);\n");
  
  // Bins native addresse
  SPVM_CSOURCE_BUILDER_EXE_add_set_sub_native_addresses(env, portable, string_buffer);
  
  // Bind precompile addresses
  SPVM_CSOURCE_BUILDER_EXE_add_set_sub_precompile_addresses(env, portable, string_buffer);
  
  // Call begin blocks
  SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_RUNTIME_API_call_begin_blocks(env);\n");
  
  
  // Call entry point sub
  SPVM_STRING_BUFFER_add(string_buffer, "  const char* package_name = \"");
  SPVM_STRING_BUFFER_add(string_buffer, (char*)package_name);
  SPVM_STRING_BUFFER_add(string_buffer, "\";\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  int32_t status_code = SPVM_RUNTIME_API_call_entry_point_sub(env, package_name, argc, argv);\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_RUNTIME_API_free_env(env);\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  SPVM_RUNTIME_API_free_runtime(runtime);\n");
  SPVM_STRING_BUFFER_add(string_buffer, "  return status_code;\n");
  SPVM_STRING_BUFFER_add(string_buffer, "}\n");
}
