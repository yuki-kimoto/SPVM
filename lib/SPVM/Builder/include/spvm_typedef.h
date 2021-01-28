#ifndef SPVM_TYPEDEF_H
#define SPVM_TYPEDEF_H

#include <stdint.h>
#include <stdlib.h>

// spvm_allow.h
struct SPVM_allow;
typedef struct SPVM_allow SPVM_ALLOW;

// spvm_mem.h
struct SPVM_mem;
typedef struct SPVM_mem SPVM_MEM;

// spvm_runtime_weaken_backref.h
struct SPVM_weaken_backref;
typedef struct SPVM_weaken_backref SPVM_WEAKEN_BACKREF;

// spvm_check_ast_info.h
struct SPVM_check_ast_info;
typedef struct SPVM_check_ast_info SPVM_CHECK_AST_INFO;

// spvm_array_field_access.h
struct SPVM_array_field_access;
typedef struct SPVM_array_field_access SPVM_ARRAY_FIELD_ACCESS;

// spvm_case_info.h
struct SPVM_case_info;
typedef struct SPVM_case_info SPVM_CASE_INFO;

// spvm_basic_type.h
struct SPVM_basic_type;
typedef struct SPVM_basic_type SPVM_BASIC_TYPE;

// spvm_opcode_array.h
struct SPVM_opcode_array;
typedef struct SPVM_opcode_array SPVM_OPCODE_ARRAY;

// spvm_opcode.h
struct SPVM_opcode;
typedef struct SPVM_opcode SPVM_OPCODE;

// spvm_undef.h
struct SPVM_undef;
typedef struct SPVM_undef SPVM_UNDEF;

// spvm_string_buffer.h
struct SPVM_string_buffer;
typedef struct SPVM_string_buffer SPVM_STRING_BUFFER;

// spvm_package_var_access.h
struct SPVM_package_var_access;
typedef struct SPVM_package_var_access SPVM_PACKAGE_VAR_ACCESS;

// spvm_package_var.h
struct SPVM_package_var;
typedef struct SPVM_package_var SPVM_PACKAGE_VAR;

// spvm_call_sub.h
struct SPVM_call_sub;
typedef struct SPVM_call_sub SPVM_CALL_SUB;

// spvm_sub_check_info.h
struct SPVM_sub_check_info;
typedef struct SPVM_sub_check_info SPVM_SUB_CHECK_INFO;

// spvm_object.h
struct SPVM_object;
typedef struct SPVM_object SPVM_OBJECT;

// spvm_block.h
struct SPVM_block;
typedef struct SPVM_block SPVM_BLOCK;

// spvm_use.h
struct SPVM_use;
typedef struct SPVM_use SPVM_USE;

// spvm_runtime.h
struct SPVM_runtime;
typedef struct SPVM_runtime SPVM_RUNTIME;

// spvm_compiler_allocator.h
struct SPVM_compiler_allocator;
typedef struct SPVM_compiler_allocator SPVM_COMPILER_ALLOCATOR;

// spvm_heap.h
struct SPVM_heap;
typedef struct SPVM_heap SPVM_HEAP;

// spvm_compiler.h
struct SPVM_compiler;
typedef struct SPVM_compiler SPVM_COMPILER;

// spvm_vm.h
struct SPVM_vm_stack;
typedef struct SPVM_vm_stack SPVM_VM_STACK;

// spvm_vm.h
struct SPVM_vm;
typedef struct SPVM_vm SPVM_VM;

// spvm_switch.h
struct SPVM_switch_info;
typedef struct SPVM_switch_info SPVM_SWITCH_INFO;

// spvm_compiler_allocator.h
struct SPVM_allocator;
typedef struct SPVM_allocator SPVM_ALLOCATOR;

// spvm_dumper.h
struct SPVM_dumper;
typedef struct SPVM_dumper SPVM_DUMPER;

// spvm_vmcode.h
struct SPVM_vmcodes;
typedef struct SPVM_vmcodes SPVM_VMCODES;

// spvm_vmcode.h
struct SPVM_vmcode;
typedef struct SPVM_vmcode SPVM_VMCODE;

// spvm_assign.h
struct SPVM_assign;
typedef struct SPVM_assign SPVM_ASSIGN;

// spvm_package.h
struct SPVM_package;
typedef struct SPVM_package SPVM_PACKAGE;

// spvm_field_access.h
struct SPVM_field_access;
typedef struct SPVM_field_access SPVM_FIELD_ACCESS;

// spvm_type.h
struct SPVM_type;
typedef struct SPVM_type SPVM_TYPE;

// spvm_type_component_array.h
struct SPVM_type_part;
typedef struct SPVM_type_part SPVM_TYPE_PART;

// spvm_enum.h
struct SPVM_enumeration;
typedef struct SPVM_enumeration SPVM_ENUMERATION;

// spvm_enumeration_value.h
struct SPVM_enumeration_value;
typedef struct SPVM_enumeration_value SPVM_ENUMERATION_VALUE;

// spvm_var.h
struct SPVM_var;
typedef struct SPVM_var SPVM_VAR;

// spvm_my.h
struct SPVM_my;
typedef struct SPVM_my SPVM_MY;

// spvm_constant.h
struct SPVM_constant;
typedef struct SPVM_constant SPVM_CONSTANT;

// spvm_op.h
struct SPVM_op;
typedef struct SPVM_op SPVM_OP;

// spvm_field.h
struct SPVM_field;
typedef struct SPVM_field SPVM_FIELD;

// spvm_descriptor.h
struct SPVM_descriptor;
typedef struct SPVM_descriptor SPVM_DESCRIPTOR;

// spvm_sub.h
struct SPVM_sub;
typedef struct SPVM_sub SPVM_SUB;

// spvm_list.h
struct SPVM_list;
typedef struct SPVM_list SPVM_LIST;

// spvm_hash_entry.h
struct SPVM_hash_entry;
typedef struct SPVM_hash_entry SPVM_HASH_ENTRY;

// spvm_hash.h
struct SPVM_hash;
typedef struct SPVM_hash SPVM_HASH;

union SPVM_yystype;
typedef union SPVM_yystype SPVM_YYSTYPE;

#endif
