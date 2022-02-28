#include "spvm_string.h"
#include "spvm_allocator.h"
#include "spvm_compiler.h"
#include "spvm_list.h"
#include "spvm_hash.h"

SPVM_STRING* SPVM_STRING_new(SPVM_COMPILER* compiler, const char* value, int32_t length) {
  
  SPVM_STRING* found_string = SPVM_HASH_fetch(compiler->string_symtable, value, length);
  if (found_string) {
    return found_string;
  }
  else {
    char* new_value = SPVM_ALLOCATOR_new_block_compile_eternal(compiler, length + 1);
    memcpy(new_value, value, length);
    new_value[length] = '\0';
    
    SPVM_STRING* string = SPVM_ALLOCATOR_new_block_compile_eternal(compiler, sizeof(SPVM_STRING));
    string->value = new_value;
    string->length = length;
    string->id = compiler->strings->length;

    SPVM_LIST_push(compiler->strings, string);
    SPVM_HASH_insert(compiler->string_symtable, new_value, length, string);
    
    return string;
  }
}
