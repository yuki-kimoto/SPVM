=encoding utf8

=head1 Name

SPVM::Document::Language::Tokenization - Tokenization in the SPVM Language

=head1 Description

This document describes the tokenization in the SPVM language.

=head1 Tokenization

This section describes the L<lexical analysis|https://en.wikipedia.org/wiki/Lexical_analysis> in the SPVM Language.

This is called tokenization.

See L<SPVM::Document::Language::SyntaxParsing> about syntax parsing.

=head2 Character Encoding

The character encoding of SPVM source codes is UTF-8.

If a character is an ASCII character, it must be an ASCII printable character or a L<space character|/"Space Characters">.

Compilation Errors:

The charactor encoding of SPVM source codes must be UTF-8. Otherwise a compilation error occurs.

If a character is an ASCII character, it must be an L<ASCII printable character|https://en.wikipedia.org/wiki/ASCII#Printable_characters> or a L<space character|/"Space Characters">. Otherwise a compilation error occurs.

=head2 Line Terminators

The line terminator is ASCII C<LF>.

When a line terminator appears, the current line number is incremented by 1.

=head2 Space Characters

The space characters are ASCII C<SP>, C<HT>, C<FF>, C<LF>.

=head2 Word Characters

The word characters are ASCII C<a-zA-Z>, C<0-9>, C<_>.

=head2 Names

This section describes names.

=head3 Symbol Name

A symbol name consists of L<word characters|/"Word Characters"> and C<::>.

It dose not contains C<__>.

It dose not begin with C<0-9>.

It dose not begin with C<::>.

It dose not end with C<::>.

It dose not contains C<::::>.

It dose not begin with C<0-9>.

Compliation Errors:

If a symbol name is invald, a compilation error occurs.

Examples:

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

=head3 Class Name

A class name is a L<symbol name|/"Symbol Name">.

Each partial name of a class name must begin with an uppercase letter.

Partial names are individual names separated by C<::>. For example, the partial names of C<Foo::Bar::Baz> are C<Foo>, C<Bar>, and C<Baz>.

Compilation Errors:

If a class name is invalid, a compilation error occurs.

Examples:
  
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

=head3 Method Name

A method name is a L<symbol name|/"Symbol Name"> without C<::> or an empty string C<"">.

Method names with the same name as L<keywords|/"Keywords"> are allowed.

Compilation Errors:

If a method name is invalid, a compilation error occurs.

Examples:

  # Method names
  FOO
  FOO_BAR3
  foo
  foo_bar
  _foo
  _foo_bar_
  
  # Invalid method names
  foo__bar
  3foo

=head3 Field Name

A field name is a L<symbol name|/"Symbol Name"> without C<::>.

Field names with the same name as L<keywords|/"Keywords"> are allowed.

Compilation Errors:

If a field names is invalid, a compilation error occurs.

Examples:

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

=head3 Variable Name

A variable name begins with C<$> and is followed by a L<symbol name|/"Symbol Name">.

The symbol name in a variable name can be surrounded by C<{> and C<}>.

Compilation Errors:

If a field names is invalid, a compilation error occurs.

If an opening C<{> exists and the closing C<}> dose not exist, a compilation error occurs.

Examples:

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

=head4 Class Variable Name

A class variable name is a L<variable name|/"Variable Name">.

Examples:

  # Class variable names
  $NAME
  $MY_NAME
  ${NAME}
  $FOO::NAME
  $FOO::BAR::NAME
  ${FOO::NAME_BRACE}
  $FOO::name
  
  # Invalid class variable names
  $::NAME
  $NAME::
  $FOO::::NAME
  $MY__NAME
  $3FOO
  ${NAME

=head4 Local Variable Name

A local variable name is a L<variable name|/"Variable Name"> without C<::>.

Examples:

  # Local variable names
  $name
  $my_name
  ${name_brace}
  $_name
  $NAME

  # Invalid local variable names
  $::name
  $name::
  $Foo::name
  $Foo::::name
  $my__name
  ${name
  $3foo

=head2 Keywords

The List of Keywords:

  alias
  allow
  as
  basic_type_id
  break
  byte
  can
  case
  cmp
  class
  compile_type_name
  copy
  default
  die
  div_uint
  div_ulong
  double
  dump
  elsif
  else
  enum
  eq
  eval
  eval_error_id
  extends
  for
  float
  false
  gt
  ge
  has
  if
  interface
  int
  interface_t
  isa
  isa_error
  isweak
  is_compile_type
  is_type
  is_error
  is_read_only
  args_width
  last
  length
  lt
  le
  long
  make_read_only
  my
  mulnum_t
  method
  mod_uint
  mod_ulong
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
  protected
  public
  precompile
  pointer
  return
  require
  required
  rw
  ro
  say
  static
  switch
  string
  short
  scalar
  true
  type_name
  undef
  unless
  unweaken
  use
  version
  void
  warn
  while
  weaken
  wo
  INIT
  __END__
  __PACKAGE__
  __FILE__
  __LINE__

=head2 Operator Tokens

The List of Operator Tokens:

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

=head2 Comment

Comments have no meaning.

  #COMMENT

A comment begins with C<#>.

It is followed by any string I<COMMENT>.

It ends with ASCII C<LF>.

L<Line directives|/"Line Directive"> take precedence over comments.

L<File directives|/"File Directive"> take precedence over comments.

Examples:

  # This is a comment line

=head2 Line Directive

A line directive set the current line number.

  #line NUMBER

A line directive begins with C<#line> from the beggining of the line.

It is followed by one or more ASCII C<SP>.

It is followed by I<NUMBER>. I<NUMBER> is a positive 32bit integer.

It ends with ASCII C<LF>.

The current line number of the source code is set to I<NUMBER>.

Line directives take precedence over L<comments|/"Comment">.

Compilation Errors:

A line directive must begin from the beggining of the line. Otherwise an compilation error occurs.

A line directive must end with "\n". Otherwise an compilation error occurs.

A line directive must have a line number. Otherwise an compilation error occurs.

The line number given to a line directive must be a positive 32bit integer. Otherwise an compilation error occurs.

Examples:

  class MyClass {
    
    static method main : void () {
      
  #line 39
      
    }
  }

=head2 File Directive

A file directive set the current file path.

  #file "FILE_PATH"

A file directive begins from the beggining of the source code.

It is followed by one or more ASCII C<SP>.

It is followed by C<">.

It is followed by I<FILE_PATH>. I<FILE_PATH> is a string that represetns a file path.

It is closed with C<">.

It ends with ASCII C<LF>.

The current file path is set to I<FILE_PATH>.

File directives take precedence over L<comments|/"Comment">.

Compilation Errors:

A file directive must begin from the beggining of the source code. Otherwise an compilation error occurs.

A file directive must end with "\n". Otherwise an compilation error occurs.

A file directive must have a file path. Otherwise an compilation error occurs.

A file directive must end with ". Otherwise an compilation error occurs.

Examples:

  #file "/path/MyClass.spvm"
  class MyClass {
  
  }

=head2 __END__

If a line begins with C<__END__> and ends with ASCII C<LF>, the line with C<__END__> and the below lines are interpreted as L<comments|/"Comment">.

Examples:
  
  class MyClass {
    
  }
  
  __END__
  
  foo
  bar

=head2 POD

POD is a syntax to write multiline comment. POD has no meaning.

The Beginning of a POD:

  =NAME

The beginning of a POD begins with C<=> from the beggining of the line.

It is followed by I<NAME>. I<NAME> is any string that begins with ASCII C<a-zA-Z>.

It ends with ASCII C<LF>.

The End of a POD:

  =cut

The end of a POD begins with C<=> from the beggining of the line.

It is followed by C<cut>.

It ends with ASCII C<LF>.

Examples:

  
  =pod
  
  Comment1
  Comment2
  
  =cut
  
  =head1
  
  Comment1
  Comment2
  
  =cut

=head2 Fat Comma

A fat comma is

  =>

The fat comma is an alias for a comma C<,>.

  # Comma
  ["a", "b", "c", "d"]
  
  # Fat Comma
  ["a" => "b", "c" => "d"]

If the left operand of a fat comma is a L<symbol name|/"Symbol Name"> without C<::>, it is wrraped by C<"> and is treated as a L<string literal|/"String Literal">.

  # foo_bar2 is treated as "foo_bar2"
  [foo_bar2 => "Mark"]
  
  ["foo_bar2" => "Mark"]

=head1 Literals

A literal represents a constant value.

=head2 Numeric Literals

A numeric literal represents a constant L<number|SPVM::Document::Language::Types/"Number">.

=head2 Integer Literals

A interger literal represents a constant number of an L<integer type|SPVM::Document::Language::Types/"Integer Types">.

=head3 Integer Literal Decimal Notation

The interger literal decimal notation represents a number of the int type or the long type using decimal numbers C<0-9>.
  
It can begin with a minus C<->.

It is followed by one or more of C<0-9>.

C<_> can be placed at the any positions after the first C<0-9> as a separator. C<_> has no meaning.

It can end with the suffix C<L> or C<l>.

If the suffix C<L> or C<l> exists, the return type is the long type. Otherwise the return type is the int type.

Compilation Errors:

If the return type is the int type and the value is greater than the max value of the int type or less than the minimal value of the int type, a compilation error occurs.

If the return type is the long type and the value is greater than the max value of the long type or less than the minimal value of the long type, a compilation error occurs.

Examples:

  123
  -123
  123L
  123l
  123_456_789
  -123_456_789L

=head3 Integer Literal Hexadecimal Notation

The interger literal hexadecimal notation represents a number of the int type or the long type using hexadecimal numbers C<0-9a-zA-Z>.

It can begin with a minus C<->.

It is followed by C<0x> or C<0X>.

It is followed by one or more C<0-9a-zA-Z>. This is called hexadecimal numbers part.

C<_> can be placed at the any positions after C<0x> or C<0X> as a separator. C<_> has no meaning.

It can end with the suffix C<L> or C<l>.

If the suffix C<L> or C<l> exists, the return type is the long type. Otherwise the return type is the int type.

If the return type is the int type, the hexadecimal numbers part is interpreted as an unsigned 32 bit integer, and is converted to a signed 32-bit integer without changing the bits. For example, C<0xFFFFFFFF> is  -1.

If the return type is the long type, the hexadecimal numbers part is interpreted as unsigned 64 bit integer, and is converted to a signed 64-bit integer without changing the bits. For example, C<0xFFFFFFFFFFFFFFFFL> is C<-1L>.

Compilation Errors:

If the return type is the int type and the hexadecimal numbers part is greater than hexadecimal C<FFFFFFFF>, a compilation error occurs.

If the return type is the long type and the hexadecimal numbers part is greater than hexadecimal C<FFFFFFFFFFFFFFFF>, a compilation error occurs.

Examples:

  0x3b4f
  0X3b4f
  -0x3F1A
  0xDeL
  0xFFFFFFFF
  0xFF_FF_FF_FF
  0xFFFFFFFFFFFFFFFFL

=head3 Integer Literal Octal Notation

The interger literal octal notation represents a number of the int type or the long type using octal numbers C<0-7>.

It can begin with a minus C<->.

It is followed by C<0>.

It is followed by one or more C<0-7>. This is called octal numbers part.

C<_> can be placed at the any positions after C<0> as a separator. C<_> has no meaning.

It can end with the suffix C<L> or C<l>.

If the suffix C<L> or C<l> exists, the return type is the long type. Otherwise the return type is the int type.

If the return type is the int type, the octal numbers part is interpreted as an unsigned 32 bit integer, and is converted to a signed 32-bit integer without changing the bits. For example, C<037777777777> is  -1.

If the return type is the long type, the octal numbers part is interpreted as unsigned 64 bit integer, and is converted to a signed 64-bit integer without changing the bits. For example, C<01777777777777777777777L> is C<-1L>.

If the return type is the long type, the value that is except for C<-> is interpreted as unsigned 64 bit integer C<uint64_t> type in the C language, and the following conversion is performed.

Compilation Errors:

If the return type is the int type and the octal numbers part is greater than octal 37777777777, a compilation error occurs.

If the return type is the long type and the octal numbers part is greater than octal 1777777777777777777777, a compilation error occurs.

Examples:

  0755
  -0644
  0666L
  0655_755

=head3 Integer Literal Binary Notation

The interger literal binary notation represents a number of the int type or the long type using binary numbers C<0> and C<1>.

It can begin with a minus C<->.

It is followed by C<0b> or C<0B>.

It is followed by one or more C<0> and C<1>. This is called binary numbers part.

C<_> can be placed at the any positions after C<0b> or C<0B> as a separator. C<_> has no meaning.

It can end with the suffix C<L> or C<l>.

If the suffix C<L> or C<l> exists, the return type is the long type. Otherwise the return type is the int type.

If the return type is the int type, the binary numbers part is interpreted as an unsigned 32 bit integer, and is converted to a signed 32-bit integer without changing the bits. For example, C<0b11111111111111111111111111111111> is  -1.

If the return type is the long type, the binary numbers part is interpreted as unsigned 64 bit integer, and is converted to a signed 64-bit integer without changing the bits. For example, C<0b1111111111111111111111111111111111111111111111111111111111111111L> is C<-1L>.

Compilation Errors:

If the return type is the int type and the value that is except for C<-> is greater than binary C<11111111111111111111111111111111>, a compilation error occurs.

If the return type is the long type and the value that is except for C<-> is greater than binary C<1111111111111111111111111111111111111111111111111111111111111111>, a compilation error occurs.

Examples:

  0b0101
  -0b1010
  0b110000L
  0b10101010_10101010

=head2 Floating Point Literals

The floating point litral represetns a floating point number.

=head3 Floating Point Literal Decimal Notation

The floating point litral decimal notation represents a number of the float type and the double type using decimal numbers C<0-9>.

It can begin with a minus C<->.

It is followed by one or more C<0-9>.

C<_> can be placed at the any positions after the first C<0-9>.

It can be followed by a floating point part, an exponent part, or a combination of a floating point part and an exponent part.

[Floating Point Part Begin]

A floating point part begins with C<.>.

It is followed by one or more C<0-9>.

[Floating Point Part End]

[Exponent Part Begin]

An exponent part begins with C<e> or C<E>.

It can be followed by C<+> or C<->

It is followed by one or more C<0-9>.

[Exponent Part End]

A floating point litral decimal notation can end with a suffix C<f>, C<F>, C<d>, or C<D>.

If a suffix does not exists, a floating point litral decimal notation must have a floating point part or an exponent part.

If the suffix C<f> or C<F> exists, the return type is the float type. Otherwise the return type is the double type.

Compilation Errors:

If the return type is the float type, the floating point litral decimal notation without the suffix must be able to be parsed by the C<strtof> function in the C language. Otherwise, a compilation error occurs.

If the return type is the double type, the floating point litral decimal notation without the suffix must be able to be parsed by the C<strtod> function in the C language. Otherwise, a compilation error occurs.

Examples:

  1.32
  -1.32
  1.32f
  1.32F
  1.32d
  1.32D
  1.32e3
  1.32e-3
  1.32E+3
  1.32E-3
  1.32e3f
  12e7

=head3 Floating Point Literal Hexadecimal Notation

The floating point litral hexadecimal notation represents a number of the float type and the double type using hexadecimal numbers C<0-9a-zA-Z>.

It can begin with a minus C<->.

It is followed by C<0x> or C<0X>.

It is followed by one or more C<0-9a-zA-Z>.

C<_> can be placed at the any positions after C<0x> or C<0X>.

It can be followed by a floating point part, an exponent part, or a combination of a floating point part and an exponent part.

[Floating Point Part Begin]

A floating point part begins with C<.>

It is followed by one or more C<0-9a-zA-Z>.

[Floating Point Part End]

[Exponent Part Begin]

An exponent part begins with C<p> or C<P>.

It can be followed by C<+> or C<->.

It is followed by one or more C<0-9>.

[Exponent Part End]

A floating point litral hexadecimal notation can end with a suffix C<f>, C<F>, C<d>, or C<D>.

If a suffix does not exists, a floating point litral hexadecimal notation must have a floating point part or an exponent part.

Compilation Errors:

If the return type is the float type, the floating point litral hexadecimal notation without the suffix must be able to be parsed by the C<strtof> function in the C language. Otherwise, a compilation error occurs.

If the return type is the double type, thefloating point litral hexadecimal notation without the suffix must be able to be parsed by the C<strtod> function in the C language. Otherwise, a compilation error occurs.

Examples:

  0x3d3d.edp0
  0x3d3d.edp3
  0x3d3d.edP3
  0x3d3d.edP+3
  0x3d3d.edP-3f
  0x3d3d.edP-3F
  0x3d3d.edP-3d
  0x3d3d.edP-3D
  0x3d3dP+3

=head2 Bool Literals

The bool literal represents a bool object.

=head3 true

C<true> is the alias for L<Bool#TRUE|SPVM::Bool/"TRUE">.

  true

Examples:

  # true
  my $bool_object_true = true;

=head3 false

C<false> is the alias for L<Bool#FALSE|SPVM::Bool/"FALSE">.

  false

Examples:

  # false
  my $bool_object_false = false;

=head2 Character Literal

A character literal represents a number of the L<byte type|SPVM::Document::Language::Types/"byte Type"> that normally represents an ASCII character.

It begins with C<'>.

It is followed by a printable ASCII character C<0x20-0x7e> or an L<character literal escape character|/"Character Literal Escape Characters">.

It ends with C<'>.

The return type is the byte type.

Compilation Errors:

If the format of the character literal is invalid, a compilation error occurs.

=head3 Character Literal Escape Characters

The List of Character Literal Escape Characters:

=begin html

<table>
  <tr>
    <th>
      Character Literal Escape Characters
    </th>
    <th>
      Values
    </th>
  </tr>
  <tr>
    <td>
      \a
    </td>
    <td>
      <code>0x07</code> BEL
    </td>
  </tr>
  <tr>
    <td>
      \t
    </td>
    <td>
      <code>0x09</code> HT
    </td>
  </tr>
  <tr>
    <td>
      \n
    </td>
    <td>
      <code>0x0A</code> LF
    </td>
  </tr>
  <tr>
    <td>
      \f
    </td>
    <td>
      <code>0x0C</code> FF
    </td>
  </tr>
  <tr>
    <td>
      \r
    </td>
    <td>
      <code>0x0D</code> CR
    </td>
  </tr>
  <tr>
    <td>
      \"
    </td>
    <td>
      <code>0x22</code> "
    </td>
  </tr>
  <tr>
    <td>
      \'
    </td>
    <td>
      <code>0x27</code> '
    </td>
  </tr>
  <tr>
    <td>
      \\
    </td>
    <td>
      <code>0x5C</code> \
    </td>
  </tr>
  <tr>
    <td>
      <a href="#Octal-Escape-Character">Octal Escape Character</a>
    </td>
    <td>
      A number represented by an octal escape character
    </td>
  </tr>
  <tr>
    <td>
      <a href="#Hexadecimal-Escape-Character">Hexadecimal Escape Character</a>
    </td>
    <td>
      A number represented by a hexadecimal escape character
    </td>
  </tr>
</table>

=end html

The type of every character literal escape character is the byte type.

Examples:

  # Charater literals
  'a'
  'x'
  '\a'
  '\t'
  '\n'
  '\f'
  '\r'
  '\"'
  '\''
  '\\'
  ' '
  '\0'
  '\012'
  '\377'
  '\o{1}'
  '\xab'
  '\xAB'
  '\x0D'
  '\x0A'
  '\xD'
  '\xA'
  '\xFF'
  '\x{A}'

=head2 Octal Escape Character

The octal escape character represents an unsined 8-bit integer using octal numbers C<0-7>.

The octal escape character is a part of a L<string literal|/"String Literal"> and a L<character literal|/"Character Literal">.

It begins with C<\0>, C<\1>, C<\2>, C<\3>, C<\4>, C<\5>, C<\6>, C<\7>, or C<\o{>.

If it begins with C<\0>, C<\1>, C<\2>, C<\3>, C<\4>, C<\5>, C<\6>, or C<\7>, it is followed by one to two C<0-7>.

If it begins with C<\o{>, it is followed by one to three C<0-7>, and ends with C<}>.

The octal numbers after C<\> or C<\o{> is called octal numbers part.

Octal numbers part is interpreted as an unsined 8-bit integer, and is converted to a number of the byte type without changing the bits.

Compilation Errors:

The octal numbers part must be less than or equal to C<377>. Otherwise a compilation error occurs.

If an octal escape character begins with C<\o{>, the close C<}> must exist. Otherwise a compilation error occurs.

Examples:
  
  # Octal escape characters
  \0
  \01
  \03
  \012
  \001
  \077
  \377
  \o{1}
  \o{12}

=head2 Hexadecimal Escape Character

The hexadecimal escape character represents an unsined 8-bit integer using hexadecimal numbers C<0-9a-fA-F>.

The hexadecimal escape character is a part of a L<string literal|/"String Literal"> and a L<character literal|/"Character Literal">.

The hexadecimal escape character begins with C<\x>.

It can be followed by C<{>.

It is followed by one or two C<0-9a-fA-F>. This is called hexadecimal numbers part.

If it contains C<{>, it must be followed by C<}>.

Hexadecimal numbers part is interpreted as an unsined 8-bit integer, and is converted to a number of the byte type without changing the bits.

Compilation Errors:

If the format of the hexadecimal escape character is invalid, a compilation error occurs.

Examples:
  
  # Hexadecimal escape characters
  \xab
  \xAB
  \x0D
  \x0A
  \xD
  \xA
  \xFF
  \x{A}

=head2 String Literal

A string literal represents a constant L<string|SPVM::Document::Language::Types/"String">.

A string literal begins with C<">.

It is followed by zero or more UTF-8 characters, L<string literal escape characters|/"String Literal Escape Characters">, or L<variable expansions|/"Variable Expansion">.

It ends with C<">.

The return type is the L<string type|SPVM::Document::Language::Types/"string Type">.

Compilation Errors:

If the format of the string literal is invalid, a compilation error occurs.

Examples:

  # String literals
  ""
  "abc";
  "あいう"
  "hello\tworld\n"
  "hello\x0D\x0A"
  "hello\xA"
  "hello\x{0A}"
  "hello\0"
  "hello\012"
  "hello\377"
  "AAA $foo BBB"
  "AAA $FOO BBB"
  "AAA $$foo BBB"
  "AAA $foo->{x} BBB"
  "AAA $foo->[3] BBB"
  "AAA $foo->{x}[3] BBB"
  "AAA $@ BBB"
  "\N{U+3042}\N{U+3044}\N{U+3046}"

=head3 String Literal Escape Characters

The List of String Literal Escape Characters:

=begin html

<table>
  <tr>
    <th>
      String Literal Escape Characters
   </th>
    <th>
      Values
   </th>
  </tr>
  <tr>
    <td>
      \a
    </td>
    <td>
      <code>0x07</code> BEL
    </td>
  </tr>
  <tr>
    <td>
      \t
    </td>
    <td>
      <code>0x09</code> HT
    </td>
  </tr>
  <tr>
    <td>
      \n
    </td>
    <td>
      <code>0x0A</code> LF
    </td>
  </tr>
  <tr>
    <td>
      \f
    </td>
    <td>
      <code>0x0C</code> FF
    </td>
  </tr>
  <tr>
    <td>
      \r
    </td>
    <td>
      <code>0x0D</code> CR
    </td>
  </tr>
  <tr>
    <td>
      \"
    </td>
    <td>
      <code>0x22</code> "
    </td>
  </tr>
  <tr>
    <td>
      \$
    </td>
    <td>
      <code>0x24</code> $
    </td>
  </tr>
  <tr>
    <td>
      \'
    </td>
    <td>
      <code>0x27</code> '
    </td>
  </tr>
  <tr>
    <td>
      \\
    </td>
    <td>
      <code>0x5C</code> \
    </td>
  </tr>
  <tr>
    <td>
      <a href="#Octal-Escape-Character">Octal Escape Character</a>
    </td>
    <td>
      A number represented by an octal escape character
    </td>
  </tr>
  <tr>
    <td>
      <a href="#Hexadecimal-Escape-Character">Hexadecimal Escape Character</a>
    </td>
    <td>
      A number represented by a hexadecimal escape character
    </td>
  </tr>
  <tr>
    <td>
      <a href="#Unicode-Escape-Character">A Unicode escape character</a>
    </td>
    <td>
      Numbers represented by an Unicode escape character
    </td>
  </tr>
  <tr>
    <td>
      <a href="#Raw-Escape-Characters">A raw escape character</a>
    </td>
    <td>
      Numbers represented by a hexadecimal escape character
    </td>
  </tr>
</table>

=end html

The type of every string literal escape character ohter than the Unicode escape character and the raw escape character is the byte type.

The type of each number contained in the Unicode escape character and the raw escape character is the byte type.

=head3 Unicode Escape Character

The Unicode escape character represents an UTF-8 character.

An UTF-8 character is represented by an Unicode code point with hexadecimal numbers C<0-9a-fA-F>.

This is one to four numbers of the byte type.

The Unicode escape character is a part of a L<string literal|/"String Literal">.

It begins with C<\N{U+>.

It is followed by one or more C<0-9a-fA-F>. This is called code point part.

It ends with C<}>.

Compilation Errors:

If a code point part is not a Unicode scalar value, a compilation error occurs.

Examples:
  
  # Unicode escape characters
  
  # あ
  \N{U+3042}
  
  # い
  \N{U+3044}
  
  # う
  \N{U+3046}"

=head3 Raw Escape Characters

A raw escape character is an escapa character that <\> is interpreted as ASCII C<\> and the following character is interpreted as itself.

For example, a raw escape character C<\s> is ASCII chracters C<\s>.

A raw escape character is a part of a L<string literal|/"String Literal">.

The List of Raw Escape Characters:

=begin html

<table>
  <tr><th>Raw Escape Characters</th></tr>
  <tr><td>\!</td></tr>
  <tr><td>\#</td></tr>
  <tr><td>\%</td></tr>
  <tr><td>\&</td></tr>
  <tr><td>\(</td></tr>
  <tr><td>\)</td></tr>
  <tr><td>\*</td></tr>
  <tr><td>\+</td></tr>
  <tr><td>\,</td></tr>
  <tr><td>\-</td></tr>
  <tr><td>\.</td></tr>
  <tr><td>\/</td></tr>
  <tr><td>\:</td></tr>
  <tr><td>\;</td></tr>
  <tr><td>\<</td></tr>
  <tr><td>\=</td></tr>
  <tr><td>\></td></tr>
  <tr><td>\?</td></tr>
  <tr><td>\@</td></tr>
  <tr><td>\A</td></tr>
  <tr><td>\B</td></tr>
  <tr><td>\D</td></tr>
  <tr><td>\G</td></tr>
  <tr><td>\H</td></tr>
  <tr><td>\K</td></tr>
  <tr><td>\N</td></tr>
  <tr><td>\P</td></tr>
  <tr><td>\R</td></tr>
  <tr><td>\S</td></tr>
  <tr><td>\V</td></tr>
  <tr><td>\W</td></tr>
  <tr><td>\X</td></tr>
  <tr><td>\Z</td></tr>
  <tr><td>\[</td></tr>
  <tr><td>\]</td></tr>
  <tr><td>\^</td></tr>
  <tr><td>\_</td></tr>
  <tr><td>\`</td></tr>
  <tr><td>\b</td></tr>
  <tr><td>\d</td></tr>
  <tr><td>\g</td></tr>
  <tr><td>\h</td></tr>
  <tr><td>\k</td></tr>
  <tr><td>\p</td></tr>
  <tr><td>\s</td></tr>
  <tr><td>\v</td></tr>
  <tr><td>\w</td></tr>
  <tr><td>\z</td></tr>
  <tr><td>\{</td></tr>
  <tr><td>\|</td></tr>
  <tr><td>\}</td></tr>
  <tr><td>\~</td></tr>
</table>

=end html

=head3 Variable Expansion

The variable expasion is a syntax to embed L<getting a local variable|SPVM::Document::Language::Operators/"Getting a Local Variable">, L<getting a class variables|SPVM::Document::Language::Operators/"Getting a Class Variable">, a L<dereference|SPVM::Document::Language::Operators/"Dereference Operator">, L<getting a field|SPVM::Document::Language::Operators/"Getting a Field">, L<getting an array element|SPVM::Document::Language::Operators/"Getting an Array Element">, L<getting the exception variable|SPVM::Document::Language::Operators/"Getting the Exception Variable"> into a L<string literal|"String Literal">.

  "AAA $foo BBB"
  "AAA $FOO BBB"
  "AAA $$foo BBB"
  "AAA $foo->{x} BBB"
  "AAA $foo->[3] BBB"
  "AAA $foo->{x}[3] BBB"
  "AAA $foo->{x}->[3] BBB"
  "AAA $@ BBB"
  "AAA ${foo}BBB"

The above codes are expanded to the following codes.

  "AAA " . $foo . " BBB"
  "AAA " . $FOO . " BBB"
  "AAA " . $$foo . " BBB"
  "AAA " . $foo->{x} . " BBB"
  "AAA " . $foo->[3] . " BBB"
  "AAA " . $foo->{x}[3] . " BBB"
  "AAA " . $foo->{x}->[3] . " BBB"
  "AAA " . $@ . "BBB"
  "AAA " . ${foo} . "BBB"

The operation of getting field does not contain L<space characters|/"Space Characters"> between C<{> and C<}>.

The index of getting array element must be a constant interger.

The getting array dose not contain L<space characters|/"Space Characters"> between C<[> and C<]>.

The end C<$> is interpreted by C<$>, not interpreted as a variable expansion.
  
  # AAA$
  "AAA$"

=head2 Single-Quoted String Literal

A single-quoted string literal represents a constant string without variable expansions with a few escape characters.

It begins with C<q'>.

It is followed by zero or more UTF-8 characters, or L<single-quoted string literal escape characters|/"Single-Quoted String Literal Escape Characters">.

It ends with C<'>.

The return type is the L<string type|SPVM::Document::Language::Types/"string Type">.

Compilation Errors:

A single-quoted string literal must be end with C<'>. Otherwise a compilation error occurs.

If the escape character in a single-quoted string literal is invalid, a compilation error occurs.

Examples:

  # Single-quoted string literals
  q'abc';
  q'abc\'\\';

=head3 Single-Quoted String Literal Escape Characters

The List of Single-Quoted String Literal Escape Characters:

=begin html

<table>
  <tr>
    <th>
      Single-Quoted String Literal Escape Characters
   </th>
    <th>
      Values
   </th>
  </tr>
  <tr>
    <td>
      \'
    </td>
    <td>
      <code>0x27</code> '
    </td>
  </tr>
  <tr>
    <td>
      \\
    </td>
    <td>
      <code>0x5C</code> \
    </td>
  </tr>
</table>

=end html

The type of every single-quoted string literal escape character is the byte type.

=head2 Here Document

A here document represents a constant string in multiple lines without escape characters and L<variable expansions|/"Variable Expansion">.

  <<'HERE_DOCUMENT_NAME';
  LINE1
  LINE2
  LINEn
  HERE_DOCUMENT_NAME

A here document begins with C<<<'HERE_DOCUMENT_NAME';> and ASCII C<LF>.

I<HERE_DOCUMENT_NAME> is a L<here document name|/"Here Document Name">.

It is followed by a string in multiple lines.

It ends with I<HERE_DOCUMENT_NAME> from the beginning of a line and ASCII C<LF>.

Compilation Errors:

C<<<'HERE_DOCUMENT_NAME';> must not contain L<space characters|/"Space Characters">. Otherwise a compilation error occurs.

Examples:
  
  # Here document
  my $string = <<'EOS';
  Hello
  World
  EOS

=head3 Here Document Name

A here document name consist of C<a-z>, C<A-Z>, C<_>, C<0-9>.

The length of a here document name is greater than or equal to 0.

A here document name cannot begin with C<0-9>.

A here document name cannot contain C<__>.

Compilaition Errors:

If the format of a here document name is invalid, a compilatio error occurs.

=head1 See Also

=over 2

=item * L<SPVM::Document::Language::SyntaxParsing>

=item * L<SPVM::Document::Language::Statements>

=item * L<SPVM::Document::Language::Operators>

=item * L<SPVM::Document::Language::Class>

=item * L<SPVM::Document::Language>

=item * L<SPVM::Document>

=back

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
