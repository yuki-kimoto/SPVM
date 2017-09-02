#ifndef SPVM_RUNTIME_H
#define SPVM_RUNTIME_H

#include "spvm_base.h"
#include "spvm_api.h"

struct SPVM_runtime {
  
  // Runtime memory allocator
  SPVM_RUNTIME_ALLOCATOR* allocator;

  // Env
  SPVM_API* api;
  
  // Exception
  SPVM_OBJECT* exception;
  
  // Bytecodes
  uint8_t* bytecodes;
  
  // Constant pool
  int32_t* constant_pool;
  
  // Constant pool subroutine symbol table
  SPVM_HASH* sub_id_symtable;
  
  // Constant pool type symbol table
  SPVM_HASH* type_id_symtable;
  
  // Constant pool type symbol table
  SPVM_HASH* field_id_symtable;
  
  // Constant pool type symbol table
  SPVM_HASH* field_info_id_symtable;
  
  // Module include symbol table
  SPVM_HASH* use_package_id_symtable;
  
  // Packages length
  int32_t packages_length;
  
  // Package base
  int32_t packages_base;
  
  // Subroutines length
  int32_t subs_length;
  
  // Subroutine base
  int32_t subs_base;
  
  // Subroutines length
  int32_t types_length;
  
  // Subroutine base
  int32_t types_base;
  
  // Type code to id
  int32_t type_code_to_id_base;
  
  int32_t objects_count;
  
  int32_t debug;
};

SPVM_RUNTIME* SPVM_RUNTIME_new();
void SPVM_RUNTIME_free(SPVM_RUNTIME* runtime);
SPVM_API* SPVM_RUNTIME_new_api(SPVM_RUNTIME* runtime);

SPVM_VALUE SPVM_RUNTIME_call_sub(SPVM_API* api, int32_t sub_id, SPVM_VALUE* args);

#endif
