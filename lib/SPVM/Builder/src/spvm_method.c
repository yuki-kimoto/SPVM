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

int32_t SPVM_METHOD_satisfy_interface_method_requirement(SPVM_COMPILER* compiler, SPVM_BASIC_TYPE* dist_basic_type, SPVM_METHOD* dist_method, SPVM_BASIC_TYPE* src_basic_type, SPVM_METHOD* src_method, const char* type_desc) {
  
  if (dist_method->is_required && !src_method) {
    if (!dist_method->is_class_method) {
      SPVM_COMPILER_error(compiler, "The \"%s\" class must implement the \"%s\" method, which is defined as a required interface method in the \"%s\" %s.\n  at %s line %d", src_basic_type->name, dist_method->name, dist_basic_type->name, type_desc, src_basic_type->op_class->file, src_basic_type->op_class->line);
      return 0;
    }
  }
  
  if (src_method) {
    if (src_method->is_class_method) {
      if (!dist_method->is_class_method) {
        SPVM_COMPILER_error(compiler, "The \"%s\" method in the \"%s\" class must be an instance method, which is defined as an interface method in the \"%s\" %s.\n  at %s line %d", src_method->name, src_basic_type->name, dist_basic_type->name, type_desc, src_basic_type->op_class->file, src_basic_type->op_class->line);
        return 0;
      }
    }
    
    SPVM_LIST* src_method_var_decls = src_method->var_decls;
    
    SPVM_LIST* dist_method_var_decls = dist_method->var_decls;
    
    if (!(src_method->required_args_length == dist_method->required_args_length)) {
      
      SPVM_COMPILER_error(compiler, "The length of the required arguments of the \"%s\" method in the \"%s\" class must be equal to the length of the required arguments of the \"%s\" method in the \"%s\" %s.\n  at %s line %d", src_method->name, src_basic_type->name, dist_method->name, dist_basic_type->name, type_desc, src_basic_type->op_class->file, src_basic_type->op_class->line);
      return 0;
    }

    if (!(src_method->args_length >= dist_method->args_length)) {
      SPVM_COMPILER_error(compiler, "The length of the arguments of the \"%s\" method in the \"%s\" class must be greather than or equal to the length of the arguments of the \"%s\" method in the \"%s\" %s.\n  at %s line %d", src_method->name, src_basic_type->name, dist_method->name, dist_basic_type->name, type_desc, src_basic_type->op_class->file, src_basic_type->op_class->line);
      return 0;
    }
    
    for (int32_t arg_index = 1; arg_index < dist_method->args_length; arg_index++) {
      SPVM_VAR_DECL* src_method_var_decl = SPVM_LIST_get(src_method_var_decls, arg_index);
      SPVM_VAR_DECL* dist_method_var_decl = SPVM_LIST_get(dist_method_var_decls, arg_index);
      
      SPVM_TYPE* src_method_var_decl_type = src_method_var_decl->type;
      SPVM_TYPE* dist_method_var_decl_type = dist_method_var_decl->type;
      
      int32_t can_assign = SPVM_TYPE_satisfy_assignment_requirement_for_interface_method(
        compiler,
        dist_method_var_decl_type->basic_type->id, dist_method_var_decl_type->dimension, dist_method_var_decl_type->flag,
        src_method_var_decl_type->basic_type->id, src_method_var_decl_type->dimension, src_method_var_decl_type->flag
      );
      
      if (!can_assign) {
        const char* src_method_var_decl_type_name = SPVM_TYPE_new_type_name(compiler, src_method_var_decl_type->basic_type->id, src_method_var_decl_type->dimension, src_method_var_decl_type->flag);
        const char* dist_method_var_decl_type_name = SPVM_TYPE_new_type_name(compiler, dist_method_var_decl_type->basic_type->id, dist_method_var_decl_type->dimension, dist_method_var_decl_type->flag);
        
        SPVM_COMPILER_error(compiler, "The %dth argument of the \"%s\" method in the \"%s\" class which argument type is \"%s\" must be able to be assigned to the %dth argument of the \"%s\" method in the \"%s\" %s which argument type is \"%s\".\n  at %s line %d", arg_index, src_method->name, src_basic_type->name, src_method_var_decl_type_name, arg_index, dist_method->name, dist_basic_type->name, type_desc, dist_method_var_decl_type_name, src_basic_type->op_class->file, src_basic_type->op_class->line);
        return 0;
      }
    }
    
    SPVM_TYPE* src_method_return_type = src_method->return_type;
    SPVM_TYPE* dist_method_return_type = dist_method->return_type;
    
    int32_t can_assign = SPVM_TYPE_satisfy_assignment_requirement_for_interface_method(
      compiler,
      dist_method_return_type->basic_type->id, dist_method_return_type->dimension, dist_method_return_type->flag,
      src_method_return_type->basic_type->id, src_method_return_type->dimension, src_method_return_type->flag
    );
    
    if (!can_assign) {
      const char* src_method_return_type_name = SPVM_TYPE_new_type_name(compiler, src_method_return_type->basic_type->id, src_method_return_type->dimension, src_method_return_type->flag);
      const char* dist_method_return_type_name = SPVM_TYPE_new_type_name(compiler, dist_method_return_type->basic_type->id, dist_method_return_type->dimension, dist_method_return_type->flag);
      
      SPVM_COMPILER_error(compiler, "The return type of the \"%s\" method in the \"%s\" class which return type is \"%s\" must be able to be assigned to the return type of the \"%s\" method in the \"%s\" %s which return type is \"%s\".\n  at %s line %d", src_method->name, src_basic_type->name, src_method_return_type_name, dist_method->name, dist_basic_type->name, type_desc, dist_method_return_type_name, src_basic_type->op_class->file, src_basic_type->op_class->line);
      return 0;
    }
  }
  
  return 1;
}

