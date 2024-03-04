=head1 Name

SPVM::Document::Language::Tokenization - Lexical Tokenization in SPVM Language

=head1 Description

This document describes lexical tokenization in SPVM language.

=head1 Tokenization

The tokenizing the source codes of SPVM language is explained.

=head2 Character Encoding of Source Code

The character encoding of SPVM source codes is UTF-8.

If a character is ASCII, it must be ASCII printable characters or ASCII space characters except for ASCII C<CR>.

Compilation Errors:

The charactor encoding of SPVM source codes must be UTF-8. Otherwise a compilation error occurs.

If a character in an SPVM source code is ASCII, it must be ASCII printable or space.

The new line of SPVM source codes must be LF. The source code cannot contains CR and CRLF.

=head2 Line Terminators

The line terminators are 0x2A C<LF> of ASCII.

When a line terminator appears, the current line number is incremented by 1.

=head2 Space Character

Space characters are C<SP>, C<HT>, C<FF> of ASCII and the L<line terminators|/"Line Terminators">.

=head2 Word Character

The word characters are alphabet(C<a-zA-Z>), number(0-9), and underscore(C<_>) of ASCII.

=head2 Symbol Name

A symbol name is the characters that are composed of L<word characters|/"Word Character"> and C<::>.

A symbol name cannnot contains C<__>, and cannnot begin with a number 0-9.

A symbol name cannnot begin with C<::>, and cannnot end with C<::>.

A symbol name cannnot contains C<::::>, and cannnot begin with a number 0-9.

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

The part names of a class name must begin uppercase letter. If the class name is C<Foo:Bar::Baz>, part names are C<Foo>, C<Bar>, and C<Baz>.

A class name must be the name that the relative class file path's all C</> are replaced with C<::> and the trailing C<.spvm> is removed. For example, If the relative class file path is C<Foo/Bar/Baz.spvm>, the class name must be C<Foo::Bar::Baz>.

  # Valid class name in the class file "Foo/Bar/Baz.spvm"
  class Foo::Bar::Baz {
    
  }

  # Invalid class name in the class file "Foo/Bar/Baz.spvm"
  class Foo::Bar::Hello {
    
  }

Compilation Errors:

If class names are invalid, a compilation error occurs.

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

=head2 Method Name

A method name is a L<symbol name|/"Symbol Name"> that doesn't contains C<::>.

0-length method name is valid. This is used in the L<anon method|/"Anon Method">.

Compilation Errors:

If method names are invalid, a compilation error occurs.

Examples:

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

A method name that is the same as a L<keyword/"Keyword"> is allowed.
  
  # "if" is a valid method name
  static method if : void () {
    
  }

=head2 Field Name

A field name is a L<symbol name|/"Symbol Name"> that doesn't contains C<::>.

Compilation Errors:

If field names are invalid, a compilation error occurs.

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

The field name that is the same as a L<keyword/"Keyword"> is allowed.
  
  # "if" is a valid field name
  has if : int;

=head2 Variable Name

A variable name begins with C<$> and is followed by a L<symbol name|/"Symbol Name">.

Compilation Errors:

The L<symbol name|/"Symbol Name"> can be wrapped by C<{> and C<}>. If a opening C<{> exists and the closing C<}> doesn't exists, a compilation error occurs.

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

=head2 Class Variable Name

A class variable name is a L<variable name|/"Variable Name">.

Compilation Errors:

If class variable names are invalid, a compilation error occurs.

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

=head2 Local Variable Name

A local variable name is a L<variable name|/"Variable Name"> that doesn't contain C<::>.

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

=head2 Current Class

C<&> before method name means the current class. C<&> is replaced with C<CURRENT_CLASS_NAME-E<gt>>.

Examples:

  class Foo {
    
    static method test : void () {
      # This means Foo->sum(1, 2)
      my $ret = &sum(1, 2);
    }
  
    static method sum : int ($num1 : int, $num2 : int) {
      return $num1 + $num2;
    }
    
  }

=head2 Keyword

The list of keywords:

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

=head2 Operator for Tokenization

The list of the operators for tokenization:

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

Note that the operators for tokenization are different from the operators that are explained in L<operators|/"Operators">. The operators for tokenization are only for tokenization.

=head2 Comment

A comment begins with C<#> and ends with a L<line terminator|/"Line Terminators">.

  # Comment

Comments have no meaning in source codes.

L<Line directives|/"Line Directive"> take precedence over L<comments|/"Comment">.

A L<File directive|/"File Directive"> take precedence over L<comments|/"Comment">.

=head2 Line Directive

A line directive begins from the beggining of the line.

A line directive begins with C<#line > and positive 32bit integer

  #line 39

And ends with a L<line terminator|/"Line Terminators">.
 
The line number in a line directive is set to the current line of the source code.

L<Line directives|/"Line Directive"> take precedence over L<comments|/"Comment">.

Compilation Errors:

A line directive must begin from the beggining of the line. Otherwise an compilation error occurs.

A line directive must end with "\n". Otherwise an compilation error occurs.

A line directive must have a line number. Otherwise an compilation error occurs.

The line number given to a line directive must be a positive 32bit integer. Otherwise an compilation error occurs.

=head2 File Directive

A file directive begins from the beggining of the source code.

A file directive begins with C<#file "> and is followed by a file path, and is closed with C<">

  #file "/Foo/Bar.spvm"

And ends with a L<line terminator|/"Line Terminators">.

The file path is set to the current file path of the source code.

A L<file directive|/"File Directive"> take precedence over L<comments|/"Comment">.

Compilation Errors:

A file directive must begin from the beggining of the source code. Otherwise an compilation error occurs.

A file directive must end with "\n". Otherwise an compilation error occurs.

A file directive must have a file path. Otherwise an compilation error occurs.

A file directive must end with ". Otherwise an compilation error occurs.

=head2 POD

POD(Plain Old Document) is a syntax to write documents in source codes.

The biginning of POD begins with C<=>, and is followed by any string that is composed of ASCII printable characters, and end with a L<line terminator|/"Line Terminators">.

The previous line of the biginning of POD must need a L<line terminator|/"Line Terminators">

The lator line of the biginning of POD must need a L<line terminator|/"Line Terminators">
  
  =pod
  
  =head1
  
  =item * foo
  

The end of POD begins with C<=>, and is followed by C<cut>, and ends with a L<line terminator|/"Line Terminators">.

The previous line of the end of POD must need a L<line terminator|/"Line Terminators">

The lator line of the end of POD must need a L<line terminator|/"Line Terminators">

  
  =cut
  

Examples:

  
  =pod
  
  Multi-Line
  Comment
  
  =cut
  
  =head1
  
  Multi-Line
  Comment
  
  =cut
  

POD has no meaning in source codes.

=head2 Literal

A literal is the way to write a constant value in source codes.

Literals are L<numeric literals|/"Numeric Literal">, the L<floating point literal|/"Floating Point Literal">, the L<character literal|/"Character Literal">, the L<string literal|/"String Literal"> and the L<bool literal|/"Bool Literal">.

=head2 Numeric Literal

A numeric literal is the way to write a constant value that type is a L<numeric type|/"Numeric Type"> in source codes.

Numeric literals are the L<integer literal|/"Integer Literal"> and the L<floating point literal|/"Floating Point Literal">.

=head2 Integer Literal

A interger literal is a L<numeric literal/"Numeric Literal"> to write a constant value that type is an L<integer type|/"Integer Type"> in source codes.

=head3 Integer Literal Decimal Notation

The interger literal decimal notation is the way to write an L<integer literal|/"Integer Literal"> using decimal numbers 0-9.

A minus - can be at the beginning, and is followed by one or more of 0-9.

C<_> can be used as a separator at the any positions after the first 0-9. C<_> has no meaning.

The suffix C<L> or C<l> can be at the end.

If the suffix C<L> or C<l> exists, the return type is the long type. Otherwise the return type is the int type.

Compilation Errors:

If the return type is the int type and the value is greater than the max value of L<int type|/"int Type"> or less than the minimal value of L<int type|/"int Type">, a compilation error occurs.

If the return type is the long type and the value is greater than the max value of L<long type|/"long Type"> or less than the minimal value of L<long type|/"long Type">, a compilation error occurs.

Examples:

  123
  -123
  123L
  123l
  123_456_789
  -123_456_789L

=head3 Integer Literal Hexadecimal Notation

The interger literal hexadecimal notation is the way to write an L<integer literal|/"Integer Literal"> using hexadecimal numbers C<0-9a-zA-Z>.

A minus - can be at the beginning, and is followed by C<0x> or C<0X>, and is followed by one or more C<0-9a-zA-Z>.

C<_> can be used as a separator at the any positions after C<0x> or C<0X>. C<_> has no meaning.

The suffix C<L> or C<l> can be at the end.

If the suffix C<L> or C<l> exists, the return type is the long type. Otherwise the return type is the int type.

If the return type is the int type, the value that is except for - is interpreted as unsigned 32 bit integer C<uint32_t> type in the C language, and the following conversion is performed.

  uint32_t value_uint32_t;
  int32_t value_int32_t = (int32_t)value_uint32_t;

And if - exists, the following conversion is performed.

  value_int32_t = -value_int32_t;

For example, C<0xFFFFFFFF> is the same as -1, C<-0xFFFFFFFF> is the same as 1.

If the return type is the long type, the value that is except for - is interpreted as unsigned 64 bit integer C<uint64_t> type in the C language, and the following conversion is performed.

  uint64_t value_uint64_t;
  value_int64_t = (int64_t)value_uint64_t;

And if - exists, the following conversion is performed.

  value_int64_t = -value_int64_t;

For example, C<0xFFFFFFFFFFFFFFFFL> is the same as C<-1L>, C<-0xFFFFFFFFFFFFFFFFL> is the same as C<1L>.

Compilation Errors:

If the return type is the int type and the value that is except for - is greater than hexadecimal C<FFFFFFFF>, a compilation error occurs.

If the return type is the long type and the value that is except for - is greater than hexadecimal C<FFFFFFFFFFFFFFFF>, a compilation error occurs.

Examples:

  0x3b4f
  0X3b4f
  -0x3F1A
  0xDeL
  0xFFFFFFFF
  0xFF_FF_FF_FF
  0xFFFFFFFFFFFFFFFFL

=head3 Integer Literal Octal Notation

The interger literal octal notation is the way to write an L<integer literal|/"Integer Literal"> using octal numbers 0-7.

A minus - can be at the beginning, and is followed by 0, and is followed by one or more 0-7.

C<_> can be used as a separator at the any positions after 0. C<_> has no meaning.

The suffix C<L> or C<l> can be at the end.

If the suffix C<L> or C<l> exists, the return type is the long type. Otherwise the return type is the int type.

If the return type is the int type, the value that is except for - is interpreted as unsigned 32 bit integer C<uint32_t> type in the C language, and the following conversion is performed.

  uint32_t value_uint32_t;
  int32_t value_int32_t = (int32_t)value_uint32_t;

And if - exists, the following conversion is performed.

  value_int32_t = -value_int32_t;

For example, 037777777777 is the same as -1, -037777777777 is the same as 1.

If the return type is the long type, the value that is except for - is interpreted as unsigned 64 bit integer C<uint64_t> type in the C language, and the following conversion is performed.

  uint64_t value_uint64_t;
  value_int64_t = (int64_t)value_uint64_t;

And if - exists, the following conversion is performed.

  value_int64_t = -value_int64_t;

For example, C<01777777777777777777777L> is the same as C<-1L>, C<-01777777777777777777777L> is the same as C<1L>.

Compilation Errors:

If the return type is the int type and the value that is except for - is greater than octal 37777777777, a compilation error occurs.

If the return type is the long type and the value that is except for - is greater than octal 1777777777777777777777, a compilation error occurs.

Examples:

  0755
  -0644
  0666L
  0655_755

=head3 Integer Literal Binary Notation

The interger literal binary notation is the way to write an L<integer literal|/"Integer Literal"> using binary numbers 0 and 1.

A minus - can be at the beginning, and is followed by C<0b> or C<0B>, and is followed by one or more 0 and 1.

C<_> can be used as a separator at the any positions after C<0b> or C<0B>. C<_> has no meaning.

The suffix C<L> or C<l> can be at the end.

If the suffix C<L> or C<l> exists, the return type is the long type. Otherwise the return type is the int type.

If the return type is the int type, the value that is except for - is interpreted as unsigned 32 bit integer C<uint32_t> type in the C language, and the following conversion is performed.

  uint32_t value_uint32_t;
  int32_t value_int32_t = (int32_t)value_uint32_t;

And if - exists, the following conversion is performed.

  value_int32_t = -value_int32_t;

For example, C<0b11111111111111111111111111111111> is the same as -1, C<-0b11111111111111111111111111111111> is the same as 1.

If the return type is the long type, the value that is except for - is interpreted as unsigned 64 bit integer C<uint64_t> type in the C language, and the following conversion is performed.

  uint64_t value_uint64_t;
  value_int64_t = (int64_t)value_uint64_t;

And if - exists, the following conversion is performed.

  value_int64_t = -value_int64_t;

For example, C<0b1111111111111111111111111111111111111111111111111111111111111111L> is the same as C<-1L>, C<-0b1111111111111111111111111111111111111111111111111111111111111111L> is the same as C<1L>.

Compilation Errors:

If the return type is the int type and the value that is except for - is greater than binary 11111111111111111111111111111111, a compilation error occurs.

If the return type is the long type and the value that is except for - is greater than binary 1111111111111111111111111111111111111111111111111111111111111111, a compilation error occurs.

Examples:

  0b0101
  -0b1010
  0b110000L
  0b10101010_10101010

=head2 Floating Point Literal

The floating point litral is a L<numeric literal/"Numeric Literal"> to write a constant value that type is a L<floating point type|/"Floating Point Type"> in source codes.

=head3 Floating Point Literal Decimal Notation

The floating point litral decimal notation is the way to write a L<floating point literal|/"Floating Point Literal"> using decimal numbers 0-9 in source codes.

A minus - can be at the beginning, and is followed by one or more 0-9

C<_> can be used as a separator at the any positions after the first 0-9.

And can be followed by a floating point part.

A floating point part is . and is followed by one or more 0-9.

And can be followed by an exponent part.

An exponent part is C<e> or C<E> and is followed by C<+>, -, or C<"">, and followed by one or more 0-9.

And can be followed by a suffix is C<f>, C<F>, C<d>, or C<D>.

one of a floating point part, an exponent part, or a suffix must exist.

If the suffix C<f> or C<F> exists, the return type is the L<float type|/"float Type">. Otherwise the return type is the L<double type|/"double Type">.

Compilation Errors:

If the return type is the L<float type|/"float Type">, the floating point literal is parsed by the C<strtof> function of the C language. If the parsing fails, a compilation error occurs.

If the return type is the L<double type|/"double Type">, the floating point literal is parsed by the C<strtod> function of the C language. If the parsing fails, a compilation error occurs.

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
  12e7

=head3 Floating Point Literal Hexadecimal Notation

The floating point litral hexadecimal notation is the way to write a L<floating point literal|/"Floating Point Literal"> using hexadecimal numbers C<0-9a-zA-Z> in source codes.

A minus - can be at the beginning, and is followed by C<0x> or C<0X>, and is followed by one or more C<0-9a-zA-Z>.

C<_> can be used as a separator at the any positions after C<0x> or C<0X>.

And can be followed by a floating point part.

A floating point part is . and is followed by one or more C<0-9a-zA-Z>.

And can be followed by an exponent part.

An exponent part is C<p> or C<P> and is followed by C<+>, -, or C<"">, and followed by one or more decimal numbers 0-9.

And can be followed by a suffix C<f>, C<F>, C<d>, or C<D> if an exponent part exist.

one of a floating point part or an exponent part must exist.

If the suffix C<f> or C<F> exists, the return type is the L<float type|/"float Type">. Otherwise the return type is the L<double type|/"double Type">.

Compilation Errors:

If the return type is the L<float type|/"float Type">, the floating point literal is parsed by the C<strtof> function of the C language. If the parsing fails, a compilation error occurs.

If the return type is the L<double type|/"double Type">, the floating point literal is parsed by the C<strtod> function of the C language. If the parsing fails, a compilation error occurs.

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

=head2 Character Literal

A character literal is a L<literal|/"Literal"> to write a constant value that type is the L<byte type|/"byte Type"> in source codes.

A character literal represents an ASCII character.

A character literal begins with C<'>.

And is followed by a printable ASCII character C<0x20-0x7e> or an L<character literal escape character|/"Character Literal Escape Characters">.

And ends with C<'>.

The return type is the L<byte type|/"byte Type">.

Compilation Errors:

If the format of the character literal is invalid, a compilation error occurs.

=head3 Character Literal Escape Characters

The list of character literal escape characters.

=begin html

<table>
  <tr>
    <th>
      Character literal escape characters
    </th>
    <th>
      ASCII characters
    </th>
  </tr>
  <tr>
    <td>
      \0
    </td>
    <td>
      <code>0x00</code> NUL
    </td>
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
      An ASCII character
    </td>
  </tr>
  <tr>
    <td>
      <a href="#Hexadecimal-Escape-Character">Hexadecimal Escape Character</a>
    </td>
    <td>
      An ASCII character
    </td>
  </tr>
</table>

=end html

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
  '\0'
  ' '
  '\xab'
  '\xAB'
  '\x0D'
  '\x0A'
  '\xD'
  '\xA'
  '\xFF'
  '\x{A}'

=head2 String Literal

A string literal is a L<literal|/"Literal"> to write a constant value that type is the L<string type|/"string Type"> in source codes.

The return type is the L<string type|/"string Type">.

A character literal begins with C<">.

And is followed by zero or more than zero UTF-8 character, or L<string literal escape characters|/"String Literal Escape Characters">, or L<variable expansions|/"Variable Expansion">.

And ends with C<">.

Compilation Errors:

If the format of the string literal is invalid, a compilation error occurs.

Examples:

  # String literals
  "abc";
  "あいう"
  "hello\tworld\n"
  "hello\x0D\x0A"
  "hello\xA"
  "hello\x{0A}"
  "AAA $foo BBB"
  "AAA $FOO BBB"
  "AAA $$foo BBB"
  "AAA $foo->{x} BBB"
  "AAA $foo->[3] BBB"
  "AAA $foo->{x}[3] BBB"
  "AAA $@ BBB"
  "\N{U+3042}\N{U+3044}\N{U+3046}"

=head3 String Literal Escape Characters

=begin html

<table>
  <tr>
    <th>
      String literal escape characters
   </th>
    <th>
      Descriptions
   </th>
  </tr>
  <tr>
    <td>
      <b>\0</b>
    </td>
    <td>
      ASCII <code>0x00</code> NUL
    </td>
  </tr>
  <tr>
    <td>
      <b>\a</b>
    </td>
    <td>
      ASCII <code>0x07</code> BEL
    </td>
  </tr>
  <tr>
    <td>
      <b>\t</b>
    </td>
    <td>
      ASCII <code>0x09</code> HT
    </td>
  </tr>
  <tr>
    <td>
      <b>\n</b>
    </td>
    <td>
      ASCII <code>0x0A</code> LF
    </td>
  </tr>
  <tr>
    <td>
      <b>\f</b>
    </td>
    <td>
      ASCII <code>0x0C</code> FF
    </td>
  </tr>
  <tr>
    <td>
      <b>\r</b>
    </td>
    <td>
      ASCII <code>0x0D</code> CR
    </td>
  </tr>
  <tr>
    <td>
      <b>\"</b>
    </td>
    <td>
      ASCII <code>0x22</code> "
    </td>
  </tr>
  <tr>
    <td>
      <b>\$</b>
    </td>
    <td>
      ASCII <code>0x24</code> $
    </td>
  </tr>
  <tr>
    <td>
      <b>\'</b>
    </td>
    <td>
      ASCII <code>0x27</code> '
    </td>
  </tr>
  <tr>
    <td>
      <b>\\</b>
    </td>
    <td>
      ASCII <code>0x5C</code> \
    </td>
  </tr>
  <tr>
    <td>
      <a href="#Octal-Escape-Character">Octal Escape Character</a>
    </td>
    <td>
      An ASCII character
    </td>
  </tr>
  <tr>
    <td>
      <a href="#Hexadecimal-Escape-Character">Hexadecimal Escape Character</a>
    </td>
    <td>
      An ASCII character
    </td>
  </tr>
  <tr>
    <td>
      <a href="#Unicode-Escape-Character">Unicode escape character</a>
    </td>
    <td>
      An UTF-8 character
    </td>
  </tr>
  <tr>
    <td>
      <a href="#Raw-Escape-Character">Raw escape character</a>
    </td>
    <td>
      The value of raw escape character
    </td>
  </tr>
</table>

=end html

=head3 Unicode Escape Character

The Unicode escape character is the way to write an UTF-8 character using an Unicode code point that is written by hexadecimal numbers C<0-9a-fA-F>.

The Unicode escape character can be used as an escape character of the L<string literal|/"String Literal">.

The Unicode escape character begins with C<N{U+>.

And is followed by one or more C<0-9a-fA-F>.

And ends with C<}>.

Compilation Errors:

If the Unicode code point is not a Unicode scalar value, a compilation error occurs.

Examples:
  
  # あいう
  "\N{U+3042}\N{U+3044}\N{U+3046}"
  
  # くぎが
  "\N{U+304F}\N{U+304E}\N{U+304c}"

=head3 Raw Escape Character

The raw escape character is the escapa character that <\> has no effect and C<\> is interpreted as ASCII C<\>.

For example, C<\s> is ASCII chracters C<\s>, C<\d> is ASCII chracters <\d>.

The raw escape character can be used as an escape character of the L<string literal|/"String Literal">.

The raw escape character is designed to be used by regular expression classes such as L<Regex|SPVM::Regex>.

The list of raw escape characters.
  
  # Raw excape literals
  \! \# \% \& \( \) \* \+ \, \- \. \/
  \: \; \< \= \> \? \@
  \A \B \D \G \H \K \N \P \R \S \V \W \X \Z
  \[ \] \^ \_ \`
  \b \d \g \h \k \p \s \v \w \z
  \{ \| \} \~

=head2 Octal Escape Character

The octal escape character is the way to write an ASCII code using octal numbers 0-7.

The octal escape character can be used as an escape character of the L<string literal|/"String Literal"> and the L<character literal|/"Character Literal">.

The octal escape character begins with C<\o{>, and it must be followed by one to three 0-7, and ends with C<}>.

Or the octal escape character begins with C<\0>, C<\1>, C<\2>, C<\3>, C<\4>, C<\5>, C<\6>, C<\7>, and it must be followed by one or two 0-7.

  # Octal escape ch1racters in ch1racter literals
  '\0'
  '\012'
  '\003'
  '\001'
  '\03'
  '\01'
  '\077'
  '\377'

  # Octal escape ch1racters in ch1racter literals
  '\o{0}'
  '\o{12}'
  '\o{03}'
  '\o{01}'
  '\o{3}'
  '\o{1}'
  '\o{77}'
  '\o{377}'

  # Octal escape ch1racters in string literals
  "Foo \0 Bar"
  "Foo \012 Bar"
  "Foo \003 Bar"
  "Foo \001 Bar"
  "Foo \03  Bar"
  "Foo \01  Bar"
  "Foo \077 Bar"
  "Foo \377 Bar"

  # Octal escape ch1racters in string literals
  "Foo \o{12} Bar"
  "Foo \o{12} Bar"
  "Foo \o{03} Bar"
  "Foo \o{01} Bar"
  "Foo \o{3}  Bar"
  "Foo \o{1}  Bar"
  "Foo \o{77} Bar"
  "Foo \o{377} Bar"

=head2 Hexadecimal Escape Character

The hexadecimal escape character is the way to write an ASCII code using hexadecimal numbers C<0-9a-fA-F>.

The hexadecimal escape character can be used as an escape character of the L<string literal|/"String Literal"> and the L<character literal|/"Character Literal">.

The hexadecimal escape character begins with C<\x>.

And is followed by one or two C<0-9a-fA-F>.

The hexadecimal numbers can be sorrounded by C<{> and C<}>.

  # Hexadecimal escape characters in character literals
  '\xab'
  '\xAB'
  '\x0D'
  '\x0A'
  '\xD'
  '\xA'
  '\xFF'
  '\x{A}'

  # Hexadecimal escape characters in string literals
  "Foo \xab  Bar"
  "Foo \xAB  Bar"
  "Foo \x0D  Bar"
  "Foo \x0A  Bar"
  "Foo \xD   Bar"
  "Foo \xA   Bar"
  "Foo \xFF  Bar"
  "Foo \x{A} Bar"

=head2 Single-Quoted String Literal

A single-quoted string literal represents a constant string value in source codes.

The return type is the L<string type|/"string Type">.

A character literal begins with C<q'>.

And is followed by zero or more than zero UTF-8 character, or L<escape characters|/"Single-Quoted String Literal Escape Characters">.

And ends with C<'>.

Compilation Errors:

A single-quoted string literal must be end with C<'>. Otherwise a compilation error occurs.

If the escape character in a single-quoted string literal is invalid, a compilation error occurs.

Examples:

  # Single-quoted string literals
  q'abc';
  q'abc\'\\';

=head3 Single-Quoted String Literal Escape Characters

=begin html

<table>
  <tr>
    <th>
      Single-quoted string literal escape characters
   </th>
    <th>
      Descriptions
   </th>
  </tr>
  <tr>
    <td>
      <b>\\</b>
    </td>
    <td>
      ASCII <code>0x5C</code> \
    </td>
  </tr>
  <tr>
    <td>
      <b>\'</b>
    </td>
    <td>
      ASCII <code>0x27</code> '
    </td>
  </tr>
</table>

=end html

=head2 Bool Literal

The bool literal is a L<literal|/"Literal"> to represent a bool value in source codes.

=head3 true

C<true> is the alias for the L<TRUE|SPVM::Bool/"TRUE"> method of L<Bool|SPVM::Bool>.

  true

Examples:

  # true
  my $is_valid = true;

=head3 false

C<false> is the alias for L<FALSE|SPVM::Bool/"FALSE"> method of L<Bool|SPVM::Bool>.

  false

Examples:

  # false
  my $is_valid = false;

=head2 Variable Expansion

The variable expasion is the feature to embed L<getting local variable|/"Getting Local Variable">, L<getting class variables|/"Getting Class Variable">, L<dereference|/"Dereference">, L<getting field/"Getting Field">, L<getting array element|/"Getting Array Element">, L<getting exception variable/"Getting Exception Variable"> into the L<string literal|"String Literal">.

  "AAA $foo BBB"
  "AAA $FOO BBB"
  "AAA $$foo BBB"
  "AAA $foo->{x} BBB"
  "AAA $foo->[3] BBB"
  "AAA $foo->{x}[3] BBB"
  "AAA $foo->{x}->[3] BBB"
  "AAA $@ BBB"
  "AAA ${foo}BBB"

The above codes are convarted to the following codes.

  "AAA " . $foo . " BBB"
  "AAA " . $FOO . " BBB"
  "AAA " . $$foo . " BBB"
  "AAA " . $foo->{x} . " BBB"
  "AAA " . $foo->[3] . " BBB"
  "AAA " . $foo->{x}[3] . " BBB"
  "AAA " . $foo->{x}->[3] . " BBB"
  "AAA " . $@ . "BBB"
  "AAA " . ${foo} . "BBB"

The getting field doesn't contain space characters between C<{> and C<}>.

The index of getting array element must be a constant value. The getting array doesn't contain space characters between C<[> and C<]>.

The end C<$> is not interpreted as a variable expansion.

  "AAA$"

=head2 Fat Comma

The fat comma C<=>> is a L<separator|/"Separators">.

  =>

The fat comma is an alias for Comma C<,>.

  # Comma
  ["a", "b", "c", "d"]
  
  # Fat Comma
  ["a" => "b", "c" => "d"]

If the characters of I<LEFT_OPERAND> of the fat camma is not wrapped by C<"> and the characters are a L<symbol name|/"Symbol Name"> that does'nt contain C<::>, the characters are treated as a L<string literal|/"String Literal">.

  # foo_bar2 is treated as "foo_bar2"
  [foo_bar2 => "Mark"]

  ["foo_bar2" => "Mark"]

=head2 Here Document

Here document is syntax to write a string literal in multiple lines without escapes and variable expansions.

  <<'HERE_DOCUMENT_NAME';
  line1
  line2
  line...
  HERE_DOCUMENT_NAME

Here document syntax begins with C<<<'HERE_DOCUMENT_NAME';> + a line terminator. C<HERE_DOCUMENT_NAME> is a L<here document name|/"Here Document Name">.

A string begins from the next line.

Here document syntax ends with the line that begins C<HERE_DOCUMENT_NAME> + a line terminator.

Compilation Errors:

C<<<'HERE_DOCUMENT_NAME'> cannot contains spaces. If so, a compilation error occurs.

Examples:
  
  # Here document
  my $string = <<'EOS';
  Hello
  World
  EOS
  
  # No escapes and variable expaneions are performed.
  my $string = <<'EOS';
  $foo
  \t
  \
  EOS

=head3 Here Document Name

Here document name is composed of C<a-z>, C<A-Z>, C<_>, C<0-9>.

Compilaition Errors:

The length of a here document name must be greater than or equal to 0. Otherwise a compilation error occurs.

A here document name cannot start with a number. If so, a compilation error occurs.

A here document name cannot contain C<__>. If so, a compilation error occurs.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
