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
#include "spvm_field_info.h"
#include "spvm_constant_pool.h"
#include "spvm_constant_pool_sub.h"
#include "spvm_constant_pool_package.h"
#include "spvm_constant_pool_field_info.h"
#include "spvm_constant_pool_type.h"
#include "spvm_object.h"
#include "spvm_api.h"

static SPVM_API_VALUE call_sub_args[255];

SPVM_API* SPVM_XS_UTIL_get_api() {
  
  SV* sv_api = get_sv("SPVM::API", 0);
  
  SPVM_API* api = (SPVM_API*)SvIV(SvRV(sv_api));
  
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

MODULE = SPVM::BaseObject		PACKAGE = SPVM::BaseObject

SV*
DESTROY(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_object = ST(0);
  
  assert(SvOK(sv_object));
  
  // API
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
  (void)RETVAL;
  
  SV* sv_class = ST(0);
  (void)sv_class;
  
  SV* sv_package_name = ST(1);
  
  // API
  SPVM_API* api = SPVM_XS_UTIL_get_api();
  
  if (!SvOK(sv_package_name)) {
    croak("Type must be specified(SPVM::Object::new_object)");
  }
  
  const char* package_name = SvPV_nolen(sv_package_name);
  
  int32_t type_id = api->get_type_id(api, package_name);
  
  if (type_id <= 0) {
    croak("Unkown package \"%s\"(SPVM::Object::new_object", package_name);
  }
  
  // New array
  SPVM_API_OBJECT* object =  api->new_object(api, type_id);
  
  // Increment
  api->inc_ref_count(api, object);

  // New sv object
  SV* sv_object = SPVM_XS_UTIL_new_sv_object(object, "SPVM::Object");
  
  XPUSHs(sv_object);
  XSRETURN(1);
}

SV*
set(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_object = ST(0);
  SV* sv_field_name = ST(1);
  SV* sv_value = ST(2);
  
  // Set API
  SPVM_API* api = SPVM_XS_UTIL_get_api();
  
  // Runtime
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->get_runtime(api);
  
  // Get content
  SPVM_OBJECT* object = SPVM_XS_UTIL_get_object(sv_object);
  
  int32_t package_type_id = object->type_id;
  
  SPVM_CONSTANT_POOL_TYPE* constant_pool_package_type = (SPVM_CONSTANT_POOL_TYPE*)&runtime->constant_pool[package_type_id];
  
  // Package name
  const char* package_name = (char*)&runtime->constant_pool[constant_pool_package_type->name_id + 1];
  
  // Field type
  const char* field_name = SvPV_nolen(sv_field_name);
  SPVM_HASH* field_name_symtable = SPVM_HASH_search(runtime->field_info_id_symtable, package_name, strlen(package_name));
  int32_t filed_info_id = (int32_t)(intptr_t)SPVM_HASH_search(field_name_symtable, field_name, strlen(field_name));
  SPVM_CONSTANT_POOL_FIELD_INFO* constant_pool_field_info = (SPVM_CONSTANT_POOL_FIELD_INFO*)&runtime->constant_pool[filed_info_id];
  int32_t field_type_id =constant_pool_field_info->type_id;
  SPVM_CONSTANT_POOL_TYPE* constant_pool_field_type = (SPVM_CONSTANT_POOL_TYPE*)&runtime->constant_pool[field_type_id];
  
  int32_t field_type_code = constant_pool_field_type->code;
  
  // Field id
  int32_t field_id = api->get_field_id(api, object, field_name);
  if (!field_id) {
    croak("Can't find %s \"%s\" field(SPVM::Object::set)", package_name, field_name);
  }
  
  switch (field_type_code) {
    case SPVM_TYPE_C_CODE_BYTE : {
      int8_t value = (int8_t)SvIV(sv_value);
      api->set_byte_field(api, object, field_id, value);
      break;
    }
    case  SPVM_TYPE_C_CODE_SHORT : {
      int16_t value = (int16_t)SvIV(sv_value);
      api->set_short_field(api, object, field_id, value);
      break;
    }
    case SPVM_TYPE_C_CODE_INT : {
      int32_t value = (int32_t)SvIV(sv_value);
      api->set_int_field(api, object, field_id, value);
      break;
    }
    case SPVM_TYPE_C_CODE_LONG : {
      int64_t value = (int64_t)SvIV(sv_value);
      api->set_long_field(api, object, field_id, value);
      break;
    }
    case SPVM_TYPE_C_CODE_FLOAT : {
      float value = (float)SvNV(sv_value);
      api->set_float_field(api, object, field_id, value);
      break;
    }
    case SPVM_TYPE_C_CODE_DOUBLE : {
      double value = (double)SvNV(sv_value);
      api->set_double_field(api, object, field_id, value);
      break;
    }
    default : {
      if (!sv_derived_from(sv_value, "SPVM::BaseObject")) {
        const char* field_type_name = (char*)&runtime->constant_pool[constant_pool_field_type->name_id + 1];
        croak("Can't set numeric value to \"%s\" field", field_type_name);
      }
      
      SPVM_OBJECT* value = SPVM_XS_UTIL_get_object(sv_value);
      int32_t value_type_id = value->type_id;
      
      SPVM_CONSTANT_POOL_TYPE* constant_pool_value_type = (SPVM_CONSTANT_POOL_TYPE*)&runtime->constant_pool[value_type_id];
      
      if (value_type_id != field_type_id
      ) {
        const char* field_type_name = (char*)&runtime->constant_pool[constant_pool_field_type->name_id + 1];
        const char* value_type_name = (char*)&runtime->constant_pool[constant_pool_value_type->name_id + 1];
        croak("Can't set \"%s\" value to \"%s\" field", value_type_name, field_type_name);
      }
      
      SPVM_API_OBJECT* set_object = SPVM_XS_UTIL_get_object(sv_value);
      
      api->set_object_field(api, object, field_id, set_object);
    }
  }
  
  XSRETURN(0);
}

SV*
get(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_object = ST(0);
  SV* sv_field_name = ST(1);
  
  // Set API
  SPVM_API* api = SPVM_XS_UTIL_get_api();
  
  // Runtime
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->get_runtime(api);
  
  // Get content
  SPVM_OBJECT* object = SPVM_XS_UTIL_get_object(sv_object);
  
  // Package type id
  int32_t package_type_id = object->type_id;
  
  // Package type
  SPVM_CONSTANT_POOL_TYPE* constant_pool_package_type = (SPVM_CONSTANT_POOL_TYPE*)&runtime->constant_pool[package_type_id];
  
  // Package name
  const char* package_name = (char*)&runtime->constant_pool[constant_pool_package_type->name_id + 1];
  
  // Field name
  const char* field_name = SvPV_nolen(sv_field_name);
  
  // Field type
  SPVM_HASH* field_name_symtable = SPVM_HASH_search(runtime->field_info_id_symtable, package_name, strlen(package_name));
  int32_t filed_info_id = (int32_t)(intptr_t)SPVM_HASH_search(field_name_symtable, field_name, strlen(field_name));
  SPVM_CONSTANT_POOL_FIELD_INFO* constant_pool_field_info = (SPVM_CONSTANT_POOL_FIELD_INFO*)&runtime->constant_pool[filed_info_id];
  int32_t field_type_id =constant_pool_field_info->type_id;
  SPVM_CONSTANT_POOL_TYPE* constant_pool_field_type = (SPVM_CONSTANT_POOL_TYPE*)&runtime->constant_pool[field_type_id];
  
  int32_t field_type_code = constant_pool_field_type->code;
  
  // Field id
  int32_t field_id = api->get_field_id(api, object, field_name);
  
  if (!field_id) {
    croak("Can't find %s \"%s\" field(SPVM::Object::set)", package_name, field_name);
  }
  
  switch (field_type_code) {
    case SPVM_TYPE_C_CODE_BYTE : {
      int8_t value = api->get_byte_field(api, object, field_id);
      SV* sv_value = sv_2mortal(newSViv(value));
      XPUSHs(sv_value);
      break;
    }
    case SPVM_TYPE_C_CODE_SHORT : {
      int16_t value = api->get_short_field(api, object, field_id);
      SV* sv_value = sv_2mortal(newSViv(value));
      XPUSHs(sv_value);
      break;
    }
    case SPVM_TYPE_C_CODE_INT : {
      int32_t value = api->get_int_field(api, object, field_id);
      SV* sv_value = sv_2mortal(newSViv(value));
      XPUSHs(sv_value);
      break;
    }
    case SPVM_TYPE_C_CODE_LONG : {
      int64_t value = api->get_long_field(api, object, field_id);
      SV* sv_value = sv_2mortal(newSViv(value));
      XPUSHs(sv_value);
      break;
    }
    case SPVM_TYPE_C_CODE_FLOAT : {
      float value = api->get_float_field(api, object, field_id);
      SV* sv_value = sv_2mortal(newSVnv(value));
      XPUSHs(sv_value);
      break;
    }
    case SPVM_TYPE_C_CODE_DOUBLE : {
      double value = api->get_double_field(api, object, field_id);
      SV* sv_value = sv_2mortal(newSVnv(value));
      XPUSHs(sv_value);
      break;
    }
    default : {
      SPVM_API_OBJECT* value = api->get_object_field(api, object, field_id);
      
      if (value != NULL) {
        api->inc_ref_count(api, value);
      }
      
      switch (field_type_code) {
        case SPVM_TYPE_C_CODE_BYTE_ARRAY : {
          SV* sv_array = SPVM_XS_UTIL_new_sv_object(value, "SPVM::Array::Byte");
          XPUSHs(sv_array);
          break;
        }
        case SPVM_TYPE_C_CODE_SHORT_ARRAY : {
          SV* sv_array = SPVM_XS_UTIL_new_sv_object(value, "SPVM::Array::Short");
          XPUSHs(sv_array);
          break;
        }
        case SPVM_TYPE_C_CODE_INT_ARRAY : {
          SV* sv_array = SPVM_XS_UTIL_new_sv_object(value, "SPVM::Array::Int");
          XPUSHs(sv_array);
          break;
        }
        case SPVM_TYPE_C_CODE_LONG_ARRAY : {
          SV* sv_array = SPVM_XS_UTIL_new_sv_object(value, "SPVM::Array::Long");
          XPUSHs(sv_array);
          break;
        }
        case SPVM_TYPE_C_CODE_FLOAT_ARRAY : {
          SV* sv_array = SPVM_XS_UTIL_new_sv_object(value, "SPVM::Array::Float");
          XPUSHs(sv_array);
          break;
        }
        case SPVM_TYPE_C_CODE_DOUBLE_ARRAY : {
          SV* sv_array = SPVM_XS_UTIL_new_sv_object(value, "SPVM::Array::Double");
          XPUSHs(sv_array);
          break;
        }
        default : {
          const char* field_type_name =  (char*)&runtime->constant_pool[constant_pool_field_type->name_id + 1];
          
          int32_t field_type_name_length = strlen(field_type_name);
          
          if (field_type_name[field_type_name_length - 1] == ']') {
            SV* sv_array = SPVM_XS_UTIL_new_sv_object(value, "SPVM::Array::Object");
            XPUSHs(sv_array);
          }
          else {
            SV* sv_object = SPVM_XS_UTIL_new_sv_object(value, "SPVM::Object");
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
  (void)RETVAL;
  
  SV* sv_class = ST(0);
  (void)sv_class;
  
  SV* sv_length = ST(1);
  
  int32_t length = (int32_t)SvIV(sv_length);
  
  // Set API
  SPVM_API* api = SPVM_XS_UTIL_get_api();
  
  // New array
  SPVM_API_OBJECT* array =  api->new_byte_array(api, length);
  
  // Increment reference count
  api->inc_ref_count(api, array);
  
  // New sv array
  SV* sv_byte_array = SPVM_XS_UTIL_new_sv_object(array, "SPVM::Array::Byte");
  
  XPUSHs(sv_byte_array);
  XSRETURN(1);
}

SV*
set_elements(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_array = ST(0);
  SV* sv_nums = ST(1);
  AV* av_nums = (AV*)SvRV(sv_nums);

  // Set API
  SPVM_API* api = SPVM_XS_UTIL_get_api();
  
  // Get content
  SPVM_API_OBJECT* array = SPVM_XS_UTIL_get_object(sv_array);
  
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
  (void)RETVAL;
  
  SV* sv_array = ST(0);

  // Set API
  SPVM_API* api = SPVM_XS_UTIL_get_api();
  
  // Get content
  SPVM_API_OBJECT* array = SPVM_XS_UTIL_get_object(sv_array);
  
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

SV*
get_data(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_spvm_string = ST(0);

  // Get SPVM string
  SPVM_API_OBJECT* spvm_string = SPVM_XS_UTIL_get_object(sv_spvm_string);
  
  // Set API
  SPVM_API* api = SPVM_XS_UTIL_get_api();
  
  // Get string bytes
  const char* string_bytes = (const char*)api->get_byte_array_elements(api, spvm_string);
  
  // Get string length
  int32_t spvm_string_length = api->get_array_length(api, spvm_string);
  
  SV* sv_string = sv_2mortal(newSVpv(string_bytes, spvm_string_length));
  
  XPUSHs(sv_string);
  XSRETURN(1);
}

MODULE = SPVM::Array::Short		PACKAGE = SPVM::Array::Short

SV*
new(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_class = ST(0);
  (void)sv_class;
  
  SV* sv_length = ST(1);
  
  int32_t length = (int32_t)SvIV(sv_length);
  
  // Set API
  SPVM_API* api = SPVM_XS_UTIL_get_api();
  
  // New array
  SPVM_API_OBJECT* array =  api->new_short_array(api, length);
  
  // Increment reference count
  api->inc_ref_count(api, array);
  
  // New sv array
  SV* sv_array = SPVM_XS_UTIL_new_sv_object(array, "SPVM::Array::Short");
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
set_elements(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_array = ST(0);
  SV* sv_nums = ST(1);
  AV* av_nums = (AV*)SvRV(sv_nums);

  // Set API
  SPVM_API* api = SPVM_XS_UTIL_get_api();
  
  // Get content
  SPVM_API_OBJECT* array = SPVM_XS_UTIL_get_object(sv_array);
  
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
  (void)RETVAL;
  
  SV* sv_array = ST(0);

  // Set API
  SPVM_API* api = SPVM_XS_UTIL_get_api();
  
  // Get content
  SPVM_API_OBJECT* array = SPVM_XS_UTIL_get_object(sv_array);
  
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
  (void)RETVAL;
  
  SV* sv_class = ST(0);
  (void)sv_class;
  
  SV* sv_length = ST(1);
  
  int32_t length = (int32_t)SvIV(sv_length);
  
  // Set API
  SPVM_API* api = SPVM_XS_UTIL_get_api();
  
  // New array
  SPVM_API_OBJECT* array =  api->new_int_array(api, length);

  // Increment reference count
  api->inc_ref_count(api, array);
  
  // New sv array
  SV* sv_array = SPVM_XS_UTIL_new_sv_object(array, "SPVM::Array::Int");
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
set_elements(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_array = ST(0);
  SV* sv_nums = ST(1);
  AV* av_nums = (AV*)SvRV(sv_nums);

  // Set API
  SPVM_API* api = SPVM_XS_UTIL_get_api();
  
  // Get content
  SPVM_API_OBJECT* array = SPVM_XS_UTIL_get_object(sv_array);
  
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
  (void)RETVAL;
  
  SV* sv_array = ST(0);

  // Set API
  SPVM_API* api = SPVM_XS_UTIL_get_api();
  
  // Get content
  SPVM_API_OBJECT* array = SPVM_XS_UTIL_get_object(sv_array);
  
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
  (void)RETVAL;
  
  SV* sv_class = ST(0);
  (void)sv_class;
  
  SV* sv_length = ST(1);
  
  int32_t length = (int32_t)SvIV(sv_length);
  
  // Set API
  SPVM_API* api = SPVM_XS_UTIL_get_api();
  
  // New array
  SPVM_API_OBJECT* array =  api->new_long_array(api, length);
  
  // Increment reference count
  api->inc_ref_count(api, array);
  
  // New sv array
  SV* sv_array = SPVM_XS_UTIL_new_sv_object(array, "SPVM::Array::Long");
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
set_elements(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_array = ST(0);
  SV* sv_nums = ST(1);
  AV* av_nums = (AV*)SvRV(sv_nums);

  // Set API
  SPVM_API* api = SPVM_XS_UTIL_get_api();
  
  // Get content
  SPVM_API_OBJECT* array = SPVM_XS_UTIL_get_object(sv_array);
  
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
  (void)RETVAL;
  
  SV* sv_array = ST(0);

  // Set API
  SPVM_API* api = SPVM_XS_UTIL_get_api();
  
  // Get content
  SPVM_API_OBJECT* array = SPVM_XS_UTIL_get_object(sv_array);
  
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
  (void)RETVAL;
  
  SV* sv_class = ST(0);
  (void)sv_class;
  
  SV* sv_length = ST(1);
  
  int32_t length = (int32_t)SvIV(sv_length);
  
  // Set API
  SPVM_API* api = SPVM_XS_UTIL_get_api();
  
  // New array
  SPVM_API_OBJECT* array =  api->new_float_array(api, length);
  
  // Increment reference count
  api->inc_ref_count(api, array);
  
  // New sv array
  SV* sv_array = SPVM_XS_UTIL_new_sv_object(array, "SPVM::Array::Float");
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
set_elements(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_array = ST(0);
  SV* sv_nums = ST(1);
  AV* av_nums = (AV*)SvRV(sv_nums);

  // Set API
  SPVM_API* api = SPVM_XS_UTIL_get_api();
  
  // Get content
  SPVM_API_OBJECT* array = SPVM_XS_UTIL_get_object(sv_array);
  
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
  (void)RETVAL;
  
  SV* sv_array = ST(0);

  // Set API
  SPVM_API* api = SPVM_XS_UTIL_get_api();
  
  // Get content
  SPVM_API_OBJECT* array = SPVM_XS_UTIL_get_object(sv_array);
  
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
  (void)RETVAL;
  
  SV* sv_class = ST(0);
  (void)sv_class;
  
  SV* sv_length = ST(1);
  
  int32_t length = (int32_t)SvIV(sv_length);
  
  // Set API
  SPVM_API* api = SPVM_XS_UTIL_get_api();
  
  // New array
  SPVM_API_OBJECT* array =  api->new_double_array(api, length);
  
  // Increment reference count
  api->inc_ref_count(api, array);
  
  // New sv array
  SV* sv_array = SPVM_XS_UTIL_new_sv_object(array, "SPVM::Array::Double");
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
set_elements(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_array = ST(0);
  SV* sv_nums = ST(1);
  AV* av_nums = (AV*)SvRV(sv_nums);

  // Set API
  SPVM_API* api = SPVM_XS_UTIL_get_api();
  
  // Get content
  SPVM_API_OBJECT* array = SPVM_XS_UTIL_get_object(sv_array);
  
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
  (void)RETVAL;
  
  SV* sv_array = ST(0);

  // Set API
  SPVM_API* api = SPVM_XS_UTIL_get_api();
  
  // Get content
  SPVM_API_OBJECT* array = SPVM_XS_UTIL_get_object(sv_array);
  
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
new_data(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_class = ST(0);
  (void)sv_class;
  
  SV* sv_string = ST(1);
  
  int32_t length = (int32_t)sv_len(sv_string);
  
  const char* string = SvPV_nolen(sv_string);
  
  // Set API
  SPVM_API* api = SPVM_XS_UTIL_get_api();
  
  // New string
  SPVM_API_OBJECT* spvm_string =  api->new_byte_array(api, length);
  
  // Increment reference count
  api->inc_ref_count(api, spvm_string);
  
  char* spvm_string_bytes = (char*)api->get_byte_array_elements(api, spvm_string);
  memcpy(spvm_string_bytes, string, length);
  
  // New sv array
  SV* sv_spvm_string = SPVM_XS_UTIL_new_sv_object(spvm_string, "SPVM::String");
  
  XPUSHs(sv_spvm_string);
  XSRETURN(1);
}

SV*
get_data(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_spvm_string = ST(0);

  // Get SPVM string
  SPVM_API_OBJECT* spvm_string = SPVM_XS_UTIL_get_object(sv_spvm_string);
  
  // Set API
  SPVM_API* api = SPVM_XS_UTIL_get_api();
  
  // Get string bytes
  const char* string_bytes = (const char*)api->get_byte_array_elements(api, spvm_string);
  
  // Get string length
  int32_t spvm_string_length = api->get_array_length(api, spvm_string);
  
  SV* sv_string = sv_2mortal(newSVpv(string_bytes, spvm_string_length));
  
  XPUSHs(sv_string);
  XSRETURN(1);
}

MODULE = SPVM::Array::Object		PACKAGE = SPVM::Array::Object

SV*
new(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_class = ST(0);
  (void)sv_class;
  
  SV* sv_element_type_name = ST(1);
  SV* sv_length = ST(2);
  
  // API
  SPVM_API* api = SPVM_XS_UTIL_get_api();
  
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->get_runtime(api);
  
  int32_t length = (int32_t)SvIV(sv_length);
  
  // Element type id
  const char* element_type_name = SvPV_nolen(sv_element_type_name);
  int32_t element_type_id = api->get_type_id(api, element_type_name);
  
  // New array
  SPVM_API_OBJECT* array =  api->new_object_array(api, element_type_id, length);
  
  // Fix type name(int[] -> int[][]);
  SV* sv_type_name = sv_2mortal(newSVsv(sv_element_type_name));
  sv_catpv(sv_type_name, "[]");
  
  // Type id
  const char* type_name = SvPV_nolen(sv_type_name);
  
  int32_t type_id = api->get_type_id(api, type_name);
  SPVM_CONSTANT_POOL_TYPE* type = (SPVM_CONSTANT_POOL_TYPE*)&runtime->constant_pool[type_id];
  
  int32_t type_code = type->code;
  
  if (type_code < 0) {
    croak("Unknown type %s. Type must be used in SPVM module at least one(SPVM::Array::Object::new())", type_name);
  }
  if (type_code >= SPVM_TYPE_C_CODE_BYTE && type_code <= SPVM_TYPE_C_CODE_DOUBLE) {
    croak("Type is not object array %s(SPVM::Array::Object::new())", type_name);
  }
  
  // Increment reference count
  api->inc_ref_count(api, array);
  
  // New sv array
  SV* sv_array = SPVM_XS_UTIL_new_sv_object(array, "SPVM::Array::Object");
  
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
  
  // Set API
  SPVM_API* api = SPVM_XS_UTIL_get_api();
  
  // Get array
  SPVM_OBJECT* array = SPVM_XS_UTIL_get_object(sv_array);
  
  // Runtime
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->get_runtime(api);
  
  // Array type id
  int32_t array_type_id = array->type_id;
  
  // Array type
  SPVM_CONSTANT_POOL_TYPE* constant_pool_array_type = (SPVM_CONSTANT_POOL_TYPE*)&runtime->constant_pool[array_type_id];
  
  // Array type name
  const char* array_type_name = (char*)&runtime->constant_pool[constant_pool_array_type->name_id + 1];

  // Get object
  SPVM_OBJECT* object = SPVM_XS_UTIL_get_object(sv_object);
  
  // Object type id
  int32_t object_type_id = object->type_id;

  // Object type
  SPVM_CONSTANT_POOL_TYPE* constant_pool_objet_type = (SPVM_CONSTANT_POOL_TYPE*)&runtime->constant_pool[object_type_id];

  // Object type name
  const char* object_type_name = (char*)&runtime->constant_pool[constant_pool_objet_type->name_id + 1];
  
  if (strncmp(array_type_name, object_type_name, strlen(array_type_name - 2)) != 0) {
    croak("Invalid type %s is set to object array %s(SPVM::Array::Object::set())", object_type_name, array_type_name);
  }
  
  // Index
  int32_t index = (int32_t)SvIV(sv_index);
  
  api->set_object_array_element(api, array, index, (SPVM_API_OBJECT*)object);
  
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
  SPVM_API* api = SPVM_XS_UTIL_get_api();
  
  // Runtime
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->get_runtime(api);
  
  // Get array
  SPVM_OBJECT* array = SPVM_XS_UTIL_get_object(sv_array);
  
  // Array type id
  int32_t array_type_id = array->type_id;
  
  // Array type
  SPVM_CONSTANT_POOL_TYPE* constant_pool_array_type = (SPVM_CONSTANT_POOL_TYPE*)&runtime->constant_pool[array_type_id];
  
  // Array type name
  const char* array_type_name = (char*)&runtime->constant_pool[constant_pool_array_type->name_id + 1];
  
  // Element type name sv
  SV* sv_element_type_name = sv_2mortal(newSVpv(array_type_name, strlen(array_type_name) - 2));
  const char* element_type_name = SvPV_nolen(sv_element_type_name);
  
  // Element type id
  int32_t element_type_id = api->get_type_id(api, element_type_name);
  SPVM_CONSTANT_POOL_TYPE* element_type = (SPVM_CONSTANT_POOL_TYPE*)&runtime->constant_pool[element_type_id];
  int32_t element_type_code = element_type->code;

  // Index
  int32_t index = (int32_t)SvIV(sv_index);
  SPVM_API_OBJECT* base_object = api->get_object_array_element(api, array, index);
  if (base_object != NULL) {
    api->inc_ref_count(api, base_object);
  }
  
  SV* sv_base_object;
  switch (element_type_code) {
    case SPVM_TYPE_C_CODE_BYTE_ARRAY :
      sv_base_object = SPVM_XS_UTIL_new_sv_object(base_object, "SPVM::Array::Byte");
      break;
    case SPVM_TYPE_C_CODE_SHORT_ARRAY :
      sv_base_object = SPVM_XS_UTIL_new_sv_object(base_object, "SPVM::Array::Short");
      break;
    case SPVM_TYPE_C_CODE_INT_ARRAY :
      sv_base_object = SPVM_XS_UTIL_new_sv_object(base_object, "SPVM::Array::Int");
      break;
    case SPVM_TYPE_C_CODE_LONG_ARRAY :
      sv_base_object = SPVM_XS_UTIL_new_sv_object(base_object, "SPVM::Array::Long");
      break;
    case SPVM_TYPE_C_CODE_FLOAT_ARRAY :
      sv_base_object = SPVM_XS_UTIL_new_sv_object(base_object, "SPVM::Array::Float");
      break;
    case SPVM_TYPE_C_CODE_DOUBLE_ARRAY :
      sv_base_object = SPVM_XS_UTIL_new_sv_object(base_object, "SPVM::Array::Double");
      break;
    default : {
      if (element_type->dimension > 0) {
        sv_base_object = SPVM_XS_UTIL_new_sv_object(base_object, "SPVM::Array::Object");
      }
      else {
        sv_base_object = SPVM_XS_UTIL_new_sv_object(base_object, "SPVM::Object");
      }
    }
  }
  
  XPUSHs(sv_base_object);
  
  XSRETURN(1);
}

MODULE = SPVM::Array		PACKAGE = SPVM::Array


MODULE = SPVM		PACKAGE = SPVM

SV*
get_objects_count(...)
  PPCODE:
{
  (void)RETVAL;
  
  SPVM_API* api = SPVM_XS_UTIL_get_api();
  int32_t objects_count = api->get_objects_count(api);
  SV* sv_objects_count = sv_2mortal(newSViv(objects_count));
  
  XPUSHs(sv_objects_count);
  XSRETURN(1);
}

SV*
compile(...)
  PPCODE:
{
  (void)RETVAL;
  
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
get_sub_names(...)
  PPCODE:
{
  (void)RETVAL;
  
  // API
  SPVM_API* api = SPVM_XS_UTIL_get_api();
  
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->get_runtime(api);
  
  int32_t subs_base = runtime->subs_base;
  int32_t subs_length = runtime->subs_length;
  AV* av_sub_names = (AV*)sv_2mortal((SV*)newAV());
  
  {
    int32_t sub_index;
    for (sub_index = 0; sub_index < subs_length; sub_index++) {
      int32_t sub_id = runtime->constant_pool[subs_base + sub_index];
      
      SPVM_CONSTANT_POOL_SUB* constant_pool_sub = (SPVM_CONSTANT_POOL_SUB*)&runtime->constant_pool[sub_id];
      int32_t sub_name_id = constant_pool_sub->abs_name_id;
      int32_t sub_name_length = runtime->constant_pool[sub_name_id];
      const char* sub_name = (char*)&runtime->constant_pool[sub_name_id + 1];
      
      SV* sv_sub_name = sv_2mortal(newSVpv(sub_name, sub_name_length));
      av_push(av_sub_names, SvREFCNT_inc(sv_sub_name));
    }
  }
  
  SV* sv_sub_names = sv_2mortal(newRV_inc((SV*)av_sub_names));
  
  XPUSHs(sv_sub_names);
  XSRETURN(1);
}

SV*
get_native_sub_names(...)
  PPCODE:
{
  (void)RETVAL;
  
  // API
  SPVM_API* api = SPVM_XS_UTIL_get_api();
  
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->get_runtime(api);
  
  int32_t subs_base = runtime->subs_base;
  int32_t subs_length = runtime->subs_length;
  AV* av_sub_names = (AV*)sv_2mortal((SV*)newAV());
  
  {
    int32_t sub_index;
    for (sub_index = 0; sub_index < subs_length; sub_index++) {
      int32_t sub_id = runtime->constant_pool[subs_base + sub_index];
      
      SPVM_CONSTANT_POOL_SUB* constant_pool_sub = (SPVM_CONSTANT_POOL_SUB*)&runtime->constant_pool[sub_id];
      if (constant_pool_sub->is_native) {
        int32_t sub_name_id = constant_pool_sub->abs_name_id;
        int32_t sub_name_length = runtime->constant_pool[sub_name_id];
        const char* sub_name = (char*)&runtime->constant_pool[sub_name_id + 1];
        
        SV* sv_sub_name = sv_2mortal(newSVpv(sub_name, sub_name_length));
        av_push(av_sub_names, SvREFCNT_inc(sv_sub_name));
      }
    }
  }
  
  SV* sv_sub_names = sv_2mortal(newRV_inc((SV*)av_sub_names));
  
  XPUSHs(sv_sub_names);
  XSRETURN(1);
}

SV*
get_native_sub_names_from_package(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_package_name = ST(0);
  const char* package_name = SvPV_nolen(sv_package_name);
  
  // API
  SPVM_API* api = SPVM_XS_UTIL_get_api();
  
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->get_runtime(api);
  
  SPVM_DYNAMIC_ARRAY* native_sub_name_ids = SPVM_HASH_search(runtime->native_sub_name_ids_symtable, package_name, strlen(package_name));
  
  AV* av_native_sub_names = (AV*)sv_2mortal((SV*)newAV());
  
  {
    int32_t sub_name_index;
    for (sub_name_index = 0; sub_name_index < native_sub_name_ids->length; sub_name_index++) {
      
      int32_t sub_name_id = (int32_t)(intptr_t)SPVM_DYNAMIC_ARRAY_fetch(native_sub_name_ids, sub_name_index);
      
      const char* native_sub_name = (char*)&runtime->constant_pool[sub_name_id + 1];
      assert(native_sub_name);
      
      SV* sv_native_sub_name = sv_2mortal(newSVpv(native_sub_name, 0));
      av_push(av_native_sub_names, SvREFCNT_inc(sv_native_sub_name));
    }
  }
  
  SV* sv_native_sub_names = sv_2mortal(newRV_inc((SV*)av_native_sub_names));
  
  XPUSHs(sv_native_sub_names);
  XSRETURN(1);
}

SV*
get_use_package_path(...)
  PPCODE:
{
  (void)RETVAL;
  
  // API
  SPVM_API* api = SPVM_XS_UTIL_get_api();

  SV* sv_package_name = ST(0);
  const char* package_name = SvPV_nolen(sv_package_name);
  
  SPVM_RUNTIME* runtime = api->get_runtime(api);
  
  int32_t* constant_pool = runtime->constant_pool;
  
  int32_t package_name_id = (int32_t)(intptr_t)SPVM_HASH_search(runtime->use_package_path_id_symtable, package_name, strlen(package_name));
  
  const char* use_package_path = (char*)&constant_pool[package_name_id + 1];
  
  SV* sv_use_package_path = sv_2mortal(newSVpv(use_package_path, 0));
  
  XPUSHs(sv_use_package_path);
  
  XSRETURN(1);
}

SV*
bind_native_sub(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_native_sub_name = ST(0);
  SV* sv_native_address = ST(1);
  
  // API
  SPVM_API* api = SPVM_XS_UTIL_get_api();
  
  // Runtime
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->get_runtime(api);
  
  // Native subroutine name
  const char* native_sub_name = SvPV_nolen(sv_native_sub_name);
  
  // Native address
  IV native_address = SvIV(sv_native_address);
  
  // Sub id
  int32_t sub_id = api->get_sub_id(api, native_sub_name);

  // Set native address
  SPVM_CONSTANT_POOL_SUB* constant_pool_sub = (SPVM_CONSTANT_POOL_SUB*)&runtime->constant_pool[sub_id];
  constant_pool_sub->native_address = (void*)native_address;

  XSRETURN(0);
}

SV*
build_field_symtable(...)
  PPCODE:
{
  (void)RETVAL;
  
  // Get compiler
  SPVM_COMPILER* compiler = (SPVM_COMPILER*)SvIV(SvRV(get_sv("SPVM::COMPILER", 0)));
  
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
          SPVM_FIELD_INFO* field = op_field->uv.field;
          const char* field_name = field->op_name->uv.name;
          
          // Field type id
          int32_t field_type_id = field->op_type->uv.type->id;
          SV* sv_field_type_id = sv_2mortal(newSViv(field_type_id));

          // Field id
          int32_t field_id = field->index;
          SV* sv_field_id = sv_2mortal(newSViv(field_id));
          
          HV* hv_field_info = (HV*)sv_2mortal((SV*)newHV());
          (void)hv_store(hv_field_info, "id", strlen("id"), SvREFCNT_inc(sv_field_id), 0);
          (void)hv_store(hv_field_info, "id", strlen("id"), SvREFCNT_inc(sv_field_id), 0);
          (void)hv_store(hv_field_info, "type_id", strlen("type_id"), SvREFCNT_inc(sv_field_type_id), 0);
          SV* sv_field_info = sv_2mortal(newRV_inc((SV*)hv_field_info));
          
          (void)hv_store(hv_package_info, field_name, strlen(field_name), SvREFCNT_inc(sv_field_info), 0);
        }
      }
      
      SV* sv_package_info = sv_2mortal(newRV_inc((SV*)hv_package_info));
      (void)hv_store(hv_field_symtable, package_name, strlen(package_name), SvREFCNT_inc(sv_package_info), 0);
    }
  }
  
  XSRETURN(0);
}

SV*
build_runtime(...)
  PPCODE:
{
  (void)RETVAL;
  
  // Get compiler
  SPVM_COMPILER* compiler = (SPVM_COMPILER*)SvIV(SvRV(get_sv("SPVM::COMPILER", 0)));
  
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
  (void)RETVAL;
  
  // Get compiler
  SPVM_COMPILER* compiler = (SPVM_COMPILER*)SvIV(SvRV(get_sv("SPVM::COMPILER", 0)));
  
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
  (void)RETVAL;
  
  SV* sv_sub_abs_name = ST(0);
  
  // Get API
  SV* sv_api = get_sv("SPVM::API", 0);
  SV* sviv_api = SvRV(sv_api);
  size_t iv_api = SvIV(sviv_api);
  SPVM_API* api = INT2PTR(SPVM_API*, iv_api);
  
  const char* sub_abs_name = SvPV_nolen(sv_sub_abs_name);
  int32_t sub_id = api->get_sub_id(api, sub_abs_name);
  
  SPVM_RUNTIME* runtime = (SPVM_RUNTIME*)api->get_runtime(api);
  
  // Subroutine information
  SPVM_CONSTANT_POOL_SUB* constant_pool_sub = (SPVM_CONSTANT_POOL_SUB*)&runtime->constant_pool[sub_id];
  
  // Arguments
  {
    int32_t arg_index;
    int32_t arg_type_ids_base = constant_pool_sub->arg_type_ids_base;
    int32_t args_length = constant_pool_sub->args_length;
    // Check argument count
    if (items - 1 != args_length) {
      croak("Argument count is defferent");
    }
    
    for (arg_index = 0; arg_index < args_length; arg_index++) {
      SV* sv_value = ST(arg_index + 1);
      
      int32_t arg_type_id = runtime->constant_pool[arg_type_ids_base + arg_index];

      // Array type
      SPVM_CONSTANT_POOL_TYPE* constant_pool_arg_type = (SPVM_CONSTANT_POOL_TYPE*)&runtime->constant_pool[arg_type_id];

      int32_t arg_type_code = constant_pool_arg_type->code;
      
      if (sv_isobject(sv_value)) {
        SV* sv_base_object = sv_value;
        if (sv_derived_from(sv_base_object, "SPVM::BaseObject")) {
          
          SPVM_OBJECT* base_object = SPVM_XS_UTIL_get_object(sv_base_object);
          
          int32_t base_object_type_id = base_object->type_id;
          
          SPVM_CONSTANT_POOL_TYPE* constant_pool_base_object_type = (SPVM_CONSTANT_POOL_TYPE*)&runtime->constant_pool[base_object_type_id];
          
          int32_t base_object_type_code =constant_pool_base_object_type->code;
          
          if (base_object_type_code != arg_type_code) {
            const char* base_object_type_name = (char*)&runtime->constant_pool[constant_pool_base_object_type->name_id + 1];
            const char* arg_type_name = (char*)&runtime->constant_pool[constant_pool_arg_type->name_id + 1];
            
            croak("Argument base_object type need %s, but %s", arg_type_name, base_object_type_name);
          }
          
          call_sub_args[arg_index].object_value = base_object;
        }
        else {
          croak("Object must be derived from SPVM::BaseObject");
        }
      }
      else {
        switch (arg_type_code) {
          case SPVM_TYPE_C_CODE_BYTE : {
            int8_t value = (int8_t)SvIV(sv_value);
            call_sub_args[arg_index].byte_value = value;
            break;
          }
          case  SPVM_TYPE_C_CODE_SHORT : {
            int16_t value = (int16_t)SvIV(sv_value);
            call_sub_args[arg_index].short_value = value;
            break;
          }
          case  SPVM_TYPE_C_CODE_INT : {
            int32_t value = (int32_t)SvIV(sv_value);
            call_sub_args[arg_index].int_value = value;
            break;
          }
          case  SPVM_TYPE_C_CODE_LONG : {
            int64_t value = (int64_t)SvIV(sv_value);
            call_sub_args[arg_index].long_value = value;
            break;
          }
          case  SPVM_TYPE_C_CODE_FLOAT : {
            float value = (float)SvNV(sv_value);
            call_sub_args[arg_index].float_value = value;
            break;
          }
          case  SPVM_TYPE_C_CODE_DOUBLE : {
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
  
  // Return type id
  int32_t return_type_id = constant_pool_sub->return_type_id;
  SPVM_CONSTANT_POOL_TYPE* return_type = (SPVM_CONSTANT_POOL_TYPE*)&runtime->constant_pool[return_type_id];
  int32_t return_type_code = return_type->code;
  
  // Return count
  int32_t return_count;
  switch (return_type_code) {
    case SPVM_TYPE_C_CODE_VOID:  {
      api->call_void_sub(api, sub_id, call_sub_args);
      return_count = 0;
      break;
    }
    case SPVM_TYPE_C_CODE_BYTE: {
      int8_t return_value = api->call_byte_sub(api, sub_id, call_sub_args);
      SV* sv_return_value = sv_2mortal(newSViv(return_value));
      XPUSHs(sv_return_value);
      return_count = 1;
      break;
    }
    case SPVM_TYPE_C_CODE_SHORT: {
      int16_t return_value = api->call_short_sub(api, sub_id, call_sub_args);
      SV* sv_return_value = sv_2mortal(newSViv(return_value));
      XPUSHs(sv_return_value);
      return_count = 1;
      break;
    }
    case SPVM_TYPE_C_CODE_INT: {
      int32_t return_value = api->call_int_sub(api, sub_id, call_sub_args);
      SV* sv_return_value = sv_2mortal(newSViv(return_value));
      XPUSHs(sv_return_value);
      return_count = 1;
      break;
    }
    case SPVM_TYPE_C_CODE_LONG: {
      int64_t return_value = api->call_long_sub(api, sub_id, call_sub_args);
      SV* sv_return_value = sv_2mortal(newSViv(return_value));
      XPUSHs(sv_return_value);
      return_count = 1;
      break;
    }
    case SPVM_TYPE_C_CODE_FLOAT: {
      float return_value = api->call_float_sub(api, sub_id, call_sub_args);
      SV* sv_return_value = sv_2mortal(newSVnv(return_value));
      XPUSHs(sv_return_value);
      return_count = 1;
      break;
    }
    case SPVM_TYPE_C_CODE_DOUBLE: {
      double return_value = api->call_double_sub(api, sub_id, call_sub_args);
      SV* sv_return_value = sv_2mortal(newSVnv(return_value));
      XPUSHs(sv_return_value);
      return_count = 1;
      break;
    }
    default: {
      SPVM_API_OBJECT* return_value = api->call_object_sub(api, sub_id, call_sub_args);
      SV* sv_return_value = NULL;
      if (return_value != NULL) {
        api->inc_ref_count(api, return_value);
        
        switch(return_type_code) {
          case SPVM_TYPE_C_CODE_BYTE_ARRAY :
            sv_return_value = SPVM_XS_UTIL_new_sv_object(return_value, "SPVM::Array::Byte");
            break;
          case SPVM_TYPE_C_CODE_SHORT_ARRAY :
            sv_return_value = SPVM_XS_UTIL_new_sv_object(return_value, "SPVM::Array::Short");
            break;
          case SPVM_TYPE_C_CODE_INT_ARRAY :
            sv_return_value = SPVM_XS_UTIL_new_sv_object(return_value, "SPVM::Array::Int");
            break;
          case SPVM_TYPE_C_CODE_LONG_ARRAY :
            sv_return_value = SPVM_XS_UTIL_new_sv_object(return_value, "SPVM::Array::Long");
            break;
          case SPVM_TYPE_C_CODE_FLOAT_ARRAY :
            sv_return_value = SPVM_XS_UTIL_new_sv_object(return_value, "SPVM::Array::Float");
            break;
          case SPVM_TYPE_C_CODE_DOUBLE_ARRAY :
            sv_return_value = SPVM_XS_UTIL_new_sv_object(return_value, "SPVM::Array::Double");
            break;
          default : {
            if (return_type->dimension > 0) {
              sv_return_value = SPVM_XS_UTIL_new_sv_object(return_value, "SPVM::Array::Object");
            }
            else {
              sv_return_value = SPVM_XS_UTIL_new_sv_object(return_value, "SPVM::Object");
            }
          }
        }
      }
      else {
        sv_return_value = &PL_sv_undef;
      }
      XPUSHs(sv_return_value);
      return_count = 1;
    }
  }
  SPVM_API_OBJECT* exception = api->get_exception(api);
  if (exception) {
    int32_t length = api->get_array_length(api, exception);
    char* exception_bytes = (char*)api->get_byte_array_elements(api, exception);
    SV* sv_exception = sv_2mortal(newSVpv(exception_bytes, length));
    croak("%s", SvPV_nolen(sv_exception));
  }
  
  XSRETURN(return_count);
}
