=encoding utf8

=head1 NAME

SPVM::Document::LanguageSpecification - SPVM Language Specification

=head1 DESCRIPTION

B<SPVM::Document::LanguageSpecification> describes SPVM language specification.

=head1 Tokenization

Describes the tokenizing of the SPVM language.

=head2 Character Set

SPVM language are written by UTF-8.

=head2 Line Terminators

Line terminators are C<LF>, C<CR>, and C<CRLF> of ASCII.

When a line terminator appears, the current line number is incremented. The line terminator is converted to C<LF> of ASCII .

=head2 Space Characters

Space characters are C<SP>, C<HT>, C<FF> of ASCII and L<"Line Terminators">.

Space characters have no meaning in programs.

=head2 Identifiers

Identifiers are L<"Class Names">, L<"Method Names">, L<"Field Names">, L<"Class Variable Names">, and L<"Local Variable Names">.

=head2 Class Names

A class names consists of one or more alphabet(C<a-zA-Z>), number(C<0-9>), underscore(C<_>) or C<::> of ASCII.

The part names of a class name must start uppercase letter. Part names means, for example, "Foo", "Bar", and "Baz" in the class name "Foo:Bar::Baz".

C<::> cannot be continued twice. The last character cannot end with C<::>.

Underscore C<_> cannot be continued twice.

A class name must be corresponding to the relative name of the module file. If the class name is "Foo::Bar::Baz", the relative name of the module file must be "Foo/Bar/Baz.spvm".

If class names are invalid, a compilation error occurs.

B<Examples of valid class names:>

  Foo
  Foo::Bar
  Foo::Bar::Baz3
  Foo::bar
  Foo_Bar::Baz_Baz

B<Examples of invalid class names:>

  Foo
  Foo::::Bar
  Foo::Bar::
  Foo__Bar
  Foo::bar

=head2 Method Names

A method name consists of one or more alphabet(C<a-zA-Z>), number(C<0-9>), or underscore(C<_>) of ASCII.

The first character must not a number.

Underscore(C<_>) cannot be continued twice.

If method names are invalid, a compilation error occurs.

B<Examples of valid method names:>

  # Valid method names
  FOO
  FOO_BAR3
  foo
  foo_bar
  _foo
  _foo_bar_

B<Examples of invalid method names:>
  
  # Invalid method names
  foo__bar
  3foo

A method name can be the same as L<"Keywords">.
  
  # "if" is a valid method name although this name is the same as the "if" keyword.
  static method if : void () {
    
  }

=head2 Field Names

A field name consists of one or more alphabet(C<a-zA-Z>), number(C<0-9>), or underscore(C<_>) of ASCII.

The first character must not number.
  
Underscore(C<_>) cannot be continued twice.

If field names are invalid, a compilation error occurs.

B<Examples of valid field names:>

  # Valid field names
  FOO
  FOO_BAR3
  foo
  foo_bar
  _foo
  _foo_bar_

B<Examples of invalid field names:>

  # Invalid field names
  foo__bar
  3foo

A field name can be the same as L<"Keywords">.
  
  # "if" is a valid field name although this name is the same as the "if" keyword.
  has if : int;

=head2 Class Variable Names

A class variable name starts with C<$>, followed alphabets(C<a-zA-Z>), numbers(C<0-9>), underscores(C<_>) or C<::> of ASCII.

The followed character must not start with a number.

C<::> cannot be continued twice. Last characters cannot end with C<::>.

Underscore(C<_>) cannot be continued twice.

If class variable names are invalid, a compilation error occurs.

B<Examples of valid class variable names:>

  # Valid class variable names
  $FOO::BAR
  $Foo::Bar3
  $FOO
  $FOO_BAR
  $foo

B<Examples of invalid class variable names:>
  
  # Invalid class variable names
  $FOO__BAR
  $3FOO

=head2 Local Variable Names

A local variable name starts with C<$>, followed alphabets(C<a-zA-Z>), numbers(C<0-9>), underscores(C<_>) of ASCII.

The followed character must not start with a number.

Underscore(C<_>) cannot be continued twice.

If local variable names are invalid, a compilation error occurs.

B<Examples of valid local variable names:>

  # Valid local variable names
  $foo
  $foo_bar3
  $_foo
  $FOO

B<Examples of invalid local variable names:>
  
  # Invalid local variable names
  $foo__bar
  $3foo

=head2 Keywords

The list of keywords.

  allow
  as
  break
  byte
  callback_t
  case
  cmp
  class
  copy
  default
  die
  divui
  divul
  double
  dump
  elsif
  else
  enum
  eq
  eval
  for
  float
  false
  gt
  ge
  has
  if
  isa
  isweak
  is_read_only
  implement
  int
  interface_t
  last
  length
  lt
  le
  long
  make_read_only
  my
  mulnum_t
  method
  mutable
  native
  ne
  next
  new
  new_string_len
  our
  object
  print
  private
  public
  precompile
  pointer_t
  ref
  refcnt
  remui
  remul
  return
  require
  rw
  ro
  static
  switch
  string
  short
  scalar
  true
  undef
  unless
  unweaken
  use
  void
  warn
  while
  weaken
  wo
  INIT
  __END__
  __CLASS__
  __FILE__
  __LINE__

=head2 Operators for Tokenization

The list of operators for tokenization.

  !
  !=
  $
  %
  &
  &&
  &=
  =
  ==
  ^
  ^=
  |
  ||
  |=
  -
  --
  -=
  ~
  @
  +
  ++
  +=
  *
  *=
  <
  <=
  >
  >=
  <=>
  %
  %=
  <<
  <<=
  >>=
  >>
  >>>
  >>>=
  .
  .=
  /
  /=
  \
  (
  )
  {
  }
  [
  ]
  ;
  :
  ,
  ->
  =>

Note that operators for tokenization include those that are not really operators, and do not include operators with names.

=head2 Comments

A comment begins with "#" and ends with L<"Line Terminators">.

  # Comment

Comments have no meaning in tokenization.

=head2 POD

POD(Plain Old Document) is a syntax to write documents easily.

POD starts from the line beginning with C<=>, followed by any string that consists of ASCII printable characters, and ending with L<"Line Terminators">.

POD ends from the line beginning with C<=cut>, and ending with L<"Line Terminators">.

B<POD Examples:>

  =pod

  Multi-Line
  Comment

  =cut

  =head1

  Multi-Line
  Comment

  =cut

POD has no meaning in tokenization.

=head2 Literals

Literals are representations of values in source codes. These are L<"Integer Literal">, L<"Floating Point Literal">, L<"Character Literal">, L<"String Literal"> and L<"Bool Literal">.

=head2 Integer Literal

=head3 Decimal Representation of Integer Literal

Decimal Representation of Integer Literal is represented by one or more consecutive characters from "0" to "9".

Can be prefixed with "+" or "-".

L<"Types"> of Integer Literal is L<"int Type"> by default.

If Integer Literal exceeds the range of numbers that can be represented by L<"int Type">, a compilation error occurs.

By suffixing "L" or "l" at the end, that represents L<"long Type"> Integer Literal.

If L<"long Type"> Integer Literal  exceeds the range of numbers that can be represented by L<"long Type">,  If it exceeds the range, a compilation error occurs.

"_" can be used as a separator. Separator has no meaning.

If Integer Literal is assigned to a L<"byte Type"> variable or passed to L<"byte Type"> Method Argument, and does not exceed the range of numbers that can be represented by L<"byte Type">, <a href = "#language-type-convertion-numeric-narrowing">Numeric Narrowing Type Conversion</a> is performed and the value converted to L<"byte Type"> value. If it exceeds the range, a compilation error will occur.

If Integer Literal is assigned to a L<"short Type"> variable or passed to L<"short Type"> Method Argument, and does not exceed the range of numbers that can be represented by L<"short Type">, <a href = "#language-type-convertion-numeric-narrowing">Numeric Narrowing Type Conversion</a> is performed and the value converted to L<"short Type"> value. If it exceeds the range, a compilation error will occur.

B<Integer Literal Example:>

  123
  +123
  -123
  123L
  123l
  123_456_789
  -123_456_789L

=head3 Hexadecimal Representation of Integer Literal

Hexadecimal Representation of Integer Literal is represented by the following rule.

Hexadecimal Representation of Integer Literal starts with "0x" or "0X".

It is followed by one or more consecutive characters "0" to "9", "a" to "f", or "A" to "F"..

Other rules are same as Decimal Representation of Integer Literal

B<Hexadecimal Representation of Integer Literal Example:>

  0x3b4f
  -0x3F1A
  0xDeL
  0xFFFFFFFF_FFFFFFFF

=head3 Octal Representation of Integer Literal

Octal Representation of Integer Literal is represented by the following rule.

Octal Representation of Integer Literal starts with "0".

It is followed by one or more consecutive characters "0" to "7".

Other rules are same as Decimal Representation of Integer Literal

B<Octal Representation of Integer Literal Example:>

  0755
  -0644
  0666L
  0655_755

=head3 Binary Representation of Integer Literal

Binary Representation of Integer Literal is represented by the following rule.

Binary Representation of Integer Literal starts with "0b" or "0B".

It is followed by one or more consecutive characters "0" or "1".

B<Binary Representation of Integer Literal Example:>

  0b0101
  -0b1010
  0b110000L
  0b10101010_10101010

=head2 Floating Point Literal

Floating Point Literal consists of B<Sign Part>, B<Numeric Part>, B<Exponent Part> and B<Suffix>.

  # Floating Point Literal
  [Sign Part][Numeric Part][Exponent Part][Suffix Part]

Floating Point Literal is B<Decimal Floating Point Literal> or B<Hexadecimal Floating Point Literal>.

B<Sign Part> is represented by "+" or "-". Sign Part is optional.

Numeric Part of Decimal Floating Point Literal starts one or more "0" to "9".

Numeric Part of Hexadecimal Floating Point Literal starts "0x" or "0X", and is followed by "0" to "9", "a" to "f", or "A" to "F".

For that the Literal is Floating Point Literal, Numeric Part contains "." or, The Literal have Exponent Part, or have Suffix Part.

Numeric part can contain "_". This is just a Numeric Separator and is ignored.

Hexadecimal Floating Point Literal needs Exponent Part.

B<Exponent Part> is consist of B<Exponential Notation> and B<Signed Decimal Integer>.

  # Exponent Part
  [Exponential Notation][Signed Decimal Integer]

Exponential Notation is "e" or "E" for Decimal Floating Point Literal, and "p" or "P" for Hexadecimal Floating Point Literal.

The meaning of Exponent Part is decimal shift for Decimal Floating Point Literal, or binary shift for Hexadecimal Floating Point Literal.

If Suffix Part is "f" or "F", the L<"Types"> of Floating Point Literal is L<"float Type">.

If Suffix Part is "d" or "D", the L<"Types"> of Floating Point Literal is L<"double Type">.

If Suffix Part is omitted, the L<"Types"> of Floating Point Literal is L<"double Type">.

If Floating Point Literal is L<"float Type">, the Floating Point Literal is converted to float value using C standard "strtof" function. If the conversion fails, a compilation error occurs.

If Floating Point Literal is L<"double Type">, the Floating Point Literal is converted to double value using C standard "strtod" function. If the conversion fails, a compilation error occurs.

B<Floating Point Literal Example:>

  1.32
  -1.32
  1.32f
  1.32F
  1.32e3
  1.32e-3
  1.32E+3
  1.32E-3
  0x3d3d.edp0
  0x3d3d.edp3
  0x3d3d.edP3
  0x3d3d.edP-3f

=head2 Charater Literal

B<Charater Literal> represents one character of ASCII.

Character Literal is enclosed in single quotes "'".

Content of Character Literal is one printable ASCII character or one Escape Character of Character Literal.

Charater Literal Type is "L<"byte Type">"

L<"Types"> of Charater Literal is L<"byte Type">.

=begin html

<table>
  <tr>
    <th>
      Escape Characters of Character Literal
   </th>
    <th>
      Description
   </th>
  </tr>
  <tr>
    <td>
      <b>\0</b>
    </td>
    <td>
      ASCII 0 NUL
    </td>
  </tr>
  <tr>
    <td>
      <b>\a</b>
    </td>
    <td>
      ASCII 7 BEL
    </td>
  </tr>
  <tr>
    <td>
      <b>\t</b>
    </td>
    <td>
      ASCII 9 HT
    </td>
  </tr>
  <tr>
    <td>
      <b>\n</b>
    </td>
    <td>
      ASCII 10 LF
    </td>
  </tr>
  <tr>
    <td>
      <b>\f</b>
    </td>
    <td>
      ASCII 12 "FF"
    </td>
  </tr>
  <tr>
    <td>
      <b>\r</b>
    </td>
    <td>
      ASCII 13 CR
    </td>
  </tr>
  <tr>
    <td>
      <b>\"</b>
    </td>
    <td>
      ASCII 34 "
    </td>
  </tr>
  <tr>
    <td>
      <b>\'</b>
    </td>
    <td>
      ASCII 39 '
    </td>
  </tr>
  <tr>
    <td>
      <b>\\</b>
    </td>
    <td>
      ASCII 92 \
    </td>
  </tr>
  <tr>
    <td>
      <b>\x + tow hexadecimal numbers</b>
    </td>
    <td>
      Specify ASCII by hexadecimal. Hexadecimal numbers are "0" to "9", "a" to "z", "A" to "Z".
    </td>
  </tr>
</table>

=end html

B<Charater Literal Example:>

B<Charater Literal> represents one character of ASCII.

  # Charater Literal 
  'a'
  'x'
  
  # Charater Literal using Escape Character
  '\a'
  '\t'
  '\n'
  '\f'
  '\r'
  '\"'
  '\''
  '\\'
  '\x0D'
  '\x0A'

=head2 String Literal

The string literal is a L<literal|"Literals"> to represents a string in source codes.

The return type is a L<string type|"string Type">.

A string literal is written by the characters of UTF-8.

The string Literal is enclosed in double quotes C<">.

B<Examples of string literals:>

  # String Literal
  my $message = "abc";
  my $message_utf8 = "あいう"

=head3 Escape charaters of String Literal

=begin html

<table>
  <tr>
    <th>
      Escape Character of String Literal
   </th>
    <th>
      Description
   </th>
  </tr>
  <tr>
    <td>
      <b>\0</b>
    </td>
    <td>
      ASCII 0 NUL
    </td>
  </tr>
  <tr>
    <td>
      <b>\a</b>
    </td>
    <td>
      ASCII 7 BEL
    </td>
  </tr>
  <tr>
    <td>
      <b>\t</b>
    </td>
    <td>
      ASCII 9 HT
    </td>
  </tr>
  <tr>
    <td>
      <b>\n</b>
    </td>
    <td>
      ASCII 10 LF
    </td>
  </tr>
  <tr>
    <td>
      <b>\f</b>
    </td>
    <td>
      ASCII 12 FF
    </td>
  </tr>
  <tr>
    <td>
      <b>\r</b>
    </td>
    <td>
      ASCII 13 CR
    </td>
  </tr>
  <tr>
    <td>
      <b>\"</b>
    </td>
    <td>
      ASCII 34 "
    </td>
  </tr>
  <tr>
    <td>
      <b>\'</b>
    </td>
    <td>
      ASCII 39 '
    </td>
  </tr>
  <tr>
    <td>
      <b>\\</b>
    </td>
    <td>
      ASCII 92 \
    </td>
  </tr>
  <tr>
    <td>
      <b>\x + two hexadecimal numbers</b>
    </td>
    <td>
      Specify ASCII by hexadecimal. Hexadecimal numbers are "0" to "9", "a" to "z", "A" to "Z". <br>For example, \x0D.
    </td>
  </tr>
  <tr>
    <td>
      <b>\N{U+} + hexadecimal numbers after U+</b>
    </td>
    <td>
      Specify the Unicode code point in hexadecimal. Hexadecimal numbers are expressed as "0" to "9", "a" to "f", "A" to "F".<br>For example, \N{U+3046}.<br>The code point is converted to UTF-8. 
    </td>
  </tr>
  <tr>
    <td>
      <b>Raw escape character<br>(For example, \s is become \s. This represents a sequence of two characters in a character literal '\\' 's')</b>
    </td>
    <td>
      \s \S \d \D \w \W \p \P \X \g \k \K \v \V \h \H \R \b \B \A \Z \z \G \N<br>
      \1 \2 \3 \4 \5 \6 \7 \8 \9 <br>
      \! \# \@ \% \& \( \) \* \+ \- \. \/ \: \; \< \= \> \? \[ \] \^ \_ \` \{ \| \} \~ \,
    </td>
  </tr>
</table>

=end html

If the espape characters that is not included avobe is used, a compiler error occurs.<br>

B<Examples of escape characters of string literals:>

  # Escape characters of string literals
  "abc\tdef\n"
  "\x0D\x0A"
  "\N{U+3042}\N{U+3044}\N{U+3046}"

=head2 Bool Literal

The bool literal is a L<literal|"Literals"> to represent a bool value in source codes.

=head3 true

C<true> is the alias for L<The TRUE method of the Bool module|SPVM::Bool/"TRUE">.

  true

B<Examples of true:>

  # true
  my $is_valid = true;

=head3 false

C<false> is the alias for L<The FALSE method of the Bool module|SPVM::Bool/"FALSE">.

  false

B<Examples of false:>

  # false
  my $is_valid = false;

=head2 Variable Expansion

B<Variable Expansion> applys L<"Local Variable">, L<"Class Variable">, L<"Dereference">, L<"Field Access">, L<"Array Access">, L<"Exception Variable"> in String Literal.

  "AAA $foo BBB"
  "AAA $FOO BBB"
  "AAA $$foo BBB"
  "AAA $foo->{x} BBB"
  "AAA $foo->[3] BBB"
  "AAA $foo->{x}[3] BBB"
  "AAA $@ BBB"

The above is expanded as the following.

  "AAA" . $foo . "BBB"
  "AAA" . $FOO . "BBB"
  "AAA" . $$foo . "BBB"
  "AAA" . $foo->{x} . "BBB"
  "AAA" . $foo->[3] . "BBB"
  "AAA" . $foo->{x}[3] . "BBB"
  "AAA" . $@ . "BBB"

The variable name can besurround with "{" and "}" to indicate the end of the variable name.

  "AAA ${foo}_ccc BBB"

The above is expanded as the following.

  "AAA " . ${foo} . "_ccc BBB"

If there is no enclosing "{" and "}", up to the valid part as a variable name is interpreted as a Variable. Dereference interpreting is same as this.

If "->" follows the variable name, it is interpreted as L<"Field Access"> or L<"Array Access">.

[1] If the following Characters are "a-z" "A-Z" "0-9" "_" "{" "[", proceed with the interpretation.

[2] If the Character following [1] is "}", or "]", then if the next Character is "->", "{", or "[", proceed with the interpretation and return back to [1], otherwise stop interpreting.

The trailing $is not treated as the start of Variable Expansion. It is treated as "$".

  "AAA$"

=head1 Syntax Parsing

The SPVM language is assumed to be parsed by yacc/bison.

=head2 The Definition of Syntax Parsing

Show the definition of syntax parsing that is written by yacc/bison. The definition of the precidence of operators is contained in this difinition.

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

  grammar
    : opt_classes

  opt_classes
    : /* Empty */
    | classes

  classes
    : classes class
    | class

  class
    : CLASS basic_type class_block END_OF_FILE
    | CLASS basic_type ':' opt_descriptors class_block END_OF_FILE
    | CLASS basic_type ';' END_OF_FILE
    | CLASS basic_type ':' opt_descriptors ';' END_OF_FILE

  class_block
    : '{' opt_declarations '}'

  opt_declarations
    : /* Empty */
    | declarations

  declarations
    : declarations declaration
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

  use
    : USE basic_type ';'
    | USE basic_type AS basic_type';'

  require
    : REQUIRE basic_type
    | REQUIRE basic_type AS basic_type';'

  allow
    : ALLOW basic_type ';'

  implement
    : IMPLEMENT basic_type ';'

  enumeration
    : opt_descriptors ENUM enumeration_block

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
    : OUR VAR_NAME ':' opt_descriptors qualified_type

  has
    : HAS field_name ':' opt_descriptors qualified_type ';'

  method
    : opt_descriptors METHOD method_name ':' qualified_type_or_void '(' opt_args opt_vaarg')' block
    | opt_descriptors METHOD method_name ':' qualified_type_or_void '(' opt_args opt_vaarg')' ';'
    | opt_descriptors METHOD ':' qualified_type_or_void '(' opt_args opt_vaarg')' block
    | opt_descriptors METHOD ':' qualified_type_or_void '(' opt_args opt_vaarg ')' ';'

  anon_method
    : opt_descriptors METHOD ':' qualified_type_or_void '(' opt_args opt_vaarg')' block
    | '[' args ']' opt_descriptors METHOD ':' qualified_type_or_void '(' opt_args opt_vaarg')' block

  opt_args
    : /* Empty */
    | args

  args
    : args ',' arg
    | args ','
    | arg

  arg
    : var ':' qualified_type

  opt_vaarg
    : /* Empty */
    | DOT3

  opt_descriptors
    : /* Empty */
    | descriptors

  descriptors
    : descriptors DESCRIPTOR
    | DESCRIPTOR

  opt_statements
    : /* Empty */
    | statements

  statements
    : statements statement
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
    | LAST ';'
    | NEXT ';'
    | BREAK ';'
    | RETURN ';'
    | RETURN expression ';'
    | DIE expression ';'
    | WARN expression ';'
    | PRINT expression ';'
    | weaken_field ';'
    | unweaken_field ';'
    | ';'
    | MAKE_READ_ONLY expression ';'

  for_statement
    : FOR '(' opt_expression ';' expression_or_logical_op ';' opt_expression ')' block

  while_statement
    : WHILE '(' expression_or_logical_op ')' block

  switch_statement
    : SWITCH '(' expression ')' switch_block

  switch_block
    : '{' case_statements '}'
    | '{' case_statements default_statement '}'

  case_statements
    : case_statements case_statement
    | case_statement

  case_statement
    : CASE expression ':' block
    | CASE expression ':'

  default_statement
    : DEFAULT ':' block
    | DEFAULT ':'

  if_require_statement
    : IF '(' require ')' block
    | IF '(' require ')' block ELSE block

  if_statement
    : IF '(' expression_or_logical_op ')' block else_statement
    | UNLESS '(' expression_or_logical_op ')' block else_statement

  else_statement
    : /* NULL */
    | ELSE block
    | ELSIF '(' expression_or_logical_op ')' block else_statement

  block
    : '{' opt_statements '}'

  eval_block
    : EVAL block ';'

  opt_expressions
    : /* Empty */
    | expressions

  opt_expression
    : /* Empty */
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
    | CURRENT_CLASS_NAME
    | isweak_field
    | comparison_op
    | isa
    | TRUE
    | FALSE

  expressions
    : expressions ',' expression
    | expressions ','
    | expression

  unary_op
    : '+' expression %prec PLUS
    | '-' expression %prec MINUS
    | BIT_NOT expression
    | REFCNT var
    | REFOP expression
    | STRING_LENGTH expression
    | DUMP expression
    | DEREF var
    | CREATE_REF var
    | NEW_STRING_LEN expression
    | IS_READ_ONLY expression
    | COPY expression

  inc
    : INC expression
    | expression INC

  dec
    : DEC expression
    | expression DEC

  binary_op
    : expression '+' expression
    | expression '-' expression
    | expression '*' expression
    | expression DIVIDE expression
    | expression DIVIDE_UNSIGNED_INT expression
    | expression DIVIDE_UNSIGNED_LONG expression
    | expression REMAINDER expression
    | expression REMAINDER_UNSIGNED_INT expression
    | expression REMAINDER_UNSIGNED_LONG expression
    | expression BIT_XOR expression
    | expression BIT_AND expression
    | expression BIT_OR expression
    | expression SHIFT expression
    | expression '.' expression

  comparison_op
    : expression NUMEQ expression
    | expression NUMNE expression
    | expression NUMGT expression
    | expression NUMGE expression
    | expression NUMLT expression
    | expression NUMLE expression
    | expression NUMERIC_CMP expression
    | expression STREQ expression
    | expression STRNE expression
    | expression STRGT expression
    | expression STRGE expression
    | expression STRLT expression
    | expression STRLE expression
    | expression STRING_CMP expression

  isa
    : expression ISA type

  logical_op
    : expression_or_logical_op LOGICAL_OR expression_or_logical_op
    | expression_or_logical_op LOGICAL_AND expression_or_logical_op
    | LOGICAL_NOT expression_or_logical_op
    | '(' logical_op ')'

  assign
    : expression ASSIGN expression
    | expression SPECIAL_ASSIGN expression

  new
    : NEW basic_type
    | NEW array_type_with_length
    | anon_method

  array_init
    : '[' opt_expressions ']'
    | '{' expressions '}'
    | '{' '}'

  convert
    : '(' qualified_type ')' expression %prec CONVERT

  array_access
    : expression ARROW '[' expression ']'
    | array_access '[' expression ']'
    | field_access '[' expression ']'

  call_spvm_method
    : CURRENT_CLASS NAME '(' opt_expressions  ')'
    | CURRENT_CLASS NAME
    | basic_type ARROW method_name '(' opt_expressions  ')'
    | basic_type ARROW method_name
    | expression ARROW method_name '(' opt_expressions ')'
    | expression ARROW method_name
    | expression ARROW '(' opt_expressions ')'

  field_access
    : expression ARROW '{' field_name '}'
    | field_access '{' field_name '}'
    | array_access '{' field_name '}'

  weaken_field
    : WEAKEN var ARROW '{' field_name '}'

  unweaken_field
    : UNWEAKEN var ARROW '{' field_name '}'

  isweak_field
    : ISWEAK var ARROW '{' field_name '}'

  array_length
    : '@' expression
    | '@' '{' expression '}'
    | SCALAR '@' expression
    | SCALAR '@' '{' expression '}'

  my_var
    : MY var ':' qualified_type
    | MY var

  var
    : VAR_NAME

  qualified_type
    : type
    | MUTABLE type {

  type
    : basic_type
    | array_type
    | ref_type

  basic_type
    : NAME
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
    : basic_type '[' expression ']'
    | array_type '[' expression ']'

  qualified_type_or_void
    : qualified_type
    | VOID

  field_name
    : NAME

  method_name
    : NAME
  
The following is a correspondence table between tokens in yacc/bison and keywords and operators in SPVM.

=begin html

<table>
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
    <td>CLASS_VAR_NAME</td><td>A class variable name</td>
  </tr>
  <tr>
    <td>CONSTANT</td><td>Literal</td>
  </tr>
  <tr>
    <td>CONVERT</td><td>(TypeName)</td>
  </tr>
  <tr>
    <td>COPY</td><td>copy</td>
  </tr>
  <tr>
    <td>CURRENT_CLASS</td><td>&</td>
  </tr>
  <tr>
    <td>CURRENT_CLASS_NAME</td><td>__CLASS__</td>
  </tr>
  <tr>
    <td>DEC</td><td>--</td>
  </tr>
  <tr>
    <td>DEFAULT</td><td>default</td>
  </tr>
  <tr>
    <td>DEREF</td><td>$</td>
  </tr>
  <tr>
    <td>DESCRIPTOR</td><td>The name of a descriptor</td>
  </tr>
  <tr>
    <td>DIE</td><td>die</td>
  </tr>
  <tr>
    <td>DIVIDE</td><td>/</td>
  </tr>
  <tr>
    <td>DIVIDE_UNSIGNED_INT</td><td>divui</td>
  </tr>
  <tr>
    <td>DIVIDE_UNSIGNED_LONG</td><td>divul</td>
  </tr>
  <tr>
    <td>DOT3</td><td>...</td>
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
    <td>IF</td><td>if</td>
  </tr>
  <tr>
    <td>IMPLEMENT</td><td>implement</td>
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
    <td>NAME</td><td>name</td>
  </tr>
  <tr>
    <td>NEW</td><td>new</td>
  </tr>
  <tr>
    <td>NEW_STRING_LEN</td><td>new_string_len</td>
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
    <td>REFCNT</td><td>refcnt</td>
  </tr>
  <tr>
    <td>REFOP</td><td>ref</td>
  </tr>
  <tr>
    <td>REMAINDER</td><td>%</td>
  </tr>
  <tr>
    <td>REMAINDER_UNSIGNED_INT</td><td>remui</td>
  </tr>
  <tr>
    <td>REMAINDER_UNSIGNED_LONG</td><td>remul</td>
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
    <td>SCALAR</td><td>scalar</td>
  </tr>
  <tr>
    <td>SELF</td><td>self</td>
  </tr>
  <tr>
    <td>SHIFT</td><td>&lt;&lt;  &gt;&gt;  &gt;&gt;&gt;</td>
  </tr>
  <tr>
    <td>SHORT</td><td>short</td>
  </tr>
  <tr>
    <td>SPECIAL_ASSIGN</td><td>+=  -=  *=  /=  &=  |=  ^=  %=  &lt;&lt;=  &gt;&gt;=  &gt;&gt;&gt;= .=</td>
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

=head1 Class

=head2 Class Definition

B<Class Definition> is the following syntax.

  class PACAKGE_NAME {
  
  }

PACAKGE_NAME must follow the rule for L<"Class Names">.

L<"Class Descriptors"> can be specified by the following syntax.

  class PACAKGE_NAME : PACAKGE_DESCRIPTOR {
  
  }
  
  class PACAKGE_NAME : PACAKGE_DESCRIPTOR1 PACAKGE_DESCRIPTOR2 PACAKGE_DESCRIPTORN {
  
  }

B<Class Definition Example:>

  # Class names
  class Point {
  
  }

  # Class names and class descriptors
  class Point : public {
  
  }

In direct children of the class block, L<"use">, L<"our">, L<"has">, L<"enum">, L<"sub"> can be defined.

  class Foo {
    # use
    use Point;
  
    # Class Variable Definition
    our $VAR int;
  
    # Field Defintion
    has var : int;
  
    # Enumeration Definition
    enum {
      CONST_VAL1,
      CONST_VAL2,
    }
  
    # Method Definition
    static method foo : int ($num : int) {
  
    }
  }

If more than one class with the same name is defined, a compilation error occurs.

=head2 Class Descriptors

The list of class descriptors.

=begin html

<table>
  <tr>
    <th>
      Descriptor
   </th>
    <th>
      Meaning
   </th>
  </tr>
  <tr>
    <td>
      <b>public</b>
    </td>
    <td>
      This class is public. Other classes can L<"new"> this class.
    </td>
  </tr>
  <tr>
    <td>
      <b>private</b>
    </td>
    <td>
      This class is private. Other classes can't L<"new"> this class. This is default setting.
    </td>
  </tr>
  <tr>
    <td>
      <b>callback_t</b>
    </td>
    <td>
      This class is L<"Callback Type">.
    </td>
  </tr>
  <tr>
    <td>
      <b>mulnum_t</b>
    </td>
    <td>
      This class is L<"Multi Numeric Types">.
    </td>
  </tr>
  <tr>
    <td>
      <b>pointer_t</b>
    </td>
    <td>
      This class is L<"Pointer Type">.
    </td>
  </tr>
  <tr>
    <td>
      <b>precompile</b>
    </td>
    <td>
      Do precompile all methods in this class, except for accessor, and enum. 
    </td>
  </tr>
</table>

=end html

If both "public" and "private" are specifed, a compilation error occurs.

If more than one of "callback_t", "mulnum_t", "pointer_t" are specified, a compilation error occurs.

=head2 Destructor

If the class is L<"Class Type">, the class defined a destructor.

Destructor is a special L<"Method"> called when the object of this class is freed.

Destructor name must be "DESTROY".

Destructor Retrun Value must be L<"void Type">, otherwise a compilation error occurs.

Destructor arguments must be one and the type must be L<"self Type">, otherwise a compilation error occurs.

  method DESTROY : void () {
  
  }

If a L<"Exception"> occurs in Destructor, the program don't exit, print the message of the exception to STDERR.

B<Destructor Example:>

  class Foo {
    static method new : Foo {
      return new Foo;
    }
  
    method DESTROY : void () {
      print "DESTROY";
    }
  }

=head2 Allow Class Access

By default, private Methods, Fields, and Class Variables cannot be accessed from outside the Class.

Also, Private Class cannot L<"Create Object"> from outside of Class.

If the class allow other class, the other class can access private Methods, Fields, and Class Variables, and can L<"Create Object"> of the class.

  allow CLASS_NAME;

allow must be defined directory under L<"Class Definition">.

  class Foo {
    allow Bar;
  }

In this example, Bar can access the private Method, Field, and Class Variable of Foo can be accessed and can Create Object of Foo.

Specifying the module of B<allow> also loads the module by L<"use"> at the same time.

=head1 Module

=head2 Module Summary

Module is a single file that can be read as SPVM source code.

  # lib/path/SPVM/Foo/Bar.spvm
  class Foo::Bar {
  
  }

Module can contain multiple Classes.

  # lib/path/SPVM/Foo/Bar.spvm
  class Foo::Bar {
  
  }
  
  class Foo::Bar::Baz {
  
  }

=head2 Module File Name

Modules must be placed in the module loading path with the following File Name.

Change "::" to "/". Add ".spvm" at the end.

  SPVM/Foo.spvm
  SPVM/Foo/Bar.spvm
  SPVM/Foo/Bar/Baz.spvm

=head2 Load Module

Use B<use> keyword to load a Module.

  use Foo;
  use Foo::Bar;

Modules are loaded at compile-time.

If the Module does not exist, a compilation error will occur.

use Keyword must be defined directly under L<"Class Definition">.

  class Foo {
    use Foo;
  }

=head2 Class Alias

Define class aliases using B<as> syntax with B<use>

  use Foo::Bar as FB;

FB is used as Foo::Bar alias in class method calls.

  # This means Foo::Bar->sum(1, 2);
  FB->sum(1, 2);

=head2 Automatically Loaded Module

The followings are Automatically Loaded Modules. They can be used without L<"use">.

=begin html

<ul>
  <li>Byte</li>
  <li>Short</li>
  <li>Int</li>
  <li>Long</li>
  <li>Float</li>
  <li>Double</li>
</ul>

=end html

=head2 Load Module Selective

In SPVM, there is an if require Statement that loads a Module only if it exists in the module path, and if it does not exist, the block does not exist.

It was designed to implement a part of features of "#ifdef" in C language.

  if (require Foo) {
  
  }

if require Statement can be followed by else Statement. 

  if (require Foo) {
  
  }
  else {
  
  }

Note that elsif Statement cannot be followed.

Let's look at an example. if Foo does not exist, no a compilation error occurs and it is assumed that there is no if block

Therefore, "$foo = new Foo;" does not result in a compilation error because it is assumed that there is no if block.

In the other hand, the else block exists, so a warning is issued.

  my $foo : object;
  if (require Foo) {
    $foo = new Foo;
  }
  else {
    warn "Warning: Can't load Foo";
  }

=head1 Class Variable

=head2 Class Variable Definition

B<Class Variable> is a global variable that belongs to L<"Class"> and exists from the start to the end of the program execution.

"our" Keyword defines a Class Variable.

  our CLASS_VARIABLE_NAME : TYPE;

Class Variable must be defined directly under L<"Class Definition">.

Class Variable Definition must specify L<"Types">. The Type must be L<"Numeric Types"> or L<"Object Types">.

Class variable mames must follows the rule specified in L<"Class Variable Names">, and must not contain "::", otherwise a compilation error occurs.

If more than one Class Variable with the same name is defined, a compilation error occurs.

Class Variable Descriptor can be specified together in Class Variable definition.

  our CLASS_VARIABLE_NAME : DESCRIPTOR TYPE;
  our CLASS_VARIABLE_NAME : DESCRIPTOR1 DESCRIPTOR2 DESCRIPTORN TYPE;

=head2 Class Variable Descriptor

List of Class Variable Descriptors.

=begin html

<table>
  <tr>
    <th>
      Descriptor
   </th>
    <th>
      Description
   </th>
  </tr>
  <tr>
    <td>
      <b>public</b>
    </td>
    <td>
      This Class Variable is public. This Class Variable can be accessed from other class.
    </td>
  </tr>
  <tr>
    <td>
      <b>private</b>
    </td>
    <td>
      This Class Variable is private. This Class Variable can't be accessed from other class. This is default setting of Class Variable.
    </td>
  </tr>
  <tr>
    <td>
      <b>ro</b>
    </td>
    <td>
      This Class Variable has Read Accessor. Read Accessor name is the same as class variable names except removing "$". For example, If the class variable names is "$FOO", Read Accessor name is "FOO".
    </td>
  </tr>
  <tr>
    <td>
      <b>wo</b>
    </td>
    <td>
      This Class Variable has Write Accessor. Write Accessor name is the same as class variable names except removing "$" and adding "SET_" to top. For example, If the class variable names is "$FOO", Read Accessor name is "SET_FOO".
    </td>
  </tr>
  <tr>
    <td>
      <b>rw</b>
    </td>
    <td>
      This Class Variable has Read accessor and Write Accessor.
    </td>
  </tr>
</table>

=end html

If both "public" and "private" Descriptors are specified, a compilation error occurs.

If more than one of "ro", "wo", and "rw" are specified at the same time, a compilation error occurs

Read Accessor of Class Variable has no arguments and the return type is same as the type of Class Variable.

Write Acessor of Class Variable has one argument and the type is same as the type of Class Variable. The type of return value is L<"void Type">.

Inline Expansion optimization is performed to Read Accessor and Write Accessor. You don't have to worry about the performance penalty of using Class Variable Accessors.

B<Class Variable Definition Example:>

  class Foo {
    our $NUM1 : byte;
    our $NUM2 : short;
    our $NUM3 : int;
    our $NUM4 : long;
    our $NUM5 : float;
    our $NUM6 : double;
  
    our $NUM_PUBLIC : public int;
    our $NUM_RO : ro int;
    our $NUM_WO : wo int;
    our $NUM_RW : rw int;
  }

=head2 Class Variable Initial Value

Class Variable is initialized with L<"Type Initial Value"> after compilation and before execution.

This initial value can be changed by using L<"INIT Block">.

  class Foo {
    our $VAR : int;
  
    INIT {
      $VAR = 3;
    }
  }

=head2 Class Variable Access

Class Variable Access is an operation to access Class Variable to get or set a value.

See L<"Get Class Variable"> for how to get the value of Class Variable.

See L<"Set Class Variable"> for the setting of the value of Class Variable.

=head1 Field

=head2 Field Definition

Field is a data area in a L<"object created using new keyword">

"has" Keyword defines a Field.

  has FIELD_NAME : TYPE;

Field must be defined directly under L<"Class Definition">.

Field Definition must be specify L<"Types">. The Type must be L<"Numeric Types"> or L<"Object Types">.

Field names must follows the rule specified in L<"Field Names">.

Field Type must be L<"Numeric Types"> or L<"Object Types">, otherwise a compilation error occurs.

If more than one field names Variable with the same name is defined, a compilation error occurs.

Field Descriptor can be specified together in Field Definition.

  has FIELD_NAME : DESCRIPTOR TYPE_NAME;
  has FIELD_NAME : DESCRIPTOR1 DESCRIPTOR2 DESCRIPTORN TYPE_NAME;

=head2 Field Descriptor

List of Field Descriptors.

=begin html

<table>
  <tr>
    <th>
      Descriptor
   </th>
    <th>
      Description
   </th>
  </tr>
  <tr>
    <td>
      <b>public</b>
    </td>
    <td>
      This field is public. This field can be accessed from other class.
    </td>
  </tr>
  <tr>
    <td>
      <b>private</b>
    </td>
    <td>
      This field is private. This field can't be accessed from other class. This is default setting.
    </td>
  </tr>
  <tr>
    <td>
      <b>ro</b>
    </td>
    <td>
      This Field has Read Accessor. Read Accessor name is the same as field mames. For example, If the field names is "foo", Read Accessor name is "foo".
    </td>
  </tr>
  <tr>
    <td>
      <b>wo</b>
    </td>
    <td>
      This Field has Write Accessor. Write Accessor name is the same as field names adding "set_" to top. For example, If the field names is "foo", Read Accessor name is "set_foo".
    </td>
  </tr>
  <tr>
    <td>
      <b>rw</b>
    </td>
    <td>
      This Field has Read Accessor and Write Accessor.
    </td>
  </tr>
</table>

=end html

If both "public" and "private" Descriptors are specified, a compilation error occurs.

If more than one of "ro", "wo", and "rw" are specified at the same time, a compilation error occurs

Read Accessor of Field has one argument that is L<"self Type"> and the return type is same as the type of Field.

Write Acessor of Class Variable has two arguments. First argument is L<"self Type"> and second argument is same as the type of Field. The type of return value is L<"void Type">.

Inline Expansion optimization is performed to Read Accessor and Write Accessor. You don't have to worry about the performance penalty of using Field Accessors.

B<Field Definition Example:>

  class Foo {
    has num1 : byte;
    has num2 : short;
    has num3 : int;
    has num4 : long;
    has num5 : float;
    has num6 : double;
  
    has num_public : public int;
    has num_ro : ro int;
    has num_wo : wo int;
    has num_rw : rw int;
  }

=head2 Field Access

Field Access is an operation to access Field to get or set a value.

  EXPRESSION->{FIELD_NAME}

Field Access has three different meanings.

B<1. Class Based Object Field Access>

Class Based Object Field Access is Field Access from object which is create by L<"new"> keyword.

  my $point = new Point;
  $point->{x} = 1;

See L<"Get Field"> to get field of Class Based Object.

See L<"Set Field"> to set field of Class Based Object.

B<2. Multi Numeric Field Access>

Multi Numeric Field Access is Field Access from the value of L<"Multi Numeric Types">. The value of L<"Multi Numeric Types"> is allocated Callstack of Method.

  my $z : Complex_2d;
  $z->{x} = 1;
  $z->{y} = 3;

See L<"Get Multi Numeric Field Value"> to get field of the value of L<"Multi Numeric Types">.

See L<"Set Multi Numeric Field Value"> to set field of the value of L<"Multi Numeric Types">.

B<3. Dereference Multi Numeric Field>

Dereference Multi Numeric Field is Field access from Reference of the value of L<"Multi Numeric Types">.

  my $z : Complex_2d;
  my $z_ref = \$z;
  $z_ref->{x} = 1;
  $z_ref->{y} = 3;

See L<"Get Multi Numeric Field Value via Dereference"> to get Multi Numeric Field via Dereference.

See L<"Set Multi Numeric Field Value via Dereference"> to set Multi Numeric Field via Dereference.

=head1 Method

=head2 Method Definition

"sub" Keyword defines Method.

  static method METHOD_NAME : RETURN_VALUE_TYPE_NAME () {
  
  }
  static method METHOD_NAME : RETURN_VALUE_TYPE_NAME (ARGUMENT_NAME1 : ARGUMENT_TYPE_NAME1, ARGUMENT_NAME2 : ARGUMENT_TYPE_NAME2, ARGUMENT_NAMEN : ARGUMENT_TYPE_NAMEN) {
  
  }

Method must be defined directly under L<"Class Definition">.

Method name must be follow the rule of L<"Method Names">.

Method names are allowed as same as L<"Keyword">. 

Type of Return Value must be L<"void Type">, L<"Numeric Types">, or L<"Object Types">, otherwise a compilation error occurs.

Argument name must be follow the rule of L<"Local Variable Names">.

Minimal Argument Count is 0. Max Argument Count is 255.

Type of Argument must be L<"Numeric Types">, L<"Object Types">, or L<"Reference Type">, otherwise a compilation error occurs.

The defined Method can be called. See L<"Method Call"> about calling Method, .

L<"Method Block"> can have zero or more Statements.

Method Definition can have L<"Method Descriptor">.

  DESCRIPTOR1 DESCRIPTOR2 DESCRIPTORN static method METHOD_NAME : RETURN_VALUE_TYPE_NAME () {
  
  }
  DESCRIPTOR1 DESCRIPTOR2 DESCRIPTORN static method METHOD_NAME : RETURN_VALUE_TYPE_NAME (ARGUMENT_NAME1 : ARGUMENT_TYPE_NAME1, ARGUMENT_NAME2 : ARGUMENT_TYPE_NAME2, ARGUMENT_NAMEN : ARGUMENT_TYPE_NAMEN) {
  
  }

If "..." follows Type of Argument, the Argument becomes Variable Length Argument. Only the last Argument can be Variable Length Argument.

The Type must be L<"Array Type">.

  static method METHOD_NAME : RETURN_VALUE_TYPE_NAME (ARGUMENT_NAME1 : ARGUMENT_TYPE_NAME1, ARGUMENT_NAME2 : ARGUMENT_TYPE_NAME2...) {
  
  }

Variable Length Argument can recieve multi values.

  # Variable Length Argument Definition
  static method sprintf : string ($format : string, $values : object[]...) {
  
  }
  
  # Call Variable Length Argument Method with multi values.
  sprintf("Value %d %f", 1, 2.0);

Variable Length Argument can recieve Array.

  # Call Variable Length Argument Method with Array.
  sprintf("Value  %d %f", [(object)1, 2.0]);

If you want to treat the value of Array as an individual element of the variable length argument, cast it to Type other than Array Type.

  sprintf("aaa %p", (object)[(object)1, 2.0]);

=head2 Method Descriptor

List of Method Descriptor.

=begin html

<table>
  <tr>
    <th>
      Descriptor
   </th>
    <th>
      Description
   </th>
  </tr>
  <tr>
    <td>
      <b>native</b>
    </td>
    <td>
      This Method is L<"Native Method">. 
    </td>
  </tr>
</table>

=end html

=head2 Native Method

Native Method is Method that call function written in Native Language(C, C++, etc).

See <a href="/native-api.html">SPVM Native API</a> Native Method.

=head2 Precompiled Method

If the Class has "precompile" descriptor, the methods of the class become Precompiled Method.

Precompiled Method is translated into C source code and converted into machine code.

The precompiled methods are C code, so you can get performance of C language.

Precompiled Method needs Build Directory described in <a href="/native-api.html">SPVM Native API</a>

=head2 Constant Method

Constant Method is a Method that the return type is L<"Numeric Types"> and returns Constant Value.

  static method foo : int () { return 5; }
  static method foo : long () { return 5L; }
  static method foo : float () { return 5.0f; }
  static method foo : double () { return 5.0; }

Inline Expansion optimization is performed to Constant Method.

Note that SPVM does not perform constant convolution optimization, so if a constant is calculated, it will not performe Inline Expansion.

  # This is not Constant Method.  Inline Expansion is not performed
  static method foo : int () { return 5 + 3; }

=head2 Method

Method is Method that has L<"self Type"> as its first argument.

  method METHOD_NAME : TYPE  (ARGUMENT2 : TYPE2, ARGUMENT3 : TYPE3, ARGUMENTN : TYPEn) {
  
  }

L<"self Type"> must be first argument.

Method can be called from the object created by L<"new">. See L<"Method Call"> for Method Call.

$self is called Invocant.

=head2 Signature

Signature is a string that follow the following rule sequence of Method Retrun Value and arguments arranged according to the following rules. Arguments do not need to exist. There cannot be spaces between them.

1. RETURN_VALUE_TYPE

2. (

3. ARGUMENT_TYPE1,ARGUMENT_TYPE2,ARGUMENT_TYPE3

4. )

It the method is a instance method, the part of signature of the first argument is "self".

B<Signature Example:>

  # Method Definition
  static method foo : int ($num1 : double, $num2 : long[])
  
  # Signature
  int(double,long[])
  
  # Method Definition
  static method foo : void ()
  
  # Signature
  void()
  
  
  # Method Definition
  method foo : int ($num1 : double, $num2 : long[])
  
  # Signature
  int(self,double,long[])

Signature is not used in SPVM programs. Signature is used when calling the SPVM Method from <a href="/native-api.html">SPVM Native API</a>.

=head2 Method Callstack

Method Callstack is memory area allocated in each method call.

Method Callstack save the folloing information.

1. Memroy area for L<"Local Variable">

2. The places of Mortal Local Variable

=head1 Enumeration

=head2 Enumeration Definition

Enumeration Definition is a syntax to define multiple L<"Constant Methods"> easily.

  # Enumeration Definition
  enum {
    FLAG1,
    FLAG2,
    FLAG3
  }

Enumeration must be defined directly under L<"Class Definition">.

  class Foo {
    enum {
      FLAG1,
      FLAG2,
      FLAG3
    }
  }

The first value starts with "0". The value is incremented by "1". In this example, "FLAG1" is "0", "FALG2" is "1", and "FLAG3" is "2".

"," can be added after the last element of Enumeration.

  enum {
    FLAG1,
    FLAG2,
    FLAG3,
  }

Enumeration is an alias for L<"Constant Method"> that the return type is L<"int Type">. It is equivalent to the following Method Definition:

  static method FLAG1 : int () { return 0; }
  static method FLAG2 : int () { return 1; }
  static method FLAG3 : int () { return 2; }

The value of L<"int Type"> can be set in the enum element.

  enum {
    FLAG1,
    FLAG2 = 4,
    FLAG3,
  }

In the above case, "FLAG1" is "0", "FALG2" is "4", and "FLAG3" is "5".

If Enum Definition is invalid, a compilation error occurs.

=head2 Enumeration Descriptor

Descriptor can be specified for Enumeration.

  private enum {
    FLAG1,
    FLAG2 = 4,
    FLAG3,
  }

List of Enumeration Descriptor

=begin html

<table>
  <tr>
    <th>
      Descriptor
   </th>
    <th>
      Description
   </th>
  </tr>
  <tr>
    <td>
      <b>public</b>
    </td>
    <td>
      This Enumeration is public. This Enumeration can be accessed from other Class. This is default setting.
    </td>
  </tr>
  <tr>
    <td>
      <b>private</b>
    </td>
    <td>
      This Enumeration is private. This Enumeration can not be accessed from other Class.
    </td>
  </tr>
</table>

=end html

If both "public" and "private" Descriptors are specified, a compilation error occurs.

=head2 Enumeration Call

Enumeration is an alias for L<"Constant Method">, so it can be called in exactly the same way as Method call.

  my $flag1 = Foo->FLAG1;
  my $flag2 = Foo->FLAG2;
  my $flag3 = Foo->FLAG3;

In special case, Enumeration Call can be used in L<"case Statement"> of L<"switch Statement">.

  switch ($num) {
    case Foo->FLAG1: {
  
      break;
    }
    case Foo->FLAG2: {
  
      break:
    }
    case Foo->FLAG3: {
  
      break:
    }
    default: {
  
    }
  }

=head1 INIT Block

B<INIT Block> is a block that is executed immediately after the compilation of program.

INIT Keyword defines INIT Block.

  INIT {
  
  }

INIT Block must be defined directly under L<"Class Definition">.

  class Foo {
    INIT {
  
    }
  }

Zero or more L<"Statements"> can be written in INIT Block.

  INIT {
    my $foo = 1 + 1;
    my $bar;
  }

L<"return Statement"> cannot be written in INIT Block.

Internally, INIT Block is a L<"Method"> that the return type is L<"void Type"> and has no arguments.

You can define multiple INIT Blocks.

The execution order of INIT Block is not guaranteed. If ohter INIT Block is defined in ohter Class, do not assume that INIT Block of the current class will be executed first.

A common use of INIT Block is to initialize L<"Class Variable">.

  class Foo {
    use Point;
    
    our $NUM : int;
    our $POINT : Point;
    INIT {
      $NUM = 3;
      $POINT = Point->new;
    }
  }

=head1 Local Variable

=head2 Local Variable Declaration

B<Local Variable> is a variable that is declared in L<"Scope Blocks">.  Local Variable has L<"Scope">. This is same as Local Variable in C Language.

Local Variable is declared using B<my> L<"Keyword">.

  my LOCAL_VARIABLE_NAME : TYPE;

The local variable name must be follow the rule of L<"Local Variable Names">.

L<"Types"> must be specified. Type must be L<"Numeric Types">, L<"Object Types">, L<"Multi Numeric Types">, or L<"Reference Type">.

  # Local Variable Declaration Examples
  my $var : int;
  my $var : Point;
  my $var : Complex_2d;
  my $var : int*;

Local Variable is initialized by L<"Local Variable Initial Value">.

  # Initialized by 0
  my $num : int;
  
  # Initialized by 0
  my $num : double;
  
  # Initialized by undef
  my $point : Point;
  
  # x is initialized by 0. y is initialized by 0.
  my $z : Complex_2d;

Initialization can be done at the same time as Local Variable Declaration.

  # Initialized by 1
  my $num : int = 1;
  
  # Initialized by 2.5
  my $num : double = 2.5;
  
  # Initialized by Point object
  my $point : Point = new Point;

Using L<"Type Inference">, you omit L<"Types"> in Local Variable Declaration.

  # int
  my $num = 1;
  
  # double
  my $num = 1.0;

Local Variable Declaration returns the value of Local Variable. This is a L<"Expressions">.

  my $ppp = my $bar = 4;
  
  if (my $bar = 1) {
  
  }
  
  while (my $bar = 1) {
  
  }

See L<"Scope"> about Local Variable Scope.

=head2 Local Variable Initial Value

Local Variable is initialized by L<"Type Initial Value">.

=head2 Local Variable Access

Local Variable Access is an operation to access Local Variable to get or set the value.

See L<"Get Local Variable"> to get Local Variable value.

L<"Set Local Variable"> to get Local Variable value.

If L<"Class Variable"> with the same name as the Local Variable exists, Program uses the variable as Local Variable, not L<"Class Variable">.

=head1 Scope

=head2 Scope Summary

B<Scope> is a range surrounded by L<"Scope Blocks">.

  # Scope Blocks 
  {
    # Start of Scope
    
    # ...
    
    # End of Scope
  }

Local Variable Declaration registers the Local Variable that is L<"Object Types"> with Mortal Variable in run-time. 

If the object is not L<"undef">, The Reference Count is added by 1.

  {
    # $num become Mortal Variable in run-time
    my $num = new Foo;
  }

At the end of Scope, the object that is registered as Mortal Variable, Reference Count is reduced by 1 except the object is not L<"undef">.

If the Reference Count become 0, the object released.

=head2 Block

The parts enclosed by C<{> and C<}> are called blocks.

  # Blocks
  {
    1;
  }
  
  if (true) {
    
  }
  
  while (true) {
    
  }
  
  enum {
    ONE,
    TWO,
  }
  
  class Foo {
    
  }

=head2 Scope Blocks

A scope block is the block that create a scope. Zero or more L<statements|"Statements"> can be written in a scope block.

Scope blocks are L<"Simple Block">, L<"Method Block">, L<"eval Block">, L<"if Block">, L<"elsif Block">, L<"else Block">, L<"for Block">, L<"while Block"> and L<"switch Block">.

=head2 Simple Block

A simple block is a scope block.

  # A simple block
  {
  
  }

=head2 Method Block

A C<method> block is a scope block.

  # A method block
  static method foo : int () {
  
  }

=head2 eval Block

a C<eval> block is a scope block.

  # A eval block
  eval {
  
  }

=head2 if Block

A C<if> block is a scope block.

  # A if block
  if (CONDITION) {
  
  }

=head2 elsif Block

A C<elsif> block is a scope block.

  # A elsif block
  elsif (CONDITION) {
  
  }

=head2 else Block

A C<else> block is a scope block.

  # A else Block
  else {
  
  }

=head2 for Block

A C<for> block is a scope block.

  # A for Block 
  for (my $i = 0; $i < 3; $i++) {
  
  }

=head2 while Block

A C<while> block is a scope block.

  # A while block
  while (CONDITION) {
  
  }

=head2 switch Block

A C<switch> block is a scope block.

  switch (CONDITION) {
  
  }

=head1 String

SPVM has the L<string type|"string Type">. A string is created by L<"String Literal"> L<"String Creation Operator"> or L<"Type Convertion"> to the string type.
  
  # Create a string using a string literal
  my $string = "Hello";
  
  # Create a string using a string creation operator
  my $string = new_string_len 3;
  
  # Create a string using a type conversion to the string type
  my $bytes = [(byte)93, 94, 95];
  my $string = (string)$bytes;

The each charcter can be get using C<-E<gt>[]>.

  # String
  my $string = "Hello";
  my $char0 = $string->[0];
  my $char1 = $string->[1];
  my $char2 = $string->[2];

By default, each character can't be set.
  
  # a compilation error.
  $string_const->[0] = 'd';

If you use C<mutable type qualifier|"mutable Type Qualifier">, each character can be set.

  my $string_mut = (mutable string)$string;
  $string_mut->[0] = 'd';

The created string is one more last byte that value is C<\0> on the internal memory. Although this has no meaning from SPVM language, this has meaning from L<Native APIs|SPVM:Document::NativeAPI>.

The length of the string can be got using a L<string length operator|"String Length Operator">
  
  # Get the length of the string
  my $message = "Hello"+
  my $length = legnth $message;

=head1 Undefined Value

An undefined value is represented by C<undef>.

  undef

An undefined value can be assigned to all L<"Object Types">.

In the level of L<native APIs|SPVM:Document::NativeAPI>, C<undef> is defined as the following.

  (void*)NULL

An undefined value can be compared by the C<==> operator and the C<!=> operator. An undefined value is guaranteed not to be equal to the any created object.

B<Examples of undefined values:>
  
  # Undefine values
  my $string : string = undef;
  
  if (undef) {
    
  }
  
  my $message = "Hello";
  if ($message == undef) {
    
  }
  
=head1 Fat Comma

Fat Comma is a L<"Separators"> represented by "B<=>>".

  =>

Fat Comma is an alias for Comma "B<,>". Wherever you can use "B<,>" you can use Fat Comma instead.

  # Comma
  ["a", "b", "c", "d"]
  
  # Use Fat Comma instead of Comma
  ["a" => "b", "c" => "d"]

Identifiers other than L<"Class Variable Names"> and L<"Local Variable Names"> placed on the Left of Fat Comma are treated as L<"String Literal">.

  # Identifiers placed on the Left of Fat Comma are treated as String Literal
  # a is "a", c is "c"
  [a => "b", c => "d"]

=head1 Array

=head2 Array Summary

Array is a data structure for continuous multiple values.

There are the following types of Array.

=begin html

<ul>
  <li>
    Numeric Types Array
 </li>
  <li>
    Object Type Array
 </li>
  <li>
    Multi Numeric Types Array
 </li>
</ul>

=end html

Numeric Types Array is Array that element type is L<"Numeric Types">.

Numeric Types Array is Array that element type is L<"Object Types">.

Numeric Types Array is Array that element type is L<"Multi Numeric Types">.

=head2 Create Array

See L<"Create Array"> to create Array.

=head2 Array Access

Array Access is an operation to access the element of Array to get or set the value.

  ARRAY->[INDEX]

See L<"Get Array Element"> to get the element value of Array.

See L<"Set Array Element"> to set the element value of Array.

=head1 Multi Numeric Value

=head2 Multi Numeric Types Definition

Multi Numeric type represents continuous numeric values. For example, there are three consecutive 32-bit signed integers, two consecutive double-precision floating point numbers. It isplaned to use 3D points, complex numbers, quaternions, etc.

Multi Numeric Types are defined by specifying mulnum_t L<"Class Descriptors"> in L<"Class Definition">.

  # Three consecutive 32bit signed integers
  class Point_3i : mulnum_t {
    has x : int;
    has y : int;
    has z : int;
  }
  
  # Tow consecutive 64bit floating point numbers
  class Complex_2d : mulnum_t {
    x : double;
    y : double;
  }

Multi Numeric Types must end with "_", Number of Fields, L<"Multi Numeric Types Suffix">.

The suffix must correspond to L<"Numeric Types">.

All Fields must be the same L<"Numeric Types">.

The maximum number of Fields is 255.

Multi Numeric Types can be used as L<"Types"> of L<"Local Variable Declaration">.

Multi Numeric Types can be used as an argument L<"Types"> in L<"Method Definition"> .

Multi Numeric Types can be used as L<"Types"> of Return Value in L<"Method Definition">.

Multi Numeric Types can be used as L<"Basic Type"> of L<"Array Type"> .

  my $points = new Point_3i[5];

Reference can be created for Multi Numeric Types value.

  my $point : Point_3i;
  my $point_ref = \$point;

L<"Undefined Value"> cannot be assigned to Multi Numeric Types value.

See L<"Multi Numeric Types Field Access"> to get and set the value of field of Multi Numeric Types Value.

=head2 Multi Numeric Types Suffix

List of Multi Numeric Types Suffix.

=begin html

<table>
  <tr>
    <th>
      <b>Numeric Types</b>
   </th>
    <th>
      Multi Numeric Types Suffix
   </th>
  </tr>
  <tr>
    <td>
      <b>byte</b>
    </td>
    <td>
      b
    </td>
  </tr>
  <tr>
    <td>
      <b>short</b>
    </td>
    <td>
      s
    </td>
  </tr>
  <tr>
    <td>
      <b>int</b>
    </td>
    <td>
      i
    </td>
  </tr>
  <tr>
    <td>
      <b>long</b>
    </td>
    <td>
      l
    </td>
  </tr>
  <tr>
    <td>
      <b>float</b>
    </td>
    <td>
      f
    </td>
  </tr>
  <tr>
    <td>
      <b>double</b>
    </td>
    <td>
      d
    </td>
  </tr>
</table>

=end html

=head2 Multi Numeric Types Usage

To use Multi Numeric Types, load a Module using L<"use Statement">.

  use Point_3i;
  use Complex_2d;

Next is L<"Local Variable Declaration">. Local Variable Declaration create continuous area for fields of Multi Numeric Types Value on L<"Method Callstack">. All fields of of Multi Numeric Types Value are initialized by L<"Type Initial Value">.

  my $point : Point_3i;
  my $z : Complex_2d;

Note that Multi Numeric Types value are not object, so cannot create a Object by L<"new"> syntax.

=head2 Multi Numeric Types Field Access

B<Multi Numeric Types Field Access> is an operation to access Multi Numeric Types Field to get or set a value.

  MULTI_NUMERIC_TYPE_VALUE->{FIELD_NAME}

See L<"Get Multi Numeric Field Value"> to get Multi Numeric Types Field Value.

See L<"Set Multi Numeric Field Value"> to set Multi Numeric Types Field Value.

=head1 Multi Numeric Array

=head2 Multi Numeric Array Summary

L<"Multi Numeric Value"> can be an element of L<"Array">.

  my $points = new Point_3i[5];
  
  my $zs = new Complex_2d[5];

Multi Numeric Array has continuous Multi Numeric Values.

The Element Type is L<"Multi Numeric Types">, not L<"Object Types">.

For example, Point_3i[5] is continuous 15 (= 3 * 5) count L<"int Type"> Value.

L<"Types"> of Multi Numeric Array is L<"Array Type">.

=head2 Multi Numeric Array Access

Multi Numeric Array Access is an operation to access Multi Numeric Array to get and set the element value.

  Array->[INDEX]

See L<"Get Array Element"> to get Array Element Value.

See L<"Set Array Element"> to get Array Element Value.

=head1 Reference

=head2 Reference Summary

Reference is data that indicates the location of L<"Local Variable"> in the memory. Reference is a feature corresponding to Pointer in C language.

You can get Reference of Local Variable using L<"Reference Operator">.

L<"Reference Type"> is represented by L<"Numeric Types"> "*" or L<"Multi Numeric Types"> followed by "*".
Reference types are represented by appending an * after L<"Numeric Types"> or L<"Multi Numeric Types">.

  # Numeric Types Reference
  my $num : int;
  my $num_ref : int* = \$num;
  
  # Multi Numeric Types Reference
  my $point : Point_3d;
  my $point_ref : Point_3d* = \$point;

Target of Reference Operator is Variable of L<"Numeric Types"> or L<"Multi Numeric Types">. L<"Object Types"> Variable or L<"Literals"> can't be target of Reference Operator.

L<"Reference Type"> can be used in Method Argument.

  # Method Definition
  static method sum : void ($out_ref : int*, $in1 : int, $in2 : int) {
    $$out_ref = $in1 + $in2;
  }
  
  # Method Call
  my $num1 = 1;
  my $num2 = 2;
  my $out : int;
  my $out_ref = \$out;
  sum($out_ref, $num1, $num2);

=head2 Dereference

Dereference is an operation to get and set the value pointed by Reference.

  # Dereference Numeric Types Reference to get the pointed value
  my $num2 = $$num_ref;
  
  # Dereference Numeric Types Reference to set the pointed value
  $$num_ref = 3;
  
  # Dereference Mutil Numeric Types Reference to get the pointed value
  my $point2 = $$point_ref;
  
  # Dereference Mutil Numeric Types Reference to set the pointed value
  $$point_ref = $point2;

If the target of Reference Type is L<"Multi Numeric Types">, the setting and getting of Multi Numeric Types Field Value can be done by Arrow Operator.

  # If the target of Reference Type is Multi Numeric Types, get Multi Numeric Types Field Value
  my $x = $point_ref->{x};
  
  # If the Target of Reference Type is Multi Numeric Types, set Multi Numeric Types Field Value
  $point_ref->{x} = 1;

=head1 Expressions

Expressions are a syntax part that can be evaluated as a value.

These are L<"Operators">, L<"Undefined Value">, L<"Literals">, L<"Get Local Variable">, L<"Set Local Variable">,
L<"Get Class Variable">, L<"Get Class Variable">, L<"Set Class Variable">, L<"Get Exception Variable">, L<"Set Exception Variable">,
L<"Get Field">, L<"Set Field">, L<"Get Array Element">, L<"Set Array Element"> and L<"Method Call">.

=head2 Get Local Variable

B<Get Local Variable> is a Expression to get L<"Local Variable"> Value.

  $var

=head2 Set Local Variable

B<Set Local Variable Expression> is a Expression to set L<"Local Variable"> Value using L<"Assignment Operator">.

  $var = RIGHT_OPERAND

The Assignment must satisfy L<"Type Compatibility">.

Set Local Variable Expression returns the value after setting.

If the right operand is L<"Object Types">, Reference Count of the object is incremented by 1.

If an object has already been assigned to $var before the assignment, the Reference Count of that object is decremented by 1.

See L<"Scope"> to know Garbage Collection of Local Variable.

=head2 Get Class Variable

B<Get Class Variable Expression> is a Expression to get L<"Class Variable"> Value.

  $CLASS_NAME::CLASS_VARIABLE_NAME

"CLASS_NAME::" can be omitted when the Class Variable belongs to own L<"Class">.

  $CLASS_VARIABLE_NAME

If you try to get the value of a Class Variable that is not defined, a compilation error occurs.

If you try to access a private Class Variable from outside the Class, a compilation error occurs.

B<Get Class Variable Example:>

  class Foo {
    our $VAR : int;
  
    static method bar : int () {
      my $var1 = $Foo::VAR;
      my $var2 = $VAR;
    }
  }

=head2 Set Class Variable

B<Set Class Variable Expression> is a Expression to set L<"Class Variable"> Value using L<"Assignment Operator">.
.

  $CLASS_NAME::CLASS_VARIABLE_NAME = RIGHT_OPERAND

"CLASS_NAME::" can be omitted when the Class Variable belongs to own L<"Class">.

  $CLASS_VARIABLE_NAME = RIGHT_OPERAND

If the assignment does not satisfy L<"Type Compatibility">, a compilation error occurs.

Set Class Variable Expression returns the value after setting.

If you try to get the value of a Class Variable that is not defined, a compilation error occurs.

If you try to access a private Class Variable from outside the Class, a compilation error occurs.

If the right operand is L<"Object Types">, Reference Count of the object is incremented by 1.

If an object has already been assigned to Class Variable before the assignment, the Reference Count of that object is decremented by 1.

B<Set Class Variable Example:>

  class Foo {
    our $VAR : int;
  
    static method bar : int () {
      $Foo::VAR = 1;
      $VAR = 3;
    }
  }

=head2 Get Exception Variable

B<Set Class Variable Expression> is a Expression to get the value of L<"Exception Variable">.

  $@

Set Class Variable Expression returns the value of L<"string Type">.

B<Set Class Variable Example:>

  eval {
    foo();
  };
  
  if (my $message = $@) {
  
  }

=head2 Set Exception Variable

B<Set Exception Variable Expression> is a Expression to set the value of L<"Exception Variable"> using L<"Assignment Operator">.

  $@ = RIGHT_OPERAND

the right operand must be L<"string Type">.

Returns the value of Exception Variable after setting. This is L<"string Type">.

The Reference Count of the right operand is incremented by 1.

If an object has already been assigned to Exception Variable before the assignment, the Reference Count of that object is decremented by 1.

B<Set Exception Variable Example:>

  $@ = "Error";

=head2 Get Field

B<Get Field Expression> is a Expression to get L<"Field"> Value.

  INVOCANT_EXPRESSION->{FIELD_NAME}

Invocant Expression is L<"Class Type">. If Expression is L<"Multi Numeric Types"> Value, The Field Access is L<"Get Multi Numeric Field Value">. If Expression is L<"Multi Numeric Reference Type"> Value, The Field Access is, otherwise a compilation error occurs.

If the field names does not found in the <a href="#language-class">Class">, a compilation error occurs

Get Field Expression returns the value of the Field stored in the object.

Retrun Type is The L<"Types"> of the Field.

B<Get Field Example:>

  my $point = Point->new;
  my $x = $point->{x};

=head2 Set Field

B<Set Field Expression> is a Expression to set L<"Field"> Value.

  INVOCANT_EXPRESSION->{FIELD_NAME} = RIGHT_OPERAND

Invocant Expression is L<"Class Type">. If Invocant Expression is L<"Multi Numeric Types">, the Field Access is ,L<"Set Multi Numeric Field Value">. If Invocant Expression is L<"Multi Numeric Reference Type">, the Field Access is L<"Set Multi Numeric Field Value via Dereference">, otherwise a compilation error occurs.

If the assignment does not satisfy L<"Type Compatibility"> of the type of Field, a compilation error occurs.

If the field names does not found in the L<"Class">, a compilation error occurs.

Set Field Expression returns the value of Field after setting. 

Return Value Type is the type of Field.

If the right operand is L<"Object Types">, Reference Count of the object is incremented by 1.

If an object has already been assigned to Field before the assignment, the Reference Count of that object is decremented by 1.

B<Set Field Example:>

  my $point = Point->new;
  $point->{x} = 1;

=head2 Get Multi Numeric Field Value

B<Get Multi Numeric Field Value Expression> is a Expression to get Field Value of L<"Multi Numeric Value">.

  INVOCANT_EXPRESSION->{FIELD_NAME}

Invocant Expression is L<"Multi Numeric Types">. If Invocant Expression is L<"Class Type">, the Field Access is L<". If Invocant Expression <a href="#language-type-ref-multi-numeric">is Multi Numeric Reference Type">, the Field Access is L<"Get Multi Numeric Field Value via Dereference">, otherwise a compilation error occurs.
  
If the field names does not found in the L<"Class">, a compilation error occurs

Get Multi Numeric Field Value Expression returns the field value in the Multi Numeric Value.

Retrun Type is The L<"Types"> of the Field.

B<Get Multi Numeric Field Value Example:>

  my $z : Complex_2d;
  my $re = $z->{x};

=head2 Set Multi Numeric Field Value

Set Multi Numeric Field Value Expression is a Expression to set Field Value of L<"Multi Numeric Value"> using L<"Assignment Operator">.

  INVOCANT_EXPRESSION->{FIELD_NAME} = RIGHT_OPERAND

<

Invocant Expression is L<"Multi Numeric Types">. If Invocant Expression is L<"Class Type">, the Field Access is L<"Set Field">. Invocant Expression is L<"Multi Numeric Reference Type">, L<"Set Multi Numeric Field Value via Dereference">, otherwise a compilation error occurs.

If the field names does not found in the L<"Class">, a compilation error occurs.

Set Multi Numeric Field Value Expression returns the value of Field after setting. 

The Assignment must satisfy L<"Type Compatibility">.

Return Value Type is the type of Field.

B<Set Multi Numeric Field Value Example:>

  my $z : Complex_2d;
  $z->{x} = 2.5;

=head2 Get Multi Numeric Field Value via Dereference

B<Get Multi Numeric Field Value via Dereference Expression> is a Expression to get Field Value of L<"Multi Numeric Value"> via L<"Dereference">.

  INVOCANT_EXPRESSION->{FIELD_NAME}

Invocant Expression is L<"Multi Numeric Reference Type">. If Invocant Expression is L<"Class Type">, the Field Access is , L<"Get Field">. If Invocant Expression is L<"Multi Numeric Types">, the Field Access is L<"Get Multi Numeric Field Value">, otherwise a compilation error occurs.

If the field names does not found in the L<"Class">, a compilation error occurs

Get Multi Numeric Field Value via Dereference Expression returns the field value in the Multi Numeric Value.

Retrun Type is The L<"Types"> of the Field.

B<Get Multi Numeric Field Value via Dereference Example:>

  my $z : Complex_2d;
  my $z_ref = \$z;
  my $re = $z_ref->{x};

=head2 Set Multi Numeric Field Value via Dereference

Set Multi Numeric Field Value Expression via Dereference is a Expression to set Field Value of L<"Multi Numeric Value"> via L<"Dereference"> using L<"Assignment Operator">.

  INVOCANT_EXPRESSION->{FIELD_NAME} = RIGHT_OPERAND

Invocant Expression is L<"Multi Numeric Reference Type">. If Invocant Expression is L<"Class Type">, L<"Set Field">. If Invocant Expression is L<"Multi Numeric Types">, L<"Set Multi Numeric Field Value">, otherwise a compilation error occurs.

If the field names does not found in the L<"Class">, a compilation error occurs

Set Multi Numeric Field Value via Dereference Expression returns the value of Field after setting.

The Assignment must satisfy L<"Type Compatibility">.

Return Value Type is the type of Field.

B<Set Multi Numeric Field Value via Dereference Example:>

  my $z : Complex_2d;
  my $z_ref = \$z;
  $z_ref->{x} = 2.5;

=head2 Get Array Element

B<Get Array Element Expression> is a Expression to get a Element Value of L<"Array">.

  ARRAY_EXPRESSION->[INDEX_EXPRESSION]

Array Expression must be L<"Array Type">.

Index Expression must be L<"int Type"> or the type that become L<"int Type"> by L<"Unary Numeric Widening Type Conversion">.

Get Array Element Expression returns the Element Value of the Index.

If Array Expression is L<"Undefined Value">, a Runtime Exception occurs.

If Index Expression is lower than 0 or more than the max index of the Array, a Runtime Exception occurs.

B<Get Array Element Example:>

  my $nums = new int[3];
  my $num = $nums->[1];
  
  my $points = new Point[3];
  my $point = $points->[1];
  
  my $objects : oarray = $points;
  my $object = (Point)$objects->[1];

=head2 Set Array Element

Set Array Element Expression is a Expression to set a Element Value of a Array using L<"Assignment Operator">.

  ARRAY_EXPRESSION->[INDEX_EXPRESSION] = RIGHT_OPERAND

Array Expression must be L<"Array Type">.

Index Expression must be L<"int Type"> or the type that become L<"int Type"> by L<"Unary Numeric Widening Type Conversion">.

The Assignment must satisfy L<"Type Compatibility">.

Set Array Element Expression returns the value of the element after setting.

If Array Expression is L<"Undefined Value">, a Runtime Exception occurs.

If Index Expression is lower than 0 or more than the max index of the Array, a Runtime Exception occurs.

If the right operand is L<"Object Types">, Reference Count of the object is incremented by 1.

If an object has already been assigned to Field before the assignment, the Reference Count of that object is decremented by 1.

B<Set Array Element Example:>

  my $nums = new int[3];
  $nums->[1] = 3;
  
  my $points = new Point[3];
  $points->[1] = Point->new(1, 2);
  
  my $objects : oarray = $points;
  $objects->[2] = Point->new(3, 5);

=head2 Create Object

B<Create Object Expression> is a Expression to create Object using B<new> keyword.

  my $object = new CLASS_NAME;

L<"Class"> that is specified by L<"Class Names"> must be L<"Class Type">.

Fields of the Object are initialized by L<"Type Initial Value">.

Created Object Reference count is 0 at first. If the Object is assigned to some Variable by L<"Assignment Operator">, The Reference Count is incremented by 1. If implicite assignment is not done, Temporary Variable is created, the object is assigned to the Temporary Variable.

B<Create Object Example:>

  my $object = new Foo;

Create Object has the following information.

=begin html

<ul>
  <li>Reference Count</li>
  <li>Back references of L<"Weaken Reference"></li>
  <li>Basic Type ID</li>
  <li>Type Dimension(Always 0)</li>
</ul>

=end html

=head2 Create Array

B<Create Array Expression> is a Expression to create Array with B<new> Keyword.

  new Type[ELEMENTS_COUNT_EXPRESSION]

Type must be L<"Numeric Types">, L<"Object Types">, L<"Multi Numeric Types">.

Elements Count Expression must be L<"int Type"> or the type that become L<"int Type"> by L<"Unary Numeric Widening Type Conversion">.

If Index Expression is lower than 0, a Runtime Exception occurs.

Created Array Length is the value of Elements Count Expression.

All Array Element is initialized by L<"Type Initial Value">.

All Element is gurantied to be continued on Memory.

Array is L<"Array Type">. This is also L<"Object Types">.

B<Create Array Example:>

  my $nums = new int[3];
  my $objects = new Foo[3];
  my $objects = new object[3];
  my $values = new Complex_2d[3]

Created Array has the following information.

=begin html

<ul>
  <li>Reference Count</li>
  <li>Basic Type ID</li>
  <li>Type Dimension(the value is 1)</li>
  <li>Array Length</li>
</ul>

=end html

Multi-Dimention Array is created by the following syntax.

  # 2 Dimention Array (3 elements of int[] Type)
  my $nums = new int[][3];
  
  # 3 Dimention Array (3 elements of int[][] Type)
  my $nums = new int[][][3];

The max of Dimention of Multi-Dimention Array is 255.

=head2 Array Initialization

SPVM has a syntax for Array Initialization to simplify Create Array. Expression is not required.

  []
  [Expression1, Expression2, Expression3]

Array Initialization returns an Array that has the length of the number of elements of Expression.

The type of Array is the type of Expression1 converted to Array Type. If no element is specified, it will be an Array Type of L<"Any Object Type">.

If Expression2 or later does not satisfy L<"Type Compatibility">, a a compilation error will occur.

B<Examples:>

  # int array
  my $nums = [1, 2, 3];
  
  # double array
  my $nums = [1.5, 2.6, 3.7];
  
  # string array
  my $strings = ["foo", "bar", "baz"];

Array Initialization has another syntax. This is same as above array init syntax, but always the generated object type is Array Type of L<"Any Object Type">. And if count of expression is odd number, a compile error occurs.

  {}
  {Expression1, Expression2, Expression3, Expression4}

B<Examples:>

  # Key values empty
  my $key_values = {};
  
  # Key values
  my $key_values = {foo => 1, bar => "Hello"};

=head2 Method Call

Methods defined by L<"Method Definition"> can be called from program. There are three types of method calls. B<Class Method Call> and B<Instance Method Call>.

Defined method can be called by Class Method Call except a case that the first argument is L<"self Type">.

  ClassName->MethodName(ARGS1, ARGS2, ARGS3, ..., ARGSn);

The arguments max count is 255.

If the number of arguments does not match the number of arguments defined in the Method Definition, a compilation error occurs The Type of each argument and the type of the argument defined in Method Definition and <a href = "#language-type-compatible">Type Compatibility</a>, a compilation error occurs.

B<Class Method Call Example>

  my $ret = Foo->bar(1, 2, 3);

=head2 Current Class

B<&> before method name means the current class. You can call method using "&" keyword instead of the current class name.

B<Current Class Example>

  class Foo {
    
    static method test : void () {
      # This means Foo->sum(1, 2)
      my $ret = &sum(1, 2);
    }
  
    static method sum : int ($num1 : int, $num2 : int) {
      return $num1 + $num2;
    }
    
  }

=head2 Instance Method Call

Instance Method Call is a method to call Method which is L<"Method">. In L<"Method Definition">, the first argument is L<"self Type"> If the argument of> is specified, it becomes Method.

Instance Method Call can be done with the following syntax using the object created by L<"Create Object">.

  OBJECT_EXPRESSION->METHOD_NAME(ARGS1, ARGS2, ARGS3, ..., ARGSn);

Instance Method Call takes arguments. If the number of arguments does not match the number of arguments defined in the Method Definition, a compilation error occurs The Type of each argument and the type of the argument defined in Method Definition and <a href = "#language-type-compatible">Type Compatibility</a>, a compilation error occurs

Instance Method Call returns Return Value if Return Value is other than L<"void Type">.

Instance Method Call is L<"Expressions">.

B<Instance Method Call Example>

  my $point = new Point;
  $point->set_x(3);

Since the object created by L<"Create Callback Object"> is a normal object, you can call Method.

  OBJECT_EXPRESSION->(ARGS1, ARGS2, ARGS3, ..., ARGSn);

B<Example that calls Method from the object created with Create Callback Object>

An Example that calls a Method from the object created by Create Callback Object.

  my $cb_obj = method : int ($num1 : int, $num2 : int) {
    return $num1 + $num2;
  };
  
  my $ret = $cb_obj->(1, 2);

=head2 Get value by Dereference

Obtaining a value by Dereference is an operation to obtain the actual value from Reference. It was designed to realize the C joint operator "*".

  $VARIABLE

The variable Type must be Reference Type, otherwise a compilation error occurs.

The value obtained by Dereference returns L<"Expressions">.

    B<Example of getting value by Dereference>

  my $num : int;
  my $num_ref : int* = \$num;
  my $num_deref : int = $$num_ref;
  
  my $z : Complex_2d;
  my $z_ref : Complex_2d* = \$z;
  my $z_deref : Complex_2d = $$z_ref;

=head2 Setting the value with Dereference

Setting a value with Dereference is an operation to set the actual value from Reference. It was designed to realize the C joint operator "*".

  $VARIABLE = Expression

The variable Type must be Reference Type, otherwise a compilation error occurs.

The Type of Expression must match the type of the variable when dereferenced, otherwise a compilation error occurs.

Setting a value with Dereference returns the set value. This is L<"Expressions">.

    B<Example of setting values ​​with Dereference>

  my $num : int;
  my $num_ref : int* = \$num;
  $$num_ref = 1;
  
  my $z : Complex_2d;
  my $z_ref : Complex_2d* = \$z;
  
  my $z2 : Complex_2d;
  
  $$z_ref = $z2;

=head2 Get Current Class Names

B<Get Current class names> is a Expression to get the current class name by __CLASS__ L<"Keyword">.

  __CLASS__

B<Get Current class names Example:>

  class Foo::Bar {
    static method baz : void () {
      # Foo::Bar
      my $class_name == __CLASS__;
    }
  }

=head2 Get Current File Name

B<Get Current File Name> is a Expression to get the current file name by __LINE__ L<"Keyword">.

  __FILE__

Current File Name means the relative path from the base path of the module file. For example, if the Module Loaded Path is "/mypath" and the Module name is "Foo::Bar", the absolute path is "/mypath/SPVM/Foo/Bar.spvm" and the relative path is "SPVM/Foo/Bar.spvm". "SPVM/Foo/Bar.spvm" is Current File Name.

B<Get Current File Name Example:>

  # SPVM/Foo/Bar.spvm
  class Foo::Bar {
    static method baz : void () {
      # SPVM/Foo/Bar.spvm
      my $file_name == __FILE__;
    }
  }
  class Foo::Bar2 {
    static method baz : void () {
      # SPVM/Foo/Bar.spvm
      my $file_name == __FILE__;
    }
  }

=head2 Get Current Line Number

B<Get Current Line Number> is a Expression to get the current line number of the current file by __LINE__ L<"Keyword">.

  __LINE__

B<Get Current Line Number Example:>

  class Foo::Bar {
    static method baz : void () {
      # 4
      my $line = __LINE__;
    }
  }

=head1 Operators

B<Operators> are L<"Unary Operators">, L<"Binary Operators">, L<"Increment Operator">, L<"Decrement Operator">, L<"Comparison Operator">, L<"Logical Operators">, and L<"Assignment Operator">.

=head2 Unary Operators

Unary operators are operators have one operand.

  UNARY_OPERATOR OPERAND

The operand is an L<expression|"Expressions">.

Unary operators are L<"Unary Plus Operator">, L<"Unary Minus Operator">, L<"Bit NOT Operator">, L<"Array Length Operator">, L<"String Creation Operator">, and L<"String Length Operator">.

=head2 Binary Operators

Binary Operator is a L<operator|"Operators"> that have two operands.

  LEFT_OPERAND BINARY_OPERATOR RIGHT_OPERAND

Binary operators are L<"Addition Operator">, L<"Subtraction Operator">, L<"Multiplication Operator">, L<"Division Operator">, L<"Remainder Operator">, L<"Bit AND Operator">, L<"Bit OR Operator">, L<"Shift Operators">, and L<"String Concatenation Operator">.

=head2 Sequential Operator

The sequential operator C<,> is an L<operator|"Operators"> like the following.

  (OPERAND1, OPERAND2, ..., OPERNADN)

The operands are evaluated from the left to the right, and return the evaluated value of the last operand.

B<Examples of sequential operators:>

  # 3 is assigned to $foo
  my $foo = (1, 2, 3);
  
  # $x is 3, $ret is 5
  my $x = 1;
  my $y = 2;
  my $ret = ($x += 2, $x + $y);

=head2 Arithmetic Operators

B<Arithmetic Operators> is an L<"Operators"> that performs arithmetic.

B<Arithmetic Operatorss> are L<"Addition Operator">, L<"Subtraction Operator">, L<"Multiplication Operator">, L<"Division Operator">, L<"Division Unsigned Int Operator">, , L<"Division Unsigned Long Operator">, L<"Remainder Operator">, L<"Remainder Unsigned Int Operator">, L<"Remainder Unsigned Long Operator">, L<"Unary Plus Operator">, L<"Unary Minus Operator">, L<"Increment Operator">, and L<"Decrement Operator">.

=head2 Unary Plus Operator

The unary plus operator C<+> is an L<Unary Operator|"Unary Operators"> to return the value of the operand.

  +OPERAND

The operand must be an L<expression|"Expressions"> that type is a L<numeric type|"Numeric Types">, otherwise a compilation error occurs.

L<"Unary Numeric Widening Type Conversion"> applys to the operand.

returns the value copied from the value of the operand.

the return type of the unary plus pperator is the type that L<"Unary Numeric Widening Type Conversion"> is performed.

B<Examples of unary plus operators:>
  
  # A unary plus operator
  my $num = +10;

=head2 Unary Minus Operator

The unary minus operator C<-> is an L<Unary Operator|"Unary Operators"> to return the negative value of the operand.

  -OPERAND

The operand must be an L<expression|"Expressions"> that type is a L<numeric type|"Numeric Types">, otherwise a compilation error occurs.

L<"Unary Numeric Widening Type Conversion"> applys to the operand.

the unary minus operator performs the following operation of C language.

  -x

Return type of a unary minus operator is the type that L<"Unary Numeric Widening Type Conversion"> is performed.

B<Examples of unary minus operators:>

  # A unary minus operator
  my $num = -10;

=head2 Addition Operator

The addition operator C<+> is a L<binary operator|"Binary Operators"> to calcurate the result of the addition of two numbers.

  LEFT_OPERAND + RIGHT_OPERAND

The left operand and the right operand must be a L<numeric type|"Numeric Types">, otherwise a compilation error occurs.

L<"Binary Numeric Widening Type Conversion"> is performed to the left operand and the right operand.

The addition operator performs the operation that exactly same as the following operation in C language.

  x + y;

The return type of the addition operator is the type that L<"Binary Numeric Widening Type Conversion"> is performed.

=head2 Subtraction Operator

The subtraction operator C<-> is a L<binary operator|"Binary Operators"> to calcurate the result of the subtraction of two numbers.

  LEFT_OPERAND - RIGHT_OPERAND

The left operand and the right operand must be a L<numeric type|"Numeric Types">, otherwise a compilation error occurs.

L<"Binary Numeric Widening Type Conversion"> is performed to the left operand and the right operand.

The subtraction operator performs the operation that exactly same as the following operation in C language.

  x - y;

The return type of the subtraction operator is the type that L<"Binary Numeric Widening Type Conversion"> is performed.

=head2 Multiplication Operator

The multiplication operator is a L<binary operator|"Binary Operators"> to calcurate the result of multiplication of two numbers.

  LEFT_OPERAND * RIGHT_OPERAND

The left operand and the right operand must be a L<numeric type|"Numeric Types">, otherwise a compilation error occurs.

L<"Binary Numeric Widening Type Conversion"> is performed to the left operand and the right operand.

The multiplication operator performs the operation that exactly same as the following operation in C language.

  x * y;

The return type of the multiplication operator is the type after L<"Binary Numeric Widening Type Conversion"> is performed.

=head2 Division Operator

The division operator C</> is a L<binary operator|"Binary Operators"> to culcurate the division of two numbers.

  LEFT_OPERAND / RIGHT_OPERAND

The left operand and the right operand must be L<"Numeric Types">, otherwise a compilation error occurs.

L<"Binary Numeric Widening Type Conversion"> is performed to the left operand and the right operand.

The division operator performs the operation that exactly same as the following operation in C language.

  x / y;

The return type of the division operator is the type after L<"Binary Numeric Widening Type Conversion"> is performed.

If the two operands are L<integral types|"Integral Types"> and the value of the right operand is C<0>, an L<exception|"Exception"> is thrown.

=head2 Division Unsigned Int Operator

The division unsigned int operator C<divui> is a L<binary operator|"Binary Operators"> to culcurate the unsigned int division of two numbers.

  LEFT_OPERAND divui RIGHT_OPERAND

The left operand and the right operand must be an L<int type|"int Type">, otherwise a compilation error occurs.

The division unsigned int operator performs the operation that exactly same as the following operation in C language.

  (uint32_t)x / (uint32_t)y;

The return type of the division operator is the L<int type|"int Type">.

If the value of the right operand is C<0>, an L<exception|"Exception"> is thrown.

=head2 Division Unsigned Long Operator

The division unsigned long operator C<divul> is a L<binary operator|"Binary Operators"> to culcurate the unsigned long division of two numbers.

  LEFT_OPERAND divul RIGHT_OPERAND

The left operand and the right operand must be an L<long type|"long Type">, otherwise a compilation error occurs.

The division unsigned long operator performs the operation that exactly same as the following operation in C language.

  (uint64_t)x / (uint64_t)y;

The return type of the division operator is the L<long type|"long Type">.

If the value of the right operand is C<0>, an L<exception|"Exception"> is thrown.

=head2 Remainder Operator

The remainder operator C<%> is a L<binary operator|"Binary Operators"> to calcurate a remainder of two numbers.

  LEFT_OPERAND % RIGHT_OPERAND

The left operand and the right operand must be an L<integral type|"Integral Types">, otherwise a compilation error occurs.

L<"Binary Numeric Widening Type Conversion"> is performed to the left operand and the right operand.

The remainder operator performs the operation that exactly same as the following operation in C language.

  x % y;

the return type of Remainder Operator is the type that L<"Binary Numeric Widening Type Conversion"> is performed.

If the right operand is C<0>, the remainder operator throw an L<exception|"Exception">.

=head2 Remainder Unsigned Int Operator

The remainder unsigned int operator C<remui> is a L<binary operator|"Binary Operators"> to calcurate a unsigned int remainder of two numbers.

  LEFT_OPERAND remui RIGHT_OPERAND

The left operand and the right operand must be a L<int type|"int Type">, otherwise a compilation error occurs.

The remainder unsigned int operator performs the operation that exactly same as the following operation in C language.

  (uint32_t)x % (uint32_t)y;

The return type of the remainder unsigned int operator is the L<int type|"int Type">.

If the value of the right operand is C<0>, an L<exception|"Exception"> is thrown .

=head2 Remainder Unsigned Long Operator

The remainder unsigned long operator C<remul> is a L<binary operator|"Binary Operators"> to calcurate a unsigned long remainder of two numbers.

  LEFT_OPERAND remul RIGHT_OPERAND

The left operand and the right operand must be a L<long type|"long Type">, otherwise a compilation error occurs.

The remainder unsigned long operator performs the operation that exactly same as the following operation in C language.

  (ulong64_t)x % (ulong64_t)y;

The return type of the remainder unsigned long operator is the L<long type|"long Type">.

If the value of the right operand is C<0>, an L<exception|"Exception"> is thrown .

=head2 Increment Operator

B<Increment Operator> is an Operator that adds 1 to the value. the meaning of Increment Operator is different depending on whether the Increment Operator is placed Pre or Post.

  # Pre Increment Operator
  ++LEXICAL_VARIABLE
  ++CLASS_VARIABLE
  ++FIELD_ACCESS
  ++ARRAY_ACCESS
  ++DEREFERENCE
  
  # Post Increment Operator
  LEXICAL_VARIABLE++
  CLASS_VARIABLE++
  FIELD_ACCESS++
  ARRAY_ACCESS++
  DEREFERENCE++

The operand of Increment Operator must L<"Local Variable">, L<"Class Variable">, <a href = "#language-field-access">Field Access</a>, L<"Array Access">, L<"Dereference">, otherwise a compilation error occurs.

The Type of operand of Increment Operator must be L<"Numeric Types">, otherwise a compilation error will occur.

=head3 Pre Increment Operator

Pre Increment Operator adds 1 to the operand and returns the value after increment.

Pre Increment Operator is equivalent to the following Expression. After 1 is added to the operand, L<"Type Cast"> is performed with the operand Type and the value is assinged to original operand.

  (OPERAND_OPERAND = (TYPE)(OPERAND_OPERAND + 1))

For example, Pre Increment of L<"byte Type"> value is equivalent to the following Expression:

  ($num = (byte)($num + 1))

=head3 Post Increment Operator

Post Increment Operator add 1 to the operand and returns the value before Increment.

Post Increment Operator is equivalent to the following Expression using L<"Sequential Operator">. The value of operand is saved in a temporary variable, 1 is added to the operand, L<"Type Cast"> is performed with the operand Type, and the value is assinged to original operand. Then the temporary variable is returned.

  (my TMP_VARIABLE = OPERAND_OPERAND, OPERAND_OPERAND = (TYPE)(OPERAND_OPERAND + 1), TMP_VARIABLE)

For example, Post Increment of L<"byte Type"> value is equivalent to the following Expression.

  (my $tmp = $num, $num = (byte)($num + 1), $tmp)

=head2 Decrement Operator

B<Decrement Operator> is an Operator that subtracts 1 to the value. the meaning of Decrement Operator is different depending on whether the Decrement Operator is placed Pre or Post.

  # Pre Decrement Operator
  --LEXICAL_VARIABLE
  --CLASS_VARIABLE
  --FIELD_ACCESS
  --ARRAY_ACCESS
  --DEREFERENCE
  
  # Post Decrement Operator
  LEXICAL_VARIABLE--
  CLASS_VARIABLE--
  FIELD_ACCESS--
  ARRAY_ACCESS--
  DEREFERENCE--

The operand of Decrement Operator must L<"Local Variable">, L<"Class Variable">, <a href = "#language-field-access">Field Access</a>, L<"Array Access">, L<"Dereference">, otherwise a compilation error occurs.

The Type of operand of Decrement Operator must be L<"Numeric Types">, otherwise a compilation error will occur.

=head3 Pre Decrement Operator

Pre Decrement Operator subtracts 1 to the operand and returns the value after decrement.

Pre Decrement Operator is equivalent to the following Expression. After 1 is subtracted to the operand, L<"Type Cast"> is performed with the operand Type and the value is assinged to original operand.

  (OPERAND_OPERAND = (TYPE)(OPERAND_OPERAND - 1))

For example, Pre Decrement of L<"byte Type"> value is equivalent to the following Expression:

  ($num = (byte)($num - 1))

=head3 Post Decrement Operator

Post Decrement Operator subtract 1 to the operand and returns the value before Decrement.

Post Decrement Operator is equivalent to the following Expression using L<"Sequential Operator">. The value of operand is saved in a temporary variable, 1 is subtracted to the operand, L<"Type Cast"> is performed with the operand Type, and the value is assinged to original operand. Then the temporary variable is returned.

  (my TMP_VARIABLE = OPERAND_OPERAND, OPERAND_OPERAND = (TYPE)(OPERAND_OPERAND - 1), TMP_VARIABLE)

For example, Post Decrement of L<"byte Type"> value is equivalent to the following Expression.

  (my $tmp = $num, $num = (byte)($num - 1), $tmp)

=head2 Bit Operator

Bit Operator is an Operator that performs Bit operation. L<"Bit AND Operator">, <a href = "#language-operator-bit-or">Bit OR Operator</a>, L<"Bit NOT Operator">.

=head2 Bit AND Operator

Bit AND is L<"Binary Operators"> represented by "&".

  LEFT_OPERAND & RIGHT_OPERAND

The left operand and the right operand must be L<"Integral Types">, otherwise a compilation error occurs.

L<"Binary Numeric Widening Type Conversion"> is performed on The left operand and the right operand.

the operation result of Bit AND Operator performs the operation that exactly same as the following operation in C language

  x & y;

The Type of Return Value of Bit AND Operator is the type after L<"Binary Numeric Widening Type"> is performed.

=head2 Bit OR Operator

Bit OR is L<"Binary Operators"> represented by "|".

  LEFT_OPERAND | RIGHT_OPERAND

The left operand and the right operand must be L<"Integral Types">, otherwise a compilation error occurs.

L<"Binary Numeric Widening Type Conversion"> is performed on The left operand and the right operand.

the operation result of Bit OR Operator performs the operation that exactly same as the following operation in C language.

  x | y;

The Type of Return Value of Bit OR Operator is the type that is L<"Binary Numeric Widening Type Converted">.

=head2 Bit NOT Operator

The bit NOT operator C<~> is a L<unary operator|"Unary Operators"> to get the value of bit-not operation.

  ~OPERAND

The operand must be an L<expression|"Expressions"> that type is an L<integral type|"Integral Types">, otherwise a compilation error occurs.

L<"Unary Numeric Widening Type Conversion"> is performed to the operand.

The bit NOT operator performs the operation that exactly same as the following operation in C language.

  ~x

The type of return value is the type that L<"Unary Numeric Widening Type Conversion"> is performed.

B<Examples of bit NOT operators:>
  
  # Bit NOT operations
  my $num = ~0xFF0A;

=head2 Shift Operators

Shift operators are operators that performs bit shift operations. These are L<"Left Shift Operator">, L<"Arithmetic Right Shift Operator">, and L<"Logical Right Shift Operator">.

=head2 Left Shift Operator

The left shift operator C<E<lt>E<lt>> is a L<binary operator|"Binary Operators"> to perform the left bit shift.

  LEFT_OPERAND << RIGHT_OPERAND

The left operand must be L<"Integral Types">, otherwise a compilation error occurs.

L<"Unary Numeric Widening Type Conversion"> is performed to the left operand.

The right operand must be L<"Integral Types"> except for the L<long type|"long Type">, otherwise a compilation error occurs.

L<"Unary Numeric Widening Type Conversion"> is performed to the right operand.

The return type is same as the type of the left operand.

The calculation result of the left shift operator is the same as the following calculation in C language.

  x << y;

=head2 Arithmetic Right Shift Operator

The arithmetic right shift operator C<E<gt>E<gt>> is a L<binary operator|"Binary Operators"> to perform the arithmetic right bit shift.

  LEFT_OPERAND >> RIGHT_OPERAND

The left operand must be L<"Integral Types">, otherwise a compilation error occurs.

L<"Unary Numeric Widening Type Conversion"> is performed to the left operand.

The right operand must be L<"Integral Types"> except for the L<long type|"long Type">, otherwise a compilation error occurs.

L<"Unary Numeric Widening Type Conversion"> is performed to the right operand.

The return type is same as the type of the left operand.

The operation result of the arithmetic right shift Operator is the operation that exactly same as the following operation in C language.

  x >> y;

=head2 Logical Right Shift Operator

The logical right shift operator C<E<gt>E<gt>E<gt>>is a L<binary operator|"Binary Operators"> to perform the logical right bit shift.

  LEFT_OPERAND >>> RIGHT_OPERAND

The left operand must be L<"Integral Types">, otherwise a compilation error occurs.

L<"Unary Numeric Widening Type Conversion"> is performed to the left operand.

The right operand must be L<"Integral Types"> except for the L<long type|"long Type">, otherwise a compilation error occurs.

L<"Unary Numeric Widening Type Conversion"> is performed to the right operand.

The return type is same as the type of the left operand.

The operation result of logical right shift Operator is the same as the following calculation in C language.
  
  // In the case that the left operand is a int type
  (uint32_t)x >> y;

  // In the case that the left operand is a long type
  (uint64_t)x >> y;

=head2 Comparison Operator

Comparison Operator is an Operator that is placed between The left operand and the right operand to compare the size, and return True/False Value.

  LEFT_OPERAND COMPARISON_OPERATOR RIGHT_OPERAND

Comparison Operators are L<"Numeric Comparison Operator">, L<"String Comparison Operator">, and L<"isa Operator">.

=head2 Numeric Comparison Operator

B<Numeric Comparison Operator> is a L<"Comparison Operator"> that is placed between The left operand and the right operand to compare the size of number or check the equqlity of objects.

  LEFT_OPERAND NUMERIC_COMPARISON_OPERATOR RIGHT_OPERAND

A list of Numeric Comparison Operators.

=begin html

<table>
  <tr>
    <th>Operator</th>
    <th>Comparable Type</th>
    <th>Description</th>
  </tr>
  <tr>
    <td>
      LEFT_OPERAND == RIGHT_OPERAND
    </td>
    <td>
      The left operand and the right operand are Numeric Types, The left operand and the right operand are Object Type (including Undefined Value)
    </td>
    <td>
      The left operand and the right operand are equal
    </td>
  </tr>
  <tr>
    <td>
      LEFT_OPERAND != RIGHT_OPERAND
    </td>
    <td>
      The left operand and the right operand are Numeric Types, The left operand and the right operand are Object Type (including Undefined Value)
    </td>
    <td>
      The left operand and the right operand are not equal
    </td>
  </tr>
  <tr>
    <td>
      LEFT_OPERAND > RIGHT_OPERAND
    </td>
    <td>
      The left operand and the right operand are Numeric Types
    </td>
    <td>
      The left operand is greater than the right operand
    </td>
  </tr>
  <tr>
    <td>
      LEFT_OPERAND >= RIGHT_OPERAND
    </td>
    <td>
      The left operand and the right operand are Numeric Types
    </td>
    <td>
      The left operand is greater than or equal to the right operand
    </td>
  </tr>
  <tr>
    <td>
      LEFT_OPERAND < RIGHT_OPERAND
    </td>
    <td>
      The left operand and the right operand are Numeric Types
    </td>
    <td>
      The left operand is less than the right operand
    </td>
  </tr>
  <tr>
    <td>
      LEFT_OPERAND <= RIGHT_OPERAND
    </td>
    <td>
      The left operand and the right operand are Numeric Types
    </td>
    <td>
      The left operand is less than or equal to the right operand
    </td>
  </tr>
  <tr>
    <td>
      LEFT_OPERAND <=> RIGHT_OPERAND
    </td>
    <td>
      The left operand and the right operand are Numeric Types
    </td>
    <td>
      If The left operand is greater than Right expression, return 1. If The left operand is lower than Right expression, return -1. If The left operand is equals to Right expression, return 0.
    </td>
  </tr>
</table>

=end html

The Types of The left operand and the right operand Comparable Types, otherwise a compilation error occurs.

In Numeric Types Comparison, L<"Binary Numeric Widening Type Conversion"> is performed for The left operand and the right operand.

the Numeric Comparison Operation is performed that exactly same as the following operation in C language.

  # Numeric Types Comparison, Object Type Comparison
  (int32_t)(x == y);
  (int32_t)(x != y);
  
  # Numeric Types Comparison
  (int32_t)(x > y);
  (int32_t)(x >= y);
  (int32_t)(x < y);
  (int32_t)(x <= y);
  (int32_t)(x > y ? 1 : x < y ? -1 : 0);

For Numeric Types Operation(==, !=, >, >=, <, <=), L<"int Type"> Operation, L<"long Type"> Operation, L<"float Type"> Operation, L<"double Type"> Operation is defined.

And Object Type Operation(==, !=) is defined.

The Type of Return Value of the Numeric Comparison Operator is L<"int Type">.

=head2 String Comparison Operator

B<String Comparison Operator> is a L<"Comparison Operator"> that compares the bytes in the tow string.

  LEFT_OPERAND STRING_COMPARISON_OPERATOR RIGHT_OPERAND

The left operand and the right operand must be L<"string Type"> or byte[] type.

A list of String Comparison Operators.

=begin html

<table>
  <tr>
    <th>Operator</th>
    <th>Description</th>
  </tr>
  <tr>
    <td>
      LEFT_OPERAND eq RIGHT_OPERAND
    </td>
    <td>
      The left operand and the right operand are equal
    </td>
  </tr>
  <tr>
    <td>
      LEFT_OPERAND ne RIGHT_OPERAND
    </td>
    <td>
      The left operand and the right operand are not equal
    </td>
  </tr>
  <tr>
    <td>
      LEFT_OPERAND gt RIGHT_OPERAND
    </td>
    <td>
      The left operand is greater than the right operand in dictionary Expression order.
    </td>
  </tr>
  <tr>
    <td>
      LEFT_OPERAND ge RIGHT_OPERAND
    </td>
    <td>
      The left operand is greater than or equal to the right operand compared in dictionary Expression order
    </td>
  </tr>
  <tr>
    <td>
      LEFT_OPERAND lt RIGHT_OPERAND
    </td>
    <td>
      The left operand is smaller than the right operand when compared in dictionary Expression order
    </td>
  </tr>
  <tr>
    <td>
      LEFT_OPERAND le RIGHT_OPERAND
    </td>
    <td>
      The left operand is less than or equal to the right operand compared in dictionary Expression order
    </td>
  </tr>
  <tr>
    <td>
      LEFT_OPERAND cmp RIGHT_OPERAND
    </td>
    <td>
      If The left operand is greater than Right expression, return 1. If The left operand is lower than Right expression, return -1. If The left operand is equals to Right expression, return 0.
    </td>
  </tr>
</table>

=end html

The Type of Return Value of the String Comparison Operator is L<"int Type">. If the condition is met, returns 1, otherwise 0.

=head2 isa Operator

B<isa Operator> is a L<"Comparison Operator"> to check whether The left operand satisfies Right Type.

  LEFT_OPERAND isa RIGHT_TYPE

isa Operator has three behaviors, depending on Right Type.

1. If Right Type is L<"Numeric Types">, L<"Multi Numeric Types">, L<"Any Object Type">, L<"Reference Type">, isa operator checks whether the type of The left operand is same as Right Type. This check is done at compile time and isa operator is replaced by L<"int Type"> value. If their types is same, replaced by 1, otherwise by 0.

2. If the Right Type is L<"Class Type">, isa operator checks whether the type of The left operand is same as Right Type at Run Time. If their types are same, L<"int Type"> 1 is return, otherwise 0. The Type of The left operand must be L<"Object Types">, otherwise a compilation error occurs.

3. If the Right Type is L<"Callback Type">, isa Operator checks whether the type of The left operand satisfy the Callback Type at Run Time. If The left operand satisfies the Callback Type, returns L<"int Type"> 1, otherwise 0. The Type of The left operand must be L<"Object Types">, otherwise a compilation error occurs.

=head2 ref Operator

B<ref Operator> is a Operator to get type name of the object.

  ref OPERAND

ref Operator return type name if the object defined. Otherwise return undef.

If OPERAND is not a object type, a compile error occurs.

=head2 dump Operator

B<dump Operator> is a Operator to dump object value.

  dump OPERAND

dump Operator return the dump string.

If OPERAND is not a object type, a compile error occurs.

The contents of the dumped string may vary from SPVM version to version. Please use dump operator only for viewing the content of object data.

=head2 Logical Operators

Logical Operators are L<"Operators"> that performs a logical operation. These are L<"Logical AND Operator">, L<"Logical OR Operator">, and L<"Logical NOT Operator">.

=head2 Logical AND Operator

The logical AND operator C<&&> returns the result of a logical AND operation.

  LEFT_OPERAND && RIGHT_OPERAND
  
The left operand and the right operand must be a L<logical operator|"Logical Operators"> or an L<expression|"Expressions">.

The return type of logical AND operator is L<"int Type">.

Thg logical AND operator performs L<"Bool Type Conversion"> to the left operand. If the evaluated value is C<0>, the logical AND operator returns C<0>.
If the value is C<1>, the right operand is evaluated.

Next, Thg logical AND operator performs L<"Bool Type Conversion"> to the right operand. If the evaluated value is C<0>, the logical AND operator returns C<0>,
otherwise returns C<1>.

Logical AND operators can be only used as conditions. Note that these can't be used as L<expressions|"Expressions">. 

=head2 Logical OR Operator

The logical OR operator C<||> returns the result of a logical OR operation.

  LEFT_OPERAND || RIGHT_OPERAND

The left operand and the right operand must be a L<logical operator|"Logical Operators"> or an L<expression|"Expressions">.

The return type of logical OR operator is L<"int Type">.

Thg logical OR operator performs L<"Bool Type Conversion"> to the left operand. If the evaluated value is C<1>, the logical OR operator returns C<1>.
If the value is C<0>, the right operand is evaluated.

Next, Thg logical OR operator performs L<"Bool Type Conversion"> to the right operand. If the evaluated value is C<1>, the logical OR operator returns C<1>,
otherwise returns C<0>.

Logical OR operators can be only used as conditions. Note that these can't be used as L<expressions|"Expressions">. 

=head2 Logical NOT Operator

The logical NOT operator C<!> returns the result of a logical NOT operation.

  !OPERAND

The operand must be a L<logical operator|"Logical Operators"> or an L<expression|"Expressions">.

The return type of logical NOT operator is L<"int Type">.

Thg logical NOT operator performs L<"Bool Type Conversion"> to the operand. If the evaluated value is C<1>, the logical NOT operator returns C<0>.
If the evaluated value is C<0>, returns C<1>.

Logical NOT operators can be only used as conditions. Note that these can't be used as L<expressions|"Expressions">. 

=head2 String Concatenation Operator

String concatenation operator C<.> is a L<binary operator|"Binary Operators"> to concat two strings.

  LEFT_OPERAND . RIGHT_OPERAND

The left operand and the right operand must be a L<string type|"string Type">, L<"byte[] Type">, or L<numeric type|"Numeric Types">, otherwise a compilation error occurs.

If the type of the operand is numeric type, a L<numeric to string type conversion|"Numeric to string Type Conversion"> is performed.

The type of return value is a L<string type|"string Type">.

A string concatenation operator returns the result to concat two operands.

If both the left operand and the right operand are a L<string literal|"String Literal">, the two string literals are concatenated at compile time.

If the left operand or the right operand is L<undef|"Undefined Value">, an exception occurs.

B<Examples of string concatenation operators:>

  my $str = "abc" . "def";
  my $str = "def" . 34;
  my $str = 123 . 456;

=head2 Assignment Operator

Assignment Operator is a L<"Binary Operators"> for assignment, expressed in "=".

  LEFT_OPERAND = RIGHTH_OPERAND

Assignment Operator has multiple meanings depending on the Right and Left sides. Please refer to each item.

In Assignment Operator, the The left operand is evaluated after the right operand is evaluated. This is with the exception of expression being executed from Left to Right as a rule.

=head2 Special Assignment Operator

Special Assignment Operator is a L<"Assignment Operator">L<"Type Compatibility">を満たさない場合は,a compilation error occurs

B<List of Special Assignment Operators>

List of Special Assignment Operators

=begin html

<table>
  <tr>
    <td>Addition Assignment Operator </td>
    <td>+=</td>
  </tr>
  <tr>
    <td>Subtraction Assignment Operator </td>
    <td>-=</td>
  </tr>
  <tr>
    <td>Multiplication Assignment Operator </td>
    <td>*=</td>
  </tr>
  <tr>
    <td>Division Assignment Operator </td>
    <td>/=</td>
  </tr>
  <tr>
    <td>Remainder Assignment Operator </td>
    <td>%=</td>
  </tr>
  <tr>
    <td>Bit AND Assignment Operator </td>
    <td>&=</td>
  </tr>
  <tr>
    <td>Bit OR Assignment Operator </td>
    <td>|=</td>
  </tr>
  <tr>
    <td>Left Shift Assignment Operator </td>
    <td><<=</td>
  </tr>
  <tr>
    <td>Arithmetic Right Shift Assignment Operator </td>
    <td>>>=</td>
  </tr>
  <tr>
    <td>Logical Right Shift Operator</td>
    <td>>>>=</td>
  </tr>
  <tr>
    <td>Concatenation Operator</td>
    <td>.=</td>
  </tr>
</table>

=end html

The Special Assignment Operator is deployed as follows:

  # Before unexpanding
  LEFT_OPERAND SPECIAL_ASSIGNMENT_OPERATOR RIGHT_OPERAND
  
  # After unwinding
  LEFT_OPERAND ASSIGNMENT_OPERATOR (LEFT_OPERAND TYPE CAST)(LEFT_OPERAND SPECIFIC_OPERATOR RIGHT_OPERAND)

For example, for add assignment Operator, it is expanded as follows:

  # Before unexpanding x is L<"byte Type">
  $x += 1;
  
  # After unwinding
  $x = (byte)($x + 1)

B<Special Assignment Operator Example>

Special Assignment Operator Example

  $x += 1;
  $x -= 1;
  $x *= 1;
  $x /= 1;
  $x &= 1;
  $x |= 1;
  $x ^= 1;
  $x %= 1;
  $x <<= 1;
  $x >>= 1;
  $x >>>= 1;
  $x .= "abc";

=head2 Reference Operator

The Reference Operator is an Operator that retrieves the address of a variable for L<"Numeric Types"> or L<"Multi Numeric Types">. Designed to achieve c address Operator "*".

  \VARIABLE

If the variable is not numeric type or Multi Numeric Types, a compilation error occurs

Reference Operator returns expression. The type returned is L<"Reference Type">.

    B<Reference Operator Example>

  my $num : int;
  my $num_ref : int* = \$num;
  
  my $z : Complex_2d;
  my $z_ref : Complex_2d* = \$z;

For a detailed description of Reference, see L<"Reference">.

=head2 Array Length Operator

The array length operator is an L<Unary Operator|"Unary Operators"> to get the length of the array.

  @OPERAND

The operand must be a L<Expression|"Expressions"> that type is an L<"Array Type">, otherwise a compilation error occurs.

The array length operator returns a L<"int Type"> value that is the length of the L<"Array">.

Array Length Operator returns L<"Expressions">

B<Examples of array length operators:>
  
  # Get the length of the array.
  my $nums = new byte[10];
  my $length = @$nums;

  # Get the length of the array with a scalar operator. This is exactly same as the avobe
  my $nums = new byte[10];
  my $length = scalar @$nums;
  
Note that SPVM does not have the context different from Perl, and array length operators always return the length of the array.

=head2 String Creation Operator

The string creation operator C<new_string_len> is an L<Unary Operator|"Unary Operators"> to create a L<string|"String"> with the length.

  new_string_len OPERAND

The operand must be an L<expression|"Expressions"> that type is a L<"Integral Type"> except for a L<long type|"long Type">, otherwise a compilation error occurs.

The string creation operator returns the string that is created with the lenght.

The return type is a L<string type|"string Type">.

B<Examples of string creation operators:>
  
  # New a string with the length
  my $message = new_string_len 5;

=head2 copy Operator

The C<copy> operator is an L<Unary Operator|"Unary Operators"> to copy the object.

  copy OPERAND

The operand must be an L<expression|"Expressions"> that type is a L<object type|"object Type">, otherwise a compilation error occurs.

If the type of operand is none of a L<string type|"string Type">, a L<numeric type|"Numerci Types">, a L<multi numeric type|"Multi Numeric Types">,
An L<exception|"Exception"> is thorwn.

The C<copy> operator returns the copied object.

The return type is same as the type of operand.

Read-only flag of the string is dropped.

B<Examples of string creation operators:>
  
  # New a string with the length
  my $message = copy "abc";

=head2 is_read_only Operator

The C<is_read_only> is an L<Unary Operator|"Unary Operators"> to check if the L<string|"String"> is read-only.

  is_read_only OPERAND

The operand must be a L<string type|"string Type">, otherwise a compilation error occurs.

If the string is read-only, the C<is_read_only> operator returns C<1>, otherwise returns C<0>.

The return type is an L<int type|"int Type">.

B<Examples of is_read_only operators:>
  
  # New a string with the length
  my $message = "Hello";
  my $is_read_only = is_read_only $message;

=head2 String Length Operator

The string length operator is an L<Unary Operator|"Unary Operators"> to get the length of the string.

  length OPERAND

The operand must be an L<expression|"Expressions"> that type is a L<"string Type">, otherwise a compilation error occurs.

The string length operator returns a L<"int Type"> value that is the length of the L<"String">.

Note that the returned length is byte size, not the count of the characters of the string that is encoded to a specific character set.

B<Examples of string length operators:>
  
  # Get the string length. The result is 5
  my $message = "Hello";
  my $length = length $message;
  
  # Get the string length of UTF-8. The result is 9, not 3
  my $message = "あいう";
  my $length = length $message;

=head2 scalar Operator

The C<scalar> operator is an L<Operator|"Operators"> that returns the value of the operand.

  scalar OPERAND

The operand must be an L<"Array Length Operator">, otherwise a compilation error occurs.

B<Examples of scalar operators:>
  
  # Get the array length 
  my $nums = new int[3];
  foo(scalar @$nums);

  # This is exactlly same as the above.
  my $nums = new int[3];
  foo(@$nums);

Note that the sclara operator exists only to reduce the confusion.

=head2 isweak Operator

isweak Operator is an Operator that checks whether Field is</a>L<"Weaken Reference.">

  isweak VARIABLE->{FIELD_NAME};

The Type of object Expression must be L<"Class Type">. otherwise a compilation error occurs.

Field names must be a existed field names, otherwise a compilation error occurs.

The Type of the value stored in field must be <a href="#language-type-object">Object Type">, otherwise a compilation error occurs.

If the value stored in field at Run Time is</a> L<"Undefined Value, it returns false. This is <a href="#language-expression">Expression">

isweak Operator returns L<"Expressions">

Operator Precidence can be a top priority by using "()".

  #  a * b is the first
  a * b + c
  
  # b + c is the first
  a * (b + c)

=head1 Statements

Statements are the parts of syntax that can be written directly under L<"Scope Blocks">.

=head2 empty Statement

An empty statement is a L<statement|"Statements"> that do nothing and ends with just C<;>.

  ;

=head2 expression Statement

The expression statement is a L<statement|"Statements"> that consisting of an L<expression|"Expressions"> and C<;>.

  Expression;

B<Examples of expression statements:>

  1;
  $var;
  1 + 2;
  foo();
  my $num = 1 + 2;

=head2 if Statement

The C<if> statement is a L<statement|"Statements"> for conditional branching.

  if (CONDITION) {
  
  }

The condition L<"Bool Type Conversion"> is executed and Block is executed if the value is non-zero.

If you want to write more than one condition, you can continue with "elsif Statement". The condition determination is performed from above, and each Expression is L<"Bool Type Conversion"> is executed, and a corresponding Block is executed if the value is non-zero.

  if (CONDITON) {
  
  }
  elsif(CONDITION) {
  
  }

You can use C<else> statement to describe what happens if or if the elsif Statement does not meet the criteria. If the if statement and elsif statement condition determination are all false, the statement inside the elseBlock is executed. Elsif Statement does not have to be.

  if (CONDITION) {
  
  }
  elsif (CONDITION) {
  
  }
  else {
  
  }

B<Examples of if statements:>

  # An example of if Statement.
  my $flag = 1;
  
  if ($flag == 1) {
    print "One \ n";
  }
  elsif ($flag == 2) {
    print "Tow \ n";
  }
  else {
    print "Other";
  }

The C<if> Statement is internally surrounded by an invisible Simple Block.

  {
    if (CONDITION) {
  
    }
  }

C<elsif> is internally expanded into C<if> Statement and C<else> Statement.

  #Before deployment
  if (CONDITION1) {
  
  }
  elsif (CONDITION2) {
  
  }
  else {
  
  }
  
  #After deployment
  if (CONDITION1) {
  }
  else {
    if (CONDITION2) {
  
    }
    else {
  
    }
  }

When a variable is declared in the conditional part of if Statement, it must be surrounded by invisible L<"Simple Block">. Be aware that elsif is internally expanded into if Statement and else Statement.

  #Before deployment
  my $num = 1;
  if (my $num = 2) {
  
  }
  elsif (my $num = 3) {
  
  }
  else {
  
  }
  
  #After deployment
  my $num = 1;
  {
    if (my $num = 2) {
  
    }
    else {
      {
        if (my $num = 3) {
          
        }
        else {
          
        }
      }
    }
  }

=head2 switch Statement

The C<switch> statement is a L<statement|"Statements"> for conditional branching with an integer of L<"int Type"> as a condition. Faster than if Statement if the condition is an integer of L<"int Type"> and there are many branches.

  switch (CONDITION) {
    case constant 1: (
  
      break;
    }
    case constant 2: {
  
      break;
    }
    case constant n: {
      break;
    }
    default: {
  
    }
  }

As the condition Expression, L<"Expressions"> can be specified. L<"Bool Type Conversion"> is executed for the condition Expression.

The constants specified in case Statement are L<"byte Type"> or L<"int Type"> constants. must be. For a constant of L<"byte Type">, type conversion to L<"int Type"> at compile time. Will be done. The value of enumType and Constant Method of L<"int Type"> are constants of L<"int Type">. As it is expanded at the time of syntax analysis, it can be used.

The constants specified in the case statement must not overlap. If there are duplicates, a compilation error occurs

If the value specified in the condition Expression matches the value specified in the case statement, jump to the position of that case statement.

If there is no match and a default statement is specified, jump to the default statement position. If no default statement is specified, switch block will not be executed.

A switch statement requires at least one case statement, otherwise a compilation error will occur.

The default Statement is optional.

Only case statement and default statement can be described directly under switch block.

The case and default Blocks can be omitted.

  switch (CONDITION) {
    case constant 1:
    case constant 2:
    {
      break;
    }
    default:
  }

If you use break Statement, you can exit from the switch block.

  switch (CONDITION) {
    case constant 1: (
      break;
    }
    case constant 2: {
      break;
    }
    case constant n: {
      break;
    }
    default: {
  
    }
  }

If a case Block exists, the last Statement must be a break Statement or a returnl Statement, otherwise a compilation error will occur.

B<Examples of switch statements:>

  # switch statements.
  my $code = 2;
  switch ($code) {
    case 1: {
      print "1 \ n";
      break;
    }
    case 2: {
      print "2 \ n";
      break;
    }
    case 3: {
      print "3 \ n";
      break;
    }
    case 4:
    case 5:
    {
      print "4 or 5 \ n"; {
      break;
    }
    default: {
      print "Other \ n";
    }
  }

=head2 case Statement

The C<case> statement is a L<statement|"Statements"> that can be used in a switch block to specify conditions. For more information on case statements, see the L<"switch Statement"> description.

=head2 default Statement

The C<default> statement is a L<statement|"Statements"> that can be used in the switch block to specify the default condition. For more information on the default Statement, see the L<"switch Statement"> description.

=head2 while Statement

The C<while> statement is a L<statement|"Statements"> for repeating.

  while (CONDITION) {
  
  }

L<"Expressions"> can be described in the condition Expression. L<"Bool Type Conversion"> is executed for condition Expression, and if the value is not 0, Block is executed. Exit the otherwise Block.

B<While Statement Example>

An example of a while Statement.

  my $i = 0;
  while ($i <5) {
  
    print "$i \ n";
  
    $i++;
  }

Inside the while block, you can leave the while block by using L<"last Statement">.

  while (1) {
    last;
  }

Inside a while block, you can use L<"next Statement"> to move to the condition immediately before the next condition Expression.

  my $i = 0;
  while ($i <5) {
  
    if ($i == 3) {
      $i++;
      next;
    }
  
    print "$i \ n";
    $i++;
  }

The while Statement is internally enclosed by an invisible L<"Simple Block">.

  {
    while (CONDITION) {
    $i++;
  }
  
  # 展開後
  my $num = 5;
  {
    while (my $num = 3) {
  
      $i++;
    }
  }

=head2 for Statement

The C<for> Statement is a L<statement|"Statements"> for repeating.

  for (INITIALIZATION_EXPRESSION; CONDITIONAL_EXPRESSION; INCREMENT_EXPRESSION) {
  
  }

L<"Expressions"> can be described in the initialization Expression. Generally, write Expression such as initialization of loop variable. Initialization Expression can be omitted.

Condition Expression, L<"Expressions"> can be described. L<"Bool Type Conversion"> is executed for condition Expression, and if the value is not 0, Block is executed. Exit the otherwise block.

L<"Expressions"> can be described in INCREMENT_EXPRESSION. Generally, Expression of Increment of loop variable is described. INCREMENT_EXPRESSION can be omitted.

for Statement has the same meaning as the following while Statement. INCREMENT_EXPRESSION is executed at the end of Block. Initialization Expression is enclosed in L<"Simple Block">.

  {
    INITIALIZATION_EXPRESSION;
    while (CONDITION) {
  
  
      INCREMENT_EXPRESSION;
    }
  }

B<Exampels fo for statements:>

  # for statements
  for (my $i = 0; $i <5; $i++) {
  
    print "$i \ n";
  }

Inside the for Block, you can exit the for Block using L<"last Statement">.

  for (INITIALIZATION_EXPRESSION; CONDITIONAL_EXPRESSION; INCREMENT_EXPRESSION) {
  
  }

Inside the for Block, you can use L<"next Statement"> to move immediately before the next INCREMENT_EXPRESSION to be executed.

  for (my $i = 0; $i <5; $i++) {
  
    if ($i == 3) {
      next;
    }
  }

=head2 return Statement

The C<return> statement is a L<statement|"Statements"> to get out of the Method. The object assigned to the mortal variable is automatically released.

  return;

If there is a Return Value, L<"Expressions"> can be specified.

  return EXPRESSION;

If the Return Value Type in L<"Method Definition"> is L<"void Type">, Expression Must not exist, otherwise a compilation error occurs.

L<"Method Definition">, if the Return Value Type is other than L<"void Type">, Expression Must match the type of, otherwise a compilation error occurs.

=head2 next Statement

The C<next> statement is a L<statement|"Statements"> to move to the beginning of the next loop block.

  next;

See also L<"while Statement">, L<"for Statement">.

=head2 last Statement

The C<last> statement" is a L<statement|"Statements"> to move to the outside of the loop block.

  last;

See also L<"while Statement">, L<"for Statement">.

=head2 break Statement

The C<break> statement is a L<statement|"Statements"> to move to the outside of the L<switch block|"switch Block">.

  break;

See also L<"switch Statement">.

=head2 warn Statement

The C<warn> statement is a L<statement|"Statements"> to print a warning string to the standard error.

  warn OPERNAD;

The operand must be L<"string Type">.

If the end character of the string is C<\n>, C<warn> statement prints the string itself.

If not, the current file name and current line number are added to the end of the string.

If the value of the operand is an L<undef|"Undefined Value">, print "Warning: something's wrong".

The buffer of the standard error is flushed after the printing.

=head2 die Statement

The C<die> statement is a L<statement|"Statements"> to throw an L<"Exception">.

  die OPERAND;

The operand must be a L<string type|"string Type">, otherwise a compilation error occurs.

The exception thrown by C<die> statement can be cached by an L<eval block|"Exception Catching">
and can be checked by the L<exception variable|"Exception Variable"> C<$@>.

B<Examples of die statements:>
  
  # Catch the exception
  eval {
    # Throw a exception
    die "Error";
  }
  
  # Check the exception
  if ($@) {
    # ...
  }
  
=head2 print Statement

The C<print> statement is a L<statement|"Statements"> to print a L<string|"String"> to the standard output.

  print OPERAND;

The oeprand must be a L<string type|"string Type">.

If the value of the operand is an L<undef|"Undefined Value">, print nothing.

=head2 make_read_only Statement

The C<make_read_only> statement is a L<statement|"Statements"> to make the L<string|"Strings"> read-only.

  make_read_only OPERAND;

The oeprand must be a L<string type|"string Type">.

Read-only strings can't be cast to L<string type|"string Type"> qualified by L<mutable|"mutable Type Qualifier">.

  # A string
  my $string = new_string_len 3;
  
  # Make the string read-only
  make_read_only $string;
  
  # The conversion to the string type qualified by mutable throw an exception.
  my $string_mut = (mutable string)$string;

=head2 weaken Statement

A weaken Statement is a Statement that sets L<"Weaken Reference"> for the Field.

  weaken VARIABLE->{FIELD_NAME};

The Type of the object Expression must be L<"Class Type">, otherwise a compilation error occurs.

Field names must be an existing field names, otherwise a compilation error occurs.

The Type of the value saved in Field must be L<"Object Types">, otherwise a compilation error occurs.

If the value stored in the Field at execution time is L<"Undefined Value">, the weak Statement does nothing.

If the value stored in the Field at runtime is not L<"Undefined Value">, then the following is done:

1. Decrement the Reference Count of the object stored in Field by 1.

2. Set the Weaken Reference flag in Field.

3. Add Field to the back reference of the object saved in Field.

Note that the Weaken Reference flag is set on the Field itself, not on the object stored in the Field.

If the Reference Count of the object saved in Field becomes 0, the Weaken Reference is not created and the object saved in Field is released.

Back Reference is the data of the object saved in Field, and is added to know the Field with the Weaken Reference flag set. There may be more than one.

  # There are multiple back references
  my $foo = new Foo;
  my $bar = new Bar;
  my $baz = new Baz;
  
  $foo->{bar} = $bar;
  $foo->{baz} = $baz;
  
  $bar->{foo} = $foo;
  $baz->{foo} = $foo;
  
  weaken $bar->{foo};
  weaken $baz->{foo};

In the above example, "$bar->{foo}" and "$baz->{foo}" have the Weaken Reference flag set. The object represented by $foo has the back References "$bar->{foo}" and "$baz->{foo}".

The information of the back Reference is necessary because when the L<"Garbage Collection"> is performed, it is necessary to assign the Undefined Value to the Field pointed to by the back Reference.

=head2 unweaken Statement

unweaken Statement is a Statement that cancels L<"Weaken Reference"> for Field.

  unweaken VARIABLE->{FIELD_NAME};

The Type of the object Expression must be L<"Class Type">, otherwise a compilation error occurs.

Field names must be an existing Field names, otherwise a compilation error occurs.

The Type of the value saved in Field must be L<"Object Types">, otherwise a compilation error occurs.

If the value stored in the Field at execution time is L<"Undefined Value">, the unweaken Statement does nothing.

If the value stored in the Field at runtime is not L<"Undefined Value">, then the following is done:

1. Increase the Reference Count of the object stored in the Field by 1.

2. Clear the Weaken Reference flag of Field.

3. Delete the Field from the back reference of the object stored in the Field.

=head1 Types

=head2 The Summary of Types

SPVM is a static type language. All data has a static type.

L<"Local Variable Declaration">, L<"Field Definition">, L<"Class Variable Definition">, and B<Arguments> and B<Return Value> of L<"Method Definition"> must specify B<Type>.

In L<"Local Variable Declaration">, L<"Type Inference"> can be used.

=head2 Type Initial Value

Local Variable Initial Value are described in L<"Class Variable Initial Value">.

A list of Type Initial Value. All Bit columns in the data are set to 0.

=begin html

<table>
  <tr>
    <th>
      <b>Type Name</b>
   </th>
    <th>
      Initial Value
   </th>
  </tr>
  <tr>
    <td>
      <b>byte</b>
    </td>
    <td>
      0
    </td>
  </tr>
  <tr>
    <td>
      <b>short</b>
    </td>
    <td>
      0
    </td>
  </tr>
  <tr>
    <td>
      <b>int</b>
    </td>
    <td>
      0
    </td>
  </tr>
  <tr>
    <td>
      <b>long</b>
    </td>
    <td>
      0
    </td>
  </tr>
  <tr>
    <td>
      <b>float</b>
    </td>
    <td>
      0
    </td>
  </tr>
  <tr>
    <td>
      <b>double</b>
    </td>
    <td>
      0
    </td>
  </tr>
  <tr>
    <td>
      <b>Object Type</b>
    </td>
    <td>
      undef
    </td>
  </tr>
  <tr>
    <td>
      <b>Multi Numeric Types</b>
    </td>
    <td>
      All Field is 0
    </td>
  </tr>
</table>

=end html

=head2 Numeric Types

Numeric Types are L<"Integral Types"> and L<"Floating Point Types">.

=head2 Integral Types

Integral types are the following four types.

=begin html

<table>
  <tr>
    <th>
      <b>Type</b>
   </th>
    <th>
      Description
   </th>
    <th>
      Size
   </th>
  </tr>
  <tr>
    <td>
      <b>byte</b>
    </td>
    <td>
      signed 8-bit integer type
    </td>
    <td>
      1 byte
    </td>
  </tr>
  <tr>
    <td>
      <b>short</b>
    </td>
    <td>
      signed 16-bit integer type
    </td>
    <td>
      2 bytes
    </td>
  </tr>
  <tr>
    <td>
      <b>int</b>
    </td>
    <td>
      signed 32-bit integer type
    </td>
    <td>
      4 bytes
    </td>
  </tr>
  <tr>
    <td>
      <b>long</b>
    </td>
    <td>
      signed 64-bit integer type
    </td>
    <td>
      8 bytes
    </td>
  </tr>
</table>

=end html

See L<"Arithmetic Operators"> for integer calculation.

Note that SPVM has only B<singed> integral types, and doesn't have B<unsigned> integral types.

=head2 byte Type

C<byte> type is a L<"Integral Types"> that represents a signed 8-bit integer. This is the same type as C<int8_t> type of C language.

=head2 short Type

C<short> type  is a L<"Integral Types"> that represents a signed 16-bit integer. This is the same type as C<int16_t> type of C language.

=head2 int Type

C<int> type is  is a L<"Integral Types"> that represents signed 32-bit integer. This is same as C<int32_t> type of C language.

=head2 long Type

C<long> type is a L<"Integral Types"> that represents a signed 64-bit integer. This is the same type as C<int64_t> type of C language.

=head2 Floating Point Types

B<Floating Point Types> are the following two.

=begin html

<table>
  <tr>
    <th>
      <b>Type</b>
    </ th>
    <th>
      Description
    </ th>
    <th>
      Size
    </ th>
  </tr>
  <tr>
    <td>
      <b>float</b>
    </td>
    <td>
      Single precision (32bit) floating point type
    </td>
    <td>
      4 bytes
    </td>
  </tr>
  <tr>
    <td>
      <b>double</b>
    </td>
    <td>
      Double precision (64bit) floating point type
    </td>
    <td>
      8 bytes
    </td>
  </tr>
</table>

=end html

See L<"Arithmetic Operators"> for floating-point calculation.

=head2 float Type

C<float> type is a L<"Floating Point Types"> that represents a single precision(32bit) floating point. This is the same type as C<float> type of C language.

=head2 double Type

C<double> type is a L<"Floating Point Types"> that represents a double precision(64bit) floating point. This is the same type as C<double> type of C language.

=head2 Class Type

Class Type is the type defined by L<"Class Definition">.

  class Foo {
  
  }

Class Type is L<"Class Type"> L<"Callback Type"> <a href = "#language-type It consists of -multi-numeric ">Multi Numeric Types</a>.

  # Class Type
  class Foo {
  
  }
  
  # Callback Type
  class Foo: callback_t {
  
  }
  
  # Multi Numeric Types
  class Foo: mulnum_t {
  
  }

L<"Pointer Type"> is also Class Type, so Pointer Type will also be Class Type.

  # Pointer Type
  class Foo: pointer_t {
  
  }

=head2 Object Types

Object types are L<"Class Type">, L<"Callback Type">, L<"Array Type">, L<"string Type">, L<"Any Object Type">.

The value of a object type can be assigned to a any object type.

  my $object: object = new Foo;
  my $object: object = new Foo [];
  my $object: object = "abc";

=head2 Numeric Object Type

B<Numeric Object Type> are the following six.

=begin html

<table>
  <tr>
    <th>
      <b>Type</b>
   </th>
    <th>
      Description
   </th>
  </tr>
  <tr>
    <td>
      Byte
    </td>
    <td>
      Numeric Object Type with L<"byte Type"> data
    </td>
  </tr>
  <tr>
    <td>
      Short
    </td>
    <td>
      Numeric Object Type with L<"short Type"> data
    </td>
  </tr>
  <tr>
    <td>
      Int
    </td>
    <td>
      Numeric Object Type with L<"<a href="#language-type-int">int Type"></a> data
    </td>
  </tr>
  <tr>
    <td>
      Long
    </td>
    <td>
      Numeric Object Type with L<"long Type"> data
    </td>
  </tr>
  <tr>
    <td>
      Float
    </td>
    <td>
      Numeric Object Type with L<"float Type"> data
    </td>
  </tr>
  <tr>
    <td>
      Double
    </td>
    <td>
    Numeric Object Type with L<"double Type"> data
    </td>
  </tr>
</table>

=end html

For the conversion between L<"Numeric Types"> and B<Numeric Object Type>, see L<"Type Conversions">.

=head2 Undefined Type

Undefined Type is the type that L<"Undefined Value"> has. It cannot be used explicitly.

The only Undefined Type value is L<"Undefined Value">.

The value of Undefined Type can be assigned to Object Type.If you assign to another Type, a compilation error occurs

=head2 Class Type

Class Type is the type defined by L<"Class Definition"> and is not "Multi Numeric Types" "Callback Type".

  packag Foo {
  
  }

Class Type can create objects by new Operator.

  my $foo = new Foo;

Class Type is a L<"Object Types">.

Class Type is a L<"Class Type">.

L<"Pointer Type"> is the Class Type.

=head2 Pointer Type

Pointer Type is the one that "pointer_t Descriptor" is specified in L<"Class Definition">.

  class Foo: pointer_t {
  
  }

Pointer Type is a type of Class Type.

Pointer type data can store C language pointers.

Field cannot be defined for Pointer Type. If it is defined, a compilation error occurs

=head2 Callback Type

Callback Type is a L<"Class Type"> with L<"Class Descriptors"> "callback_t".

  class Comparator: callback_t {
    method: int ($x1: object, $x2: object);
  }

Callback Type is designed to provide a feature corresponding to Function Pointer in C language.

Callback Type must have only one L<"Method Definition">. Method must be L<"Method">.

Method names of Callback Type must be anonymouse.

Callback Type must not have any L<"Field Definition"> and L<"Class Variable Definition">.

Callback Type is a L<"Object Types">.

Callback Type cannot be the operand of L<"new Statement">.

The variable of Callback Type can be assigned a L<"Class Type"> object that matches the Callback Type. "Matches the Callback Type" means the following two cases.

1. Class Type object with anonimouse name and the L<"Signature"> is same as Callback Type

  # Callback Type Definition
  class Comparator: callback_t {
    method: int ($x1: object, $x2: object);
  }
  
  # Class Definition
  class SomeComparator {
    static method new: int () {
      return new SomeComparator;
    }
  
    method: int ($x1: object, $x2: object) {
  
    }
  }
  
  # The object can be assign to the variable of Callback Type
  my $comparator: Comparator = SomeComparator->new;

2. Class Type object which is created by L<"Create Callback Object"> and the L<"Signature"> is same as Callback Type.

  Definition of #Callback Type
  class Comparator: callback_t {
    method: int ($x1: object, $x2: object);
  }
  
  # The object which is created by Create Callback Object can be assign to the variable of Callback Type
  my $comparator : Comparator = method: int ($x1: object, $x2: object) {
  
  }

=head2 Any Object Type

Any Object Type is represented by "object". Designed to represent the "void *" Type in C.

  my $object: object;

You can methodstitute the value of "Object Types" for Any Object Type.

  my $object: object = new Foo;
  my $object: object = "abc";
  my $object: object = new Foo [3];

=head2 self Type

self Type represents the Class Type to which it belongs, and indicates that the argument is Invocant.

  self

It can only be used as the type of the first argument in L<"Method Definition">.

=head2 void Type

B<void Type> is a special Type that can only be used in the return type of L<"Method Definition"> and indicates the Method has no Return Value.

  void

=head2 Basic Type

A Type that does not have dimensions is called a Basic Type. L<"Numeric Types">, L<"Class Type </ a>, <a href = "#language-type- any-object ">Any Object Type">, L<"string Type"> is a Basic Type.

=head2 Array Type

Array Type represents multiple continuous data areas. L<"Basic Type"> can be an Array.

  int[]
  double[]
  Point[]
  object[]
  string []

Array has dimensions and can express up to 255 dimensions.

  # Two dimensions
  int[] []
  
  # Three-dimensional
  int[] [] []

Array Type is L<"Object Types">.

Use new Operator to create an Array. In the following example, L<"int Type"> Array with 3 elements is created.

my $nums = new int [3];

You also use new Operator when creating a multidimensional Array.The following example creates an Array of int[] Type with 3 elements.

my $nums = new int[] [3];

=head2 Numeric Array Type

Numeric Array Type means L<"Numeric Types"> with the element L<"Array Type"> It is.

B<Numeric Array Type list>

=begin html

<ul>
  <li>
    byte[]
  </li>
  <li>
    short[]
  </li>
  <li>
    int[]
  </li>
  <li>
    long[]
  </li>
  <li>
    float[]
  </li>
  <li>
    double[]
  </li>
</ul>

=end html

Data represented by Numeric Array Type must have elements whose size is L<"Numeric Types">, and must be consecutive by the number of Array Length.

All elements of Numeric Array Type are initialized by L<"Type Initial Value"> when Create Array is performed.

=head2 byte[] Type

In SPVM, the L<"byte[] Type"> is a special Type in that it is L<"string Type">.

  byte[]

L<"string Type"> is treated as L<"string Type"> at compile time, but at runtime It will be L<"byte[] Type">.

=head2 Object Array Type

Object Array Type is L<"Array Type"> that has the value of L<"Object Types"> as an element. It is.

B<Object Array TypeのExample>

=begin html

<ul>
  <li>
    Foo[]
 </li>
  <li>
    Foo[][]
 </li>
  <li>
    Comparable[]
 </li>
  <li>
    object[]
 </li>
</ul>

=end html

The data represented by Object Array Type must have elements of size of L<"Object Types"> and consecutive by the number of Array Length.

All elements of Object Array Type are initialized by L<"Type Initial Value"> when Create Array is performed.

=head2 Multi Numeric Array Type

Multi Numeric Array Type means L<"Array Type that has the value of <a href="#language-type-multi-numeric">Multi Numeric Types"> as an element.</a>.

B<Multi Numeric Array Type Example>

=begin html

<ul>
  <li>
    Complex_2d[]
 </li>
  <li>
    Complex_2f[]
 </li>
</ul>

=end html

Data represented by Multi Numeric Array Type must have elements whose size is L<"Multi Numeric Types"> and must be contiguous with the number of Array Length ..

All elements of Multi Numeric Array Type are initialized by L<"Type Initial Value"> when Create Array is performed.

=head2 Any Object Array Type

Any Object Array Type is an arbitrary L<"Object Types"> expressed as an oarray as an element. A Type that can be assigned the value of array ">Array Type</a>. Any Array Type can be cast to void * Type and passed to the first argument of the C language qsort function, but Any Object Array Type is not designed to realize the function corresponding to this. It was

  my $array : oarray = new Point[3];
  my $array : oarray = new object[3];

If a value with a Type other than Object Type is assigned, a compilation error occurs

Note that "oarrayType" is a different Type than "object[] Type". While oarrayType is a Type that can be methodstituted with an arbitrary Array Type value that has an Object Type value as an element, "object[] Type" is a Type that represents an "Array that has an objectType value as an element". Therefore, the value of arbitrary Array Type cannot be assigned.

Any Object Array Type is L<"Array Type">. L<"Array Length Operator"> to get length, L<"Set Array Element">, L<"Get Array Element">.

  my $array : oarray = new Int[3];
  
  # Get the length of the element of Any Object Array Type
  my $length = @$array;
  
  # Get the value of any object array type element
  my $num = (Int)$array->[0];
  
  # Setting the value of the element of Any Object Array Type
  $array->[0] = Int->new(5);

When setting the value of the element of Any Object Array Type, a check is made at runtime whether the type of the element is smaller than the type Dimension of Array by 1. If the check fails, L<"Exception"> will occur. Any Object Array Type guarantees runtime Type safety.

=head2 string Type

C<string> type is a L<"Types"> that represents a L<"String">.

  string

C<string> type can be qualified L<"mutable Type Qualifier">.

  mutable string

B<Examples:>
  
  # string type
  my $message : string;
  my $message : mutable string;

=head2 Multi Numeric Types

Multi Numeric Types are a type that can represent continuous numerical values.

Multi Numeric Types can be defined by specifying "mulnum_t" Descriptor in L<"Class Definition">.

  class Point_3i : mulnum_t {
    has x : int;
    has y : int;
    has z : int;
  }

See L<"Values ​​"> for a detailed explanation of Multi Numeric Types.

=head2 Reference Type

Reference Type is a Type that can store the address of a variable. Add "*" after L<"Numeric Types"> or L<"Multi Numeric Types"> You can define it.

  my $num : int;
  my $num_ref : int* = \$num;
  
  my $point : Point_3i;
  my $point_ref : Point_3i* = \$point;

Only the address of the Local Variable acquired by L<"Reference Operator"> can be assigned to the value of Reference Type.

If only Local Variable Declaration of Reference Type is performed, a compilation error occurs

Reference Type can be used as Type of L<"Local Variable Declaration">. The address of the Local Variable must be stored by the Reference Operator. In case of only Local Variable Declaration, a compilation error occurs

Reference Type can be used as Type of argument in L<"Method Definition">.

Reference Type cannot be used as Return Value Type in L<"Method Definition">.

Reference Type cannot be used as the type of Field in L<"Class Definition">.

Reference Type cannot be used as the type of Class Variable in L<"Class Definition">.

If the Reference Type is used at an Invalid location, a compilation error occurs

See L<"Reference"> for a detailed explanation of Reference.

=head2 Numeric Reference Type

Numeric Reference Type means L<"Numeric Types"> for L<"Reference Type">. Says.

=head2 Multi Numeric Reference Type

Multi Numeric Reference Type means L<"Reference Type"> for L<"Multi Numeric Types"> variables. > Means.

=head1 Type Inference

Omitting L<"Types"> when L<"Local Variable Declaration"> by Type Inference can. Type Inference is always performed by the type on the Right side of Assignment Operator.

  # int
  my $num = 1;
  
  # double
  my $num = 1.0;
  
  # Foo
  my $foo = new Foo;

=head1 Type Conversions

=head2 Type Cast

Type Cast is Type Conversion that is explicitly described.

  # Type Cast
  (TYPE)EXPRESSION

L<"int Type"> value is converted to L<"long Type"> Become.

  my $num = (long)3;

ype Cast returns L<"Expressions">.

If the source Type and the specified Type are the same, the value is simply copied.

  my $num : int = (int)4;

B<List of Type Conversion in Type Cast>

It is a list of Type Conversion in Type Cast. If a Type Cast not listed in this table is performed, a compilation error occurs.

=begin html

<table>
  <tr>
    <th>
      <b>The specified Type</b>
   </th>
    <th>
      <b>Source type</b>
   </th>
    <th>
      Content of conversion
   </th>
  </tr>
  <tr>
    <td>
      <b>byte[]</b>
    </td>
    <td>
      <b>string</b>
    </td>
    <td>
      The address value is copied.
    </td>
  </tr>
  <tr>
    <td>
      <b>string</b>
    </td>
    <td>
      <b>byte[]</b>
    </td>
    <td>
      The address value is copied.
    </td>
  </tr>
  <tr>
    <td>
      <b>Numeric Types</b>
    </td>
    <td>
      <b>Numeric Types</b>
    </td>
    <td>
      L<"Numeric Types Conversion"> is performed.
    </td>
  </tr>
  <tr>
    <td>
      <b>Numeric Object Type</b>
    </td>
    <td>
      <b>Numeric Types</b>
    </td>
    <td>
      L<"Boxing Type Conversion"> is performed. Numeric Types represented by Numeric Types and Numeric Object Type must be the same. For example, if Numeric Types are int, Numeric Object Type must be Int Type.
    </td>
  </tr>
  <tr>
    <td>
      <b>Any Object Type</b>
    </td>
    <td>
      <b>Numeric Types</b>
    </td>
    <td>
      L<"Boxing Type Conversion"> is performed.
    </td>
  </tr>
  <tr>
    <td>
      <b>Numeric Types</b>
    </td>
    <td>
      <b>Numeric Object Type</b>
    </td>
    <td>
      L<"Unboxing Type Conversion"> is performed. Numeric Types represented by Numeric Types and Numeric Object Type must be the same. For example, if Numeric Types are int, Numeric Object Type must be Int Type.
    </td>
  </tr>
  <tr>
    <td>
      <b>Numeric Types</b>
    </td>
    <td>
      <b>Any Object Type</b>
    </td>
    <td>
      L<"Unboxing Type Conversion"> is performed.
    </td>
  </tr>
  <tr>
    <td>
      <b>string Type</b>
    </td>
    <td>
      <b>Numeric Types</b>
    </td>
    <td>
      The number is converted to a string using the "%g" format of the C standard sprintf function.
    </td>
  </tr>
</table>

=end html

=head2 Implicit Type Conversion

Implicit type conversion is automatic type conversion performed by SPVM. The following are the places where implicit Type Conversion may occur.

=begin html

<ul>
  <li>When assigning to a different Type</li>
  <li>When passing to Method Arguments of different Type</li>
  <li>When returning a Type different from Return Value</li>
</ul>

=end html

Implicit Type Conversion occurs when:

=head3 Implicit Widening Type Conversion

If both the source and destination Type are Numeric Types and the destination Type is greater than the source Type, L<"Numeric Widening Type Conversion"> is done.

  # Implicit Widening Type Conversion
  my $num : long = 123;
  my $num : double = 12.5f;

=head3 Implicit Narrowing Type Conversion

Both the source and destination Type are Numeric Types, and the destination Type is smaller than the source Type, and the source value can be expressed in the range of Integer Literal and destination Type value. L<"Numeric Narrowing Type Conversion"> is performed.

  # Implicit Narrowing Type Conversion
  my $num : byte = 123;
  my $num : short = 134;

=head3 Implicit Numeric Type to Any Object Conversion

If the source Type is Numeric Types and the destination Type is Any Object Type, L<"Boxing Type Conversion"> to the corresponding Numeric Object Type Is done. In the following case, the converted Int Type object is assigned to the generic object.

  # Implicit Boxing Type Conversion to objectType
  my $num = 123;
  my $object : object = $num;

=head3 Implicit Numeric Type to Numeric Object Type Conversion

When the source Type is Numeric Types and the destination Type is the corresponding Numeric Object Type, L<"Boxing Type Conversion"> to the corresponding Numeric Object Type a> is done.

  # Implicit Boxing Type Conversion to object Type
  my $num = 123;
  my $object : Int = $num;

When the source Type is Any Object Type and the destination Type is Numeric Types, L<"Unboxing Type Conversion"> in the corresponding Numeric Types are displayed. Will be opened. In the following case, an attempt is made to convert the Int Type object to L<"int Type">.

=head3 Implicit Numeric Object Type to Numeric Type Conversion

  # Implicit Unboxing Type Conversion from objectType-
  my $object : object;
  my $num : int = $object;

If the source Type is Numeric Object Type and the destination Type is the corresponding Numeric Types, L<"Unboxing Type Conversion"> in the corresponding Numeric Types Is done.

  # Implicit Unboxing Type Conversion from Numeric Object Type
  my $num_obj = Int->new(3);
  my $num : int = $num_obj;

=head3 Implicit Numeric Type to string Type Conversion

If the source Type is Numeric Types and the destination Type is L<"string Type">, <a href = "#language-type-convertion-numeric-to-string ">Numeric-to-string Type Conversion</a> is performed. In the following case, the numerical value "123" is converted to String "" 123 "" and assigned.

  # Implicit Boxing Type Conversion to string Type
  my $num = 123;
  my $str : string = $num;

=head2 Numeric Types Conversion

Numeric Types Conversion is the conversion from L<"Numeric Types"> to L<"Numeric Types">.

Numeric Types Conversion performs exactly the same processing as Numeric Types Conversion in the corresponding C language. For example, Type Conversion from int to long in SPVM is the same as the type conversion from int32_t Type to int64_t Type in C language.

  # SPVM conversion
  my $src : int = 5;
  my $dist = (long)$src;
  
  # Correspondence in C language
  int32_t src = 5;
  int64_t dist = (int64_t)src;

SPVM has two Numeric Types Convertions.

There are some rules for automatic type conversion of Numeric Types.

=begin html

<ul>
  <li>L<"Unary Numeric Widening Type Conversion"></li>
  <li>L<"Binary Numeric Widening Type Conversion"></li>
</ul>

=end html

Numeric types have an order.

=begin html

<ul>
  <li>L<"Numeric Types Order"></li>
</ul>

=end html

=head2 Numeric Types Order

L<"Numeric Types"> has the order of Type. The order of Type is "byte", "short", "int", "long", "float", "double" from the smallest.

=head2 Unary Numeric Widening Type Conversion

Unary Numeric Widening Type Conversion means that L<"Expressions"> is L<"byte Type"> or short Type. In this case, perform L<"Numeric Widening Type Conversion"> to L<"int Type"> I say that.

Unary Numeric Widening Type Conversion is performed in the following cases.

=begin html

<ul>
  <li>Array Index</li>
  <li>Dimension when creating Array</li>
  <li>Unary Plus Operator operands</li>
  <li>Unary Minus Operator operands</li>
  <li>Left and the right operands of Shift Operator "<<" ">>" ">>>"</li>
</ul>

=end html

=head2 Binary Numeric Widening Type Conversion

Binary Numeric Widening Type Conversion is performed to the left operand and the right operand in Binary Operator that takes Numeric Types on the Left and Right sides. L<"Numeric Widening Type Conversion">.

The following rules apply.

1. When one Expression is L<"double Type">, the other Type is L<"double Type"> Is converted to>.

2. If one Expression is L<"float Type">, the other Type is L<"float Type"> Is converted to>.

3. When one Expression is L<"long Type">, the other Type is L<"long Type"> Is converted to>.

4, otherwise, it will be converted to L<"int Type">.

Binary Numeric Widening Type Conversion is performed in the following cases.

=head2 Numeric Narrowing Type Conversion

Numeric Narrowing Type Conversion is a conversion rule applied when converting from a large type to a small type in L<"Numeric Types">.

=head2 Numeric Widening Type Conversion

Numeric Widening Type Conversion is a conversion rule applied when converting from a small type to a large type in L<"Numeric Types">.

=head2 Numeric to string Type Conversion

The numerci to string type conversion is a L<type conversion|"Type Conversions"> from a L<numeric type|"Numeric Types"> to a L<string type|"string Type"">.

  # Numeric to string type conversion
  my $byte = (byte)1;
  my $short = (short)2;
  my $int = 3;
  my $long = 4L;
  my $float = 2.5f;
  my $double = 3.3;
  
  # The string is "1".
  my $string_byte = (string)$byte;
  
  # The string is "2".
  my $string_short = (string)$short;

  # The string is "3".
  my $string_int = (string)$int;

  # The string is "4".
  my $string_long = (string)$long;
  
  # The string is "2.5"
  my $string_float = (string)$float;
  
  # The string is "3.3"
  my $string_double = (string)$double;

=head2 string to byte[] Type Conversion

string to byte[] type conversion is a L<"Type Conversions"> from L<"string Type"> to L<"byte[] Type">.

  # string to byte[] Type Conversion
  my $string : string = "Hello";
  my $bytes : byte[] = (byte[])$string;

A new byte[] object is created and all characters in the string are copied to the elements of byte[] object.

=head2 byte[] to string Type Conversion

byte[] to string type conversion is a L<"Type Conversions"> from L<"byte[] type"> to L<"string Type">.

  # byte[] to string type conversion
  my $bytes : byte[] = new byte[3];
  $bytes->[0] = 'a';
  $bytes->[1] = 'b';
  $bytes->[2] = 'c';
  my $string : string = (string)$bytes;

A new string is created and all elements in the byte[] object are copied to the characters of the string.

=head2 Boxing Type Conversion

Boxing Type Conversion is the operation to convert the value of Numeric Types to Numeric Object Type.

=head2 Unboxing Type Conversion

Unboxing Type Conversion is an operation to convert the value of Numeric Object Type to the corresponding value of Numeric Types.

=head2 Bool Type Conversion

Bool Type Conversion is a conversion applied in the conditional part of if Statement, etc. for True/False Value judgment.

B<Where Bool Type Conversion takes place>

B<Inside the if statement braces>

  if (CONDITION) {
  
  }

B<In unless statement brackets>

  unless (CONDITION) {
  
  }

B<The second in the parentheses for>

  for (INITIALIZEATION;CONDITION;NEXT_VALUE;) {
  
  }

B<in parentheses while>

  while (CONDITION) {
  
  }

B<Left and Right of Logical AND Operator>

  CONDITION && CONDITION

B<Left and Right of Logical OR Operator>

  CONDITION || CONDITION

B<Right side of Logical NOT Operator>

  !CONDITION

Expression specified by Bool Type Conversion is L<"Numeric Types"> or L<"Object Types"> or It must be L<"Undefined Type">, otherwise a compilation error occurs.

Return Value of Bool Type Conversion is Expression of L<"int Type">.

If Expression is L<"Undefined Value">, 0 is returned.

If Expression is Bool->FALSE, 0 is returned. This is special case of the object of Bool class. false keywords means Bool->FALSE.

If Expression is Bool->TRUE, 1 is returned.  This is special case of the object of Bool class. true keywords means Bool->TRUE.

When Expression is L<"Numeric Types">, L<"Unary Numeric Widening Type Conversion"> is done.

If Expression is L<"int Type">, that value is returned.

Expression is L<"long Type">, L<"float Type">, <a href = "#language- If it is type-double ">double Type</a>, Object Type, the operation that exactly same as the following operation in C language is performed and the result is returned.

  !!x

If Expression is Object Type, 0 is returned if it is Undefined Value, 1 otherwise.

B<Bool Type Conversion Examples>

  if (1) {
    # run
  }
  
  if (0) {
    # not run
  }
  
  if (1.5) {
    # run
  }
  
  if (0.0) {
    # not run
  }
  
  if (true) {
    # run
  }
  
  if (Bool->TRUE) {
    # run
  }
  
  if (false) {
    # not run
  }
  
  if (Bool->FALSE) {
    # not run
  }
  
  my $object = SPVM::Int->new(1);
  
  if ($object) {
    # run
  }
  
  if (undef) {
    # not run
  }

=head1 Type Qualifiers

Type qualifiers qualify the type.

  QUALIFIER TYPE

=head2 mutable Type Qualifier

The C<mutable> type qualifier is used to allow to set the character of the string.

  my $string : mutable string;

B<Examples:>
  
  # Mutable string
  my $message = (mutable string)"abc";
  $message->[0] = 'd';

=head1 Exception

=head2 Exception overview

SPVM has a mechanism of Exception. Exception consists of raising L<"Exception"> and catching the exception.

=head2 Throw Exception

Use L<"die Statement"> to throw L<"Exception">.

  die EXPRESSION;

When the die statement is executed, the stack trace and the String specified by Expression are displayed, and the program ends. The stack trace includes class names, Method names, File Name and line number. File Name is a relative File Name from the path where Module is loaded.

  Error
  from TestCase::Minimal->sum2 at SPVM/TestCase/Minimal.spvm line 1640
  from TestCase->main at SPVM/TestCase.spvm line 1198

=head2 Exception Catching

Exception catching is a function that can stop the program from ending and get an error message when L<"Exception"> is thrown.

Exceptions are caught using eval Block Statement. Please note that the eval Block Statement requires a semicolon at the end.

  eval {
    # Processing that may throw L<"Exception">
  };

When L<"Exception"> is caught by the eval Block, the program termination is stopped and L<"is added to <a href="#language-exception-var">Exception Variable">. The message specified in Exception is thrown</a> is methodstituted.

=head2 Exception Variable

B<Exception Variable> is a global variable that is represented by "B<$@>"

  $@

See L<"Set Class Variable"> to get Exception Variable Value.

See L<"Set Exception Variable"> to set Exception Variable Value.

=head1 Garbage Collection

The object is released from memory when the Reference Count reaches 0.

If the object is an Array that has Object Type values ​​as elements, the Reference Count of all Array elements that are not Undefined Value is decremented by 1 before Garbage Collection

When an object is a Class Type and has a Field of Object Type, the Reference Count of the objects owned by all Fields of Object Type that are not Undefined Value is decremented by 1 before Garbage Collection. If Weaken Reference is set to the object saved in Field, Weaken Reference is released before Reference Count is decremented by 1.

When the object has Back references of Weaken Reference, Undefined Value is assigned to all Fields registered as back References and all back References are deleted.

The above process is done recursively.

=head1 Callback

Callback Type in SPVM is a Class Type in which only one unnamed Method with no implementation is defined. If callback_tDescriptor is specified in L<"Class Definition">, it becomes Callback Type.

The purpose of Callback Type is to provide a Type that can be assigned to different objects when they have the same MethodDefinition. Consider that the function corresponding to the C function pointer is realized in SPVM.

  class Foo1 {
    static method new : Foo1 () {
      new Foo1;
    }
    method : int ($num : int) {
      return 1 + $num;
    }
  }
  
  class Foo2 {
    static method new : Foo2 () {
      new Foo2;
    }
    method : int ($num : int) {
      return 2 + $num;
    }
  }
  
  class FooCallback : callback_t {
  method : int ($num : int);
  }

Foo1 and Foo2 have the same MethodDefinition "method: int ($num: int)". Now suppose you want to selectively call the Foo1 or :Foo2 Method.

In this case, if you define a Callback Type FooCallback with the same MethodDefinition, you can assign either object to this Type. Then you can call Method from this object.

  my $foo1 = Foo1->new;
  my $foo2 = Foo2->new;
  
  my $foo : FooCallback;
  
  my $flag = 1;
  if ($flag) {
    $foo = $foo1;
  }
  else {
    $foo = $foo2;
  }
  
  my $ret = $foo->(5);

If $flag is 1, the anonymous Method of Foo1 is called, otherwise the anonymous Method of Foo2 is called.

For more information on Callback Type, see L<"Callback Type">.

=head2 Create Callback Object

Create Callback Object is a Syntax that creates an object that conforms to Callback Type by using a special syntax for the purpose of Callback.

  method : TYPE_NAME  (ARGS1 : TYPE1, ARGS2 : TYPE2, ARGSN : TYPEn) {
  
  }

When Create Callback Object is performed, L<"Class Definition"> is performed internally, an object based on that Class is generated, and <a href = " Returned as # language-expression ">Expression</a>. It is possible to assign to a variable like the following.

  my $cb_obj = method : TYPE (ARGS1 : TYPE1, ARGS2 : TYPE2, ..., ARGSn : TYPEn) {
  
  };

Method defined by Create Callback Object must be L<"Method">. It must also be a Method with no name.

B<Create Callback Object Example>

  my $comparator = method : int ($x1 : object, $x2 : object) {
  
  }

You can call Method because the object created by Create Callback Object is a normal object. For the call to Create Callback Object, see L<"Method Call">.

=head2 Capture

In Create Callback Object, you can use the syntax called Capture to use the variables defined outside the Method defined by Create Callback Object inside the Method defined by Create Callback Object.

  # Capture
  [VariableName1 : Type1, VariableName2 : Type2] method MethodNames : int ($x1 : object, $x2 : object) {
  
  };

Capture Example.

  my $foo = 1;
  my $bar = 5L;
  
  my $comparator = [$foo : int, $bar : long] method : int ($x1 : object, $x2 : object) {
  
    print "$foo\n";
    print "$bar\n";
  }

The variable name used in Capture must be the one with "$" added at the beginning of L<"Field Names">.

The Capture is actually defined as a Field of Class. Capture is a field definition and value setting syntax sugar.

If L<"Local Variable"> with the same name as the Capture variable exists in the Scope, access the Local Variable.

If there is a L<"Class Variable"> with the same name as the Capture variable, access the Capture variable.

If you write Create Callback Object and Capture without using syntax sugar, it will be as follows.

  class ComapartorImpl {
    has foo : int;
    has bar : long;
  
    method : int ($x1 : object, $x2 : object) {
      print $self->{foo} . "\n";
      print $self->{bar} . "\n";
    }
  }

  my $foo = 1;
  my $bar = 5L;
  
  my $comparator = new ComparatorImpl;
  
  $comparator->{foo} = $foo;
  $comparator->{bar} = $bar;

Capture is a syntax for writing such a long description short.

=head1 Weaken Reference

Weaken Reference is a reference that does not increase the Reference Count. Weaken Reference can be used to solve the problem of circular references.

SPVM has GC of Reference Count Type. In the GC of Reference Count Type, the object is automatically released when the Reference Count becomes 0, but when the circular reference occurs, the Reference Count does not become 0 and the object is automatically released. not.

This is an Example when the Field of the object is circularly referenced.

  {
    my $foo = new Foo;
    my $bar = new Bar;
  
    $foo->{bar} = $bar;
    $bar->{foo} = $foo;
  }

In this case, both objects are not released when the Scope ends. This is because a circular reference has occurred and the Reference Count does not become 0.

Weaken Reference is a function to correctly destroy objects when a circular reference occurs in a programming language that has a Reference Count GC.

In such a case, it is possible to release correctly by setting one Field to Weaken Reference using L<"weaken Statement">.

  {
    my $foo = new Foo;
    my $bar = new Bar;
  
    $foo->{bar} = $bar;
    $bar->{foo} = $foo;
  
    weaken $foo->{bar};
  }

Before the weaken statement is executed, $foo has a Reference Count of 2 and $bar has a Reference Count of 2.

If there is no weaken statement, the reference count of $foo and the reference count of $bar will not be 0 and will not be released even if the scope ends.

When a weaken statement is executed, $foo has a Reference Count of 2 and $bar has a Reference Count of 1.

When the Scope ends, the Reference Count of $bar is decremented by 1 and becomes 0, so it is released correctly.

Even if there are 3 circular references, you can release them correctly by setting Weaken Reference in 1 Field.

  {
    my $foo = new Foo;
    my $bar = new Bar;
    my $baz = new Baz;
  
    $foo->{bar} = $bar;
    $bar->{baz} = $baz;
    $baz->{foo} = $foo;
  
    weaken $foo->{bar};
  }

As a syntax related to Weaken Reference, Weaken Reference can be released L<"weaken Statement">, and it can be confirmed whether Field is Weaken Reference <a href = "#language- There is an operator-isweak ">isweak Operator</a>.

=head1 Default Loaded Modules

SPVM loads the following modules just after the program start. These modules are deeply relataed to SPVM language, such as L<type conversions|"Type Conversions">.

=begin html

<ul>
  <li><a href="https://metacpan.org/pod/SPVM::Byte">Byte</a></li>
  <li><a href="https://metacpan.org/pod/SPVM::Short">Short</a></li>
  <li><a href="https://metacpan.org/pod/SPVM::Int">Int</a></li>
  <li><a href="https://metacpan.org/pod/SPVM::Long">Long</a></li>
  <li><a href="https://metacpan.org/pod/SPVM::Float">Float</a></li>
  <li><a href="https://metacpan.org/pod/SPVM::Double">Double</a></li>
  <li><a href="https://metacpan.org/pod/SPVM::Bool">Bool</a></li>
</ul>

=end html
