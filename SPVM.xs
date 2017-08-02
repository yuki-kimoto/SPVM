#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"

#include "ppport.h"

#include <stdint.h>
#include <assert.h>

#include "spvm_compiler.h"
#include "spvm_hash.h"
#include "spvm_dynamic_array.h"
#include "spvm_util_allocator.h"
#include "spvm_constant_pool.h"
#include "spvm_bytecode_array.h"
#include "spvm_runtime.h"
#include "spvm_op.h"
#include "spvm_sub.h"
#include "spvm_package.h"
#include "spvm_sub.h"
#include "spvm_my_var.h"
#include "spvm_type.h"
#include "spvm_field.h"

#include "spvm_api.h"
#include "spvm_xs_util.h"

static SPVM_API_VALUE call_sub_args[255];

SPVM_COMPILER* SPVM_XS_INTERNAL_UTIL_get_compiler() {

  // Get compiler
  SV* sv_compiler = get_sv("SPVM::COMPILER", 0);
  SV* sviv_compiler = SvROK(sv_compiler) ? SvRV(sv_compiler) : sv_compiler;
  size_t iv_compiler = SvIV(sviv_compiler);
  SPVM_COMPILER* compiler = INT2PTR(SPVM_COMPILER*, iv_compiler);
  
  return compiler;
}

MODULE = SPVM::BaseObject		PACKAGE = SPVM::BaseObject

SV*
DESTROY(...)
  PPCODE:
{
  SV* sv_object = ST(0);
  
  assert(SvOK(sv_object));
  
  // warn("DESTROY");
  
  // Set API
  SPVM_API* api = SPVM_XS_UTIL_get_api();
  
  // Get content
  SPVM_API_OBJECT* object = SPVM_XS_UTIL_get_object(sv_object);
  
  assert(api->get_ref_count(api, object));
  
  // Decrement reference count
  api->dec_ref_count(api, object);
  
  XSRETURN(0);
}

MODULE = SPVM::Object		PACKAGE = SPVM::Object

SV*
new_object(...)
  PPCODE:
{
  SV* sv_class = ST(0);
  SV* sv_package = ST(1);
  
  if (!SvOK(sv_package)) {
    croak("Type must be specified(SPVM::Object::new_object)");
  }
  
  const char* package = SvPV_nolen(sv_package);

  int32_t package_id = SPVM_XS_UTIL_get_package_id(package);
  if (package_id == SPVM_API_ERROR_NO_ID) {
    croak("Unkown package \"%s\"(SPVM::Object::new_object", package);
  }
  
  // Set API
  SPVM_API* api = SPVM_XS_UTIL_get_api();
  
  // Malloc array
  SPVM_API_OBJECT* object =  api->new_object(api, package_id);
  
  // Increment
  api->inc_ref_count(api, object);

  // New sv object
  SV* sv_object = SPVM_XS_UTIL_new_sv_object(package, object);
  
  XPUSHs(sv_object);
  XSRETURN(1);
}

SV*
set(...)
  PPCODE:
{
  SV* sv_object = ST(0);
  SV* sv_field_name = ST(1);
  SV* sv_value = ST(2);
  
  // Set API
  SPVM_API* api = SPVM_XS_UTIL_get_api();
  
  // Get content
  SPVM_API_OBJECT* object = SPVM_XS_UTIL_get_object(sv_object);

  // Package name
  const char* package_name = SPVM_XS_UTIL_get_type(sv_object);
  
  // Field type
  const char* field_name = SvPV_nolen(sv_field_name);
  const char* field_type = SPVM_XS_UTIL_get_field_type(package_name, field_name);

  // Field id
  int32_t field_id = api->get_field_id(api, object, field_name);
  if (field_id == SPVM_API_ERROR_NO_ID) {
    croak("Can't find %s \"%s\" field(SPVM::Object::set)", package_name, field_name);
  }
  
  assert(field_type);
  
  int32_t field_type_length = strlen(field_type);
  if (strEQ(field_type, "byte")) {
    int8_t value = (int8_t)SvIV(sv_value);
    api->set_byte_field(api, object, field_id, value);
  }
  else if (strEQ(field_type, "short")) {
    int16_t value = (int16_t)SvIV(sv_value);
    api->set_short_field(api, object, field_id, value);
  }
  else if (strEQ(field_type, "int")) {
    int32_t value = (int32_t)SvIV(sv_value);
    api->set_int_field(api, object, field_id, value);
  }
  else if (strEQ(field_type, "long")) {
    int64_t value = (int64_t)SvIV(sv_value);
    api->set_long_field(api, object, field_id, value);
  }
  else if (strEQ(field_type, "float")) {
    float value = (float)SvNV(sv_value);
    api->set_float_field(api, object, field_id, value);
  }
  else if (strEQ(field_type, "double")) {
    double value = (double)SvNV(sv_value);
    api->set_double_field(api, object, field_id, value);
  }
  else {
    if (!(sv_isobject(sv_value) && sv_derived_from(sv_value, "SPVM::BaseObject"))) {
      croak("Can't set numeric value to \"%s\" field", field_type);
    }
    const char* value_type = SPVM_XS_UTIL_get_type(sv_value);
    if (!strEQ(field_type, value_type)) {
      croak("Can't set \"%s\" value to \"%s\" field", value_type, field_type);
    }
    
    SPVM_API_ARRAY* array = SPVM_XS_UTIL_get_array(sv_value);
    
    api->set_object_field(api, object, field_id, array);
  }
  
  XSRETURN(0);
}

SV*
get(...)
  PPCODE:
{
  SV* sv_object = ST(0);
  SV* sv_field_name = ST(1);
  
  // Set API
  SPVM_API* api = SPVM_XS_UTIL_get_api();
  
  // Get content
  SPVM_API_OBJECT* object = SPVM_XS_UTIL_get_object(sv_object);

  // Package name
  const char* package_name = SPVM_XS_UTIL_get_type(sv_object);
  
  // Field type
  const char* field_name = SvPV_nolen(sv_field_name);
  const char* field_type = SPVM_XS_UTIL_get_field_type(package_name, field_name);
  
  // Field id
  int32_t field_id = api->get_field_id(api, object, field_name);
  if (field_id == SPVM_API_ERROR_NO_ID) {
    croak("Can't find %s \"%s\" field(SPVM::Object::set)", package_name, field_name);
  }
  
  if (strEQ(field_type, "byte")) {
    int8_t value = api->get_byte_field(api, object, field_id);
    SV* sv_value = sv_2mortal(newSViv(value));
    XPUSHs(sv_value);
  }
  else if (strEQ(field_type, "short")) {
    int16_t value = api->get_short_field(api, object, field_id);
    SV* sv_value = sv_2mortal(newSViv(value));
    XPUSHs(sv_value);
  }
  else if (strEQ(field_type, "int")) {
    int32_t value = api->get_int_field(api, object, field_id);
    SV* sv_value = sv_2mortal(newSViv(value));
    XPUSHs(sv_value);
  }
  else if (strEQ(field_type, "long")) {
    int64_t value = api->get_long_field(api, object, field_id);
    SV* sv_value = sv_2mortal(newSViv(value));
    XPUSHs(sv_value);
  }
  else if (strEQ(field_type, "float")) {
    float value = api->get_float_field(api, object, field_id);
    SV* sv_value = sv_2mortal(newSVnv(value));
    XPUSHs(sv_value);
  }
  else if (strEQ(field_type, "double")) {
    double value = api->get_double_field(api, object, field_id);
    SV* sv_value = sv_2mortal(newSVnv(value));
    XPUSHs(sv_value);
  }
  else {
    SPVM_API_BASE_OBJECT* value = api->get_object_field(api, object, field_id);

    if (value != NULL) {
      api->inc_ref_count(api, value);
    }
    
    int32_t field_type_length = strlen(field_type);
    if (strcmp(field_type, "byte[]") == 0) {
      SV* sv_array = SPVM_XS_UTIL_new_sv_byte_array((SPVM_API_ARRAY*)value);
      XPUSHs(sv_array);
    }
    else if (strcmp(field_type, "short[]") == 0) {
      SV* sv_array = SPVM_XS_UTIL_new_sv_short_array((SPVM_API_ARRAY*)value);
      XPUSHs(sv_array);
    }
    else if (strcmp(field_type, "int[]") == 0) {
      SV* sv_array = SPVM_XS_UTIL_new_sv_int_array((SPVM_API_ARRAY*)value);
      XPUSHs(sv_array);
    }
    else if (strcmp(field_type, "long[]") == 0) {
      SV* sv_array = SPVM_XS_UTIL_new_sv_long_array((SPVM_API_ARRAY*)value);
      XPUSHs(sv_array);
    }
    else if (strcmp(field_type, "float[]") == 0) {
      SV* sv_array = SPVM_XS_UTIL_new_sv_float_array((SPVM_API_ARRAY*)value);
      XPUSHs(sv_array);
    }
    else if (strcmp(field_type, "double[]") == 0) {
      SV* sv_array = SPVM_XS_UTIL_new_sv_double_array((SPVM_API_ARRAY*)value);
      XPUSHs(sv_array);
    }
    else if (strcmp(field_type, "string") == 0) {
      SV* sv_array = SPVM_XS_UTIL_new_sv_string((SPVM_API_ARRAY*)value);
      XPUSHs(sv_array);
    }
    else if (field_type[field_type_length - 1] == ']') {
      SV* sv_array = SPVM_XS_UTIL_new_sv_object_array(field_type, (SPVM_API_ARRAY*)value);
      XPUSHs(sv_array);
    }
    else {
      SV* sv_object = SPVM_XS_UTIL_new_sv_object(field_type, (SPVM_API_OBJECT*)value);
      XPUSHs(sv_object);
    }
  }
  
  XSRETURN(1);
}

MODULE = SPVM::Array::Byte		PACKAGE = SPVM::Array::Byte

SV*
new(...)
  PPCODE:
{
  SV* sv_class = ST(0);
  SV* sv_length = ST(1);
  
  int32_t length = (int32_t)SvIV(sv_length);
  
  // Set API
  SPVM_API* api = SPVM_XS_UTIL_get_api();
  
  // Malloc array
  SPVM_API_ARRAY* array =  api->new_byte_array(api, length);
  
  // Increment reference count
  api->inc_ref_count(api, array);
  
  // New sv array
  SV* sv_byte_array = SPVM_XS_UTIL_new_sv_byte_array(array);
  
  XPUSHs(sv_byte_array);
  XSRETURN(1);
}

SV*
set_elements(...)
  PPCODE:
{
  SV* sv_array = ST(0);
  SV* sv_nums = ST(1);
  AV* av_nums = SvRV(sv_nums);

  // Set API
  SPVM_API* api = SPVM_XS_UTIL_get_api();
  
  // Get content
  SPVM_API_ARRAY* array = SPVM_XS_UTIL_get_array(sv_array);
  
  int32_t length = api->get_array_length(api, array);
  
  int8_t* elements = api->get_byte_array_elements(api, array);
  
  {
    int32_t i;
    for (i = 0; i < length; i++) {
      SV** sv_num_ptr = av_fetch(av_nums, i, 0);
      SV* sv_num = sv_num_ptr ? *sv_num_ptr : &PL_sv_undef;
      elements[i] = (int8_t)SvIV(sv_num);
    }
  }
  
  XSRETURN(0);
}

SV*
get_elements(...)
  PPCODE:
{
  SV* sv_array = ST(0);

  // Set API
  SPVM_API* api = SPVM_XS_UTIL_get_api();
  
  // Get content
  SPVM_API_ARRAY* array = SPVM_XS_UTIL_get_array(sv_array);
  
  int32_t length = api->get_array_length(api, array);
  
  int8_t* elements = api->get_byte_array_elements(api, array);
  
  AV* av_nums = (AV*)sv_2mortal((SV*)newAV());
  {
    int32_t i;
    for (i = 0; i < length; i++) {
      SV* sv_num = sv_2mortal(newSViv(elements[i]));
      av_store(av_nums, i, SvREFCNT_inc(sv_num));
    }
  }
  SV* sv_nums = sv_2mortal(newRV_inc((SV*)av_nums));
  
  XPUSHs(sv_nums);
  XSRETURN(1);
}

MODULE = SPVM::Array::Short		PACKAGE = SPVM::Array::Short

SV*
new(...)
  PPCODE:
{
  SV* sv_class = ST(0);
  SV* sv_length = ST(1);
  
  int32_t length = (int32_t)SvIV(sv_length);
  
  // Set API
  SPVM_API* api = SPVM_XS_UTIL_get_api();
  
  // Malloc array
  SPVM_API_ARRAY* array =  api->new_short_array(api, length);
  
  // Increment reference count
  api->inc_ref_count(api, array);
  
  // New sv array
  SV* sv_array = SPVM_XS_UTIL_new_sv_short_array(array);
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
set_elements(...)
  PPCODE:
{
  SV* sv_array = ST(0);
  SV* sv_nums = ST(1);
  AV* av_nums = SvRV(sv_nums);

  // Set API
  SPVM_API* api = SPVM_XS_UTIL_get_api();
  
  // Get content
  SPVM_API_ARRAY* array = SPVM_XS_UTIL_get_array(sv_array);
  
  int32_t length = api->get_array_length(api, array);
  
  int16_t* elements = api->get_short_array_elements(api, array);
  
  {
    int32_t i;
    for (i = 0; i < length; i++) {
      SV** sv_num_ptr = av_fetch(av_nums, i, 0);
      SV* sv_num = sv_num_ptr ? *sv_num_ptr : &PL_sv_undef;
      elements[i] = (int16_t)SvIV(sv_num);
    }
  }
  
  XSRETURN(0);
}

SV*
get_elements(...)
  PPCODE:
{
  SV* sv_array = ST(0);

  // Set API
  SPVM_API* api = SPVM_XS_UTIL_get_api();
  
  // Get content
  SPVM_API_ARRAY* array = SPVM_XS_UTIL_get_array(sv_array);
  
  int32_t length = api->get_array_length(api, array);
  
  int16_t* elements = api->get_short_array_elements(api, array);
  
  AV* av_nums = (AV*)sv_2mortal((SV*)newAV());
  {
    int32_t i;
    for (i = 0; i < length; i++) {
      SV* sv_num = sv_2mortal(newSViv(elements[i]));
      av_store(av_nums, i, SvREFCNT_inc(sv_num));
    }
  }
  SV* sv_nums = sv_2mortal(newRV_inc((SV*)av_nums));
  
  XPUSHs(sv_nums);
  XSRETURN(1);
}

MODULE = SPVM::Array::Int		PACKAGE = SPVM::Array::Int

SV*
new(...)
  PPCODE:
{
  SV* sv_class = ST(0);
  SV* sv_length = ST(1);
  
  int32_t length = (int32_t)SvIV(sv_length);
  
  // Set API
  SPVM_API* api = SPVM_XS_UTIL_get_api();
  
  // Malloc array
  SPVM_API_ARRAY* array =  api->new_int_array(api, length);

  // Increment reference count
  api->inc_ref_count(api, array);
  
  // New sv array
  SV* sv_array = SPVM_XS_UTIL_new_sv_int_array(array);
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
set_elements(...)
  PPCODE:
{
  SV* sv_array = ST(0);
  SV* sv_nums = ST(1);
  AV* av_nums = SvRV(sv_nums);

  // Set API
  SPVM_API* api = SPVM_XS_UTIL_get_api();
  
  // Get content
  SPVM_API_ARRAY* array = SPVM_XS_UTIL_get_array(sv_array);
  
  int32_t length = api->get_array_length(api, array);
  
  int32_t* elements = api->get_int_array_elements(api, array);
  
  {
    int32_t i;
    for (i = 0; i < length; i++) {
      SV** sv_num_ptr = av_fetch(av_nums, i, 0);
      SV* sv_num = sv_num_ptr ? *sv_num_ptr : &PL_sv_undef;
      elements[i] = (int32_t)SvIV(sv_num);
    }
  }
  
  XSRETURN(0);
}

SV*
get_elements(...)
  PPCODE:
{
  SV* sv_array = ST(0);

  // Set API
  SPVM_API* api = SPVM_XS_UTIL_get_api();
  
  // Get content
  SPVM_API_ARRAY* array = SPVM_XS_UTIL_get_array(sv_array);
  
  int32_t length = api->get_array_length(api, array);
  
  int32_t* elements = api->get_int_array_elements(api, array);
  
  AV* av_nums = (AV*)sv_2mortal((SV*)newAV());
  {
    int32_t i;
    for (i = 0; i < length; i++) {
      SV* sv_num = sv_2mortal(newSViv(elements[i]));
      av_store(av_nums, i, SvREFCNT_inc(sv_num));
    }
  }
  SV* sv_nums = sv_2mortal(newRV_inc((SV*)av_nums));
  
  XPUSHs(sv_nums);
  XSRETURN(1);
}

MODULE = SPVM::Array::Long		PACKAGE = SPVM::Array::Long

SV*
new(...)
  PPCODE:
{
  SV* sv_class = ST(0);
  SV* sv_length = ST(1);
  
  int32_t length = (int32_t)SvIV(sv_length);
  
  // Set API
  SPVM_API* api = SPVM_XS_UTIL_get_api();
  
  // Malloc array
  SPVM_API_ARRAY* array =  api->new_long_array(api, length);
  
  // Increment reference count
  api->inc_ref_count(api, array);
  
  // New sv array
  SV* sv_array = SPVM_XS_UTIL_new_sv_long_array(array);
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
set_elements(...)
  PPCODE:
{
  SV* sv_array = ST(0);
  SV* sv_nums = ST(1);
  AV* av_nums = SvRV(sv_nums);

  // Set API
  SPVM_API* api = SPVM_XS_UTIL_get_api();
  
  // Get content
  SPVM_API_ARRAY* array = SPVM_XS_UTIL_get_array(sv_array);
  
  int32_t length = api->get_array_length(api, array);
  
  int64_t* elements = api->get_long_array_elements(api, array);
  
  {
    int32_t i;
    for (i = 0; i < length; i++) {
      SV** sv_num_ptr = av_fetch(av_nums, i, 0);
      SV* sv_num = sv_num_ptr ? *sv_num_ptr : &PL_sv_undef;
      elements[i] = (int64_t)SvIV(sv_num);
    }
  }
  
  XSRETURN(0);
}

SV*
get_elements(...)
  PPCODE:
{
  SV* sv_array = ST(0);

  // Set API
  SPVM_API* api = SPVM_XS_UTIL_get_api();
  
  // Get content
  SPVM_API_ARRAY* array = SPVM_XS_UTIL_get_array(sv_array);
  
  int32_t length = api->get_array_length(api, array);
  
  int64_t* elements = api->get_long_array_elements(api, array);
  
  AV* av_nums = (AV*)sv_2mortal((SV*)newAV());
  {
    int32_t i;
    for (i = 0; i < length; i++) {
      SV* sv_num = sv_2mortal(newSViv(elements[i]));
      av_store(av_nums, i, SvREFCNT_inc(sv_num));
    }
  }
  SV* sv_nums = sv_2mortal(newRV_inc((SV*)av_nums));
  
  XPUSHs(sv_nums);
  XSRETURN(1);
}

MODULE = SPVM::Array::Float		PACKAGE = SPVM::Array::Float

SV*
new(...)
  PPCODE:
{
  SV* sv_class = ST(0);
  SV* sv_length = ST(1);
  
  int32_t length = (int32_t)SvIV(sv_length);
  
  // Set API
  SPVM_API* api = SPVM_XS_UTIL_get_api();
  
  // Malloc array
  SPVM_API_ARRAY* array =  api->new_float_array(api, length);
  
  // Increment reference count
  api->inc_ref_count(api, array);
  
  // New sv array
  SV* sv_array = SPVM_XS_UTIL_new_sv_float_array(array);
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
set_elements(...)
  PPCODE:
{
  SV* sv_array = ST(0);
  SV* sv_nums = ST(1);
  AV* av_nums = SvRV(sv_nums);

  // Set API
  SPVM_API* api = SPVM_XS_UTIL_get_api();
  
  // Get content
  SPVM_API_ARRAY* array = SPVM_XS_UTIL_get_array(sv_array);
  
  int32_t length = api->get_array_length(api, array);
  
  float* elements = api->get_float_array_elements(api, array);
  
  {
    int32_t i;
    for (i = 0; i < length; i++) {
      SV** sv_num_ptr = av_fetch(av_nums, i, 0);
      SV* sv_num = sv_num_ptr ? *sv_num_ptr : &PL_sv_undef;
      elements[i] = (float)SvNV(sv_num);
    }
  }
  
  XSRETURN(0);
}

SV*
get_elements(...)
  PPCODE:
{
  SV* sv_array = ST(0);

  // Set API
  SPVM_API* api = SPVM_XS_UTIL_get_api();
  
  // Get content
  SPVM_API_ARRAY* array = SPVM_XS_UTIL_get_array(sv_array);
  
  int32_t length = api->get_array_length(api, array);
  
  float* elements = api->get_float_array_elements(api, array);
  
  AV* av_nums = (AV*)sv_2mortal((SV*)newAV());
  {
    int32_t i;
    for (i = 0; i < length; i++) {
      SV* sv_num = sv_2mortal(newSVnv((NV)elements[i]));
      av_store(av_nums, i, SvREFCNT_inc(sv_num));
    }
  }
  SV* sv_nums = sv_2mortal(newRV_inc((SV*)av_nums));
  
  XPUSHs(sv_nums);
  XSRETURN(1);
}

MODULE = SPVM::Array::Double		PACKAGE = SPVM::Array::Double

SV*
new(...)
  PPCODE:
{
  SV* sv_class = ST(0);
  SV* sv_length = ST(1);
  
  int32_t length = (int32_t)SvIV(sv_length);
  
  // Set API
  SPVM_API* api = SPVM_XS_UTIL_get_api();
  
  // Malloc array
  SPVM_API_ARRAY* array =  api->new_double_array(api, length);
  
  // Increment reference count
  api->inc_ref_count(api, array);
  
  // New sv array
  SV* sv_array = SPVM_XS_UTIL_new_sv_double_array(array);
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
set_elements(...)
  PPCODE:
{
  SV* sv_array = ST(0);
  SV* sv_nums = ST(1);
  AV* av_nums = SvRV(sv_nums);

  // Set API
  SPVM_API* api = SPVM_XS_UTIL_get_api();
  
  // Get content
  SPVM_API_ARRAY* array = SPVM_XS_UTIL_get_array(sv_array);
  
  int32_t length = api->get_array_length(api, array);
  
  double* elements = api->get_double_array_elements(api, array);
  
  {
    int32_t i;
    for (i = 0; i < length; i++) {
      SV** sv_num_ptr = av_fetch(av_nums, i, 0);
      SV* sv_num = sv_num_ptr ? *sv_num_ptr : &PL_sv_undef;
      elements[i] = (double)SvNV(sv_num);
    }
  }
  
  XSRETURN(0);
}

SV*
get_elements(...)
  PPCODE:
{
  SV* sv_array = ST(0);

  // Set API
  SPVM_API* api = SPVM_XS_UTIL_get_api();
  
  // Get content
  SPVM_API_ARRAY* array = SPVM_XS_UTIL_get_array(sv_array);
  
  int32_t length = api->get_array_length(api, array);
  
  double* elements = api->get_double_array_elements(api, array);
  
  AV* av_nums = (AV*)sv_2mortal((SV*)newAV());
  {
    int32_t i;
    for (i = 0; i < length; i++) {
      SV* sv_num = sv_2mortal(newSVnv((NV)elements[i]));
      av_store(av_nums, i, SvREFCNT_inc(sv_num));
    }
  }
  SV* sv_nums = sv_2mortal(newRV_inc((SV*)av_nums));
  
  XPUSHs(sv_nums);
  XSRETURN(1);
}

MODULE = SPVM::String		PACKAGE = SPVM::String

SV*
new_raw(...)
  PPCODE:
{
  SV* sv_class = ST(0);
  SV* sv_string = ST(1);
  
  int32_t length = (int32_t)sv_len(sv_string);
  
  // Set API
  SPVM_API* api = SPVM_XS_UTIL_get_api();
  
  // Malloc array
  SPVM_API_ARRAY* array =  api->new_byte_array(api, length);
  
  // Increment reference count
  api->inc_ref_count(api, array);
  
  const char* string = SvPV_nolen(sv_string);
  int8_t* elements = api->get_byte_array_elements(api, array);
  memcpy(elements, string, length);
  
  // New sv array
  SV* sv_array = SPVM_XS_UTIL_new_sv_string(array);
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

MODULE = SPVM::Array		PACKAGE = SPVM::Array


MODULE = SPVM		PACKAGE = SPVM

SV*
compile(...)
  PPCODE:
{
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
      SPVM_OP* op_use_package = SPVM_OP_new_op_use_from_package_name(compiler, name, file, line);
      SPVM_DYNAMIC_ARRAY_push(compiler->op_use_stack, op_use_package);
      SPVM_HASH_insert(compiler->op_use_symtable, name, strlen(name), op_use_package);
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
      SPVM_DYNAMIC_ARRAY_push(compiler->include_pathes, include_path);
    }
  }
  
  // Compile SPVM
  SPVM_COMPILER_compile(compiler);
  if (compiler->error_count > 0) {
    croak("SPVM compile error %d", compiler->error_count);
  }
  
  // Set compiler
  size_t iv_compiler = PTR2IV(compiler);
  SV* sviv_compiler = sv_2mortal(newSViv(iv_compiler));
  SV* sv_compiler = sv_2mortal(newRV_inc(sviv_compiler));
  sv_setsv(get_sv("SPVM::COMPILER", 0), sv_compiler);
  
  XSRETURN(0);
}

SV*
build_sub_symtable(...)
  PPCODE:
{
  // Get compiler
  SPVM_COMPILER* compiler = SPVM_XS_INTERNAL_UTIL_get_compiler();
  
  // Subroutine information
  HV* hv_sub_symtable = get_hv("SPVM::SUB_SYMTABLE", 0);
  
  // abs_name, arg_types, return_type, id, type_id
  SPVM_DYNAMIC_ARRAY* op_packages = compiler->op_packages;
  {
    int32_t package_index;
    for (package_index = 0; package_index < op_packages->length; package_index++) {
      SPVM_OP* op_package = SPVM_DYNAMIC_ARRAY_fetch(op_packages, package_index);
      SPVM_DYNAMIC_ARRAY* op_subs = op_package->uv.package->op_subs;
      {
        int32_t sub_index;
        for (sub_index = 0; sub_index < op_subs->length; sub_index++) {
          // Sub information
          HV* hv_sub_info = (HV*)sv_2mortal((SV*)newHV());
          
          SPVM_OP* op_sub = SPVM_DYNAMIC_ARRAY_fetch(op_subs, sub_index);
          SPVM_SUB* sub = op_sub->uv.sub;
          const char* sub_abs_name = sub->abs_name;
          
          // Subroutine id
          int32_t sub_id = sub->constant_pool_index;
          SV* sv_sub_id = sv_2mortal(newSViv(sub_id));
          hv_store(hv_sub_info, "id", strlen("id"), SvREFCNT_inc(sv_sub_id), 0);
          
          // Argument types
          AV* av_arg_type_names = (AV*)sv_2mortal((SV*)newAV());
          AV* av_arg_type_ids = (AV*)sv_2mortal((SV*)newAV());
          SPVM_DYNAMIC_ARRAY* op_args = sub->op_args;
          {
            int32_t arg_index;
            for (arg_index = 0; arg_index < op_args->length; arg_index++) {
              SPVM_OP* op_arg = SPVM_DYNAMIC_ARRAY_fetch(op_args, arg_index);
              SPVM_OP* op_arg_type = op_arg->uv.my_var->op_type;
              SPVM_TYPE* arg_type = op_arg_type->uv.type;
              const char* arg_type_name = arg_type->name;
              int32_t arg_type_id = arg_type->id;
              
              SV* sv_arg_type_name = sv_2mortal(newSVpv(arg_type_name, 0));
              av_push(av_arg_type_names, SvREFCNT_inc(sv_arg_type_name));
              
              SV* sv_arg_type_id = sv_2mortal(newSViv(arg_type_id));
              av_push(av_arg_type_ids, SvREFCNT_inc(sv_arg_type_id));
            }
          }
          SV* sv_arg_type_names = sv_2mortal(newRV_inc((SV*)av_arg_type_names));
          hv_store(hv_sub_info, "arg_types", strlen("arg_types"), SvREFCNT_inc(sv_arg_type_names), 0);
          
          SV* sv_arg_type_ids = sv_2mortal(newRV_inc((SV*)av_arg_type_ids));
          hv_store(hv_sub_info, "arg_type_ids", strlen("arg_type_ids"), SvREFCNT_inc(sv_arg_type_ids), 0);
          
          // Return type
          SPVM_OP* op_return_type = sub->op_return_type;
          SPVM_TYPE* return_type = SPVM_OP_get_type(compiler, op_return_type);
          if (return_type) {
            const char* return_type = op_return_type->uv.type->name;
            SV* sv_return_type = sv_2mortal(newSVpv(return_type, 0));
            hv_store(hv_sub_info, "return_type", strlen("return_type"), SvREFCNT_inc(sv_return_type), 0);
          }
          else {
            hv_store(hv_sub_info, "return_type", strlen("return_type"), &PL_sv_undef, 0);
          }
          
          // Return type id
          SV* sv_return_type_id;
          if (return_type) {
            sv_return_type_id = sv_2mortal(newSViv(return_type->id));
          }
          else {
            sv_return_type_id = sv_2mortal(newSViv(-1));
          }
          hv_store(hv_sub_info, "return_type_id", strlen("return_type_id"), SvREFCNT_inc(sv_return_type_id), 0);
          
          SV* sv_sub_info = sv_2mortal(newRV_inc((SV*)hv_sub_info));
          hv_store(hv_sub_symtable, sub_abs_name, strlen(sub_abs_name), SvREFCNT_inc(sv_sub_info), 0);
        }
      }
    }
  }
  
  XSRETURN(0);
}

SV*
build_type_symtable(...)
  PPCODE:
{
  // Get compiler
  SPVM_COMPILER* compiler = SPVM_XS_INTERNAL_UTIL_get_compiler();
  
  // Subroutine information
  HV* hv_type_symtable = get_hv("SPVM::TYPE_SYMTABLE", 0);
  
  // abs_name, arg_types, return_type, id, type_id
  SPVM_DYNAMIC_ARRAY* types = compiler->types;
  {
    int32_t type_id;
    for (type_id = 0; type_id < types->length; type_id++) {
      SPVM_TYPE* type = SPVM_DYNAMIC_ARRAY_fetch(types, type_id);
      
      const char* type_name = type->name;
      int32_t type_id = type->id;
      SV* sv_type_id = sv_2mortal(newSViv(type_id));
      
      HV* hv_type_info = (HV*)sv_2mortal((SV*)newHV());
      hv_store(hv_type_info, "id", strlen("id"), SvREFCNT_inc(sv_type_id), 0);
      SV* sv_type_info = sv_2mortal(newRV_inc((SV*)hv_type_info));
      
      hv_store(hv_type_symtable, type_name, strlen(type_name), SvREFCNT_inc(sv_type_info), 0);
    }
  }
  
  XSRETURN(0);
}

SV*
build_package_symtable(...)
  PPCODE:
{
  // Get compiler
  SPVM_COMPILER* compiler = SPVM_XS_INTERNAL_UTIL_get_compiler();
  
  // Subroutine information
  HV* hv_package_symtable = get_hv("SPVM::PACKAGE_SYMTABLE", 0);
  
  // abs_name, arg_packages, return_package, id, package_id
  SPVM_DYNAMIC_ARRAY* op_packages = compiler->op_packages;
  {
    int32_t package_index;
    for (package_index = 0; package_index < op_packages->length; package_index++) {
      SPVM_OP* op_package = SPVM_DYNAMIC_ARRAY_fetch(op_packages, package_index);
      SPVM_PACKAGE* package = op_package->uv.package;
      
      const char* package_name = package->op_name->uv.name;
      int32_t package_id = package->constant_pool_index;
      SV* sv_package_id = sv_2mortal(newSViv(package_id));
      
      HV* hv_package_info = (HV*)sv_2mortal((SV*)newHV());
      hv_store(hv_package_info, "id", strlen("id"), SvREFCNT_inc(sv_package_id), 0);
      SV* sv_package_info = sv_2mortal(newRV_inc((SV*)hv_package_info));

      hv_store(hv_package_symtable, package_name, strlen(package_name), SvREFCNT_inc(sv_package_info), 0);
    }
  }
  
  XSRETURN(0);
}

SV*
build_field_symtable(...)
  PPCODE:
{
  // Get compiler
  SPVM_COMPILER* compiler = SPVM_XS_INTERNAL_UTIL_get_compiler();
  
  // Field symbol table
  HV* hv_field_symtable = get_hv("SPVM::FIELD_SYMTABLE", 0);
  
  // name, arg_types, return_type
  SPVM_DYNAMIC_ARRAY* op_packages = compiler->op_packages;
  {
    int32_t package_index;
    for (package_index = 0; package_index < op_packages->length; package_index++) {
      SPVM_OP* op_package = SPVM_DYNAMIC_ARRAY_fetch(op_packages, package_index);
      const char* package_name = op_package->uv.package->op_name->uv.name;
      
      HV* hv_package_info = (HV*)sv_2mortal((SV*)newHV());
      
      SPVM_DYNAMIC_ARRAY* op_fields = op_package->uv.package->op_fields;
      {
        int32_t field_index;
        for (field_index = 0; field_index < op_fields->length; field_index++) {
          SPVM_OP* op_field = SPVM_DYNAMIC_ARRAY_fetch(op_fields, field_index);
          SPVM_FIELD* field = op_field->uv.field;
          const char* field_name = field->op_name->uv.name;
          
          // Field type
          const char* field_type = field->op_type->uv.type->name;
          SV* sv_field_type = sv_2mortal(newSVpv(field_type, 0));
          
          // Field id
          int32_t field_id = field->index;
          SV* sv_field_id = sv_2mortal(newSViv(field_id));
          
          HV* hv_field_info = (HV*)sv_2mortal((SV*)newHV());
          hv_store(hv_field_info, "type", strlen("type"), SvREFCNT_inc(sv_field_type), 0);
          hv_store(hv_field_info, "id", strlen("id"), SvREFCNT_inc(sv_field_id), 0);
          SV* sv_field_info = sv_2mortal(newRV_inc((SV*)hv_field_info));
          
          hv_store(hv_package_info, field_name, strlen(field_name), SvREFCNT_inc(sv_field_info), 0);
        }
      }
      
      SV* sv_package_info = sv_2mortal(newRV_inc((SV*)hv_package_info));
      hv_store(hv_field_symtable, package_name, strlen(package_name), SvREFCNT_inc(sv_package_info), 0);
    }
  }
  
  XSRETURN(0);
}

SV*
build_runtime(...)
  PPCODE:
{
  // Get compiler
  SPVM_COMPILER* compiler = SPVM_XS_INTERNAL_UTIL_get_compiler();
  
  // Create run-time
  SPVM_RUNTIME* runtime = SPVM_COMPILER_new_runtime(compiler);
  
  // SPVM API
  SPVM_API* api = runtime->api;
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
  // Get compiler
  SPVM_COMPILER* compiler = SPVM_XS_INTERNAL_UTIL_get_compiler();
  
  // Free compiler
  SPVM_COMPILER_free(compiler);
  
  // Set undef to compiler
  sv_setsv(get_sv("SPVM::COMPILER", 0), &PL_sv_undef);
  
  XSRETURN(0);
}

SV*
call_sub(...)
  PPCODE:
{
  SV* sv_sub_abs_name = ST(0);
  
  HV* hv_sub_symtable = get_hv("SPVM::SUB_SYMTABLE", 0);
  
  const char* sub_abs_name = SvPV_nolen(sv_sub_abs_name);
  SV** sv_sub_info_ptr = hv_fetch(hv_sub_symtable, sub_abs_name, strlen(sub_abs_name), 0);
  SV* sv_sub_info = sv_sub_info_ptr ? *sv_sub_info_ptr : &PL_sv_undef;
  HV* hv_sub_info = (HV*)SvRV(sv_sub_info);
  
  // Subroutine id
  SV** sv_sub_id_ptr = hv_fetch(hv_sub_info, "id", strlen("id"), 0);
  SV* sv_sub_id = sv_sub_id_ptr ? *sv_sub_id_ptr : &PL_sv_undef;
  int32_t sub_id = (int32_t)SvIV(sv_sub_id);
  
  // Argument types
  SV** sv_arg_type_names_ptr = hv_fetch(hv_sub_info, "arg_types", strlen("arg_types"), 0);
  SV* sv_arg_type_names = sv_arg_type_names_ptr ? *sv_arg_type_names_ptr : &PL_sv_undef;
  AV* av_arg_type_names = (AV*)SvRV(sv_arg_type_names);
  int32_t args_length = av_len(av_arg_type_names) + 1;
  
  // Argument type id
  SV** sv_arg_type_ids_ptr = hv_fetch(hv_sub_info, "arg_type_ids", strlen("arg_type_ids"), 0);
  SV* sv_arg_type_ids = sv_arg_type_ids_ptr ? *sv_arg_type_ids_ptr : &PL_sv_undef;
  AV* av_arg_type_ids = (AV*)SvRV(sv_arg_type_ids);
  
  // Return type
  SV** sv_return_type_ptr = hv_fetch(hv_sub_info, "return_type", strlen("return_type"), 0);
  SV* sv_return_type = sv_return_type_ptr ? *sv_return_type_ptr : &PL_sv_undef;

  // Return type id
  SV** sv_return_type_id_ptr = hv_fetch(hv_sub_info, "return_type_id", strlen("return_type_id"), 0);
  SV* sv_return_type_id = sv_return_type_id_ptr ? *sv_return_type_id_ptr : &PL_sv_undef;
  int32_t return_type_id = SvIV(sv_return_type_id);
  
  // Get API
  SV* sv_api = get_sv("SPVM::API", 0);
  SV* sviv_api = SvROK(sv_api) ? SvRV(sv_api) : sv_api;
  size_t iv_api = SvIV(sviv_api);
  SPVM_API* api = INT2PTR(SPVM_API*, iv_api);
  
  // Check argument count
  if (items - 1 != args_length) {
    croak("Argument count is defferent");
  }
  
  // Push arguments
  {
    int32_t arg_index;
    for (arg_index = 0; arg_index < args_length; arg_index++) {
      SV* sv_value = ST(arg_index + 1);
      
      SV** sv_arg_type_id_ptr = av_fetch(av_arg_type_ids, arg_index, 0);
      SV* sv_arg_type_id = sv_arg_type_id_ptr ? *sv_arg_type_id_ptr : &PL_sv_undef;
      int32_t arg_type_id = SvIV(sv_arg_type_id);
      
      if (sv_isobject(sv_value)) {
        SV* sv_base_object = sv_value;
        if (sv_derived_from(sv_base_object, "SPVM::BaseObject")) {
          SV** sv_arg_type_name_ptr = av_fetch(av_arg_type_names, arg_index, 0);
          SV* sv_arg_type_name = sv_arg_type_name_ptr ? *sv_arg_type_name_ptr : &PL_sv_undef;
          const char* arg_type_name = SvPV_nolen(sv_arg_type_name);
         
          HV* hv_base_object = (HV*)SvRV(sv_base_object);
          
          SV** sv_base_object_type_name_ptr = hv_fetch(hv_base_object, "type", strlen("type"), 0);
          SV* sv_base_object_type_name = sv_base_object_type_name_ptr ? *sv_base_object_type_name_ptr : &PL_sv_undef;
          const char* base_object_type_name = SvPV_nolen(sv_base_object_type_name);
          
          if (!strEQ(base_object_type_name, arg_type_name)) {
            croak("Argument base_object type need %s, but %s", arg_type_name, base_object_type_name);
          }
          
          // Get content
          SV** sv_content_ptr = hv_fetch(hv_base_object, "content", strlen("content"), 0);
          SV* sv_content = sv_content_ptr ? *sv_content_ptr : &PL_sv_undef;
          SV* sviv_content = SvRV(sv_content);
          size_t iv_content = SvIV(sviv_content);
          SPVM_API_BASE_OBJECT* base_object = INT2PTR(SPVM_API_BASE_OBJECT*, iv_content);
          
          call_sub_args[arg_index].object_value = base_object;
        }
        else {
          croak("Object must be derived from SPVM::BaseObject");
        }
      }
      else {
        switch (arg_type_id) {
          case SPVM_TYPE_C_ID_BYTE : {
            int8_t value = (int8_t)SvIV(sv_value);
            call_sub_args[arg_index].byte_value = value;
            break;
          }
          case  SPVM_TYPE_C_ID_SHORT : {
            int16_t value = (int16_t)SvIV(sv_value);
            call_sub_args[arg_index].short_value = value;
            break;
          }
          case  SPVM_TYPE_C_ID_INT : {
            int32_t value = (int32_t)SvIV(sv_value);
            call_sub_args[arg_index].int_value = value;
            break;
          }
          case  SPVM_TYPE_C_ID_LONG : {
            int64_t value = (int64_t)SvIV(sv_value);
            call_sub_args[arg_index].long_value = value;
            break;
          }
          case  SPVM_TYPE_C_ID_FLOAT : {
            float value = (float)SvNV(sv_value);
            call_sub_args[arg_index].float_value = value;
            break;
          }
          case  SPVM_TYPE_C_ID_DOUBLE : {
            double value = (double)SvNV(sv_value);
            call_sub_args[arg_index].double_value = value;
            break;
          }
          default :
            assert(0);
        }
      }
    }
  }
  
  api->set_exception(api, NULL);
  
  switch (return_type_id) {
    case SPVM_TYPE_C_ID_VOID:  {
      api->call_void_sub(api, sub_id, &call_sub_args);
      SPVM_API_ARRAY* exception = api->get_exception(api);
      if (exception) {
        int32_t length = api->get_array_length(api, exception);
        int8_t* exception_bytes = api->get_byte_array_elements(api, exception);
        SV* sv_exception = newSVpv(exception_bytes, length);
        croak("%s", SvPV_nolen(sv_exception));
      }
      XSRETURN(0);
      break;
    }
    case SPVM_TYPE_C_ID_BYTE: {
      int8_t return_value = api->call_byte_sub(api, sub_id, &call_sub_args);
      SPVM_API_ARRAY* exception = api->get_exception(api);
      if (exception) {
        int32_t length = api->get_array_length(api, exception);
        int8_t* exception_bytes = api->get_byte_array_elements(api, exception);
        SV* sv_exception = newSVpv(exception_bytes, length);
        croak("%s", SvPV_nolen(sv_exception));
      }
      SV* sv_return_value = sv_2mortal(newSViv(return_value));
      XPUSHs(sv_return_value);
      XSRETURN(1);
      break;
    }
    case SPVM_TYPE_C_ID_SHORT: {
      int16_t return_value = api->call_short_sub(api, sub_id, &call_sub_args);
      SPVM_API_ARRAY* exception = api->get_exception(api);
      if (exception) {
        int32_t length = api->get_array_length(api, exception);
        int8_t* exception_bytes = api->get_byte_array_elements(api, exception);
        SV* sv_exception = newSVpv(exception_bytes, length);
        croak("%s", SvPV_nolen(sv_exception));
      }
      SV* sv_return_value = sv_2mortal(newSViv(return_value));
      XPUSHs(sv_return_value);
      XSRETURN(1);
      break;
    }
    case SPVM_TYPE_C_ID_INT: {
      int32_t return_value = api->call_int_sub(api, sub_id, &call_sub_args);
      SPVM_API_ARRAY* exception = api->get_exception(api);
      if (exception) {
        int32_t length = api->get_array_length(api, exception);
        int8_t* exception_bytes = api->get_byte_array_elements(api, exception);
        SV* sv_exception = newSVpv(exception_bytes, length);
        croak("%s", SvPV_nolen(sv_exception));
      }
      SV* sv_return_value = sv_2mortal(newSViv(return_value));
      XPUSHs(sv_return_value);
      XSRETURN(1);
      break;
    }
    case SPVM_TYPE_C_ID_LONG: {
      int64_t return_value = api->call_long_sub(api, sub_id, &call_sub_args);
      SPVM_API_ARRAY* exception = api->get_exception(api);
      if (exception) {
        int32_t length = api->get_array_length(api, exception);
        int8_t* exception_bytes = api->get_byte_array_elements(api, exception);
        SV* sv_exception = newSVpv(exception_bytes, length);
        croak("%s", SvPV_nolen(sv_exception));
      }
      SV* sv_return_value = sv_2mortal(newSViv(return_value));
      XPUSHs(sv_return_value);
      XSRETURN(1);
      break;
    }
    case SPVM_TYPE_C_ID_FLOAT: {
      float return_value = api->call_float_sub(api, sub_id, &call_sub_args);
      SPVM_API_ARRAY* exception = api->get_exception(api);
      if (exception) {
        int32_t length = api->get_array_length(api, exception);
        int8_t* exception_bytes = api->get_byte_array_elements(api, exception);
        SV* sv_exception = newSVpv(exception_bytes, length);
        croak("%s", SvPV_nolen(sv_exception));
      }
      SV* sv_return_value = sv_2mortal(newSVnv(return_value));
      XPUSHs(sv_return_value);
      XSRETURN(1);
      break;
    }
    case SPVM_TYPE_C_ID_DOUBLE: {
      double return_value = api->call_double_sub(api, sub_id, &call_sub_args);
      SPVM_API_ARRAY* exception = api->get_exception(api);
      if (exception) {
        int32_t length = api->get_array_length(api, exception);
        int8_t* exception_bytes = api->get_byte_array_elements(api, exception);
        SV* sv_exception = newSVpv(exception_bytes, length);
        croak("%s", SvPV_nolen(sv_exception));
      }
      SV* sv_return_value = sv_2mortal(newSVnv(return_value));
      XPUSHs(sv_return_value);
      XSRETURN(1);
      break;
    }
    default: {
      SPVM_API_BASE_OBJECT* return_value = api->call_object_sub(api, sub_id, &call_sub_args);
      SPVM_API_ARRAY* exception = api->get_exception(api);
      if (exception) {
        int32_t length = api->get_array_length(api, exception);
        int8_t* exception_bytes = api->get_byte_array_elements(api, exception);
        SV* sv_exception = newSVpv(exception_bytes, length);
        croak("%s", SvPV_nolen(sv_exception));
      }
      
      SV* sv_return_value = NULL;
      if (return_value != NULL) {
        api->inc_ref_count(api, return_value);
        
        switch(return_type_id) {
          case SPVM_TYPE_C_ID_ARRAY_BYTE :
            sv_return_value = SPVM_XS_UTIL_new_sv_byte_array((SPVM_API_ARRAY*)return_value);
            break;
          case SPVM_TYPE_C_ID_ARRAY_SHORT :
            sv_return_value = SPVM_XS_UTIL_new_sv_short_array((SPVM_API_ARRAY*)return_value);
            break;
          case SPVM_TYPE_C_ID_ARRAY_INT :
            sv_return_value = SPVM_XS_UTIL_new_sv_int_array((SPVM_API_ARRAY*)return_value);
            break;
          case SPVM_TYPE_C_ID_ARRAY_LONG :
            sv_return_value = SPVM_XS_UTIL_new_sv_long_array((SPVM_API_ARRAY*)return_value);
            break;
          case SPVM_TYPE_C_ID_ARRAY_FLOAT :
            sv_return_value = SPVM_XS_UTIL_new_sv_float_array((SPVM_API_ARRAY*)return_value);
            break;
          case SPVM_TYPE_C_ID_ARRAY_DOUBLE :
            sv_return_value = SPVM_XS_UTIL_new_sv_double_array((SPVM_API_ARRAY*)return_value);
            break;
          case SPVM_TYPE_C_ID_STRING :
            sv_return_value = SPVM_XS_UTIL_new_sv_string((SPVM_API_ARRAY*)return_value);
            break;
          default : {
            const char* return_type = SvPV_nolen(sv_return_type);
            int32_t type_length = strlen(return_type);
            if (return_type[type_length -1] == ']') {
              sv_return_value = SPVM_XS_UTIL_new_sv_object_array(return_type, (SPVM_API_ARRAY*)return_value);
            }
            else {
              sv_return_value = SPVM_XS_UTIL_new_sv_object(return_type, (SPVM_API_OBJECT*)return_value);
            }
          }
        }
      }
      else {
        sv_return_value = &PL_sv_undef;
      }
      XPUSHs(sv_return_value);
      XSRETURN(1);
    }
  }
}
