#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "spvm_hash.h"
#include "spvm_hash_entry.h"
#include "spvm_hash_func.h"
#include "spvm_allocator_util.h"
#include "spvm_parser.h"
#include "spvm.h"

SPVM_HASH* SPVM_HASH_new(SPVM* spvm, int32_t table_capacity) {
  (void)spvm;
  
  assert(table_capacity >= 0);

  // Create hash
  SPVM_HASH* hash = SPVM_ALLOCATOR_UTIL_safe_malloc_i32(1, sizeof(SPVM_HASH));

  // Default table capacity
  if (table_capacity == 0) {
    hash->table_capacity = 101;
  }
  else {
    hash->table_capacity = table_capacity;
  }
  
  // Initialize table
  hash->table = SPVM_ALLOCATOR_UTIL_safe_malloc_i32(hash->table_capacity, sizeof(SPVM_HASH_ENTRY*));
  memset(hash->table, 0, hash->table_capacity * sizeof(SPVM_HASH_ENTRY*));
  
  // Initialize entries
  hash->entries_capacity = 255;
  hash->entries = SPVM_ALLOCATOR_UTIL_safe_malloc_i32(hash->entries_capacity, sizeof(SPVM_HASH_ENTRY));
  hash->entries_length = 0;
  
  // Initialize key buffer
  hash->key_buffer_capacity = 0xFF;
  hash->key_buffer = SPVM_ALLOCATOR_UTIL_safe_malloc_i32(hash->key_buffer_capacity, sizeof(char));
  hash->key_buffer_length = 0;
  
  return hash;
}

void SPVM_HASH_maybe_extend_entries(SPVM* spvm, SPVM_HASH* hash) {
  (void)spvm;
  
  assert(hash);
  
  int32_t entries_length = hash->entries_length;
  
  assert(entries_length >= 0);
  
  int32_t entries_capacity = hash->entries_capacity;
  
  if (entries_length >= entries_capacity) {
    int32_t new_entries_capacity = entries_capacity * 2;
    hash->entries = SPVM_ALLOCATOR_UTIL_safe_realloc_i32(hash->entries, new_entries_capacity, sizeof(SPVM_HASH_ENTRY));
    hash->entries_capacity = new_entries_capacity;
  }
}

void SPVM_HASH_maybe_extend_key_buffer(SPVM* spvm, SPVM_HASH* hash, int32_t length) {
  (void)spvm;
  
  assert(hash);
  
  int32_t key_buffer_length = hash->key_buffer_length;
  
  assert(key_buffer_length >= 0);
  
  int32_t key_buffer_capacity = hash->key_buffer_capacity;
  
  if (key_buffer_length + length >= key_buffer_capacity) {
    int32_t new_key_buffer_capacity = key_buffer_capacity * 2;
    hash->key_buffer = SPVM_ALLOCATOR_UTIL_safe_realloc_i32(hash->key_buffer, new_key_buffer_capacity, sizeof(SPVM_HASH_ENTRY));
    hash->key_buffer_capacity = new_key_buffer_capacity;
  }
}

void SPVM_HASH_free(SPVM* spvm, SPVM_HASH* hash) {
  (void)spvm;
  
  assert(hash);
  
  free(hash->table);
  free(hash->entries);
  free(hash);
}

int32_t SPVM_HASH_new_hash_entry(SPVM* spvm, SPVM_HASH* hash, const char* key, void* value) {
  (void)spvm;
  
  assert(hash);
  assert(key);
  
  int32_t index = hash->entries_length;
  
  SPVM_HASH_maybe_extend_entries(spvm, hash);
  SPVM_HASH_ENTRY* hash_entry = &hash->entries[index];
  
  int32_t key_length = strlen(key);
  SPVM_HASH_maybe_extend_key_buffer(spvm, hash, key_length);
  
  hash_entry->key_index = hash->key_buffer_length;
  
  strncpy(&hash->key_buffer[hash->key_buffer_length], key, key_length);
  hash->key_buffer[hash->key_buffer_length + key_length] = '\0';
  
  hash->key_buffer_length += key_length + 1;
  
  *(void**)&hash_entry->value = value;
  hash_entry->next_index = -1;
  
  hash->entries_length++;
  
  return index;
}

void SPVM_HASH_rehash(SPVM* spvm, SPVM_HASH* hash, int32_t new_table_capacity) {
  (void)spvm;
  
  assert(hash);
  assert(new_table_capacity > 0);
  
  // Create new hash
  SPVM_HASH* new_hash = SPVM_HASH_new(spvm, new_table_capacity);
  
  // Rehash
  for (int32_t i = 0; i < hash->entries_length; i++) {
    SPVM_HASH_ENTRY* entry = &hash->entries[i];
    
    const char* key = &hash->key_buffer[entry->key_index];
    
    assert(key);
    
    void* value = *(void**)&entry->value;
    
    SPVM_HASH_insert_norehash(spvm, new_hash, key, strlen(key), value);
  }
  
  
  // Replace hash fields
  free(hash->table);
  free(hash->entries);
  free(hash->key_buffer);
  hash->entries_length = new_hash->entries_length;
  hash->table_capacity = new_hash->table_capacity;
  hash->entries_capacity = new_hash->entries_capacity;
  hash->table = new_hash->table;
  hash->entries = new_hash->entries;
  
  hash->key_buffer_capacity = new_hash->key_buffer_capacity;
  hash->key_buffer_length = new_hash->key_buffer_length;
  hash->key_buffer = new_hash->key_buffer;
}

void SPVM_HASH_insert_norehash(SPVM* spvm, SPVM_HASH* hash, const char* key, int32_t length, void* value) {
  (void)spvm;
  
  assert(hash);
  assert(key);
  assert(length > 0);
  
  uint32_t hash_value = SPVM_HASH_FUNC_calc_hash(spvm, key, length);
  int32_t index = hash_value % hash->table_capacity;
  
  if (hash->table[index]) {
    SPVM_HASH_ENTRY* next_entry = hash->table[index];
    while (1) {
      if (strncmp(key, &hash->key_buffer[next_entry->key_index], length) == 0) {
        *(void**)&next_entry->value = value;
        break;
      }
      else {
        if (next_entry->next_index != -1) {
          next_entry = &hash->entries[next_entry->next_index];
        }
        else {
          int32_t new_entry_index = SPVM_HASH_new_hash_entry(spvm, hash, key, value);
          next_entry->next_index = new_entry_index;
          break;
        }
      }
    }
  }
  else {
    int32_t new_entry_index = SPVM_HASH_new_hash_entry(spvm, hash, key, value);
    hash->table[index] = &hash->entries[new_entry_index];
  }
}

void SPVM_HASH_insert(SPVM* spvm, SPVM_HASH* hash, const char* key, int32_t length, void* value) {
  (void)spvm;
  
  assert(hash);
  assert(key);
  assert(length > 0);
  
  // Rehash
  if (hash->entries_length > hash->table_capacity * 0.75) {
    int32_t new_table_capacity = (hash->table_capacity * 2) + 1;
    
    SPVM_HASH_rehash(spvm, hash, new_table_capacity);
  }
  
  SPVM_HASH_insert_norehash(spvm, hash, key, length, value);
}

void* SPVM_HASH_search(SPVM* spvm, SPVM_HASH* hash, const char* key, int32_t length) {
  (void)spvm;
  
  assert(hash);
  assert(key);
  assert(length > 0);

  uint32_t hash_value = SPVM_HASH_FUNC_calc_hash(spvm, key, length);
  int32_t index = hash_value % hash->table_capacity;
  
  SPVM_HASH_ENTRY* next_entry = hash->table[index];
  while (1) {
    if (next_entry) {
      
      if (strncmp(key, &hash->key_buffer[next_entry->key_index], length) == 0) {
        return *(void**)&next_entry->value;
      }
      else {
        if (next_entry->next_index == -1) {
          next_entry = NULL;
        }
        else {
          next_entry = &hash->entries[next_entry->next_index];
        }
      }
    }
    else {
      return NULL;
    }
  }
}
