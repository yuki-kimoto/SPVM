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

%token <opval> CLASS HAS METHOD OUR ENUM MY USE AS REQUIRE ALIAS ALLOW CURRENT_CLASS MUTABLE
%token <opval> ATTRIBUTE MAKE_READ_ONLY INTERFACE EVAL_ERROR_ID ARGS_WIDTH VERSION_DECL
%token <opval> IF UNLESS ELSIF ELSE FOR WHILE LAST NEXT SWITCH CASE DEFAULT BREAK EVAL
%token <opval> SYMBOL_NAME VAR_NAME CONSTANT EXCEPTION_VAR
%token <opval> UNDEF VOID BYTE SHORT INT LONG FLOAT DOUBLE STRING OBJECT TRUE FALSE END_OF_FILE
%token <opval> FATCAMMA RW RO WO INIT NEW OF BASIC_TYPE_ID EXTENDS SUPER
%token <opval> RETURN WEAKEN DIE WARN PRINT SAY CURRENT_CLASS_NAME UNWEAKEN '[' '{' '('

%type <opval> grammar
%type <opval> opt_classes classes class class_block version_decl
%type <opval> opt_definitions definitions definition
%type <opval> enumeration enumeration_block opt_enumeration_values enumeration_values enumeration_value
%type <opval> method anon_method opt_args args arg use require alias our has has_for_anon_list has_for_anon
%type <opval> opt_attributes attributes
%type <opval> opt_statements statements statement if_statement else_statement 
%type <opval> for_statement while_statement foreach_statement
%type <opval> switch_statement case_statement case_statements opt_case_statements default_statement
%type <opval> block eval_block init_block switch_block if_require_statement
%type <opval> unary_operator binary_operator comparison_operator isa isa_error is_type is_error is_compile_type
%type <opval> call_method
%type <opval> array_access field_access weaken_field unweaken_field isweak_field convert array_length
%type <opval> assign inc dec allow can
%type <opval> new array_init die warn opt_extends
%type <opval> var_decl var interface union_type
%type <opval> operator opt_operators operators opt_operator logical_operator void_return_operator
%type <opval> field_name method_name alias_name is_read_only
%type <opval> type qualified_type basic_type array_type class_type opt_class_type
%type <opval> array_type_with_length ref_type  return_type type_comment opt_type_comment

%right <opval> ASSIGN SPECIAL_ASSIGN
%left <opval> LOGICAL_OR
%left <opval> LOGICAL_AND
%left <opval> BIT_OR BIT_XOR
%left <opval> BIT_AND
%nonassoc <opval> NUMEQ NUMNE STREQ STRNE
%nonassoc <opval> NUMGT NUMGE NUMLT NUMLE STRGT STRGE STRLT STRLE ISA ISA_ERROR IS_TYPE IS_ERROR IS_COMPILE_TYPE NUMERIC_CMP STRING_CMP CAN
%left <opval> SHIFT
%left <opval> '+' '-' '.'
%left <opval> '*' DIVIDE DIVIDE_UNSIGNED_INT DIVIDE_UNSIGNED_LONG MODULO  MODULO_UNSIGNED_INT MODULO_UNSIGNED_LONG
%right <opval> LOGICAL_NOT BIT_NOT '@' CREATE_REF DEREF PLUS MINUS CONVERT SCALAR STRING_LENGTH ISWEAK REFCNT TYPE_NAME COMPILE_TYPE_NAME DUMP NEW_STRING_LEN IS_READ_ONLY COPY
%nonassoc <opval> INC DEC
%left <opval> ARROW

%%

grammar
  : opt_classes

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
  : CLASS opt_class_type opt_extends class_block END_OF_FILE
    {
      $$ = SPVM_OP_build_class(compiler, $1, $2, $4, NULL, $3);
    }
  | CLASS opt_class_type opt_extends ':' opt_attributes class_block END_OF_FILE
    {
      $$ = SPVM_OP_build_class(compiler, $1, $2, $6, $5, $3);
    }
  | CLASS opt_class_type opt_extends ';' END_OF_FILE
    {
      $$ = SPVM_OP_build_class(compiler, $1, $2, NULL, NULL, $3);
    }
  | CLASS opt_class_type opt_extends ':' opt_attributes ';' END_OF_FILE
    {
      $$ = SPVM_OP_build_class(compiler, $1, $2, NULL, $5, $3);
    }

opt_class_type
  : /* Empty */
    {
      $$ = NULL;
    }
  | class_type

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
  | use
  | alias
  | allow
  | interface
  | init_block
  | enumeration
  | our
  | has ';'
  | method

init_block
  : INIT block
    { 
      $$ = SPVM_OP_build_init_block(compiler, $1, $2);
    }

version_decl
  : VERSION_DECL CONSTANT ';'
    {
      $$ = SPVM_OP_build_version_decl(compiler, $1, $2);
    }

use
  : USE basic_type ';'
    {
      int32_t is_require = 0;
      SPVM_OP* op_name_alias = NULL;
      $$ = SPVM_OP_build_use(compiler, $1, $2, op_name_alias, is_require);
    }
  | USE basic_type AS alias_name ';'
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

alias
  : ALIAS basic_type AS alias_name ';'
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
      $$ = SPVM_OP_build_implement(compiler, $1, $2);
    }

enumeration
  : opt_attributes ENUM enumeration_block
    {
      $$ = SPVM_OP_build_enumeration_definition(compiler, $2, $3, $1);
    }

enumeration_block 
  : '{' opt_enumeration_values '}'
    {
      SPVM_OP* op_enum_block = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ENUM_BLOCK, $1->file, $1->line);
      SPVM_OP_insert_child(compiler, op_enum_block, op_enum_block->last, $2);
      $$ = op_enum_block;
    }

opt_enumeration_values
  : /* Empty */
    {
      $$ = SPVM_OP_new_op_list(compiler, compiler->current_file, compiler->current_line);
    }
  | enumeration_values
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
    
enumeration_values
  : enumeration_values ',' enumeration_value 
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
  | enumeration_values ','
  | enumeration_value
  
enumeration_value
  : method_name
    {
      $$ = SPVM_OP_build_enumeration_value(compiler, $1, NULL);
    }
  | method_name ASSIGN CONSTANT
    {
      $$ = SPVM_OP_build_enumeration_value(compiler, $1, $3);
    }

our
  : OUR VAR_NAME ':' opt_attributes qualified_type opt_type_comment ';'
    {
      $$ = SPVM_OP_build_class_var_definition(compiler, $1, $2, $4, $5);
    }

has
  : HAS field_name ':' opt_attributes qualified_type opt_type_comment
    {
      $$ = SPVM_OP_build_field_definition(compiler, $1, $2, $4, $5);
    }

method
  : opt_attributes METHOD method_name ':' return_type '(' opt_args ')' block
     {
       $$ = SPVM_OP_build_method_definition(compiler, $2, $3, $5, $7, $1, $9, NULL, 0, 0);
     }
  | opt_attributes METHOD method_name ':' return_type '(' opt_args ')' ';'
     {
       $$ = SPVM_OP_build_method_definition(compiler, $2, $3, $5, $7, $1, NULL, NULL, 0, 0);
     }
  | opt_attributes METHOD ':' return_type '(' opt_args ')' block
     {
       $$ = SPVM_OP_build_method_definition(compiler, $2, NULL, $4, $6, $1, $8, NULL, 0, 0);
     }
  | opt_attributes METHOD ':' return_type '(' opt_args ')' ';'
     {
       $$ = SPVM_OP_build_method_definition(compiler, $2, NULL, $4, $6, $1, NULL, NULL, 0, 0);
     }

anon_method
  : opt_attributes METHOD ':' return_type '(' opt_args ')' block
     {
       int32_t is_init = 0;
       int32_t is_anon = 1;
       $$ = SPVM_OP_build_method_definition(compiler, $2, NULL, $4, $6, $1, $8, NULL, is_init, is_anon);
     }
  | '[' has_for_anon_list ']' opt_attributes METHOD ':' return_type '(' opt_args ')' block
     {
       SPVM_OP* op_list_args;
       if ($2->id == SPVM_OP_C_ID_LIST) {
         op_list_args = $2;
       }
       else {
         op_list_args = SPVM_OP_new_op_list(compiler, $2->file, $2->line);
         SPVM_OP_insert_child(compiler, op_list_args, op_list_args->last, $2);
       }
       
       int32_t is_init = 0;
       int32_t is_anon = 1;
       $$ = SPVM_OP_build_method_definition(compiler, $5, NULL, $7, $9, $4, $11, op_list_args, is_init, is_anon);
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
  : var ':' qualified_type opt_type_comment
    {
      $$ = SPVM_OP_build_arg(compiler, $1, $3, NULL, NULL);
    }
  | var ':' qualified_type opt_type_comment ASSIGN operator
    {
      $$ = SPVM_OP_build_arg(compiler, $1, $3, NULL, $6);
    }

has_for_anon_list
  : has_for_anon_list ',' has_for_anon
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
  | has_for_anon_list ','
  | has_for_anon

has_for_anon
  : HAS field_name ':' opt_attributes qualified_type opt_type_comment
    {
      $$ = SPVM_OP_build_anon_method_field_definition(compiler, $1, $2, $4, $5, NULL);
    }
  | HAS field_name ':' opt_attributes qualified_type opt_type_comment ASSIGN operator
    {
      $$ = SPVM_OP_build_anon_method_field_definition(compiler, $1, $2, $4, $5, $8);
    }
  | var ':' opt_attributes qualified_type opt_type_comment
    {
      SPVM_OP* op_field = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_FIELD, $1->file, $1->line);
      
      $$ = SPVM_OP_build_anon_method_field_definition(compiler, op_field, NULL, $3, $4, $1);
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
  | operator ';'
    {
      $$ = SPVM_OP_build_operator_statement(compiler, $1);
    }
  | void_return_operator ';'
  | ';'
    {
      $$ = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_DO_NOTHING, compiler->current_file, compiler->current_line);
    }
  | die ';'

die
  : DIE operator
    {
      $$ = SPVM_OP_build_die(compiler, $1, $2, NULL);
    }
  | DIE
    {
      $$ = SPVM_OP_build_die(compiler, $1, NULL, NULL);
    }
  | DIE type operator
    {
      $$ = SPVM_OP_build_die(compiler, $1, $3, $2);
    }
  | DIE type
    {
      $$ = SPVM_OP_build_die(compiler, $1, NULL, $2);
    }
  | DIE operator ',' operator
    {
      $$ = SPVM_OP_build_die(compiler, $1, $4, $2);
    }

void_return_operator
  : warn
  | PRINT operator
    {
      $$ = SPVM_OP_build_print(compiler, $1, $2);
    }
  | SAY operator
    {
      $$ = SPVM_OP_build_print(compiler, $1, $2);
    }
  | weaken_field
  | unweaken_field
  | MAKE_READ_ONLY operator
    {
      $$ = SPVM_OP_build_make_read_only(compiler, $1, $2);
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

for_statement
  : FOR '(' opt_operator ';' operator ';' opt_operator ')' block
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
      op_block->uv.block->id = SPVM_BLOCK_C_ID_SWITCH;
      $$ = SPVM_OP_build_switch_block(compiler, op_block, $2, NULL);
    }
  | '{' opt_case_statements default_statement '}'
    {
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, compiler->current_file, compiler->current_line);
      op_block->uv.block->id = SPVM_BLOCK_C_ID_SWITCH;
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
      
      // if is wraped with block to allow the following syntax
      //  if (var_decl $var = 3) { ... }
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, $1->file, $1->line);
      SPVM_OP_insert_child(compiler, op_block, op_block->last, op_if);
      
      $$ = op_block;
    }
  | UNLESS '(' operator ')' block else_statement
    {
      SPVM_OP* op_if = SPVM_OP_build_if_statement(compiler, $1, $3, $5, $6, 0);
      
      // if is wraped with block to allow the following syntax
      //  if (var_decl $var = 3) { ... }
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
      $$ = SPVM_OP_build_if_statement(compiler, $1, $3, $5, $6, 0);
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
  | call_method
  | field_access
  | array_access
  | convert
  | new
  | array_init
  | array_length
  | var_decl
  | unary_operator
  | binary_operator
  | assign
  | inc
  | dec
  | '(' operators ')'
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
  | CURRENT_CLASS_NAME
  | isweak_field
  | comparison_operator
  | isa
  | isa_error
  | is_type
  | is_error
  | is_compile_type
  | TRUE
    {
      $$ = SPVM_OP_new_op_true(compiler, $1);
    }
  | FALSE
    {
      $$ = SPVM_OP_new_op_false(compiler, $1);
    }
  | is_read_only
  | can
  | logical_operator
  | BASIC_TYPE_ID type
    {
      $$ = SPVM_OP_build_basic_type_id(compiler, $1, $2);
    }
  | EVAL_ERROR_ID
  | ARGS_WIDTH

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
  | REFCNT operator
    {
      $$ = SPVM_OP_build_unary_op_var(compiler, $1, $2);
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
  | DEREF var
    {
      $$ = SPVM_OP_build_unary_op_var(compiler, $1, $2);
    }
  | CREATE_REF operator
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

is_read_only
  : IS_READ_ONLY operator
    {
      $$ = SPVM_OP_build_is_read_only(compiler, $1, $2);
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
  | operator BIT_XOR operator
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
  | operator '.' operator
    {
      $$ = SPVM_OP_build_binary_op(compiler, $2, $1, $3);
    }

comparison_operator
  : operator NUMEQ operator
    {
      $$ = SPVM_OP_build_comparison_op(compiler, $2, $1, $3);
    }
  | operator NUMNE operator
    {
      $$ = SPVM_OP_build_comparison_op(compiler, $2, $1, $3);
    }
  | operator NUMGT operator
    {
      $$ = SPVM_OP_build_comparison_op(compiler, $2, $1, $3);
    }
  | operator NUMGE operator
    {
      $$ = SPVM_OP_build_comparison_op(compiler, $2, $1, $3);
    }
  | operator NUMLT operator
    {
      $$ = SPVM_OP_build_comparison_op(compiler, $2, $1, $3);
    }
  | operator NUMLE operator
    {
      $$ = SPVM_OP_build_comparison_op(compiler, $2, $1, $3);
    }
  | operator NUMERIC_CMP operator
    {
      $$ = SPVM_OP_build_comparison_op(compiler, $2, $1, $3);
    }
  | operator STREQ operator
    {
      $$ = SPVM_OP_build_comparison_op(compiler, $2, $1, $3);
    }
  | operator STRNE operator
    {
      $$ = SPVM_OP_build_comparison_op(compiler, $2, $1, $3);
    }
  | operator STRGT operator
    {
      $$ = SPVM_OP_build_comparison_op(compiler, $2, $1, $3);
    }
  | operator STRGE operator
    {
      $$ = SPVM_OP_build_comparison_op(compiler, $2, $1, $3);
    }
  | operator STRLT operator
    {
      $$ = SPVM_OP_build_comparison_op(compiler, $2, $1, $3);
    }
  | operator STRLE operator
    {
      $$ = SPVM_OP_build_comparison_op(compiler, $2, $1, $3);
    }
  | operator STRING_CMP operator
    {
      $$ = SPVM_OP_build_comparison_op(compiler, $2, $1, $3);
    }

isa
  : operator ISA type
    {
      $$ = SPVM_OP_build_isa(compiler, $2, $1, $3);
    }

isa_error
  : operator ISA_ERROR type
    {
      $$ = SPVM_OP_build_isa_error(compiler, $2, $1, $3);
    }

is_type
  : operator IS_TYPE type
    {
      $$ = SPVM_OP_build_is_type(compiler, $2, $1, $3);
    }
    
is_error
  : operator IS_ERROR type
    {
      $$ = SPVM_OP_build_is_error(compiler, $2, $1, $3);
    }
    
is_compile_type
  : operator IS_COMPILE_TYPE type
    {
      $$ = SPVM_OP_build_is_compile_type(compiler, $2, $1, $3);
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

convert
  : '(' qualified_type ')' operator %prec CONVERT
    {
      SPVM_OP* op_convert = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE_CAST, $2->file, $2->line);
      $$ = SPVM_OP_build_type_cast(compiler, op_convert, $2, $4, NULL);
    }
  | operator ARROW '(' qualified_type ')' %prec CONVERT
    {
      SPVM_OP* op_convert = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE_CAST, $4->file, $4->line);
      $$ = SPVM_OP_build_type_cast(compiler, op_convert, $4, $1, NULL);
    }

call_method
  : CURRENT_CLASS SYMBOL_NAME '(' opt_operators  ')'
    {
      SPVM_OP* op_call_method = SPVM_OP_new_op_call_method(compiler, compiler->current_file, compiler->current_line);
      $$ = SPVM_OP_build_call_method(compiler, op_call_method, $1, $2, $4);
    }
  | CURRENT_CLASS SYMBOL_NAME
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

array_access
  : operator ARROW '[' operator ']'
    {
      SPVM_OP* op_array_access = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_ACCESS, compiler->current_file, compiler->current_line);
      $$ = SPVM_OP_build_array_access(compiler, op_array_access, $1, $4);
    }
  | array_access '[' operator ']'
    {
      SPVM_OP* op_array_access = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_ACCESS, compiler->current_file, compiler->current_line);
      $$ = SPVM_OP_build_array_access(compiler, op_array_access, $1, $3);
    }
  | field_access '[' operator ']'
    {
      SPVM_OP* op_array_access = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_ACCESS, compiler->current_file, compiler->current_line);
      $$ = SPVM_OP_build_array_access(compiler, op_array_access, $1, $3);
    }

field_access
  : operator ARROW '{' field_name '}'
    {
      SPVM_OP* op_field_access = SPVM_OP_new_op_field_access(compiler, compiler->current_file, compiler->current_line);
      $$ = SPVM_OP_build_field_access(compiler, op_field_access, $1, $4);
    }
  | field_access '{' field_name '}'
    {
      SPVM_OP* op_field_access = SPVM_OP_new_op_field_access(compiler, compiler->current_file, compiler->current_line);
      $$ = SPVM_OP_build_field_access(compiler, op_field_access, $1, $3);
    }
  | array_access '{' field_name '}'
    {
      SPVM_OP* op_array_access = $1;
      SPVM_OP* op_field_access = SPVM_OP_new_op_field_access(compiler, compiler->current_file, compiler->current_line);
      $$ = SPVM_OP_build_field_access(compiler, op_field_access, op_array_access, $3);
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

can
  : operator CAN method_name
    {
      $$ = SPVM_OP_build_can(compiler, $2, $1, $3);
    }
  | operator CAN CONSTANT
    {
      $$ = SPVM_OP_build_can(compiler, $2, $1, $3);
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

var_decl
  : MY var ':' qualified_type opt_type_comment
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

qualified_type
  : type
  | MUTABLE type {
    $$ = SPVM_OP_build_mutable_type(compiler, $2);
  }

type
  : basic_type
  | array_type
  | ref_type

class_type
  : basic_type

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
      $$ = SPVM_OP_build_array_type(compiler, $1, NULL);
    }
  | array_type '[' ']'
    {
      $$ = SPVM_OP_build_array_type(compiler, $1, NULL);
    }

array_type_with_length
  : basic_type '[' operator ']'
    {
      $$ = SPVM_OP_build_array_type(compiler, $1, $3);
    }
  | array_type '[' operator ']'
    {
      $$ = SPVM_OP_build_array_type(compiler, $1, $3);
    }

return_type
  : qualified_type opt_type_comment
  | VOID
    {
      $$ = SPVM_OP_new_op_void_type(compiler, compiler->current_file, compiler->current_line);
    }

opt_type_comment
  : /* Empty */
    {
      $$ = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_DO_NOTHING, compiler->current_file, compiler->current_line);
    }
  | type_comment

type_comment
  : OF union_type
    {
      $$ = $2;
    }

union_type
  : union_type BIT_OR type
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
  | type
    {
      $$ = $1;
    }

field_name
  : SYMBOL_NAME

method_name
  : SYMBOL_NAME

alias_name
  : SYMBOL_NAME

%%
