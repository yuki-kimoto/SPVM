#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"

#include "ppport.h"

#include <stdint.h>
#include <assert.h>

#include "spvm_compiler.h"
#include "spvm_hash.h"
#include "spvm_array.h"
#include "spvm_util_allocator.h"
#include "spvm_constant_pool.h"
#include "spvm_bytecode_array.h"
#include "spvm_runtime.h"
#include "spvm_op.h"
#include "spvm_sub.h"
#include "spvm_package.h"
#include "spvm_sub.h"
#include "spvm_my_var.h"
#include "spvm_type.h"
#include "spvm_env.h"

MODULE = SPVM::Data		PACKAGE = SPVM::Data

SV*
value(...)
  PPCODE:
{
  SV* sv_self = ST(0);

  if (sv_isobject(sv_self) && sv_derived_from(sv_self, "SPVM::Data")) {
    HV* hv_self = (HV*)SvRV(sv_self);
    
    SV** sv_type_name_ptr = hv_fetch(hv_self, "type_name", strlen("type_name"), 0);
    SV* sv_type_name = sv_type_name_ptr ? *sv_type_name_ptr : &PL_sv_undef;
    const char* type_name = SvPV_nolen(sv_type_name);
    
    SV** sv_value_ptr = hv_fetch(hv_self, "value", strlen("value"), 0);
    SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
    
    SV* sv_return_value;
  
    if (strEQ(type_name, "byte")) {
      int8_t value = (int8_t)SvIV(sv_value);
      sv_return_value = sv_2mortal(newSViv(value));
    }
    else if (strEQ(type_name, "short")) {
      int16_t value = (int16_t)SvIV(sv_value);
      sv_return_value = sv_2mortal(newSViv(value));
    }
    else if (strEQ(type_name, "int")) {
      int32_t value = (int32_t)SvIV(sv_value);
      sv_return_value = sv_2mortal(newSViv(value));
    }
    else if (strEQ(type_name, "long")) {
      int64_t value = (int64_t)SvIV(sv_value);
      sv_return_value = sv_2mortal(newSViv(value));
    }
    else if (strEQ(type_name, "float")) {
      IV iv_value = SvIV(sv_value);
      float value;
      memcpy(&value, &iv_value, sizeof(float));
      sv_return_value = sv_2mortal(newSVnv(value));
    }
    else if (strEQ(type_name, "double")) {
      IV iv_value = SvIV(sv_value);
      double value;
      memcpy(&value, &iv_value, sizeof(double));
      sv_return_value = sv_2mortal(newSVnv(value));
    }
    else {
      croak("Can't get reference value");
    }
    
    XPUSHs(sv_return_value);
    XSRETURN(1);
  }
  else {
    croak("Not SPVM::Datg object");
  }
}

MODULE = SPVM		PACKAGE = SPVM

SV*
compile(...)
  PPCODE:
{
  // Create compiler
  SPVM_COMPILER* compiler = SPVM_COMPILER_new();

  // Add package
  AV* av_package_infos = get_av("SPVM::PACKAGE_INFOS", 0);
  int32_t av_package_infos_length = (int32_t)av_len(av_package_infos) + 1;
  {
    int32_t i;
    for (i = 0; i < av_package_infos_length; i++) {
      SV** sv_package_info_ptr = av_fetch(av_package_infos, i, 0);
      SV* sv_package_info = sv_package_info_ptr ? *sv_package_info_ptr : &PL_sv_undef;
      HV* hv_package_info = (HV*)SvRV(sv_package_info);
      
      // Name
      SV** sv_name_ptr = hv_fetch(hv_package_info, "name", strlen("name"), 0);
      SV* sv_name = sv_name_ptr ? *sv_name_ptr : &PL_sv_undef;
      const char* name = SvPV_nolen(sv_name);
      
      // File
      SV** sv_file_ptr = hv_fetch(hv_package_info, "file", strlen("file"), 0);
      SV* sv_file = sv_file_ptr ? *sv_file_ptr : &PL_sv_undef;
      const char* file = SvPV_nolen(sv_file);
      
      // Line
      SV** sv_line_ptr = hv_fetch(hv_package_info, "line", strlen("line"), 0);
      SV* sv_line = sv_line_ptr ? *sv_line_ptr : &PL_sv_undef;
      int32_t line = (int32_t)SvIV(sv_line);
      
      // push package to compiler use stack
      SPVM_OP* op_use_package = SPVM_OP_new_op_use_from_package_name(compiler, name, file, line);
      SPVM_ARRAY_push(compiler->op_use_stack, op_use_package);
      SPVM_HASH_insert(compiler->op_use_symtable, name, strlen(name), op_use_package);
    }
  }
  
  // Add include paths
  AV* av_include_paths = get_av("main::INC", 0);;
  int32_t av_include_paths_length = (int32_t)av_len(av_include_paths) + 1;
  {
    int32_t i;
    for (i = 0; i < av_include_paths_length; i++) {
      SV** sv_include_path_ptr = av_fetch(av_include_paths, i, 0);
      SV* sv_include_path = sv_include_path_ptr ? *sv_include_path_ptr : &PL_sv_undef;
      char* include_path = SvPV_nolen(sv_include_path);
      SPVM_ARRAY_push(compiler->include_pathes, include_path);
    }
  }
  
  // Compile SPVM
  SPVM_COMPILER_compile(compiler);
  if (compiler->error_count > 0) {
    croak("SPVM compile error %d", compiler->error_count);
  }
  
  // Set compiler
  size_t iv_compiler = PTR2IV(compiler);
  SV* sviv_compiler = sv_2mortal(newSViv(iv_compiler));
  SV* sv_compiler = sv_2mortal(newRV_inc(sviv_compiler));
  sv_setsv(get_sv("SPVM::COMPILER", 0), sv_compiler);
  
  XSRETURN(0);
}

SV*
build_sub_symtable(...)
  PPCODE:
{
  // Get compiler
  SV* sv_compiler = get_sv("SPVM::COMPILER", 0);
  SV* sviv_compiler = SvROK(sv_compiler) ? SvRV(sv_compiler) : sv_compiler;
  size_t iv_compiler = SvIV(sviv_compiler);
  SPVM_COMPILER* compiler = INT2PTR(SPVM_COMPILER*, iv_compiler);
  
  // Subroutine information
  HV* hv_sub_symtable = get_hv("SPVM::SUB_SYMTABLE", 0);
  
  // abs_name, arg_types, return_type, constant_pool_index, type_id
  SPVM_ARRAY* op_packages = compiler->op_packages;
  {
    int32_t package_index;
    for (package_index = 0; package_index < op_packages->length; package_index++) {
      SPVM_OP* op_package = SPVM_ARRAY_fetch(op_packages, package_index);
      SPVM_ARRAY* op_subs = op_package->uv.package->op_subs;
      {
        int32_t sub_index;
        for (sub_index = 0; sub_index < op_subs->length; sub_index++) {
          // Sub information
          AV* av_sub_info = (HV*)sv_2mortal((SV*)newAV());
          
          SPVM_OP* op_sub = SPVM_ARRAY_fetch(op_subs, sub_index);
          SPVM_SUB* sub = op_sub->uv.sub;
          const char* sub_abs_name = sub->abs_name;
          
          // 1. Constant pool index
          int32_t constant_pool_index = sub->constant_pool_index;
          SV* sv_constant_pool_index = sv_2mortal(newSViv(constant_pool_index));
          av_push(av_sub_info, SvREFCNT_inc(sv_constant_pool_index));
          
          // arg_type_ids
          AV* av_arg_type_names = (AV*)sv_2mortal((SV*)newAV());
          SPVM_ARRAY* op_args = sub->op_args;
          {
            int32_t arg_index;
            for (arg_index = 0; arg_index < op_args->length; arg_index++) {
              SPVM_OP* op_arg = SPVM_ARRAY_fetch(op_args, arg_index);
              SPVM_OP* op_arg_type = op_arg->uv.my_var->op_type;
              const char* arg_type_name = op_arg_type->uv.type->name;
              
              SV* sv_arg_type_name = sv_2mortal(newSVpv(arg_type_name, 0));
              av_push(av_arg_type_names, SvREFCNT_inc(sv_arg_type_name));
            }
          }
          
          // 2. Push argment resolved type ids
          SV* sv_arg_type_names = sv_2mortal(newRV_inc((SV*)av_arg_type_names));
          av_push(av_sub_info, SvREFCNT_inc(sv_arg_type_names));
          
          // Return type
          SPVM_OP* op_return_type = sub->op_return_type;
          SPVM_TYPE* return_type = SPVM_OP_get_type(compiler, op_return_type);
          if (return_type) {
            const char* return_type_name = op_return_type->uv.type->name;
            SV* sv_return_type_name = sv_2mortal(newSVpv(return_type_name, 0));
            
            // 3. Push return type resolved id
            av_push(av_sub_info, SvREFCNT_inc(sv_return_type_name));
          }
          else {
            av_push(av_sub_info, &PL_sv_undef);
          }
          
          SV* sv_sub_info = sv_2mortal(newRV_inc((SV*)av_sub_info));
          hv_store(hv_sub_symtable, sub_abs_name, strlen(sub_abs_name), SvREFCNT_inc(sv_sub_info), 0);
        }
      }
    }
  }
  
  XSRETURN(0);
}

SV*
build_type_symtable(...)
  PPCODE:
{
  // Get compiler
  SV* sv_compiler = get_sv("SPVM::COMPILER", 0);
  SV* sviv_compiler = SvROK(sv_compiler) ? SvRV(sv_compiler) : sv_compiler;
  size_t iv_compiler = SvIV(sviv_compiler);
  SPVM_COMPILER* compiler = INT2PTR(SPVM_COMPILER*, iv_compiler);
  
  // Subroutine information
  HV* hv_type_symtable = get_hv("SPVM::TYPE_SYMTABLE", 0);
  
  // abs_name, arg_types, return_type, constant_pool_index, type_id
  SPVM_ARRAY* types = compiler->types;
  {
    int32_t type_index;
    for (type_index = 0; type_index < types->length; type_index++) {
      SPVM_TYPE* type = SPVM_ARRAY_fetch(types, type_index);
      
      const char* type_name = type->name;
      int32_t type_id = type->id;
      SV* sv_type_id = sv_2mortal(newSViv(type_id));
      
      hv_store(hv_type_symtable, type_name, strlen(type_name), SvREFCNT_inc(sv_type_id), 0);
    }
  }
  
  XSRETURN(0);
}

SV*
build_runtime(...)
  PPCODE:
{
  // Get compiler
  SV* sv_compiler = get_sv("SPVM::COMPILER", 0);
  SV* sviv_compiler = SvROK(sv_compiler) ? SvRV(sv_compiler) : sv_compiler;
  size_t iv_compiler = SvIV(sviv_compiler);
  SPVM_COMPILER* compiler = INT2PTR(SPVM_COMPILER*, iv_compiler);
  
  // Create run-time
  SPVM_RUNTIME* runtime = SPVM_RUNTIME_new();
  
  // Copy constant pool to runtime
  runtime->constant_pool = SPVM_UTIL_ALLOCATOR_safe_malloc_i32(compiler->constant_pool->length, sizeof(int32_t));
  memcpy(runtime->constant_pool, compiler->constant_pool->values, compiler->constant_pool->length * sizeof(int32_t));

  // Copy bytecodes to runtime
  runtime->bytecodes = SPVM_UTIL_ALLOCATOR_safe_malloc_i32(compiler->bytecode_array->length, sizeof(uint8_t));
  memcpy(runtime->bytecodes, compiler->bytecode_array->values, compiler->bytecode_array->length * sizeof(uint8_t));
  
  // Runtime
  size_t iv_runtime = PTR2IV(runtime);
  SV* sviv_runtime = sv_2mortal(newSViv(iv_runtime));
  SV* sv_runtime = sv_2mortal(newRV_inc(sviv_runtime));
  sv_setsv(get_sv("SPVM::RUNTIME", 0), sv_runtime);
  
  XSRETURN(0);
}

SV*
free_compiler(...)
  PPCODE:
{
  // Get compiler
  SV* sv_compiler = get_sv("SPVM::COMPILER", 0);
  SV* sviv_compiler = SvROK(sv_compiler) ? SvRV(sv_compiler) : sv_compiler;
  size_t iv_compiler = SvIV(sviv_compiler);
  SPVM_COMPILER* compiler = INT2PTR(SPVM_COMPILER*, iv_compiler);
  
  // Free compiler
  SPVM_COMPILER_free(compiler);
  
  // Set undef to compiler
  sv_setsv(get_sv("SPVM::COMPILER", 0), &PL_sv_undef);
  
  XSRETURN(0);
}

SV*
call_sub(...)
  PPCODE:
{
  SV* sv_sub_abs_name = ST(0);
  
  HV* hv_sub_symtable = get_hv("SPVM::SUB_SYMTABLE", 0);
  
  const char* sub_abs_name = SvPV_nolen(sv_sub_abs_name);
  SV** sv_sub_info_ptr = hv_fetch(hv_sub_symtable, sub_abs_name, strlen(sub_abs_name), 0);
  SV* sv_sub_info = sv_sub_info_ptr ? *sv_sub_info_ptr : &PL_sv_undef;
  AV* av_sub_info = (AV*)SvRV(sv_sub_info);
  
  # Constant poll index
  SV** sv_sub_constant_pool_index_ptr = av_fetch(av_sub_info, 0, 0);
  SV* sv_sub_constant_pool_index = sv_sub_constant_pool_index_ptr ? *sv_sub_constant_pool_index_ptr : &PL_sv_undef;
  int32_t sub_constant_pool_index = (int32_t)SvIV(sv_sub_constant_pool_index);
  
  # Argument return types
  SV** sv_arg_type_names_ptr = av_fetch(av_sub_info, 1, 0);
  SV* sv_arg_type_names = sv_arg_type_names_ptr ? *sv_arg_type_names_ptr : &PL_sv_undef;
  AV* av_arg_type_names = (AV*)SvRV(sv_arg_type_names);
  int32_t args_length = av_len(av_arg_type_names) + 1;
  
  # Return type
  SV** sv_return_type_name_ptr = av_fetch(av_sub_info, 2, 0);
  SV* sv_return_type_name = sv_return_type_name_ptr ? *sv_return_type_name_ptr : &PL_sv_undef;
  
  // Get runtime
  SV* sv_runtime = get_sv("SPVM::RUNTIME", 0);
  SV* sviv_runtime = SvROK(sv_runtime) ? SvRV(sv_runtime) : sv_runtime;
  size_t iv_runtime = SvIV(sviv_runtime);
  SPVM_RUNTIME* runtime = INT2PTR(SPVM_RUNTIME*, iv_runtime);
  SPVM_ENV* env = runtime->env;
  
  // Initialize runtime before push arguments and call subroutine
  SPVM_RUNTIME_init(env);
  
  // Check argument count
  if (items - 1 != args_length) {
    croak("Argument count is defferent");
  }
  
  // Push arguments
  {
    int32_t arg_index;
    for (arg_index = 0; arg_index < args_length; arg_index++) {
      SV* sv_data = ST(arg_index + 1);
      
      if (sv_isobject(sv_data) && sv_derived_from(sv_data, "SPVM::Data")) {
        HV* hv_data = (HV*)SvRV(sv_data);
        
        SV** sv_data_type_name_ptr = hv_fetch(hv_data, "type_name", strlen("type_name"), 0);
        SV* sv_data_type_name = sv_data_type_name_ptr ? *sv_data_type_name_ptr : &PL_sv_undef;
        const char* data_type_name = SvPV_nolen(sv_data_type_name);
        
        SV** sv_arg_type_name_ptr = av_fetch(av_arg_type_names, arg_index, 0);
        SV* sv_arg_type_name = sv_arg_type_name_ptr ? *sv_arg_type_name_ptr : &PL_sv_undef;
        const char* arg_type_name = SvPV_nolen(sv_arg_type_name);
        
        if (!strEQ(data_type_name, arg_type_name)) {
          croak("Argument data type need %s, but %s", arg_type_name, data_type_name);
        }
        
        SV** sv_value_ptr = hv_fetch(hv_data, "value", strlen("value"), 0);
        SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
        
        if (strEQ(data_type_name, "byte")) {
          int8_t value = (int8_t)SvIV(sv_value);
          env->push_var_byte(env, value);
        }
        else if (strEQ(data_type_name, "short")) {
          IV value = SvIV(sv_value);
          env->push_var_short(env, value);
        }
        else if (strEQ(data_type_name, "int")) {
          int32_t value = (int32_t)SvIV(sv_value);
          env->push_var_int(env, value);
        }
        else if (strEQ(data_type_name, "long")) {
          int64_t value = (int64_t)SvIV(sv_value);
          env->push_var_long(env, value);
        }
        else if (strEQ(data_type_name, "float")) {
          IV iv_value = SvIV(sv_value);
          float value;
          memcpy(&value, &iv_value, sizeof(float));
          env->push_var_float(env, value);
        }
        else if (strEQ(data_type_name, "double")) {
          IV iv_value = SvIV(sv_value);
          double value;
          memcpy(&value, &iv_value, sizeof(double));
          env->push_var_double(env, value);
        }
        else {
          assert(0);
        }
      }
      else {
        croak("Only receive SPVM::Data");
      }
    }
  }
  
  env->call_sub(env, sub_constant_pool_index);
  
  if (SvOK(sv_return_type_name)) {
    // Create data
    HV* hv_data = sv_2mortal((SV*)newHV());
    SV* sv_data = sv_2mortal(newRV_inc((SV*)hv_data));
    HV* hv_class = gv_stashpv("SPVM::Data", 0);
    sv_bless(sv_data, hv_class);

    const char* return_type_name = SvPV_nolen(sv_return_type_name);
    SV* sv_value;
    if (strEQ(return_type_name, "byte")) {
      int8_t return_value = env->pop_return_value_byte(env);
      sv_value = sv_2mortal(newSViv(return_value));
    }
    else if (strEQ(return_type_name, "short")) {
      int16_t return_value = env->pop_return_value_short(env);
      sv_value = sv_2mortal(newSViv(return_value));
    }
    else if (strEQ(return_type_name, "int")) {
      int32_t return_value = env->pop_return_value_int(env);
      sv_value = sv_2mortal(newSViv(return_value));
    }
    else if (strEQ(return_type_name, "long")) {
      int64_t return_value = env->pop_return_value_long(env);
      sv_value = sv_2mortal(newSViv(return_value));
    }
    else if (strEQ(return_type_name, "float")) {
      float return_value = env->pop_return_value_float(env);
      int64_t spvm_value;
      memcpy(&spvm_value, &return_value, sizeof(float));
      sv_value = sv_2mortal(newSViv(spvm_value));
    }
    else if (strEQ(return_type_name, "double")) {
      double return_value = env->pop_return_value_double(env);
      int64_t spvm_value;
      memcpy(&spvm_value, &return_value, sizeof(double));
      sv_value = sv_2mortal(newSViv(spvm_value));
    }
    else {
      void* return_value = env->pop_return_value_address(env);
      sv_value = sv_2mortal(newSViv(return_value));
    }
    
    // Store value
    hv_store(hv_data, "value", strlen("value"), SvREFCNT_inc(sv_value), 0);
    
    // Store resolved type name
    SV* sv_return_type_name = sv_2mortal(newSVpv(return_type_name, 0));
    hv_store(hv_data, "type_name", strlen("type_name"), SvREFCNT_inc(sv_return_type_name), 0);
    
    {
      SV** sv_type_name_ptr = hv_fetch(hv_data, "type_name", strlen("type_name"), 0);
      SV* sv_type_name = sv_type_name_ptr ? *sv_type_name_ptr : &PL_sv_undef;
      const char* type_name = SvPV_nolen(sv_type_name);
    }
    
    XPUSHs(sv_data);
    XSRETURN(1);
  }
  else {
    XSRETURN(0);
  }
}

SV*
byte(...)
  PPCODE:
{
  SV* sv_original_value = ST(0);
  
  // Create object
  HV* hv_data = sv_2mortal((SV*)newHV());
  SV* sv_data = sv_2mortal(newRV_inc((SV*)hv_data));
  HV* hv_class = gv_stashpv("SPVM::Data", 0);
  sv_bless(sv_data, hv_class);
  
  // byte
  int8_t value = SvIV(sv_original_value);
  SV* sv_value = sv_2mortal(newSViv(value));
  
  // Store value
  hv_store(hv_data, "value", strlen("value"), SvREFCNT_inc(sv_value), 0);
  
  // Store resolved type
  SV* sv_type = sv_2mortal(newSVpv("byte", 0));
  hv_store(hv_data, "type_name", strlen("type_name"), SvREFCNT_inc(sv_type), 0);
  
  XPUSHs(sv_data);
  XSRETURN(1);
}

SV*
short(...)
  PPCODE:
{
  SV* sv_original_value = ST(0);
  
  // Create object
  HV* hv_data = sv_2mortal((SV*)newHV());
  SV* sv_data = sv_2mortal(newRV_inc((SV*)hv_data));
  HV* hv_class = gv_stashpv("SPVM::Data", 0);
  sv_bless(sv_data, hv_class);
  
  // short
  int16_t value = SvIV(sv_original_value);
  SV* sv_value = sv_2mortal(newSViv(value));
  
  // Store value
  hv_store(hv_data, "value", strlen("value"), SvREFCNT_inc(sv_value), 0);
  
  // Store resolved type
  SV* sv_type = sv_2mortal(newSVpv("short", 0));
  hv_store(hv_data, "type_name", strlen("type_name"), SvREFCNT_inc(sv_type), 0);
  
  XPUSHs(sv_data);
  XSRETURN(1);
}

SV*
int(...)
  PPCODE:
{
  SV* sv_original_value = ST(0);
  
  // Create object
  HV* hv_data = sv_2mortal((SV*)newHV());
  SV* sv_data = sv_2mortal(newRV_inc((SV*)hv_data));
  HV* hv_class = gv_stashpv("SPVM::Data", 0);
  sv_bless(sv_data, hv_class);
  
  // int
  int32_t value = SvIV(sv_original_value);
  SV* sv_value = sv_2mortal(newSViv(value));
  
  // Store value
  hv_store(hv_data, "value", strlen("value"), SvREFCNT_inc(sv_value), 0);
  
  // Store resolved type
  SV* sv_type = sv_2mortal(newSVpv("int", 0));
  hv_store(hv_data, "type_name", strlen("type_name"), SvREFCNT_inc(sv_type), 0);
  
  XPUSHs(sv_data);
  XSRETURN(1);
}

SV*
long(...)
  PPCODE:
{
  SV* sv_original_value = ST(0);
  
  // Create object
  HV* hv_data = sv_2mortal((SV*)newHV());
  SV* sv_data = sv_2mortal(newRV_inc((SV*)hv_data));
  HV* hv_class = gv_stashpv("SPVM::Data", 0);
  sv_bless(sv_data, hv_class);
  
  // int
  int64_t value = SvIV(sv_original_value);
  SV* sv_value = sv_2mortal(newSViv(value));
  
  // Store value
  hv_store(hv_data, "value", strlen("value"), SvREFCNT_inc(sv_value), 0);
  
  // Store resolved type
  SV* sv_type = sv_2mortal(newSVpv("long", 0));
  hv_store(hv_data, "type_name", strlen("type_name"), SvREFCNT_inc(sv_type), 0);
  
  XPUSHs(sv_data);
  XSRETURN(1);
}

SV*
float(...)
  PPCODE:
{
  SV* sv_original_value = ST(0);
  
  // Create object
  HV* hv_data = sv_2mortal((SV*)newHV());
  SV* sv_data = sv_2mortal(newRV_inc((SV*)hv_data));
  HV* hv_class = gv_stashpv("SPVM::Data", 0);
  sv_bless(sv_data, hv_class);
  
  // float
  float value = (float)SvNV(sv_original_value);
  int64_t spvm_value;
  memcpy(&spvm_value, &value, sizeof(float));
  SV* sv_value = sv_2mortal(newSViv(spvm_value));
  
  // Store value
  hv_store(hv_data, "value", strlen("value"), SvREFCNT_inc(sv_value), 0);
  
  // Store resolved type
  SV* sv_type = sv_2mortal(newSVpv("float", 0));
  hv_store(hv_data, "type_name", strlen("type_name"), SvREFCNT_inc(sv_type), 0);
  
  XPUSHs(sv_data);
  XSRETURN(1);
}

SV*
double(...)
  PPCODE:
{
  SV* sv_original_value = ST(0);
  
  // Create object
  HV* hv_data = sv_2mortal((SV*)newHV());
  SV* sv_data = sv_2mortal(newRV_inc((SV*)hv_data));
  HV* hv_class = gv_stashpv("SPVM::Data", 0);
  sv_bless(sv_data, hv_class);
  
  // double
  double value = (double)SvNV(sv_original_value);
  int64_t spvm_value;
  memcpy(&spvm_value, &value, sizeof(double));
  SV* sv_value = sv_2mortal(newSViv(spvm_value));
  
  // Store value
  hv_store(hv_data, "value", strlen("value"), SvREFCNT_inc(sv_value), 0);
  
  // Store resolved type
  SV* sv_type = sv_2mortal(newSVpv("double", 0));
  hv_store(hv_data, "type_name", strlen("type_name"), SvREFCNT_inc(sv_type), 0);
  
  XPUSHs(sv_data);
  XSRETURN(1);
}
