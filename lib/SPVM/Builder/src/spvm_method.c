// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include <stdlib.h>

#include "spvm_method.h"

#include "spvm_allocator.h"
#include "spvm_compiler.h"
#include "spvm_var_decl.h"
#include "spvm_list.h"
#include "spvm_op.h"
#include "spvm_type.h"
#include "spvm_basic_type.h"
#include "spvm_opcode_list.h"

SPVM_METHOD* SPVM_METHOD_new(SPVM_COMPILER* compiler) {
  SPVM_METHOD* method = SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->current_each_compile_allocator, sizeof(SPVM_METHOD));
  
  method->var_decls = SPVM_LIST_new_list_permanent(compiler->current_each_compile_allocator, 0);
  method->anon_method_fields = SPVM_LIST_new_list_permanent(compiler->current_each_compile_allocator, 0);
  
  method->opcode_list = SPVM_OPCODE_LIST_new(compiler);
  
  return method;
}

int32_t SPVM_METHOD_satisfy_method_override_requirement(SPVM_COMPILER* compiler, SPVM_BASIC_TYPE* basic_type, SPVM_METHOD* method, SPVM_BASIC_TYPE* dist_basic_type, SPVM_METHOD* dist_method, const char* type_desc) {
  
  if (dist_method->is_required && !method) {
    if (!dist_method->is_class_method) {
      SPVM_COMPILER_error(compiler, "The \"%s\" class must implement the \"%s\" method, which is defined as a required interface method in the \"%s\" %s.\n  at %s line %d", basic_type->name, dist_method->name, dist_basic_type->name, type_desc, basic_type->op_class->file, basic_type->op_class->line);
      return 0;
    }
  }
  
  if (method) {
    if (method->is_class_method) {
      if (!dist_method->is_class_method) {
        SPVM_COMPILER_error(compiler, "The \"%s\" method in the \"%s\" class must be an instance method, which is defined as an interface method in the \"%s\" %s.\n  at %s line %d", method->name, basic_type->name, dist_basic_type->name, type_desc, basic_type->op_class->file, basic_type->op_class->line);
        return 0;
      }
    }
    
    SPVM_LIST* method_var_decls = method->var_decls;
    
    SPVM_LIST* dist_method_var_decls = dist_method->var_decls;
    
    if (!(method->required_args_length == dist_method->required_args_length)) {
      
      SPVM_COMPILER_error(compiler, "The length of the required arguments of the \"%s\" method in the \"%s\" class must be equal to the length of the required arguments of the \"%s\" method in the \"%s\" %s.\n  at %s line %d", method->name, basic_type->name, dist_method->name, dist_basic_type->name, type_desc, basic_type->op_class->file, basic_type->op_class->line);
      return 0;
    }

    if (!(method->args_length >= dist_method->args_length)) {
      SPVM_COMPILER_error(compiler, "The length of the arguments of the \"%s\" method in the \"%s\" class must be greather than or equal to the length of the arguments of the \"%s\" method in the \"%s\" %s.\n  at %s line %d", method->name, basic_type->name, dist_method->name, dist_basic_type->name, type_desc, basic_type->op_class->file, basic_type->op_class->line);
      return 0;
    }
    
    for (int32_t arg_index = 1; arg_index < dist_method->args_length; arg_index++) {
      SPVM_VAR_DECL* method_var_decl = SPVM_LIST_get(method_var_decls, arg_index);
      SPVM_VAR_DECL* dist_method_var_decl = SPVM_LIST_get(dist_method_var_decls, arg_index);
      
      SPVM_TYPE* method_var_decl_type = method_var_decl->type;
      SPVM_TYPE* dist_method_var_decl_type = dist_method_var_decl->type;
      
      int32_t assignability_for_method = SPVM_TYPE_satisfy_assignment_requirement_for_method_definition(compiler, dist_method_var_decl_type->basic_type->id, dist_method_var_decl_type->dimension, dist_method_var_decl_type->flag, method_var_decl_type->basic_type->id, method_var_decl_type->dimension, method_var_decl_type->flag);
      
      if (!assignability_for_method) {
        const char* method_var_decl_type_name = SPVM_TYPE_new_type_name(compiler, method_var_decl_type->basic_type->id, method_var_decl_type->dimension, method_var_decl_type->flag);
        const char* dist_method_var_decl_type_name = SPVM_TYPE_new_type_name(compiler, dist_method_var_decl_type->basic_type->id, dist_method_var_decl_type->dimension, dist_method_var_decl_type->flag);
        
        SPVM_COMPILER_error(compiler, "The %dth argument of the \"%s\" method in the \"%s\" class which argument type is \"%s\" must be able to be assigned to the %dth argument of the \"%s\" method in the \"%s\" %s which argument type is \"%s\".\n  at %s line %d", arg_index, method->name, basic_type->name, method_var_decl_type_name, arg_index, dist_method->name, dist_basic_type->name, type_desc, dist_method_var_decl_type_name, basic_type->op_class->file, basic_type->op_class->line);
        return 0;
      }
    }
    
    SPVM_TYPE* method_return_type = method->return_type;
    SPVM_TYPE* dist_method_return_type = dist_method->return_type;
    
    int32_t assignability_for_method_definition = SPVM_TYPE_satisfy_assignment_requirement_for_method_definition(
      compiler,
      dist_method_return_type->basic_type->id, dist_method_return_type->dimension, dist_method_return_type->flag,
      method_return_type->basic_type->id, method_return_type->dimension, method_return_type->flag
    );
    
    if (!assignability_for_method_definition) {
      const char* method_return_type_name = SPVM_TYPE_new_type_name(compiler, method_return_type->basic_type->id, method_return_type->dimension, method_return_type->flag);
      const char* dist_method_return_type_name = SPVM_TYPE_new_type_name(compiler, dist_method_return_type->basic_type->id, dist_method_return_type->dimension, dist_method_return_type->flag);
      
      SPVM_COMPILER_error(compiler, "The return type of the \"%s\" method in the \"%s\" class which return type is \"%s\" must be able to be assigned to the return type of the \"%s\" method in the \"%s\" %s which return type is \"%s\".\n  at %s line %d", method->name, basic_type->name, method_return_type_name, dist_method->name, dist_basic_type->name, type_desc, dist_method_return_type_name, basic_type->op_class->file, basic_type->op_class->line);
      return 0;
    }
  }
  
  return 1;
}

