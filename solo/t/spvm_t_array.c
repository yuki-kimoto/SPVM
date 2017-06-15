#include <stdio.h>

#include "../../spvm_array.h"

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
    SPVM_ARRAY* array = SPVM_ARRAY_new(10);
    
    // capacity
    OK(array->capacity == 10);
    
    // length default is 0
    OK(array->length == 0);
    
    // First element is NULL
    OK(array->values[0] == NULL);
    
    // Last element is NULL
    OK(array->values[9] == NULL);
    
    SPVM_ARRAY_free(array);
  }
    
  // Array - capacity default
  {
    SPVM_ARRAY* array = SPVM_ARRAY_new(0);
    
    OK(array->capacity == 128);
    
    OK(array->length == 0);
  }

  // Array - push
  {
    SPVM_ARRAY* array = SPVM_ARRAY_new(0);
    
    // push long value at first
    int32_t value1 = 10;
    SPVM_ARRAY_push(array, &value1);
    OK(*(int32_t*)array->values[0] == 10);
    OK(array->length == 1);
    
    // push long value next
    int32_t value2 = 15;
    SPVM_ARRAY_push(array, &value2);
    OK(*(int32_t*)array->values[1] == 15);
    OK(array->length == 2);
    
    // push pointer value
    const char* value3 = "foo";
    SPVM_ARRAY_push(array, value3);
    OK(array->values[2] == value3);
  }

  // Array - pop
  {
    SPVM_ARRAY* array = SPVM_ARRAY_new(0);
    
    // push long value at first
    int32_t value1 = 10;
    SPVM_ARRAY_push(array, &value1);
    OK(*(int32_t*)array->values[0] == 10);
    OK(array->length == 1);
    
    // push long value next
    int32_t value2 = 15;
    SPVM_ARRAY_push(array, &value2);
    OK(*(int32_t*)array->values[1] == 15);
    OK(array->length == 2);
    
    // pop
    void* pop_value = SPVM_ARRAY_pop(array);
    OK(*(int32_t*)pop_value == 15);
    OK(array->length == 1);
  }
  
  // Array - push capacity resize
  {
    SPVM_ARRAY* array = SPVM_ARRAY_new(2);
    
    int32_t value1 = 1;
    int32_t value2 = 2;
    SPVM_ARRAY_push(array, &value1);
    SPVM_ARRAY_push(array, &value2);
    OK(array->capacity == 2);
    
    int32_t value3 = 3;
    SPVM_ARRAY_push(array, &value3);
    OK(array->capacity == 4);
    OK(array->length == 3);
    OK(*(int32_t*)array->values[0] == 1);
    OK(*(int32_t*)array->values[1] == 2);
    OK(*(int32_t*)array->values[2] == 3);
  }

  // Array - fetch
  {
    SPVM_ARRAY* array = SPVM_ARRAY_new(0);
    int32_t value1 = 3;
    int32_t value2 = 5;
    
    SPVM_ARRAY_push(array, &value1);
    SPVM_ARRAY_push(array, &value2);
    
    OK(*(int32_t*)SPVM_ARRAY_fetch(array, 0) == 3);
    OK(*(int32_t*)SPVM_ARRAY_fetch(array, 1) == 5);
  }

  // Array - push many values
  {
    SPVM_ARRAY* array = SPVM_ARRAY_new(1);
    
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
    
    SPVM_ARRAY_push(array, &value1);
    SPVM_ARRAY_push(array, &value2);
    SPVM_ARRAY_push(array, &value3);
    SPVM_ARRAY_push(array, &value4);
    SPVM_ARRAY_push(array, &value5);
    SPVM_ARRAY_push(array, &value6);
    SPVM_ARRAY_push(array, &value7);
    SPVM_ARRAY_push(array, &value8);
    SPVM_ARRAY_push(array, &value9);
    SPVM_ARRAY_push(array, &value10);
    SPVM_ARRAY_push(array, &value11);
    SPVM_ARRAY_push(array, &value12);
    SPVM_ARRAY_push(array, &value13);
    SPVM_ARRAY_push(array, &value14);
  }
  
  return 0;
}
