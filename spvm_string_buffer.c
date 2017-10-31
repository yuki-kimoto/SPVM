#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "spvm_string_buffer.h"
#include "spvm_util_allocator.h"
#include "spvm_value.h"

SPVM_STRING_BUFFER* SPVM_STRING_BUFFER_new(int32_t page_byte_size) {
  
  SPVM_STRING_BUFFER* string_buffer = (SPVM_STRING_BUFFER*) SPVM_UTIL_ALLOCATOR_safe_malloc_zero(sizeof(SPVM_STRING_BUFFER));
  
  string_buffer->capacity = 0xFFFF;
  string_buffer->buffer = (char*)SPVM_UTIL_ALLOCATOR_safe_malloc_zero(string_buffer->capacity);
  
  return string_buffer;
}

void* SPVM_STRING_BUFFER_add(SPVM_STRING_BUFFER* string_buffer, char* string) {
  
  assert(byte_size > 0);
  
  if (byte_size > string_buffer->page_byte_size) {
    fprintf(stderr, "Very lerge memory byte size is specified(SPVM_STRING_BUFFER_alloc())\n");
    abort();
  }
  
  // Adjust alignment
  int32_t aligned_byte_size = (byte_size - 1) + ((int32_t)sizeof(SPVM_VALUE) - ((byte_size - 1) % (int32_t)sizeof(SPVM_VALUE)));
  
  // Move to next page
  if (string_buffer->current_offset + aligned_byte_size > string_buffer->page_byte_size) {
    // Next page is not yet allocated
    string_buffer->current_page++;
    string_buffer->current_offset = 0;
    
    if (string_buffer->current_page == string_buffer->pages_length) {
      int32_t new_string_buffer_pages_length = string_buffer->pages_length * 2;
      
      int64_t new_pages_byte_size = (int64_t)new_string_buffer_pages_length * (int64_t)sizeof(char*);
      char** new_pages = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(new_pages_byte_size);
      memcpy(new_pages, string_buffer->pages, string_buffer->pages_length * sizeof(char*));
      free(string_buffer->pages);
      string_buffer->pages = new_pages;
      
      {
        int32_t i;
        for (i = string_buffer->pages_length; i < new_string_buffer_pages_length; i++) {
          string_buffer->pages[i] = SPVM_UTIL_ALLOCATOR_safe_malloc_zero(string_buffer->page_byte_size);
        }
      }
      
      string_buffer->pages_length = new_string_buffer_pages_length;
    }
  }
  
  // Allocated address
  char* alloc_address = string_buffer->pages[string_buffer->current_page] + string_buffer->current_offset;
  
  string_buffer->current_offset += aligned_byte_size;
  
  return alloc_address;
}

void SPVM_STRING_BUFFER_free(SPVM_STRING_BUFFER* string_buffer) {
  
  free(string_buffer->buffer);
  
  free(string_buffer);
}
