#include "spvm_native.h"

static const char* MFILE = "SPVM/Sort.c";

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

int32_t SPNATIVE__SPVM__Sort__sortb_native(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* sv_nums = stack[0].oval;
  int32_t offset = stack[1].ival;
  int32_t length = stack[2].ival;
  
  int8_t* nums = env->get_elems_byte(env, sv_nums);
  
  DualPivotQuickSort_byte(nums, offset, offset + length - 1);
  
  return 0;
}

int32_t SPNATIVE__SPVM__Sort__sorts_native(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  void* sv_nums = stack[0].oval;
  int32_t offset = stack[1].ival;
  int32_t length = stack[2].ival;
  
  int16_t* nums = env->get_elems_short(env, sv_nums);
  
  DualPivotQuickSort_short(nums, offset, offset + length - 1);
  
  return 0;
}

int32_t SPNATIVE__SPVM__Sort__sorti_native(SPVM_ENV* env, SPVM_VALUE* stack) {
  void* sv_nums = stack[0].oval;
  int32_t offset = stack[1].ival;
  int32_t length = stack[2].ival;
  
  int32_t* nums = env->get_elems_int(env, sv_nums);
  
  DualPivotQuickSort_int(nums, offset, offset + length - 1);
  
  return 0;
}

int32_t SPNATIVE__SPVM__Sort__sortl_native(SPVM_ENV* env, SPVM_VALUE* stack) {
  void* sv_nums = stack[0].oval;
  int32_t offset = stack[1].ival;
  int32_t length = stack[2].ival;
  
  int64_t* nums = env->get_elems_long(env, sv_nums);
  
  DualPivotQuickSort_long(nums, offset, offset + length - 1);
  
  return 0;
}

int32_t SPNATIVE__SPVM__Sort__sortf_native(SPVM_ENV* env, SPVM_VALUE* stack) {
  void* sv_nums = stack[0].oval;
  int32_t offset = stack[1].ival;
  int32_t length = stack[2].ival;
  
  float* nums = env->get_elems_float(env, sv_nums);
  
  DualPivotQuickSort_float(nums, offset, offset + length - 1);
  
  return 0;
}

int32_t SPNATIVE__SPVM__Sort__sortd_native(SPVM_ENV* env, SPVM_VALUE* stack) {
  void* sv_nums = stack[0].oval;
  int32_t offset = stack[1].ival;
  int32_t length = stack[2].ival;
  
  double* nums = env->get_elems_double(env, sv_nums);
  
  DualPivotQuickSort_double(nums, offset, offset + length - 1);
  
  return 0;
}

