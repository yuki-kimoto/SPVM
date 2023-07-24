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

SPVM_STRING* SPVM_STRING_new_global(SPVM_COMPILER* compiler, const char* value, int32_t length) {
  
  SPVM_STRING* found_global_string = SPVM_HASH_get(compiler->global_string_symtable, value, length);
  if (found_global_string) {
    return found_global_string;
  }
  else {
    SPVM_STRING* global_string = SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->global_allocator, sizeof(SPVM_STRING));
    global_string->value = SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->global_allocator, length + 1);
    memcpy((char*)global_string->value, value, length);
    global_string->length = length;
    
    SPVM_LIST_push(compiler->global_strings, global_string);
    SPVM_HASH_set(compiler->global_string_symtable, global_string->value, length, global_string);
    
    return global_string;
  }
}

SPVM_STRING* SPVM_STRING_new_global_tmp(SPVM_COMPILER* compiler, const char* value, int32_t length) {
  
  SPVM_STRING* global_string = SPVM_ALLOCATOR_alloc_memory_block_tmp(compiler->global_allocator, sizeof(SPVM_STRING));
  global_string->value = SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->global_allocator, length + 1);
  memcpy((char*)global_string->value, value, length);
  global_string->length = length;
  
  return global_string;
}

void SPVM_STRING_free_global_tmp(SPVM_COMPILER* compiler, SPVM_STRING* string) {
  
  SPVM_ALLOCATOR_free_memory_block_tmp(compiler->global_allocator, string);
}
