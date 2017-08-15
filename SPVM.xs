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

#include "spvm_nai.h"
#include "spvm_xs_util.h"

static SPVM_NAI_VALUE call_sub_args[255];

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
  SPVM_NAI* nai = SPVM_XS_UTIL_get_nai();
  
  // Get content
  SPVM_NAI_OBJECT* object = SPVM_XS_UTIL_get_object(sv_object);
  
  assert(nai->get_ref_count(nai, object));
  
  // Decrement reference count
  nai->dec_ref_count(nai, object);
  
  XSRETURN(0);
}

MODULE = SPVM::Object		PACKAGE = SPVM::Object

SV*
new_object(...)
  PPCODE:
{
  SV* sv_class = ST(0);
  SV* sv_package_name = ST(1);
  
  if (!SvOK(sv_package_name)) {
    croak("Type must be specified(SPVM::Object::new_object)");
  }
  
  const char* package_name = SvPV_nolen(sv_package_name);

  int32_t package_id = SPVM_XS_UTIL_get_package_id(package_name);
  int32_t type_id = SPVM_XS_UTIL_get_type_id_from_package_name(package_name);
  
  if (package_id == SPVM_NAI_ERROR_NO_ID) {
    croak("Unkown package \"%s\"(SPVM::Object::new_object", package_name);
  }
  
  // Set API
  SPVM_NAI* nai = SPVM_XS_UTIL_get_nai();
  
  // Malloc array
  SPVM_NAI_OBJECT* object =  nai->new_object(nai, package_id);
  
  // Increment
  nai->inc_ref_count(nai, object);

  // New sv object
  SV* sv_object = SPVM_XS_UTIL_new_sv_object(type_id, object);
  
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
  SPVM_NAI* nai = SPVM_XS_UTIL_get_nai();
  
  // Get content
  SPVM_NAI_OBJECT* object = SPVM_XS_UTIL_get_object(sv_object);

  // Package type id
  int32_t package_type_id = SPVM_XS_UTIL_get_sv_object_type_id(sv_object);
  
  // Package name
  const char* package_name = SPVM_XS_UTIL_get_type_name(package_type_id);
  
  // Field type
  const char* field_name = SvPV_nolen(sv_field_name);
  int32_t field_type_id = SPVM_XS_UTIL_get_field_type_id(package_name, field_name);

  // Field id
  int32_t field_id = nai->get_field_id(nai, object, field_name);
  if (field_id == SPVM_NAI_ERROR_NO_ID) {
    croak("Can't find %s \"%s\" field(SPVM::Object::set)", package_name, field_name);
  }
  
  switch (field_type_id) {
    case SPVM_TYPE_C_ID_BYTE : {
      int8_t value = (int8_t)SvIV(sv_value);
      nai->set_byte_field(nai, object, field_id, value);
      break;
    }
    case  SPVM_TYPE_C_ID_SHORT : {
      int16_t value = (int16_t)SvIV(sv_value);
      nai->set_short_field(nai, object, field_id, value);
      break;
    }
    case SPVM_TYPE_C_ID_INT : {
      int32_t value = (int32_t)SvIV(sv_value);
      nai->set_int_field(nai, object, field_id, value);
      break;
    }
    case SPVM_TYPE_C_ID_LONG : {
      int64_t value = (int64_t)SvIV(sv_value);
      nai->set_long_field(nai, object, field_id, value);
      break;
    }
    case SPVM_TYPE_C_ID_FLOAT : {
      float value = (float)SvNV(sv_value);
      nai->set_float_field(nai, object, field_id, value);
      break;
    }
    case SPVM_TYPE_C_ID_DOUBLE : {
      double value = (double)SvNV(sv_value);
      nai->set_double_field(nai, object, field_id, value);
      break;
    }
    default : {
      if (!sv_derived_from(sv_value, "SPVM::BaseObject")) {
        const char* field_type_name = SPVM_XS_UTIL_get_type_name(field_type_id);
        croak("Can't set numeric value to \"%s\" field", field_type_name);
      }
      int32_t value_type_id = SPVM_XS_UTIL_get_sv_object_type_id(sv_value);
      if (value_type_id != field_type_id) {
        const char* field_type_name = SPVM_XS_UTIL_get_type_name(field_type_id);
        const char* value_type_name = SPVM_XS_UTIL_get_type_name(value_type_id);
        croak("Can't set \"%s\" value to \"%s\" field", value_type_name, field_type_name);
      }
      
      SPVM_NAI_OBJECT* array = SPVM_XS_UTIL_get_array(sv_value);
      
      nai->set_object_field(nai, object, field_id, array);
    }
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
  SPVM_NAI* nai = SPVM_XS_UTIL_get_nai();
  
  // Get content
  SPVM_NAI_OBJECT* object = SPVM_XS_UTIL_get_object(sv_object);
  
  // Package type id
  int32_t package_type_id = SPVM_XS_UTIL_get_sv_object_type_id(sv_object);

  // Package name
  const char* package_name = SPVM_XS_UTIL_get_type_name(package_type_id);

  // Field type id
  const char* field_name = SvPV_nolen(sv_field_name);
  int32_t field_type_id = SPVM_XS_UTIL_get_field_type_id(package_name, field_name);
  
  // Field id
  int32_t field_id = nai->get_field_id(nai, object, field_name);
  
  if (field_id == SPVM_NAI_ERROR_NO_ID) {
    croak("Can't find %s \"%s\" field(SPVM::Object::set)", package_name, field_name);
  }
  
  switch (field_type_id) {
    case SPVM_TYPE_C_ID_BYTE : {
      int8_t value = nai->get_byte_field(nai, object, field_id);
      SV* sv_value = sv_2mortal(newSViv(value));
      XPUSHs(sv_value);
      break;
    }
    case SPVM_TYPE_C_ID_SHORT : {
      int16_t value = nai->get_short_field(nai, object, field_id);
      SV* sv_value = sv_2mortal(newSViv(value));
      XPUSHs(sv_value);
      break;
    }
    case SPVM_TYPE_C_ID_INT : {
      int32_t value = nai->get_int_field(nai, object, field_id);
      SV* sv_value = sv_2mortal(newSViv(value));
      XPUSHs(sv_value);
      break;
    }
    case SPVM_TYPE_C_ID_LONG : {
      int64_t value = nai->get_long_field(nai, object, field_id);
      SV* sv_value = sv_2mortal(newSViv(value));
      XPUSHs(sv_value);
      break;
    }
    case SPVM_TYPE_C_ID_FLOAT : {
      float value = nai->get_float_field(nai, object, field_id);
      SV* sv_value = sv_2mortal(newSVnv(value));
      XPUSHs(sv_value);
      break;
    }
    case SPVM_TYPE_C_ID_DOUBLE : {
      double value = nai->get_double_field(nai, object, field_id);
      SV* sv_value = sv_2mortal(newSVnv(value));
      XPUSHs(sv_value);
      break;
    }
    default : {
      SPVM_NAI_OBJECT* value = nai->get_object_field(nai, object, field_id);
      
      if (value != NULL) {
        nai->inc_ref_count(nai, value);
      }
      
      switch (field_type_id) {
        case SPVM_TYPE_C_ID_BYTE_ARRAY : {
          SV* sv_array = SPVM_XS_UTIL_new_sv_byte_array((SPVM_NAI_OBJECT*)value);
          XPUSHs(sv_array);
          break;
        }
        case SPVM_TYPE_C_ID_SHORT_ARRAY : {
          SV* sv_array = SPVM_XS_UTIL_new_sv_short_array((SPVM_NAI_OBJECT*)value);
          XPUSHs(sv_array);
          break;
        }
        case SPVM_TYPE_C_ID_INT_ARRAY : {
          SV* sv_array = SPVM_XS_UTIL_new_sv_int_array((SPVM_NAI_OBJECT*)value);
          XPUSHs(sv_array);
          break;
        }
        case SPVM_TYPE_C_ID_LONG_ARRAY : {
          SV* sv_array = SPVM_XS_UTIL_new_sv_long_array((SPVM_NAI_OBJECT*)value);
          XPUSHs(sv_array);
          break;
        }
        case SPVM_TYPE_C_ID_FLOAT_ARRAY : {
          SV* sv_array = SPVM_XS_UTIL_new_sv_float_array((SPVM_NAI_OBJECT*)value);
          XPUSHs(sv_array);
          break;
        }
        case SPVM_TYPE_C_ID_DOUBLE_ARRAY : {
          SV* sv_array = SPVM_XS_UTIL_new_sv_double_array((SPVM_NAI_OBJECT*)value);
          XPUSHs(sv_array);
          break;
        }
        case SPVM_TYPE_C_ID_STRING : {
          SV* sv_array = SPVM_XS_UTIL_new_sv_string((SPVM_NAI_OBJECT*)value);
          XPUSHs(sv_array);
          break;
        }
        default : {
          const char* field_type_name = SPVM_XS_UTIL_get_type_name(field_type_id);
          
          int32_t field_type_name_length = strlen(field_type_name);
          
          if (field_type_name[field_type_name_length - 1] == ']') {
            SV* sv_array = SPVM_XS_UTIL_new_sv_object_array(field_type_id, (SPVM_NAI_OBJECT*)value);
            XPUSHs(sv_array);
          }
          else {
            SV* sv_object = SPVM_XS_UTIL_new_sv_object(field_type_id, (SPVM_NAI_OBJECT*)value);
            XPUSHs(sv_object);
          }
        }
      }
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
  SPVM_NAI* nai = SPVM_XS_UTIL_get_nai();
  
  // Malloc array
  SPVM_NAI_OBJECT* array =  nai->new_byte_array(nai, length);
  
  // Increment reference count
  nai->inc_ref_count(nai, array);
  
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
  AV* av_nums = (AV*)SvRV(sv_nums);

  // Set API
  SPVM_NAI* nai = SPVM_XS_UTIL_get_nai();
  
  // Get content
  SPVM_NAI_OBJECT* array = SPVM_XS_UTIL_get_array(sv_array);
  
  int32_t length = nai->get_array_length(nai, array);
  
  int8_t* elements = nai->get_byte_array_elements(nai, array);
  
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
  SPVM_NAI* nai = SPVM_XS_UTIL_get_nai();
  
  // Get content
  SPVM_NAI_OBJECT* array = SPVM_XS_UTIL_get_array(sv_array);
  
  int32_t length = nai->get_array_length(nai, array);
  
  int8_t* elements = nai->get_byte_array_elements(nai, array);
  
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
  SPVM_NAI* nai = SPVM_XS_UTIL_get_nai();
  
  // Malloc array
  SPVM_NAI_OBJECT* array =  nai->new_short_array(nai, length);
  
  // Increment reference count
  nai->inc_ref_count(nai, array);
  
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
  AV* av_nums = (AV*)SvRV(sv_nums);

  // Set API
  SPVM_NAI* nai = SPVM_XS_UTIL_get_nai();
  
  // Get content
  SPVM_NAI_OBJECT* array = SPVM_XS_UTIL_get_array(sv_array);
  
  int32_t length = nai->get_array_length(nai, array);
  
  int16_t* elements = nai->get_short_array_elements(nai, array);
  
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
  SPVM_NAI* nai = SPVM_XS_UTIL_get_nai();
  
  // Get content
  SPVM_NAI_OBJECT* array = SPVM_XS_UTIL_get_array(sv_array);
  
  int32_t length = nai->get_array_length(nai, array);
  
  int16_t* elements = nai->get_short_array_elements(nai, array);
  
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
  SPVM_NAI* nai = SPVM_XS_UTIL_get_nai();
  
  // Malloc array
  SPVM_NAI_OBJECT* array =  nai->new_int_array(nai, length);

  // Increment reference count
  nai->inc_ref_count(nai, array);
  
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
  AV* av_nums = (AV*)SvRV(sv_nums);

  // Set API
  SPVM_NAI* nai = SPVM_XS_UTIL_get_nai();
  
  // Get content
  SPVM_NAI_OBJECT* array = SPVM_XS_UTIL_get_array(sv_array);
  
  int32_t length = nai->get_array_length(nai, array);
  
  int32_t* elements = nai->get_int_array_elements(nai, array);
  
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
  SPVM_NAI* nai = SPVM_XS_UTIL_get_nai();
  
  // Get content
  SPVM_NAI_OBJECT* array = SPVM_XS_UTIL_get_array(sv_array);
  
  int32_t length = nai->get_array_length(nai, array);
  
  int32_t* elements = nai->get_int_array_elements(nai, array);
  
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
  SPVM_NAI* nai = SPVM_XS_UTIL_get_nai();
  
  // Malloc array
  SPVM_NAI_OBJECT* array =  nai->new_long_array(nai, length);
  
  // Increment reference count
  nai->inc_ref_count(nai, array);
  
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
  AV* av_nums = (AV*)SvRV(sv_nums);

  // Set API
  SPVM_NAI* nai = SPVM_XS_UTIL_get_nai();
  
  // Get content
  SPVM_NAI_OBJECT* array = SPVM_XS_UTIL_get_array(sv_array);
  
  int32_t length = nai->get_array_length(nai, array);
  
  int64_t* elements = nai->get_long_array_elements(nai, array);
  
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
  SPVM_NAI* nai = SPVM_XS_UTIL_get_nai();
  
  // Get content
  SPVM_NAI_OBJECT* array = SPVM_XS_UTIL_get_array(sv_array);
  
  int32_t length = nai->get_array_length(nai, array);
  
  int64_t* elements = nai->get_long_array_elements(nai, array);
  
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
  SPVM_NAI* nai = SPVM_XS_UTIL_get_nai();
  
  // Malloc array
  SPVM_NAI_OBJECT* array =  nai->new_float_array(nai, length);
  
  // Increment reference count
  nai->inc_ref_count(nai, array);
  
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
  AV* av_nums = (AV*)SvRV(sv_nums);

  // Set API
  SPVM_NAI* nai = SPVM_XS_UTIL_get_nai();
  
  // Get content
  SPVM_NAI_OBJECT* array = SPVM_XS_UTIL_get_array(sv_array);
  
  int32_t length = nai->get_array_length(nai, array);
  
  float* elements = nai->get_float_array_elements(nai, array);
  
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
  SPVM_NAI* nai = SPVM_XS_UTIL_get_nai();
  
  // Get content
  SPVM_NAI_OBJECT* array = SPVM_XS_UTIL_get_array(sv_array);
  
  int32_t length = nai->get_array_length(nai, array);
  
  float* elements = nai->get_float_array_elements(nai, array);
  
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
  SPVM_NAI* nai = SPVM_XS_UTIL_get_nai();
  
  // Malloc array
  SPVM_NAI_OBJECT* array =  nai->new_double_array(nai, length);
  
  // Increment reference count
  nai->inc_ref_count(nai, array);
  
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
  AV* av_nums = (AV*)SvRV(sv_nums);

  // Set API
  SPVM_NAI* nai = SPVM_XS_UTIL_get_nai();
  
  // Get content
  SPVM_NAI_OBJECT* array = SPVM_XS_UTIL_get_array(sv_array);
  
  int32_t length = nai->get_array_length(nai, array);
  
  double* elements = nai->get_double_array_elements(nai, array);
  
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
  SPVM_NAI* nai = SPVM_XS_UTIL_get_nai();
  
  // Get content
  SPVM_NAI_OBJECT* array = SPVM_XS_UTIL_get_array(sv_array);
  
  int32_t length = nai->get_array_length(nai, array);
  
  double* elements = nai->get_double_array_elements(nai, array);
  
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
  SPVM_NAI* nai = SPVM_XS_UTIL_get_nai();
  
  // Malloc array
  SPVM_NAI_OBJECT* array =  nai->new_byte_array(nai, length);
  
  // Increment reference count
  nai->inc_ref_count(nai, array);
  
  const char* string = SvPV_nolen(sv_string);
  int8_t* elements = nai->get_byte_array_elements(nai, array);
  memcpy(elements, string, length);
  
  // New sv array
  SV* sv_array = SPVM_XS_UTIL_new_sv_string(array);
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

MODULE = SPVM::Array::Object		PACKAGE = SPVM::Array::Object

SV*
new(...)
  PPCODE:
{
  SV* sv_class = ST(0);
  SV* sv_type_name = ST(1);
  SV* sv_length = ST(2);
  
  int32_t length = (int32_t)SvIV(sv_length);
  
  // Set API
  SPVM_NAI* nai = SPVM_XS_UTIL_get_nai();
  
  // Malloc array
  SPVM_NAI_OBJECT* array =  nai->new_object_array(nai, length);
  
  // Fix type name(int[] -> int[][]);
  sv_catpv(sv_type_name, "[]");
  
  // Type id
  const char* type_name = SvPV_nolen(sv_type_name);
  int32_t type_id = SPVM_XS_UTIL_get_type_id(type_name);
  if (type_id < 0) {
    croak("Unknown type %s. Type must be used in SPVM module at least one(SPVM::Array::Object::new())", type_name);
  }
  if (type_id >= SPVM_TYPE_C_ID_BYTE && type_id <= SPVM_TYPE_C_ID_DOUBLE) {
    croak("Type is not object array %s(SPVM::Array::Object::new())", type_name);
  }
  
  // Increment reference count
  nai->inc_ref_count(nai, array);
  
  // New sv array
  SV* sv_array = SPVM_XS_UTIL_new_sv_object_array(type_id, array);
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
set(...)
  PPCODE:
{
  SV* sv_array = ST(0);
  SV* sv_index = ST(1);
  SV* sv_object = ST(2);
  
  // Set API
  SPVM_NAI* nai = SPVM_XS_UTIL_get_nai();
  
  // Get array
  SPVM_NAI_OBJECT* array = SPVM_XS_UTIL_get_array(sv_array);
  
  // Array type id
  int32_t array_type_id = SPVM_XS_UTIL_get_sv_object_type_id(sv_array);
  
  // Array type name
  const char* array_type_name = SPVM_XS_UTIL_get_type_name(array_type_id);
  
  // Object type id
  int32_t object_type_id = SPVM_XS_UTIL_get_sv_object_type_id(sv_object);
  
  // Object type name
  const char* object_type_name = SPVM_XS_UTIL_get_type_name(object_type_id);
  
  if (strncmp(array_type_name, object_type_name, strlen(array_type_name - 2)) != 0) {
    croak("Invalid type %s is set to object array %s(SPVM::Array::Object::set())", object_type_name, array_type_name);
  }
  
  // Get object
  SPVM_NAI_OBJECT* object = SPVM_XS_UTIL_get_object(sv_object);
  
  // Index
  int32_t index = (int32_t)SvIV(sv_index);
  
  nai->set_object_array_element(nai, array, index, (SPVM_NAI_OBJECT*)object);
  
  XSRETURN(0);
}

SV*
get(...)
  PPCODE:
{
  SV* sv_array = ST(0);
  SV* sv_index = ST(1);
  
  // Set API
  SPVM_NAI* nai = SPVM_XS_UTIL_get_nai();
  
  // Get array
  SPVM_NAI_OBJECT* array = SPVM_XS_UTIL_get_array(sv_array);
  
  // Array type id
  int32_t array_type_id = SPVM_XS_UTIL_get_sv_object_type_id(sv_array);
  
  // Array type name
  const char* array_type_name = SPVM_XS_UTIL_get_type_name(array_type_id);
  
  // Element type name sv
  SV* sv_element_type_name = sv_2mortal(newSVpv(array_type_name, strlen(array_type_name) - 2));
  const char* element_type_name = SvPV_nolen(sv_element_type_name);
  
  // Element type id
  int32_t element_type_id = SPVM_XS_UTIL_get_type_id(element_type_name);

  // Index
  int32_t index = (int32_t)SvIV(sv_index);
  SPVM_NAI_OBJECT* base_object = nai->get_object_array_element(nai, array, index);
  if (base_object != NULL) {
    nai->inc_ref_count(nai, base_object);
  }
  
  SV* sv_base_object;
  switch (element_type_id) {
    case SPVM_TYPE_C_ID_BYTE_ARRAY :
      sv_base_object = SPVM_XS_UTIL_new_sv_byte_array((SPVM_NAI_OBJECT*)base_object);
      break;
    case SPVM_TYPE_C_ID_SHORT_ARRAY :
      sv_base_object = SPVM_XS_UTIL_new_sv_short_array((SPVM_NAI_OBJECT*)base_object);
      break;
    case SPVM_TYPE_C_ID_INT_ARRAY :
      sv_base_object = SPVM_XS_UTIL_new_sv_int_array((SPVM_NAI_OBJECT*)base_object);
      break;
    case SPVM_TYPE_C_ID_LONG_ARRAY :
      sv_base_object = SPVM_XS_UTIL_new_sv_long_array((SPVM_NAI_OBJECT*)base_object);
      break;
    case SPVM_TYPE_C_ID_FLOAT_ARRAY :
      sv_base_object = SPVM_XS_UTIL_new_sv_float_array((SPVM_NAI_OBJECT*)base_object);
      break;
    case SPVM_TYPE_C_ID_DOUBLE_ARRAY :
      sv_base_object = SPVM_XS_UTIL_new_sv_double_array((SPVM_NAI_OBJECT*)base_object);
      break;
    case SPVM_TYPE_C_ID_STRING :
      sv_base_object = SPVM_XS_UTIL_new_sv_string((SPVM_NAI_OBJECT*)base_object);
      break;
    default : {
      const char* return_type_name = SPVM_XS_UTIL_get_type_name(element_type_id);
      int32_t element_type_name_length = strlen(element_type_name);
      if (element_type_name[element_type_name_length - 1] == ']') {
        sv_base_object = SPVM_XS_UTIL_new_sv_object_array(element_type_id, (SPVM_NAI_OBJECT*)base_object);
      }
      else {
        sv_base_object = SPVM_XS_UTIL_new_sv_object(element_type_id, (SPVM_NAI_OBJECT*)base_object);
      }
    }
  }
  
  XPUSHs(sv_base_object);
  
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
  
  // Debug model
  HV* hv_env = get_hv("ENV", 0);
  SV** sv_debug_ptr = hv_fetch(hv_env, "SPVM_DEBUG", strlen("SPVM_DEBUG"), 0);
  SV* sv_debug = sv_debug_ptr ? *sv_debug_ptr : &PL_sv_undef;
  if (SvTRUE(sv_debug)) {
    compiler->debug = 1;
  }
  
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
  
  // id, arg_type_ids, return_type_id
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
          AV* av_arg_type_ids = (AV*)sv_2mortal((SV*)newAV());
          SPVM_DYNAMIC_ARRAY* op_args = sub->op_args;
          {
            int32_t arg_index;
            for (arg_index = 0; arg_index < op_args->length; arg_index++) {
              SPVM_OP* op_arg = SPVM_DYNAMIC_ARRAY_fetch(op_args, arg_index);
              SPVM_OP* op_arg_type = op_arg->uv.my_var->op_type;
              SPVM_TYPE* arg_type = op_arg_type->uv.type;
              int32_t arg_type_id = arg_type->id;
              
              SV* sv_arg_type_id = sv_2mortal(newSViv(arg_type_id));
              av_push(av_arg_type_ids, SvREFCNT_inc(sv_arg_type_id));
            }
          }
          SV* sv_arg_type_ids = sv_2mortal(newRV_inc((SV*)av_arg_type_ids));
          hv_store(hv_sub_info, "arg_type_ids", strlen("arg_type_ids"), SvREFCNT_inc(sv_arg_type_ids), 0);
          
          // Return type id
          SPVM_OP* op_return_type = sub->op_return_type;
          SPVM_TYPE* return_type = SPVM_OP_get_type(compiler, op_return_type);
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
      
      // Type name
      const char* type_name = type->name;
      int32_t type_id = type->id;
      SV* sv_type_id = sv_2mortal(newSViv(type_id));
      
      HV* hv_type_info = (HV*)sv_2mortal((SV*)newHV());
      hv_store(hv_type_info, "id", strlen("id"), SvREFCNT_inc(sv_type_id), 0);
      hv_store(hv_type_info, "type_id", strlen("type_id"), SvREFCNT_inc(sv_type_id), 0);
      SV* sv_type_info = sv_2mortal(newRV_inc((SV*)hv_type_info));
      
      hv_store(hv_type_symtable, type_name, strlen(type_name), SvREFCNT_inc(sv_type_info), 0);
    }
  }
  
  XSRETURN(0);
}

SV*
build_type_names(...)
  PPCODE:
{
  // Get compiler
  SPVM_COMPILER* compiler = SPVM_XS_INTERNAL_UTIL_get_compiler();
  
  // Subroutine information
  AV* av_type_names = get_av("SPVM::TYPE_NAMES", 0);
  
  SPVM_DYNAMIC_ARRAY* types = compiler->types;
  {
    int32_t type_id;
    for (type_id = 0; type_id < types->length; type_id++) {
      SPVM_TYPE* type = SPVM_DYNAMIC_ARRAY_fetch(types, type_id);
      
      const char* type_name = type->name;
      SV* sv_type_name = sv_2mortal(newSVpv(type_name, 0));
      int32_t type_id = type->id;
      
      av_store(av_type_names, type_id, SvREFCNT_inc(sv_type_name));
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
      // Package name
      SPVM_OP* op_package = SPVM_DYNAMIC_ARRAY_fetch(op_packages, package_index);
      SPVM_PACKAGE* package = op_package->uv.package;
      const char* package_name = package->op_name->uv.name;
      
      // Package id
      int32_t package_id = package->constant_pool_index;
      SV* sv_package_id = sv_2mortal(newSViv(package_id));
      
      // Type id
      HV* hv_type_symtable = get_hv("SPVM::TYPE_SYMTABLE", 0);
      SV** sv_type_info_ptr = hv_fetch(hv_type_symtable, package_name, strlen(package_name), 0);
      SV* sv_type_info = *sv_type_info_ptr;
      HV* hv_type_info = (HV*)SvRV(sv_type_info);
      SV** sv_type_id_ptr = hv_fetch(hv_type_info, "id", strlen("id"), 0);
      SV* sv_type_id = *sv_type_id_ptr;
      
      // Package information
      HV* hv_package_info = (HV*)sv_2mortal((SV*)newHV());
      hv_store(hv_package_info, "id", strlen("id"), SvREFCNT_inc(sv_package_id), 0);
      hv_store(hv_package_info, "type_id", strlen("type_id"), SvREFCNT_inc(sv_type_id), 0);
      SV* sv_package_info = sv_2mortal(newRV_inc((SV*)hv_package_info));
      
      // Add package information
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
          
          // Field type id
          int32_t field_type_id = field->op_type->uv.type->id;
          SV* sv_field_type_id = sv_2mortal(newSViv(field_type_id));
          
          // Field id
          int32_t field_id = field->index;
          SV* sv_field_id = sv_2mortal(newSViv(field_id));
          
          HV* hv_field_info = (HV*)sv_2mortal((SV*)newHV());
          hv_store(hv_field_info, "id", strlen("id"), SvREFCNT_inc(sv_field_id), 0);
          hv_store(hv_field_info, "type_id", strlen("type_id"), SvREFCNT_inc(sv_field_type_id), 0);
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
  SPVM_NAI* nai = runtime->nai;
  size_t iv_nai = PTR2IV(nai);
  SV* sviv_nai = sv_2mortal(newSViv(iv_nai));
  SV* sv_nai = sv_2mortal(newRV_inc(sviv_nai));
  sv_setsv(get_sv("SPVM::API", 0), sv_nai);
  
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
  SV* sv_sub_info = *sv_sub_info_ptr;
  HV* hv_sub_info = (HV*)SvRV(sv_sub_info);
  
  // Subroutine id
  SV** sv_sub_id_ptr = hv_fetch(hv_sub_info, "id", strlen("id"), 0);
  SV* sv_sub_id = *sv_sub_id_ptr;
  int32_t sub_id = (int32_t)SvIV(sv_sub_id);
  
  // Argument type ids
  SV** sv_arg_type_ids_ptr = hv_fetch(hv_sub_info, "arg_type_ids", strlen("arg_type_ids"), 0);
  SV* sv_arg_type_ids = *sv_arg_type_ids_ptr;
  AV* av_arg_type_ids = (AV*)SvRV(sv_arg_type_ids);
  int32_t args_length = av_len(av_arg_type_ids) + 1;
  
  // Return type id
  SV** sv_return_type_id_ptr = hv_fetch(hv_sub_info, "return_type_id", strlen("return_type_id"), 0);
  SV* sv_return_type_id = *sv_return_type_id_ptr;
  int32_t return_type_id = SvIV(sv_return_type_id);
  
  // Get API
  SV* sv_nai = get_sv("SPVM::API", 0);
  SV* sviv_nai = SvROK(sv_nai) ? SvRV(sv_nai) : sv_nai;
  size_t iv_nai = SvIV(sviv_nai);
  SPVM_NAI* nai = INT2PTR(SPVM_NAI*, iv_nai);
  
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
         
          HV* hv_base_object = (HV*)SvRV(sv_base_object);
          
          SV** sv_base_object_type_id_ptr = hv_fetch(hv_base_object, "type_id", strlen("type_id"), 0);
          SV* sv_base_object_type_id = *sv_base_object_type_id_ptr;
          int32_t base_object_type_id = SvIV(sv_base_object_type_id);
          
          if (base_object_type_id != arg_type_id) {
            const char* base_object_type_name = SPVM_XS_UTIL_get_type_name(base_object_type_id);
            const char* arg_type_name = SPVM_XS_UTIL_get_type_name(arg_type_id);
            
            croak("Argument base_object type need %s, but %s", arg_type_name, base_object_type_name);
          }
          
          // Get content
          SV** sv_content_ptr = hv_fetch(hv_base_object, "content", strlen("content"), 0);
          SV* sv_content = sv_content_ptr ? *sv_content_ptr : &PL_sv_undef;
          SV* sviv_content = SvRV(sv_content);
          size_t iv_content = SvIV(sviv_content);
          SPVM_NAI_OBJECT* base_object = INT2PTR(SPVM_NAI_OBJECT*, iv_content);
          
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
  
  nai->set_exception(nai, NULL);
  
  switch (return_type_id) {
    case SPVM_TYPE_C_ID_VOID:  {
      nai->call_void_sub(nai, sub_id, call_sub_args);
      SPVM_NAI_OBJECT* exception = nai->get_exception(nai);
      if (exception) {
        int32_t length = nai->get_array_length(nai, exception);
        int8_t* exception_bytes = nai->get_byte_array_elements(nai, exception);
        SV* sv_exception = newSVpv(exception_bytes, length);
        croak("%s", SvPV_nolen(sv_exception));
      }
      XSRETURN(0);
      break;
    }
    case SPVM_TYPE_C_ID_BYTE: {
      int8_t return_value = nai->call_byte_sub(nai, sub_id, call_sub_args);
      SPVM_NAI_OBJECT* exception = nai->get_exception(nai);
      if (exception) {
        int32_t length = nai->get_array_length(nai, exception);
        int8_t* exception_bytes = nai->get_byte_array_elements(nai, exception);
        SV* sv_exception = newSVpv(exception_bytes, length);
        croak("%s", SvPV_nolen(sv_exception));
      }
      SV* sv_return_value = sv_2mortal(newSViv(return_value));
      XPUSHs(sv_return_value);
      XSRETURN(1);
      break;
    }
    case SPVM_TYPE_C_ID_SHORT: {
      int16_t return_value = nai->call_short_sub(nai, sub_id, call_sub_args);
      SPVM_NAI_OBJECT* exception = nai->get_exception(nai);
      if (exception) {
        int32_t length = nai->get_array_length(nai, exception);
        int8_t* exception_bytes = nai->get_byte_array_elements(nai, exception);
        SV* sv_exception = newSVpv(exception_bytes, length);
        croak("%s", SvPV_nolen(sv_exception));
      }
      SV* sv_return_value = sv_2mortal(newSViv(return_value));
      XPUSHs(sv_return_value);
      XSRETURN(1);
      break;
    }
    case SPVM_TYPE_C_ID_INT: {
      int32_t return_value = nai->call_int_sub(nai, sub_id, call_sub_args);
      SPVM_NAI_OBJECT* exception = nai->get_exception(nai);
      if (exception) {
        int32_t length = nai->get_array_length(nai, exception);
        int8_t* exception_bytes = nai->get_byte_array_elements(nai, exception);
        SV* sv_exception = newSVpv(exception_bytes, length);
        croak("%s", SvPV_nolen(sv_exception));
      }
      SV* sv_return_value = sv_2mortal(newSViv(return_value));
      XPUSHs(sv_return_value);
      XSRETURN(1);
      break;
    }
    case SPVM_TYPE_C_ID_LONG: {
      int64_t return_value = nai->call_long_sub(nai, sub_id, call_sub_args);
      SPVM_NAI_OBJECT* exception = nai->get_exception(nai);
      if (exception) {
        int32_t length = nai->get_array_length(nai, exception);
        int8_t* exception_bytes = nai->get_byte_array_elements(nai, exception);
        SV* sv_exception = newSVpv(exception_bytes, length);
        croak("%s", SvPV_nolen(sv_exception));
      }
      SV* sv_return_value = sv_2mortal(newSViv(return_value));
      XPUSHs(sv_return_value);
      XSRETURN(1);
      break;
    }
    case SPVM_TYPE_C_ID_FLOAT: {
      float return_value = nai->call_float_sub(nai, sub_id, call_sub_args);
      SPVM_NAI_OBJECT* exception = nai->get_exception(nai);
      if (exception) {
        int32_t length = nai->get_array_length(nai, exception);
        int8_t* exception_bytes = nai->get_byte_array_elements(nai, exception);
        SV* sv_exception = newSVpv(exception_bytes, length);
        croak("%s", SvPV_nolen(sv_exception));
      }
      SV* sv_return_value = sv_2mortal(newSVnv(return_value));
      XPUSHs(sv_return_value);
      XSRETURN(1);
      break;
    }
    case SPVM_TYPE_C_ID_DOUBLE: {
      double return_value = nai->call_double_sub(nai, sub_id, call_sub_args);
      SPVM_NAI_OBJECT* exception = nai->get_exception(nai);
      if (exception) {
        int32_t length = nai->get_array_length(nai, exception);
        int8_t* exception_bytes = nai->get_byte_array_elements(nai, exception);
        SV* sv_exception = newSVpv(exception_bytes, length);
        croak("%s", SvPV_nolen(sv_exception));
      }
      SV* sv_return_value = sv_2mortal(newSVnv(return_value));
      XPUSHs(sv_return_value);
      XSRETURN(1);
      break;
    }
    default: {
      SPVM_NAI_OBJECT* return_value = nai->call_object_sub(nai, sub_id, call_sub_args);
      SPVM_NAI_OBJECT* exception = nai->get_exception(nai);
      if (exception) {
        int32_t length = nai->get_array_length(nai, exception);
        int8_t* exception_bytes = nai->get_byte_array_elements(nai, exception);
        SV* sv_exception = newSVpv(exception_bytes, length);
        croak("%s", SvPV_nolen(sv_exception));
      }
      
      SV* sv_return_value = NULL;
      if (return_value != NULL) {
        nai->inc_ref_count(nai, return_value);
        
        switch(return_type_id) {
          case SPVM_TYPE_C_ID_BYTE_ARRAY :
            sv_return_value = SPVM_XS_UTIL_new_sv_byte_array((SPVM_NAI_OBJECT*)return_value);
            break;
          case SPVM_TYPE_C_ID_SHORT_ARRAY :
            sv_return_value = SPVM_XS_UTIL_new_sv_short_array((SPVM_NAI_OBJECT*)return_value);
            break;
          case SPVM_TYPE_C_ID_INT_ARRAY :
            sv_return_value = SPVM_XS_UTIL_new_sv_int_array((SPVM_NAI_OBJECT*)return_value);
            break;
          case SPVM_TYPE_C_ID_LONG_ARRAY :
            sv_return_value = SPVM_XS_UTIL_new_sv_long_array((SPVM_NAI_OBJECT*)return_value);
            break;
          case SPVM_TYPE_C_ID_FLOAT_ARRAY :
            sv_return_value = SPVM_XS_UTIL_new_sv_float_array((SPVM_NAI_OBJECT*)return_value);
            break;
          case SPVM_TYPE_C_ID_DOUBLE_ARRAY :
            sv_return_value = SPVM_XS_UTIL_new_sv_double_array((SPVM_NAI_OBJECT*)return_value);
            break;
          case SPVM_TYPE_C_ID_STRING :
            sv_return_value = SPVM_XS_UTIL_new_sv_string((SPVM_NAI_OBJECT*)return_value);
            break;
          default : {
            const char* return_type_name = SPVM_XS_UTIL_get_type_name(return_type_id);
            int32_t type_name_length = strlen(return_type_name);
            if (return_type_name[type_name_length - 1] == ']') {
              sv_return_value = SPVM_XS_UTIL_new_sv_object_array(return_type_id, (SPVM_NAI_OBJECT*)return_value);
            }
            else {
              sv_return_value = SPVM_XS_UTIL_new_sv_object(return_type_id, (SPVM_NAI_OBJECT*)return_value);
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
