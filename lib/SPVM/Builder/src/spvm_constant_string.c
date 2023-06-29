// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include "spvm_constant_string.h"
#include "spvm_allocator.h"
#include "spvm_compiler.h"
#include "spvm_list.h"
#include "spvm_hash.h"
#include "spvm_string_buffer.h"

SPVM_CONSTANT_STRING* SPVM_CONSTANT_STRING_new(SPVM_COMPILER* compiler, const char* value, int32_t length) {
  
  SPVM_CONSTANT_STRING* found_string = SPVM_HASH_get(compiler->global_constant_string_symtable, value, length);
  if (found_string) {
    return found_string;
  }
  else {
    SPVM_CONSTANT_STRING* string = SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->allocator, sizeof(SPVM_CONSTANT_STRING));
    string->value = SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->allocator, length + 1);
    memcpy((char*)string->value, value, length);
    string->length = length;
    
    SPVM_LIST_push(compiler->global_constant_strings, string);
    SPVM_HASH_set(compiler->global_constant_string_symtable, string->value, length, string);
    
    return string;
  }
}
