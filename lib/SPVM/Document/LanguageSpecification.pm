=encoding utf8

=head1 NAME

SPVM::Document::LanguageSpecification - SPVM Language Specification

=head1 DESCRIPTION

B<SPVM::Document::LanguageSpecification> defines SPVM language specification.

=head1 Tokenization

The tokenizing the source codes of SPVM language is explained.

=head2 Character Set

The source codes of SPVM language are written by C<UTF-8>.

=head2 Line Terminators

The line terminators are C<LF>, C<CR>, and C<CRLF> of ASCII.

When a line terminator appears, the current line number is incremented by C<1>. The line terminator is converted to C<LF> of ASCII.

=head2 Space Characters

Space characters are C<SP>, C<HT>, C<FF> of ASCII and the L<line terminators|/"Line Terminators">.

=head2 Word Characters

The word characters are alphabet(C<a-zA-Z>), number(C<0-9>), and underscore(C<_>) of ASCII.

=head2 Symbol Name

A symbol name is the characters that are composed of L<word characters|/"Word Characters"> and C<::>.

A symbol name can't contains C<__>, and can't start with a number C<0-9>.

A symbol name can't start with C<::>, and can't end with C<::>.

A symbol name can't contains C<::::>, and can't start with a number C<0-9>.

  # Symbol names
  foo
  foo_bar2
  Foo::Bar
  
  # Invalid symbol names
  2foo
  foo__bar
  ::Foo
  Foo::
  Foo::::Bar

=head2 Class Name

A class name is a L<symbol name|/"Symbol Name">.

The part names of a class name must start uppercase letter. If the class name is C<Foo:Bar::Baz>, part names are C<Foo>, C<Bar>, and C<Baz>.

A class name must be corresponding to the relative name of the module file. If the class name is C<Foo::Bar::Baz>, the relative name of the module file must be C<Foo/Bar/Baz.spvm>.

If class names are invalid, a compilation error will occur.

B<Examples:>
  
  # Class names
  Foo
  Foo::Bar
  Foo::Bar::Baz3
  Foo::bar
  Foo_Bar::Baz_Baz

  # Invalid class names
  Foo
  Foo::::Bar
  Foo::Bar::
  Foo__Bar
  Foo::bar

=head2 Method Name

A method name is a L<symbol name|/"Symbol Name"> that doesn't contains C<::>.

0-length method name is valid. This is used in the L<anon method|/"Anon Method">.

If method names are invalid, a compilation error will occur.

B<Examples:>

  # Valid method names
  FOO
  FOO_BAR3
  foo
  foo_bar
  _foo
  _foo_bar_

  # Invalid method names
  foo__bar
  3foo

A method name that is same as a L</"Keywords"> is allowed.
  
  # "if" is a valid method name
  static method if : void () {
    
  }

=head2 Field Name

A field name is a L<symbol name|/"Symbol Name"> that doesn't contains C<::>.

If field names are invalid, a compilation error will occur.

B<Examples:>

  # Field names
  FOO
  FOO_BAR3
  foo
  foo_bar
  _foo
  _foo_bar_

  # Invalid field names
  foo__bar
  3foo
  Foo::Bar

The field name that is same as a L</"Keywords"> is allowed.
  
  # "if" is a valid field name
  has if : int;

=head2 Variable Name

A variable name starts with C<$> and is followed by a L<symbol name|/"Symbol Name">.

The L<symbol name|/"Symbol Name"> can be wrapped by C<{> and C<}>. If a opening C<{> exists and the closing C<}> doesn't exists, a compilation error will occur.

B<Examples:>

  # Variable names
  $name
  $my_name
  ${name}
  $Foo::name
  $Foo::Bar::name
  ${Foo::name}

  # Invalid variable names
  $::name
  $name::
  $Foo::::name
  $my__name
  ${name

=head2 Class Variable Name

A class variable name is a L<variable name|/"Variable Name">.

If class variable names are invalid, a compilation error will occur.

B<Examples:>

  # Class variable names
  $NAME
  $MY_NAME
  ${NAME}
  $FOO::NAME
  $FOO::BAR::NAME
  ${FOO::NAME}
  $FOO::name
  
  # Invalid class variable names
  $::NAME
  $NAME::
  $FOO::::NAME
  $MY__NAME
  $3FOO
  ${NAME

=head2 Local Variable Name

A local variable name is a L<variable name|/"Variable Name"> that doesn't contain C<::>.

B<Examples:>

  # Local variable names
  $name
  $my_name
  ${name}
  $_name
  $NAME

  # Invalid local variable names
  $::name
  $name::
  $Foo::::name
  $my__name
  ${name
  $Foo::name
  $Foo::Bar::name
  ${Foo::name}
  $3foo

=head2 Keywords

The list of keywords:

  alias
  allow
  as
  break
  byte
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
  has_impl
  if
  isa
  isweak
  is_read_only
  interface
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
  of
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
  required
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

The list of operators for tokenization:

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

A comment begins with C<#> and ends with L</"Line Terminators">.

  # Comment

Comments have no meaning in tokenization.

=head2 POD

POD(Plain Old Document) is a syntax to write documents easily.

POD starts from the line beginning with C<=>, followed by any string that is composed of ASCII printable characters, and ending with L</"Line Terminators">.

POD ends from the line beginning with C<=cut>, and ending with L</"Line Terminators">.

B<Examples:>

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

Literals are representations of values in source codes. These are L</"Integer Literal">, L</"Floating Point Literal">, L</"Character Literal">, L</"String Literal"> and L</"Bool Literal">.

=head2 Integer Literal

=head3 Decimal Representation of Integer Literal

Decimal Representation of Integer Literal is represented by one or more consecutive characters from C<0> to C<9>.

Can be prefixed with C<+> or C<->.

L</"Types"> of Integer Literal is L</"int Type"> by default.

If Integer Literal exceeds the range of numbers that can be represented by L</"int Type">, a compilation error will occur.

By suffixing C<L> or C<l> at the end, that represents L</"long Type"> Integer Literal.

If L</"long Type"> Integer Literal  exceeds the range of numbers that can be represented by L</"long Type">,  If it exceeds the range, a compilation error will occur.

C<_> can be used as a separator. Separator has no meaning.

If Integer Literal is assigned to a L</"byte Type"> variable or passed to L</"byte Type"> Method Argument, and does not exceed the range of numbers that can be represented by L</"byte Type">, the L<numeric narrowing type conversion|/"Numeric Narrowing Type Conversion"> is performed and the value converted to L</"byte Type"> value. If it exceeds the range, a compilation error will occur.

If Integer Literal is assigned to a L</"short Type"> variable or passed to L</"short Type"> Method Argument, and does not exceed the range of numbers that can be represented by L</"short Type">, the L<numeric narrowing type conversion|/"Numeric Narrowing Type Conversion"> is performed and the value converted to L</"short Type"> value. If it exceeds the range, a compilation error will occur.

B<Examples:>

  123
  +123
  -123
  123L
  123l
  123_456_789
  -123_456_789L

=head3 Hexadecimal Representation of Integer Literal

Hexadecimal Representation of Integer Literal is represented by the following rule.

Hexadecimal Representation of Integer Literal starts with C<0x> or C<0X>.

It is followed by one or more consecutive characters C<0> to C<9>, C<a> to C<f>, or C<A> to C<F>.

Other rules are same as Decimal Representation of Integer Literal

B<Examples:>

  0x3b4f
  -0x3F1A
  0xDeL
  0xFFFFFFFF_FFFFFFFF

=head3 Octal Representation of Integer Literal

Octal Representation of Integer Literal is represented by the following rule.

Octal Representation of Integer Literal starts with C<0>.

It is followed by one or more consecutive characters C<0> to C<7>.

Other rules are same as Decimal Representation of Integer Literal

B<Examples:>

  0755
  -0644
  0666L
  0655_755

=head3 Binary Representation of Integer Literal

Binary Representation of Integer Literal is represented by the following rule.

Binary Representation of Integer Literal starts with C<0b> or C<0B>.

It is followed by one or more consecutive characters C<0> or C<1>.

B<Examples:>

  0b0101
  -0b1010
  0b110000L
  0b10101010_10101010

=head2 Floating Point Literal

Floating Point Literal is composed of B<Sign Part>, B<Numeric Part>, B<Exponent Part> and B<Suffix>.

  # Floating Point Literal
  [Sign Part][Numeric Part][Exponent Part][Suffix Part]

Floating Point Literal is B<Decimal Floating Point Literal> or B<Hexadecimal Floating Point Literal>.

B<Sign Part> is represented by C<+> or C<->. Sign Part is optional.

Numeric Part of Decimal Floating Point Literal starts one or more C<0> to C<9>.

Numeric Part of Hexadecimal Floating Point Literal starts C<0x> or C<0X>, and is followed by C<0> to C<9>, C<a> to C<f>, or C<A> to C<F>.

For that the Literal is Floating Point Literal, Numeric Part contains C<.> or, The Literal have Exponent Part, or have Suffix Part.

Numeric part can contain C<_>. This is just a Numeric Separator and is ignored.

Hexadecimal Floating Point Literal needs Exponent Part.

B<Exponent Part> is consist of B<Exponential Notation> and B<Signed Decimal Integer>.

  # Exponent Part
  [Exponential Notation][Signed Decimal Integer]

Exponential Notation is C<e> or C<E> for Decimal Floating Point Literal, and C<p> or C<P> for Hexadecimal Floating Point Literal.

The meaning of Exponent Part is decimal shift for Decimal Floating Point Literal, or binary shift for Hexadecimal Floating Point Literal.

If Suffix Part is C<f> or C<F>, the L</"Types"> of Floating Point Literal is L</"float Type">.

If Suffix Part is C<d> or C<D>, the L</"Types"> of Floating Point Literal is L</"double Type">.

If Suffix Part is omitted, the L</"Types"> of Floating Point Literal is L</"double Type">.

If Floating Point Literal is L</"float Type">, the Floating Point Literal is converted to float value using C standard "strtof" function. If the conversion fails, a compilation error will occur.

If Floating Point Literal is L</"double Type">, the Floating Point Literal is converted to double value using C standard "strtod" function. If the conversion fails, a compilation error will occur.

B<Examples:>

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

Character Literal is enclosed in single quotes C<'>.

Content of Character Literal is one printable ASCII character or one Escape Character of Character Literal.

Charater Literal Type is "L</"byte TypeC<>>

L</"Types"> of Charater Literal is L</"byte Type">.

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

B<Examples:>

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

The string literal is a L<literal|/"Literals"> to represents a string in source codes.

The return type is a L<string type|/"String Type">.

A string literal is written by the characters of UTF-8.

The string Literal is enclosed in double quotes C<">.

B<Examples:>

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

B<Examples:>

  # Escape characters of string literals
  "abc\tdef\n"
  "\x0D\x0A"
  "\N{U+3042}\N{U+3044}\N{U+3046}"

=head2 Bool Literal

The bool literal is a L<literal|/"Literals"> to represent a bool value in source codes.

=head3 true

C<true> is the alias for the L<TRUE|SPVM::Bool/"TRUE"> method of L<Bool|SPVM::Bool>.

  true

B<Examples:>

  # true
  my $is_valid = true;

=head3 false

C<false> is the alias for L<FALSE|SPVM::Bool/"FALSE"> method of L<Bool|SPVM::Bool>.

  false

B<Examples:>

  # false
  my $is_valid = false;

=head2 Variable Expansion

B<Variable Expansion> applys L</"Local Variable">, L</"Class Variable">, L</"Dereference">, L</"Field Access">, L</"Array Access">, L</"Exception Variable"> in String Literal.

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

The variable name can besurround with C<{> and C<}> to indicate the end of the variable name.

  "AAA ${foo}_ccc BBB"

The above is expanded as the following.

  "AAA " . ${foo} . "_ccc BBB"

If there is no enclosing C<{> and C<}>, up to the valid part as a variable name is interpreted as a Variable. Dereference interpreting is same as this.

If "->" follows the variable name, it is interpreted as L</"Field Access"> or L</"Array Access">.

[1] If the following Characters are "a-zC< >A-ZC< >0-9C< >_C< >{C< >[", proceed with the interpretation.

[2] If the Character following [1] is C<}>, or C<]>, then if the next Character is "->", C<{>, or C<[>, proceed with the interpretation and return back to [1], otherwise stop interpreting.

The trailing $is not treated as the start of Variable Expansion. It is treated as C<$>.

  "AAA$"

=head2 Fat Comma

The fat comma C<=>> is a L<separator|/"Separators">.

  =>

The fat comma is an alias for Comma C<,>.

  # Comma
  ["a", "b", "c", "d"]
  
  # Fat Comma
  ["a" => "b", "c" => "d"]

If the characters of the left operand of the fat camma is not wrapped by C<"> and the characters are a L<symbol name|/"Symbol Name"> that does'nt contain C<::>, the characters are treated as a L<string literal|/"String Literal">.

  # foo_bar2 is treated as "foo_bar2"
  [foo_bar2 => "Mark"]

  ["foo_bar2" => "Mark"]

=head1 Syntax Parsing

The SPVM language is assumed to be parsed by yacc/bison.

=head2 Syntax Parsing Definition

The definition of syntax parsing of SPVM language. This is written by yacc/bison syntax.

  %token <opval> CLASS HAS METHOD OUR ENUM MY USE AS REQUIRE ALIAS ALLOW CURRENT_CLASS MUTABLE
  %token <opval> DESCRIPTOR MAKE_READ_ONLY INTERFACE
  %token <opval> IF UNLESS ELSIF ELSE FOR WHILE LAST NEXT SWITCH CASE DEFAULT BREAK EVAL
  %token <opval> SYMBOL_NAME VAR_NAME CONSTANT EXCEPTION_VAR
  %token <opval> UNDEF VOID BYTE SHORT INT LONG FLOAT DOUBLE STRING OBJECT TRUE FALSE END_OF_FILE
  %token <opval> DOT3 FATCAMMA RW RO WO INIT NEW OF
  %token <opval> RETURN WEAKEN DIE WARN PRINT CURRENT_CLASS_NAME UNWEAKEN '[' '{' '('
  %type <opval> grammar
  %type <opval> opt_classes classes class class_block
  %type <opval> opt_declarations declarations declaration
  %type <opval> enumeration enumeration_block opt_enumeration_values enumeration_values enumeration_value
  %type <opval> method anon_method opt_args args arg has use require alias our
  %type <opval> opt_descriptors descriptors
  %type <opval> opt_statements statements statement if_statement else_statement
  %type <opval> for_statement while_statement switch_statement case_statement default_statement
  %type <opval> block eval_block init_block switch_block if_require_statement
  %type <opval> unary_op binary_op comparison_op isa logical_op op
  %type <opval> call_spvm_method opt_vaarg
  %type <opval> array_access field_access weaken_field unweaken_field isweak_field convert array_length
  %type <opval> assign inc dec allow has_impl
  %type <opval> new array_init
  %type <opval> my_var var interface
  %type <opval> value_op opt_value_ops value_ops opt_value_op case_statements
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
  %right <opval> LOGICAL_NOT BIT_NOT '@' CREATE_REF DEREF PLUS MINUS CONVERT SCALAR STRING_LENGTH ISWEAK REFCNT REFOP DUMP NEW_STRING_LEN IS_READ_ONLY COPY HAS_IMPL
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
    | our
    | use
    | allow
    | interface
    | init_block
    | alias

  init_block
    : INIT block

  use
    : USE class_name ';'
    | USE class_name AS class_alias_name ';'

  require
    : REQUIRE class_name

  alias
    : ALIAS class_name AS class_alias_name ';'

  allow
    : ALLOW class_name ';'

  interface
    : INTERFACE class_name ';'

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
    : OUR VAR_NAME ':' opt_descriptors qualified_type opt_type_comment ';'

  has
    : HAS field_name ':' opt_descriptors qualified_type opt_type_comment ';'

  method
    : opt_descriptors METHOD method_name ':' return_type '(' opt_args opt_vaarg')' block
    | opt_descriptors METHOD method_name ':' return_type '(' opt_args opt_vaarg')' ';'
    | opt_descriptors METHOD ':' return_type '(' opt_args opt_vaarg')' block
    | opt_descriptors METHOD ':' return_type '(' opt_args opt_vaarg ')' ';'

  anon_method
    : opt_descriptors METHOD ':' return_type '(' opt_args opt_vaarg')' block
    | '[' args ']' opt_descriptors METHOD ':' return_type '(' opt_args opt_vaarg')' block

  opt_args
    : /* Empty */
    | args

  args
    : args ',' arg
    | args ','
    | arg

  arg
    : var ':' qualified_type opt_type_comment

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
    | value_op ';'
    | LAST ';'
    | NEXT ';'
    | BREAK ';'
    | RETURN ';'
    | RETURN value_op ';'
    | DIE value_op ';'
    | WARN value_op ';'
    | PRINT value_op ';'
    | weaken_field ';'
    | unweaken_field ';'
    | ';'
    | MAKE_READ_ONLY value_op ';'

  for_statement
    : FOR '(' opt_value_op ';' op ';' opt_value_op ')' block

  while_statement
    : WHILE '(' op ')' block

  switch_statement
    : SWITCH '(' value_op ')' switch_block

  switch_block
    : '{' case_statements '}'
    | '{' case_statements default_statement '}'

  case_statements
    : case_statements case_statement
    | case_statement

  case_statement
    : CASE value_op ':' block
    | CASE value_op ':'

  default_statement
    : DEFAULT ':' block
    | DEFAULT ':'

  if_require_statement
    : IF '(' require ')' block
    | IF '(' require ')' block ELSE block

  if_statement
    : IF '(' op ')' block else_statement
    | UNLESS '(' op ')' block else_statement

  else_statement
    : /* NULL */
    | ELSE block
    | ELSIF '(' op ')' block else_statement

  block
    : '{' opt_statements '}'

  eval_block
    : EVAL block ';'

  opt_value_ops
    : /* Empty */
    | value_ops

  opt_value_op
    : /* Empty */
    | value_op

  op
    : value_op
    | logical_op

  value_op
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
    | '(' value_ops ')'
    | CURRENT_CLASS_NAME
    | isweak_field
    | comparison_op
    | isa
    | TRUE
    | FALSE
    | is_read_only
    | has_impl

  value_ops
    : value_ops ',' value_op
    | value_ops ','
    | value_op

  unary_op
    : '+' value_op %prec PLUS
    | '-' value_op %prec MINUS
    | BIT_NOT value_op
    | REFCNT var
    | REFOP value_op
    | STRING_LENGTH value_op
    | DUMP value_op
    | DEREF var
    | CREATE_REF var
    | NEW_STRING_LEN value_op
    | COPY value_op

  is_read_only
    : IS_READ_ONLY value_op

  inc
    : INC value_op
    | value_op INC

  dec
    : DEC value_op
    | value_op DEC

  binary_op
    : value_op '+' value_op
    | value_op '-' value_op
    | value_op '*' value_op
    | value_op DIVIDE value_op
    | value_op DIVIDE_UNSIGNED_INT value_op
    | value_op DIVIDE_UNSIGNED_LONG value_op
    | value_op REMAINDER value_op
    | value_op REMAINDER_UNSIGNED_INT value_op
    | value_op REMAINDER_UNSIGNED_LONG value_op
    | value_op BIT_XOR value_op
    | value_op BIT_AND value_op
    | value_op BIT_OR value_op
    | value_op SHIFT value_op
    | value_op '.' value_op

  comparison_op
    : value_op NUMEQ value_op
    | value_op NUMNE value_op
    | value_op NUMGT value_op
    | value_op NUMGE value_op
    | value_op NUMLT value_op
    | value_op NUMLE value_op
    | value_op NUMERIC_CMP value_op
    | value_op STREQ value_op
    | value_op STRNE value_op
    | value_op STRGT value_op
    | value_op STRGE value_op
    | value_op STRLT value_op
    | value_op STRLE value_op
    | value_op STRING_CMP value_op

  isa
    : value_op ISA type

  logical_op
    : op LOGICAL_OR op
    | op LOGICAL_AND op
    | LOGICAL_NOT op
    | '(' logical_op ')'

  assign
    : value_op ASSIGN value_op
    | value_op SPECIAL_ASSIGN value_op

  new
    : NEW basic_type
    | NEW array_type_with_length
    | anon_method

  array_init
    : '[' opt_value_ops ']'
    | '{' value_ops '}'
    | '{' '}'

  convert
    : '(' qualified_type ')' value_op %prec CONVERT

  array_access
    : value_op ARROW '[' value_op ']'
    | array_access '[' value_op ']'
    | field_access '[' value_op ']'

  call_spvm_method
    : CURRENT_CLASS SYMBOL_NAME '(' opt_value_ops  ')'
    | CURRENT_CLASS SYMBOL_NAME
    | class_name ARROW method_name '(' opt_value_ops  ')'
    | class_name ARROW method_name
    | value_op ARROW method_name '(' opt_value_ops ')'
    | value_op ARROW method_name
    | value_op ARROW '(' opt_value_ops ')'

  field_access
    : value_op ARROW '{' field_name '}'
    | field_access '{' field_name '}'
    | array_access '{' field_name '}'

  weaken_field
    : WEAKEN var ARROW '{' field_name '}'

  unweaken_field
    : UNWEAKEN var ARROW '{' field_name '}'

  isweak_field
    : ISWEAK var ARROW '{' field_name '}'

  has_impl
    : HAS_IMPL var ARROW method_name

  array_length
    : '@' value_op
    | '@' '{' value_op '}'
    | SCALAR '@' value_op
    | SCALAR '@' '{' value_op '}'

  my_var
    : MY var ':' qualified_type opt_type_comment
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
    : basic_type '[' value_op ']'
    | array_type '[' value_op ']'

  return_type
    : qualified_type opt_type_comment
    | VOID

  opt_type_comment
    : /* Empty */
    | type_comment

  type_comment
    : OF type

  field_name
    : SYMBOL_NAME

  method_name
    : SYMBOL_NAME

  class_name
    : SYMBOL_NAME

  class_alias_name
    : SYMBOL_NAME

=head2 Syntax Parsing Tokens

The list of syntax parsing tokens:

=begin html

<table>
  <tr>
    <th>Tokens</td><th>Keywords or Operators</th>
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
    <td>HAS</td><td>has</td>
  </tr>
  <tr>
    <td>HAS_IMPL</td><td>has_impl</td>
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

=head2 Operator Precidence

The definition of the precidence of operators. This is written by yacc/bison syntax.

The bottom is the highest precidence and the top is the lowest precidence.
  
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
  %right <opval> LOGICAL_NOT BIT_NOT '@' CREATE_REF DEREF PLUS MINUS CONVERT SCALAR STRING_LENGTH ISWEAK REFCNT REFOP DUMP NEW_STRING_LEN IS_READ_ONLY COPY HAS_IMPL
  %nonassoc <opval> INC DEC
  %left <opval> ARROW

See also L<syntax parsing tokens|/"Syntax Parsing Tokens"> to know real operators.

The operator precidence can be increased using C<()>.

  #  a * b is calculated at first
  a * b + c
  
  # b + c is calculated at first
  a * (b + c)

=head1 Class

Descriptions of classes.

=head2 Class Definition

The C<class> keyword defins a class. A class has a class block.

  class CLASS_NAME {
  
  }

Class names must follow the rule of L<class names|/"Class Name">.

L<Class descriptors|/"Class Descriptors"> can be specified after C<:>.

  class CLASS_NAME : CLASS_DESCRIPTOR {
  
  }
  
  class CLASS_NAME : CLASS_DESCRIPTOR1 CLASS_DESCRIPTOR2 ... CLASS_DESCRIPTORN {
  
  }

B<Examples:>

  # The definition of a class
  class Point {
  
  }

  # With class descriptors
  class Point : public {
  
  }

Direct children of the class block must be L<use|/"Load Modules">, L<our|/"Class Variable">,
L<has|/"Field Definition">, L<enum|/"Enumeration Definition">, L<method|/"Method Definition">, L<allow|/"Allow Class Access">,
L<interface|/"interface Statement"> and L<INIT block|/"INIT Block"> can be defined.

  class Foo {
 
    use Point;
  
    our $VAR : int;
  
    has var : int;
  
    enum {
      CONST_VAL1,
      CONST_VAL2,
    }
  
    static method foo : int ($num : int) {
      # ...
    }

    interface Asset;
    
    INIT {
      # ...
    }
  }

If more than one class in a module file, a compilation error will occur.

If the class name is different from the name that the module file C</> is replaced with C<::> and added C<.spvm> to the end, a compilation error will occur.

  # Valid class name for "Foo/Bar/Baz.spvm"
  class Foo::Bar::Baz {
    
  }

  # Invalid class name for "Foo/Bar/Baz.spvm"
  class Foo::Bar::Hello {
    
  }

=head2 Class Descriptors

The list of class descriptors.

=begin html

<table>
  <tr>
    <th>
      Descriptors
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
      This class is public. Other classes can new the object from this class.
    </td>
  </tr>
  <tr>
    <td>
      <b>private</b>
    </td>
    <td>
      This class is private. Other classes can't new the object from this class. This is default setting.
    </td>
  </tr>
  <tr>
    <td>
      <b>interface_t</b>
    </td>
    <td>
      This class is an <a href="#Interface-Type">interface type</a>.
    </td>
  </tr>
  <tr>
    <td>
      <b>mulnum_t</b>
    </td>
    <td>
      This class is a <a href="#Multi-Numeric-Types">multi-numeric type</a>.
    </td>
  </tr>
  <tr>
    <td>
      <b>pointer_t</b>
    </td>
    <td>
      This class is a <a href="#Pointer-Type">pointer type</a>.
    </td>
  </tr>
  <tr>
    <td>
      <b>precompile</b>
    </td>
    <td>
      Do <a href="#Precompiled-Method">precompile</a> all methods in this class, except for accessors, and enumurations. 
    </td>
  </tr>
</table>

=end html

If both "public" and "private" are specifed, a compilation error will occur.

If more than one of "mulnum_t", "pointer_t" are specified, a compilation error will occur.

=head2 Destructor

If a L<class|/"Class"> can has the destructor.

  method DESTROY : void () {
  
  }

A destructor is a special L<method|/"Method"> called when the object is destroyed.

A destructor name must be C<DESTROY>.

A destructor retrun type must be L<void type|/"void Type">, otherwise a compilation error will occur.

A destructor must be an L<instance method|/"Instance Method"> that don't have the arguments, otherwise a compilation error will occur.

If a L</"Exception"> occurs in the destructor, the exception is not thrown, and prints the message to STDERR.

B<Examples:>

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

Also, Private Class cannot L</"new Operator"> from outside of Class.

If the class allow other class, the other class can access private Methods, Fields, and Class Variables, and can L</"new Operator"> of the class.

  allow CLASS_NAME;

allow must be defined directory under L</"Class Definition">.

  class Foo {
    allow Bar;
  }

In this example, Bar can access the private Method, Field, and Class Variable of Foo can be accessed and can new Operator of Foo.

Specifying the module of B<allow> also loads the module by L</"use"> at the same time.

=head2 Interface Guarantee

Interface Guarantee C<interface> is a syntax to guarantee that the class has the required method defined in the L<interfaces|/"Interface">.

  class Asset::Memory {
    interface Asset;

    method add_chunk : void ($chunk : string) {
      # ...
    }
    method contains : int ($substring : string){
      # ...
    }
    method size : int (){
      # ...
    }
    method is_file : int (){
      # ...
    }
  }

If the method implementation is not found, an exception is thrown at runtime.

The existence of the method implementation can be checked by the L<has_impl|/"has_impl Operator"> operator.

=head2 Anon Class

The anon class is the class that is defined by the L<anon method|/"Anon Method"> syntax.

A anon class has its unique L<class name|/"Class Name"> corresponding to the class name, the line number and the position of columns the anon class is defined.

L<Examples:>
    123456789...
  1:class Foo::Bar {
  2:  method sum : void () {
  3:    my $anon_method = method : string () {
  4:      
  5:    }
  6:: }
  7:}
  
  # The name of anon class
  Foo::Bar::anon::3::23;

=head1 Interface

Explains interfaces.

=head2 Interface Definition

A interface is defined using a L<class definition|/"Class Definition"> with a L<class descriptor/"Class Descriptors"> C<interface_t>.

  class Stringable: interface_t {
    required method to_string : string ();
    method foo : int ($num : long);
  }

A interface can have multiple method declarations. The methods can't have the method blocks.

A interface must have only one required method. The required method is the method that has the L<method descriptor|/"Method Descriptors"> C<required>.

The type of the interface is the L</"Interface Type">.

The class that has L<interface Guarantees|/"Interface Guarantee"> must have the required method that is declared in the interface. Otherwise a compilation error will occur.

  class Point {
    interface Stringable;
    
    method to_string : string () {
      my $x = $self->x;
      my $y = $self->y;
      
      my $string = "($x,$y)";
      
      return $string;
    }
  }
  
  my $stringable = (Stringable)Point->new_xy(1, 2);
  my $string = $stringable->to_string;

A interface can't have L<filed definitions|/"Field Definition">.

A interface can't have L<class variable definitions|/"Class Variable Definition">.

A interface can have L<interface Guarantees|/"Interface Guarantee">.

  class TestCase::Pointable : interface_t {
    interface Stringable;
    
    required method x : int ();
    method y : int();
    method to_string : string ();
  }

If the interface definition is invalid, a compilation error will occur.

C<new> operator can't create the objects from interfaces.

=head1 Module

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

Change "::" to C</>. Add ".spvm" at the end.

  SPVM/Foo.spvm
  SPVM/Foo/Bar.spvm
  SPVM/Foo/Bar/Baz.spvm

=head2 Load Modules

The C<use> syntax loads a Module.
  
  # Load a module
  use Foo;

If the module does not exist, a compilation error will occur.

Modules are loaded at compile-time.

C<use> syntax must be defined directly under L</"Class Definition">.

  class Foo {
    use Foo;
  }

=head2 Class Alias

C<alias> syntax create an alias name for a class name.
  
  # Create alias
  alias Foo::Bar as FB;

FB is used as Foo::Bar alias in L<class method calls|Class Method Call>.

  # This means Foo::Bar->sum(1, 2);
  FB->sum(1, 2);

C<alias> syntax must be defined directly under L</"Class Definition">.

  class Foo {
    alias Foo::Bar as FB;
  }

You can create an alias at the same time as loading a module by C<use>.
  
  use Foo::Bar as FB;

=head2 Automatically Loaded Module

The followings are Automatically Loaded Modules. They can be used without L</"use">.

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

Let's look at an example. if Foo does not exist, no a compilation error will occur and it is assumed that there is no if block

Therefore, "$foo = new Foo;" does not result in a compilation error because it is assumed that there is no if block.

In the other hand, the else block exists, so a warning is issued.

  my $foo : object;
  if (require Foo) {
    $foo = new Foo;
  }
  else {
    warn "Warning: Can't load Foo";
  }

=head2 Default Loaded Modules

The following modules are loaded by default. These modules are deeply related to the features of SPVM language itself, such as L<type conversion|/"Type Conversion">.

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

=head1 Class Variable

=head2 Class Variable Definition

B<Class Variable> is a global variable that belongs to L</"Class"> and exists from the start to the end of the program execution.

"our" Keyword defines a Class Variable.

  our CLASS_VARIABLE_NAME : TYPE;

Class Variable must be defined directly under L</"Class Definition">.

Class Variable Definition must specify L</"Types">. The Type must be L</"Numeric Types"> or L</"Object Types">.

Class variable mames must follows the rule specified in L</"Class Variable Name">, and must not contain "::", otherwise a compilation error will occur.

If more than one Class Variable with the same name is defined, a compilation error will occur.

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
      This Class Variable has Read Accessor. Read Accessor name is the same as class variable names except removing C<$>. For example, If the class variable names is "$FOO", Read Accessor name is "FOO".
    </td>
  </tr>
  <tr>
    <td>
      <b>wo</b>
    </td>
    <td>
      This Class Variable has Write Accessor. Write Accessor name is the same as class variable names except removing C<$> and adding "SET_" to top. For example, If the class variable names is "$FOO", Read Accessor name is "SET_FOO".
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

If both "public" and "private" Descriptors are specified, a compilation error will occur.

If more than one of "ro", "wo", and "rw" are specified at the same time, a compilation error will occur

Read Accessor of Class Variable has no arguments and the return type is same as the type of Class Variable.

Write Acessor of Class Variable has one argument and the type is same as the type of Class Variable. The return type is L</"void Type">.

Inline Expansion optimization is performed to Read Accessor and Write Accessor. You don't have to worry about the performance penalty of using Class Variable Accessors.

B<Examples:>

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

Class Variable is initialized with L</"Type Initial Value"> after compilation and before execution.

This initial value can be changed by using L</"INIT Block">.

  class Foo {
    our $VAR : int;
  
    INIT {
      $VAR = 3;
    }
  }

=head2 Class Variable Access

Class Variable Access is an operation to access Class Variable to get or set a value.

See L</"Getting Class Variable"> for how to get the value of Class Variable.

See L</"Setting Class Variable"> for the setting of the value of Class Variable.

=head1 Field

=head2 Field Definition

Field is a data area in a L</"object created using new keyword">

C<has> keyword defines a field.

  has FIELD_NAME : TYPE;

Field must be defined directly under L</"Class Definition">.

Field Definition must be specify L</"Types">. The Type must be L</"Numeric Types"> or L</"Object Types">.

Field names must follows the rule specified in L</"Field Name">.

Field Type must be L</"Numeric Types"> or L</"Object Types">, otherwise a compilation error will occur.

If more than one field names Variable with the same name is defined, a compilation error will occur.

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

If both "public" and "private" Descriptors are specified, a compilation error will occur.

If more than one of "ro", "wo", and "rw" are specified at the same time, a compilation error will occur

Read Accessor of Field has one argument that is L</"self Type"> and the return type is same as the type of Field.

Write Acessor of Class Variable has two arguments. First argument is L</"self Type"> and second argument is same as the type of Field. The return type is L</"void Type">.

Inline Expansion optimization is performed to Read Accessor and Write Accessor. You don't have to worry about the performance penalty of using Field Accessors.

B<Examples:>

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

The field access is an L<operator|/"Operators"> to get or set the field.

  INVOCANT->{FIELD_NAME}

The field access has three different syntax.

If the invocant is different from the following three field access, a compilation error will occur.

If the field name does not found, a compilation error will occur

=head3 Field Access of the Class

The field access of the L<class|/"Class">.

  my $point = new Point;
  $point->{x} = 1;
  my $x = $point->{x};

See L</"Getting Field"> to get the field of the L<class|/"Class">.

See L</"Setting Field"> to set the field of the L<class|/"Class">.

=head3 Field Access of the Multi-Numeric Type

The field access of the L<multi-numeric type|/"Multi-Numeric Types">.

  my $z : Complex_2d;
  $z->{re} = 1;
  my $re = $z->{re};

See L</"Getting Multi-Numeric Field"> to get the field of the L<multi-numeric type|/"Multi-Numeric Types">.

See L</"Setting Multi-Numeric Field"> to set the field of L<multi-numeric type|/"Multi-Numeric Types">.

=head3 Field Access of the Multi-Numeric Reference via Derefernce

The field access of the L<multi-numeric reference|/"Multi-Numeric Reference Type"> via derefernce.

  my $z : Complex_2d;
  my $z_ref = \$z;
  $z_ref->{re} = 1;
  my $re = $z_ref->{re};

See L</"Getting Multi-Numeric Field via Dereference"> to get the field of the L<multi-numeric reference|/"Multi-Numeric Reference Type"> via dereference.

See L</"Setting Multi-Numeric Field via Dereference"> to set the field of the L<multi-numeric reference|/"Multi-Numeric Reference Type"> via dereference.

=head1 Method

a.

=head2 Method Definition

The C<method> keyword defines a class method or an instance method.
  
  # Static method
  static method METHOD_NAME : RETURN_VALUE_TYPE (ARG_NAME1 : ARG_TYPE1, ARG_NAME2 : ARG_TYPE2, ...) {
    
  }

  # Instance method
  method METHOD_NAME : RETURN_VALUE_TYPE (ARG_NAME1 : ARG_TYPE1, ARG_NAME2 : ARG_TYPE2, ...) {
    
  }

Methods must be defined directly under L</"Class Definition">.

Method names must be follow the rule of L</"Method Name">.

The argument names must be follow the rule of L</"Local Variable Name">.

The minimal length of arguments is C<0>. The max length of arguments is C<255>.

The types of the arguments must be L</"Numeric Types">, L</"Multi-Numeric Types">, L</"Object Types">, or L</"Reference Type">, otherwise a compilation error will occur.

The type of the return value must be L</"void Type">, L</"Numeric Types">, L</"Multi-Numeric Types"> or L</"Object Types">, otherwise a compilation error will occur.

Defined methods can be called using L</"Method Call"> syntax.

A method can have L<method descriptors|/"Method Descriptors">.

  DESCRIPTORS static method METHOD_NAME : RETURN_VALUE_TYPE (ARG_NAME1 : ARG_TYPE1, ARG_NAME2 : ARG_TYPE2, ...) {
  
  }

A method has L</"Method Block"> except for the case that the method has the C<native> L<method descriptors|/"Method Descriptors">. 

=head3 Variable Length Arguments

C<...> after the type of the argument indicates the argument is a variable length argument. Only the last argument can become a variable length argument.

  static method METHOD_NAME : RETURN_VALUE_TYPE (ARG_NAME1 : ARG_TYPE1, ARG_NAME2 : ARG_TYPE2...) {
  
  }

The type of the variable length argument must be L</"Array Types">.

A variable length argument can recieve multiple values.

  # Definition of variable length argument 
  static method sprintf : string ($format : string, $values : object[]...) {
  
  }
  
  # Pass multiple values to the a variable length argument
  sprintf("Value %d %f", 1, 2.0);

A variable length argument can recieve an array.

  # Pass array to a variable lenght argument
  sprintf("Value  %d %f", [(object)1, 2.0]);

If you want to treat the value as an individual element, cast it to type other than L</"Array Types">..

  sprintf("aaa %p", (object)[(object)1, 2.0]);

=head2 Class Method

A class method is defined with the C<static> keyword.

  static method sum : int ($num1 : int, $num2 : int) {
    # ...
  }

A class method can be called from the L<class name|/"Class Name">.
  
  # Call a class method
  my $total = Foo->sum(1, 2);

If the class method is belong to the current class, a class method can be called using L<&|/"Current Class"> syntax.
  
  # Call a class method using C<&>
  my $total = &sum(1, 2);

=head2 Instance Method

An instance method is defined without the C<static> keyword.

  method add_chunk : void ($chunk : string) {
    # ...
  }

An instance method can be called from the object.
  
  # Call an instance method
  my $point = Point->new;
  $point->set_x(3);

=head2 Method Descriptors

Method descriptors are descriptors used in a L<method definition|/"Method Definition">.

=begin html

<table>
  <tr>
    <th>
      Descriptors
   </th>
    <th>
      Descriptions
   </th>
  </tr>
  <tr>
    <td>
      <b>public</b>
    </td>
    <td>
      This method is public. This method can be accessed from other classes. This is default setting.
    </td>
  </tr>
  <tr>
    <td>
      <b>private</b>
    </td>
    <td>
      This method is private. This method can not be accessed from other classes.
    </td>
  </tr>
  <tr>
    <td>
      <b>precompile</b>
    </td>
    <td>
      This method is a <a href="#Precompile-Method">precompile method</a>.
    </td>
  </tr>
  <tr>
    <td>
      <b>native</b>
    </td>
    <td>
      This method is a <a href="#Native-Method">native method</a>.
    </td>
  </tr>
  <tr>
    <td>
      <b>required</b>
    </td>
    <td>
      This method is required.
    </td>
  </tr>
</table>

If C<native> and C<precompile> descriptors can't used together.

C<public> and C<private> descriptors can't be used together.

C<required> can be only used in a method of a L<interface|/"Interface">.

If the specifed descriptor is not found or the way to specify is invalid, a compilation error will occur.

B<Examples:>
  
  # private method
  private method : int sum ($num1 : int, $num2 : int) {
    return $num1 + $num2;
  }
  
  # precompile method
  precompile method : int sum ($num1 : int, $num2 : int) {
    return $num1 + $num2;
  }
  
  # native method
  native method : int sum ($num1 : int, $num2 : int);

=end html

=head2 Native Method

Native methods are the L<methods|/"Method"> that is written by native languages such as C, C++.

A native method is defined by the C<native> L<method descriptor|/"Method Descriptors">.

  native sum : int ($num1 : int, $num2 : int);

A native method doesn't have its L<method block|/"Method Block">.

See also the L<SPVM Native API|SPVM::Document::NativeAPI> to interface native methods.

=head2 Precompiled Method

If the class has the C<precompile> L<class descriptor|/"Class Descriptors">, the methods of the class are precompiled.

The source code of each precompiled method is translated to C source code and is compiled to the machine code such as C<MyMath.o>.

And it is linked to a shared library such as C<MyMath.so> on Linux/Unix, C<MyMath.dll> on Windows, or C<MyMath.dylib> on Mac.

And each function in the shared library is bind to the SPVM method.

Precompiled methods need the L<build directory|SPVM/"SPVM_BUILD_DIR"> such as C<~/.spvm_build> to compile and link them.

=head2 Constant Method

Constant Method is a Method that the return type is L</"Numeric Types"> and returns Constant Value.

  static method foo : int () { return 5; }
  static method foo : long () { return 5L; }
  static method foo : float () { return 5.0f; }
  static method foo : double () { return 5.0; }

Inline Expansion optimization is performed to Constant Method.

Note that SPVM does not perform constant convolution optimization, so if a constant is calculated, it will not performe Inline Expansion.

  # This is not Constant Method.  Inline Expansion is not performed
  static method foo : int () { return 5 + 3; }

=head2 Signature

A signature is a string that represents the return type and the types of the arguments of a L<method|/"Method">.

  RETURN_TYPE(ARG_TYPE1,ARG_TYPE2,ARG_TYPEn)

It the method is an L<instance method|/"Instance Method">, the type representation of the first argument is C<self>.

B<Examples:>

  # Method Definition
  static method foo : int ($num1 : double, $num2 : long[])
  
  # The signature
  int(double,long[])
  
  # Method Definition
  static method foo : void ()
  
  # The signature
  void()
  
  # Method Definition
  method foo : int ($num1 : double, $num2 : long[])
  
  # Signature
  int(self,double,long[])

Signatures are used by L<native APIs|SPVM::Document::NativeAPI>.

=head1 Enumeration

Explains enumeration.

=head2 Enumeration Definition

The C<enum> keyword defines an enumeration. An enumeration defines constant values.

  # Enumeration Definition
  enum {
    FLAG1,
    FLAG2,
    FLAG3
  }

An enumeration must be defined directly under L</"Class Definition">.

The first value of an enumeration starts with C<0>. The next value is incremented by C<1>, and this is continued in the same way. In this example, C<FLAG1> is C<0>, C<FALG2> is C<1>, and C<FLAG3> is C<2>.

The type of a value of an enumeration is the L<int type|/"int Type">.

C<,> after the last value can be allowed.

  enum {
    FLAG1,
    FLAG2,
    FLAG3,
  }

A value of an enumeration is implemented as a L<constant method|/"Constant Method">.

  static method FLAG1 : int () { return 0; }
  static method FLAG2 : int () { return 1; }
  static method FLAG3 : int () { return 2; }

The value can be set explicitly.

  enum {
    FLAG1,
    FLAG2 = 4,
    FLAG3,
  }

In the above example, C<FLAG1> is C<0>, C<FALG2> is C<4>, and C<FLAG3> is C<5>.

If an enumeration definition is invalid, a compilation error will occur.

B<Examples:>

  class Foo {
    enum {
      FLAG1,
      FLAG2,
      FLAG3,
    }
  }

=head2 Enumeration Descriptors

Descriptors can be specified to an enumeration definition.

  private enum {
    FLAG1,
    FLAG2 = 4,
    FLAG3,
  }

B<The list of enumeration descriptors:>

=begin html

<table>
  <tr>
    <th>
      Descriptors
   </th>
    <th>
      Descriptions
   </th>
  </tr>
  <tr>
    <td>
      <b>public</b>
    </td>
    <td>
      This enumeration is public. Each value of this enumeration can be accessed from other classes. This is default setting.
    </td>
  </tr>
  <tr>
    <td>
      <b>private</b>
    </td>
    <td>
      This enumeration is private. Each value of this enumeration can not be accessed from other classes.
    </td>
  </tr>
</table>

=end html

If both "public" and "private" descriptors are specified, a compilation error will occur.

=head2 Enumeration Call

The value of enumeration called as a L<class method call|/"Class Method Call">.

  my $flag1 = Foo->FLAG1;
  my $flag2 = Foo->FLAG2;
  my $flag3 = Foo->FLAG3;

In special cases, a value of an enumeration can be used as the operand of a L<case statement|/"case Statement">.

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

INIT Block must be defined directly under L</"Class Definition">.

  class Foo {
    INIT {
  
    }
  }

Zero or more L</"Statements"> can be written in INIT Block.

  INIT {
    my $foo = 1 + 1;
    my $bar;
  }

L</"return Statement"> cannot be written in INIT Block.

Internally, INIT Block is a L</"Method"> that the return type is L</"void Type"> and has no arguments.

You can define multiple INIT Blocks.

The execution order of INIT Block is not guaranteed. If ohter INIT Block is defined in ohter Class, do not assume that INIT Block of the current class will be executed first.

A common use of INIT Block is to initialize L</"Class Variable">.

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

B<Local Variable> is a variable that is declared in L</"Scope Blocks">.  Local Variable has L</"Scope">. This is same as Local Variable in C Language.

Local Variable is declared using B<my> L</"Keyword">.

  my LOCAL_VARIABLE_NAME : TYPE;

The local variable name must be follow the rule of L</"Local Variable Name">.

L</"Types"> must be specified. Type must be L</"Numeric Types">, L</"Object Types">, L</"Multi-Numeric Types">, or L</"Reference Type">.

  # Local Variable Declaration Examples
  my $var : int;
  my $var : Point;
  my $var : Complex_2d;
  my $var : int*;

Local Variable is initialized by L</"Local Variable Initial Value">.

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

Using L</"Type Inference">, you omit L</"Types"> in Local Variable Declaration.

  # int
  my $num = 1;
  
  # double
  my $num = 1.0;

Local Variable Declaration returns the value of Local Variable. This is a L</"Expressions">.

  my $ppp = my $bar = 4;
  
  if (my $bar = 1) {
  
  }
  
  while (my $bar = 1) {
  
  }

See L</"Scope"> about Local Variable Scope.

=head2 Local Variable Initial Value

Local Variable is initialized by L</"Type Initial Value">.

=head2 Local Variable Access

Local Variable Access is an operation to access Local Variable to get or set the value.

See L</"Getting Local Variable"> to get Local Variable value.

L</"Setting Local Variable"> to get Local Variable value.

If L</"Class Variable"> with the same name as the Local Variable exists, Program uses the variable as Local Variable, not L</"Class Variable">.

=head1 Scope

B<Scope> is a range surrounded by L</"Scope Blocks">.

  # Scope Blocks 
  {
    # Start of Scope
    
    # ...
    
    # End of Scope
  }

Local Variable Declaration registers the Local Variable that is L</"Object Types"> with Mortal Variable in run-time. 

If the object is not L</"undef">, The reference count is added by C<1>.

  {
    # $num become Mortal Variable in run-time
    my $num = new Foo;
  }

At the end of Scope, the object that is registered as Mortal Variable, Reference Count is reduced by 1 except the object is not L</"undef">.

If the reference count become 0, the object released.

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

A scope block is the block that create a scope. Zero or more L<statements|/"Statements"> can be written in a scope block.

Scope blocks are L</"Simple Block">, L</"Method Block">, L</"eval Block">, L</"if Block">, L</"elsif Block">, L</"else Block">, L</"for Block">, L</"while Block"> and L</"switch Block">.

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
  
  };

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

SPVM has the L<string type|/"String Type">. A string is created by L</"String Literal"> L</"String Creating Operator"> or L</"Type Convertion"> to the string type.
  
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

If you use C<mutable type qualifier|/"mutable Type Qualifier">, each character can be set.

  my $string_mut = (mutable string)$string;
  $string_mut->[0] = 'd';

The created string is one more last byte that value is C<\0> on the internal memory. Although this has no meaning from SPVM language, this has meaning from L<Native APIs|SPVM:Document::NativeAPI>.

The length of the string can be got using a L<string length operator|/"String Length Operator">
  
  # Getting the length of the string
  my $message = "Hello"+
  my $length = length $message;

=head1 Undefined Value

An undefined value is represented by C<undef>.

  undef

An undefined value can be assigned to an L<object type|/"Object Types">.

In the level of L<native APIs|SPVM:Document::NativeAPI>, C<undef> is defined as C<(void*)NULL>.

  (void*)NULL

An undefined value can be compared by the C<==> operator and the C<!=> operator. An undefined value is guaranteed not to be equal to the any created object.

The type of C<undef> is L<undefined type|/"Undefined Type">

B<Examples:>
  
  # Undefine values
  my $string : string = undef;
  
  if (undef) {
    
  }
  
  my $message = "Hello";
  if ($message == undef) {
    
  }

=head1 Array

The array is the data structure for multiple values.

There are the following types of array.

=begin html

<ul>
  <li>
    Numeric Array
 </li>
  <li>
    Object Array
 </li>
  <li>
    Multi-Numeric Array
 </li>
</ul>

=end html

The numeric array is the array that the type of the element is the L<numeric type|/"Numeric Types">.

The object array is the array that the type of the element is the L<object type|/"Object Types">.

The multi-numeric array is the array that the type of the element is the L<multi-numeric type|/"Multi-Numeric Types">.

See L</"Creating Array"> to create Array.

=head2 Array Access

Array Access is an operation to access the element of Array to get or set the value.

  ARRAY->[INDEX]

See L</"Getting Array Element"> to get the element value of Array.

See L</"Setting Array Element"> to set the element value of Array.

=head1 Multi-Numeric Value

=head2 Multi-Numeric Types Definition

Multi-Numeric type represents continuous numeric values. For example, there are three consecutive 32-bit signed integers, two consecutive double-precision floating point numbers. It isplaned to use 3D points, complex numbers, quaternions, etc.

Multi-Numeric Types are defined by specifying mulnum_t L</"Class Descriptors"> in L</"Class Definition">.

  # Three consecutive 32bit signed integers
  class Complex_2d : mulnum_t {
    has x : int;
    has y : int;
    has z : int;
  }
  
  # Tow consecutive 64bit floating point numbers
  class Complex_2d : mulnum_t {
    x : double;
    y : double;
  }

Multi-Numeric Types must end with C<_>, Number of Fields, L</"Multi-Numeric Types Suffix">.

The suffix must correspond to L</"Numeric Types">.

All Fields must be the same L</"Numeric Types">.

The maximum number of Fields is 255.

Multi-Numeric Types can be used as L</"Types"> of L</"Local Variable Declaration">.

Multi-Numeric Types can be used as an argument L</"Types"> in L</"Method Definition"> .

Multi-Numeric Types can be used as L</"Types"> of Return Value in L</"Method Definition">.

Multi-Numeric Types can be used as L</"Basic Type"> of L</"Array Types"> .

  my $points = new Complex_2d[5];

Reference can be created for Multi-Numeric Types value.

  my $z : Complex_2d;
  my $z_ref = \$z;

L</"Undefined Value"> cannot be assigned to Multi-Numeric Types value.

See L</"Multi-Numeric Types Field Access"> to get and set the value of field of Multi-Numeric Types Value.

=head2 Multi-Numeric Types Suffix

List of Multi-Numeric Types Suffix.

=begin html

<table>
  <tr>
    <th>
      <b>Numeric Types</b>
   </th>
    <th>
      Multi-Numeric Types Suffix
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

=head2 Multi-Numeric Types Usage

To use Multi-Numeric Types, load a Module using L</"use Statement">.

  use Complex_2d;
  use Complex_2d;

Next is L</"Local Variable Declaration">. Local Variable Declaration create continuous area for fields of Multi-Numeric Types Value. All fields of of Multi-Numeric Types Value are initialized by L</"Type Initial Value">.

  my $z : Complex_2d;
  my $z : Complex_2d;

Note that Multi-Numeric Types value are not object, so cannot create a Object by L</"new"> syntax.

=head2 Multi-Numeric Types Field Access

B<Multi-Numeric Types Field Access> is an operation to access Multi-Numeric Types Field to get or set a value.

  MULTI_NUMERIC_TYPE_VALUE->{FIELD_NAME}

See L</"Getting Multi-Numeric Field"> to get Multi-Numeric Types Field.

See L</"Setting Multi-Numeric Field"> to set Multi-Numeric Types Field.

=head1 Multi-Numeric Array

L</"Multi-Numeric Value"> can be an element of L</"Array">.

  my $points = new Complex_2d[5];
  
  my $zs = new Complex_2d[5];

Multi-Numeric Array has continuous Multi-Numeric Values.

The Element Type is L</"Multi-Numeric Types">, not L</"Object Types">.

For example, Complex_2d[5] is continuous 15 (= 3 * 5) count L</"int Type"> Value.

L</"Types"> of Multi-Numeric Array is L</"Array Types">.

=head2 Multi-Numeric Array Access

Multi-Numeric Array Access is an operation to access Multi-Numeric Array to get and set the element value.

  Array->[INDEX]

See L</"Getting Array Element"> to get Array Element Value.

See L</"Setting Array Element"> to get Array Element Value.

=head1 Reference

The reference is the address of a L<local variable|/"Local Variable"> on the memory.

=head2 Creating Reference

The L<reference operator|/"Reference Operator"> creates the reference of a L<local variable|/"Local Variable">.

A reference is assigned to the L<reference type/"Reference Type">.

The operand of a reference operator must be the variable of a L<numeric type|/"Numeric Types"> or a L<multi-numeric type|/"Multi-Numeric Types">.

  # The reference of numeric type
  my $num : int;
  my $num_ref : int* = \$num;
  
  # The reference of multi-numeric type
  my $z : Complex_2d;;
  my $z_ref : Complex_2d* = \$z;

The L<reference type|/"Reference Type"> can be used as the types of the arguments of a method.

  # Method Definition
  static method sum : void ($result_ref : int*, $num1 : int, $num2 : int) {
    $$result_ref = $num1 + $num2;
  }
  
  # Method Call
  my $num1 = 1;
  my $num2 = 2;
  my $result_ref = \$result;
  sum($result_ref, $num1, $num2);

=head2 Dereference

The dereference is the operation to get the value from a reference.

A L<dereference operator|/"Dereference Operators"> perform a dereference.

  # Get the value using a dereference
  my $num2 = $$num_ref;
  
  # Set the value using a dereference
  $$num_ref = 3;
  
  # Get the value of a multi-numeric type using a dereference
  my $z2 = $$z_ref;
  
  # Set the value of a multi-numeric type using a dereference
  $$z_ref = $z2;

In the referencec of L<multi-numeric types|/"Multi-Numeric Types">, the deference can be performed using the arrow operator C<-E<gt>>.

  # Get a field of a multi-numeric type using a dereference
  my $x = $z_ref->{re};
  
  # Set a field of a multi-numeric type using a dereference
  $z_ref->{re} = 1;

=head1 Operators

B<Operators> are L</"Unary Operators">, L</"Binary Operators">, L</"Increment Operator">, L</"Decrement Operator">, L</"Comparison Operator">, L</"Logical Operators">, and L</"Assignment Operator">.

=head2 Value-Returning Operators

The value-returning operator is the L<operator|/"Operators> that return a value.

The value-returning operators are L</"Operators">, L</"Undefined Value">, L</"Literals">, L</"Getting Local Variable">, L</"Setting Local Variable">,
L</"Getting Class Variable">, L</"Getting Class Variable">, L</"Setting Class Variable">, L</"Getting Exception Variable">, L</"Setting Exception Variable">,
L</"Getting Field">, L</"Setting Field">, L</"Getting Multi-Numeric Field">, L</"Setting Multi-Numeric Field">, L</"Getting Multi-Numeric Field via Dereference">, L</"Setting Multi-Numeric Field via Dereference">, <"Getting Array Element">, L</"Setting Array Element"> and L</"Method Call">.

=head2 Unary Operators

Unary operators are operators have one operand.

  UNARY_OPERATOR OPERAND

The operand is an L<operator|/"Operators">.

Unary operators are L</"Unary Plus Operator">, L</"Unary Minus Operator">, L</"Bit NOT Operator">, L</"Array Length Operator">, L</"String Creating Operator">, and L</"String Length Operator">.

=head2 Binary Operators

Binary Operator is a L<operator|/"Operators"> that have two operands.

  LEFT_OPERAND BINARY_OPERATOR RIGHT_OPERAND

Binary operators are L</"Addition Operator">, L</"Subtraction Operator">, L</"Multiplication Operator">, L</"Division Operator">, L</"Remainder Operator">, L</"Bit AND Operator">, L</"Bit OR Operator">, L</"Shift Operators">, and L</"String Concatenation Operator">.

=head2 Sequential Operator

The sequential operator C<,> is an L<operator|/"Operators"> like the following.

  (OPERAND1, OPERAND2, ..., OPERNADN)

The operands are evaluated from the left to the right, and return the evaluated value of the last operand.

B<Exampless:>

  # 3 is assigned to $foo
  my $foo = (1, 2, 3);
  
  # $x is 3, $ret is 5
  my $x = 1;
  my $y = 2;
  my $ret = ($x += 2, $x + $y);

=head2 Arithmetic Operators

B<Arithmetic Operators> is an L</"Operators"> that performs arithmetic.

B<Arithmetic Operatorss> are L</"Addition Operator">, L</"Subtraction Operator">, L</"Multiplication Operator">, L</"Division Operator">, L</"Division Unsigned Int Operator">, , L</"Division Unsigned Long Operator">, L</"Remainder Operator">, L</"Remainder Unsigned Int Operator">, L</"Remainder Unsigned Long Operator">, L</"Unary Plus Operator">, L</"Unary Minus Operator">, L</"Increment Operator">, and L</"Decrement Operator">.

=head2 Unary Plus Operator

The unary plus operator C<+> is an L<Unary Operator|/"Unary Operators"> to return the value of the operand.

  +OPERAND

The operand must be an L<operator|/"Operators"> that type is a L<numeric type|/"Numeric Types">, otherwise a compilation error will occur.

L</"Numeric Widening Type Conversion"> applys to the operand.

returns the value copied from the value of the operand.

the return type of the unary plus pperator is the type that L</"Numeric Widening Type Conversion"> is performed.

B<Examples:>
  
  # A unary plus operator
  my $num = +10;

=head2 Unary Minus Operator

The unary minus operator C<-> is an L<Unary Operator|/"Unary Operators"> to return the negative value of the operand.

  -OPERAND

The operand must be an L<operator|/"Operators"> that type is a L<numeric type|/"Numeric Types">, otherwise a compilation error will occur.

L</"Numeric Widening Type Conversion"> applys to the operand.

the unary minus operator performs the following operation of C language.

  -x

Return type of an unary minus operator is the type that L</"Numeric Widening Type Conversion"> is performed.

B<Examples:>

  # A unary minus operator
  my $num = -10;

=head2 Addition Operator

The addition operator C<+> is a L<binary operator|/"Binary Operators"> to calculate the result of the addition of two numbers.

  LEFT_OPERAND + RIGHT_OPERAND

The left operand and the right operand must be a L<numeric type|/"Numeric Types">, otherwise a compilation error will occur.

L</"Binary Numeric Type Conversion"> is performed to the left operand and the right operand.

The addition operator performs the operation that exactly same as the following operation in C language.

  x + y;

The return type of the addition operator is the type that L</"Binary Numeric Type Conversion"> is performed.

=head2 Subtraction Operator

The subtraction operator C<-> is a L<binary operator|/"Binary Operators"> to calculate the result of the subtraction of two numbers.

  LEFT_OPERAND - RIGHT_OPERAND

The left operand and the right operand must be a L<numeric type|/"Numeric Types">, otherwise a compilation error will occur.

L</"Binary Numeric Type Conversion"> is performed to the left operand and the right operand.

The subtraction operator performs the operation that exactly same as the following operation in C language.

  x - y;

The return type of the subtraction operator is the type that L</"Binary Numeric Type Conversion"> is performed.

=head2 Multiplication Operator

The multiplication operator is a L<binary operator|/"Binary Operators"> to calculate the result of multiplication of two numbers.

  LEFT_OPERAND * RIGHT_OPERAND

The left operand and the right operand must be a L<numeric type|/"Numeric Types">, otherwise a compilation error will occur.

L</"Binary Numeric Type Conversion"> is performed to the left operand and the right operand.

The multiplication operator performs the operation that exactly same as the following operation in C language.

  x * y;

The return type of the multiplication operator is the type after L</"Binary Numeric Type Conversion"> is performed.

=head2 Division Operator

The division operator C</> is a L<binary operator|/"Binary Operators"> to culcurate the division of two numbers.

  LEFT_OPERAND / RIGHT_OPERAND

The left operand and the right operand must be L</"Numeric Types">, otherwise a compilation error will occur.

L</"Binary Numeric Type Conversion"> is performed to the left operand and the right operand.

The division operator performs the operation that exactly same as the following operation in C language.

  x / y;

The return type of the division operator is the type after L</"Binary Numeric Type Conversion"> is performed.

If the two operands are L<integral types|/"Integral Types"> and the value of the right operand is C<0>, an L<exception|/"Exception"> is thrown.

=head2 Division Unsigned Int Operator

The division unsigned int operator C<divui> is a L<binary operator|/"Binary Operators"> to culcurate the unsigned int division of two numbers.

  LEFT_OPERAND divui RIGHT_OPERAND

The left operand and the right operand must be an L<int type|/"int Type">, otherwise a compilation error will occur.

The division unsigned int operator performs the operation that exactly same as the following operation in C language.

  (uint32_t)x / (uint32_t)y;

The return type of the division operator is the L<int type|/"int Type">.

If the value of the right operand is C<0>, an L<exception|/"Exception"> is thrown.

=head2 Division Unsigned Long Operator

The division unsigned long operator C<divul> is a L<binary operator|/"Binary Operators"> to culcurate the unsigned long division of two numbers.

  LEFT_OPERAND divul RIGHT_OPERAND

The left operand and the right operand must be an L<long type|/"long Type">, otherwise a compilation error will occur.

The division unsigned long operator performs the operation that exactly same as the following operation in C language.

  (uint64_t)x / (uint64_t)y;

The return type of the division operator is the L<long type|/"long Type">.

If the value of the right operand is C<0>, an L<exception|/"Exception"> is thrown.

=head2 Remainder Operator

The remainder operator C<%> is a L<binary operator|/"Binary Operators"> to calculate a remainder of two numbers.

  LEFT_OPERAND % RIGHT_OPERAND

The left operand and the right operand must be an L<integral type|/"Integral Types">, otherwise a compilation error will occur.

L</"Binary Numeric Type Conversion"> is performed to the left operand and the right operand.

The remainder operator performs the operation that exactly same as the following operation in C language.

  x % y;

the return type of Remainder Operator is the type that L</"Binary Numeric Type Conversion"> is performed.

If the right operand is C<0>, the remainder operator throw an L<exception|/"Exception">.

=head2 Remainder Unsigned Int Operator

The remainder unsigned int operator C<remui> is a L<binary operator|/"Binary Operators"> to calculate a unsigned int remainder of two numbers.

  LEFT_OPERAND remui RIGHT_OPERAND

The left operand and the right operand must be a L<int type|/"int Type">, otherwise a compilation error will occur.

The remainder unsigned int operator performs the operation that exactly same as the following operation in C language.

  (uint32_t)x % (uint32_t)y;

The return type of the remainder unsigned int operator is the L<int type|/"int Type">.

If the value of the right operand is C<0>, an L<exception|/"Exception"> is thrown .

=head2 Remainder Unsigned Long Operator

The remainder unsigned long operator C<remul> is a L<binary operator|/"Binary Operators"> to calculate a unsigned long remainder of two numbers.

  LEFT_OPERAND remul RIGHT_OPERAND

The left operand and the right operand must be a L<long type|/"long Type">, otherwise a compilation error will occur.

The remainder unsigned long operator performs the operation that exactly same as the following operation in C language.

  (ulong64_t)x % (ulong64_t)y;

The return type of the remainder unsigned long operator is the L<long type|/"long Type">.

If the value of the right operand is C<0>, an L<exception|/"Exception"> is thrown .

=head2 Increment Operators

Increment operators are the L<pre-increment operator|/"Pre-Increment Operator"> and L<post-increment operator|/"Post-Increment Operator">.

=head3 Pre-Increment Operator

The pre-increment operator adds C<1> to the value of the operand and returns the value after the incrementation.
  
  # Pre-increment operator
  ++OPERAND

The type of the operand must be a L<local variable|/"Local Variable">, a L<class variable|/"Class Variable">, a L<field access|/"Field Access"></a>, an L<array access|/"Array Access">, a L<dereference|/"Dereference">, otherwise a compilation error will occur.

The pre-increment operator performs the same operation as the following.

  (OPERAND = (TYPE_OF_OPERAND)(OPERAND + 1))

For example, if the type of the operand is the L<byte type|/"byte Type">, the following operation is performed.

  ($num = (byte)($num + 1))

B<Examples:>
  
  # Pre-increment of a local variable
  ++$num;
  
  # Pre-increment of a class variable
  ++$NUM;
  
  # Pre-increment of an element of an array
  ++$point->{x};
  
  # Pre-increment of a field
  ++$nums->[0];
  
  # Pre-increment of a dereferenced value
  ++$$num_ref;

=head3 Post-Increment Operator

The post-increment operator adds C<1> to the value of the operand and returns the value before the incrementation.
  
  # Post-increment operator
  OPERAND++

The type of the operand must be a L<local variable|/"Local Variable">, a L<class variable|/"Class Variable">, a L<field access|/"Field Access"></a>, an L<array access|/"Array Access">, a L<dereference|/"Dereference">, otherwise a compilation error will occur.

The post-increment operator performs the same operation as the following.

  (my TMP_VARIABLE = OPERAND, OPERAND = (TYPE_OF_OPERAND)(OPERAND + 1), TMP_VARIABLE)

For example, if the type of the operand is the L<byte type|/"byte Type">, the following operation is performed.

  (my $tmp = $num, $num = (byte)($num + 1), $tmp)

B<Examples:>
  
  # Post-increment of a local variable
  $num++;
  
  # Post-increment of a class variable
  $NUM++;
  
  # Post-increment of an element of an array
  $point->{x}++;
  
  # Post-increment of a field
  $nums->[0]++;
  
  # Post-increment of a dereferenced value
  $$num_ref++;

=head2 Decrement Operators

Decrement operators are the L<pre-decrement operator|/"Pre-Decrement Operator"> and L<post-decrement operator|/"Post-Decrement Operator">.

=head3 Pre-Decrement Operator

The pre-decrement operator subtracts C<1> to the value of the operand and returns the value after the decrementation.
  
  # Pre-decrement operator
  --OPERAND

The type of the operand must be a L<local variable|/"Local Variable">, a L<class variable|/"Class Variable">, a L<field access|/"Field Access"></a>, an L<array access|/"Array Access">, a L<dereference|/"Dereference">, otherwise a compilation error will occur.

The pre-decrement operator performs the same operation as the following.

  (OPERAND = (TYPE_OF_OPERAND)(OPERAND - 1))

For example, if the type of the operand is the L<byte type|/"byte Type">, the following operation is performed.

  ($num = (byte)($num - 1))

B<Examples:>
  
  # Pre-decrement of a local variable
  --$num;
  
  # Pre-decrement of a class variable
  --$NUM;
  
  # Pre-decrement of an element of an array
  --$point->{x};
  
  # Pre-decrement of a field
  --$nums->[0];
  
  # Pre-decrement of a dereferenced value
  --$$num_ref;

=head3 Post-Decrement Operator

The post-decrement operator subtracts C<1> to the value of the operand and returns the value before the decrementation.
  
  # Post-decrement operator
  OPERAND--

The type of the operand must be a L<local variable|/"Local Variable">, a L<class variable|/"Class Variable">, a L<field access|/"Field Access"></a>, an L<array access|/"Array Access">, a L<dereference|/"Dereference">, otherwise a compilation error will occur.

The post-decrement operator performs the same operation as the following.

  (my TMP_VARIABLE = OPERAND, OPERAND = (TYPE_OF_OPERAND)(OPERAND - 1), TMP_VARIABLE)

For example, if the type of the operand is the L<byte type|/"byte Type">, the following operation is performed.

  (my $tmp = $num, $num = (byte)($num - 1), $tmp)

B<Examples:>
  
  # Post-decrement of a local variable
  $num--;
  
  # Post-decrement of a class variable
  $NUM--;
  
  # Post-decrement of an element of an array
  $point->{x}--;
  
  # Post-decrement of a field
  $nums->[0]--;
  
  # Post-decrement of a dereferenced value
  $$num_ref--;

=head2 Bit Operators

Bit operators are L<operators|/"Operators"> to perform bit operations.

Bit operators are the L<bit AND operator|/"Bit AND Operator">, the L<bit OR operator|/"Bit OR Operator">, or the L<bit NOT operator|/"Bit NOT Operator">.

=head2 Bit AND Operator

The bit AND operator C<&> is an L<operator|/"Operators"> to performe a bit AND operation.

  LEFT_OPERAND & RIGHT_OPERAND

The left operand and the right operand must be an L<integral type/"Integral Types">, otherwise a compilation error will occur.

A L<binary numeric widening type conversion|/"Binary Numeric Type Conversion"> is performed.

The return value is the same as the follwoing operation of C<C language>.

  x & y;

The return type is the type after the L<binary numeric widening type conversion|/"Binary Numeric Widening Type"> is performed.

B<Examples:>
  
  # The bit AND operator
  my $num1 = 0xff;
  my $num2 = 0x12;
  my $result = $num1 & $num2;
  
=head2 Bit OR Operator

The bit OR operator C<|> is an L<operator|/"Operators"> to performe a bit OR operation.

  LEFT_OPERAND | RIGHT_OPERAND

The left operand and the right operand must be an L<integral type/"Integral Types">, otherwise a compilation error will occur.

A L<binary numeric widening type conversion|/"Binary Numeric Type Conversion"> is performed.

The return value is the same as the follwoing operation of C<C language>.

  x | y;

The return type is the type after the L<binary numeric widening type conversion|/"Binary Numeric Widening Type"> is performed.

B<Examples:>
  
  # The bit OR operator
  my $num1 = 0xff;
  my $num2 = 0x12;
  my $result = $num1 | $num2;

=head2 Bit NOT Operator

The bit NOT operator C<~> is an L<unary operator|/"Unary Operators"> to perform the bit NOT operation.

  ~OPERAND

The type of the operand must is an L<integral type|/"Integral Types">, otherwise a compilation error will occur.

The L<numeric widening type conversion|/"Numeric Widening Type Conversion"> is performed.

The return value is the same as the follwoing operation of C<C language>.

  ~x

The return type is the type that the L<numeric widening type conversion|/"Numeric Widening Type Conversion"> is performed.

B<Examples:>
  
  # The bit NOT operator
  my $num = ~0xFF0A;

=head2 Shift Operators

Shift operators are operators that performs bit shift operations. These are L</"Left Shift Operator">, L</"Arithmetic Right Shift Operator">, and L</"Logical Right Shift Operator">.

=head2 Left Shift Operator

The left shift operator C<E<lt>E<lt>> is a L<binary operator|/"Binary Operators"> to perform the left bit shift.

  LEFT_OPERAND << RIGHT_OPERAND

The left operand must be L</"Integral Types">, otherwise a compilation error will occur.

L</"Numeric Widening Type Conversion"> is performed to the left operand.

The right operand must be L</"Integral Types"> except for the L<long type|/"long Type">, otherwise a compilation error will occur.

L</"Numeric Widening Type Conversion"> is performed to the right operand.

The return type is same as the type of the left operand.

The calculation result of the left shift operator is the same as the following calculation in C language.

  x << y;

=head2 Arithmetic Right Shift Operator

The arithmetic right shift operator C<E<gt>E<gt>> is a L<binary operator|/"Binary Operators"> to perform the arithmetic right bit shift.

  LEFT_OPERAND >> RIGHT_OPERAND

The left operand must be L</"Integral Types">, otherwise a compilation error will occur.

L</"Numeric Widening Type Conversion"> is performed to the left operand.

The right operand must be L</"Integral Types"> except for the L<long type|/"long Type">, otherwise a compilation error will occur.

L</"Numeric Widening Type Conversion"> is performed to the right operand.

The return type is same as the type of the left operand.

The operation result of the arithmetic right shift Operator is the operation that exactly same as the following operation in C language.

  x >> y;

=head2 Logical Right Shift Operator

The logical right shift operator C<E<gt>E<gt>E<gt>>is a L<binary operator|/"Binary Operators"> to perform the logical right bit shift.

  LEFT_OPERAND >>> RIGHT_OPERAND

The left operand must be L</"Integral Types">, otherwise a compilation error will occur.

L</"Numeric Widening Type Conversion"> is performed to the left operand.

The right operand must be L</"Integral Types"> except for the L<long type|/"long Type">, otherwise a compilation error will occur.

L</"Numeric Widening Type Conversion"> is performed to the right operand.

The return type is same as the type of the left operand.

The operation result of logical right shift Operator is the same as the following calculation in C language.
  
  // In the case that the left operand is a int type
  (uint32_t)x >> y;

  // In the case that the left operand is a long type
  (uint64_t)x >> y;

=head2 Comparison Operator

Comparison Operator is an operator that is placed between The left operand and the right operand to compare the size, and return True/False Value.

  LEFT_OPERAND COMPARISON_OPERATOR RIGHT_OPERAND

Comparison Operators are L</"Numeric Comparison Operator">, L</"String Comparison Operator">, and L</"isa Operator">.

=head2 Numeric Comparison Operator

B<Numeric Comparison Operator> is a L</"Comparison Operator"> that is placed between The left operand and the right operand to compare the size of number or check the equqlity of objects.

  LEFT_OPERAND NUMERIC_COMPARISON_OPERATOR RIGHT_OPERAND

A list of Numeric Comparison Operators.

=begin html

<table>
  <tr>
    <th>Operator</th>
    <th>Allowing Type</th>
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
      If The left operand is greater than Right value_op, return 1. If The left operand is lower than Right value_op, return -1. If The left operand is equals to Right value_op, return 0.
    </td>
  </tr>
</table>

=end html

The Types of The left operand and the right operand Comparable Types, otherwise a compilation error will occur.

In Numeric Types Comparison, L</"Binary Numeric Type Conversion"> is performed for The left operand and the right operand.

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

For Numeric Types Operation(==, !=, >, >=, <, <=), L</"int Type"> Operation, L</"long Type"> Operation, L</"float Type"> Operation, L</"double Type"> Operation is defined.

And Object Type Operation(==, !=) is defined.

The return type of the Numeric Comparison Operator is L</"int Type">.

=head2 String Comparison Operator

B<String Comparison Operator> is a L</"Comparison Operator"> that compares the bytes in the tow string.

  LEFT_OPERAND STRING_COMPARISON_OPERATOR RIGHT_OPERAND

The left operand and the right operand must be L</"String Type"> or byte[] type.

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
      If The left operand is greater than Right value_op, return 1. If The left operand is lower than Right value_op, return -1. If The left operand is equals to Right value_op, return 0.
    </td>
  </tr>
</table>

=end html

The return type of the String Comparison Operator is L</"int Type">. If the condition is met, returns 1, otherwise 0.

=head2 isa Operator

B<isa Operator> is a L</"Comparison Operator"> to check whether The left operand satisfies Right Type.

  LEFT_OPERAND isa RIGHT_TYPE

isa Operator has three behaviors, depending on Right Type.

1. If Right Type is L</"Numeric Types">, L</"Multi-Numeric Types">, L</"Any Object Type">, L</"Reference Type">, isa operator checks whether the type of The left operand is same as Right Type. This check is done at compile-time and isa operator is replaced by L</"int Type"> value. If their types is same, replaced by 1, otherwise by 0.

2. If the Right Type is L</"Class Type">, isa operator checks whether the type of The left operand is same as Right Type at Run Time. If their types are same, L</"int Type"> 1 is return, otherwise 0. The type of The left operand must be L</"Object Types">, otherwise a compilation error will occur.

3. If the Right Type is L</"Interface Type">, isa Operator checks whether the type of The left operand satisfy the Interface Type at Run Time. If The left operand satisfies the Interface Type, returns L</"int Type"> 1, otherwise 0. The type of The left operand must be L</"Object Types">, otherwise a compilation error will occur.

=head2 ref Operator

B<ref Operator> is a Operator to get type name of the object.

  ref OPERAND

ref Operator return type name if the object defined. Otherwise return undef.

If OPERAND is not a object type, a compilation error will occur.

=head2 dump Operator

B<dump Operator> is a Operator to dump object value.

  dump OPERAND

dump Operator return the dump string.

If OPERAND is not a object type, a compilation error will occur.

The contents of the dumped string may vary from SPVM version to version. Please use dump operator only for viewing the content of object data.

=head2 Logical Operators

The logical operators are the L<operators|/"Operators"> to perform logical operations.

The logical operators are the L<logical AND operator|/"Logical AND Operator">, the L<logical OR operator|/"Logical OR Operator">, and the L<logical NOT operator|/"Logical NOT Operator">.

=head3 Logical AND Operator

The logical AND operator C<&&> returns the result of a logical AND operation.

  LEFT_OPERAND && RIGHT_OPERAND
  
The left operand and the right operand must be a L<logical operator|/"Logical Operators"> or an L<operator|/"Operators">.

The return type of logical AND operator is L</"int Type">.

Thg logical AND operator performs L</"Bool Type Conversion"> to the left operand. If the evaluated value is C<0>, the logical AND operator returns C<0>.
If the value is C<1>, the right operand is evaluated.

Next, Thg logical AND operator performs L</"Bool Type Conversion"> to the right operand. If the evaluated value is C<0>, the logical AND operator returns C<0>,
otherwise returns C<1>.

Logical AND operators can be only used as conditions. Note that these can't be used as L<value_ops|/"Expressions">. 

=head3 Logical OR Operator

The logical OR operator C<||> returns the result of a logical OR operation.

  LEFT_OPERAND || RIGHT_OPERAND

The left operand and the right operand must be a L<logical operator|/"Logical Operators"> or an L<operator|/"Operators">.

The return type of logical OR operator is L</"int Type">.

Thg logical OR operator performs L</"Bool Type Conversion"> to the left operand. If the evaluated value is C<1>, the logical OR operator returns C<1>.
If the value is C<0>, the right operand is evaluated.

Next, Thg logical OR operator performs L</"Bool Type Conversion"> to the right operand. If the evaluated value is C<1>, the logical OR operator returns C<1>,
otherwise returns C<0>.

Logical OR operators can be only used as conditions. Note that these can't be used as L<value_ops|/"Expressions">. 

=head3 Logical NOT Operator

The logical NOT operator C<!> returns the result of a logical NOT operation.

  !OPERAND

The operand must be a L<logical operator|/"Logical Operators"> or an L<operator|/"Operators">.

The return type of logical NOT operator is L</"int Type">.

Thg logical NOT operator performs L</"Bool Type Conversion"> to the operand. If the evaluated value is C<1>, the logical NOT operator returns C<0>.
If the evaluated value is C<0>, returns C<1>.

Logical NOT operators can be only used as conditions. Note that these can't be used as L<value_ops|/"Expressions">. 

=head2 String Concatenation Operator

String concatenation operator C<.> is a L<binary operator|/"Binary Operators"> to concat two strings.

  LEFT_OPERAND . RIGHT_OPERAND

The left operand and the right operand must be a L<string type|/"String Type">, L</"byte[] Type">, or L<numeric type|/"Numeric Types">, otherwise a compilation error will occur.

If the type of the operand is numeric type, a L<numeric to string type conversion|/"Numeric to String Type Conversion"> is performed.

The return type is a L<string type|/"String Type">.

A string concatenation operator returns the result to concat two operands.

If both the left operand and the right operand are a L<string literal|/"String Literal">, the two string literals are concatenated at compile-time.

If the left operand or the right operand is L<undef|/"Undefined Value">, an exception occurs.

B<Examples:>

  my $str = "abc" . "def";
  my $str = "def" . 34;
  my $str = 123 . 456;

=head2 Assignment Operator

Assignment Operator is a L</"Binary Operators"> for assignment, expressed in C<=>.

  LEFT_OPERAND = RIGHTH_OPERAND

Assignment Operator has multiple meanings depending on the Right and Left sides. Please refer to each item.

In Assignment Operator, the The left operand is evaluated after the right operand is evaluated. This is with the exception of value_op being executed from Left to Right as a rule.

=head2 Special Assignment Operator

Special Assignment Operator is a L</"Assignment Operator">the L<type assignability|/"Type Assignability"> ,a compilation error will occur

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

  # Before unexpanding x is L</"byte Type">
  $x += 1;
  
  # After unwinding
  $x = (byte)($x + 1)

B<Examples:>

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

=head2 Array Length Operator

The array length operator is an L<Unary Operator|/"Unary Operators"> to get the length of the array.

  @OPERAND

The operand must be a L<Expression|/"Expressions"> that type is an L</"Array Types">, otherwise a compilation error will occur.

The array length operator returns a L</"int Type"> value that is the length of the L</"Array">.

Array Length Operator returns L</"Expressions">

B<Examples:>
  
  # Getting the length of the array.
  my $nums = new byte[10];
  my $length = @$nums;

  # Getting the length of the array with a scalar operator. This is exactly same as the avobe
  my $nums = new byte[10];
  my $length = scalar @$nums;
  
Note that SPVM does not have the context different from Perl, and array length operators always return the length of the array.

=head2 String Creating Operator

The string creation operator C<new_string_len> is an L<Unary Operator|/"Unary Operators"> to create a L<string|/"String"> with the length.

  new_string_len OPERAND

The operand must be an L<operator|/"Operators"> that type is a L</"Integral Type"> except for a L<long type|/"long Type">, otherwise a compilation error will occur.

The string creation operator returns the string that is created with the lenght.

The return type is a L<string type|/"String Type">.

B<Examples:>
  
  # New a string with the length
  my $message = new_string_len 5;

=head2 copy Operator

The C<copy> operator is an L<Unary Operator|/"Unary Operators"> to copy the object.

  copy OPERAND

The operand must be an L<operator|/"Operators"> that type is a L<object type|/"object Type">, otherwise a compilation error will occur.

If the type of operand is none of a L<string type|/"String Type">, a L<numeric type|/"Numerci Types">, a L<multi-numeric type|/"Multi-Numeric Types">,
An L<exception|/"Exception"> is thorwn.

The C<copy> operator returns the copied object.

The return type is same as the type of operand.

Read-only flag of the string is dropped.

B<Examples:>
  
  # New a string with the length
  my $message = copy "abc";

=head2 is_read_only Operator

The C<is_read_only> is an L<Unary Operator|/"Unary Operators"> to check if the L<string|/"String"> is read-only.

  is_read_only OPERAND

The operand must be a L<string type|/"String Type">, otherwise a compilation error will occur.

If the string is read-only, the C<is_read_only> operator returns C<1>, otherwise returns C<0>.

The return type is an L<int type|/"int Type">.

B<Examples:>
  
  # New a string with the length
  my $message = "Hello";
  my $is_read_only = is_read_only $message;

=head2 String Length Operator

The string length operator is an L<Unary Operator|/"Unary Operators"> to get the length of the string.

  length OPERAND

The operand must be an L<operator|/"Operators"> that type is a L</"String Type">, otherwise a compilation error will occur.

The string length operator returns a L</"int Type"> value that is the length of the L</"String">.

Note that the returned length is byte size, not the count of the characters of the string that is encoded to a specific character set.

B<Examples:>
  
  # Getting the string length. The result is 5
  my $message = "Hello";
  my $length = length $message;
  
  # Getting the string length of UTF-8. The result is 9, not 3
  my $message = "あいう";
  my $length = length $message;

=head2 scalar Operator

The C<scalar> operator is an L<Operator|/"Operators"> that returns the value of the operand.

  scalar OPERAND

The operand must be an L</"Array Length Operator">, otherwise a compilation error will occur.

B<Examples:>
  
  # Getting the array length 
  my $nums = new int[3];
  foo(scalar @$nums);

  # This is exactlly same as the above.
  my $nums = new int[3];
  foo(@$nums);

Note that the sclara operator exists only to reduce the confusion.

=head2 isweak Operator

The C<isweak> operator checks whether the L<field|/"Field"> is L<weak reference|/"Weak Reference.">

  isweak OBJECT->{FIELD_NAME};

The type of the object must be the L<class type|/"Class Type">, otherwise a compilation error will occur.

If the field name is not found, a compilation error will occur.

The type of the field targetted by the C<isweak> operator is not an L<object type|/"Object Types">, a compilation error will occur.

If the field is weaken, the C<isweak> operator returns C<1>, otherwise returns C<0>.

The return type of the C<isweak> operator is the L<int type|/"int Type">.

See L</"Weak Reference"> to know the behavior of the C<isweak> operator.

B<Examples:>

  # isweak
  my $isweak = isweak $object->{point};

=head2 has_impl Operator

The C<has_impl> operator checks the existence of the method implementation.

  has_impl OPERAND->METHOD_NAME

  has_impl OPERAND

The operand must the object that has a L<class type|/"Class Type"> or an L<interface type|/"Interface Type">, otherwise a compilation error will occur.

If the class or the interface doesn't have the method declaration, a compilation error will occur.

The method name must be a L<method name|/"Method Name">, otherwise a compilation error will occur.

If method name is not specified, the method name become C<"">.

The return type is L<int type|/"int Type">.

If the class or the interface has the method implementation, returns C<1>, otherwise returns C<0>.

B<Examples:>

  my $stringable = (Stringable)Point->new_xy(1, 2);
  
  if (has_impl $stringable->to_string) {
    # ...
  }

=head2 Type Cast

The type cast is the L<operator|/"Operators"> to perform an L<explicite type conversion|/"Explicite Type Conversion">.

  # Type Cast
  (TYPE)OPERAND
  
  # Postfix Type Cast
  OPERAND->(TYPE)

If the type cast doesn't have the L<type castability|"Type Castability">, a compilation error will occur.

A type cast performs a L<type conversion|/"Type Conversion">, merely copying, or copying with a runtime type checking.

The behavior of type casts are explains in L<Type Castability>.

B<Examples:>
  
  # Explicte long to int type conversion
  my $num = (int)123L;

  # Explicte byte[] to string type conversion
  my $num = (string)new byte[3];

  # Explicte string to byte[] type conversion
  my $num = (byte[])"Hello";

  # Postfix type cast
  my $point = Point->new;
  my $stringable = $point->(Stringable);

=head2 Getting Local Variable

The getting local variable is an L<operator|/"Operators"> to get the value of the L<local variable|/"Local Variable">.

  $var

The return value is the value of the local variable.

The return type is the type of the local variable.

=head2 Setting Local Variable

The setting local variable is an L<operator|/"Operators"> to set the value of L</"Local Variable"> using the L<assignment operator|/"Assignment Operator">.

  $var = VALUE

The assignment of the value must satisfy the L<type assignability|/"Type Assignability">, otherwise a compilation error will occur.

The return value is the value after the assignment.

If the type of the assigned value is an L<object type|/"Object Types">, the reference count of the object is incremented by C<1>.

If an object has already been assigned to $var before the assignment, the reference count of the object is decremented by C<1>.

See the L<scope|/"Scope"> to know the L<garbage collection|/"Garbage Collection"> of local variables.

=head2 Getting Class Variable

The getting class variable is an L<operator|/"Operators"> to get the value of the L<class variable|/"Class Variable">.

  $CLASS_NAME::CLASS_VARIABLE_NAME

C<CLASS_NAME::> can be omitted if the class variable belongs to the current L<class|/"Class">.

  $CLASS_VARIABLE_NAME

If the class variable does not found, a compilation error will occur.

If the class variable is C<private> and it is accessed outside of the class, a compilation error will occur.

B<Examples:>

  class Foo {
    our $VAR : int;
  
    static method bar : int () {
      my $var1 = $Foo::VAR;
      my $var2 = $VAR;
    }
  }

=head2 Setting Class Variable

B<Setting Class Variable Expression> is an L<operator|/"Operators"> to set L</"Class Variable"> Value using the L<assignment operator|/"Assignment Operator">.

  $CLASS_NAME::CLASS_VARIABLE_NAME = VALUE

"CLASS_NAME::" can be omitted when the Class Variable belongs to own L</"Class">.

  $CLASS_VARIABLE_NAME = VALUE

If the assignment does not satisfy the L<type assignability|/"Type Assignability">, a compilation error will occur.

The return value is the value after the setting.

The return type is the type of the class variable.

If the class variable does not found, a compilation error will occur.

If the class variable is C<private> and it is accessed outside of the class, a compilation error will occur.

If the type of the assigned value is an L<object type|/"Object Types">, the reference count of the object is incremented by C<1>.

If an object has already been assigned to $CLASS_VARIABLE_NAME before the assignment, the reference count of the object is decremented by C<1>.

B<Examples:>

  class Foo {
    our $VAR : int;
  
    static method bar : int () {
      $Foo::VAR = 1;
      $VAR = 3;
    }
  }

=head2 Getting Exception Variable

The setting exception variable is an L<operator|/"Operators"> to get the value of the L<exception variable|/"Exception Variable">.

  $@

The return value is the value of L<exception variable|/"Exception Variable">.

The return type is the L<string type|/"String Type">.

B<Examples:>
  
  # Getting the exception variable
  my $message = $@;

=head2 Setting Exception Variable

The setting exception variable is an L<operator|/"Operators"> to set the value of L</"Exception Variable"> using the L<assignment operator|/"Assignment Operator">.

  $@ = VALUE

The type of the assigned value must be L</"String Type">.

The return value is the value after the setting.

The return type is the L<string type|/"String Type">.

The reference count of the assigned value is incremented by C<1>.

If an string has already been assigned to the exception variable before the assignment, the reference count of the string is decremented by C<1>.

B<Examples:>

  $@ = "Error";

=head2 Getting Field

The getting field is an L<operator|/"Operators"> to get the L<field|/"Field"> of the object. This is one syntax of the L<field access|/"Field Access">.

  INVOCANT->{FIELD_NAME}

The type of invocant is a L<class type|/"Class Type">.

The retrun type is the L<type|/"Types"> of the Field.

B<Examples:>

  my $point = Point->new;
  my $x = $point->{x};

=head2 Setting Field

The setting field is an L<operator|/"Operators"> to set the L<field|/"Field"> of the object. This is one syntax of the L<field access|/"Field Access">.

  INVOCANT->{FIELD_NAME} = VALUE

The type of invocant is a L<class type|/"Class Type">.

If the assignment does not satisfy the L<type assignability|/"Type Assignability">, a compilation error will occur.

The return value is the value after the setting. 

The return type is the type of the field.

If the type of assigned value is a L<basic object type|/"Object Types">, Reference Count of the object is incremented by C<1>.

If an object has already been assigned to Field before the assignment, the reference count of that object is decremented by C<1>.

B<Examples:>

  my $point = Point->new;
  $point->{x} = 1;

=head2 Getting Multi-Numeric Field

B<Getting Multi-Numeric Field Expression> is an L<operator|/"Operators"> to get Field of L</"Multi-Numeric Value">. This is one syntax of the L<field access|/"Field Access">.

  INVOCANT->{FIELD_NAME}

Invocant Expression is L</"Multi-Numeric Types">.
  
If the field names does not found in the L</"Class">, a compilation error will occur

Getting Multi-Numeric Field Expression returns the field value in the Multi-Numeric Value.

Retrun Type is The L</"Types"> of the Field.

B<Examples:>

  my $z : Complex_2d;
  my $re = $z->{re};

=head2 Setting Multi-Numeric Field

Setting Multi-Numeric Field Expression is an L<operator|/"Operators"> to set Field of L</"Multi-Numeric Value"> using L</"Assignment Operator">. This is one syntax of the L<field access|/"Field Access">.

  INVOCANT->{FIELD_NAME} = RIGHT_OPERAND

Invocant Expression is L</"Multi-Numeric Types">.

If the field names does not found in the L</"Class">, a compilation error will occur.

Setting Multi-Numeric Field Expression returns the value of Field after setting. 

The assignment must satisfy the L<type assignability|/"Type Assignability">.

Return Value Type is the type of Field.

B<Examples:>

  my $z : Complex_2d;
  $z->{re} = 2.5;

=head2 Getting Array Element

B<Getting Array Element Expression> is an L<operator|/"Operators"> to get a Element Value of L</"Array">.

  ARRAY_EXPRESSION->[INDEX_EXPRESSION]

Array Expression must be L</"Array Types">.

Index Expression must be L</"int Type"> or the type that become L</"int Type"> by L</"Numeric Widening Type Conversion">.

Getting Array Element Expression returns the Element Value of the Index.

If Array Expression is L</"Undefined Value">, a Runtime Exception occurs.

If Index Expression is lower than 0 or more than the max index of the Array, a Runtime Exception occurs.

B<Examples:>

  my $nums = new int[3];
  my $num = $nums->[1];
  
  my $points = new Point[3];
  my $point = $points->[1];
  
  my $objects : object[] = $points;
  my $object = (Point)$objects->[1];

=head2 Setting Array Element

Setting Array Element Expression is an L<operator|/"Operators"> to set a Element Value of a Array using L</"Assignment Operator">.

  ARRAY_EXPRESSION->[INDEX_EXPRESSION] = RIGHT_OPERAND

Array Expression must be L</"Array Types">.

Index Expression must be L</"int Type"> or the type that become L</"int Type"> by L</"Numeric Widening Type Conversion">.

The assignment must satisfy the L<type assignability|/"Type Assignability">.

Setting Array Element Expression returns the value of the element after setting.

If Array Expression is L</"Undefined Value">, a Runtime Exception occurs.

If Index Expression is lower than 0 or more than the max index of the Array, a Runtime Exception occurs.

If the right operand is L</"Object Types">, Reference Count of the object is incremented by C<1>.

If an object has already been assigned to Field before the assignment, the reference count of that object is decremented by C<1>.

B<Examples:>

  my $nums = new int[3];
  $nums->[1] = 3;
  
  my $points = new Point[3];
  $points->[1] = Point->new(1, 2);
  
  my $objects : object[] = $points;
  $objects->[2] = Point->new(3, 5);

=head2 new Operator

The C<new> operator is an L<operator|/"Operators"> to create an object or an array.

=head2 Creating Object

The creating object is an L<operator|/"Operators"> to create an object using the C<new> keyword.

  new CLASS_NAME;

The class name must be the name of the L<class|/"Class"> defined by the L<class definition|/"Class Definition">.

The fields of the created object are initialized by L<the rule of type initial value|/"Type Initial Value">.

The reference count of the created object is C<0>. If the object is assigned to a local variable, a class variable, or a field by L</"Assignment Operator">, the reference count is incremented by C<1>.

B<Examples:>

  my $object = new Foo;

=head2 Creating Array

The creating array is an L<operator|/"Operators"> to create an array using the C<new> keyword.

  new BasicType[LENGTH]

The type must be a L<basic type|/"Basic Type">.

The type of length must be the L<int type|/"int Type"> or the type that become L<int type|/"int Type"> after the L<numeric widening type conversion|/"Numeric Widening Type Conversion">.

If the length is lower than C<0>, an exception is thrown.

All elements of the array are initialized by L<the rule of type initial value|/"Type Initial Value">.

The type of created array is the L<array type|/"Array Types">.

B<Examples:>

  my $nums = new int[3];
  my $objects = new Foo[3];
  my $objects = new object[3];
  my $values = new Complex_2d[3]

=head3 Multi Dimensional Array

Multi dimensional arrays can be created.

  new BasicType[][LENGTH]
  new BasicType[][]...[LENGTH]

B<Examples:>

  # 2 dimentional int array
  my $nums = new int[][3];
  
  # 3 dimentional int array
  my $nums = new int[][][3];

The max dimention is C<255>.

=head2 Array Initialization

The array initialization is an L<operator|/"Operators"> to create an array and initialize the array easily.

  []
  [ELEMENT1, ELEMENT2, ELEMENT3]

The array initialization create an L<array|/"Array"> that has the length of the elements.

And the array is initialized by the elements.

And the created array is returned.

The type of the created array is the type that C<1> dimension is added to the type of the first element.

If no element is specified, the type of the create array becomes L<any object type|/"Any Object Type">.

B<Examples:>

  # int array
  my $nums = [1, 2, 3];
  
  # double array
  my $nums = [1.5, 2.6, 3.7];
  
  # string array
  my $strings = ["foo", "bar", "baz"];

The first example is same as the following codes.

  # int array
  my $nums = new int[3];
  $nums->[0] = 1;
  $nums->[1] = 2;
  $nums->[2] = 3;

The array initialization has another syntax using C<{}>. 

  {}
  {ELEMENT1, ELEMENT2, ELEMENT3, ELEMENT4}

This is same as above array init syntax, but the type of the created array is always L</"Any Object Array Type"> C<object[]>.

And if the length of the elements is odd number, a compilation error will occur.

B<Examples:>

  # Key values empty
  my $key_values = {};
  
  # Key values
  my $key_values = {foo => 1, bar => "Hello"};

=head2 Method Calls

Method calls are L</"Class Method Call"> and L</"Instance Method Call">.

=head3 Class Method Call

A method defined as the L<class method|/"Class Method"> can be called using the class method call.

  ClassName->MethodName(ARGS1, ARGS2, ...);

If the number of arguments does not correct, a compilation error will occur.

If the types of arguments have no type compatible, a compilation error will occur.

B<Examples:>

  my $ret = Foo->bar(1, 2, 3);

=head3 Instance Method Call

A method defined as the L<instance method|/"Instance Method"> can be called using the instance method call.

  Object->MethodName(ARGS1, ARGS2, ...);

If the number of arguments does not correct, a compilation error will occur.

If the types of arguments have no type compatible, a compilation error will occur.

B<Examples:>
  
  $object->bar(5, 3. 6);

=head3 Current Class

B<&> before method name means the current class. You can call method using C<&> keyword instead of the current class name.

B<Examples:>

  class Foo {
    
    static method test : void () {
      # This means Foo->sum(1, 2)
      my $ret = &sum(1, 2);
    }
  
    static method sum : int ($num1 : int, $num2 : int) {
      return $num1 + $num2;
    }
    
  }

=head2 Reference Operator

The reference operator C<\> is the L<operator|/"Operators"> to create a L<reference|/"Reference">.

  \ OPERAND

The operand must be a L<local variable|/"Local Variable"> that type is a L<numeric type|/"Numeric Types"> or a L<multi-numeric type|/"Multi-Numeric Types">. Otherwise a compilation error will occur.

The return type is the L<reference type|/"Reference Type"> of the operand.

B<Examples:>
  
  # Create the reference of a numeric type
  my $num : int;
  my $num_ref : int* = \$num;
  
  # Create the reference of a multi-numeric type
  my $z : Complex_2d;
  my $z_ref : Complex_2d* = \$z;

=head2 Dereference Operators

The dereference operators are the L<operatoers|/"Operators"> to perform a deference.

=head3 Getting value by Dereference

Obtaining a value by Dereference is an operation to obtain the actual value from Reference. It was designed to realize the C joint operator C<*>.

  $ VARIABLE

The variable Type must be Reference Type, otherwise a compilation error will occur.

The value obtained by Dereference returns L</"Expressions">.

    B<Example of getting value by Dereference>

  my $num : int;
  my $num_ref : int* = \$num;
  my $num_deref : int = $$num_ref;
  
  my $z : Complex_2d;
  my $z_ref : Complex_2d* = \$z;
  my $z_deref : Complex_2d = $$z_ref;

=head3 Setting the value with Dereference

Setting a value with Dereference is an operation to set the actual value from Reference. It was designed to realize the C joint operator C<*>.

  $ VARIABLE = OPERAND

The variable Type must be Reference Type, otherwise a compilation error will occur.

The type of Expression must match the type of the variable when dereferenced, otherwise a compilation error will occur.

Setting a value with Dereference returns the set value. This is L</"Expressions">.

    B<Example of setting values ​​with Dereference>

  my $num : int;
  my $num_ref : int* = \$num;
  $$num_ref = 1;
  
  my $z : Complex_2d;
  my $z_ref : Complex_2d* = \$z;
  
  my $z2 : Complex_2d;
  
  $$z_ref = $z2;


=head3 Getting Multi-Numeric Field via Dereference

B<Getting Multi-Numeric Field via Dereference Expression> is an L<operator|/"Operators"> to get Field of L</"Multi-Numeric Value"> via L</"Dereference">. This is one syntax of the L<field access|/"Field Access">

  INVOCANT->{FIELD_NAME}

Invocant Expression is L</"Multi-Numeric Reference Type">.

If the field names does not found in the L</"Class">, a compilation error will occur

Getting Multi-Numeric Field via Dereference Expression returns the field value in the Multi-Numeric Value.

Retrun Type is The L</"Types"> of the Field.

B<Examples:>

  my $z : Complex_2d;
  my $z_ref = \$z;
  my $re = $z_ref->{re};

=head3 Setting Multi-Numeric Field via Dereference

Setting Multi-Numeric Field Expression via Dereference is an L<operator|/"Operators"> to set Field of L</"Multi-Numeric Value"> via L</"Dereference"> using L</"Assignment Operator">. This is one syntax of the L<field access|/"Field Access">.

  INVOCANT->{FIELD_NAME} = RIGHT_OPERAND

Invocant Expression is L</"Multi-Numeric Reference Type">.

If the field names does not found in the L</"Class">, a compilation error will occur

Setting Multi-Numeric Field via Dereference Expression returns the value of Field after setting.

The assignment must satisfy the L<type assignability|/"Type Assignability">.

Return Value Type is the type of Field.

B<Examples:>

  my $z : Complex_2d;
  my $z_ref = \$z;
  $z_ref->{re} = 2.5;

=head2 Getting Current Class Name

The getting current class name C<__CLASS__> is an L<operator|/"Operators"> to get the current class name.

  __CLASS__

B<Examples:>

  class Foo::Bar {
    static method baz : void () {
      # Foo::Bar
      my $class_name = __CLASS__;
    }
  }

=head2 Getting Current File Name

The getting current file name C<__FILE__> is an L<operator|/"Operators"> to get the current file name.

  __FILE__

Current File Name means the relative path from the base path of the module file. For example, if the Module Loaded Path is "/mypath" and the Module name is "Foo::Bar", the absolute path is "/mypath/SPVM/Foo/Bar.spvm" and the relative path is "SPVM/Foo/Bar.spvm". "SPVM/Foo/Bar.spvm" is Current File Name.

B<Examples:>

  # SPVM/Foo/Bar.spvm
  class Foo::Bar {
    static method baz : void () {
      # Get the current file name - SPVM/Foo/Bar.spvm
      my $file_name == __FILE__;
    }
  }
  class Foo::Bar2 {
    static method baz : void () {
      # Get the current file name - SPVM/Foo/Bar.spvm
      my $file_name == __FILE__;
    }
  }

=head2 Getting Current Line Number

The getting current line number C<__LINE__> is an L<operator|/"Operators"> to get the current line number of the current file.

  __LINE__

B<Examples:>

  class Foo::Bar {
    static method baz : void () {
      # Get the current line number - 4
      my $line = __LINE__;
    }
  }

=head2 Anon Method

The anon method is an L<operator|/"Operators"> to define an L<anon calss|/"Anon Class"> and define an L<instance method|/"Instance Method"> that has 0-length name and create the object by the L<new|/"Creating Object"> operator.

  method : TYPE_NAME  (ARGS1 : TYPE1, ARGS2 : TYPE2, ...) {
  
  }

B<Examples:>
  
  # Anon method
  class Foo::Bar {
    method some_method : void () {
      my $comparator = (Comparator)method : int ($x1 : object, $x2 : object) {
        my $point1 = (Point)$x1;
        my $point2 = (Point)$x2;
        
        return $point1->x <=> $point2->x;
      };
    }
  }

See also L<Comparator|SPVM::Comparator>.

The above example is same as the following codes.

  class Foo::Bar {
    method some_method : void () {
      my $comparator = (Comparator)new Foo::Bar::anon::3::31;
    }
  }

  class Foo::Bar::anon::3::31 : public {
    method : int ($x1 : object, $x2 : object) {
      my $point1 = (Point)$x1;
      my $point2 = (Point)$x2;
      
      return $point1->x <=> $point2->x;
    }
  }

=head3 Capture

The capture is a syntax to pass L<local variables|/"Local Variable"> to an L<anon method|/"Anon Method">.

  # Capture
  [VAR_NAME1 : Type1, VAR_NAME2 : Type2] method METHOD_NAME : int ($x1 : object, $x2 : object) {
  
  };

B<Examples:>

  class Foo::Bar {
    method some_method : void () {
      my $foo = 1;
      my $bar = 5L;
      my $comparator = (Comparator)[$foo : int, $bar : long] method : int ($x1 : object, $x2 : object) {
        print "$foo\n";
        print "$bar\n";
      };
    }
  }

A capture is actually implemented as a L<field|/"Field">.

The above example is same as the following codes.

  class Foo::Bar {
    method some_method : void () {
      my $foo = 1;
      my $bar = 5L;
      
      my $anon = new Foo::Bar::anon::5::61;
      $anon->{foo} = $foo;
      $anon->{bar} = $bar;
      my $comparator = (Comparator)$anon;
    }
  }

  class Foo::Bar::anon::5::61 : public {
    has foo : public int;
    has bar : public long;
    
    method : int ($x1 : object, $x2 : object) {
      print "$self->{foo}\n";
      print "$self->{bar}\n";
    }
  }

=head1 Statements

Statements are the parts of syntax that can be written directly under L</"Scope Blocks">.

=head2 empty Statement

An empty statement is a L<statement|/"Statements"> that do nothing and ends with just C<;>.

  ;

=head2 Operator Statement

The operator statement is the L<statement|/"Statements"> that executes an L<operator|/"Operators">.

A operator statement is composed of an L<operator|/"Operators"> and C<;>.

  OPERATOR;

The operator must be a L<value-returing operator|/"Value-Returning Operators">.

B<Examples:>

  1;
  $var;
  1 + 2;
  foo();
  my $num = 1 + 2;

=head2 if Statement

The C<if> statement is a L<statement|/"Statements"> for conditional branching.

  if (CONDITION) {
  
  }

The condition L</"Bool Type Conversion"> is executed and Block is executed if the value is non-zero.

If you want to write more than one condition, you can continue with "elsif Statement". The condition determination is performed from above, and each Expression is L</"Bool Type Conversion"> is executed, and a corresponding Block is executed if the value is non-zero.

  if (CONDITION) {
  
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

B<Examples:>

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

When a variable is declared in the conditional part of if Statement, it must be surrounded by invisible L</"Simple Block">. Be aware that elsif is internally expanded into if Statement and else Statement.

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

=head2 unless Statement

The C<unless> statement is a L<statement|/"Statements"> for conditional branches. 

  unless (CONDITION) {
    
  }

This is the same as the following L<if Statement|/"if Statement">.

  if (!CONDITION) {
    
  }

=head2 switch Statement

The C<switch> statement is a L<statement|/"Statements"> for conditional branching with an integer of L</"int Type"> as a condition. Faster than if Statement if the condition is an integer of L</"int Type"> and there are many branches.

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

As the condition Expression, L</"Expressions"> can be specified. L</"Bool Type Conversion"> is executed for the condition Expression.

The constants specified in L</"case Statement"> are L</"byte Type"> or L</"int Type"> constants. must be. For a constant of L</"byte Type">, type conversion to L</"int Type"> at compile-time. Will be done. The value of enumType and Constant Method of L</"int Type"> are constants of L</"int Type">. As it is expanded at the time of syntax analysis, it can be used.

The constants specified in the case statement must not overlap. If there are duplicates, a compilation error will occur

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

B<Examples:>

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

The C<case> statement is a L<statement|/"Statements"> that can be used in a switch block to specify conditions. For more information on case statements, see the L</"switch Statement"> description.

=head2 default Statement

The C<default> statement is a L<statement|/"Statements"> that can be used in the switch block to specify the default condition. For more information on the default Statement, see the L</"switch Statement"> description.

=head2 while Statement

The C<while> statement is a L<statement|/"Statements"> for repeating.

  while (CONDITION) {
  
  }

L</"Expressions"> can be described in the condition Expression. L</"Bool Type Conversion"> is executed for condition Expression, and if the value is not 0, Block is executed. Exit the otherwise Block.

B<Examples:>

An example of a while Statement.

  my $i = 0;
  while ($i <5) {
  
    print "$i \ n";
  
    $i++;
  }

Inside the while block, you can leave the while block by using L</"last Statement">.

  while (1) {
    last;
  }

Inside a while block, you can use L</"next Statement"> to move to the condition immediately before the next condition Expression.

  my $i = 0;
  while ($i <5) {
  
    if ($i == 3) {
      $i++;
      next;
    }
  
    print "$i \ n";
    $i++;
  }

The while Statement is internally enclosed by an invisible L</"Simple Block">.

  {
    while (CONDITION) {
    $i++;
  }
  
  # After expansion
  my $num = 5;
  {
    while (my $num = 3) {
  
      $i++;
    }
  }

=head2 for Statement

The C<for> Statement is a L<statement|/"Statements"> for repeating.

  for (INIT_STATEMENT; CONDITION; INCREMENT_STATEMENT) {
  
  }

L</"Expressions"> can be described in the initialization Expression. Generally, write Expression such as initialization of loop variable. Initialization Expression can be omitted.

Condition Expression, L</"Expressions"> can be described. L</"Bool Type Conversion"> is executed for condition Expression, and if the value is not 0, Block is executed. Exit the otherwise block.

L</"Expressions"> can be described in INCREMENT_STATEMENT. Generally, Expression of Increment of loop variable is described. INCREMENT_STATEMENT can be omitted.

for Statement has the same meaning as the following while Statement. INCREMENT_STATEMENT is executed at the end of Block. Initialization Expression is enclosed in L</"Simple Block">.

  {
    INIT_STATEMENT;
    while (CONDITION) {
  
  
      INCREMENT_STATEMENT;
    }
  }

B<Exampels fo for statements:>

  # for statements
  for (my $i = 0; $i <5; $i++) {
  
    print "$i \ n";
  }

Inside the for Block, you can exit the for Block using L</"last Statement">.

  for (INIT_STATEMENT; CONDITION; INCREMENT_STATEMENT) {
  
  }

Inside the for Block, you can use L</"next Statement"> to move immediately before the next INCREMENT_STATEMENT to be executed.

  for (my $i = 0; $i <5; $i++) {
  
    if ($i == 3) {
      next;
    }
  }

=head2 return Statement

The C<return> statement is a L<statement|/"Statements"> to get out of the method. The object assigned to the mortal variable is automatically released.

  return;

If there is a Return Value, L</"Expressions"> can be specified.

  return EXPRESSION;

If the Return Value Type in L</"Method Definition"> is L</"void Type">, Expression Must not exist, otherwise a compilation error will occur.

L</"Method Definition">, if the Return Value Type is other than L</"void Type">, Expression Must match the type of, otherwise a compilation error will occur.

=head2 next Statement

The C<next> statement is a L<statement|/"Statements"> to move to the beginning of the next loop block.

  next;

See also L</"while Statement">, L</"for Statement">.

=head2 last Statement

The C<last> statement" is a L<statement|/"Statements"> to move to the outside of the loop block.

  last;

See also L</"while Statement">, L</"for Statement">.

=head2 break Statement

The C<break> statement is a L<statement|/"Statements"> to move to the outside of the L<switch block|/"switch Block">.

  break;

See also L</"switch Statement">.

=head2 warn Statement

The C<warn> statement is a L<statement|/"Statements"> to print a warning string to the standard error.

  warn OPERNAD;

The operand must be L</"String Type">.

If the end character of the string is C<\n>, C<warn> statement prints the string itself.

If not, the current file name and current line number are added to the end of the string.

If the value of the operand is an L<undef|/"Undefined Value">, print "Warning: something's wrong".

The buffer of the standard error is flushed after the printing.

=head2 die Statement

The C<die> statement is a L<statement|/"Statements"> to L<throw an exception|/"Throwing Exception">.

  die OPERAND;

The operand must be the L<string type|/"String Type">. If not a compilation error will occur.

You can specify the error message to the operand.

  # Throw an exception
  die "Error";

The error message is set to the L<exception variable|/"Exception Variable"> C<$@>.

If an exception is thrown, the program prints the error message to the standard error with the stack traces and finishes with error code C<255>.

The stack traces constain the class names, the method names, the file names and the line numbers.

  Error
  from TestCase::Minimal->sum2 at SPVM/TestCase/Minimal.spvm line 1640
  from TestCase->main at SPVM/TestCase.spvm line 1198

The exception can be catched using an L<eval block|/"Exception Catching">.

B<Examples:>
  
  # Catch the exception
  eval {
    # Throw an exception
    die "Error";
  };
  
  # Check the exception
  if ($@) {
    # ...
  }

=head2 print Statement

The C<print> statement is a L<statement|/"Statements"> to print a L<string|/"String"> to the standard output.

  print OPERAND;

The oeprand must be a L<string type|/"String Type">.

If the value of the operand is an L<undef|/"Undefined Value">, print nothing.

=head2 make_read_only Statement

The C<make_read_only> statement is a L<statement|/"Statements"> to make the L<string|/"Strings"> read-only.

  make_read_only OPERAND;

The oeprand must be a L<string type|/"String Type">.

Read-only strings can't be cast to L<string type|/"String Type"> qualified by L<mutable|/"mutable Type Qualifier">.

  # A string
  my $string = new_string_len 3;
  
  # Make the string read-only
  make_read_only $string;
  
  # The conversion to the string type qualified by mutable throw an exception.
  my $string_mut = (mutable string)$string;

=head2 weaken Statement

The C<weaken> statement is a L<statement|/"Statements"> to create a L<weak reference|/"Weak Reference">.

  weaken OBJECT->{FIELD_NAME};

The type of the object must be the L<class type|/"Class Type">, otherwise a compilation error will occur.

If the field name is not found, a compilation error will occur.

The type of the field targetted by the C<weaken> statement is not an L<object type|/"Object Types">, a compilation error will occur.

See L</"Weak Reference"> to know the behavior of the C<weaken> statement.

B<Examples:>

  # weaken
  weaken $object->{point};

=head2 unweaken Statement

The C<unweaken> statement is a L<statement|/"Statements"> to unweakens a L<weak reference|/"Weak Reference">.

  unweaken OBJECT->{FIELD_NAME};

The type of the object must be the L<class type|/"Class Type">, otherwise a compilation error will occur.

If the field name is not found, a compilation error will occur.

The type of the field targetted by the C<unweaken> statement is not an L<object type|/"Object Types">, a compilation error will occur.

See L</"Weak Reference"> to know the behavior of the C<unweaken> statement.

B<Examples:>

  # unweaken
  unweaken $object->{point};

=head1 Types

SPVM is a static type language. All data has a static type.

L</"Local Variable Declaration">, L</"Field Definition">, L</"Class Variable Definition">, and B<Arguments> and B<Return Value> of L</"Method Definition"> must specify B<Type>.

In L</"Local Variable Declaration">, L</"Type Inference"> can be used.

=head2 Type Initial Value

Local Variable Initial Value are described in L</"Class Variable Initial Value">.

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
      <b>Multi-Numeric Types</b>
    </td>
    <td>
      All Field is 0
    </td>
  </tr>
</table>

=end html

=head2 Numeric Types

Numeric Types are L</"Integral Types"> and L</"Floating Point Types">.

=head3 Numeric Types Order

L</"Numeric Types"> has the type order. The order is "byte", "short", "int", "long", "float", "double" from the smallest.

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

See L</"Arithmetic Operators"> for integer calculation.

Note that SPVM has only B<singed> integral types, and doesn't have B<unsigned> integral types.

=head2 byte Type

C<byte> type is a L</"Integral Types"> that represents a signed 8-bit integer. This is the same type as C<int8_t> type of C language.

=head2 short Type

C<short> type  is a L</"Integral Types"> that represents a signed 16-bit integer. This is the same type as C<int16_t> type of C language.

=head2 int Type

C<int> type is  is a L</"Integral Types"> that represents signed 32-bit integer. This is same as C<int32_t> type of C language.

=head2 long Type

C<long> type is a L</"Integral Types"> that represents a signed 64-bit integer. This is the same type as C<int64_t> type of C language.

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

See L</"Arithmetic Operators"> for floating-point calculation.

=head2 float Type

C<float> type is a L</"Floating Point Types"> that represents a single precision(32bit) floating point. This is the same type as C<float> type of C language.

=head2 double Type

C<double> type is a L</"Floating Point Types"> that represents a double precision(64bit) floating point. This is the same type as C<double> type of C language.

=head2 Class Type

The class type is the type that can create the object using a L<new operator|/"new Operator">.

  new ClassType;

=head2 Pointer Type

The pointer type is the type that has a L<class descriptor|/"Class Descriptors"> C<pointer_t>.

  # Pointer Type
  class Foo: pointer_t {
  
  }

A pointer type is a L<class type|/"Class Type">.

=head2 Basic Object Types

Basic object types are the L<class type|/"Class Type">, the L<array type|/"Array Types">, the L<string type|/"String Type">, and the L<any object type|/"Any Object Type">.

=head2 Object Types

Object types are the L<basic object types|/"Basic Object Types"> and the L<array types|/"Array Types">.

A object type can be assigned to a L<any object type|/"Any Object Type">.

  my $object: object = new Foo;
  my $object: object = "abc";

=head2 Numeric Object Types

A numeric object type is the L<object type|/"Object Types"> that is corresponding to the L<numeric type|/"Numeric Types">.

The list of numeric object types:

=begin html

<table>
  <tr>
    <th>
      <b>Numeric Object Types</b>
   </th>
    <th>
      Corresponding Numeric Types
   </th>
  </tr>
  <tr>
    <td>
      Byte
    </td>
    <td>
      byte
    </td>
  </tr>
  <tr>
    <td>
      Short
    </td>
    <td>
      short
    </td>
  </tr>
  <tr>
    <td>
      Int
    </td>
    <td>
      int
    </td>
  </tr>
  <tr>
    <td>
      Long
    </td>
    <td>
      long
    </td>
  </tr>
  <tr>
    <td>
      Float
    </td>
    <td>
      float
    </td>
  </tr>
  <tr>
    <td>
      Double
    </td>
    <td>
      double
    </td>
  </tr>
</table>

=end html

The document of numeric object types:

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

See also L</"Boxing Type Conversion"> and L</"Unboxing Type Conversion">.

=head2 Undefined Type

The undefined type is the type of L<undef|/"Undefined Value"> value.

=head2 Interface Type

The interface type is a type that is defined using a C<class> keyword and a L<class descriptor|/"Class Descriptors"> C<interface_t>.

  class Stringable: interface_t {
    required method to_string : string ();
  }

See also L</"Interface">.

Note that interface types are not L<class types|/"Class Types"> although they are defined by C<class> keyword.

=head2 Any Object Type

Any Object Type is represented by "object". Designed to represent the "void *" Type in C.

  my $object: object;

You can methodstitute the value of "Object Types" for Any Object Type.

  my $object: object = new Foo;
  my $object: object = "abc";
  my $object: object = new Foo [3];

=head2 void Type

B<void Type> is a special Type that can only be used in the return type of L</"Method Definition"> and indicates the method has no Return Value.

  void

=head2 Basic Type

The basic types are L<numeric types|/"Numeric Types">, L<multi-numeric types|/"Multi-Numeric Types">, the L<class type|/"Class Type">, the L<any object type|/"Any Object Type">, and the L<string type|/"String Type">.

Another definition of basic types are the types that is not L<array types|"Array Types"> and can become the element of L<array types|"Array Types">.

=head2 Array Types

Array Types represents multiple continuous data areas. L</"Basic Type"> can be an Array.

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

Array Types is L</"Object Types">.

Use new Operator to create an Array. In the following example, L</"int Type"> Array with 3 elements is created.

my $nums = new int [3];

You also use new Operator when creating a Multi-Dimensional Array.The following example creates an Array of int[] Type with 3 elements.

my $nums = new int[] [3];

=head3 Numeric Array Types

Numeric Array Types means L</"Numeric Types"> with the element L</"Array Types"> It is.

B<Numeric Array Types list>

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

Data represented by Numeric Array Types must have elements whose size is L</"Numeric Types">, and must be consecutive by the number of Array Length.

All elements of Numeric Array Types are initialized by L</"Type Initial Value"> when the L<creating array|/"Creating Array"> is performed.

=head3 byte[] Type

The C<byte[]> type is an L<array type|/"Array Types"> that the element type is C<byte>.

  byte[]

=head3 Object Array Types

Object array types are L</"Array Types"> that the type of the element is an L<object type|/"Object Types">.

B<Examples:>

  # Object array types
  my $points : Point[];
  my $points_2dim : Point[][];
  my $stringables : Stringable[];
  my $strings : string[];
  my $objects : object[];

=head3 String Array Types

String array types are L</"Array Types"> that the type of the element is the L<string type|/"String Types">.

B<Examples:>

  # String array types
  my $strings : string[];

=head3 Class Array Types

Class array types are L</"Array Types"> that the type of the element is the L<class type|/"Class Types">.

B<Examples:>

  # Class array types
  my $points : Point[];

=head3 Interface Array Types

Interface array types are L</"Array Types"> that the type of the element is the L<interface type|/"Interface Type">.

B<Examples:>

  # Interface array types
  my $stringables : Stringable[];

=head3 Multi-Dimensional Array Type

The multi-dimensional array type is the L<array type|/"Array Types"> that the type of the element is an L<array type|/"Array Types">.

B<Examples:>

  # Multi-dimensional array types
  my $nums_2dim : Int[][];

=head3 Multi-Numeric Array Types

A multi-numeric array type is an L<array type|/"Array Types"> that the basic type is a L<multi-numeric type|"Multi-Numeric Types">.

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

The byte size of the element is the total byte size of the fields of the L<multi-numeric type|"Multi-Numeric Types">.

For example, The byte size of the element of L<Complex_2d|SPVM::Complex_2d> is 16 bytes (2 * 8 bytes).

The object of the multi-numeric array type can be created by the L<new|/"Creating Array"> operator.

  my $complex_nums = new Complex_2d[10];

=head3 Any Object Array Type

The any object array type C<object[]> is the type that any L<object array type|/"Object Array Types"> can be assigned.

  # Any object array Type
  my $array : object[] = new Point[3];
  my $array : object[] = new object[3];
  my $array : object[] = new Point[][3];

If a invalid type is assigned, a compilation error will occur.

Any Object Array Type is an L<array type|/"Array Types">.

You can get the array length using the L<array length operator|/"Array Length Operator">.

  my $array : object[] = new Int[3];
  
  # Getting the length of the element of Any Object Array Type
  my $length = @$array;

You can get and set the element using the L<get array element|/"Getting Array Element"> syntax and the L<set array element|/"Setting Array Element">.
 
  # Getting the element of any object array
  my $num = (Int)$array->[0];
  
  # Setting the element of any object array
  $array->[0] = Int->new(5);

When setting the element of any object array, the element type is checked. If the dimension of the element is not the dimension of the array - C<1>, an L<exception|/"Exception"> is thrown.

=head2 String Type

The C<string> type is a L<type|/"Types"> for the L</"String">.

  string

C<string> type can be qualified by L</"mutable Type Qualifier">.

  mutable string

B<Examples:>
  
  # string type
  my $message : string = "Hello";
  my $message : mutable string = new_string_len 256;

=head2 Multi-Numeric Types

Multi-Numeric Types are a type that can represent continuous numerical values.

Multi-Numeric Types can be defined by specifying "mulnum_t" Descriptor in L</"Class Definition">.

  class Complex_2d : mulnum_t {
    has x : int;
    has y : int;
    has z : int;
  }

See L</"Values ​​"> for a detailed explanation of Multi-Numeric Types.

=head2 Reference Type

Reference Type is a Type that can store the address of a variable. Add C<*> after L</"Numeric Types"> or L</"Multi-Numeric Types"> You can define it.

  my $num : int;
  my $num_ref : int* = \$num;
  
  my $z : Complex_2d;
  my $z_ref : Complex_2d* = \$z;

Only the address of the Local Variable acquired by L</"Reference Operator"> can be assigned to the value of Reference Type.

If only Local Variable Declaration of Reference Type is performed, a compilation error will occur

Reference Type can be used as Type of L</"Local Variable Declaration">. The address of the Local Variable must be stored by the Reference Operator. In case of only Local Variable Declaration, a compilation error will occur

Reference Type can be used as Type of argument in L</"Method Definition">.

Reference Type cannot be used as Return Value Type in L</"Method Definition">.

Reference Type cannot be used as the type of Field in L</"Class Definition">.

Reference Type cannot be used as the type of Class Variable in L</"Class Definition">.

If the Reference Type is used at an Invalid location, a compilation error will occur

See L</"Reference"> for a detailed explanation of Reference.

=head2 Reference Types

Reference Types are L<Numeric Reference Type> and L<Multi-Numeric Reference Type>.

=head2 Numeric Reference Type

Numeric Reference Type means L</"Numeric Types"> for L</"Reference Type">. Says.

=head2 Multi-Numeric Reference Type

Multi-Numeric Reference Type means L</"Reference Type"> for L</"Multi-Numeric Types"> variables. > Means.

=head1 Type Inference

Omitting L</"Types"> when L</"Local Variable Declaration"> by Type Inference can. Type Inference is always performed by the type on the Right side of Assignment Operator.

  # int
  my $num = 1;
  
  # double
  my $num = 1.0;
  
  # Foo
  my $foo = new Foo;

=head2 Type Qualifiers

Type qualifiers qualify the type.

  QUALIFIER TYPE

=head3 mutable Type Qualifier

The C<mutable> type qualifier is used to allow to set the character of the string.

  my $string : mutable string;

B<Examples:>
  
  # Mutable string
  my $message = (mutable string)"abc";
  $message->[0] = 'd';

=head1 Type Assignability

The type assignability at compile-time is explained.

The assignability is false, a compilation error will occur.

=head2 Type Assignability to Numeric

Explains the type assignability to the L<numeric types|"Numeric Types">.

=head3 Type Assignability from Numeric to Numeric

If the L<nemric type order|/"Numeric Types Order"> of the left operand is greater than or equal to the L<nemric type order|/"Numeric Types Order"> of the right operand, the assignability is true.

If the L<nemric type order|/"Numeric Types Order"> of the left operand is greater than the L<nemric type order|/"Numeric Types Order"> of the right operand, the L<numeric widening type conversion|/"Numeric Widening Type Conversion"> is performed.

=begin html

<table>
  <tr><th>Assignability</th><th>To</th><th>From</th><th><a href="#Implicite-Type-Conversion">Implicite Type Conversion</a></th></tr>
  <tr><td>True</td><td>byte</td><td>byte</td><td>None</td></tr>
  <tr><td>True</td><td>short</td><td>short</td><td>None</td></tr>
  <tr><td>True</td><td>int</td><td>int</td><td>None</td></tr>
  <tr><td>True</td><td>long</td><td>long</td><td>None</td></tr>
  <tr><td>True</td><td>float</td><td>float</td><td>None</td></tr>
  <tr><td>True</td><td>double</td><td>double</td><td>None</td></tr>
  <tr><td>True</td><td>short</td><td>byte</td><td><a href="#Numeric-Widening-Type-Conversion">Numeric Widening Type Conversion</a></td></tr>
  <tr><td>True</td><td>int</td><td>byte</td><td><a href="#Numeric-Widening-Type-Conversion">Numeric Widening Type Conversion</a></td></tr>
  <tr><td>True</td><td>long</td><td>byte</td><td><a href="#Numeric-Widening-Type-Conversion">Numeric Widening Type Conversion</a></td></tr>
  <tr><td>True</td><td>float</td><td>byte</td><td><a href="#Numeric-Widening-Type-Conversion">Numeric Widening Type Conversion</a></td></tr>
  <tr><td>True</td><td>double</td><td>byte</td><td><a href="#Numeric-Widening-Type-Conversion">Numeric Widening Type Conversion</a></td></tr>
  <tr><td>True</td><td>int</td><td>short</td><td><a href="#Numeric-Widening-Type-Conversion">Numeric Widening Type Conversion</a></td></tr>
  <tr><td>True</td><td>long</td><td>short</td><td><a href="#Numeric-Widening-Type-Conversion">Numeric Widening Type Conversion</a></td></tr>
  <tr><td>True</td><td>float</td><td>short</td><td><a href="#Numeric-Widening-Type-Conversion">Numeric Widening Type Conversion</a></td></tr>
  <tr><td>True</td><td>double</td><td>short</td><td><a href="#Numeric-Widening-Type-Conversion">Numeric Widening Type Conversion</a></td></tr>
  <tr><td>True</td><td>long</td><td>int</td><td><a href="#Numeric-Widening-Type-Conversion">Numeric Widening Type Conversion</a></td></tr>
  <tr><td>True</td><td>float</td><td>int</td><td><a href="#Numeric-Widening-Type-Conversion">Numeric Widening Type Conversion</a></td></tr>
  <tr><td>True</td><td>double</td><td>int</td><td><a href="#Numeric-Widening-Type-Conversion">Numeric Widening Type Conversion</a></td></tr>
  <tr><td>True</td><td>float</td><td>long</td><td><a href="#Numeric-Widening-Type-Conversion">Numeric Widening Type Conversion</a></td></tr>
  <tr><td>True</td><td>double</td><td>long</td><td><a href="#Numeric-Widening-Type-Conversion">Numeric Widening Type Conversion</a></td></tr>
  <tr><td>True</td><td>double</td><td>float</td><td><a href="#Numeric-Widening-Type-Conversion">Numeric Widening Type Conversion</a></td></tr>
</table>

=end html

B<Examples:>
  
  # int to int
  my $num : int = 3;
  
  # byte to int
  my $num : int = (byte)5;
  
  # double to double
  my $num : double = 4.5;
  
  # float to double
  my $num : double = 4.5f;

If the L<nemric type order|/"Numeric Types Order"> of the left operand is lower than the L<nemric type order|/"Numeric Types Order"> of the right operand, the type assignability is conditional true.

The condition is that the right operand is a L<interger literal|Integer Literal> and the value is between the max and minimal value of the type of the left operand.

If the condition is ture, the L<numeric narrowing type conversion|/"Numeric Narrowing Type Conversion"> is performed.

=begin html

<table>
  <tr><th>Assignability</th><th>To</th><th>From</th><th><a href="#Implicite-Type-Conversion">Implicite Type Conversion</a></th></tr>
  <tr><td>Conditional True</td><td>byte</td><td>short</td><td><a href="#Numeric Narrowing Type Conversion">Numeric Narrowing Type Conversion</a></td></tr>
  <tr><td>Conditional True</td><td>byte</td><td>int</td><td><a href="#Numeric Narrowing Type Conversion">Numeric Narrowing Type Conversion</a></td></tr>
  <tr><td>Conditional True</td><td>byte</td><td>long</td><td><a href="#Numeric Narrowing Type Conversion">Numeric Narrowing Type Conversion</a></td></tr>
  <tr><td>False</td><td>byte</td><td>float</td><td>None</td></tr>
  <tr><td>False</td><td>byte</td><td>double</td><td>None</td></tr>
  <tr><td>Conditional True</td><td>short</td><td>int</td><td><a href="#Numeric Narrowing Type Conversion">Numeric Narrowing Type Conversion</a></td></tr>
  <tr><td>Conditional True</td><td>short</td><td>long</td><td><a href="#Numeric Narrowing Type Conversion">Numeric Narrowing Type Conversion</a></td></tr>
  <tr><td>False</td><td>short</td><td>float</td><td>None</td></tr>
  <tr><td>False</td><td>short</td><td>double</td><td>None</td></tr>
  <tr><td>Conditional True</td><td>int</td><td>long</td><td><a href="#Numeric Narrowing Type Conversion">Numeric Narrowing Type Conversion</a></td></tr>
  <tr><td>False</td><td>int</td><td>float</td><td>None</td></tr>
  <tr><td>False</td><td>int</td><td>double</td><td>None</td></tr>
  <tr><td>False</td><td>long</td><td>float</td><td>None</td></tr>
  <tr><td>False</td><td>long</td><td>double</td><td>None</td></tr>
  <tr><td>False</td><td>float</td><td>double</td><td>None</td></tr>
</table>

=end html

B<Examples:>
  
  # int to byte
  my $num : byte = 127;

=head3 Type Assignability from NumericObject to Numeric

If the type of the left operand is a L<numeric type|/"Numeric Types"> corresponding to the numeric object type of the right operand and the type of the right operand is a L<numeric object type|/"Numeric Object Type">, the assignability is true.

=begin html

<table>
  <tr><th>Assignability</th><th>To</th><th>From</th><th><a href="#Implicite-Type-Conversion">Implicite Type Conversion</a></th></tr>
  <tr><td>True</td><td>byte</td><td>Byte</td><td>Unboxing Type Conversion</td></tr>
  <tr><td>True</td><td>short</td><td>Short</td><td>Unboxing Type Conversion</td></tr>
  <tr><td>True</td><td>int</td><td>Int</td><td>Unboxing Type Conversion</td></tr>
  <tr><td>True</td><td>long</td><td>Long</td><td>Unboxing Type Conversion</td></tr>
  <tr><td>True</td><td>float</td><td>Float</td><td>Unboxing Type Conversion</td></tr>
  <tr><td>True</td><td>double</td><td>Double</td><td>Unboxing Type Conversion</td></tr>
</table>

=end html

B<Examples:>

  my $int : int = Int->new(3);

  my $double : double = Double->new(3.5);

=head3 Type Assignability from Any Object to Numeric

If the type of the left operand is a L<numeric type|/"Numeric Types"> and the type of the right operand is a L<any object type|/"Any Object Type"> C<object>, the assignability is true.

The L<unboxing type conversion|/"Unboxing Type Conversion"> corresponding to the numeric type is performed.

=begin html

<table>
  <tr><th>Assignability</th><th>To</th><th>From</th><th><a href="#Implicite-Type-Conversion">Implicite Type Conversion</a></th></tr>
  <tr><td>True</td><td>NUMERIC_X</td><td>object</td><td>Unboxing Type Conversion</td></tr>
</table>

=end html

B<Examples:>

  my $int : int = (object)Int->new(3);

  my $double : double = (object)Double->new(3.5);

=head3 Type Assignability from Others to Numeric

If the type of the left operand is a L<numeric type|/"Numeric Types"> and the type of the right operand is other than the types described above, the assignability is false.

=head2 Type Assignability to Multi-Numeric

If the type of the left operand is a L<multi-numeric type|/"Multi-Numeric Types"> and the type of the right operand is the same type of the left operand, the assignability is true.

Otherwise, the assignability is false.

=begin html

<table>
  <tr><th>Assignability</th><th>To</th><th>From</th><th><a href="#Implicite-Type-Conversion">Implicite Type Conversion</a></th></tr>
  <tr><td>True</td><td>MULNUM_X</td><td>MULNUM_X</td><td>None</td></tr>
  <tr><td>False</td><td>MULNUM_X</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

B<Examples:>

  my $z1 : Complex_2d;
  my $z2 : Complex_2d = $z1;

=head2 Type Assignability to Referenece

If the type of the left operand is a L<reference type|/"Reference Types"> and the type of the right operand is the same type of the left operand, the assignability is true.

Otherwise, the assignability is false.

=begin html

<table>
  <tr><th>Assignability</th><th>To</th><th>From</th><th><a href="#Implicite-Type-Conversion">Implicite Type Conversion</a></th></tr>
  <tr><td>True</td><td>REF_X</td><td>REF_X</td><td>None</td></tr>
  <tr><td>False</td><td>REF_X</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

B<Examples:>

  my $num : int = 5;
  my $num_ref : int* = \num;

=head2 Type Assignability to String

If the type of the left operand is the L<string type|/"String Type"> without the L<mutable type qualifier|/"mutable Type Qualifier"> and the type of the right operand is the L<string type|/"String Type">, the assignability is true.

If the type of the left operand is the L<string type|/"String Type"> with the L<mutable type qualifier|/"mutable Type Qualifier"> and the type of the right operand is the L<string type|/"String Type"> with the L<mutable type qualifier|/"mutable Type Qualifier">, the assignability is true.

If the type of the left operand is the L<string type|/"String Type"> with the L<mutable type qualifier|/"mutable Type Qualifier"> and the type of the right operand is the L<string type|/"String Type"> without the L<mutable type qualifier|/"mutable Type Qualifier">, the assignability is false.

If the type of the left operand is the L<string type|/"String Type"> and the type of the right operand is a L<numeric type|/"Numeric Types"> or the L<undef type|/"Undefined Type">, the assignability is true.

If the type of the right operand is a L<numeric type|/"Numeric Types">, the L<Numeric-to-String type conversion|/"Numeric-to-String Type Conversion"> is performed.

=begin html

<table>
  <tr><th>Assignability</th><th>To</th><th>From</th><th><a href="#Implicite-Type-Conversion">Implicite Type Conversion</a></th></tr>
  <tr><td>True</td><td>string</td><td>string</td><td>None</td></tr>
  <tr><td>True</td><td>string</td><td>mutable string</td><td>None</td></tr>
  <tr><td>True</td><td>mutable string</td><td>mutable string</td><td>None</td></tr>
  <tr><td>False</td><td>mutable string</td><td>string</td><td>None</td></tr>
  <tr><td>True</td><td>string</td><td>string</td><td>None</td></tr>
  <tr><td>True</td><td>string</td><td>NUMERIC_X</td><td>Numeric-to-String type conversion</td></tr>
  <tr><td>True</td><td>string</td><td>undef</td><td>None</td></tr>
  <tr><td>False</td><td>string</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

B<Examples:>

  my $string : string = "abc";
  my $num_string : string = 3;
  my $string : string = undef;

=head2 Type Assignability to NumericObject

If the type of the left operand is a L<numeric object type|/"Numeric Object Types"> and the type of the right operand is the same type of the left operand, a L<numeric type|/"Numeric Types"> that is corresponding to the numeric object type, or the L<undef type|/"Undefined Type">, the assignability is true.

Otherwise, the assignability is false.

If the type of the right operand is a L<numeric type|/"Numeric Types">, the L<boxing type conversion|/"Boxing Type Conversion"> is performed.

=begin html

<table>
  <tr><th>Assignability</th><th>To</th><th>From</th><th><a href="#Implicite-Type-Conversion">Implicite Type Conversion</a></th></tr>
  <tr><td>True</td><td>NUMERIC_OBJECT_X</td><td>NUMERIC_OBJECT_X</td><td>None</td></tr>
  <tr><td>True</td><td>NUMERIC_OBJECT_X</td><td>NUMERIC_X</td><td>Boxing type conversion</td></tr>
  <tr><td>True</td><td>NUMERIC_OBJECT</td><td>undef</td><td>None</td></tr>
  <tr><td>False</td><td>NUMERIC_OBJECT</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

B<Examples:>

  my $num_object : Int = Int->new(3);
  my $num_object : Int = 3;
  my $num_object : Int = undef;

=head2 Type Assignability to Class

If the type of the left operand is a L<class type|/"Class Type"> and the type of the right operand is the same type, or the L<undef type|/"Undefined Type">, the assignability is true.

Otherwise, the assignability is false.

=begin html

<table>
  <tr><th>Assignability</th><th>To</th><th>From</th><th><a href="#Implicite-Type-Conversion">Implicite Type Conversion</a></th></tr>
  <tr><td>True</td><td>CLASS_X</td><td>CLASS_X</td><td>None</td></tr>
  <tr><td>True</td><td>CLASS</td><td>undef</td><td>None</td></tr>
  <tr><td>False</td><td>CLASS</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

B<Examples:>

  my $point : Point = Point->new;
  my $point : Point = undef;

=head2 Type Assignability to Interface

If the type of the left operand is an L<interface type|/"Interface Type"> and the type of the right operand is the same type, or the L<undef type|/"Undefined Type">, the assignability is true.

If the type of the left operand is an L<interface type|/"Interface Type"> and the type of the right operand is a L<class type|/"Class Type"> and the class has the same interface of the left operand, the assignability is true.

Otherwise, the assignability is false.

=begin html

<table>
  <tr><th>Assignability</th><th>To</th><th>From</th><th><a href="#Implicite-Type-Conversion">Implicite Type Conversion</a></th></tr>
  <tr><td>True</td><td>INTERFACE_X</td><td>INTERFACE_X</td><td>None</td></tr>
  <tr><td>Conditional True</td><td>INTERFACE_X</td><td>CLASS_Y</td><td>None</td></tr>
  <tr><td>True</td><td>INTERFACE</td><td>undef</td><td>None</td></tr>
  <tr><td>False</td><td>INTERFACE</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

B<Examples:>
  
  # Point has Stringable interface
  my $stringable : Stringable = Point->new_xy(1, 2);
  my $stringable : Stringable = undef;

=head2 Type Assignability to Any Object

If the type of the left operand is the L<any object type|/"Any Object Type"> and the type of the right operand is an L<object type|/"Object Types">, a L<numeric type|/"Numeric Types"> or the L<undef type|/"Undefined Type">, the assignability is true.

Otherwise, the assignability is false.

If the type of the right operand is a L<numeric type|/"Numeric Types">, the L<boxing type conversion|/"Boxing Type Conversion"> is performed.

=begin html

<table>
  <tr><th>Assignability</th><th>To</th><th>From</th><th><a href="#Implicite-Type-Conversion">Implicite Type Conversion</a></th></tr>
  <tr><td>True</td><td>object</td><td>OBJECT_X</td><td>None</td></tr>
  <tr><td>True</td><td>object</td><td>NUMERIC_X</td><td>Boxing type conversion</td></tr>
  <tr><td>True</td><td>object</td><td>undef</td><td>None</td></tr>
  <tr><td>False</td><td>object</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

B<Examples:>

  my $object : object = Point->new;
  my $num_object : object = 3;
  my $object : object = undef;

=head2 Type Assignability to Undefined

If the type of the left operand is the L<undefined type|/"Undefined Type">, the assignability is false.

=begin html

<table>
  <tr><th>Assignability</th><th>To</th><th>From</th><th><a href="#Implicite-Type-Conversion">Implicite Type Conversion</a></th></tr>
  <tr><td>False</td><td>Undefined Type</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

B<Examples:>
  
  # The assignability is false
  undef = Point->new;
  
=head2 Type Assignability to Numeric Array

If the type of the left operand is a L<numeric array type|/"Numeric Array Types"> and the type of the right operand is the same type of the left operand or the L<undef type|/"Undefined Type">, the assignability is true.

Otherwise, the assignability is false.

=begin html

<table>
  <tr><th>Assignability</th><th>To</th><th>From</th><th><a href="#Implicite-Type-Conversion">Implicite Type Conversion</a></th></tr>
  <tr><td>True</td><td>byte[]</td><td>byte[]</td><td>None</td></tr>
  <tr><td>True</td><td>short[]</td><td>short[]</td><td>None</td></tr>
  <tr><td>True</td><td>int[]</td><td>int[]</td><td>None</td></tr>
  <tr><td>True</td><td>long[]</td><td>long[]</td><td>None</td></tr>
  <tr><td>True</td><td>float[]</td><td>float[]</td><td>None</td></tr>
  <tr><td>True</td><td>double[]</td><td>double[]</td><td>None</td></tr>
  <tr><td>True</td><td>NUMERIC[]</td><td>undef</td><td>None</td></tr>
  <tr><td>False</td><td>NUMERIC[]</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

B<Examples:>

  my $nums : int[] = new int[3];
  my $nums : int[] = undef;

=head2 Type Assignability to Multi-Numeric Array

If the type of the left operand is a L<multi-numeric array type|/"Multi-Numeric Array Types"> and the type of the right operand is the same type of the left operand or the L<undef type|/"Undefined Type">, the assignability is true.

Otherwise, the assignability is false.

=begin html

<table>
  <tr><th>Assignability</th><th>To</th><th>From</th><th><a href="#Implicite-Type-Conversion">Implicite Type Conversion</a></th></tr>
  <tr><td>True</td><td>MULNUM_X[]</td><td>MULNUM_X[]</td><td>None</td></tr>
  <tr><td>True</td><td>MULNUM_X[]</td><td>undef</td><td>None</td></tr>
  <tr><td>False</td><td>MULNUM_X[]</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

B<Examples:>

  my $nums : Complex_2d[] = new Complex_2d[3];
  my $nums : Complex_2d[] = undef;

=head2 Type Assignability to String Array

If the type of the left operand is a L<string array type|/"String Array Type"> and the type of the right operand is the same type of the left operand or the L<undef type|/"Undefined Type">, the assignability is true.

Otherwise, the assignability is false.

=begin html

<table>
  <tr><th>Assignability</th><th>To</th><th>From</th><th><a href="#Implicite-Type-Conversion">Implicite Type Conversion</a></th></tr>
  <tr><td>True</td><td>string[]</td><td>string[]</td><td>None</td></tr>
  <tr><td>True</td><td>string[]</td><td>undef</td><td>None</td></tr>
  <tr><td>False</td><td>string[]</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

B<Examples:>

  my $strings : string[] = ["abc", "def"];
  my $strings : string[] = undef;

=head2 Type Assignability to Class Array

If the type of the left operand is a L<class array type|/"Class Array Types"> and the type of the right operand is the same type of the left operand or the L<undef type|/"Undefined Type">, the assignability is true.

Otherwise, the assignability is false.

=begin html

<table>
  <tr><th>Assignability</th><th>To</th><th>From</th><th><a href="#Implicite-Type-Conversion">Implicite Type Conversion</a></th></tr>
  <tr><td>True</td><td>CLASS_X[]</td><td>CLASS_X[]</td><td>None</td></tr>
  <tr><td>True</td><td>CLASS_X[]</td><td>undef</td><td>None</td></tr>
  <tr><td>False</td><td>CLASS_X[]</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

B<Examples:>

  my $points : Point[] = new Point[3];
  my $points : Point[] = undef;

=head2 Type Assignability to Interface Array

If the type of the left operand is an L<interface array type|/"Interface Array Types"> and the type of the right operand is the same type of the left operand or the L<undef type|/"Undefined Type">, the assignability is true.

If the type of the left operand is an L<interface array type|/"Interface Array Types"> and the type of the right operand is a L<class array type|/"Class Array Types"> and its L<basic type|/"Basic Type"> can assign to the basic type of the left operand, the assignability is true.

Otherwise, the assignability is false.

=begin html

<table>
  <tr><th>Assignability</th><th>To</th><th>From</th><th><a href="#Implicite-Type-Conversion">Implicite Type Conversion</a></th></tr>
  <tr><td>True</td><td>INTERFACE_X[]</td><td>INTERFACE_X[]</td><td>None</td></tr>
  <tr><td>True</td><td>INTERFACE_X[]</td><td>undef</td><td>None</td></tr>
  <tr><td>Conditional True</td><td>INTERFACE_X[]</td><td>CLASS_Y[]</td><td>None</td></tr>
  <tr><td>False</td><td>INTERFACE_X[]</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

B<Examples:>

  my $stringables : Stringable[] = new Stringable[3];

  my $stringables : Stringable[] = new Point[3];
  
  my $stringables : Stringable[] = undef;

=head2 Type Assignability to Any Object Array

If the type of the left operand is the L<any object array type|/"Any Object Array Type"> C<object[]> and the type of the right operand is an L<object array type|/"Object Array Type"> or the L<undef type|/"Undefined Type">, the assignability is true.

Otherwise, the assignability is false.

=begin html

<table>
  <tr><th>Assignability</th><th>To</th><th>From</th><th><a href="#Implicite-Type-Conversion">Implicite Type Conversion</a></th></tr>
  <tr><td>True</td><td>object[]</td><td>OBJECT_X[]</td><td>None</td></tr>
  <tr><td>True</td><td>object[]</td><td>undef</td><td>None</td></tr>
  <tr><td>False</td><td>object[]</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

B<Examples:>

  my $any_objects0 : object[];
  my $any_objects : object[] = $any_objects0;

  my $points : Point[];
  my $any_object : object[] = $points;

  my $any_object : object[] = undef;

  my $points_2dim : Point[][];
  my $any_object : object[] = $points_2dim;

  my $stringables : Stringable[];
  my $any_object : object[] = $stringables;
  
  my $strings : string[];
  my $any_object : object[] = $strings;
  
=head2 Type Assignability to Multi-Dimensional Array

If the type of the left operand is a L<multi-dimensional array type|/"Multi-Dimensional Array Type"> and the type of the right operand is the same type of the left operand or the L<undef type|/"Undefined Type">, the assignability is true.

If the L<basic type|/"Basic Type"> of the type of the left operand is an L<interface type|/"Interface Type"> and the L<basic type|/"Basic Type"> of the type of the right operand is a L<class type|/"Class Type"> and the dimension of the type of the right operand is same as the dimension of the type left oerand and the L<basic type|/"Basic Type"> of the type of the right operand has the interface of the L<basic type|/"Basic Type"> of the type of the left operand , the assignability is true.

Otherwise, the assignability is false.

=begin html

<table>
  <tr><th>Assignability</th><th>To</th><th>From</th><th><a href="#Implicite-Type-Conversion">Implicite Type Conversion</a></th></tr>
  <tr><td>True</td><td>MULDIM_X</td><td>MULDIM_X</td><td>None</td></tr>
  <tr><td>True</td><td>object[]</td><td>undef</td><td>None</td></tr>
  <tr><td>Conditional True</td><td>INTERFACE_MULDIM_X[]</td><td>CLASS_MULDIM_Y[]</td><td>None</td></tr>
  <tr><td>False</td><td>object[]</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

B<Examples:>

  my $points_2dim : Point[][];
  my $muldim_array : Point[][] = $points_2dim;

  my $muldim_array : Point[][] = undef;

  my $strings_2dim : String[][];
  my $muldim_array : Stringable[][] = $strings_2dim;

  {
    my $cb = method : string ($object : object) {
      my $point = (Point)$object;
      return $point->to_string;
    };
    my $muldim_array : Stringer[][] = [[$cb]];
  }

=head1 Type Castability

The type castability at compile-time is explained.

The castability is false, a compilation error will occur.

=head2 Type Castability to Numeric

The type castability to the L<numeric types|/"Numeric Types"> is explained.

=head3 Type Castability from Numeric to Numeric

If the type of the left operand is a L<numeric type|/"Numeric Types"> and the type of the right operand is a L<numeric type|/"Numeric Types">, the type castability is true.

If the L<nemric type order|/"Numeric Types Order"> of the left operand is greater than the L<nemric type order|/"Numeric Types Order"> of the right operand, the L<numeric widening type conversion|/"Numeric Widening Type Conversion"> is performed.

If the L<nemric type order|/"Numeric Types Order"> of the left operand is lower than the L<nemric type order|/"Numeric Types Order"> of the right operand, the L<numeric narrowing type conversion|/"Numeric Narrowing Type Conversion"> is performed.

If the L<nemric type order|/"Numeric Types Order"> of the left operand is equal to the L<nemric type order|/"Numeric Types Order"> of the right operand, copying is performed.

=begin html

<table>
  <tr><th>Type Castability</th><th>To</th><th>From</th><th><a href="#Type-Conversion">Type Conversion or Copying</a></th></tr>
  <tr><td>True</td><td>byte</td><td>byte</td><td>Copying</td></tr>
  <tr><td>True</td><td>short</td><td>short</td><td>Copying</td></tr>
  <tr><td>True</td><td>int</td><td>int</td><td>Copying</td></tr>
  <tr><td>True</td><td>long</td><td>long</td><td>Copying</td></tr>
  <tr><td>True</td><td>float</td><td>float</td><td>Copying</td></tr>
  <tr><td>True</td><td>double</td><td>double</td><td>Copying</td></tr>
  <tr><td>True</td><td>short</td><td>byte</td><td><a href="#Numeric-Widening-Type-Conversion">Numeric Widening Type Conversion</a></td></tr>
  <tr><td>True</td><td>int</td><td>byte</td><td><a href="#Numeric-Widening-Type-Conversion">Numeric Widening Type Conversion</a></td></tr>
  <tr><td>True</td><td>long</td><td>byte</td><td><a href="#Numeric-Widening-Type-Conversion">Numeric Widening Type Conversion</a></td></tr>
  <tr><td>True</td><td>float</td><td>byte</td><td><a href="#Numeric-Widening-Type-Conversion">Numeric Widening Type Conversion</a></td></tr>
  <tr><td>True</td><td>double</td><td>byte</td><td><a href="#Numeric-Widening-Type-Conversion">Numeric Widening Type Conversion</a></td></tr>
  <tr><td>True</td><td>int</td><td>short</td><td><a href="#Numeric-Widening-Type-Conversion">Numeric Widening Type Conversion</a></td></tr>
  <tr><td>True</td><td>long</td><td>short</td><td><a href="#Numeric-Widening-Type-Conversion">Numeric Widening Type Conversion</a></td></tr>
  <tr><td>True</td><td>float</td><td>short</td><td><a href="#Numeric-Widening-Type-Conversion">Numeric Widening Type Conversion</a></td></tr>
  <tr><td>True</td><td>double</td><td>short</td><td><a href="#Numeric-Widening-Type-Conversion">Numeric Widening Type Conversion</a></td></tr>
  <tr><td>True</td><td>long</td><td>int</td><td><a href="#Numeric-Widening-Type-Conversion">Numeric Widening Type Conversion</a></td></tr>
  <tr><td>True</td><td>float</td><td>int</td><td><a href="#Numeric-Widening-Type-Conversion">Numeric Widening Type Conversion</a></td></tr>
  <tr><td>True</td><td>double</td><td>int</td><td><a href="#Numeric-Widening-Type-Conversion">Numeric Widening Type Conversion</a></td></tr>
  <tr><td>True</td><td>float</td><td>long</td><td><a href="#Numeric-Widening-Type-Conversion">Numeric Widening Type Conversion</a></td></tr>
  <tr><td>True</td><td>double</td><td>long</td><td><a href="#Numeric-Widening-Type-Conversion">Numeric Widening Type Conversion</a></td></tr>
  <tr><td>True</td><td>double</td><td>float</td><td><a href="#Numeric-Widening-Type-Conversion">Numeric Widening Type Conversion</a></td></tr>
  <tr><td>True</td><td>byte</td><td>short</td><td><a href="#Numeric Narrowing Type Conversion">Numeric Narrowing Type Conversion</a></td></tr>
  <tr><td>True</td><td>byte</td><td>int</td><td><a href="#Numeric Narrowing Type Conversion">Numeric Narrowing Type Conversion</a></td></tr>
  <tr><td>True</td><td>byte</td><td>long</td><td><a href="#Numeric Narrowing Type Conversion">Numeric Narrowing Type Conversion</a></td></tr>
  <tr><td>True</td><td>byte</td><td>float</td><td><a href="#Numeric Narrowing Type Conversion">Numeric Narrowing Type Conversion</a></td></tr>
  <tr><td>True</td><td>byte</td><td>double</td><td><a href="#Numeric Narrowing Type Conversion">Numeric Narrowing Type Conversion</a></td></tr>
  <tr><td>True</td><td>short</td><td>int</td><td><a href="#Numeric Narrowing Type Conversion">Numeric Narrowing Type Conversion</a></td></tr>
  <tr><td>True</td><td>short</td><td>long</td><td><a href="#Numeric Narrowing Type Conversion">Numeric Narrowing Type Conversion</a></td></tr>
  <tr><td>True</td><td>short</td><td>float</td><td><a href="#Numeric Narrowing Type Conversion">Numeric Narrowing Type Conversion</a></td></tr>
  <tr><td>True</td><td>short</td><td>double</td><td><a href="#Numeric Narrowing Type Conversion">Numeric Narrowing Type Conversion</a></td></tr>
  <tr><td>True</td><td>int</td><td>long</td><td><a href="#Numeric Narrowing Type Conversion">Numeric Narrowing Type Conversion</a></td></tr>
  <tr><td>True</td><td>int</td><td>float</td><td><a href="#Numeric Narrowing Type Conversion">Numeric Narrowing Type Conversion</a></td></tr>
  <tr><td>True</td><td>int</td><td>double</td><td><a href="#Numeric Narrowing Type Conversion">Numeric Narrowing Type Conversion</a></td></tr>
  <tr><td>True</td><td>long</td><td>float</td><td><a href="#Numeric Narrowing Type Conversion">Numeric Narrowing Type Conversion</a></td></tr>
  <tr><td>True</td><td>long</td><td>double</td><td><a href="#Numeric Narrowing Type Conversion">Numeric Narrowing Type Conversion</a></td></tr>
  <tr><td>True</td><td>float</td><td>double</td><td><a href="#Numeric Narrowing Type Conversion">Numeric Narrowing Type Conversion</a></td></tr>
</table>

=end html

B<Examples:>
  
  # int to int
  my $num = (int)3;
  
  # byte to int
  my $num_byte : byte = 5;
  my $num = (int)5;
  
  # double to double
  my $num = (double)4.5;
  
  # float to double
  my $num = (double)4.5f;
  
  # int to byte
  my $num = (byte)127;

  # double to int
  my $num = (int)2.5;

=head3 Type Castability from NumericObject to Numeric

If the type of the left operand is a L<numeric type|/"Numeric Types"> corresponding to the numeric object type of the right operand and the type of the right operand is a L<numeric object type|/"Numeric Object Type">, the type castability is true.

=begin html

<table>
  <tr><th>Type Castability</th><th>To</th><th>From</th><th><a href="#Type-Conversion">Type Conversion or Copying</a></th></tr>
  <tr><td>True</td><td>byte</td><td>Byte</td><td>Unboxing Type Conversion</td></tr>
  <tr><td>True</td><td>short</td><td>Short</td><td>Unboxing Type Conversion</td></tr>
  <tr><td>True</td><td>int</td><td>Int</td><td>Unboxing Type Conversion</td></tr>
  <tr><td>True</td><td>long</td><td>Long</td><td>Unboxing Type Conversion</td></tr>
  <tr><td>True</td><td>float</td><td>Float</td><td>Unboxing Type Conversion</td></tr>
  <tr><td>True</td><td>double</td><td>Double</td><td>Unboxing Type Conversion</td></tr>
</table>

=end html

B<Examples:>

  my $int = (int)Int->new(3);

  my $double = (double)Double->new(3.5);

=head3 Type Castability from Any Object to Numeric

If the type of the left operand is a L<numeric type|/"Numeric Types"> and the type of the right operand is a L<any object type|/"Any Object Type"> C<object>, the type castability is true.

The L<unboxing type conversion|/"Unboxing Type Conversion"> corresponding to the numeric type is performed.

=begin html

<table>
  <tr><th>Type Castability</th><th>To</th><th>From</th><th><a href="#Type-Conversion">Type Conversion or Copying</a></th></tr>
  <tr><td>True</td><td>NUMERIC_X</td><td>object</td><td>Unboxing Type Conversion</td></tr>
</table>

=end html

B<Examples:>
  
  my $object : object = Int->new(3);
  my $int = (int)$object;
  
  my $object : object = Double->new(3.5);
  my $double = (double)$object;

=head3 Type Castability from Others to Numeric

If the type of the left operand is a L<numeric type|/"Numeric Types"> and the type of the right operand is other than the types described above, the type castability is false.

=head2 Type Castability to Multi-Numeric

If the type of the left operand is a L<multi-numeric type|/"Multi-Numeric Types"> and the type of the right operand is the same type of the left operand, the type castability is true.

Otherwise, the type castability is false.

=begin html

<table>
  <tr><th>Type Castability</th><th>To</th><th>From</th><th><a href="#Type-Conversion">Type Conversion or Copying</a></th></tr>
  <tr><td>True</td><td>MULNUM_X</td><td>MULNUM_X</td><td>Copying</td></tr>
  <tr><td>False</td><td>MULNUM_X</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

B<Examples:>

  my $z1 : Complex_2d;
  my $z2 = (Complex_2d)$z1;

=head2 Type Castability to Referenece

If the type of the left operand is a L<reference type|/"Reference Types"> and the type of the right operand is the same type of the left operand, the type castability is true.

Otherwise, the type castability is false.

=begin html

<table>
  <tr><th>Type Castability</th><th>To</th><th>From</th><th><a href="#Type-Conversion">Type Conversion or Copying</a></th></tr>
  <tr><td>True</td><td>REF_X</td><td>REF_X</td><td>Copying</td></tr>
  <tr><td>False</td><td>REF_X</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

B<Examples:>

  my $num : int = 5;
  my $num_ref = (int*)\num;

=head2 Type Castability to String

If the type of the left operand is the L<string type|/"String Type"> and the type of the right operand is the L<string type|/"String Type">, the type castability is true.

If the type of the left operand is the L<string type|/"String Type"> with the L<mutable type qualifier|/"mutable Type Qualifier"> and the type of the right operand is the L<string type|/"String Type"> without the L<mutable type qualifier|/"mutable Type Qualifier">, the L<runtime type checking|/"Runtime Type Checking"> is performed.

If the type of the right operand is a L<numeric type|/"Numeric Types">, the L<Numeric-to-String type conversion|/"Numeric-to-String Type Conversion"> is performed.

If the type of the left operand is the L<string type|/"String Type"> and the type of the right operand is a L<numeric type|/"Numeric Types">, the L<undef type|/"Undefined Type">, or the L<any object type|/"Any Object Type"> C<object>, the type castability is true.

If the type of the right operand is a L<numeric type|/"Numeric Types">, the L<Numeric-to-String type conversion|/"Numeric-to-String Type Conversion"> is performed.

If the type of the left operand is the L<string type|/"String Type"> and the type of the right operand is the L<any object type|/"Any Object Type"> C<object>, the type castability is true and the runtime type checking is performed.

=begin html

<table>
  <tr><th>Type Castability</th><th>To</th><th>From</th><th><a href="#Type-Conversion">Type Conversion or Copying</a></th></tr>
  <tr><td>True</td><td>string</td><td>string</td><td>Copying</td></tr>
  <tr><td>True</td><td>string</td><td>mutable string</td><td>Copying</td></tr>
  <tr><td>True</td><td>mutable string</td><td>mutable string</td><td>Copying</td></tr>
  <tr><td>True</td><td>mutable string</td><td>string</td><td>Copying with the runtime type checking</td></tr>
  <tr><td>True</td><td>string</td><td>string</td><td>Copying</td></tr>
  <tr><td>True</td><td>string</td><td>NUMERIC_X</td><td>Numeric-to-String type conversion</td></tr>
  <tr><td>True</td><td>string</td><td>object</td><td>Copying with the runtime type checking</td></tr>
  <tr><td>True</td><td>string</td><td>undef</td><td>Copying</td></tr>
  <tr><td>False</td><td>string</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

B<Examples:>

  my $string = (string)"abc";
  my $num_string = (string)3;
  my $string : string = undef;

=head2 Type Castability to NumericObject

If the type of the left operand is a L<numeric object type|/"Numeric Object Types"> and the types of the right operands are the following cases:

If the type of the right operand is the same type of the left operand, a L<numeric type|/"Numeric Types"> that is corresponding to the numeric object type, the L<any object type|/"Any Object Type"> C<object>, or the L<undef type|/"Undefined Type">, the type castability is true.

The type of the right operand is other than above, the type castability is false.

If the type of the right operand is a L<numeric type|/"Numeric Types">, the L<boxing type conversion|/"Boxing Type Conversion"> is performed.

If the type of the left operand is the type of the right operand is the L<any object type|/"Any Object Type"> C<object>, the L<runtime type checking|/"Runtime Type Checking"> is performed.

=begin html

<table>
  <tr><th>Type Castability</th><th>To</th><th>From</th><th><a href="#Type-Conversion">Type Conversion or Copying</a></th></tr>
  <tr><td>True</td><td>NUMERIC_OBJECT_X</td><td>NUMERIC_OBJECT_X</td><td>Copying</td></tr>
  <tr><td>True</td><td>NUMERIC_OBJECT_X</td><td>NUMERIC_X</td><td>Boxing type conversion</td></tr>
  <tr><td>True</td><td>NUMERIC_OBJECT</td><td>object</td><td>Copying with the runtime type checking</td></tr>
  <tr><td>True</td><td>NUMERIC_OBJECT</td><td>undef</td><td>Copying</td></tr>
  <tr><td>False</td><td>NUMERIC_OBJECT</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

B<Examples:>

  my $num_object = (Int)Int->new(3);
  my $num_object = (Int)3;
  my $num_object = (Int)undef;
  
  my $object : object = Int->new(3);
  my $num_object = (Int)$object;

=head2 Type Castability to Class

If the type of the left operand is a L<class type|/"Class Type"> and the types of the right operands are the following cases:

If the type of the right operand is the same type, the L<any object type|/"Any Object Type"> C<object>, an L<interface type|/"Interface Type"> or the L<undef type|/"Undefined Type">, the type castability is true.

Otherwise, the type castability is false.

If the type of the right operand is the L<any object type|/"Any Object Type"> C<object> or an L<interface type|/"Interface Type">, the L<runtime type checking|/"Runtime Type Checking"> is performed.

=begin html

<table>
  <tr><th>Type Castability</th><th>To</th><th>From</th><th><a href="#Type-Conversion">Type Conversion or Copying</a></th></tr>
  <tr><td>True</td><td>CLASS_X</td><td>CLASS_X</td><td>Copying</td></tr>
  <tr><td>True</td><td>CLASS_X</td><td>INTERFACE_Y</td><td>Copying with the runtime type checking</td></tr>
  <tr><td>True</td><td>CLASS_X</td><td>object</td><td>Copying with the runtime type checking</td></tr>
  <tr><td>True</td><td>CLASS</td><td>undef</td><td>Copying</td></tr>
  <tr><td>False</td><td>CLASS</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

B<Examples:>

  my $point : Point = Point->new;
  
  my $stringable : Stringable;
  my $point = (Point)$stringable;

  my $stringer : Stringer;
  my $point = (Point)$stringer

  my $point = (Point)undef;

=head2 Type Castability to Interface

If the type of the left operand is an L<interface type|/"Interface Type">, and the types of the right operands are the following cases:

If the type of the right operand is the same type, the L<any object type|/"Any Object Type"> C<object> , an L<interface type|/"Interface Type"> or the L<undef type|/"Undefined Type">, the type castability is true.

If the type of the right operand is a L<class type|/"Class Type"> and the class has the interface of the left operand, the type castability is true.

Otherwise, the type castability is false.

If the type of the right operand is the L<any object type|/"Any Object Type"> C<object>, an L<interface type|/"Interface Type">, the L<runtime type checking|/"Runtime Type Checking"> is performed.
=begin html

<table>
  <tr><th>Type Castability</th><th>To</th><th>From</th><th><a href="#Type-Conversion">Type Conversion or Copying</a></th></tr>
  <tr><td>True</td><td>INTERFACE_X</td><td>INTERFACE_X</td><td>Copying</td></tr>
  <tr><td>Conditional True</td><td>INTERFACE_X</td><td>CLASS_Y</td><td>Copying</td></tr>
  <tr><td>True</td><td>INTERFACE_X</td><td>INTERFACE_Y</td><td>Copying with the runtime type checking</td></tr>
  <tr><td>True</td><td>INTERFACE_X</td><td>object</td><td>Copying with the runtime type checking</td></tr>
  <tr><td>True</td><td>INTERFACE</td><td>undef</td><td>Copying</td></tr>
  <tr><td>False</td><td>INTERFACE</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

B<Examples:>
  
  my $stringable1 : Stringable;
  my $stringable2 = (Stringable)$stringable1;
  
  my $cloneable : Cloneable;
  my $stringable = (Stringable)$cloneable;
  
  my $stringable  = (Stringable)Point->new_xy(1, 2);

  my $object : object  = Point->new_xy(1, 2);
  my $stringable  = (Stringable)Point->new_xy(1, 2);
  
  my $stringable : Stringable = undef;

=head2 Type Castability to Any Object

If the type of the left operand is the L<any object type|/"Any Object Type"> and the types of the right operands are the following cases:
 
If the type of the right operand is an L<object type|/"Object Types">, a L<numeric type|/"Numeric Types"> or the L<undef type|/"Undefined Type">, the type castability is true.

Otherwise, the type castability is false.

If the type of the right operand is a L<numeric type|/"Numeric Types">, the L<boxing type conversion|/"Boxing Type Conversion"> is performed.

=begin html

<table>
  <tr><th>Type Castability</th><th>To</th><th>From</th><th><a href="#Type-Conversion">Type Conversion or Copying</a></th></tr>
  <tr><td>True</td><td>object</td><td>OBJECT_X</td><td>Copying</td></tr>
  <tr><td>True</td><td>object</td><td>NUMERIC_X</td><td>Boxing type conversion</td></tr>
  <tr><td>True</td><td>object</td><td>undef</td><td>Copying</td></tr>
  <tr><td>False</td><td>object</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

B<Examples:>

  my $object : object = Point->new;
  my $num_object : object = 3;
  my $object : object = undef;

=head2 Type Castability to Numeric Array

If the type of the left operand is the L<byte[] type|/"byte[] Type"> and the type of the right operand is the L<string type|/"String Type">, the type castability is true.

If the type of the left operand is a L<numeric array type|/"Numeric Array Types"> and the types of the right operands are the following cases:

If the type of the right operand is the same type of the left operand, the L<any object type|/"Any Object Type"> C<obejct> or the L<undef type|/"Undefined Type">, the type castability is true.

Otherwise, the type castability is false.

If the type of the left operand is the L<byte[] type|/"byte[] Type"> and the type of the right operand is the L<string type|/"String Type">, L<String-to-byte[] Type Conversion> is performed.

If the type of the right operand is the L<any object type|/"Any Object Type"> C<obejct>, the L<runtime type checking|/"Runtime Type Checking"> is performed.

=begin html

<table>
  <tr><th>Type Castability</th><th>To</th><th>From</th><th><a href="#Type-Conversion">Type Conversion or Copying</a></th></tr>
  <tr><td>True</td><td>byte[]</td><td>string</td><td><a href="#String-to-byte[]-Type-Conversion">String-to-byte[] Type Conversion</a></td></tr>
  <tr><td>True</td><td>NUMERIC_X[]</td><td>NUMERIC_X[]</td><td>Copying</td></tr>
  <tr><td>True</td><td>NUMERIC[]</td><td>object</td><td>Copying with the runtime type checking</td></tr>
  <tr><td>True</td><td>NUMERIC[]</td><td>undef</td><td>Copying</td></tr>
  <tr><td>False</td><td>NUMERIC[]</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

B<Examples:>
  
  my $bytes = (byte[])"abc";
  
  my $nums = (int[])new int[3];
  
  my $object : object = new int[3];
  my $nums = (int[])$object;
  
  my $nums = (int[])undef;

=head2 Type Castability to Multi-Numeric Array

If the type of the left operand is a L<multi-numeric array type|/"Multi-Numeric Array Types"> and the types of the right operands are the following cases:
 
If the type of the right operand is the same type of the left operand, the L<any object type|/"Any Object Type"> C<obejct> or the L<undef type|/"Undefined Type">, the type castability is true.

Otherwise, the type castability is false.

If the type of the right operand is the L<any object type|/"Any Object Type"> C<obejct>, the L<runtime type checking|/"Runtime Type Checking"> is performed.

=begin html

<table>
  <tr><th>Type Castability</th><th>To</th><th>From</th><th><a href="#Type-Conversion">Type Conversion or Copying</a></th></tr>
  <tr><td>True</td><td>MULNUM_X[]</td><td>MULNUM_X[]</td><td>Copying</td></tr>
  <tr><td>True</td><td>MULNUM_X[]</td><td>object</td><td>Copying with the runtime type checking</td></tr>
  <tr><td>True</td><td>MULNUM_X[]</td><td>undef</td><td>Copying</td></tr>
  <tr><td>False</td><td>MULNUM_X[]</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

B<Examples:>

  my $nums = (Complex_2d[])new Complex_2d[3];

  my $object : object = new Complex_2d[3];
  my $nums = (Complex_2d[])$object;

  my $nums = (Complex_2d[])undef;

=head2 Type Castability to String Array

If the type of the left operand is a L<string array type|/"String Array Type"> and the types of the right operands are the following cases:
 
If the type of the right operand is the same type of the left operand, the L<any object type|/"Any Object Type"> C<obejct>, the L<any object array type|/"Any Object Array Type"> C<obejct[]> or the L<undef type|/"Undefined Type">, the type castability is true.

Otherwise, the type castability is false.

If the type of the right operand is the L<any object type|/"Any Object Type"> C<obejct>, or the L<any object array type|/"Any Object Array Type"> C<obejct[]>, the L<runtime type checking|/"Runtime Type Checking"> is performed.

=begin html

<table>
  <tr><th>Type Castability</th><th>To</th><th>From</th><th><a href="#Type-Conversion">Type Conversion or Copying</a></th></tr>
  <tr><td>True</td><td>string[]</td><td>string[]</td><td>Copying</td></tr>
  <tr><td>True</td><td>string[]</td><td>object</td><td>Copying with the runtime type checking</td></tr>
  <tr><td>True</td><td>string[]</td><td>object[]</td><td>Copying with the runtime type checking</td></tr>
  <tr><td>True</td><td>string[]</td><td>undef</td><td>Copying</td></tr>
  <tr><td>False</td><td>string[]</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

B<Examples:>

  my $strings = (string[])["abc", "def"];

  my $object : object = ["abc", "def"];
  my $strings = (string[])$object;

  my $objects : object[] = ["abc", "def"];
  my $strings = (string[])$object;

  my $strings  = (string[])undef;

=head2 Type Castability to Class Array

If the type of the left operand is a L<class array type|/"Class Array Types"> and the types of the right operands are the following cases:
 
If the type of the right operand is the same type of the left operand, the L<any object type|/"Any Object Type"> C<obejct>, the L<any object array type|/"Any Object Array Type"> C<obejct[]> or the L<undef type|/"Undefined Type">, the type castability is true.

Otherwise, the type castability is false.

If the type of the right operand is the L<any object type|/"Any Object Type"> C<obejct>, or the L<any object array type|/"Any Object Array Type"> C<obejct[]>, the L<runtime type checking|/"Runtime Type Checking"> is performed.

=begin html

<table>
  <tr><th>Type Castability</th><th>To</th><th>From</th><th><a href="#Type-Conversion">Type Conversion or Copying</a></th></tr>
  <tr><td>True</td><td>CLASS_X[]</td><td>CLASS_X[]</td><td>Copying</td></tr>
  <tr><td>True</td><td>CLASS_X[]</td><td>object</td><td>Copying with the runtime type checking</td></tr>
  <tr><td>True</td><td>CLASS_X[]</td><td>object[]</td><td>Copying with the runtime type checking</td></tr>
  <tr><td>True</td><td>CLASS_X[]</td><td>undef</td><td>Copying</td></tr>
  <tr><td>False</td><td>CLASS_X[]</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

B<Examples:>

  my $points = (Point[])new Point[3];

  my $object : object = new Point[3];
  my $points = (Point[])$object;

  my $objects : object[] = new Point[3];
  my $points = (Point[])$object;

  my $points = (Point[])undef;

=head2 Type Castability to Interface Array

If the type of the left operand is an L<interface array type|/"Interface Array Types"> and the types of the right operands are the following cases:

If the type of the right operand is a L<class array type|/"Class Array Types"> and its L<basic type|/"Basic Type"> has the interface of the basic type of the left operand, the type castability is true.

If the type of the right operand is the same type of the left operand, the type castability is true.

If the type of the right operand is an differnt type of L<interface array type|/"Interface Array Types">, the type castability is also true.

If the type of the right operand is the L<any object type|/"Any Object Type"> C<obejct>, the L<any object array type|/"Any Object Array Type"> C<obejct[]>  or the L<undef type|/"Undefined Type">, the type castability is true.

Otherwise, the type castability is false.

If the type of the right operand is an differnt type of  L<interface array type|/"Interface Array Types">, the L<runtime type checking|/"Runtime Type Checking"> is performed.

If the type of the right operand is the L<any object type|/"Any Object Type"> C<obejct>, or the L<any object array type|/"Any Object Array Type"> C<obejct[]>, the L<runtime type checking|/"Runtime Type Checking"> is performed.

=begin html

<table>
  <tr><th>Type Castability</th><th>To</th><th>From</th><th><a href="#Type-Conversion">Type Conversion or Copying</a></th></tr>
  <tr><td>Conditional True</td><td>INTERFACE_X[]</td><td>CLASS_Y[]</td><td>Copying</td></tr>
  <tr><td>True</td><td>INTERFACE_X[]</td><td>INTERFACE_X[]</td><td>Copying</td></tr>
  <tr><td>True</td><td>INTERFACE_X[]</td><td>INTERFACE_Y[]</td><td>Copying with the runtime type checking</td></tr>
  <tr><td>True</td><td>INTERFACE_X[]</td><td>object</td><td>Copying with the runtime type checking</td></tr>
  <tr><td>True</td><td>INTERFACE_X[]</td><td>object[]</td><td>Copying with the runtime type checking</td></tr>
  <tr><td>True</td><td>INTERFACE_X[]</td><td>undef</td><td>Copying</td></tr>
  <tr><td>False</td><td>INTERFACE_X[]</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

B<Examples:>

  my $stringables = (Stringable[])new Stringable[3];

  my $stringables = (Stringable[])new Point[3];
  
  my $stringables = (Stringable[])undef;

=head2 Type Castability to Any Object Array

If the type of the left operand is the L<any object array type|/"Any Object Array Type"> C<object[]> and the types of the right operands are the following cases:

If the type of the right operand is an L<object array type|/"Object Array Type"> or the L<undef type|/"Undefined Type">, the type castability is true.

If the type of the right operand is an L<any object type|/"Any Object Type">, the type castability is true.

Otherwise, the type castability is false.

If the type of the right operand is an L<any object type|/"Any Object Type">, the L<runtime type checking|/"Runtime Type Checking"> is performed.

=begin html

<table>
  <tr><th>Type Castability</th><th>To</th><th>From</th><th><a href="#Type-Conversion">Type Conversion or Copying</a></th></tr>
  <tr><td>True</td><td>object[]</td><td>OBJECT_X[]</td><td>Copying</td></tr>
  <tr><td>True</td><td>object[]</td><td>undef</td><td>Copying</td></tr>
  <tr><td>True</td><td>object[]</td><td>object</td><td>Copying with the runtime type checking</td></tr>
  <tr><td>False</td><td>object[]</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

B<Examples:>

  my $any_object : object;
  my $any_objects = (object[])$any_object;

  my $any_objects0 : object[];
  my $any_objects = (object[])$any_objects0;

  my $points : Point[];
  my $any_object = (object[])$points;

  my $any_object = (object[])undef;

  my $points_2dim : Point[][];
  my $any_object = (object[])$points_2dim;

  my $stringables : Stringable[];
  my $any_object = (object[])$stringables;
  
  my $strings : string[];
  my $any_object = (object[])$strings;
  
=head2 Type Castability to Multi-Dimensional Array

If the type of the left operand is a L<multi-dimensional array type|/"Multi-Dimensional Array Type"> and  and the types of the right operands are the following cases:

If the type of the right operand is the same type of the left operand or the L<undef type|/"Undefined Type">, the type castability is true.

If the type of the right operand is an L<any object type|/"Any Object Type">, the type castability is true.

If the L<basic type|/"Basic Type"> of the type of the left operand is an L<interface type|/"Interface Type"> and the L<basic type|/"Basic Type"> of the type of the right operand is a L<class type|/"Class Type"> and the dimension of the type of the right operand is same as the dimension of the type left oerand and the L<basic type|/"Basic Type"> of the type of the right operand has the interface of the L<basic type|/"Basic Type"> of the type of the left operand , the type castability is true.

Otherwise, the type castability is false.

=begin html

<table>
  <tr><th>Type Castability</th><th>To</th><th>From</th><th><a href="#Type-Conversion">Type Conversion or Copying</a></th></tr>
  <tr><td>True</td><td>MULDIM_X</td><td>MULDIM_X</td><td>Copying</td></tr>
  <tr><td>True</td><td>MULDIM_X</td><td>object</td><td>Copying with the runtime type checking</td></tr>
  <tr><td>True</td><td>MULDIM_X</td><td>object[]</td><td>Copying with the runtime type checking</td></tr>
  <tr><td>True</td><td>MULDIM_X</td><td>undef</td><td>Copying</td></tr>
  <tr><td>Conditional True</td><td>INTERFACE_MULDIM_X[]</td><td>CLASS_MULDIM_Y[]</td><td>Copying</td></tr>
  <tr><td>False</td><td>object[]</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

B<Examples:>

  my $points_2dim : Point[][];
  my $muldim_array : Point[][] = $points_2dim;

  my $muldim_array : Point[][] = undef;

  my $strings_2dim : String[][];
  my $muldim_array : Stringable[][] = $strings_2dim;

  {
    my $cb = method : string ($object : object) {
      my $point = (Point)$object;
      return $point->to_string;
    };
    my $muldim_array : Stringer[][] = [[$cb]];
  }
  
=head1 Runtime Type Checking

Some L<type cast|/"Type Cast"> operations have runtime type checking. The L<runtime type assignability/"Runtime Type Assignability"> is used to check the type.

=head2 Runtime Type Assignability

The runtime type assignability is the type assignalibility when L<Runtime Type Checking> is performed.

The runtime assignability is false, an exception will be thrown.

If the type of the distribution is an L<object type|/"Object Types"> and the type of the source is L<undef|\"Undefined Type">, the runtime type assignability is true.

If the type of the distribution is same as the type of the source, the runtime type assignability is true.

If the type of the distribution is the L<any object type|/"Any Object Type"> C<object> and the type of the source is an L<object type|/"Object Types">, the runtime type assignability is true.

If the type of the distribution is the L<any object array type|/"Any Object Array Type"> C<object[]> and the type of the source is an L<object array type|/"Object Array Types">, the runtime type assignability is true.

If the type of distribution is an L<interface type|/"Interface Type">, an L<interface array type|/"Interface Array Type">, an L<interface multi-dimensional array type|/"Interface Multi-Dumensional Array Type"> and the dimention of the type of the distribution is same as the dimention of the type of the source and the basic type of distribution has the interface of the basic type of the source, the runtime type assignability is true.

=head2 Runtime Type Assignability

The runtime type assignability is the type assignalibility at runtime.

The runtime assignability is false, an exception will be thrown.

If the type of the distribution is an L<object type|/"Object Types"> and the type of the source is L<undef|\"Undefined Type">, the runtime type assignability is true.

If the type of the distribution is same as the type of the source, the runtime type assignability is true.

If the type of the distribution is the L<any object type|/"Any Object Type"> C<object> and the type of the source is an L<object type|/"Object Types">, the runtime type assignability is true.

If the type of the distribution is the L<any object array type|/"Any Object Array Type"> C<object[]> and the type of the source is an L<object array type|/"Object Array Types">, the runtime type assignability is true.

If the type of distribution is an L<interface type|/"Interface Type">, an L<interface array type|/"Interface Array Type">, an L<interface multi-dimensional array type|/"Interface Multi-Dumensional Array Type"> and the dimention of the type of the distribution is same as the dimention of the type of the source and the basic type of distribution has the interface of the basic type of the source, the runtime type assignability is true.

=begin html

<table>
  <tr><th>Runtime Assignability</th><th>To</th><th>From</th></tr>
  <tr><td>True</td><td>OBJECT_X</td><td>undef</td></tr>
  <tr><td>True</td><td>object</td><td>OBJECT_X</td></tr>
  <tr><td>True</td><td>object[]</td><td>OBJECT_X[]</td></tr>
  <tr><td>Conditional True</td><td>INTERFACE_X</td><td>OBJECT_Y</td></tr>
  <tr><td>Conditional True</td><td>INTERFACE_X[]</td><td>OBJECT_Y</td></tr>
  <tr><td>Conditional True</td><td>INTERFACE_MULDIM_X</td><td>OBJECT_Y</td></tr>
  <tr><td>False</td><td>object[]</td><td>OTHER</td></tr>
</table>

=end html

=head1 Type Conversion

Type conversion is explained.

=head2 Explicite Type Conversion

The explicite type conversion is the L<type conversion|/"Type Conversion"> performed by a L<type cast|/"Type Cast"> expicitely.

B<Examples:>
  
  # Explicte long to int type conversion
  my $num = (int)123L;

  # Explicte byte[] to string type conversion
  my $num = (string)new byte[3];

  # Explicte string to byte[] type conversion
  my $num = (byte[])"Hello";

=head2 Implicite Type Conversion

The implicite type conversion is the L<type conversion|/"Type Conversion"> performed implicitly when a value is assigned using L<assignment operator|/"Assignment Operator">, pass an argument to a method using a L<method call|/"Method Calls">, or set a return value using the L<return statement|/"return Statement">.

See L<"Type Assignability"> if you know when implicite type conversion is performed.

B<Examples:>
  
  # Implicite int to double type conversion
  my $num : double = 5;
  
  # Implicte double to Double type conversion
  my $num_object : Double = 5.1;
  
  # Implicte Double to double type conversion
  my $num : double = Double->new(5.1);
  
  # Implicte int to string type conversion
  my $string : string = 4;

=head2 Numeric Widening Type Conversion

The numeric widening type conversion is a L<conversion|"Type Conversion"> from a small-order L<numeric type|/"Numeric Types"> to a large-order L<numeric type|/"Numeric Types">.

See also L<numeric types order|/"Numeric Types Order"> abount the order of numeric type.

The return value of a converion are same as the return value of the type cast of C<C language>.
  
  (TYPE)OPERAND

B<byte to short:>

  int8_t from = VALUE;
  int16_t to = (int16_t)from;

B<byte to int:>

  int8_t from = VALUE;
  int32_t to = (int32_t)from;

B<byte to long:>

  int8_t from = VALUE;
  int64_t to = (int64_t)from;

B<byte to float:>

  int8_t from = VALUE;
  float to = (float)from;

B<byte to double:>

  int8_t from = VALUE;
  double to = (double)from;

B<short to int:>

  int16_t from = VALUE;
  int32_t to = (int32_t)from;

B<short to long:>

  int16_t from = VALUE;
  int64_t to = (int64_t)from;

B<short to float:>

  int16_t from = VALUE;
  float to = (float)from;

B<short to double:>

  int16_t from = VALUE;
  double to = (double)from;

B<int to long:>

  int32_t from = VALUE;
  int64_t to = (int64_t)from;

B<int to float:>

  int32_t from = VALUE;
  float to = (float)from;

B<int to double:>

  int32_t from = VALUE;
  double to = (double)from;

B<long to float:>

  int64_t from = VALUE;
  float to = (float)from;

B<long to double:>

  int64_t from = VALUE;
  double to = (double)from;

The numeric widening type conversion is performed in some of the L<type casts|/"Type Cast">, the index of the L<array access|/"Array Access">, the length of the L<creating array|/"Creating Array">, the operand of the L<unary plus operator|/"Unary Plus Operator">, the operand of the L<unary minus operator|/"Unary Minus Operator">, and the left and right operands of the L<shift operators|"Shift Operators">.

=head2 Numeric Narrowing Type Conversion

The numeric narrowing type conversion is a L<conversion|"Type Conversion"> from a large-order L<numeric type|/"Numeric Types"> to a small-order L<numeric type|/"Numeric Types">.

See also L<numeric types order|/"Numeric Types Order"> abount the order of numeric type.

The return value of a converion are same as the return value of the type cast of C<C language>.
  
  (TYPE)OPERAND

b<double to float:>

  double from = value;
  float to = (float)from;

b<double to long:>

  double from = value;
  int64_t to = (int64_t)from;

b<double to int:>

  double from = value;
  int32_t to = (int32_t)from;

b<double to short:>

  double from = value;
  int16_t to = (int16_t)from;

b<double to byte:>

  double from = value;
  int8_t to = (int8_t)from;

b<float to long:>

  float from = value;
  int64_t to = (int64_t)from;

b<float to int:>

  float from = value;
  int32_t to = (int32_t)from;

b<float to short:>

  float from = value;
  int16_t to = (int16_t)from;

b<float to byte:>

  float from = value;
  int8_t to = (int8_t)from;

b<long to int:>

  int64_t from = value;
  int32_t to = (int32_)from;

b<long to short:>

  int64_t from = value;
  int16_t to = (int16_t)from;

b<long to byte:>

  int64_t from = value;
  int8_t to = (int8_t)from;

b<int to short:>

  int32_t from = value;
  int16_t to = (int16_t)from;

b<int to byte:>

  int32_t from = value;
  int16_t to = (int16_t)from;

b<short to byte:>

  int16_t from = value;
  int8_t to = (int8_t)from;

The numeric narrowing type conversion is performed in some of the L<type casts|/"Type Cast">.

=head2 Binary Numeric Type Conversion

Binary Numeric Type Conversion is performed to the left operand and the right operand in Binary Operator that takes Numeric Types on the Left and Right sides. L</"Numeric Widening Type Conversion">.

The following rules apply.

1. When one Expression is L</"double Type">, the other Type is L</"double Type"> Is converted to>.

2. If one Expression is L</"float Type">, the other Type is L</"float Type"> Is converted to>.

3. When one Expression is L</"long Type">, the other Type is L</"long Type"> Is converted to>.

4, otherwise, it will be converted to L</"int Type">.

Binary Numeric Type Conversion is performed in the following cases.

=head2 Numeric-to-String Type Conversion

The numeric-to-String type conversion is a L<type conversion|/"Type Conversion"> from a L<numeric type|/"Numeric Types"> to the L<string type|/"String Type">.

  # Numeric-to-String type conversion
  my $byte = (byte)1;
  my $short = (short)2;
  my $int = 3;
  my $long = 4L;
  my $float = 2.5f;
  my $double = 3.3;
  
  # The string is 1.
  my $string_byte = (string)$byte;
  
  # The string is 2.
  my $string_short = (string)$short;

  # The string is 3.
  my $string_int = (string)$int;

  # The string is 4.
  my $string_long = (string)$long;
  
  # The string is "2.5"
  my $string_float = (string)$float;
  
  # The string is "3.3"
  my $string_double = (string)$double;

=head2 String-to-byte[] Type Conversion

The String-to-byte[] type conversion is a L</"Type Conversion"> from L</"String Type"> to L</"byte[] Type">.

  # String-to-byte[] Type Conversion
  my $string : string = "Hello";
  my $bytes : byte[] = (byte[])$string;

A new byte[] object is created and all characters in the string are copied to the elements of byte[] object.

=head2 byte[]-to-String Type Conversion

The byte[]-to-String type conversion is a L</"Type Conversion"> from L</"byte[] type"> to L</"String Type">.

  # byte[]-to-String type conversion
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

The bool type conversion is a L<type conversion|/"Type Conversion"> that is performed in operands of conditional branches.

The operand of the L<if statement|/"if Statement">:

  if (CONDITION) {
  
  }

The operand of the L<unless statement|/"unless Statement">:

  unless (CONDITION) {
  
  }

The second operand of the L<for statement|/"for Statement">:

  for (INITIALIZEATION;CONDITION;NEXT_VALUE;) {
  
  }

The operand of the L<while statement|/"while Statement">:

  while (CONDITION) {
  
  }

The left and right operand of the L<logical AND operator|/"Logical AND Operator">:

  CONDITION && CONDITION

The left and right operand of the L<logical OR operator|/"Logical OR Operator">:

  CONDITION || CONDITION

The operand of the L<logical NOT operator|/"Logical NOT Operator">:

  !CONDITION

The type of the operand of the bool type conversion must be a L<numeric type|/"Numeric Types"> or an L<object type|/"Object Types"> or the L<undef type|/"Undefined Type">, otherwise a compilation error will occur.

The return type of the bool type conversion is the L<int type|/"int Type">.

If the operand is the L<undef|/"Undefined Value"> value, C<0> is returned.

If the operand is L<true|/"true">(the C<TRUE> method of L<Bool|SPVM::Bool>), C<1> is returned.

If the operand is L<false|/"false">(the C<FALSE> method of L<Bool|SPVM::Bool>), C<0> is returned.

If the type of the operand is a L<numeric type|/"Numeric Types">, the L<numeric widening type conversion|/"Numeric Widening Type Conversion"> is performed.

And the following operation is performed.

  !!OPERAND

If the type of the operand is an L<object type|/"Object Types"> except for the L<Bool|SPVM::Bool> type, and if the object is not L<undef|/"Undefined Value"> value, C<1> is returned. If the object is L<undef|/"Undefined Value"> value, C<0> is returned.

B<Examples:>

  if (1) {
    # ok
  }
  
  if (0) {
    # not ok
  }
  
  if (1.5) {
    # ok
  }
  
  if (0.0) {
    # not ok
  }
  
  if (true) {
    # ok
  }
  
  if (Bool->TRUE) {
    # ok
  }
  
  if (false) {
    # not ok
  }
  
  if (Bool->FALSE) {
    # not ok
  }
  
  my $object = SPVM::Int->new(1);
  
  if ($object) {
    # ok
  }
  
  $object = undef;
  if ($object) {
    # not ok
  }
  
  if (undef) {
    # not ok
  }

=head1 Type Comment

The type comment syntax is supported. The type comment can be written after C<of> keyword.

  TYPE of TYPE

The type comment can be used the type of the L<field decralation|/"Field Definition">, the L<class variable definition|/"Class Variable Definition">, the L<local variable declaration|/"Local Variable Declaration">, and the return value and the types of arguments of the L<method definition|/"Method Definition">.

  has points : List of Point;
  
  our $POINTS : List of Point;
  
  my $points : List of Point;
  
  static method foo : List of Point ($arg : List of Point) { ... }

If the type specified as the type comment is not found, a compilation error will occur.

Type comments have no meanings at runtime.

=head1 Exception

Explains exceptions.

=head2 Throwing Exception

You can throw an exception using the L<die statement|/"die Statement">.

  die OPERAND;

B<Examples:>

  # Throw an exception
  die "Error";

=head2 Exception Catching

You can catch an exception using an L<eval block|/"eval Block">.

  eval {
    die "Error";
  };

The L<undef|/"Undefined Value"> is set to the L<exception variable|/"Exception Variable"> C<$@> at the top of the L<eval block|/"eval Block">.

The error message is set to the L<exception variable|/"Exception Variable"> C<$@> when the exception is thrown.

B<Examples:>
  
  # Catch the exception
  eval {
    # Throw an exception
    die "Error";
  };
  
  # Check the error message
  if ($@) {
    # ...
  }

=head2 Exception Variable

B<Exception Variable> is a global variable that is represented by "B<$@>"

  $@

See L</"Setting Class Variable"> to get Exception Variable Value.

See L</"Setting Exception Variable"> to set Exception Variable Value.

=head1 Garbage Collection

The object is released from memory when the reference count reaches 0.

If the object is an Array that has Object Type values ​​as elements, the reference count of all Array elements that are not Undefined Value is decremented by C<1> before Garbage Collection

When an object is a L<class type|/"Class Type"> and has a field of Object Type, the reference count of the objects owned by all Fields of Object Type that are not Undefined Value is decremented by C<1> before Garbage Collection. If Weak Reference is set to the object saved in Field, Weak Reference is released before Reference Count is decremented by C<1>.

When the object has Back references of Weak Reference, Undefined Value is assigned to all Fields registered as back References and all back References are deleted.

The above process is done recursively.

=head1 Weak Reference

Weak Reference is a reference that does not increase the reference count. Weak Reference can be used to solve the problem of circular references.

SPVM has GC of Reference Count Type. In the GC of Reference Count Type, the object is automatically released when the reference count becomes 0, but when the circular reference occurs, the reference count does not become 0 and the object is automatically released. not.

This is an Example when the Field of the object is circularly referenced.

  {
    my $foo = new Foo;
    my $bar = new Bar;
  
    $foo->{bar} = $bar;
    $bar->{foo} = $foo;
  }

In this case, both objects are not released when the Scope ends. This is because a circular reference has occurred and the reference count does not become 0.

Weak Reference is a function to correctly destroy objects when a circular reference occurs in a programming language that has a Reference Count GC.

In such a case, it is possible to release correctly by setting one Field to Weak Reference using L</"weaken Statement">.

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

When the Scope ends, the reference count of $bar is decremented by C<1> and becomes 0, so it is released correctly.

Even if there are 3 circular references, you can release them correctly by setting Weak Reference in 1 Field.

  {
    my $foo = new Foo;
    my $bar = new Bar;
    my $baz = new Baz;
  
    $foo->{bar} = $bar;
    $bar->{baz} = $baz;
    $baz->{foo} = $foo;
  
    weaken $foo->{bar};
  }

As a syntax related to Weak Reference, Weak Reference can be released L</"weaken Statement">, and it can be confirmed whether Field is Weak Reference the L<isweak operator|/"isweak Operator">.

=head1 SEE ALSO

=head2 Examples

You can see more examples in the following test codes.

L<Examples of SPVM|https://github.com/yuki-kimoto/SPVM/tree/master/t/default/lib/SPVM/TestCase>
