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
%}

%token <opval> MY HAS SUB PACKAGE IF ELSIF ELSE RETURN FOR WHILE USE MALLOC
%token <opval> LAST NEXT NAME VAR CONSTANT ENUM DESCRIPTOR CORETYPE UNDEF DIE
%token <opval> SWITCH CASE DEFAULT VOID TRY CATCH

%type <opval> grammar opt_statements statements statement my field if_statement else_statement
%type <opval> block enumeration_block package_block sub opt_declarations_in_package call_sub unop binop
%type <opval> opt_terms terms term args arg opt_args use declaration_in_package declarations_in_package
%type <opval> enumeration_values enumeration_value
%type <opval> type package_name field_name sub_name package declarations_in_grammar opt_enumeration_values type_array
%type <opval> for_statement while_statement expression opt_declarations_in_grammar opt_term
%type <opval> call_field array_elem convert_type enumeration new_object type_name array_length declaration_in_grammar
%type <opval> switch_statement case_statement default_statement type_array_with_length
%type <opval> ';' opt_descriptors descriptors type_or_void normal_statement try_catch


%right <opval> ASSIGN
%left <opval> OR
%left <opval> AND
%left <opval> BIT_OR BIT_XOR
%left <opval> BIT_AND
%nonassoc <opval> REL
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
      $$ = SPVM_OP_new_op_list(compiler, compiler->cur_module_path, compiler->cur_line);
    }
  |	declarations_in_grammar
    {
      if ($1->code == SPVM_OP_C_CODE_LIST) {
        $$ = $1;
      }
      else {
        $$ = SPVM_OP_new_op_list(compiler, $1->file, $1->line);
        SPVM_OP_sibling_splice(compiler, $$, $$->first, 0, $1);
      }
    }
  
declarations_in_grammar
  : declarations_in_grammar declaration_in_grammar
    {
      $$ = SPVM_OP_append_elem(compiler, $1, $2, $1->file, $1->line);
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
      $$ = SPVM_OP_new_op_list(compiler, compiler->cur_module_path, compiler->cur_line);
    }
  |	declarations_in_package
    {
      if ($1->code == SPVM_OP_C_CODE_LIST) {
        $$ = $1;
      }
      else {
        $$ = SPVM_OP_new_op_list(compiler, $1->file, $1->line);
        SPVM_OP_sibling_splice(compiler, $$, $$->first, 0, $1);
      }
    }

declarations_in_package
  : declarations_in_package declaration_in_package
    {
      $$ = SPVM_OP_append_elem(compiler, $1, $2, $1->file, $1->line);
    }
  | declaration_in_package

declaration_in_package
  : field
  | sub
  | enumeration

package_block
  : '{' opt_declarations_in_package '}'
    {
      $$ = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_CLASS_BLOCK, $1->file, $1->line);
      SPVM_OP_sibling_splice(compiler, $$, NULL, 0, $2);
    }

enumeration_block 
  : '{' opt_enumeration_values '}'
    {
      $$ = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_ENUM_BLOCK, $1->file, $1->line);
      SPVM_OP_sibling_splice(compiler, $$, NULL, 0, $2);
    }

opt_enumeration_values
  :	/* Empty */
    {
      $$ = SPVM_OP_new_op_list(compiler, compiler->cur_module_path, compiler->cur_line);
    }
  |	enumeration_values
    {
      if ($1->code == SPVM_OP_C_CODE_LIST) {
        $$ = $1;
      }
      else {
        $$ = SPVM_OP_new_op_list(compiler, $1->file, $1->line);
        SPVM_OP_sibling_splice(compiler, $$, $$->first, 0, $1);
      }
    }
    
enumeration_values
  : enumeration_values ',' enumeration_value 
    {
      $$ = SPVM_OP_append_elem(compiler, $1, $3, $1->file, $1->line);
    }
  | enumeration_value
  
enumeration_value
  : NAME
    {
      $$ = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_ENUMERATION_VALUE, $1->file, $1->line);
      SPVM_OP_sibling_splice(compiler, $$, NULL, 0, $1);
    }
  | NAME ASSIGN CONSTANT
    {
      $$ = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_ENUMERATION_VALUE, $1->file, $1->line);
      SPVM_OP_sibling_splice(compiler, $$, NULL, 0, $1);
      SPVM_OP_sibling_splice(compiler, $$, $1, 0, $3);
    }

opt_statements
  :	/* Empty */
    {
      $$ = SPVM_OP_new_op_list(compiler, compiler->cur_module_path, compiler->cur_line);
    }
  |	statements
    {
      if ($1->code == SPVM_OP_C_CODE_LIST) {
        $$ = $1;
      }
      else {
        $$ = SPVM_OP_new_op_list(compiler, $1->file, $1->line);
        SPVM_OP_sibling_splice(compiler, $$, $$->first, 0, $1);
      }
    }
    
statements
  : statements statement 
    {
      $$ = SPVM_OP_append_elem(compiler, $1, $2, $1->file, $1->line);
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
  | try_catch

block 
  : '{' opt_statements '}'
    {
      $$ = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_BLOCK, $1->file, $1->line);
      SPVM_OP_sibling_splice(compiler, $$, NULL, 0, $2);
    }

normal_statement
  : term ';'
    {
      $$ = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_POP, $1->file, $1->line);
      SPVM_OP_sibling_splice(compiler, $$, NULL, 0, $1);
    }
  | expression ';'
  | ';'
    {
      $$ = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_NULL, $1->file, $1->line);
    }

for_statement
  : FOR '(' normal_statement term ';' opt_term ')' block
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
      $$ = SPVM_OP_build_if_statement(compiler, $1, $3, $5, $6);
    }

else_statement
  : /* NULL */
    {
      $$ = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_NULL, compiler->cur_module_path, compiler->cur_line);
    };
  | ELSE block
    {
      $2->flag |= SPVM_OP_C_FLAG_BLOCK_ELSE;
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
enumeration
  : ENUM enumeration_block
    {
      $$ = SPVM_OP_build_enumeration(compiler, $1, $2);
    }

my
  : MY VAR ':' type
    {
      $$ = SPVM_OP_build_my_var(compiler, $1, $2, $4, NULL);
    }
  | MY VAR
    {
      $$ = SPVM_OP_build_my_var(compiler, $1, $2, NULL, NULL);
    }
  | MY VAR ':' type ASSIGN term
    {
      $$ = SPVM_OP_build_my_var(compiler, $1, $2, $4, $6);
    }
  | MY VAR ASSIGN term
    {
      $$ = SPVM_OP_build_my_var(compiler, $1, $2, NULL, $4);
    }

expression
  : LAST
    {
      $$ = SPVM_OP_build_last(compiler, $1);
    }
  | NEXT
    {
      $$ = SPVM_OP_build_next(compiler, $1);
    }
  | RETURN {
      $$ = SPVM_OP_build_return(compiler, $1, NULL);
    }
  | RETURN term
    {
      $$ = SPVM_OP_build_return(compiler, $1, $2);
    }
  | DIE term
    {
      $$ = SPVM_OP_build_die(compiler, $1, $2);
    }
  | my

opt_terms
  :	/* Empty */
    {
      $$ = SPVM_OP_new_op_list(compiler, compiler->cur_module_path, compiler->cur_line);
    }
  |	terms
    {
      if ($1->code == SPVM_OP_C_CODE_LIST) {
        $$ = $1;
      }
      else {
        $$ = SPVM_OP_new_op_list(compiler, $1->file, $1->line);
        SPVM_OP_sibling_splice(compiler, $$, $$->first, 0, $1);
      }
    }
    
terms
  : terms ',' term
    {
      $$ = SPVM_OP_append_elem(compiler, $1, $3, $1->file, $1->line);
    }
  | term

array_length
  : ARRAY_LENGTH term
    {
      $$ = SPVM_OP_build_array_length(compiler, $1, $2);
    }

opt_term
  : /* NULL */
    {
      $$ = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_NULL, compiler->cur_module_path, compiler->cur_line);
    }
  | term

term
  : VAR
  | CONSTANT
  | UNDEF
  | call_sub
  | call_field
  | unop
  | binop
  | array_elem
  | convert_type
  | new_object
  | array_length

new_object
  : MALLOC type_name
    {
      $$ = SPVM_OP_build_malloc_object(compiler, $1, $2);
    }
  | MALLOC type_array_with_length
    {
      $$ = SPVM_OP_build_malloc_object(compiler, $1, $2);
    }

convert_type
  : '(' type ')' term
    {
      $$ = SPVM_OP_build_convert_type(compiler, $2, $4);
    }

call_field
  : term '{' field_name '}'
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
      SPVM_OP* op = SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_NEGATE, $1->file, $1->line);
      $$ = SPVM_OP_build_unop(compiler, op, $2);
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
  | term ASSIGN term
    {
      $$ = SPVM_OP_build_binop(compiler, $2, $1, $3);
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
  : term '[' term ']'
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
      $$ = SPVM_OP_new_op_list(compiler, compiler->cur_module_path, compiler->cur_line);
    }
  |	args
    {
      if ($1->code == SPVM_OP_C_CODE_LIST) {
        $$ = $1;
      }
      else {
        $$ = SPVM_OP_new_op_list(compiler, $1->file, $1->line);
        SPVM_OP_sibling_splice(compiler, $$, $$->first, 0, $1);
      }
    }

args
  : args ',' arg
    {
      $$ = SPVM_OP_append_elem(compiler, $1, $3, $1->file, $1->line);
    }
  | arg

arg
  : VAR ':' type
    {
      $$ = SPVM_OP_build_my_var(compiler, SPVM_OP_new_op(compiler, SPVM_OP_C_CODE_MY_VAR, $1->file, $1->line), $1, $3, NULL);
    }

opt_descriptors
  :	/* Empty */
    {
      $$ = SPVM_OP_new_op_list(compiler, compiler->cur_module_path, compiler->cur_line);
    }
  |	descriptors
    {
      if ($1->code == SPVM_OP_C_CODE_LIST) {
        $$ = $1;
      }
      else {
        $$ = SPVM_OP_new_op_list(compiler, $1->file, $1->line);
        SPVM_OP_sibling_splice(compiler, $$, $$->first, 0, $1);
      }
    }
    
descriptors
  : descriptors ',' DESCRIPTOR
    {
      $$ = SPVM_OP_append_elem(compiler, $1, $3, $1->file, $1->line);
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

try_catch
  : TRY block CATCH '(' VAR ')' block
    {
      $$ = SPVM_OP_build_try_catch(compiler, $1, $2, $3, $5, $7);
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

%%

