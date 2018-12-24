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
  #include "spvm_list.h"
  #include "spvm_package.h"
%}

%token <opval> PACKAGE HAS SUB OUR ENUM MY SELF USE 
%token <opval> DESCRIPTOR
%token <opval> IF UNLESS ELSIF ELSE FOR WHILE LAST NEXT SWITCH CASE DEFAULT EVAL
%token <opval> NAME VAR_NAME CONSTANT PACKAGE_VAR_NAME EXCEPTION_VAR
%token <opval> UNDEF VOID BYTE SHORT INT LONG FLOAT DOUBLE STRING OBJECT
%token <opval> AMPERSAND DOT3 FATCAMMA RW RO WO BEGIN REQUIRE
%token <opval> RETURN WEAKEN CROAK CURRENT_PACKAGE

%type <opval> grammar
%type <opval> opt_packages packages package package_block
%type <opval> opt_declarations declarations declaration
%type <opval> enumeration enumeration_block opt_enumeration_values enumeration_values enumeration_value
%type <opval> sub anon_sub opt_args args arg invocant has use require our string_length
%type <opval> opt_descriptors descriptors sub_names opt_sub_names
%type <opval> opt_statements statements statement if_statement else_statement 
%type <opval> for_statement while_statement switch_statement case_statement default_statement
%type <opval> block eval_block begin_block if_require_statement
%type <opval> unop binop
%type <opval> call_sub opt_vaarg
%type <opval> array_access field_access weaken_field weaken_array_element convert_type convert array_length
%type <opval> deref ref assign incdec
%type <opval> new array_init
%type <opval> my_var var package_var_access
%type <opval> term opt_expression_terms expression_terms expression_term condition_term
%type <opval> field_name sub_name
%type <opval> type basic_type array_type array_type_with_length ref_type  type_or_void

%right <opval> ASSIGN SPECIAL_ASSIGN
%left <opval> COND_OR
%left <opval> COND_AND
%left <opval> BIT_OR BIT_XOR
%left <opval> BIT_AND
%nonassoc <opval> REL ISA
%left <opval> SHIFT
%left <opval> '+' '-' '.'
%left <opval> MULTIPLY DIVIDE REMAINDER
%right <opval> NEW CAST
%right <opval> COND_NOT BIT_NOT '@' SCALAR UMINUS REF DEREF LENGTH
%nonassoc <opval> INC DEC
%left <opval> ARROW
%left <opval> '('
%left <opval> '[' '{'

%%

grammar
  : opt_packages
    {
      $$ = SPVM_OP_build_grammar(compiler, $1);
      compiler->op_grammar = $$;
    }

opt_packages
  :	/* Empty */
    {
      $$ = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    }
  |	packages
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
  
packages
  : packages package
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
  | package

package
  : PACKAGE basic_type package_block
    {
      $$ = SPVM_OP_build_package(compiler, $1, $2, $3, NULL);
    }
  | PACKAGE basic_type ':' opt_descriptors package_block
    {
      $$ = SPVM_OP_build_package(compiler, $1, $2, $5, $4);
    }

package_block
  : '{' opt_declarations '}'
    {
      SPVM_OP* op_class_block = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CLASS_BLOCK, $1->file, $1->line);
      SPVM_OP_insert_child(compiler, op_class_block, op_class_block->last, $2);
      $$ = op_class_block;
    }

opt_declarations
  :	/* Empty */
    {
      $$ = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    }
  |	declarations
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
  | sub
  | enumeration
  | our ';'
  | use
  | begin_block

begin_block
  : BEGIN block
    { 
      SPVM_OP* op_sub = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_SUB, compiler->cur_file, compiler->cur_line);
      SPVM_OP* op_sub_name = SPVM_OP_new_op_name(compiler, "BEGIN", compiler->cur_file, compiler->cur_line);
      SPVM_OP* op_void_type = SPVM_OP_new_op_void_type(compiler, compiler->cur_file, compiler->cur_line);
      $$ = SPVM_OP_build_sub(compiler, op_sub, op_sub_name, op_void_type, NULL, NULL, $2, NULL, NULL, 1);
    }
    
use
  : USE basic_type ';'
    {
      $$ = SPVM_OP_build_use(compiler, $1, $2, NULL, 0);
    }
  | USE basic_type '(' opt_sub_names ')' ';'
    {
      $$ = SPVM_OP_build_use(compiler, $1, $2, $4, 0);
    }

require
  : REQUIRE basic_type
    {
      SPVM_OP* op_use = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_USE, compiler->cur_file, compiler->cur_line);
      $$ = SPVM_OP_build_use(compiler, op_use, $2, NULL, 1);
    }

enumeration
  : ENUM enumeration_block
    {
      $$ = SPVM_OP_build_enumeration(compiler, $1, $2);
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
  : sub_name
    {
      $$ = SPVM_OP_build_enumeration_value(compiler, $1, NULL);
    }
  | sub_name ASSIGN CONSTANT
    {
      $$ = SPVM_OP_build_enumeration_value(compiler, $1, $3);
    }

our
  : OUR PACKAGE_VAR_NAME ':' opt_descriptors type
    {
      $$ = SPVM_OP_build_our(compiler, $1, $2, $4, $5);
    }

has
  : HAS field_name ':' opt_descriptors type ';'
    {
      $$ = SPVM_OP_build_has(compiler, $1, $2, $4, $5);
    }

sub
  : opt_descriptors SUB sub_name ':' type_or_void '(' opt_args opt_vaarg')' block
     {
       $$ = SPVM_OP_build_sub(compiler, $2, $3, $5, $7, $1, $10, NULL, $8, 0);
     }
  | opt_descriptors SUB sub_name ':' type_or_void '(' opt_args opt_vaarg')' ';'
     {
       $$ = SPVM_OP_build_sub(compiler, $2, $3, $5, $7, $1, NULL, NULL, $8, 0);
     }

anon_sub
  : opt_descriptors SUB ':' type_or_void '(' opt_args opt_vaarg')' block
     {
       $$ = SPVM_OP_build_sub(compiler, $2, NULL, $4, $6, $1, $9, NULL, $7, 0);
     }
  | '[' args ']' opt_descriptors SUB ':' type_or_void '(' opt_args opt_vaarg')' block
     {
       SPVM_OP* op_list_args;
       if ($2->id == SPVM_OP_C_ID_LIST) {
         op_list_args = $2;
       }
       else {
         op_list_args = SPVM_OP_new_op_list(compiler, $2->file, $2->line);
         SPVM_OP_insert_child(compiler, op_list_args, op_list_args->last, $2);
       }
       
       $$ = SPVM_OP_build_sub(compiler, $5, NULL, $7, $9, $4, $12, op_list_args, $10, 0);
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
  | arg

arg
  : var ':' type
    {
      $$ = SPVM_OP_build_arg(compiler, $1, $3);
    }

opt_vaarg
  : /* Empty */
    {
      $$ = NULL;
    }
  | DOT3

invocant
  : var ':' SELF
    {
      SPVM_TYPE* type = SPVM_TYPE_new(compiler);
      type->is_self = 1;
      SPVM_OP* op_type = SPVM_OP_new_op_type(compiler, type, $3->file, $3->line);
      
      $$ = SPVM_OP_build_arg(compiler, $1, op_type);
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
  : if_statement
  | for_statement
  | while_statement
  | block
  | switch_statement
  | case_statement
  | default_statement
  | eval_block
  | if_require_statement
  | expression_term ';'
    {
      $$ = $1;
    }
  | LAST ';'
  | NEXT ';'
  | RETURN ';'
    {
      $$ = SPVM_OP_build_return(compiler, $1, NULL);
    }
  | RETURN expression_term ';'
    {
      $$ = SPVM_OP_build_return(compiler, $1, $2);
    }
  | CROAK ';'
    {
      $$ = SPVM_OP_build_croak(compiler, $1, NULL);
    }
  | CROAK expression_term ';'
    {
      $$ = SPVM_OP_build_croak(compiler, $1, $2);
    }
  | weaken_field ';'
  | weaken_array_element ';'
  | ';'
    {
      $$ = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NULL, compiler->cur_file, compiler->cur_line);
    }

for_statement
  : FOR '(' term ';' term ';' term ')' block
    {
      $$ = SPVM_OP_build_for_statement(compiler, $1, $3, $5, $7, $9);
    }

while_statement
  : WHILE '(' term ')' block
    {
      $$ = SPVM_OP_build_while_statement(compiler, $1, $3, $5);
    }

switch_statement
  : SWITCH '(' expression_term ')' block
    {
      $$ = SPVM_OP_build_switch_statement(compiler, $1, $3, $5);
    }

case_statement
  : CASE expression_term ':'
    {
      $$ = SPVM_OP_build_case_statement(compiler, $1, $2);
    }

default_statement
  : DEFAULT ':'

if_require_statement
  : IF '(' require ')' block
    {
      SPVM_OP* op_if_require = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_IF_REQUIRE, compiler->cur_file, compiler->cur_line);
      
      $$ = SPVM_OP_build_if_require_statement(compiler, op_if_require, $3, $5);
    }

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
  | UNLESS '(' term ')' block else_statement
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

opt_expression_terms
  :	/* Empty */
    {
      $$ = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    }
  |	expression_terms
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
    
term
  : expression_term
  | condition_term

expression_term
  : var
  | EXCEPTION_VAR
  | package_var_access
  | CONSTANT
  | UNDEF
  | call_sub
  | field_access
  | array_access
  | convert_type
  | new
  | array_init
  | array_length
  | string_length
  | my_var
  | binop
  | unop
  | ref
  | deref
  | assign
  | incdec
  | '(' expression_term ')'
    {
      $$ = SPVM_OP_build_single_parenthes_term(compiler, $2);
    }
  | CURRENT_PACKAGE

expression_terms
  : expression_terms ',' expression_term
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
  | expression_terms ','
    {
      $$ = $1;
    }
  | expression_term
    {
      $$ = $1;
    }

unop
  : '+' expression_term %prec UMINUS
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PLUS, $1->file, $1->line);
      $$ = SPVM_OP_build_unop(compiler, op, $2);
    }
  | '-' expression_term %prec UMINUS
    {
      SPVM_OP* op_negate = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NEGATE, $1->file, $1->line);
      $$ = SPVM_OP_build_unop(compiler, op_negate, $2);
    }
  | BIT_NOT expression_term
    {
      $$ = SPVM_OP_build_unop(compiler, $1, $2);
    }

incdec
  : INC expression_term
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PRE_INC, $1->file, $1->line);
      $$ = SPVM_OP_build_incdec(compiler, op, $2);
    }
  | expression_term INC
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_POST_INC, $2->file, $2->line);
      $$ = SPVM_OP_build_incdec(compiler, op, $1);
    }
  | DEC expression_term
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PRE_DEC, $1->file, $1->line);
      $$ = SPVM_OP_build_incdec(compiler, op, $2);
    }
  | expression_term DEC
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_POST_DEC, $2->file, $2->line);
      $$ = SPVM_OP_build_incdec(compiler, op, $1);
    }

binop
  : expression_term '+' expression_term
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ADD, $2->file, $2->line);
      $$ = SPVM_OP_build_binop(compiler, op, $1, $3);
    }
  | expression_term '-' expression_term
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_SUBTRACT, $2->file, $2->line);
      $$ = SPVM_OP_build_binop(compiler, op, $1, $3);
    }
  | expression_term '.' expression_term
    {
      $$ = SPVM_OP_build_concat(compiler, $2, $1, $3);
    }
  | expression_term MULTIPLY expression_term
    {
      $$ = SPVM_OP_build_binop(compiler, $2, $1, $3);
    }
  | expression_term DIVIDE expression_term
    {
      $$ = SPVM_OP_build_binop(compiler, $2, $1, $3);
    }
  | expression_term REMAINDER expression_term
    {
      $$ = SPVM_OP_build_binop(compiler, $2, $1, $3);
    }
  | expression_term BIT_XOR expression_term
    {
      $$ = SPVM_OP_build_binop(compiler, $2, $1, $3);
    }
  | expression_term AMPERSAND expression_term %prec BIT_AND
    {
      $$ = SPVM_OP_build_binop(compiler, $2, $1, $3);
    }
  | expression_term BIT_OR expression_term
    {
      $$ = SPVM_OP_build_binop(compiler, $2, $1, $3);
    }
  | expression_term SHIFT expression_term
    {
      $$ = SPVM_OP_build_binop(compiler, $2, $1, $3);
    }

assign
  : expression_term ASSIGN expression_term
    {
      $$ = SPVM_OP_build_assign(compiler, $2, $1, $3);
    }
  | expression_term SPECIAL_ASSIGN expression_term
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
  | NEW array_type '{' opt_expression_terms '}'
    {
      $$ = SPVM_OP_build_new(compiler, $1, $2, $4);
    }
  | anon_sub
    {
      // Package
      SPVM_OP* op_package = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_PACKAGE, $1->file, $1->line);
      
      // Create class block
      SPVM_OP* op_class_block = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CLASS_BLOCK, $1->file, $1->line);
      SPVM_OP* op_list_declarations = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
      SPVM_OP_insert_child(compiler, op_list_declarations, op_list_declarations->last, $1);
      SPVM_OP_insert_child(compiler, op_class_block, op_class_block->last, op_list_declarations);
      
      // Build package
      SPVM_OP_build_package(compiler, op_package, NULL, op_class_block, NULL);

      // Type
      SPVM_OP* op_type = SPVM_OP_new_op_type(compiler, op_package->uv.package->op_type->uv.type, $1->file, $1->line);
      
      // New
      SPVM_OP* op_new = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_NEW, $1->file, $1->line);
      $$ = SPVM_OP_build_new(compiler, op_new, op_type, NULL);
    }

array_init
  : '[' opt_expression_terms ']'
    {
      SPVM_OP* op_array_init = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_INIT, compiler->cur_file, compiler->cur_line);
      $$ = SPVM_OP_build_array_init(compiler, op_array_init, $2);
    }

convert_type
  : convert expression_term %prec CAST
    {
      SPVM_OP* op_convert = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_CONVERT, $1->file, $1->line);
      $$ = SPVM_OP_build_convert(compiler, op_convert, $1, $2);
    }

convert
  : '(' type ')'
    {
      $$ = $2;
    }

array_access
  : expression_term ARROW '[' expression_term ']'
    {
      $$ = SPVM_OP_build_array_access(compiler, $1, $4);
    }
  | array_access '[' expression_term ']'
    {
      $$ = SPVM_OP_build_array_access(compiler, $1, $3);
    }
  | field_access '[' expression_term ']'
    {
      $$ = SPVM_OP_build_array_access(compiler, $1, $3);
    }

call_sub
  : NAME '(' opt_expression_terms  ')'
    {
      $$ = SPVM_OP_build_call_sub(compiler, NULL, $1, $3);
    }
  | basic_type ARROW sub_name '(' opt_expression_terms  ')'
    {
      $$ = SPVM_OP_build_call_sub(compiler, $1, $3, $5);
    }
  | basic_type ARROW sub_name
    {
      SPVM_OP* op_expression_terms = SPVM_OP_new_op_list(compiler, $1->file, $2->line);
      $$ = SPVM_OP_build_call_sub(compiler, $1, $3, op_expression_terms);
    }
  | expression_term ARROW sub_name '(' opt_expression_terms ')'
    {
      $$ = SPVM_OP_build_call_sub(compiler, $1, $3, $5);
    }
  | expression_term ARROW sub_name
    {
      SPVM_OP* op_expression_terms = SPVM_OP_new_op_list(compiler, $1->file, $2->line);
      $$ = SPVM_OP_build_call_sub(compiler, $1, $3, op_expression_terms);
    }
  | expression_term ARROW '(' opt_expression_terms ')'
    {
      SPVM_OP* op_sub_name = SPVM_OP_new_op_name(compiler, "", $2->file, $2->line);
      $$ = SPVM_OP_build_call_sub(compiler, $1, op_sub_name, $4);
    }
field_access
  : expression_term ARROW '{' field_name '}'
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
  : WEAKEN field_access
    {
      $$ = SPVM_OP_build_weaken_field(compiler, $1, $2);
    }

weaken_array_element
  : WEAKEN array_access
    {
      $$ = SPVM_OP_build_weaken_array_element(compiler, $1, $2);
    }

array_length
  : '@' expression_term
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      $$ = SPVM_OP_build_array_length(compiler, op_array_length, $2);
    }
  | '@' '{' expression_term '}'
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      $$ = SPVM_OP_build_array_length(compiler, op_array_length, $3);
    }
  | SCALAR '@' expression_term
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      $$ = SPVM_OP_build_array_length(compiler, op_array_length, $3);
    }
  | SCALAR '@' '{' expression_term '}'
    {
      SPVM_OP* op_array_length = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_ARRAY_LENGTH, compiler->cur_file, compiler->cur_line);
      $$ = SPVM_OP_build_array_length(compiler, op_array_length, $4);
    }

string_length
  : LENGTH expression_term
    {
      $$ = SPVM_OP_build_string_length(compiler, $1, $2);
    }
deref
  : DEREF var
    {
      $$ = SPVM_OP_build_deref(compiler, $1, $2);
    }

ref
  : REF var
    {
      SPVM_OP* op_ref = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_REF, $1->file, $1->line);
      $$ = SPVM_OP_build_ref(compiler, op_ref, $2);
    }
  | REF '{' var '}'
    {
      SPVM_OP* op_ref = SPVM_OP_new_op(compiler, SPVM_OP_C_ID_REF, $1->file, $1->line);
      $$ = SPVM_OP_build_ref(compiler, op_ref, $3);
    }

condition_term
  : expression_term REL expression_term
    {
      $$ = SPVM_OP_build_binop(compiler, $2, $1, $3);
    }
  | term ISA type
    {
      $$ = SPVM_OP_build_isa(compiler, $2, $1, $3);
    }
  | term COND_OR term
    {
      $$ = SPVM_OP_build_or(compiler, $2, $1, $3);
    }
  | term COND_AND term
    {
      $$ = SPVM_OP_build_and(compiler, $2, $1, $3);
    }
  | COND_NOT term
    {
      $$ = SPVM_OP_build_not(compiler, $1, $2);
    }
  | '(' condition_term ')'
    {
      $$ = SPVM_OP_build_single_parenthes_term(compiler, $2);
    }

my_var
  : MY var ':' type
    {
      $$ = SPVM_OP_build_my(compiler, $1, $2, $4);
    }
  | MY var
    {
      $$ = SPVM_OP_build_my(compiler, $1, $2, NULL);
    }

var
  : VAR_NAME
    {
      $$ = SPVM_OP_build_var(compiler, $1);
    }

package_var_access
  : PACKAGE_VAR_NAME
    {
      $$ = SPVM_OP_build_package_var_access(compiler, $1);
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
  : basic_type AMPERSAND
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
  : basic_type '[' expression_term ']'
    {
      $$ = SPVM_OP_build_array_type(compiler, $1, $3);
    }
  | array_type '[' expression_term ']'
    {
      $$ = SPVM_OP_build_array_type(compiler, $1, $3);
    }

type_or_void
  : type
  | VOID
    {
      $$ = SPVM_OP_new_op_void_type(compiler, compiler->cur_file, compiler->cur_line);
    }

field_name
  : NAME

sub_name
  : NAME

opt_sub_names
  :	/* Empty */
    {
      $$ = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    }
  |	sub_names
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

sub_names
  : sub_names ',' sub_name
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
  | sub_name

%%
