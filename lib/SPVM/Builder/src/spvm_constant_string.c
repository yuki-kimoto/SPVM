// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include "spvm_constant_string.h"
#include "spvm_allocator.h"
#include "spvm_compiler.h"
#include "spvm_list.h"
#include "spvm_hash.h"
#include "spvm_string_buffer.h"

SPVM_CONSTANT_STRING* SPVM_CONSTANT_STRING_new(SPVM_COMPILER* compiler, const char* value, int32_t length) {
  
  SPVM_CONSTANT_STRING* found_string = SPVM_HASH_get(compiler->constant_string_symtable, value, length);
  if (found_string) {
    return found_string;
  }
  else {
    int32_t string_pool_id = compiler->constant_string_pool->length;
    
    SPVM_STRING_BUFFER_add_len_nullstr(compiler->constant_string_pool, (char*)value, length);
    
    SPVM_CONSTANT_STRING* string = SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->allocator, sizeof(SPVM_CONSTANT_STRING));
    string->value = (char*)(compiler->constant_string_pool->value + string_pool_id);
    string->length = length;
    string->id = compiler->constant_strings->length;
    string->string_pool_id = string_pool_id;
    
    SPVM_LIST_push(compiler->constant_strings, string);
    SPVM_HASH_set(compiler->constant_string_symtable, string->value, length, string);
    
    return string;
  }
}
