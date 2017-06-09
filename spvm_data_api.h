#ifndef SPVM_DATA_API_H
#define SPVM_DATA_API_H

union SPVM_value;
typedef union SPVM_value SPVM_VALUE;

struct SPVM_data;
typedef struct SPVM_data SPVM_DATA;

struct SPVM_data_array;
typedef struct SPVM_data_array SPVM_DATA_ARRAY;

struct SPVM_data_object;
typedef struct SPVM_data_object SPVM_DATA_OBJECT;

// SPVM_VALUE
union SPVM_value {
  int8_t byte_value;
  int16_t short_value;
  int32_t int_value;
  int64_t long_value;
  float float_value;
  double double_value;
  void* address_value;
};

// SPVM_DATA
enum {
  SPVM_DATA_C_HEADER_BYTE_SIZE = 32
};

enum {
  SPVM_DATA_C_TYPE_OBJECT = 0,
  SPVM_DATA_C_TYPE_ARRAY = 1,
};

struct SPVM_data {
  int32_t* constant_pool;
  int8_t type;
  int32_t ref_count;
};

// SPVM_DATA_ARRAY
struct SPVM_data_array {
  int32_t* constant_pool;
  int8_t type;
  int8_t value_type;
  int32_t ref_count;
  int32_t length;
};

enum {
  SPVM_DATA_ARRAY_C_VALUE_TYPE_BYTE = 0,
  SPVM_DATA_ARRAY_C_VALUE_TYPE_SHORT = 1,
  SPVM_DATA_ARRAY_C_VALUE_TYPE_INT = 2,
  SPVM_DATA_ARRAY_C_VALUE_TYPE_LONG = 3,
  SPVM_DATA_ARRAY_C_VALUE_TYPE_FLOAT = 4,
  SPVM_DATA_ARRAY_C_VALUE_TYPE_DOUBLE = 5,
  SPVM_DATA_ARRAY_C_VALUE_TYPE_REF = 6,
};

extern const int32_t SPVM_DATA_ARRAY_C_VALUE_SIZES[];

// SPVM_DATA_OBJECT
struct SPVM_data_object {
  int32_t* constant_pool;
  int8_t type;
  int32_t ref_count;
  int32_t package_constant_pool_address;
  int32_t field_name_indexes_constant_pool_address;
};

int32_t* SPVM_DATA_API_get_constant_pool(SPVM_DATA* data);
int32_t SPVM_DATA_API_get_ref_count(SPVM_DATA* data);
int32_t SPVM_DATA_API_get_array_length(SPVM_DATA_ARRAY* data_array);
int8_t* SPVM_DATA_API_get_array_values_byte(SPVM_DATA_ARRAY* data_array);
int16_t* SPVM_DATA_API_get_array_values_short(SPVM_DATA_ARRAY* data_array);
int32_t* SPVM_DATA_API_get_array_values_int(SPVM_DATA_ARRAY* data_array);
int64_t* SPVM_DATA_API_get_array_values_long(SPVM_DATA_ARRAY* data_array);
float* SPVM_DATA_API_get_array_values_float(SPVM_DATA_ARRAY* data_array);
double* SPVM_DATA_API_get_array_values_double(SPVM_DATA_ARRAY* data_array);
SPVM_DATA** SPVM_DATA_API_get_array_values_ref(SPVM_DATA_ARRAY* data_array);

int32_t SPVM_DATA_API_get_object_fields_length(SPVM_DATA_OBJECT* data_object);
int32_t SPVM_DATA_API_dump_object_field_names(SPVM_DATA_OBJECT* data_object);
int32_t SPVM_DATA_API_get_object_field_index(SPVM_DATA_OBJECT* data_object, const char* name);
SPVM_VALUE* SPVM_DATA_API_get_object_fields(SPVM_DATA_OBJECT* data_object);

int8_t SPVM_DATA_API_get_object_field_value_byte(SPVM_DATA_OBJECT* data_object, const char* name);
int16_t SPVM_DATA_API_get_object_field_value_short(SPVM_DATA_OBJECT* data_object, const char* name);
int32_t SPVM_DATA_API_get_object_field_value_int(SPVM_DATA_OBJECT* data_object, const char* name);
int64_t SPVM_DATA_API_get_object_field_value_long(SPVM_DATA_OBJECT* data_object, const char* name);
float SPVM_DATA_API_get_object_field_value_float(SPVM_DATA_OBJECT* data_object, const char* name);
double SPVM_DATA_API_get_object_field_value_double(SPVM_DATA_OBJECT* data_object, const char* name);
SPVM_DATA* SPVM_DATA_API_get_object_field_value_ref(SPVM_DATA_OBJECT* data_object, const char* name);

void SPVM_DATA_API_set_object_field_value_byte(SPVM_DATA_OBJECT* data_object, const char* name, int8_t value);
void SPVM_DATA_API_set_object_field_value_short(SPVM_DATA_OBJECT* data_object, const char* name, int16_t value);
void SPVM_DATA_API_set_object_field_value_int(SPVM_DATA_OBJECT* data_object, const char* name, int32_t value);
void SPVM_DATA_API_set_object_field_value_long(SPVM_DATA_OBJECT* data_object, const char* name, int64_t value);
void SPVM_DATA_API_set_object_field_value_float(SPVM_DATA_OBJECT* data_object, const char* name, float value);
void SPVM_DATA_API_set_object_field_value_double(SPVM_DATA_OBJECT* data_object, const char* name, double value);

#endif
