#include <stdio.h>

#include "spvm_list.h"

#define OK(condition) \
  if (condition) {\
    printf("OK\n");\
  }\
  else {\
    printf("Not OK at line %d\n", __LINE__);\
  }

int main()
{
  // Array - new and free
  {
    SPVM_LIST* list = SPVM_LIST_new(10);
    
    // capacity
    OK(list->capacity == 10);
    
    // length default is 0
    OK(list->length == 0);
    
    // First element is NULL
    OK(list->values[0] == NULL);
    
    // Last element is NULL
    OK(list->values[9] == NULL);
    
    SPVM_LIST_free(list);
  }
    
  // Array - capacity default
  {
    SPVM_LIST* list = SPVM_LIST_new(0);
    
    OK(list->capacity == 1);
    
    OK(list->length == 0);
  }

  // Array - push
  {
    SPVM_LIST* list = SPVM_LIST_new(0);
    
    // push long value at first
    int32_t value1 = 10;
    SPVM_LIST_push(list, &value1);
    OK(*(int32_t*)list->values[0] == 10);
    OK(list->length == 1);
    
    // push long value next
    int32_t value2 = 15;
    SPVM_LIST_push(list, &value2);
    OK(*(int32_t*)list->values[1] == 15);
    OK(list->length == 2);
    
    // push pointer value
    const char* value3 = "foo";
    SPVM_LIST_push(list, (char*)value3);
    OK(list->values[2] == value3);
  }

  // Array - pop
  {
    SPVM_LIST* list = SPVM_LIST_new(0);
    
    // push long value at first
    int32_t value1 = 10;
    SPVM_LIST_push(list, &value1);
    OK(*(int32_t*)list->values[0] == 10);
    OK(list->length == 1);
    
    // push long value next
    int32_t value2 = 15;
    SPVM_LIST_push(list, &value2);
    OK(*(int32_t*)list->values[1] == 15);
    OK(list->length == 2);
    
    // pop
    void* pop_value = SPVM_LIST_pop(list);
    OK(*(int32_t*)pop_value == 15);
    OK(list->length == 1);
  }
  
  // Array - push capacity resize
  {
    SPVM_LIST* list = SPVM_LIST_new(2);
    
    int32_t value1 = 1;
    int32_t value2 = 2;
    SPVM_LIST_push(list, &value1);
    SPVM_LIST_push(list, &value2);
    OK(list->capacity == 2);
    
    int32_t value3 = 3;
    SPVM_LIST_push(list, &value3);
    OK(list->capacity == 4);
    OK(list->length == 3);
    OK(*(int32_t*)list->values[0] == 1);
    OK(*(int32_t*)list->values[1] == 2);
    OK(*(int32_t*)list->values[2] == 3);
  }

  // Array - fetch
  {
    SPVM_LIST* list = SPVM_LIST_new(0);
    int32_t value1 = 3;
    int32_t value2 = 5;
    
    SPVM_LIST_push(list, &value1);
    SPVM_LIST_push(list, &value2);
    
    OK(*(int32_t*)SPVM_LIST_fetch(list, 0) == 3);
    OK(*(int32_t*)SPVM_LIST_fetch(list, 1) == 5);
  }

  // Array - push many values
  {
    SPVM_LIST* list = SPVM_LIST_new(1);
    
    int32_t value1 = 1;
    int32_t value2 = 2;
    int32_t value3 = 3;
    int32_t value4 = 4;
    int32_t value5 = 5;
    int32_t value6 = 6;
    int32_t value7 = 7;
    int32_t value8 = 8;
    int32_t value9 = 9;
    int32_t value10 = 10;
    int32_t value11 = 11;
    int32_t value12 = 12;
    int32_t value13 = 13;
    int32_t value14 = 14;
    
    SPVM_LIST_push(list, &value1);
    SPVM_LIST_push(list, &value2);
    SPVM_LIST_push(list, &value3);
    SPVM_LIST_push(list, &value4);
    SPVM_LIST_push(list, &value5);
    SPVM_LIST_push(list, &value6);
    SPVM_LIST_push(list, &value7);
    SPVM_LIST_push(list, &value8);
    SPVM_LIST_push(list, &value9);
    SPVM_LIST_push(list, &value10);
    SPVM_LIST_push(list, &value11);
    SPVM_LIST_push(list, &value12);
    SPVM_LIST_push(list, &value13);
    SPVM_LIST_push(list, &value14);
  }
  
  return 0;
}
