// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include "spvm_string.h"
#include "spvm_allocator.h"
#include "spvm_compiler.h"
#include "spvm_list.h"
#include "spvm_hash.h"

SPVM_STRING* SPVM_STRING_new(SPVM_COMPILER* compiler, const char* value, int32_t length) {
  
  SPVM_STRING* found_constant_string = SPVM_HASH_get(compiler->constant_string_symtable, value, length);
  if (found_constant_string) {
    return found_constant_string;
  }
  else {
    SPVM_STRING* constant_string = SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->global_allocator, sizeof(SPVM_STRING));
    constant_string->value = SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->global_allocator, length + 1);
    memcpy((char*)constant_string->value, value, length);
    constant_string->length = length;
    
    SPVM_LIST_push(compiler->constant_strings, constant_string);
    SPVM_HASH_set(compiler->constant_string_symtable, constant_string->value, length, constant_string);
    
    return constant_string;
  }
}
