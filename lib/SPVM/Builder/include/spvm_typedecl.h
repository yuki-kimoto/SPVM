#ifndef SPVM_TYPEDECL_H
#define SPVM_TYPEDECL_H

#include <stdint.h>
#include <stddef.h>

// spvm_precompile.h
struct spvm_precompile;
typedef struct spvm_precompile SPVM_PRECOMPILE;

// spvm_runtime_basic_type.h
struct spvm_runtime_basic_type;
typedef struct spvm_runtime_basic_type SPVM_RUNTIME_BASIC_TYPE;

// spvm_runtime_type.h
struct spvm_runtime_type;
typedef struct spvm_runtime_type SPVM_RUNTIME_TYPE;

// spvm_runtime_constant_string.h
struct spvm_runtime_constant_string;
typedef struct spvm_runtime_constant_string SPVM_RUNTIME_CONSTANT_STRING;

// spvm_runtime_field.h
struct spvm_runtime_field;
typedef struct spvm_runtime_field SPVM_RUNTIME_FIELD;

// spvm_runtime_method.h
struct spvm_runtime_method;
typedef struct spvm_runtime_method SPVM_RUNTIME_METHOD;

// spvm_runtime_class_var.h
struct spvm_runtime_class_var;
typedef struct spvm_runtime_class_var SPVM_RUNTIME_CLASS_VAR;

// spvm_runtime_class.h
struct spvm_runtime_class;
typedef struct spvm_runtime_class SPVM_RUNTIME_CLASS;

// spvm_constant_string.h
struct spvm_constant_string;
typedef struct spvm_constant_string SPVM_CONSTANT_STRING;

// spvm_interface.h
struct spvm_interface;
typedef struct spvm_interface SPVM_INTERFACE;

// spvm_hash.h
struct spvm_hash;
typedef struct spvm_hash SPVM_HASH;
struct spvm_hash_entry;
typedef struct spvm_hash_entry SPVM_HASH_ENTRY;

// spvm_list.h
struct spvm_list;
typedef struct spvm_list SPVM_LIST;

// spvm_allow.h
struct spvm_allow;
typedef struct spvm_allow SPVM_ALLOW;

// spvm_runtime_weaken_backref.h
struct spvm_weaken_backref;
typedef struct spvm_weaken_backref SPVM_WEAKEN_BACKREF;

// spvm_check_ast_info.h
struct spvm_check_ast_info;
typedef struct spvm_check_ast_info SPVM_CHECK_AST_INFO;

// spvm_array_field_access.h
struct spvm_array_field_access;
typedef struct spvm_array_field_access SPVM_ARRAY_FIELD_ACCESS;

// spvm_case_info.h
struct spvm_case_info;
typedef struct spvm_case_info SPVM_CASE_INFO;

// spvm_basic_type.h
struct spvm_basic_type;
typedef struct spvm_basic_type SPVM_BASIC_TYPE;

// spvm_opcode_array.h
struct spvm_opcode_array;
typedef struct spvm_opcode_array SPVM_OPCODE_ARRAY;

// spvm_opcode.h
struct spvm_opcode;
typedef struct spvm_opcode SPVM_OPCODE;

// spvm_string_buffer.h
struct spvm_string_buffer;
typedef struct spvm_string_buffer SPVM_STRING_BUFFER;

// spvm_class_var_access.h
struct spvm_class_var_access;
typedef struct spvm_class_var_access SPVM_CLASS_VAR_ACCESS;

// spvm_class_var.h
struct spvm_class_var;
typedef struct spvm_class_var SPVM_CLASS_VAR;

// spvm_call_method.h
struct spvm_call_method;
typedef struct spvm_call_method SPVM_CALL_METHOD;

// spvm_object.h
struct spvm_object;
typedef struct spvm_object SPVM_OBJECT;

// spvm_block.h
struct spvm_block;
typedef struct spvm_block SPVM_BLOCK;

// spvm_use.h
struct spvm_use;
typedef struct spvm_use SPVM_USE;

// spvm_runtime.h
struct spvm_runtime;
typedef struct spvm_runtime SPVM_RUNTIME;

// spvm_compiler.h
struct spvm_compiler;
typedef struct spvm_compiler SPVM_COMPILER;

// spvm_switch.h
struct spvm_switch_info;
typedef struct spvm_switch_info SPVM_SWITCH_INFO;

// spvm_allocator.h
struct spvm_allocator;
typedef struct spvm_allocator SPVM_ALLOCATOR;

// spvm_dumper.h
struct spvm_dumper;
typedef struct spvm_dumper SPVM_DUMPER;

// spvm_assign.h
struct spvm_assign;
typedef struct spvm_assign SPVM_ASSIGN;

// spvm_class.h
struct spvm_class;
typedef struct spvm_class SPVM_CLASS;

// spvm_field_access.h
struct spvm_field_access;
typedef struct spvm_field_access SPVM_FIELD_ACCESS;

// spvm_type.h
struct spvm_type;
typedef struct spvm_type SPVM_TYPE;

// spvm_type_component_array.h
struct spvm_type_part;
typedef struct spvm_type_part SPVM_TYPE_PART;

// spvm_var.h
struct spvm_var;
typedef struct spvm_var SPVM_VAR;

// spvm_var_decl.h
struct spvm_var_decl;
typedef struct spvm_var_decl SPVM_VAR_DECL;

// spvm_constant.h
struct spvm_constant;
typedef struct spvm_constant SPVM_CONSTANT;

// spvm_op.h
struct spvm_op;
typedef struct spvm_op SPVM_OP;

// spvm_field.h
struct spvm_field;
typedef struct spvm_field SPVM_FIELD;

// spvm_descriptor.h
struct spvm_descriptor;
typedef struct spvm_descriptor SPVM_DESCRIPTOR;

// spvm_method.h
struct spvm_method;
typedef struct spvm_method SPVM_METHOD;

union spvm_yystype;
typedef union spvm_yystype SPVM_YYSTYPE;

#endif
