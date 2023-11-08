// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "spvm_hash.h"
#include "spvm_allocator.h"

SPVM_HASH* SPVM_HASH_new(SPVM_ALLOCATOR* allocator, int32_t table_capacity, int32_t memory_block_type) {
  
  assert(table_capacity >= 0);
  
  // Create hash
  SPVM_HASH* hash;
  if (memory_block_type == SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP) {
    hash = SPVM_ALLOCATOR_alloc_memory_block_tmp(allocator, sizeof(SPVM_HASH));
  }
  else if (memory_block_type == SPVM_ALLOCATOR_C_ALLOC_TYPE_PERMANENT) {
    hash = SPVM_ALLOCATOR_alloc_memory_block_permanent(allocator, sizeof(SPVM_HASH));
  }
  else {
    assert(0);
  }
  
  // Default table capacity
  if (table_capacity == 0) {
    hash->table_capacity = 1;
  }
  else {
    hash->table_capacity = table_capacity;
  }
  
  // Initialize table
  if (memory_block_type == SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP) {
    hash->table = SPVM_ALLOCATOR_alloc_memory_block_tmp(allocator, hash->table_capacity * sizeof(SPVM_HASH_ENTRY*));
  }
  else if (memory_block_type == SPVM_ALLOCATOR_C_ALLOC_TYPE_PERMANENT) {
    hash->table = SPVM_ALLOCATOR_alloc_memory_block_permanent(allocator, hash->table_capacity * sizeof(SPVM_HASH_ENTRY*));
  }
  else {
    assert(0);
  }
  
  hash->keys_length = 0;
  
  hash->allocator = allocator;
  
  hash->memory_block_type = memory_block_type;
  
  return hash;
}

SPVM_HASH* SPVM_HASH_new_hash_permanent(SPVM_ALLOCATOR* allocator, int32_t capacity) {
  
  int32_t memory_block_type = SPVM_ALLOCATOR_C_ALLOC_TYPE_PERMANENT;
  
  SPVM_HASH* hash = SPVM_HASH_new(allocator, capacity, memory_block_type);
  
  return hash;
}

void* SPVM_HASH_get(SPVM_HASH* hash, const char* key, int32_t key_length) {
  
  assert(hash);
  assert(key_length >= 0);
  
  int32_t hash_value = SPVM_HASH_calc_hash_value(key, key_length);
  int32_t table_index = hash_value % hash->table_capacity;
  
  SPVM_HASH_ENTRY* entry = hash->table[table_index];
  
  while (1) {
    if (entry) {
      int32_t match = 0;
      int32_t entry_key_length = entry->key_length;
      if (key_length == 0 && entry_key_length == 0) {
        match = 1;
      }
      else if (entry_key_length == key_length && memcmp(key, entry->key, key_length) == 0) {
        match = 1;
      }
      
      if (match) {
        return entry->value;
      }
      else {
        entry = entry->next_entry;
      }
    }
    else {
      return NULL;
    }
  }
}

void SPVM_HASH_set(SPVM_HASH* hash, const char* key, int32_t key_length, void* value) {
  
  assert(hash);
  assert(key);
  assert(key_length >= 0);
  
  // Rehash
  if (hash->keys_length > hash->table_capacity * 0.75) {
    int32_t new_table_capacity = (hash->table_capacity * 2) + 1;
    
    SPVM_HASH_rehash(hash, new_table_capacity);
  }
  
  assert(hash);
  assert(key);
  assert(key_length >= 0);
  
  int32_t hash_value = SPVM_HASH_calc_hash_value(key, key_length);
  int32_t table_index = hash_value % hash->table_capacity;
  
  SPVM_HASH_ENTRY* entry = hash->table[table_index];
  if (entry) {
    while (1) {
      int32_t match = 0;
      int32_t entry_key_length = entry->key_length;
      if (entry_key_length == 0 && key_length == 0) {
        match = 1;
      }
      else if (entry_key_length == key_length && memcmp(key, entry->key, key_length) == 0) {
        match = 1;
      }
      
      if (match) {
        entry->value = value;
        break;
      }
      else {
        if (entry->next_entry) {
          entry = entry->next_entry;
        }
        else {
          SPVM_HASH_ENTRY* new_entry = SPVM_HASH_new_hash_entry(hash, key, key_length, value);
          entry->next_entry = new_entry;
          break;
        }
      }
    }
  }
  else {
    SPVM_HASH_ENTRY* new_entry = SPVM_HASH_new_hash_entry(hash, key, key_length, value);
    hash->table[table_index] = new_entry;
  }
}

void SPVM_HASH_set_entry(SPVM_HASH_ENTRY** table, int32_t table_capacity, const char* key, int32_t key_length, SPVM_HASH_ENTRY* entry) {
  
  assert(key);
  assert(key_length >= 0);
  
  int32_t hash_value = SPVM_HASH_calc_hash_value(key, key_length);
  int32_t table_index = hash_value % table_capacity;
  
  entry->next_entry = NULL;
  
  SPVM_HASH_ENTRY* found_entry = table[table_index];
  if (found_entry) {
    while (1) {
      if (found_entry->next_entry) {
        found_entry = found_entry->next_entry;
      }
      else {
        found_entry->next_entry = entry;
        break;
      }
    }
  }
  else {
    table[table_index] = entry;
  }
}

void SPVM_HASH_free(SPVM_HASH* hash) {
  
  SPVM_ALLOCATOR* allocator = hash->allocator;
  
  assert(hash);
  
  if (hash->memory_block_type == SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP) {
    for (int32_t table_index = 0; table_index < hash->table_capacity; table_index++) {
      SPVM_HASH_ENTRY* entry = hash->table[table_index];
      
      if (entry) {
        while (1) {
          const char* key = entry->key;
          int32_t key_length = entry->key_length;
          
          SPVM_HASH_ENTRY* next_entry = entry->next_entry;
          
          SPVM_ALLOCATOR_free_memory_block_tmp(allocator, entry->key);
          entry->key = NULL;
          
          SPVM_ALLOCATOR_free_memory_block_tmp(allocator, entry);
          entry = NULL;
          
          if (next_entry) {
            entry = next_entry;
          }
          else {
            break;
          }
        }
      }
    }
    
    SPVM_ALLOCATOR_free_memory_block_tmp(allocator, hash->table);
    SPVM_ALLOCATOR_free_memory_block_tmp(allocator, hash);
  }
  else if (hash->memory_block_type == SPVM_ALLOCATOR_C_ALLOC_TYPE_PERMANENT) {
    // Nothing
  }
  else {
    assert(0);
  }
}

SPVM_HASH_ENTRY* SPVM_HASH_new_hash_entry(SPVM_HASH* hash, const char* key, int32_t key_length, void* value) {
  
  assert(hash);
  assert(key);
  
  SPVM_ALLOCATOR* allocator = hash->allocator;
  
  SPVM_HASH_ENTRY* new_entry = NULL;
  char* new_key = NULL;
  
  if (hash->memory_block_type == SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP) {
    new_entry = SPVM_ALLOCATOR_alloc_memory_block_tmp(allocator, sizeof(SPVM_HASH_ENTRY));
    new_key = SPVM_ALLOCATOR_alloc_memory_block_tmp(allocator, key_length + 1);
  }
  else if (hash->memory_block_type == SPVM_ALLOCATOR_C_ALLOC_TYPE_PERMANENT) {
    new_entry = SPVM_ALLOCATOR_alloc_memory_block_permanent(allocator, sizeof(SPVM_HASH_ENTRY));
    new_key = SPVM_ALLOCATOR_alloc_memory_block_permanent(allocator, key_length + 1);
  }
  else {
    assert(0);
  }
  
  memcpy(new_key, key, key_length);
  
  new_entry->key = new_key;
  new_entry->key_length = key_length;
  new_entry->value = value;
  
  hash->keys_length++;
  
  return new_entry;
}

void SPVM_HASH_rehash(SPVM_HASH* hash, int32_t new_table_capacity) {
  
  assert(hash);
  assert(new_table_capacity > 0);
  
  SPVM_ALLOCATOR* allocator = hash->allocator;
  
  SPVM_HASH_ENTRY** new_table = NULL;
  if (hash->memory_block_type == SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP) {
    new_table = SPVM_ALLOCATOR_alloc_memory_block_tmp(allocator, sizeof(SPVM_HASH_ENTRY) * new_table_capacity);
  }
  else if (hash->memory_block_type == SPVM_ALLOCATOR_C_ALLOC_TYPE_PERMANENT) {
    new_table = SPVM_ALLOCATOR_alloc_memory_block_permanent(allocator, sizeof(SPVM_HASH_ENTRY) * new_table_capacity);
  }
  else {
    assert(0);
  }
  
  // Rehash
  for (int32_t table_index = 0; table_index < hash->table_capacity; table_index++) {
    SPVM_HASH_ENTRY* entry = hash->table[table_index];
    
    if (entry) {
      while (1) {
        const char* key = entry->key;
        int32_t key_length = entry->key_length;
        
        SPVM_HASH_ENTRY* next_entry = entry->next_entry;
        
        SPVM_HASH_set_entry(new_table, new_table_capacity, key, key_length, entry);
        
        if (next_entry) {
          entry = next_entry;
        }
        else {
          break;
        }
      }
    }
  }
  
  // Replace hash fields
  if (hash->memory_block_type == SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP) {
    SPVM_ALLOCATOR_free_memory_block_tmp(allocator, hash->table);
  }
  else if (hash->memory_block_type == SPVM_ALLOCATOR_C_ALLOC_TYPE_PERMANENT) {
    // Nothing
  }
  else {
    assert(0);
  }
  hash->table = NULL;
  
  hash->table_capacity = new_table_capacity;
  hash->table = new_table;
}

int32_t SPVM_HASH_calc_hash_value(const char* str, int32_t len) {
  
  assert(len >= 0);
  
  const char* str_tmp = str;
  int32_t hash = 5381;
  while (len--) {
    hash = ((hash << 5) + hash) + (uint8_t) *str_tmp++;
  }
  
  if (hash < 0) {
    hash = ~hash;
  }
  
  return hash;
}
