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
%}

%token <opval> CLASS HAS METHOD OUR ENUM MY USE AS REQUIRE ALLOW CURRENT_CLASS MUTABLE
%token <opval> DESCRIPTOR MAKE_READ_ONLY IMPLEMENT
%token <opval> IF UNLESS ELSIF ELSE FOR WHILE LAST NEXT SWITCH CASE DEFAULT BREAK EVAL
%token <opval> NAME VAR_NAME CONSTANT EXCEPTION_VAR
%token <opval> UNDEF VOID BYTE SHORT INT LONG FLOAT DOUBLE STRING OBJECT TRUE FALSE END_OF_FILE
%token <opval> DOT3 FATCAMMA RW RO WO INIT NEW
%token <opval> RETURN WEAKEN DIE WARN PRINT CURRENT_CLASS_NAME UNWEAKEN '[' '{' '('

%type <opval> grammar
%type <opval> opt_classes classes class class_block
%type <opval> opt_declarations declarations declaration
%type <opval> enumeration enumeration_block opt_enumeration_values enumeration_values enumeration_value
%type <opval> method anon_method opt_args args arg has use require our
%type <opval> opt_descriptors descriptors
%type <opval> opt_statements statements statement if_statement else_statement 
%type <opval> for_statement while_statement switch_statement case_statement default_statement
%type <opval> block eval_block init_block switch_block if_require_statement
%type <opval> unary_op binary_op comparison_op isa logical_op expression_or_logical_op
%type <opval> call_spvm_method opt_vaarg
%type <opval> array_access field_access weaken_field unweaken_field isweak_field convert array_length
%type <opval> assign inc dec allow
%type <opval> new array_init
%type <opval> my_var var implement
%type <opval> expression opt_expressions expressions opt_expression case_statements
%type <opval> field_name method_name
%type <opval> type qualified_type basic_type array_type array_type_with_length ref_type  qualified_type_or_void

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
%right <opval> LOGICAL_NOT BIT_NOT '@' CREATE_REF DEREF PLUS MINUS CONVERT SCALAR STRING_LENGTH ISWEAK REFCNT REFOP DUMP NEW_STRING_LEN IS_READ_ONLY COPY
%nonassoc <opval> INC DEC
%left <opval> ARROW

%%

grammar
  : opt_classes
    {
      $$ = SPVM_OP_build_grammar(compiler, $1);
      compiler->op_grammar = $$;
    }

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
  | our ';'
  | use
  | allow
  | implement
  | init_block

init_block
  : INIT block
    { 
      SPVM_OP* op_method = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_METHOD, compiler->cur_file, compiler->cur_line);
      SPVM_OP* op_method_name = SPVM_OP_new_op_name(compiler, "INIT", compiler->cur_file, compiler->cur_line);
      SPVM_OP* op_void_type = SPVM_OP_new_op_void_type(compiler, compiler->cur_file, compiler->cur_line);

      SPVM_OP* op_list_descriptors = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
      SPVM_OP* op_descriptor_static = SPVM_OP_new_op_descriptor(compiler, SPVM_DESCRIPTOR_C_ID_STATIC, compiler->cur_file, compiler->cur_line);
      SPVM_OP_insert_child(compiler, op_list_descriptors, op_list_descriptors->first, op_descriptor_static);

      int32_t can_precompile = 0;
      $$ = SPVM_OP_build_method(compiler, op_method, op_method_name, op_void_type, NULL, op_list_descriptors, $2, NULL, NULL, 1, 0, can_precompile);
    }
    
use
  : USE basic_type ';'
    {
      $$ = SPVM_OP_build_use(compiler, $1, $2, NULL, 0);
    }
  | USE basic_type AS basic_type';'
    {
      $$ = SPVM_OP_build_use(compiler, $1, $2, $4, 0);
    }

require
  : REQUIRE basic_type
    {
      SPVM_OP* op_use = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_USE, compiler->cur_file, compiler->cur_line);
      $$ = SPVM_OP_build_use(compiler, op_use, $2, NULL, 1);
    }
  | REQUIRE basic_type AS basic_type';'
    {
      SPVM_OP* op_use = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_USE, compiler->cur_file, compiler->cur_line);
      $$ = SPVM_OP_build_use(compiler, op_use, $2, $4, 1);
    }

allow
  : ALLOW basic_type ';'
    {
      $$ = SPVM_OP_build_allow(compiler, $1, $2);
    }

implement
  : IMPLEMENT basic_type ';'
    {
      $$ = SPVM_OP_build_compatible(compiler, $1, $2);
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
  : OUR VAR_NAME ':' opt_descriptors qualified_type
    {
      $$ = SPVM_OP_build_our(compiler, $1, $2, $4, $5);
    }

has
  : HAS field_name ':' opt_descriptors qualified_type ';'
    {
      $$ = SPVM_OP_build_has(compiler, $1, $2, $4, $5);
    }

method
  : opt_descriptors METHOD method_name ':' qualified_type_or_void '(' opt_args opt_vaarg')' block
     {
       int32_t can_precompile = 1;
       $$ = SPVM_OP_build_method(compiler, $2, $3, $5, $7, $1, $10, NULL, $8, 0, 0, can_precompile);
     }
  | opt_descriptors METHOD method_name ':' qualified_type_or_void '(' opt_args opt_vaarg')' ';'
     {
       int32_t can_precompile = 0;
       $$ = SPVM_OP_build_method(compiler, $2, $3, $5, $7, $1, NULL, NULL, $8, 0, 0, can_precompile);
     }
  | opt_descriptors METHOD ':' qualified_type_or_void '(' opt_args opt_vaarg')' block
     {
       int32_t can_precompile = 1;
       $$ = SPVM_OP_build_method(compiler, $2, NULL, $4, $6, $1, $9, NULL, $7, 0, 0, can_precompile);
     }
  | opt_descriptors METHOD ':' qualified_type_or_void '(' opt_args opt_vaarg ')' ';'
     {
       int32_t can_precompile = 0;
       $$ = SPVM_OP_build_method(compiler, $2, NULL, $4, $6, $1, NULL, NULL, $7, 0, 0, can_precompile);
     }

anon_method
  : opt_descriptors METHOD ':' qualified_type_or_void '(' opt_args opt_vaarg')' block
     {
       int32_t is_init = 0;
       int32_t is_anon = 1;
       int32_t can_precompile = 1;
       
       $$ = SPVM_OP_build_method(compiler, $2, NULL, $4, $6, $1, $9, NULL, $7, is_init, is_anon, can_precompile);
     }
  | '[' args ']' opt_descriptors METHOD ':' qualified_type_or_void '(' opt_args opt_vaarg')' block
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
       int32_t can_precompile = 1;
       $$ = SPVM_OP_build_method(compiler, $5, NULL, $7, $9, $4, $12, op_list_args, $10, is_init, is_anon, can_precompile);
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
  : var ':' qualified_type
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
  | expression ';'
    {
      $$ = SPVM_OP_build_expression_statement(compiler, $1);
    }
  | LAST ';'
  | NEXT ';'
  | BREAK ';'
  | RETURN ';'
    {
      $$ = SPVM_OP_build_return(compiler, $1, NULL);
    }
  | RETURN expression ';'
    {
      $$ = SPVM_OP_build_return(compiler, $1, $2);
    }
  | DIE expression ';'
    {
      $$ = SPVM_OP_build_die(compiler, $1, $2);
    }
  | WARN expression ';'
    {
      $$ = SPVM_OP_build_warn(compiler, $1, $2);
    }
  | PRINT expression ';'
    {
      $$ = SPVM_OP_build_print(compiler, $1, $2);
    }
  | weaken_field ';'
  | unweaken_field ';'
  | ';'
    {
      $$ = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NULL, compiler->cur_file, compiler->cur_line);
    }
  | MAKE_READ_ONLY expression ';'
    {
      $$ = SPVM_OP_build_make_read_only(compiler, $1, $2);
    }

for_statement
  : FOR '(' opt_expression ';' expression_or_logical_op ';' opt_expression ')' block
    {
      $$ = SPVM_OP_build_for_statement(compiler, $1, $3, $5, $7, $9);
    }

while_statement
  : WHILE '(' expression_or_logical_op ')' block
    {
      $$ = SPVM_OP_build_while_statement(compiler, $1, $3, $5);
    }

switch_statement
  : SWITCH '(' expression ')' switch_block
    {
      $$ = SPVM_OP_build_switch_statement(compiler, $1, $3, $5);
    }

switch_block
  : '{' case_statements '}'
    {
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, compiler->cur_file, compiler->cur_line);
      op_block->uv.block->id = SPVM_BLOCK_C_ID_SWITCH;
      $$ = SPVM_OP_build_switch_block(compiler, op_block, $2, NULL);
    }
  | '{' case_statements default_statement '}'
    {
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, compiler->cur_file, compiler->cur_line);
      op_block->uv.block->id = SPVM_BLOCK_C_ID_SWITCH;
      $$ = SPVM_OP_build_switch_block(compiler, op_block, $2, $3);
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
  : CASE expression ':' block
    {
      $$ = SPVM_OP_build_case_statement(compiler, $1, $2, $4);
    }
  | CASE expression ':'
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
  : IF '(' expression_or_logical_op ')' block else_statement
    {
      SPVM_OP* op_if = SPVM_OP_build_if_statement(compiler, $1, $3, $5, $6);
      
      // if is wraped with block to allow the following syntax
      //  if (my $var = 3) { ... }
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, $1->file, $1->line);
      SPVM_OP_insert_child(compiler, op_block, op_block->last, op_if);
      
      $$ = op_block;
    }
  | UNLESS '(' expression_or_logical_op ')' block else_statement
    {
      SPVM_OP* op_if = SPVM_OP_build_if_statement(compiler, $1, $3, $5, $6);
      
      // if is wraped with block to allow the following syntax
      //  if (my $var = 3) { ... }
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
  | ELSIF '(' expression_or_logical_op ')' block else_statement
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

opt_expressions
  : /* Empty */
    {
      $$ = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    }
  | expressions
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
    
opt_expression
  : /* Empty */
    {
      $$ = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NULL, compiler->cur_file, compiler->cur_line);
    }
  | expression

expression_or_logical_op
  : expression
  | logical_op

expression
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
  | my_var
  | unary_op
  | binary_op
  | assign
  | inc
  | dec
  | '(' expressions ')'
    {
      if ($2->id == SPVM_OP_C_ID_LIST) {
        SPVM_OP* op_expression = $2->first;
        SPVM_OP* op_sequence = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_SEQUENCE, compiler->cur_file, compiler->cur_line);
        while ((op_expression = SPVM_OP_sibling(compiler, op_expression))) {
          SPVM_OP* op_stab = SPVM_OP_cut_op(compiler, op_expression);
          SPVM_OP_insert_child(compiler, op_sequence, op_sequence->last, op_expression);
          op_expression = op_stab;
        }
        $$ = op_sequence;
      }
      else {
        $$ = $2;
      }
    }
  | CURRENT_CLASS_NAME
  | isweak_field
  | comparison_op
  | isa
  | TRUE
    {
      $$ = SPVM_OP_new_op_true(compiler, $1);
    }
  | FALSE
    {
      $$ = SPVM_OP_new_op_false(compiler, $1);
    }

expressions
  : expressions ',' expression
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
  | expressions ','
    {
      $$ = $1;
    }
  | expression
    {
      $$ = $1;
    }

unary_op
  : '+' expression %prec PLUS
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PLUS, $1->file, $1->line);
      $$ = SPVM_OP_build_unary_op(compiler, op, $2);
    }
  | '-' expression %prec MINUS
    {
      SPVM_OP* op_negate = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_MINUS, $1->file, $1->line);
      $$ = SPVM_OP_build_unary_op(compiler, op_negate, $2);
    }
  | BIT_NOT expression
    {
      $$ = SPVM_OP_build_unary_op(compiler, $1, $2);
    }
  | REFCNT var
    {
      $$ = SPVM_OP_build_unary_op(compiler, $1, $2);
    }
  | REFOP expression
    {
      $$ = SPVM_OP_build_unary_op(compiler, $1, $2);
    }
  | STRING_LENGTH expression
    {
      $$ = SPVM_OP_build_unary_op(compiler, $1, $2);
    }
  | DUMP expression
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
  | NEW_STRING_LEN expression
    {
      $$ = SPVM_OP_build_unary_op(compiler, $1, $2);
    }
  | IS_READ_ONLY expression
    {
      $$ = SPVM_OP_build_unary_op(compiler, $1, $2);
    }
  | COPY expression
    {
      $$ = SPVM_OP_build_unary_op(compiler, $1, $2);
    }

inc
  : INC expression
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PRE_INC, $1->file, $1->line);
      $$ = SPVM_OP_build_inc(compiler, op, $2);
    }
  | expression INC
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_POST_INC, $2->file, $2->line);
      $$ = SPVM_OP_build_inc(compiler, op, $1);
    }

dec
  : DEC expression
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PRE_DEC, $1->file, $1->line);
      $$ = SPVM_OP_build_dec(compiler, op, $2);
    }
  | expression DEC
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_POST_DEC, $2->file, $2->line);
      $$ = SPVM_OP_build_dec(compiler, op, $1);
    }

binary_op
  : expression '+' expression
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ADD, $2->file, $2->line);
      $$ = SPVM_OP_build_binary_op(compiler, op, $1, $3);
    }
  | expression '-' expression
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_SUBTRACT, $2->file, $2->line);
      $$ = SPVM_OP_build_binary_op(compiler, op, $1, $3);
    }
  | expression '*' expression
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_MULTIPLY, $2->file, $2->line);
      $$ = SPVM_OP_build_binary_op(compiler, op, $1, $3);
    }
  | expression DIVIDE expression
    {
      $$ = SPVM_OP_build_binary_op(compiler, $2, $1, $3);
    }
  | expression DIVIDE_UNSIGNED_INT expression
    {
      $$ = SPVM_OP_build_binary_op(compiler, $2, $1, $3);
    }
  | expression DIVIDE_UNSIGNED_LONG expression
    {
      $$ = SPVM_OP_build_binary_op(compiler, $2, $1, $3);
    }
  | expression REMAINDER expression
    {
      $$ = SPVM_OP_build_binary_op(compiler, $2, $1, $3);
    }
  | expression REMAINDER_UNSIGNED_INT expression
    {
      $$ = SPVM_OP_build_binary_op(compiler, $2, $1, $3);
    }
  | expression REMAINDER_UNSIGNED_LONG expression
    {
      $$ = SPVM_OP_build_binary_op(compiler, $2, $1, $3);
    }
  | expression BIT_XOR expression
    {
      $$ = SPVM_OP_build_binary_op(compiler, $2, $1, $3);
    }
  | expression BIT_AND expression
    {
      $$ = SPVM_OP_build_binary_op(compiler, $2, $1, $3);
    }
  | expression BIT_OR expression
    {
      $$ = SPVM_OP_build_binary_op(compiler, $2, $1, $3);
    }
  | expression SHIFT expression
    {
      $$ = SPVM_OP_build_binary_op(compiler, $2, $1, $3);
    }
  | expression '.' expression
    {
      $$ = SPVM_OP_build_binary_op(compiler, $2, $1, $3);
    }

comparison_op
  : expression NUMEQ expression
    {
      $$ = SPVM_OP_build_comparison_op(compiler, $2, $1, $3);
    }
  | expression NUMNE expression
    {
      $$ = SPVM_OP_build_comparison_op(compiler, $2, $1, $3);
    }
  | expression NUMGT expression
    {
      $$ = SPVM_OP_build_comparison_op(compiler, $2, $1, $3);
    }
  | expression NUMGE expression
    {
      $$ = SPVM_OP_build_comparison_op(compiler, $2, $1, $3);
    }
  | expression NUMLT expression
    {
      $$ = SPVM_OP_build_comparison_op(compiler, $2, $1, $3);
    }
  | expression NUMLE expression
    {
      $$ = SPVM_OP_build_comparison_op(compiler, $2, $1, $3);
    }
  | expression NUMERIC_CMP expression
    {
      $$ = SPVM_OP_build_comparison_op(compiler, $2, $1, $3);
    }
  | expression STREQ expression
    {
      $$ = SPVM_OP_build_comparison_op(compiler, $2, $1, $3);
    }
  | expression STRNE expression
    {
      $$ = SPVM_OP_build_comparison_op(compiler, $2, $1, $3);
    }
  | expression STRGT expression
    {
      $$ = SPVM_OP_build_comparison_op(compiler, $2, $1, $3);
    }
  | expression STRGE expression
    {
      $$ = SPVM_OP_build_comparison_op(compiler, $2, $1, $3);
    }
  | expression STRLT expression
    {
      $$ = SPVM_OP_build_comparison_op(compiler, $2, $1, $3);
    }
  | expression STRLE expression
    {
      $$ = SPVM_OP_build_comparison_op(compiler, $2, $1, $3);
    }
  | expression STRING_CMP expression
    {
      $$ = SPVM_OP_build_comparison_op(compiler, $2, $1, $3);
    }

isa
  : expression ISA type
    {
      $$ = SPVM_OP_build_isa(compiler, $2, $1, $3);
    }
    
logical_op
  : expression_or_logical_op LOGICAL_OR expression_or_logical_op
    {
      $$ = SPVM_OP_build_or(compiler, $2, $1, $3);
    }
  | expression_or_logical_op LOGICAL_AND expression_or_logical_op
    {
      $$ = SPVM_OP_build_and(compiler, $2, $1, $3);
    }
  | LOGICAL_NOT expression_or_logical_op
    {
      $$ = SPVM_OP_build_not(compiler, $1, $2);
    }
  | '(' logical_op ')'
    {
      $$ = $2;
    }

assign
  : expression ASSIGN expression
    {
      $$ = SPVM_OP_build_assign(compiler, $2, $1, $3);
    }
  | expression SPECIAL_ASSIGN expression
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
      SPVM_OP* op_type = SPVM_OP_new_op_type(compiler, op_class->uv.class->op_type->uv.type, op_method->file, op_method->line);
      
      // New
      SPVM_OP* op_new = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NEW, op_method->file, op_method->line);
      $$ = SPVM_OP_build_new(compiler, op_new, op_type, NULL);
    }

array_init
  : '[' opt_expressions ']'
    {
      SPVM_OP* op_array_init = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_INIT, compiler->cur_file, compiler->cur_line);
      int32_t is_key_values = 0;
      $$ = SPVM_OP_build_array_init(compiler, op_array_init, $2, is_key_values);
    }
  | '{' expressions '}'
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
  : '(' qualified_type ')' expression %prec CONVERT
    {
      SPVM_OP* op_convert = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CONVERT, $2->file, $2->line);
      $$ = SPVM_OP_build_convert(compiler, op_convert, $2, $4, NULL);
    }

array_access
  : expression ARROW '[' expression ']'
    {
      $$ = SPVM_OP_build_array_access(compiler, $1, $4);
    }
  | array_access '[' expression ']'
    {
      $$ = SPVM_OP_build_array_access(compiler, $1, $3);
    }
  | field_access '[' expression ']'
    {
      $$ = SPVM_OP_build_array_access(compiler, $1, $3);
    }

call_spvm_method
  : CURRENT_CLASS NAME '(' opt_expressions  ')'
    {
      $$ = SPVM_OP_build_call_method(compiler, $1, $2, $4);
    }
  | CURRENT_CLASS NAME
    {
      SPVM_OP* op_expressions = SPVM_OP_new_op_list(compiler, $1->file, $2->line);
      $$ = SPVM_OP_build_call_method(compiler, $1, $2, op_expressions);
    }
  | basic_type ARROW method_name '(' opt_expressions  ')'
    {
      $$ = SPVM_OP_build_call_method(compiler, $1, $3, $5);
    }
  | basic_type ARROW method_name
    {
      SPVM_OP* op_expressions = SPVM_OP_new_op_list(compiler, $1->file, $2->line);
      $$ = SPVM_OP_build_call_method(compiler, $1, $3, op_expressions);
    }
  | expression ARROW method_name '(' opt_expressions ')'
    {
      $$ = SPVM_OP_build_call_method(compiler, $1, $3, $5);
    }
  | expression ARROW method_name
    {
      SPVM_OP* op_expressions = SPVM_OP_new_op_list(compiler, $1->file, $2->line);
      $$ = SPVM_OP_build_call_method(compiler, $1, $3, op_expressions);
    }
  | expression ARROW '(' opt_expressions ')'
    {
      SPVM_OP* op_method_name = SPVM_OP_new_op_name(compiler, "", $2->file, $2->line);
      $$ = SPVM_OP_build_call_method(compiler, $1, op_method_name, $4);
    }
field_access
  : expression ARROW '{' field_name '}'
    {
      $$ = SPVM_OP_build_field_access(compiler, $1, $4);
    }
  | field_access '{' field_name '}'
    {
      $$ = SPVM_OP_build_field_access(compiler, $1, $3);
    }
  | array_access '{' field_name '}'
    {
      $$ = SPVM_OP_build_field_access(compiler, $1, $3);
    }

weaken_field
  : WEAKEN var ARROW '{' field_name '}'
    {
      SPVM_OP* op_field_access = SPVM_OP_build_field_access(compiler, $2, $5);
      $$ = SPVM_OP_build_weaken_field(compiler, $1, op_field_access);
    }

unweaken_field
  : UNWEAKEN var ARROW '{' field_name '}'
    {
      SPVM_OP* op_field_access = SPVM_OP_build_field_access(compiler, $2, $5);
      $$ = SPVM_OP_build_unweaken_field(compiler, $1, op_field_access);
    }

isweak_field
  : ISWEAK var ARROW '{' field_name '}'
    {
      SPVM_OP* op_field_access = SPVM_OP_build_field_access(compiler, $2, $5);
      $$ = SPVM_OP_build_isweak_field(compiler, $1, op_field_access);
    }

array_length
  : '@' expression
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      $$ = SPVM_OP_build_array_length(compiler, op_array_length, $2);
    }
  | '@' '{' expression '}'
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      $$ = SPVM_OP_build_array_length(compiler, op_array_length, $3);
    }
  | SCALAR '@' expression
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      $$ = SPVM_OP_build_array_length(compiler, op_array_length, $3);
    }
  | SCALAR '@' '{' expression '}'
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      $$ = SPVM_OP_build_array_length(compiler, op_array_length, $4);
    }

my_var
  : MY var ':' qualified_type
    {
      $$ = SPVM_OP_build_my(compiler, $1, $2, $4, NULL);
    }
  | MY var
    {
      $$ = SPVM_OP_build_my(compiler, $1, $2, NULL, NULL);
    }

var
  : VAR_NAME
    {
      $$ = SPVM_OP_build_var(compiler, $1);
    }

qualified_type
  : type
  | MUTABLE type {
    $2->uv.type->is_mutable = 1;
    $$ = $2;
  }

type
  : basic_type
  | array_type
  | ref_type

basic_type
  : NAME
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
  : basic_type '[' expression ']'
    {
      $$ = SPVM_OP_build_array_type(compiler, $1, $3);
    }
  | array_type '[' expression ']'
    {
      $$ = SPVM_OP_build_array_type(compiler, $1, $3);
    }

qualified_type_or_void
  : qualified_type
  | VOID
    {
      $$ = SPVM_OP_new_op_void_type(compiler, compiler->cur_file, compiler->cur_line);
    }

field_name
  : NAME

method_name
  : NAME

%%
