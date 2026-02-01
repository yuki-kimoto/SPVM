// Copyright (c) 2023 Yuki Kimoto
// MIT License

%pure-parser
%parse-param  { SPVM_COMPILER* compiler }
%lex-param  { SPVM_COMPILER* compiler }

%{
  #include <stdio.h>
  
  #include "spvm_compiler.h"
  #include "spvm_yacc_util.h"
  #include "spvm_toke.h"
  #include "spvm_op.h"
  #include "spvm_dumper.h"
  #include "spvm_constant.h"
  #include "spvm_type.h"
  #include "spvm_block.h"
  #include "spvm_list.h"
  #include "spvm_attribute.h"
  #include "spvm_string.h"
%}

%token <opval> CLASS HAS GET SET METHOD OUR ENUM MY USE AS REQUIRE ALIAS ALLOW OUTMOST_CLASS MUTABLE
%token <opval> ATTRIBUTE MAKE_READ_ONLY MAKE_FIXED_LENGTH INTERFACE EVAL_ERROR_ID ARGS_WIDTH VERSION_DECL VERSION_FROM
%token <opval> IF UNLESS ELSIF ELSE FOR WHILE LAST NEXT SWITCH CASE DEFAULT BREAK EVAL BREAK_POINT
%token <opval> SYMBOL_NAME VAR_NAME CONSTANT EXCEPTION_VAR COPY_FIELDS EXISTS DELETE
%token <opval> UNDEF VOID BYTE SHORT INT LONG FLOAT DOUBLE STRING OBJECT ELEMENT TRUE FALSE END_OF_FILE
%token <opval> RW RO WO INIT END NEW OF BASIC_TYPE_ID EXTENDS SUPER SET_LENGTH SET_CAPACITY
%token <opval> RETURN WEAKEN DIE WARN WARN_LEVEL DIAG PRINT SAY STDERR OUTMOST_CLASS_NAME UNWEAKEN ENABLE_OPTIONS DISABLE_OPTIONS

%type <opval> grammar
%type <opval> field_name method_name class_name
%type <opval> basic_type  opt_basic_type array_type array_type_with_length type runtime_type ref_type return_type
%type <opval> union_type generic_type
%type <opval> opt_classes classes class class_block opt_extends version_decl version_from
%type <opval> opt_definitions definitions definition
%type <opval> enumeration enumeration_block opt_enumeration_items enumeration_items enumeration_item
%type <opval> method anon_method opt_args args arg use use_without_alias require class_alias our has getter opt_getter setter opt_setter anon_method_fields anon_method_field interface allow
%type <opval> opt_attributes attributes
%type <opval> opt_statements statements statement if_statement else_statement 
%type <opval> for_statement while_statement foreach_statement
%type <opval> switch_statement case_statement case_statements opt_case_statements default_statement
%type <opval> block eval_block init_block end_block switch_block if_require_statement
%type <opval> die exists delete
%type <opval> var_decl var
%type <opval> operator opt_operators operators opt_operator
%type <opval> void_return_operator warn warn_level
%type <opval> unary_operator array_length
%type <opval> inc dec
%type <opval> binary_operator arithmetic_operator bit_operator comparison_operator string_concatenation logical_operator defined_or ternary_operator
%type <opval> assign
%type <opval> new array_init
%type <opval> type_check type_cast can
%type <opval> call_method caller
%type <opval> array_element_access field_access hash_value_access
%type <opval> weaken_field unweaken_field isweak_field
%type <opval> sequential copy_fields break_point

%left <opval> ',' FATCAMMA
%right <opval> ASSIGN SPECIAL_ASSIGN
%right <oval> '?' ':'
%left <opval> LOGICAL_OR DEFINED_OR
%left <opval> LOGICAL_AND
%left <opval> BIT_OR BIT_XOR
%left <opval> BIT_AND
%nonassoc <opval> NUMEQ NUMNE STREQ STRNE
%nonassoc <opval> NUMGT NUMGE NUMLT NUMLE STRGT STRGE STRLT STRLE ISA ISA_ERROR IS_TYPE IS_ERROR IS_COMPILE_TYPE NUMERIC_CMP STRING_CMP CAN
%left <opval> SHIFT
%left <opval> '+' '-' '.'
%left <opval> '*' DIVIDE DIVIDE_UNSIGNED_INT DIVIDE_UNSIGNED_LONG MODULO  MODULO_UNSIGNED_INT MODULO_UNSIGNED_LONG
%right <opval> LOGICAL_NOT BIT_NOT '@' REFERENCE DEREFERENCE PLUS MINUS CONVERT SCALAR STRING_LENGTH ISWEAK TYPE_NAME COMPILE_TYPE_NAME DUMP NEW_STRING_LEN IS_READ_ONLY IS_FIXED_LENGTH COPY ADDRESS IS_OPTIONS CAPACITY CALLER
%nonassoc <opval> INC DEC
%left <opval> ARROW
%nonassoc <opval> ')'
%left <opval> '('
%left <opval> '[' '{'

%%

grammar
  : opt_classes
  
field_name
  : SYMBOL_NAME

method_name
  : SYMBOL_NAME

class_name
  : SYMBOL_NAME

runtime_type
  : basic_type
  | array_type

type
  : runtime_type
  | ref_type
  | union_type
  | generic_type
  | MUTABLE type
    {
      $$ = SPVM_OP_build_mutable_type(compiler, $2);
    }

union_type
  : type BIT_OR type
    {
      $$ = SPVM_OP_build_union_type(compiler, $1, $3);
    }

generic_type
  : basic_type OF type
    {
      $$ = SPVM_OP_build_generic_type(compiler, $1, $3);
    }

basic_type
  : SYMBOL_NAME
    {
      $$ = SPVM_OP_build_basic_type(compiler, $1);
    }
  | BYTE
    {
      SPVM_OP* op_type = SPVM_OP_new_op_byte_type(compiler, $1->file, $1->line);
      
      $$ = op_type;
    }
  | SHORT
    {
      SPVM_OP* op_type = SPVM_OP_new_op_short_type(compiler, $1->file, $1->line);
      
      $$ = op_type;
    }
  | INT
    {
      SPVM_OP* op_type = SPVM_OP_new_op_int_type(compiler, $1->file, $1->line);
      
      $$ = op_type;
    }
  | LONG
    {
      SPVM_OP* op_type = SPVM_OP_new_op_long_type(compiler, $1->file, $1->line);
      
      $$ = op_type;
    }
  | FLOAT
    {
      SPVM_OP* op_type = SPVM_OP_new_op_float_type(compiler, $1->file, $1->line);
      
      $$ = op_type;
    }
  | DOUBLE
    {
      SPVM_OP* op_type = SPVM_OP_new_op_double_type(compiler, $1->file, $1->line);
      
      $$ = op_type;
    }
  | OBJECT
    {
      SPVM_OP* op_type = SPVM_OP_new_op_any_object_type(compiler, $1->file, $1->line);
      $$ = op_type;
    }
  | STRING
    {
      SPVM_OP* op_type = SPVM_OP_new_op_string_type(compiler, $1->file, $1->line);
      
      $$ = op_type;
    }

ref_type
  : basic_type '*'
    {
      $$ = SPVM_OP_build_ref_type(compiler, $1);
    }

array_type
  : basic_type '[' ']'
    {
      $$ = SPVM_OP_build_array_type(compiler, $1, NULL, 0);
    }
  | array_type '[' ']'
    {
      $$ = SPVM_OP_build_array_type(compiler, $1, NULL, 0);
    }
  | basic_type '.' '.' '.'
    {
      
      $$ = SPVM_OP_build_array_type(compiler, $1, NULL, 1);
    }

array_type_with_length
  : basic_type '[' operator ']'
    {
      $$ = SPVM_OP_build_array_type(compiler, $1, $3, 0);
    }
  | array_type '[' operator ']'
    {
      $$ = SPVM_OP_build_array_type(compiler, $1, $3, 0);
    }

return_type
  : type
  | VOID
    {
      $$ = SPVM_OP_new_op_void_type(compiler, compiler->current_file, compiler->current_line);
    }
  | ELEMENT
    {
      $$ = SPVM_OP_new_op_element_type(compiler, $1->file, $1->line);
    }
  | ELEMENT '[' ']'
    {
      $$ = SPVM_OP_new_op_element_array_type(compiler, $1->file, $1->line);
    }

opt_classes
  : /* Empty */
    {
      $$ = SPVM_OP_new_op_list(compiler, compiler->current_file, compiler->current_line);
    }
  | classes
    {
      if ($1->id == SPVM_OP_C_ID_LIST) {
        $$ = $1;
      }
      else {
        SPVM_OP* op_list = SPVM_OP_new_op_list(compiler, $1->file, $1->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, $1);
        $$ = op_list;
      }
    }
  
classes
  : classes class
    {
      SPVM_OP* op_list;
      if ($1->id == SPVM_OP_C_ID_LIST) {
        op_list = $1;
      }
      else {
        op_list = SPVM_OP_new_op_list(compiler, $1->file, $1->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, $1);
      }
      SPVM_OP_insert_child(compiler, op_list, op_list->last, $2);
      
      $$ = op_list;
    }
  | class

class
  : CLASS opt_basic_type opt_extends class_block END_OF_FILE
    {
      $$ = SPVM_OP_build_class(compiler, $1, $2, $4, NULL, $3);
    }
  | CLASS opt_basic_type opt_extends ':' opt_attributes class_block END_OF_FILE
    {
      $$ = SPVM_OP_build_class(compiler, $1, $2, $6, $5, $3);
    }
  | CLASS opt_basic_type opt_extends ';' END_OF_FILE
    {
      $$ = SPVM_OP_build_class(compiler, $1, $2, NULL, NULL, $3);
    }
  | CLASS opt_basic_type opt_extends ':' opt_attributes ';' END_OF_FILE
    {
      $$ = SPVM_OP_build_class(compiler, $1, $2, NULL, $5, $3);
    }
  | opt_statements END_OF_FILE
    {
      $$ = SPVM_OP_build_anon_class_from_statements(compiler, $1);
    }
  
opt_basic_type
  : /* Empty */
    {
      $$ = NULL;
    }
  | basic_type

opt_extends
  : /* Empty */
    {
      $$ = NULL;
    }
  | EXTENDS basic_type
    {
      $$ = SPVM_OP_build_extends(compiler, $1, $2);
    }

class_block
  : '{' opt_definitions '}'
    {
      SPVM_OP* op_class_block = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CLASS_BLOCK, $1->file, $1->line);
      SPVM_OP_insert_child(compiler, op_class_block, op_class_block->last, $2);
      $$ = op_class_block;
    }

opt_definitions
  : /* Empty */
    {
      $$ = SPVM_OP_new_op_list(compiler, compiler->current_file, compiler->current_line);
    }
  | definitions
    {
      if ($1->id == SPVM_OP_C_ID_LIST) {
        $$ = $1;
      }
      else {
        $$ = SPVM_OP_new_op_list(compiler, $1->file, $1->line);
        SPVM_OP_insert_child(compiler, $$, $$->last, $1);
      }
    }

definitions
  : definitions definition
    {
      SPVM_OP* op_list;
      if ($1->id == SPVM_OP_C_ID_LIST) {
        op_list = $1;
      }
      else {
        op_list = SPVM_OP_new_op_list(compiler, $1->file, $1->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, $1);
      }
      SPVM_OP_insert_child(compiler, op_list, op_list->last, $2);
      
      $$ = op_list;
    }
  | definition

definition
  : version_decl
  | version_from
  | use
  | class_alias
  | allow
  | interface
  | init_block
  | end_block
  | enumeration
  | our
  | has ';'
  | method

init_block
  : INIT block
    { 
      $$ = SPVM_OP_build_init_block(compiler, $1, $2);
    }

end_block
  : END block
    { 
      $$ = SPVM_OP_build_end_block(compiler, $1, $2);
    }

version_decl
  : VERSION_DECL CONSTANT ';'
    {
      $$ = SPVM_OP_build_version_decl(compiler, $1, $2);
    }

version_from
  : VERSION_FROM basic_type ';'
    {
      $$ = SPVM_OP_build_version_from(compiler, $1, $2);
    }

use_without_alias
  : USE basic_type ';'
    {
      int32_t is_require = 0;
      SPVM_OP* op_name_class_alias = NULL;
      $$ = SPVM_OP_build_use(compiler, $1, $2, op_name_class_alias, is_require);
    }

use
  : use_without_alias
  | USE basic_type AS class_name ';'
    {
      int32_t is_require = 0;
      $$ = SPVM_OP_build_use(compiler, $1, $2, $4, is_require);
    }

require
  : REQUIRE basic_type
    {
      SPVM_OP* op_use = SPVM_OP_new_op_use(compiler, compiler->current_file, compiler->current_line);
      int32_t is_require = 1;
      $$ = SPVM_OP_build_use(compiler, op_use, $2, NULL, is_require);
    }

class_alias
  : ALIAS basic_type AS class_name ';'
    {
      SPVM_OP* op_use = SPVM_OP_new_op_use(compiler, compiler->current_file, compiler->current_line);
      $$ = SPVM_OP_build_alias(compiler, op_use, $2, $4);
    }

allow
  : ALLOW basic_type ';'
    {
      $$ = SPVM_OP_build_allow(compiler, $1, $2);
    }

interface
  : INTERFACE basic_type ';'
    {
      $$ = SPVM_OP_build_interface_statement(compiler, $1, $2);
    }

enumeration
  : opt_attributes ENUM enumeration_block
    {
      $$ = SPVM_OP_build_enumeration(compiler, $2, $3, $1);
    }

enumeration_block 
  : '{' opt_enumeration_items '}'
    {
      SPVM_OP* op_enum_block = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ENUM_BLOCK, $1->file, $1->line);
      SPVM_OP_insert_child(compiler, op_enum_block, op_enum_block->last, $2);
      $$ = op_enum_block;
    }

opt_enumeration_items
  : /* Empty */
    {
      $$ = SPVM_OP_new_op_list(compiler, compiler->current_file, compiler->current_line);
    }
  | enumeration_items
    {
      if ($1->id == SPVM_OP_C_ID_LIST) {
        $$ = $1;
      }
      else {
        SPVM_OP* op_list = SPVM_OP_new_op_list(compiler, $1->file, $1->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, $1);
        $$ = op_list;
      }
    }
    
enumeration_items
  : enumeration_items ',' enumeration_item 
    {
      SPVM_OP* op_list;
      if ($1->id == SPVM_OP_C_ID_LIST) {
        op_list = $1;
      }
      else {
        op_list = SPVM_OP_new_op_list(compiler, $1->file, $1->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, $1);
      }
      SPVM_OP_insert_child(compiler, op_list, op_list->last, $3);
      
      $$ = op_list;
    }
  | enumeration_items ','
  | enumeration_item
  
enumeration_item
  : method_name
    {
      $$ = SPVM_OP_build_enumeration_item(compiler, $1, NULL);
    }
  | method_name ASSIGN CONSTANT
    {
      $$ = SPVM_OP_build_enumeration_item(compiler, $1, $3);
    }

our
  : OUR VAR_NAME ':' opt_attributes type opt_getter opt_setter ';'
    {
      $$ = SPVM_OP_build_class_var(compiler, $1, $2, $4, $5, $6, $7);
    }

has
  : HAS field_name ':' opt_attributes type opt_getter opt_setter
    {
      $$ = SPVM_OP_build_field(compiler, $1, $2, $4, $5, $6, $7);
    }

opt_getter
  : /* Empty */
    {
      $$ = NULL;
    }
  | getter

getter
  : GET block
    {
      SPVM_OP* op_return_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_DO_NOTHING, compiler->current_file, compiler->current_line);
      SPVM_OP* op_arg = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_DO_NOTHING, compiler->current_file, compiler->current_line);
      $$ = SPVM_OP_build_accessor(compiler, $1, op_arg, $2, op_return_type);
    }

opt_setter
  : /* Empty */
    {
      $$ = NULL;
    }
  | setter

setter
  : SET block
    {
      SPVM_OP* op_return_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_DO_NOTHING, compiler->current_file, compiler->current_line);
      SPVM_OP* op_arg = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_DO_NOTHING, compiler->current_file, compiler->current_line);
      $$ = SPVM_OP_build_accessor(compiler, $1, op_arg, $2, op_return_type);
    }
  | SET '(' arg ')' block
    {
      SPVM_OP* op_return_type = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_DO_NOTHING, compiler->current_file, compiler->current_line);
      $$ = SPVM_OP_build_accessor(compiler, $1, $3, $5, op_return_type);
    }
  | SET ':' return_type '(' arg ')' block
    {
      $$ = SPVM_OP_build_accessor(compiler, $1, $5, $7, $3);
    }
  | SET ':' return_type
    {
      SPVM_OP* op_arg = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_DO_NOTHING, compiler->current_file, compiler->current_line);
      SPVM_OP* op_block = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_DO_NOTHING, compiler->current_file, compiler->current_line);
      $$ = SPVM_OP_build_accessor(compiler, $1, op_arg, op_block, $3);
    }

method
  : opt_attributes METHOD method_name ':' return_type '(' opt_args ')' block
     {
       $$ = SPVM_OP_build_method(compiler, $2, $3, $5, $7, $1, $9);
     }
  | opt_attributes METHOD method_name ':' return_type '(' opt_args ')' ';'
     {
       $$ = SPVM_OP_build_method(compiler, $2, $3, $5, $7, $1, NULL);
     }
  | opt_attributes METHOD ':' return_type '(' opt_args ')' block
     {
       $$ = SPVM_OP_build_method(compiler, $2, NULL, $4, $6, $1, $8);
     }
  | opt_attributes METHOD ':' return_type '(' opt_args ')' ';'
     {
       $$ = SPVM_OP_build_method(compiler, $2, NULL, $4, $6, $1, NULL);
     }

anon_method
  : opt_attributes METHOD ':' return_type '(' opt_args ')' block
     {
       $$ = SPVM_OP_build_method(compiler, $2, NULL, $4, $6, $1, $8);
     }
  | '[' anon_method_fields ']' opt_attributes METHOD ':' return_type '(' opt_args ')' block
     {
       SPVM_OP* op_anon_method_fields;
       if ($2->id == SPVM_OP_C_ID_LIST) {
         op_anon_method_fields = $2;
       }
       else {
         op_anon_method_fields = SPVM_OP_new_op_list(compiler, $2->file, $2->line);
         SPVM_OP_insert_child(compiler, op_anon_method_fields, op_anon_method_fields->last, $2);
       }
       
       $$ = SPVM_OP_build_method(compiler, $5, NULL, $7, $9, $4, $11);
       
       SPVM_OP_attach_anon_method_fields(compiler, $$, op_anon_method_fields);
     }

opt_args
  : /* Empty */
    {
      $$ = SPVM_OP_new_op_list(compiler, compiler->current_file, compiler->current_line);
    }
  | args
    {
      if ($1->id == SPVM_OP_C_ID_LIST) {
        $$ = $1;
      }
      else {
        SPVM_OP* op_list = SPVM_OP_new_op_list(compiler, $1->file, $1->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, $1);
        $$ = op_list;
      }
    }

args
  : args ',' arg
    {
      SPVM_OP* op_list;
      if ($1->id == SPVM_OP_C_ID_LIST) {
        op_list = $1;
      }
      else {
        op_list = SPVM_OP_new_op_list(compiler, $1->file, $1->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, $1);
      }
      SPVM_OP_insert_child(compiler, op_list, op_list->last, $3);
      
      $$ = op_list;
    }
  | args ','
  | arg

arg
  : var ':' type
    {
      $$ = SPVM_OP_build_arg(compiler, $1, $3, NULL, NULL);
    }
  | var ':' type ASSIGN operator
    {
      $$ = SPVM_OP_build_arg(compiler, $1, $3, NULL, $5);
    }

anon_method_fields
  : anon_method_fields ',' anon_method_field
    {
      SPVM_OP* op_list;
      if ($1->id == SPVM_OP_C_ID_LIST) {
        op_list = $1;
      }
      else {
        op_list = SPVM_OP_new_op_list(compiler, $1->file, $1->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, $1);
      }
      SPVM_OP_insert_child(compiler, op_list, op_list->last, $3);
      
      $$ = op_list;
    }
  | anon_method_fields ','
  | anon_method_field

anon_method_field
  : HAS field_name ':' opt_attributes type
    {
      $$ = SPVM_OP_build_anon_method_field(compiler, $1, $2, $4, $5, NULL);
    }
  | HAS field_name ':' opt_attributes type ASSIGN operator
    {
      $$ = SPVM_OP_build_anon_method_field(compiler, $1, $2, $4, $5, $7);
    }
  | var ':' opt_attributes type
    {
      SPVM_OP* op_field = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_FIELD, $1->file, $1->line);
      
      $$ = SPVM_OP_build_anon_method_field(compiler, op_field, NULL, $3, $4, $1);
    }
  | var ':' opt_attributes type ASSIGN operator
    {
      SPVM_OP* op_field = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_FIELD, $1->file, $1->line);
      
      $$ = SPVM_OP_build_anon_method_field(compiler, op_field, $1, $3, $4, $6);
    }
    
opt_attributes
  : /* Empty */
    {
      $$ = SPVM_OP_new_op_list(compiler, compiler->current_file, compiler->current_line);
    }
  | attributes
    {
      if ($1->id == SPVM_OP_C_ID_LIST) {
        $$ = $1;
      }
      else {
        SPVM_OP* op_list = SPVM_OP_new_op_list(compiler, $1->file, $1->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, $1);
        $$ = op_list;
      }
    }
    
attributes
  : attributes ATTRIBUTE
    {
      SPVM_OP* op_list;
      if ($1->id == SPVM_OP_C_ID_LIST) {
        op_list = $1;
      }
      else {
        op_list = SPVM_OP_new_op_list(compiler, $1->file, $1->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, $1);
      }
      SPVM_OP_insert_child(compiler, op_list, op_list->last, $2);
      
      $$ = op_list;
    }
  | ATTRIBUTE

opt_statements
  : /* Empty */
    {
      $$ = SPVM_OP_new_op_list(compiler, compiler->current_file, compiler->current_line);
    }
  | statements
    {
      if ($1->id == SPVM_OP_C_ID_LIST) {
        $$ = $1;
      }
      else {
        SPVM_OP* op_list = SPVM_OP_new_op_list(compiler, $1->file, $1->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, $1);
        $$ = op_list;
      }
    }
    
statements
  : statements statement 
    {
      SPVM_OP* op_list;
      if ($1->id == SPVM_OP_C_ID_LIST) {
        op_list = $1;
      }
      else {
        op_list = SPVM_OP_new_op_list(compiler, $1->file, $1->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, $1);
      }
      SPVM_OP_insert_child(compiler, op_list, op_list->last, $2);
      
      $$ = op_list;
    }
  | statement

statement
  : if_statement
  | for_statement
  | foreach_statement
  | while_statement
  | block
  | switch_statement
  | case_statement
  | default_statement
  | eval_block
  | if_require_statement
  | LAST ';'
  | NEXT ';'
  | BREAK ';'
  | RETURN ';'
    {
      $$ = SPVM_OP_build_return(compiler, $1, NULL);
    }
  | RETURN operator ';'
    {
      $$ = SPVM_OP_build_return(compiler, $1, $2);
    }
  | die ';'
  | operator ';'
    {
      $$ = SPVM_OP_build_operator_statement(compiler, $1);
    }
  | void_return_operator ';'
  | ';'
    {
      $$ = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_DO_NOTHING, compiler->current_file, compiler->current_line);
    }
  | use_without_alias

die
  : DIE operator
    {
      $$ = SPVM_OP_build_die(compiler, $1, $2, NULL);
    }
  | DIE
    {
      $$ = SPVM_OP_build_die(compiler, $1, NULL, NULL);
    }
  | DIE basic_type operator
    {
      $$ = SPVM_OP_build_die(compiler, $1, $3, $2);
    }
  | DIE basic_type
    {
      $$ = SPVM_OP_build_die(compiler, $1, NULL, $2);
    }
  | DIE operator ',' operator
    {
      $$ = SPVM_OP_build_die(compiler, $1, $4, $2);
    }

void_return_operator
  : warn
  | warn_level
  | PRINT operator
    {
      $$ = SPVM_OP_build_print(compiler, $1, $2, 0);
    }
  | PRINT STDERR operator
    {
      $$ = SPVM_OP_build_print(compiler, $1, $3, 1);
    }
  | SAY operator
    {
      $$ = SPVM_OP_build_print(compiler, $1, $2, 0);
    }
  | SAY STDERR operator
    {
      $$ = SPVM_OP_build_print(compiler, $1, $3, 1);
    }
  | weaken_field
  | unweaken_field
  | MAKE_READ_ONLY operator
    {
      $$ = SPVM_OP_build_make_read_only(compiler, $1, $2);
    }
  | MAKE_FIXED_LENGTH operator
    {
      $$ = SPVM_OP_build_make_fixed_length(compiler, $1, $2);
    }
  | ENABLE_OPTIONS operator
    {
      $$ = SPVM_OP_build_enable_options(compiler, $1, $2);
    }
  | DISABLE_OPTIONS operator
    {
      $$ = SPVM_OP_build_disable_options(compiler, $1, $2);
    }
  | copy_fields
  | delete
  | SET_LENGTH '(' operator ',' operator ')'
    {
      $$ = SPVM_OP_build_binary_op(compiler, $1, $3, $5);
    }
  | SET_CAPACITY '(' operator ',' operator ')'
    {
      $$ = SPVM_OP_build_binary_op(compiler, $1, $3, $5);
    }
  | break_point

for_statement
  : FOR '(' opt_operator ';' opt_operator ';' opt_operator ')' block
    {
      $$ = SPVM_OP_build_for_statement(compiler, $1, $3, $5, $7, $9);
    }

foreach_statement
  : FOR var_decl '(' '@' operator ')' block
    {
      $$ = SPVM_OP_build_foreach_statement(compiler, $1, $2, $5, $7);
    }
  | FOR var_decl '(' '@' '{' operator '}' ')' block
    {
      $$ = SPVM_OP_build_foreach_statement(compiler, $1, $2, $6, $9);
    }

while_statement
  : WHILE '(' operator ')' block
    {
      $$ = SPVM_OP_build_while_statement(compiler, $1, $3, $5);
    }

switch_statement
  : SWITCH '(' operator ')' switch_block
    {
      $$ = SPVM_OP_build_switch_statement(compiler, $1, $3, $5);
    }

switch_block
  : '{' opt_case_statements '}'
    {
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, compiler->current_file, compiler->current_line);
      $$ = SPVM_OP_build_switch_block(compiler, op_block, $2, NULL);
    }
  | '{' opt_case_statements default_statement '}'
    {
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, compiler->current_file, compiler->current_line);
      $$ = SPVM_OP_build_switch_block(compiler, op_block, $2, $3);
    }

opt_case_statements
  : /* Empty */
    {
      $$ = SPVM_OP_new_op_list(compiler, compiler->current_file, compiler->current_line);
    }
  | case_statements
    {
      if ($1->id == SPVM_OP_C_ID_LIST) {
        $$ = $1;
      }
      else {
        SPVM_OP* op_list = SPVM_OP_new_op_list(compiler, $1->file, $1->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, $1);
        $$ = op_list;
      }
    }

case_statements
  : case_statements case_statement
    {
      SPVM_OP* op_list;
      if ($1->id == SPVM_OP_C_ID_LIST) {
        op_list = $1;
      }
      else {
        op_list = SPVM_OP_new_op_list(compiler, $1->file, $1->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, $1);
      }
      SPVM_OP_insert_child(compiler, op_list, op_list->last, $2);
      
      $$ = op_list;
    }
  | case_statement
    {
      $$ = $1;
    }

case_statement
  : CASE operator ':' block
    {
      $$ = SPVM_OP_build_case_statement(compiler, $1, $2, $4);
    }
  | CASE operator ':'
    {
      $$ = SPVM_OP_build_case_statement(compiler, $1, $2, NULL);
    }

default_statement
  : DEFAULT ':' block
    {
      $$ = SPVM_OP_build_default_statement(compiler, $1, $3);
    }
  | DEFAULT ':'
    {
      $$ = SPVM_OP_build_default_statement(compiler, $1, NULL);
    }

if_require_statement
  : IF '(' require ')' block
    {
      SPVM_OP* op_if_require = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_IF_REQUIRE, compiler->current_file, compiler->current_line);
      
      $$ = SPVM_OP_build_if_require_statement(compiler, op_if_require, $3, $5, NULL);
    }
  | IF '(' require ')' block ELSE block
    {
      SPVM_OP* op_if_require = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_IF_REQUIRE, compiler->current_file, compiler->current_line);
      
      $$ = SPVM_OP_build_if_require_statement(compiler, op_if_require, $3, $5, $7);
    }
if_statement
  : IF '(' operator ')' block else_statement
    {
      SPVM_OP* op_if = SPVM_OP_build_if_statement(compiler, $1, $3, $5, $6, 0);
      
      // condition part has own scope
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, $1->file, $1->line);
      SPVM_OP_insert_child(compiler, op_block, op_block->last, op_if);
      
      $$ = op_block;
    }
  | UNLESS '(' operator ')' block else_statement
    {
      SPVM_OP* op_if = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_IF, $1->file, $1->line);
      op_if = SPVM_OP_build_if_statement(compiler, op_if, $3, $6, $5, 0);
      
      // condition part has own scope
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, $1->file, $1->line);
      SPVM_OP_insert_child(compiler, op_block, op_block->last, op_if);
      
      $$ = op_block;
    }

else_statement
  : /* NULL */
    {
      $$ = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_DO_NOTHING, compiler->current_file, compiler->current_line);
    };
  | ELSE block
    {
      $$ = $2;
    }
  | ELSIF '(' operator ')' block else_statement
    {
      SPVM_OP* op_if = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_IF, $1->file, $1->line);
      $$ = SPVM_OP_build_if_statement(compiler, op_if, $3, $5, $6, 0);
    }

block 
  : '{' opt_statements '}'
    {
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, $1->file, $1->line);
      SPVM_OP_insert_child(compiler, op_block, op_block->last, $2);
      $$ = op_block;
    }

eval_block
  : EVAL block
    {
      $$ = SPVM_OP_build_eval(compiler, $1, $2);
    }

var_decl
  : MY var ':' type
    {
      $$ = SPVM_OP_build_var_decl(compiler, $1, $2, $4, NULL);
    }
  | MY var
    {
      $$ = SPVM_OP_build_var_decl(compiler, $1, $2, NULL, NULL);
    }

var
  : VAR_NAME
    {
      $$ = SPVM_OP_build_var(compiler, $1);
    }

opt_operators
  : /* Empty */
    {
      $$ = SPVM_OP_new_op_list(compiler, compiler->current_file, compiler->current_line);
    }
  | operators
    {
      if ($1->id == SPVM_OP_C_ID_LIST) {
        $$ = $1;
      }
      else {
        SPVM_OP* op_list = SPVM_OP_new_op_list(compiler, $1->file, $1->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, $1);
        $$ = op_list;
      }
    }
    
opt_operator
  : /* Empty */
    {
      $$ = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_DO_NOTHING, compiler->current_file, compiler->current_line);
    }
  | operator

operator
  : var
  | EXCEPTION_VAR
  | CONSTANT
  | UNDEF
  | type_cast
  | new
  | var_decl
  | EVAL_ERROR_ID
  | ARGS_WIDTH
  | TRUE
    {
      $$ = SPVM_OP_new_op_true(compiler, $1);
    }
  | FALSE
    {
      $$ = SPVM_OP_new_op_false(compiler, $1);
    }
  | OUTMOST_CLASS_NAME
  | unary_operator
  | binary_operator
  | ternary_operator
  | assign
  | inc
  | dec
  | type_check
  | BASIC_TYPE_ID type
    {
      $$ = SPVM_OP_build_basic_type_id(compiler, $1, $2);
    }
  | can
  | array_init
  | array_element_access
  | field_access
  | hash_value_access
  | isweak_field
  | call_method
  | sequential
  | exists
  | caller

sequential
  : '(' operators ')'
    {
      if ($2->id == SPVM_OP_C_ID_LIST) {
        SPVM_OP* op_operator = $2->first;
        SPVM_OP* op_sequence = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_SEQUENCE, compiler->current_file, compiler->current_line);
        while ((op_operator = SPVM_OP_sibling(compiler, op_operator))) {
          SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_operator);
          SPVM_OP_insert_child(compiler, op_sequence, op_sequence->last, op_operator);
          op_operator = op_stab;
        }
        $$ = op_sequence;
      }
      else {
        $$ = $2;
      }
    }
  | '(' operators ',' if_statement ',' operator ')'
    {
      SPVM_OP* op_operator = $2->first;
      SPVM_OP* op_sequence = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_SEQUENCE, compiler->current_file, compiler->current_line);
      
      SPVM_OP_insert_child(compiler, op_sequence, op_sequence->last, $2);
      SPVM_OP_insert_child(compiler, op_sequence, op_sequence->last, $4);
      SPVM_OP_insert_child(compiler, op_sequence, op_sequence->last, $6);
      
      $$ = op_sequence;
    }

operators
  : operators ',' operator
    {
      SPVM_OP* op_list;
      if ($1->id == SPVM_OP_C_ID_LIST) {
        op_list = $1;
      }
      else {
        op_list = SPVM_OP_new_op_list(compiler, $1->file, $1->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, $1);
      }
      SPVM_OP_insert_child(compiler, op_list, op_list->last, $3);
      
      $$ = op_list;
    }
  | operators ','
    {
      $$ = $1;
    }
  | operator
    {
      $$ = $1;
    }

unary_operator
  : '+' operator %prec PLUS
    {
      SPVM_OP* operator = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PLUS, $1->file, $1->line);
      $$ = SPVM_OP_build_unary_op(compiler, operator, $2);
    }
  | '-' operator %prec MINUS
    {
      SPVM_OP* op_negate = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_MINUS, $1->file, $1->line);
      $$ = SPVM_OP_build_unary_op(compiler, op_negate, $2);
    }
  | BIT_NOT operator
    {
      $$ = SPVM_OP_build_unary_op(compiler, $1, $2);
    }
  | TYPE_NAME operator
    {
      $$ = SPVM_OP_build_unary_op(compiler, $1, $2);
    }
  | COMPILE_TYPE_NAME operator
    {
      $$ = SPVM_OP_build_unary_op(compiler, $1, $2);
    }
  | STRING_LENGTH operator
    {
      $$ = SPVM_OP_build_unary_op(compiler, $1, $2);
    }
  | DUMP operator
    {
      $$ = SPVM_OP_build_unary_op(compiler, $1, $2);
    }
  | DEREFERENCE var
    {
      $$ = SPVM_OP_build_unary_op_var(compiler, $1, $2);
    }
  | REFERENCE operator
    {
      $$ = SPVM_OP_build_unary_op_var(compiler, $1, $2);
    }
  | NEW_STRING_LEN operator
    {
      $$ = SPVM_OP_build_unary_op(compiler, $1, $2);
    }
  | COPY operator
    {
      $$ = SPVM_OP_build_unary_op(compiler, $1, $2);
    }
  | IS_READ_ONLY operator
    {
      $$ = SPVM_OP_build_unary_op(compiler, $1, $2);
    }
  | IS_FIXED_LENGTH operator
    {
      $$ = SPVM_OP_build_unary_op(compiler, $1, $2);
    }
  | array_length
  | ADDRESS operator
    {
      $$ = SPVM_OP_build_unary_op(compiler, $1, $2);
    }
  | IS_OPTIONS operator
    {
      $$ = SPVM_OP_build_unary_op(compiler, $1, $2);
    }
  | CAPACITY operator
    {
      $$ = SPVM_OP_build_unary_op(compiler, $1, $2);
    }

array_length
  : '@' operator
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->current_file, compiler->current_line);
      $$ = SPVM_OP_build_array_length(compiler, op_array_length, $2);
    }
  | '@' '{' operator '}'
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->current_file, compiler->current_line);
      $$ = SPVM_OP_build_array_length(compiler, op_array_length, $3);
    }
  | SCALAR '@' operator
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->current_file, compiler->current_line);
      $$ = SPVM_OP_build_array_length(compiler, op_array_length, $3);
    }
  | SCALAR '@' '{' operator '}'
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->current_file, compiler->current_line);
      $$ = SPVM_OP_build_array_length(compiler, op_array_length, $4);
    }

inc
  : INC operator
    {
      SPVM_OP* operator = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PRE_INC, $1->file, $1->line);
      $$ = SPVM_OP_build_inc(compiler, operator, $2);
    }
  | operator INC
    {
      SPVM_OP* operator = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_POST_INC, $2->file, $2->line);
      $$ = SPVM_OP_build_inc(compiler, operator, $1);
    }

dec
  : DEC operator
    {
      SPVM_OP* operator = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PRE_DEC, $1->file, $1->line);
      $$ = SPVM_OP_build_dec(compiler, operator, $2);
    }
  | operator DEC
    {
      SPVM_OP* operator = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_POST_DEC, $2->file, $2->line);
      $$ = SPVM_OP_build_dec(compiler, operator, $1);
    }

binary_operator
  : arithmetic_operator
  | bit_operator
  | comparison_operator
  | string_concatenation
  | logical_operator
  | defined_or

arithmetic_operator
  : operator '+' operator
    {
      SPVM_OP* operator = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ADD, $2->file, $2->line);
      $$ = SPVM_OP_build_binary_op(compiler, operator, $1, $3);
    }
  | operator '-' operator
    {
      SPVM_OP* operator = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_SUBTRACT, $2->file, $2->line);
      $$ = SPVM_OP_build_binary_op(compiler, operator, $1, $3);
    }
  | operator '*' operator
    {
      SPVM_OP* operator = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_MULTIPLY, $2->file, $2->line);
      $$ = SPVM_OP_build_binary_op(compiler, operator, $1, $3);
    }
  | operator DIVIDE operator
    {
      $$ = SPVM_OP_build_binary_op(compiler, $2, $1, $3);
    }
  | operator DIVIDE_UNSIGNED_INT operator
    {
      $$ = SPVM_OP_build_binary_op(compiler, $2, $1, $3);
    }
  | operator DIVIDE_UNSIGNED_LONG operator
    {
      $$ = SPVM_OP_build_binary_op(compiler, $2, $1, $3);
    }
  | operator MODULO operator
    {
      $$ = SPVM_OP_build_binary_op(compiler, $2, $1, $3);
    }
  | operator MODULO_UNSIGNED_INT operator
    {
      $$ = SPVM_OP_build_binary_op(compiler, $2, $1, $3);
    }
  | operator MODULO_UNSIGNED_LONG operator
    {
      $$ = SPVM_OP_build_binary_op(compiler, $2, $1, $3);
    }

ternary_operator
  : operator '?' operator ':' operator
    {
      SPVM_OP* ternary_op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TERNARY_OP, $1->file, $1->line);
      $$ = SPVM_OP_build_ternary_op(compiler, ternary_op, $1, $3, $5);
    }

bit_operator
  : operator BIT_XOR operator
    {
      $$ = SPVM_OP_build_binary_op(compiler, $2, $1, $3);
    }
  | operator BIT_AND operator
    {
      $$ = SPVM_OP_build_binary_op(compiler, $2, $1, $3);
    }
  | operator BIT_OR operator
    {
      $$ = SPVM_OP_build_binary_op(compiler, $2, $1, $3);
    }
  | operator SHIFT operator
    {
      $$ = SPVM_OP_build_binary_op(compiler, $2, $1, $3);
    }

comparison_operator
  : operator NUMEQ operator
    {
      $$ = SPVM_OP_build_binary_op(compiler, $2, $1, $3);
    }
  | operator NUMNE operator
    {
      $$ = SPVM_OP_build_binary_op(compiler, $2, $1, $3);
    }
  | operator NUMGT operator
    {
      $$ = SPVM_OP_build_binary_op(compiler, $2, $1, $3);
    }
  | operator NUMGE operator
    {
      $$ = SPVM_OP_build_binary_op(compiler, $2, $1, $3);
    }
  | operator NUMLT operator
    {
      $$ = SPVM_OP_build_binary_op(compiler, $2, $1, $3);
    }
  | operator NUMLE operator
    {
      $$ = SPVM_OP_build_binary_op(compiler, $2, $1, $3);
    }
  | operator NUMERIC_CMP operator
    {
      $$ = SPVM_OP_build_binary_op(compiler, $2, $1, $3);
    }
  | operator STREQ operator
    {
      $$ = SPVM_OP_build_binary_op(compiler, $2, $1, $3);
    }
  | operator STRNE operator
    {
      $$ = SPVM_OP_build_binary_op(compiler, $2, $1, $3);
    }
  | operator STRGT operator
    {
      $$ = SPVM_OP_build_binary_op(compiler, $2, $1, $3);
    }
  | operator STRGE operator
    {
      $$ = SPVM_OP_build_binary_op(compiler, $2, $1, $3);
    }
  | operator STRLT operator
    {
      $$ = SPVM_OP_build_binary_op(compiler, $2, $1, $3);
    }
  | operator STRLE operator
    {
      $$ = SPVM_OP_build_binary_op(compiler, $2, $1, $3);
    }
  | operator STRING_CMP operator
    {
      $$ = SPVM_OP_build_binary_op(compiler, $2, $1, $3);
    }

string_concatenation
  : operator '.' operator
    {
      $$ = SPVM_OP_build_binary_op(compiler, $2, $1, $3);
    }

logical_operator
  : operator LOGICAL_OR operator
    {
      $$ = SPVM_OP_build_logical_or(compiler, $2, $1, $3);
    }
  | operator LOGICAL_AND operator
    {
      $$ = SPVM_OP_build_logical_and(compiler, $2, $1, $3);
    }
  | LOGICAL_NOT operator
    {
      $$ = SPVM_OP_build_logical_not(compiler, $1, $2);
    }

defined_or
  : operator DEFINED_OR operator
    {
      $$ = SPVM_OP_build_defined_or(compiler, $2, $1, $3);
    }

type_check
  : operator ISA runtime_type
    {
      $$ = SPVM_OP_build_type_check(compiler, $2, $1, $3);
    }
  | operator ISA_ERROR runtime_type
    {
      $$ = SPVM_OP_build_type_check(compiler, $2, $1, $3);
    }
  | operator IS_TYPE runtime_type
    {
      $$ = SPVM_OP_build_type_check(compiler, $2, $1, $3);
    }
  | operator IS_ERROR runtime_type
    {
      $$ = SPVM_OP_build_type_check(compiler, $2, $1, $3);
    }
  | operator IS_COMPILE_TYPE type
    {
      $$ = SPVM_OP_build_type_check(compiler, $2, $1, $3);
    }

type_cast
  : '(' type ')' operator %prec CONVERT
    {
      SPVM_OP* op_type_cast = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE_CAST, $2->file, $2->line);
      $$ = SPVM_OP_build_type_cast(compiler, op_type_cast, $2, $4);
    }
  | operator ARROW '(' type ')' %prec CONVERT
    {
      SPVM_OP* op_type_cast = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE_CAST, $4->file, $4->line);
      $$ = SPVM_OP_build_type_cast(compiler, op_type_cast, $4, $1);
    }

can
  : operator CAN method_name
    {
      $$ = SPVM_OP_build_can(compiler, $2, $1, $3);
    }
  | operator CAN CONSTANT
    {
      $$ = SPVM_OP_build_can(compiler, $2, $1, $3);
    }

assign
  : operator ASSIGN operator
    {
      $$ = SPVM_OP_build_assign(compiler, $2, $1, $3);
    }
  | operator SPECIAL_ASSIGN operator
    {
      $$ = SPVM_OP_build_special_assign(compiler, $2, $1, $3);
    }

new
  : NEW basic_type
    {
      $$ = SPVM_OP_build_new(compiler, $1, $2, NULL);
    }
  | NEW array_type_with_length
    {
      SPVM_OP* op_length = $2->last;
      SPVM_OP_cut_op(compiler, $2->last);
      $$ = SPVM_OP_build_new(compiler, $1, $2, op_length);
    }
  | anon_method
    {
      $$ = SPVM_OP_build_anon_method(compiler, $1);
    }

array_init
  : '[' opt_operators ']'
    {
      SPVM_OP* op_array_init = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_INIT, compiler->current_file, compiler->current_line);
      int32_t is_key_values = 0;
      $$ = SPVM_OP_build_array_init(compiler, op_array_init, $2, is_key_values);
    }
  | '{' operators '}'
    {
      SPVM_OP* op_array_init = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_INIT, compiler->current_file, compiler->current_line);
      int32_t is_key_values = 1;
      $$ = SPVM_OP_build_array_init(compiler, op_array_init, $2, is_key_values);
    }
  | '{' '}'
    {
      SPVM_OP* op_array_init = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_INIT, compiler->current_file, compiler->current_line);
      int32_t is_key_values = 1;
      SPVM_OP* op_list_elements = SPVM_OP_new_op_list(compiler, compiler->current_file, compiler->current_line);
      $$ = SPVM_OP_build_array_init(compiler, op_array_init, op_list_elements, is_key_values);
    }

call_method
  : OUTMOST_CLASS SYMBOL_NAME '(' opt_operators  ')'
    {
      SPVM_OP* op_call_method = SPVM_OP_new_op_call_method(compiler, compiler->current_file, compiler->current_line);
      $$ = SPVM_OP_build_call_method(compiler, op_call_method, $1, $2, $4);
    }
  | OUTMOST_CLASS SYMBOL_NAME
    {
      SPVM_OP* op_call_method = SPVM_OP_new_op_call_method(compiler, compiler->current_file, compiler->current_line);
      SPVM_OP* op_operators = SPVM_OP_new_op_list(compiler, $1->file, $2->line);
      $$ = SPVM_OP_build_call_method(compiler, op_call_method, $1, $2, op_operators);
    }
  | basic_type ARROW method_name '(' opt_operators  ')'
    {
      SPVM_OP* op_call_method = SPVM_OP_new_op_call_method(compiler, compiler->current_file, compiler->current_line);
      $$ = SPVM_OP_build_call_method(compiler, op_call_method, $1, $3, $5);
    }
  | basic_type ARROW method_name
    {
      SPVM_OP* op_call_method = SPVM_OP_new_op_call_method(compiler, compiler->current_file, compiler->current_line);
      SPVM_OP* op_operators = SPVM_OP_new_op_list(compiler, $1->file, $2->line);
      $$ = SPVM_OP_build_call_method(compiler, op_call_method, $1, $3, op_operators);
    }
  | operator ARROW method_name '(' opt_operators ')'
    {
      SPVM_OP* op_call_method = SPVM_OP_new_op_call_method(compiler, compiler->current_file, compiler->current_line);
      $$ = SPVM_OP_build_call_method(compiler, op_call_method, $1, $3, $5);
    }
  | operator ARROW method_name
    {
      SPVM_OP* op_call_method = SPVM_OP_new_op_call_method(compiler, compiler->current_file, compiler->current_line);
      SPVM_OP* op_operators = SPVM_OP_new_op_list(compiler, $1->file, $2->line);
      $$ = SPVM_OP_build_call_method(compiler, op_call_method, $1, $3, op_operators);
    }
  | operator ARROW '(' opt_operators ')'
    {
      SPVM_OP* op_call_method = SPVM_OP_new_op_call_method(compiler, compiler->current_file, compiler->current_line);
      SPVM_OP* op_method_name = SPVM_OP_new_op_name(compiler, "", $2->file, $2->line);
      $$ = SPVM_OP_build_call_method(compiler, op_call_method, $1, op_method_name, $4);
    }

array_element_access
  : operator ARROW '[' operator ']'
    {
      SPVM_OP* op_array_element_access = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_ELEMENT_ACCESS, compiler->current_file, compiler->current_line);
      $$ = SPVM_OP_build_element_access(compiler, op_array_element_access, $1, $4);
    }
  | array_element_access '[' operator ']'
    {
      SPVM_OP* op_array_element_access = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_ELEMENT_ACCESS, compiler->current_file, compiler->current_line);
      $$ = SPVM_OP_build_element_access(compiler, op_array_element_access, $1, $3);
    }
  | field_access '[' operator ']'
    {
      SPVM_OP* op_array_element_access = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_ELEMENT_ACCESS, compiler->current_file, compiler->current_line);
      $$ = SPVM_OP_build_element_access(compiler, op_array_element_access, $1, $3);
    }
  | hash_value_access '[' operator ']'
    {
      SPVM_OP* op_array_element_access = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_ELEMENT_ACCESS, compiler->current_file, compiler->current_line);
      $$ = SPVM_OP_build_element_access(compiler, op_array_element_access, $1, $3);
    }

field_access
  : operator ARROW '{' field_name '}'
    {
      SPVM_OP* op_field_access = SPVM_OP_new_op_field_access(compiler, compiler->current_file, compiler->current_line);
      $$ = SPVM_OP_build_field_access(compiler, op_field_access, $1, $4);
    }
  | array_element_access '{' field_name '}'
    {
      SPVM_OP* op_field_access = SPVM_OP_new_op_field_access(compiler, compiler->current_file, compiler->current_line);
      $$ = SPVM_OP_build_field_access(compiler, op_field_access, $1, $3);
    }
  | field_access '{' field_name '}'
    {
      SPVM_OP* op_field_access = SPVM_OP_new_op_field_access(compiler, compiler->current_file, compiler->current_line);
      $$ = SPVM_OP_build_field_access(compiler, op_field_access, $1, $3);
    }
  | hash_value_access '{' field_name '}'
    {
      SPVM_OP* op_field_access = SPVM_OP_new_op_field_access(compiler, compiler->current_file, compiler->current_line);
      $$ = SPVM_OP_build_field_access(compiler, op_field_access, $1, $3);
    }

hash_value_access
  : operator ARROW '{' operator '}'
    {
      SPVM_OP* op_hash_value_access = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_HASH_VALUE_ACCESS, compiler->current_file, compiler->current_line);
      $$ = SPVM_OP_build_binary_op(compiler, op_hash_value_access, $1, $4);
    }
  | array_element_access '{' operator '}'
    {
      SPVM_OP* op_hash_value_access = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_HASH_VALUE_ACCESS, compiler->current_file, compiler->current_line);
      $$ = SPVM_OP_build_binary_op(compiler, op_hash_value_access, $1, $3);
    }
  | field_access '{' operator '}'
    {
      SPVM_OP* op_hash_value_access = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_HASH_VALUE_ACCESS, compiler->current_file, compiler->current_line);
      $$ = SPVM_OP_build_binary_op(compiler, op_hash_value_access, $1, $3);
    }
  | hash_value_access '{' operator '}'
    {
      SPVM_OP* op_hash_value_access = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_HASH_VALUE_ACCESS, compiler->current_file, compiler->current_line);
      $$ = SPVM_OP_build_binary_op(compiler, op_hash_value_access, $1, $3);
    }

weaken_field
  : WEAKEN var ARROW '{' field_name '}'
    {
      SPVM_OP* op_field_access = SPVM_OP_new_op_field_access(compiler, compiler->current_file, compiler->current_line);
      SPVM_OP_build_field_access(compiler, op_field_access, $2, $5);
      $$ = SPVM_OP_build_weaken_field(compiler, $1, op_field_access);
    }

unweaken_field
  : UNWEAKEN var ARROW '{' field_name '}'
    {
      SPVM_OP* op_field_access = SPVM_OP_new_op_field_access(compiler, compiler->current_file, compiler->current_line);
      SPVM_OP_build_field_access(compiler, op_field_access, $2, $5);
      $$ = SPVM_OP_build_unweaken_field(compiler, $1, op_field_access);
    }

isweak_field
  : ISWEAK var ARROW '{' field_name '}'
    {
      SPVM_OP* op_field_access = SPVM_OP_new_op_field_access(compiler, compiler->current_file, compiler->current_line);
      SPVM_OP_build_field_access(compiler, op_field_access, $2, $5);
      $$ = SPVM_OP_build_isweak_field(compiler, $1, op_field_access);
    }

warn
  : WARN operator
    {
      $$ = SPVM_OP_build_warn(compiler, $1, $2);
    }
  | WARN
    {
      $$ = SPVM_OP_build_warn(compiler, $1, NULL);
    }

warn_level
  : WARN_LEVEL operator ',' operator
    {
      $$ = SPVM_OP_build_warn_level(compiler, $1, $2, $4);
    }
    
copy_fields
  : COPY_FIELDS operator ',' operator ',' type
    {
      $$ = SPVM_OP_build_copy_fields(compiler, $1, $2, $4, $6);
    }

exists
  : EXISTS var ARROW '{' field_name '}'
    {
      SPVM_OP* op_field_access = SPVM_OP_new_op_field_access(compiler, compiler->current_file, compiler->current_line);
      SPVM_OP_build_field_access(compiler, op_field_access, $2, $5);
      $$ = SPVM_OP_build_exists(compiler, $1, op_field_access);
    }

delete
  : DELETE var ARROW '{' field_name '}'
    {
      SPVM_OP* op_field_access = SPVM_OP_new_op_field_access(compiler, compiler->current_file, compiler->current_line);
      SPVM_OP_build_field_access(compiler, op_field_access, $2, $5);
      $$ = SPVM_OP_build_delete(compiler, $1, op_field_access);
    }

caller
  : CALLER
    {
      $$ = SPVM_OP_build_caller(compiler, $1, NULL);
    }
  | CALLER operator
    {
      $$ = SPVM_OP_build_caller(compiler, $1, $2);
    }

break_point
  : BREAK_POINT
    {
      $$ = SPVM_OP_build_caller(compiler, $1, NULL);
    }
%%
