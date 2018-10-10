#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <stddef.h>

#include "spvm_native.h"

#include "spvm_list.h"
#include "spvm_hash.h"
#include "spvm_object.h"
#include "spvm_util_allocator.h"

#include "spvm_runtime.h"
#include "spvm_runtime_api.h"
#include "spvm_runtime_allocator.h"
#include "spvm_runtime_basic_type.h"
#include "spvm_runtime_package.h"
#include "spvm_runtime_sub.h"
#include "spvm_runtime_field.h"
#include "spvm_runtime_package_var.h"
#include "spvm_runtime_my.h"
#include "spvm_runtime_info_type.h"
#include "spvm_runtime_info_switch_info.h"
#include "spvm_runtime_info_case_info.h"
#include "spvm_portable.h"

// Only use for constant value
#include "spvm_type.h"
#include "spvm_package.h"
#include "spvm_package_var.h"
#include "spvm_sub.h"
#include "spvm_basic_type.h"
#include "spvm_field.h"

void SPVM_RUNTIME_free(SPVM_ENV* env) {
  
  SPVM_RUNTIME* runtime = env->runtime;
  
  // Free exception
  SPVM_RUNTIME_API_set_exception(env, NULL);
  
  // Free portable
  SPVM_PORTABLE_free(runtime->portable);
  
  free(runtime->sub_native_addresses);
  free(runtime->sub_precompile_addresses);
  
  if (runtime->exception != NULL) {
    free(runtime->exception);
  }
  
  free(runtime->mortal_stack);
  
  SPVM_HASH_free(runtime->basic_type_symtable);
  SPVM_HASH_free(runtime->field_symtable);
  SPVM_HASH_free(runtime->sub_symtable);
  
  for (int32_t switch_index = 0; switch_index < runtime->info_switch_infos->length; switch_index++) {
    SPVM_RUNTIME_INFO_SWITCH_INFO* info_switch_info = SPVM_LIST_fetch(runtime->info_switch_infos, switch_index);
    
    SPVM_LIST* case_infos = info_switch_info->case_infos;
    for (int32_t case_index = 0; case_index < case_infos->length; case_index++) {
      SPVM_RUNTIME_INFO_CASE_INFO* info_case_info = SPVM_LIST_fetch(case_infos, case_index);
      free(info_case_info);
    }
    SPVM_LIST_free(info_switch_info->case_infos);
  }
  SPVM_LIST_free(runtime->info_switch_infos);

  for (int32_t package_id = 0; package_id < runtime->packages_length; package_id++) {
    
    SPVM_RUNTIME_PACKAGE* package = &runtime->packages[package_id];
    
    SPVM_LIST_free(package->fields);
    SPVM_LIST_free(package->field_signatures);
    SPVM_LIST_free(package->package_vars);
    SPVM_LIST_free(package->package_var_signatures);
    SPVM_LIST_free(package->subs);
    SPVM_LIST_free(package->sub_signatures);
    SPVM_LIST_free(package->object_field_indexes);

    SPVM_HASH_free(package->field_symtable);
    SPVM_HASH_free(package->field_signature_symtable);
    SPVM_HASH_free(package->package_var_symtable);
    SPVM_HASH_free(package->package_var_signature_symtable);
    SPVM_HASH_free(package->sub_symtable);
    SPVM_HASH_free(package->sub_signature_symtable);
  }
  SPVM_HASH_free(runtime->package_symtable);

  // Free package variables heap
  free(runtime->package_vars_heap);
  
  // Free runtime
  free(runtime);
}
