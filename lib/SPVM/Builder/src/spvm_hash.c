#include <string.h>
#include <stdlib.h>
#include <assert.h>

#include "spvm_hash.h"
#include "spvm_allocator.h"
#include "spvm_allocator.h"
#include "spvm_native.h"

SPVM_HASH* SPVM_HASH_new(SPVM_ALLOCATOR* allocator, int32_t table_capacity, int32_t memory_block_type, SPVM_ENV* env) {
  
  assert(table_capacity >= 0);

  // Create hash
  SPVM_HASH* hash;
  if (memory_block_type == SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP) {
    hash = SPVM_ALLOCATOR_new_block_compile_tmp(allocator, sizeof(SPVM_HASH));
  }
  else if (memory_block_type == SPVM_ALLOCATOR_C_ALLOC_TYPE_PERMANENT) {
    hash = SPVM_ALLOCATOR_new_block_permanent(allocator, sizeof(SPVM_HASH));
  }
  else if (memory_block_type == SPVM_COMPIER_ALLOCATOR_C_MEMORY_BLOCK_TYPE_RUN_TIME) {
    hash = SPVM_ALLOCATOR_new_block_runtime(allocator, sizeof(SPVM_HASH), env);
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
    hash->table = SPVM_ALLOCATOR_new_block_compile_tmp(allocator, hash->table_capacity * sizeof(int32_t));
  }
  else if (memory_block_type == SPVM_ALLOCATOR_C_ALLOC_TYPE_PERMANENT) {
    hash->table = SPVM_ALLOCATOR_new_block_permanent(allocator, hash->table_capacity * sizeof(int32_t));
  }
  else if (memory_block_type == SPVM_COMPIER_ALLOCATOR_C_MEMORY_BLOCK_TYPE_RUN_TIME) {
    hash->table = SPVM_ALLOCATOR_new_block_runtime(allocator, hash->table_capacity * sizeof(int32_t), env);
  }
  else {
    assert(0);
  }

  memset(hash->table, -1, hash->table_capacity * sizeof(int32_t));
  
  // Initialize entries
  hash->entries_capacity = 1;

  if (memory_block_type == SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP) {
    hash->entries =  SPVM_ALLOCATOR_new_block_compile_tmp(allocator, hash->entries_capacity * sizeof(SPVM_HASH_ENTRY));
  }
  else if (memory_block_type == SPVM_ALLOCATOR_C_ALLOC_TYPE_PERMANENT) {
    hash->entries =  SPVM_ALLOCATOR_new_block_permanent(allocator, hash->entries_capacity * sizeof(SPVM_HASH_ENTRY));
  }
  else if (memory_block_type == SPVM_COMPIER_ALLOCATOR_C_MEMORY_BLOCK_TYPE_RUN_TIME) {
    hash->entries =  SPVM_ALLOCATOR_new_block_runtime(allocator, hash->entries_capacity * sizeof(SPVM_HASH_ENTRY), env);
  }
  else {
    assert(0);
  }
  hash->entries_length = 0;

  // Initialize key buffer
  hash->key_buffer_capacity = 1;
  if (memory_block_type == SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP) {
    hash->key_buffer = SPVM_ALLOCATOR_new_block_compile_tmp(allocator, hash->key_buffer_capacity);
  }
  else if (memory_block_type == SPVM_ALLOCATOR_C_ALLOC_TYPE_PERMANENT) {
    hash->key_buffer = SPVM_ALLOCATOR_new_block_permanent(allocator, hash->key_buffer_capacity);
  }
  else if (memory_block_type == SPVM_COMPIER_ALLOCATOR_C_MEMORY_BLOCK_TYPE_RUN_TIME) {
    hash->key_buffer = SPVM_ALLOCATOR_new_block_runtime(allocator, hash->key_buffer_capacity, env);
  }
  else {
    assert(0);
  }

  hash->key_buffer_length = 0;

  hash->allocator = allocator;
  
  hash->memory_block_type = memory_block_type;
  
  hash->env = env;

  return hash;
}

void SPVM_HASH_insert(SPVM_HASH* hash, const char* key, int32_t length, void* value) {
  
  assert(hash);
  assert(key);
  assert(length >= 0);
  
  // Rehash
  if (hash->entries_length > hash->table_capacity * 0.75) {
    int32_t new_table_capacity = (hash->table_capacity * 2) + 1;
    
    SPVM_HASH_rehash(hash, new_table_capacity);
  }
  
  SPVM_HASH_insert_norehash(hash, key, length, value);
}

void* SPVM_HASH_fetch(SPVM_HASH* hash, const char* key, int32_t length) {
  int32_t exists = 0;
  return SPVM_HASH_fetch_with_exists(hash, key, length, &exists);
}

void* SPVM_HASH_fetch_with_exists(SPVM_HASH* hash, const char* key, int32_t length, int32_t* exists) {

  assert(hash);
  assert(length >= 0);
  
  int32_t hash_value = SPVM_HASH_calc_hash_value(key, length);
  int32_t table_index = hash_value % hash->table_capacity;
  
  int32_t entry_index = -1;
  if (hash->table[table_index] != -1) {
    entry_index = hash->table[table_index];
  }
  while (1) {
    assert(entry_index >= -1);
    if (entry_index != -1) {
      int32_t match = 0;
      int32_t key_length;
      memcpy(&key_length, &hash->key_buffer[hash->entries[entry_index].key_index], sizeof(int32_t));
      if (length == 0 && key_length == 0) {
        match = 1;
      }
      else if (key_length == length && memcmp(key, &hash->key_buffer[hash->entries[entry_index].key_index + sizeof(int32_t)], length) == 0) {
        match = 1;
      }
      
      if (match) {
        *exists = 1;
        return hash->entries[entry_index].value;
      }
      else {
        if (hash->entries[entry_index].next_index == -1) {
          entry_index = -1;
        }
        else {
          entry_index = hash->entries[entry_index].next_index;
        }
      }
    }
    else {
      return NULL;
    }
  }
}

void SPVM_HASH_free(SPVM_HASH* hash) {

  SPVM_ALLOCATOR* allocator = hash->allocator;
  
  assert(hash);

  if (hash->memory_block_type == SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP) {
    SPVM_ALLOCATOR_free_block_compile_tmp(allocator, hash->table);
    SPVM_ALLOCATOR_free_block_compile_tmp(allocator, hash->entries);
    SPVM_ALLOCATOR_free_block_compile_tmp(allocator, hash->key_buffer);
    SPVM_ALLOCATOR_free_block_compile_tmp(allocator, hash);
  }
  else if (hash->memory_block_type == SPVM_ALLOCATOR_C_ALLOC_TYPE_PERMANENT) {
    // Nothing
  }
  else if (hash->memory_block_type == SPVM_COMPIER_ALLOCATOR_C_MEMORY_BLOCK_TYPE_RUN_TIME) {
    SPVM_ALLOCATOR_free_block_runtime(allocator, hash->table, hash->env);
    SPVM_ALLOCATOR_free_block_runtime(allocator, hash->entries, hash->env);
    SPVM_ALLOCATOR_free_block_runtime(allocator, hash->key_buffer, hash->env);
    SPVM_ALLOCATOR_free_block_runtime(allocator, hash, hash->env);
  }
  else {
    assert(0);
  }
}

void SPVM_HASH_maybe_extend_entries(SPVM_HASH* hash) {

  SPVM_ALLOCATOR* allocator = hash->allocator;
  
  assert(hash);
  
  int32_t entries_length = hash->entries_length;
  
  assert(entries_length >= 0);
  
  int32_t entries_capacity = hash->entries_capacity;
  
  if (entries_length >= entries_capacity) {
    int32_t new_entries_capacity = entries_capacity * 2;
    
    SPVM_HASH_ENTRY* new_entries;
    if (hash->memory_block_type == SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP) {
      new_entries = SPVM_ALLOCATOR_new_block_compile_tmp(allocator, new_entries_capacity * sizeof(SPVM_HASH_ENTRY));
    }
    else if (hash->memory_block_type == SPVM_ALLOCATOR_C_ALLOC_TYPE_PERMANENT) {
      new_entries = SPVM_ALLOCATOR_new_block_permanent(allocator, new_entries_capacity * sizeof(SPVM_HASH_ENTRY));
    }
    else if (hash->memory_block_type == SPVM_COMPIER_ALLOCATOR_C_MEMORY_BLOCK_TYPE_RUN_TIME) {
      new_entries = SPVM_ALLOCATOR_new_block_runtime(allocator, new_entries_capacity * sizeof(SPVM_HASH_ENTRY), hash->env);
    }
    else {
      assert(0);
    }

    memcpy(new_entries, hash->entries, entries_capacity * sizeof(SPVM_HASH_ENTRY));
    if (hash->memory_block_type == SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP) {
      SPVM_ALLOCATOR_free_block_compile_tmp(allocator, hash->entries);
    }
    else if (hash->memory_block_type == SPVM_ALLOCATOR_C_ALLOC_TYPE_PERMANENT) {
      // Nothing
    }
    else if (hash->memory_block_type == SPVM_COMPIER_ALLOCATOR_C_MEMORY_BLOCK_TYPE_RUN_TIME) {
      SPVM_ALLOCATOR_free_block_runtime(allocator, hash->entries, hash->env);
    }
    else {
      assert(0);
    }

    hash->entries = new_entries;
    
    hash->entries_capacity = new_entries_capacity;
  }
}

void SPVM_HASH_maybe_extend_key_buffer(SPVM_HASH* hash, int32_t length) {
  
  SPVM_ALLOCATOR* allocator = hash->allocator;

  assert(hash);
  
  int32_t key_buffer_length = hash->key_buffer_length;
  
  assert(key_buffer_length >= 0);
  
  int32_t key_buffer_capacity = hash->key_buffer_capacity;
  
  if (key_buffer_length + length + (int32_t)sizeof(int32_t) >= key_buffer_capacity) {
    int32_t new_key_buffer_capacity = (key_buffer_length + length + sizeof(int32_t)) * 2;
    
    char* new_key_buffer;
    if (hash->memory_block_type == SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP) {
      new_key_buffer = SPVM_ALLOCATOR_new_block_compile_tmp(allocator, new_key_buffer_capacity);
    }
    else if (hash->memory_block_type == SPVM_ALLOCATOR_C_ALLOC_TYPE_PERMANENT) {
      new_key_buffer = SPVM_ALLOCATOR_new_block_permanent(allocator, new_key_buffer_capacity);
    }
    else if (hash->memory_block_type == SPVM_COMPIER_ALLOCATOR_C_MEMORY_BLOCK_TYPE_RUN_TIME) {
      new_key_buffer = SPVM_ALLOCATOR_new_block_runtime(allocator, new_key_buffer_capacity, hash->env);
    }
    else {
      assert(0);
    }

    memcpy(new_key_buffer, hash->key_buffer, key_buffer_capacity);
    if (hash->memory_block_type == SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP) {
      SPVM_ALLOCATOR_free_block_compile_tmp(allocator, hash->key_buffer);
    }
    else if (hash->memory_block_type == SPVM_ALLOCATOR_C_ALLOC_TYPE_PERMANENT) {
      // Nothing
    }
    else if (hash->memory_block_type == SPVM_COMPIER_ALLOCATOR_C_MEMORY_BLOCK_TYPE_RUN_TIME) {
      SPVM_ALLOCATOR_free_block_runtime(allocator, hash->key_buffer, hash->env);
    }
    else {
      assert(0);
    }

    hash->key_buffer = new_key_buffer;

    hash->key_buffer_capacity = new_key_buffer_capacity;
  }
}

int32_t SPVM_HASH_new_hash_entry(SPVM_HASH* hash, const char* key, int32_t key_length, void* value) {
  
  assert(hash);
  assert(key);
  
  int32_t index = hash->entries_length;
  
  SPVM_HASH_maybe_extend_entries(hash);
  
  SPVM_HASH_maybe_extend_key_buffer(hash, key_length);
  
  hash->entries[index].key_index = hash->key_buffer_length;
  
  // Copy key length
  memcpy(&hash->key_buffer[hash->key_buffer_length], &key_length, sizeof(int32_t));
  
  // Copy key
  memcpy(&hash->key_buffer[hash->key_buffer_length + sizeof(int32_t)], key, key_length);
  
  hash->key_buffer_length += sizeof(int32_t) + key_length;
  
  hash->entries[index].value = value;
  hash->entries[index].next_index = -1;
  
  hash->entries_length++;
  
  return index;
}

void SPVM_HASH_rehash(SPVM_HASH* hash, int32_t new_table_capacity) {
  
  assert(hash);
  assert(new_table_capacity > 0);
  
  SPVM_ALLOCATOR* allocator = hash->allocator;

  // Create new hash
  SPVM_HASH* new_hash = SPVM_HASH_new(allocator, new_table_capacity, hash->memory_block_type, NULL);
  
  // Rehash
  {
    int32_t i;
    for (i = 0; i < hash->entries_length; i++) {
      int32_t key_length;
      memcpy(&key_length, &hash->key_buffer[hash->entries[i].key_index], sizeof(int32_t));
      const char* key = &hash->key_buffer[hash->entries[i].key_index + sizeof(int32_t)];
      
      void* value = hash->entries[i].value;
      
      SPVM_HASH_insert_norehash(new_hash, key, key_length, value);
    }
  }
  
  // Replace hash fields
  if (hash->memory_block_type == SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP) {
    SPVM_ALLOCATOR_free_block_compile_tmp(allocator, hash->table);
    SPVM_ALLOCATOR_free_block_compile_tmp(allocator, hash->entries);
    SPVM_ALLOCATOR_free_block_compile_tmp(allocator, hash->key_buffer);
  }
  else if (hash->memory_block_type == SPVM_ALLOCATOR_C_ALLOC_TYPE_PERMANENT) {
    // Nothing
  }
  else if (hash->memory_block_type == SPVM_COMPIER_ALLOCATOR_C_MEMORY_BLOCK_TYPE_RUN_TIME) {
    SPVM_ALLOCATOR_free_block_runtime(allocator, hash->table, hash->env);
    SPVM_ALLOCATOR_free_block_runtime(allocator, hash->entries, hash->env);
    SPVM_ALLOCATOR_free_block_runtime(allocator, hash->key_buffer, hash->env);
  }
  else {
    assert(0);
  }

  hash->entries_length = new_hash->entries_length;
  hash->table_capacity = new_hash->table_capacity;
  hash->entries_capacity = new_hash->entries_capacity;
  hash->table = new_hash->table;
  hash->entries = new_hash->entries;
  
  hash->key_buffer_capacity = new_hash->key_buffer_capacity;
  hash->key_buffer_length = new_hash->key_buffer_length;
  hash->key_buffer = new_hash->key_buffer;
  
  if (hash->memory_block_type == SPVM_ALLOCATOR_C_ALLOC_TYPE_TMP) {
    SPVM_ALLOCATOR_free_block_compile_tmp(allocator, new_hash);
  }
  else if (hash->memory_block_type == SPVM_ALLOCATOR_C_ALLOC_TYPE_PERMANENT) {
    // Nothing
  }
  else if (hash->memory_block_type == SPVM_COMPIER_ALLOCATOR_C_MEMORY_BLOCK_TYPE_RUN_TIME) {
    SPVM_ALLOCATOR_free_block_runtime(allocator, new_hash, hash->env);
  }
  else {
    assert(0);
  }
}

void SPVM_HASH_insert_norehash(SPVM_HASH* hash, const char* key, int32_t length, void* value) {
  
  assert(hash);
  assert(key);
  assert(length >= 0);
  
  int32_t hash_value = SPVM_HASH_calc_hash_value(key, length);
  int32_t table_index = hash_value % hash->table_capacity;
  
  assert(hash->table[table_index] >= -1);
  
  if (hash->table[table_index] != -1) {
    
    int32_t entry_index = hash->table[table_index];
    while (1) {
      int32_t match = 0;
      int32_t key_length;
      memcpy(&key_length, &hash->key_buffer[hash->entries[entry_index].key_index], sizeof(int32_t));
      if (key_length == 0 && length == 0) {
        match = 1;
      }
      else if (key_length == length && memcmp(key, &hash->key_buffer[hash->entries[entry_index].key_index + sizeof(int32_t)], length) == 0) {
        match = 1;
      }
      
      if (match) {
        hash->entries[entry_index].value = value;
        break;
      }
      else {
        if (hash->entries[entry_index].next_index != -1) {
          entry_index = hash->entries[entry_index].next_index;
        }
        else {
          int32_t new_entry_index = SPVM_HASH_new_hash_entry(hash, key, length, value);
          hash->entries[entry_index].next_index = new_entry_index;
          break;
        }
      }
    }
  }
  else {
    int32_t new_entry_index = SPVM_HASH_new_hash_entry(hash, key, length, value);
    hash->table[table_index] = new_entry_index;
  }
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
