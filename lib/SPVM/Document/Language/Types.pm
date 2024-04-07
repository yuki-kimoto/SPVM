=head1 Name

SPVM::Document::Language::Types - Types in the SPVM Language

=head1 Description

This document describes types in the SPVM language.

=head1 Value

This section describes values.

=head2 Number

The value of L<numeric types|/"Numeric Types"> is called number.

Normally, numbers are created by L<numeric literals|SPVM::Document::Language::Tokenization/"Numeric Literal">.

  # byte - 8bit signed integer
  my $number = (byte)1;
  
  # short - 16bit signed integer
  my $number = (short)1;
  
  # int - 32bit signed integer
  my $number = 1;
  
  # long - 64bit signed integer
  my $number = 1L;
  
  # float - 32bit floating point
  my $number = 1.5f;
  
  # double - 64bit floating point
  my $number = 1.0;

A character created by the L<character literal|SPVM::Document::Language::Tokenization/"Character Literal"> is a number of the byte type.
  
  # A number of the byte type created by a character literal
  my $char = 'a';

See the following section operations for numbers.

=over

=item * L<Numeric Operators|SPVM::Document::Language::Operators/"Numeric Operators">

=item * L<Numeric Comparison Operators|SPVM::Document::Language::Operators/"Numeric Comparison Operators">

=back

=head3 Internal Representation of Negative Integers

Negative integers are represented by L<two's complement|https://en.wikipedia.org/wiki/Two%27s_complement>.

=head2 String

The value of the L<string type|/"string Type"> is called string.

A string consists of characters of the C<byte> type.

A string has its length.

A string is an L<object|/"Object">.

Normally, a string is created by a L<string literal|SPVM::Document::Language::Tokenization/"String Literal"> or the L<new_string_len operator|SPVM::Document::Language::Operators/"new_string_len Operator">.
  
  # A string created by a string literal
  my $string = "Hello";
  my $char = $string->[0];
  
  # A mutable string created by the new_string_len operator
  my $string = new_string_len 3;
  $string->[0] = 'a';

See the following sections about operations for strings.

=over 2

=item * L<length Operator|SPVM::Document::Language::Operators/"length Operator">

=item * L<String Concatenation Operator|SPVM::Document::Language::Operators/"String Concatenation Operator">

=item * L<Getting a Character|SPVM::Document::Language::Operators/"Getting a Character">

=item * L<Setting a Character|SPVM::Document::Language::Operators/"Setting a Character">

=item * L<new_string_len Operator|SPVM::Document::Language::Operators/"new_string_len Operator">

=item * L<make_read_only Operator|SPVM::Document::Language::Operators/"make_read_only Operator">

=item * L<is_read_only Operator|SPVM::Document::Language::Operators/"is_read_only Operator">

=item * L<String Comparison Operators|SPVM::Document::Language::Operators/"String Comparison Operators">

=item * L<copy Operator|SPVM::Document::Language::Operators/"copy Operator">

=back

=head3 Sting Native Level Representation

At the L<native level|SPVM::Document::NativeClass>, the character just after the last character of the string is set to C<\0>, so the characters in the string can be used as a C language string.

  # The characters in the string can be used as a C language string
  void* obj_string = stack[0].oval;
  const char* chars = env->get_chars(env, stack, obj_string);
  if (strcmp(chars, "Hello") == 0) {
    
  }

=head2 Array

The value of an L<array type|/"Array Types"> is called array.

An array consists of a set of L<numbers|/"Number">, a set of L<objects|/"Object">, or a set of L<multi-numeric numbers|/"Multi-Numeric Number">.

An array has its length.

The elements of an array are arranged by index and the index starts from 0.

An array is an L<object|/"Object">.

Normally, an array is created by the L<new Operator|SPVM::Document::Language::Operators/"Creating an Array"> and an L<array initialization|SPVM::Document::Language::Operators/"Array Initialization">.
  
  # An array created by the new operator
  my $numbers = new int[3];
  $numbergers->[0] = 1;
  
  my $strings = new string[3];
  
  my $objects = new Point[3];
  
  my $mulnum_numbers = new Complex_2d[3];
  
  # An array created by an array initialization
  my $numbers = [1, 2, 3];

All elements of an array can be got by the L<for statement|SPVM::Document::Language::Statements/"for Statement">.

  # for statement
  for (my $i = 0; $i < @$numbers; $i++) {
    my $number = $numbers->[$i];
  }
  
  # for-each statement
  for my $number (@$numbers) {
    
  }

See the following sections about operations for arrays.

=over 2

=item * L<Creating Array in new Operator|SPVM::Document::Language::Operators/"Creating an Array">

=item * L<Array Initialization|SPVM::Document::Language::Operators/"Array Initialization">

=item * L<Array Length Operator|SPVM::Document::Language::Operators/"Array Length Operator">

=item * L<Getting an Array Element|SPVM::Document::Language::Operators/"Getting an Array Element">

=item * L<Setting an Array Element|SPVM::Document::Language::Operators/"Setting an Array Element">

=back

=head2 Object

The value of an L<object type|/"Object Types"> is called object.

A L<string|/"String"> is an object.

An L<array|/"Array"> is an object.

An objcet of the L<class type|/"class Type"> has its fields. A field is a L<number|/"Number"> or an L<object|/"Object">.

Normally, an object is created by the L<new|SPVM::Document::Language::Operators/"new"> operator.

  # An object created by the new operator
  my $point = new Point;

When an object is created, memory for the object is allocated in heap memory.

Created objects are destroyed by L<garbage collection|SPVM::Document::Language::GarbageCollection>.

See the following sections about operations for objects.

=over 2

=item * L<new Operator|SPVM::Document::Language::Operators/"new Operator">

=item * L<dump Operator|SPVM::Document::Language::Operators/"dump Operator">

=item * L<Getting a Field|SPVM::Document::Language::Operators/"Getting a Field">

=item * L<Setting a Field|SPVM::Document::Language::Operators/"Setting a Field">

=item * L<isa Operator|SPVM::Document::Language::Operators/"isa Operator">

=item * L<is_type Operator|SPVM::Document::Language::Operators/"is_type Operator">

=item * L<type_name Operator|SPVM::Document::Language::Operators/"type_name Operator">

=back

=head3 Object Native Level Representation

At L<native level|SPVM::Document::NativeClass>, an object is a memory address.

  void* obj_point = stack[0].oval;

=head2 Undefined Value

The value of the L<undef type|/"undef Type"> is called undefined value.

An undefined value means the value is undefined.

An undefined value is created by the L<undef|SPVM::Document::Language::Operators/"undef Operator"> operator.

  undef

An undefined value is able to be assigned to an L<object type|/"Object Types">.

  my $point : Point = undef;

Examples:

  # Examples of undefined values
  my $string : string = undef;
  
  if (undef) {
    
  }
  
  my $message = "Hello";
  if ($message == undef) {
    
  }

=head3 Undefined Value Native Level Representation

At L<native level|SPVM::Document::NativeClass>, an undefined value is equal to 0, normally a null pointer C<NULL> defined in C<stddef.h>.
  
  NULL

=head2 Multi-Numeric Number

The value of a L<multi-numeric type|/"Multi-Numeric Types"> is called multi-numeric number.

A multi-numeric number is a set of L<numbers|/"Number"> of the same type.

  my $z : Complex_2d;
  $z->{re} = 1;
  $z->{im} = 2;

See the following sections about operations for multi-numeric numbers.

=over 2

=item * L<Getting a Multi-Numeric Field|SPVM::Document::Language::Operators/"Getting a Multi-Numeric Field">

=item * L<Setting a Multi-Numeric Field|SPVM::Document::Language::Operators/"Setting a Multi-Numeric Field">

=back

=head2 Reference

The value of a L<reference type|/"Reference Types"> is called reference.

A reference has a referencing value.

A referencing value must be a L<number|/"Number"> or a L<multi-numeric number|/"Multi-Numeric Number">

The L<reference operator|SPVM::Document::Language::Operators/"Reference Operator"> C<\> creates a reference.

  my $number : int;
  my $number_ref = \$number;

See the following sections about operations for multi-numeric numbers.

=over 2

=item * L<Getting a Referenced Value|SPVM::Document::Language::Operators/"Getting a Referenced Value">

=item * L<Setting a Referenced Value|SPVM::Document::Language::Operators/"Setting a Referenced Value">

=item * L<Reference Operator|SPVM::Document::Language::Operators/"Reference Operator">

=item * L<Dereference Operator|SPVM::Document::Language::Operators/"Dereference Operator">

=item * L<Getting a Referenced Multi-Numeric Field|SPVM::Document::Language::Operators/"Getting a Referenced Multi-Numeric Field">

=item * L<Setting a Referenced Multi-Numeric Field|SPVM::Document::Language::Operators/"Setting a Referenced Multi-Numeric Field">

=back

=head3 Reference Native Level Representation

At L<native level|SPVM::Document::NativeClass>, a reference is a memory address.

  int32_t* num_ref = stack[0].iref;

=head1 Types

This section describes types.

=head2 Numeric Types

This section lists numeric types.

=head3 Integer Types

This section lists integer types.

=head4 byte Type

The C<byte> type is the type for a signed 8-bit integer.

  byte

=head4 short Type

The C<short> type is the type for a signed 16-bit integer.

  short

=head4 int Type

The C<int> type is the type for a signed 32-bit integer.

  int

=head4 long Type

The C<long> type is the type for a signed 64-bit integer.

  long

=head3 Floating Point Types

This section lists floating point types.

=head4 float Type

The C<float> type is the type for 32bit floating point.

  float

=head4 double Type

The C<double> type is the type for 64bit floating point.

  double

=head3 Numeric Types Order

L<numeric types|/"Numeric Types"> have its order.

The order is C<byte>, C<short>, C<int>, C<long>, C<float>, C<double> from smallest to largest.

=head2 Object Types

This section lists object types.

=head3 string Type

The C<string> type is the type for L<strings/"String">.

  string

The C<string> type is an object type.

C<string> type can be qualified by the L<mutable type qualifier/"mutable Type Qualifier">.

  mutable string

=head3 Class Type

The class type is the type that can create the object using a L<new operator|/"new Operator">.

  new ClassType;

=head4 Numeric Object Types

A numeric object type is the L<object type|/"Object Types"> that is corresponding to the L<numeric type|/"Numeric Types">.

The list of numeric object types:

=begin html

<table>
  <tr>
    <th>
      Numeric Object Types
    </th>
    <th>
      Corresponding Numeric Types
    </th>
  </tr>
  <tr>
    <td>
      <a href="https://metacpan.org/pod/SPVM::Byte">Byte</a>
    </td>
    <td>
      byte
    </td>
  </tr>
  <tr>
    <td>
      <a href="https://metacpan.org/pod/SPVM::Short">Short</a>
    </td>
    <td>
      short
    </td>
  </tr>
  <tr>
    <td>
      <a href="https://metacpan.org/pod/SPVM::Int">Int</a>
    </td>
    <td>
      int
    </td>
  </tr>
  <tr>
    <td>
      <a href="https://metacpan.org/pod/SPVM::Long">Long</a>
    </td>
    <td>
      long
    </td>
  </tr>
  <tr>
    <td>
      <a href="https://metacpan.org/pod/SPVM::Float">Float</a>
    </td>
    <td>
      float
    </td>
  </tr>
  <tr>
    <td>
      <a href="https://metacpan.org/pod/SPVM::Double">Double</a>
    </td>
    <td>
      double
    </td>
  </tr>
</table>

=end html

See also the L<boxing conversion|/"Boxing Conversion"> and L</"Unboxing Conversion">.

=head3 Interface Type

The interface type is a type that is defined using a C<class> keyword and a L<class attribute|/"Class Attribute"> C<interface_t>.

  class Stringable : interface_t {
    method to_string : string ();
  }

See also L</"Interface">.

Note that interface types are not L<class types|/"Class Type"> although they are defined by C<class> keyword.

=head3 Any Object Type

Any object type is represented by "object". Designed to represent the "void *" type in C.

  my $object: object;

You can methodstitute the value of "Object Types" for Any Object Type.

  my $object: object = new Foo;
  my $object: object = "abc";
  my $object: object = new Foo [3];

=head2 Basic Types

A basic type is a type whose type dimension is 0 and which can be an element of an array.

Basic types are L<numeric types|/"Numeric Types">, L<multi-numeric types|/"Multi-Numeric Types">, L<class types|/"Class Type">, the L<any object type|/"Any Object Type">, and the L<string type|/"string Type">.

=head2 undef Type

The undef type is the type of an L<undefined value|/"Undefined Value">.

=head2 void Type

B<void Type> is a special type that can only be used in the return type of the L<method definition|/"Method Definition"> and indicates the method has no return value.

  void

=head2 Array Types

The array type is the L<type|Type> for the L<array|/"Array">. The array type is composed of the L<basic type|/"Basic Types"> and the dimension such as C<[]>, C<[][]>.

  # Numeric array
  int[]
  double[]
  
  # String array
  string []
  
  # Class array
  Point[]
  
  # Any object array
  object[]
  
  # 2 dimensional array
  int[][]
  
  # 3 dimensional array
  int[][][]

The array type is an L<object type|/"Object Types">.

Compilation Errors:

The maximam value of dimesions is 255. Otherwise a compilation error occurs.

=head3 Numeric Array Type

The numeric array type is an L<array type|Array Type> for the array of the L<numeric type|/"Numeric Types">.

The list of the numeric array.

=over 2

=item * byte[]

=item * short[]

=item * int[]

=item * long[]

=item * float[]

=item * double[]

=back

Each element are initialized by the L<initial value/"Type Initial Value"> when the L<creating array|/"Creating Array"> is performed.

=head3 byte[] Type

The C<byte[]> type is an L<array type|/"Array Types"> that the element type is C<byte>.

  byte[]

=head3 Object Array Type

Object array types are the L<array type|/"Array Types"> that the type of the element is an L<object type|/"Object Types">.

Examples:

  # Object array types
  my $points : Point[];
  my $points_2dim : Point[][];
  my $stringables : Stringable[];
  my $strings : string[];
  my $objects : object[];

=head3 String Array Type

String array types are the L<array type|/"Array Types"> that the type of the element is the L<string type|/"string Type">.

Examples:

  # String array types
  my $strings : string[];

=head3 Class Array Type

Class array types are the L<array type|/"Array Types"> that the type of the element is the L<class type|/"Class Type">.

Examples:

  # Class array types
  my $points : Point[];

=head3 Interface Array Type

Interface array types are the L<array type|/"Array Types"> that the type of the element is the L<interface type|/"Interface Type">.

Examples:

  # Interface array types
  my $stringables : Stringable[];

=head3 Multi-Dimensional Array Type

The multi-dimensional array type is the L<array type|/"Array Types"> that the type of the element is an L<array type|/"Array Types">.

Examples:

  # Multi-dimensional array types
  my $numbers_2dim : Int[][];

=head3 Multi-Numeric Array Type

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

The any object array type C<object[]> is the type that any L<object array type|/"Object Array Type"> can be assigned.

  # Any object array Type
  my $array : object[] = new Point[3];
  my $array : object[] = new object[3];
  my $array : object[] = new Point[][3];

Any object array type is an L<array type|/"Array Types">.

You can get the array length using the L<array length operator|/"The array Length Operator">.

  my $array : object[] = new Int[3];
  
  # Getting the length of the element of Any Object Array Type
  my $length = @$array;

You can get and set the element using the L<get array element|/"Getting Array Element"> syntax and the L<set array element|/"Setting Array Element">.
 
  # Getting the element of any object array
  my $number = (Int)$array->[0];
  
  # Setting the element of any object array
  $array->[0] = Int->new(5);

When setting the element of any object array, the element type is checked. If the dimension of the element is not the dimension of the array - 1, an exception is thrown.

Compilation Errors:

If a invalid type is assigned, a compilation error occurs.

=head2 Multi-Numeric Types

The multi-numeric type is the type to represent a L<multi-numeric number|/"Multi-Numeric Number">.

The multi-numeric type can be used as the L<type|/"Types"> of the L<local variable declaration|/"Local Variable Declaration">.

  my $z : Complex_2d;

The value is initialized by the L<initial value/"Type Initial Value">.

The multi-numeric type can be used as an argument the L<type|/"Types"> in the L<method definition|/"Method Definition">.

The multi-numeric type can be used as the return L<type|/"Types"> of the L<method definition|/"Method Definition">.

  static method add_double_complex : Complex_2d ($z1 : Complex_2d, $z2 : Complex_2d) { ... }

The multi-numeric type can be used as a L<basic type|/"Basic Types"> of the L<array type|/"Array Types"> .

  my $points = new Complex_2d[5];

The reference can be created for the value of the multi-numeric type.

  my $z : Complex_2d;
  my $z_ref = \$z;

L<undef|/"Undefined Value"> cannot be assigned to the multi-numeric type.

=head3 Multi-Numeric Types Suffix

The list of the multi-numeric type suffix.

=begin html

<table>
  <tr>
    <th>
      Numeric Types
   </th>
    <th>
     Type Suffix
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

=head3 Multi-Numeric Types Field Access

The multi-numeric type field access is an syntax to access the field of the multi-numeric number.

  MULTI_NUMERIC_VALUE->{FIELD_NAME}

See L</"Getting Multi-Numeric Field"> to get the field of the multi-numeric number.

See L</"Setting Multi-Numeric Field"> to set the field of the multi-numeric number.

=head2 Reference Types

Reference Types is a type that can store the address of a variable. Add C<*> after a L<numeric type|/"Numeric Types"> or the L<multi-numeric type|/"Multi-Numeric Types"> You can define it.

  my $number : int;
  my $number_ref : int* = \$number;
  
  my $z : Complex_2d;
  my $z_ref : Complex_2d* = \$z;

Only the address of the Local Variable acquired by L</"Reference Operator"> can be assigned to the value of Reference Types.

Reference Types can be used as type of argument in the L<method definition|/"Method Definition">.

Reference Types cannot be used as return value type in the L<method definition|/"Method Definition">.

Reference Types cannot be used as the field type in the L<class definition|/"Class Definition">.

Reference Types cannot be used as the type of Class Variable in the L<class definition|/"Class Definition">.

See L</"Reference"> for a detailed explanation of Reference.

Compilation Errors:

If only Local Variable Declaration of Reference Types is performed, a compilation error occurs

Reference Types can be used as type of the L<local variable declaration|/"Local Variable Declaration">. The address of the Local Variable must be stored by the Reference Operator. In case of only Local Variable Declaration, a compilation error occurs

If the Reference Types is used at an Invalid location, a compilation error occurs

=head3 Numeric Reference Types

Numeric Reference Types means a L<numeric type|/"Numeric Types"> for a L<Reference Types|/"Reference Types">. Says.

=head3 Multi-Numeric Reference Types

Multi-Numeric Reference Types means a L<Reference Types|/"Reference Types"> for the L<multi-numeric type|/"Multi-Numeric Types"> variables. > Means.

=head2 Type Qualifiers

A type qualifier qualify a type.

  QUALIFIER TYPE

The I<QUALIFIER> qualified the type I<TYPE>.

=head3 mutable Type Qualifier

The C<mutable> type qualifier allows characters of a string to be changed.
  
  # The mutable type qualifier
  my $string : mutable string;

Examples:
  
  # The mutable type qualifier
  my $message = (mutable string)copy "abc";
  $message->[0] = 'd';

=head2 Type Initial Value

The list of initial values.

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
      0 (All bits are <code>0</code>)
    </td>
  </tr>
  <tr>
    <td>
      <b>double</b>
    </td>
    <td>
      0 (All bits are <code>0</code>)
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
      All fields are set to <code>0</code> (All bits are <code>0</code>)
    </td>
  </tr>
</table>

=end html

=head2 Type Width

The type width is the required length of the L<runtime stack|SPVM::Document::NativeClass/"Runtime Stack"> for the type.

If the type is a multi-numeric type, it is the length of the fields, owhterwise it is 1.

=head1 Type Conversions

Type conversion is explained.

=head2 Integer Promotional Conversion

The integer promotional conversion is a L<type conversion|"Type Conversion"> to convert an L<integer type within int|/"Integer Types within int"> to the int type using the L<numeric widening conversion|/"Numeric Widening Conversion">.

=head2 Numeric Widening Conversion

The numeric widening conversion is a L<type conversion|"Type Conversion"> from a small-order L<numeric type|/"Numeric Types"> to a large-order L<numeric type|/"Numeric Types">.

See also L<numeric types order|/"Numeric Types Order"> abount the order of numeric type.

The return value of a converion are same as the return value of the type cast of the C language.
  
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

The numeric widening conversion is performed in some of the L<type casts|/"Type Cast">, the index of the L<element access|/"The array Access">, the length of the L<creating array|/"Creating Array">, I<OPERAND> of the L<unary plus operator|/"Unary Plus Operator">, I<OPERAND> of the L<unary minus operator|/"Unary Minus Operator">, and the left and right operands of the L<shift operators|"Shift Operator">.

=head2 Numeric Narrowing Conversion

The numeric narrowing conversion is a L<conversion|"Type Conversion"> from a wide L<numeric type|/"Numeric Types"> to a narrow L<numeric type|/"Numeric Types">.

See also L<numeric types order|/"Numeric Types Order"> abount the order of numeric type.

The return value of a converion are same as the return value of the type cast of the C language.
  
  (TYPE)OPERAND

B<double to float:>

  double from = value;
  float to = (float)from;

B<double to long:>

  double from = value;
  int64_t to = (int64_t)from;

B<double to int:>

  double from = value;
  int32_t to = (int32_t)from;

B<double to short:>

  double from = value;
  int16_t to = (int16_t)from;

B<double to byte:>

  double from = value;
  int8_t to = (int8_t)from;

B<float to long:>

  float from = value;
  int64_t to = (int64_t)from;

B<float to int:>

  float from = value;
  int32_t to = (int32_t)from;

B<float to short:>

  float from = value;
  int16_t to = (int16_t)from;

B<float to byte:>

  float from = value;
  int8_t to = (int8_t)from;

B<long to int:>

  int64_t from = value;
  int32_t to = (int32_)from;

B<long to short:>

  int64_t from = value;
  int16_t to = (int16_t)from;

B<long to byte:>

  int64_t from = value;
  int8_t to = (int8_t)from;

B<int to short:>

  int32_t from = value;
  int16_t to = (int16_t)from;

B<int to byte:>

  int32_t from = value;
  int16_t to = (int16_t)from;

B<short to byte:>

  int16_t from = value;
  int8_t to = (int8_t)from;

The numeric narrowing conversion is performed in some of the L<type casts|/"Type Cast">.

=head2 Binary Numeric Conversion

The binary numeric conversion is a L<type conversion|/"Type Conversion"> to upgrade the type of I<LEFT_OPERAND> or I<RIGHT_OPERAND> of the binary operator that operands are L<numeric types|/"Numeric Types">.

The following rules apply in order.

1. If I<LEFT_OPERAND> or I<RIGHT_OPERAND> is the L<double type|/"double Type">, I<OPERAND> of the small type is converted to the big type using the L<numeric widening conversion|/"Numeric Widening Conversion">.

2. If I<LEFT_OPERAND> or I<RIGHT_OPERAND> is the L<float type|/"float Type">, I<OPERAND> of the small type is converted to the big type using the L<numeric widening conversion|/"Numeric Widening Conversion">.

3. If I<LEFT_OPERAND> or I<RIGHT_OPERAND> is the long type, I<OPERAND> of the small type is converted to the big type using the L<numeric widening conversion|/"Numeric Widening Conversion">.

4, Otherwise, both I<LEFT_OPERAND> and I<RIGHT_OPERAND> are converted to the int type using the L<numeric widening conversion|/"Numeric Widening Conversion">.

=head2 Numeric-to-String Conversion

The numeric-to-string conversion is a L<type conversion|/"Type Conversion"> from a L<numeric type|/"Numeric Types"> to the L<string type|/"string Type">.

  # The numeric-to-string conversion
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

=head2 String-to-byte Conversion

The String-to-byte conversion is a L<type conversion|/"Type Conversion"> from the L<string Type|/"string Type"> to L</"byte Type">.

  # The String-to-byte conversion
  my $string : string = "Hello";
  my $number : byte = (byte)$string;

If the string is not defined, returns 0.

If not, the string is coverted to a number by the C<strtoll> function in the C language.

The number is greater than C<INT8_MAX>, the number is set to C<INT8_MAX>.

The number is less than C<INT8_MIN>, the number is set to C<INT8_MIN>.

And returns the number.

=head2 String-to-short Conversion

The String-to-short conversion is a L<type conversion|/"Type Conversion"> from the L<string Type|/"string Type"> to L</"short Type">.

  # The String-to-short conversion
  my $string : string = "Hello";
  my $number : short = (short)$string;

If the string is not defined, returns 0.

If not, the string is coverted to a number by the C<strtoll> function in the C language.

The number is greater than C<INT16_MAX>, the number is set to C<INT16_MAX>.

The number is less than C<INT16_MIN>, the number is set to C<INT16_MIN>.

And returns the number.

=head2 String-to-int Conversion

The String-to-int conversion is a L<type conversion|/"Type Conversion"> from the L<string Type|/"string Type"> to L</"int Type">.

  # The String-to-int conversion
  my $string : string = "Hello";
  my $number : int = (int)$string;

If the string is not defined, returns 0.

If not, the string is coverted to a number by the C<strtoll> function in the C language.

The number is greater than C<INT32_MAX>, the number is set to C<INT32_MAX>.

The number is less than C<INT32_MIN>, the number is set to C<INT32_MIN>.

And returns the number.

=head2 String-to-long Conversion

The String-to-long conversion is a L<type conversion|/"Type Conversion"> from the L<string Type|/"string Type"> to L</"long Type">.

  # The String-to-long conversion
  my $string : string = "Hello";
  my $number : long = (long)$string;

If the string is not defined, returns 0.

If not, the string is coverted to a number by the C<strtoll> function in the C language.

And returns the number.

=head2 String-to-float Conversion

The String-to-float conversion is a L<type conversion|/"Type Conversion"> from the L<string Type|/"string Type"> to L</"float Type">.

  # The String-to-float conversion
  my $string : string = "Hello";
  my $float : float = (float)$string;

If the string is not defined, returns 0.

If not, the string is coverted to a number by the C<strtof> function in the C language.

And returns the number.

=head2 String-to-double Conversion

The String-to-double conversion is a L<type conversion|/"Type Conversion"> from the L<string Type|/"string Type"> to L</"double Type">.

  # The String-to-double conversion
  my $string : string = "Hello";
  my $number : double = (double)$string;

If the string is not defined, returns 0.

If not, the string is coverted to a number by the C<strtod> function in the C language.

And returns the number.

=head2 String-to-byte[] Conversion

The String-to-byte[] conversion is a L<type conversion|/"Type Conversion"> from the L<string Type|/"string Type"> to L</"byte[] Type">.

  # The String-to-byte[] conversion
  my $string : string = "Hello";
  my $bytes : byte[] = (byte[])$string;

A new byte[] object is created and all characters in the string are copied to the elements of byte[] object.

=head2 byte[]-to-string Conversion

The byte[]-to-string conversion is a L<type conversion|/"Type Conversion"> from the L<byte[] type|/"byte[] type"> to the L<string Type|/"string Type">.

  # byte[]-to-string conversion
  my $bytes : byte[] = new byte[3];
  $bytes->[0] = 'a';
  $bytes->[1] = 'b';
  $bytes->[2] = 'c';
  my $string : string = (string)$bytes;

A new string is created and all elements in the C<byte[]> object are copied to the characters of the string.

=head2 Boxing Conversion

The boxing conversion is a L<type coversion|/"Type Conversion"> to convert the value of L<numeric type|/"Numeric Types"> to the corresponding L<numeric object type|/"Numeric Object Types">.

=head2 Unboxing Conversion

The unboxing conversion is a L<type coversion|/"Type Conversion"> to convert the value of the L<numeric object type|/"Numeric Object Types"> to the value of the corresponding L<numeric type|/"Numeric Types">.

=head2 Boolean Conversion

The boolean conversion converts an operand to an int value that indicates a boolean value.

This conversion is performed on the follwoing operands.

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

The boolean conversion returns the following value corresponding to the type of the condional operand.

If the type is the int type, return the value.

If the type is the L<undef|/"undef Type">, returns 0.

If the type is the value returned by the L<TRUE method of Bool|SPVM::Bool|/"TRUE">, returns 1.

If the type is the value returned by the L<FALSE method of Bool|SPVM::Bool|/"FALSE">, returns 0.

If the type is an L<integer type within int|/"Integer Types within int">, the L<integer promotional conversion|/"Integer Promotional Conversion"> is performed on I<OPERAND>.

And the following operation in the C language is performed on I<OPERAND> .

  !!OPERAND

Compilation Errors:

The type of I<OPERAND> of the boolean conversion must be a L<numeric type|/"Numeric Types">, an L<object type|/"Object Types"> or an L<Reference Types|/"Reference Types"> or the L<undef type|/"undef Type">. Otherwise a compilation error occurs.

Examples:

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
  
  my $value = 1;
  my $ref = \$value;
  
  if ($ref) {
    # ok
  }
  
  if (undef) {
    # not ok
  }

=head1 Implicite Type Conversion

The implicite type conversion is the L<type conversion|/"Type Conversion"> performed implicitly when a value is assigned using L<assignment operator|/"Assignment Operator">, pass an argument to a method using a L<method call|/"Method Call">, or set a return value using the L<return statement|/"return Statement">.

See L<"Assignment Requirement"> if you know when implicite type conversion is performed.

Examples:
  
  # The implicite type conversion from int to double 
  my $number : double = 5;
  
  # The implicite type conversion from double to Double
  my $number_object : Double = 5.1;
  
  # The implicite type conversion from Double to double
  my $number : double = Double->new(5.1);
  
  # The implicite type conversion from int to string
  my $string : string = 4;

=head1 Assignment Requirement

The assignment requirement at compile-time is explained.

Compilation Errors:

The assignment requirement is false, a compilation error occurs.

=head2 Assignment Requirement to Numeric

Explains the assignment requirement to the L<numeric types|"Numeric Types">.

=head3 Assignment Requirement from Numeric to Numeric

If the L<nemric type order|/"Numeric Types Order"> of I<LEFT_OPERAND> is greater than or equal to the L<nemric type order|/"Numeric Types Order"> of I<RIGHT_OPERAND>, the assignment requirement is true.

If the L<nemric type order|/"Numeric Types Order"> of I<LEFT_OPERAND> is greater than the L<nemric type order|/"Numeric Types Order"> of I<RIGHT_OPERAND>, the L<numeric widening conversion|/"Numeric Widening Conversion"> is performed.

=begin html

<table>
  <tr><th>Assignment Requirement</th><th>To</th><th>From</th><th><a href="#Implicite-Type-Conversion">Implicite Type Conversion</a></th></tr>
  <tr><td>True</td><td>byte</td><td>byte</td><td>None</td></tr>
  <tr><td>True</td><td>short</td><td>short</td><td>None</td></tr>
  <tr><td>True</td><td>int</td><td>int</td><td>None</td></tr>
  <tr><td>True</td><td>long</td><td>long</td><td>None</td></tr>
  <tr><td>True</td><td>float</td><td>float</td><td>None</td></tr>
  <tr><td>True</td><td>double</td><td>double</td><td>None</td></tr>
  <tr><td>True</td><td>short</td><td>byte</td><td><a href="#Numeric-Widening-Conversion">Numeric Widening Conversion</a></td></tr>
  <tr><td>True</td><td>int</td><td>byte</td><td><a href="#Numeric-Widening-Conversion">Numeric Widening Conversion</a></td></tr>
  <tr><td>True</td><td>long</td><td>byte</td><td><a href="#Numeric-Widening-Conversion">Numeric Widening Conversion</a></td></tr>
  <tr><td>True</td><td>float</td><td>byte</td><td><a href="#Numeric-Widening-Conversion">Numeric Widening Conversion</a></td></tr>
  <tr><td>True</td><td>double</td><td>byte</td><td><a href="#Numeric-Widening-Conversion">Numeric Widening Conversion</a></td></tr>
  <tr><td>True</td><td>int</td><td>short</td><td><a href="#Numeric-Widening-Conversion">Numeric Widening Conversion</a></td></tr>
  <tr><td>True</td><td>long</td><td>short</td><td><a href="#Numeric-Widening-Conversion">Numeric Widening Conversion</a></td></tr>
  <tr><td>True</td><td>float</td><td>short</td><td><a href="#Numeric-Widening-Conversion">Numeric Widening Conversion</a></td></tr>
  <tr><td>True</td><td>double</td><td>short</td><td><a href="#Numeric-Widening-Conversion">Numeric Widening Conversion</a></td></tr>
  <tr><td>True</td><td>long</td><td>int</td><td><a href="#Numeric-Widening-Conversion">Numeric Widening Conversion</a></td></tr>
  <tr><td>True</td><td>float</td><td>int</td><td><a href="#Numeric-Widening-Conversion">Numeric Widening Conversion</a></td></tr>
  <tr><td>True</td><td>double</td><td>int</td><td><a href="#Numeric-Widening-Conversion">Numeric Widening Conversion</a></td></tr>
  <tr><td>True</td><td>float</td><td>long</td><td><a href="#Numeric-Widening-Conversion">Numeric Widening Conversion</a></td></tr>
  <tr><td>True</td><td>double</td><td>long</td><td><a href="#Numeric-Widening-Conversion">Numeric Widening Conversion</a></td></tr>
  <tr><td>True</td><td>double</td><td>float</td><td><a href="#Numeric-Widening-Conversion">Numeric Widening Conversion</a></td></tr>
</table>

=end html

Examples:
  
  # int to int
  my $number : int = 3;
  
  # byte to int
  my $number : int = (byte)5;
  
  # double to double
  my $number : double = 4.5;
  
  # float to double
  my $number : double = 4.5f;

If the L<nemric type order|/"Numeric Types Order"> of I<LEFT_OPERAND> is less than the L<nemric type order|/"Numeric Types Order"> of I<RIGHT_OPERAND>, the assignment requirement is conditional true.

The condition is that I<RIGHT_OPERAND> is a L<interger literal|Integer Literal> and the value is between the max and minimal value of the type of I<LEFT_OPERAND>.

If the condition is ture, the L<numeric narrowing conversion|/"Numeric Narrowing Conversion"> is performed.

=begin html

<table>
  <tr><th>Assignment Requirement</th><th>To</th><th>From</th><th><a href="#Implicite-Type-Conversion">Implicite Type Conversion</a></th></tr>
  <tr><td>Conditional True</td><td>byte</td><td>short</td><td><a href="#Numeric-Narrowing-Conversion">Numeric Narrowing Conversion</a></td></tr>
  <tr><td>Conditional True</td><td>byte</td><td>int</td><td><a href="#Numeric-Narrowing-Conversion">Numeric Narrowing Conversion</a></td></tr>
  <tr><td>Conditional True</td><td>byte</td><td>long</td><td><a href="#Numeric-Narrowing-Conversion">Numeric Narrowing Conversion</a></td></tr>
  <tr><td>False</td><td>byte</td><td>float</td><td>None</td></tr>
  <tr><td>False</td><td>byte</td><td>double</td><td>None</td></tr>
  <tr><td>Conditional True</td><td>short</td><td>int</td><td><a href="#Numeric-Narrowing-Conversion">Numeric Narrowing Conversion</a></td></tr>
  <tr><td>Conditional True</td><td>short</td><td>long</td><td><a href="#Numeric-Narrowing-Conversion">Numeric Narrowing Conversion</a></td></tr>
  <tr><td>False</td><td>short</td><td>float</td><td>None</td></tr>
  <tr><td>False</td><td>short</td><td>double</td><td>None</td></tr>
  <tr><td>Conditional True</td><td>int</td><td>long</td><td><a href="#Numeric-Narrowing-Conversion">Numeric Narrowing Conversion</a></td></tr>
  <tr><td>False</td><td>int</td><td>float</td><td>None</td></tr>
  <tr><td>False</td><td>int</td><td>double</td><td>None</td></tr>
  <tr><td>False</td><td>long</td><td>float</td><td>None</td></tr>
  <tr><td>False</td><td>long</td><td>double</td><td>None</td></tr>
  <tr><td>False</td><td>float</td><td>double</td><td>None</td></tr>
</table>

=end html

Examples:
  
  # int to byte
  my $number : byte = 127;

=head3 Assignment Requirement from NumericObject to Numeric

If the type of I<LEFT_OPERAND> is a L<numeric type|/"Numeric Types"> corresponding to the numeric object type of I<RIGHT_OPERAND> and the type of I<RIGHT_OPERAND> is a L<numeric object type|/"Numeric Object Types">, the assignment requirement is true.

=begin html

<table>
  <tr><th>Assignment Requirement</th><th>To</th><th>From</th><th><a href="#Implicite-Type-Conversion">Implicite Type Conversion</a></th></tr>
  <tr><td>True</td><td>byte</td><td>Byte</td><td><a href="#Unboxing-Conversion">Unboxing Conversion</td></a></tr>
  <tr><td>True</td><td>short</td><td>Short</td><td><a href="#Unboxing-Conversion">Unboxing Conversion</td></a></tr>
  <tr><td>True</td><td>int</td><td>Int</td><td><a href="#Unboxing-Conversion">Unboxing Conversion</td></a></tr>
  <tr><td>True</td><td>long</td><td>Long</td><td><a href="#Unboxing-Conversion">Unboxing Conversion</td></a></tr>
  <tr><td>True</td><td>float</td><td>Float</td><td><a href="#Unboxing-Conversion">Unboxing Conversion</td></a></tr>
  <tr><td>True</td><td>double</td><td>Double</td><td><a href="#Unboxing-Conversion">Unboxing Conversion</td></a></tr>
</table>

=end html

Examples:

  my $int : int = Int->new(3);

  my $double : double = Double->new(3.5);

=head3 Assignment Requirement from Any Object to Numeric

If the type of I<LEFT_OPERAND> is a L<numeric type|/"Numeric Types"> and the type of I<RIGHT_OPERAND> is a L<any object type|/"Any Object Type"> C<object>, the assignment requirement is true.

The L<unboxing conversion|/"Unboxing Conversion"> corresponding to the numeric type is performed.

=begin html

<table>
  <tr><th>Assignment Requirement</th><th>To</th><th>From</th><th><a href="#Implicite-Type-Conversion">Implicite Type Conversion</a></th></tr>
  <tr><td>True</td><td>NUMERIC_X</td><td>object</td><td><a href="#Unboxing-Conversion">Unboxing Conversion</td></a></tr>
</table>

=end html

Examples:

  my $int : int = (object)Int->new(3);

  my $double : double = (object)Double->new(3.5);

=head3 Assignment Requirement from Others to Numeric

If the type of I<LEFT_OPERAND> is a L<numeric type|/"Numeric Types"> and the type of I<RIGHT_OPERAND> is other than the types described above, the assignment requirement is false.

=head2 Assignment Requirement to Multi-Numeric

If the type of I<LEFT_OPERAND> is a L<multi-numeric type|/"Multi-Numeric Types"> and the type of I<RIGHT_OPERAND> is the same type of I<LEFT_OPERAND>, the assignment requirement is true.

Otherwise, the assignment requirement is false.

=begin html

<table>
  <tr><th>Assignment Requirement</th><th>To</th><th>From</th><th><a href="#Implicite-Type-Conversion">Implicite Type Conversion</a></th></tr>
  <tr><td>True</td><td>MULNUM_X</td><td>MULNUM_X</td><td>None</td></tr>
  <tr><td>False</td><td>MULNUM_X</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

Examples:

  my $z1 : Complex_2d;
  my $z2 : Complex_2d = $z1;

=head2 Assignment Requirement to Referenece

If the type of I<LEFT_OPERAND> is a L<Reference Types|/"Reference Types"> and the type of I<RIGHT_OPERAND> is the same type of I<LEFT_OPERAND>, the assignment requirement is true.

Otherwise, the assignment requirement is false.

=begin html

<table>
  <tr><th>Assignment Requirement</th><th>To</th><th>From</th><th><a href="#Implicite-Type-Conversion">Implicite Type Conversion</a></th></tr>
  <tr><td>True</td><td>REF_X</td><td>REF_X</td><td>None</td></tr>
  <tr><td>False</td><td>REF_X</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

Examples:

  my $number : int = 5;
  my $number_ref : int* = \num;

=head2 Assignment Requirement to String

If the type of I<LEFT_OPERAND> is the L<string type|/"string Type"> without the L<mutable type qualifier|/"mutable Type Qualifier"> and the type of I<RIGHT_OPERAND> is the L<string type|/"string Type">, the assignment requirement is true.

If the type of I<LEFT_OPERAND> is the L<string type|/"string Type"> with the L<mutable type qualifier|/"mutable Type Qualifier"> and the type of I<RIGHT_OPERAND> is the L<string type|/"string Type"> with the L<mutable type qualifier|/"mutable Type Qualifier">, the assignment requirement is true.

If the type of I<LEFT_OPERAND> is the L<string type|/"string Type"> with the L<mutable type qualifier|/"mutable Type Qualifier"> and the type of I<RIGHT_OPERAND> is the L<string type|/"string Type"> without the L<mutable type qualifier|/"mutable Type Qualifier">, the assignment requirement is false.

If the type of I<LEFT_OPERAND> is the L<string type|/"string Type"> and the type of I<RIGHT_OPERAND> is a L<numeric type|/"Numeric Types"> or the L<undef type|/"undef Type">, the assignment requirement is true.

If the type of I<RIGHT_OPERAND> is a L<numeric type|/"Numeric Types">, the L<numeric-to-string conversion|/"Numeric-to-String Conversion"> is performed.

=begin html

<table>
  <tr><th>Assignment Requirement</th><th>To</th><th>From</th><th><a href="#Implicite-Type-Conversion">Implicite Type Conversion</a></th></tr>
  <tr><td>True</td><td>string</td><td>string</td><td>None</td></tr>
  <tr><td>True</td><td>string</td><td>mutable string</td><td>None</td></tr>
  <tr><td>True</td><td>mutable string</td><td>mutable string</td><td>None</td></tr>
  <tr><td>False</td><td>mutable string</td><td>string</td><td>None</td></tr>
  <tr><td>True</td><td>string</td><td>string</td><td>None</td></tr>
  <tr><td>True</td><td>string</td><td>NUMERIC_X</td><td>numeric-to-string conversion</td></tr>
  <tr><td>True</td><td>string</td><td>undef</td><td>None</td></tr>
  <tr><td>False</td><td>string</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

Examples:

  my $string : string = "abc";
  my $number_string : string = 3;
  my $string : string = undef;

=head2 Assignment Requirement to NumericObject

If the type of I<LEFT_OPERAND> is a L<numeric object type|/"Numeric Object Types"> and the type of I<RIGHT_OPERAND> is the same type of I<LEFT_OPERAND>, a L<numeric type|/"Numeric Types"> that is corresponding to the numeric object type, or the L<undef type|/"undef Type">, the assignment requirement is true.

Otherwise, the assignment requirement is false.

If the type of I<RIGHT_OPERAND> is a L<numeric type|/"Numeric Types">, the L<boxing conversion|/"Boxing Conversion"> is performed.

=begin html

<table>
  <tr><th>Assignment Requirement</th><th>To</th><th>From</th><th><a href="#Implicite-Type-Conversion">Implicite Type Conversion</a></th></tr>
  <tr><td>True</td><td>NUMERIC_OBJECT_X</td><td>NUMERIC_OBJECT_X</td><td>None</td></tr>
  <tr><td>True</td><td>NUMERIC_OBJECT_X</td><td>NUMERIC_X</td><td><a href="#Boxing-Conversion">Boxing Conversion</td></a></tr>
  <tr><td>True</td><td>NUMERIC_OBJECT</td><td>undef</td><td>None</td></tr>
  <tr><td>False</td><td>NUMERIC_OBJECT</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

Examples:

  my $number_object : Int = Int->new(3);
  my $number_object : Int = 3;
  my $number_object : Int = undef;

=head2 Assignment Requirement to Class

If the type of I<LEFT_OPERAND> is a L<class type|/"Class Type"> and the type of I<RIGHT_OPERAND> is the same type, or the L<undef type|/"undef Type">, the assignment requirement is true.

If the type of I<LEFT_OPERAND> is a super class of the type of I<RIGHT_OPERAND>, the assignment requirement is true.

Otherwise, the assignment requirement is false.

=begin html

<table>
  <tr><th>Assignment Requirement</th><th>To</th><th>From</th><th><a href="#Implicite-Type-Conversion">Implicite Type Conversion</a></th></tr>
  <tr><td>True</td><td>CLASS_X</td><td>CLASS_X</td><td>None</td></tr>
  <tr><td>True</td><td>CLASS</td><td>undef</td><td>None</td></tr>
  <tr><td>True</td><td>SUPER_CLASS_X</td><td>CLASS_Y</td><td>None</td></tr>
  <tr><td>False</td><td>CLASS</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

Examples:

  my $point : Point = Point->new;
  my $point : Point = undef;

=head2 Assignment Requirement to Interface

If the type of I<LEFT_OPERAND> is an L<interface type|/"Interface Type"> and the type of I<RIGHT_OPERAND> is the same type, or the L<undef type|/"undef Type">, the assignment requirement is true.

If the type of I<LEFT_OPERAND> is an L<interface type|/"Interface Type"> and the type of I<RIGHT_OPERAND> is a L<class type|/"Class Type"> and the class has the same interface of I<LEFT_OPERAND>, the assignment requirement is true.

Otherwise, the assignment requirement is false.

=begin html

<table>
  <tr><th>Assignment Requirement</th><th>To</th><th>From</th><th><a href="#Implicite-Type-Conversion">Implicite Type Conversion</a></th></tr>
  <tr><td>True</td><td>INTERFACE_X</td><td>INTERFACE_X</td><td>None</td></tr>
  <tr><td>True</td><td>INTERFACE_X</td><td>INTERFACE_HAVING_Y</td><td>None</td></tr>
  <tr><td>True</td><td>INTERFACE</td><td>undef</td><td>None</td></tr>
  <tr><td>False</td><td>INTERFACE</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

Examples:
  
  # Point has Stringable interface
  my $stringable : Stringable = Point->new(1, 2);
  my $stringable : Stringable = undef;

=head2 Assignment Requirement to Any Object

If the type of I<LEFT_OPERAND> is the L<any object type|/"Any Object Type"> and the type of I<RIGHT_OPERAND> is an L<object type|/"Object Types">, a L<numeric type|/"Numeric Types"> or the L<undef type|/"undef Type">, the assignment requirement is true.

Otherwise, the assignment requirement is false.

If the type of I<RIGHT_OPERAND> is a L<numeric type|/"Numeric Types">, the L<boxing conversion|/"Boxing Conversion"> is performed.

=begin html

<table>
  <tr><th>Assignment Requirement</th><th>To</th><th>From</th><th><a href="#Implicite-Type-Conversion">Implicite Type Conversion</a></th></tr>
  <tr><td>True</td><td>object</td><td>OBJECT_Y</td><td>None</td></tr>
  <tr><td>True</td><td>object</td><td>NUMERIC_X</td><td><a href="#Boxing-Conversion">Boxing Conversion</td></a></tr>
  <tr><td>True</td><td>object</td><td>undef</td><td>None</td></tr>
  <tr><td>False</td><td>object</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

Examples:

  my $object : object = Point->new;
  my $number_object : object = 3;
  my $object : object = undef;

=head2 Assignment Requirement to Undefined

If the type of I<LEFT_OPERAND> is the L<undef type|/"undef Type">, the assignment requirement is false.

=begin html

<table>
  <tr><th>Assignment Requirement</th><th>To</th><th>From</th><th><a href="#Implicite-Type-Conversion">Implicite Type Conversion</a></th></tr>
  <tr><td>False</td><td>undef Type</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

Examples:

  # The assignment requirement is false
  undef = Point->new;

=head2 Assignment Requirement to Numeric Array

If the type of I<LEFT_OPERAND> is a L<numeric array type|/"Numeric Array Type"> and the type of I<RIGHT_OPERAND> is the same type of I<LEFT_OPERAND> or the L<undef type|/"undef Type">, the assignment requirement is true.

Otherwise, the assignment requirement is false.

=begin html

<table>
  <tr><th>Assignment Requirement</th><th>To</th><th>From</th><th><a href="#Implicite-Type-Conversion">Implicite Type Conversion</a></th></tr>
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

Examples:

  my $numbers : int[] = new int[3];
  my $numbers : int[] = undef;

=head2 Assignment Requirement to Multi-Numeric Array

If the type of I<LEFT_OPERAND> is a L<multi-numeric array type|/"Multi-Numeric Array Type"> and the type of I<RIGHT_OPERAND> is the same type of I<LEFT_OPERAND> or the L<undef type|/"undef Type">, the assignment requirement is true.

Otherwise, the assignment requirement is false.

=begin html

<table>
  <tr><th>Assignment Requirement</th><th>To</th><th>From</th><th><a href="#Implicite-Type-Conversion">Implicite Type Conversion</a></th></tr>
  <tr><td>True</td><td>MULNUM_X[]</td><td>MULNUM_X[]</td><td>None</td></tr>
  <tr><td>True</td><td>MULNUM_X[]</td><td>undef</td><td>None</td></tr>
  <tr><td>False</td><td>MULNUM_X[]</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

Examples:

  my $numbers : Complex_2d[] = new Complex_2d[3];
  my $numbers : Complex_2d[] = undef;

=head2 Assignment Requirement to String Array

If the type of I<LEFT_OPERAND> is a L<string array type|/"String Array Type"> and the type of I<RIGHT_OPERAND> is the same type of I<LEFT_OPERAND> or the L<undef type|/"undef Type">, the assignment requirement is true.

Otherwise, the assignment requirement is false.

=begin html

<table>
  <tr><th>Assignment Requirement</th><th>To</th><th>From</th><th><a href="#Implicite-Type-Conversion">Implicite Type Conversion</a></th></tr>
  <tr><td>True</td><td>string[]</td><td>string[]</td><td>None</td></tr>
  <tr><td>True</td><td>string[]</td><td>undef</td><td>None</td></tr>
  <tr><td>False</td><td>string[]</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

Examples:

  my $strings : string[] = ["abc", "def"];
  my $strings : string[] = undef;

=head2 Assignment Requirement to Class Array

If the type of I<LEFT_OPERAND> is a L<class array type|/"Class Array Type"> and the type of I<RIGHT_OPERAND> is the same type of I<LEFT_OPERAND> or the L<undef type|/"undef Type">, the assignment requirement is true.

If the L<basic type|/"Basic Types"> of I<LEFT_OPERAND> is an super class of the type of I<RIGHT_OPERAND>, the assignment requirement is true.

Otherwise, the assignment requirement is false.

=begin html

<table>
  <tr><th>Assignment Requirement</th><th>To</th><th>From</th><th><a href="#Implicite-Type-Conversion">Implicite Type Conversion</a></th></tr>
  <tr><td>True</td><td>CLASS_X[]</td><td>CLASS_X[]</td><td>None</td></tr>
  <tr><td>True</td><td>SUPER_CLASS_X[]</td><td>CLASS_Y[]</td><td>None</td></tr>
  <tr><td>True</td><td>CLASS_X[]</td><td>undef</td><td>None</td></tr>
  <tr><td>False</td><td>CLASS_X[]</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

Examples:

  my $points : Point[] = new Point[3];
  my $points : Point[] = undef;

=head2 Assignment Requirement to Interface Array

If the type of I<LEFT_OPERAND> is an L<interface array type|/"Interface Array Type"> and the type of I<RIGHT_OPERAND> is the same type of I<LEFT_OPERAND> or the L<undef type|/"undef Type">, the assignment requirement is true.

If the type of I<LEFT_OPERAND> is an L<interface array type|/"Interface Array Type"> and the type of I<RIGHT_OPERAND> is a L<class array type|/"Class Array Type"> and its L<basic type|/"Basic Types"> can assign to the basic type of I<LEFT_OPERAND>, the assignment requirement is true.

Otherwise, the assignment requirement is false.

=begin html

<table>
  <tr><th>Assignment Requirement</th><th>To</th><th>From</th><th><a href="#Implicite-Type-Conversion">Implicite Type Conversion</a></th></tr>
  <tr><td>True</td><td>INTERFACE_X[]</td><td>INTERFACE_X[]</td><td>None</td></tr>
  <tr><td>True</td><td>INTERFACE_X[]</td><td>undef</td><td>None</td></tr>
  <tr><td>True</td><td>INTERFACE_X[]</td><td>INTERFACE_HAVING_Y[]</td><td>None</td></tr>
  <tr><td>False</td><td>INTERFACE_X[]</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

Examples:

  my $stringables : Stringable[] = new Stringable[3];

  my $stringables : Stringable[] = new Point[3];
  
  my $stringables : Stringable[] = undef;

=head2 Assignment Requirement to Any Object Array

If the type of I<LEFT_OPERAND> is the L<any object array type|/"Any Object Array Type"> C<object[]> and the type of I<RIGHT_OPERAND> is an L<object array type|/"Object Array Type"> or the L<undef type|/"undef Type">, the assignment requirement is true.

Otherwise, the assignment requirement is false.

=begin html

<table>
  <tr><th>Assignment Requirement</th><th>To</th><th>From</th><th><a href="#Implicite-Type-Conversion">Implicite Type Conversion</a></th></tr>
  <tr><td>True</td><td>object[]</td><td>OBJECT_ARRAY_Y</td><td>None</td></tr>
  <tr><td>True</td><td>object[]</td><td>undef</td><td>None</td></tr>
  <tr><td>False</td><td>object[]</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

Examples:

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

=head2 Assignment Requirement to Multi-Dimensional Array

If the type of I<LEFT_OPERAND> is a L<multi-dimensional array type|/"Multi-Dimensional Array Type"> and the type of I<RIGHT_OPERAND> is the same type of I<LEFT_OPERAND> or the L<undef type|/"undef Type">, the assignment requirement is true.

If the type dimesion of I<LEFT_OPERAND> is equal to the type dimension of I<RIGHT_OPERAND>, and the L<basic type|/"Basic Types"> of I<LEFT_OPERAND> is a super class of the L<basic type|/"Basic Types"> of I<RIGHT_OPERAND>, the assignment requirement is true.

If the type dimesion of I<LEFT_OPERAND> is equal to the type dimension of I<RIGHT_OPERAND>, and the L<basic type|/"Basic Types"> of I<RIGHT_OPERAND> has the L<basic type|/"Basic Types"> of I<LEFT_OPERAND>, the assignment requirement is true.

Otherwise, the assignment requirement is false.

=begin html

<table>
  <tr><th>Assignment Requirement</th><th>To</th><th>From</th><th><a href="#Implicite-Type-Conversion">Implicite Type Conversion</a></th></tr>
  <tr><td>True</td><td>X[]..</td><td>X[]..</td><td>None</td></tr>
  <tr><td>True</td><td>object[]</td><td>undef</td><td>None</td></tr>
  <tr><td>True</td><td>SUPER_CLASS_X[]..</td><td>CLASS_Y[]..</td><td>None</td></tr>
  <tr><td>True</td><td>INTERFACE_X[]..</td><td>INTERFACE_HAVING_Y[]..</td><td>None</td></tr>
  <tr><td>False</td><td>object[]</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

(C<[]..> means one or more C<[]>)

Examples:

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

=head1 Cast Requirement

The cast requirement at compile-time is explained.

Compilation Errors:

The cast requirement is false, a compilation error occurs.

=head2 Cast Requirement to Numeric

The cast requirement to the L<numeric types|/"Numeric Types"> is explained.

=head3 Cast Requirement from Numeric to Numeric

If the type of I<LEFT_OPERAND> is a L<numeric type|/"Numeric Types"> and the type of I<RIGHT_OPERAND> is a L<numeric type|/"Numeric Types">, the cast requirement is true.

If the L<nemric type order|/"Numeric Types Order"> of I<LEFT_OPERAND> is greater than the L<nemric type order|/"Numeric Types Order"> of I<RIGHT_OPERAND>, the L<numeric widening conversion|/"Numeric Widening Conversion"> is performed.

If the L<nemric type order|/"Numeric Types Order"> of I<LEFT_OPERAND> is less than the L<nemric type order|/"Numeric Types Order"> of I<RIGHT_OPERAND>, the L<numeric narrowing conversion|/"Numeric Narrowing Conversion"> is performed.

If the L<nemric type order|/"Numeric Types Order"> of I<LEFT_OPERAND> is equal to the L<nemric type order|/"Numeric Types Order"> of I<RIGHT_OPERAND>, copying is performed.

=begin html

<table>
  <tr><th>Cast Requirement</th><th>To</th><th>From</th><th><a href="#Type-Conversion">Conversion or Type Checking</a></th></tr>
  <tr><td>True</td><td>byte</td><td>byte</td><td>None</td></tr>
  <tr><td>True</td><td>short</td><td>short</td><td>None</td></tr>
  <tr><td>True</td><td>int</td><td>int</td><td>None</td></tr>
  <tr><td>True</td><td>long</td><td>long</td><td>None</td></tr>
  <tr><td>True</td><td>float</td><td>float</td><td>None</td></tr>
  <tr><td>True</td><td>double</td><td>double</td><td>None</td></tr>
  <tr><td>True</td><td>short</td><td>byte</td><td><a href="#Numeric-Widening-Conversion">Numeric Widening Conversion</a></td></tr>
  <tr><td>True</td><td>int</td><td>byte</td><td><a href="#Numeric-Widening-Conversion">Numeric Widening Conversion</a></td></tr>
  <tr><td>True</td><td>long</td><td>byte</td><td><a href="#Numeric-Widening-Conversion">Numeric Widening Conversion</a></td></tr>
  <tr><td>True</td><td>float</td><td>byte</td><td><a href="#Numeric-Widening-Conversion">Numeric Widening Conversion</a></td></tr>
  <tr><td>True</td><td>double</td><td>byte</td><td><a href="#Numeric-Widening-Conversion">Numeric Widening Conversion</a></td></tr>
  <tr><td>True</td><td>int</td><td>short</td><td><a href="#Numeric-Widening-Conversion">Numeric Widening Conversion</a></td></tr>
  <tr><td>True</td><td>long</td><td>short</td><td><a href="#Numeric-Widening-Conversion">Numeric Widening Conversion</a></td></tr>
  <tr><td>True</td><td>float</td><td>short</td><td><a href="#Numeric-Widening-Conversion">Numeric Widening Conversion</a></td></tr>
  <tr><td>True</td><td>double</td><td>short</td><td><a href="#Numeric-Widening-Conversion">Numeric Widening Conversion</a></td></tr>
  <tr><td>True</td><td>long</td><td>int</td><td><a href="#Numeric-Widening-Conversion">Numeric Widening Conversion</a></td></tr>
  <tr><td>True</td><td>float</td><td>int</td><td><a href="#Numeric-Widening-Conversion">Numeric Widening Conversion</a></td></tr>
  <tr><td>True</td><td>double</td><td>int</td><td><a href="#Numeric-Widening-Conversion">Numeric Widening Conversion</a></td></tr>
  <tr><td>True</td><td>float</td><td>long</td><td><a href="#Numeric-Widening-Conversion">Numeric Widening Conversion</a></td></tr>
  <tr><td>True</td><td>double</td><td>long</td><td><a href="#Numeric-Widening-Conversion">Numeric Widening Conversion</a></td></tr>
  <tr><td>True</td><td>double</td><td>float</td><td><a href="#Numeric-Widening-Conversion">Numeric Widening Conversion</a></td></tr>
  <tr><td>True</td><td>byte</td><td>short</td><td><a href="#Numeric-Narrowing-Conversion">Numeric Narrowing Conversion</a></td></tr>
  <tr><td>True</td><td>byte</td><td>int</td><td><a href="#Numeric-Narrowing-Conversion">Numeric Narrowing Conversion</a></td></tr>
  <tr><td>True</td><td>byte</td><td>long</td><td><a href="#Numeric-Narrowing-Conversion">Numeric Narrowing Conversion</a></td></tr>
  <tr><td>True</td><td>byte</td><td>float</td><td><a href="#Numeric-Narrowing-Conversion">Numeric Narrowing Conversion</a></td></tr>
  <tr><td>True</td><td>byte</td><td>double</td><td><a href="#Numeric-Narrowing-Conversion">Numeric Narrowing Conversion</a></td></tr>
  <tr><td>True</td><td>short</td><td>int</td><td><a href="#Numeric-Narrowing-Conversion">Numeric Narrowing Conversion</a></td></tr>
  <tr><td>True</td><td>short</td><td>long</td><td><a href="#Numeric-Narrowing-Conversion">Numeric Narrowing Conversion</a></td></tr>
  <tr><td>True</td><td>short</td><td>float</td><td><a href="#Numeric-Narrowing-Conversion">Numeric Narrowing Conversion</a></td></tr>
  <tr><td>True</td><td>short</td><td>double</td><td><a href="#Numeric-Narrowing-Conversion">Numeric Narrowing Conversion</a></td></tr>
  <tr><td>True</td><td>int</td><td>long</td><td><a href="#Numeric-Narrowing-Conversion">Numeric Narrowing Conversion</a></td></tr>
  <tr><td>True</td><td>int</td><td>float</td><td><a href="#Numeric-Narrowing-Conversion">Numeric Narrowing Conversion</a></td></tr>
  <tr><td>True</td><td>int</td><td>double</td><td><a href="#Numeric-Narrowing-Conversion">Numeric Narrowing Conversion</a></td></tr>
  <tr><td>True</td><td>long</td><td>float</td><td><a href="#Numeric-Narrowing-Conversion">Numeric Narrowing Conversion</a></td></tr>
  <tr><td>True</td><td>long</td><td>double</td><td><a href="#Numeric-Narrowing-Conversion">Numeric Narrowing Conversion</a></td></tr>
  <tr><td>True</td><td>float</td><td>double</td><td><a href="#Numeric-Narrowing-Conversion">Numeric Narrowing Conversion</a></td></tr>
</table>

=end html

Examples:
  
  # int to int
  my $number = (int)3;
  
  # byte to int
  my $number_byte : byte = 5;
  my $number = (int)5;
  
  # double to double
  my $number = (double)4.5;
  
  # float to double
  my $number = (double)4.5f;
  
  # int to byte
  my $number = (byte)127;

  # double to int
  my $number = (int)2.5;

=head3 Cast Requirement from NumericObject to Numeric

If the type of I<LEFT_OPERAND> is a L<numeric type|/"Numeric Types"> corresponding to the numeric object type of I<RIGHT_OPERAND> and the type of I<RIGHT_OPERAND> is a L<numeric object type|/"Numeric Object Types">, the cast requirement is true.

=begin html

<table>
  <tr><th>Cast Requirement</th><th>To</th><th>From</th><th><a href="#Type-Conversion">Conversion or Type Checking</a></th></tr>
  <tr><td>True</td><td>byte</td><td>Byte</td><td><a href="#Unboxing-Conversion">Unboxing Conversion</td></a></tr>
  <tr><td>True</td><td>short</td><td>Short</td><td><a href="#Unboxing-Conversion">Unboxing Conversion</td></a></tr>
  <tr><td>True</td><td>int</td><td>Int</td><td><a href="#Unboxing-Conversion">Unboxing Conversion</td></a></tr>
  <tr><td>True</td><td>long</td><td>Long</td><td><a href="#Unboxing-Conversion">Unboxing Conversion</td></a></tr>
  <tr><td>True</td><td>float</td><td>Float</td><td><a href="#Unboxing-Conversion">Unboxing Conversion</td></a></tr>
  <tr><td>True</td><td>double</td><td>Double</td><td><a href="#Unboxing-Conversion">Unboxing Conversion</td></a></tr>
</table>

=end html

Examples:

  my $int = (int)Int->new(3);

  my $double = (double)Double->new(3.5);

=head3 Cast Requirement from Any Object to Numeric

If the type of I<LEFT_OPERAND> is a L<numeric type|/"Numeric Types"> and the type of I<RIGHT_OPERAND> is a L<any object type|/"Any Object Type"> C<object>, the cast requirement is true.

The L<unboxing conversion|/"Unboxing Conversion"> corresponding to the numeric type is performed.

=begin html

<table>
  <tr><th>Cast Requirement</th><th>To</th><th>From</th><th><a href="#Type-Conversion">Conversion or Type Checking</a></th></tr>
  <tr><td>True</td><td>NUMERIC_X</td><td>object</td><td><a href="#Unboxing-Conversion">Unboxing Conversion</td></a></tr>
</table>

=end html

Examples:
  
  my $object : object = Int->new(3);
  my $int = (int)$object;
  
  my $object : object = Double->new(3.5);
  my $double = (double)$object;

=head3 Cast Requirement from Others to Numeric

If the type of I<LEFT_OPERAND> is a L<numeric type|/"Numeric Types"> and the type of I<RIGHT_OPERAND> is other than the types described above, the cast requirement is false.

=head2 Cast Requirement to Multi-Numeric

If the type of I<LEFT_OPERAND> is a L<multi-numeric type|/"Multi-Numeric Types"> and the type of I<RIGHT_OPERAND> is the same type of I<LEFT_OPERAND>, the cast requirement is true.

Otherwise, the cast requirement is false.

=begin html

<table>
  <tr><th>Cast Requirement</th><th>To</th><th>From</th><th><a href="#Type-Conversion">Conversion or Type Checking</a></th></tr>
  <tr><td>True</td><td>MULNUM_X</td><td>MULNUM_X</td><td>None</td></tr>
  <tr><td>False</td><td>MULNUM_X</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

Examples:

  my $z1 : Complex_2d;
  my $z2 = (Complex_2d)$z1;

=head2 Cast Requirement to Referenece

If the type of I<LEFT_OPERAND> is a L<Reference Types|/"Reference Types"> and the type of I<RIGHT_OPERAND> is the same type of I<LEFT_OPERAND>, the cast requirement is true.

Otherwise, the cast requirement is false.

=begin html

<table>
  <tr><th>Cast Requirement</th><th>To</th><th>From</th><th><a href="#Type-Conversion">Conversion or Type Checking</a></th></tr>
  <tr><td>True</td><td>REF_X</td><td>REF_X</td><td>None</td></tr>
  <tr><td>False</td><td>REF_X</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

Examples:

  my $number : int = 5;
  my $number_ref = (int*)\num;

=head2 Cast Requirement to String

If the type of I<LEFT_OPERAND> is the L<string type|/"string Type"> and the type of I<RIGHT_OPERAND> is the L<string type|/"string Type">, the cast requirement is true.

If the type of I<LEFT_OPERAND> is the L<string type|/"string Type"> with the L<mutable type qualifier|/"mutable Type Qualifier"> and the type of I<RIGHT_OPERAND> is the L<string type|/"string Type"> without the L<mutable type qualifier|/"mutable Type Qualifier">, the L<assignment requirement|/"Assignment Requirement"> without implicite type conversion is performed.

If the type of I<RIGHT_OPERAND> is a L<numeric type|/"Numeric Types">, the L<numeric-to-string conversion|/"Numeric-to-String Conversion"> is performed.

If the type of I<LEFT_OPERAND> is the L<string type|/"string Type"> and the type of I<RIGHT_OPERAND> is a L<numeric type|/"Numeric Types">, the L<undef type|/"undef Type">, or the L<any object type|/"Any Object Type"> C<object>, the cast requirement is true.

If the type of I<RIGHT_OPERAND> is a L<numeric type|/"Numeric Types">, the L<numeric-to-string conversion|/"Numeric-to-String Conversion"> is performed.

If the type of I<LEFT_OPERAND> is the L<string type|/"string Type"> and the type of I<RIGHT_OPERAND> is the L<any object type|/"Any Object Type"> C<object>, the cast requirement is true and the runtime type checking is performed.

=begin html

<table>
  <tr><th>Cast Requirement</th><th>To</th><th>From</th><th><a href="#Type-Conversion">Conversion or Type Checking</a></th></tr>
  <tr><td>True</td><td>string</td><td>string</td><td>None</td></tr>
  <tr><td>True</td><td>string</td><td>mutable string</td><td>None</td></tr>
  <tr><td>True</td><td>mutable string</td><td>mutable string</td><td>None</td></tr>
  <tr><td>True</td><td>mutable string</td><td>string</td><td><a href="#Runtime-Type-Checking">Runtime type checking</a></td></tr>
  <tr><td>True</td><td>string</td><td>string</td><td>None</td></tr>
  <tr><td>True</td><td>string</td><td>NUMERIC_X</td><td>Numeric-to-String Conversion</td></tr>
  <tr><td>True</td><td>string</td><td>object</td><td><a href="#Runtime-Type-Checking">Runtime type checking</a></td></tr>
  <tr><td>True</td><td>string</td><td>undef</td><td>None</td></tr>
  <tr><td>False</td><td>string</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

Examples:

  my $string = (string)"abc";
  my $number_string = (string)3;
  my $string : string = undef;

=head2 Cast Requirement to NumericObject

If the type of I<LEFT_OPERAND> is a L<numeric object type|/"Numeric Object Types"> and the types of I<RIGHT_OPERAND>s are the following cases:

If the type of I<RIGHT_OPERAND> is the same type of I<LEFT_OPERAND>, a L<numeric type|/"Numeric Types"> that is corresponding to the numeric object type, the L<any object type|/"Any Object Type"> C<object>, or the L<undef type|/"undef Type">, the cast requirement is true.

The type of I<RIGHT_OPERAND> is other than above, the cast requirement is false.

If the type of I<RIGHT_OPERAND> is a L<numeric type|/"Numeric Types">, the L<boxing conversion|/"Boxing Conversion"> is performed.

If the type of I<LEFT_OPERAND> is the type of I<RIGHT_OPERAND> is the L<any object type|/"Any Object Type"> C<object>, the L<assignment requirement|/"Assignment Requirement"> without implicite type conversion is performed.

=begin html

<table>
  <tr><th>Cast Requirement</th><th>To</th><th>From</th><th><a href="#Type-Conversion">Conversion or Type Checking</a></th></tr>
  <tr><td>True</td><td>NUMERIC_OBJECT_X</td><td>NUMERIC_OBJECT_X</td><td>None</td></tr>
  <tr><td>True</td><td>NUMERIC_OBJECT_X</td><td>NUMERIC_X</td><td><a href="#Boxing-Conversion">Boxing Conversion</td></a></tr>
  <tr><td>True</td><td>NUMERIC_OBJECT</td><td>object</td><td><a href="#Runtime-Type-Checking">Runtime type checking</a></td></tr>
  <tr><td>True</td><td>NUMERIC_OBJECT</td><td>undef</td><td>None</td></tr>
  <tr><td>False</td><td>NUMERIC_OBJECT</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

Examples:

  my $number_object = (Int)Int->new(3);
  my $number_object = (Int)3;
  my $number_object = (Int)undef;
  
  my $object : object = Int->new(3);
  my $number_object = (Int)$object;

=head2 Cast Requirement to Class

If the type of I<LEFT_OPERAND> is a L<class type|/"Class Type"> and the types of I<RIGHT_OPERAND>s are the following cases:

If the type of I<RIGHT_OPERAND> is the same type, the L<any object type|/"Any Object Type"> C<object>, an L<interface type|/"Interface Type"> or the L<undef type|/"undef Type">, the cast requirement is true.

If the type of I<LEFT_OPERAND> is a super class of the type of right operand, the cast requirement is true.

If the type of I<RIGHT_OPERAND> is a super class of the type of left operand, the cast requirement is true.

Otherwise, the cast requirement is false.

If the type of I<RIGHT_OPERAND> is the L<any object type|/"Any Object Type"> C<object> or an L<interface type|/"Interface Type">, the L<assignment requirement|/"Assignment Requirement"> without implicite type conversion is performed.

=begin html

<table>
  <tr><th>Cast Requirement</th><th>To</th><th>From</th><th><a href="#Type-Conversion">Conversion or Type Checking</a></th></tr>
  <tr><td>True</td><td>CLASS_X</td><td>CLASS_X</td><td>None</td></tr>
  <tr><td>True</td><td>SUPER_CLASS_X</td><td>CLASS_Y</td><td>None</td></tr>
  <tr><td>True</td><td>CLASS_X</td><td>SUPER_CLASS_Y</td><td><a href="#Runtime-Type-Checking">Runtime type checking</a></td></tr>
  <tr><td>True</td><td>CLASS_X</td><td>INTERFACE_Y</td><td><a href="#Runtime-Type-Checking">Runtime type checking</a></td></tr>
  <tr><td>True</td><td>CLASS_X</td><td>object</td><td><a href="#Runtime-Type-Checking">Runtime type checking</a></td></tr>
  <tr><td>True</td><td>CLASS</td><td>undef</td><td>None</td></tr>
  <tr><td>False</td><td>CLASS</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

Examples:

  my $point : Point = Point->new;
  
  my $stringable : Stringable;
  my $point = (Point)$stringable;

  my $stringer : Stringer;
  my $point = (Point)$stringer

  my $point = (Point)undef;

=head2 Cast Requirement to Interface

If the type of I<LEFT_OPERAND> is an L<interface type|/"Interface Type">, and the types of I<RIGHT_OPERAND>s are the following cases:

If the type of I<RIGHT_OPERAND> is the same type, the L<any object type|/"Any Object Type"> C<object> , an L<interface type|/"Interface Type"> or the L<undef type|/"undef Type">, the cast requirement is true.

If the type of I<RIGHT_OPERAND> is a L<class type|/"Class Type"> and the class has the interface of I<LEFT_OPERAND>, the cast requirement is true.

Otherwise, the cast requirement is false.

If the type of I<RIGHT_OPERAND> is the L<any object type|/"Any Object Type"> C<object>, an L<interface type|/"Interface Type">, the L<assignment requirement|/"Assignment Requirement"> without implicite type conversion is performed.

=begin html

<table>
  <tr><th>Cast Requirement</th><th>To</th><th>From</th><th><a href="#Type-Conversion">Conversion or Type Checking</a></th></tr>
  <tr><td>True</td><td>INTERFACE_X</td><td>INTERFACE_X</td><td>None</td></tr>
  <tr><td>True</td><td>INTERFACE_X</td><td>INTERFACE_HAVING_Y</td><td>None</td></tr>
  <tr><td>True</td><td>INTERFACE_X</td><td>INTERFACE_Y</td><td><a href="#Runtime-Type-Checking">Runtime type checking</a></td></tr>
  <tr><td>True</td><td>INTERFACE_X</td><td>object</td><td><a href="#Runtime-Type-Checking">Runtime type checking</a></td></tr>
  <tr><td>True</td><td>INTERFACE</td><td>undef</td><td>None</td></tr>
  <tr><td>False</td><td>INTERFACE</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

Examples:
  
  my $stringable1 : Stringable;
  my $stringable2 = (Stringable)$stringable1;
  
  my $cloneable : Cloneable;
  my $stringable = (Stringable)$cloneable;
  
  my $stringable  = (Stringable)Point->new(1, 2);

  my $object : object  = Point->new(1, 2);
  my $stringable  = (Stringable)Point->new(1, 2);
  
  my $stringable : Stringable = undef;

=head2 Cast Requirement to Any Object

If the type of I<LEFT_OPERAND> is the L<any object type|/"Any Object Type"> and the types of I<RIGHT_OPERAND>s are the following cases:
 
If the type of I<RIGHT_OPERAND> is an L<object type|/"Object Types">, a L<numeric type|/"Numeric Types"> or the L<undef type|/"undef Type">, the cast requirement is true.

Otherwise, the cast requirement is false.

If the type of I<RIGHT_OPERAND> is a L<numeric type|/"Numeric Types">, the L<boxing conversion|/"Boxing Conversion"> is performed.

=begin html

<table>
  <tr><th>Cast Requirement</th><th>To</th><th>From</th><th><a href="#Type-Conversion">Conversion or Type Checking</a></th></tr>
  <tr><td>True</td><td>object</td><td>OBJECT_Y</td><td>None</td></tr>
  <tr><td>True</td><td>object</td><td>NUMERIC_X</td><td><a href="#Boxing-Conversion">Boxing Conversion</td></a></tr>
  <tr><td>True</td><td>object</td><td>undef</td><td>None</td></tr>
  <tr><td>False</td><td>object</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

Examples:

  my $object : object = Point->new;
  my $number_object : object = 3;
  my $object : object = undef;

=head2 Cast Requirement to Numeric Array

If the type of I<LEFT_OPERAND> is the L<byte[] type|/"byte[] Type"> and the type of I<RIGHT_OPERAND> is the L<string type|/"string Type">, the cast requirement is true.

If the type of I<LEFT_OPERAND> is a L<numeric array type|/"Numeric Array Type"> and the types of I<RIGHT_OPERAND>s are the following cases:

If the type of I<RIGHT_OPERAND> is the same type of I<LEFT_OPERAND>, the L<any object type|/"Any Object Type"> C<obejct> or the L<undef type|/"undef Type">, the cast requirement is true.

Otherwise, the cast requirement is false.

If the type of I<LEFT_OPERAND> is the L<byte[] type|/"byte[] Type"> and the type of I<RIGHT_OPERAND> is the L<string type|/"string Type">, L<String-to-byte[] Conversion> is performed.

If the type of I<RIGHT_OPERAND> is the L<any object type|/"Any Object Type"> C<obejct>, the L<assignment requirement|/"Assignment Requirement"> without implicite type conversion is performed.

=begin html

<table>
  <tr><th>Cast Requirement</th><th>To</th><th>From</th><th><a href="#Type-Conversion">Conversion or Type Checking</a></th></tr>
  <tr><td>True</td><td>byte[]</td><td>string</td><td><a href="#String-to-byte[]-Type-Conversion">String-to-byte[] Conversion</a></td></tr>
  <tr><td>True</td><td>NUMERIC_X[]</td><td>NUMERIC_X[]</td><td>None</td></tr>
  <tr><td>True</td><td>NUMERIC[]</td><td>object</td><td><a href="#Runtime-Type-Checking">Runtime type checking</a></td></tr>
  <tr><td>True</td><td>NUMERIC[]</td><td>undef</td><td>None</td></tr>
  <tr><td>False</td><td>NUMERIC[]</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

Examples:
  
  my $bytes = (byte[])"abc";
  
  my $numbers = (int[])new int[3];
  
  my $object : object = new int[3];
  my $numbers = (int[])$object;
  
  my $numbers = (int[])undef;

=head2 Cast Requirement to Multi-Numeric Array

If the type of I<LEFT_OPERAND> is a L<multi-numeric array type|/"Multi-Numeric Array Type"> and the types of I<RIGHT_OPERAND>s are the following cases:
 
If the type of I<RIGHT_OPERAND> is the same type of I<LEFT_OPERAND>, the L<any object type|/"Any Object Type"> C<obejct> or the L<undef type|/"undef Type">, the cast requirement is true.

Otherwise, the cast requirement is false.

If the type of I<RIGHT_OPERAND> is the L<any object type|/"Any Object Type"> C<obejct>, the L<assignment requirement|/"Assignment Requirement"> without implicite type conversion is performed.

=begin html

<table>
  <tr><th>Cast Requirement</th><th>To</th><th>From</th><th><a href="#Type-Conversion">Conversion or Type Checking</a></th></tr>
  <tr><td>True</td><td>MULNUM_X[]</td><td>MULNUM_X[]</td><td>None</td></tr>
  <tr><td>True</td><td>MULNUM_X[]</td><td>object</td><td><a href="#Runtime-Type-Checking">Runtime type checking</a></td></tr>
  <tr><td>True</td><td>MULNUM_X[]</td><td>undef</td><td>None</td></tr>
  <tr><td>False</td><td>MULNUM_X[]</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

Examples:

  my $numbers = (Complex_2d[])new Complex_2d[3];

  my $object : object = new Complex_2d[3];
  my $numbers = (Complex_2d[])$object;

  my $numbers = (Complex_2d[])undef;

=head2 Cast Requirement to String Array

If the type of I<LEFT_OPERAND> is a L<string array type|/"String Array Type"> and the types of I<RIGHT_OPERAND>s are the following cases:
 
If the type of I<RIGHT_OPERAND> is the same type of I<LEFT_OPERAND>, the L<any object type|/"Any Object Type"> C<obejct>, the L<any object array type|/"Any Object Array Type"> C<obejct[]> or the L<undef type|/"undef Type">, the cast requirement is true.

Otherwise, the cast requirement is false.

If the type of I<RIGHT_OPERAND> is the L<any object type|/"Any Object Type"> C<obejct>, or the L<any object array type|/"Any Object Array Type"> C<obejct[]>, the L<assignment requirement|/"Assignment Requirement"> without implicite type conversion is performed.

=begin html

<table>
  <tr><th>Cast Requirement</th><th>To</th><th>From</th><th><a href="#Type-Conversion">Conversion or Type Checking</a></th></tr>
  <tr><td>True</td><td>string[]</td><td>string[]</td><td>None</td></tr>
  <tr><td>True</td><td>string[]</td><td>object</td><td><a href="#Runtime-Type-Checking">Runtime type checking</a></td></tr>
  <tr><td>True</td><td>string[]</td><td>object[]</td><td><a href="#Runtime-Type-Checking">Runtime type checking</a></td></tr>
  <tr><td>True</td><td>string[]</td><td>undef</td><td>None</td></tr>
  <tr><td>False</td><td>string[]</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

Examples:

  my $strings = (string[])["abc", "def"];

  my $object : object = ["abc", "def"];
  my $strings = (string[])$object;

  my $objects : object[] = ["abc", "def"];
  my $strings = (string[])$object;

  my $strings  = (string[])undef;

=head2 Cast Requirement to Class Array

If the type of I<LEFT_OPERAND> is a L<class array type|/"Class Array Type"> and the types of I<RIGHT_OPERAND>s are the following cases:

If the L<basic type|/"Basic Types"> of I<LEFT_OPERAND> is a super class of the L<basic type|/"Basic Types"> of I<RIGHT_OPERAND>, the cast requirement is true.

If the L<basic type|/"Basic Types"> of I<RIGHT_OPERAND> is a super class of the L<basic type|/"Basic Types"> of I<LEFT_OPERAND>, the cast requirement is true.

If the type of I<RIGHT_OPERAND> is the same type of I<LEFT_OPERAND>, the L<any object type|/"Any Object Type"> C<obejct>, the L<any object array type|/"Any Object Array Type"> C<obejct[]> or the L<undef type|/"undef Type">, the cast requirement is true.

Otherwise, the cast requirement is false.

If the type of I<RIGHT_OPERAND> is the L<any object type|/"Any Object Type"> C<obejct>, or the L<any object array type|/"Any Object Array Type"> C<obejct[]>, the L<assignment requirement|/"Assignment Requirement"> without implicite type conversion is performed.

=begin html

<table>
  <tr><th>Cast Requirement</th><th>To</th><th>From</th><th><a href="#Type-Conversion">Conversion or Type Checking</a></th></tr>
  <tr><td>True</td><td>CLASS_X[]</td><td>CLASS_X[]</td><td>None</td></tr>
  <tr><td>True</td><td>SUPER_CLASS_X[]</td><td>CLASS_Y[]</td><td>None</td></tr>
  <tr><td>True</td><td>CLASS_X[]</td><td>SUPER_CLASS_Y[]</td><td><a href="#Runtime-Type-Checking">Runtime type checking</a></td></tr>
  <tr><td>True</td><td>CLASS_X[]</td><td>object</td><td><a href="#Runtime-Type-Checking">Runtime type checking</a></td></tr>
  <tr><td>True</td><td>CLASS_X[]</td><td>object[]</td><td><a href="#Runtime-Type-Checking">Runtime type checking</a></td></tr>
  <tr><td>True</td><td>CLASS_X[]</td><td>undef</td><td>None</td></tr>
  <tr><td>False</td><td>CLASS_X[]</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

Examples:

  my $points = (Point[])new Point[3];

  my $object : object = new Point[3];
  my $points = (Point[])$object;

  my $objects : object[] = new Point[3];
  my $points = (Point[])$object;

  my $points = (Point[])undef;

=head2 Cast Requirement to Interface Array

If the type of I<LEFT_OPERAND> is an L<interface array type|/"Interface Array Type"> and the types of I<RIGHT_OPERAND>s are the following cases:

If the type of I<RIGHT_OPERAND> is a L<class array type|/"Class Array Type"> and its L<basic type|/"Basic Types"> has the interface of the basic type of I<LEFT_OPERAND>, the cast requirement is true.

If the type of I<RIGHT_OPERAND> is the same type of I<LEFT_OPERAND>, the cast requirement is true.

If the type of I<RIGHT_OPERAND> is an differnt type of L<interface array type|/"Interface Array Type">, the cast requirement is also true.

If the type of I<RIGHT_OPERAND> is the L<any object type|/"Any Object Type"> C<obejct>, the L<any object array type|/"Any Object Array Type"> C<obejct[]>  or the L<undef type|/"undef Type">, the cast requirement is true.

Otherwise, the cast requirement is false.

If the type of I<RIGHT_OPERAND> is an differnt type of  L<interface array type|/"Interface Array Type">, the L<assignment requirement|/"Assignment Requirement"> without implicite type conversion is performed.

If the type of I<RIGHT_OPERAND> is the L<any object type|/"Any Object Type"> C<obejct>, or the L<any object array type|/"Any Object Array Type"> C<obejct[]>, the L<assignment requirement|/"Assignment Requirement"> without implicite type conversion is performed.

=begin html

<table>
  <tr><th>Cast Requirement</th><th>To</th><th>From</th><th><a href="#Type-Conversion">Conversion or Type Checking</a></th></tr>
  <tr><td>True</td><td>INTERFACE_X[]</td><td>INTERFAECE_HAVING_Y[]</td><td>None</td></tr>
  <tr><td>True</td><td>INTERFACE_X[]</td><td>INTERFACE_X[]</td><td>None</td></tr>
  <tr><td>True</td><td>INTERFACE_X[]</td><td>INTERFACE_Y[]</td><td><a href="#Runtime-Type-Checking">Runtime type checking</a></td></tr>
  <tr><td>True</td><td>INTERFACE_X[]</td><td>object</td><td><a href="#Runtime-Type-Checking">Runtime type checking</a></td></tr>
  <tr><td>True</td><td>INTERFACE_X[]</td><td>object[]</td><td><a href="#Runtime-Type-Checking">Runtime type checking</a></td></tr>
  <tr><td>True</td><td>INTERFACE_X[]</td><td>undef</td><td>None</td></tr>
  <tr><td>False</td><td>INTERFACE_X[]</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

Examples:

  my $stringables = (Stringable[])new Stringable[3];

  my $stringables = (Stringable[])new Point[3];
  
  my $stringables = (Stringable[])undef;

=head2 Cast Requirement to Any Object Array

If the type of I<LEFT_OPERAND> is the L<any object array type|/"Any Object Array Type"> C<object[]> and the types of I<RIGHT_OPERAND>s are the following cases:

If the type of I<RIGHT_OPERAND> is an L<object array type|/"Object Array Type"> or the L<undef type|/"undef Type">, the cast requirement is true.

If the type of I<RIGHT_OPERAND> is an L<any object type|/"Any Object Type">, the cast requirement is true.

Otherwise, the cast requirement is false.

If the type of I<RIGHT_OPERAND> is an L<any object type|/"Any Object Type">, the L<assignment requirement|/"Assignment Requirement"> without implicite type conversion is performed.

=begin html

<table>
  <tr><th>Cast Requirement</th><th>To</th><th>From</th><th><a href="#Type-Conversion">Conversion or Type Checking</a></th></tr>
  <tr><td>True</td><td>object[]</td><td>OBJECT_ARRAY_Y</td><td>None</td></tr>
  <tr><td>True</td><td>object[]</td><td>undef</td><td>None</td></tr>
  <tr><td>True</td><td>object[]</td><td>object</td><td><a href="#Runtime-Type-Checking">Runtime type checking</a></td></tr>
  <tr><td>False</td><td>object[]</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

Examples:

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
  
=head2 Cast Requirement to Multi-Dimensional Array

If the type of I<LEFT_OPERAND> is a L<multi-dimensional array type|/"Multi-Dimensional Array Type"> and  and the types of I<RIGHT_OPERAND>s are the following cases:

If the type of I<RIGHT_OPERAND> is the same type of I<LEFT_OPERAND> or the L<undef type|/"undef Type">, the cast requirement is true.

If the type of I<RIGHT_OPERAND> is an L<any object type|/"Any Object Type">, the cast requirement is true.

If the type dimesion of I<LEFT_OPERAND> is equal to the type dimension of I<RIGHT_OPERAND>, and the L<basic type|/"Basic Types"> of I<LEFT_OPERAND> is a super class of the L<basic type|/"Basic Types"> of I<RIGHT_OPERAND>, the cast requirement is true.

If the type dimesion of I<LEFT_OPERAND> is equal to the type dimension of I<RIGHT_OPERAND>, and the L<basic type|/"Basic Types"> of I<RIGHT_OPERAND> is a super class of the L<basic type|/"Basic Types"> of I<LEFT_OPERAND>, the cast requirement is true.

If the L<basic type|/"Basic Types"> of the type of I<LEFT_OPERAND> is an L<interface type|/"Interface Type"> and the L<basic type|/"Basic Types"> of the type of I<RIGHT_OPERAND> is a L<class type|/"Class Type"> and the dimension of the type of I<RIGHT_OPERAND> is the same as the dimension of the type left oerand and the L<basic type|/"Basic Types"> of the type of I<RIGHT_OPERAND> has the interface of the L<basic type|/"Basic Types"> of the type of I<LEFT_OPERAND> , the cast requirement is true.

Otherwise, the cast requirement is false.

=begin html

<table>
  <tr><th>Cast Requirement</th><th>To</th><th>From</th><th><a href="#Type-Conversion">Conversion or Type Checking</a></th></tr>
  <tr><td>True</td><td>ANY_X[]..</td><td>ANY_X[]..</td><td>None</td></tr>
  <tr><td>True</td><td>ANY_X[]..</td><td>object</td><td><a href="#Runtime-Type-Checking">Runtime type checking</a></td></tr>
  <tr><td>True</td><td>ANY_X[]..</td><td>object[]</td><td><a href="#Runtime-Type-Checking">Runtime type checking</a></td></tr>
  <tr><td>True</td><td>ANY_X[]..</td><td>undef</td><td>None</td></tr>
  <tr><td>True</td><td>SUPER_CLASS_X[]..</td><td>CLASS_Y[]..</td><td>None</td></tr>
  <tr><td>True</td><td>CLASS_X[]..</td><td>SUPER_CLASS_Y[]..</td><td><a href="#Runtime-Type-Checking">Runtime type checking</a></td></tr>
  <tr><td>True</td><td>INTERFACE_X[]..</td><td>INTERFACE_HAVING_Y[]..</td><td>None</td></tr>
  <tr><td>False</td><td>object[]</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

(C<[]..> means one or more C<[]>)

Examples:

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

=end html

(C<[]..> means one or more C<[]>)

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
