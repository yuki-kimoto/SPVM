#include "spvm.h"
#include "spvm_ref_array.h"

const int32_t SPVM_REF_ARRAY_C_VALUE_SIZES[] = {
  sizeof(int8_t),
  sizeof(int16_t),
  sizeof(int32_t),
  sizeof(int64_t),
  sizeof(float),
  sizeof(double),
  sizeof(void*),
};
