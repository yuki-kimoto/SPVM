// Copyright (c) 2023 Yuki Kimoto
// MIT License

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <assert.h>
#include <inttypes.h>
#include <ctype.h>
#include "spvm_compiler.h"
#include "spvm_list.h"
#include "spvm_hash.h"
#include "spvm_op.h"
#include "spvm_method.h"
#include "spvm_constant.h"
#include "spvm_field.h"
#include "spvm_var_decl.h"
#include "spvm_var.h"
#include "spvm_type.h"
#include "spvm_class.h"
#include "spvm_field_access.h"
#include "spvm_call_method.h"
#include "spvm_type.h"
#include "spvm_opcode_builder.h"
#include "spvm_ast_checker.h"
#include "spvm_switch_info.h"
#include "spvm_attribute.h"
#include "spvm_allocator.h"
#include "spvm_use.h"
#include "spvm_class_var.h"
#include "spvm_class_var_access.h"
#include "spvm_precompile.h"
#include "spvm_block.h"
#include "spvm_basic_type.h"
#include "spvm_case_info.h"
#include "spvm_array_field_access.h"
#include "spvm_string_buffer.h"
#include "spvm_allow.h"
#include "spvm_interface.h"
#include "spvm_constant_string.h"
#include "spvm_dumper.h"






















































const char* const* SPVM_OP_C_ID_NAMES(void) {

  static const char* const id_names[] = {
    "GRAMMAR",
    "LIST",
    "PUSHMARK",
    "DO_NOTHING",
    "NAME",
    "ATTRIBUTE",
    "CURRENT_CLASS",
    "CLASS",
    "EXTENDS",
    "CLASS_BLOCK",
    "END_OF_FILE",
    "IF",
    "UNLESS",
    "ELSIF",
    "ELSE",
    "CONDITION",
    "CONDITION_NOT",
    "SWITCH",
    "CASE",
    "DEFAULT",
    "SWITCH_CONDITION",
    "BREAK",
    "FOR",
    "WHILE",
    "LOOP",
    "LOOP_INCREMENT",
    "LAST",
    "NEXT",
    "MY",
    "FIELD",
    "METHOD",
    "ENUM",
    "ENUMERATION_VALUE",
    "ENUM_BLOCK",
    "BLOCK",
    "EVAL",
    "TYPE",
    "MUTABLE",
    "VOID",
    "BYTE",
    "SHORT",
    "INT",
    "LONG",
    "FLOAT",
    "DOUBLE",
    "STRING",
    "OBJECT",
    "DOT3",
    "OF",
    "USE",
    "AS",
    "ALIAS",
    "REQUIRE",
    "IF_REQUIRE",
    "INIT",
    "INTERFACE",
    "RETURN",
    "CONSTANT",
    "INC",
    "DEC",
    "PRE_INC",
    "POST_INC",
    "PRE_DEC",
    "POST_DEC",
    "MINUS",
    "PLUS",
    "ADD",
    "SUBTRACT",
    "MULTIPLY",
    "DIVIDE",
    "BIT_AND",
    "BIT_OR",
    "BIT_XOR",
    "BIT_NOT",
    "REMAINDER",
    "LEFT_SHIFT",
    "RIGHT_ARITHMETIC_SHIFT",
    "RIGHT_LOGICAL_SHIFT",
    "LOGICAL_AND",
    "LOGICAL_OR",
    "LOGICAL_NOT",
    "ARRAY_ACCESS",
    "ASSIGN",
    "CALL_METHOD",
    "FIELD_ACCESS",
    "VAR",
    "TYPE_CAST",
    "UNDEF",
    "ARRAY_LENGTH",
    "DIE",
    "EXCEPTION_VAR",
    "NEW",
    "WEAKEN",
    "WEAKEN_FIELD",
    "UNWEAKEN",
    "UNWEAKEN_FIELD",
    "ISWEAK",
    "ISWEAK_FIELD",
    "SPECIAL_ASSIGN",
    "CONCAT",
    "CLASS_VAR",
    "CLASS_VAR_ACCESS",
    "ARRAY_INIT",
    "BOOL",
    "CHECK_CONVERT",
    "NUMERIC_EQ",
    "NUMERIC_NE",
    "NUMERIC_LT",
    "NUMERIC_LE",
    "NUMERIC_GT",
    "NUMERIC_GE",
    "NUMERIC_CMP",
    "STRING_EQ",
    "STRING_NE",
    "STRING_GT",
    "STRING_GE",
    "STRING_LT",
    "STRING_LE",
    "STRING_CMP",
    "ISA",
    "IS_TYPE",
    "IS_COMPILE_TYPE",
    "SEQUENCE",
    "SCALAR",
    "ARRAY_FIELD_ACCESS",
    "REFERENCE",
    "DEREF",
    "STRING_LENGTH",
    "CURRENT_CLASS_NAME",
    "REFCNT",
    "ALLOW",
    "WARN",
    "PRINT",
    "SAY",
    "TYPE_NAME",
    "COMPILE_TYPE_NAME",
    "DUMP",
    "TRUE",
    "FALSE",
    "DIVIDE_UNSIGNED_INT",
    "DIVIDE_UNSIGNED_LONG",
    "REMAINDER_UNSIGNED_INT",
    "REMAINDER_UNSIGNED_LONG",
    "NEW_STRING_LEN",
    "IS_READ_ONLY",
    "MAKE_READ_ONLY",
    "COPY",
    "CAN",
    "CLASS_ID",
    "ERROR_CODE",
    "SET_ERROR_CODE",
    "ERROR",
    "ITEMS",
    "VERSION",
    "CUT",
  };
  
  return id_names;
}

SPVM_OP* SPVM_OP_build_class(SPVM_COMPILER* compiler, SPVM_OP* op_class, SPVM_OP* op_type, SPVM_OP* op_block, SPVM_OP* op_list_attributes, SPVM_OP* op_extends) {
  
  // Class
  SPVM_CLASS* class = SPVM_CLASS_new(compiler);
  
  // Set class
  op_class->uv.class = class;
  
  class->op_class = op_class;
  class->op_extends = op_extends;
  
  class->class_path = compiler->cur_class_path;
  class->class_rel_file = compiler->cur_rel_file;
  class->class_file = compiler->cur_file;
  
  if (op_extends) {
    SPVM_OP* op_name_parent_class = op_extends->first;
    class->parent_class_name = op_name_parent_class->uv.name;
    // add use stack
    SPVM_OP* op_use = SPVM_OP_new_op_use(compiler, op_name_parent_class->file, op_name_parent_class->line);
    SPVM_OP* op_name_class_alias = NULL;
    int32_t is_require = 0;
    SPVM_OP_build_use(compiler, op_use, op_name_parent_class, op_name_class_alias, is_require);
  }
  
  if (class->class_path) {
    SPVM_CONSTANT_STRING_new(compiler, class->class_path, strlen(class->class_path));
  }
  SPVM_CONSTANT_STRING_new(compiler, class->class_rel_file, strlen(class->class_rel_file));
  SPVM_CONSTANT_STRING_new(compiler, class->class_file, strlen(class->class_file));
  
  if (!op_type) {
    // Class is anon
    class->is_anon = 1;
    
    SPVM_OP* op_method = op_block->first->last;
    assert(op_method);
    assert(op_method->id == SPVM_OP_C_ID_METHOD);

    // int32_t max length is 10(2147483647)
    int32_t int32_max_length = 10;
    
    // Create anon method class name
    // If Foo::Bar anon method is defined line 123, method keyword start pos 32, the anon method class name become Foo::Bar::anon::123::32. This is uniqe in whole program.
    const char* anon_method_defined_rel_file_class_name = compiler->cur_rel_file_class_name;
    int32_t anon_method_defined_line = op_method->line;
    int32_t anon_method_defined_column = op_method->column;
    int32_t anon_method_class_name_length = 6 + strlen(anon_method_defined_rel_file_class_name) + 2 + int32_max_length + 2 + int32_max_length;
    
    // Anon class name
    char* name_class_tmp = SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->allocator, anon_method_class_name_length + 1);
    sprintf(name_class_tmp, "%s::anon::%d::%d", anon_method_defined_rel_file_class_name, anon_method_defined_line, anon_method_defined_column);

    SPVM_CONSTANT_STRING* name_class_string = SPVM_CONSTANT_STRING_new(compiler, name_class_tmp, strlen(name_class_tmp));
    const char* name_class = name_class_string->value;

    SPVM_OP* op_name_class = SPVM_OP_new_op_name(compiler, name_class, op_class->file, op_class->line);
    op_type = SPVM_OP_build_basic_type(compiler, op_name_class);
    
    op_method->uv.method->anon_method_defined_class_name = anon_method_defined_rel_file_class_name;
  }
  
  const char* class_name = op_type->uv.type->basic_type->name;
  class->type = op_type->uv.type;

  if (!class->is_anon) {
    assert(!islower(class_name[0]));
    
    // If class name is different from the class name corresponding to the class file, compile error occur.
    if (strcmp(class_name, compiler->cur_rel_file_class_name) != 0) {
      // If class fail load by if (require xxx) syntax, that is ok
      const char* not_found_class_class_name = SPVM_HASH_get(compiler->not_found_class_class_symtable, class_name, strlen(class_name));
      if (!not_found_class_class_name) {
        SPVM_COMPILER_error(compiler, "The class name \"%s\" must be \"%s\".\n  at %s line %d", class_name, compiler->cur_rel_file_class_name, op_class->file, op_class->line);
        return op_class;
      }
    }
  }
  
  SPVM_HASH* class_symtable = compiler->class_symtable;
  
  // Assert
  SPVM_CLASS* found_class = SPVM_HASH_get(class_symtable, class_name, strlen(class_name));
  if (found_class) { assert(0); }

  // Add class
  SPVM_LIST_push(compiler->classes, class);
  SPVM_HASH_set(compiler->class_symtable, class_name, strlen(class_name), class);
  
  SPVM_OP* op_name_class = SPVM_OP_new_op_name(compiler, op_type->uv.type->basic_type->name, op_type->file, op_type->line);
  class->op_name = op_name_class;
  
  class->name = op_name_class->uv.name;

  // Class attributes
  int32_t class_attributes_count = 0;
  int32_t access_control_attributes_count = 0;
  if (op_list_attributes) {
    SPVM_OP* op_attribute = op_list_attributes->first;
    while ((op_attribute = SPVM_OP_sibling(compiler, op_attribute))) {
      SPVM_ATTRIBUTE* attribute = op_attribute->uv.attribute;
      switch (attribute->id) {
        case SPVM_ATTRIBUTE_C_ID_POINTER: {
          class->category = SPVM_CLASS_C_CATEGORY_CLASS;
          class->is_pointer = 1;
          class_attributes_count++;
          break;
        }
        case SPVM_ATTRIBUTE_C_ID_MULNUM_T: {
          class->category = SPVM_CLASS_C_CATEGORY_MULNUM;
          class_attributes_count++;
          break;
        }
        case SPVM_ATTRIBUTE_C_ID_PRIVATE: {
          class->access_control_type = SPVM_ATTRIBUTE_C_ID_PRIVATE;
          access_control_attributes_count++;
          break;
        }
        case SPVM_ATTRIBUTE_C_ID_PROTECTED: {
          class->access_control_type = SPVM_ATTRIBUTE_C_ID_PROTECTED;
          access_control_attributes_count++;
          break;
        }
        case SPVM_ATTRIBUTE_C_ID_PUBLIC: {
          class->access_control_type = SPVM_ATTRIBUTE_C_ID_PUBLIC;
          access_control_attributes_count++;
          break;
        }
        case SPVM_ATTRIBUTE_C_ID_PRECOMPILE: {
          class->is_precompile = 1;
          break;
        }
        case SPVM_ATTRIBUTE_C_ID_INTERFACE_T: {
          class->category = SPVM_CLASS_C_CATEGORY_INTERFACE;
          class_attributes_count++;
          break;
        }
        default: {
          SPVM_COMPILER_error(compiler, "Invalid class attribute \"%s\".\n  at %s line %d", SPVM_ATTRIBUTE_get_name(compiler, attribute->id), op_class->file, op_class->line);
        }
      }
    }
    if (class_attributes_count > 1) {
      SPVM_COMPILER_error(compiler, "Only one of class attributes \"mulnum_t\", \"pointer\" or \"interface_t\" can be specified.\n  at %s line %d", op_list_attributes->file, op_list_attributes->line);
    }
    if (access_control_attributes_count > 1) {
      SPVM_COMPILER_error(compiler, "Only one of class attributes \"private\", \"protected\" or \"public\" can be specified.\n  at %s line %d", op_list_attributes->file, op_list_attributes->line);
    }
  }
  
  // The default of the access controll is private
  if (class->access_control_type == SPVM_ATTRIBUTE_C_ID_UNKNOWN) {
    class->access_control_type = SPVM_ATTRIBUTE_C_ID_PRIVATE;
  }
  
  // Declarations
  if (op_block) {
    SPVM_OP* op_decls = op_block->first;
    SPVM_OP* op_decl = op_decls->first;
    while ((op_decl = SPVM_OP_sibling(compiler, op_decl))) {
      // version declaration
      if (op_decl->id == SPVM_OP_C_ID_VERSION_DECL) {
        if (class->version_string) {
          SPVM_COMPILER_error(compiler, "The version has already been declared.\n  at %s line %d", op_decl->file, op_decl->line);
          break;
        }
        
        SPVM_OP* op_version_string = op_decl->first;
        SPVM_CONSTANT* version_string_constant = op_version_string->uv.constant;
        const char* version_string = version_string_constant->value.oval;
        int32_t version_string_length = version_string_constant->string_length;
        
        // Version string validation
        {
          int32_t dot_count = 0;
          int32_t digits_after_dot = 0;
          int32_t invalid_char = 0;
          for (int32_t version_string_index = 0; version_string_index < version_string_length; version_string_index++) {
            char ch = version_string[version_string_index];
            
            if (!(ch == '.' || isdigit(ch) || ch == '_')) {
              invalid_char = 1;
              break;
            }
            
            if (ch == '.') {
              dot_count++;
            }
            
            if (dot_count > 0 && isdigit(ch)) {
              digits_after_dot++;
            }
          }
          
          if (invalid_char) {
            SPVM_COMPILER_error(compiler, "A character in a version string must be a number or \".\" or \"_\".\n  at %s line %d", op_decl->file, op_decl->line);
            break;
          }
          
          if (!isdigit(version_string[0])) {
            SPVM_COMPILER_error(compiler, "A version string must begin with a number.\n  at %s line %d", op_decl->file, op_decl->line);
            break;
          }
          
          if (!isdigit(version_string[version_string_length - 1])) {
            SPVM_COMPILER_error(compiler, "A version string must end with a number.\n  at %s line %d", op_decl->file, op_decl->line);
            break;
          }
          
          if (!(dot_count <= 1)) {
            SPVM_COMPILER_error(compiler, "The number of \".\" in a version string must be less than or equal to 1.\n  at %s line %d", op_decl->file, op_decl->line);
            break;
          }
          
          if (!(digits_after_dot % 3 == 0)) {
            SPVM_COMPILER_error(compiler, "The length of characters after \".\" in a version string must be divisible by 3.\n  at %s line %d", op_decl->file, op_decl->line);
            break;
          }
        }
        
        SPVM_CONSTANT_STRING_new(compiler, version_string, version_string_length);
        class->version_string = version_string;
      }
      // use statement
      else if (op_decl->id == SPVM_OP_C_ID_USE) {
        SPVM_OP* op_use = op_decl;
        
        SPVM_LIST_push(class->use_class_names, (void*)op_use->uv.use->class_name);
        
        // Class alias
        const char* class_alias_name = op_use->uv.use->class_alias_name;
        if (class_alias_name) {
    
          // Class name must begin with upper case, otherwise compiler error occur.
          // (Invalid example) Foo::bar
          if (islower(class_alias_name[0])) {
            SPVM_COMPILER_error(compiler, "The class alias name \"%s\" must begin with an upper case character.\n  at %s line %d", class_alias_name, op_decl->file, op_decl->line);
          }
          else {
            const char* use_class_name = op_use->uv.use->class_name;
            const char* use_class_name_exists = SPVM_HASH_get(class->class_alias_symtable, class_alias_name, strlen(class_alias_name));
            if (use_class_name_exists) {
              SPVM_COMPILER_error(compiler, "The class alias name \"%s\" is already used.\n  at %s line %d", class_alias_name, op_decl->file, op_decl->line);
            }
            else {
              SPVM_HASH_set(class->class_alias_symtable, class_alias_name, strlen(class_alias_name), (void*)use_class_name);
            }
          }
        }
      }
      // allow statement
      else if (op_decl->id == SPVM_OP_C_ID_ALLOW) {
        SPVM_LIST_push(class->allows, op_decl->uv.allow);
      }
      // interface statement
      else if (op_decl->id == SPVM_OP_C_ID_INTERFACE) {
        if (class->category == SPVM_CLASS_C_CATEGORY_MULNUM) {
          SPVM_COMPILER_error(compiler, "The interface statement cannnot be used in the definition of the multi-numeric type.\n  at %s line %d", op_decl->file, op_decl->line);
        }
        const char* interface_name = op_decl->uv.interface->class_name;
        
        if (strcmp(class->name, interface_name) == 0) {
          SPVM_COMPILER_error(compiler, "The interface name specified by the interface statement must be different from the name of the current interface.\n  at %s line %d", op_decl->file, op_decl->line);
        }
        
        SPVM_LIST_push(class->interface_decls, op_decl->uv.interface);
      }
      // Class var declarations
      else if (op_decl->id == SPVM_OP_C_ID_CLASS_VAR) {
        SPVM_CLASS_VAR* class_var = op_decl->uv.class_var;

        if (class->category == SPVM_CLASS_C_CATEGORY_INTERFACE) {
          SPVM_COMPILER_error(compiler, "The interface cannnot have class variables.\n  at %s line %d", op_decl->file, op_decl->line);
        }
        SPVM_LIST_push(class->class_vars, op_decl->uv.class_var);

        // Getter
        if (class_var->has_getter) {
          // static method FOO : TYPE () {
          //   return $FOO;
          // }

          SPVM_OP* op_method = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_METHOD, op_decl->file, op_decl->line);
          SPVM_CONSTANT_STRING* method_name_string = SPVM_CONSTANT_STRING_new(compiler, class_var->name + 1, strlen(class_var->name) - 1);
          const char* method_name = method_name_string->value;
          SPVM_OP* op_name_method = SPVM_OP_new_op_name(compiler, method_name, op_decl->file, op_decl->line);

          // If the type of the class_var is byte or short, the return type becomes int
          SPVM_TYPE* class_var_type = class_var->type;
          SPVM_TYPE* return_type;
          if (SPVM_TYPE_is_byte_type(compiler, class_var_type->basic_type->id, class_var_type->dimension, class_var_type->flag)
            || SPVM_TYPE_is_short_type(compiler, class_var_type->basic_type->id, class_var_type->dimension, class_var_type->flag))
          {
            return_type = SPVM_TYPE_new_int_type(compiler);
          }
          else {
            return_type = class_var->type;
          }
          SPVM_OP* op_return_type = SPVM_OP_new_op_type(compiler, return_type, op_decl->file, op_decl->line);

          SPVM_OP* op_args = SPVM_OP_new_op_list(compiler, op_decl->file, op_decl->line);
          
          SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, op_decl->file, op_decl->line);
          SPVM_OP* op_statements = SPVM_OP_new_op_list(compiler, op_decl->file, op_decl->line);
          SPVM_OP* op_return = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_RETURN, op_decl->file, op_decl->line);

          SPVM_OP* op_name_class_var_access = SPVM_OP_new_op_name(compiler, class_var->name, op_decl->file, op_decl->line);
          SPVM_OP* op_class_var_access = SPVM_OP_new_op_class_var_access(compiler, op_name_class_var_access);
          
          SPVM_OP_insert_child(compiler, op_return, op_return->last, op_class_var_access);
          SPVM_OP_insert_child(compiler, op_statements, op_statements->last, op_return);
          SPVM_OP_insert_child(compiler, op_block, op_block->last, op_statements);

          SPVM_OP* op_list_attributes = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
          SPVM_OP* op_attribute_static = SPVM_OP_new_op_attribute(compiler, SPVM_ATTRIBUTE_C_ID_STATIC, compiler->cur_file, compiler->cur_line);
          SPVM_OP_insert_child(compiler, op_list_attributes, op_list_attributes->first, op_attribute_static);
          
          SPVM_OP_build_method_definition(compiler, op_method, op_name_method, op_return_type, op_args, op_list_attributes, op_block, NULL, NULL, 0, 0);

          op_method->uv.method->is_class_var_getter = 1;
          op_method->uv.method->field_method_original_name = class_var->name;
          op_method->uv.method->field_method_original_type = class_var->type;
         
          SPVM_LIST_push(class->methods, op_method->uv.method);
        }

        // Setter
        if (class_var->has_setter) {
          
          // method SET_FOO : void ($foo : TYPE) {
          //   $FOO = $foo;
          // }
          
          SPVM_OP* op_method = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_METHOD, op_decl->file, op_decl->line);
          char* method_name_tmp = SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->allocator, 4 + strlen(class_var->name) - 1 + 1);
          memcpy(method_name_tmp, "SET_", 4);
          memcpy(method_name_tmp + 4, class_var->name + 1, strlen(class_var->name) - 1);

          SPVM_CONSTANT_STRING* method_name_string = SPVM_CONSTANT_STRING_new(compiler, method_name_tmp, strlen(method_name_tmp));
          const char* method_name = method_name_string->value;

          SPVM_OP* op_name_method = SPVM_OP_new_op_name(compiler, method_name, op_decl->file, op_decl->line);
          SPVM_OP* op_return_type = SPVM_OP_new_op_void_type(compiler, op_decl->file, op_decl->line);
          SPVM_OP* op_args = SPVM_OP_new_op_list(compiler, op_decl->file, op_decl->line);

          // If the type of the class_var is byte or short, the arg type becomes int
          SPVM_TYPE* class_var_type = class_var->type;
          SPVM_TYPE* arg_type;
          if (SPVM_TYPE_is_byte_type(compiler, class_var_type->basic_type->id, class_var_type->dimension, class_var_type->flag)
            || SPVM_TYPE_is_short_type(compiler, class_var_type->basic_type->id, class_var_type->dimension, class_var_type->flag))
          {
            arg_type = SPVM_TYPE_new_int_type(compiler);
          }
          else {
            arg_type = class_var->type;
          }
          SPVM_OP* op_type_value = SPVM_OP_new_op_type(compiler, arg_type, op_decl->file, op_decl->line);

          SPVM_OP* op_var_value_name = SPVM_OP_new_op_name(compiler, class_var->name, op_decl->file, op_decl->line);
          SPVM_OP* op_var_value = SPVM_OP_new_op_var(compiler, op_var_value_name);
          SPVM_OP* op_arg_value = SPVM_OP_build_arg(compiler, op_var_value, op_type_value, NULL, NULL);

          SPVM_OP_insert_child(compiler, op_args, op_args->last, op_arg_value);
          
          SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, op_decl->file, op_decl->line);
          SPVM_OP* op_statements = SPVM_OP_new_op_list(compiler, op_decl->file, op_decl->line);

          SPVM_OP* op_name_class_var_access = SPVM_OP_new_op_name(compiler, class_var->name, op_decl->file, op_decl->line);
          SPVM_OP* op_class_var_access = SPVM_OP_new_op_class_var_access(compiler, op_name_class_var_access);

          SPVM_OP* op_var_assign_value_name = SPVM_OP_new_op_name(compiler, class_var->name, op_decl->file, op_decl->line);
          SPVM_OP* op_var_assign_value = SPVM_OP_new_op_var(compiler, op_var_assign_value_name);

          SPVM_OP* op_type_cast = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE_CAST, op_decl->file, op_decl->line);
          SPVM_OP* op_type_for_cast = SPVM_OP_new_op_type(compiler, class_var_type, op_decl->file, op_decl->line);
          SPVM_OP_build_type_cast(compiler, op_type_cast, op_type_for_cast, op_var_assign_value, NULL);

          SPVM_OP* op_assign = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ASSIGN, op_decl->file, op_decl->line);
          SPVM_OP_build_assign(compiler, op_assign, op_class_var_access, op_type_cast);
          
          SPVM_OP_insert_child(compiler, op_statements, op_statements->last, op_assign);
          SPVM_OP_insert_child(compiler, op_block, op_block->last, op_statements);

          SPVM_OP* op_list_attributes = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
          SPVM_OP* op_attribute_static = SPVM_OP_new_op_attribute(compiler, SPVM_ATTRIBUTE_C_ID_STATIC, compiler->cur_file, compiler->cur_line);
          SPVM_OP_insert_child(compiler, op_list_attributes, op_list_attributes->first, op_attribute_static);
          
          SPVM_OP_build_method_definition(compiler, op_method, op_name_method, op_return_type, op_args, op_list_attributes, op_block, NULL, NULL, 0, 0);
          
          op_method->uv.method->is_class_var_setter = 1;
          op_method->uv.method->field_method_original_name = class_var->name;
          op_method->uv.method->field_method_original_type = class_var->type;
          
          SPVM_LIST_push(class->methods, op_method->uv.method);
        }
      }
      // Field declarations
      else if (op_decl->id == SPVM_OP_C_ID_FIELD) {
        SPVM_FIELD* field = op_decl->uv.field;
        
        if (class->category == SPVM_CLASS_C_CATEGORY_INTERFACE) {
          SPVM_COMPILER_error(compiler, "The interface cannnot have fields.\n  at %s line %d", op_decl->file, op_decl->line);
        }
        SPVM_LIST_push(class->fields, field);
        
        // Getter
        if (field->has_getter) {
          // method foo : TYPE () {
          //   return $self->{foo};
          // }
          
          SPVM_OP* op_method = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_METHOD, op_decl->file, op_decl->line);
          SPVM_OP* op_name_method = SPVM_OP_new_op_name(compiler, field->name, op_decl->file, op_decl->line);

          // If the type of the field is byte or short, the return type becomes int
          SPVM_TYPE* field_type = field->type;
          SPVM_TYPE* return_type;
          if (SPVM_TYPE_is_byte_type(compiler, field_type->basic_type->id, field_type->dimension, field_type->flag)
            || SPVM_TYPE_is_short_type(compiler, field_type->basic_type->id, field_type->dimension, field_type->flag))
          {
            return_type = SPVM_TYPE_new_int_type(compiler);
          }
          else {
            return_type = field->type;
          }
          SPVM_OP* op_return_type = SPVM_OP_new_op_type(compiler, return_type, op_decl->file, op_decl->line);

          SPVM_OP* op_args = SPVM_OP_new_op_list(compiler, op_decl->file, op_decl->line);
          
          SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, op_decl->file, op_decl->line);
          SPVM_OP* op_statements = SPVM_OP_new_op_list(compiler, op_decl->file, op_decl->line);
          SPVM_OP* op_return = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_RETURN, op_decl->file, op_decl->line);

          SPVM_OP* op_var_name_invocant = SPVM_OP_new_op_name(compiler, "$self", op_decl->file, op_decl->line);
          SPVM_OP* op_var_self_invocant = SPVM_OP_new_op_var(compiler, op_var_name_invocant);
          SPVM_OP* op_name_field_access = SPVM_OP_new_op_name(compiler, field->name, op_decl->file, op_decl->line);
          
          SPVM_OP* op_field_access = SPVM_OP_new_op_field_access(compiler, op_decl->file, op_decl->line);

          SPVM_OP_build_field_access(compiler, op_field_access, op_var_self_invocant, op_name_field_access);
          
          SPVM_OP_insert_child(compiler, op_return, op_return->last, op_field_access);
          SPVM_OP_insert_child(compiler, op_statements, op_statements->last, op_return);
          SPVM_OP_insert_child(compiler, op_block, op_block->last, op_statements);
          
          SPVM_OP_build_method_definition(compiler, op_method, op_name_method, op_return_type, op_args, NULL, op_block, NULL, NULL, 0, 0);
          
          op_method->uv.method->is_field_getter = 1;
          op_method->uv.method->field_method_original_name = field->name;
          op_method->uv.method->field_method_original_type = field->type;
          
          SPVM_LIST_push(class->methods, op_method->uv.method);
        }

        // Setter
        if (field->has_setter) {
          // method set_foo : void ($foo : TYPE) {
          //   $self->{foo} = $foo;
          // }

          SPVM_OP* op_method = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_METHOD, op_decl->file, op_decl->line);
          char* method_name_tmp = SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->allocator, 4 + strlen(field->name) + 1);
          memcpy(method_name_tmp, "set_", 4);
          memcpy(method_name_tmp + 4, field->name, strlen(field->name));
          SPVM_CONSTANT_STRING* method_name_string = SPVM_CONSTANT_STRING_new(compiler, method_name_tmp, strlen(method_name_tmp));
          const char* method_name = method_name_string->value;
          SPVM_OP* op_name_method = SPVM_OP_new_op_name(compiler, method_name, op_decl->file, op_decl->line);
          SPVM_OP* op_return_type = SPVM_OP_new_op_void_type(compiler, op_decl->file, op_decl->line);
          SPVM_OP* op_args = SPVM_OP_new_op_list(compiler, op_decl->file, op_decl->line);

          // If the type of the field is byte or short, the arg type becomes int
          SPVM_TYPE* field_type = field->type;
          SPVM_TYPE* arg_type;
          if (SPVM_TYPE_is_byte_type(compiler, field_type->basic_type->id, field_type->dimension, field_type->flag)
            || SPVM_TYPE_is_short_type(compiler, field_type->basic_type->id, field_type->dimension, field_type->flag))
          {
            arg_type = SPVM_TYPE_new_int_type(compiler);
          }
          else {
            arg_type = field->type;
          }
          SPVM_OP* op_type_value = SPVM_OP_new_op_type(compiler, arg_type, op_decl->file, op_decl->line);

          SPVM_OP* op_var_value_name = SPVM_OP_new_op_name(compiler, field->name, op_decl->file, op_decl->line);
          SPVM_OP* op_var_value = SPVM_OP_new_op_var(compiler, op_var_value_name);
          SPVM_OP* op_arg_value = SPVM_OP_build_arg(compiler, op_var_value, op_type_value, NULL, NULL);

          SPVM_OP_insert_child(compiler, op_args, op_args->last, op_arg_value);
          
          SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, op_decl->file, op_decl->line);
          SPVM_OP* op_statements = SPVM_OP_new_op_list(compiler, op_decl->file, op_decl->line);

          SPVM_OP* op_var_name_invocant = SPVM_OP_new_op_name(compiler, "$self", op_decl->file, op_decl->line);
          SPVM_OP* op_var_self_invocant = SPVM_OP_new_op_var(compiler, op_var_name_invocant);
          SPVM_OP* op_name_field_access = SPVM_OP_new_op_name(compiler, field->name, op_decl->file, op_decl->line);
          SPVM_OP* op_field_access = SPVM_OP_new_op_field_access(compiler, op_decl->file, op_decl->line);
          SPVM_OP_build_field_access(compiler, op_field_access, op_var_self_invocant, op_name_field_access);

          SPVM_OP* op_var_assign_value_name = SPVM_OP_new_op_name(compiler, field->name, op_decl->file, op_decl->line);
          SPVM_OP* op_var_assign_value = SPVM_OP_new_op_var(compiler, op_var_assign_value_name);
          
          SPVM_OP* op_type_cast = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE_CAST, op_decl->file, op_decl->line);
          SPVM_OP* op_type_for_cast = SPVM_OP_new_op_type(compiler, field_type, op_decl->file, op_decl->line);
          SPVM_OP_build_type_cast(compiler, op_type_cast, op_type_for_cast, op_var_assign_value, NULL);

          SPVM_OP* op_assign = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ASSIGN, op_decl->file, op_decl->line);
          SPVM_OP_build_assign(compiler, op_assign, op_field_access, op_type_cast);
          
          SPVM_OP_insert_child(compiler, op_statements, op_statements->last, op_assign);
          SPVM_OP_insert_child(compiler, op_block, op_block->last, op_statements);
          
          SPVM_OP_build_method_definition(compiler, op_method, op_name_method, op_return_type, op_args, NULL, op_block, NULL, NULL, 0, 0);
          
          op_method->uv.method->is_field_setter = 1;
          op_method->uv.method->field_method_original_name = field->name;
          op_method->uv.method->field_method_original_type = field->type;
          
          SPVM_LIST_push(class->methods, op_method->uv.method);
        }
      }
      // Enum declarations
      else if (op_decl->id == SPVM_OP_C_ID_ENUM) {
        SPVM_OP* op_enum_block = op_decl->first;
        SPVM_OP* op_enumeration_values = op_enum_block->first;
        SPVM_OP* op_method = op_enumeration_values->first;
        while ((op_method = SPVM_OP_sibling(compiler, op_method))) {
          SPVM_LIST_push(class->methods, op_method->uv.method);
        }
      }
      // Method declarations
      else if (op_decl->id == SPVM_OP_C_ID_METHOD) {
        SPVM_LIST_push(class->methods, op_decl->uv.method);
        
        // Captures is added to field
        SPVM_LIST* captures = op_decl->uv.method->captures;
        for (int32_t i = 0; i < captures->length; i++) {
          SPVM_VAR_DECL* capture_var_decl = SPVM_LIST_get(captures, i);
          
          SPVM_OP* op_field = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_FIELD, capture_var_decl->op_var_decl->file, capture_var_decl->op_var_decl->line);
          SPVM_CONSTANT_STRING* field_name_string = SPVM_CONSTANT_STRING_new(compiler, capture_var_decl->var->name + 1, strlen(capture_var_decl->var->name) - 1);
          
          SPVM_OP* op_name_field = SPVM_OP_new_op_name(compiler, field_name_string->value, capture_var_decl->op_var_decl->file, capture_var_decl->op_var_decl->line);
          
          SPVM_TYPE* type_new_capture_var_decl = SPVM_TYPE_new(compiler, capture_var_decl->type->basic_type->id, capture_var_decl->type->dimension, capture_var_decl->type->flag);
          SPVM_OP* op_type_new_capture_var_decl = SPVM_OP_new_op_type(compiler, type_new_capture_var_decl, capture_var_decl->op_var_decl->file, capture_var_decl->op_var_decl->line);
          SPVM_OP_build_field_definition(compiler, op_field, op_name_field, NULL, op_type_new_capture_var_decl);
          SPVM_LIST_push(class->fields, op_field->uv.field);
          op_field->uv.field->is_captured = 1;
        }
        
        // Begin block
        if (op_decl->uv.method->is_init) {
          class->has_init_block = 1;
        }
      }
      else {
        assert(0);
      }
    }
  }
  
  // Field declarations
  for (int32_t i = 0; i < class->fields->length; i++) {
    SPVM_FIELD* field = SPVM_LIST_get(class->fields, i);

    // The default of the access controll of the field is private.
    if (field->access_control_type == SPVM_ATTRIBUTE_C_ID_UNKNOWN) {
      // If anon method, field is public
      if (class->is_anon) {
        field->access_control_type = SPVM_ATTRIBUTE_C_ID_PUBLIC;
      }
      // If multi-numeric type, field is public
      else if (class->category == SPVM_CLASS_C_CATEGORY_MULNUM) {
        field->access_control_type = SPVM_ATTRIBUTE_C_ID_PUBLIC;
      }
      // Default is private
      else {
        field->access_control_type = SPVM_ATTRIBUTE_C_ID_PRIVATE;
      }
    }

    field->index = i;
    const char* field_name = field->op_name->uv.name;

    SPVM_FIELD* found_field = SPVM_HASH_get(class->field_symtable, field_name, strlen(field_name));
    
    if (found_field) {
      SPVM_COMPILER_error(compiler, "Redeclaration of the \"%s\" field in the \"%s\" class.\n  at %s line %d", field_name, class_name, field->op_field->file, field->op_field->line);
    }
    else {
      SPVM_HASH_set(class->field_symtable, field_name, strlen(field_name), field);
      
      // Add op class
      field->class = class;
    }
  }

  // Class variable declarations
  for (int32_t i = 0; i < class->class_vars->length; i++) {
    SPVM_CLASS_VAR* class_var = SPVM_LIST_get(class->class_vars, i);
    const char* class_var_name = class_var->name;

    SPVM_CLASS_VAR* found_class_var = SPVM_HASH_get(class->class_var_symtable, class_var_name, strlen(class_var_name));
    
    if (found_class_var) {
      SPVM_COMPILER_error(compiler, "Redeclaration of the class variable \"$%s\" in the \"%s\" class.\n  at %s line %d", class_var_name + 1, class_name, class_var->op_class_var->file, class_var->op_class_var->line);
    }
    else {
      SPVM_HASH_set(class->class_var_symtable, class_var_name, strlen(class_var_name), class_var);
      
      // Add op class
      class_var->class = class;
    }
  }
  
  // INIT block
  {
    // Check INIT block existance
    int32_t has_init_block = 0;
    for (int32_t i = 0; i < class->methods->length; i++) {
      SPVM_METHOD* method = SPVM_LIST_get(class->methods, i);
      if (method->is_init) {
        has_init_block = 1;
        break;
      }
    }
    
    // Add an default INIT block
    if (class->category == SPVM_CLASS_C_CATEGORY_CLASS && !has_init_block) {
      SPVM_OP* op_init = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_INIT, op_class->file, op_class->line);
      
      // Statements
      SPVM_OP* op_list_statements = SPVM_OP_new_op_list(compiler, op_class->file, op_class->line);
      
      // Block
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, op_class->file, op_class->line);
      SPVM_OP_insert_child(compiler, op_block, op_block->last, op_list_statements);
      
      SPVM_OP* op_method = SPVM_OP_build_init_block(compiler, op_init, op_block);
      
      SPVM_LIST_push(class->methods, op_method->uv.method);
    }
  }
  
  // Method declarations
  for (int32_t i = 0; i < class->methods->length; i++) {
    SPVM_METHOD* method = SPVM_LIST_get(class->methods, i);
    
    SPVM_OP* op_name_method = method->op_name;
    const char* method_name = op_name_method->uv.name;
    
    int32_t must_have_block;
    if (class->category == SPVM_CLASS_C_CATEGORY_INTERFACE) {
      must_have_block = 0;
    }
    else {
      if (method->is_native) {
        must_have_block = 0;
      }
      else {
        must_have_block = 1;
      }
    }
    
    if (must_have_block && !method->op_block) {
      SPVM_COMPILER_error(compiler, "The non-native method must have the block.\n  at %s line %d", op_name_method->file, op_name_method->line);
    }
    
    // Method check
    
    // Set first argument type if not set
    if (method->args_length > 0) {
      SPVM_VAR_DECL* arg_var_decl_first = SPVM_LIST_get(method->var_decls, 0);
      SPVM_OP* op_arg_first_type = NULL;
      if (!method->is_class_method) {
        SPVM_TYPE* arg_invocant_type = op_type->uv.type;
        op_arg_first_type = SPVM_OP_new_op_type(compiler, arg_invocant_type, method->op_method->file, method->op_method->line);
        arg_var_decl_first->type = op_arg_first_type->uv.type;
        assert(arg_invocant_type->basic_type);
      }
      else {
        SPVM_OP* op_type_new_arg_var_decl_first = SPVM_OP_new_op_type(compiler, arg_var_decl_first->type, arg_var_decl_first->op_var_decl->file, arg_var_decl_first->op_var_decl->line);
        op_arg_first_type = op_type_new_arg_var_decl_first;
        assert(op_arg_first_type->uv.type->basic_type);
      }
    }

    // If Method is anon, method must be method
    if (strlen(method_name) == 0 && method->is_class_method) {
      SPVM_COMPILER_error(compiler, "The anon method must be an instance method.\n  at %s line %d", method->op_method->file, method->op_method->line);
    }

    if (class->category == SPVM_CLASS_C_CATEGORY_INTERFACE) {
      // Method having interface_t attribute must be method
      if (method->is_class_method) {
        SPVM_COMPILER_error(compiler, "The method defined in the interface must be an instance method.\n  at %s line %d", method->op_method->file, method->op_method->line);
      }
    }
    else if (class->category == SPVM_CLASS_C_CATEGORY_CLASS) {
      if (method->is_required) {
        SPVM_COMPILER_error(compiler, "The method defined in the class cannnot have the method attribute \"required\".\n  at %s line %d", method->op_method->file, method->op_method->line);
      }
    }
    
    if (method->is_native) {
      if (method->op_block) {
        SPVM_COMPILER_error(compiler, "The native method cannnot have the block.\n  at %s line %d", method->op_method->file, method->op_method->line);
      }
    }
    
    SPVM_METHOD* found_method = SPVM_HASH_get(class->method_symtable, method_name, strlen(method_name));
    
    if (found_method) {
      SPVM_COMPILER_error(compiler, "Redeclaration of the \"%s\" method in the \"%s\" class.\n  at %s line %d", method_name, class_name, method->op_method->file, method->op_method->line);
    }
    // Unknown method
    else {
      const char* found_method_name = SPVM_HASH_get(class->method_symtable, method_name, strlen(method_name));
      if (found_method_name) {
        SPVM_COMPILER_error(compiler, "Redeclaration of the \"%s\" method.\n  at %s line %d", method_name, method->op_method->file, method->op_method->line);
      }
      else {
        // Bind standard functions
        method->class = class;
        
        if (method->is_destructor) {
          class->destructor_method = method;
        }
        
        if (method->is_init) {
          class->init_method = method;
        }

        if (method->is_required) {
          if (class->required_method) {
            SPVM_COMPILER_error(compiler, "The interface cannnot have multiple required methods \"%s\".\n  at %s line %d", method_name, method->op_method->file, method->op_method->line);
          }
          class->required_method = method;
        }
        
        assert(method->op_method->file);
        
        // Method absolute name
        int32_t method_abs_name_length = strlen(class->name) + 2 + strlen(method->name);
        char* method_abs_name = SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->allocator, method_abs_name_length + 1);
        memcpy(method_abs_name, class->name, strlen(class->name));
        memcpy(method_abs_name + strlen(class_name), "->", 2);
        memcpy(method_abs_name + strlen(class_name) + 2, method_name, strlen(method_name));
        method->abs_name = method_abs_name;

        // Add the method to the method symtable of the class
        SPVM_HASH_set(class->method_symtable, method->name, strlen(method->name), method);
      }
    }
  }
  
  // mulnum_t
  if (class->category == SPVM_CLASS_C_CATEGORY_MULNUM) {
    if (class->methods->length > 0) {
      SPVM_COMPILER_error(compiler, "The multi-numeric type cannnot have methods.\n  at %s line %d", op_class->file, op_class->line);
    }
    if (class->class_vars->length > 0) {
      SPVM_COMPILER_error(compiler, "The multi-numeric type cannnot have class variables.\n  at %s line %d", op_class->file, op_class->line);
    }
    if (class->fields->length == 0) {
      SPVM_COMPILER_error(compiler, "The multi-numeric type must have at least one field.\n  at %s line %d", class->op_class->file, class->op_class->line);
    }
    else if (class->fields->length > 255) {
      SPVM_COMPILER_error(compiler, "The length of the fields defined in the multi-numeric type must be less than or equal to 255.\n  at %s line %d", class->op_class->file, class->op_class->line);
    }
  }

  return op_class;
}

SPVM_OP* SPVM_OP_build_extends(SPVM_COMPILER* compiler, SPVM_OP* op_extends, SPVM_OP* op_name_parent_class) {
  
  SPVM_OP_insert_child(compiler, op_extends, op_extends->last, op_name_parent_class);
  
  return op_extends;
}

SPVM_OP* SPVM_OP_build_version_decl(SPVM_COMPILER* compiler, SPVM_OP* op_version_decl, SPVM_OP* op_version_string) {
  
  SPVM_OP_insert_child(compiler, op_version_decl, op_version_decl->last, op_version_string);
  
  return op_version_decl;
}

SPVM_OP* SPVM_OP_build_allow(SPVM_COMPILER* compiler, SPVM_OP* op_allow, SPVM_OP* op_name_class) {
  
  SPVM_ALLOW* allow = SPVM_ALLOW_new(compiler);
  op_allow->uv.allow = allow;
  allow->op_allow = op_allow;
  allow->class_name = op_name_class->uv.name;
  
  // add use stack
  SPVM_OP* op_use = SPVM_OP_new_op_use(compiler, op_allow->file, op_allow->line);
  SPVM_OP* op_name_class_alias = NULL;
  int32_t is_require = 0;
  SPVM_OP_build_use(compiler, op_use, op_name_class, op_name_class_alias, is_require);
  
  return op_allow;
}

SPVM_OP* SPVM_OP_build_alias(SPVM_COMPILER* compiler, SPVM_OP* op_use, SPVM_OP* op_name_class, SPVM_OP* op_name_class_alias) {
  
  SPVM_USE* use = op_use->uv.use;
  use->op_use = op_use;
  use->class_name = op_name_class->uv.name;
  const char* class_alias_name = op_name_class_alias->uv.name;
  use->class_alias_name = class_alias_name;
  
  return op_use;
}

SPVM_OP* SPVM_OP_build_use(SPVM_COMPILER* compiler, SPVM_OP* op_use, SPVM_OP* op_name_class, SPVM_OP* op_name_class_alias, int32_t is_require) {
  
  SPVM_USE* use = op_use->uv.use;
  use->op_use = op_use;
  use->is_require = is_require;
  use->class_name = op_name_class->uv.name;
  
  if (op_name_class_alias) {
    const char* class_alias_name = op_name_class_alias->uv.name;
    use->class_alias_name = class_alias_name;
  }

  SPVM_LIST_push(compiler->op_use_stack, op_use);
  
  return op_use;
}

SPVM_OP* SPVM_OP_build_enumeration_definition(SPVM_COMPILER* compiler, SPVM_OP* op_enumeration, SPVM_OP* op_enumeration_block, SPVM_OP* op_attributes) {
  
  SPVM_OP_insert_child(compiler, op_enumeration, op_enumeration->last, op_enumeration_block);
  
  SPVM_OP* op_enumeration_values = op_enumeration_block->first;
  SPVM_OP* op_method = op_enumeration_values->first;
  while ((op_method = SPVM_OP_sibling(compiler, op_method))) {
    SPVM_METHOD* method = op_method->uv.method;

    // Enumeration attributes
    int32_t access_control_attributes_count = 0;
    if (op_attributes) {
      SPVM_OP* op_attribute = op_attributes->first;
      while ((op_attribute = SPVM_OP_sibling(compiler, op_attribute))) {
        SPVM_ATTRIBUTE* attribute = op_attribute->uv.attribute;
        
        switch (attribute->id) {
          case SPVM_ATTRIBUTE_C_ID_PRIVATE: {
            method->access_control_type = SPVM_ATTRIBUTE_C_ID_PRIVATE;
            access_control_attributes_count++;
            break;
          }
          case SPVM_ATTRIBUTE_C_ID_PROTECTED: {
            method->access_control_type = SPVM_ATTRIBUTE_C_ID_PROTECTED;
            access_control_attributes_count++;
            break;
          }
          case SPVM_ATTRIBUTE_C_ID_PUBLIC: {
            method->access_control_type = SPVM_ATTRIBUTE_C_ID_PUBLIC;
            access_control_attributes_count++;
            break;
          }
          default: {
            SPVM_COMPILER_error(compiler, "Invalid enumeration attribute \"%s\".\n  at %s line %d", SPVM_ATTRIBUTE_get_name(compiler, attribute->id), op_attributes->file, op_attributes->line);
          }
        }
      }
      if (access_control_attributes_count > 1) {
        SPVM_COMPILER_error(compiler, "Only one of enumeration attributes \"private\", \"protected\" or \"public\" can be specified.\n  at %s line %d", op_method->file, op_method->line);
      }
    }
    
    // The default of the access controll of the enumeration is public.
    if (method->access_control_type == SPVM_ATTRIBUTE_C_ID_UNKNOWN) {
      method->access_control_type = SPVM_ATTRIBUTE_C_ID_PUBLIC;
    }
  }
  
  // Reset enum information
  compiler->current_enum_value = 0;
  
  return op_enumeration;
}

SPVM_OP* SPVM_OP_build_enumeration_value(SPVM_COMPILER* compiler, SPVM_OP* op_name, SPVM_OP* op_constant) {
  
  if (op_constant) {
    
    SPVM_CONSTANT* constant = op_constant->uv.constant;
    
    if (constant->type->dimension == 0 && constant->type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_INT) {
      compiler->current_enum_value = constant->value.ival;
    }
    else {
      SPVM_COMPILER_error(compiler, "The value of the enumeration must be int type.\n  at %s line %d", op_constant->file, op_constant->line);
    }
    
    compiler->current_enum_value++;
  }
  else {
    op_constant = SPVM_OP_new_op_constant_int(compiler, (int32_t)compiler->current_enum_value, op_name->file, op_name->line);
    
    compiler->current_enum_value++;
  }
  
  // Return
  SPVM_OP* op_return = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_RETURN, op_name->file, op_name->line);
  SPVM_OP_insert_child(compiler, op_return, op_return->last, op_constant);
  
  // Statements
  SPVM_OP* op_list_statements = SPVM_OP_new_op_list(compiler, op_name->file, op_name->line);
  SPVM_OP_insert_child(compiler, op_list_statements, op_list_statements->last, op_return);

  // Block
  SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, op_name->file, op_name->line);
  SPVM_OP_insert_child(compiler, op_block, op_block->last, op_list_statements);
  
  // method
  SPVM_OP* op_method = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_METHOD, op_name->file, op_name->line);
  op_method->file = op_name->file;
  op_method->line = op_name->line;
  
  // Type
  SPVM_OP* op_return_type = SPVM_OP_new_op_type(compiler, op_constant->uv.constant->type, op_name->file, op_name->line);

  SPVM_OP* op_list_attributes = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
  SPVM_OP* op_attribute_static = SPVM_OP_new_op_attribute(compiler, SPVM_ATTRIBUTE_C_ID_STATIC, compiler->cur_file, compiler->cur_line);
  SPVM_OP_insert_child(compiler, op_list_attributes, op_list_attributes->first, op_attribute_static);
  
  // Build method
  op_method = SPVM_OP_build_method_definition(compiler, op_method, op_name, op_return_type, NULL, op_list_attributes, op_block, NULL, NULL, 0, 0);
  
  // Set constant
  op_method->uv.method->op_inline = op_constant;
  
  // Method is enumeration
  op_method->uv.method->is_enum = 1;
  
  return op_method;
}

SPVM_OP* SPVM_OP_build_class_var_definition(SPVM_COMPILER* compiler, SPVM_OP* op_class_var, SPVM_OP* op_name, SPVM_OP* op_attributes, SPVM_OP* op_type) {
  
  SPVM_CLASS_VAR* class_var = SPVM_CLASS_VAR_new(compiler);
  
  const char* name = op_name->uv.name;;
  class_var->name = op_name->uv.name;
  
  if (strstr(name, "::")) {
    SPVM_COMPILER_error(compiler, "The class varaible name \"%s\" cannnot contain \"::\".\n  at %s line %d", class_var->name, op_name->file, op_name->line);
  }
  
  class_var->op_name = op_name;
  class_var->type = op_type->uv.type;
  class_var->op_class_var = op_class_var;

  op_class_var->uv.class_var = class_var;

  // Class variable attributes
  if (op_attributes) {
    int32_t field_method_attributes_count = 0;
    int32_t access_control_attributes_count = 0;
    SPVM_OP* op_attribute = op_attributes->first;
    while ((op_attribute = SPVM_OP_sibling(compiler, op_attribute))) {
      SPVM_ATTRIBUTE* attribute = op_attribute->uv.attribute;
      
      switch (attribute->id) {
        case SPVM_ATTRIBUTE_C_ID_PRIVATE: {
          class_var->access_control_type = SPVM_ATTRIBUTE_C_ID_PRIVATE;
          access_control_attributes_count++;
          break;
        }
        case SPVM_ATTRIBUTE_C_ID_PROTECTED: {
          class_var->access_control_type = SPVM_ATTRIBUTE_C_ID_PROTECTED;
          access_control_attributes_count++;
          break;
        }
        case SPVM_ATTRIBUTE_C_ID_PUBLIC: {
          class_var->access_control_type = SPVM_ATTRIBUTE_C_ID_PUBLIC;
          access_control_attributes_count++;
          break;
        }
        case SPVM_ATTRIBUTE_C_ID_RW: {
          class_var->has_setter = 1;
          class_var->has_getter = 1;
          field_method_attributes_count++;
          break;
        }
        case SPVM_ATTRIBUTE_C_ID_RO: {
          class_var->has_getter = 1;
          field_method_attributes_count++;
          break;
        }
        case SPVM_ATTRIBUTE_C_ID_WO: {
          class_var->has_setter = 1;
          field_method_attributes_count++;
          break;
        }
        default: {
          SPVM_COMPILER_error(compiler, "Invalid class variable attribute \"%s\".\n  at %s line %d", SPVM_ATTRIBUTE_get_name(compiler, attribute->id), op_attributes->file, op_attributes->line);
        }
      }
      if (field_method_attributes_count > 1) {
        SPVM_COMPILER_error(compiler, "Only one of class variable attributes \"rw\", \"ro\", \"wo\" can be specifed.\n  at %s line %d", op_class_var->file, op_class_var->line);
      }
      if (access_control_attributes_count > 1) {
        SPVM_COMPILER_error(compiler, "Only one of class variable attributes \"private\", \"protected\" or \"public\" can be specified.\n  at %s line %d", op_class_var->file, op_class_var->line);
      }
    }
  }
  
  // The default of the access controll of the class variable is private.
  if (class_var->access_control_type == SPVM_ATTRIBUTE_C_ID_UNKNOWN) {
    class_var->access_control_type = SPVM_ATTRIBUTE_C_ID_PRIVATE;
  }
  
  return op_class_var;
}

SPVM_OP* SPVM_OP_build_field_definition(SPVM_COMPILER* compiler, SPVM_OP* op_field, SPVM_OP* op_name_field, SPVM_OP* op_attributes, SPVM_OP* op_type) {

  // Create field information
  SPVM_FIELD* field = SPVM_FIELD_new(compiler);

  // Field Name
  field->op_name = op_name_field;
  field->name = op_name_field->uv.name;

  if (strstr(field->op_name->uv.name, "::")) {
    SPVM_COMPILER_error(compiler, "The field name \"%s\" cannnot contain \"::\".\n  at %s line %d", field->name, op_name_field->file, op_name_field->line);
  }

  // Type
  field->type = op_type->uv.type;
  
  // Set field informaiton
  op_field->uv.field = field;

  // Field attributes
  if (op_attributes) {
    SPVM_OP* op_attribute = op_attributes->first;
    int32_t field_method_attributes_count = 0;
    int32_t access_control_attributes_count = 0;
    while ((op_attribute = SPVM_OP_sibling(compiler, op_attribute))) {
      SPVM_ATTRIBUTE* attribute = op_attribute->uv.attribute;
      
      switch (attribute->id) {
        case SPVM_ATTRIBUTE_C_ID_PRIVATE: {
          field->access_control_type = SPVM_ATTRIBUTE_C_ID_PRIVATE;
          access_control_attributes_count++;
          break;
        }
        case SPVM_ATTRIBUTE_C_ID_PROTECTED: {
          field->access_control_type = SPVM_ATTRIBUTE_C_ID_PROTECTED;
          access_control_attributes_count++;
          break;
        }
        case SPVM_ATTRIBUTE_C_ID_PUBLIC: {
          field->access_control_type = SPVM_ATTRIBUTE_C_ID_PUBLIC;
          access_control_attributes_count++;
          break;
        }
        case SPVM_ATTRIBUTE_C_ID_RW: {
          field->has_setter = 1;
          field->has_getter = 1;
          field_method_attributes_count++;
          break;
        }
        case SPVM_ATTRIBUTE_C_ID_RO: {
          field->has_getter = 1;
          field_method_attributes_count++;
          break;
        }
        case SPVM_ATTRIBUTE_C_ID_WO: {
          field->has_setter = 1;
          field_method_attributes_count++;
          break;
        }
        default: {
          SPVM_COMPILER_error(compiler, "Invalid field attribute \"%s\".\n  at %s line %d", SPVM_ATTRIBUTE_get_name(compiler, attribute->id), op_attributes->file, op_attributes->line);
        }
      }
      
      if (field_method_attributes_count > 1) {
        SPVM_COMPILER_error(compiler, "Only one of field attributes \"rw\", \"ro\" or \"wo\" can be specifed.\n  at %s line %d", op_field->file, op_field->line);
      }
      if (access_control_attributes_count > 1) {
        SPVM_COMPILER_error(compiler, "Only one of field attributes \"private\", \"protected\" or \"public\" can be specified.\n  at %s line %d", op_field->file, op_field->line);
      }
    }
  }
  
  field->op_field = op_field;
  
  return op_field;
}

SPVM_OP* SPVM_OP_build_method_definition(SPVM_COMPILER* compiler, SPVM_OP* op_method, SPVM_OP* op_name_method, SPVM_OP* op_return_type, SPVM_OP* op_args, SPVM_OP* op_attributes, SPVM_OP* op_block, SPVM_OP* op_captures, SPVM_OP* op_dot3, int32_t is_init, int32_t is_anon) {
  SPVM_METHOD* method = SPVM_METHOD_new(compiler);
  
  // Is anon method
  if (is_anon) {
    method->is_anon = 1;
  }
  
  if (op_name_method == NULL) {
    SPVM_CONSTANT_STRING* anon_method_name_string = SPVM_CONSTANT_STRING_new(compiler, "", strlen(""));
    const char* anon_method_name = anon_method_name_string->value;
    op_name_method = SPVM_OP_new_op_name(compiler, anon_method_name, op_method->file, op_method->line);
  }
  const char* method_name = op_name_method->uv.name;
  if (strstr(method_name, "::")) {
    SPVM_COMPILER_error(compiler, "The method name \"%s\" cannnot contain \"::\".\n  at %s line %d", method_name, op_name_method->file, op_name_method->line);
  }
  
  // Block is method block
  if (op_block) {
    op_block->uv.block->id = SPVM_BLOCK_C_ID_METHOD;
  }
  
  // Create method information
  method->op_name = op_name_method;
  
  method->name = method->op_name->uv.name;
  
  if (op_dot3) {
    method->have_vaarg = 1;
  }
  
  method->is_init = is_init;
  if (!is_init && strcmp(method_name, "INIT") == 0) {
    SPVM_COMPILER_error(compiler, "\"INIT\" cannnot be used as a method name.\n  at %s line %d", op_name_method->file, op_name_method->line);
  }

  // Method attributes
  int32_t access_control_attributes_count = 0;
  if (op_attributes) {
    SPVM_OP* op_attribute = op_attributes->first;
    while ((op_attribute = SPVM_OP_sibling(compiler, op_attribute))) {
      SPVM_ATTRIBUTE* attribute = op_attribute->uv.attribute;
      
      switch (attribute->id) {
        case SPVM_ATTRIBUTE_C_ID_PRIVATE: {
          method->access_control_type = SPVM_ATTRIBUTE_C_ID_PRIVATE;
          access_control_attributes_count++;
          break;
        }
        case SPVM_ATTRIBUTE_C_ID_PROTECTED: {
          method->access_control_type = SPVM_ATTRIBUTE_C_ID_PROTECTED;
          access_control_attributes_count++;
          break;
        }
        case SPVM_ATTRIBUTE_C_ID_PUBLIC: {
          method->access_control_type = SPVM_ATTRIBUTE_C_ID_PUBLIC;
          access_control_attributes_count++;
          break;
        }
        case SPVM_ATTRIBUTE_C_ID_PRECOMPILE: {
          method->is_precompile = 1;
          break;
        }
        case SPVM_ATTRIBUTE_C_ID_REQUIRED: {
          method->is_required = 1;
          break;
        }
        case SPVM_ATTRIBUTE_C_ID_NATIVE: {
          method->is_native = 1;
          break;
        }
        case SPVM_ATTRIBUTE_C_ID_STATIC: {
          method->is_class_method = 1;
          break;
        }
        default: {
          SPVM_COMPILER_error(compiler, "Invalid method attribute \"%s\".\n  at %s line %d", SPVM_ATTRIBUTE_get_name(compiler, attribute->id), op_attributes->file, op_attributes->line);
        }
      }
    }
    
    if (method->is_native && method->is_precompile) {
      SPVM_COMPILER_error(compiler, "Only one of method attributes \"native\" and \"precompile\" can be specified.\n  at %s line %d", op_attributes->file, op_attributes->line);
    }
    if (access_control_attributes_count > 1) {
      SPVM_COMPILER_error(compiler, "Only one of method attributes \"private\", \"protected\" or \"public\" can be specified.\n  at %s line %d", op_method->file, op_method->line);
    }
  }
  
  // The default of the access controll of the method is publice.
  if (method->access_control_type == SPVM_ATTRIBUTE_C_ID_UNKNOWN) {
    method->access_control_type = SPVM_ATTRIBUTE_C_ID_PUBLIC;
  }
  
  // Native method cannnot have block
  if ((method->is_native) && op_block) {
    SPVM_COMPILER_error(compiler, "The native method cannnot have the block.\n  at %s line %d", op_block->file, op_block->line);
  }
  
  // method args
  if (!op_args) {
    op_args = SPVM_OP_new_op_list(compiler, op_method->file, op_method->line);
  }
  
  // Add $self : self before the first argument
  if (!method->is_class_method) {
    SPVM_OP* op_arg_var_name_self = SPVM_OP_new_op_name(compiler, "$self", op_method->file, op_method->line);
    SPVM_OP* op_arg_var_self = SPVM_OP_new_op_var(compiler, op_arg_var_name_self);
    SPVM_TYPE* self_type = SPVM_TYPE_new(compiler, 0, 0, 0);
    SPVM_OP* op_self_type = SPVM_OP_new_op_type(compiler, self_type, op_method->file, op_method->line);
    op_self_type->flag |= SPVM_OP_C_FLAG_TYPE_IS_SELF;
    SPVM_OP* op_arg_self = SPVM_OP_build_arg(compiler, op_arg_var_self, op_self_type, NULL, NULL);
    SPVM_OP_insert_child(compiler, op_args, op_args->first, op_arg_self);
  }

  // Add method arguments
  {
    int32_t found_optional_arg = 0;
    int32_t required_args_length = 0;
    int32_t args_length = 0;
    SPVM_OP* op_arg = op_args->first;
    while ((op_arg = SPVM_OP_sibling(compiler, op_arg))) {
      SPVM_VAR_DECL* arg_var_decl = op_arg->uv.var->var_decl;
      if (!found_optional_arg) {
        if (arg_var_decl->op_optional_arg_default) {
          found_optional_arg = 1;
        }
        else {
          required_args_length++;
        }
      }
      args_length++;
    }
    method->args_length = args_length;
    method->required_args_length = required_args_length;
  }

  // Capture variables
  if (op_captures) {
    SPVM_OP* op_capture = op_captures->first;
    while ((op_capture = SPVM_OP_sibling(compiler, op_capture))) {
      SPVM_LIST_push(method->captures, op_capture->uv.var->var_decl);
    }
  }
  
  // Variable declarations of arguments
  SPVM_OP* op_arg = op_args->first;
  while ((op_arg = SPVM_OP_sibling(compiler, op_arg))) {
    SPVM_LIST_push(method->var_decls, op_arg->uv.var->var_decl);
  }

  // return type
  method->return_type = op_return_type->uv.type;
  
  if (strcmp(method->op_name->uv.name, "DESTROY") == 0) {
    method->is_destructor = 1;
    
    // DESTROY return type must be void
    if (!(method->return_type->dimension == 0 && method->return_type->basic_type->id == SPVM_NATIVE_C_BASIC_TYPE_ID_VOID)) {
      SPVM_COMPILER_error(compiler, "The return type of the DESTROY destructor method must be the void type.\n  at %s line %d", op_method->file, op_method->line);
    }
    
    // DESTROY is instance method
    if (method->is_class_method) {
      SPVM_COMPILER_error(compiler, "The DESTROY destructor method must be an instance method.\n  at %s line %d", op_method->file, op_method->line);
    }

    // DESTROY doesn't have arguments without invocant
    if (method->args_length != 1) {
      SPVM_COMPILER_error(compiler, "The DESTROY destructor method cannnot have arguments.\n  at %s line %d", op_method->file, op_method->line);
    }
  }
  
  if (op_block) {

    SPVM_OP* op_list_statement = op_block->first;

    // Add variable declarations before the first of the statements
    for (int32_t i = method->args_length - 1; i >= 0; i--) {
      SPVM_VAR_DECL* arg_var_decl = SPVM_LIST_get(method->var_decls, i);
      assert(arg_var_decl);
      SPVM_OP* op_name_var = SPVM_OP_new_op_name(compiler, arg_var_decl->var->name, arg_var_decl->op_var_decl->file, arg_var_decl->op_var_decl->line);
      SPVM_OP* op_var = SPVM_OP_new_op_var(compiler, op_name_var);
      op_var->uv.var->var_decl = arg_var_decl;
      op_var->uv.var->is_declaration = 1;
      op_var->uv.var->var_decl = arg_var_decl;

      SPVM_OP_insert_child(compiler, op_list_statement, op_list_statement->first, op_var);
    }

    // Add condition_flag variable to first of block
    {
      char* name = "$.condition_flag";
      SPVM_OP* op_name = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NAME, op_list_statement->file, op_list_statement->last->line + 1);
      op_name->uv.name = name;
      SPVM_OP* op_var = SPVM_OP_build_var(compiler, op_name);
      SPVM_OP* op_var_decl = SPVM_OP_new_op_var_decl(compiler, op_list_statement->file, op_list_statement->last->line + 1);
      SPVM_OP* op_type = SPVM_OP_new_op_int_type(compiler, op_list_statement->file, op_list_statement->line);
      op_var = SPVM_OP_build_var_decl(compiler, op_var_decl, op_var, op_type, NULL);
      SPVM_OP_insert_child(compiler, op_list_statement, op_list_statement->first, op_var);
    }

    // Add return statement after the last of the statements
    {
      SPVM_OP* op_return = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_RETURN, op_list_statement->file, op_list_statement->last->line + 1);
      SPVM_TYPE* return_type = method->return_type;
      if (SPVM_TYPE_is_void_type(compiler, return_type->basic_type->id, return_type->dimension, return_type->flag)) {
        SPVM_OP_insert_child(compiler, op_list_statement, op_list_statement->last, op_return);
      }
      else {
        // Return variable name
        char* name = "$.return";
        SPVM_OP* op_name = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NAME, op_list_statement->file, op_list_statement->last->line + 1);
        op_name->uv.name = name;
        SPVM_OP* op_var = SPVM_OP_build_var(compiler, op_name);
        SPVM_OP* op_var_decl = SPVM_OP_new_op_var_decl(compiler, op_list_statement->file, op_list_statement->last->line + 1);
        SPVM_OP* op_type = SPVM_OP_new_op_type(compiler, return_type, op_list_statement->file, op_list_statement->last->line + 1);
        op_var = SPVM_OP_build_var_decl(compiler, op_var_decl, op_var, op_type, NULL);
        SPVM_OP_insert_child(compiler, op_return, op_return->last, op_var);
        SPVM_OP_insert_child(compiler, op_list_statement, op_list_statement->last, op_return);
      }
    }
  }
  
  // Save block
  method->op_block = op_block;
  
  method->op_method = op_method;
  
  op_method->uv.method = method;
  
  return op_method;
}

SPVM_OP* SPVM_OP_build_arg(SPVM_COMPILER* compiler, SPVM_OP* op_var, SPVM_OP* op_type, SPVM_OP* op_attributes, SPVM_OP* op_optional_arg_default) {
  
  SPVM_OP* op_var_decl = SPVM_OP_new_op_var_decl_eternal(compiler, op_var->file, op_var->line);

  op_var_decl->uv.var_decl->is_arg = 1;
  
  op_var_decl->uv.var_decl->op_optional_arg_default = op_optional_arg_default;
  
  op_var = SPVM_OP_build_var_decl(compiler, op_var_decl, op_var, op_type, op_attributes);
  
  return op_var;
}

SPVM_OP* SPVM_OP_build_init_block(SPVM_COMPILER* compiler, SPVM_OP* op_init, SPVM_OP* op_block) {
    
  SPVM_OP* op_method = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_METHOD, op_init->file, op_init->line);
  SPVM_CONSTANT_STRING* method_name_string = SPVM_CONSTANT_STRING_new(compiler, "INIT", strlen("INIT"));
  const char* method_name = method_name_string->value;
  SPVM_OP* op_method_name = SPVM_OP_new_op_name(compiler, "INIT", op_init->file, op_init->line);
  SPVM_OP* op_void_type = SPVM_OP_new_op_void_type(compiler, op_init->file, op_init->line);
  
  SPVM_OP* op_list_attributes = SPVM_OP_new_op_list(compiler, op_init->file, op_init->line);
  SPVM_OP* op_attribute_static = SPVM_OP_new_op_attribute(compiler, SPVM_ATTRIBUTE_C_ID_STATIC, op_init->file, op_init->line);
  SPVM_OP_insert_child(compiler, op_list_attributes, op_list_attributes->first, op_attribute_static);
  
  int32_t is_init = 1;
  SPVM_OP_build_method_definition(compiler, op_method, op_method_name, op_void_type, NULL, op_list_attributes, op_block, NULL, NULL, is_init, 0);
  
  return op_method;
}

SPVM_OP* SPVM_OP_build_var(SPVM_COMPILER* compiler, SPVM_OP* op_var_name) {
  
  SPVM_OP* op_var = SPVM_OP_new_op_var(compiler, op_var_name);
  
  return op_var;
}

SPVM_OP* SPVM_OP_build_eval(SPVM_COMPILER* compiler, SPVM_OP* op_eval, SPVM_OP* op_eval_block) {
  
  SPVM_OP_insert_child(compiler, op_eval, op_eval->last, op_eval_block);
  
  // eval block
  op_eval_block->uv.block->id = SPVM_BLOCK_C_ID_EVAL;
  
  return op_eval;
}

SPVM_OP* SPVM_OP_build_switch_statement(SPVM_COMPILER* compiler, SPVM_OP* op_switch, SPVM_OP* op_operand_condition, SPVM_OP* op_switch_block) {
  
  SPVM_OP* op_switch_condition = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_SWITCH_CONDITION, op_operand_condition->file, op_operand_condition->line);
  SPVM_OP_insert_child(compiler, op_switch_condition, op_switch_condition->last, op_operand_condition);
  
  SPVM_OP* op_switch_condition_do_nothing = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_DO_NOTHING, op_switch_condition->file, op_switch_condition->line);
  SPVM_OP_insert_child(compiler, op_switch_condition_do_nothing, op_switch_condition_do_nothing->last, op_switch_condition);
  
  SPVM_OP_insert_child(compiler, op_switch, op_switch->last, op_switch_condition_do_nothing);
  SPVM_OP_insert_child(compiler, op_switch, op_switch->last, op_switch_block);
  
  SPVM_SWITCH_INFO* switch_info = SPVM_SWITCH_INFO_new(compiler);
  op_switch->uv.switch_info = switch_info;
  
  op_switch_condition->uv.switch_info = switch_info;
  
  return op_switch;
}

SPVM_OP* SPVM_OP_build_switch_block(SPVM_COMPILER* compiler, SPVM_OP* op_switch_block, SPVM_OP* op_case_statements, SPVM_OP* op_default_statement) {
  
  if (op_case_statements->id != SPVM_OP_C_ID_LIST) {
    SPVM_OP* op_list = SPVM_OP_new_op_list(compiler, op_case_statements->file, op_case_statements->line);
    SPVM_OP_insert_child(compiler, op_list, op_list->last, op_case_statements);
    op_case_statements = op_list;
  }
  
  SPVM_OP_insert_child(compiler, op_switch_block, op_switch_block->last, op_case_statements);
  if (op_default_statement) {
    SPVM_OP_insert_child(compiler, op_switch_block, op_switch_block->last, op_default_statement);
  }
  
  return op_switch_block;
}

SPVM_OP* SPVM_OP_build_case_statement(SPVM_COMPILER* compiler, SPVM_OP* op_case_info, SPVM_OP* op_operand, SPVM_OP* op_block) {
  
  SPVM_CASE_INFO* case_info = SPVM_CASE_INFO_new(compiler);
  
  SPVM_OP_insert_child(compiler, op_case_info, op_case_info->last, op_operand);
  op_operand->flag = SPVM_OP_C_FLAG_CONSTANT_CASE;
  
  if (op_block) {
    SPVM_OP* op_statements = op_block->first;
    if (op_statements) {
      SPVM_OP* op_last_statement = op_statements->last;
      
      // Add "break" statement if it doesn't exist
      {
        // No statement
        if (!op_last_statement) {
          SPVM_OP* op_break = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_BREAK, op_statements->file, op_statements->line);
          SPVM_OP_insert_child(compiler, op_statements, op_statements->last, op_break);
        }
        // The last statement is not "break" statement
        else if (op_last_statement->id != SPVM_OP_C_ID_BREAK) {
          SPVM_OP* op_break = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_BREAK, op_last_statement->file, op_last_statement->line + 1);
          SPVM_OP_insert_child(compiler, op_statements, op_statements->last, op_break);
        }
      }
    }
    SPVM_OP_insert_child(compiler, op_case_info, op_case_info->last, op_block);
  }
  
  case_info->op_case_info = op_case_info;
  
  op_case_info->uv.case_info = case_info;
  
  return op_case_info;
}

SPVM_OP* SPVM_OP_build_default_statement(SPVM_COMPILER* compiler, SPVM_OP* op_default, SPVM_OP* op_block) {
  
  if (op_block) {
    SPVM_OP_insert_child(compiler, op_default, op_default->last, op_block);
  }
  
  return op_default;
}

SPVM_OP* SPVM_OP_build_condition(SPVM_COMPILER* compiler, SPVM_OP* op_operand_condition, int32_t is_not) {
  // Condition
  int32_t id;
  if (is_not) {
    id = SPVM_OP_C_ID_CONDITION_NOT;
  }
  else {
    id = SPVM_OP_C_ID_CONDITION;
  }
  SPVM_OP* op_condition = SPVM_OP_new_op(compiler, id, op_operand_condition->file, op_operand_condition->line);
  
  if (SPVM_OP_is_rel_op(compiler, op_operand_condition)) {
    assert(op_operand_condition->moresib == 0);
    SPVM_OP_insert_child(compiler, op_condition, op_condition->last, op_operand_condition);
  }
  else {
    SPVM_OP* op_assign_bool = SPVM_OP_new_op_assign_bool(compiler, op_operand_condition, op_operand_condition->file, op_operand_condition->line);
    SPVM_OP_insert_child(compiler, op_condition, op_condition->last, op_assign_bool);
  }
  
  return op_condition;
}

SPVM_OP* SPVM_OP_build_for_statement(SPVM_COMPILER* compiler, SPVM_OP* op_for, SPVM_OP* op_operand_init, SPVM_OP* op_operand_condition, SPVM_OP* op_operand_increment, SPVM_OP* op_block_statements) {
  
  // Loop
  SPVM_OP* op_loop = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_LOOP, op_for->file, op_for->line);
  
  // Condition
  SPVM_OP* op_condition = SPVM_OP_build_condition(compiler, op_operand_condition, 1);
  op_condition->flag |= SPVM_OP_C_FLAG_CONDITION_LOOP;

  // Set block flag
  op_block_statements->uv.block->id = SPVM_BLOCK_C_ID_LOOP_STATEMENTS;

  // Outer block for initialize loop variable
  SPVM_OP* op_block_init = SPVM_OP_new_op_block(compiler, op_for->file, op_for->line);
  op_block_init->uv.block->id = SPVM_BLOCK_C_ID_LOOP_INIT;
  
  // Block for increment
  SPVM_OP* op_loop_increment = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_LOOP_INCREMENT, op_for->file, op_for->line);

  SPVM_OP_insert_child(compiler, op_loop_increment, op_loop_increment->last, op_operand_increment);

  SPVM_OP_insert_child(compiler, op_block_init, op_block_init->last, op_operand_init);
  SPVM_OP_insert_child(compiler, op_block_init, op_block_init->last, op_condition);
  SPVM_OP_insert_child(compiler, op_block_init, op_block_init->last, op_block_statements);
  SPVM_OP_insert_child(compiler, op_block_init, op_block_init->last, op_loop_increment);
  
  SPVM_OP_insert_child(compiler, op_loop, op_loop->last, op_block_init);
  
  return op_loop;
}

SPVM_OP* SPVM_OP_build_foreach_statement(SPVM_COMPILER* compiler, SPVM_OP* op_for, SPVM_OP* op_var_element, SPVM_OP* op_array, SPVM_OP* op_block_statements) {

  /*
    {
      
      my $.array = $array;
      my $.array_length = @$.array;
      for (my $.i = 0; $.i < $.array_length; $.i++) {
        my $element = $.array->[$.i];
        
        # ...
      }
    }
  */

  SPVM_OP* op_var_init_name = SPVM_OP_new_op_name(compiler, "$.i", op_for->file, op_for->line);
  SPVM_OP* op_var_init_orig = SPVM_OP_new_op_var(compiler, op_var_init_name);
  SPVM_OP* op_var_array_name = SPVM_OP_new_op_name(compiler, "$.array", op_for->file, op_for->line);
  SPVM_OP* op_var_array_orig = SPVM_OP_new_op_var(compiler, op_var_array_name);
  SPVM_OP* op_var_array_length_name = SPVM_OP_new_op_name(compiler, "$.array_length", op_for->file, op_for->line);
  SPVM_OP* op_var_array_length_orig = SPVM_OP_new_op_var(compiler, op_var_array_length_name);
  
  // my $.i
  SPVM_OP* op_var_init_for_decl = SPVM_OP_new_op_var_clone(compiler, op_var_init_orig, op_var_init_orig->file, op_var_init_orig->line);
  SPVM_OP* op_var_decl_init = SPVM_OP_new_op_var_decl(compiler, op_for->file, op_for->line);
  SPVM_OP_build_var_decl(compiler, op_var_decl_init, op_var_init_for_decl, NULL, NULL);
  
  // 0
  SPVM_OP* op_constant_zero = SPVM_OP_new_op_constant_int(compiler, 0, op_for->file, op_for->line);
  
  // my $.i = 0
  SPVM_OP* op_assign_init = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ASSIGN, op_for->file, op_for->line);
  SPVM_OP_build_assign(compiler, op_assign_init, op_var_init_for_decl, op_constant_zero);
  
  // my $.array
  SPVM_OP* op_var_array_for_assign = SPVM_OP_new_op_var_clone(compiler, op_var_array_orig, op_var_array_orig->file, op_var_array_orig->line);
  SPVM_OP* op_var_decl_array = SPVM_OP_new_op_var_decl(compiler, op_for->file, op_for->line);
  SPVM_OP_build_var_decl(compiler, op_var_decl_array, op_var_array_for_assign, NULL, NULL);
  
  // my $.array = $array
  SPVM_OP* op_assign_array = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ASSIGN, op_for->file, op_for->line);
  SPVM_OP_build_assign(compiler, op_assign_array,  op_var_array_for_assign, op_array);
  
  // @$.array
  SPVM_OP* op_var_array_for_length = SPVM_OP_new_op_var_clone(compiler, op_var_array_orig, op_var_array_orig->file, op_var_array_orig->line);
  SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
  SPVM_OP_build_array_length(compiler, op_array_length, op_var_array_for_length);
  
  // my $.array_length
  SPVM_OP* op_var_array_length_for_assign = SPVM_OP_new_op_var_clone(compiler, op_var_array_length_orig, op_var_array_length_orig->file, op_var_array_length_orig->line);
  SPVM_OP* op_var_decl_array_length = SPVM_OP_new_op_var_decl(compiler, op_for->file, op_for->line);
  SPVM_OP_build_var_decl(compiler, op_var_decl_array_length, op_var_array_length_for_assign, NULL, NULL);
  
  // my $.array_length = @$.array
  SPVM_OP* op_assign_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ASSIGN, op_for->file, op_for->line);
  SPVM_OP_build_assign(compiler, op_assign_array_length, op_var_array_length_for_assign, op_array_length);
  
  // $.i < $array_length
  SPVM_OP* op_var_init_for_condition = SPVM_OP_new_op_var_clone(compiler, op_var_init_orig, op_var_array_orig->file, op_var_array_orig->line);
  SPVM_OP* op_var_array_length_for_condition = SPVM_OP_new_op_var_clone(compiler, op_var_array_length_orig, op_var_array_orig->file, op_var_array_orig->line);
  SPVM_OP* op_numlt = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NUMERIC_LT, op_for->file, op_for->line);
  SPVM_OP* op_numlt_comparison = SPVM_OP_build_comparison_op(compiler, op_numlt, op_var_init_for_condition, op_var_array_length_for_condition);
  
  // $.array->[$.i]
  SPVM_OP* op_var_init_for_array_access = SPVM_OP_new_op_var_clone(compiler, op_var_init_orig, op_var_init_orig->file, op_var_init_orig->line);
  SPVM_OP* op_var_array_for_array_access = SPVM_OP_new_op_var_clone(compiler, op_var_array_orig, op_var_array_orig->file, op_var_array_orig->line);
  SPVM_OP* op_array_access = SPVM_OP_build_array_access(compiler, op_var_array_for_array_access, op_var_init_for_array_access);
  
  // my $element = $.array->[$.i]
  SPVM_OP* op_assign_element = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ASSIGN, op_for->file, op_for->line);
  SPVM_OP_build_assign(compiler, op_assign_element, op_var_element, op_array_access);
  
  // $.i
  SPVM_OP* op_var_init_for_increament = SPVM_OP_new_op_var_clone(compiler, op_var_init_orig, op_var_init_orig->file, op_var_init_orig->line);
  
  // ++$.i;
  SPVM_OP* op_inc_increament = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PRE_INC, op_for->file, op_for->line);
  SPVM_OP_build_inc(compiler, op_inc_increament, op_var_init_for_increament);
  
  SPVM_OP* op_statements = op_block_statements->first;
  if (!op_statements) {
    op_statements = SPVM_OP_new_op_list(compiler, op_for->file, op_for->line);
    SPVM_OP_insert_child(compiler, op_block_statements, op_block_statements->first, op_statements);
  }
  SPVM_OP_insert_child(compiler, op_statements, op_statements->first, op_assign_element);
  
  op_for = SPVM_OP_build_for_statement(compiler, op_for, op_assign_init, op_numlt_comparison, op_inc_increament, op_block_statements);
  
  SPVM_OP* op_block_new = SPVM_OP_new_op_block(compiler, op_for->file, op_for->line);
  SPVM_OP* op_statements_new = SPVM_OP_new_op_list(compiler, op_for->file, op_for->line);
  SPVM_OP_insert_child(compiler, op_block_new, op_block_new->last, op_statements_new);
  
  SPVM_OP_insert_child(compiler, op_statements_new, op_statements_new->last, op_assign_array);
  SPVM_OP_insert_child(compiler, op_statements_new, op_statements_new->last, op_assign_array_length);
  SPVM_OP_insert_child(compiler, op_statements_new, op_statements_new->last, op_for);
  
  return op_block_new;
}

SPVM_OP* SPVM_OP_build_while_statement(SPVM_COMPILER* compiler, SPVM_OP* op_while, SPVM_OP* op_operand_condition, SPVM_OP* op_block_statements) {
  
  // Loop
  SPVM_OP* op_loop = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_LOOP, op_while->file, op_while->line);
  
  // Init statement. This is null.
  SPVM_OP* op_operand_init = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_DO_NOTHING, op_while->file, op_while->line);
  
  // Condition
  assert(op_operand_condition->moresib == 0);
  SPVM_OP* op_condition = SPVM_OP_build_condition(compiler, op_operand_condition, 1);
  op_condition->flag |= SPVM_OP_C_FLAG_CONDITION_LOOP;

  // Set block flag
  op_block_statements->uv.block->id = SPVM_BLOCK_C_ID_LOOP_STATEMENTS;
  
  // Next value. This is null.
  SPVM_OP* op_operand_increment = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_DO_NOTHING, op_while->file, op_while->line);

  SPVM_OP* op_block_init = SPVM_OP_new_op_block(compiler, op_while->file, op_while->line);
  op_block_init->uv.block->id = SPVM_BLOCK_C_ID_LOOP_INIT;

  // Block for increment
  SPVM_OP* op_loop_increment = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_LOOP_INCREMENT, op_while->file, op_while->line);
  SPVM_OP_insert_child(compiler, op_loop_increment, op_loop_increment->last, op_operand_increment);
  
  SPVM_OP_insert_child(compiler, op_block_init, op_block_init->last, op_operand_init);
  SPVM_OP_insert_child(compiler, op_block_init, op_block_init->last, op_condition);
  SPVM_OP_insert_child(compiler, op_block_init, op_block_init->last, op_block_statements);
  SPVM_OP_insert_child(compiler, op_block_init, op_block_init->last, op_loop_increment);
  
  SPVM_OP_insert_child(compiler, op_loop, op_loop->last, op_block_init);
  
  return op_loop;
}

SPVM_OP* SPVM_OP_build_if_require_statement(SPVM_COMPILER* compiler, SPVM_OP* op_if_require, SPVM_OP* op_use, SPVM_OP* op_block_true, SPVM_OP* op_block_false) {
  
  SPVM_OP_insert_child(compiler, op_if_require, op_if_require->last, op_use);
  SPVM_OP_insert_child(compiler, op_if_require, op_if_require->last, op_block_true);
  if (!op_block_false) {
    op_block_false = SPVM_OP_new_op_block(compiler, op_block_true->file, op_block_true->line);
  }
  SPVM_OP_insert_child(compiler, op_if_require, op_if_require->last, op_block_false);
  
  return op_if_require;
}

SPVM_OP* SPVM_OP_build_if_statement(SPVM_COMPILER* compiler, SPVM_OP* op_if, SPVM_OP* op_operand_condition, SPVM_OP* op_block_true, SPVM_OP* op_block_false, int32_t no_scope) {
  
  // ELSIF is same as IF
  int32_t not_condition = 0;
  
  if (op_if->id == SPVM_OP_C_ID_UNLESS) {
    op_if->id = SPVM_OP_C_ID_IF;
    not_condition = 1;
  }
  else if (op_if->id == SPVM_OP_C_ID_ELSIF) {
    op_if->id = SPVM_OP_C_ID_IF;
  }
  
  // Condition
  SPVM_OP* op_condition = SPVM_OP_build_condition(compiler, op_operand_condition, not_condition);
  op_condition->flag |= SPVM_OP_C_FLAG_CONDITION_IF;

  // Create true block if needed
  if (op_block_true->id != SPVM_OP_C_ID_BLOCK) {
    SPVM_OP* op_not_block = op_block_true;
    
    op_block_true = SPVM_OP_new_op_block(compiler, op_not_block->file, op_not_block->line);
    SPVM_OP* op_list = SPVM_OP_new_op_list(compiler, op_not_block->file, op_not_block->line);
    SPVM_OP_insert_child(compiler, op_list, op_list->last, op_not_block);
    SPVM_OP_insert_child(compiler, op_block_true, op_block_true->last, op_list);
  }
  op_block_true->uv.block->id = SPVM_BLOCK_C_ID_IF;
  op_block_true->uv.block->no_scope = no_scope;
  
  // Create false block if needed
  if (op_block_false->id != SPVM_OP_C_ID_BLOCK) {
    SPVM_OP* op_not_block = op_block_false;
    
    // Create block
    op_block_false = SPVM_OP_new_op_block(compiler, op_not_block->file, op_not_block->line);
    SPVM_OP* op_list = SPVM_OP_new_op_list(compiler, op_not_block->file, op_not_block->line);
    SPVM_OP_insert_child(compiler, op_list, op_list->last, op_not_block);
    SPVM_OP_insert_child(compiler, op_block_false, op_block_false->last, op_list);
  }
  op_block_false->uv.block->id = SPVM_BLOCK_C_ID_ELSE;
  op_block_false->uv.block->no_scope = no_scope;
  
  SPVM_OP_insert_child(compiler, op_if, op_if->last, op_condition);
  SPVM_OP_insert_child(compiler, op_if, op_if->last, op_block_true);
  SPVM_OP_insert_child(compiler, op_if, op_if->last, op_block_false);
  
  return op_if;
}

SPVM_OP* SPVM_OP_build_array_length(SPVM_COMPILER* compiler, SPVM_OP* op_array_length, SPVM_OP* op_operand) {
  
  SPVM_OP_insert_child(compiler, op_array_length, op_array_length->last, op_operand);
  
  return op_array_length;
}

SPVM_OP* SPVM_OP_build_string_length(SPVM_COMPILER* compiler, SPVM_OP* op_string_length, SPVM_OP* op_operand) {
  
  SPVM_OP_insert_child(compiler, op_string_length, op_string_length->last, op_operand);
  
  return op_string_length;
}

SPVM_OP* SPVM_OP_build_new(SPVM_COMPILER* compiler, SPVM_OP* op_new, SPVM_OP* op_type, SPVM_OP* op_list_elements) {
  
  SPVM_OP_insert_child(compiler, op_new, op_new->last, op_type);
  
  if (op_list_elements) {
    SPVM_OP* op_array_init = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_INIT, op_list_elements->file, op_list_elements->line);
    SPVM_OP_insert_child(compiler, op_array_init, op_array_init->last, op_list_elements);
    SPVM_OP_insert_child(compiler, op_array_init, op_array_init->last, op_type);
    
    return op_array_init;
  }
  
  return op_new;
}

SPVM_OP* SPVM_OP_build_array_init(SPVM_COMPILER* compiler, SPVM_OP* op_array_init, SPVM_OP* op_list_elements, int32_t is_key_values) {

  // Check key value pairs count when {} array init syntax
  if (is_key_values) {
    if (op_list_elements) {
      int32_t element_index = 0;
      SPVM_OP* op_operand_element = op_list_elements->first;
      while ((op_operand_element = SPVM_OP_sibling(compiler, op_operand_element))) {
        if (element_index == 0) {
          // Convert to any object type
          SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_operand_element);
          SPVM_OP* op_type_cast = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE_CAST, op_operand_element->file, op_operand_element->line);
          SPVM_OP* op_dist_type = SPVM_OP_new_op_any_object_type(compiler, op_operand_element->file, op_operand_element->line);
          SPVM_OP_build_type_cast(compiler, op_type_cast, op_dist_type, op_operand_element, NULL);
          SPVM_OP_replace_op(compiler, op_stab, op_type_cast);
          op_operand_element = op_type_cast;
        }
        element_index++;
      }
      int32_t is_odd = element_index % 2 == 1;
      if (is_odd) {
        SPVM_COMPILER_error(compiler, "The lenght of the elements in {} of the array initialization must be an even number.\n  at %s line %d", op_list_elements->file, op_list_elements->line);
      }
    }
  }
  
  SPVM_OP_insert_child(compiler, op_array_init, op_array_init->last, op_list_elements);
  
  return  op_array_init;
}

SPVM_OP* SPVM_OP_build_array_access(SPVM_COMPILER* compiler, SPVM_OP* op_operand_array, SPVM_OP* op_operand_index) {
  
  SPVM_OP* op_array_access = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_ACCESS, op_operand_array->file, op_operand_array->line);
  SPVM_OP_insert_child(compiler, op_array_access, op_array_access->last, op_operand_array);
  SPVM_OP_insert_child(compiler, op_array_access, op_array_access->last, op_operand_index);
  
  return op_array_access;
}

SPVM_OP* SPVM_OP_build_field_access(SPVM_COMPILER* compiler, SPVM_OP* op_field_access, SPVM_OP* op_invocant, SPVM_OP* op_name_field) {
  
  SPVM_OP_insert_child(compiler, op_field_access, op_field_access->last, op_invocant);
  
  SPVM_FIELD_ACCESS* field_access = op_field_access->uv.field_access;
  
  field_access->op_invocant = op_invocant;
  field_access->op_name = op_name_field;

  return op_field_access;
}

SPVM_OP* SPVM_OP_build_can(SPVM_COMPILER* compiler, SPVM_OP* op_can, SPVM_OP* op_var, SPVM_OP* op_name) {
  
  if (op_name->id == SPVM_OP_C_ID_CONSTANT) {
    SPVM_OP* op_constant = op_name;
    SPVM_CONSTANT* constant = op_constant->uv.constant;
    SPVM_TYPE* constant_type = constant->type;
    const char* constant_chars = (const char*)constant->value.oval;
    int32_t is_empty_string = 0;
    if (SPVM_TYPE_is_string_type(compiler, constant_type->basic_type->id, constant_type->dimension, constant_type->flag)) {
      if (strcmp(constant_chars, "") == 0) {
        is_empty_string = 1;
      }
    }
    
    if (!is_empty_string) {
      SPVM_COMPILER_error(compiler, "If the right operand of the can operator is a constant value, it must be an empty string \"\".\n  at %s line %d", op_name->file, op_name->line);
    }
    
    op_name = SPVM_OP_new_op_name(compiler, "", op_name->file, op_name->line);
  }
  
  SPVM_OP_insert_child(compiler, op_can, op_can->last, op_var);
  SPVM_OP_insert_child(compiler, op_can, op_can->last, op_name);

  SPVM_OP* op_name_var_condition = SPVM_OP_new_op_name(compiler, "$.condition_flag", op_var->file, op_var->line);
  SPVM_OP* op_var_condition = SPVM_OP_new_op_var(compiler, op_name_var_condition);
  SPVM_OP* op_assign = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ASSIGN, op_var->file, op_var->line);
  SPVM_OP_build_assign(compiler, op_assign, op_var_condition, op_can);

  return op_assign;
}

SPVM_OP* SPVM_OP_build_is_read_only(SPVM_COMPILER* compiler, SPVM_OP* op_is_read_only, SPVM_OP* op_operand) {
  
  // Build op
  SPVM_OP_insert_child(compiler, op_is_read_only, op_is_read_only->last, op_operand);

  SPVM_OP* op_name_var_condition = SPVM_OP_new_op_name(compiler, "$.condition_flag", op_operand->file, op_operand->line);
  SPVM_OP* op_var_condition = SPVM_OP_new_op_var(compiler, op_name_var_condition);
  SPVM_OP* op_assign = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ASSIGN, op_operand->file, op_operand->line);
  SPVM_OP_build_assign(compiler, op_assign, op_var_condition, op_is_read_only);

  return op_assign;
}

SPVM_OP* SPVM_OP_build_weaken_field(SPVM_COMPILER* compiler, SPVM_OP* op_weaken, SPVM_OP* op_field_access) {
  
  SPVM_OP* op_weaken_field = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_WEAKEN_FIELD, op_weaken->file, op_weaken->line);
  SPVM_OP_insert_child(compiler, op_weaken_field, op_weaken_field->last, op_field_access);
  
  op_field_access->flag |= SPVM_OP_C_FLAG_FIELD_ACCESS_WEAKEN;
  
  return op_weaken_field;
}

SPVM_OP* SPVM_OP_build_unweaken_field(SPVM_COMPILER* compiler, SPVM_OP* op_unweaken, SPVM_OP* op_field_access) {
  
  SPVM_OP* op_unweaken_field = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_UNWEAKEN_FIELD, op_unweaken->file, op_unweaken->line);
  SPVM_OP_insert_child(compiler, op_unweaken_field, op_unweaken_field->last, op_field_access);
  
  op_field_access->flag |= SPVM_OP_C_FLAG_FIELD_ACCESS_UNWEAKEN;
  
  return op_unweaken_field;
}

SPVM_OP* SPVM_OP_build_isweak_field(SPVM_COMPILER* compiler, SPVM_OP* op_isweak, SPVM_OP* op_field_access) {
  
  SPVM_OP* op_isweak_field = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ISWEAK_FIELD, op_isweak->file, op_isweak->line);
  SPVM_OP_insert_child(compiler, op_isweak_field, op_isweak_field->last, op_field_access);
  op_field_access->flag |= SPVM_OP_C_FLAG_FIELD_ACCESS_ISWEAK;

  SPVM_OP* op_name_var = SPVM_OP_new_op_name(compiler, "$.condition_flag", op_field_access->file, op_field_access->line);
  SPVM_OP* op_var = SPVM_OP_new_op_var(compiler, op_name_var);
  SPVM_OP* op_assign = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ASSIGN, op_field_access->file, op_field_access->line);
  SPVM_OP_build_assign(compiler, op_assign, op_var, op_field_access);
  
  return op_assign;
}

SPVM_OP* SPVM_OP_build_type_cast(SPVM_COMPILER* compiler, SPVM_OP* op_type_cast, SPVM_OP* op_type, SPVM_OP* op_operand, SPVM_OP* op_attributes) {
  
  SPVM_OP_insert_child(compiler, op_type_cast, op_type_cast->last, op_operand);
  SPVM_OP_insert_child(compiler, op_type_cast, op_type_cast->last, op_type);
  
  op_type_cast->file = op_type->file;
  op_type_cast->line = op_type->line;

  return op_type_cast;
}

SPVM_OP* SPVM_OP_build_implement(SPVM_COMPILER* compiler, SPVM_OP* op_interface, SPVM_OP* op_name_class) {
  
  SPVM_INTERFACE* interface = SPVM_INTERFACE_new(compiler);
  op_interface->uv.interface = interface;
  interface->op_interface = op_interface;
  interface->class_name = op_name_class->uv.name;
  
  // add use stack
  SPVM_OP* op_use = SPVM_OP_new_op_use(compiler, op_interface->file, op_interface->line);
  SPVM_OP* op_name_class_alias = NULL;
  int32_t is_require = 0;
  SPVM_OP_build_use(compiler, op_use, op_name_class, op_name_class_alias, is_require);
  
  return op_interface;
}

SPVM_OP* SPVM_OP_build_var_decl(SPVM_COMPILER* compiler, SPVM_OP* op_var_decl, SPVM_OP* op_var, SPVM_OP* op_type, SPVM_OP* op_attributes) {
  
  // Declaration
  op_var->uv.var->is_declaration = 1;
  
  // Create var_decl var information
  SPVM_VAR_DECL* var_decl = op_var_decl->uv.var_decl;
  if (op_type) {
    var_decl->type = op_type->uv.type;
  }
  
  // Name OP
  SPVM_OP* op_name = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NAME, op_var->file, op_var->line);
  op_name->uv.name = op_var->uv.var->name;
  var_decl->var = op_var->uv.var;

  op_var->uv.var->var_decl = var_decl;
  
  if (strstr(op_var->uv.var->name, "::")) {
    SPVM_COMPILER_error(compiler, "The local variable \"%s\" cannnot contain \"::\".\n  at %s line %d", op_var->uv.var->name, op_var->file, op_var->line);
  }
  
  return op_var;
}

SPVM_OP* SPVM_OP_build_call_method(SPVM_COMPILER* compiler, SPVM_OP* op_call_method, SPVM_OP* op_invocant, SPVM_OP* op_name_method, SPVM_OP* op_list_operands) {
  
  SPVM_OP_insert_child(compiler, op_call_method, op_call_method->last, op_list_operands);
  
  SPVM_CALL_METHOD* call_method = op_call_method->uv.call_method;
  
  const char* method_name = op_name_method->uv.name;
  
  // Class method call
  if (op_invocant->id == SPVM_OP_C_ID_NAME || op_invocant->id == SPVM_OP_C_ID_CURRENT_CLASS) {
    call_method->is_class_method_call = 1;
    call_method->op_invocant = op_invocant;
    call_method->op_name = op_name_method;
    if (op_invocant->id == SPVM_OP_C_ID_TYPE) {
      op_invocant->flag |= SPVM_OP_C_FLAG_TYPE_IS_MAYBE_CLASS_ALIAS;
    }
  }
  // Instance method call
  else {
    call_method->op_invocant = op_invocant;
    call_method->op_name = op_name_method;
    
    if (op_invocant->id == SPVM_OP_C_ID_VAR) {
      op_invocant->uv.var->call_method = call_method;
    }
    
    SPVM_OP_insert_child(compiler, op_list_operands, op_list_operands->first, op_invocant);
  }
  
  return op_call_method;
}

SPVM_OP* SPVM_OP_build_unary_op(SPVM_COMPILER* compiler, SPVM_OP* op_unary, SPVM_OP* op_first) {
  
  // Build op
  SPVM_OP_insert_child(compiler, op_unary, op_unary->last, op_first);
  
  return op_unary;
}

SPVM_OP* SPVM_OP_build_unary_op_var(SPVM_COMPILER* compiler, SPVM_OP* op_unary, SPVM_OP* op_first) {
  
  const char* op_name = SPVM_OP_get_op_name(compiler, op_unary->id);
  char op_name_lc[16] = {0};
  snprintf(op_name_lc, 16, "%s", op_name);
  for (int32_t i = 0; i < 16; i++) {
    if (op_name_lc[i] != '\0') {
      op_name_lc[i] += ('a' - 'A');
    }
  }
  
  if (op_first->id != SPVM_OP_C_ID_VAR) {
    SPVM_COMPILER_error(compiler, "The operand of the %s operator must be a variable.\n  at %s line %d", op_name_lc, op_first->file, op_first->line);
  }
  
  // Build op
  SPVM_OP_insert_child(compiler, op_unary, op_unary->last, op_first);
  
  return op_unary;
}

SPVM_OP* SPVM_OP_build_comparison_op(SPVM_COMPILER* compiler, SPVM_OP* op_comparison, SPVM_OP* op_first, SPVM_OP* op_last) {

  SPVM_OP_insert_child(compiler, op_comparison, op_comparison->last, op_first);
  SPVM_OP_insert_child(compiler, op_comparison, op_comparison->last, op_last);
  
  SPVM_OP* op_name_var = SPVM_OP_new_op_name(compiler, "$.condition_flag", op_comparison->file, op_comparison->line);
  SPVM_OP* op_var = SPVM_OP_new_op_var(compiler, op_name_var);
  SPVM_OP* op_assign = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ASSIGN, op_comparison->file, op_comparison->line);
  SPVM_OP_build_assign(compiler, op_assign, op_var, op_comparison);
  
  return op_assign;
}

SPVM_OP* SPVM_OP_build_is_type(SPVM_COMPILER* compiler, SPVM_OP* op_is_type, SPVM_OP* op_operand, SPVM_OP* op_type) {
  
  // Build op
  SPVM_OP_insert_child(compiler, op_is_type, op_is_type->last, op_operand);
  SPVM_OP_insert_child(compiler, op_is_type, op_is_type->last, op_type);

  SPVM_OP* op_name_var = SPVM_OP_new_op_name(compiler, "$.condition_flag", op_is_type->file, op_is_type->line);
  SPVM_OP* op_var = SPVM_OP_new_op_var(compiler, op_name_var);
  SPVM_OP* op_assign = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ASSIGN, op_is_type->file, op_is_type->line);
  SPVM_OP_build_assign(compiler, op_assign, op_var, op_is_type);
  
  return op_assign;
}

SPVM_OP* SPVM_OP_build_binary_op(SPVM_COMPILER* compiler, SPVM_OP* op_bin, SPVM_OP* op_first, SPVM_OP* op_last) {
  
  // Build op
  SPVM_OP_insert_child(compiler, op_bin, op_bin->last, op_first);
  SPVM_OP_insert_child(compiler, op_bin, op_bin->last, op_last);
  
  return op_bin;
}

SPVM_OP* SPVM_OP_build_inc(SPVM_COMPILER* compiler, SPVM_OP* op_inc, SPVM_OP* op_first) {
  
  // Build op
  SPVM_OP_insert_child(compiler, op_inc, op_inc->last, op_first);
  
  if (!SPVM_OP_is_mutable(compiler, op_first)) {
    SPVM_COMPILER_error(compiler, "The operand of ++ operator must be mutable.\n  at %s line %d", op_first->file, op_first->line);
  }
  
  return op_inc;
}

SPVM_OP* SPVM_OP_build_dec(SPVM_COMPILER* compiler, SPVM_OP* op_dec, SPVM_OP* op_first) {
  
  // Build op
  SPVM_OP_insert_child(compiler, op_dec, op_dec->last, op_first);

  if (!SPVM_OP_is_mutable(compiler, op_first)) {
    SPVM_COMPILER_error(compiler, "The operand of -- operator must be mutable.\n  at %s line %d", op_first->file, op_first->line);
  }
  
  return op_dec;
}


SPVM_OP* SPVM_OP_build_logical_and(SPVM_COMPILER* compiler, SPVM_OP* op_logical_and, SPVM_OP* op_first, SPVM_OP* op_last) {
  
  // Convert && to if statement
  /* before
    AND
      first
      last
  */
  
  /* after 
    IF              if1
      CONDITION
        first
      IF            if2
        CONDITION
          last
        TYPE_CONVERTION_BOOL
          condition_flag  true
        TYPE_CONVERTION_BOOL
          0               false1
      TYPE_CONVERTION_BOOL
        0                 false2
  */
  
  SPVM_OP* op_if1 = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_IF, op_logical_and->file, op_logical_and->line);
  
  // Constant true
  SPVM_OP* op_name_var_true = SPVM_OP_new_op_name(compiler, "$.condition_flag", op_logical_and->file, op_logical_and->line);
  SPVM_OP* op_var_true = SPVM_OP_new_op_var(compiler, op_name_var_true);
  SPVM_OP* op_assign_bool_true = SPVM_OP_new_op_assign_bool(compiler, op_var_true, op_if1->file, op_if1->line);
  
  // Constant false 1
  SPVM_OP* op_constant_false1 = SPVM_OP_new_op_constant_int(compiler, 0, op_if1->file, op_if1->line);
  SPVM_OP* op_assign_bool_false1 = SPVM_OP_new_op_assign_bool(compiler, op_constant_false1, op_if1->file, op_if1->line);
  
  // Constant false 2
  SPVM_OP* op_constant_false2 = SPVM_OP_new_op_constant_int(compiler, 0, op_if1->file, op_if1->line);
  SPVM_OP* op_assign_bool_false2 = SPVM_OP_new_op_assign_bool(compiler, op_constant_false2, op_if1->file, op_if1->line);
  
  // if2
  SPVM_OP* op_if2 = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_IF, op_if1->file, op_if1->line);
  
  // Build if tree
  int32_t no_scope = 1;
  SPVM_OP_build_if_statement(compiler, op_if2, op_last, op_assign_bool_true, op_assign_bool_false1, no_scope);
  SPVM_OP_build_if_statement(compiler, op_if1, op_first, op_if2, op_assign_bool_false2, no_scope);

  SPVM_OP* op_name_var = SPVM_OP_new_op_name(compiler, "$.condition_flag", op_logical_and->file, op_logical_and->line);
  SPVM_OP* op_var = SPVM_OP_new_op_var(compiler, op_name_var);
  SPVM_OP* op_assign = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ASSIGN, op_logical_and->file, op_logical_and->line);
  SPVM_OP_build_assign(compiler, op_assign, op_var, op_if1);
  
  return op_assign;
}

SPVM_OP* SPVM_OP_build_logical_or(SPVM_COMPILER* compiler, SPVM_OP* op_logical_or, SPVM_OP* op_first, SPVM_OP* op_last) {
  
  // Convert || to if statement
  // before
  //  OR
  //    first
  //    last
  
  // after 
  //  IF      if1
  //    first
  //    TYPE_CONVERTION_BOOL
  //      condition_flag     true1
  //    IF    if2
  //      last
  //      TYPE_CONVERTION_BOOL
  //        condition_flag   true2
  //      TYPE_CONVERTION_BOOL
  //        0                false
  
  SPVM_OP* op_if1 = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_IF, op_logical_or->file, op_logical_or->line);
  
  // Constant true 1
  SPVM_OP* op_name_var_true1 = SPVM_OP_new_op_name(compiler, "$.condition_flag", op_logical_or->file, op_logical_or->line);
  SPVM_OP* op_var_true1 = SPVM_OP_new_op_var(compiler, op_name_var_true1);
  SPVM_OP* op_bool_true1 = SPVM_OP_new_op_assign_bool(compiler, op_var_true1, op_if1->file, op_if1->line);
  
  // Constant true 2
  SPVM_OP* op_name_var_true2 = SPVM_OP_new_op_name(compiler, "$.condition_flag", op_logical_or->file, op_logical_or->line);
  SPVM_OP* op_var_true2 = SPVM_OP_new_op_var(compiler, op_name_var_true2);
  SPVM_OP* op_bool_true2 = SPVM_OP_new_op_assign_bool(compiler, op_var_true2, op_if1->file, op_if1->line);
  
  // Constant false
  SPVM_OP* op_constant_false = SPVM_OP_new_op_constant_int(compiler, 0, op_if1->file, op_if1->line);
  SPVM_OP* op_bool_false = SPVM_OP_new_op_assign_bool(compiler, op_constant_false, op_if1->file, op_if1->line);
  
  // if2
  SPVM_OP* op_if2 = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_IF, op_if1->file, op_if1->line);
  
  // Build if tree
  int32_t no_scope = 1;
  SPVM_OP_build_if_statement(compiler, op_if2, op_last, op_bool_true2, op_bool_false, no_scope);
  SPVM_OP_build_if_statement(compiler, op_if1, op_first, op_bool_true1, op_if2, no_scope);
  
  SPVM_OP* op_name_var = SPVM_OP_new_op_name(compiler, "$.condition_flag", op_logical_or->file, op_logical_or->line);
  SPVM_OP* op_var = SPVM_OP_new_op_var(compiler, op_name_var);
  SPVM_OP* op_assign = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ASSIGN, op_logical_or->file, op_logical_or->line);
  SPVM_OP_build_assign(compiler, op_assign, op_var, op_if1);
  
  return op_assign;
}

SPVM_OP* SPVM_OP_build_logical_not(SPVM_COMPILER* compiler, SPVM_OP* op_not, SPVM_OP* op_first) {
  
  // Convert ! to if statement
  // before
  //  LOGICAL_NOT
  //    first
  
  // after 
  //  IF
  //    first
  //    TYPE_CONVERTION_BOOL
  //      0
  //    TYPE_CONVERTION_BOOL
  //      1
  
  SPVM_OP* op_if = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_IF, op_not->file, op_not->line);
  
  // Constant false
  SPVM_OP* op_constant_false = SPVM_OP_new_op_constant_int(compiler, 0, op_if->file, op_if->line);
  SPVM_OP* op_assign_bool_false = SPVM_OP_new_op_assign_bool(compiler, op_constant_false, op_if->file, op_if->line);

  // Constant true
  SPVM_OP* op_constant_true = SPVM_OP_new_op_constant_int(compiler, 1, op_if->file, op_if->line);
  SPVM_OP* op_assign_bool_true = SPVM_OP_new_op_assign_bool(compiler, op_constant_true, op_if->file, op_if->line);
  
  // Build if tree
  int32_t no_scope = 1;
  SPVM_OP_build_if_statement(compiler, op_if, op_first, op_assign_bool_false, op_assign_bool_true, no_scope);

  SPVM_OP* op_name_var = SPVM_OP_new_op_name(compiler, "$.condition_flag", op_not->file, op_not->line);
  SPVM_OP* op_var = SPVM_OP_new_op_var(compiler, op_name_var);
  SPVM_OP* op_assign = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ASSIGN, op_not->file, op_not->line);
  SPVM_OP_build_assign(compiler, op_assign, op_var, op_if);
  
  return op_assign;
}

SPVM_OP* SPVM_OP_build_special_assign(SPVM_COMPILER* compiler, SPVM_OP* op_special_assign, SPVM_OP* op_operand_dist, SPVM_OP* op_operand_src) {
  
  SPVM_OP_insert_child(compiler, op_special_assign, op_special_assign->last, op_operand_src);
  SPVM_OP_insert_child(compiler, op_special_assign, op_special_assign->last, op_operand_dist);
  
  if (!SPVM_OP_is_mutable(compiler, op_operand_dist)) {
    SPVM_COMPILER_error(compiler, "The left operand of the special assign operator must be mutable.\n  at %s line %d", op_operand_dist->file, op_operand_dist->line);
  }
  
  return op_special_assign;
}

SPVM_OP* SPVM_OP_build_assign(SPVM_COMPILER* compiler, SPVM_OP* op_assign, SPVM_OP* op_operand_dist, SPVM_OP* op_operand_src) {
  
  // Build op
  // Exchange left and right for excecution order
  
  SPVM_OP_insert_child(compiler, op_assign, op_assign->last, op_operand_src);
  SPVM_OP_insert_child(compiler, op_assign, op_assign->last, op_operand_dist);
  
  op_operand_dist->is_dist = 1;
  
  if (!SPVM_OP_is_mutable(compiler, op_operand_dist)) {
    SPVM_COMPILER_error(compiler, "The left operand of the assign operator must be mutable.\n  at %s line %d", op_operand_dist->file, op_operand_dist->line);
  }
  
  return op_assign;
}

SPVM_OP* SPVM_OP_build_return(SPVM_COMPILER* compiler, SPVM_OP* op_return, SPVM_OP* op_operand) {
  
  if (op_operand) {
    SPVM_OP_insert_child(compiler, op_return, op_return->last, op_operand);
  }
  
  return op_return;
}

SPVM_OP* SPVM_OP_build_operator_statement(SPVM_COMPILER* compiler, SPVM_OP* op_operator) {
  
  return op_operator;
}

SPVM_OP* SPVM_OP_build_die(SPVM_COMPILER* compiler, SPVM_OP* op_die, SPVM_OP* op_operand) {
  
  if (!op_operand || op_operand->id == SPVM_OP_C_ID_UNDEF) {
    // Default error message
    op_operand = SPVM_OP_new_op_constant_string(compiler, "Error", strlen("Error"), op_die->file, op_die->line);
  }
  
  // Exception variable
  SPVM_OP* op_exception_var = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_EXCEPTION_VAR, op_operand->file, op_operand->line);
  
  // Assign
  SPVM_OP* op_assign = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ASSIGN, op_operand->file, op_operand->line);
  SPVM_OP_build_assign(compiler, op_assign, op_exception_var, op_operand);
  
  SPVM_OP_insert_child(compiler, op_die, op_die->last, op_assign);

  return op_die;
}

SPVM_OP* SPVM_OP_build_warn(SPVM_COMPILER* compiler, SPVM_OP* op_warn, SPVM_OP* op_operand) {
  
  if (!op_operand || op_operand->id == SPVM_OP_C_ID_UNDEF) {
    // Default warn message
    op_operand = SPVM_OP_new_op_constant_string(compiler, "Warning", strlen("Warning"), op_warn->file, op_warn->line);
  }
  
  SPVM_OP_insert_child(compiler, op_warn, op_warn->last, op_operand);
  
  return op_warn;
}

SPVM_OP* SPVM_OP_build_class_id(SPVM_COMPILER* compiler, SPVM_OP* op_class_id, SPVM_OP* op_name_class) {
  
  SPVM_OP_insert_child(compiler, op_class_id, op_class_id->last, op_name_class);
  
  return op_class_id;
}

SPVM_OP* SPVM_OP_build_set_error_code(SPVM_COMPILER* compiler, SPVM_OP* op_set_error_code, SPVM_OP* op_number) {
  
  SPVM_OP_insert_child(compiler, op_set_error_code, op_set_error_code->last, op_number);
  
  return op_set_error_code;
}

SPVM_OP* SPVM_OP_build_print(SPVM_COMPILER* compiler, SPVM_OP* op_print, SPVM_OP* op_operand) {
  
  SPVM_OP_insert_child(compiler, op_print, op_print->last, op_operand);
  
  return op_print;
}

SPVM_OP* SPVM_OP_build_make_read_only(SPVM_COMPILER* compiler, SPVM_OP* op_make_read_only, SPVM_OP* op_operand) {
  
  SPVM_OP_insert_child(compiler, op_make_read_only, op_make_read_only->last, op_operand);
  
  return op_make_read_only;
}

SPVM_OP* SPVM_OP_build_basic_type(SPVM_COMPILER* compiler, SPVM_OP* op_name) {
  
  const char* name = op_name->uv.name;
  
  SPVM_OP* op_type;
  
  // Add basic type
  SPVM_BASIC_TYPE* found_basic_type = SPVM_HASH_get(compiler->basic_type_symtable, name, strlen(name));
  if (found_basic_type) {
    // Type op
    SPVM_TYPE* type = SPVM_TYPE_new(compiler, found_basic_type->id, 0, 0);
    op_type = SPVM_OP_new_op_type(compiler, type, op_name->file, op_name->line);
  }
  else {
    SPVM_BASIC_TYPE* new_basic_type = SPVM_BASIC_TYPE_new(compiler);
    new_basic_type->id = compiler->basic_types->length;
    new_basic_type->name = name;
    SPVM_LIST_push(compiler->basic_types, new_basic_type);
    SPVM_HASH_set(compiler->basic_type_symtable, new_basic_type->name, strlen(new_basic_type->name), new_basic_type);

    SPVM_TYPE* type = SPVM_TYPE_new(compiler, new_basic_type->id, 0, 0);
    op_type = SPVM_OP_new_op_type(compiler, type, op_name->file, op_name->line);
  }
  
  SPVM_OP_insert_child(compiler, op_type, op_type->last, op_name);

  return op_type;
}

SPVM_OP* SPVM_OP_build_ref_type(SPVM_COMPILER* compiler, SPVM_OP* op_type_original) {
  
  // Type
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, op_type_original->uv.type->basic_type->id, op_type_original->uv.type->dimension, SPVM_NATIVE_C_TYPE_FLAG_REF);
  
  // Type OP
  SPVM_OP* op_type = SPVM_OP_new_op_type(compiler, type, op_type_original->file, op_type_original->line);
  SPVM_OP_insert_child(compiler, op_type, op_type->last, op_type_original);

  return op_type;
}

SPVM_OP* SPVM_OP_build_mutable_type(SPVM_COMPILER* compiler, SPVM_OP* op_type_child) {
  
  // Type
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, op_type_child->uv.type->basic_type->id, op_type_child->uv.type->dimension, op_type_child->uv.type->flag | SPVM_NATIVE_C_TYPE_FLAG_MUTABLE);
  
  // Type OP
  SPVM_OP* op_type = SPVM_OP_new_op_type(compiler, type, op_type_child->file, op_type_child->line);
  
  return op_type;
}

SPVM_OP* SPVM_OP_build_array_type(SPVM_COMPILER* compiler, SPVM_OP* op_type_child, SPVM_OP* op_operand_length) {
  
  // Type
  SPVM_TYPE* type = SPVM_TYPE_new(compiler, op_type_child->uv.type->basic_type->id, op_type_child->uv.type->dimension + 1, 0);
  
  // Type OP
  SPVM_OP* op_type = SPVM_OP_new_op_type(compiler, type, op_type_child->file, op_type_child->line);
  SPVM_OP_insert_child(compiler, op_type, op_type->last, op_type_child);
  
  if (op_operand_length) {
    SPVM_OP_insert_child(compiler, op_type, op_type->last, op_operand_length);
  }
  else {
    SPVM_OP* op_do_nothing = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_DO_NOTHING, op_type_child->file, op_type_child->line);
    SPVM_OP_insert_child(compiler, op_type, op_type->last, op_do_nothing);
  }

  return op_type;
}

SPVM_OP* SPVM_OP_build_any_object_array_type(SPVM_COMPILER* compiler, SPVM_OP* op_element) {
  
  // Type
  SPVM_TYPE* type = SPVM_TYPE_new_any_object_array_type(compiler);
  
  // Type OP
  SPVM_OP* op_type = SPVM_OP_new_op_type(compiler, type, op_element->file, op_element->line);

  return op_type;
}

SPVM_OP* SPVM_OP_new_op_assign_bool(SPVM_COMPILER* compiler, SPVM_OP* op_operand, const char* file, int32_t line) {
  SPVM_OP* op_bool = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_BOOL, file, line);
  SPVM_OP_insert_child(compiler, op_bool, op_bool->last, op_operand);

  SPVM_OP* op_name_var = SPVM_OP_new_op_name(compiler, "$.condition_flag", file, line);
  SPVM_OP* op_var = SPVM_OP_new_op_var(compiler, op_name_var);
  SPVM_OP* op_assign = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ASSIGN, file, line);
  SPVM_OP_build_assign(compiler, op_assign, op_var, op_bool);
  
  return op_assign;
}

SPVM_OP* SPVM_OP_new_op_var_decl(SPVM_COMPILER* compiler, const char* file, int32_t line) {
  SPVM_OP* op_var_decl = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_MY, file, line);
  SPVM_VAR_DECL* var_decl = SPVM_VAR_DECL_new(compiler);
  
  op_var_decl->uv.var_decl = var_decl;
  var_decl->op_var_decl = op_var_decl;
  
  return op_var_decl;
}

SPVM_OP* SPVM_OP_new_op_var_decl_eternal(SPVM_COMPILER* compiler, const char* file, int32_t line) {
  SPVM_OP* op_var_decl = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_MY, file, line);
  SPVM_VAR_DECL* var_decl = SPVM_VAR_DECL_new_eternal(compiler);
  
  op_var_decl->uv.var_decl = var_decl;
  var_decl->op_var_decl = op_var_decl;
  
  return op_var_decl;
}

SPVM_OP* SPVM_OP_new_op_type(SPVM_COMPILER* compiler, SPVM_TYPE* type, const char* file, int32_t line) {
  SPVM_OP* op_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE, file, line);
  op_type->uv.type = type;
  
  SPVM_LIST_push(compiler->op_types, op_type);
  
  return op_type;
}

SPVM_OP* SPVM_OP_new_op_attribute(SPVM_COMPILER* compiler, int32_t id, const char* file, int32_t line) {
  SPVM_OP* op_attribute = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ATTRIBUTE, file, line);
  
  SPVM_ATTRIBUTE* attribute = SPVM_ATTRIBUTE_new(compiler);
  attribute->id = id;
  op_attribute->uv.attribute = attribute;
  
  return op_attribute;
}

SPVM_OP* SPVM_OP_new_op_undef(SPVM_COMPILER* compiler, const char* file, int32_t line) {
  SPVM_OP* op_undef = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_UNDEF, file, line);
  
  return op_undef;
}

SPVM_OP* SPVM_OP_new_op_block(SPVM_COMPILER* compiler, const char* file, int32_t line) {
  SPVM_OP* op_block = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_BLOCK, file, line);
  
  SPVM_BLOCK* block = SPVM_BLOCK_new(compiler);
  op_block->uv.block = block;
  
  return op_block;
}

SPVM_OP* SPVM_OP_new_op_use(SPVM_COMPILER* compiler, const char* file, int32_t line) {
  SPVM_OP* op_use = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_USE, file, line);
  
  SPVM_USE* use = SPVM_USE_new(compiler);
  op_use->uv.use = use;
  
  return op_use;
}

SPVM_OP* SPVM_OP_new_op_name(SPVM_COMPILER* compiler, const char* name, const char* file, int32_t line) {
  
  SPVM_OP* op_name = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NAME, file, line);
  
  SPVM_CONSTANT_STRING* name_string = SPVM_CONSTANT_STRING_new(compiler, name, strlen(name));
  
  name = name_string->value;
  
  op_name->uv.name = name;
  
  return op_name;
}

SPVM_OP* SPVM_OP_new_op_var(SPVM_COMPILER* compiler, SPVM_OP* op_name) {
  
  SPVM_OP* op_var = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_VAR, op_name->file, op_name->line);

  SPVM_VAR* var = SPVM_VAR_new(compiler);
  var->op_name = op_name;
  var->name = op_name->uv.name;
  op_var->uv.var = var;
  
  return op_var;
}

SPVM_OP* SPVM_OP_new_op_class_var_access(SPVM_COMPILER* compiler, SPVM_OP* op_class_var_name) {
  
  const char* class_var_name = op_class_var_name->uv.name;
  
  SPVM_OP* op_class_var_access = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CLASS_VAR_ACCESS, op_class_var_name->file, op_class_var_name->line);

  SPVM_CLASS_VAR_ACCESS* class_var_access = SPVM_CLASS_VAR_ACCESS_new(compiler);
  class_var_access->op_name = op_class_var_name;
  op_class_var_access->uv.class_var_access = class_var_access;
  
  return op_class_var_access;
}

SPVM_OP* SPVM_OP_new_op_var_clone(SPVM_COMPILER* compiler, SPVM_OP* original_op_var, const char* file, int32_t line) {
  (void)compiler;
  
  SPVM_OP* op_name = SPVM_OP_new_op_name(compiler, original_op_var->uv.var->name, file, line);
  SPVM_OP* op_var = SPVM_OP_new_op_var(compiler, op_name);
  SPVM_VAR* var = op_var->uv.var;
  
  var->var_decl = original_op_var->uv.var->var_decl;
  
  return op_var;
}

SPVM_OP* SPVM_OP_new_op_var_clone_var_or_assign(SPVM_COMPILER* compiler, SPVM_OP* original_op_var_or_assign) {
  (void)compiler;
  
  SPVM_OP* original_op_var;
  if (original_op_var_or_assign->id == SPVM_OP_C_ID_ASSIGN) {
    if (original_op_var_or_assign->last->id == SPVM_OP_C_ID_VAR) {
      original_op_var = original_op_var_or_assign->last;
    }
    else {
      assert(0);
    }
  }
  else if (original_op_var_or_assign->id == SPVM_OP_C_ID_VAR) {
    original_op_var = original_op_var_or_assign;
  }
  else {
    assert(0);
  }
  
  SPVM_OP* op_var = SPVM_OP_new_op_var_clone(compiler, original_op_var, original_op_var_or_assign->file, original_op_var_or_assign->line);
  return op_var;
}


SPVM_OP* SPVM_OP_new_op_field_access_clone(SPVM_COMPILER* compiler, SPVM_OP* original_op_field_access) {
  (void)compiler;
  
  SPVM_OP* op_var_invoker = SPVM_OP_new_op_var_clone_var_or_assign(compiler, original_op_field_access->first);
  
  SPVM_OP* op_field_access = SPVM_OP_new_op_field_access(compiler, original_op_field_access->file, original_op_field_access->line);

  SPVM_OP* op_name_field = SPVM_OP_new_op_name(compiler, original_op_field_access->uv.field_access->op_name->uv.name, original_op_field_access->file, original_op_field_access->line);
  SPVM_OP_build_field_access(compiler, op_field_access, op_var_invoker, op_name_field);
  
  op_field_access->uv.field_access->op_invocant = original_op_field_access->uv.field_access->op_invocant;
  op_field_access->uv.field_access->op_name = original_op_field_access->uv.field_access->op_name;
  op_field_access->uv.field_access->field = original_op_field_access->uv.field_access->field;
  op_field_access->uv.field_access->inline_expansion = original_op_field_access->uv.field_access->inline_expansion;

  return op_field_access;
}

SPVM_OP* SPVM_OP_new_op_array_access_clone(SPVM_COMPILER* compiler, SPVM_OP* original_op_array_access) {
  (void)compiler;
  
  SPVM_OP* op_var_array = SPVM_OP_new_op_var_clone_var_or_assign(compiler, original_op_array_access->first);
  SPVM_OP* op_var_index = SPVM_OP_new_op_var_clone_var_or_assign(compiler, original_op_array_access->last);
  
  SPVM_OP* op_array_access = SPVM_OP_build_array_access(compiler, op_var_array, op_var_index);
  
  return op_array_access;
}

SPVM_OP* SPVM_OP_new_op_array_field_access(SPVM_COMPILER* compiler, const char* file, int32_t line) {
  (void)compiler;
  
  SPVM_OP* op_array_field_access = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_FIELD_ACCESS, file, line);
  
  SPVM_ARRAY_FIELD_ACCESS* array_field_access = SPVM_ARRAY_FIELD_ACCESS_new(compiler);
  
  op_array_field_access->uv.array_field_access = array_field_access;
  
  return op_array_field_access;
}

SPVM_OP* SPVM_OP_new_op_array_field_access_clone(SPVM_COMPILER* compiler, SPVM_OP* original_op_array_field_access) {
  (void)compiler;
  
  SPVM_OP* op_array_field_access = SPVM_OP_new_op_array_field_access(compiler, original_op_array_field_access->file, original_op_array_field_access->line);
  
  SPVM_OP* op_var_array = SPVM_OP_new_op_var_clone_var_or_assign(compiler, original_op_array_field_access->first);
  SPVM_OP* op_var_index = SPVM_OP_new_op_var_clone_var_or_assign(compiler, original_op_array_field_access->last);

  SPVM_OP_insert_child(compiler, op_array_field_access, op_array_field_access->last, op_var_array);
  SPVM_OP_insert_child(compiler, op_array_field_access, op_array_field_access->last, op_var_index);
  
  op_array_field_access->uv.array_field_access->field = original_op_array_field_access->uv.array_field_access->field;
  
  return op_array_field_access;
}

SPVM_OP* SPVM_OP_new_op_class_var_access_clone(SPVM_COMPILER* compiler, SPVM_OP* original_op_class_var_access) {
  (void)compiler;
  
  SPVM_CLASS_VAR_ACCESS* oritinal_class_var_access = original_op_class_var_access->uv.class_var_access;

  const char* class_var_name = oritinal_class_var_access->op_name->uv.name;
  
  SPVM_OP* op_class_var_name = SPVM_OP_new_op_name(compiler, class_var_name, original_op_class_var_access->file, original_op_class_var_access->line);
  
  SPVM_OP* op_class_var_access = SPVM_OP_new_op_class_var_access(compiler, op_class_var_name);

  return op_class_var_access;
}

SPVM_OP* SPVM_OP_new_op_deref_clone(SPVM_COMPILER* compiler, SPVM_OP* original_op_deref) {
  (void)compiler;
  
  SPVM_OP* op_deref = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_DEREF, original_op_deref->file, original_op_deref->line);
  
  SPVM_OP* op_var = SPVM_OP_new_op_var_clone_var_or_assign(compiler, original_op_deref->first);
  
  SPVM_OP_build_unary_op(compiler, op_deref, op_var);
  
  return op_deref;
}

SPVM_OP* SPVM_OP_new_op_operand_mutable_clone(SPVM_COMPILER* compiler, SPVM_OP* original_op_operand_mutable) {
  
  SPVM_OP* op_operand_mutable;
  switch (original_op_operand_mutable->id) {
    case SPVM_OP_C_ID_VAR: {
      op_operand_mutable = SPVM_OP_new_op_var_clone(compiler, original_op_operand_mutable, original_op_operand_mutable->file, original_op_operand_mutable->line);
      break;
    }
    case SPVM_OP_C_ID_CLASS_VAR_ACCESS: {
      op_operand_mutable = SPVM_OP_new_op_class_var_access_clone(compiler, original_op_operand_mutable);
      break;
    }
    case SPVM_OP_C_ID_ARRAY_ACCESS: {
      op_operand_mutable = SPVM_OP_new_op_array_access_clone(compiler, original_op_operand_mutable);
      break;
    }
    case SPVM_OP_C_ID_FIELD_ACCESS: {
      op_operand_mutable = SPVM_OP_new_op_field_access_clone(compiler, original_op_operand_mutable);
      break;
    }
    case SPVM_OP_C_ID_ARRAY_FIELD_ACCESS: {
      op_operand_mutable = SPVM_OP_new_op_array_field_access_clone(compiler, original_op_operand_mutable);
      break;
    }
    case SPVM_OP_C_ID_DEREF: {
      op_operand_mutable = SPVM_OP_new_op_deref_clone(compiler, original_op_operand_mutable);
      break;
    }
    default: {
      assert(0);
    }
  }
  
  return op_operand_mutable;
}

SPVM_OP* SPVM_OP_new_op_constant(SPVM_COMPILER* compiler, const char* file, int32_t line) {
  SPVM_OP* op_constant = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CONSTANT, file, line);
  SPVM_CONSTANT* constant = SPVM_CONSTANT_new(compiler);
  assert(constant);
  op_constant->uv.constant = constant;
  constant->op_constant = op_constant;
  
  return op_constant;
}

SPVM_OP* SPVM_OP_new_op_constant_byte(SPVM_COMPILER* compiler, int8_t value, const char* file, int32_t line) {
  SPVM_OP* op_constant = SPVM_OP_new_op_constant(compiler, file, line);
  SPVM_CONSTANT* constant = op_constant->uv.constant;
  
  constant->value.bval = value;
  SPVM_OP* op_constant_type = SPVM_OP_new_op_byte_type(compiler, file, line);
  constant->type = op_constant_type->uv.type;
  
  return op_constant;
}

SPVM_OP* SPVM_OP_new_op_constant_short(SPVM_COMPILER* compiler, int16_t value, const char* file, int32_t line) {
  SPVM_OP* op_constant = SPVM_OP_new_op_constant(compiler, file, line);
  SPVM_CONSTANT* constant = op_constant->uv.constant;
  
  constant->value.sval = value;
  SPVM_OP* op_constant_type = SPVM_OP_new_op_short_type(compiler, file, line);
  constant->type = op_constant_type->uv.type;
  
  return op_constant;
}

SPVM_OP* SPVM_OP_new_op_constant_int(SPVM_COMPILER* compiler, int32_t value, const char* file, int32_t line) {
  SPVM_OP* op_constant = SPVM_OP_new_op_constant(compiler, file, line);
  SPVM_CONSTANT* constant = op_constant->uv.constant;
  
  assert(op_constant->uv.constant);
  
  constant->value.ival = value;
  SPVM_OP* op_constant_type = SPVM_OP_new_op_int_type(compiler, file, line);
  constant->type = op_constant_type->uv.type;
  
  return op_constant;
}

SPVM_OP* SPVM_OP_new_op_constant_long(SPVM_COMPILER* compiler, int64_t value, const char* file, int32_t line) {
  SPVM_OP* op_constant = SPVM_OP_new_op_constant(compiler, file, line);
  SPVM_CONSTANT* constant = op_constant->uv.constant;
  
  constant->value.lval = value;
  SPVM_OP* op_constant_type = SPVM_OP_new_op_long_type(compiler, file, line);
  constant->type = op_constant_type->uv.type;
  
  return op_constant;
}

SPVM_OP* SPVM_OP_new_op_constant_float(SPVM_COMPILER* compiler, float value, const char* file, int32_t line) {
  SPVM_OP* op_constant = SPVM_OP_new_op_constant(compiler, file, line);
  SPVM_CONSTANT* constant = op_constant->uv.constant;
  
  constant->value.fval = value;
  SPVM_OP* op_constant_type = SPVM_OP_new_op_float_type(compiler, file, line);
  constant->type = op_constant_type->uv.type;
  
  return op_constant;
}

SPVM_OP* SPVM_OP_new_op_constant_double(SPVM_COMPILER* compiler, double value, const char* file, int32_t line) {
  SPVM_OP* op_constant = SPVM_OP_new_op_constant(compiler, file, line);
  SPVM_CONSTANT* constant = op_constant->uv.constant;
  
  constant->value.dval = value;
  SPVM_OP* op_constant_type = SPVM_OP_new_op_double_type(compiler, file, line);
  constant->type = op_constant_type->uv.type;
  
  return op_constant;
}

SPVM_OP* SPVM_OP_new_op_constant_string(SPVM_COMPILER* compiler, const char* string, int32_t length, const char* file, int32_t line) {

  SPVM_OP* op_constant = SPVM_OP_new_op_constant(compiler, file, line);
  SPVM_CONSTANT* constant = op_constant->uv.constant;
  
  SPVM_CONSTANT_STRING* cached_string_string = SPVM_CONSTANT_STRING_new(compiler, string, length);
  const char* cached_string = cached_string_string->value;

  constant->value.oval = (void*)cached_string;
  SPVM_OP* op_constant_type = SPVM_OP_new_op_string_type(compiler, file, line);
  constant->type = op_constant_type->uv.type;
  constant->string_length = length;
  
  return op_constant;
}

SPVM_OP* SPVM_OP_new_op_void_type(SPVM_COMPILER* compiler, const char* file, int32_t line) {
  SPVM_TYPE* type = SPVM_TYPE_new_void_type(compiler);
  SPVM_OP* op_type = SPVM_OP_new_op_type(compiler, type, file, line);
  
  return op_type;
}

SPVM_OP* SPVM_OP_new_op_byte_type(SPVM_COMPILER* compiler, const char* file, int32_t line) {
  SPVM_TYPE* type = SPVM_TYPE_new_byte_type(compiler);
  SPVM_OP* op_type = SPVM_OP_new_op_type(compiler, type, file, line);
  
  return op_type;
}

SPVM_OP* SPVM_OP_new_op_short_type(SPVM_COMPILER* compiler, const char* file, int32_t line) {
  SPVM_TYPE* type = SPVM_TYPE_new_short_type(compiler);
  SPVM_OP* op_type = SPVM_OP_new_op_type(compiler, type, file, line);
  
  return op_type;
}

SPVM_OP* SPVM_OP_new_op_int_type(SPVM_COMPILER* compiler, const char* file, int32_t line) {
  SPVM_TYPE* type = SPVM_TYPE_new_int_type(compiler);
  SPVM_OP* op_type = SPVM_OP_new_op_type(compiler, type, file, line);
  
  return op_type;
}

SPVM_OP* SPVM_OP_new_op_bool_object_type(SPVM_COMPILER* compiler, const char* file, int32_t line) {
  SPVM_TYPE* type = SPVM_TYPE_new_bool_object_type(compiler);
  SPVM_OP* op_type = SPVM_OP_new_op_type(compiler, type, file, line);
  
  return op_type;
}

SPVM_OP* SPVM_OP_new_op_long_type(SPVM_COMPILER* compiler, const char* file, int32_t line) {
  SPVM_TYPE* type = SPVM_TYPE_new_long_type(compiler);
  SPVM_OP* op_type = SPVM_OP_new_op_type(compiler, type, file, line);
  
  return op_type;
}

SPVM_OP* SPVM_OP_new_op_float_type(SPVM_COMPILER* compiler, const char* file, int32_t line) {
  SPVM_TYPE* type = SPVM_TYPE_new_float_type(compiler);
  SPVM_OP* op_type = SPVM_OP_new_op_type(compiler, type, file, line);
  
  return op_type;
}

SPVM_OP* SPVM_OP_new_op_double_type(SPVM_COMPILER* compiler, const char* file, int32_t line) {
  SPVM_TYPE* type = SPVM_TYPE_new_double_type(compiler);
  SPVM_OP* op_type = SPVM_OP_new_op_type(compiler, type, file, line);
  
  return op_type;
}

SPVM_OP* SPVM_OP_new_op_string_type(SPVM_COMPILER* compiler, const char* file, int32_t line) {
  SPVM_TYPE* type = SPVM_TYPE_new_string_type(compiler);
  SPVM_OP* op_type = SPVM_OP_new_op_type(compiler, type, file, line);
  
  return op_type;
}

SPVM_OP* SPVM_OP_new_op_undef_type(SPVM_COMPILER* compiler, const char* file, int32_t line) {
  SPVM_TYPE* type = SPVM_TYPE_new_undef_type(compiler);
  SPVM_OP* op_type = SPVM_OP_new_op_type(compiler, type, file, line);
  
  return op_type;
}

SPVM_OP* SPVM_OP_new_op_byte_ref_type(SPVM_COMPILER* compiler, const char* file, int32_t line) {
  SPVM_TYPE* type = SPVM_TYPE_new_byte_ref_type(compiler);
  SPVM_OP* op_type = SPVM_OP_new_op_type(compiler, type, file, line);
  
  return op_type;
}

SPVM_OP* SPVM_OP_new_op_short_ref_type(SPVM_COMPILER* compiler, const char* file, int32_t line) {
  SPVM_TYPE* type = SPVM_TYPE_new_short_ref_type(compiler);
  SPVM_OP* op_type = SPVM_OP_new_op_type(compiler, type, file, line);
  
  return op_type;
}

SPVM_OP* SPVM_OP_new_op_int_ref_type(SPVM_COMPILER* compiler, const char* file, int32_t line) {
  SPVM_TYPE* type = SPVM_TYPE_new_int_ref_type(compiler);
  SPVM_OP* op_type = SPVM_OP_new_op_type(compiler, type, file, line);
  
  return op_type;
}

SPVM_OP* SPVM_OP_new_op_long_ref_type(SPVM_COMPILER* compiler, const char* file, int32_t line) {
  SPVM_TYPE* type = SPVM_TYPE_new_long_ref_type(compiler);
  SPVM_OP* op_type = SPVM_OP_new_op_type(compiler, type, file, line);
  
  return op_type;
}

SPVM_OP* SPVM_OP_new_op_float_ref_type(SPVM_COMPILER* compiler, const char* file, int32_t line) {
  SPVM_TYPE* type = SPVM_TYPE_new_float_ref_type(compiler);
  SPVM_OP* op_type = SPVM_OP_new_op_type(compiler, type, file, line);
  
  return op_type;
}

SPVM_OP* SPVM_OP_new_op_double_ref_type(SPVM_COMPILER* compiler, const char* file, int32_t line) {
  SPVM_TYPE* type = SPVM_TYPE_new_double_ref_type(compiler);
  SPVM_OP* op_type = SPVM_OP_new_op_type(compiler, type, file, line);
  
  return op_type;
}

SPVM_OP* SPVM_OP_new_op_any_object_type(SPVM_COMPILER* compiler, const char* file, int32_t line) {
  SPVM_TYPE* type = SPVM_TYPE_new_any_object_type(compiler);
  SPVM_OP* op_type = SPVM_OP_new_op_type(compiler, type, file, line);
  
  return op_type;
}

SPVM_OP* SPVM_OP_new_op_true(SPVM_COMPILER* compiler, SPVM_OP* op) {
  
  SPVM_CONSTANT_STRING* class_var_name_string = SPVM_CONSTANT_STRING_new(compiler, "$Bool::TRUE", strlen("$Bool::TRUE"));
  const char* class_var_name = class_var_name_string->value;
  SPVM_OP* op_class_var_name = SPVM_OP_new_op_name(compiler, class_var_name, op->file, op->line);
  SPVM_OP* op_class_var_access = SPVM_OP_new_op_class_var_access(compiler, op_class_var_name);
  op_class_var_access->uv.class_var_access->inline_expansion = 1;

  return op_class_var_access;
}

SPVM_OP* SPVM_OP_new_op_false(SPVM_COMPILER* compiler, SPVM_OP* op) {
  
  SPVM_CONSTANT_STRING* class_var_name_string = SPVM_CONSTANT_STRING_new(compiler, "$Bool::FALSE", strlen("$Bool::FALSE"));
  const char* class_var_name = class_var_name_string->value;
  SPVM_OP* op_class_var_name = SPVM_OP_new_op_name(compiler, class_var_name, op->file, op->line);
  SPVM_OP* op_class_var_access = SPVM_OP_new_op_class_var_access(compiler, op_class_var_name);
  op_class_var_access->uv.class_var_access->inline_expansion = 1;
  
  return op_class_var_access;
}

SPVM_OP* SPVM_OP_new_op_field_access(SPVM_COMPILER* compiler, const char* file, int32_t line) {
  SPVM_OP* op_field_access = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_FIELD_ACCESS, file, line);
  
  SPVM_FIELD_ACCESS* field_access = SPVM_FIELD_ACCESS_new(compiler);

  op_field_access->uv.field_access = field_access;
  
  return op_field_access;
}

SPVM_OP* SPVM_OP_new_op_call_method(SPVM_COMPILER* compiler, const char* file, int32_t line) {

  SPVM_OP* op_call_method = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CALL_METHOD, file, line);
  
  SPVM_CALL_METHOD* call_method = SPVM_CALL_METHOD_new(compiler);
  
  op_call_method->uv.call_method = call_method;
  
  return op_call_method;
}

SPVM_OP* SPVM_OP_new_op_list(SPVM_COMPILER* compiler, const char* file, int32_t line) {
  
  SPVM_OP* op_pushmark = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PUSHMARK, file, line);
  
  SPVM_OP* op_list = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_LIST, file, line);
  SPVM_OP_insert_child(compiler, op_list, op_list->last, op_pushmark);
  
  return op_list;
}

SPVM_OP* SPVM_OP_new_op_var_tmp(SPVM_COMPILER* compiler, SPVM_TYPE* type, const char* file, int32_t line) {
  
  // Temparary variable name
  char* name = SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->allocator, strlen("$.tmp_2147483647") + 1);
  sprintf(name, "$.tmp_%d", compiler->tmp_vars_length);
  compiler->tmp_vars_length++;
  SPVM_OP* op_name = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NAME, file, line);
  op_name->uv.name = name;
  SPVM_OP* op_var = SPVM_OP_build_var(compiler, op_name);
  SPVM_OP* op_var_decl = SPVM_OP_new_op_var_decl(compiler, file, line);
  assert(type);
  SPVM_OP* op_type = SPVM_OP_new_op_type(compiler, type, file, line);
  
  SPVM_OP_build_var_decl(compiler, op_var_decl, op_var, op_type, NULL);
  
  op_var->uv.var->is_initialized = 1;
  
  return op_var;
}

SPVM_OP* SPVM_OP_new_op_name_tmp_var(SPVM_COMPILER* compiler, const char* file, int32_t line) {
  
  // Temparary variable name
  char* name = SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->allocator, strlen("$.op2147483647") + 1);
  sprintf(name, "$.op%d", compiler->tmp_vars_length);
  compiler->tmp_vars_length++;
  SPVM_OP* op_name = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NAME, file, line);
  op_name->uv.name = name;
  
  return op_name;
}

SPVM_OP* SPVM_OP_new_op(SPVM_COMPILER* compiler, int32_t id, const char* file, int32_t line) {

  SPVM_OP *op = SPVM_ALLOCATOR_alloc_memory_block_tmp(compiler->allocator, sizeof(SPVM_OP));
  
  memset(op, 0, sizeof(SPVM_OP));
  
  op->id = id;
  
  assert(!op->file);
  assert(!op->line);
  
  op->file = file;
  op->line = line;
  
  SPVM_LIST_push(compiler->ops, op);
  
  return op;
}

int32_t SPVM_OP_is_allowed(SPVM_COMPILER* compiler, SPVM_CLASS* class_current, SPVM_CLASS* class_dist) {
  (void)compiler;
  
  SPVM_LIST* allows = class_dist->allows;
  
  const char* current_class_name = class_current->name;
  const char* dist_class_name = class_dist->name;
  
  int32_t is_allowed = 0;
  if (strcmp(current_class_name, dist_class_name) == 0) {
    is_allowed = 1;
  }
  else {
    for (int32_t i = 0; i < allows->length; i++) {
      SPVM_ALLOW* allow = SPVM_LIST_get(allows, i);
      const char* allow_basic_type_name = allow->class_name;
      if (strcmp(current_class_name, allow_basic_type_name) == 0) {
        is_allowed = 1;
        break;
      }
    }
  }
  
  return is_allowed;
}

int32_t SPVM_OP_is_mutable(SPVM_COMPILER* compiler, SPVM_OP* op) {
  (void)compiler;
  
  switch (op->id) {
    case SPVM_OP_C_ID_VAR:
    case SPVM_OP_C_ID_CLASS_VAR_ACCESS:
    case SPVM_OP_C_ID_ARRAY_ACCESS:
    case SPVM_OP_C_ID_FIELD_ACCESS:
    case SPVM_OP_C_ID_DEREF:
    case SPVM_OP_C_ID_EXCEPTION_VAR:
    case SPVM_OP_C_ID_ARRAY_FIELD_ACCESS:
      return 1;
  }
  
  return 0;
}

int32_t SPVM_OP_is_rel_op(SPVM_COMPILER* compiler, SPVM_OP* op) {
  (void)compiler;
  
  switch (op->id) {
    case SPVM_OP_C_ID_NUMERIC_EQ:
    case SPVM_OP_C_ID_NUMERIC_NE:
    case SPVM_OP_C_ID_NUMERIC_GT:
    case SPVM_OP_C_ID_NUMERIC_GE:
    case SPVM_OP_C_ID_NUMERIC_LT:
    case SPVM_OP_C_ID_NUMERIC_LE:
    case SPVM_OP_C_ID_NUMERIC_CMP:
    case SPVM_OP_C_ID_STRING_EQ:
    case SPVM_OP_C_ID_STRING_NE:
    case SPVM_OP_C_ID_STRING_GT:
    case SPVM_OP_C_ID_STRING_GE:
    case SPVM_OP_C_ID_STRING_LT:
    case SPVM_OP_C_ID_STRING_LE:
    case SPVM_OP_C_ID_STRING_CMP:
    case SPVM_OP_C_ID_ISA:
    case SPVM_OP_C_ID_IS_TYPE:
    {
      return 1;
    }
  }
  
  return 0;
}

SPVM_OP* SPVM_OP_get_parent(SPVM_COMPILER* compiler, SPVM_OP* op_target) {
  (void)compiler;
  
  SPVM_OP* op_parent;
  SPVM_OP* op_cur = op_target;
  while (1) {
    if (op_cur->moresib) {
      op_cur = op_cur->sibparent;
    }
    else {
      op_parent = op_cur->sibparent;
      break;
    }
  }
  
  return op_parent;
}

void SPVM_OP_get_before(SPVM_COMPILER* compiler, SPVM_OP* op_target, SPVM_OP** op_before_ptr, int32_t* next_is_child_ptr) {

  // Get parent
  SPVM_OP* op_parent = SPVM_OP_get_parent(compiler, op_target);
  
  SPVM_OP* op_before;
  int32_t next_is_child = 0;
  if (op_parent->first == op_target) {
    op_before = op_parent;
    next_is_child = 1;
  }
  else {
    op_before = op_parent->first;
    while (1) {
      if (op_before->sibparent == op_target) {
        break;
      }
      else {
        op_before = op_before->sibparent;
      }
    }
  }
  
  *op_before_ptr = op_before;
  *next_is_child_ptr = next_is_child;
}

// Replace target op with replace op
void SPVM_OP_replace_op(SPVM_COMPILER* compiler, SPVM_OP* op_target, SPVM_OP* op_replace) {
  (void)compiler;
  
  // Get parent op
  SPVM_OP* op_parent = SPVM_OP_get_parent(compiler, op_target);
  
  int32_t op_target_is_last_child = op_parent->last == op_target;

  // Get before op
  int32_t next_is_child;
  SPVM_OP* op_before;
  SPVM_OP_get_before(compiler, op_target, &op_before, &next_is_child);
  
  // Stab
  if (next_is_child) {
    // One child
    if (op_before->first == op_before->last) {
      op_before->first = op_replace;
      op_before->last = op_replace;
    }
    // More
    else {
      op_before->first = op_replace;
    }
  }
  else {
    op_before->sibparent = op_replace;
  }
  op_replace->moresib = op_target->moresib;
  op_replace->sibparent = op_target->sibparent;

  if (op_target_is_last_child) {
    op_parent->last = op_replace;
  }
}

// Cut op and insert stab into original position and return stab
SPVM_OP* SPVM_OP_cut_op(SPVM_COMPILER* compiler, SPVM_OP* op_target) {
  // Get parent op
  SPVM_OP* op_parent = SPVM_OP_get_parent(compiler, op_target);
  
  int32_t op_target_is_last_child = op_parent->last == op_target;

  // Get before op
  int32_t next_is_child;
  SPVM_OP* op_before;
  SPVM_OP_get_before(compiler, op_target, &op_before, &next_is_child);
  
  // Stab
  SPVM_OP* op_stab = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_DO_NOTHING, op_target->file, op_target->line);
  if (next_is_child) {
    
    // One child
    if (op_before->first == op_before->last) {
      op_before->first = op_stab;
      op_before->last = op_stab;
    }
    // More
    else {
      op_before->first = op_stab;
    }
  }
  else {
    op_before->sibparent = op_stab;
  }
  op_stab->moresib = op_target->moresib;
  op_stab->sibparent = op_target->sibparent;

  // Clear target
  op_target->moresib = 0;
  op_target->sibparent = NULL;
  
  if (op_target_is_last_child) {
    op_parent->last = op_stab;
  }
  
  return op_stab;
}

SPVM_TYPE* SPVM_OP_get_type(SPVM_COMPILER* compiler, SPVM_OP* op) {
  
  SPVM_TYPE*  type = NULL;
  
  switch (op->id) {
    case SPVM_OP_C_ID_TRUE:
    case SPVM_OP_C_ID_FALSE:
    {
      type = SPVM_TYPE_new_bool_object_type(compiler);
      break;
    }
    case SPVM_OP_C_ID_RETURN:
    case SPVM_OP_C_ID_LOOP_INCREMENT:
    case SPVM_OP_C_ID_CONDITION:
    case SPVM_OP_C_ID_CONDITION_NOT:
    case SPVM_OP_C_ID_SWITCH:
    case SPVM_OP_C_ID_DEFAULT:
    case SPVM_OP_C_ID_CASE:
    case SPVM_OP_C_ID_LAST:
    case SPVM_OP_C_ID_NEXT:
    case SPVM_OP_C_ID_BREAK:
    case SPVM_OP_C_ID_DIE:
    case SPVM_OP_C_ID_WARN:
    case SPVM_OP_C_ID_PRINT:
    case SPVM_OP_C_ID_SAY:
    case SPVM_OP_C_ID_MAKE_READ_ONLY:
    {
      // Dummy int variable
      type = SPVM_TYPE_new_int_type(compiler);
      break;
    }
    case SPVM_OP_C_ID_CLASS: {
      SPVM_CLASS* class = op->uv.class;
      type = class->type;
      break;
    }
    case SPVM_OP_C_ID_NUMERIC_EQ:
    case SPVM_OP_C_ID_NUMERIC_NE:
    case SPVM_OP_C_ID_NUMERIC_GT:
    case SPVM_OP_C_ID_NUMERIC_GE:
    case SPVM_OP_C_ID_NUMERIC_LT:
    case SPVM_OP_C_ID_NUMERIC_LE:
    case SPVM_OP_C_ID_NUMERIC_CMP:
    case SPVM_OP_C_ID_BOOL:
    case SPVM_OP_C_ID_STRING_EQ:
    case SPVM_OP_C_ID_STRING_NE:
    case SPVM_OP_C_ID_STRING_GT:
    case SPVM_OP_C_ID_STRING_GE:
    case SPVM_OP_C_ID_STRING_LT:
    case SPVM_OP_C_ID_STRING_LE:
    case SPVM_OP_C_ID_STRING_CMP:
    case SPVM_OP_C_ID_ISA:
    case SPVM_OP_C_ID_IS_TYPE:
    case SPVM_OP_C_ID_IF:
    case SPVM_OP_C_ID_ISWEAK_FIELD:
    case SPVM_OP_C_ID_IS_READ_ONLY:
    case SPVM_OP_C_ID_CAN:
    case SPVM_OP_C_ID_CLASS_ID:
    case SPVM_OP_C_ID_ERROR_CODE:
    case SPVM_OP_C_ID_SET_ERROR_CODE:
    case SPVM_OP_C_ID_ERROR:
    case SPVM_OP_C_ID_ITEMS:
    {
      type = SPVM_TYPE_new_int_type(compiler);
      break;
    }
    case SPVM_OP_C_ID_ARRAY_LENGTH:
    case SPVM_OP_C_ID_STRING_LENGTH:
    case SPVM_OP_C_ID_REFCNT:
    {
      type = SPVM_TYPE_new_int_type(compiler);
      break;
    }
    case SPVM_OP_C_ID_ARRAY_ACCESS: {
      SPVM_TYPE* first_type = SPVM_OP_get_type(compiler, op->first);
      SPVM_BASIC_TYPE* basic_type = SPVM_HASH_get(compiler->basic_type_symtable, first_type->basic_type->name, strlen(first_type->basic_type->name));
      if (SPVM_TYPE_is_string_type(compiler, basic_type->id, first_type->dimension, 0)) {
        type = SPVM_TYPE_new_byte_type(compiler);
      }
      else if (SPVM_TYPE_is_any_object_array_type(compiler, basic_type->id, first_type->dimension, 0)) {
        type = SPVM_TYPE_new_any_object_type(compiler);
      }
      else {
        type = SPVM_TYPE_new(compiler, basic_type->id, first_type->dimension - 1, 0);
      }
      
      break;
    }
    case SPVM_OP_C_ID_ADD:
    case SPVM_OP_C_ID_SUBTRACT:
    case SPVM_OP_C_ID_MULTIPLY:
    case SPVM_OP_C_ID_DIVIDE:
    case SPVM_OP_C_ID_DIVIDE_UNSIGNED_INT:
    case SPVM_OP_C_ID_DIVIDE_UNSIGNED_LONG:
    case SPVM_OP_C_ID_REMAINDER:
    case SPVM_OP_C_ID_REMAINDER_UNSIGNED_INT:
    case SPVM_OP_C_ID_REMAINDER_UNSIGNED_LONG:
    case SPVM_OP_C_ID_INC:
    case SPVM_OP_C_ID_PRE_INC:
    case SPVM_OP_C_ID_POST_INC:
    case SPVM_OP_C_ID_DEC:
    case SPVM_OP_C_ID_PRE_DEC:
    case SPVM_OP_C_ID_POST_DEC:
    case SPVM_OP_C_ID_LEFT_SHIFT:
    case SPVM_OP_C_ID_RIGHT_ARITHMETIC_SHIFT:
    case SPVM_OP_C_ID_RIGHT_LOGICAL_SHIFT:
    case SPVM_OP_C_ID_BIT_XOR:
    case SPVM_OP_C_ID_BIT_OR:
    case SPVM_OP_C_ID_BIT_AND:
    case SPVM_OP_C_ID_BIT_NOT:
    case SPVM_OP_C_ID_PLUS:
    case SPVM_OP_C_ID_MINUS:
    case SPVM_OP_C_ID_NEW:
    case SPVM_OP_C_ID_CHECK_CONVERT:
    case SPVM_OP_C_ID_ARRAY_INIT:
    case SPVM_OP_C_ID_COPY:
    case SPVM_OP_C_ID_CUT:
    {
      type = SPVM_OP_get_type(compiler, op->first);
      break;
    }
    case SPVM_OP_C_ID_LIST:
    case SPVM_OP_C_ID_SEQUENCE:
      type = SPVM_OP_get_type(compiler, op->last);
      break;
    case SPVM_OP_C_ID_ASSIGN: {
      type = SPVM_OP_get_type(compiler, op->last);
      break;
    }
    case SPVM_OP_C_ID_TYPE_CAST: {
      SPVM_OP* op_type = op->last;
      type = SPVM_OP_get_type(compiler, op_type);
      break;
    }
    case SPVM_OP_C_ID_TYPE: {
      if (op->uv.type) {
        type = op->uv.type;
      }
      break;
    }
    case SPVM_OP_C_ID_SWITCH_CONDITION : {
      type = SPVM_OP_get_type(compiler, op->first);
      break;
    }
    case SPVM_OP_C_ID_UNDEF : {
      type = SPVM_TYPE_new_undef_type(compiler);
      break;
    }
    case SPVM_OP_C_ID_CONSTANT: {
      SPVM_CONSTANT* constant = op->uv.constant;
      type = constant->type;
      break;
    }
    case SPVM_OP_C_ID_VAR: {
      SPVM_VAR* var = op->uv.var;
      type = var->var_decl->type;
      break;
    }
    case SPVM_OP_C_ID_CLASS_VAR_ACCESS: {
      SPVM_CLASS_VAR* class_var = op->uv.class_var_access->class_var;
      if (class_var->type) {
        type = class_var->type;
      }
      break;
    }
    case SPVM_OP_C_ID_CLASS_VAR: {
      SPVM_CLASS_VAR* class_var = op->uv.class_var;
      if (class_var->type) {
        type = class_var->type;
      }
      break;
    }
    case SPVM_OP_C_ID_CONCAT:
    case SPVM_OP_C_ID_TYPE_NAME:
    case SPVM_OP_C_ID_COMPILE_TYPE_NAME:
    case SPVM_OP_C_ID_DUMP:
    case SPVM_OP_C_ID_EXCEPTION_VAR:
    case SPVM_OP_C_ID_NEW_STRING_LEN:
    {
      type = SPVM_TYPE_new_string_type(compiler);
      break;
    }
    case SPVM_OP_C_ID_MY: {
      
      SPVM_VAR_DECL* var_decl = op->uv.var_decl;
      type = var_decl->type;
      break;
    }
    case SPVM_OP_C_ID_CALL_METHOD: {
      SPVM_CALL_METHOD*call_method = op->uv.call_method;
      const char*call_method_method_name =call_method->method->name;
      SPVM_CLASS*call_method_method_class =call_method->method->class;
      SPVM_METHOD* method = SPVM_HASH_get(call_method_method_class->method_symtable,call_method_method_name, strlen(call_method_method_name));
      type = method->return_type;
      break;
    }
    case SPVM_OP_C_ID_FIELD_ACCESS: {
      if (op->flag & (SPVM_OP_C_FLAG_FIELD_ACCESS_WEAKEN|SPVM_OP_C_FLAG_FIELD_ACCESS_UNWEAKEN|SPVM_OP_C_FLAG_FIELD_ACCESS_ISWEAK)) {
        type = SPVM_TYPE_new_int_type(compiler);
      }
      else {
        SPVM_FIELD_ACCESS* field_access = op->uv.field_access;
        SPVM_FIELD* field = field_access->field;
        type = field->type;
      }
      break;
    }
    case SPVM_OP_C_ID_ARRAY_FIELD_ACCESS: {
      SPVM_ARRAY_FIELD_ACCESS* array_field_access = op->uv.array_field_access;
      SPVM_FIELD* field = array_field_access->field;
      type = field->type;
      break;
    }
    case SPVM_OP_C_ID_FIELD: {
      SPVM_FIELD* field = op->uv.field;
      type = field->type;
      break;
    }
    case SPVM_OP_C_ID_CREATE_REF: {
      SPVM_TYPE* operand_type = SPVM_OP_get_type(compiler, op->first);
      assert(operand_type->dimension == 0);
      switch (operand_type->basic_type->id) {
        case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
          type = SPVM_TYPE_new_byte_ref_type(compiler);
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
          type = SPVM_TYPE_new_short_ref_type(compiler);
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
          type = SPVM_TYPE_new_int_ref_type(compiler);
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
          type = SPVM_TYPE_new_long_ref_type(compiler);
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
          type = SPVM_TYPE_new_float_ref_type(compiler);
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
          type = SPVM_TYPE_new_double_ref_type(compiler);
          break;
        }
        default: {
          assert(SPVM_TYPE_is_mulnum_type(compiler, operand_type->basic_type->id, operand_type->dimension, operand_type->flag));
          type = SPVM_TYPE_new(compiler, operand_type->basic_type->id, operand_type->dimension, operand_type->flag | SPVM_NATIVE_C_TYPE_FLAG_REF);
        }
      }
      break;
    }
    case SPVM_OP_C_ID_DEREF: {
      SPVM_TYPE* operand_type = SPVM_OP_get_type(compiler, op->first);
      assert(operand_type->dimension == 0);
      switch (operand_type->basic_type->id) {
        case SPVM_NATIVE_C_BASIC_TYPE_ID_BYTE: {
          type = SPVM_TYPE_new_byte_type(compiler);
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_SHORT: {
          type = SPVM_TYPE_new_short_type(compiler);
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_INT: {
          type = SPVM_TYPE_new_int_type(compiler);
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_LONG: {
          type = SPVM_TYPE_new_long_type(compiler);
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_FLOAT: {
          type = SPVM_TYPE_new_float_type(compiler);
          break;
        }
        case SPVM_NATIVE_C_BASIC_TYPE_ID_DOUBLE: {
          type = SPVM_TYPE_new_double_type(compiler);
          break;
        }
        default: {
          assert(SPVM_TYPE_is_mulnum_ref_type(compiler, operand_type->basic_type->id, operand_type->dimension, operand_type->flag));
          type = SPVM_TYPE_new(compiler, operand_type->basic_type->id, operand_type->dimension, operand_type->flag & ~SPVM_NATIVE_C_TYPE_FLAG_REF);
        }
      }
      break;
    }
  }
  
  return type;
}

// Insert child. Child must not have sibling.
void SPVM_OP_insert_child(SPVM_COMPILER* compiler, SPVM_OP* parent, SPVM_OP* start, SPVM_OP* insert) {
  (void)compiler;
  
  // del_count not used
  assert(parent);
  assert(insert);
  assert(insert->moresib == 0);
  
  if (start) {
    if (start->moresib) {
      insert->moresib = 1;
      insert->sibparent = start->sibparent;
      
      start->sibparent = insert;
    }
    else {
      parent->last = insert;

      insert->moresib = 0;
      insert->sibparent = parent;
      
      start->moresib = 1;
      start->sibparent = insert;
    }
  }
  else {
    if (parent->first) {
      insert->moresib = 1;
      insert->sibparent = parent->first;
      
      parent->first = insert;
    }
    else {
      insert->moresib = 0;
      insert->sibparent = parent;
      
      parent->first = insert;
      parent->last = insert;
    }
  }
}

SPVM_OP* SPVM_OP_sibling(SPVM_COMPILER* compiler, SPVM_OP* op) {
  (void)compiler;
  
  return op->moresib ? op->sibparent : NULL;
}

const char* SPVM_OP_get_op_name(SPVM_COMPILER* compiler, int32_t op_id) {
  const char* op_name = (SPVM_OP_C_ID_NAMES())[op_id];
  
  return op_name;
}
