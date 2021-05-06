#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "spvm_hash.h"

#define OK(condition) \
  if (condition) {\
    printf("OK\n");\
  }\
  else {\
    printf("Not OK at line %d\n", __LINE__);\
  }

int main()
{
  // Hash - first same key
  {
    SPVM_HASH* hash = SPVM_HASH_new(0);
    int32_t value1 = 3;
    SPVM_HASH_insert_norehash(hash, "", 0, &value1);
    
    int32_t value1_ret = *(int32_t*)SPVM_HASH_fetch(hash, "", 0);
    OK(value1_ret == 3);
  }
  
  // Hash - new
  {
    SPVM_HASH* hash = SPVM_HASH_new(10);
    // capacity
    OK(hash->table_capacity == 10);
    OK(hash->entries_length == 0);
  }

  // Hash - capacity default
  {
    SPVM_HASH* hash = SPVM_HASH_new(0);
    // capacity
    OK(hash->table_capacity == 1);
  }

  // Hash - first same key
  {
    SPVM_HASH* hash = SPVM_HASH_new(101);
    int32_t value1 = 3;
    SPVM_HASH_insert_norehash(hash, "key1", 4, &value1);

    int32_t value1_ret = *(int32_t*)SPVM_HASH_fetch(hash, "key1", 4);
    OK(value1_ret == 3);

    int32_t value2 = 5;
    SPVM_HASH_insert_norehash(hash, "key", 3, &value2);
    
    int32_t value2_ret = *(int32_t*)SPVM_HASH_fetch(hash, "key", 3);
    OK(value2_ret == 5);
  }

  // Hash - insert and search
  {
    SPVM_HASH* hash = SPVM_HASH_new(101);
    int32_t value1 = 3;
    SPVM_HASH_insert_norehash(hash, "key1", 4, &value1);
    int32_t hash_value1 = SPVM_HASH_calc_hash_value("key1", 4);
    int32_t index1 = hash_value1 % 101;
   
    OK(*(int32_t*)((SPVM_HASH_ENTRY*)&hash->entries[hash->table[index1]])->value == 3);
    OK(hash->entries_length == 1);

    int32_t value2 = 5;
    SPVM_HASH_insert_norehash(hash, "key2", 4, &value2);
    int32_t hash_value2 = SPVM_HASH_calc_hash_value("key2", 4);
    int32_t index2 = hash_value2 % 101;
    
    OK(*(int32_t*)((SPVM_HASH_ENTRY*)&hash->entries[hash->table[index2]])->value == 5);
    OK(hash->entries_length == 2);
    
    // Replace
    int32_t value3 = 7;
    SPVM_HASH_insert_norehash(hash, "key1", 4, &value3);
    int32_t hash_value3 = SPVM_HASH_calc_hash_value("key1", 4);
    int32_t index3 = hash_value3 % 101;
    
    OK(*(int32_t*)((SPVM_HASH_ENTRY*)&hash->entries[hash->table[index3]])->value == 7);
    OK(hash->entries_length == 2);
    
    // Search
    int32_t value1_1 = *(int32_t*)SPVM_HASH_fetch(hash, "key1", 4);
    OK(value1_1 == 7);
    int32_t value2_1 = *(int32_t*)SPVM_HASH_fetch(hash, "key2", 4);
    OK(value2_1 == 5);
    void* value3_1 = SPVM_HASH_fetch(hash, "none", 4);
    OK(!value3_1);
  }
  
  // Rehash
  {
    SPVM_HASH* hash = SPVM_HASH_new(5);
    
    int32_t value1 = 1;
    SPVM_HASH_insert(hash, "key1", 4, &value1);
    int32_t value2 = 2;
    SPVM_HASH_insert(hash, "key2", 4, &value2);
    int32_t value3 = 3;
    SPVM_HASH_insert(hash, "key3", 4, &value3);
    int32_t value4 = 4;
    SPVM_HASH_insert(hash, "key4", 4, &value4);
    
    OK(hash->table_capacity == 5);
    OK(hash->entries_length == 4);
    
    // Rehash
    int32_t value5 = 5;
    SPVM_HASH_insert(hash, "key5", 4, &value5);

    OK(hash->table_capacity == 11);
    OK(hash->entries_length == 5);

    int32_t* search_value1_ptr = SPVM_HASH_fetch(hash, "key1", 4);
    int32_t search_value1 = *search_value1_ptr;
    OK(search_value1 == 1);

    int32_t search_value2 = *(int32_t*)SPVM_HASH_fetch(hash, "key2", 4);
    OK(search_value2 == 2);
    int32_t search_value3 = *(int32_t*)SPVM_HASH_fetch(hash, "key3", 4);
    OK(search_value3 == 3);
    int32_t search_value4 = *(int32_t*)SPVM_HASH_fetch(hash, "key4", 4);
    OK(search_value4 == 4);
    int32_t search_value5 = *(int32_t*)SPVM_HASH_fetch(hash, "key5", 4);
    OK(search_value5 == 5);

    int32_t value6 = 6;
    SPVM_HASH_insert(hash, "key6", 4, &value6);
    int32_t value7 = 7;
    SPVM_HASH_insert(hash, "key7", 4, &value7);
    int32_t value8 = 8;
    SPVM_HASH_insert(hash, "key8", 4, &value8);
    int32_t value9 = 9;
    SPVM_HASH_insert(hash, "key9", 4, &value9);

    OK(hash->table_capacity == 11);
    OK(hash->entries_length == 9);
    
    // Rehash
    int32_t value10 = 10;
    SPVM_HASH_insert(hash, "key10", 5, &value10);
    OK(hash->table_capacity == 23);
    OK(hash->entries_length == 10);
    
    int32_t search_value6 = *(int32_t*)SPVM_HASH_fetch(hash, "key6", 4);
    OK(search_value6 == 6);
    int32_t search_value7 = *(int32_t*)SPVM_HASH_fetch(hash, "key7", 4);
    OK(search_value7 == 7);
    int32_t search_value8 = *(int32_t*)SPVM_HASH_fetch(hash, "key8", 4);
    OK(search_value8 == 8);
    int32_t search_value9 = *(int32_t*)SPVM_HASH_fetch(hash, "key9", 4);
    OK(search_value9 == 9);
    int32_t search_value10 = *(int32_t*)SPVM_HASH_fetch(hash, "key10", 5);
    OK(search_value10 == 10);
  }

  // Many insert and search
  {
    SPVM_HASH* hash = SPVM_HASH_new(0);
    
    int32_t i;
    int32_t max = 70000;
    
    SPVM_HASH_insert(hash, "", strlen(""), (void*)(intptr_t)-1);
    
    for (i = 1; i < max; i++) {
      char* key = malloc(10);
      sprintf(key, "key%d", i);
      SPVM_HASH_insert(hash, key, strlen(key), (void*)(intptr_t)(i * 10));
    }
    
    _Bool ok = 1;
    
    int32_t value = (int32_t)(intptr_t)SPVM_HASH_fetch(hash, "", strlen(""));
    if (value != -1) {
      ok = 0;
    }
    
    for (i = 1; i < max; i++) {
      char* key = malloc(10);
      sprintf(key, "key%d", i);
      int32_t value = (int32_t)(intptr_t)SPVM_HASH_fetch(hash, key, strlen(key));
      if (value != i * 10) {
        ok = 0;
      }
    }
    OK(ok);
  }

  // Hash - insert link
  {
    SPVM_HASH* hash = SPVM_HASH_new(1);
    int32_t value1 = 3;
    SPVM_HASH_insert_norehash(hash, "key1", 4, &value1);
    
    OK(*(int32_t*)((SPVM_HASH_ENTRY*)&hash->entries[hash->table[0]])->value == 3);
    OK(((SPVM_HASH_ENTRY*)&hash->entries[hash->table[0]]) == &hash->entries[0]);
    OK(hash->table_capacity == 1);
    OK(hash->entries_length == 1);
    
    int32_t value2 = 5;
    SPVM_HASH_insert_norehash(hash, "key2", 4, &value2);
    
    OK(*(int32_t*)hash->entries[((SPVM_HASH_ENTRY*)&hash->entries[hash->table[0]])->next_index].value == 5);
    OK(hash->table_capacity == 1);
    OK(hash->entries_length == 2);
    
    int32_t value3 = 7;
    SPVM_HASH_insert_norehash(hash, "key3", 4, &value3);
    
    OK(*(int32_t*)hash->entries[hash->entries[((SPVM_HASH_ENTRY*)&hash->entries[hash->table[0]])->next_index].next_index].value == 7);
    OK(hash->table_capacity == 1);
    OK(hash->entries_length == 3);

    // Search
    int32_t value1_1 = *(int32_t*)SPVM_HASH_fetch(hash, "key1", 4);
    OK(value1_1 == 3);
    int32_t value2_1 = *(int32_t*)SPVM_HASH_fetch(hash, "key2", 4);
    OK(value2_1 == 5);
    int32_t value3_1 = *(int32_t*)SPVM_HASH_fetch(hash, "key3", 4);
    OK(value3_1 == 7);
    
    // free
    SPVM_HASH_free(hash);
  }
  
  // fetch_with_exists
  {
    SPVM_HASH* hash = SPVM_HASH_new(0);
    
    SPVM_HASH_insert(hash, "foo", strlen("foo"), (void*)(intptr_t)-1);
    int32_t foo_exists = 0;
    SPVM_HASH_fetch_with_exists(hash, "foo", strlen("foo"), &foo_exists);
    OK(foo_exists);
    
    SPVM_HASH_insert(hash, "bar", strlen("bar"), (void*)NULL);
    int32_t bar_exists = 0;
    SPVM_HASH_fetch_with_exists(hash, "bar", strlen("bar"), &bar_exists);
    OK(bar_exists);

    int32_t baz_exists = 0;
    SPVM_HASH_fetch_with_exists(hash, "baz", strlen("baz"), &baz_exists);
    OK(!baz_exists);
  }
  
  return 0;
}
