#ifndef SPVM_BASE_H
#define SPVM_BASE_H

#include <stdint.h>
#include <stdlib.h>

/* spvm_value.h */
union SPVM_value;
typedef union SPVM_value SPVM_VALUE;

/* spvm_ref_array.h */
struct SPVM_ref_array;
typedef struct SPVM_ref_array SPVM_REF_ARRAY;

/* spvm_ref.h */
struct SPVM_ref;
typedef struct SPVM_ref SPVM_REF;

/* spvm_ref_string.h */
struct SPVM_ref_string;
typedef struct SPVM_ref_string SPVM_REF_STRING;

/* spvm_ref_object.h */
struct SPVM_ref_object;
typedef struct SPVM_ref_object SPVM_REF_OBJECT;

/* spvm_env.h */
struct SPVM_sv;
typedef struct SPVM_sv SPVM_SV;

/* spvm_allocator_runtime.h */
struct SPVM_allocator_runtime;
typedef struct SPVM_allocator_runtime SPVM_ALLOCATOR_RUNTIME;

/* spvm_allocator_parser.h */
struct SPVM_allocator_parser;
typedef struct SPVM_allocator_parser SPVM_ALLOCATOR_PARSER;

/* spvm_env.h */
struct SPVM_env;
typedef struct SPVM_env SPVM_ENV;

/* spvm_heap.h */
struct SPVM_heap;
typedef struct SPVM_heap SPVM_HEAP;

/* spvm_parser.h */
struct SPVM_parser;
typedef struct SPVM_parser SPVM_PARSER;

/* spvm_vm.h */
struct SPVM_vm_stack;
typedef struct SPVM_vm_stack SPVM_VM_STACK;

/* spvm_vm.h */
struct SPVM_vm;
typedef struct SPVM_vm SPVM_VM;

/* spvm_switch.h */
struct SPVM_switch_info;
typedef struct SPVM_switch_info SPVM_SWITCH_INFO;

/* spvm_allocator_parser.h */
struct SPVM_allocator;
typedef struct SPVM_allocator SPVM_ALLOCATOR;

/* spvm_dumper.h */
struct SPVM_dumper;
typedef struct SPVM_dumper SPVM_DUMPER;

/* spvm_bytecode_array.h */
struct SPVM_bytecode_array;
typedef struct SPVM_bytecode_array SPVM_BYTECODE_ARRAY;

/* spvm_assign.h */
struct SPVM_bytecode;
typedef struct SPVM_bytecode SPVM_BYTECODE;

/* spvm_vmcode.h */
struct SPVM_vmcodes;
typedef struct SPVM_vmcodes SPVM_VMCODES;

/* spvm_constant_pool_field.h */
struct SPVM_constant_pool_field;
typedef struct SPVM_constant_pool_field SPVM_CONSTANT_POOL_FIELD;

/* spvm_constant_pool_package.h */
struct SPVM_constant_pool_package;
typedef struct SPVM_constant_pool_package SPVM_CONSTANT_POOL_PACKAGE;

/* spvm_constant_pool_sub.h */
struct SPVM_constant_pool_sub;
typedef struct SPVM_constant_pool_sub SPVM_CONSTANT_POOL_SUB;

/* spvm_constant_pool.h */
struct SPVM_constant_pool;
typedef struct SPVM_constant_pool SPVM_CONSTANT_POOL;

/* spvm_vmcode.h */
struct SPVM_vmcode;
typedef struct SPVM_vmcode SPVM_VMCODE;

/* spvm_resolved_type.h */
struct SPVM_resolved_type;
typedef struct SPVM_resolved_type SPVM_RESOLVED_TYPE;

/* spvm_assign.h */
struct SPVM_assign;
typedef struct SPVM_assign SPVM_ASSIGN;

/* spvm_package.h */
struct SPVM_package;
typedef struct SPVM_package SPVM_PACKAGE;

/* spvm_type.h */
struct SPVM_name_info;
typedef struct SPVM_name_info SPVM_NAME_INFO;

/* spvm_type.h */
struct SPVM_type;
typedef struct SPVM_type SPVM_TYPE;

/* spvm_type_component_array.h */
struct SPVM_type_part;
typedef struct SPVM_type_part SPVM_TYPE_PART;

/* spvm_type_component_array.h */
struct SPVM_type_component_name;
typedef struct SPVM_type_component_name SPVM_TYPE_COMPONENT_NAME;

/* spvm_type_component_array.h */
struct SPVM_type_component_array;
typedef struct SPVM_type_component_array SPVM_TYPE_COMPONENT_ARRAY;

/* spvm_enum.h */
struct SPVM_enumeration;
typedef struct SPVM_enumeration SPVM_ENUMERATION;

/* spvm_enumeration_value.h */
struct SPVM_enumeration_value;
typedef struct SPVM_enumeration_value SPVM_ENUMERATION_VALUE;

/* spvm_use.h */
struct SPVM_use;
typedef struct SPVM_use SPVM_USE;

/* spvm_memory_pool.h */
struct SPVM_memory_pool;
typedef struct SPVM_memory_pool SPVM_MEMORY_POOL;

/* spvm_var.h */
struct SPVM_var;
typedef struct SPVM_var SPVM_VAR;

/* spvm_my_var.h */
struct SPVM_my_var;
typedef struct SPVM_my_var SPVM_MY_VAR;

/* spvm_constant.h */
struct SPVM_constant;
typedef struct SPVM_constant SPVM_CONSTANT;

/* spvm_op.h */
struct SPVM_op;
typedef struct SPVM_op SPVM_OP;

/* spvm_field.h */
struct SPVM_field;
typedef struct SPVM_field SPVM_FIELD;

/* spvm_descriptor.h */
struct SPVM_descriptor;
typedef struct SPVM_descriptor SPVM_DESCRIPTOR;

/* spvm_sub.h */
struct SPVM_sub;
typedef struct SPVM_sub SPVM_SUB;

/* spvm_array_element.h */
struct SPVM_array_element;
typedef struct SPVM_array_element SPVM_ARRAY_ELEMENT;

/* spvm_array.h */
struct SPVM_array;
typedef struct SPVM_array SPVM_ARRAY;

/* spvm_hash.h */
struct SPVM_hash_entry;
typedef struct SPVM_hash_entry SPVM_HASH_ENTRY;

struct SPVM_hash;
typedef struct SPVM_hash SPVM_HASH;

/* spvm.h */
struct spvm_;
typedef struct spvm_ SPVM;

union SPVM_yystype;
typedef union SPVM_yystype SPVM_YYSTYPE;

#endif
