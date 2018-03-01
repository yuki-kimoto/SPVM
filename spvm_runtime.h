#ifndef SPVM_RUNTIME_H
#define SPVM_RUNTIME_H

#include "spvm_base.h"
#include "spvm_api.h"

struct SPVM_runtime {
  // Exception
  SPVM_OBJECT* exception;
  
  // Runtime memory allocator
  SPVM_RUNTIME_ALLOCATOR* allocator;

  // Env
  SPVM_API* api;
  
  // opcodes
  SPVM_OPCODE* opcodes;
  
  // Constant pool
  int32_t* constant_pool;
  
  // Constant pool subroutine symbol table
  SPVM_HASH* sub_symtable;
  
  // Constant pool type symbol table
  SPVM_HASH* type_symtable;

  // Constant pool package symbol table
  SPVM_HASH* package_symtable;
  
  // Constant pool field symbol table
  SPVM_HASH* field_symtable;
  
  // Module include symbol table
  SPVM_HASH* use_package_path_id_symtable;
  
  // Package variables
  SPVM_API_VALUE* package_vars;
  
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
  
  char* jit_source_file;
  
  int32_t jit_count;
};

SPVM_RUNTIME* SPVM_RUNTIME_new();
void SPVM_RUNTIME_free(SPVM_RUNTIME* runtime);
SPVM_API* SPVM_RUNTIME_new_api(SPVM_RUNTIME* runtime);

SPVM_API_VALUE SPVM_RUNTIME_call_sub(SPVM_API* api, int32_t sub_id, SPVM_API_VALUE* args);

SPVM_API_VALUE SPVM_RUNTIME_call_sub_native(SPVM_API* api, int32_t sub_id, SPVM_API_VALUE* args);
SPVM_API_VALUE SPVM_RUNTIME_call_sub_jit(SPVM_API* api, int32_t sub_id, SPVM_API_VALUE* args);
SPVM_API_VALUE SPVM_RUNTIME_call_sub_vm(SPVM_API* api, int32_t sub_id, SPVM_API_VALUE* args);

#endif
