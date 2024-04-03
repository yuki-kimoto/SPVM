=head1 Name

SPVM::Document::Language::SyntaxParsing - Syntax Parsing in the SPVM Language

=head1 Description

This document describes syntax parsing in the SPVM language.

=head1 Syntax Parsing

Syntax parsing is the next step to build an AST after L<tokenization|SPVM::Document::Language::Tokenization>.

=head2 Syntax Parsing Rule

The rule of the syntax parsing of the SPVM language is described using L<GNU Bison|https://en.wikipedia.org/wiki/GNU_Bison> syntax.

  %token <opval> CLASS HAS METHOD OUR ENUM MY USE AS REQUIRE ALIAS ALLOW CURRENT_CLASS MUTABLE
  %token <opval> ATTRIBUTE MAKE_READ_ONLY INTERFACE EVAL_ERROR_ID ARGS_WIDTH VERSION_DECL
  %token <opval> IF UNLESS ELSIF ELSE FOR WHILE LAST NEXT SWITCH CASE DEFAULT BREAK EVAL
  %token <opval> SYMBOL_NAME VAR_NAME CONSTANT EXCEPTION_VAR
  %token <opval> UNDEF VOID BYTE SHORT INT LONG FLOAT DOUBLE STRING OBJECT TRUE FALSE END_OF_FILE
  %token <opval> FATCAMMA RW RO WO INIT NEW OF BASIC_TYPE_ID EXTENDS SUPER
  %token <opval> RETURN WEAKEN DIE WARN PRINT SAY CURRENT_CLASS_NAME UNWEAKEN '[' '{' '('
  %type <opval> grammar
  %type <opval> field_name method_name class_name
  %type <opval> type qualified_type basic_type array_type class_type opt_class_type
  %type <opval> array_type_with_length ref_type return_type type_comment opt_type_comment union_type
  %type <opval> opt_classes classes class class_block opt_extends version_decl
  %type <opval> opt_definitions definitions definition
  %type <opval> enumeration enumeration_block opt_enumeration_values enumeration_values enumeration_value
  %type <opval> method anon_method opt_args args arg use require class_alias our has has_for_anon_list has_for_anon interface allow
  %type <opval> opt_attributes attributes
  %type <opval> opt_statements statements statement if_statement else_statement
  %type <opval> for_statement while_statement foreach_statement
  %type <opval> switch_statement case_statement case_statements opt_case_statements default_statement
  %type <opval> block eval_block init_block switch_block if_require_statement
  %type <opval> die
  %type <opval> var_decl var
  %type <opval> operator opt_operators operators opt_operator
  %type <opval> void_return_operator warn
  %type <opval> unary_operator array_length
  %type <opval> inc dec
  %type <opval> binary_operator arithmetic_operator bit_operator comparison_operator string_concatenation logical_operator
  %type <opval> assign
  %type <opval> new array_init
  %type <opval> type_check type_cast can
  %type <opval> call_method
  %type <opval> element_access field_access
  %type <opval> weaken_field unweaken_field isweak_field
  %type <opval> sequential
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
  %right <opval> LOGICAL_NOT BIT_NOT '@' REFERENCE DEREFERENCE PLUS MINUS CONVERT SCALAR STRING_LENGTH ISWEAK TYPE_NAME COMPILE_TYPE_NAME DUMP NEW_STRING_LEN IS_READ_ONLY COPY
  %nonassoc <opval> INC DEC
  %left <opval> ARROW

  grammar
    : opt_classes

  field_name
    : SYMBOL_NAME

  method_name
    : SYMBOL_NAME

  class_name
    : SYMBOL_NAME

  qualified_type
    : type
    | MUTABLE type {

  type
    : basic_type
    | array_type
    | ref_type

  class_type
    : basic_type

  basic_type
    : SYMBOL_NAME
    | BYTE
    | SHORT
    | INT
    | LONG
    | FLOAT
    | DOUBLE
    | OBJECT
    | STRING

  ref_type
    : basic_type '*'

  array_type
    : basic_type '[' ']'
    | array_type '[' ']'

  array_type_with_length
    : basic_type '[' operator ']'
    | array_type '[' operator ']'

  return_type
    : qualified_type opt_type_comment
    | VOID

  opt_type_comment
    : /* Empty */
    | type_comment

  type_comment
    : OF union_type

  union_type
    : union_type BIT_OR type
    | type

  opt_classes
    : /* Empty */
    | classes

  classes
    : classes class
    | class

  class
    : CLASS opt_class_type opt_extends class_block END_OF_FILE
    | CLASS opt_class_type opt_extends ':' opt_attributes class_block END_OF_FILE
    | CLASS opt_class_type opt_extends ';' END_OF_FILE
    | CLASS opt_class_type opt_extends ':' opt_attributes ';' END_OF_FILE

  opt_class_type
    : /* Empty */
    | class_type

  opt_extends
    : /* Empty */
    | EXTENDS basic_type

  class_block
    : '{' opt_definitions '}'

  opt_definitions
    : /* Empty */
    | definitions

  definitions
    : definitions definition
    | definition

  definition
    : version_decl
    | use
    | class_alias
    | allow
    | interface
    | init_block
    | enumeration
    | our
    | has ';'
    | method

  init_block
    : INIT block

  version_decl
    : VERSION_DECL CONSTANT ';'

  use
    : USE basic_type ';'
    | USE basic_type AS class_name ';'

  require
    : REQUIRE basic_type

  class_alias
    : ALIAS basic_type AS class_name ';'

  allow
    : ALLOW basic_type ';'

  interface
    : INTERFACE basic_type ';'

  enumeration
    : opt_attributes ENUM enumeration_block

  enumeration_block
    : '{' opt_enumeration_values '}'

  opt_enumeration_values
    : /* Empty */
    | enumeration_values

  enumeration_values
    : enumeration_values ',' enumeration_value
    | enumeration_values ','
    | enumeration_value

  enumeration_value
    : method_name
    | method_name ASSIGN CONSTANT

  our
    : OUR VAR_NAME ':' opt_attributes qualified_type opt_type_comment ';'

  has
    : HAS field_name ':' opt_attributes qualified_type opt_type_comment

  method
    : opt_attributes METHOD method_name ':' return_type '(' opt_args ')' block
    | opt_attributes METHOD method_name ':' return_type '(' opt_args ')' ';'
    | opt_attributes METHOD ':' return_type '(' opt_args ')' block
    | opt_attributes METHOD ':' return_type '(' opt_args ')' ';'

  anon_method
    : opt_attributes METHOD ':' return_type '(' opt_args ')' block
    | '[' has_for_anon_list ']' opt_attributes METHOD ':' return_type '(' opt_args ')' block

  opt_args
    : /* Empty */
    | args

  args
    : args ',' arg
    | args ','
    | arg

  arg
    : var ':' qualified_type opt_type_comment
    | var ':' qualified_type opt_type_comment ASSIGN operator

  has_for_anon_list
    : has_for_anon_list ',' has_for_anon
    | has_for_anon_list ','
    | has_for_anon

  has_for_anon
    : HAS field_name ':' opt_attributes qualified_type opt_type_comment
    | HAS field_name ':' opt_attributes qualified_type opt_type_comment ASSIGN operator
    | var ':' opt_attributes qualified_type opt_type_comment

  opt_attributes
    : /* Empty */
    | attributes

  attributes
    : attributes ATTRIBUTE
    | ATTRIBUTE

  opt_statements
    : /* Empty */
    | statements

  statements
    : statements statement
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
    | RETURN operator ';'
    | operator ';'
    | void_return_operator ';'
    | ';'
    | die ';'

  die
    : DIE operator
    | DIE
    | DIE type operator
    | DIE type
    | DIE operator ',' operator

  void_return_operator
    : warn
    | PRINT operator
    | SAY operator
    | weaken_field
    | unweaken_field
    | MAKE_READ_ONLY operator

  warn
    : WARN operator
    | WARN

  for_statement
    : FOR '(' opt_operator ';' operator ';' opt_operator ')' block

  foreach_statement
    : FOR var_decl '(' '@' operator ')' block
    | FOR var_decl '(' '@' '{' operator '}' ')' block

  while_statement
    : WHILE '(' operator ')' block

  switch_statement
    : SWITCH '(' operator ')' switch_block

  switch_block
    : '{' opt_case_statements '}'
    | '{' opt_case_statements default_statement '}'

  opt_case_statements
    : /* Empty */
    | case_statements

  case_statements
    : case_statements case_statement
    | case_statement

  case_statement
    : CASE operator ':' block
    | CASE operator ':'

  default_statement
    : DEFAULT ':' block
    | DEFAULT ':'

  if_require_statement
    : IF '(' require ')' block
    | IF '(' require ')' block ELSE block

  if_statement
    : IF '(' operator ')' block else_statement
    | UNLESS '(' operator ')' block else_statement

  else_statement
    : /* NULL */
    | ELSE block
    | ELSIF '(' operator ')' block else_statement

  block
    : '{' opt_statements '}'

  eval_block
    : EVAL block

  var_decl
    : MY var ':' qualified_type opt_type_comment
    | MY var

  var
    : VAR_NAME

  opt_operators
    : /* Empty */
    | operators

  opt_operator
    : /* Empty */
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
    | FALSE
    | CURRENT_CLASS_NAME
    | unary_operator
    | binary_operator
    | assign
    | inc
    | dec
    | type_check
    | BASIC_TYPE_ID type
    | can
    | array_init
    | element_access
    | field_access
    | isweak_field
    | call_method
    | sequential

  sequential
    : '(' operators ')'

  operators
    : operators ',' operator
    | operators ','
    | operator

  unary_operator
    : '+' operator %prec PLUS
    | '-' operator %prec MINUS
    | BIT_NOT operator
    | TYPE_NAME operator
    | COMPILE_TYPE_NAME operator
    | STRING_LENGTH operator
    | DUMP operator
    | DEREFERENCE var
    | REFERENCE operator
    | NEW_STRING_LEN operator
    | COPY operator
    | IS_READ_ONLY operator
    | array_length

  array_length
    : '@' operator
    | '@' '{' operator '}'
    | SCALAR '@' operator
    | SCALAR '@' '{' operator '}'

  inc
    : INC operator
    | operator INC

  dec
    : DEC operator
    | operator DEC

  binary_operator
    : arithmetic_operator
    | bit_operator
    | comparison_operator
    | string_concatenation
    | logical_operator

  arithmetic_operator
    : operator '+' operator
    | operator '-' operator
    | operator '*' operator
    | operator DIVIDE operator
    | operator DIVIDE_UNSIGNED_INT operator
    | operator DIVIDE_UNSIGNED_LONG operator
    | operator MODULO operator
    | operator MODULO_UNSIGNED_INT operator
    | operator MODULO_UNSIGNED_LONG operator

  bit_operator
    : operator BIT_XOR operator
    | operator BIT_AND operator
    | operator BIT_OR operator
    | operator SHIFT operator

  comparison_operator
    : operator NUMEQ operator
    | operator NUMNE operator
    | operator NUMGT operator
    | operator NUMGE operator
    | operator NUMLT operator
    | operator NUMLE operator
    | operator NUMERIC_CMP operator
    | operator STREQ operator
    | operator STRNE operator
    | operator STRGT operator
    | operator STRGE operator
    | operator STRLT operator
    | operator STRLE operator
    | operator STRING_CMP operator

  string_concatenation
    : operator '.' operator

  logical_operator
    : operator LOGICAL_OR operator
    | operator LOGICAL_AND operator
    | LOGICAL_NOT operator

  type_check
    : operator ISA type
    | operator ISA_ERROR type
    | operator IS_TYPE type
    | operator IS_ERROR type
    | operator IS_COMPILE_TYPE type

  type_cast
    : '(' qualified_type ')' operator %prec CONVERT
    | operator ARROW '(' qualified_type ')' %prec CONVERT

  can
    : operator CAN method_name
    | operator CAN CONSTANT

  assign
    : operator ASSIGN operator
    | operator SPECIAL_ASSIGN operator

  new
    : NEW basic_type
    | NEW array_type_with_length
    | anon_method

  array_init
    : '[' opt_operators ']'
    | '{' operators '}'
    | '{' '}'

  call_method
    : CURRENT_CLASS SYMBOL_NAME '(' opt_operators  ')'
    | CURRENT_CLASS SYMBOL_NAME
    | basic_type ARROW method_name '(' opt_operators  ')'
    | basic_type ARROW method_name
    | operator ARROW method_name '(' opt_operators ')'
    | operator ARROW method_name
    | operator ARROW '(' opt_operators ')'

  element_access
    : operator ARROW '[' operator ']'
    | element_access '[' operator ']'
    | field_access '[' operator ']'

  field_access
    : operator ARROW '{' field_name '}'
    | field_access '{' field_name '}'
    | element_access '{' field_name '}'

  weaken_field
    : WEAKEN var ARROW '{' field_name '}'

  unweaken_field
    : UNWEAKEN var ARROW '{' field_name '}'

  isweak_field
    : ISWEAK var ARROW '{' field_name '}'

=head2 Syntax Parsing Token

These are the values of the tokens used in L</"Syntax Parsing Rule">.

=begin html

<table>
  <tr>
    <th>Tokens</td><th>Token Values</th>
  </tr>
  <tr>
    <td>ALIAS</td><td>alias</td>
  </tr>
  <tr>
    <td>ALLOW</td><td>allow</td>
  </tr>
  <tr>
    <td>ARROW</td><td>-></td>
  </tr>
  <tr>
    <td>AS</td><td>as</td>
  </tr>
  <tr>
    <td>ASSIGN</td><td>=</td>
  </tr>
  <tr>
    <td>BIT_AND</td><td>&</td>
  </tr>
  <tr>
    <td>BASIC_TYPE_ID</td><td>basic_type_id</td>
  </tr>
  <tr>
    <td>BIT_NOT</td><td>~</td>
  </tr>
  <tr>
    <td>BIT_OR</td><td>|</td>
  </tr>
  <tr>
    <td>BIT_XOR</td><td>^</td>
  </tr>
  <tr>
    <td>BREAK</td><td>break</td>
  </tr>
  <tr>
    <td>BYTE</td><td>byte</td>
  </tr>
  <tr>
    <td>CASE</td><td>case</td>
  </tr>
  <tr>
    <td>CLASS</td><td>class</td>
  </tr>
  <tr>
    <td>VAR_NAME</td><td>A variable name</td>
  </tr>
  <tr>
    <td>COMPILE_TYPE_NAME</td><td>compile_type_name</td>
  </tr>
  <tr>
    <td>CONSTANT</td><td>A literal</td>
  </tr>
  <tr>
    <td>CONVERT</td><td>(TYPE_NAME)</td>
  </tr>
  <tr>
    <td>COPY</td><td>copy</td>
  </tr>
  <tr>
    <td>CURRENT_CLASS</td><td>&</td>
  </tr>
  <tr>
    <td>CURRENT_CLASS_NAME</td><td>__PACKAGE__</td>
  </tr>
  <tr>
    <td>DEC</td><td>--</td>
  </tr>
  <tr>
    <td>DEFAULT</td><td>default</td>
  </tr>
  <tr>
    <td>DEREFERENCE</td><td>$</td>
  </tr>
  <tr>
    <td>ATTRIBUTE</td><td>An attribute name</td>
  </tr>
  <tr>
    <td>DIE</td><td>die</td>
  </tr>
  <tr>
    <td>DIVIDE</td><td>/</td>
  </tr>
  <tr>
    <td>DIVIDE_UNSIGNED_INT</td><td>div_uint</td>
  </tr>
  <tr>
    <td>DIVIDE_UNSIGNED_LONG</td><td>div_ulong</td>
  </tr>
  <tr>
    <td>DOUBLE</td><td>double</td>
  </tr>
  <tr>
    <td>DUMP</td><td>dump</td>
  </tr>
  <tr>
    <td>ELSE</td><td>else</td>
  </tr>
  <tr>
    <td>ELSIF</td><td>elsif</td>
  </tr>
  <tr>
    <td>END_OF_FILE</td><td>The end of the file</td>
  </tr>
  <tr>
    <td>ENUM</td><td>enum</td>
  </tr>
  <tr>
    <td>EVAL_ERROR_ID</td><td>eval_error_id</td>
  </tr>
  <tr>
    <td>EXTENDS</td><td>extends</td>
  </tr>
  <tr>
    <td>EVAL</td><td>eval</td>
  </tr>
  <tr>
    <td>EXCEPTION_VAR</td><td>$@</td>
  </tr>
  <tr>
    <td>FATCAMMA</td><td>=></td>
  </tr>
  <tr>
    <td>FLOAT</td><td>float</td>
  </tr>
  <tr>
    <td>FOR</td><td>for</td>
  </tr>
  <tr>
    <td>HAS</td><td>has</td>
  </tr>
  <tr>
    <td>CAN</td><td>can</td>
  </tr>
  <tr>
    <td>IF</td><td>if</td>
  </tr>
  <tr>
    <td>INTERFACE</td><td>interface</td>
  </tr>
  <tr>
    <td>INC</td><td>++</td>
  </tr>
  <tr>
    <td>INIT</td><td>INIT</td>
  </tr>
  <tr>
    <td>INT</td><td>int</td>
  </tr>
  <tr>
    <td>ISA</td><td>isa</td>
  </tr>
  <tr>
    <td>ISWEAK</td><td>isweak</td>
  </tr>
  <tr>
    <td>IS_TYPE</td><td>is_type</td>
  </tr>
  <tr>
    <td>IS_READ_ONLY</td><td>is_read_only</td>
  </tr>
  <tr>
    <td>LAST</td><td>last</td>
  </tr>
  <tr>
    <td>LENGTH</td><td>length</td>
  </tr>
  <tr>
    <td>LOGICAL_AND</td><td>&&</td>
  </tr>
  <tr>
    <td>LOGICAL_NOT</td><td>!</td>
  </tr>
  <tr>
    <td>LOGICAL_OR</td><td>||</td>
  </tr>
  <tr>
    <td>LONG</td><td>long</td>
  </tr>
  <tr>
    <td>MAKE_READ_ONLY</td><td>make_read_only</td>
  </tr>
  <tr>
    <td>METHOD</td><td>method</td>
  </tr>
  <tr>
    <td>MINUS</td><td>-</td>
  </tr>
  <tr>
    <td>MUTABLE</td><td>mutable</td>
  </tr>
  <tr>
    <td>MY</td><td>my</td>
  </tr>
  <tr>
    <td>SYMBOL_NAME</td><td>A symbol name</td>
  </tr>
  <tr>
    <td>NEW</td><td>new</td>
  </tr>
  <tr>
    <td>NEW_STRING_LEN</td><td>new_string_len</td>
  </tr>
  <tr>
    <td>OF</td><td>of</td>
  </tr>
  <tr>
    <td>NEXT</td><td>next</td>
  </tr>
  <tr>
    <td>NUMEQ</td><td>==</td>
  </tr>
  <tr>
    <td>NUMERIC_CMP</td><td>&lt;=&gt;</td>
  </tr>
  <tr>
    <td>NUMGE</td><td>&gt;=</td>
  </tr>
  <tr>
    <td>NUMGT</td><td>&gt;</td>
  </tr>
  <tr>
    <td>NUMLE</td><td>&lt;=</td>
  </tr>
  <tr>
    <td>NUMLT</td><td>&lt;</td>
  </tr>
  <tr>
    <td>NUMNE</td><td>!=</td>
  </tr>
  <tr>
    <td>OBJECT</td><td>object</td>
  </tr>
  <tr>
    <td>OUR</td><td>our</td>
  </tr>
  <tr>
    <td>PLUS</td><td>+</td>
  </tr>
  <tr>
    <td>PRINT</td><td>print</td>
  </tr>
  <tr>
    <td>REF</td><td>\</td>
  </tr>
  <tr>
    <td>TYPE_NAME</td><td>type_name</td>
  </tr>
  <tr>
    <td>MODULO</td><td>%</td>
  </tr>
  <tr>
    <td>MODULO_UNSIGNED_INT</td><td>mod_uint</td>
  </tr>
  <tr>
    <td>MODULO_UNSIGNED_LONG</td><td>mod_ulong</td>
  </tr>
  <tr>
    <td>REQUIRE</td><td>require</td>
  </tr>
  <tr>
    <td>RETURN</td><td>return</td>
  </tr>
  <tr>
    <td>RO</td><td>ro</td>
  </tr>
  <tr>
    <td>RW</td><td>rw</td>
  </tr>
  <tr>
    <td>SAY</td><td>say</td>
  </tr>
  <tr>
    <td>SCALAR</td><td>scalar</td>
  </tr>
  <tr>
    <td>SELF</td><td>self</td>
  </tr>
  <tr>
    <td>SHIFT</td><td>&lt;&lt;<br>&gt;&gt;<br>&gt;&gt;&gt;</td>
  </tr>
  <tr>
    <td>SHORT</td><td>short</td>
  </tr>
  <tr>
    <td>SPECIAL_ASSIGN</td><td>+=<br>-=<br>*=<br>/=<br>&=<br>|=<br>^=<br>%=<br>&lt;&lt;=<br>&gt;&gt;=<br>&gt;&gt;&gt;=<br>.=</td>
  </tr>
  <tr>
    <td>SRING_CMP</td><td>cmp</td>
  </tr>
  <tr>
    <td>STREQ</td><td>eq</td>
  </tr>
  <tr>
    <td>STRGE</td><td>ge</td>
  </tr>
  <tr>
    <td>STRGT</td><td>gt</td>
  </tr>
  <tr>
    <td>STRING</td><td>string</td>
  </tr>
  <tr>
    <td>STRLE</td><td>le</td>
  </tr>
  <tr>
    <td>STRLT</td><td>lt</td>
  </tr>
  <tr>
    <td>STRNE</td><td>ne</td>
  </tr>
  <tr>
    <td>SWITCH</td><td>switch</td>
  </tr>
  <tr>
    <td>UNDEF</td><td>undef</td>
  </tr>
  <tr>
    <td>UNLESS</td><td>unless</td>
  </tr>
  <tr>
    <td>UNWEAKEN</td><td>unweaken</td>
  </tr>
  <tr>
    <td>USE</td><td>use</td>
  </tr>
  <tr>
    <td>VAR</td><td>var</td>
  </tr>
  <tr>
    <td>VERSION</td><td>version</td>
  </tr>
  <tr>
    <td>VOID</td><td>void</td>
  </tr>
  <tr>
    <td>WARN</td><td>warn</td>
  </tr>
  <tr>
    <td>WEAKEN</td><td>weaken</td>
  </tr>
  <tr>
    <td>WHILE</td><td>while</td>
  </tr>
  <tr>
    <td>WO</td><td>wo</td>
  </tr>
</table>

=end html

=head2 Operator Precidence

The operator precidence in the SPVM language is described using L<GNU Bison|https://en.wikipedia.org/wiki/GNU_Bison> syntax.

The bottom is the highest precidence and the top is the lowest precidence.
  
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
  %right <opval> LOGICAL_NOT BIT_NOT '@' REFERENCE DEREFERENCE PLUS MINUS CONVERT SCALAR STRING_LENGTH ISWEAK TYPE_NAME COMPILE_TYPE_NAME DUMP NEW_STRING_LEN IS_READ_ONLY COPY
  %nonassoc <opval> INC DEC
  %left <opval> ARROW

The operator precidence can be increased using C<()>.

  #  a * b is calculated at first
  a * b + c
  
  # b + c is calculated at first
  a * (b + c)

=head1 See Also

=over 2

=item * L<SPVM::Document::Language::Tokenization>

=item * L<SPVM::Document::Language>

=item * L<SPVM::Document>

=back

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
