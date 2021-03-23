#ifndef SPVM_HASH_H
#define SPVM_HASH_H

#include <stdint.h>
#include <stddef.h>

struct spvm_hash;
typedef struct spvm_hash SPVM_HASH;

struct spvm_hash_entry;
typedef struct spvm_hash_entry SPVM_HASH_ENTRY;

// Hash function
int32_t SPVM_HASH_FUNC_calc_hash_for_index(const char* str, int32_t len);

// Hash table
struct spvm_hash {
  int32_t* table;
  char* key_buffer;
  SPVM_HASH_ENTRY* entries;
  int32_t table_capacity;
  int32_t entries_capacity;
  int32_t entries_length;
  int32_t key_buffer_capacity;
  int32_t key_buffer_length;
};

// Hash entry
struct spvm_hash_entry {
  void* value;
  int32_t next_index;
  int32_t key_index;
};

// Hash function
SPVM_HASH* SPVM_HASH_new(int32_t capacity);
void SPVM_HASH_free(SPVM_HASH* hash);
void SPVM_HASH_maybe_extend_entries(SPVM_HASH* hash);

int32_t SPVM_HASH_new_hash_entry(SPVM_HASH* hash, const char* key, int32_t length, void* value);
void SPVM_HASH_rehash(SPVM_HASH* hash, int32_t new_table_capacity);
void SPVM_HASH_insert_norehash(SPVM_HASH* hash, const char* key, int32_t length, void* value);
void SPVM_HASH_insert(SPVM_HASH* hash, const char* key, int32_t length, void* value);
void* SPVM_HASH_fetch(SPVM_HASH* hash, const char* key, int32_t length);

#endif
