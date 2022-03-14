#include "spvm_string.h"
#include "spvm_allocator.h"
#include "spvm_compiler.h"
#include "spvm_list.h"
#include "spvm_hash.h"
#include "spvm_string_buffer.h"

SPVM_STRING* SPVM_STRING_new(SPVM_COMPILER* compiler, const char* value, int32_t length) {
  
  SPVM_STRING* found_string = SPVM_HASH_fetch(compiler->string_symtable, value, length);
  if (found_string) {
    return found_string;
  }
  else {
    int32_t string_buffer_id = compiler->string_buffer->length;
    
    SPVM_STRING_BUFFER_add_len_nullstr(compiler->string_buffer, (char*)value, length);
    
    SPVM_STRING* string = SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->allocator, sizeof(SPVM_STRING));
    string->value = (char*)(compiler->string_buffer->buffer + string_buffer_id);
    string->length = length;
    string->id = compiler->strings->length;
    string->string_buffer_id = string_buffer_id;
    
    SPVM_LIST_push(compiler->strings, string);
    SPVM_HASH_insert(compiler->string_symtable, string->value, length, string);
    
    return string;
  }
}
