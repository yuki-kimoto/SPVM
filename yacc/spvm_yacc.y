%pure-parser
%parse-param	{ SPVM_COMPILER* compiler }
%lex-param	{ SPVM_COMPILER* compiler }

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
%}

%token <opval> MY HAS SUB PACKAGE IF ELSIF ELSE RETURN FOR WHILE USE NEW OUR SELF CLASS EQ NE GT GE LT LE
%token <opval> LAST NEXT NAME CONSTANT ENUM DESCRIPTOR CORETYPE UNDEF CROAK VAR_NAME INTERFACE
%token <opval> SWITCH CASE DEFAULT VOID EVAL BYTE SHORT INT LONG FLOAT DOUBLE STRING WEAKEN

%type <opval> grammar opt_statements statements statement my_var field if_statement else_statement
%type <opval> block enumeration_block package_block sub opt_declarations_in_package call_sub unop binop
%type <opval> opt_assignable_terms assignable_terms assignable_term args arg opt_args use declaration_in_package declarations_in_package term logical_term relative_term
%type <opval> enumeration_values enumeration_value weaken_field our_var invocant
%type <opval> type package_name field_name sub_name package declarations_in_grammar opt_enumeration_values type_array
%type <opval> for_statement while_statement expression opt_declarations_in_grammar var
%type <opval> call_field array_elem convert_type enumeration new_object type_name array_length declaration_in_grammar
%type <opval> switch_statement case_statement default_statement type_array_with_length
%type <opval> ';' opt_descriptors opt_colon_descriptors descriptors type_or_void normal_statement normal_statement_for_end eval_block


%right <opval> ASSIGN SPECIAL_ASSIGN
%left <opval> OR
%left <opval> AND
%left <opval> BIT_OR BIT_XOR
%left <opval> BIT_AND
%nonassoc <opval> REL
%left <opval> SHIFT
%left <opval> '+' '-' '.'
%left <opval> MULTIPLY DIVIDE REMAINDER
%right <opval> NOT '~' ARRAY_LENGTH UMINUS
%nonassoc <opval> INC DEC
%nonassoc <opval> ')'
%left <opval> ARROW
%left <opval> '('
%left <opval> '[' '{'

%%

grammar
  : opt_declarations_in_grammar
    {
      $$ = SPVM_OP_build_grammar(compiler, $1);
      
      // Syntax error
      if (compiler->error_count) {
        YYABORT;
      }
    }

opt_declarations_in_grammar
  :	/* Empty */
    {
      $$ = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    }
  |	declarations_in_grammar
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
  
declarations_in_grammar
  : declarations_in_grammar declaration_in_grammar
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
  | declaration_in_grammar

declaration_in_grammar
  : use
  | package

use
  : USE package_name ';'
    {
      $$ = SPVM_OP_build_use(compiler, $1, $2);
    }

package
  : PACKAGE package_name opt_colon_descriptors package_block
    {
      $$ = SPVM_OP_build_package(compiler, $1, $2, $4, $3);
    }

opt_declarations_in_package
  :	/* Empty */
    {
      $$ = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    }
  |	declarations_in_package
    {
      if ($1->id == SPVM_OP_C_ID_LIST) {
        $$ = $1;
      }
      else {
        $$ = SPVM_OP_new_op_list(compiler, $1->file, $1->line);
        SPVM_OP_insert_child(compiler, $$, $$->last, $1);
      }
    }

declarations_in_package
  : declarations_in_package declaration_in_package
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
  | declaration_in_package

declaration_in_package
  : field
  | sub
  | enumeration
  | our_var ';'

package_block
  : '{' opt_declarations_in_package '}'
    {
      SPVM_OP* op_class_block = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CLASS_BLOCK, $1->file, $1->line);
      SPVM_OP_insert_child(compiler, op_class_block, op_class_block->last, $2);
      $$ = op_class_block;
    }

enumeration_block 
  : '{' opt_enumeration_values '}'
    {
      SPVM_OP* op_enum_block = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ENUM_BLOCK, $1->file, $1->line);
      SPVM_OP_insert_child(compiler, op_enum_block, op_enum_block->last, $2);
      $$ = op_enum_block;
    }

opt_enumeration_values
  :	/* Empty */
    {
      $$ = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    }
  |	enumeration_values
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
    {
      $$ = $1;
    }
  | enumeration_value
  
enumeration_value
  : NAME
    {
      $$ = SPVM_OP_build_enumeration_value(compiler, $1, NULL);
    }
  | NAME ASSIGN CONSTANT
    {
      $$ = SPVM_OP_build_enumeration_value(compiler, $1, $3);
    }

opt_statements
  :	/* Empty */
    {
      $$ = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    }
  |	statements
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
  : normal_statement
  | if_statement
  | for_statement
  | while_statement
  | block
  | switch_statement
  | case_statement
  | default_statement
  | eval_block

block 
  : '{' opt_statements '}'
    {
      SPVM_OP* op_block = SPVM_OP_new_op_block(compiler, $1->file, $1->line);
      SPVM_OP_insert_child(compiler, op_block, op_block->last, $2);
      $$ = op_block;
    }

normal_statement
  : assignable_term ';'
  | expression ';'
  | ';'
    {
      $$ = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NULL, $1->file, $1->line);
    }

normal_statement_for_end
  : assignable_term
  | expression

for_statement
  : FOR '(' normal_statement term ';' normal_statement_for_end ')' block
    {
      $$ = SPVM_OP_build_for_statement(compiler, $1, $3, $4, $6, $8);
    }

while_statement
  : WHILE '(' term ')' block
    {
      $$ = SPVM_OP_build_while_statement(compiler, $1, $3, $5);
    }

switch_statement
  : SWITCH '(' assignable_term ')' block
    {
      $$ = SPVM_OP_build_switch_statement(compiler, $1, $3, $5);
    }

case_statement
  : CASE assignable_term ':'
    {
      $$ = SPVM_OP_build_case_statement(compiler, $1, $2);
    }

default_statement
  : DEFAULT ':'

if_statement
  : IF '(' term ')' block else_statement
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
  | ELSIF '(' term ')' block else_statement
    {
      $$ = SPVM_OP_build_if_statement(compiler, $1, $3, $5, $6);
    }

field
  : HAS field_name ':' opt_descriptors type ';'
    {
      $$ = SPVM_OP_build_field(compiler, $1, $2, $4, $5);
    }

sub
  : opt_descriptors SUB sub_name ':' type_or_void '(' opt_args ')' block
     {
       $$ = SPVM_OP_build_sub(compiler, $2, $3, $5, $7, $1, $9);
     }
  | opt_descriptors SUB sub_name ':' type_or_void '(' opt_args ')' ';'
     {
       $$ = SPVM_OP_build_sub(compiler, $2, $3, $5, $7, $1, NULL);
     }

enumeration
  : ENUM enumeration_block
    {
      $$ = SPVM_OP_build_enumeration(compiler, $1, $2);
    }

my_var
  : MY var ':' type
    {
      $$ = SPVM_OP_build_my(compiler, $2, $4);
    }
  | MY var
    {
      $$ = SPVM_OP_build_my(compiler, $2, NULL);
    }

our_var
  : OUR var ':' type
    {
      $$ = SPVM_OP_build_our(compiler, $2, $4);
    }

opt_assignable_terms
  :	/* Empty */
    {
      $$ = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    }
  |	assignable_terms
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
    
assignable_terms
  : assignable_terms ',' assignable_term
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
  | assignable_terms ','
    {
      $$ = $1
    }
  | assignable_term

array_length
  : ARRAY_LENGTH assignable_term
    {
      $$ = SPVM_OP_build_array_length(compiler, $1, $2);
    }
  | ARRAY_LENGTH '{' assignable_term '}'
    {
      $$ = SPVM_OP_build_array_length(compiler, $1, $3);
    }

term
  : assignable_term
  | relative_term
  | logical_term

assignable_term
  : var
  | CONSTANT
    {
      $$ = SPVM_OP_build_constant(compiler, $1);
    }
  | UNDEF
  | call_sub
  | call_field
  | array_elem
  | convert_type
  | new_object
  | array_length
  | my_var
  | binop
  | unop

expression
  : LAST
  | NEXT
  | RETURN {
      $$ = SPVM_OP_build_return(compiler, $1, NULL);
    }
  | RETURN assignable_term
    {
      $$ = SPVM_OP_build_return(compiler, $1, $2);
    }
  | CROAK
    {
      $$ = SPVM_OP_build_croak(compiler, $1, NULL);
    }
  | CROAK assignable_term
    {
      $$ = SPVM_OP_build_croak(compiler, $1, $2);
    }
  | call_field ASSIGN assignable_term
    {
      $$ = SPVM_OP_build_assign(compiler, $2, $1, $3);
    }
  | array_elem ASSIGN assignable_term
    {
      $$ = SPVM_OP_build_assign(compiler, $2, $1, $3);
    }
  | weaken_field

new_object
  : NEW type_name
    {
      $$ = SPVM_OP_build_new_object(compiler, $1, $2, NULL);
    }
  | NEW type_array_with_length
    {
      $$ = SPVM_OP_build_new_object(compiler, $1, $2, NULL);
    }
  | NEW type_array '{' opt_assignable_terms '}'
    {
      $$ = SPVM_OP_build_new_object(compiler, $1, $2, $4);
    }

convert_type
  : '(' type ')' assignable_term
    {
      SPVM_OP* op_convert = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CONVERT, $2->file, $2->line);
      $$ = SPVM_OP_build_convert(compiler, op_convert, $2, $4);
    }

call_field
  : assignable_term ARROW '{' field_name '}'
    {
      $$ = SPVM_OP_build_call_field(compiler, $1, $4);
    }
  | call_field '{' field_name '}'
    {
      $$ = SPVM_OP_build_call_field(compiler, $1, $3);
    }
  | array_elem '{' field_name '}'
    {
      $$ = SPVM_OP_build_call_field(compiler, $1, $3);
    }

weaken_field
  : WEAKEN call_field
    {
      $$ = SPVM_OP_build_weaken_field(compiler, $1, $2);
    }

unop
  : '+' assignable_term %prec UMINUS
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PLUS, $1->file, $1->line);
      $$ = SPVM_OP_build_unop(compiler, op, $2);
    }
  | '-' assignable_term %prec UMINUS
    {
      SPVM_OP* op_negate = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NEGATE, $1->file, $1->line);
      $$ = SPVM_OP_build_unop(compiler, op_negate, $2);
    }
  | INC assignable_term
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PRE_INC, $1->file, $1->line);
      $$ = SPVM_OP_build_unop(compiler, op, $2);
    }
  | assignable_term INC
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_POST_INC, $2->file, $2->line);
      $$ = SPVM_OP_build_unop(compiler, op, $1);
    }
  | DEC assignable_term
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PRE_DEC, $1->file, $1->line);
      $$ = SPVM_OP_build_unop(compiler, op, $2);
    }
  | assignable_term DEC
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_POST_DEC, $2->file, $2->line);
      $$ = SPVM_OP_build_unop(compiler, op, $1);
    }
  | '~' assignable_term
    {
      $$ = SPVM_OP_build_unop(compiler, $1, $2);
    }

binop
  : assignable_term '+' assignable_term
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ADD, $2->file, $2->line);
      $$ = SPVM_OP_build_binop(compiler, op, $1, $3);
    }
  | assignable_term '-' assignable_term
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_SUBTRACT, $2->file, $2->line);
      $$ = SPVM_OP_build_binop(compiler, op, $1, $3);
    }
  | assignable_term '.' assignable_term
    {
      $$ = SPVM_OP_build_concat_string(compiler, $2, $1, $3);
    }
  | assignable_term MULTIPLY assignable_term
    {
      $$ = SPVM_OP_build_binop(compiler, $2, $1, $3);
    }
  | assignable_term DIVIDE assignable_term
    {
      $$ = SPVM_OP_build_binop(compiler, $2, $1, $3);
    }
  | assignable_term REMAINDER assignable_term
    {
      $$ = SPVM_OP_build_binop(compiler, $2, $1, $3);
    }
  | assignable_term BIT_XOR assignable_term
    {
      $$ = SPVM_OP_build_binop(compiler, $2, $1, $3);
    }
  | assignable_term BIT_AND assignable_term
    {
      $$ = SPVM_OP_build_binop(compiler, $2, $1, $3);
    }
  | assignable_term BIT_OR assignable_term
    {
      $$ = SPVM_OP_build_binop(compiler, $2, $1, $3);
    }
  | assignable_term SHIFT assignable_term
    {
      $$ = SPVM_OP_build_binop(compiler, $2, $1, $3);
    }
  | assignable_term EQ assignable_term
    {
      $$ = SPVM_OP_build_binop(compiler, $2, $1, $3);
    }
  | assignable_term NE assignable_term
    {
      $$ = SPVM_OP_build_binop(compiler, $2, $1, $3);
    }
  | assignable_term GT assignable_term
    {
      $$ = SPVM_OP_build_binop(compiler, $2, $1, $3);
    }
  | assignable_term GE assignable_term
    {
      $$ = SPVM_OP_build_binop(compiler, $2, $1, $3);
    }
  | assignable_term LT assignable_term
    {
      $$ = SPVM_OP_build_binop(compiler, $2, $1, $3);
    }
  | assignable_term LE assignable_term
    {
      $$ = SPVM_OP_build_binop(compiler, $2, $1, $3);
    }
  | my_var ASSIGN assignable_term
    {
      $$ = SPVM_OP_build_assign(compiler, $2, $1, $3);
    }
  | var ASSIGN assignable_term
    {
      $$ = SPVM_OP_build_assign(compiler, $2, $1, $3);
    }
  | var SPECIAL_ASSIGN assignable_term
    {
      $$ = SPVM_OP_build_assign(compiler, $2, $1, $3);
    }
  | '(' assignable_term ')'
    {
      $$ = $2;
    }

relative_term
  : assignable_term REL assignable_term
    {
      $$ = SPVM_OP_build_binop(compiler, $2, $1, $3);
    }

logical_term
  : term OR term
    {
      $$ = SPVM_OP_build_or(compiler, $2, $1, $3);
    }
  | term AND term
    {
      $$ = SPVM_OP_build_and(compiler, $2, $1, $3);
    }
  | NOT term
    {
      $$ = SPVM_OP_build_not(compiler, $1, $2);
    }

array_elem
  : assignable_term ARROW '[' assignable_term ']'
    {
      $$ = SPVM_OP_build_array_elem(compiler, $1, $4);
    }
  | array_elem '[' assignable_term ']'
    {
      $$ = SPVM_OP_build_array_elem(compiler, $1, $3);
    }
  | call_field '[' assignable_term ']'
    {
      $$ = SPVM_OP_build_array_elem(compiler, $1, $3);
    }

call_sub
  : sub_name '(' opt_assignable_terms  ')'
    {
      $$ = SPVM_OP_build_call_sub(compiler, SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NULL, $1->file, $1->line), $1, $3);
    }
  | package_name ARROW sub_name '(' opt_assignable_terms  ')'
    {
      $$ = SPVM_OP_build_call_sub(compiler, $1, $3, $5);
    }
  | package_name ARROW sub_name
    {
      SPVM_OP* op_assignable_terms = SPVM_OP_new_op_list(compiler, $1->file, $2->line);
      $$ = SPVM_OP_build_call_sub(compiler, $1, $3, op_assignable_terms);
    }
  | assignable_term ARROW sub_name '(' opt_assignable_terms ')'
    {
      $$ = SPVM_OP_build_call_sub(compiler, $1, $3, $5);
    }
  | assignable_term ARROW sub_name
    {
      SPVM_OP* op_assignable_terms = SPVM_OP_new_op_list(compiler, $1->file, $2->line);
      $$ = SPVM_OP_build_call_sub(compiler, $1, $3, op_assignable_terms);
    }

opt_args
  :	/* Empty */
    {
      $$ = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    }
  |	args
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
  | invocant
    {
       // Add invocant to arguments
       SPVM_OP* op_args = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
       SPVM_OP_insert_child(compiler, op_args, op_args->last, $1);
       
       $$ = op_args;
    }
  | invocant ',' args
    {
      // Add invocant to arguments
      SPVM_OP* op_args;
      if ($3->id == SPVM_OP_C_ID_LIST) {
        op_args = $3;
      }
      else {
        SPVM_OP* op_list = SPVM_OP_new_op_list(compiler, $1->file, $1->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, $3);
        op_args = op_list;
      }
      
      SPVM_OP_insert_child(compiler, op_args, op_args->first, $1);
       
      $$ = op_args;
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
    {
      $$ = $1;
    }
  | arg

arg
  : var ':' type
    {
      $$ = SPVM_OP_build_arg(compiler, $1, $3);
    }

invocant
  : var ':' SELF
    {
      $$ = SPVM_OP_build_arg(compiler, $1, $3);
    }
  | var ':' CLASS
    {
      $$ = SPVM_OP_build_arg(compiler, $1, $3);
    }

opt_colon_descriptors
  :	/* Empty */
    {
      $$ = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    }
  |	':' descriptors
    {
      if ($2->id == SPVM_OP_C_ID_LIST) {
        $$ = $2;
      }
      else {
        SPVM_OP* op_list = SPVM_OP_new_op_list(compiler, $2->file, $2->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, $2);
        $$ = op_list;
      }
    }

opt_descriptors
  :	/* Empty */
    {
      $$ = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    }
  |	descriptors
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

type
  : type_name
  | type_array

type_name
  : NAME
    {
      $$ = SPVM_OP_build_type_name(compiler, $1);
    }
  | BYTE
    {
      $$ = SPVM_OP_build_type_byte(compiler, $1);
    }
  | SHORT
    {
      $$ = SPVM_OP_build_type_short(compiler, $1);
    }
  | INT
    {
      $$ = SPVM_OP_build_type_int(compiler, $1);
    }
  | LONG
    {
      $$ = SPVM_OP_build_type_long(compiler, $1);
    }
  | FLOAT
    {
      $$ = SPVM_OP_build_type_float(compiler, $1);
    }
  | DOUBLE
    {
      $$ = SPVM_OP_build_type_double(compiler, $1);
    }

type_array
  : type_name '[' ']'
    {
      $$ = SPVM_OP_build_type_array(compiler, $1, NULL);
    }
  | type_array '[' ']'
    {
      $$ = SPVM_OP_build_type_array(compiler, $1, NULL);
    }

type_array_with_length
  : type_name '[' assignable_term ']'
    {
      $$ = SPVM_OP_build_type_array(compiler, $1, $3);
    }
  | type_array '[' assignable_term ']'
    {
      $$ = SPVM_OP_build_type_array(compiler, $1, $3);
    }

type_or_void
  : type
  | VOID
    {
      $$ = SPVM_OP_new_op_void(compiler, compiler->cur_file, compiler->cur_line);
    }

field_name : NAME
sub_name : NAME
package_name : NAME

var
  : VAR_NAME
    {
      $$ = SPVM_OP_build_var(compiler, $1);
    }

eval_block
  : EVAL block
    {
      $$ = SPVM_OP_build_eval(compiler, $1, $2);
    }

%%
