#include "spvm_base.h"
#include "spvm_native.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <float.h>
#include <math.h>
#include <time.h>
#include <complex.h>
#include <memory.h>

int32_t SPVM_NATIVE_SPVM__CORE__new_oarray_proto(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* oarray = stack[0].oval;
  int32_t length = stack[1].ival;
  
  if (oarray == NULL) {
    SPVM_CROAK("Prototype array must be defined", "SPVM/CORE.c", __LINE__);
  }
  
  int32_t basic_type_id = env->object_basic_type_id(env, oarray);
  int32_t element_dimension = env->object_type_dimension(env, oarray) - 1;
  
  void* new_oarray = env->new_marray(env, basic_type_id, element_dimension, length);
  
  stack[0].oval = new_oarray;
  
  return SPVM_SUCCESS;
}

int32_t SPVM_NATIVE_SPVM__CORE__reverseb(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* onums = stack[0].oval;
  
  if (onums == NULL) {
    SPVM_CROAK("Array must be defined", "SPVM/CORE.c", __LINE__);
  }

  int32_t array_length = env->len(env, onums);
  if (array_length == 0) {
    return SPVM_SUCCESS;
  }
  
  int8_t* nums = env->belems(env, onums);
  
  for(int32_t i = 0; i < array_length / 2; i++){
    int8_t tmp = nums[i];
    nums[i] = nums[array_length - i - 1];
    nums[array_length - i - 1] = tmp;
  }
  
  return SPVM_SUCCESS;
}

int32_t SPVM_NATIVE_SPVM__CORE__reverses(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* onums = stack[0].oval;
  
  if (onums == NULL) {
    SPVM_CROAK("Array must be defined", "SPVM/CORE.c", __LINE__);
  }

  int32_t array_length = env->len(env, onums);
  if (array_length == 0) {
    return SPVM_SUCCESS;
  }
  
  int16_t* nums = env->selems(env, onums);
  
  for(int32_t i = 0; i < array_length / 2; i++){
    int16_t tmp = nums[i];
    nums[i] = nums[array_length - i - 1];
    nums[array_length - i - 1] = tmp;
  }
  
  return SPVM_SUCCESS;
}

int32_t SPVM_NATIVE_SPVM__CORE__reversei(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* onums = stack[0].oval;
  
  if (onums == NULL) {
    SPVM_CROAK("Array must be defined", "SPVM/CORE.c", __LINE__);
  }

  int32_t array_length = env->len(env, onums);
  if (array_length == 0) {
    return SPVM_SUCCESS;
  }
  
  int32_t* nums = env->ielems(env, onums);
  
  for(int32_t i = 0; i < array_length / 2; i++){
    int32_t tmp = nums[i];
    nums[i] = nums[array_length - i - 1];
    nums[array_length - i - 1] = tmp;
  }
  
  return SPVM_SUCCESS;
}

int32_t SPVM_NATIVE_SPVM__CORE__reversel(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* onums = stack[0].oval;
  
  if (onums == NULL) {
    SPVM_CROAK("Array must be defined", "SPVM/CORE.c", __LINE__);
  }

  int32_t array_length = env->len(env, onums);
  if (array_length == 0) {
    return SPVM_SUCCESS;
  }
  
  int64_t* nums = env->lelems(env, onums);
  
  for(int32_t i = 0; i < array_length / 2; i++){
    int64_t tmp = nums[i];
    nums[i] = nums[array_length - i - 1];
    nums[array_length - i - 1] = tmp;
  }
  
  return SPVM_SUCCESS;
}

int32_t SPVM_NATIVE_SPVM__CORE__reversef(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* onums = stack[0].oval;
  
  if (onums == NULL) {
    SPVM_CROAK("Array must be defined", "SPVM/CORE.c", __LINE__);
  }

  int32_t array_length = env->len(env, onums);
  if (array_length == 0) {
    return SPVM_SUCCESS;
  }
  
  float* nums = env->felems(env, onums);
  
  for(int32_t i = 0; i < array_length / 2; i++){
    float tmp = nums[i];
    nums[i] = nums[array_length - i - 1];
    nums[array_length - i - 1] = tmp;
  }
  
  return SPVM_SUCCESS;
}

int32_t SPVM_NATIVE_SPVM__CORE__reversed(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* onums = stack[0].oval;
  
  if (onums == NULL) {
    SPVM_CROAK("Array must be defined", "SPVM/CORE.c", __LINE__);
  }

  int32_t array_length = env->len(env, onums);
  if (array_length == 0) {
    return SPVM_SUCCESS;
  }
  
  double* nums = env->delems(env, onums);
  
  for(int32_t i = 0; i < array_length / 2; i++){
    double tmp = nums[i];
    nums[i] = nums[array_length - i - 1];
    nums[array_length - i - 1] = tmp;
  }
  
  return SPVM_SUCCESS;
}

int32_t SPVM_NATIVE_SPVM__CORE__reverseo(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* onums = stack[0].oval;
  
  if (onums == NULL) {
    SPVM_CROAK("Array must be defined", "SPVM/CORE.c", __LINE__);
  }

  int32_t array_length = env->len(env, onums);
  if (array_length == 0) {
    return SPVM_SUCCESS;
  }
  
  for(int32_t i = 0; i < array_length / 2; i++){
    void* tmp = env->oelem(env, onums, i);
    env->set_oelem(env, onums, i, env->oelem(env, onums, array_length - i - 1));
    env->set_oelem(env, onums, array_length - i - 1, tmp);
  }
  
  return SPVM_SUCCESS;
}

/*
  Dual pivot Quicksort
  https://www.geeksforgeeks.org/dual-pivot-quicksort/
*/
static void swap_byte(int8_t* a, int8_t* b) 
{ 
    int8_t temp = *a; 
    *a = *b; 
    *b = temp; 
}
static int32_t partition_byte(int8_t* arr, int32_t low, int32_t high, int32_t* lp) 
{ 
    if (arr[low] > arr[high]) 
        swap_byte(&arr[low], &arr[high]); 
    // p is the left pivot, and q is the right pivot. 
    int32_t j = low + 1; 
    int32_t g = high - 1, k = low + 1, p = arr[low], q = arr[high]; 
    while (k <= g) { 
  
        // if elements are less than the left pivot 
        if (arr[k] < p) { 
            swap_byte(&arr[k], &arr[j]); 
            j++; 
        } 
  
        // if elements are greater than or equal  
        // to the right pivot 
        else if (arr[k] >= q) { 
            while (arr[g] > q && k < g) 
                g--; 
            swap_byte(&arr[k], &arr[g]); 
            g--; 
            if (arr[k] < p) { 
                swap_byte(&arr[k], &arr[j]); 
                j++; 
            } 
        } 
        k++; 
    } 
    j--; 
    g++; 
  
    // bring pivots to their appropriate positions. 
    swap_byte(&arr[low], &arr[j]); 
    swap_byte(&arr[high], &arr[g]); 
  
    // returning the indeces of the pivots. 
    *lp = j; // because we cannot return two elements  
             // from a function. 
  
    return g;
}
static void DualPivotQuickSort_byte(int8_t* arr, int32_t low, int32_t high) 
{ 
    if (low < high) { 
        // lp means left pivot, and rp means right pivot. 
        int32_t lp, rp;  
        rp = partition_byte(arr, low, high, &lp); 
        DualPivotQuickSort_byte(arr, low, lp - 1); 
        DualPivotQuickSort_byte(arr, lp + 1, rp - 1); 
        DualPivotQuickSort_byte(arr, rp + 1, high); 
    } 
}
static void swap_short(int16_t* a, int16_t* b) 
{ 
    int16_t temp = *a; 
    *a = *b; 
    *b = temp; 
}
static int32_t partition_short(int16_t* arr, int32_t low, int32_t high, int32_t* lp) 
{ 
    if (arr[low] > arr[high]) 
        swap_short(&arr[low], &arr[high]); 
    // p is the left pivot, and q is the right pivot. 
    int32_t j = low + 1; 
    int32_t g = high - 1, k = low + 1, p = arr[low], q = arr[high]; 
    while (k <= g) { 
  
        // if elements are less than the left pivot 
        if (arr[k] < p) { 
            swap_short(&arr[k], &arr[j]); 
            j++; 
        } 
  
        // if elements are greater than or equal  
        // to the right pivot 
        else if (arr[k] >= q) { 
            while (arr[g] > q && k < g) 
                g--; 
            swap_short(&arr[k], &arr[g]); 
            g--; 
            if (arr[k] < p) { 
                swap_short(&arr[k], &arr[j]); 
                j++; 
            } 
        } 
        k++; 
    } 
    j--; 
    g++; 
  
    // bring pivots to their appropriate positions. 
    swap_short(&arr[low], &arr[j]); 
    swap_short(&arr[high], &arr[g]); 
  
    // returning the indeces of the pivots. 
    *lp = j; // because we cannot return two elements  
             // from a function. 
  
    return g; 
}
static void DualPivotQuickSort_short(int16_t* arr, int32_t low, int32_t high) 
{ 
    if (low < high) { 
        // lp means left pivot, and rp means right pivot. 
        int32_t lp, rp;  
        rp = partition_short(arr, low, high, &lp); 
        DualPivotQuickSort_short(arr, low, lp - 1); 
        DualPivotQuickSort_short(arr, lp + 1, rp - 1); 
        DualPivotQuickSort_short(arr, rp + 1, high); 
    } 
}
static void swap_int(int32_t* a, int32_t* b) 
{ 
    int32_t temp = *a; 
    *a = *b; 
    *b = temp; 
}
static int32_t partition_int(int32_t* arr, int32_t low, int32_t high, int32_t* lp) 
{ 
    if (arr[low] > arr[high]) 
        swap_int(&arr[low], &arr[high]); 
    // p is the left pivot, and q is the right pivot. 
    int32_t j = low + 1; 
    int32_t g = high - 1, k = low + 1, p = arr[low], q = arr[high]; 
    while (k <= g) { 
  
        // if elements are less than the left pivot 
        if (arr[k] < p) { 
            swap_int(&arr[k], &arr[j]); 
            j++; 
        } 
  
        // if elements are greater than or equal  
        // to the right pivot 
        else if (arr[k] >= q) { 
            while (arr[g] > q && k < g) 
                g--; 
            swap_int(&arr[k], &arr[g]); 
            g--; 
            if (arr[k] < p) { 
                swap_int(&arr[k], &arr[j]); 
                j++; 
            } 
        } 
        k++; 
    } 
    j--; 
    g++; 
  
    // bring pivots to their appropriate positions. 
    swap_int(&arr[low], &arr[j]); 
    swap_int(&arr[high], &arr[g]); 
  
    // returning the indeces of the pivots. 
    *lp = j; // because we cannot return two elements  
             // from a function. 
  
    return g; 
}
static void DualPivotQuickSort_int(int32_t* arr, int32_t low, int32_t high) 
{ 
    if (low < high) { 
        // lp means left pivot, and rp means right pivot. 
        int32_t lp, rp;  
        rp = partition_int(arr, low, high, &lp); 
        DualPivotQuickSort_int(arr, low, lp - 1); 
        DualPivotQuickSort_int(arr, lp + 1, rp - 1); 
        DualPivotQuickSort_int(arr, rp + 1, high); 
    } 
}
static void swap_long(int64_t* a, int64_t* b) 
{ 
    int64_t temp = *a; 
    *a = *b; 
    *b = temp; 
}
static int32_t partition_long(int64_t* arr, int32_t low, int32_t high, int32_t* lp) 
{ 
    if (arr[low] > arr[high]) 
        swap_long(&arr[low], &arr[high]); 
    // p is the left pivot, and q is the right pivot. 
    int32_t j = low + 1; 
    int32_t g = high - 1, k = low + 1, p = arr[low], q = arr[high]; 
    while (k <= g) { 
  
        // if elements are less than the left pivot 
        if (arr[k] < p) { 
            swap_long(&arr[k], &arr[j]); 
            j++; 
        } 
  
        // if elements are greater than or equal  
        // to the right pivot 
        else if (arr[k] >= q) { 
            while (arr[g] > q && k < g) 
                g--; 
            swap_long(&arr[k], &arr[g]); 
            g--; 
            if (arr[k] < p) { 
                swap_long(&arr[k], &arr[j]); 
                j++; 
            } 
        } 
        k++; 
    } 
    j--; 
    g++; 
  
    // bring pivots to their appropriate positions. 
    swap_long(&arr[low], &arr[j]); 
    swap_long(&arr[high], &arr[g]); 
  
    // returning the indeces of the pivots. 
    *lp = j; // because we cannot return two elements  
             // from a function. 
  
    return g; 
}
static void DualPivotQuickSort_long(int64_t* arr, int32_t low, int32_t high) 
{ 
    if (low < high) { 
        // lp means left pivot, and rp means right pivot. 
        int32_t lp, rp;  
        rp = partition_long(arr, low, high, &lp); 
        DualPivotQuickSort_long(arr, low, lp - 1); 
        DualPivotQuickSort_long(arr, lp + 1, rp - 1); 
        DualPivotQuickSort_long(arr, rp + 1, high); 
    } 
}
static void swap_float(float* a, float* b) 
{ 
    float temp = *a; 
    *a = *b; 
    *b = temp; 
}
static int32_t partition_float(float* arr, int32_t low, int32_t high, int32_t* lp) 
{ 
    if (arr[low] > arr[high]) 
        swap_float(&arr[low], &arr[high]); 
    // p is the left pivot, and q is the right pivot. 
    int32_t j = low + 1; 
    int32_t g = high - 1, k = low + 1, p = arr[low], q = arr[high]; 
    while (k <= g) { 
  
        // if elements are less than the left pivot 
        if (arr[k] < p) { 
            swap_float(&arr[k], &arr[j]); 
            j++; 
        } 
  
        // if elements are greater than or equal  
        // to the right pivot 
        else if (arr[k] >= q) { 
            while (arr[g] > q && k < g) 
                g--; 
            swap_float(&arr[k], &arr[g]); 
            g--; 
            if (arr[k] < p) { 
                swap_float(&arr[k], &arr[j]); 
                j++; 
            } 
        } 
        k++; 
    } 
    j--; 
    g++; 
  
    // bring pivots to their appropriate positions. 
    swap_float(&arr[low], &arr[j]); 
    swap_float(&arr[high], &arr[g]); 
  
    // returning the indeces of the pivots. 
    *lp = j; // because we cannot return two elements  
             // from a function. 
  
    return g; 
}
static void DualPivotQuickSort_float(float* arr, int32_t low, int32_t high) 
{ 
    if (low < high) { 
        // lp means left pivot, and rp means right pivot. 
        int32_t lp, rp;  
        rp = partition_float(arr, low, high, &lp); 
        DualPivotQuickSort_float(arr, low, lp - 1); 
        DualPivotQuickSort_float(arr, lp + 1, rp - 1); 
        DualPivotQuickSort_float(arr, rp + 1, high); 
    } 
}
static void swap_double(double* a, double* b) 
{ 
    double temp = *a; 
    *a = *b; 
    *b = temp; 
}
static int32_t partition_double(double* arr, int32_t low, int32_t high, int32_t* lp) 
{ 
    if (arr[low] > arr[high]) 
        swap_double(&arr[low], &arr[high]); 
    // p is the left pivot, and q is the right pivot. 
    int32_t j = low + 1; 
    int32_t g = high - 1, k = low + 1, p = arr[low], q = arr[high]; 
    while (k <= g) { 
  
        // if elements are less than the left pivot 
        if (arr[k] < p) { 
            swap_double(&arr[k], &arr[j]); 
            j++; 
        } 
  
        // if elements are greater than or equal  
        // to the right pivot 
        else if (arr[k] >= q) { 
            while (arr[g] > q && k < g) 
                g--; 
            swap_double(&arr[k], &arr[g]); 
            g--; 
            if (arr[k] < p) { 
                swap_double(&arr[k], &arr[j]); 
                j++; 
            } 
        } 
        k++; 
    } 
    j--; 
    g++; 
  
    // bring pivots to their appropriate positions. 
    swap_double(&arr[low], &arr[j]); 
    swap_double(&arr[high], &arr[g]); 
  
    // returning the indeces of the pivots. 
    *lp = j; // because we cannot return two elements  
             // from a function. 
  
    return g; 
}
static void DualPivotQuickSort_double(double* arr, int32_t low, int32_t high) 
{ 
    if (low < high) { 
        // lp means left pivot, and rp means right pivot. 
        int32_t lp, rp;  
        rp = partition_double(arr, low, high, &lp); 
        DualPivotQuickSort_double(arr, low, lp - 1); 
        DualPivotQuickSort_double(arr, lp + 1, rp - 1); 
        DualPivotQuickSort_double(arr, rp + 1, high); 
    } 
}

int32_t SPVM_NATIVE_SPVM__CORE__sortb(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* onums = stack[0].oval;
  
  if (onums == NULL) {
    SPVM_CROAK("Array must be defined", "SPVM/CORE.c", __LINE__);
  }

  int32_t array_length = env->len(env, onums);
  if (array_length == 0) {
    return SPVM_SUCCESS;
  }
  
  int8_t* nums = env->belems(env, onums);
  
  DualPivotQuickSort_byte(nums, 0, array_length - 1);
  
  return SPVM_SUCCESS;
}

int32_t SPVM_NATIVE_SPVM__CORE__sorts(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* onums = stack[0].oval;
  
  if (onums == NULL) {
    SPVM_CROAK("Array must be defined", "SPVM/CORE.c", __LINE__);
  }
  
  if (onums == NULL) {
    SPVM_CROAK("Array must be defined", "SPVM/CORE.c", __LINE__);
  }

  int32_t array_length = env->len(env, onums);
  if (array_length == 0) {
    return SPVM_SUCCESS;
  }
  
  int16_t* nums = env->selems(env, onums);
  
  DualPivotQuickSort_short(nums, 0, array_length - 1);
  
  return SPVM_SUCCESS;
}

int32_t SPVM_NATIVE_SPVM__CORE__sorti(SPVM_ENV* env, SPVM_VALUE* stack) {
  void* onums = stack[0].oval;
  
  if (onums == NULL) {
    SPVM_CROAK("Array must be defined", "SPVM/CORE.c", __LINE__);
  }

  int32_t array_length = env->len(env, onums);
  if (array_length == 0) {
    return SPVM_SUCCESS;
  }
  
  int32_t* nums = env->ielems(env, onums);
  
  DualPivotQuickSort_int(nums, 0, array_length - 1);
  
  return SPVM_SUCCESS;
}

int32_t SPVM_NATIVE_SPVM__CORE__sortl(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* onums = stack[0].oval;

  int32_t array_length = env->len(env, onums);
  if (array_length == 0) {
    return SPVM_SUCCESS;
  }
  
  int64_t* nums = env->lelems(env, onums);
  
  DualPivotQuickSort_long(nums, 0, array_length - 1);
  
  return SPVM_SUCCESS;
}

int32_t SPVM_NATIVE_SPVM__CORE__sortf(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* onums = stack[0].oval;
  
  int32_t array_length = env->len(env, onums);
  if (array_length == 0) {
    return SPVM_SUCCESS;
  }
  
  float* nums = env->felems(env, onums);
  
  DualPivotQuickSort_float(nums, 0, array_length - 1);
  
  return SPVM_SUCCESS;
}

int32_t SPVM_NATIVE_SPVM__CORE__sortd(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* onums = stack[0].oval;

  int32_t array_length = env->len(env, onums);
  if (array_length == 0) {
    return SPVM_SUCCESS;
  }
  
  double* nums = env->delems(env, onums);
  
  DualPivotQuickSort_double(nums, 0, array_length - 1);
  
  return SPVM_SUCCESS;
}

int32_t SPVM_NATIVE_SPVM__CORE__type_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  void* object = stack[0].oval;
  
  if (object == NULL) {
    return SPVM_EXCEPTION;
  }
  
  void* type_name = env->type_name(env, object);
  
  stack[0].oval = type_name;
  
  return SPVM_SUCCESS;
}

int32_t SPVM_NATIVE_SPVM__CORE__cadd(SPVM_ENV* env, SPVM_VALUE* stack) {
  double _Complex x_in1 = stack[0].dval + stack[1].dval * _Complex_I ;
  double _Complex x_in2 = stack[2].dval + stack[3].dval * _Complex_I ;
  
  double _Complex x_out = x_in1 + x_in2;
  
  stack[0].dval = creal(x_out);
  stack[1].dval = cimag(x_out);
  
  return SPVM_SUCCESS;
}

int32_t SPVM_NATIVE_SPVM__CORE__csub(SPVM_ENV* env, SPVM_VALUE* stack) {
  double _Complex x_in1 = stack[0].dval + stack[1].dval * _Complex_I ;
  double _Complex x_in2 = stack[2].dval + stack[3].dval * _Complex_I ;
  
  double _Complex x_out = x_in1 - x_in2;
  
  stack[0].dval = creal(x_out);
  stack[1].dval = cimag(x_out);
  
  return SPVM_SUCCESS;
}

int32_t SPVM_NATIVE_SPVM__CORE__cmul(SPVM_ENV* env, SPVM_VALUE* stack) {
  double _Complex x_in1 = stack[0].dval + stack[1].dval * _Complex_I ;
  double _Complex x_in2 = stack[2].dval + stack[3].dval * _Complex_I ;
  
  double _Complex x_out = x_in1 * x_in2;
  
  stack[0].dval = creal(x_out);
  stack[1].dval = cimag(x_out);
  
  return SPVM_SUCCESS;
}

int32_t SPVM_NATIVE_SPVM__CORE__cdiv(SPVM_ENV* env, SPVM_VALUE* stack) {
  double _Complex x_in1 = stack[0].dval + stack[1].dval * _Complex_I ;
  double _Complex x_in2 = stack[2].dval + stack[3].dval * _Complex_I ;
  
  double _Complex x_out = x_in1 / x_in2;
  
  stack[0].dval = creal(x_out);
  stack[1].dval = cimag(x_out);
  
  return SPVM_SUCCESS;
}

int32_t SPVM_NATIVE_SPVM__CORE__caddf(SPVM_ENV* env, SPVM_VALUE* stack) {
  float _Complex x_in1 = stack[0].fval + stack[1].fval * _Complex_I ;
  float _Complex x_in2 = stack[2].fval + stack[3].fval * _Complex_I ;
  
  float _Complex x_out = x_in1 + x_in2;
  
  stack[0].fval = creal(x_out);
  stack[1].fval = cimag(x_out);
  
  return SPVM_SUCCESS;
}

int32_t SPVM_NATIVE_SPVM__CORE__csubf(SPVM_ENV* env, SPVM_VALUE* stack) {
  float _Complex x_in1 = stack[0].fval + stack[1].fval * _Complex_I ;
  float _Complex x_in2 = stack[2].fval + stack[3].fval * _Complex_I ;
  
  float _Complex x_out = x_in1 - x_in2;
  
  stack[0].fval = creal(x_out);
  stack[1].fval = cimag(x_out);
  
  return SPVM_SUCCESS;
}

int32_t SPVM_NATIVE_SPVM__CORE__cmulf(SPVM_ENV* env, SPVM_VALUE* stack) {
  float _Complex x_in1 = stack[0].fval + stack[1].fval * _Complex_I ;
  float _Complex x_in2 = stack[2].fval + stack[3].fval * _Complex_I ;
  
  float _Complex x_out = x_in1 * x_in2;
  
  stack[0].fval = creal(x_out);
  stack[1].fval = cimag(x_out);
  
  return SPVM_SUCCESS;
}

int32_t SPVM_NATIVE_SPVM__CORE__cdivf(SPVM_ENV* env, SPVM_VALUE* stack) {
  float _Complex x_in1 = stack[0].fval + stack[1].fval * _Complex_I ;
  float _Complex x_in2 = stack[2].fval + stack[3].fval * _Complex_I ;
  
  float _Complex x_out = x_in1 / x_in2;
  
  stack[0].fval = creal(x_out);
  stack[1].fval = cimag(x_out);
  
  return SPVM_SUCCESS;
}

int32_t SPVM_NATIVE_SPVM__CORE__new_icomplex(SPVM_ENV* env, SPVM_VALUE* stack) { return SPVM_SUCCESS; }

int32_t SPVM_NATIVE_SPVM__CORE__new_lcomplex(SPVM_ENV* env, SPVM_VALUE* stack) { return SPVM_SUCCESS; }

int32_t SPVM_NATIVE_SPVM__CORE__new_fcomplex(SPVM_ENV* env, SPVM_VALUE* stack) { return SPVM_SUCCESS; }

int32_t SPVM_NATIVE_SPVM__CORE__new_dcomplex(SPVM_ENV* env, SPVM_VALUE* stack) { return SPVM_SUCCESS; }

int32_t SPVM_NATIVE_SPVM__CORE__time(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;

  int64_t timer_value = (int64_t)time(NULL);
  
  stack[0].lval = timer_value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_NATIVE_SPVM__CORE__print(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  void* string = stack[0].oval;
  
  const char* bytes = (const char*)env->belems(env, string);
  int32_t string_length = env->len(env, string);
  
  {
    int32_t i;
    for (i = 0; i < string_length; i++) {
      putchar(bytes[i]);
    }
  }
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_NATIVE_SPVM__CORE__warn(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  void* object = stack[0].oval;
  
  const char* bytes = (const char*)env->belems(env, object);
  int32_t string_length = env->len(env, object);
  
  {
    int32_t i;
    for (i = 0; i < string_length; i++) {
      putc(bytes[i], stderr);
    }
  }
  
  fprintf(stderr, "\n");
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_NATIVE_SPVM__CORE__isinff(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  float fval = stack[0].fval;
  
  stack[0].ival = isinf(fval);
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_NATIVE_SPVM__CORE__isfinitef(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  float fval = stack[0].fval;
  
  stack[0].ival = isfinite(fval);
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_NATIVE_SPVM__CORE__isnanf(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  float fval = stack[0].fval;
  
  stack[0].ival = isnan(fval);
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_NATIVE_SPVM__CORE__INFINITYF(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].fval = (float)INFINITY;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_NATIVE_SPVM__CORE__NANF(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].fval = (float)NAN;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_NATIVE_SPVM__CORE__INFINITY(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].dval = (double)INFINITY;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_NATIVE_SPVM__CORE__NAN(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].dval = (double)NAN;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_NATIVE_SPVM__CORE__signbitf(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  double fval = stack[0].fval;
  
  stack[0].ival = signbit(fval);
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_NATIVE_SPVM__CORE__signbit(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  double dval = stack[0].dval;
  
  stack[0].ival = signbit(dval);
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_NATIVE_SPVM__CORE__isinf(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  double dval = stack[0].dval;
  
  stack[0].ival = isinf(dval);
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_NATIVE_SPVM__CORE__isnan(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  double dval = stack[0].dval;
  
  stack[0].ival = isnan(dval);
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_NATIVE_SPVM__CORE__isfinite(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  double dval = stack[0].dval;
  
  stack[0].ival = isfinite(dval);
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_NATIVE_SPVM__CORE__sin(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = sin(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_NATIVE_SPVM__CORE__cos(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = cos(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_NATIVE_SPVM__CORE__tan(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = tan(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_NATIVE_SPVM__CORE__asin(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = asin(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_NATIVE_SPVM__CORE__acosh(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = acosh(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_NATIVE_SPVM__CORE__atanh(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = atanh(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_NATIVE_SPVM__CORE__asinh(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = asinh(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_NATIVE_SPVM__CORE__acos(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = acos(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_NATIVE_SPVM__CORE__atan(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = atan(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_NATIVE_SPVM__CORE__exp(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = exp(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_NATIVE_SPVM__CORE__exp2(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = exp2(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_NATIVE_SPVM__CORE__log(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = log(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_NATIVE_SPVM__CORE__log10(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = log10(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_NATIVE_SPVM__CORE__sqrt(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = sqrt(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_NATIVE_SPVM__CORE__cbrt(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = cbrt(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_NATIVE_SPVM__CORE__ceil(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = ceil(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_NATIVE_SPVM__CORE__remainder(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  // x - Math.Round(x / y) * y
  double value = remainder(stack[0].dval, stack[1].dval);

  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_NATIVE_SPVM__CORE__floor(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = floor(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_NATIVE_SPVM__CORE__nearbyint(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = nearbyint(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_NATIVE_SPVM__CORE__atan2(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = atan2(stack[0].dval, stack[1].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_NATIVE_SPVM__CORE__pow(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = pow(stack[0].dval, stack[1].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_NATIVE_SPVM__CORE__round(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = round(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_NATIVE_SPVM__CORE__abs(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  int32_t value = (int32_t)labs(stack[0].ival);
  
  stack[0].ival = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_NATIVE_SPVM__CORE__labs(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  int64_t value = (int64_t)labs(stack[0].lval);
  
  stack[0].lval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_NATIVE_SPVM__CORE__fabs(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = fabs(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_NATIVE_SPVM__CORE__erf(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = erf(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_NATIVE_SPVM__CORE__erfc(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = erfc(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_NATIVE_SPVM__CORE__lgamma(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = lgamma(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_NATIVE_SPVM__CORE__tgamma(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = tgamma(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_NATIVE_SPVM__CORE__sinh(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = sinh(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_NATIVE_SPVM__CORE__cosh(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = cosh(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_NATIVE_SPVM__CORE__tanh(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = tanh(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_NATIVE_SPVM__CORE__hypot(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = hypot(stack[0].dval, stack[1].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_NATIVE_SPVM__CORE__expm1(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = expm1(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_NATIVE_SPVM__CORE__log1p(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  
  double value = log1p(stack[0].dval);
  
  stack[0].dval = value;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_NATIVE_SPVM__CORE__FLT_MAX(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].fval = FLT_MAX;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_NATIVE_SPVM__CORE__FLT_MIN(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].fval = FLT_MIN;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_NATIVE_SPVM__CORE__DBL_MAX(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].dval = DBL_MAX;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_NATIVE_SPVM__CORE__DBL_MIN(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].dval = DBL_MIN;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_NATIVE_SPVM__CORE__INT8_MIN(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].bval = (int8_t)-128;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_NATIVE_SPVM__CORE__INT8_MAX(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].bval = (int8_t)127;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_NATIVE_SPVM__CORE__INT16_MIN(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].sval = (int16_t)-32768;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_NATIVE_SPVM__CORE__INT16_MAX(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].sval = (int16_t)32767;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_NATIVE_SPVM__CORE__INT32_MIN(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].ival = (int32_t)-2147483648UL;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_NATIVE_SPVM__CORE__INT32_MAX(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].ival = (int32_t)2147483647L;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_NATIVE_SPVM__CORE__INT64_MIN(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].lval = (int64_t)-9223372036854775808ULL;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_NATIVE_SPVM__CORE__INT64_MAX(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].lval = (int64_t)9223372036854775807LL;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_NATIVE_SPVM__CORE__PI(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].dval = 3.14159265358979323846;
  
  return SPVM_SUCCESS;;
}

int32_t SPVM_NATIVE_SPVM__CORE__E(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;
  (void)stack;
  
  stack[0].dval = 2.7182818284590452354;
  
  return SPVM_SUCCESS;;
}

// https://github.com/gcc-mirror/gcc/blob/master/libstdc++-v3/libsupc++/hash_bytes.cc#L72-L112
int32_t SPVM_NATIVE_SPVM__CORE__murmur_hash(SPVM_ENV* env, SPVM_VALUE* stack) {
  (void)env;

  void* object = stack[0].oval;
  uint32_t seed = stack[1].ival;

  const char* buf = (const char*)env->belems(env, object);
  uint32_t len = env->len(env, object);

  uint32_t m = 0x5bd1e995;
  uint32_t hash = seed ^ len;

  // Mix 4 bytes at a time into the hash.
  while(len >= 4) {
    uint32_t k;
    memcpy(&k, buf, sizeof(k));
    k *= m;
    k ^= k >> 24;
    k *= m;
    hash *= m;
    hash ^= k;
    buf += 4;
    len -= 4;
  }

  // Handle the last few bytes of the input array.
  switch(len) {
    case 3:
      hash ^= (unsigned char)buf[2] << 16;
    case 2:
      hash ^= (unsigned char)buf[1] << 8;
    case 1:
      hash ^= (unsigned char)buf[0];
      hash *= m;
    };

  // Do a few final mixes of the hash.
  hash ^= hash >> 13;
  hash *= m;
  hash ^= hash >> 15;
  stack[0].lval = hash; // return a long value to ensure being positive.

  return SPVM_SUCCESS;;
}
