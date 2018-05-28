#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"

#include "ppport.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <assert.h>
#include <inttypes.h>
#include <stdint.h>

#include "spvm_compiler.h"
#include "spvm_hash.h"
#include "spvm_list.h"
#include "spvm_util_allocator.h"
#include "spvm_runtime.h"
#include "spvm_op.h"
#include "spvm_sub.h"
#include "spvm_package.h"
#include "spvm_sub.h"
#include "spvm_my.h"
#include "spvm_type.h"
#include "spvm_field.h"
#include "spvm_object.h"
#include "spvm_api.h"
#include "spvm_opcode_builder.h"
#include "spvm_jitcode_builder.h"
#include "spvm_list.h"
#include "spvm_jitcode_builder.h"
#include "spvm_string_buffer.h"
#include "spvm_basic_type.h"
#include "spvm_use.h"

static SPVM_VALUE call_sub_args[255];

SPVM_ENV* SPVM_XS_UTIL_get_api() {
  
  SV* sv_api = get_sv("SPVM::API", 0);
  
  SPVM_ENV* api = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_api)));
  
  return api;
}

SV* SPVM_XS_UTIL_new_sv_object(SPVM_OBJECT* object, const char* package) {
  // Create object
  size_t iv_object = PTR2IV(object);
  SV* sviv_object = sv_2mortal(newSViv(iv_object));
  SV* sv_object = sv_2mortal(newRV_inc(sviv_object));
  HV* hv_class = gv_stashpv(package, 0);
  sv_bless(sv_object, hv_class);
  
  return sv_object;
}

SV* SPVM_XS_UTIL_create_sv_type_name(int32_t basic_type_id, int32_t dimension) {
  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();

  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->get_runtime(api);
  SPVM_COMPILER* compiler = runtime->compiler;

  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_fetch(compiler->basic_types, basic_type_id);
  assert(basic_type);

  SV* sv_type_name = sv_2mortal(newSVpv("SPVM::", 0));
  
  sv_catpv(sv_type_name, basic_type->name);
  
  int32_t dim_index;
  for (dim_index = 0; dim_index < dimension; dim_index++) {
    sv_catpv(sv_type_name, "[]");
  }
  
  return sv_type_name;
}

SPVM_OBJECT* SPVM_XS_UTIL_get_object(SV* sv_object) {
  
  if (SvOK(sv_object)) {
    size_t iv_object = SvIV(SvRV(sv_object));
    SPVM_OBJECT* object = INT2PTR(SPVM_OBJECT*, iv_object);
    
    return object;
  }
  else {
    return NULL;
  }
}

MODULE = SPVM::Perl::Object		PACKAGE = SPVM::Perl::Object

SV*
DESTROY(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_object = ST(0);
  
  assert(SvOK(sv_object));
  
  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  // Get object
  void* object = SPVM_XS_UTIL_get_object(sv_object);
  
  assert(api->get_ref_count(api, object));
  
  // Decrement reference count
  api->dec_ref_count(api, object);
  
  XSRETURN(0);
}

MODULE = SPVM::Perl::Object::Package::String		PACKAGE = SPVM::Perl::Object::Package::String

SV*
new_string(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_class = ST(0);
  (void)sv_class;
  
  SV* sv_bytes = ST(1);
  int32_t length = sv_len(sv_bytes);
  
  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  // New string
  void* string =  api->new_string(api, SvPV_nolen(sv_bytes), length);
  
  // Increment reference count
  api->inc_ref_count(api, string);
  
  // New sv string
  SV* sv_string = SPVM_XS_UTIL_new_sv_object(string, "SPVM::Perl::Object::Package::String");
  
  XPUSHs(sv_string);
  XSRETURN(1);
}

SV*
to_data(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_string = ST(0);

  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  // Get object
  void* string = SPVM_XS_UTIL_get_object(sv_string);
  
  int32_t string_length = api->get_array_length(api, string);
  
  int8_t* bytes = api->get_byte_array_elements(api, string);

  SV* sv_data = sv_2mortal(newSVpvn((char*)bytes, string_length));
  
  XPUSHs(sv_data);
  XSRETURN(1);
}

MODULE = SPVM::Perl::Object::Array::Byte		PACKAGE = SPVM::Perl::Object::Array::Byte

SV*
new_len(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_class = ST(0);
  (void)sv_class;
  
  SV* sv_length = ST(1);
  
  int32_t length = (int32_t)SvIV(sv_length);
  
  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  // New array
  void* array =  api->new_byte_array(api, length);
  
  // Increment reference count
  api->inc_ref_count(api, array);
  
  // New sv array
  SV* sv_byte_array = SPVM_XS_UTIL_new_sv_object(array, "SPVM::Perl::Object::Array::Byte");
  
  XPUSHs(sv_byte_array);
  XSRETURN(1);
}

SV*
set_elements(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_array = ST(0);
  SV* sv_values = ST(1);
  
  if (!(SvROK(sv_values) && sv_derived_from(sv_values, "ARRAY"))) {
    croak("Values must be array refenrece(SPVM::Perl::Object::Array::Byte::set_elements())");
  }
  
  AV* av_values = (AV*)SvRV(sv_values);
  
  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  // Get object
  void* array = SPVM_XS_UTIL_get_object(sv_array);
  
  int32_t length = api->get_array_length(api, array);
  
  int8_t* elements = api->get_byte_array_elements(api, array);

  // Check length
  if (av_len(av_values) + 1 != length) {
    croak("Elements length must be same as array length(SPVM::Perl::Object::Array::Byte::set_elements())");
  }
  
  {
    int32_t i;
    for (i = 0; i < length; i++) {
      SV** sv_value_ptr = av_fetch(av_values, i, 0);
      SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
      elements[i] = (int8_t)SvIV(sv_value);
    }
  }
  
  XSRETURN(0);
}

SV*
set_elements_range(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_array = ST(0);
  SV* sv_index = ST(1);
  SV* sv_count = ST(2);
  SV* sv_values = ST(3);
  
  // Index
  int32_t index = (int32_t)SvIV(sv_index);
  
  // Count
  int32_t count = (int32_t)SvIV(sv_count);
  
  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  // Get object
  void* array = SPVM_XS_UTIL_get_object(sv_array);
  
  // Length
  int32_t length = api->get_array_length(api, array);
  
  // Check index
  if (index < 0 || index > length - 1) {
    croak("Index is out of range(SPVM::Perl::Object::Array::Byte::set_elements_range())");
  }
  
  // Check count
  if (count < 0 || index + count > length - 1) {
    croak("Index + count is out of range(SPVM::Perl::Object::Array::Byte::set_elements_range())");
  }
  
  // Check if sv values is array reference
  if (!(SvROK(sv_values) && sv_derived_from(sv_values, "ARRAY"))) {
    croak("Values must be array refenrece(SPVM::Perl::Object::Array::Byte::set_elements_range())");
  }
  
  AV* av_values = (AV*)SvRV(sv_values);
  
  // Check elements length
  if (av_len(av_values) + 1 != count) {
    croak("Elements length must be same as count argument(SPVM::Perl::Object::Array::Byte::set_elements_range())");
  }
  
  // Elements
  int8_t* elements = api->get_byte_array_elements(api, array);
  
  // Set element value
  {
    int32_t i;
    
    for (i = 0; i < count; i++) {
      SV** sv_value_ptr = av_fetch(av_values, i, 0);
      SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
      elements[index + i] = (int8_t)SvIV(sv_value);
    }
  }
  
  XSRETURN(0);
}

SV*
set_data(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_array = ST(0);
  SV* sv_data = ST(1);
  
  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  // Get object
  void* array = SPVM_XS_UTIL_get_object(sv_array);
  
  int32_t length = api->get_array_length(api, array);
  
  int8_t* elements = api->get_byte_array_elements(api, array);
  
  // Check range
  if ((int32_t)sv_len(sv_data) != length) {
    croak("Data total byte size must be same as array length(SPVM::Perl::Object::Array::Byte::set_data())");
  }
  
  if (length > 0) {
    memcpy(elements, SvPV_nolen(sv_data), length);
  }
  
  XSRETURN(0);
}

SV*
set_data_range(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_array = ST(0);
  SV* sv_index = ST(1);
  SV* sv_count = ST(2);
  SV* sv_data = ST(3);
  
  // Index
  int32_t index = (int32_t)SvIV(sv_index);
  
  // Count
  int32_t count = (int32_t)SvIV(sv_count);
  
  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  // Get object
  void* array = SPVM_XS_UTIL_get_object(sv_array);
  
  // Length
  int32_t length = api->get_array_length(api, array);
  
  // Check index
  if (index < 0 || index > length - 1) {
    croak("Index is out of range(SPVM::Perl::Object::Array::Byte::set_data_range())");
  }
  
  // Check count
  if (count < 0 || index + count > length - 1) {
    croak("Index + count is out of range(SPVM::Perl::Object::Array::Byte::set_data_range())");
  }
  
  // Check data byte size
  int32_t data_byte_size = (int32_t)sv_len(sv_data);
  
  if (data_byte_size != count) {
    croak("Data byte size must be same as count argument(SPVM::Perl::Object::Array::Byte::set_data_range())");
  }
  
  // Elements
  int8_t* elements = api->get_byte_array_elements(api, array);
  
  // Copy data
  if (count > 0) {
    memcpy(elements + index, SvPV_nolen(sv_data), count);
  }
  
  XSRETURN(0);
}

SV*
set(...)
  PPCODE:
{
  (void)RETVAL;
  
  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  SV* sv_array = ST(0);
  SV* sv_index = ST(1);
  SV* sv_value = ST(2);
  
  // Index
  int32_t index = (int32_t)SvIV(sv_index);

  // Array
  void* array = SPVM_XS_UTIL_get_object(sv_array);
  
  // Length
  int32_t length = api->get_array_length(api, array);
  
  // Check range
  if (index < 0 || index > length - 1) {
    croak("Out of range(SPVM::Perl::Object::Array::Byte::set())");
  }
  
  // Value
  int8_t value = (int8_t)SvIV(sv_value);
  
  // Set element
  int8_t* elements = api->get_byte_array_elements(api, array);
  
  elements[index] = value;
  
  XSRETURN(0);
}

SV*
get(...)
  PPCODE:
{
  (void)RETVAL;
  
  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  SV* sv_array = ST(0);
  SV* sv_index = ST(1);
  
  // Index
  int32_t index = (int32_t)SvIV(sv_index);

  // Array
  void* array = SPVM_XS_UTIL_get_object(sv_array);
  
  // Length
  int32_t length = api->get_array_length(api, array);
  
  // Check range
  if (index < 0 || index > length - 1) {
    croak("Out of range(SPVM::Perl::Object::Array::Byte::set())");
  }
  
  // Get element
  int8_t* elements = api->get_byte_array_elements(api, array);
  int8_t value = elements[index];
  SV* sv_value = sv_2mortal(newSViv(value));
  
  XPUSHs(sv_value);
  XSRETURN(1);
}

SV*
get_elements(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_array = ST(0);
  
  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  // Get object
  void* array = SPVM_XS_UTIL_get_object(sv_array);
  
  int32_t length = api->get_array_length(api, array);
  
  int8_t* elements = api->get_byte_array_elements(api, array);
  
  AV* av_values = (AV*)sv_2mortal((SV*)newAV());
  {
    int32_t i;
    for (i = 0; i < length; i++) {
      SV* sv_value = sv_2mortal(newSViv(elements[i]));
      av_push(av_values, SvREFCNT_inc(sv_value));
    }
  }
  SV* sv_values = sv_2mortal(newRV_inc((SV*)av_values));
  
  XPUSHs(sv_values);
  XSRETURN(1);
}

SV*
get_elements_range(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_array = ST(0);
  SV* sv_index = ST(1);
  SV* sv_count = ST(2);
  
  // Index
  int32_t index = (int32_t)SvIV(sv_index);
  
  // Count
  int32_t count = (int32_t)SvIV(sv_count);
  
  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  // Get object
  void* array = SPVM_XS_UTIL_get_object(sv_array);
  
  // Length
  int32_t length = api->get_array_length(api, array);
  
  // Check index
  if (index < 0 || index > length - 1) {
    croak("Index is out of range(SPVM::Perl::Object::Array::Byte::get_elements_range())");
  }
  
  // Check count
  if (count < 0 || index + count > length - 1) {
    croak("Index + count is out of range(SPVM::Perl::Object::Array::Byte::get_elements_range())");
  }
  
  int8_t* elements = api->get_byte_array_elements(api, array);
  
  AV* av_values = (AV*)sv_2mortal((SV*)newAV());
  {
    int32_t i;
    for (i = index; i < index + count; i++) {
      SV* sv_value = sv_2mortal(newSViv(elements[i]));
      av_push(av_values, SvREFCNT_inc(sv_value));
    }
  }
  SV* sv_values = sv_2mortal(newRV_inc((SV*)av_values));
  
  XPUSHs(sv_values);
  XSRETURN(1);
}

SV*
to_data(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_array = ST(0);

  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  // Get object
  void* array = SPVM_XS_UTIL_get_object(sv_array);
  
  int32_t length = api->get_array_length(api, array);
  
  int8_t* elements = api->get_byte_array_elements(api, array);
  
  SV* sv_data = sv_2mortal(newSVpvn((char*)elements, length));
  
  XPUSHs(sv_data);
  XSRETURN(1);
}

SV*
to_data_range(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_array = ST(0);
  SV* sv_index = ST(1);
  SV* sv_count = ST(2);
  
  // Index
  int32_t index = (int32_t)SvIV(sv_index);
  
  // Count
  int32_t count = (int32_t)SvIV(sv_count);
  
  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  // Get object
  void* array = SPVM_XS_UTIL_get_object(sv_array);
  
  // Length
  int32_t length = api->get_array_length(api, array);
  
  // Check index
  if (index < 0 || index > length - 1) {
    croak("Index is out of range(SPVM::Perl::Object::Array::Byte::to_data_range())");
  }
  
  // Check count
  if (count < 0 || index + count > length - 1) {
    croak("Index + count is out of range(SPVM::Perl::Object::Array::Byte::to_data_range())");
  }
  
  int8_t* elements = api->get_byte_array_elements(api, array);
  
  SV* sv_data = sv_2mortal(newSVpvn((char*)(elements + index), count));
  
  XPUSHs(sv_data);
  XSRETURN(1);
}

MODULE = SPVM::Perl::Object::Array::Short		PACKAGE = SPVM::Perl::Object::Array::Short

SV*
new_len(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_class = ST(0);
  (void)sv_class;
  
  SV* sv_length = ST(1);
  
  int32_t length = (int32_t)SvIV(sv_length);
  
  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  // New array
  void* array =  api->new_short_array(api, length);
  
  // Increment reference count
  api->inc_ref_count(api, array);
  
  // New sv array
  SV* sv_array = SPVM_XS_UTIL_new_sv_object(array, "SPVM::Perl::Object::Array::Short");
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
set_elements(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_array = ST(0);
  SV* sv_values = ST(1);
  AV* av_values = (AV*)SvRV(sv_values);

  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  // Get object
  void* array = SPVM_XS_UTIL_get_object(sv_array);
  
  int32_t length = api->get_array_length(api, array);
  
  int16_t* elements = api->get_short_array_elements(api, array);

  // Check range
  if (av_len(av_values) + 1 != length) {
    croak("Elements length must be same as array length(SPVM::Perl::Object::Array::Short::set_elements())");
  }
  
  {
    int32_t i;
    for (i = 0; i < length; i++) {
      SV** sv_value_ptr = av_fetch(av_values, i, 0);
      SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
      elements[i] = (int16_t)SvIV(sv_value);
    }
  }
  
  XSRETURN(0);
}

SV*
set_elements_range(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_array = ST(0);
  SV* sv_index = ST(1);
  SV* sv_count = ST(2);
  SV* sv_values = ST(3);
  
  // Index
  int32_t index = (int32_t)SvIV(sv_index);
  
  // Count
  int32_t count = (int32_t)SvIV(sv_count);
  
  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  // Get object
  void* array = SPVM_XS_UTIL_get_object(sv_array);
  
  // Length
  int32_t length = api->get_array_length(api, array);
  
  // Check index
  if (index < 0 || index > length - 1) {
    croak("Index is out of range(SPVM::Perl::Object::Array::Short::set_elements_range())");
  }
  
  // Check count
  if (count < 0 || index + count > length - 1) {
    croak("Index + count is out of range(SPVM::Perl::Object::Array::Short::set_elements_range())");
  }
  
  // Check if sv values is array reference
  if (!(SvROK(sv_values) && sv_derived_from(sv_values, "ARRAY"))) {
    croak("Values must be array refenrece(SPVM::Perl::Object::Array::Short::set_elements_range())");
  }
  
  AV* av_values = (AV*)SvRV(sv_values);
  
  // Check elements length
  if (av_len(av_values) + 1 != count) {
    croak("Elements length must be same as count argument(SPVM::Perl::Object::Array::Short::set_elements_range())");
  }
  
  // Elements
  int16_t* elements = api->get_short_array_elements(api, array);
  
  // Set element value
  {
    int32_t i;
    
    for (i = 0; i < count; i++) {
      SV** sv_value_ptr = av_fetch(av_values, i, 0);
      SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
      elements[index + i] = (int16_t)SvIV(sv_value);
    }
  }
  
  XSRETURN(0);
}

SV*
set_data(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_array = ST(0);
  SV* sv_data = ST(1);
  
  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  // Get object
  void* array = SPVM_XS_UTIL_get_object(sv_array);
  
  int32_t length = api->get_array_length(api, array);
  
  int16_t* elements = api->get_short_array_elements(api, array);
  
  // Check range
  if ((int32_t)sv_len(sv_data) != length * 2) {
    croak("Data total byte size must be same as array length * 2(SPVM::Perl::Object::Array::Short::set_data())");
  }
  
  if (length > 0) {
    memcpy(elements, SvPV_nolen(sv_data), length * 2);
  }
  
  XSRETURN(0);
}

SV*
set_data_range(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_array = ST(0);
  SV* sv_index = ST(1);
  SV* sv_count = ST(2);
  SV* sv_data = ST(3);
  
  // Index
  int32_t index = (int32_t)SvIV(sv_index);
  
  // Count
  int32_t count = (int32_t)SvIV(sv_count);
  
  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  // Get object
  void* array = SPVM_XS_UTIL_get_object(sv_array);
  
  // Length
  int32_t length = api->get_array_length(api, array);
  
  // Check index
  if (index < 0 || index > length - 1) {
    croak("Index is out of range(SPVM::Perl::Object::Array::Short::set_data_range())");
  }
  
  // Check count
  if (count < 0 || index + count > length - 1) {
    croak("Index + count is out of range(SPVM::Perl::Object::Array::Short::set_data_range())");
  }
  
  // Check data short size
  int32_t data_short_size = (int32_t)sv_len(sv_data);
  
  if (data_short_size != count * 2) {
    croak("Data byte size must be same as count argument * 2(SPVM::Perl::Object::Array::Short::set_data_range())");
  }
  
  // Elements
  int16_t* elements = api->get_short_array_elements(api, array);
  
  // Copy data
  if (count > 0) {
    memcpy(elements + index, SvPV_nolen(sv_data), count * 2);
  }
  
  XSRETURN(0);
}

SV*
set(...)
  PPCODE:
{
  (void)RETVAL;
  
  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  SV* sv_array = ST(0);
  SV* sv_index = ST(1);
  SV* sv_value = ST(2);
  
  // Index
  int32_t index = (int32_t)SvIV(sv_index);

  // Array
  void* array = SPVM_XS_UTIL_get_object(sv_array);
  
  // Length
  int32_t length = api->get_array_length(api, array);
  
  // Check range
  if (index < 0 || index > length - 1) {
    croak("Out of range(SPVM::Perl::Object::Array::Short::set())");
  }
  
  // Value
  int16_t value = (int16_t)SvIV(sv_value);
  
  // Set element
  int16_t* elements = api->get_short_array_elements(api, array);
  
  elements[index] = value;
  
  XSRETURN(0);
}

SV*
get(...)
  PPCODE:
{
  (void)RETVAL;
  
  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  SV* sv_array = ST(0);
  SV* sv_index = ST(1);
  
  // Index
  int32_t index = (int32_t)SvIV(sv_index);

  // Array
  void* array = SPVM_XS_UTIL_get_object(sv_array);
  
  // Length
  int32_t length = api->get_array_length(api, array);
  
  // Check range
  if (index < 0 || index > length - 1) {
    croak("Out of range(SPVM::Perl::Object::Array::Short::set())");
  }
  
  // Get element
  int16_t* elements = api->get_short_array_elements(api, array);
  int16_t value = elements[index];
  SV* sv_value = sv_2mortal(newSViv(value));
  
  XPUSHs(sv_value);
  XSRETURN(1);
}

SV*
get_elements(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_array = ST(0);

  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  // Get object
  void* array = SPVM_XS_UTIL_get_object(sv_array);
  
  int32_t length = api->get_array_length(api, array);
  
  int16_t* elements = api->get_short_array_elements(api, array);
  
  AV* av_values = (AV*)sv_2mortal((SV*)newAV());
  {
    int32_t i;
    for (i = 0; i < length; i++) {
      SV* sv_value = sv_2mortal(newSViv(elements[i]));
      av_push(av_values, SvREFCNT_inc(sv_value));
    }
  }
  SV* sv_values = sv_2mortal(newRV_inc((SV*)av_values));
  
  XPUSHs(sv_values);
  XSRETURN(1);
}

SV*
get_elements_range(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_array = ST(0);
  SV* sv_index = ST(1);
  SV* sv_count = ST(2);
  
  // Index
  int32_t index = (int32_t)SvIV(sv_index);
  
  // Count
  int32_t count = (int32_t)SvIV(sv_count);
  
  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  // Get object
  void* array = SPVM_XS_UTIL_get_object(sv_array);
  
  // Length
  int32_t length = api->get_array_length(api, array);
  
  // Check index
  if (index < 0 || index > length - 1) {
    croak("Index is out of range(SPVM::Perl::Object::Array::Short::get_elements_range())");
  }
  
  // Check count
  if (count < 0 || index + count > length - 1) {
    croak("Index + count is out of range(SPVM::Perl::Object::Array::Short::get_elements_range())");
  }
  
  int16_t* elements = api->get_short_array_elements(api, array);
  
  AV* av_values = (AV*)sv_2mortal((SV*)newAV());
  {
    int32_t i;
    for (i = index; i < index + count; i++) {
      SV* sv_value = sv_2mortal(newSViv(elements[i]));
      av_push(av_values, SvREFCNT_inc(sv_value));
    }
  }
  SV* sv_values = sv_2mortal(newRV_inc((SV*)av_values));
  
  XPUSHs(sv_values);
  XSRETURN(1);
}

SV*
to_data(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_array = ST(0);

  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  // Get object
  void* array = SPVM_XS_UTIL_get_object(sv_array);
  
  int32_t length = api->get_array_length(api, array);
  
  int16_t* elements = api->get_short_array_elements(api, array);
  
  SV* sv_data = sv_2mortal(newSVpvn((char*)elements, length * 2));
  
  XPUSHs(sv_data);
  XSRETURN(1);
}

SV*
to_data_range(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_array = ST(0);
  SV* sv_index = ST(1);
  SV* sv_count = ST(2);
  
  // Index
  int32_t index = (int32_t)SvIV(sv_index);
  
  // Count
  int32_t count = (int32_t)SvIV(sv_count);
  
  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  // Get object
  void* array = SPVM_XS_UTIL_get_object(sv_array);
  
  // Length
  int32_t length = api->get_array_length(api, array);
  
  // Check index
  if (index < 0 || index > length - 1) {
    croak("Index is out of range(SPVM::Perl::Object::Array::Short::to_data_range())");
  }
  
  // Check count
  if (count < 0 || index + count > length - 1) {
    croak("Index + count is out of range(SPVM::Perl::Object::Array::Short::to_data_range())");
  }
  
  int16_t* elements = api->get_short_array_elements(api, array);
  
  SV* sv_data = sv_2mortal(newSVpvn((char*)(elements + index), count * 2));
  
  XPUSHs(sv_data);
  XSRETURN(1);
}

MODULE = SPVM::Perl::Object::Array::Int		PACKAGE = SPVM::Perl::Object::Array::Int

SV*
new_len(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_class = ST(0);
  (void)sv_class;
  
  SV* sv_length = ST(1);
  
  int32_t length = (int32_t)SvIV(sv_length);
  
  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  // New array
  void* array =  api->new_int_array(api, length);

  // Increment reference count
  api->inc_ref_count(api, array);
  
  // New sv array
  SV* sv_array = SPVM_XS_UTIL_new_sv_object(array, "SPVM::Perl::Object::Array::Int");
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
set_elements(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_array = ST(0);
  SV* sv_values = ST(1);
  AV* av_values = (AV*)SvRV(sv_values);

  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  // Get object
  void* array = SPVM_XS_UTIL_get_object(sv_array);
  
  int32_t length = api->get_array_length(api, array);
  
  int32_t* elements = api->get_int_array_elements(api, array);

  // Check range
  if (av_len(av_values) + 1 != length) {
    croak("Elements length must be same as array length(SPVM::Perl::Object::Array::Int::set_elements())");
  }
  
  {
    int32_t i;
    for (i = 0; i < length; i++) {
      SV** sv_value_ptr = av_fetch(av_values, i, 0);
      SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
      elements[i] = (int32_t)SvIV(sv_value);
    }
  }
  
  XSRETURN(0);
}

SV*
set_elements_range(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_array = ST(0);
  SV* sv_index = ST(1);
  SV* sv_count = ST(2);
  SV* sv_values = ST(3);
  
  // Index
  int32_t index = (int32_t)SvIV(sv_index);
  
  // Count
  int32_t count = (int32_t)SvIV(sv_count);
  
  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  // Get object
  void* array = SPVM_XS_UTIL_get_object(sv_array);
  
  // Length
  int32_t length = api->get_array_length(api, array);
  
  // Check index
  if (index < 0 || index > length - 1) {
    croak("Index is out of range(SPVM::Perl::Object::Array::Int::set_elements_range())");
  }
  
  // Check count
  if (count < 0 || index + count > length - 1) {
    croak("Index + count is out of range(SPVM::Perl::Object::Array::Int::set_elements_range())");
  }
  
  // Check if sv values is array reference
  if (!(SvROK(sv_values) && sv_derived_from(sv_values, "ARRAY"))) {
    croak("Values must be array refenrece(SPVM::Perl::Object::Array::Int::set_elements_range())");
  }
  
  AV* av_values = (AV*)SvRV(sv_values);
  
  // Check elements length
  if (av_len(av_values) + 1 != count) {
    croak("Elements length must be same as count argument(SPVM::Perl::Object::Array::Int::set_elements_range())");
  }
  
  // Elements
  int32_t* elements = api->get_int_array_elements(api, array);
  
  // Set element value
  {
    int32_t i;
    
    for (i = 0; i < count; i++) {
      SV** sv_value_ptr = av_fetch(av_values, i, 0);
      SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
      elements[index + i] = (int32_t)SvIV(sv_value);
    }
  }
  
  XSRETURN(0);
}

SV*
set_data(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_array = ST(0);
  SV* sv_data = ST(1);
  
  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  // Get object
  void* array = SPVM_XS_UTIL_get_object(sv_array);
  
  int32_t length = api->get_array_length(api, array);
  
  int32_t* elements = api->get_int_array_elements(api, array);
  
  // Check range
  if ((int32_t)sv_len(sv_data) != length * 4) {
    croak("Data total byte size must be same as array length * 4(SPVM::Perl::Object::Array::Int::set_data())");
  }
  
  if (length > 0) {
    memcpy(elements, SvPV_nolen(sv_data), length * 4);
  }
  
  XSRETURN(0);
}

SV*
set_data_range(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_array = ST(0);
  SV* sv_index = ST(1);
  SV* sv_count = ST(2);
  SV* sv_data = ST(3);
  
  // Index
  int32_t index = (int32_t)SvIV(sv_index);
  
  // Count
  int32_t count = (int32_t)SvIV(sv_count);
  
  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  // Get object
  void* array = SPVM_XS_UTIL_get_object(sv_array);
  
  // Length
  int32_t length = api->get_array_length(api, array);
  
  // Check index
  if (index < 0 || index > length - 1) {
    croak("Index is out of range(SPVM::Perl::Object::Array::Int::set_data_range())");
  }
  
  // Check count
  if (count < 0 || index + count > length - 1) {
    croak("Index + count is out of range(SPVM::Perl::Object::Array::Int::set_data_range())");
  }
  
  // Check data int size
  int32_t data_int_size = (int32_t)sv_len(sv_data);
  
  if (data_int_size != count * 4) {
    croak("Data byte size must be same as count argument * 4(SPVM::Perl::Object::Array::Int::set_data_range())");
  }
  
  // Elements
  int32_t* elements = api->get_int_array_elements(api, array);
  
  // Copy data
  if (count > 0) {
    memcpy(elements + index, SvPV_nolen(sv_data), count * 4);
  }
  
  XSRETURN(0);
}

SV*
set(...)
  PPCODE:
{
  (void)RETVAL;
  
  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  SV* sv_array = ST(0);
  SV* sv_index = ST(1);
  SV* sv_value = ST(2);
  
  // Index
  int32_t index = (int32_t)SvIV(sv_index);

  // Array
  void* array = SPVM_XS_UTIL_get_object(sv_array);
  
  // Length
  int32_t length = api->get_array_length(api, array);
  
  // Check range
  if (index < 0 || index > length - 1) {
    croak("Out of range(SPVM::Perl::Object::Array::Int::set())");
  }
  
  // Value
  int32_t value = (int32_t)SvIV(sv_value);
  
  // Set element
  int32_t* elements = api->get_int_array_elements(api, array);
  
  elements[index] = value;
  
  XSRETURN(0);
}

SV*
get(...)
  PPCODE:
{
  (void)RETVAL;
  
  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  SV* sv_array = ST(0);
  SV* sv_index = ST(1);
  
  // Index
  int32_t index = (int32_t)SvIV(sv_index);

  // Array
  void* array = SPVM_XS_UTIL_get_object(sv_array);
  
  // Length
  int32_t length = api->get_array_length(api, array);
  
  // Check range
  if (index < 0 || index > length - 1) {
    croak("Out of range(SPVM::Perl::Object::Array::Int::set())");
  }
  
  // Get element
  int32_t* elements = api->get_int_array_elements(api, array);
  int32_t value = elements[index];
  SV* sv_value = sv_2mortal(newSViv(value));
  
  XPUSHs(sv_value);
  XSRETURN(1);
}

SV*
get_elements(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_array = ST(0);

  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  // Get object
  void* array = SPVM_XS_UTIL_get_object(sv_array);
  
  int32_t length = api->get_array_length(api, array);
  
  int32_t* elements = api->get_int_array_elements(api, array);
  
  AV* av_values = (AV*)sv_2mortal((SV*)newAV());
  {
    int32_t i;
    for (i = 0; i < length; i++) {
      SV* sv_value = sv_2mortal(newSViv(elements[i]));
      av_push(av_values, SvREFCNT_inc(sv_value));
    }
  }
  SV* sv_values = sv_2mortal(newRV_inc((SV*)av_values));
  
  XPUSHs(sv_values);
  XSRETURN(1);
}

SV*
get_elements_range(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_array = ST(0);
  SV* sv_index = ST(1);
  SV* sv_count = ST(2);
  
  // Index
  int32_t index = (int32_t)SvIV(sv_index);
  
  // Count
  int32_t count = (int32_t)SvIV(sv_count);
  
  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  // Get object
  void* array = SPVM_XS_UTIL_get_object(sv_array);
  
  // Length
  int32_t length = api->get_array_length(api, array);
  
  // Check index
  if (index < 0 || index > length - 1) {
    croak("Index is out of range(SPVM::Perl::Object::Array::Int::get_elements_range())");
  }
  
  // Check count
  if (count < 0 || index + count > length - 1) {
    croak("Index + count is out of range(SPVM::Perl::Object::Array::Int::get_elements_range())");
  }
  
  int32_t* elements = api->get_int_array_elements(api, array);
  
  AV* av_values = (AV*)sv_2mortal((SV*)newAV());
  {
    int32_t i;
    for (i = index; i < index + count; i++) {
      SV* sv_value = sv_2mortal(newSViv(elements[i]));
      av_push(av_values, SvREFCNT_inc(sv_value));
    }
  }
  SV* sv_values = sv_2mortal(newRV_inc((SV*)av_values));
  
  XPUSHs(sv_values);
  XSRETURN(1);
}

SV*
to_data(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_array = ST(0);

  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  // Get object
  void* array = SPVM_XS_UTIL_get_object(sv_array);
  
  int32_t length = api->get_array_length(api, array);
  
  int32_t* elements = api->get_int_array_elements(api, array);
  
  SV* sv_data = sv_2mortal(newSVpvn((char*)elements, length * 4));
  
  XPUSHs(sv_data);
  XSRETURN(1);
}

SV*
to_data_range(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_array = ST(0);
  SV* sv_index = ST(1);
  SV* sv_count = ST(2);
  
  // Index
  int32_t index = (int32_t)SvIV(sv_index);
  
  // Count
  int32_t count = (int32_t)SvIV(sv_count);
  
  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  // Get object
  void* array = SPVM_XS_UTIL_get_object(sv_array);
  
  // Length
  int32_t length = api->get_array_length(api, array);
  
  // Check index
  if (index < 0 || index > length - 1) {
    croak("Index is out of range(SPVM::Perl::Object::Array::Int::to_data_range())");
  }
  
  // Check count
  if (count < 0 || index + count > length - 1) {
    croak("Index + count is out of range(SPVM::Perl::Object::Array::Int::to_data_range())");
  }
  
  int32_t* elements = api->get_int_array_elements(api, array);
  
  SV* sv_data = sv_2mortal(newSVpvn((char*)(elements + index), count * 4));
  
  XPUSHs(sv_data);
  XSRETURN(1);
}

MODULE = SPVM::Perl::Object::Array::Long		PACKAGE = SPVM::Perl::Object::Array::Long

SV*
new_len(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_class = ST(0);
  (void)sv_class;
  
  SV* sv_length = ST(1);
  
  int32_t length = (int32_t)SvIV(sv_length);
  
  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  // New array
  void* array =  api->new_long_array(api, length);
  
  // Increment reference count
  api->inc_ref_count(api, array);
  
  // New sv array
  SV* sv_array = SPVM_XS_UTIL_new_sv_object(array, "SPVM::Perl::Object::Array::Long");
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
set_elements(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_array = ST(0);
  SV* sv_values = ST(1);
  AV* av_values = (AV*)SvRV(sv_values);

  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  // Get object
  void* array = SPVM_XS_UTIL_get_object(sv_array);
  
  int32_t length = api->get_array_length(api, array);
  
  int64_t* elements = api->get_long_array_elements(api, array);

  // Check range
  if (av_len(av_values) + 1 != length) {
    croak("Elements length must be same as array length(SPVM::Perl::Object::Array::Long::set_elements())");
  }
  
  {
    int32_t i;
    for (i = 0; i < length; i++) {
      SV** sv_value_ptr = av_fetch(av_values, i, 0);
      SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
      elements[i] = (int64_t)SvIV(sv_value);
    }
  }
  
  XSRETURN(0);
}

SV*
set_elements_range(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_array = ST(0);
  SV* sv_index = ST(1);
  SV* sv_count = ST(2);
  SV* sv_values = ST(3);
  
  // Index
  int32_t index = (int32_t)SvIV(sv_index);
  
  // Count
  int32_t count = (int32_t)SvIV(sv_count);
  
  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  // Get object
  void* array = SPVM_XS_UTIL_get_object(sv_array);
  
  // Length
  int32_t length = api->get_array_length(api, array);
  
  // Check index
  if (index < 0 || index > length - 1) {
    croak("Index is out of range(SPVM::Perl::Object::Array::Long::set_elements_range())");
  }
  
  // Check count
  if (count < 0 || index + count > length - 1) {
    croak("Index + count is out of range(SPVM::Perl::Object::Array::Long::set_elements_range())");
  }
  
  // Check if sv values is array reference
  if (!(SvROK(sv_values) && sv_derived_from(sv_values, "ARRAY"))) {
    croak("Values must be array refenrece(SPVM::Perl::Object::Array::Long::set_elements_range())");
  }
  
  AV* av_values = (AV*)SvRV(sv_values);
  
  // Check elements length
  if (av_len(av_values) + 1 != count) {
    croak("Elements length must be same as count argument(SPVM::Perl::Object::Array::Long::set_elements_range())");
  }
  
  // Elements
  int64_t* elements = api->get_long_array_elements(api, array);
  
  // Set element value
  {
    int32_t i;
    
    for (i = 0; i < count; i++) {
      SV** sv_value_ptr = av_fetch(av_values, i, 0);
      SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
      elements[index + i] = (int64_t)SvIV(sv_value);
    }
  }
  
  XSRETURN(0);
}

SV*
set_data(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_array = ST(0);
  SV* sv_data = ST(1);
  
  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();

  // Get object
  void* array = SPVM_XS_UTIL_get_object(sv_array);
  
  int32_t length = api->get_array_length(api, array);
  
  int64_t* elements = api->get_long_array_elements(api, array);
  
  // Check range
  if ((int32_t)sv_len(sv_data) != length * 8) {
    croak("Data total byte size must be same as array length * 8(SPVM::Perl::Object::Array::Long::set_data())");
  }
  
  if (length > 0) {
    memcpy(elements, SvPV_nolen(sv_data), length * 8);
  }
  
  XSRETURN(0);
}

SV*
set_data_range(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_array = ST(0);
  SV* sv_index = ST(1);
  SV* sv_count = ST(2);
  SV* sv_data = ST(3);
  
  // Index
  int32_t index = (int32_t)SvIV(sv_index);
  
  // Count
  int32_t count = (int32_t)SvIV(sv_count);
  
  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  // Get object
  void* array = SPVM_XS_UTIL_get_object(sv_array);
  
  // Length
  int32_t length = api->get_array_length(api, array);
  
  // Check index
  if (index < 0 || index > length - 1) {
    croak("Index is out of range(SPVM::Perl::Object::Array::Long::set_data_range())");
  }
  
  // Check count
  if (count < 0 || index + count > length - 1) {
    croak("Index + count is out of range(SPVM::Perl::Object::Array::Long::set_data_range())");
  }
  
  // Check data long size
  int32_t data_long_size = (int32_t)sv_len(sv_data);
  
  if (data_long_size != count * 8) {
    croak("Data byte size must be same as count argument * 8(SPVM::Perl::Object::Array::Long::set_data_range())");
  }
  
  // Elements
  int64_t* elements = api->get_long_array_elements(api, array);
  
  // Copy data
  if (count > 0) {
    memcpy(elements + index, SvPV_nolen(sv_data), count * 8);
  }
  
  XSRETURN(0);
}

SV*
set(...)
  PPCODE:
{
  (void)RETVAL;
  
  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  SV* sv_array = ST(0);
  SV* sv_index = ST(1);
  SV* sv_value = ST(2);
  
  // Index
  int32_t index = (int32_t)SvIV(sv_index);

  // Array
  void* array = SPVM_XS_UTIL_get_object(sv_array);
  
  // Length
  int32_t length = api->get_array_length(api, array);
  
  // Check range
  if (index < 0 || index > length - 1) {
    croak("Out of range(SPVM::Perl::Object::Array::Long::set())");
  }
  
  // Value
  int64_t value = (int64_t)SvIV(sv_value);
  
  // Set element
  int64_t* elements = api->get_long_array_elements(api, array);
  
  elements[index] = value;
  
  XSRETURN(0);
}

SV*
get(...)
  PPCODE:
{
  (void)RETVAL;
  
  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  SV* sv_array = ST(0);
  SV* sv_index = ST(1);
  
  // Index
  int32_t index = (int32_t)SvIV(sv_index);

  // Array
  void* array = SPVM_XS_UTIL_get_object(sv_array);
  
  // Length
  int32_t length = api->get_array_length(api, array);
  
  // Check range
  if (index < 0 || index > length - 1) {
    croak("Out of range(SPVM::Perl::Object::Array::Long::set())");
  }
  
  // Get element
  int64_t* elements = api->get_long_array_elements(api, array);
  int64_t value = elements[index];
  SV* sv_value = sv_2mortal(newSViv(value));
  
  XPUSHs(sv_value);
  XSRETURN(1);
}

SV*
get_elements(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_array = ST(0);

  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  // Get object
  void* array = SPVM_XS_UTIL_get_object(sv_array);
  
  int32_t length = api->get_array_length(api, array);
  
  int64_t* elements = api->get_long_array_elements(api, array);
  
  AV* av_values = (AV*)sv_2mortal((SV*)newAV());
  {
    int32_t i;
    for (i = 0; i < length; i++) {
      SV* sv_value = sv_2mortal(newSViv(elements[i]));
      av_push(av_values, SvREFCNT_inc(sv_value));
    }
  }
  SV* sv_values = sv_2mortal(newRV_inc((SV*)av_values));
  
  XPUSHs(sv_values);
  XSRETURN(1);
}

SV*
get_elements_range(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_array = ST(0);
  SV* sv_index = ST(1);
  SV* sv_count = ST(2);
  
  // Index
  int32_t index = (int32_t)SvIV(sv_index);
  
  // Count
  int32_t count = (int32_t)SvIV(sv_count);
  
  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  // Get object
  void* array = SPVM_XS_UTIL_get_object(sv_array);
  
  // Length
  int32_t length = api->get_array_length(api, array);
  
  // Check index
  if (index < 0 || index > length - 1) {
    croak("Index is out of range(SPVM::Perl::Object::Array::Long::get_elements_range())");
  }
  
  // Check count
  if (count < 0 || index + count > length - 1) {
    croak("Index + count is out of range(SPVM::Perl::Object::Array::Long::get_elements_range())");
  }
  
  int64_t* elements = api->get_long_array_elements(api, array);
  
  AV* av_values = (AV*)sv_2mortal((SV*)newAV());
  {
    int32_t i;
    for (i = index; i < index + count; i++) {
      SV* sv_value = sv_2mortal(newSViv(elements[i]));
      av_push(av_values, SvREFCNT_inc(sv_value));
    }
  }
  SV* sv_values = sv_2mortal(newRV_inc((SV*)av_values));
  
  XPUSHs(sv_values);
  XSRETURN(1);
}

SV*
to_data(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_array = ST(0);

  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  // Get object
  void* array = SPVM_XS_UTIL_get_object(sv_array);
  
  int32_t length = api->get_array_length(api, array);
  
  int64_t* elements = api->get_long_array_elements(api, array);
  
  SV* sv_data = sv_2mortal(newSVpvn((char*)elements, length * 8));
  
  XPUSHs(sv_data);
  XSRETURN(1);
}

SV*
to_data_range(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_array = ST(0);
  SV* sv_index = ST(1);
  SV* sv_count = ST(2);
  
  // Index
  int32_t index = (int32_t)SvIV(sv_index);
  
  // Count
  int32_t count = (int32_t)SvIV(sv_count);
  
  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  // Get object
  void* array = SPVM_XS_UTIL_get_object(sv_array);
  
  // Length
  int32_t length = api->get_array_length(api, array);
  
  // Check index
  if (index < 0 || index > length - 1) {
    croak("Index is out of range(SPVM::Perl::Object::Array::Long::to_data_range())");
  }
  
  // Check count
  if (count < 0 || index + count > length - 1) {
    croak("Index + count is out of range(SPVM::Perl::Object::Array::Long::to_data_range())");
  }
  
  int64_t* elements = api->get_long_array_elements(api, array);
  
  SV* sv_data = sv_2mortal(newSVpvn((char*)(elements + index), count * 8));
  
  XPUSHs(sv_data);
  XSRETURN(1);
}

MODULE = SPVM::Perl::Object::Array::Float		PACKAGE = SPVM::Perl::Object::Array::Float

SV*
new_len(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_class = ST(0);
  (void)sv_class;
  
  SV* sv_length = ST(1);
  
  int32_t length = (int32_t)SvIV(sv_length);
  
  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  // New array
  void* array =  api->new_float_array(api, length);
  
  // Increment reference count
  api->inc_ref_count(api, array);
  
  // New sv array
  SV* sv_array = SPVM_XS_UTIL_new_sv_object(array, "SPVM::Perl::Object::Array::Float");
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
set_elements(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_array = ST(0);
  SV* sv_values = ST(1);
  AV* av_values = (AV*)SvRV(sv_values);

  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  // Get object
  void* array = SPVM_XS_UTIL_get_object(sv_array);
  
  int32_t length = api->get_array_length(api, array);
  
  float* elements = api->get_float_array_elements(api, array);

  // Check range
  if (av_len(av_values) + 1 != length) {
    croak("Elements length must be same as array length(SPVM::Perl::Object::Array::Float::set_elements())");
  }
  
  {
    int32_t i;
    for (i = 0; i < length; i++) {
      SV** sv_value_ptr = av_fetch(av_values, i, 0);
      SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
      elements[i] = (float)SvNV(sv_value);
    }
  }
  
  XSRETURN(0);
}

SV*
set_elements_range(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_array = ST(0);
  SV* sv_index = ST(1);
  SV* sv_count = ST(2);
  SV* sv_values = ST(3);
  
  // Index
  int32_t index = (int32_t)SvIV(sv_index);
  
  // Count
  int32_t count = (int32_t)SvIV(sv_count);
  
  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  // Get object
  void* array = SPVM_XS_UTIL_get_object(sv_array);
  
  // Length
  int32_t length = api->get_array_length(api, array);
  
  // Check index
  if (index < 0 || index > length - 1) {
    croak("Index is out of range(SPVM::Perl::Object::Array::Float::set_elements_range())");
  }
  
  // Check count
  if (count < 0 || index + count > length - 1) {
    croak("Index + count is out of range(SPVM::Perl::Object::Array::Float::set_elements_range())");
  }
  
  // Check if sv values is array reference
  if (!(SvROK(sv_values) && sv_derived_from(sv_values, "ARRAY"))) {
    croak("Values must be array refenrece(SPVM::Perl::Object::Array::Float::set_elements_range())");
  }
  
  AV* av_values = (AV*)SvRV(sv_values);
  
  // Check elements length
  if (av_len(av_values) + 1 != count) {
    croak("Elements length must be same as count argument(SPVM::Perl::Object::Array::Float::set_elements_range())");
  }
  
  // Elements
  float* elements = api->get_float_array_elements(api, array);
  
  // Set element value
  {
    int32_t i;
    
    for (i = 0; i < count; i++) {
      SV** sv_value_ptr = av_fetch(av_values, i, 0);
      SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
      elements[index + i] = (float)SvNV(sv_value);
    }
  }
  
  XSRETURN(0);
}

SV*
set_data(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_array = ST(0);
  SV* sv_data = ST(1);
  
  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();

  // Get object
  void* array = SPVM_XS_UTIL_get_object(sv_array);
  
  int32_t length = api->get_array_length(api, array);
  
  float* elements = api->get_float_array_elements(api, array);
  
  // Check range
  if ((int32_t)sv_len(sv_data) != length * 4) {
    croak("Data total byte size must be same as array length * 4(SPVM::Perl::Object::Array::Float::set_data())");
  }
  
  if (length > 0) {
    memcpy(elements, SvPV_nolen(sv_data), length * 4);
  }
  
  XSRETURN(0);
}

SV*
set_data_range(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_array = ST(0);
  SV* sv_index = ST(1);
  SV* sv_count = ST(2);
  SV* sv_data = ST(3);
  
  // Index
  int32_t index = (int32_t)SvIV(sv_index);
  
  // Count
  int32_t count = (int32_t)SvIV(sv_count);
  
  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  // Get object
  void* array = SPVM_XS_UTIL_get_object(sv_array);
  
  // Length
  int32_t length = api->get_array_length(api, array);
  
  // Check index
  if (index < 0 || index > length - 1) {
    croak("Index is out of range(SPVM::Perl::Object::Array::Float::set_data_range())");
  }
  
  // Check count
  if (count < 0 || index + count > length - 1) {
    croak("Index + count is out of range(SPVM::Perl::Object::Array::Float::set_data_range())");
  }
  
  // Check data float size
  int32_t data_float_size = (int32_t)sv_len(sv_data);
  
  if (data_float_size != count * 4) {
    croak("Data byte size must be same as count argument * 4(SPVM::Perl::Object::Array::Float::set_data_range())");
  }
  
  // Elements
  float* elements = api->get_float_array_elements(api, array);
  
  // Copy data
  if (count > 0) {
    memcpy(elements + index, SvPV_nolen(sv_data), count * 4);
  }
  
  XSRETURN(0);
}

SV*
set(...)
  PPCODE:
{
  (void)RETVAL;
  
  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  SV* sv_array = ST(0);
  SV* sv_index = ST(1);
  SV* sv_value = ST(2);
  
  // Index
  int32_t index = (int32_t)SvIV(sv_index);

  // Array
  void* array = SPVM_XS_UTIL_get_object(sv_array);
  
  // Length
  int32_t length = api->get_array_length(api, array);
  
  // Check range
  if (index < 0 || index > length - 1) {
    croak("Out of range(SPVM::Perl::Object::Array::Float::set())");
  }
  
  // Value
  float value = (float)SvNV(sv_value);
  
  // Set element
  float* elements = api->get_float_array_elements(api, array);
  
  elements[index] = value;
  
  XSRETURN(0);
}

SV*
get(...)
  PPCODE:
{
  (void)RETVAL;
  
  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  SV* sv_array = ST(0);
  SV* sv_index = ST(1);
  
  // Index
  int32_t index = (int32_t)SvIV(sv_index);

  // Array
  void* array = SPVM_XS_UTIL_get_object(sv_array);
  
  // Length
  int32_t length = api->get_array_length(api, array);
  
  // Check range
  if (index < 0 || index > length - 1) {
    croak("Out of range(SPVM::Perl::Object::Array::Float::set())");
  }
  
  // Get element
  float* elements = api->get_float_array_elements(api, array);
  float value = elements[index];
  SV* sv_value = sv_2mortal(newSVnv(value));
  
  XPUSHs(sv_value);
  XSRETURN(1);
}

SV*
get_elements(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_array = ST(0);

  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  // Get object
  void* array = SPVM_XS_UTIL_get_object(sv_array);
  
  int32_t length = api->get_array_length(api, array);
  
  float* elements = api->get_float_array_elements(api, array);
  
  AV* av_values = (AV*)sv_2mortal((SV*)newAV());
  {
    int32_t i;
    for (i = 0; i < length; i++) {
      SV* sv_value = sv_2mortal(newSVnv((NV)elements[i]));
      av_push(av_values, SvREFCNT_inc(sv_value));
    }
  }
  SV* sv_values = sv_2mortal(newRV_inc((SV*)av_values));
  
  XPUSHs(sv_values);
  XSRETURN(1);
}

SV*
get_elements_range(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_array = ST(0);
  SV* sv_index = ST(1);
  SV* sv_count = ST(2);
  
  // Index
  int32_t index = (int32_t)SvIV(sv_index);
  
  // Count
  int32_t count = (int32_t)SvIV(sv_count);
  
  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  // Get object
  void* array = SPVM_XS_UTIL_get_object(sv_array);
  
  // Length
  int32_t length = api->get_array_length(api, array);
  
  // Check index
  if (index < 0 || index > length - 1) {
    croak("Index is out of range(SPVM::Perl::Object::Array::Float::get_elements_range())");
  }
  
  // Check count
  if (count < 0 || index + count > length - 1) {
    croak("Index + count is out of range(SPVM::Perl::Object::Array::Float::get_elements_range())");
  }
  
  float* elements = api->get_float_array_elements(api, array);
  
  AV* av_values = (AV*)sv_2mortal((SV*)newAV());
  {
    int32_t i;
    for (i = index; i < index + count; i++) {
      SV* sv_value = sv_2mortal(newSVnv(elements[i]));
      av_push(av_values, SvREFCNT_inc(sv_value));
    }
  }
  SV* sv_values = sv_2mortal(newRV_inc((SV*)av_values));
  
  XPUSHs(sv_values);
  XSRETURN(1);
}

SV*
to_data(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_array = ST(0);

  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  // Get object
  void* array = SPVM_XS_UTIL_get_object(sv_array);
  
  int32_t length = api->get_array_length(api, array);
  
  float* elements = api->get_float_array_elements(api, array);
  
  SV* sv_data = sv_2mortal(newSVpvn((char*)elements, length * 4));
  
  XPUSHs(sv_data);
  XSRETURN(1);
}

SV*
to_data_range(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_array = ST(0);
  SV* sv_index = ST(1);
  SV* sv_count = ST(2);
  
  // Index
  int32_t index = (int32_t)SvIV(sv_index);
  
  // Count
  int32_t count = (int32_t)SvIV(sv_count);
  
  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  // Get object
  void* array = SPVM_XS_UTIL_get_object(sv_array);
  
  // Length
  int32_t length = api->get_array_length(api, array);
  
  // Check index
  if (index < 0 || index > length - 1) {
    croak("Index is out of range(SPVM::Perl::Object::Array::Float::to_data_range())");
  }
  
  // Check count
  if (count < 0 || index + count > length - 1) {
    croak("Index + count is out of range(SPVM::Perl::Object::Array::Float::to_data_range())");
  }
  
  float* elements = api->get_float_array_elements(api, array);
  
  SV* sv_data = sv_2mortal(newSVpvn((char*)(elements + index), count * 4));
  
  XPUSHs(sv_data);
  XSRETURN(1);
}

MODULE = SPVM::Perl::Object::Array::Double		PACKAGE = SPVM::Perl::Object::Array::Double

SV*
new_len(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_class = ST(0);
  (void)sv_class;
  
  SV* sv_length = ST(1);
  
  int32_t length = (int32_t)SvIV(sv_length);
  
  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  // New array
  void* array =  api->new_double_array(api, length);
  
  // Increment reference count
  api->inc_ref_count(api, array);
  
  // New sv array
  SV* sv_array = SPVM_XS_UTIL_new_sv_object(array, "SPVM::Perl::Object::Array::Double");
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
set_elements(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_array = ST(0);
  SV* sv_values = ST(1);
  AV* av_values = (AV*)SvRV(sv_values);

  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  // Get object
  void* array = SPVM_XS_UTIL_get_object(sv_array);
  
  int32_t length = api->get_array_length(api, array);
  
  double* elements = api->get_double_array_elements(api, array);

  // Check range
  if (av_len(av_values) + 1 != length) {
    croak("Elements length must be same as array length(SPVM::Perl::Object::Array::Double::set_elements())");
  }
  
  {
    int32_t i;
    for (i = 0; i < length; i++) {
      SV** sv_value_ptr = av_fetch(av_values, i, 0);
      SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
      elements[i] = (double)SvNV(sv_value);
    }
  }
  
  XSRETURN(0);
}

SV*
set_elements_range(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_array = ST(0);
  SV* sv_index = ST(1);
  SV* sv_count = ST(2);
  SV* sv_values = ST(3);
  
  // Index
  int32_t index = (int32_t)SvIV(sv_index);
  
  // Count
  int32_t count = (int32_t)SvIV(sv_count);
  
  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  // Get object
  void* array = SPVM_XS_UTIL_get_object(sv_array);
  
  // Length
  int32_t length = api->get_array_length(api, array);
  
  // Check index
  if (index < 0 || index > length - 1) {
    croak("Index is out of range(SPVM::Perl::Object::Array::Double::set_elements_range())");
  }
  
  // Check count
  if (count < 0 || index + count > length - 1) {
    croak("Index + count is out of range(SPVM::Perl::Object::Array::Double::set_elements_range())");
  }
  
  // Check if sv values is array reference
  if (!(SvROK(sv_values) && sv_derived_from(sv_values, "ARRAY"))) {
    croak("Values must be array refenrece(SPVM::Perl::Object::Array::Double::set_elements_range())");
  }
  
  AV* av_values = (AV*)SvRV(sv_values);
  
  // Check elements length
  if (av_len(av_values) + 1 != count) {
    croak("Elements length must be same as count argument(SPVM::Perl::Object::Array::Double::set_elements_range())");
  }
  
  // Elements
  double* elements = api->get_double_array_elements(api, array);
  
  // Set element value
  {
    int32_t i;
    
    for (i = 0; i < count; i++) {
      SV** sv_value_ptr = av_fetch(av_values, i, 0);
      SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
      elements[index + i] = (double)SvNV(sv_value);
    }
  }
  
  XSRETURN(0);
}

SV*
set_data(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_array = ST(0);
  SV* sv_data = ST(1);
  
  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();

  // Get object
  void* array = SPVM_XS_UTIL_get_object(sv_array);
  
  int32_t length = api->get_array_length(api, array);
  
  double* elements = api->get_double_array_elements(api, array);
  
  // Check range
  if ((int32_t)sv_len(sv_data) != length * 8) {
    croak("Data total byte size must be same as array length * 8(SPVM::Perl::Object::Array::Double::set_data())");
  }
  
  if (length > 0) {
    memcpy(elements, SvPV_nolen(sv_data), length * 8);
  }
  
  XSRETURN(0);
}

SV*
set_data_range(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_array = ST(0);
  SV* sv_index = ST(1);
  SV* sv_count = ST(2);
  SV* sv_data = ST(3);
  
  // Index
  int32_t index = (int32_t)SvIV(sv_index);
  
  // Count
  int32_t count = (int32_t)SvIV(sv_count);
  
  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  // Get object
  void* array = SPVM_XS_UTIL_get_object(sv_array);
  
  // Length
  int32_t length = api->get_array_length(api, array);
  
  // Check index
  if (index < 0 || index > length - 1) {
    croak("Index is out of range(SPVM::Perl::Object::Array::Double::set_data_range())");
  }
  
  // Check count
  if (count < 0 || index + count > length - 1) {
    croak("Index + count is out of range(SPVM::Perl::Object::Array::Double::set_data_range())");
  }
  
  // Check data double size
  int32_t data_double_size = (int32_t)sv_len(sv_data);
  
  if (data_double_size != count * 8) {
    croak("Data byte size must be same as count argument * 8(SPVM::Perl::Object::Array::Double::set_data_range())");
  }
  
  // Elements
  double* elements = api->get_double_array_elements(api, array);
  
  // Copy data
  if (count > 0) {
    memcpy(elements + index, SvPV_nolen(sv_data), count * 8);
  }
  
  XSRETURN(0);
}

SV*
set(...)
  PPCODE:
{
  (void)RETVAL;
  
  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  SV* sv_array = ST(0);
  SV* sv_index = ST(1);
  SV* sv_value = ST(2);
  
  // Index
  int32_t index = (int32_t)SvIV(sv_index);

  // Array
  void* array = SPVM_XS_UTIL_get_object(sv_array);
  
  // Length
  int32_t length = api->get_array_length(api, array);
  
  // Check range
  if (index < 0 || index > length - 1) {
    croak("Out of range(SPVM::Perl::Object::Array::Double::set())");
  }
  
  // Value
  double value = (double)SvNV(sv_value);
  
  // Set element
  double* elements = api->get_double_array_elements(api, array);
  
  elements[index] = value;
  
  XSRETURN(0);
}

SV*
get(...)
  PPCODE:
{
  (void)RETVAL;
  
  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  SV* sv_array = ST(0);
  SV* sv_index = ST(1);
  
  // Index
  int32_t index = (int32_t)SvIV(sv_index);

  // Array
  void* array = SPVM_XS_UTIL_get_object(sv_array);
  
  // Length
  int32_t length = api->get_array_length(api, array);
  
  // Check range
  if (index < 0 || index > length - 1) {
    croak("Out of range(SPVM::Perl::Object::Array::Double::set())");
  }
  
  // Get element
  double* elements = api->get_double_array_elements(api, array);
  double value = elements[index];
  SV* sv_value = sv_2mortal(newSVnv(value));
  
  XPUSHs(sv_value);
  XSRETURN(1);
}

SV*
get_elements(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_array = ST(0);

  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  // Get object
  void* array = SPVM_XS_UTIL_get_object(sv_array);
  
  int32_t length = api->get_array_length(api, array);
  
  double* elements = api->get_double_array_elements(api, array);
  
  AV* av_values = (AV*)sv_2mortal((SV*)newAV());
  {
    int32_t i;
    for (i = 0; i < length; i++) {
      SV* sv_value = sv_2mortal(newSVnv((NV)elements[i]));
      av_push(av_values, SvREFCNT_inc(sv_value));
    }
  }
  SV* sv_values = sv_2mortal(newRV_inc((SV*)av_values));
  
  XPUSHs(sv_values);
  XSRETURN(1);
}

SV*
get_elements_range(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_array = ST(0);
  SV* sv_index = ST(1);
  SV* sv_count = ST(2);
  
  // Index
  int32_t index = (int32_t)SvIV(sv_index);
  
  // Count
  int32_t count = (int32_t)SvIV(sv_count);
  
  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  // Get object
  void* array = SPVM_XS_UTIL_get_object(sv_array);
  
  // Length
  int32_t length = api->get_array_length(api, array);
  
  // Check index
  if (index < 0 || index > length - 1) {
    croak("Index is out of range(SPVM::Perl::Object::Array::Double::get_elements_range())");
  }
  
  // Check count
  if (count < 0 || index + count > length - 1) {
    croak("Index + count is out of range(SPVM::Perl::Object::Array::Double::get_elements_range())");
  }
  
  double* elements = api->get_double_array_elements(api, array);
  
  AV* av_values = (AV*)sv_2mortal((SV*)newAV());
  {
    int32_t i;
    for (i = index; i < index + count; i++) {
      SV* sv_value = sv_2mortal(newSVnv(elements[i]));
      av_push(av_values, SvREFCNT_inc(sv_value));
    }
  }
  SV* sv_values = sv_2mortal(newRV_inc((SV*)av_values));
  
  XPUSHs(sv_values);
  XSRETURN(1);
}

SV*
to_data(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_array = ST(0);

  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  // Get object
  void* array = SPVM_XS_UTIL_get_object(sv_array);
  
  int32_t length = api->get_array_length(api, array);
  
  double* elements = api->get_double_array_elements(api, array);
  
  SV* sv_data = sv_2mortal(newSVpvn((char*)elements, length * 8));
  
  XPUSHs(sv_data);
  XSRETURN(1);
}

SV*
to_data_range(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_array = ST(0);
  SV* sv_index = ST(1);
  SV* sv_count = ST(2);
  
  // Index
  int32_t index = (int32_t)SvIV(sv_index);
  
  // Count
  int32_t count = (int32_t)SvIV(sv_count);
  
  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  // Get object
  void* array = SPVM_XS_UTIL_get_object(sv_array);
  
  // Length
  int32_t length = api->get_array_length(api, array);
  
  // Check index
  if (index < 0 || index > length - 1) {
    croak("Index is out of range(SPVM::Perl::Object::Array::Double::to_data_range())");
  }
  
  // Check count
  if (count < 0 || index + count > length - 1) {
    croak("Index + count is out of range(SPVM::Perl::Object::Array::Double::to_data_range())");
  }
  
  double* elements = api->get_double_array_elements(api, array);
  
  SV* sv_data = sv_2mortal(newSVpvn((char*)(elements + index), count * 8));
  
  XPUSHs(sv_data);
  XSRETURN(1);
}

MODULE = SPVM::Perl::Object::Array::Object		PACKAGE = SPVM::Perl::Object::Array::Object

SV*
new_len(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_class = ST(0);
  (void)sv_class;
  
  SV* sv_basic_type_name = ST(1);
  SV* sv_length = ST(2);
  
  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  int32_t length = (int32_t)SvIV(sv_length);

  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->get_runtime(api);
  SPVM_COMPILER* compiler = runtime->compiler;

  // Element type id
  const char* basic_type_name = SvPV_nolen(sv_basic_type_name);
  
  SPVM_BASIC_TYPE* basic_type = SPVM_HASH_search(compiler->basic_type_symtable, basic_type_name, strlen(basic_type_name));
  assert(basic_type);
  
  // New array
  void* array = api->new_object_array(api, basic_type->id, length);
  
  // Fix type name(int[] -> int[][]);
  SV* sv_type_name = sv_2mortal(newSVsv(sv_basic_type_name));
  sv_catpv(sv_type_name, "[]");
  
  // Increment reference count
  api->inc_ref_count(api, array);
  
  // New sv array
  SV* sv_array = SPVM_XS_UTIL_new_sv_object(array, "SPVM::Perl::Object::Array::Object");
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
set(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_array = ST(0);
  SV* sv_index = ST(1);
  SV* sv_object = ST(2);
  
  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  // Get array
  SPVM_OBJECT* array = SPVM_XS_UTIL_get_object(sv_array);
  
  // Runtime
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->get_runtime(api);
  SPVM_COMPILER* compiler = runtime->compiler;
  
  // Get object
  SPVM_OBJECT* object = SPVM_XS_UTIL_get_object(sv_object);
  
  // Index
  int32_t index = (int32_t)SvIV(sv_index);
  
  api->set_object_array_element(api, array, index, (void*)object);
  
  XSRETURN(0);
}

SV*
get(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_array = ST(0);
  SV* sv_index = ST(1);
  
  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  // Runtime
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->get_runtime(api);
  SPVM_COMPILER* compiler = runtime->compiler;
  
  // Get array
  SPVM_OBJECT* array = SPVM_XS_UTIL_get_object(sv_array);
  
  // Dimension
  int32_t dimension = array->dimension - 1;
  
  // Element type id
  SPVM_BASIC_TYPE* basic_type = SPVM_LIST_fetch(compiler->basic_types, array->basic_type_id);

  // Index
  int32_t index = (int32_t)SvIV(sv_index);
  void* basic_object = api->get_object_array_element(api, array, index);
  if (basic_object != NULL) {
    api->inc_ref_count(api, basic_object);
  }
  
  SV* sv_basic_object;
  if (dimension == 0) {
    SV* sv_basic_type_name = sv_2mortal(newSVpv("SPVM::", 0));
    sv_catpv(sv_basic_type_name, basic_type->name);
    
    sv_basic_object = SPVM_XS_UTIL_new_sv_object(basic_object, SvPV_nolen(sv_basic_type_name));
  }
  else if (dimension == 1) {
    switch (basic_type->id) {
      case SPVM_BASIC_TYPE_C_ID_BYTE :
        sv_basic_object = SPVM_XS_UTIL_new_sv_object(basic_object, "SPVM::Perl::Object::Array::Byte");
        break;
      case SPVM_BASIC_TYPE_C_ID_SHORT :
        sv_basic_object = SPVM_XS_UTIL_new_sv_object(basic_object, "SPVM::Perl::Object::Array::Short");
        break;
      case SPVM_BASIC_TYPE_C_ID_INT :
        sv_basic_object = SPVM_XS_UTIL_new_sv_object(basic_object, "SPVM::Perl::Object::Array::Int");
        break;
      case SPVM_BASIC_TYPE_C_ID_LONG :
        sv_basic_object = SPVM_XS_UTIL_new_sv_object(basic_object, "SPVM::Perl::Object::Array::Long");
        break;
      case SPVM_BASIC_TYPE_C_ID_FLOAT :
        sv_basic_object = SPVM_XS_UTIL_new_sv_object(basic_object, "SPVM::Perl::Object::Array::Float");
        break;
      case SPVM_BASIC_TYPE_C_ID_DOUBLE :
        sv_basic_object = SPVM_XS_UTIL_new_sv_object(basic_object, "SPVM::Perl::Object::Array::Double");
        break;
      default :
        sv_basic_object = SPVM_XS_UTIL_new_sv_object(basic_object, "SPVM::Perl::Object::Array::Object");
    }
  }
  else {
    sv_basic_object = SPVM_XS_UTIL_new_sv_object(basic_object, "SPVM::Perl::Object::Array::Object");
  }
  
  XPUSHs(sv_basic_object);
  
  XSRETURN(1);
}

MODULE = SPVM::Perl::Object::Array		PACKAGE = SPVM::Perl::Object::Array

MODULE = SPVM::Build::SPVMInfo		PACKAGE = SPVM::Build::SPVMInfo

SV*
get_sub_name(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_sub_id = ST(0);
  
  int32_t sub_id = (int32_t)SvIV(sv_sub_id);
  
  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->get_runtime(api);
  SPVM_COMPILER* compiler = runtime->compiler;
  
  SPVM_OP* op_sub = SPVM_LIST_fetch(compiler->op_subs, sub_id);
  SPVM_SUB* sub = op_sub->uv.sub;

  const char* sub_name = sub->abs_name;
  
  SV* sv_sub_name = sv_2mortal(newSVpvn(sub_name, strlen(sub_name)));
  
  XPUSHs(sv_sub_name);
  XSRETURN(1);
}

SV*
get_sub_names(...)
  PPCODE:
{
  (void)RETVAL;
  
  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->get_runtime(api);
  SPVM_COMPILER* compiler = runtime->compiler;
  
  AV* av_sub_names = (AV*)sv_2mortal((SV*)newAV());
  
  {
    int32_t sub_index;
    for (sub_index = 0; sub_index < compiler->op_subs->length; sub_index++) {
      SPVM_OP* op_sub = SPVM_LIST_fetch(compiler->op_subs, sub_index);
      SPVM_SUB* sub = op_sub->uv.sub;

      const char* sub_name = sub->abs_name;
      
      SV* sv_sub_name = sv_2mortal(newSVpvn(sub_name, strlen(sub_name)));
      av_push(av_sub_names, SvREFCNT_inc(sv_sub_name));
    }
  }
  
  SV* sv_sub_names = sv_2mortal(newRV_inc((SV*)av_sub_names));
  
  XPUSHs(sv_sub_names);
  XSRETURN(1);
}

SV*
get_subs_from_package_id(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_package_id = ST(0);
  int32_t package_id = SvIV(sv_package_id);
  
  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->get_runtime(api);
  SPVM_COMPILER* compiler = runtime->compiler;

  SPVM_OP* op_package = SPVM_LIST_fetch(compiler->op_packages, package_id);
  SPVM_PACKAGE* package = op_package->uv.package;
  
  AV* av_subs = (AV*)sv_2mortal((SV*)newAV());
  {
    int32_t sub_index;
    for (sub_index = 0; sub_index < package->op_subs->length; sub_index++) {
      
      SPVM_OP* op_sub = SPVM_LIST_fetch(package->op_subs, sub_index);
      SPVM_SUB* sub = op_sub->uv.sub;
      
      // Subroutine name
      const char* sub_name = sub->abs_name;
      SV* sv_sub_name = sv_2mortal(newSVpvn(sub_name, strlen(sub_name)));
      
      // Subroutine id
      int32_t sub_id = sub->id;
      SV* sv_sub_id = sv_2mortal(newSViv(sub_id));

      // Subroutine is_enum
      int32_t sub_is_enum = sub->is_enum;
      SV* sv_sub_is_enum = sv_2mortal(newSViv(sub_is_enum));

      // Subroutine is_native
      int32_t sub_is_native = sub->is_native;
      SV* sv_sub_is_native = sv_2mortal(newSViv(sub_is_native));

      // Subroutine
      HV* hv_sub = (HV*)sv_2mortal((SV*)newHV());
      
      hv_store(hv_sub, "name", strlen("name"), SvREFCNT_inc(sv_sub_name), 0);
      hv_store(hv_sub, "id", strlen("id"), SvREFCNT_inc(sv_sub_id), 0);
      hv_store(hv_sub, "is_enum", strlen("is_enum"), SvREFCNT_inc(sv_sub_is_enum), 0);
      hv_store(hv_sub, "is_native", strlen("is_native"), SvREFCNT_inc(sv_sub_is_native), 0);
      
      SV* sv_sub = sv_2mortal(newRV_inc((SV*)hv_sub));
      av_push(av_subs, SvREFCNT_inc((SV*)sv_sub));
    }
  }
  
  SV* sv_subs = sv_2mortal(newRV_inc((SV*)av_subs));
  
  XPUSHs(sv_subs);
  XSRETURN(1);
}

SV*
get_packages(...)
  PPCODE:
{
  (void)RETVAL;
  
  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->get_runtime(api);
  SPVM_COMPILER* compiler = runtime->compiler;
  
  AV* av_packages = (AV*)sv_2mortal((SV*)newAV());
  
  {
    int32_t package_index;
    for (package_index = 0; package_index < compiler->op_packages->length; package_index++) {
  
      SPVM_OP* op_package = SPVM_LIST_fetch(compiler->op_packages, package_index);
      SPVM_PACKAGE* package = op_package->uv.package;
      
      // Package name
      const char* package_name = package->op_name->uv.name;
      SV* sv_package_name = sv_2mortal(newSVpvn(package_name, strlen(package_name)));
      
      // Package id
      int32_t package_id = package->id;
      SV* sv_package_id = sv_2mortal(newSViv(package_id));

      // Is JIT
      int32_t package_is_jit = package->is_jit;
      SV* sv_package_is_jit = sv_2mortal(newSViv(package_is_jit));

      // Is interface
      int32_t package_is_interface = package->is_interface;
      SV* sv_package_is_interface = sv_2mortal(newSViv(package_is_interface));
      
      // Package
      HV* hv_package = (HV*)sv_2mortal((SV*)newHV());
      
      hv_store(hv_package, "name", strlen("name"), SvREFCNT_inc(sv_package_name), 0);
      hv_store(hv_package, "id", strlen("id"), SvREFCNT_inc(sv_package_id), 0);
      hv_store(hv_package, "is_jit", strlen("is_jit"), SvREFCNT_inc(sv_package_is_jit), 0);
      hv_store(hv_package, "is_interface", strlen("is_interface"), SvREFCNT_inc(sv_package_is_interface), 0);
      
      SV* sv_package = sv_2mortal(newRV_inc((SV*)hv_package));
      av_push(av_packages, SvREFCNT_inc((SV*)sv_package));
    }
  }
  
  SV* sv_packages = sv_2mortal(newRV_inc((SV*)av_packages));
  
  XPUSHs(sv_packages);
  XSRETURN(1);
}

SV*
get_native_sub_names(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  
  // Get compiler
  SPVM_COMPILER* compiler = INT2PTR(SPVM_COMPILER*, SvIV(SvRV(get_sv("SPVM::COMPILER", 0))));
  
  SPVM_LIST* op_subs = compiler->op_subs;
  
  AV* av_sub_names = (AV*)sv_2mortal((SV*)newAV());
  {
    int32_t sub_index;
    for (sub_index = 0; sub_index < op_subs->length; sub_index++) {
      SPVM_OP* op_sub = SPVM_LIST_fetch(op_subs, sub_index);
      SPVM_SUB* sub = op_sub->uv.sub;
      
      if (sub->is_native) {
        const char* sub_name = sub->abs_name;
        SV* sv_sub_name = sv_2mortal(newSVpvn(sub_name, strlen(sub_name)));
        av_push(av_sub_names, SvREFCNT_inc(sv_sub_name));
      }
    }
  }
  
  SV* sv_sub_names = sv_2mortal(newRV_inc((SV*)av_sub_names));
  
  XPUSHs(sv_sub_names);
  XSRETURN(1);
}

SV*
get_package_load_path(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_package_name = ST(0);
  
  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();

  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->get_runtime(api);
  SPVM_COMPILER* compiler = runtime->compiler;


  const char* package_name = SvPV_nolen(sv_package_name);
  

  // Subroutine information
  SPVM_OP* op_package = SPVM_HASH_search(compiler->op_package_symtable, package_name, strlen(package_name));;
  SPVM_PACKAGE* package = op_package->uv.package;
  
  const char* package_load_path = package->load_path;
  
  SV* sv_package_load_path = sv_2mortal(newSVpvn(package_load_path, strlen(package_load_path)));
  
  XPUSHs(sv_package_load_path);
  
  XSRETURN(1);
}

MODULE = SPVM::Build		PACKAGE = SPVM::Build

SV*
compile(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  
  // Create compiler
  SPVM_COMPILER* compiler = SPVM_COMPILER_new();
  
  // Add package
  AV* av_package_infos = get_av("SPVM::PACKAGE_INFOS", 0);
  int32_t av_package_infos_length = (int32_t)av_len(av_package_infos) + 1;
  {
    int32_t i;
    for (i = 0; i < av_package_infos_length; i++) {
      SV** sv_package_info_ptr = av_fetch(av_package_infos, i, 0);
      SV* sv_package_info = sv_package_info_ptr ? *sv_package_info_ptr : &PL_sv_undef;
      HV* hv_package_info = (HV*)SvRV(sv_package_info);
      
      // Name
      SV** sv_name_ptr = hv_fetch(hv_package_info, "name", strlen("name"), 0);
      SV* sv_name = sv_name_ptr ? *sv_name_ptr : &PL_sv_undef;
      const char* name = SvPV_nolen(sv_name);
      
      // File
      SV** sv_file_ptr = hv_fetch(hv_package_info, "file", strlen("file"), 0);
      SV* sv_file = sv_file_ptr ? *sv_file_ptr : &PL_sv_undef;
      const char* file = SvPV_nolen(sv_file);
      
      // Line
      SV** sv_line_ptr = hv_fetch(hv_package_info, "line", strlen("line"), 0);
      SV* sv_line = sv_line_ptr ? *sv_line_ptr : &PL_sv_undef;
      int32_t line = (int32_t)SvIV(sv_line);
      
      // push package to compiler use stack
      SPVM_OP* op_name_package = SPVM_OP_new_op_name(compiler, name, file, line);
      SPVM_OP* op_type_package = SPVM_OP_build_basic_type(compiler, op_name_package);
      SPVM_OP* op_use_package = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_USE, file, line);
      SPVM_OP_build_use(compiler, op_use_package, op_type_package);
      SPVM_LIST_push(compiler->op_use_stack, op_use_package);
    }
  }
  
  // Add include paths
  AV* av_include_paths = get_av("main::INC", 0);;
  int32_t av_include_paths_length = (int32_t)av_len(av_include_paths) + 1;
  {
    int32_t i;
    for (i = 0; i < av_include_paths_length; i++) {
      SV** sv_include_path_ptr = av_fetch(av_include_paths, i, 0);
      SV* sv_include_path = sv_include_path_ptr ? *sv_include_path_ptr : &PL_sv_undef;
      char* include_path = SvPV_nolen(sv_include_path);
      SPVM_LIST_push(compiler->module_include_pathes, include_path);
    }
  }

  // Add package
  AV* av_jit_package_names = get_av("SPVM::JIT_PACKAGE_NAMES", 0);
  int32_t av_jit_package_names_length = (int32_t)av_len(av_jit_package_names) + 1;
  {
    int32_t i;
    for (i = 0; i < av_jit_package_names_length; i++) {
      SV** sv_jit_package_name_ptr = av_fetch(av_jit_package_names, i, 0);
      SV* sv_jit_package_name = sv_jit_package_name_ptr ? *sv_jit_package_name_ptr : &PL_sv_undef;
      
      char* jit_package_name = SvPV_nolen(sv_jit_package_name);
      
      SPVM_LIST_push(compiler->jit_package_names, jit_package_name);
      SPVM_HASH_insert(compiler->jit_package_name_symtable, jit_package_name, strlen(jit_package_name), (void*)(intptr_t)1);
    }
  }
  
  // Set compiler
  size_t iv_compiler = PTR2IV(compiler);
  SV* sviv_compiler = sv_2mortal(newSViv(iv_compiler));
  SV* sv_compiler = sv_2mortal(newRV_inc(sviv_compiler));
  sv_setsv(get_sv("SPVM::COMPILER", 0), sv_compiler);

  // Compile SPVM
  SPVM_COMPILER_compile(compiler);
  SV* sv_compile_success;
  
  if (compiler->error_count > 0) {
    sv_compile_success = sv_2mortal(newSViv(0));
  }
  else {
    sv_compile_success = sv_2mortal(newSViv(1));
  }
  
  XPUSHs(sv_compile_success);
  
  XSRETURN(1);
}

SV*
build_opcode(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);

  // Get compiler
  SPVM_COMPILER* compiler = INT2PTR(SPVM_COMPILER*, SvIV(SvRV(get_sv("SPVM::COMPILER", 0))));
  
  // Build opcode
  SPVM_OPCODE_BUILDER_build_opcode_array(compiler);
  
  XSRETURN(0);
}

SV*
bind_native_sub(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  SV* sv_native_sub_name = ST(1);
  SV* sv_native_address = ST(2);
  
  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();

  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->get_runtime(api);
  SPVM_COMPILER* compiler = runtime->compiler;
  
  
  // Native subroutine name
  const char* native_sub_name = SvPV_nolen(sv_native_sub_name);
  
  // Native address
  void* native_address = INT2PTR(void*, SvIV(sv_native_address));
  
  // Set native address to subroutine
  SPVM_OP* op_sub = SPVM_HASH_search(compiler->op_sub_symtable, native_sub_name, strlen(native_sub_name));
  SPVM_SUB* sub = op_sub->uv.sub;
  
  sub->native_address = native_address;
  
  XSRETURN(0);
}

SV*
build_runtime(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  
  // Get compiler
  SPVM_COMPILER* compiler = INT2PTR(SPVM_COMPILER*, SvIV(SvRV(get_sv("SPVM::COMPILER", 0))));
  
  // Create run-time
  SPVM_RUNTIME* runtime = SPVM_COMPILER_new_runtime(compiler);
  
  // Set API
  SPVM_ENV* api = runtime->api;
  size_t iv_api = PTR2IV(api);
  SV* sviv_api = sv_2mortal(newSViv(iv_api));
  SV* sv_api = sv_2mortal(newRV_inc(sviv_api));
  sv_setsv(get_sv("SPVM::API", 0), sv_api);
  
  XSRETURN(0);
}

SV*
free_compiler(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  
  // Get compiler
  SPVM_COMPILER* compiler = INT2PTR(SPVM_COMPILER*, SvIV(SvRV(get_sv("SPVM::COMPILER", 0))));
  
  // Free compiler
  SPVM_COMPILER_free(compiler);
  
  // Set undef to compiler
  sv_setsv(get_sv("SPVM::COMPILER", 0), &PL_sv_undef);
  
  XSRETURN(0);
}

MODULE = SPVM::Build::JIT		PACKAGE = SPVM::Build::JIT

SV*
build_jitcode(...)
  PPCODE:
{
  SV* sv_self = ST(0);
  SV* sv_sub_id = ST(1);
  int32_t sub_id = SvIV(sv_sub_id);
  
  // String buffer for jitcode
  SPVM_STRING_BUFFER* string_buffer = SPVM_STRING_BUFFER_new(0);
  
  // Build sub jitcode
  SPVM_JITCODE_BUILDER_build_sub_jitcode(string_buffer, sub_id);
  
  SV* sv_jitcode_source = sv_2mortal(newSVpv(string_buffer->buffer, string_buffer->length));
  
  SPVM_STRING_BUFFER_free(string_buffer);
  
  XPUSHs(sv_jitcode_source);
  XSRETURN(1);
}

SV*
bind_jitcode_sub(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  SV* sv_sub_abs_name = ST(1);
  SV* sv_sub_native_address = ST(2);
  
  const char* sub_abs_name = SvPV_nolen(sv_sub_abs_name);
  void* sub_jit_address = INT2PTR(void*, SvIV(sv_sub_native_address));
  
  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  
  int32_t sub_id = api->get_sub_id(api, sub_abs_name);

  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->get_runtime(api);
  SPVM_COMPILER* compiler = runtime->compiler;
  
  // Subroutine information
  SPVM_OP* op_sub = SPVM_LIST_fetch(compiler->op_subs, sub_id);
  SPVM_SUB* sub = op_sub->uv.sub;
  
  sub->jit_address = sub_jit_address;
  sub->is_jit_compiled = 1;
  
  XSRETURN(0);
}

MODULE = SPVM		PACKAGE = SPVM

SV*
get_objects_count(...)
  PPCODE:
{
  (void)RETVAL;
  
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();
  int32_t objects_count = api->get_objects_count(api);
  SV* sv_objects_count = sv_2mortal(newSViv(objects_count));
  
  XPUSHs(sv_objects_count);
  XSRETURN(1);
}

SV*
call_sub(...)
  PPCODE:
{
  (void)RETVAL;

  int32_t stack_arg_start = 0;
  
  SV* sv_sub_abs_name = ST(0);
  stack_arg_start++;
  
  // API
  SPVM_ENV* api = SPVM_XS_UTIL_get_api();

  const char* sub_abs_name = SvPV_nolen(sv_sub_abs_name);
  int32_t sub_id = api->get_sub_id(api, sub_abs_name);
  
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->get_runtime(api);
  SPVM_COMPILER* compiler = runtime->compiler;
  
  // Subroutine information
  SPVM_OP* op_sub = SPVM_LIST_fetch(compiler->op_subs, sub_id);
  SPVM_SUB* sub = op_sub->uv.sub;
  
  
  // Arguments
  {
    // If class method, first argument is ignored
    if (sub->call_type_id == SPVM_SUB_C_CALL_TYPE_ID_CLASS_METHOD) {
      stack_arg_start++;
    }
    
    int32_t arg_index;
    // Check argument count
    if (items - stack_arg_start != sub->op_args->length) {
      croak("Argument count is defferent");
    }
    
    for (arg_index = 0; arg_index < sub->op_args->length; arg_index++) {
      SV* sv_value = ST(arg_index + stack_arg_start);
      
      SPVM_OP* op_arg = SPVM_LIST_fetch(sub->op_args, arg_index);
      SPVM_TYPE* arg_type = op_arg->uv.my->op_type->uv.type;
      
      int32_t arg_basic_type_id = arg_type->basic_type->id;
      int32_t arg_type_dimension = arg_type->dimension;
      
      if (arg_type_dimension == 0 && arg_type->basic_type->id >= SPVM_BASIC_TYPE_C_ID_BYTE && arg_type->basic_type->id <= SPVM_BASIC_TYPE_C_ID_DOUBLE) {
        switch (arg_type->basic_type->id) {
          case SPVM_BASIC_TYPE_C_ID_BYTE : {
            int8_t value = (int8_t)SvIV(sv_value);
            call_sub_args[arg_index].bval = value;
            break;
          }
          case  SPVM_BASIC_TYPE_C_ID_SHORT : {
            int16_t value = (int16_t)SvIV(sv_value);
            call_sub_args[arg_index].sval = value;
            break;
          }
          case  SPVM_BASIC_TYPE_C_ID_INT : {
            int32_t value = (int32_t)SvIV(sv_value);
            call_sub_args[arg_index].ival = value;
            break;
          }
          case  SPVM_BASIC_TYPE_C_ID_LONG : {
            int64_t value = (int64_t)SvIV(sv_value);
            call_sub_args[arg_index].lval = value;
            break;
          }
          case  SPVM_BASIC_TYPE_C_ID_FLOAT : {
            float value = (float)SvNV(sv_value);
            call_sub_args[arg_index].fval = value;
            break;
          }
          case  SPVM_BASIC_TYPE_C_ID_DOUBLE : {
            double value = (double)SvNV(sv_value);
            call_sub_args[arg_index].dval = value;
            break;
          }
        }
      }
      else {
        if (!SvOK(sv_value)) {
          call_sub_args[arg_index].oval = NULL;
        }
        else {
          if (sv_isobject(sv_value)) {
            SV* sv_basic_object = sv_value;
            if (sv_derived_from(sv_basic_object, "SPVM::Perl::Object")) {
              
              SPVM_OBJECT* basic_object = SPVM_XS_UTIL_get_object(sv_basic_object);
              
              if (!(basic_object->basic_type_id == arg_type->basic_type->id && basic_object->dimension == arg_type->dimension)) {
                SPVM_TYPE* basic_object_type = SPVM_LIST_fetch(compiler->basic_types, basic_object->basic_type_id);
                SV* sv_arg_type_name = SPVM_XS_UTIL_create_sv_type_name(arg_type->basic_type->id, arg_type->dimension);
                SV* sv_basic_object_type = SPVM_XS_UTIL_create_sv_type_name(basic_object_type->basic_type->id, basic_object_type->dimension);
                
                croak("Argument basic_object type need %s, but %s", SvPV_nolen(sv_arg_type_name), SvPV_nolen(sv_basic_object_type));
              }
              
              call_sub_args[arg_index].oval = basic_object;
            }
            else {
              croak("Object must be derived from SPVM::Perl::Object");
            }
          }
          else {
            croak("Argument must be numeric value or SPVM::Perl::Object subclass");
          }
        }
      }
    }
  }
  
  // Return type id
  SPVM_TYPE* return_type = sub->op_return_type->uv.type;

  int32_t return_basic_type_id = return_type->basic_type->id;
  int32_t return_type_dimension = return_type->dimension;
  
  PUSHMARK(SP);
          
  // Return count
  SV* sv_return_value = NULL;
  if (return_type_dimension == 0 && return_basic_type_id <= SPVM_BASIC_TYPE_C_ID_DOUBLE) {
    switch (return_basic_type_id) {
      case SPVM_BASIC_TYPE_C_ID_VOID:  {
        api->call_void_sub(api, sub_id, call_sub_args);
        break;
      }
      case SPVM_BASIC_TYPE_C_ID_BYTE: {
        int8_t return_value = api->call_byte_sub(api, sub_id, call_sub_args);
        sv_return_value = sv_2mortal(newSViv(return_value));
        break;
      }
      case SPVM_BASIC_TYPE_C_ID_SHORT: {
        int16_t return_value = api->call_short_sub(api, sub_id, call_sub_args);
        sv_return_value = sv_2mortal(newSViv(return_value));
        break;
      }
      case SPVM_BASIC_TYPE_C_ID_INT: {
        int32_t return_value = api->call_int_sub(api, sub_id, call_sub_args);
        sv_return_value = sv_2mortal(newSViv(return_value));
        break;
      }
      case SPVM_BASIC_TYPE_C_ID_LONG: {
        int64_t return_value = api->call_long_sub(api, sub_id, call_sub_args);
        sv_return_value = sv_2mortal(newSViv(return_value));
        break;
      }
      case SPVM_BASIC_TYPE_C_ID_FLOAT: {
        float return_value = api->call_float_sub(api, sub_id, call_sub_args);
        sv_return_value = sv_2mortal(newSVnv(return_value));
        break;
      }
      case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
        double return_value = api->call_double_sub(api, sub_id, call_sub_args);
        sv_return_value = sv_2mortal(newSVnv(return_value));
        break;
      }
      default:
        assert(0);
    }
  }
  else {
    void* return_value = api->call_object_sub(api, sub_id, call_sub_args);
    sv_return_value = NULL;
    if (return_value != NULL) {
      api->inc_ref_count(api, return_value);
      
      if (return_type_dimension == 1) {
        switch(return_basic_type_id) {
          case SPVM_BASIC_TYPE_C_ID_BYTE :
            sv_return_value = SPVM_XS_UTIL_new_sv_object(return_value, "SPVM::Perl::Object::Array::Byte");
            break;
          case SPVM_BASIC_TYPE_C_ID_SHORT :
            sv_return_value = SPVM_XS_UTIL_new_sv_object(return_value, "SPVM::Perl::Object::Array::Short");
            break;
          case SPVM_BASIC_TYPE_C_ID_INT :
            sv_return_value = SPVM_XS_UTIL_new_sv_object(return_value, "SPVM::Perl::Object::Array::Int");
            break;
          case SPVM_BASIC_TYPE_C_ID_LONG :
            sv_return_value = SPVM_XS_UTIL_new_sv_object(return_value, "SPVM::Perl::Object::Array::Long");
            break;
          case SPVM_BASIC_TYPE_C_ID_FLOAT :
            sv_return_value = SPVM_XS_UTIL_new_sv_object(return_value, "SPVM::Perl::Object::Array::Float");
            break;
          case SPVM_BASIC_TYPE_C_ID_DOUBLE :
            sv_return_value = SPVM_XS_UTIL_new_sv_object(return_value, "SPVM::Perl::Object::Array::Double");
            break;        
        }
      }
      else {
        if (return_type->dimension > 0) {
          sv_return_value = SPVM_XS_UTIL_new_sv_object(return_value, "SPVM::Perl::Object::Array::Object");
        }
        else {
          SV* sv_return_type_name = SPVM_XS_UTIL_create_sv_type_name(return_type->basic_type->id, return_type->dimension);
          
          sv_return_value = SPVM_XS_UTIL_new_sv_object(return_value, SvPV_nolen(sv_return_type_name));
        }
      }
    }
    else {
      sv_return_value = &PL_sv_undef;
    }
  }
  SPAGAIN;
  ax = (SP - PL_stack_base) + 1;
  
  void* exception = api->get_exception(api);
  if (exception) {
    int32_t length = api->get_array_length(api, exception);
    int8_t* exception_bytes = api->get_byte_array_elements(api, exception);
    SV* sv_exception = sv_2mortal(newSVpvn((char*)exception_bytes, length));
    croak("%s", SvPV_nolen(sv_exception));
  }
  
  int32_t return_count;
  if (return_type_dimension == 0 && return_basic_type_id == SPVM_BASIC_TYPE_C_ID_VOID) {
    return_count = 0;
  }
  else {
    XPUSHs(sv_return_value);
    return_count = 1;
  }
  
  XSRETURN(return_count);
}
