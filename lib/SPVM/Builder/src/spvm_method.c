// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include <stdlib.h>

#include "spvm_method.h"
#include "assert.h"

#include "spvm_allocator.h"
#include "spvm_compiler.h"
#include "spvm_list.h"
#include "spvm_op.h"
#include "spvm_opcode_list.h"

SPVM_METHOD* SPVM_METHOD_new(SPVM_COMPILER* compiler) {
  SPVM_METHOD* method = SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->current_each_compile_allocator, sizeof(SPVM_METHOD));
  
  method->var_decls = SPVM_LIST_new_list_permanent(compiler->current_each_compile_allocator, 0);
  method->anon_method_fields = SPVM_LIST_new_list_permanent(compiler->current_each_compile_allocator, 0);
  method->overload_method_names = SPVM_LIST_new_list_permanent(compiler->current_each_compile_allocator, 0);
  
  method->opcode_list = SPVM_OPCODE_LIST_new(compiler);
  
  return method;
}
