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
  #include "spvm_class.h"
  #include "spvm_descriptor.h"
  #include "spvm_constant_string.h"
%}

%token <opval> CLASS HAS METHOD OUR ENUM MY USE AS REQUIRE ALIAS ALLOW CURRENT_CLASS MUTABLE
%token <opval> DESCRIPTOR MAKE_READ_ONLY INTERFACE ERRNO
%token <opval> IF UNLESS ELSIF ELSE FOR WHILE LAST NEXT SWITCH CASE DEFAULT BREAK EVAL
%token <opval> SYMBOL_NAME VAR_NAME CONSTANT EXCEPTION_VAR
%token <opval> UNDEF VOID BYTE SHORT INT LONG FLOAT DOUBLE STRING OBJECT TRUE FALSE END_OF_FILE
%token <opval> DOT3 FATCAMMA RW RO WO INIT NEW OF CLASS_ID
%token <opval> RETURN WEAKEN DIE WARN PRINT CURRENT_CLASS_NAME UNWEAKEN '[' '{' '('

%type <opval> grammar
%type <opval> opt_classes classes class class_block
%type <opval> opt_declarations declarations declaration
%type <opval> enumeration enumeration_block opt_enumeration_values enumeration_values enumeration_value
%type <opval> method anon_method opt_args args arg has use require alias our
%type <opval> opt_descriptors descriptors
%type <opval> opt_statements statements statement if_statement else_statement 
%type <opval> for_statement while_statement 
%type <opval> switch_statement case_statement case_statements opt_case_statements default_statement
%type <opval> block eval_block init_block switch_block if_require_statement
%type <opval> unary_operator binary_operator comparison_operator isa
%type <opval> call_spvm_method opt_vaarg
%type <opval> array_access field_access weaken_field unweaken_field isweak_field convert array_length
%type <opval> assign inc dec allow has_impl
%type <opval> new array_init
%type <opval> var_decl var interface
%type <opval> operator opt_operators operators opt_operator logical_operator
%type <opval> field_name method_name class_name class_alias_name is_read_only
%type <opval> type qualified_type basic_type array_type
%type <opval> array_type_with_length ref_type  return_type type_comment opt_type_comment

%right <opval> ASSIGN SPECIAL_ASSIGN
%left <opval> LOGICAL_OR
%left <opval> LOGICAL_AND
%left <opval> BIT_OR BIT_XOR
%left <opval> BIT_AND
%nonassoc <opval> NUMEQ NUMNE STREQ STRNE
%nonassoc <opval> NUMGT NUMGE NUMLT NUMLE STRGT STRGE STRLT STRLE ISA NUMERIC_CMP STRING_CMP
%left <opval> SHIFT
%left <opval> '+' '-' '.'
%left <opval> '*' DIVIDE DIVIDE_UNSIGNED_INT DIVIDE_UNSIGNED_LONG REMAINDER  REMAINDER_UNSIGNED_INT REMAINDER_UNSIGNED_LONG
%right <opval> LOGICAL_NOT BIT_NOT '@' CREATE_REF DEREF PLUS MINUS CONVERT SCALAR STRING_LENGTH ISWEAK REFCNT REFOP DUMP NEW_STRING_LEN IS_READ_ONLY COPY HAS_IMPL SET_ERRNO
%nonassoc <opval> INC DEC
%left <opval> ARROW

%%

grammar
  : opt_classes

opt_classes
  : /* Empty */
    {
      $$ = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
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
  : CLASS basic_type class_block END_OF_FILE
    {
      $$ = SPVM_OP_build_class(compiler, $1, $2, $3, NULL);
    }
  | CLASS basic_type ':' opt_descriptors class_block END_OF_FILE
    {
      $$ = SPVM_OP_build_class(compiler, $1, $2, $5, $4);
    }
  | CLASS basic_type ';' END_OF_FILE
    {
      $$ = SPVM_OP_build_class(compiler, $1, $2, NULL, NULL);
    }
  | CLASS basic_type ':' opt_descriptors ';' END_OF_FILE
    {
      $$ = SPVM_OP_build_class(compiler, $1, $2, NULL, $4);
    }

class_block
  : '{' opt_declarations '}'
    {
      SPVM_OP* op_class_block = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CLASS_BLOCK, $1->file, $1->line);
      SPVM_OP_insert_child(compiler, op_class_block, op_class_block->last, $2);
      $$ = op_class_block;
    }

opt_declarations
  : /* Empty */
    {
      $$ = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    }
  | declarations
    {
      if ($1->id == SPVM_OP_C_ID_LIST) {
        $$ = $1;
      }
      else {
        $$ = SPVM_OP_new_op_list(compiler, $1->file, $1->line);
        SPVM_OP_insert_child(compiler, $$, $$->last, $1);
      }
    }

declarations
  : declarations declaration
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
  | declaration

declaration
  : has
  | method
  | enumeration
  | our
  | use
  | allow
  | interface
  | init_block
  | alias

init_block
  : INIT block
    { 
      SPVM_OP* op_method = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_METHOD, compiler->cur_file, compiler->cur_line);
      SPVM_CONSTANT_STRING* method_name_string = SPVM_CONSTANT_STRING_new(compiler, "INIT", strlen("INIT"));
      const char* method_name = method_name_string->value;
      SPVM_OP* op_method_name = SPVM_OP_new_op_name(compiler, "INIT", compiler->cur_file, compiler->cur_line);
      SPVM_OP* op_void_type = SPVM_OP_new_op_void_type(compiler, compiler->cur_file, compiler->cur_line);

      SPVM_OP* op_list_descriptors = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
      SPVM_OP* op_descriptor_static = SPVM_OP_new_op_descriptor(compiler, SPVM_DESCRIPTOR_C_ID_STATIC, compiler->cur_file, compiler->cur_line);
      SPVM_OP_insert_child(compiler, op_list_descriptors, op_list_descriptors->first, op_descriptor_static);

      $$ = SPVM_OP_build_method(compiler, op_method, op_method_name, op_void_type, NULL, op_list_descriptors, $2, NULL, NULL, 1, 0);
    }
    
use
  : USE class_name ';'
    {
      int32_t is_require = 0;
      SPVM_OP* op_name_class_alias = NULL;
      $$ = SPVM_OP_build_use(compiler, $1, $2, op_name_class_alias, is_require);
    }
  | USE class_name AS class_alias_name ';'
    {
      int32_t is_require = 0;
      $$ = SPVM_OP_build_use(compiler, $1, $2, $4, is_require);
    }

require
  : REQUIRE class_name
    {
      SPVM_OP* op_use = SPVM_OP_new_op_use(compiler, compiler->cur_file, compiler->cur_line);
      int32_t is_require = 1;
      $$ = SPVM_OP_build_use(compiler, op_use, $2, NULL, is_require);
    }

alias
  : ALIAS class_name AS class_alias_name ';'
    {
      SPVM_OP* op_use = SPVM_OP_new_op_use(compiler, compiler->cur_file, compiler->cur_line);
      $$ = SPVM_OP_build_alias(compiler, op_use, $2, $4);
    }

allow
  : ALLOW class_name ';'
    {
      $$ = SPVM_OP_build_allow(compiler, $1, $2);
    }

interface
  : INTERFACE class_name ';'
    {
      $$ = SPVM_OP_build_implement(compiler, $1, $2);
    }

enumeration
  : opt_descriptors ENUM enumeration_block
    {
      $$ = SPVM_OP_build_enumeration(compiler, $2, $3, $1);
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
      $$ = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
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
  : OUR VAR_NAME ':' opt_descriptors qualified_type opt_type_comment ';'
    {
      $$ = SPVM_OP_build_our(compiler, $1, $2, $4, $5);
    }

has
  : HAS field_name ':' opt_descriptors qualified_type opt_type_comment ';'
    {
      $$ = SPVM_OP_build_has(compiler, $1, $2, $4, $5);
    }

method
  : opt_descriptors METHOD method_name ':' return_type '(' opt_args opt_vaarg')' block
     {
       $$ = SPVM_OP_build_method(compiler, $2, $3, $5, $7, $1, $10, NULL, $8, 0, 0);
     }
  | opt_descriptors METHOD method_name ':' return_type '(' opt_args opt_vaarg')' ';'
     {
       $$ = SPVM_OP_build_method(compiler, $2, $3, $5, $7, $1, NULL, NULL, $8, 0, 0);
     }
  | opt_descriptors METHOD ':' return_type '(' opt_args opt_vaarg')' block
     {
       $$ = SPVM_OP_build_method(compiler, $2, NULL, $4, $6, $1, $9, NULL, $7, 0, 0);
     }
  | opt_descriptors METHOD ':' return_type '(' opt_args opt_vaarg ')' ';'
     {
       $$ = SPVM_OP_build_method(compiler, $2, NULL, $4, $6, $1, NULL, NULL, $7, 0, 0);
     }

anon_method
  : opt_descriptors METHOD ':' return_type '(' opt_args opt_vaarg')' block
     {
       int32_t is_init = 0;
       int32_t is_anon = 1;
       $$ = SPVM_OP_build_method(compiler, $2, NULL, $4, $6, $1, $9, NULL, $7, is_init, is_anon);
     }
  | '[' args ']' opt_descriptors METHOD ':' return_type '(' opt_args opt_vaarg')' block
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
       $$ = SPVM_OP_build_method(compiler, $5, NULL, $7, $9, $4, $12, op_list_args, $10, is_init, is_anon);
     }

opt_args
  : /* Empty */
    {
      $$ = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
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
      $$ = SPVM_OP_build_arg(compiler, $1, $3, NULL);
    }

opt_vaarg
  : /* Empty */
    {
      $$ = NULL;
    }
  | DOT3

opt_descriptors
  : /* Empty */
    {
      $$ = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    }
  | descriptors
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
    
descriptors
  : descriptors DESCRIPTOR
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
  | DESCRIPTOR

opt_statements
  : /* Empty */
    {
      $$ = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
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
  | while_statement
  | block
  | switch_statement
  | case_statement
  | default_statement
  | eval_block
  | if_require_statement
  | operator ';'
    {
      $$ = SPVM_OP_build_value_op_statement(compiler, $1);
    }
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
  | DIE operator ';'
    {
      $$ = SPVM_OP_build_die(compiler, $1, $2);
    }
  | DIE ';'
    {
      $$ = SPVM_OP_build_die(compiler, $1, NULL);
    }
  | WARN operator ';'
    {
      $$ = SPVM_OP_build_warn(compiler, $1, $2);
    }
  | PRINT operator ';'
    {
      $$ = SPVM_OP_build_print(compiler, $1, $2);
    }
  | weaken_field ';'
  | unweaken_field ';'
  | ';'
    {
      $$ = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NULL, compiler->cur_file, compiler->cur_line);
    }
  | MAKE_READ_ONLY operator ';'
    {
      $$ = SPVM_OP_build_make_read_only(compiler, $1, $2);
    }

for_statement
  : FOR '(' opt_operator ';' operator ';' opt_operator ')' block
    {
      $$ = SPVM_OP_build_for_statement(compiler, $1, $3, $5, $7, $9);
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
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, compiler->cur_file, compiler->cur_line);
      op_block->uv.block->id = SPVM_BLOCK_C_ID_SWITCH;
      $$ = SPVM_OP_build_switch_block(compiler, op_block, $2, NULL);
    }
  | '{' opt_case_statements default_statement '}'
    {
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, compiler->cur_file, compiler->cur_line);
      op_block->uv.block->id = SPVM_BLOCK_C_ID_SWITCH;
      $$ = SPVM_OP_build_switch_block(compiler, op_block, $2, $3);
    }

opt_case_statements
  : /* Empty */
    {
      $$ = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
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
      SPVM_OP* op_if_require = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_IF_REQUIRE, compiler->cur_file, compiler->cur_line);
      
      $$ = SPVM_OP_build_if_require_statement(compiler, op_if_require, $3, $5, NULL);
    }
  | IF '(' require ')' block ELSE block
    {
      SPVM_OP* op_if_require = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_IF_REQUIRE, compiler->cur_file, compiler->cur_line);
      
      $$ = SPVM_OP_build_if_require_statement(compiler, op_if_require, $3, $5, $7);
    }
if_statement
  : IF '(' operator ')' block else_statement
    {
      SPVM_OP* op_if = SPVM_OP_build_if_statement(compiler, $1, $3, $5, $6);
      
      // if is wraped with block to allow the following syntax
      //  if (var_decl $var = 3) { ... }
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, $1->file, $1->line);
      SPVM_OP_insert_child(compiler, op_block, op_block->last, op_if);
      
      $$ = op_block;
    }
  | UNLESS '(' operator ')' block else_statement
    {
      SPVM_OP* op_if = SPVM_OP_build_if_statement(compiler, $1, $3, $5, $6);
      
      // if is wraped with block to allow the following syntax
      //  if (var_decl $var = 3) { ... }
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, $1->file, $1->line);
      SPVM_OP_insert_child(compiler, op_block, op_block->last, op_if);
      
      $$ = op_block;
    }

else_statement
  : /* NULL */
    {
      $$ = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NULL, compiler->cur_file, compiler->cur_line);
    };
  | ELSE block
    {
      $$ = $2;
    }
  | ELSIF '(' operator ')' block else_statement
    {
      $$ = SPVM_OP_build_if_statement(compiler, $1, $3, $5, $6);
    }

block 
  : '{' opt_statements '}'
    {
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, $1->file, $1->line);
      SPVM_OP_insert_child(compiler, op_block, op_block->last, $2);
      $$ = op_block;
    }

eval_block
  : EVAL block ';'
    {
      $$ = SPVM_OP_build_eval(compiler, $1, $2);
    }

opt_operators
  : /* Empty */
    {
      $$ = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
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
      $$ = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NULL, compiler->cur_file, compiler->cur_line);
    }
  | operator

operator
  : var
  | EXCEPTION_VAR
  | CONSTANT
  | UNDEF
  | call_spvm_method
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
        SPVM_OP* op_sequence = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_SEQUENCE, compiler->cur_file, compiler->cur_line);
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
  | TRUE
    {
      $$ = SPVM_OP_new_op_true(compiler, $1);
    }
  | FALSE
    {
      $$ = SPVM_OP_new_op_false(compiler, $1);
    }
  | is_read_only
  | has_impl
  | logical_operator
  | CLASS_ID class_name
    {
      $$ = SPVM_OP_build_class_id(compiler, $1, $2);
    }
  | ERRNO
    {
      $$ = SPVM_OP_build_errno(compiler, $1);
    }
  | SET_ERRNO operator
    {
      $$ = SPVM_OP_build_set_errno(compiler, $1, $2);
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
  | REFCNT var
    {
      $$ = SPVM_OP_build_unary_op(compiler, $1, $2);
    }
  | REFOP operator
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
      $$ = SPVM_OP_build_unary_op(compiler, $1, $2);
    }
  | CREATE_REF var
    {
      $$ = SPVM_OP_build_unary_op(compiler, $1, $2);
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
  | operator REMAINDER operator
    {
      $$ = SPVM_OP_build_binary_op(compiler, $2, $1, $3);
    }
  | operator REMAINDER_UNSIGNED_INT operator
    {
      $$ = SPVM_OP_build_binary_op(compiler, $2, $1, $3);
    }
  | operator REMAINDER_UNSIGNED_LONG operator
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
      $$ = SPVM_OP_build_new(compiler, $1, $2, NULL);
    }
  | anon_method
    {
      // Method
      SPVM_OP* op_method = $1;
      
      // Class
      SPVM_OP* op_class = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CLASS, op_method->file, op_method->line);
      
      // Create class block
      SPVM_OP* op_class_block = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CLASS_BLOCK, op_method->file, op_method->line);
      SPVM_OP* op_list_declarations = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
      SPVM_OP_insert_child(compiler, op_list_declarations, op_list_declarations->last, op_method);
      SPVM_OP_insert_child(compiler, op_class_block, op_class_block->last, op_list_declarations);
      
      // Build class
      SPVM_OP_build_class(compiler, op_class, NULL, op_class_block, NULL);

      // Type
      SPVM_OP* op_type = SPVM_OP_new_op_type(compiler, op_class->uv.class->type, op_method->file, op_method->line);
      
      // New
      SPVM_OP* op_new = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NEW, op_method->file, op_method->line);
      $$ = SPVM_OP_build_new(compiler, op_new, op_type, NULL);
    }

array_init
  : '[' opt_operators ']'
    {
      SPVM_OP* op_array_init = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_INIT, compiler->cur_file, compiler->cur_line);
      int32_t is_key_values = 0;
      $$ = SPVM_OP_build_array_init(compiler, op_array_init, $2, is_key_values);
    }
  | '{' operators '}'
    {
      SPVM_OP* op_array_init = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_INIT, compiler->cur_file, compiler->cur_line);
      int32_t is_key_values = 1;
      $$ = SPVM_OP_build_array_init(compiler, op_array_init, $2, is_key_values);
    }
  | '{' '}'
    {
      SPVM_OP* op_array_init = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_INIT, compiler->cur_file, compiler->cur_line);
      int32_t is_key_values = 1;
      SPVM_OP* op_list_elements = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
      $$ = SPVM_OP_build_array_init(compiler, op_array_init, op_list_elements, is_key_values);
    }

convert
  : '(' qualified_type ')' operator %prec CONVERT
    {
      SPVM_OP* op_convert = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE_CAST, $2->file, $2->line);
      $$ = SPVM_OP_build_convert(compiler, op_convert, $2, $4, NULL);
    }
  | operator ARROW '(' qualified_type ')' %prec CONVERT
    {
      SPVM_OP* op_convert = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_TYPE_CAST, $4->file, $4->line);
      $$ = SPVM_OP_build_convert(compiler, op_convert, $4, $1, NULL);
    }

array_access
  : operator ARROW '[' operator ']'
    {
      $$ = SPVM_OP_build_array_access(compiler, $1, $4);
    }
  | array_access '[' operator ']'
    {
      $$ = SPVM_OP_build_array_access(compiler, $1, $3);
    }
  | field_access '[' operator ']'
    {
      $$ = SPVM_OP_build_array_access(compiler, $1, $3);
    }

call_spvm_method
  : CURRENT_CLASS SYMBOL_NAME '(' opt_operators  ')'
    {
      SPVM_OP* op_call_method = SPVM_OP_new_op_call_method(compiler, compiler->cur_file, compiler->cur_line);
      $$ = SPVM_OP_build_call_method(compiler, op_call_method, $1, $2, $4);
    }
  | CURRENT_CLASS SYMBOL_NAME
    {
      SPVM_OP* op_call_method = SPVM_OP_new_op_call_method(compiler, compiler->cur_file, compiler->cur_line);
      SPVM_OP* op_operators = SPVM_OP_new_op_list(compiler, $1->file, $2->line);
      $$ = SPVM_OP_build_call_method(compiler, op_call_method, $1, $2, op_operators);
    }
  | class_name ARROW method_name '(' opt_operators  ')'
    {
      SPVM_OP* op_call_method = SPVM_OP_new_op_call_method(compiler, compiler->cur_file, compiler->cur_line);
      $$ = SPVM_OP_build_call_method(compiler, op_call_method, $1, $3, $5);
    }
  | class_name ARROW method_name
    {
      SPVM_OP* op_call_method = SPVM_OP_new_op_call_method(compiler, compiler->cur_file, compiler->cur_line);
      SPVM_OP* op_operators = SPVM_OP_new_op_list(compiler, $1->file, $2->line);
      $$ = SPVM_OP_build_call_method(compiler, op_call_method, $1, $3, op_operators);
    }
  | operator ARROW method_name '(' opt_operators ')'
    {
      SPVM_OP* op_call_method = SPVM_OP_new_op_call_method(compiler, compiler->cur_file, compiler->cur_line);
      $$ = SPVM_OP_build_call_method(compiler, op_call_method, $1, $3, $5);
    }
  | operator ARROW method_name
    {
      SPVM_OP* op_call_method = SPVM_OP_new_op_call_method(compiler, compiler->cur_file, compiler->cur_line);
      SPVM_OP* op_operators = SPVM_OP_new_op_list(compiler, $1->file, $2->line);
      $$ = SPVM_OP_build_call_method(compiler, op_call_method, $1, $3, op_operators);
    }
  | operator ARROW '(' opt_operators ')'
    {
      SPVM_OP* op_call_method = SPVM_OP_new_op_call_method(compiler, compiler->cur_file, compiler->cur_line);
      SPVM_OP* op_method_name = SPVM_OP_new_op_name(compiler, "", $2->file, $2->line);
      $$ = SPVM_OP_build_call_method(compiler, op_call_method, $1, op_method_name, $4);
    }

field_access
  : operator ARROW '{' field_name '}'
    {
      SPVM_OP* op_field_access = SPVM_OP_new_op_field_access(compiler, compiler->cur_file, compiler->cur_line);
      $$ = SPVM_OP_build_field_access(compiler, op_field_access, $1, $4);
    }
  | field_access '{' field_name '}'
    {
      SPVM_OP* op_field_access = SPVM_OP_new_op_field_access(compiler, compiler->cur_file, compiler->cur_line);
      $$ = SPVM_OP_build_field_access(compiler, op_field_access, $1, $3);
    }
  | array_access '{' field_name '}'
    {
      SPVM_OP* op_field_access = SPVM_OP_new_op_field_access(compiler, compiler->cur_file, compiler->cur_line);
      $$ = SPVM_OP_build_field_access(compiler, op_field_access, $1, $3);
    }

weaken_field
  : WEAKEN var ARROW '{' field_name '}'
    {
      SPVM_OP* op_field_access = SPVM_OP_new_op_field_access(compiler, compiler->cur_file, compiler->cur_line);
      SPVM_OP_build_field_access(compiler, op_field_access, $2, $5);
      $$ = SPVM_OP_build_weaken_field(compiler, $1, op_field_access);
    }

unweaken_field
  : UNWEAKEN var ARROW '{' field_name '}'
    {
      SPVM_OP* op_field_access = SPVM_OP_new_op_field_access(compiler, compiler->cur_file, compiler->cur_line);
      SPVM_OP_build_field_access(compiler, op_field_access, $2, $5);
      $$ = SPVM_OP_build_unweaken_field(compiler, $1, op_field_access);
    }

isweak_field
  : ISWEAK var ARROW '{' field_name '}'
    {
      SPVM_OP* op_field_access = SPVM_OP_new_op_field_access(compiler, compiler->cur_file, compiler->cur_line);
      SPVM_OP_build_field_access(compiler, op_field_access, $2, $5);
      $$ = SPVM_OP_build_isweak_field(compiler, $1, op_field_access);
    }

has_impl
  : HAS_IMPL var ARROW method_name
    {
      $$ = SPVM_OP_build_has_impl(compiler, $1, $2, $4);
    }
  | HAS_IMPL var
    {
      $$ = SPVM_OP_build_has_impl(compiler, $1, $2, NULL);
    }

array_length
  : '@' operator
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      $$ = SPVM_OP_build_array_length(compiler, op_array_length, $2);
    }
  | '@' '{' operator '}'
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      $$ = SPVM_OP_build_array_length(compiler, op_array_length, $3);
    }
  | SCALAR '@' operator
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      $$ = SPVM_OP_build_array_length(compiler, op_array_length, $3);
    }
  | SCALAR '@' '{' operator '}'
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
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
      $$ = SPVM_OP_new_op_void_type(compiler, compiler->cur_file, compiler->cur_line);
    }

opt_type_comment
  : /* Empty */
    {
      $$ = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NULL, compiler->cur_file, compiler->cur_line);
    }
  | type_comment

type_comment
  : OF type
    {
      $$ = $2;
    }
    
field_name
  : SYMBOL_NAME

method_name
  : SYMBOL_NAME

class_name
  : SYMBOL_NAME

class_alias_name
  : SYMBOL_NAME

%%
