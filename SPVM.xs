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

#include "spvm_api.h"

#include "spvm_compiler.h"
#include "spvm_hash.h"
#include "spvm_list.h"
#include "spvm_type.h"
#include "spvm_class.h"
#include "spvm_field.h"
#include "spvm_class_var.h"
#include "spvm_basic_type.h"
#include "spvm_object.h"
#include "spvm_native.h"
#include "spvm_opcode_builder.h"
#include "spvm_csource_builder_precompile.h"
#include "spvm_list.h"
#include "spvm_string_buffer.h"
#include "spvm_limit.h"
#include "spvm_allocator.h"
#include "spvm_method.h"

#include "spvm_runtime_basic_type.h"
#include "spvm_runtime_class.h"
#include "spvm_runtime_class_var.h"
#include "spvm_runtime_field.h"
#include "spvm_runtime_info.h"
#include "spvm_runtime_manager.h"
#include "spvm_runtime_method.h"
#include "spvm_runtime_string.h"
#include "spvm_runtime_type.h"

static const char* MFILE = "SPVM.xs";

SV* SPVM_XS_UTIL_new_sv_object(SPVM_ENV* env, SPVM_OBJECT* object, const char* class) {
  
  // Create object
  size_t iv_object = PTR2IV(object);
  SV* sviv_object = sv_2mortal(newSViv(iv_object));
  SV* sv_object = sv_2mortal(newRV_inc(sviv_object));

  HV* hv_data = (HV*)sv_2mortal((SV*)newHV());
  (void)hv_store(hv_data, "object", strlen("object"), SvREFCNT_inc(sv_object), 0);
  SV* sv_data = sv_2mortal(newRV_inc((SV*)hv_data));

  // Set ENV
  size_t iv_env = PTR2IV(env);
  SV* sviv_env = sv_2mortal(newSViv(iv_env));
  SV* sv_env = sv_2mortal(newRV_inc(sviv_env));
  (void)hv_store(hv_data, "env", strlen("env"), SvREFCNT_inc(sv_env), 0);

  HV* hv_class = gv_stashpv(class, 0);
  sv_bless(sv_data, hv_class);
  
  return sv_data;
}

SPVM_OBJECT* SPVM_XS_UTIL_get_object(SV* sv_data) {
  
  if (SvOK(sv_data)) {
    HV* hv_data = (HV*)SvRV(sv_data);
    
    SV** sv_object_ptr = hv_fetch(hv_data, "object", strlen("object"), 0);
    SV* sv_object = sv_object_ptr ? *sv_object_ptr : &PL_sv_undef;
    size_t iv_object = SvIV(SvRV(sv_object));
    SPVM_OBJECT* object = INT2PTR(SPVM_OBJECT*, iv_object);
    
    return object;
  }
  else {
    return NULL;
  }
}

SPVM_OBJECT* SPVM_XS_UTIL_new_mulnum_array(SPVM_ENV* env, const char* basic_type_name, SV* sv_elems, SV** sv_error) {
  
  if (!sv_derived_from(sv_elems, "ARRAY")) {
    *sv_error = sv_2mortal(newSVpvf("Argument must be array reference at %s line %d\n", MFILE, __LINE__));
    return NULL;
  }
  
  AV* av_elems = (AV*)SvRV(sv_elems);
  
  int32_t length = av_len(av_elems) + 1;
  
  // Runtime
  SPVM_COMPILER* compiler = (SPVM_COMPILER*)env->compiler;
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_get_basic_type(env, basic_type_name);
  
  if (basic_type == NULL) {
    *sv_error = sv_2mortal(newSVpvf("Not found %s at %s line %d\n", basic_type_name, MFILE, __LINE__));
    return NULL;
  }
  
  // New array
  void* array = env->new_mulnum_array(env, basic_type->id, length);

  for (int32_t index = 0; index < length; index++) {
    SV** sv_element_ptr = av_fetch(av_elems, index, 0);
    SV* sv_element = sv_element_ptr ? *sv_element_ptr : &PL_sv_undef;

    if (sv_derived_from(sv_element, "HASH")) {
      
      SPVM_RUNTIME_CLASS* class = SPVM_API_get_runtime_class_from_basic_type_id(env, basic_type->id);
      assert(class);
      
      SPVM_RUNTIME_FIELD* first_field = SPVM_API_get_runtime_field_from_index(env, class->id, 0);
      assert(first_field);

      void* elems = (void*)env->get_elems_int(env, array);
      
      HV* hv_value = (HV*)SvRV(sv_element);
      int32_t fields_length = class->field_ids->length;
      // Field exists check
      int32_t hash_keys_length = 0;
      while (hv_iternext(hv_value)) {
        hash_keys_length++;
      }
      if (hash_keys_length != fields_length) {
        *sv_error = sv_2mortal(newSVpvf("Value element hash key is lacked at %s line %d\n", MFILE, __LINE__));
        return NULL;
      }

      for (int32_t field_index = 0; field_index < class->field_ids->length; field_index++) {
        SPVM_RUNTIME_FIELD* field = SPVM_API_get_runtime_field_from_index(env, class->id, field_index);
        const char* field_name = field->name;
        
        SV** sv_field_value_ptr = hv_fetch(hv_value, field_name, strlen(field_name), 0);
        SV* sv_field_value;
        if (sv_field_value_ptr) {
          sv_field_value = *sv_field_value_ptr;
        }
        else {
          *sv_error = sv_2mortal(newSVpvf("Value element must be defined at %s line %d\n", MFILE, __LINE__));
          return NULL;
        }

        SPVM_RUNTIME_TYPE* first_field_type = SPVM_LIST_fetch(compiler->runtime_types, first_field->type_id);
        switch (first_field_type->basic_type_id) {
          case SPVM_BASIC_TYPE_C_ID_BYTE: {
            ((int8_t*)elems)[(fields_length * index) + field_index] = (int8_t)SvIV(sv_field_value);
            break;
          }
          case SPVM_BASIC_TYPE_C_ID_SHORT: {
            ((int16_t*)elems)[(fields_length * index) + field_index] = (int16_t)SvIV(sv_field_value);
            break;
          }
          case SPVM_BASIC_TYPE_C_ID_INT: {
            ((int32_t*)elems)[(fields_length * index) + field_index] = (int32_t)SvIV(sv_field_value);
            break;
          }
          case SPVM_BASIC_TYPE_C_ID_LONG: {
            ((int64_t*)elems)[(fields_length * index) + field_index] = (int64_t)SvIV(sv_field_value);
            break;
          }
          case SPVM_BASIC_TYPE_C_ID_FLOAT: {
            ((float*)elems)[(fields_length * index) + field_index] = (float)SvNV(sv_field_value);
            break;
          }
          case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
            ((double*)elems)[(fields_length * index) + field_index] = (double)SvNV(sv_field_value);
            break;
          }
          default:
            assert(0);
        }
      }
    }
    else {
      *sv_error = sv_2mortal(newSVpvf("Element must be a hash reference at %s line %d\n", MFILE, __LINE__));
      return NULL;
    }
  }
  
  return array;
}

MODULE = SPVM::ExchangeAPI		PACKAGE = SPVM::ExchangeAPI

SV*
call_spvm_method(...)
  PPCODE:
{
  (void)RETVAL;
  
  // Arguments
  SV* sv_env = ST(0);
  SV* sv_class_name = ST(1);
  SV* sv_method_name = ST(2);
  
  // Env
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));

  // Runtime
  SPVM_COMPILER* compiler = (SPVM_COMPILER*)env->compiler;
  
  // Class Name
  const char* class_name = SvPV_nolen(sv_class_name);
  
  // Method name
  const char* method_name = SvPV_nolen(sv_method_name);
  
  // Basic type
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_get_basic_type(env, class_name);
  
  // Class
  SPVM_RUNTIME_CLASS* class = SPVM_API_get_runtime_class_from_basic_type_id(env, basic_type->id);
  
  // Method not found
  int32_t method_not_found;
  SPVM_RUNTIME_METHOD* method = NULL;
  if (class == NULL) {
    method_not_found = 1;
  }
  else {
    method = SPVM_API_get_runtime_method_from_runtime_class(env, class->id, method_name);
    if (method == NULL) {
      method_not_found = 1;
    }
    else {
      method_not_found = 0;
    }
  }
  if (method_not_found) {
    croak("%s->%s method not found at %s line %d\n", class_name, method_name, MFILE, __LINE__);
  }
  
  // Base index of SPVM arguments
  int32_t spvm_args_base = 3;

  // If class method, first argument is ignored
  if (method->is_class_method) {
    spvm_args_base++;
  }
  
  // Check argument count
  if (items - spvm_args_base < method->arg_type_ids->length) {
    croak("Too few arguments %s->%s at %s line %d\n", class_name, method_name, MFILE, __LINE__);
  }
  else if (items - spvm_args_base > method->arg_type_ids->length) {
    croak("Too many arguments %s->%s at %s line %d\n", class_name, method_name, MFILE, __LINE__);
  }

  // Argument stack
  // In SPVM, argument index is different from arguments stack index which is
  // used arguments and return values because multi numeric type have multi width.
  SPVM_VALUE args_stack[SPVM_LIMIT_C_METHOD_ARGS_MAX_COUNT];
  int32_t args_stack_index = 0;

  // Arguments have reference type
  int32_t args_have_ref = 0;

  // Reference stack.
  int32_t ref_stack_index = 0;
  SPVM_VALUE ref_stack[SPVM_LIMIT_C_METHOD_ARGS_MAX_COUNT];
  int32_t ref_stack_indexes[SPVM_LIMIT_C_METHOD_ARGS_MAX_COUNT];

  // Arguments
  for (int32_t args_index = 0; args_index < method->arg_type_ids->length; args_index++) {
    
    int32_t args_index_nth = args_index + 1;
    
    // Get value from Perl argument stack
    SV* sv_value = ST(spvm_args_base + args_index);

    int32_t arg_type_id = (intptr_t)SPVM_LIST_fetch(method->arg_type_ids, args_index);
    SPVM_RUNTIME_TYPE* arg_type = SPVM_LIST_fetch(compiler->runtime_types, arg_type_id);
    
    int32_t arg_basic_type_id = arg_type->basic_type_id;
    int32_t arg_type_dimension = arg_type->dimension;
    
    // Process argument corresponding to the type category
    switch (arg_type->category) {
      // Perl scalar to SPVM byte
      case SPVM_TYPE_C_TYPE_CATEGORY_BYTE : {
        int8_t value = (int8_t)SvIV(sv_value);
        args_stack[args_stack_index].bval = value;
        args_stack_index++;
        break;
      }
      // Perl scalar to SPVM short
      case SPVM_TYPE_C_TYPE_CATEGORY_SHORT : {
        int16_t value = (int16_t)SvIV(sv_value);
        args_stack[args_stack_index].sval = value;
        args_stack_index++;
        break;
      }
      // Perl scalar to SPVM int
      case SPVM_TYPE_C_TYPE_CATEGORY_INT : {
        int32_t value = (int32_t)SvIV(sv_value);
        args_stack[args_stack_index].ival = value;
        args_stack_index++;
        break;
      }
      // Perl scalar to SPVM long
      case SPVM_TYPE_C_TYPE_CATEGORY_LONG : {
        int64_t value = (int64_t)SvIV(sv_value);
        args_stack[args_stack_index].lval = value;
        args_stack_index++;
        break;
      }
      // Perl scalar to SPVM float
      case SPVM_TYPE_C_TYPE_CATEGORY_FLOAT : {
        float value = (float)SvNV(sv_value);
        args_stack[args_stack_index].fval = value;
        args_stack_index++;
        break;
      }
      // Perl scalar to SPVM double
      case SPVM_TYPE_C_TYPE_CATEGORY_DOUBLE : {
        double value = (double)SvNV(sv_value);
        args_stack[args_stack_index].dval = value;
        args_stack_index++;
        break;
      }
      // Perl scalar to SPVM string
      case SPVM_TYPE_C_TYPE_CATEGORY_STRING: {
        // Perl undef to SPVM undef
        if (!SvOK(sv_value)) {
          args_stack[args_stack_index].oval = NULL;
        }
        else {
          // Perl non-ref scalar to SPVM string
          // If Perl value is non-ref scalar, the value is converted to SPVM::BlessedObject::String object
          if (!SvROK(sv_value)) {
            // Convert Perl decoded string to loose UTF-8 bytes.
            SV* sv_value_copy = sv_2mortal(newSVsv(sv_value));
            sv_utf8_encode(sv_value_copy);
            const char* chars = SvPV_nolen(sv_value_copy);
            int32_t length = SvCUR(sv_value_copy);
            void* string = env->new_string(env, chars, length);
            
            SV* sv_string = SPVM_XS_UTIL_new_sv_object(env, string, "SPVM::BlessedObject::String");
            
            sv_value = sv_string;
          }
          
          // Perl SPVM::BlessedObject::String to SPVM string
          if (sv_isobject(sv_value) && sv_derived_from(sv_value, "SPVM::BlessedObject::String")) {
            SPVM_OBJECT* object = SPVM_XS_UTIL_get_object(sv_value);
            
            args_stack[args_stack_index].oval = object;
          }
          else {
            croak("%dth argument of %s->%s must be a non-ref scalar or a SPVM::BlessedObject::String object at %s line %d\n", args_index_nth, class_name, method_name, MFILE, __LINE__);
          }
        }
        args_stack_index++;
        break;
      }
      // Perl SPVM::BlessedObject::Class to SPVM class
      case SPVM_TYPE_C_TYPE_CATEGORY_CLASS:
      {
        if (!SvOK(sv_value)) {
          args_stack[args_stack_index].oval = NULL;
        }
        else {
          if (sv_isobject(sv_value) && sv_derived_from(sv_value, "SPVM::BlessedObject::Class")) {
            SPVM_OBJECT* object = SPVM_XS_UTIL_get_object(sv_value);
            assert(arg_type_dimension == 0);
            if (object->basic_type_id != arg_basic_type_id) {
              croak("%dth argument of %s->%s must be %s class line %d\n", args_index_nth, class_name, method_name, MFILE, __LINE__);
            }
            args_stack[args_stack_index].oval = object;
          }
          else {
            croak("%dth argument of %s->%s must be a SPVM::BlessedObject::Class object at %s line %d\n", args_index_nth, class_name, method_name, MFILE, __LINE__);
          }
        }
        args_stack_index++;
        break;
      }
      // Perl SPVM::BlessedObject to SPVM any object
      case SPVM_TYPE_C_TYPE_CATEGORY_ANY_OBJECT:
      {
        if (!SvOK(sv_value)) {
          args_stack[args_stack_index].oval = NULL;
        }
        else {
          if (sv_isobject(sv_value) && sv_derived_from(sv_value, "SPVM::BlessedObject")) {
            SPVM_OBJECT* object = SPVM_XS_UTIL_get_object(sv_value);
            args_stack[args_stack_index].oval = object;
          }
          else {
            croak("%dth argument of %s->%s must be a SPVM::BlessedObject at %s line %d\n", args_index_nth, class_name, method_name, MFILE, __LINE__);
          }
        }
        args_stack_index++;
        break;
      }
      // Perl hash reference to SPVM byte multi numeric type
      case SPVM_TYPE_C_TYPE_CATEGORY_MULNUM_BYTE: {
        if (sv_derived_from(sv_value, "HASH")) {
          SPVM_RUNTIME_BASIC_TYPE* arg_basic_type = SPVM_LIST_fetch(compiler->runtime_basic_types, arg_basic_type_id);
          SPVM_RUNTIME_CLASS* arg_class = SPVM_API_get_runtime_class_from_basic_type_id(env, arg_basic_type->id);
          HV* hv_value = (HV*)SvRV(sv_value);
          int32_t fields_length = arg_class->field_ids->length;
          for (int32_t field_index = 0; field_index < fields_length; field_index++) {
            SPVM_RUNTIME_FIELD* field = SPVM_API_get_runtime_field_from_index(env, arg_class->id, field_index);
            const char* field_name = field->name;
            SV** sv_field_value_ptr = hv_fetch(hv_value, field_name, strlen(field_name), 0);
            SV* sv_field_value;
            if (sv_field_value_ptr) {
              sv_field_value = *sv_field_value_ptr;
            }
            else {
              croak("%dth argument's field \"%s\" of \"%s\" is missing at %s line %d\n", args_index_nth, field_name, arg_class->name, MFILE, __LINE__);
            }
            int8_t value = (int8_t)SvIV(sv_field_value);
            args_stack[args_stack_index + field_index].bval = value;
          }
          args_stack_index += arg_class->field_ids->length;
        }
        else {
          croak("%dth argument of %s->%s must be a hash reference at %s line %d\n", args_index_nth, class_name, method_name, MFILE, __LINE__);
        }
        break;
      }
      // Perl hash reference to SPVM short multi numeric type
      case SPVM_TYPE_C_TYPE_CATEGORY_MULNUM_SHORT: {
        if (sv_derived_from(sv_value, "HASH")) {
          SPVM_RUNTIME_BASIC_TYPE* arg_basic_type = SPVM_LIST_fetch(compiler->runtime_basic_types, arg_basic_type_id);
          SPVM_RUNTIME_CLASS* arg_class = SPVM_API_get_runtime_class_from_basic_type_id(env, arg_basic_type->id);
          HV* hv_value = (HV*)SvRV(sv_value);
          int32_t fields_length = arg_class->field_ids->length;
          for (int32_t field_index = 0; field_index < fields_length; field_index++) {
            SPVM_RUNTIME_FIELD* field = SPVM_API_get_runtime_field_from_index(env, arg_class->id, field_index);
            const char* field_name = field->name;
            SV** sv_field_value_ptr = hv_fetch(hv_value, field_name, strlen(field_name), 0);
            SV* sv_field_value;
            if (sv_field_value_ptr) {
              sv_field_value = *sv_field_value_ptr;
            }
            else {
              croak("%dth argument's field \"%s\" of \"%s\" is missing at %s line %d\n", args_index_nth, field_name, arg_class->name, MFILE, __LINE__);
            }
            int16_t value = (int16_t)SvIV(sv_field_value);
            args_stack[args_stack_index + field_index].sval = value;
          }
          args_stack_index += arg_class->field_ids->length;
        }
        else {
          croak("%dth argument of %s->%s must be a hash reference at %s line %d\n", args_index_nth, class_name, method_name, MFILE, __LINE__);
        }
        break;
      }
      // Perl hash reference to SPVM int multi numeric type
      case SPVM_TYPE_C_TYPE_CATEGORY_MULNUM_INT: {
        if (sv_derived_from(sv_value, "HASH")) {
          SPVM_RUNTIME_BASIC_TYPE* arg_basic_type = SPVM_LIST_fetch(compiler->runtime_basic_types, arg_basic_type_id);
          SPVM_RUNTIME_CLASS* arg_class = SPVM_API_get_runtime_class_from_basic_type_id(env, arg_basic_type->id);
          HV* hv_value = (HV*)SvRV(sv_value);
          int32_t fields_length = arg_class->field_ids->length;
          for (int32_t field_index = 0; field_index < fields_length; field_index++) {
            SPVM_RUNTIME_FIELD* field = SPVM_API_get_runtime_field_from_index(env, arg_class->id, field_index);
            const char* field_name = field->name;
            SV** sv_field_value_ptr = hv_fetch(hv_value, field_name, strlen(field_name), 0);
            SV* sv_field_value;
            if (sv_field_value_ptr) {
              sv_field_value = *sv_field_value_ptr;
            }
            else {
              croak("%dth argument's field \"%s\" of \"%s\" is missing at %s line %d\n", args_index_nth, field_name, arg_class->name, MFILE, __LINE__);
            }
            int32_t value = (int32_t)SvIV(sv_field_value);
            args_stack[args_stack_index + field_index].ival = value;
          }
          args_stack_index += arg_class->field_ids->length;
        }
        else {
          croak("%dth argument of %s->%s must be a hash reference at %s line %d\n", args_index_nth, class_name, method_name, MFILE, __LINE__);
        }
        break;
      }
      // Perl hash reference to SPVM long multi numeric type
      case SPVM_TYPE_C_TYPE_CATEGORY_MULNUM_LONG: {
        if (sv_derived_from(sv_value, "HASH")) {
          SPVM_RUNTIME_BASIC_TYPE* arg_basic_type = SPVM_LIST_fetch(compiler->runtime_basic_types, arg_basic_type_id);
          SPVM_RUNTIME_CLASS* arg_class = SPVM_API_get_runtime_class_from_basic_type_id(env, arg_basic_type->id);
          HV* hv_value = (HV*)SvRV(sv_value);
          int32_t fields_length = arg_class->field_ids->length;
          for (int32_t field_index = 0; field_index < fields_length; field_index++) {
            SPVM_RUNTIME_FIELD* field = SPVM_API_get_runtime_field_from_index(env, arg_class->id, field_index);
            const char* field_name = field->name;
            SV** sv_field_value_ptr = hv_fetch(hv_value, field_name, strlen(field_name), 0);
            SV* sv_field_value;
            if (sv_field_value_ptr) {
              sv_field_value = *sv_field_value_ptr;
            }
            else {
              croak("%dth argument's field \"%s\" of \"%s\" is missing at %s line %d\n", args_index_nth, field_name, arg_class->name, MFILE, __LINE__);
            }
            int64_t value = (int64_t)SvIV(sv_field_value);
            args_stack[args_stack_index + field_index].lval = value;
          }
          args_stack_index += arg_class->field_ids->length;
        }
        else {
          croak("%dth argument of %s->%s must be a hash reference at %s line %d\n", args_index_nth, class_name, method_name, MFILE, __LINE__);
        }
        break;
      }
      // Perl hash reference to SPVM float multi numeric type
      case SPVM_TYPE_C_TYPE_CATEGORY_MULNUM_FLOAT: {
        if (sv_derived_from(sv_value, "HASH")) {
          SPVM_RUNTIME_BASIC_TYPE* arg_basic_type = SPVM_LIST_fetch(compiler->runtime_basic_types, arg_basic_type_id);
          SPVM_RUNTIME_CLASS* arg_class = SPVM_API_get_runtime_class_from_basic_type_id(env, arg_basic_type->id);
          HV* hv_value = (HV*)SvRV(sv_value);
          int32_t fields_length = arg_class->field_ids->length;
          for (int32_t field_index = 0; field_index < fields_length; field_index++) {
            SPVM_RUNTIME_FIELD* field = SPVM_API_get_runtime_field_from_index(env, arg_class->id, field_index);
            const char* field_name = field->name;
            SV** sv_field_value_ptr = hv_fetch(hv_value, field_name, strlen(field_name), 0);
            SV* sv_field_value;
            if (sv_field_value_ptr) {
              sv_field_value = *sv_field_value_ptr;
            }
            else {
              croak("%dth argument's field \"%s\" of \"%s\" is missing at %s line %d\n", args_index_nth, field_name, arg_class->name, MFILE, __LINE__);
            }
            float value = (float)SvNV(sv_field_value);
            args_stack[args_stack_index + field_index].fval = value;
          }
          args_stack_index += arg_class->field_ids->length;
        }
        else {
          croak("%dth argument of %s->%s must be a hash reference at %s line %d\n", args_index_nth, class_name, method_name, MFILE, __LINE__);
        }
        break;
      }
      // Perl hash reference to SPVM double multi numeric type
      case SPVM_TYPE_C_TYPE_CATEGORY_MULNUM_DOUBLE: {
        if (sv_derived_from(sv_value, "HASH")) {
          SPVM_RUNTIME_BASIC_TYPE* arg_basic_type = SPVM_LIST_fetch(compiler->runtime_basic_types, arg_basic_type_id);
          SPVM_RUNTIME_CLASS* arg_class = SPVM_API_get_runtime_class_from_basic_type_id(env, arg_basic_type->id);
          HV* hv_value = (HV*)SvRV(sv_value);
          int32_t fields_length = arg_class->field_ids->length;
          for (int32_t field_index = 0; field_index < fields_length; field_index++) {
            SPVM_RUNTIME_FIELD* field = SPVM_API_get_runtime_field_from_index(env, arg_class->id, field_index);
            const char* field_name = field->name;
            SV** sv_field_value_ptr = hv_fetch(hv_value, field_name, strlen(field_name), 0);
            SV* sv_field_value;
            if (sv_field_value_ptr) {
              sv_field_value = *sv_field_value_ptr;
            }
            else {
              croak("%dth argument's field \"%s\" of \"%s\" is missing at %s line %d\n", args_index_nth, field_name, arg_class->name, MFILE, __LINE__);
            }
            double value = (double)SvNV(sv_field_value);
            args_stack[args_stack_index + field_index].dval = value;
          }
          args_stack_index += arg_class->field_ids->length;
        }
        else {
          croak("%dth argument of %s->%s must be a hash reference at %s line %d\n", args_index_nth, class_name, method_name, MFILE, __LINE__);
        }
        break;
      }
      case SPVM_TYPE_C_TYPE_CATEGORY_MULNUM_ARRAY:
      case SPVM_TYPE_C_TYPE_CATEGORY_NUMERIC_ARRAY:
      case SPVM_TYPE_C_TYPE_CATEGORY_OBJECT_ARRAY:
      {
        // Perl undef to SPVM undef
        if (!SvOK(sv_value)) {
          args_stack[args_stack_index].oval = NULL;
        }
        else {
          // Argument: Perl array referecne to SPVM array
          if (SvROK(sv_value) && sv_derived_from(sv_value, "ARRAY")) {
            
            SV* sv_elems = sv_value;
            
            AV* av_elems = (AV*)SvRV(sv_elems);
            
            int32_t length = av_len(av_elems) + 1;
            
            if (arg_type_dimension == 1 || arg_basic_type_id == SPVM_BASIC_TYPE_C_ID_OARRAY) {
              switch (arg_basic_type_id) {
                // Argument: Perl array referecne to SPVM byte array
                case SPVM_BASIC_TYPE_C_ID_BYTE: {
                  void* array = env->new_byte_array(env, length);
                  int8_t* elems = env->get_elems_byte(env, array);
                  for (int32_t i = 0; i < length; i++) {
                    SV** sv_value_ptr = av_fetch(av_elems, i, 0);
                    SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
                    elems[i] = (int8_t)SvIV(sv_value);
                  }
                  SV* sv_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
                  sv_value = sv_array;
                  break;
                }
                // Argument: Perl array referecne to SPVM short array
                case SPVM_BASIC_TYPE_C_ID_SHORT: {
                  void* array = env->new_short_array(env, length);
                  int16_t* elems = env->get_elems_short(env, array);
                  for (int32_t i = 0; i < length; i++) {
                    SV** sv_value_ptr = av_fetch(av_elems, i, 0);
                    SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
                    elems[i] = (int16_t)SvIV(sv_value);
                  }
                  SV* sv_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
                  sv_value = sv_array;
                  break;
                }
                // Argument: Perl array referecne to SPVM int array
                case SPVM_BASIC_TYPE_C_ID_INT: {
                  void* array = env->new_int_array(env, length);
                  int32_t* elems = env->get_elems_int(env, array);
                  for (int32_t i = 0; i < length; i++) {
                    SV** sv_value_ptr = av_fetch(av_elems, i, 0);
                    SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
                    elems[i] = (int32_t)SvIV(sv_value);
                  }
                  SV* sv_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
                  sv_value = sv_array;
                  break;
                }
                // Argument: Perl array referecne to SPVM long array
                case SPVM_BASIC_TYPE_C_ID_LONG: {
                  void* array = env->new_long_array(env, length);
                  int64_t* elems = env->get_elems_long(env, array);
                  for (int32_t i = 0; i < length; i++) {
                    SV** sv_value_ptr = av_fetch(av_elems, i, 0);
                    SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
                    elems[i] = (int64_t)SvIV(sv_value);
                  }
                  SV* sv_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
                  sv_value = sv_array;
                  break;
                }
                // Argument: Perl array referecne to SPVM float array
                case SPVM_BASIC_TYPE_C_ID_FLOAT: {
                  void* array = env->new_float_array(env, length);
                  float* elems = env->get_elems_float(env, array);
                  for (int32_t i = 0; i < length; i++) {
                    SV** sv_value_ptr = av_fetch(av_elems, i, 0);
                    SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
                    elems[i] = (float)SvNV(sv_value);
                  }
                  SV* sv_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
                  sv_value = sv_array;
                  break;
                }
                // Argument: Perl array referecne to SPVM double array
                case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
                  void* array = env->new_double_array(env, length);
                  double* elems = env->get_elems_double(env, array);
                  for (int32_t i = 0; i < length; i++) {
                    SV** sv_value_ptr = av_fetch(av_elems, i, 0);
                    SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
                    elems[i] = (double)SvNV(sv_value);
                  }
                  SV* sv_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
                  sv_value = sv_array;
                  break;
                }
                // Argument: Perl array referecne to SPVM string array
                case SPVM_BASIC_TYPE_C_ID_STRING: {
                  
                  void* array = env->new_object_array(env, SPVM_BASIC_TYPE_C_ID_STRING, length);
                  for (int32_t i = 0; i < length; i++) {
                    SV** sv_elem_ptr = av_fetch(av_elems, i, 0);
                    SV* sv_elem = sv_elem_ptr ? *sv_elem_ptr : &PL_sv_undef;
                    if (!SvOK(sv_elem)) {
                      env->set_elem_object(env, array, i, NULL);
                    }
                    else {
                      if (!SvROK(sv_elem)) {
                        SV* sv_elem_copy = sv_2mortal(newSVsv(sv_elem));
                        sv_utf8_encode(sv_elem_copy);
                        const char* chars = SvPV_nolen(sv_elem_copy);
                        int32_t length = SvCUR(sv_elem_copy);
                        void* string = env->new_string(env, chars, length);
                        SV* sv_string = SPVM_XS_UTIL_new_sv_object(env, string, "SPVM::BlessedObject::String");
                        sv_elem = sv_string;
                      }
                      if (sv_isobject(sv_elem) && sv_derived_from(sv_elem, "SPVM::BlessedObject::String")) {
                        SPVM_OBJECT* object = SPVM_XS_UTIL_get_object(sv_elem);
                        env->set_elem_object(env, array, i, object);
                      }
                      else {
                        croak("%dth argument of %s->%s must be inherit SPVM::BlessedObject::String at %s line %d\n", args_index_nth, class_name, method_name, MFILE, __LINE__);
                      }
                    }
                  }
                  SV* sv_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
                  sv_value = sv_array;

                  break;
                }
                case SPVM_BASIC_TYPE_C_ID_ANY_OBJECT:
                case SPVM_BASIC_TYPE_C_ID_OARRAY:
                {
                  // New array
                  void* array = env->new_object_array(env, SPVM_BASIC_TYPE_C_ID_ANY_OBJECT, length);

                  for (int32_t i = 0; i < length; i++) {
                    SV** sv_value_ptr = av_fetch(av_elems, i, 0);
                    SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
                    if (SvOK(sv_value)) {
                      
                      // Convert non-ref scalar to byte[]
                      if (!SvROK(sv_value)) {
                        // Copy
                        SV* sv_value_copy = sv_2mortal(newSVsv(sv_value));
                        
                        // Encode to UTF-8
                        sv_utf8_encode(sv_value_copy);
                        
                        int32_t length = sv_len(sv_value_copy);
                        const char* chars = SvPV_nolen(sv_value_copy);
                        
                        void* string = env->new_string_raw(env, chars, length);
                        env->inc_ref_count(env, string);
                        
                        sv_value = SPVM_XS_UTIL_new_sv_object(env, string, "SPVM::BlessedObject::Array");
                      }
                      
                      if (!sv_derived_from(sv_value, "SPVM::BlessedObject")) {
                        croak("Element of %dth argument of %s->%s must inherit SPVM::BlessedObject object at %s line %d\n", args_index_nth, class_name, method_name, MFILE, __LINE__);
                      }
                      
                      env->set_elem_object(env, array, i, SPVM_XS_UTIL_get_object(sv_value));
                    }
                    else {
                      env->set_elem_object(env, array, i, NULL);
                    }
                  }
                  
                  // New sv array
                  SV* sv_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
                  sv_value = sv_array;
                  break;
                }
                default: {
                  if (arg_type->category == SPVM_TYPE_C_TYPE_CATEGORY_MULNUM_ARRAY) {
                    SV* sv_error = NULL;
                    SPVM_RUNTIME_BASIC_TYPE* arg_basic_type = SPVM_LIST_fetch(compiler->runtime_basic_types, arg_basic_type_id);
                    const char* arg_basic_type_name = arg_basic_type->name;
                    SPVM_OBJECT* array = SPVM_XS_UTIL_new_mulnum_array(env, arg_basic_type_name, sv_value, &sv_error);
                    if (sv_error) {
                      croak_sv(sv_error);
                    }
                    SV* sv_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
                    sv_value = sv_array;
                  }
                  else {
                    assert(0);
                  }
                }
              }
            }
          }
          
          if (sv_isobject(sv_value) && sv_derived_from(sv_value, "SPVM::BlessedObject::Array")) {
            SPVM_OBJECT* object = SPVM_XS_UTIL_get_object(sv_value);
            
            if (arg_basic_type_id == SPVM_BASIC_TYPE_C_ID_OARRAY) {
              if (object->type_dimension == 0) {
                croak("%dth argument of %s->%s is invalid object type at %s line %d\n", args_index_nth, class_name, method_name, MFILE, __LINE__);
              }
            }
            else {
              if (!(object->basic_type_id == arg_basic_type_id && object->type_dimension == arg_type_dimension)) {
                croak("%dth argument of %s->%s is invalid object type at %s line %d\n", args_index_nth, class_name, method_name, MFILE, __LINE__);
              }
            }
            
            args_stack[args_stack_index].oval = object;
          }
          else {
            croak("%dth argument of %s->%s must be a valid array reference or SPVM::BlessedObject::Array at %s line %d\n", args_index_nth, class_name, method_name, MFILE, __LINE__);
          }
        }
        
        args_stack_index++;
        break;
      }
      // Perl reference to SPVM byte reference
      case SPVM_TYPE_C_TYPE_CATEGORY_REF_BYTE: {
        args_have_ref = 1;
        if (!(SvROK(sv_value) && !SvROK(SvRV(sv_value)))) {
          croak("%dth argument of %s->%s must be sa calar reference which referenced value is non-ref scalar at %s line %d\n", args_index_nth, class_name, method_name, MFILE, __LINE__);
        }
        SV* sv_value_deref = SvRV(sv_value);
        int8_t value = (int8_t)SvIV(sv_value_deref);
        ref_stack[ref_stack_index].bval = value;
        args_stack[args_stack_index].oval = &ref_stack[ref_stack_index];
        ref_stack_indexes[args_index] = ref_stack_index;
        ref_stack_index++;
        args_stack_index++;
        break;
      }
      // Perl reference to SPVM short reference
      case SPVM_TYPE_C_TYPE_CATEGORY_REF_SHORT: {
        args_have_ref = 1;
        if (!(SvROK(sv_value) && !SvROK(SvRV(sv_value)))) {
          croak("%dth argument of %s->%s must be a scalar reference which referenced value is non-ref scalar at %s line %d\n", args_index_nth, class_name, method_name, MFILE, __LINE__);
        }
        SV* sv_value_deref = SvRV(sv_value);
        int16_t value = (int16_t)SvIV(sv_value_deref);
        ref_stack[ref_stack_index].sval = value;
        args_stack[args_stack_index].oval = &ref_stack[ref_stack_index];
        ref_stack_indexes[args_index] = ref_stack_index;
        ref_stack_index++;
        args_stack_index++;
        break;
      }
      // Perl reference to SPVM int reference
      case SPVM_TYPE_C_TYPE_CATEGORY_REF_INT: {
        args_have_ref = 1;
        if (!(SvROK(sv_value) && !SvROK(SvRV(sv_value)))) {
          croak("%dth argument of %s->%s must be a scalar reference which referenced value is non-ref scalar at %s line %d\n", args_index_nth, class_name, method_name, MFILE, __LINE__);
        }
        SV* sv_value_deref = SvRV(sv_value);
        int32_t value = (int32_t)SvIV(sv_value_deref);
        ref_stack[ref_stack_index].ival = value;
        args_stack[args_stack_index].oval = &ref_stack[ref_stack_index];
        ref_stack_indexes[args_index] = ref_stack_index;
        ref_stack_index++;
        args_stack_index++;
        break;
      }
      // Perl reference to SPVM long reference
      case SPVM_TYPE_C_TYPE_CATEGORY_REF_LONG: {
        args_have_ref = 1;
        if (!(SvROK(sv_value) && !SvROK(SvRV(sv_value)))) {
          croak("%dth argument of %s->%s must be a scalar reference which referenced value is non-ref scalar at %s line %d\n", args_index_nth, class_name, method_name, MFILE, __LINE__);
        }
        SV* sv_value_deref = SvRV(sv_value);
        int64_t value = (int64_t)SvIV(sv_value_deref);
        ref_stack[ref_stack_index].lval = value;
        args_stack[args_stack_index].oval = &ref_stack[ref_stack_index];
        ref_stack_indexes[args_index] = ref_stack_index;
        ref_stack_index++;
        args_stack_index++;
        break;
      }
      // Perl reference to SPVM long reference
      case SPVM_TYPE_C_TYPE_CATEGORY_REF_FLOAT: {
        args_have_ref = 1;
        if (!(SvROK(sv_value) && !SvROK(SvRV(sv_value)))) {
          croak("%dth argument of %s->%s must be a scalar reference which referenced value is non-ref scalar at %s line %d\n", args_index_nth, class_name, method_name, MFILE, __LINE__);
        }
        SV* sv_value_deref = SvRV(sv_value);
        float value = (float)SvNV(sv_value_deref);
        ref_stack[ref_stack_index].fval = value;
        args_stack[args_stack_index].oval = &ref_stack[ref_stack_index];
        ref_stack_indexes[args_index] = ref_stack_index;
        ref_stack_index++;
        args_stack_index++;
        break;
      }
      // Perl reference to SPVM double reference
      case SPVM_TYPE_C_TYPE_CATEGORY_REF_DOUBLE: {
        args_have_ref = 1;
        if (!(SvROK(sv_value) && !SvROK(SvRV(sv_value)))) {
          croak("%dth argument of %s->%s must be a scalar reference which referenced value is non-ref scalar at %s line %d\n", args_index_nth, class_name, method_name, MFILE, __LINE__);
        }
        SV* sv_value_deref = SvRV(sv_value);
        double value = (double)SvNV(sv_value_deref);
        ref_stack[ref_stack_index].dval = value;
        args_stack[args_stack_index].oval = &ref_stack[ref_stack_index];
        ref_stack_indexes[args_index] = ref_stack_index;
        ref_stack_index++;
        args_stack_index++;
        break;
      }
      case SPVM_TYPE_C_TYPE_CATEGORY_REF_MULNUM_BYTE: {
        args_have_ref = 1;
        HV* hv_value = NULL;
        if (SvOK(sv_value)) {
          if (SvROK(sv_value) && sv_derived_from(sv_value, "REF")) {
            SV* hv_value_ref = SvRV(sv_value);
            if (SvROK(hv_value_ref) && sv_derived_from(hv_value_ref , "HASH")) {
              hv_value = (HV*)SvRV(hv_value_ref);
            }
          }
        }
        if (hv_value == NULL) {
          croak("%dth argument of %s->%s must be a scalar reference of hash reference at %s line %d\n", args_index_nth, class_name, method_name, MFILE, __LINE__);
        }
        SPVM_RUNTIME_BASIC_TYPE* arg_basic_type = SPVM_LIST_fetch(compiler->runtime_basic_types, arg_basic_type_id);
        SPVM_RUNTIME_CLASS* arg_class = SPVM_API_get_runtime_class_from_basic_type_id(env, arg_basic_type->id);
        int32_t fields_length = arg_class->field_ids->length;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          SPVM_RUNTIME_FIELD* field = SPVM_API_get_runtime_field_from_index(env, arg_class->id, field_index);
          const char* field_name = field->name;
          SV** sv_field_value_ptr = hv_fetch(hv_value, field_name, strlen(field_name), 0);
          SV* sv_field_value;
          if (sv_field_value_ptr) {
            sv_field_value = *sv_field_value_ptr;
          }
          else {
            croak("%dth argument's field \"%s\" of \"%s\" is missing at %s line %d\n", args_index_nth, field_name, arg_class->name, MFILE, __LINE__);
          }
          int8_t value = (int8_t)SvIV(sv_field_value);
          ((int8_t*)&ref_stack[ref_stack_index])[field_index] = value;
        }
        args_stack[args_stack_index].oval = &ref_stack[ref_stack_index];
        ref_stack_indexes[args_index] = ref_stack_index;
        ref_stack_index += fields_length;
        args_stack_index++;
        
        break;
      }
      case SPVM_TYPE_C_TYPE_CATEGORY_REF_MULNUM_SHORT: {
        args_have_ref = 1;
        HV* hv_value = NULL;
        if (SvOK(sv_value)) {
          if (SvROK(sv_value) && sv_derived_from(sv_value, "REF")) {
            SV* hv_value_ref = SvRV(sv_value);
            if (SvROK(hv_value_ref) && sv_derived_from(hv_value_ref , "HASH")) {
              hv_value = (HV*)SvRV(hv_value_ref);
            }
          }
        }
        if (hv_value == NULL) {
          croak("%dth argument of %s->%s must be a scalar reference of hash reference at %s line %d\n", args_index_nth, class_name, method_name, MFILE, __LINE__);
        }
        SPVM_RUNTIME_BASIC_TYPE* arg_basic_type = SPVM_LIST_fetch(compiler->runtime_basic_types, arg_basic_type_id);
        SPVM_RUNTIME_CLASS* arg_class = SPVM_API_get_runtime_class_from_basic_type_id(env, arg_basic_type->id);
        int32_t fields_length = arg_class->field_ids->length;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          SPVM_RUNTIME_FIELD* field = SPVM_API_get_runtime_field_from_index(env, arg_class->id, field_index);
          const char* field_name = field->name;
          SV** sv_field_value_ptr = hv_fetch(hv_value, field_name, strlen(field_name), 0);
          SV* sv_field_value;
          if (sv_field_value_ptr) {
            sv_field_value = *sv_field_value_ptr;
          }
          else {
            croak("%dth argument's field \"%s\" of \"%s\" is missing at %s line %d\n", args_index_nth, field_name, arg_class->name, MFILE, __LINE__);
          }
          int16_t value = (int16_t)SvIV(sv_field_value);
          ((int16_t*)&ref_stack[ref_stack_index])[field_index] = value;
        }
        args_stack[args_stack_index].oval = &ref_stack[ref_stack_index];
        ref_stack_indexes[args_index] = ref_stack_index;
        ref_stack_index += fields_length;
        args_stack_index++;
        break;
      }
      case SPVM_TYPE_C_TYPE_CATEGORY_REF_MULNUM_INT: {
        args_have_ref = 1;
        HV* hv_value = NULL;
        if (SvOK(sv_value)) {
          if (SvROK(sv_value) && sv_derived_from(sv_value, "REF")) {
            SV* hv_value_ref = SvRV(sv_value);
            if (SvROK(hv_value_ref) && sv_derived_from(hv_value_ref , "HASH")) {
              hv_value = (HV*)SvRV(hv_value_ref);
            }
          }
        }
        if (hv_value == NULL) {
          croak("%dth argument of %s->%s must be a scalar reference of hash reference at %s line %d\n", args_index_nth, class_name, method_name, MFILE, __LINE__);
        }
        SPVM_RUNTIME_BASIC_TYPE* arg_basic_type = SPVM_LIST_fetch(compiler->runtime_basic_types, arg_basic_type_id);
        SPVM_RUNTIME_CLASS* arg_class = SPVM_API_get_runtime_class_from_basic_type_id(env, arg_basic_type->id);
        int32_t fields_length = arg_class->field_ids->length;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          SPVM_RUNTIME_FIELD* field = SPVM_API_get_runtime_field_from_index(env, arg_class->id, field_index);
          const char* field_name = field->name;
          SV** sv_field_value_ptr = hv_fetch(hv_value, field_name, strlen(field_name), 0);
          SV* sv_field_value;
          if (sv_field_value_ptr) {
            sv_field_value = *sv_field_value_ptr;
          }
          else {
            croak("%dth argument's field \"%s\" of \"%s\" is missing at %s line %d\n", args_index_nth, field_name, arg_class->name, MFILE, __LINE__);
          }
          int32_t value = (int32_t)SvIV(sv_field_value);
          ((int32_t*)&ref_stack[ref_stack_index])[field_index] = value;
        }
        args_stack[args_stack_index].oval = &ref_stack[ref_stack_index];
        ref_stack_indexes[args_index] = ref_stack_index;
        ref_stack_index += fields_length;
        args_stack_index++;
        break;
      }
      case SPVM_TYPE_C_TYPE_CATEGORY_REF_MULNUM_LONG: {
        args_have_ref = 1;
        HV* hv_value = NULL;
        if (SvOK(sv_value)) {
          if (SvROK(sv_value) && sv_derived_from(sv_value, "REF")) {
            SV* hv_value_ref = SvRV(sv_value);
            if (SvROK(hv_value_ref) && sv_derived_from(hv_value_ref , "HASH")) {
              hv_value = (HV*)SvRV(hv_value_ref);
            }
          }
        }
        if (hv_value == NULL) {
          croak("%dth argument of %s->%s must be a scalar reference of hash reference at %s line %d\n", args_index_nth, class_name, method_name, MFILE, __LINE__);
        }
        SPVM_RUNTIME_BASIC_TYPE* arg_basic_type = SPVM_LIST_fetch(compiler->runtime_basic_types, arg_basic_type_id);
        SPVM_RUNTIME_CLASS* arg_class = SPVM_API_get_runtime_class_from_basic_type_id(env, arg_basic_type->id);
        int32_t fields_length = arg_class->field_ids->length;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          SPVM_RUNTIME_FIELD* field = SPVM_API_get_runtime_field_from_index(env, arg_class->id, field_index);
          const char* field_name = field->name;
          SV** sv_field_value_ptr = hv_fetch(hv_value, field_name, strlen(field_name), 0);
          SV* sv_field_value;
          if (sv_field_value_ptr) {
            sv_field_value = *sv_field_value_ptr;
          }
          else {
            croak("%dth argument's field \"%s\" of \"%s\" is missing at %s line %d\n", args_index_nth, field_name, arg_class->name, MFILE, __LINE__);
          }
          int64_t value = (int64_t)SvIV(sv_field_value);
          ((int64_t*)&ref_stack[ref_stack_index])[field_index] = value;
        }
        args_stack[args_stack_index].oval = &ref_stack[ref_stack_index];
        ref_stack_indexes[args_index] = ref_stack_index;
        ref_stack_index += fields_length;
        args_stack_index++;
        break;
      }
      case SPVM_TYPE_C_TYPE_CATEGORY_REF_MULNUM_FLOAT: {
        args_have_ref = 1;
        HV* hv_value = NULL;
        if (SvOK(sv_value)) {
          if (SvROK(sv_value) && sv_derived_from(sv_value, "REF")) {
            SV* hv_value_ref = SvRV(sv_value);
            if (SvROK(hv_value_ref) && sv_derived_from(hv_value_ref , "HASH")) {
              hv_value = (HV*)SvRV(hv_value_ref);
            }
          }
        }
        if (hv_value == NULL) {
          croak("%dth argument of %s->%s must be a scalar reference of hash reference at %s line %d\n", args_index_nth, class_name, method_name, MFILE, __LINE__);
        }
        SPVM_RUNTIME_BASIC_TYPE* arg_basic_type = SPVM_LIST_fetch(compiler->runtime_basic_types, arg_basic_type_id);
        SPVM_RUNTIME_CLASS* arg_class = SPVM_API_get_runtime_class_from_basic_type_id(env, arg_basic_type->id);
        int32_t fields_length = arg_class->field_ids->length;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          SPVM_RUNTIME_FIELD* field = SPVM_API_get_runtime_field_from_index(env, arg_class->id, field_index);
          const char* field_name = field->name;
          SV** sv_field_value_ptr = hv_fetch(hv_value, field_name, strlen(field_name), 0);
          SV* sv_field_value;
          if (sv_field_value_ptr) {
            sv_field_value = *sv_field_value_ptr;
          }
          else {
            croak("%dth argument's field \"%s\" of \"%s\" is missing at %s line %d\n", args_index_nth, field_name, arg_class->name, MFILE, __LINE__);
          }
          float value = (float)SvNV(sv_field_value);
          ((float*)&ref_stack[ref_stack_index])[field_index] = value;
        }
        args_stack[args_stack_index].oval = &ref_stack[ref_stack_index];
        ref_stack_indexes[args_index] = ref_stack_index;
        ref_stack_index += fields_length;
        args_stack_index++;
        break;
      }
      case SPVM_TYPE_C_TYPE_CATEGORY_REF_MULNUM_DOUBLE: {
        args_have_ref = 1;
        HV* hv_value = NULL;
        if (SvOK(sv_value)) {
          if (SvROK(sv_value) && sv_derived_from(sv_value, "REF")) {
            SV* hv_value_ref = SvRV(sv_value);
            if (SvROK(hv_value_ref) && sv_derived_from(hv_value_ref , "HASH")) {
              hv_value = (HV*)SvRV(hv_value_ref);
            }
          }
        }
        if (hv_value == NULL) {
          croak("%dth argument of %s->%s must be a scalar reference of hash reference at %s line %d\n", args_index_nth, class_name, method_name, MFILE, __LINE__);
        }
        SPVM_RUNTIME_BASIC_TYPE* arg_basic_type = SPVM_LIST_fetch(compiler->runtime_basic_types, arg_basic_type_id);
        SPVM_RUNTIME_CLASS* arg_class = SPVM_API_get_runtime_class_from_basic_type_id(env, arg_basic_type->id);
        int32_t fields_length = arg_class->field_ids->length;
        for (int32_t field_index = 0; field_index < fields_length; field_index++) {
          SPVM_RUNTIME_FIELD* field = SPVM_API_get_runtime_field_from_index(env, arg_class->id, field_index);
          const char* field_name = field->name;
          SV** sv_field_value_ptr = hv_fetch(hv_value, field_name, strlen(field_name), 0);
          SV* sv_field_value;
          if (sv_field_value_ptr) {
            sv_field_value = *sv_field_value_ptr;
          }
          else {
            croak("%dth argument's field \"%s\" of \"%s\" is missing at %s line %d\n", args_index_nth, field_name, arg_class->name, MFILE, __LINE__);
          }
          double value = (double)SvNV(sv_field_value);
          ((double*)&ref_stack[ref_stack_index])[field_index] = value;
        }
        args_stack[args_stack_index].oval = &ref_stack[ref_stack_index];
        ref_stack_indexes[args_index] = ref_stack_index;
        ref_stack_index += fields_length;
        args_stack_index++;
        break;
      }
      default:
        assert(0);
    }
  }
  
  // Return
  SPVM_RUNTIME_TYPE* method_return_type = SPVM_LIST_fetch(compiler->runtime_types, method->return_type_id);
  int32_t method_return_basic_type_id = method_return_type->basic_type_id;
  int32_t method_return_type_dimension = method_return_type->dimension;

  SV* sv_return_value = NULL;
  int32_t excetpion_flag = 0;
  switch (method_return_type->category) {
    case SPVM_TYPE_C_TYPE_CATEGORY_VOID: {
      excetpion_flag = env->call_spvm_method(env, method->id, args_stack);
      break;
    }
    case SPVM_TYPE_C_TYPE_CATEGORY_BYTE: {
      excetpion_flag = env->call_spvm_method(env, method->id, args_stack);
      if (!excetpion_flag) {
        sv_return_value = sv_2mortal(newSViv(args_stack[0].bval));
      }
      break;
    }
    case SPVM_TYPE_C_TYPE_CATEGORY_SHORT: {
      excetpion_flag = env->call_spvm_method(env, method->id, args_stack);
      if (!excetpion_flag) {
        sv_return_value = sv_2mortal(newSViv(args_stack[0].sval));
      }
      break;
    }
    case SPVM_TYPE_C_TYPE_CATEGORY_INT: {
      excetpion_flag = env->call_spvm_method(env, method->id, args_stack);
      if (!excetpion_flag) {
        sv_return_value = sv_2mortal(newSViv(args_stack[0].ival));
      }
      break;
    }
    case SPVM_TYPE_C_TYPE_CATEGORY_LONG: {
      excetpion_flag = env->call_spvm_method(env, method->id, args_stack);
      if (!excetpion_flag) {
        sv_return_value = sv_2mortal(newSViv(args_stack[0].lval));
      }
      break;
    }
    case SPVM_TYPE_C_TYPE_CATEGORY_FLOAT: {
      excetpion_flag = env->call_spvm_method(env, method->id, args_stack);
      if (!excetpion_flag) {
        sv_return_value = sv_2mortal(newSVnv(args_stack[0].fval));
      }
      break;
    }
    case SPVM_TYPE_C_TYPE_CATEGORY_DOUBLE: {
      excetpion_flag = env->call_spvm_method(env, method->id, args_stack);
      if (!excetpion_flag) {
        sv_return_value = sv_2mortal(newSVnv(args_stack[0].dval));
      }
      break;
    }
    case SPVM_TYPE_C_TYPE_CATEGORY_STRING:
    case SPVM_TYPE_C_TYPE_CATEGORY_CLASS:
    case SPVM_TYPE_C_TYPE_CATEGORY_ANY_OBJECT:
    case SPVM_TYPE_C_TYPE_CATEGORY_NUMERIC_ARRAY:
    case SPVM_TYPE_C_TYPE_CATEGORY_OBJECT_ARRAY:
    case SPVM_TYPE_C_TYPE_CATEGORY_MULNUM_ARRAY:
    {
      excetpion_flag = env->call_spvm_method(env, method->id, args_stack);
      
      if (!excetpion_flag) {
        SPVM_OBJECT* return_value = (SPVM_OBJECT*)args_stack[0].oval;
        sv_return_value = NULL;
        if (return_value != NULL) {
          env->inc_ref_count(env, return_value);
          
          // Array
          if (return_value->type_dimension > 0) {
            sv_return_value = SPVM_XS_UTIL_new_sv_object(env, return_value, "SPVM::BlessedObject::Array");
          }
          else {
            
            // String
            if (return_value->basic_type_id == SPVM_BASIC_TYPE_C_ID_STRING) {
              sv_return_value = SPVM_XS_UTIL_new_sv_object(env, return_value, "SPVM::BlessedObject::String");
            }
            // Object
            else {
              SPVM_RUNTIME_BASIC_TYPE* method_return_basic_type = SPVM_LIST_fetch(compiler->runtime_basic_types, return_value->basic_type_id);
              SV* sv_perl_class_name = sv_2mortal(newSVpv("SPVM::", 0));
              sv_catpv(sv_perl_class_name, method_return_basic_type->name);
              sv_return_value = SPVM_XS_UTIL_new_sv_object(env, return_value, SvPV_nolen(sv_perl_class_name));
            }
          }
        }
        // undef
        else {
          sv_return_value = &PL_sv_undef;
        }
      }
      break;
    }
    case SPVM_TYPE_C_TYPE_CATEGORY_MULNUM_BYTE:
    case SPVM_TYPE_C_TYPE_CATEGORY_MULNUM_SHORT:
    case SPVM_TYPE_C_TYPE_CATEGORY_MULNUM_INT:
    case SPVM_TYPE_C_TYPE_CATEGORY_MULNUM_LONG:
    case SPVM_TYPE_C_TYPE_CATEGORY_MULNUM_FLOAT:
    case SPVM_TYPE_C_TYPE_CATEGORY_MULNUM_DOUBLE:
    {
      excetpion_flag = env->call_spvm_method(env, method->id, args_stack);
      
      SPVM_RUNTIME_BASIC_TYPE* method_return_basic_type = SPVM_LIST_fetch(compiler->runtime_basic_types, method_return_basic_type_id);

      SPVM_RUNTIME_CLASS* method_return_class = SPVM_API_get_runtime_class_from_basic_type_id(env, method_return_basic_type->id);
      assert(method_return_class);
      
      SPVM_RUNTIME_FIELD* method_return_first_field = SPVM_API_get_runtime_field_from_index(env, method_return_class->id, 0);
      assert(method_return_first_field);
      
      HV* hv_value = (HV*)sv_2mortal((SV*)newHV());
      for (int32_t field_index = 0; field_index < method_return_class->field_ids->length; field_index++) {
        SPVM_RUNTIME_FIELD* field = SPVM_API_get_runtime_field_from_index(env, method_return_class->id, field_index);
        const char* field_name = field->name;
        
        SV* sv_field_value = NULL;
        SPVM_RUNTIME_TYPE* method_return_first_field_type = SPVM_LIST_fetch(compiler->runtime_types, method_return_first_field->type_id);
        switch (method_return_first_field_type->basic_type_id) {
          case SPVM_BASIC_TYPE_C_ID_BYTE: {
            sv_field_value = sv_2mortal(newSViv(args_stack[field_index].bval));
            break;
          }
          case SPVM_BASIC_TYPE_C_ID_SHORT: {
            sv_field_value = sv_2mortal(newSViv(args_stack[field_index].sval));
            break;
          }
          case SPVM_BASIC_TYPE_C_ID_INT: {
            sv_field_value = sv_2mortal(newSViv(args_stack[field_index].ival));
            break;
          }
          case SPVM_BASIC_TYPE_C_ID_LONG: {
            sv_field_value = sv_2mortal(newSViv(args_stack[field_index].lval));
            break;
          }
          case SPVM_BASIC_TYPE_C_ID_FLOAT: {
            sv_field_value = sv_2mortal(newSVnv(args_stack[field_index].fval));
            break;
          }
          case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
            sv_field_value = sv_2mortal(newSVnv(args_stack[field_index].dval));
            break;
          }
          default:
            assert(0);
        }
        
        (void)hv_store(hv_value, field_name, strlen(field_name), SvREFCNT_inc(sv_field_value), 0);
        sv_return_value = sv_2mortal(newRV_inc((SV*)hv_value));
      }
      break;
    }
    default:
      assert(0);
  }
  
  // Restore reference value
  if (args_have_ref) {
    for (int32_t args_index = 0; args_index < method->arg_type_ids->length; args_index++) {
      SV* sv_value = ST(spvm_args_base + args_index);
      
      int32_t arg_type_id = (intptr_t)SPVM_LIST_fetch(method->arg_type_ids, args_index);
      SPVM_RUNTIME_TYPE* arg_type = SPVM_LIST_fetch(compiler->runtime_types, arg_type_id);
      
      // Convert to runtime type
      int32_t arg_basic_type_id = arg_type->basic_type_id;
      int32_t arg_type_dimension = arg_type->dimension;
      
      int32_t ref_stack_index = ref_stack_indexes[args_index];
      switch (arg_type->category) {
        case SPVM_TYPE_C_TYPE_CATEGORY_REF_BYTE : {
          SV* sv_value_deref = SvRV(sv_value);
          sv_setiv(sv_value_deref, ref_stack[ref_stack_index].bval);
          break;
        }
        case SPVM_TYPE_C_TYPE_CATEGORY_REF_SHORT : {
          SV* sv_value_deref = SvRV(sv_value);
          sv_setiv(sv_value_deref, ref_stack[ref_stack_index].sval);
          break;
        }
        case SPVM_TYPE_C_TYPE_CATEGORY_REF_INT : {
          SV* sv_value_deref = SvRV(sv_value);
          sv_setiv(sv_value_deref, ref_stack[ref_stack_index].ival);
          break;
        }
        case SPVM_TYPE_C_TYPE_CATEGORY_REF_LONG : {
          SV* sv_value_deref = SvRV(sv_value);
          sv_setiv(sv_value_deref, ref_stack[ref_stack_index].lval);
          break;
        }
        case SPVM_TYPE_C_TYPE_CATEGORY_REF_FLOAT : {
          SV* sv_value_deref = SvRV(sv_value);
          sv_setnv(sv_value_deref, ref_stack[ref_stack_index].fval);
          break;
        }
        case SPVM_TYPE_C_TYPE_CATEGORY_REF_DOUBLE : {
          SV* sv_value_deref = SvRV(sv_value);
          sv_setnv(sv_value_deref, ref_stack[ref_stack_index].dval);
          break;
        }
        case SPVM_TYPE_C_TYPE_CATEGORY_REF_MULNUM_BYTE: {
          SPVM_RUNTIME_BASIC_TYPE* arg_basic_type = SPVM_LIST_fetch(compiler->runtime_basic_types, arg_basic_type_id);
          HV* hv_value = (HV*)SvRV(SvRV(sv_value));
          SPVM_RUNTIME_CLASS* arg_class = SPVM_API_get_runtime_class_from_basic_type_id(env, arg_basic_type->id);
          assert(arg_class);
          SPVM_RUNTIME_FIELD* arg_first_field = SPVM_API_get_runtime_field_from_index(env, arg_class->id, 0);
          assert(arg_first_field);
          for (int32_t field_index = 0; field_index < arg_class->field_ids->length; field_index++) {
            SPVM_RUNTIME_FIELD* field = SPVM_API_get_runtime_field_from_index(env, arg_class->id, field_index);
            const char* field_name = field->name;
            SV* sv_field_value = sv_2mortal(newSViv(((int8_t*)&ref_stack[ref_stack_index])[field_index]));
            (void)hv_store(hv_value, field_name, strlen(field_name), SvREFCNT_inc(sv_field_value), 0);
          }
          break;
        }
        case SPVM_TYPE_C_TYPE_CATEGORY_REF_MULNUM_SHORT: {
          SPVM_RUNTIME_BASIC_TYPE* arg_basic_type = SPVM_LIST_fetch(compiler->runtime_basic_types, arg_basic_type_id);
          HV* hv_value = (HV*)SvRV(SvRV(sv_value));
          SPVM_RUNTIME_CLASS* arg_class = SPVM_API_get_runtime_class_from_basic_type_id(env, arg_basic_type->id);
          assert(arg_class);
          SPVM_RUNTIME_FIELD* arg_first_field = SPVM_API_get_runtime_field_from_index(env, arg_class->id, 0);
          assert(arg_first_field);
          for (int32_t field_index = 0; field_index < arg_class->field_ids->length; field_index++) {
            SPVM_RUNTIME_FIELD* field = SPVM_API_get_runtime_field_from_index(env, arg_class->id, field_index);
            const char* field_name = field->name;
            SV* sv_field_value = sv_2mortal(newSViv(((int16_t*)&ref_stack[ref_stack_index])[field_index]));
            (void)hv_store(hv_value, field_name, strlen(field_name), SvREFCNT_inc(sv_field_value), 0);
          }
          break;
        }
        case SPVM_TYPE_C_TYPE_CATEGORY_REF_MULNUM_INT: {
          SPVM_RUNTIME_BASIC_TYPE* arg_basic_type = SPVM_LIST_fetch(compiler->runtime_basic_types, arg_basic_type_id);
          HV* hv_value = (HV*)SvRV(SvRV(sv_value));
          SPVM_RUNTIME_CLASS* arg_class = SPVM_API_get_runtime_class_from_basic_type_id(env, arg_basic_type->id);
          assert(arg_class);
          SPVM_RUNTIME_FIELD* arg_first_field = SPVM_API_get_runtime_field_from_index(env, arg_class->id, 0);
          assert(arg_first_field);
          for (int32_t field_index = 0; field_index < arg_class->field_ids->length; field_index++) {
            SPVM_RUNTIME_FIELD* field = SPVM_API_get_runtime_field_from_index(env, arg_class->id, field_index);
            const char* field_name = field->name;
            SV* sv_field_value = sv_2mortal(newSViv(((int32_t*)&ref_stack[ref_stack_index])[field_index]));
            (void)hv_store(hv_value, field_name, strlen(field_name), SvREFCNT_inc(sv_field_value), 0);
          }
          break;
        }
        case SPVM_TYPE_C_TYPE_CATEGORY_REF_MULNUM_LONG: {
          SPVM_RUNTIME_BASIC_TYPE* arg_basic_type = SPVM_LIST_fetch(compiler->runtime_basic_types, arg_basic_type_id);
          HV* hv_value = (HV*)SvRV(SvRV(sv_value));
          SPVM_RUNTIME_CLASS* arg_class = SPVM_API_get_runtime_class_from_basic_type_id(env, arg_basic_type->id);
          assert(arg_class);
          SPVM_RUNTIME_FIELD* arg_first_field = SPVM_API_get_runtime_field_from_index(env, arg_class->id, 0);
          assert(arg_first_field);
          for (int32_t field_index = 0; field_index < arg_class->field_ids->length; field_index++) {
            SPVM_RUNTIME_FIELD* field = SPVM_API_get_runtime_field_from_index(env, arg_class->id, field_index);
            const char* field_name = field->name;
            SV* sv_field_value = sv_2mortal(newSViv(((int64_t*)&ref_stack[ref_stack_index])[field_index]));
            (void)hv_store(hv_value, field_name, strlen(field_name), SvREFCNT_inc(sv_field_value), 0);
          }
          break;
        }
        case SPVM_TYPE_C_TYPE_CATEGORY_REF_MULNUM_FLOAT: {
          SPVM_RUNTIME_BASIC_TYPE* arg_basic_type = SPVM_LIST_fetch(compiler->runtime_basic_types, arg_basic_type_id);
          HV* hv_value = (HV*)SvRV(SvRV(sv_value));
          SPVM_RUNTIME_CLASS* arg_class = SPVM_API_get_runtime_class_from_basic_type_id(env, arg_basic_type->id);
          assert(arg_class);
          SPVM_RUNTIME_FIELD* arg_first_field = SPVM_API_get_runtime_field_from_index(env, arg_class->id, 0);
          assert(arg_first_field);
          for (int32_t field_index = 0; field_index < arg_class->field_ids->length; field_index++) {
            SPVM_RUNTIME_FIELD* field = SPVM_API_get_runtime_field_from_index(env, arg_class->id, field_index);
            const char* field_name = field->name;
            SV* sv_field_value = sv_2mortal(newSVnv(((float*)&ref_stack[ref_stack_index])[field_index]));
            (void)hv_store(hv_value, field_name, strlen(field_name), SvREFCNT_inc(sv_field_value), 0);
          }
          break;
        }
        case SPVM_TYPE_C_TYPE_CATEGORY_REF_MULNUM_DOUBLE: {
          SPVM_RUNTIME_BASIC_TYPE* arg_basic_type = SPVM_LIST_fetch(compiler->runtime_basic_types, arg_basic_type_id);
          HV* hv_value = (HV*)SvRV(SvRV(sv_value));
          SPVM_RUNTIME_CLASS* arg_class = SPVM_API_get_runtime_class_from_basic_type_id(env, arg_basic_type->id);
          assert(arg_class);
          SPVM_RUNTIME_FIELD* arg_first_field = SPVM_API_get_runtime_field_from_index(env, arg_class->id, 0);
          assert(arg_first_field);
          for (int32_t field_index = 0; field_index < arg_class->field_ids->length; field_index++) {
            SPVM_RUNTIME_FIELD* field = SPVM_API_get_runtime_field_from_index(env, arg_class->id, field_index);
            const char* field_name = field->name;
            SV* sv_field_value = sv_2mortal(newSVnv(((double*)&ref_stack[ref_stack_index])[field_index]));
            (void)hv_store(hv_value, field_name, strlen(field_name), SvREFCNT_inc(sv_field_value), 0);
          }
          break;
        }
      }
    }
  }
  
  // Exception
  if (excetpion_flag) {
    void* exception = env->get_exception(env);
    int32_t length = env->length(env, exception);
    const char* exception_chars = env->get_chars(env, exception);
    SV* sv_exception = sv_2mortal(newSVpvn((char*)exception_chars, length));
    croak("%s\n at %s line %d\n", SvPV_nolen(sv_exception), MFILE, __LINE__);
  }
  // Success
  else {
    int32_t return_count;
    if (method_return_type->category == SPVM_TYPE_C_TYPE_CATEGORY_VOID) {
      return_count = 0;
    }
    else {
      XPUSHs(sv_return_value);
      return_count = 1;
    }
  
    XSRETURN(return_count);
  }
}

SV*
array_to_elems(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_array = ST(1);
  
  // Env
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  // Runtime
  SPVM_COMPILER* compiler = (SPVM_COMPILER*)env->compiler;

  // Array must be SPVM::BlessedObject::Array or SPVM::BlessedObject::Array
  if (!(SvROK(sv_array) && sv_derived_from(sv_array, "SPVM::BlessedObject::Array"))) {
    croak("Array must be SPVM::BlessedObject::Array object at %s line %d\n", MFILE, __LINE__);
  }
  
  // Get object
  SPVM_OBJECT* array = SPVM_XS_UTIL_get_object(sv_array);
  
  int32_t length = env->length(env, array);

  int32_t basic_type_id = array->basic_type_id;
  int32_t dimension = array->type_dimension;
  int32_t is_array_type = dimension > 0;
  
  AV* av_values = (AV*)sv_2mortal((SV*)newAV());
  if (is_array_type) {
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_LIST_fetch(compiler->runtime_basic_types, basic_type_id);
    int32_t element_type_dimension = dimension - 1;

    if (array->type_category == SPVM_TYPE_C_TYPE_CATEGORY_MULNUM_ARRAY) {
      
      for (int32_t index = 0; index < length; index++) {
        SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_LIST_fetch(compiler->runtime_basic_types, array->basic_type_id);
        
        SPVM_RUNTIME_CLASS* class = SPVM_API_get_runtime_class_from_basic_type_id(env, basic_type->id);
        assert(class);
        
        SPVM_RUNTIME_FIELD* first_field = SPVM_API_get_runtime_field_from_index(env, class->id, 0);
        assert(first_field);

        void* elems = (void*)env->get_elems_int(env, array);
        
        HV* hv_value = (HV*)sv_2mortal((SV*)newHV());
        int32_t field_length = class->field_ids->length;
        for (int32_t field_index = 0; field_index < class->field_ids->length; field_index++) {
          SPVM_RUNTIME_FIELD* field = SPVM_API_get_runtime_field_from_index(env, class->id, field_index);
          const char* field_name = field->name;

          SV* sv_field_value;
          SPVM_RUNTIME_TYPE* first_field_type = SPVM_LIST_fetch(compiler->runtime_types, first_field->type_id);
          switch (first_field_type->basic_type_id) {
            case SPVM_BASIC_TYPE_C_ID_BYTE: {
              int8_t field_value = ((int8_t*)elems)[(field_length * index) + field_index];
              sv_field_value = sv_2mortal(newSViv(field_value));
              break;
            }
            case SPVM_BASIC_TYPE_C_ID_SHORT: {
              int16_t field_value = ((int16_t*)elems)[(field_length * index) + field_index];
              sv_field_value = sv_2mortal(newSViv(field_value));
              break;
            }
            case SPVM_BASIC_TYPE_C_ID_INT: {
              int32_t field_value = ((int32_t*)elems)[(field_length * index) + field_index];
              sv_field_value = sv_2mortal(newSViv(field_value));
              break;
            }
            case SPVM_BASIC_TYPE_C_ID_LONG: {
              int64_t field_value = ((int64_t*)elems)[(field_length * index) + field_index];
              sv_field_value = sv_2mortal(newSViv(field_value));
              break;
            }
            case SPVM_BASIC_TYPE_C_ID_FLOAT: {
              float field_value = ((float*)elems)[(field_length * index) + field_index];
              sv_field_value = sv_2mortal(newSVnv(field_value));
              break;
            }
            case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
              double field_value = ((double*)elems)[(field_length * index) + field_index];
              sv_field_value = sv_2mortal(newSVnv(field_value));
              break;
            }
            default:
              croak("Unexpected error: set field value");
          }
          SvREFCNT_inc(sv_field_value);
          (void)hv_store(hv_value, field_name, strlen(field_name), sv_field_value, 0);
        }
        SV* sv_value = sv_2mortal(newRV_inc((SV*)hv_value));
        av_push(av_values, SvREFCNT_inc(sv_value));
      }
    }
    else if (array->type_category == SPVM_TYPE_C_TYPE_CATEGORY_OBJECT_ARRAY) {
      if (basic_type_id == SPVM_BASIC_TYPE_C_ID_STRING) {
        for (int32_t i = 0; i < length; i++) {
          void* object = env->get_elem_object(env, array, i);
          
          SV* sv_value;
          if (object != NULL) {
            env->inc_ref_count(env, object);
            sv_value = SPVM_XS_UTIL_new_sv_object(env, object, "SPVM::BlessedObject::String");
          }
          else {
            sv_value = &PL_sv_undef;
          }
          
          av_push(av_values, SvREFCNT_inc(sv_value));
        }
      }
      else {
        for (int32_t index = 0; index < length; index++) {
          // Element type id
          SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_LIST_fetch(compiler->runtime_basic_types, array->basic_type_id);

          // Index
          SPVM_OBJECT* value = env->get_elem_object(env, array, index);
          if (value == NULL) {
            av_push(av_values, &PL_sv_undef);
          }
          else {
            env->inc_ref_count(env, value);
            int32_t element_type_is_array_type = element_type_dimension > 0;
            SV* sv_value;
            if (element_type_is_array_type) {
              sv_value = SPVM_XS_UTIL_new_sv_object(env, value, "SPVM::BlessedObject::Array");
            }
            else {
              SV* sv_perl_class_name = sv_2mortal(newSVpv("SPVM::", 0));
              sv_catpv(sv_perl_class_name, basic_type->name);
              sv_value = SPVM_XS_UTIL_new_sv_object(env, value, SvPV_nolen(sv_perl_class_name));
            }
            av_push(av_values, SvREFCNT_inc(sv_value));
          }
        }
      }
    }
    else {
      switch (basic_type_id) {
        case SPVM_BASIC_TYPE_C_ID_BYTE: {
          int8_t* elems = env->get_elems_byte(env, array);
          for (int32_t i = 0; i < length; i++) {
            SV* sv_value = sv_2mortal(newSViv(elems[i]));
            av_push(av_values, SvREFCNT_inc(sv_value));
          }
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_SHORT: {
          int16_t* elems = env->get_elems_short(env, array);
          for (int32_t i = 0; i < length; i++) {
            SV* sv_value = sv_2mortal(newSViv(elems[i]));
            av_push(av_values, SvREFCNT_inc(sv_value));
          }
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_INT: {
          int32_t* elems = env->get_elems_int(env, array);
          for (int32_t i = 0; i < length; i++) {
            SV* sv_value = sv_2mortal(newSViv(elems[i]));
            av_push(av_values, SvREFCNT_inc(sv_value));
          }
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_LONG: {
          int64_t* elems = env->get_elems_long(env, array);
          for (int32_t i = 0; i < length; i++) {
            SV* sv_value = sv_2mortal(newSViv(elems[i]));
            av_push(av_values, SvREFCNT_inc(sv_value));
          }
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_FLOAT: {
          float* elems = env->get_elems_float(env, array);
          for (int32_t i = 0; i < length; i++) {
            SV* sv_value = sv_2mortal(newSVnv(elems[i]));
            av_push(av_values, SvREFCNT_inc(sv_value));
          }
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
          double* elems = env->get_elems_double(env, array);
          for (int32_t i = 0; i < length; i++) {
            SV* sv_value = sv_2mortal(newSVnv(elems[i]));
            av_push(av_values, SvREFCNT_inc(sv_value));
          }
          break;
        }
        default:
          assert(0);
      }
    }
  }
  else {
    croak("Argument must be array type at %s line %d\n", MFILE, __LINE__);
  }

  SV* sv_values = sv_2mortal(newRV_inc((SV*)av_values));
  
  XPUSHs(sv_values);
  XSRETURN(1);
}

SV*
array_to_bin(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_array = ST(1);
  
  // Env
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  // Runtime
  SPVM_COMPILER* compiler = (SPVM_COMPILER*)env->compiler;

  // Array must be SPVM::BlessedObject::Array object or SPVM::BlessedObject::String
  if (!(SvROK(sv_array) && sv_derived_from(sv_array, "SPVM::BlessedObject::Array"))) {
    croak("Data must be SPVM::BlessedObject::Array at %s line %d\n", MFILE, __LINE__);
  }

  // Get object
  SPVM_OBJECT* array = SPVM_XS_UTIL_get_object(sv_array);
  
  int32_t length = env->length(env, array);

  int32_t basic_type_id = array->basic_type_id;
  int32_t dimension = array->type_dimension;
  int32_t is_array_type = dimension > 0;
  
  SV* sv_bin;
  if (is_array_type) {
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_LIST_fetch(compiler->runtime_basic_types, basic_type_id);
    int32_t element_type_dimension = dimension - 1;

    if (array->type_category == SPVM_TYPE_C_TYPE_CATEGORY_MULNUM_ARRAY) {
      SPVM_RUNTIME_CLASS* class = SPVM_API_get_runtime_class_from_basic_type_id(env, basic_type->id);
      assert(class);
      
      SPVM_RUNTIME_FIELD* first_field = SPVM_API_get_runtime_field_from_index(env, class->id, 0);
      assert(first_field);

      int32_t field_length = class->field_ids->length;

      SPVM_RUNTIME_TYPE* first_field_type = SPVM_LIST_fetch(compiler->runtime_types, first_field->type_id);
      switch (first_field_type->basic_type_id) {
        case SPVM_BASIC_TYPE_C_ID_BYTE: {
          int8_t* elems = env->get_elems_byte(env, array);
          
          sv_bin = sv_2mortal(newSVpvn((char*)elems, field_length * length));
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_SHORT: {
          int16_t* elems = env->get_elems_short(env, array);
          
          sv_bin = sv_2mortal(newSVpvn((char*)elems, field_length * length * 2));
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_INT: {
          int32_t* elems = env->get_elems_int(env, array);
          
          sv_bin = sv_2mortal(newSVpvn((char*)elems, field_length * length * 4));
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_LONG: {
          int64_t* elems = env->get_elems_long(env, array);
          
          sv_bin = sv_2mortal(newSVpvn((char*)elems, field_length * length * 8));
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_FLOAT: {
          float* elems = env->get_elems_float(env, array);
          
          sv_bin = sv_2mortal(newSVpvn((char*)elems, field_length * length * 4));
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
          double* elems = env->get_elems_double(env, array);
          
          sv_bin = sv_2mortal(newSVpvn((char*)elems, field_length * length * 8));
          break;
        }
        default:
          croak("Invalid type at %s line %d\n", MFILE, __LINE__);
      }
    }
    else if (array->type_category == SPVM_TYPE_C_TYPE_CATEGORY_OBJECT_ARRAY) {
      croak("Objec type is not supported at %s line %d\n", MFILE, __LINE__);
    }
    else {
      switch (basic_type_id) {
        case SPVM_BASIC_TYPE_C_ID_BYTE: {
          int8_t* elems = env->get_elems_byte(env, array);
          
          sv_bin = sv_2mortal(newSVpvn((char*)elems, length));
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_SHORT: {
          int16_t* elems = env->get_elems_short(env, array);
          
          sv_bin = sv_2mortal(newSVpvn((char*)elems, length * 2));
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_INT: {
          int32_t* elems = env->get_elems_int(env, array);
          
          sv_bin = sv_2mortal(newSVpvn((char*)elems, length * 4));
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_LONG: {
          int64_t* elems = env->get_elems_long(env, array);
          
          sv_bin = sv_2mortal(newSVpvn((char*)elems, length * 8));
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_FLOAT: {
          float* elems = env->get_elems_float(env, array);
          
          sv_bin = sv_2mortal(newSVpvn((char*)elems, length * 4));
          break;
        }
        case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
          double* elems = env->get_elems_double(env, array);
          
          sv_bin = sv_2mortal(newSVpvn((char*)elems, length * 8));
          break;
        }
        default:
          croak("Invalid type at %s line %d\n", MFILE, __LINE__);
      }
    }
  }
  else {
    croak("Argument must be array type at %s line %d\n", MFILE, __LINE__);
  }
  
  XPUSHs(sv_bin);
  XSRETURN(1);
}

SV*
string_object_to_string(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_string = ST(1);
  
  // Env
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  // Runtime
  SPVM_COMPILER* compiler = (SPVM_COMPILER*)env->compiler;

  // String must be SPVM::BlessedObject::String or SPVM::BlessedObject::String
  if (!(SvROK(sv_string) && sv_derived_from(sv_string, "SPVM::BlessedObject::String"))) {
    croak("String must be SPVM::BlessedObject::String object at %s line %d\n", MFILE, __LINE__);
  }
  
  // Get object
  SPVM_OBJECT* string = SPVM_XS_UTIL_get_object(sv_string);
  
  int32_t length = env->length(env, string);
  const char* chars = env->get_chars(env, string);

  SV* sv_return_value = sv_2mortal(newSVpv(chars, length));

  int32_t is_valid_utf8 = sv_utf8_decode(sv_return_value);
  if (!is_valid_utf8) {
    croak("String is invalid UTF-8 at %s line %d\n", MFILE, __LINE__);
  }

  XPUSHs(sv_return_value);
  XSRETURN(1);
}

SV*
array_length(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_array = ST(1);
  
  // Env
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  // Runtime
  SPVM_COMPILER* compiler = (SPVM_COMPILER*)env->compiler;

  // Array must be SPVM::BlessedObject::Array or SPVM::BlessedObject::Array
  if (!(SvROK(sv_array) && sv_derived_from(sv_array, "SPVM::BlessedObject::Array"))) {
    croak("Array must be SPVM::BlessedObject::Array object at %s line %d\n", MFILE, __LINE__);
  }
  
  // Get object
  SPVM_OBJECT* array = SPVM_XS_UTIL_get_object(sv_array);
  
  int32_t length = env->length(env, array);


  SV* sv_length = sv_2mortal(newSViv(length));
  
  XPUSHs(sv_length);
  XSRETURN(1);
}

SV*
array_set(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_array = ST(1);
  SV* sv_index = ST(2);
  SV* sv_value = ST(3);

  // Env
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  // Index
  int32_t index = (int32_t)SvIV(sv_index);

  // Array
  SPVM_OBJECT* array = SPVM_XS_UTIL_get_object(sv_array);
  
  // Length
  int32_t length = env->length(env, array);
  
  // Check range
  if (index < 0 || index > length - 1) {
    croak("Out of range)");
  }

  int32_t basic_type_id = array->basic_type_id;
  int32_t dimension = array->type_dimension;

  if (dimension == 1) {
    switch (basic_type_id) {
      case SPVM_BASIC_TYPE_C_ID_BYTE: {
        // Value
        int8_t value = (int8_t)SvIV(sv_value);
        
        // Set element
        int8_t* elements = env->get_elems_byte(env, array);
        
        elements[index] = value;
        
        break;
      }
      case SPVM_BASIC_TYPE_C_ID_SHORT: {
        // Value
        int16_t value = (int16_t)SvIV(sv_value);
        
        // Set element
        int16_t* elements = env->get_elems_short(env, array);
        
        elements[index] = value;
        break;
      }
      case SPVM_BASIC_TYPE_C_ID_INT: {
        // Value
        int32_t value = (int32_t)SvIV(sv_value);
        
        // Set element
        int32_t* elements = env->get_elems_int(env, array);
        
        elements[index] = value;
        break;
      }
      case SPVM_BASIC_TYPE_C_ID_LONG: {
        // Value
        int64_t value = (int64_t)SvIV(sv_value);
        
        // Set element
        int64_t* elements = env->get_elems_long(env, array);
        
        elements[index] = value;
        break;
      }
      case SPVM_BASIC_TYPE_C_ID_FLOAT: {
        // Value
        float value = (float)SvNV(sv_value);
        
        // Set element
        float* elements = env->get_elems_float(env, array);
        
        elements[index] = value;
        break;
      }
      case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
        // Value
        double value = (double)SvNV(sv_value);
        
        // Set element
        double* elements = env->get_elems_double(env, array);
        
        elements[index] = value;
        break;
      }
      default: {
        // Get object
        SPVM_OBJECT* value = SPVM_XS_UTIL_get_object(sv_value);
        
        env->set_elem_object(env, array, index, value);
      }
    }
  }
  else if (dimension > 1) {
    
    // Get object
    SPVM_OBJECT* value = SPVM_XS_UTIL_get_object(sv_value);
    
    env->set_elem_object(env, array, index, value);
  }
  else {
    assert(0);
  }
  
  XSRETURN(0);
}

SV*
array_get(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_array = ST(1);
  SV* sv_index = ST(2);

  // Env
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  // Index
  int32_t index = (int32_t)SvIV(sv_index);

  // Array
  SPVM_OBJECT* array = SPVM_XS_UTIL_get_object(sv_array);
  
  // Length
  int32_t length = env->length(env, array);
  
  // Check range
  if (index < 0 || index > length - 1) {
    croak("Out of range)");
  }

  int32_t basic_type_id = array->basic_type_id;
  int32_t dimension = array->type_dimension;

  SV* sv_value = NULL;
  _Bool is_object = 0;
  if (dimension == 1) {
    switch (basic_type_id) {
      case SPVM_BASIC_TYPE_C_ID_BYTE: {
        // Get element
        int8_t* elements = env->get_elems_byte(env, array);
        int8_t value = elements[index];
        sv_value = sv_2mortal(newSViv(value));
        break;
      }
      case SPVM_BASIC_TYPE_C_ID_SHORT: {
        // Get element
        int16_t* elements = env->get_elems_short(env, array);
        int16_t value = elements[index];
        sv_value = sv_2mortal(newSViv(value));
        break;
      }
      case SPVM_BASIC_TYPE_C_ID_INT: {
        // Get element
        int32_t* elements = env->get_elems_int(env, array);
        int32_t value = elements[index];
        sv_value = sv_2mortal(newSViv(value));
        break;
      }
      case SPVM_BASIC_TYPE_C_ID_LONG: {
        // Get element
        int64_t* elements = env->get_elems_long(env, array);
        int64_t value = elements[index];
        sv_value = sv_2mortal(newSViv(value));
        break;
      }
      case SPVM_BASIC_TYPE_C_ID_FLOAT: {
        // Get element
        float* elements = env->get_elems_float(env, array);
        float value = elements[index];
        sv_value = sv_2mortal(newSVnv(value));
        break;
      }
      case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
        // Get element
        double* elements = env->get_elems_double(env, array);
        double value = elements[index];
        sv_value = sv_2mortal(newSVnv(value));
        break;
      }
      default:
        is_object = 1;
    }
  }
  else if (dimension > 1) {
    is_object = 1;
  }
  else {
    assert(0);
  }
  
  if (is_object) {
    SPVM_COMPILER* compiler = (SPVM_COMPILER*)env->compiler;
    
    // Element dimension
    int32_t element_dimension = array->type_dimension - 1;
    
    // Element type id
    SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_LIST_fetch(compiler->runtime_basic_types, array->basic_type_id);

    // Index
    SPVM_OBJECT* value = env->get_elem_object(env, array, index);
    if (value != NULL) {
      env->inc_ref_count(env, value);
    }
    
    if (element_dimension == 0) {
      SV* sv_perl_class_name = sv_2mortal(newSVpv("SPVM::", 0));
      sv_catpv(sv_perl_class_name, basic_type->name);
      sv_value = SPVM_XS_UTIL_new_sv_object(env, value, SvPV_nolen(sv_perl_class_name));
    }
    else if (element_dimension > 0) {
      sv_value = SPVM_XS_UTIL_new_sv_object(env, value, "SPVM::Data::Array");
    }
  }
  
  XPUSHs(sv_value);
  XSRETURN(1);
}

SV*
new_string_array(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_elems = ST(1);

  // Environment
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  SV* sv_array;
  if (SvOK(sv_elems)) {
    if (!sv_derived_from(sv_elems, "ARRAY")) {
      croak("Argument of SPVM::ExchangeAPI::new_string_array() must be array reference at %s line %d\n", MFILE, __LINE__);
    }

    AV* av_elems = (AV*)SvRV(sv_elems);

    int32_t length = av_len(av_elems) + 1;

    // New array
    SPVM_OBJECT* array = env->new_object_array(env, SPVM_BASIC_TYPE_C_ID_STRING, length);

    for (int32_t i = 0; i < length; i++) {
      SV** sv_str_value_ptr = av_fetch(av_elems, i, 0);
      SV* sv_str_value = sv_str_value_ptr ? *sv_str_value_ptr : &PL_sv_undef;
      if (SvOK(sv_str_value)) {
        // Copy
        SV* sv_str_value_copy = sv_2mortal(newSVsv(sv_str_value));
        
        // Encode to UTF-8
        sv_utf8_encode(sv_str_value_copy);
        
        int32_t length = sv_len(sv_str_value_copy);
        const char* chars = SvPV_nolen(sv_str_value_copy);
        
        void* string = env->new_string_raw(env, chars, length);
        env->set_elem_object(env, array, i, string);
      }
      else {
        env->set_elem_object(env, array, i, NULL);
      }
    }

    // New sv array
    sv_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
  }
  else {
    sv_array = &PL_sv_undef;
  }
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
new_byte_array(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_elems = ST(1);
  
  SV* sv_array;
  if (SvOK(sv_elems)) {
    if (!sv_derived_from(sv_elems, "ARRAY")) {
      croak("Argument of SPVM::ExchangeAPI::new_byte_array() must be array reference at %s line %d\n", MFILE, __LINE__);
    }
    
    // Elements
    AV* av_elems = (AV*)SvRV(sv_elems);
    
    // Array Length
    int32_t length = av_len(av_elems) + 1;
    
    // New byte array
    SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
    void* array = env->new_byte_array(env, length);
    
    // Copy Perl elements to SPVM elements
    int8_t* elems = env->get_elems_byte(env, array);
    for (int32_t i = 0; i < length; i++) {
      SV** sv_value_ptr = av_fetch(av_elems, i, 0);
      SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
      elems[i] = (int8_t)SvIV(sv_value);
    }
    
    // New SPVM::BlessedObject::Array object
    sv_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
  }
  else {
    sv_array = &PL_sv_undef;
  }
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
new_byte_array_unsigned(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_elems = ST(1);
  
  SV* sv_array;
  if (SvOK(sv_elems)) {
    if (!sv_derived_from(sv_elems, "ARRAY")) {
      croak("Argument of SPVM::ExchangeAPI::new_byte_array() must be array reference at %s line %d\n", MFILE, __LINE__);
    }
    
    // Elements
    AV* av_elems = (AV*)SvRV(sv_elems);
    
    // Array Length
    int32_t length = av_len(av_elems) + 1;
    
    // New byte array
    SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
    void* array = env->new_byte_array(env, length);
    
    // Copy Perl elements to SPVM elements
    int8_t* elems = env->get_elems_byte(env, array);
    for (int32_t i = 0; i < length; i++) {
      SV** sv_value_ptr = av_fetch(av_elems, i, 0);
      SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
      elems[i] = (uint8_t)SvUV(sv_value);
    }
    
    // New SPVM::BlessedObject::Array object
    sv_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
  }
  else {
    sv_array = &PL_sv_undef;
  }
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
new_byte_array_len(...)
  PPCODE:
{
  (void)RETVAL;

  SV* sv_env = ST(0);
  SV* sv_length = ST(1);
  
  // Env
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  int32_t length = (int32_t)SvIV(sv_length);
  
  if (length < 0) {
    croak("Length must be more than or equals to 0 at %s line %d\n", MFILE, __LINE__);
  }
  
  // New array
  void* array = env->new_byte_array(env, length);
  
  // New sv array
  SV* sv_byte_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
  
  XPUSHs(sv_byte_array);
  XSRETURN(1);
}

SV*
new_byte_array_from_bin(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_binary = ST(1);
  
  SV* sv_array;
  if (SvOK(sv_binary)) {
    int32_t binary_length = sv_len(sv_binary);
    int32_t array_length = binary_length;
    int8_t* binary = (int8_t*)SvPV_nolen(sv_binary);
    
    // Environment
    SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
    
    // New array
    void* array = env->new_byte_array(env, array_length);

    int8_t* elems = env->get_elems_byte(env, array);
    memcpy(elems, binary, array_length);
    
    // New sv array
    sv_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
  }
  else {
    sv_array = &PL_sv_undef;
  }
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
new_string(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_value = ST(1);
  
  SV* sv_string;
  if (SvOK(sv_value)) {
    
    if (SvROK(sv_value)) {
      croak("Argument must not be reference at %s line %d\n", MFILE, __LINE__);
    }
    else {
      // Environment
      SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
      
      // Copy
      SV* sv_value_tmp = sv_2mortal(newSVsv(sv_value));
      
      // Encode to UTF-8
      sv_utf8_encode(sv_value_tmp);
      
      int32_t length = sv_len(sv_value_tmp);
      
      const char* value = SvPV_nolen(sv_value_tmp);
      
      void* string = env->new_string(env, value, length);
      
      sv_string = SPVM_XS_UTIL_new_sv_object(env, string, "SPVM::BlessedObject::String");
    }
  }
  else {
    croak("Argument must be defined at %s line %d\n", MFILE, __LINE__);
  }
  
  XPUSHs(sv_string);
  XSRETURN(1);
}

SV*
new_string_from_bin(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_binary = ST(1);
  
  SV* sv_string;
  if (SvOK(sv_binary)) {
    if (SvROK(sv_binary)) {
      croak("Argument must not be reference at %s line %d\n", MFILE, __LINE__);
    }
    else {
      int32_t binary_length = sv_len(sv_binary);
      int32_t string_length = binary_length;
      int8_t* binary = (int8_t*)SvPV_nolen(sv_binary);
      
      // Environment
      SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
      
      // New string
      void* string = env->new_string(env, (const char*)binary, string_length);

      const char* chars = env->get_chars(env, string);
      memcpy((char*)chars, binary, string_length);
      
      // New sv string
      sv_string = SPVM_XS_UTIL_new_sv_object(env, string, "SPVM::BlessedObject::String");
    }
  }
  else {
    croak("Argument must be defined at %s line %d\n", MFILE, __LINE__);
  }
  
  XPUSHs(sv_string);
  XSRETURN(1);
}

SV*
new_short_array(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_elems = ST(1);
  
  SV* sv_array;
  if (SvOK(sv_elems)) {
    if (!sv_derived_from(sv_elems, "ARRAY")) {
      croak("Argument of SPVM::ExchangeAPI::new_short_array() must be array reference at %s line %d\n", MFILE, __LINE__);
    }
    
    // Elements
    AV* av_elems = (AV*)SvRV(sv_elems);
    
    // Array length
    int32_t length = av_len(av_elems) + 1;
    
    // New array
    SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
    void* array = env->new_short_array(env, length);
    
    // Copy Perl elements to SPVM elements
    int16_t* elems = env->get_elems_short(env, array);
    for (int32_t i = 0; i < length; i++) {
      SV** sv_value_ptr = av_fetch(av_elems, i, 0);
      SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
      elems[i] = (int16_t)SvIV(sv_value);
    }
    
    // New SPVM::BlessedObject::Array object
    sv_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
  }
  else {
    sv_array = &PL_sv_undef;
  }
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
new_short_array_unsigned(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_elems = ST(1);
  
  SV* sv_array;
  if (SvOK(sv_elems)) {
    if (!sv_derived_from(sv_elems, "ARRAY")) {
      croak("Argument of SPVM::ExchangeAPI::new_short_array() must be array reference at %s line %d\n", MFILE, __LINE__);
    }
    
    // Elements
    AV* av_elems = (AV*)SvRV(sv_elems);
    
    // Array length
    int32_t length = av_len(av_elems) + 1;
    
    // New array
    SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
    void* array = env->new_short_array(env, length);
    
    // Copy Perl elements to SPVM elements
    int16_t* elems = env->get_elems_short(env, array);
    for (int32_t i = 0; i < length; i++) {
      SV** sv_value_ptr = av_fetch(av_elems, i, 0);
      SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
      elems[i] = (uint16_t)SvUV(sv_value);
    }
    
    // New SPVM::BlessedObject::Array object
    sv_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
  }
  else {
    sv_array = &PL_sv_undef;
  }
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
new_short_array_len(...)
  PPCODE:
{
  (void)RETVAL;

  SV* sv_env = ST(0);
  SV* sv_length = ST(1);
  
  // Env
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  int32_t length = (int32_t)SvIV(sv_length);
  
  if (length < 0) {
    croak("Length must be more than or equals to 0 at %s line %d\n", MFILE, __LINE__);
  }
  
  // New array
  void* array = env->new_short_array(env, length);
  
  // New sv array
  SV* sv_short_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
  
  XPUSHs(sv_short_array);
  XSRETURN(1);
}

SV*
new_short_array_from_bin(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_binary = ST(1);
  
  SV* sv_array;
  if (SvOK(sv_binary)) {
    int32_t binary_length = sv_len(sv_binary);
    int32_t array_length = binary_length / sizeof(int16_t);
    int16_t* binary = (int16_t*)SvPV_nolen(sv_binary);
    
    // Environment
    SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
    
    // New array
    void* array = env->new_short_array(env, array_length);

    int16_t* elems = env->get_elems_short(env, array);
    memcpy(elems, binary, array_length * sizeof(int16_t));
    
    // sv array
    sv_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
  }
  else {
    sv_array = &PL_sv_undef;
  }
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
new_int_array(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_elems = ST(1);
  
  SV* sv_array;
  if (SvOK(sv_elems)) {
    if (!sv_derived_from(sv_elems, "ARRAY")) {
      croak("Argument of SPVM::ExchangeAPI::new_int_array() must be array reference at %s line %d\n", MFILE, __LINE__);
    }
    
    // Elements
    AV* av_elems = (AV*)SvRV(sv_elems);
    
    // Array length
    int32_t length = av_len(av_elems) + 1;
    
    // New array
    SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
    void* array = env->new_int_array(env, length);
    
    // Copy Perl elements to SPVM erlements
    int32_t* elems = env->get_elems_int(env, array);
    for (int32_t i = 0; i < length; i++) {
      SV** sv_value_ptr = av_fetch(av_elems, i, 0);
      SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
      elems[i] = (int32_t)SvIV(sv_value);
    }
    
    // New SPVM::BlessedObject::Array object
    sv_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
  }
  else {
    sv_array = &PL_sv_undef;
  }
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
new_int_array_unsigned(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_elems = ST(1);
  
  SV* sv_array;
  if (SvOK(sv_elems)) {
    if (!sv_derived_from(sv_elems, "ARRAY")) {
      croak("Argument of SPVM::ExchangeAPI::new_int_array() must be array reference at %s line %d\n", MFILE, __LINE__);
    }
    
    // Elements
    AV* av_elems = (AV*)SvRV(sv_elems);
    
    // Array length
    int32_t length = av_len(av_elems) + 1;
    
    // New array
    SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
    void* array = env->new_int_array(env, length);
    
    // Copy Perl elements to SPVM erlements
    int32_t* elems = env->get_elems_int(env, array);
    for (int32_t i = 0; i < length; i++) {
      SV** sv_value_ptr = av_fetch(av_elems, i, 0);
      SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
      elems[i] = (uint32_t)SvUV(sv_value);
    }
    
    // New SPVM::BlessedObject::Array object
    sv_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
  }
  else {
    sv_array = &PL_sv_undef;
  }
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
new_int_array_len(...)
  PPCODE:
{
  (void)RETVAL;

  SV* sv_env = ST(0);
  SV* sv_length = ST(1);
  
  // Env
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  int32_t length = (int32_t)SvIV(sv_length);
  
  if (length < 0) {
    croak("Length must be more than or equals to 0 at %s line %d\n", MFILE, __LINE__);
  }
  
  // New array
  void* array = env->new_int_array(env, length);
  
  // New sv array
  SV* sv_int_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
  
  XPUSHs(sv_int_array);
  XSRETURN(1);
}

SV*
new_int_array_from_bin(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_binary = ST(1);
  
  SV* sv_array;
  if (SvOK(sv_binary)) {
    int32_t binary_length = sv_len(sv_binary);
    int32_t array_length = binary_length / sizeof(int32_t);
    int32_t* binary = (int32_t*)SvPV_nolen(sv_binary);
    
    // Environment
    SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
    
    // New array
    void* array = env->new_int_array(env, array_length);

    int32_t* elems = env->get_elems_int(env, array);
    memcpy(elems, binary, array_length * sizeof(int32_t));
    
    // sv array
    sv_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
  }
  else {
    sv_array = &PL_sv_undef;
  }
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
new_long_array(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_elems = ST(1);
  
  SV* sv_array;
  if (SvOK(sv_elems)) {
    if (!sv_derived_from(sv_elems, "ARRAY")) {
      croak("Argument of SPVM::ExchangeAPI::new_long_array() must be array reference at %s line %d\n", MFILE, __LINE__);
    }
    
    // Elements
    AV* av_elems = (AV*)SvRV(sv_elems);
    
    // Array length
    int32_t length = av_len(av_elems) + 1;
    
    // New array
    SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
    void* array = env->new_long_array(env, length);
    
    // Copy Perl elements to SPVM elements
    int64_t* elems = env->get_elems_long(env, array);
    for (int32_t i = 0; i < length; i++) {
      SV** sv_value_ptr = av_fetch(av_elems, i, 0);
      SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
      elems[i] = (int64_t)SvIV(sv_value);
    }
    
    // New SPVM::BlessedObject::Array object
    sv_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
  }
  else {
    sv_array = &PL_sv_undef;
  }
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
new_long_array_unsigned(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_elems = ST(1);
  
  SV* sv_array;
  if (SvOK(sv_elems)) {
    if (!sv_derived_from(sv_elems, "ARRAY")) {
      croak("Argument of SPVM::ExchangeAPI::new_long_array() must be array reference at %s line %d\n", MFILE, __LINE__);
    }
    
    // Elements
    AV* av_elems = (AV*)SvRV(sv_elems);
    
    // Array length
    int32_t length = av_len(av_elems) + 1;
    
    // New array
    SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
    void* array = env->new_long_array(env, length);
    
    // Copy Perl elements to SPVM elements
    int64_t* elems = env->get_elems_long(env, array);
    for (int32_t i = 0; i < length; i++) {
      SV** sv_value_ptr = av_fetch(av_elems, i, 0);
      SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
      elems[i] = (uint64_t)SvUV(sv_value);
    }
    
    // New SPVM::BlessedObject::Array object
    sv_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
  }
  else {
    sv_array = &PL_sv_undef;
  }
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
new_long_array_len(...)
  PPCODE:
{
  (void)RETVAL;

  SV* sv_env = ST(0);
  SV* sv_length = ST(1);
  
  // Env
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  int32_t length = (int32_t)SvIV(sv_length);
  
  if (length < 0) {
    croak("Length must be more than or equals to 0 at %s line %d\n", MFILE, __LINE__);
  }
  
  // New array
  void* array = env->new_long_array(env, length);
  
  // New sv array
  SV* sv_long_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
  
  XPUSHs(sv_long_array);
  XSRETURN(1);
}

SV*
new_long_array_from_bin(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_binary = ST(1);
  
  SV* sv_array;
  if (SvOK(sv_binary)) {
    int32_t binary_length = sv_len(sv_binary);
    int32_t array_length = binary_length / sizeof(int64_t);
    int64_t* binary = (int64_t*)SvPV_nolen(sv_binary);
    
    // Environment
    SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
    
    // New array
    void* array = env->new_long_array(env, array_length);

    int64_t* elems = env->get_elems_long(env, array);
    memcpy(elems, binary, array_length * sizeof(int64_t));
    
    // sv array
    sv_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
  }
  else {
    sv_array = &PL_sv_undef;
  }
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
new_float_array(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_elems = ST(1);
  
  SV* sv_array;
  if (SvOK(sv_elems)) {
    if (!sv_derived_from(sv_elems, "ARRAY")) {
      croak("Argument of SPVM::ExchangeAPI::new_float_array() must be array reference at %s line %d\n", MFILE, __LINE__);
    }
    
    AV* av_elems = (AV*)SvRV(sv_elems);
    
    int32_t length = av_len(av_elems) + 1;
    
    // Environment
    SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
    
    // New array
    void* array = env->new_float_array(env, length);

    float* elems = env->get_elems_float(env, array);
    for (int32_t i = 0; i < length; i++) {
      SV** sv_value_ptr = av_fetch(av_elems, i, 0);
      SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
      elems[i] = (float)SvNV(sv_value);
    }
    
    // New sv array
    sv_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
  }
  else {
    sv_array = &PL_sv_undef;
  }
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
new_float_array_len(...)
  PPCODE:
{
  (void)RETVAL;

  SV* sv_env = ST(0);
  SV* sv_length = ST(1);
  
  // Env
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  int32_t length = (int32_t)SvIV(sv_length);
  
  if (length < 0) {
    croak("Length must be more than or equals to 0 at %s line %d\n", MFILE, __LINE__);
  }
  
  // New array
  void* array = env->new_float_array(env, length);
  
  // New sv array
  SV* sv_float_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
  
  XPUSHs(sv_float_array);
  XSRETURN(1);
}

SV*
new_float_array_from_bin(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_binary = ST(1);
  
  SV* sv_array;
  if (SvOK(sv_binary)) {
    int32_t binary_length = sv_len(sv_binary);
    int32_t array_length = binary_length / sizeof(float);
    float* binary = (float*)SvPV_nolen(sv_binary);
    
    // Environment
    SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
    
    // New array
    void* array = env->new_float_array(env, array_length);

    float* elems = env->get_elems_float(env, array);
    memcpy(elems, binary, array_length * sizeof(float));
    
    // sv array
    sv_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
  }
  else {
    sv_array = &PL_sv_undef;
  }
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
new_double_array(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_elems = ST(1);
  
  SV* sv_array;
  if (SvOK(sv_elems)) {
    if (!sv_derived_from(sv_elems, "ARRAY")) {
      croak("Argument of SPVM::ExchangeAPI::new_double_array() must be array reference at %s line %d\n", MFILE, __LINE__);
    }
    
    AV* av_elems = (AV*)SvRV(sv_elems);
    
    int32_t length = av_len(av_elems) + 1;
    
    // Environment
    SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
    
    // New array
    void* array = env->new_double_array(env, length);

    double* elems = env->get_elems_double(env, array);
    for (int32_t i = 0; i < length; i++) {
      SV** sv_value_ptr = av_fetch(av_elems, i, 0);
      SV* sv_value = sv_value_ptr ? *sv_value_ptr : &PL_sv_undef;
      elems[i] = (double)SvNV(sv_value);
    }
    
    // sv array
    sv_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
  }
  else {
    sv_array = &PL_sv_undef;
  }
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
new_double_array_len(...)
  PPCODE:
{
  (void)RETVAL;

  SV* sv_env = ST(0);
  SV* sv_length = ST(1);
  
  // Env
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  int32_t length = (int32_t)SvIV(sv_length);
  
  if (length < 0) {
    croak("Length must be more than or equals to 0 at %s line %d\n", MFILE, __LINE__);
  }
  
  // New array
  void* array = env->new_double_array(env, length);
  
  // New sv array
  SV* sv_double_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
  
  XPUSHs(sv_double_array);
  XSRETURN(1);
}

SV*
new_double_array_from_bin(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_binary = ST(1);
  
  SV* sv_array;
  if (SvOK(sv_binary)) {
    int32_t binary_length = sv_len(sv_binary);
    int32_t array_length = binary_length / sizeof(double);
    double* binary = (double*)SvPV_nolen(sv_binary);
    
    // Environment
    SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
    
    // New array
    void* array = env->new_double_array(env, array_length);

    double* elems = env->get_elems_double(env, array);
    memcpy(elems, binary, array_length * sizeof(double));
    
    // New sv array
    sv_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
  }
  else {
    sv_array = &PL_sv_undef;
  }
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
new_string_array_len(...)
  PPCODE:
{
  (void)RETVAL;

  SV* sv_env = ST(0);
  SV* sv_length = ST(1);

  // Env
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  int32_t length = (int32_t)SvIV(sv_length);
  
  if (length < 0) {
    croak("Length must be more than or equals to 0 at %s line %d\n", MFILE, __LINE__);
  }
  
  // Element type id
  const char* basic_type_name = "string";
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_get_basic_type(env, basic_type_name);
  assert(basic_type);
  
  // New array
  void* array = env->new_object_array(env, basic_type->id, length);
  
  // New sv array
  SV* sv_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
new_object_array_len(...)
  PPCODE:
{
  (void)RETVAL;

  SV* sv_env = ST(0);
  SV* sv_basic_type_name = ST(1);
  SV* sv_length = ST(2);

  // Env
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  int32_t length = (int32_t)SvIV(sv_length);
  
  if (length < 0) {
    croak("Length must be more than or equals to 0 at %s line %d\n", MFILE, __LINE__);
  }
  
  // Element type id
  const char* basic_type_name = SvPV_nolen(sv_basic_type_name);
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_get_basic_type(env, basic_type_name);
  assert(basic_type);
  
  // New array
  void* array = env->new_object_array(env, basic_type->id, length);
  
  // New sv array
  SV* sv_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
_new_object_array(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_basic_type_name = ST(1);
  SV* sv_elems = ST(2);
  
  if (!sv_derived_from(sv_elems, "ARRAY")) {
    croak("Second argument of SPVM::new_object_array must be array reference at %s line %d\n", MFILE, __LINE__);
  }
  
  const char* basic_type_name = SvPV_nolen(sv_basic_type_name);
  
  AV* av_elems = (AV*)SvRV(sv_elems);
  
  int32_t length = av_len(av_elems) + 1;
  
  // Environment
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  // Runtime
  SPVM_COMPILER* compiler = (SPVM_COMPILER*)env->compiler;
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_get_basic_type(env, basic_type_name);
  assert(basic_type);
  
  // New array
  SPVM_OBJECT* array = env->new_object_array(env, basic_type->id, length);

  int32_t array_basic_type_id  = array->basic_type_id;
  int32_t array_type_dimension = array->type_dimension;
  int32_t element_type_dimension = array_type_dimension - 1;

  for (int32_t index = 0; index < length; index++) {
    SV** sv_element_ptr = av_fetch(av_elems, index, 0);
    SV* sv_element = sv_element_ptr ? *sv_element_ptr : &PL_sv_undef;
    
    if (!SvOK(sv_element)) {
      env->set_elem_object(env, array, index, NULL);
    }
    else if (sv_isobject(sv_element) && sv_derived_from(sv_element, "SPVM::BlessedObject::Class")) {
      SPVM_OBJECT* object = SPVM_XS_UTIL_get_object(sv_element);
      
      if (object->basic_type_id == array_basic_type_id && object->type_dimension == element_type_dimension) {
        env->set_elem_object(env, array, index, object);
      }
      else {
        croak("Element is invalid object type at %s line %d\n", MFILE, __LINE__);
      }
    }
    else {
      croak("Element must be SPVM::BlessedObject object at %s line %d\n", MFILE, __LINE__);
    }
  }
  
  // New sv array
  SV* sv_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
_new_muldim_array(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_basic_type_name = ST(1);
  SV* sv_element_type_dimension = ST(2);
  SV* sv_elems = ST(3);
  
  if (!sv_derived_from(sv_elems, "ARRAY")) {
    croak("Argument must be array reference at %s line %d\n", MFILE, __LINE__);
  }
  
  AV* av_elems = (AV*)SvRV(sv_elems);
  
  int32_t length = av_len(av_elems) + 1;
  
  // Environment
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  // Runtime
  SPVM_COMPILER* compiler = (SPVM_COMPILER*)env->compiler;

  int32_t element_type_dimension = (int32_t)SvIV(sv_element_type_dimension);

  // Element type id
  const char* basic_type_name = SvPV_nolen(sv_basic_type_name);
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_get_basic_type(env, basic_type_name);
  assert(basic_type);
  
  // New array
  SPVM_OBJECT* array = env->new_muldim_array(env, basic_type->id, element_type_dimension, length);
  
  int32_t array_basic_type_id = array->basic_type_id;

  for (int32_t index = 0; index < length; index++) {
    SV** sv_element_ptr = av_fetch(av_elems, index, 0);
    SV* sv_element = sv_element_ptr ? *sv_element_ptr : &PL_sv_undef;
    
    if (!SvOK(sv_element)) {
      env->set_elem_object(env, array, index, NULL);
    }
    else if (sv_isobject(sv_element) && sv_derived_from(sv_element, "SPVM::BlessedObject")) {
      SPVM_OBJECT* object = SPVM_XS_UTIL_get_object(sv_element);
      
      if (object->basic_type_id == array_basic_type_id && object->type_dimension == element_type_dimension) {
        env->set_elem_object(env, array, index, object);
      }
      else {
        croak("Element is invalid object type at %s line %d\n", MFILE, __LINE__);
      }
    }
    else {
      croak("Element must be inherit SPVM::BlessedObject object at %s line %d\n", MFILE, __LINE__);
    }
  }
  
  // New sv array
  SV* sv_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
_new_mulnum_array(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_basic_type_name = ST(1);
  SV* sv_elems = ST(2);

  const char* basic_type_name = SvPV_nolen(sv_basic_type_name);
  
  // Env
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  SV* sv_error = NULL;
  SPVM_OBJECT* array = SPVM_XS_UTIL_new_mulnum_array(env, basic_type_name, sv_elems, &sv_error);
  
  if (sv_error) {
    croak_sv(sv_error);
  }
  
  SV* sv_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
_new_mulnum_array_from_bin(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  SV* sv_basic_type_name = ST(1);
  SV* sv_binary = ST(2);
  
  if (!SvOK(sv_binary)) {
    croak("Argument must be defined at %s line %d\n", MFILE, __LINE__);
  }
  
  const char* basic_type_name = SvPV_nolen(sv_basic_type_name);
  
  void* binary = (void*)SvPV_nolen(sv_binary);
  
  int32_t binary_length = sv_len(sv_binary);
  
  // Env
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  // Runtime
  SPVM_COMPILER* compiler = (SPVM_COMPILER*)env->compiler;
  
  SPVM_RUNTIME_BASIC_TYPE* basic_type = SPVM_API_get_basic_type(env, basic_type_name);
  
  if (basic_type == NULL) {
    const char* basic_type_name = basic_type->name;
    croak("Can't load %s at %s line %d\n", basic_type_name, MFILE, __LINE__);
  }

  SPVM_RUNTIME_CLASS* class = SPVM_API_get_runtime_class_from_basic_type_id(env, basic_type->id);
  assert(class);
  
  SPVM_RUNTIME_FIELD* first_field = SPVM_API_get_runtime_field_from_index(env, class->id, 0);
  assert(first_field);

  int32_t field_length = class->field_ids->length;

  int32_t array_length;
  
  
  int32_t field_width;
  
  SPVM_RUNTIME_TYPE* first_field_type = SPVM_LIST_fetch(compiler->runtime_types, first_field->type_id);
  switch (first_field_type->basic_type_id) {
    case SPVM_BASIC_TYPE_C_ID_BYTE: {
      field_width = 1;
      break;
    }
    case SPVM_BASIC_TYPE_C_ID_SHORT: {
      field_width = 2;
      break;
    }
    case SPVM_BASIC_TYPE_C_ID_INT: {
      field_width = 4;
      break;
    }
    case SPVM_BASIC_TYPE_C_ID_LONG: {
      field_width = 8;
      break;
    }
    case SPVM_BASIC_TYPE_C_ID_FLOAT: {
      field_width = 4;
      break;
    }
    case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
      field_width = 8;
      break;
    }
    default:
      croak("Unexpected error:set field width");
  }
  
  if (binary_length % (field_length * field_width) != 0) {
    croak("Invalid binary data size at %s line %d", MFILE, __LINE__);
  }
  
  array_length = binary_length / field_length / field_width;

  SPVM_OBJECT* array = env->new_mulnum_array(env, basic_type->id, array_length);

  int32_t basic_type_id = array->basic_type_id;
  int32_t dimension = array->type_dimension;
  
  switch (first_field_type->basic_type_id) {
    case SPVM_BASIC_TYPE_C_ID_BYTE: {
      int8_t* elems = env->get_elems_byte(env, array);
      if (array_length > 0) {
        memcpy(elems, binary, field_length * array_length * field_width);
      }
      break;
    }
    case SPVM_BASIC_TYPE_C_ID_SHORT: {
      int16_t* elems = env->get_elems_short(env, array);
      if (array_length > 0) {
        memcpy(elems, binary, field_length * array_length * field_width);
      }
      break;
    }
    case SPVM_BASIC_TYPE_C_ID_INT: {
      int32_t* elems = env->get_elems_int(env, array);
      if (array_length > 0) {
        memcpy(elems, binary, field_length * array_length * field_width);
      }
      break;
    }
    case SPVM_BASIC_TYPE_C_ID_LONG: {
      int64_t* elems = env->get_elems_long(env, array);
      if (array_length > 0) {
        memcpy(elems, binary, field_length * array_length * field_width);
      }
      break;
    }
    case SPVM_BASIC_TYPE_C_ID_FLOAT: {
      float* elems = env->get_elems_float(env, array);
      if (array_length > 0) {
        memcpy(elems, binary, field_length * array_length * field_width);
      }
      break;
    }
    case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
      double* elems = env->get_elems_double(env, array);
      if (array_length > 0) {
        memcpy(elems, binary, field_length * array_length * field_width);
      }
      break;
    }
    default:
      assert(0);
  }
  
  // New sv array
  SV* sv_array = SPVM_XS_UTIL_new_sv_object(env, array, "SPVM::BlessedObject::Array");
  
  XPUSHs(sv_array);
  XSRETURN(1);
}

SV*
get_exception(...)
  PPCODE:
{
  (void)RETVAL;

  SV* sv_env = ST(0);
  
  // Env
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  void* str_exception = env->get_exception(env);
  
  SV* sv_exception;
  if (str_exception) {
    env->inc_ref_count(env, str_exception);
    sv_exception = SPVM_XS_UTIL_new_sv_object(env, str_exception, "SPVM::BlessedObject::String");
  }
  else {
    sv_exception = &PL_sv_undef;
  }
  
  XPUSHs(sv_exception);
  XSRETURN(1);
}

SV*
_set_exception(...)
  PPCODE:
{
  (void)RETVAL;

  SV* sv_env = ST(0);
  SV* sv_exception = ST(1);
  
  // Env
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));

  if (SvOK(sv_exception)) {
    if (!(sv_isobject(sv_exception) && sv_derived_from(sv_exception, "SPVM::BlessedObject::String"))) {
      croak("The argument must be a SPVM::BlessedObject::String object");
    }
    SPVM_OBJECT* exception = SPVM_XS_UTIL_get_object(sv_exception);
    env->set_exception(env, exception);
  }
  else {
    env->set_exception(env, NULL);
  }
  
  XSRETURN(0);
}

SV*
get_memory_blocks_count(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_env = ST(0);
  
  // Env
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  int32_t memory_blocks_count = env->get_memory_blocks_count(env);
  SV* sv_memory_blocks_count = sv_2mortal(newSViv(memory_blocks_count));
  
  XPUSHs(sv_memory_blocks_count);
  XSRETURN(1);
}

MODULE = SPVM::BlessedObject		PACKAGE = SPVM::BlessedObject

SV*
DESTROY(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_object = ST(0);
  HV* hv_object = (HV*)SvRV(sv_object);

  assert(SvOK(sv_object));
  
  // Get object
  void* object = SPVM_XS_UTIL_get_object(sv_object);

  SV** sv_env_ptr = hv_fetch(hv_object, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
  
  assert(env->get_ref_count(env, object));
  
  // Decrement reference count
  env->dec_ref_count(env, object);
  
  XSRETURN(0);
}

MODULE = SPVM::Builder		PACKAGE = SPVM::Builder

SV*
create_compiler_env(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);

  SPVM_ENV* compiler_env = SPVM_API_new_env_raw(NULL);
  
  size_t iv_compiler_env = PTR2IV(compiler_env);
  SV* sviv_compiler_env = sv_2mortal(newSViv(iv_compiler_env));
  SV* sv_compiler_env = sv_2mortal(newRV_inc(sviv_compiler_env));
  (void)hv_store(hv_self, "compiler_env", strlen("compiler_env"), SvREFCNT_inc(sv_compiler_env), 0);
}

SV*
create_compiler(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);

  SV** sv_compiler_env_ptr = hv_fetch(hv_self, "compiler_env", strlen("compiler_env"), 0);
  SV* sv_compiler_env = sv_compiler_env_ptr ? *sv_compiler_env_ptr : &PL_sv_undef;
  SPVM_ENV* compiler_env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_compiler_env)));
  
  // Create compiler
  void* compiler = compiler_env->new_compiler(compiler_env);

  size_t iv_compiler = PTR2IV(compiler);
  SV* sviv_compiler = sv_2mortal(newSViv(iv_compiler));
  SV* sv_compiler = sv_2mortal(newRV_inc(sviv_compiler));
  (void)hv_store(hv_self, "compiler", strlen("compiler"), SvREFCNT_inc(sv_compiler), 0);
}

SV*
compile_spvm(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  SV* sv_class_name = ST(1);
  SV* sv_start_file = ST(2);
  SV* sv_start_line = ST(3);
  
  HV* hv_self = (HV*)SvRV(sv_self);

  SV** sv_compiler_ptr = hv_fetch(hv_self, "compiler", strlen("compiler"), 0);
  SV* sv_compiler = sv_compiler_ptr ? *sv_compiler_ptr : &PL_sv_undef;
  SPVM_COMPILER* compiler = INT2PTR(SPVM_COMPILER*, SvIV(SvRV(sv_compiler)));
  
  // Include directries
  SV** sv_module_dirs_ptr = hv_fetch(hv_self, "module_dirs", strlen("module_dirs"), 0);
  SV* sv_module_dirs = sv_module_dirs_ptr ? *sv_module_dirs_ptr : &PL_sv_undef;
  
  // Name
  const char* class_name = SvPV_nolen(sv_class_name);
  char* class_name_copy = SPVM_ALLOCATOR_new_block_compile_eternal(compiler->allocator, sv_len(sv_class_name) + 1);
  memcpy(class_name_copy, class_name, sv_len(sv_class_name));
  
  // File
  const char* start_file = SvPV_nolen(sv_start_file);
  char* start_file_copy = SPVM_ALLOCATOR_new_block_compile_eternal(compiler->allocator, sv_len(sv_start_file) + 1);
  memcpy(start_file_copy, start_file, sv_len(sv_start_file));
  
  // Line
  int32_t start_line = (int32_t)SvIV(sv_start_line);

  SPVM_ENV* compiler_env = SPVM_API_new_env_raw(NULL);

  // Set starting file
  compiler_env->compiler_set_start_file(compiler_env, compiler, start_file_copy);
  
  // Set starting line
  compiler_env->compiler_set_start_line(compiler_env, compiler, start_line);
  
  // Add include paths
  AV* av_module_dirs;
  if (SvOK(sv_module_dirs)) {
    av_module_dirs = (AV*)SvRV(sv_module_dirs);
  }
  else {
    av_module_dirs = (AV*)sv_2mortal((SV*)newAV());
  }
  int32_t av_module_dirs_length = (int32_t)av_len(av_module_dirs) + 1;
  for (int32_t i = 0; i < av_module_dirs_length; i++) {
    SV** sv_include_dir_ptr = av_fetch(av_module_dirs, i, 0);
    SV* sv_include_dir = sv_include_dir_ptr ? *sv_include_dir_ptr : &PL_sv_undef;
    char* include_dir = SvPV_nolen(sv_include_dir);
    compiler_env->compiler_add_module_dir(compiler_env, compiler, include_dir);
  }

  // Compile SPVM
  int32_t compile_error_code = compiler_env->compiler_compile_spvm(compiler_env, compiler, class_name_copy);

  compiler_env->free_env_raw(compiler_env);

  SV* sv_compile_success;
  if (compile_error_code == 0) {
    sv_compile_success = sv_2mortal(newSViv(1));
  }
  else {
    sv_compile_success = sv_2mortal(newSViv(0));
  }
  
  XPUSHs(sv_compile_success);
  
  XSRETURN(1);
}

SV*
get_method_names(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  SV* sv_class_name = ST(1);
  SV* sv_category = ST(2);

  HV* hv_self = (HV*)SvRV(sv_self);

  // Name
  const char* class_name = SvPV_nolen(sv_class_name);

  // The environment for the compiler
  SV** sv_compiler_env_ptr = hv_fetch(hv_self, "compiler_env", strlen("compiler_env"), 0);
  SV* sv_compiler_env = sv_compiler_env_ptr ? *sv_compiler_env_ptr : &PL_sv_undef;
  SPVM_ENV* compiler_env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_compiler_env)));
  
  SPVM_COMPILER* compiler;
  SV** sv_compiler_ptr = hv_fetch(hv_self, "compiler", strlen("compiler"), 0);
  SV* sv_compiler = sv_compiler_ptr ? *sv_compiler_ptr : &PL_sv_undef;
  compiler = INT2PTR(SPVM_COMPILER*, SvIV(SvRV(sv_compiler)));

  AV* av_method_names = (AV*)sv_2mortal((SV*)newAV());
  SV* sv_method_names = sv_2mortal(newRV_inc((SV*)av_method_names));
  
  int32_t class_id = compiler_env->compiler_get_class_id(compiler_env, compiler, class_name);
  int32_t methods_length = compiler_env->compiler_get_methods_length(compiler_env, compiler, class_id);
  for (int32_t method_index = 0; method_index < methods_length; method_index++) {
    int32_t method_id = compiler_env->compiler_get_method_id(compiler_env, compiler, class_id, method_index);
    const char* method_name = compiler_env->compiler_get_method_name(compiler_env, compiler, method_id);
    SV* sv_method_name = sv_2mortal(newSVpv(method_name, 0));
    int32_t is_push = 0;
    if (SvOK(sv_category)) {
      if(strEQ(SvPV_nolen(sv_category), "native") && compiler_env->compiler_is_native_method(compiler_env, compiler, method_id)) {
        av_push(av_method_names, SvREFCNT_inc(sv_method_name));
      }
      else if (strEQ(SvPV_nolen(sv_category), "precompile") && compiler_env->compiler_is_precompile_method(compiler_env, compiler, method_id)) {
        av_push(av_method_names, SvREFCNT_inc(sv_method_name));
      }
    }
    else {
      av_push(av_method_names, SvREFCNT_inc(sv_method_name));
    }
  }
  
  XPUSHs(sv_method_names);
  XSRETURN(1);
}

SV*
get_anon_class_names_by_parent_class_name(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  SV* sv_class_name = ST(1);
  SV* sv_category = ST(2);

  HV* hv_self = (HV*)SvRV(sv_self);

  // Name
  const char* class_name = SvPV_nolen(sv_class_name);

  // The environment for the compiler
  SV** sv_compiler_env_ptr = hv_fetch(hv_self, "compiler_env", strlen("compiler_env"), 0);
  SV* sv_compiler_env = sv_compiler_env_ptr ? *sv_compiler_env_ptr : &PL_sv_undef;
  SPVM_ENV* compiler_env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_compiler_env)));
  
  // Compiler
  SPVM_COMPILER* compiler;
  SV** sv_compiler_ptr = hv_fetch(hv_self, "compiler", strlen("compiler"), 0);
  SV* sv_compiler = sv_compiler_ptr ? *sv_compiler_ptr : &PL_sv_undef;
  compiler = INT2PTR(SPVM_COMPILER*, SvIV(SvRV(sv_compiler)));

  AV* av_anon_class_names = (AV*)sv_2mortal((SV*)newAV());
  SV* sv_anon_class_names = sv_2mortal(newRV_inc((SV*)av_anon_class_names));
  
  // Copy class load path to builder
  SPVM_CLASS* class = SPVM_HASH_fetch(compiler->class_symtable, class_name, strlen(class_name));

  int32_t methods_length = compiler_env->compiler_get_methods_length(compiler_env, compiler, class->id);

  for (int32_t method_index = 0; method_index < methods_length; method_index++) {
    
    SPVM_METHOD* method = SPVM_LIST_fetch(class->methods, method_index);
    int32_t method_id = method->id;
    int32_t is_anon_method = compiler_env->compiler_is_anon_method(compiler_env, compiler, method_id);
    
    if (is_anon_method) {
      SPVM_CLASS* anon_class = SPVM_LIST_fetch(compiler->classes, method->class->id);
      const char* anon_class_name = anon_class->name;
      SV* sv_anon_class_name = sv_2mortal(newSVpv(anon_class_name, 0));
      av_push(av_anon_class_names, SvREFCNT_inc(sv_anon_class_name));
    }
  }
  
  XPUSHs(sv_anon_class_names);
  XSRETURN(1);
}

SV*
get_class_names_exclude_anon(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);

  HV* hv_self = (HV*)SvRV(sv_self);

  // The environment for the compiler
  SV** sv_compiler_env_ptr = hv_fetch(hv_self, "compiler_env", strlen("compiler_env"), 0);
  SV* sv_compiler_env = sv_compiler_env_ptr ? *sv_compiler_env_ptr : &PL_sv_undef;
  SPVM_ENV* compiler_env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_compiler_env)));

  SV** sv_compiler_ptr = hv_fetch(hv_self, "compiler", strlen("compiler"), 0);
  SV* sv_compiler = sv_compiler_ptr ? *sv_compiler_ptr : &PL_sv_undef;
  SPVM_COMPILER* compiler = INT2PTR(SPVM_COMPILER*, SvIV(SvRV(sv_compiler)));

  AV* av_class_names = (AV*)sv_2mortal((SV*)newAV());
  SV* sv_class_names = sv_2mortal(newRV_inc((SV*)av_class_names));

  int32_t classes_legnth = compiler_env->compiler_get_classes_length(compiler_env, compiler);

  for (int32_t class_id = 0; class_id < classes_legnth; class_id++) {
    const char* class_name = compiler_env->compiler_get_class_name(compiler_env, compiler, class_id);
    int32_t is_anon_class = compiler_env->compiler_is_anon_class(compiler_env, compiler, class_id);
    if (!is_anon_class) {
      SV* sv_class_name = sv_2mortal(newSVpv(class_name, 0));
      av_push(av_class_names, SvREFCNT_inc(sv_class_name));
    }
  }
  
  XPUSHs(sv_class_names);
  XSRETURN(1);
}

SV*
get_class_names(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);

  HV* hv_self = (HV*)SvRV(sv_self);

  // The environment for the compiler
  SV** sv_compiler_env_ptr = hv_fetch(hv_self, "compiler_env", strlen("compiler_env"), 0);
  SV* sv_compiler_env = sv_compiler_env_ptr ? *sv_compiler_env_ptr : &PL_sv_undef;
  SPVM_ENV* compiler_env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_compiler_env)));

  SPVM_COMPILER* compiler;
  SV** sv_compiler_ptr = hv_fetch(hv_self, "compiler", strlen("compiler"), 0);
  SV* sv_compiler = sv_compiler_ptr ? *sv_compiler_ptr : &PL_sv_undef;
  compiler = INT2PTR(SPVM_COMPILER*, SvIV(SvRV(sv_compiler)));

  AV* av_class_names = (AV*)sv_2mortal((SV*)newAV());
  SV* sv_class_names = sv_2mortal(newRV_inc((SV*)av_class_names));
  
  int32_t classes_legnth = compiler_env->compiler_get_classes_length(compiler_env, compiler);
  for (int32_t class_id = 0; class_id < classes_legnth; class_id++) {
    const char* class_name = compiler_env->compiler_get_class_name(compiler_env, compiler, class_id);
    SV* sv_class_name = sv_2mortal(newSVpv(class_name, 0));
    av_push(av_class_names, SvREFCNT_inc(sv_class_name));
  }
  
  XPUSHs(sv_class_names);
  XSRETURN(1);
}

SV*
get_error_messages(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);

  HV* hv_self = (HV*)SvRV(sv_self);

  // The environment for the compiler
  SV** sv_compiler_env_ptr = hv_fetch(hv_self, "compiler_env", strlen("compiler_env"), 0);
  SV* sv_compiler_env = sv_compiler_env_ptr ? *sv_compiler_env_ptr : &PL_sv_undef;
  SPVM_ENV* compiler_env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_compiler_env)));
  
  // Compiler
  SV** sv_compiler_ptr = hv_fetch(hv_self, "compiler", strlen("compiler"), 0);
  SV* sv_compiler = sv_compiler_ptr ? *sv_compiler_ptr : &PL_sv_undef;
  SPVM_COMPILER* compiler = INT2PTR(SPVM_COMPILER*, SvIV(SvRV(sv_compiler)));

  AV* av_error_messages = (AV*)sv_2mortal((SV*)newAV());
  SV* sv_error_messages = sv_2mortal(newRV_inc((SV*)av_error_messages));

  int32_t error_messages_legnth = compiler_env->compiler_get_error_messages_length(compiler_env, compiler);

  for (int32_t i = 0; i < error_messages_legnth; i++) {
    const char* error_message = compiler_env->compiler_get_error_message(compiler_env, compiler, i);
    SV* sv_error_message = sv_2mortal(newSVpv(error_message, 0));
    av_push(av_error_messages, SvREFCNT_inc(sv_error_message));
  }
  
  XPUSHs(sv_error_messages);
  XSRETURN(1);
}

SV*
get_classes_length(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);

  HV* hv_self = (HV*)SvRV(sv_self);

  SPVM_COMPILER* compiler;
  SV** sv_compiler_ptr = hv_fetch(hv_self, "compiler", strlen("compiler"), 0);
  SV* sv_compiler = sv_compiler_ptr ? *sv_compiler_ptr : &PL_sv_undef;
  compiler = INT2PTR(SPVM_COMPILER*, SvIV(SvRV(sv_compiler)));
  
  int32_t classes_length = compiler->classes->length;
  SV* sv_classes_length = sv_2mortal(newSViv(classes_length));
  
  XPUSHs(sv_classes_length);
  XSRETURN(1);
}

SV*
get_module_file(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  SV* sv_class_name = ST(1);

  HV* hv_self = (HV*)SvRV(sv_self);

  // Name
  const char* class_name = SvPV_nolen(sv_class_name);

  SPVM_COMPILER* compiler;
  SV** sv_compiler_ptr = hv_fetch(hv_self, "compiler", strlen("compiler"), 0);
  SV* sv_compiler = sv_compiler_ptr ? *sv_compiler_ptr : &PL_sv_undef;
  compiler = INT2PTR(SPVM_COMPILER*, SvIV(SvRV(sv_compiler)));

  // Copy class load path to builder
  SPVM_RUNTIME_CLASS* class = SPVM_HASH_fetch(compiler->class_symtable, class_name, strlen(class_name));
  const char* module_file;
  SV* sv_module_file;
  if (class) {
    module_file = class->module_file;
    sv_module_file = sv_2mortal(newSVpv(module_file, 0));
  }
  else {
    sv_module_file = &PL_sv_undef;
  }
  
  XPUSHs(sv_module_file);
  XSRETURN(1);
}

SV*
get_module_source(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  SV* sv_class_name = ST(1);

  HV* hv_self = (HV*)SvRV(sv_self);
  
  // Name
  const char* class_name = SvPV_nolen(sv_class_name);

  SPVM_COMPILER* compiler;
  SV** sv_compiler_ptr = hv_fetch(hv_self, "compiler", strlen("compiler"), 0);
  SV* sv_compiler = sv_compiler_ptr ? *sv_compiler_ptr : &PL_sv_undef;
  compiler = INT2PTR(SPVM_COMPILER*, SvIV(SvRV(sv_compiler)));

  // Copy class load path to builder
  SV* sv_module_source;
  const char* module_source = SPVM_HASH_fetch(compiler->module_source_symtable, class_name, strlen(class_name));
  if (module_source) {
    sv_module_source = sv_2mortal(newSVpv(module_source, 0));
  }
  else {
    sv_module_source = &PL_sv_undef;
  }

  XPUSHs(sv_module_source);
  XSRETURN(1);
}

SV*
_init(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);

  SV** sv_compiler_ptr = hv_fetch(hv_self, "compiler", strlen("compiler"), 0);
  SV* sv_compiler = sv_compiler_ptr ? *sv_compiler_ptr : &PL_sv_undef;
  SPVM_COMPILER* compiler = INT2PTR(SPVM_COMPILER*, SvIV(SvRV(sv_compiler)));
  
  for (int32_t i = 0; i < compiler->methods->length; i++) {
    SPVM_METHOD* method = SPVM_LIST_fetch(compiler->methods, i);
    SPVM_RUNTIME_METHOD* runtime_method = SPVM_LIST_fetch(compiler->runtime_methods, i);
    
    runtime_method->precompile_address = method->precompile_address;
    runtime_method->native_address = method->native_address;
  }
  
  // Create env
  SPVM_ENV* env = SPVM_API_new_env_raw(NULL);
  
  if (env == NULL) {
    croak("Can't create SPVM env");
  }

  // Set the compiler
  env->compiler = compiler;
  
  // Don't use compiler information
  compiler->strings = NULL;
  compiler->string_symtable = NULL;

  compiler->types = NULL;
  compiler->type_symtable = NULL;
  
  // Initialize env
  SPVM_API_init_env(env);

  env->call_init_blocks(env);
  
  // Set ENV
  size_t iv_env = PTR2IV(env);
  SV* sviv_env = sv_2mortal(newSViv(iv_env));
  SV* sv_env = sv_2mortal(newRV_inc(sviv_env));
  (void)hv_store(hv_self, "env", strlen("env"), SvREFCNT_inc(sv_env), 0);
}

SV*
set_native_method_address(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  SV* sv_class_name = ST(1);
  SV* sv_method_name = ST(2);
  SV* sv_native_address = ST(3);

  // The environment for the compiler
  SV** sv_compiler_env_ptr = hv_fetch(hv_self, "compiler_env", strlen("compiler_env"), 0);
  SV* sv_compiler_env = sv_compiler_env_ptr ? *sv_compiler_env_ptr : &PL_sv_undef;
  SPVM_ENV* compiler_env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_compiler_env)));

  // Compiler
  SV** sv_compiler_ptr = hv_fetch(hv_self, "compiler", strlen("compiler"), 0);
  SV* sv_compiler = sv_compiler_ptr ? *sv_compiler_ptr : &PL_sv_undef;
  SPVM_COMPILER* compiler = INT2PTR(SPVM_COMPILER*, SvIV(SvRV(sv_compiler)));

  // Class name
  const char* class_name = SvPV_nolen(sv_class_name);

  // Method name
  const char* method_name = SvPV_nolen(sv_method_name);
  
  // Method id
  int32_t method_id = compiler_env->compiler_get_method_id_by_name(compiler_env, compiler, class_name, method_name);
  
  // Native address
  void* native_address = INT2PTR(void*, SvIV(sv_native_address));
  
  compiler_env->compiler_set_native_method_address(compiler_env, compiler, method_id, native_address);

  assert(native_address == compiler_env->compiler_get_native_method_address(compiler_env, compiler, method_id));

  XSRETURN(0);
}

SV*
set_precompile_method_address(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  SV* sv_class_name = ST(1);
  SV* sv_method_name = ST(2);
  SV* sv_precompile_address = ST(3);

  // The environment for the compiler
  SV** sv_compiler_env_ptr = hv_fetch(hv_self, "compiler_env", strlen("compiler_env"), 0);
  SV* sv_compiler_env = sv_compiler_env_ptr ? *sv_compiler_env_ptr : &PL_sv_undef;
  SPVM_ENV* compiler_env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_compiler_env)));

  // Compiler
  SV** sv_compiler_ptr = hv_fetch(hv_self, "compiler", strlen("compiler"), 0);
  SV* sv_compiler = sv_compiler_ptr ? *sv_compiler_ptr : &PL_sv_undef;
  SPVM_COMPILER* compiler = INT2PTR(SPVM_COMPILER*, SvIV(SvRV(sv_compiler)));

  // Class name
  const char* class_name = SvPV_nolen(sv_class_name);

  // Method name
  const char* method_name = SvPV_nolen(sv_method_name);
  
  // Method id
  int32_t method_id = compiler_env->compiler_get_method_id_by_name(compiler_env, compiler, class_name, method_name);
  
  // Native address
  void* precompile_address = INT2PTR(void*, SvIV(sv_precompile_address));
  
  compiler_env->compiler_set_precompile_method_address(compiler_env, compiler, method_id, precompile_address);

  assert(precompile_address == compiler_env->compiler_get_precompile_method_address(compiler_env, compiler, method_id));

  XSRETURN(0);
}

SV*
DESTROY(...)
  PPCODE:
{
  (void)RETVAL;
  
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  
  SV** sv_env_ptr = hv_fetch(hv_self, "env", strlen("env"), 0);
  SV* sv_env = sv_env_ptr ? *sv_env_ptr : &PL_sv_undef;
  if (SvOK(sv_env)) {
    SPVM_ENV* env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_env)));
    
    // Cleanup global variables
    SPVM_API_cleanup_global_vars(env);
    
    env->free_env_raw(env);
  }
  
  // Compiler env
  SV** sv_compiler_env_ptr = hv_fetch(hv_self, "compiler_env", strlen("compiler_env"), 0);
  SV* sv_compiler_env = sv_compiler_env_ptr ? *sv_compiler_env_ptr : &PL_sv_undef;
  SPVM_ENV* compiler_env = INT2PTR(SPVM_ENV*, SvIV(SvRV(sv_compiler_env)));
  
  // Free compiler
  SV** sv_compiler_ptr = hv_fetch(hv_self, "compiler", strlen("compiler"), 0);
  SV* sv_compiler = sv_compiler_ptr ? *sv_compiler_ptr : &PL_sv_undef;
  SPVM_COMPILER* compiler = INT2PTR(SPVM_COMPILER*, SvIV(SvRV(sv_compiler)));
  compiler_env->compiler_free(compiler_env, compiler);
  
  // Free the environment for the compiler
  compiler_env->free_env_raw(compiler_env);
  compiler_env = NULL;
}

MODULE = SPVM::Builder::CC		PACKAGE = SPVM::Builder::CC

SV*
build_class_csource_precompile(...)
  PPCODE:
{
  SV* sv_self = ST(0);
  HV* hv_self = (HV*)SvRV(sv_self);
  SV* sv_class_name = ST(1);
  const char* class_name = SvPV_nolen(sv_class_name);
  
  // Env
  SV** sv_builder_ptr = hv_fetch(hv_self, "builder", strlen("builder"), 0);
  SV* sv_builder = sv_builder_ptr ? *sv_builder_ptr : &PL_sv_undef;
  HV* hv_builder = (HV*)SvRV(sv_builder);

  SPVM_COMPILER* compiler;
  SV** sv_compiler_ptr = hv_fetch(hv_builder, "compiler", strlen("compiler"), 0);
  SV* sv_compiler = sv_compiler_ptr ? *sv_compiler_ptr : &PL_sv_undef;
  compiler = INT2PTR(SPVM_COMPILER*, SvIV(SvRV(sv_compiler)));
  
  // String buffer for csource
  SPVM_STRING_BUFFER* string_buffer = SPVM_STRING_BUFFER_new(compiler->allocator, 0, 0, NULL);

  // Build class csource
  
  int32_t build_class_csource_start_memory_blocks_count_compile_tmp = compiler->allocator->memory_blocks_count_compile_tmp;
  SPVM_CSOURCE_BUILDER_PRECOMPILE_build_class_csource(compiler, string_buffer, class_name);
  assert(compiler->allocator->memory_blocks_count_compile_tmp == build_class_csource_start_memory_blocks_count_compile_tmp);
  
  SV* sv_class_csource = sv_2mortal(newSVpv(string_buffer->buffer, string_buffer->length));
  
  SPVM_STRING_BUFFER_free(string_buffer);

  XPUSHs(sv_class_csource);
  XSRETURN(1);
}

MODULE = SPVM		PACKAGE = SPVM
