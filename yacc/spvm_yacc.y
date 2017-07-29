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
%}

%token <opval> MY HAS SUB PACKAGE IF ELSIF ELSE RETURN FOR WHILE USE NEW
%token <opval> LAST NEXT NAME VAR CONSTANT ENUM DESCRIPTOR CORETYPE UNDEF DIE
%token <opval> SWITCH CASE DEFAULT VOID EVAL EXCEPTION_VAR

%type <opval> grammar opt_statements statements statement my_var field if_statement else_statement
%type <opval> block enumeration_block package_block sub opt_declarations_in_package call_sub unop binop
%type <opval> opt_terms terms term args arg opt_args use declaration_in_package declarations_in_package
%type <opval> enumeration_values enumeration_value
%type <opval> type package_name field_name sub_name package declarations_in_grammar opt_enumeration_values type_array
%type <opval> for_statement while_statement expression opt_declarations_in_grammar
%type <opval> call_field array_elem convert_type enumeration new_object type_name array_length declaration_in_grammar
%type <opval> switch_statement case_statement default_statement type_array_with_length
%type <opval> ';' opt_descriptors descriptors type_or_void normal_statement normal_statement_for_end eval_block


%right <opval> ASSIGN
%left <opval> OR
%left <opval> AND
%left <opval> BIT_OR BIT_XOR
%left <opval> BIT_AND
%nonassoc <opval> REL '<' '>'
%left <opval> SHIFT
%left <opval> '+' '-'
%left <opval> MULTIPLY DIVIDE REMAINDER
%right <opval> NOT '~' ARRAY_LENGTH UMINUS
%nonassoc <opval> INC DEC
%left <opval> ARROW
%nonassoc <opval> ')'
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
      if ($1->code == SPVM_OP_C_CODE_LIST) {
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
      if ($1->code == SPVM_OP_C_CODE_LIST) {
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
  : PACKAGE package_name package_block
    {
      $$ = SPVM_OP_build_package(compiler, $1, $2, $3);
      if (compiler->fatal_error) {
        YYABORT;
      }
    }

opt_declarations_in_package
  :	/* Empty */
    {
      $$ = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    }
  |	declarations_in_package
    {
      if ($1->code == SPVM_OP_C_CODE_LIST) {
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
      if ($1->code == SPVM_OP_C_CODE_LIST) {
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

package_block
  : '{' opt_declarations_in_package '}'
    {
      SPVM_OP* op_class_block = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_CLASS_BLOCK, $1->file, $1->line);
      SPVM_OP_insert_child(compiler, op_class_block, op_class_block->last, $2);
      $$ = op_class_block;
    }

enumeration_block 
  : '{' opt_enumeration_values '}'
    {
      SPVM_OP* op_enum_block = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_ENUM_BLOCK, $1->file, $1->line);
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
      if ($1->code == SPVM_OP_C_CODE_LIST) {
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
      if ($1->code == SPVM_OP_C_CODE_LIST) {
        op_list = $1;
      }
      else {
        op_list = SPVM_OP_new_op_list(compiler, $1->file, $1->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, $1);
      }
      SPVM_OP_insert_child(compiler, op_list, op_list->last, $3);
      
      $$ = op_list;
    }
  | enumeration_value
  
enumeration_value
  : NAME
    {
      SPVM_OP* op_enumeration_value = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_ENUMERATION_VALUE, $1->file, $1->line);
      SPVM_OP_insert_child(compiler, op_enumeration_value, op_enumeration_value->last, $1);
      $$ = op_enumeration_value;
    }
  | NAME ASSIGN term
    {
      SPVM_OP* op_enumeration_value = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_ENUMERATION_VALUE, $1->file, $1->line);
      SPVM_OP_insert_child(compiler, op_enumeration_value, op_enumeration_value->last, $1);
      SPVM_OP_insert_child(compiler, op_enumeration_value, op_enumeration_value->last, $3);
      $$ = op_enumeration_value;
    }

opt_statements
  :	/* Empty */
    {
      $$ = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    }
  |	statements
    {
      if ($1->code == SPVM_OP_C_CODE_LIST) {
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
      if ($1->code == SPVM_OP_C_CODE_LIST) {
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
      SPVM_OP* op_code_block = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_BLOCK, $1->file, $1->line);
      SPVM_OP_insert_child(compiler, op_code_block, op_code_block->last, $2);
      $$ = op_code_block;
    }

normal_statement
  : term ';'
    {
      SPVM_OP* op_pop = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_POP, $1->file, $1->line);
      SPVM_OP_insert_child(compiler, op_pop, op_pop->last, $1);
      $$ = op_pop;
    }
  | expression ';'
  | ';'
    {
      $$ = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_NULL, $1->file, $1->line);
    }

normal_statement_for_end
  : term
    {
      SPVM_OP* op_pop = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_POP, $1->file, $1->line);
      SPVM_OP_insert_child(compiler, op_pop, op_pop->last, $1);
      $$ = op_pop;
    }
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
  : SWITCH '(' term ')' block
    {
      $$ = SPVM_OP_build_switch_statement(compiler, $1, $3, $5);
    }

case_statement
  : CASE term ':'
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
      SPVM_OP* op_block = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_BLOCK, $1->file, $1->line);
      SPVM_OP_insert_child(compiler, op_block, op_block->last, op_if);
      
      $$ = op_block;
    }

else_statement
  : /* NULL */
    {
      $$ = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_NULL, compiler->cur_file, compiler->cur_line);
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
  : HAS field_name ':' type ';'
    {
      $$ = SPVM_OP_build_field(compiler, $1, $2, $4);
    }

sub
 : SUB sub_name '(' opt_args ')' ':' opt_descriptors type_or_void block
     {
       $$ = SPVM_OP_build_sub(compiler, $1, $2, $4, $7, $8, $9);
     }
 | SUB sub_name '(' opt_args ')' ':' opt_descriptors type_or_void ';'
     {
       $$ = SPVM_OP_build_sub(compiler, $1, $2, $4, $7, $8, NULL);
     }
 | SUB NEW '(' opt_args ')' ':' opt_descriptors type_or_void block
     {
       $$ = SPVM_OP_build_sub(compiler, $1, $2, $4, $7, $8, $9);
     }
 | SUB NEW '(' opt_args ')' ':' opt_descriptors type_or_void ';'
     {
       $$ = SPVM_OP_build_sub(compiler, $1, $2, $4, $7, $8, NULL);
     }
enumeration
  : ENUM enumeration_block
    {
      $$ = SPVM_OP_build_enumeration(compiler, $1, $2);
    }

my_var
  : MY VAR ':' type
    {
      $$ = SPVM_OP_build_my_var(compiler, $1, $2, $4);
    }
  | MY VAR
    {
      $$ = SPVM_OP_build_my_var(compiler, $1, $2, NULL);
    }

expression
  : LAST
  | NEXT
  | RETURN {
      $$ = SPVM_OP_build_return(compiler, $1, NULL);
    }
  | RETURN term
    {
      $$ = SPVM_OP_build_return(compiler, $1, $2);
    }
  | DIE
    {
      $$ = SPVM_OP_build_die(compiler, $1, NULL);
    }
  | DIE term
    {
      $$ = SPVM_OP_build_die(compiler, $1, $2);
    }
  | call_field ASSIGN term
    {
      $$ = SPVM_OP_build_assignop(compiler, $2, $1, $3);
    }
  | array_elem ASSIGN term
    {
      $$ = SPVM_OP_build_assignop(compiler, $2, $1, $3);
    }
  | EXCEPTION_VAR ASSIGN term
    {
      $$ = SPVM_OP_build_assignop(compiler, $2, $1, $3);
    }

opt_terms
  :	/* Empty */
    {
      $$ = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    }
  |	terms
    {
      if ($1->code == SPVM_OP_C_CODE_LIST) {
        $$ = $1;
      }
      else {
        SPVM_OP* op_list = SPVM_OP_new_op_list(compiler, $1->file, $1->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, $1);
        $$ = op_list;
      }
    }
    
terms
  : terms ',' term
    {
      SPVM_OP* op_list;
      if ($1->code == SPVM_OP_C_CODE_LIST) {
        op_list = $1;
      }
      else {
        op_list = SPVM_OP_new_op_list(compiler, $1->file, $1->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, $1);
      }
      SPVM_OP_insert_child(compiler, op_list, op_list->last, $3);
      
      $$ = op_list;
    }
  | term

array_length
  : ARRAY_LENGTH term
    {
      $$ = SPVM_OP_build_array_length(compiler, $1, $2);
    }
  | ARRAY_LENGTH '{' term '}'
    {
      $$ = SPVM_OP_build_array_length(compiler, $1, $3);
    }

term
  : VAR
  | EXCEPTION_VAR
  | CONSTANT
    {
      $$ = SPVM_OP_build_constant(compiler, $1);
    }
  | UNDEF
  | call_sub
  | call_field
  | unop
  | binop
  | array_elem
  | convert_type
  | new_object
  | array_length
  | my_var

new_object
  : NEW type_name
    {
      $$ = SPVM_OP_build_malloc_object(compiler, $1, $2);
    }
  | NEW type_array_with_length
    {
      $$ = SPVM_OP_build_malloc_object(compiler, $1, $2);
    }

convert_type
  : '(' type ')' term
    {
      $$ = SPVM_OP_build_convert_type(compiler, $2, $4);
    }

call_field
  : term ARROW '{' field_name '}'
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

unop
  : '+' term %prec UMINUS
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_PLUS, $1->file, $1->line);
      $$ = SPVM_OP_build_unop(compiler, op, $2);
    }
  | '-' term %prec UMINUS
    {
      if ($2->code == SPVM_OP_C_CODE_CONSTANT) {
        SPVM_OP* op_constant = $2;
        SPVM_CONSTANT* constant = op_constant->uv.constant;
        if (constant->sign) {
          constant->sign = 0;
        }
        else {
          constant->sign = 1;
        }
        $$ = op_constant;
      }
      else {
        SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_NEGATE, $1->file, $1->line);
        $$ = SPVM_OP_build_unop(compiler, op, $2);
      }
    }
  | INC term
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_PRE_INC, $1->file, $1->line);
      $$ = SPVM_OP_build_unop(compiler, op, $2);
    }
  | term INC
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_POST_INC, $2->file, $2->line);
      $$ = SPVM_OP_build_unop(compiler, op, $1);
    }
  | DEC term
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_PRE_DEC, $1->file, $1->line);
      $$ = SPVM_OP_build_unop(compiler, op, $2);
    }
  | term DEC
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_POST_DEC, $2->file, $2->line);
      $$ = SPVM_OP_build_unop(compiler, op, $1);
    }
  | '~' term
    {
      $$ = SPVM_OP_build_unop(compiler, $1, $2);
    }
  | NOT term
    {
      $$ = SPVM_OP_build_unop(compiler, $1, $2);
    }

binop
  : term '+' term
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_ADD, $2->file, $2->line);
      $$ = SPVM_OP_build_binop(compiler, op, $1, $3);
    }
  | term '-' term
    {
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_SUBTRACT, $2->file, $2->line);
      $$ = SPVM_OP_build_binop(compiler, op, $1, $3);
    }
  | term MULTIPLY term
    {
      $$ = SPVM_OP_build_binop(compiler, $2, $1, $3);
    }
  | term DIVIDE term
    {
      $$ = SPVM_OP_build_binop(compiler, $2, $1, $3);
    }
  | term REMAINDER term
    {
      $$ = SPVM_OP_build_binop(compiler, $2, $1, $3);
    }
  | term BIT_XOR term
    {
      $$ = SPVM_OP_build_binop(compiler, $2, $1, $3);
    }
  | term BIT_AND term
    {
      $$ = SPVM_OP_build_binop(compiler, $2, $1, $3);
    }
  | term BIT_OR term
    {
      $$ = SPVM_OP_build_binop(compiler, $2, $1, $3);
    }
  | term SHIFT term
    {
      $$ = SPVM_OP_build_binop(compiler, $2, $1, $3);
    }
  | term REL term
    {
      $$ = SPVM_OP_build_binop(compiler, $2, $1, $3);
    }
  | term '<' term %prec REL
    {
      SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_LT);
      $$ = SPVM_OP_build_binop(compiler, op, $1, $3);
    }
  | term '>' term %prec REL
    {
      SPVM_OP* op = SPVM_TOKE_newOP(compiler, SPVM_OP_C_CODE_GT);
      $$ = SPVM_OP_build_binop(compiler, op, $1, $3);
    }
  | my_var ASSIGN '[' opt_terms ']'
    {
      $$ = SPVM_OP_build_assignop(compiler, $2, $1, $4);
    }
  | my_var ASSIGN term
    {
      $$ = SPVM_OP_build_assignop(compiler, $2, $1, $3);
    }
  | VAR ASSIGN term
    {
      $$ = SPVM_OP_build_assignop(compiler, $2, $1, $3);
    }
  | '(' term ')'
    {
      $$ = $2;
    }
  | term OR term
    {
      $$ = SPVM_OP_build_binop(compiler, $2, $1, $3);
    }
  | term AND term
    {
      $$ = SPVM_OP_build_binop(compiler, $2, $1, $3);
    }

array_elem
  : term ARROW '[' term ']'
    {
      $$ = SPVM_OP_build_array_elem(compiler, $1, $4);
    }
  | array_elem '[' term ']'
    {
      $$ = SPVM_OP_build_array_elem(compiler, $1, $3);
    }
  | call_field '[' term ']'
    {
      $$ = SPVM_OP_build_array_elem(compiler, $1, $3);
    }

call_sub
  : sub_name '(' opt_terms  ')'
    {
      $$ = SPVM_OP_build_call_sub(compiler, SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_NULL, $1->file, $1->line), $1, $3);
    }
  | term ARROW sub_name '(' opt_terms ')'
    {
      $$ = SPVM_OP_build_call_sub(compiler, $1, $3, $5);
    }
  | term ARROW sub_name
    {
      SPVM_OP* op_terms = SPVM_OP_new_op_list(compiler, $1->file, $2->line);
      $$ = SPVM_OP_build_call_sub(compiler, $1, $3, op_terms);
    }
  | package_name ARROW sub_name '(' opt_terms  ')'
    {
      $$ = SPVM_OP_build_call_sub(compiler, $1, $3, $5);
    }
  | package_name ARROW sub_name
    {
      SPVM_OP* op_terms = SPVM_OP_new_op_list(compiler, $1->file, $2->line);
      $$ = SPVM_OP_build_call_sub(compiler, $1, $3, op_terms);
    }
    
opt_args
  :	/* Empty */
    {
      $$ = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    }
  |	args
    {
      if ($1->code == SPVM_OP_C_CODE_LIST) {
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
      if ($1->code == SPVM_OP_C_CODE_LIST) {
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
  : VAR ':' type
    {
      $$ = SPVM_OP_build_my_var(compiler, SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_MY, $1->file, $1->line), $1, $3);
    }

opt_descriptors
  :	/* Empty */
    {
      $$ = SPVM_OP_new_op_list(compiler, compiler->cur_file, compiler->cur_line);
    }
  |	descriptors
    {
      if ($1->code == SPVM_OP_C_CODE_LIST) {
        $$ = $1;
      }
      else {
        SPVM_OP* op_list = SPVM_OP_new_op_list(compiler, $1->file, $1->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->first, $1);
        $$ = op_list;
      }
    }
    
descriptors
  : descriptors ',' DESCRIPTOR
    {
      SPVM_OP* op_list;
      if ($1->code == SPVM_OP_C_CODE_LIST) {
        op_list = $1;
      }
      else {
        op_list = SPVM_OP_new_op_list(compiler, $1->file, $1->line);
        SPVM_OP_insert_child(compiler, op_list, op_list->last, $1);
      }
      SPVM_OP_insert_child(compiler, op_list, op_list->last, $3);
      
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
  : type_name '[' term ']'
    {
      $$ = SPVM_OP_build_type_array(compiler, $1, $3);
    }
  | type_array '[' term ']'
    {
      $$ = SPVM_OP_build_type_array(compiler, $1, $3);
    }

type_or_void
  : type
  | VOID


field_name : NAME
sub_name : NAME
package_name : NAME

eval_block
  : EVAL block
    {
      $$ = SPVM_OP_build_eval(compiler, $1, $2);
    }

%%
