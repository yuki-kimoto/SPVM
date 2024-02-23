=head1 Name

SPVM::Document::Language::Types - Types in SPVM Language

=head1 Description

This document describes types in SPVM language.

=head1 Types

SPVM language has data types.

See L<Data type - Wikipedia|https://en.wikipedia.org/wiki/Type_system> about data types.

=head2 Initial Value

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
      <b>Multi-Numeric Type</b>
    </td>
    <td>
      All fields are set to <code>0</code> (All bits are <code>0</code>)
    </td>
  </tr>
</table>

=end html

=head2 Numeric Type

The numeric type are an L<integer type|/"Integer Type"> and L</"Floating Point Type">.

=head3 Numeric Type Order

a L<numeric type|/"Numeric Type"> has the type order. The order is "byte", "short", "int", "long", "float", "double" from the smallest.

=head2 Integer Type

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

Note that SPVM has only B<singed> integer types, and doesn't have B<unsigned> integer types.

=head2 Integer Type Within int

The integer type within C<int> is an L<integer type|/"Integer Type"> within the int type.

In other words, the integer types within C<int> are the L<byte type|/"byte Type">, the L<short type|/"short Type">, and the int type.

=head2 byte Type

C<byte> type is an L<integer type|/"Integer Type"> that represents a signed 8-bit integer. This is the same type as C<int8_t> type of the C language.

=head2 short Type

C<short> type  is an L<integer type|/"Integer Type"> that represents a signed 16-bit integer. This is the same type as C<int16_t> type of the C language.

=head2 int Type

C<int> type is  is an L<integer type|/"Integer Type"> that represents signed 32-bit integer. This is the same as C<int32_t> type of the C language.

=head2 long Type

C<long> type is an L<integer type|/"Integer Type"> that represents a signed 64-bit integer. This is the same type as C<int64_t> type of the C language.

=head2 Floating Point Type

B<Floating Point Type> are the following two.

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

=head2 float Type

The C<float> type is a L<floating point type|/"Floating Point Type"> that represents a single precision(32bit) floating point. This is the same type as C<float> type of the C language.

=head2 double Type

The C<double> type is a L<floating point type|/"Floating Point Type"> that represents a double precision(64bit) floating point. This is the same type as C<double> type of the C language.

=head2 Class Type

The class type is the type that can create the object using a L<new operator|/"new Operator">.

  new ClassType;

=head2 Basic Object Type

Basic object types are the L<class type|/"Class Type">, the L<array type|/"Array Type">, the L<string type|/"string Type">, and the L<any object type|/"Any Object Type">.

=head2 Object Type

Object types are the L<basic object types|/"Basic Object Type"> and the L<array types|/"Array Type">.

A object type can be assigned to a L<any object type|/"Any Object Type">.

  my $object: object = new Foo;
  my $object: object = "abc";

=head2 Numeric Object Type

A numeric object type is the L<object type|/"Object Type"> that is corresponding to the L<numeric type|/"Numeric Type">.

The list of numeric object types:

=begin html

<table>
  <tr>
    <th>
      Numeric Object Type
    </th>
    <th>
      Corresponding Numeric Type
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

=head2 undef Type

The undef type is the type of L<undef|/"Undefined Value"> value.

=head3 Undefined Value

An undefined value is represented by C<undef>.

  undef

An undefined value can be assigned to an L<object type|/"Object Type">.

In the level of L<native APIs|SPVM:Document::NativeAPI>, undef is defined as C<(void*)NULL>.

  (void*)NULL

An undefined value can be compared by the C<==> operator and the C<!=> operator. An undefined value is guaranteed not to be equal to the any created object.

The type of undef is L<undef type|/"undef Type">

Examples:
  
  # Undefine values
  my $string : string = undef;
  
  if (undef) {
    
  }
  
  my $message = "Hello";
  if ($message == undef) {
    
  }

=head2 Interface Type

The interface type is a type that is defined using a C<class> keyword and a L<class attribute|/"Class Attribute"> C<interface_t>.

  class Stringable : interface_t {
    method to_string : string ();
  }

See also L</"Interface">.

Note that interface types are not L<class types|/"Class Type"> although they are defined by C<class> keyword.

=head2 Any Object Type

Any Object Type is represented by "object". Designed to represent the "void *" Type in C.

  my $object: object;

You can methodstitute the value of "Object Type" for Any Object Type.

  my $object: object = new Foo;
  my $object: object = "abc";
  my $object: object = new Foo [3];

=head2 void Type

B<void Type> is a special Type that can only be used in the return type of the L<method definition|/"Method Definition"> and indicates the method has no return value.

  void

=head2 Basic Type

The basic types are L<numeric types|/"Numeric Type">, L<multi-numeric types|/"Multi-Numeric Type">, the L<class type|/"Class Type">, the L<any object type|/"Any Object Type">, and the L<string type|/"string Type">.

Another definition of basic types are the types that is not L<array types|"Array Type"> and can become the element of L<array types|"Array Type">.

=head2 Array Type

The array type is the L<type|Type> for the L<array|/"Array">. The array type is composed of the L<basic type|/"Basic Type"> and the dimension such as C<[]>, C<[][]>.

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

The array type is an L<object type|/"Object Type">.

Compilation Errors:

The maximam value of dimesions is 255. Otherwise a compilation error occurs.

=head3 Array

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

The numeric array is the array that the type of the element is the L<numeric type|/"Numeric Type">.

The object array is the array that the type of the element is the L<object type|/"Object Type">.

The multi-numeric array is the array that the type of the element is the L<multi-numeric type|/"Multi-Numeric Type">.

See L</"Creating Array"> to create Array.

=head3 Array Access

Array Access is an L<operator|/"Operators"> to access the element of Array to get or set the value.

  ARRAY->[INDEX]

See L</"Getting Array Element"> to get the element value of Array.

See L</"Setting Array Element"> to set the element value of Array.

=head3 Numeric Array Type

The numeric array type is an L<array type|Array Type> for the array of the L<numeric type|/"Numeric Type">.

The list of the numeric array.

=over 2

=item * byte[]

=item * short[]

=item * int[]

=item * long[]

=item * float[]

=item * double[]

=back

Each element are initialized by the L<initial value/"Initial Value"> when the L<creating array|/"Creating Array"> is performed.

=head3 byte[] Type

The C<byte[]> type is an L<array type|/"Array Type"> that the element type is C<byte>.

  byte[]

=head3 Object Array Type

Object array types are the L<array type|/"Array Type"> that the type of the element is an L<object type|/"Object Type">.

Examples:

  # Object array types
  my $points : Point[];
  my $points_2dim : Point[][];
  my $stringables : Stringable[];
  my $strings : string[];
  my $objects : object[];

=head3 String Array Type

String array types are the L<array type|/"Array Type"> that the type of the element is the L<string type|/"string Type">.

Examples:

  # String array types
  my $strings : string[];

=head3 Class Array Type

Class array types are the L<array type|/"Array Type"> that the type of the element is the L<class type|/"Class Type">.

Examples:

  # Class array types
  my $points : Point[];

=head3 Interface Array Type

Interface array types are the L<array type|/"Array Type"> that the type of the element is the L<interface type|/"Interface Type">.

Examples:

  # Interface array types
  my $stringables : Stringable[];

=head3 Multi-Dimensional Array Type

The multi-dimensional array type is the L<array type|/"Array Type"> that the type of the element is an L<array type|/"Array Type">.

Examples:

  # Multi-dimensional array types
  my $nums_2dim : Int[][];

=head3 Multi-Numeric Array Type

A multi-numeric array type is an L<array type|/"Array Type"> that the basic type is a L<multi-numeric type|"Multi-Numeric Type">.

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

The byte size of the element is the total byte size of the fields of the L<multi-numeric type|"Multi-Numeric Type">.

For example, The byte size of the element of L<Complex_2d|SPVM::Complex_2d> is 16 bytes (2 * 8 bytes).

The object of the multi-numeric array type can be created by the L<new|/"Creating Array"> operator.

  my $complex_nums = new Complex_2d[10];

=head4 Multi-Numeric Array

The L<multi-numeric values|/"Multi-Numeric Value"> can be the elements of the L<array|/"Array">.

  my $zs = new Complex_2d[3];

The elements of the multi-numeric array is continuous multi-numeric values.
  
  | Complex_2d  | Complex_2d  | Complex_2d  |
  |  re  |  im  |  re  |  im  |  re  |  im  |

=head5 Multi-Numeric Array Access

The multi-numeric array access is a syntax to access the element of the multi-numeric array.

  ARRAY->[INDEX]

See L</"Getting Array Element"> to get the element of the array.

See L</"Setting Array Element"> to set the element of the array.

=head2 Dereference

The dereference is the operation to get the value from a reference.

A L<dereference operator|/"Dereference Operator"> perform a dereference.

  # Get the value using a dereference
  my $num2 = $$num_ref;
  
  # Set the value using a dereference
  $$num_ref = 3;
  
  # Get the value of a multi-numeric type using a dereference
  my $z2 = $$z_ref;
  
  # Set the value of a multi-numeric type using a dereference
  $$z_ref = $z2;

In the referencec of L<multi-numeric types|/"Multi-Numeric Type">, the deference can be performed using the arrow operator C<-E<gt>>.

  # Get a field of a multi-numeric type using a dereference
  my $x = $z_ref->{re};
  
  # Set a field of a multi-numeric type using a dereference
  $z_ref->{re} = 1;

=head3 Any Object Array Type

The any object array type C<object[]> is the type that any L<object array type|/"Object Array Type"> can be assigned.

  # Any object array Type
  my $array : object[] = new Point[3];
  my $array : object[] = new object[3];
  my $array : object[] = new Point[][3];

Any Object Array Type is an L<array type|/"Array Type">.

You can get the array length using the L<array length operator|/"The array Length Operator">.

  my $array : object[] = new Int[3];
  
  # Getting the length of the element of Any Object Array Type
  my $length = @$array;

You can get and set the element using the L<get array element|/"Getting Array Element"> syntax and the L<set array element|/"Setting Array Element">.
 
  # Getting the element of any object array
  my $num = (Int)$array->[0];
  
  # Setting the element of any object array
  $array->[0] = Int->new(5);

When setting the element of any object array, the element type is checked. If the dimension of the element is not the dimension of the array - 1, an exception is thrown.

Compilation Errors:

If a invalid type is assigned, a compilation error occurs.

=head2 string Type

The C<string> type is a L<type|/"Types"> for the L</"String">.

  string

C<string> type can be qualified by L</"mutable Type Qualifier">.

  mutable string

Examples:
  
  # string type
  my $message : string = "Hello";
  my $message : mutable string = new_string_len 256;

=head3 String

SPVM has the L<string type|/"string Type">. A string is created by L</"String Literal"> L</"String Creating Operator"> or L</"Type Convertion"> to the string type.
  
  # Create a string using a string literal
  my $string = "Hello";
  
  # Create a string using a string creation operator
  my $string = new_string_len 3;
  
  # Create a string using the type cast to the string type
  my $bytes = [(byte)93, 94, 95];
  my $string = (string)$bytes;

The each charcter can be get using C<-E<gt>[]>.

  # String
  my $string = "Hello";
  my $char0 = $string->[0];
  my $char1 = $string->[1];
  my $char2 = $string->[2];

By default, each character cannnot be set.
  
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

=head2 Multi-Numeric Type

The multi-numeric type is the type to represent a L<multi-numeric value|/"Multi-Numeric Value">.

The multi-numeric type can be used as the L<type|/"Types"> of the L<local variable declaration|/"Local Variable Declaration">.

  my $z : Complex_2d;

The value is initialized by the L<initial value/"Initial Value">.

The multi-numeric type can be used as an argument the L<type|/"Types"> in the L<method definition|/"Method Definition">.

The multi-numeric type can be used as the return L<type|/"Types"> of the L<method definition|/"Method Definition">.

  static method add_double_complex : Complex_2d ($z1 : Complex_2d, $z2 : Complex_2d) { ... }

The multi-numeric type can be used as a L<basic type|/"Basic Type"> of the L<array type|/"Array Type"> .

  my $points = new Complex_2d[5];

The reference can be created for the value of the multi-numeric type.

  my $z : Complex_2d;
  my $z_ref = \$z;

L<undef|/"Undefined Value"> cannot be assigned to the multi-numeric type.

=head3 Multi-Numeric Value

A multi-numeric value is a value that represents continuous multiple numeric values in memory.

=head4 Multi-Numeric Type Definition

A L<multi-numeric type|/"Multi-Numeric Type"> is defined by the L<class definition|/"Class Definition"> that has the C<mulnum_t> L<class attribute|/"Class Attribute">.

  # Continuous two 64bit floating point
  class Complex_2d : mulnum_t {
    re : double;
    im : double;
  }

The type of a field must be a L<numeric type|/"Numeric Type">.

The types of all fields must be the same types.

The length of the fields must be less than or equal to 255.

The multi-numeric type must end with the following suffix.

  _[FieldsLength][TypeSuffix]

The length of the fields in the suffix must be the same as the length of the fields.

The type suffix in the suffix must correspond to the L<numeric type|/"Numeric Type"> that is explained in the L<multi-numeric type suffix|/"Multi-Numeric Type Suffix">.

See the L<multi-numeric type field access|/"Multi-Numeric Type Field Access"> to get and set the field of the multi-numeric type.

=head3 Multi-Numeric Type Suffix

The list of the multi-numeric type suffix.

=begin html

<table>
  <tr>
    <th>
      Numeric Type
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

=head3 Multi-Numeric Type Field Access

The multi-numeric type field access is an syntax to access the field of the multi-numeric value.

  MULTI_NUMERIC_VALUE->{FIELD_NAME}

See L</"Getting Multi-Numeric Field"> to get the field of the multi-numeric value.

See L</"Setting Multi-Numeric Field"> to set the field of the multi-numeric value.

=head2 Reference Type

Reference Type is a Type that can store the address of a variable. Add C<*> after a L<numeric type|/"Numeric Type"> or the L<multi-numeric type|/"Multi-Numeric Type"> You can define it.

  my $num : int;
  my $num_ref : int* = \$num;
  
  my $z : Complex_2d;
  my $z_ref : Complex_2d* = \$z;

Only the address of the Local Variable acquired by L</"Reference Operator"> can be assigned to the value of Reference Type.

Reference Type can be used as Type of argument in the L<method definition|/"Method Definition">.

Reference Type cannot be used as return value Type in the L<method definition|/"Method Definition">.

Reference Type cannot be used as the field type in the L<class definition|/"Class Definition">.

Reference Type cannot be used as the type of Class Variable in the L<class definition|/"Class Definition">.

See L</"Reference"> for a detailed explanation of Reference.

Compilation Errors:

If only Local Variable Declaration of Reference Type is performed, a compilation error occurs

Reference Type can be used as Type of the L<local variable declaration|/"Local Variable Declaration">. The address of the Local Variable must be stored by the Reference Operator. In case of only Local Variable Declaration, a compilation error occurs

If the Reference Type is used at an Invalid location, a compilation error occurs

=head3 Reference

The reference is the address of a L<local variable|/"Local Variable"> on the memory.

=head4 Creating Reference

The L<reference operator|/"Reference Operator"> creates the reference of a L<local variable|/"Local Variable">.

A reference is assigned to the L<reference type/"Reference Type">.

The operand of a reference operator must be the variable of a L<numeric type|/"Numeric Type"> or a L<multi-numeric type|/"Multi-Numeric Type">.

  # The reference of numeric type
  my $num : int;
  my $num_ref : int* = \$num;
  
  # The reference of multi-numeric type
  my $z : Complex_2d;
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

=head2 Numeric Reference Type

Numeric Reference Type means a L<numeric type|/"Numeric Type"> for a L<reference type|/"Reference Type">. Says.

=head2 Multi-Numeric Reference Type

Multi-Numeric Reference Type means a L<reference type|/"Reference Type"> for the L<multi-numeric type|/"Multi-Numeric Type"> variables. > Means.

=head2 Type Qualifier

Type qualifiers qualify the type.

  QUALIFIER TYPE

=head3 mutable Type Qualifier

The C<mutable> type qualifier is used to allow to set the character of the string.

  my $string : mutable string;

Examples:
  
  # Mutable string
  my $message = (mutable string)"abc";
  $message->[0] = 'd';

=head2 Type Inference

Omitting the L<type|/"Types"> when the L<local variable declaration|/"Local Variable Declaration"> by Type Inference can. Type Inference is always performed by the type on the Right side of Assignment Operator.

  # int
  my $num = 1;
  
  # double
  my $num = 1.0;
  
  # Foo
  my $foo = new Foo;

=head2 Type Assignability

The assignability at compile-time is explained.

Compilation Errors:

The assignability is false, a compilation error occurs.

=head3 Type Assignability to Numeric

Explains the assignability to the L<numeric types|"Numeric Type">.

=head4 Type Assignability from Numeric to Numeric

If the L<nemric type order|/"Numeric Type Order"> of I<LEFT_OPERAND> is greater than or equal to the L<nemric type order|/"Numeric Type Order"> of I<RIGHT_OPERAND>, the assignability is true.

If the L<nemric type order|/"Numeric Type Order"> of I<LEFT_OPERAND> is greater than the L<nemric type order|/"Numeric Type Order"> of I<RIGHT_OPERAND>, the L<numeric widening conversion|/"Numeric Widening Conversion"> is performed.

=begin html

<table>
  <tr><th>Type Assignability</th><th>To</th><th>From</th><th><a href="#Implicite-Type-Conversion">Implicite Type Conversion</a></th></tr>
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
  my $num : int = 3;
  
  # byte to int
  my $num : int = (byte)5;
  
  # double to double
  my $num : double = 4.5;
  
  # float to double
  my $num : double = 4.5f;

If the L<nemric type order|/"Numeric Type Order"> of I<LEFT_OPERAND> is less than the L<nemric type order|/"Numeric Type Order"> of I<RIGHT_OPERAND>, the assignability is conditional true.

The condition is that I<RIGHT_OPERAND> is a L<interger literal|Integer Literal> and the value is between the max and minimal value of the type of I<LEFT_OPERAND>.

If the condition is ture, the L<numeric narrowing conversion|/"Numeric Narrowing Conversion"> is performed.

=begin html

<table>
  <tr><th>Type Assignability</th><th>To</th><th>From</th><th><a href="#Implicite-Type-Conversion">Implicite Type Conversion</a></th></tr>
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
  my $num : byte = 127;

=head4 Type Assignability from NumericObject to Numeric

If the type of I<LEFT_OPERAND> is a L<numeric type|/"Numeric Type"> corresponding to the numeric object type of I<RIGHT_OPERAND> and the type of I<RIGHT_OPERAND> is a L<numeric object type|/"Numeric Object Type">, the assignability is true.

=begin html

<table>
  <tr><th>Type Assignability</th><th>To</th><th>From</th><th><a href="#Implicite-Type-Conversion">Implicite Type Conversion</a></th></tr>
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

=head4 Type Assignability from Any Object to Numeric

If the type of I<LEFT_OPERAND> is a L<numeric type|/"Numeric Type"> and the type of I<RIGHT_OPERAND> is a L<any object type|/"Any Object Type"> C<object>, the assignability is true.

The L<unboxing conversion|/"Unboxing Conversion"> corresponding to the numeric type is performed.

=begin html

<table>
  <tr><th>Type Assignability</th><th>To</th><th>From</th><th><a href="#Implicite-Type-Conversion">Implicite Type Conversion</a></th></tr>
  <tr><td>True</td><td>NUMERIC_X</td><td>object</td><td><a href="#Unboxing-Conversion">Unboxing Conversion</td></a></tr>
</table>

=end html

Examples:

  my $int : int = (object)Int->new(3);

  my $double : double = (object)Double->new(3.5);

=head4 Type Assignability from Others to Numeric

If the type of I<LEFT_OPERAND> is a L<numeric type|/"Numeric Type"> and the type of I<RIGHT_OPERAND> is other than the types described above, the assignability is false.

=head3 Type Assignability to Multi-Numeric

If the type of I<LEFT_OPERAND> is a L<multi-numeric type|/"Multi-Numeric Type"> and the type of I<RIGHT_OPERAND> is the same type of I<LEFT_OPERAND>, the assignability is true.

Otherwise, the assignability is false.

=begin html

<table>
  <tr><th>Type Assignability</th><th>To</th><th>From</th><th><a href="#Implicite-Type-Conversion">Implicite Type Conversion</a></th></tr>
  <tr><td>True</td><td>MULNUM_X</td><td>MULNUM_X</td><td>None</td></tr>
  <tr><td>False</td><td>MULNUM_X</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

Examples:

  my $z1 : Complex_2d;
  my $z2 : Complex_2d = $z1;

=head3 Type Assignability to Referenece

If the type of I<LEFT_OPERAND> is a L<reference type|/"Reference Type"> and the type of I<RIGHT_OPERAND> is the same type of I<LEFT_OPERAND>, the assignability is true.

Otherwise, the assignability is false.

=begin html

<table>
  <tr><th>Type Assignability</th><th>To</th><th>From</th><th><a href="#Implicite-Type-Conversion">Implicite Type Conversion</a></th></tr>
  <tr><td>True</td><td>REF_X</td><td>REF_X</td><td>None</td></tr>
  <tr><td>False</td><td>REF_X</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

Examples:

  my $num : int = 5;
  my $num_ref : int* = \num;

=head3 Type Assignability to String

If the type of I<LEFT_OPERAND> is the L<string type|/"string Type"> without the L<mutable type qualifier|/"mutable Type Qualifier"> and the type of I<RIGHT_OPERAND> is the L<string type|/"string Type">, the assignability is true.

If the type of I<LEFT_OPERAND> is the L<string type|/"string Type"> with the L<mutable type qualifier|/"mutable Type Qualifier"> and the type of I<RIGHT_OPERAND> is the L<string type|/"string Type"> with the L<mutable type qualifier|/"mutable Type Qualifier">, the assignability is true.

If the type of I<LEFT_OPERAND> is the L<string type|/"string Type"> with the L<mutable type qualifier|/"mutable Type Qualifier"> and the type of I<RIGHT_OPERAND> is the L<string type|/"string Type"> without the L<mutable type qualifier|/"mutable Type Qualifier">, the assignability is false.

If the type of I<LEFT_OPERAND> is the L<string type|/"string Type"> and the type of I<RIGHT_OPERAND> is a L<numeric type|/"Numeric Type"> or the L<undef type|/"undef Type">, the assignability is true.

If the type of I<RIGHT_OPERAND> is a L<numeric type|/"Numeric Type">, the L<numeric-to-string conversion|/"Numeric-to-String Conversion"> is performed.

=begin html

<table>
  <tr><th>Type Assignability</th><th>To</th><th>From</th><th><a href="#Implicite-Type-Conversion">Implicite Type Conversion</a></th></tr>
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
  my $num_string : string = 3;
  my $string : string = undef;

=head3 Type Assignability to NumericObject

If the type of I<LEFT_OPERAND> is a L<numeric object type|/"Numeric Object Type"> and the type of I<RIGHT_OPERAND> is the same type of I<LEFT_OPERAND>, a L<numeric type|/"Numeric Type"> that is corresponding to the numeric object type, or the L<undef type|/"undef Type">, the assignability is true.

Otherwise, the assignability is false.

If the type of I<RIGHT_OPERAND> is a L<numeric type|/"Numeric Type">, the L<boxing conversion|/"Boxing Conversion"> is performed.

=begin html

<table>
  <tr><th>Type Assignability</th><th>To</th><th>From</th><th><a href="#Implicite-Type-Conversion">Implicite Type Conversion</a></th></tr>
  <tr><td>True</td><td>NUMERIC_OBJECT_X</td><td>NUMERIC_OBJECT_X</td><td>None</td></tr>
  <tr><td>True</td><td>NUMERIC_OBJECT_X</td><td>NUMERIC_X</td><td><a href="#Boxing-Conversion">Boxing Conversion</td></a></tr>
  <tr><td>True</td><td>NUMERIC_OBJECT</td><td>undef</td><td>None</td></tr>
  <tr><td>False</td><td>NUMERIC_OBJECT</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

Examples:

  my $num_object : Int = Int->new(3);
  my $num_object : Int = 3;
  my $num_object : Int = undef;

=head3 Type Assignability to Class

If the type of I<LEFT_OPERAND> is a L<class type|/"Class Type"> and the type of I<RIGHT_OPERAND> is the same type, or the L<undef type|/"undef Type">, the assignability is true.

If the type of I<LEFT_OPERAND> is a super class of the type of I<RIGHT_OPERAND>, the assignability is true.

Otherwise, the assignability is false.

=begin html

<table>
  <tr><th>Type Assignability</th><th>To</th><th>From</th><th><a href="#Implicite-Type-Conversion">Implicite Type Conversion</a></th></tr>
  <tr><td>True</td><td>CLASS_X</td><td>CLASS_X</td><td>None</td></tr>
  <tr><td>True</td><td>CLASS</td><td>undef</td><td>None</td></tr>
  <tr><td>True</td><td>SUPER_CLASS_X</td><td>CLASS_Y</td><td>None</td></tr>
  <tr><td>False</td><td>CLASS</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

Examples:

  my $point : Point = Point->new;
  my $point : Point = undef;

=head3 Type Assignability to Interface

If the type of I<LEFT_OPERAND> is an L<interface type|/"Interface Type"> and the type of I<RIGHT_OPERAND> is the same type, or the L<undef type|/"undef Type">, the assignability is true.

If the type of I<LEFT_OPERAND> is an L<interface type|/"Interface Type"> and the type of I<RIGHT_OPERAND> is a L<class type|/"Class Type"> and the class has the same interface of I<LEFT_OPERAND>, the assignability is true.

Otherwise, the assignability is false.

=begin html

<table>
  <tr><th>Type Assignability</th><th>To</th><th>From</th><th><a href="#Implicite-Type-Conversion">Implicite Type Conversion</a></th></tr>
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

=head3 Type Assignability to Any Object

If the type of I<LEFT_OPERAND> is the L<any object type|/"Any Object Type"> and the type of I<RIGHT_OPERAND> is an L<object type|/"Object Type">, a L<numeric type|/"Numeric Type"> or the L<undef type|/"undef Type">, the assignability is true.

Otherwise, the assignability is false.

If the type of I<RIGHT_OPERAND> is a L<numeric type|/"Numeric Type">, the L<boxing conversion|/"Boxing Conversion"> is performed.

=begin html

<table>
  <tr><th>Type Assignability</th><th>To</th><th>From</th><th><a href="#Implicite-Type-Conversion">Implicite Type Conversion</a></th></tr>
  <tr><td>True</td><td>object</td><td>OBJECT_Y</td><td>None</td></tr>
  <tr><td>True</td><td>object</td><td>NUMERIC_X</td><td><a href="#Boxing-Conversion">Boxing Conversion</td></a></tr>
  <tr><td>True</td><td>object</td><td>undef</td><td>None</td></tr>
  <tr><td>False</td><td>object</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

Examples:

  my $object : object = Point->new;
  my $num_object : object = 3;
  my $object : object = undef;

=head3 Type Assignability to Undefined

If the type of I<LEFT_OPERAND> is the L<undef type|/"undef Type">, the assignability is false.

=begin html

<table>
  <tr><th>Type Assignability</th><th>To</th><th>From</th><th><a href="#Implicite-Type-Conversion">Implicite Type Conversion</a></th></tr>
  <tr><td>False</td><td>undef Type</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

Examples:

  # The assignability is false
  undef = Point->new;

=head3 Type Assignability to Numeric Array

If the type of I<LEFT_OPERAND> is a L<numeric array type|/"Numeric Array Type"> and the type of I<RIGHT_OPERAND> is the same type of I<LEFT_OPERAND> or the L<undef type|/"undef Type">, the assignability is true.

Otherwise, the assignability is false.

=begin html

<table>
  <tr><th>Type Assignability</th><th>To</th><th>From</th><th><a href="#Implicite-Type-Conversion">Implicite Type Conversion</a></th></tr>
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

  my $nums : int[] = new int[3];
  my $nums : int[] = undef;

=head3 Type Assignability to Multi-Numeric Array

If the type of I<LEFT_OPERAND> is a L<multi-numeric array type|/"Multi-Numeric Array Type"> and the type of I<RIGHT_OPERAND> is the same type of I<LEFT_OPERAND> or the L<undef type|/"undef Type">, the assignability is true.

Otherwise, the assignability is false.

=begin html

<table>
  <tr><th>Type Assignability</th><th>To</th><th>From</th><th><a href="#Implicite-Type-Conversion">Implicite Type Conversion</a></th></tr>
  <tr><td>True</td><td>MULNUM_X[]</td><td>MULNUM_X[]</td><td>None</td></tr>
  <tr><td>True</td><td>MULNUM_X[]</td><td>undef</td><td>None</td></tr>
  <tr><td>False</td><td>MULNUM_X[]</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

Examples:

  my $nums : Complex_2d[] = new Complex_2d[3];
  my $nums : Complex_2d[] = undef;

=head3 Type Assignability to String Array

If the type of I<LEFT_OPERAND> is a L<string array type|/"String Array Type"> and the type of I<RIGHT_OPERAND> is the same type of I<LEFT_OPERAND> or the L<undef type|/"undef Type">, the assignability is true.

Otherwise, the assignability is false.

=begin html

<table>
  <tr><th>Type Assignability</th><th>To</th><th>From</th><th><a href="#Implicite-Type-Conversion">Implicite Type Conversion</a></th></tr>
  <tr><td>True</td><td>string[]</td><td>string[]</td><td>None</td></tr>
  <tr><td>True</td><td>string[]</td><td>undef</td><td>None</td></tr>
  <tr><td>False</td><td>string[]</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

Examples:

  my $strings : string[] = ["abc", "def"];
  my $strings : string[] = undef;

=head3 Type Assignability to Class Array

If the type of I<LEFT_OPERAND> is a L<class array type|/"Class Array Type"> and the type of I<RIGHT_OPERAND> is the same type of I<LEFT_OPERAND> or the L<undef type|/"undef Type">, the assignability is true.

If the L<basic type|/"Basic Type"> of I<LEFT_OPERAND> is an super class of the type of I<RIGHT_OPERAND>, the assignability is true.

Otherwise, the assignability is false.

=begin html

<table>
  <tr><th>Type Assignability</th><th>To</th><th>From</th><th><a href="#Implicite-Type-Conversion">Implicite Type Conversion</a></th></tr>
  <tr><td>True</td><td>CLASS_X[]</td><td>CLASS_X[]</td><td>None</td></tr>
  <tr><td>True</td><td>SUPER_CLASS_X[]</td><td>CLASS_Y[]</td><td>None</td></tr>
  <tr><td>True</td><td>CLASS_X[]</td><td>undef</td><td>None</td></tr>
  <tr><td>False</td><td>CLASS_X[]</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

Examples:

  my $points : Point[] = new Point[3];
  my $points : Point[] = undef;

=head3 Type Assignability to Interface Array

If the type of I<LEFT_OPERAND> is an L<interface array type|/"Interface Array Type"> and the type of I<RIGHT_OPERAND> is the same type of I<LEFT_OPERAND> or the L<undef type|/"undef Type">, the assignability is true.

If the type of I<LEFT_OPERAND> is an L<interface array type|/"Interface Array Type"> and the type of I<RIGHT_OPERAND> is a L<class array type|/"Class Array Type"> and its L<basic type|/"Basic Type"> can assign to the basic type of I<LEFT_OPERAND>, the assignability is true.

Otherwise, the assignability is false.

=begin html

<table>
  <tr><th>Type Assignability</th><th>To</th><th>From</th><th><a href="#Implicite-Type-Conversion">Implicite Type Conversion</a></th></tr>
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

=head3 Type Assignability to Any Object Array

If the type of I<LEFT_OPERAND> is the L<any object array type|/"Any Object Array Type"> C<object[]> and the type of I<RIGHT_OPERAND> is an L<object array type|/"Object Array Type"> or the L<undef type|/"undef Type">, the assignability is true.

Otherwise, the assignability is false.

=begin html

<table>
  <tr><th>Type Assignability</th><th>To</th><th>From</th><th><a href="#Implicite-Type-Conversion">Implicite Type Conversion</a></th></tr>
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

=head3 Type Assignability to Multi-Dimensional Array

If the type of I<LEFT_OPERAND> is a L<multi-dimensional array type|/"Multi-Dimensional Array Type"> and the type of I<RIGHT_OPERAND> is the same type of I<LEFT_OPERAND> or the L<undef type|/"undef Type">, the assignability is true.

If the type dimesion of I<LEFT_OPERAND> is equal to the type dimension of I<RIGHT_OPERAND>, and the L<basic type|/"Basic Type"> of I<LEFT_OPERAND> is a super class of the L<basic type|/"Basic Type"> of I<RIGHT_OPERAND>, the assignability is true.

If the type dimesion of I<LEFT_OPERAND> is equal to the type dimension of I<RIGHT_OPERAND>, and the L<basic type|/"Basic Type"> of I<RIGHT_OPERAND> has the L<basic type|/"Basic Type"> of I<LEFT_OPERAND>, the assignability is true.

Otherwise, the assignability is false.

=begin html

<table>
  <tr><th>Type Assignability</th><th>To</th><th>From</th><th><a href="#Implicite-Type-Conversion">Implicite Type Conversion</a></th></tr>
  <tr><td>True</td><td>X[]..[]</td><td>X[]..[]</td><td>None</td></tr>
  <tr><td>True</td><td>object[]</td><td>undef</td><td>None</td></tr>
  <tr><td>True</td><td>SUPER_CLASS_X[]..[]</td><td>CLASS_Y[]..[]</td><td>None</td></tr>
  <tr><td>True</td><td>INTERFACE_X[]..[]</td><td>INTERFACE_HAVING_Y[]..[]</td><td>None</td></tr>
  <tr><td>False</td><td>object[]</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

(C<[]..[]> means two or more C<[]>)

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

=head2 Type Castability

The castability at compile-time is explained.

Compilation Errors:

The castability is false, a compilation error occurs.

=head3 Type Castability to Numeric

The castability to the L<numeric types|/"Numeric Type"> is explained.

=head4 Type Castability from Numeric to Numeric

If the type of I<LEFT_OPERAND> is a L<numeric type|/"Numeric Type"> and the type of I<RIGHT_OPERAND> is a L<numeric type|/"Numeric Type">, the castability is true.

If the L<nemric type order|/"Numeric Type Order"> of I<LEFT_OPERAND> is greater than the L<nemric type order|/"Numeric Type Order"> of I<RIGHT_OPERAND>, the L<numeric widening conversion|/"Numeric Widening Conversion"> is performed.

If the L<nemric type order|/"Numeric Type Order"> of I<LEFT_OPERAND> is less than the L<nemric type order|/"Numeric Type Order"> of I<RIGHT_OPERAND>, the L<numeric narrowing conversion|/"Numeric Narrowing Conversion"> is performed.

If the L<nemric type order|/"Numeric Type Order"> of I<LEFT_OPERAND> is equal to the L<nemric type order|/"Numeric Type Order"> of I<RIGHT_OPERAND>, copying is performed.

=begin html

<table>
  <tr><th>Type Castability</th><th>To</th><th>From</th><th><a href="#Type-Conversion">Conversion or Type Checking</a></th></tr>
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

=head4 Type Castability from NumericObject to Numeric

If the type of I<LEFT_OPERAND> is a L<numeric type|/"Numeric Type"> corresponding to the numeric object type of I<RIGHT_OPERAND> and the type of I<RIGHT_OPERAND> is a L<numeric object type|/"Numeric Object Type">, the castability is true.

=begin html

<table>
  <tr><th>Type Castability</th><th>To</th><th>From</th><th><a href="#Type-Conversion">Conversion or Type Checking</a></th></tr>
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

=head4 Type Castability from Any Object to Numeric

If the type of I<LEFT_OPERAND> is a L<numeric type|/"Numeric Type"> and the type of I<RIGHT_OPERAND> is a L<any object type|/"Any Object Type"> C<object>, the castability is true.

The L<unboxing conversion|/"Unboxing Conversion"> corresponding to the numeric type is performed.

=begin html

<table>
  <tr><th>Type Castability</th><th>To</th><th>From</th><th><a href="#Type-Conversion">Conversion or Type Checking</a></th></tr>
  <tr><td>True</td><td>NUMERIC_X</td><td>object</td><td><a href="#Unboxing-Conversion">Unboxing Conversion</td></a></tr>
</table>

=end html

Examples:
  
  my $object : object = Int->new(3);
  my $int = (int)$object;
  
  my $object : object = Double->new(3.5);
  my $double = (double)$object;

=head4 Type Castability from Others to Numeric

If the type of I<LEFT_OPERAND> is a L<numeric type|/"Numeric Type"> and the type of I<RIGHT_OPERAND> is other than the types described above, the castability is false.

=head3 Type Castability to Multi-Numeric

If the type of I<LEFT_OPERAND> is a L<multi-numeric type|/"Multi-Numeric Type"> and the type of I<RIGHT_OPERAND> is the same type of I<LEFT_OPERAND>, the castability is true.

Otherwise, the castability is false.

=begin html

<table>
  <tr><th>Type Castability</th><th>To</th><th>From</th><th><a href="#Type-Conversion">Conversion or Type Checking</a></th></tr>
  <tr><td>True</td><td>MULNUM_X</td><td>MULNUM_X</td><td>None</td></tr>
  <tr><td>False</td><td>MULNUM_X</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

Examples:

  my $z1 : Complex_2d;
  my $z2 = (Complex_2d)$z1;

=head3 Type Castability to Referenece

If the type of I<LEFT_OPERAND> is a L<reference type|/"Reference Type"> and the type of I<RIGHT_OPERAND> is the same type of I<LEFT_OPERAND>, the castability is true.

Otherwise, the castability is false.

=begin html

<table>
  <tr><th>Type Castability</th><th>To</th><th>From</th><th><a href="#Type-Conversion">Conversion or Type Checking</a></th></tr>
  <tr><td>True</td><td>REF_X</td><td>REF_X</td><td>None</td></tr>
  <tr><td>False</td><td>REF_X</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

Examples:

  my $num : int = 5;
  my $num_ref = (int*)\num;

=head3 Type Castability to String

If the type of I<LEFT_OPERAND> is the L<string type|/"string Type"> and the type of I<RIGHT_OPERAND> is the L<string type|/"string Type">, the castability is true.

If the type of I<LEFT_OPERAND> is the L<string type|/"string Type"> with the L<mutable type qualifier|/"mutable Type Qualifier"> and the type of I<RIGHT_OPERAND> is the L<string type|/"string Type"> without the L<mutable type qualifier|/"mutable Type Qualifier">, the L<runtime type checking|/"Runtime Type Assignability"> is performed.

If the type of I<RIGHT_OPERAND> is a L<numeric type|/"Numeric Type">, the L<numeric-to-string conversion|/"Numeric-to-String Conversion"> is performed.

If the type of I<LEFT_OPERAND> is the L<string type|/"string Type"> and the type of I<RIGHT_OPERAND> is a L<numeric type|/"Numeric Type">, the L<undef type|/"undef Type">, or the L<any object type|/"Any Object Type"> C<object>, the castability is true.

If the type of I<RIGHT_OPERAND> is a L<numeric type|/"Numeric Type">, the L<numeric-to-string conversion|/"Numeric-to-String Conversion"> is performed.

If the type of I<LEFT_OPERAND> is the L<string type|/"string Type"> and the type of I<RIGHT_OPERAND> is the L<any object type|/"Any Object Type"> C<object>, the castability is true and the runtime type checking is performed.

=begin html

<table>
  <tr><th>Type Castability</th><th>To</th><th>From</th><th><a href="#Type-Conversion">Conversion or Type Checking</a></th></tr>
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
  my $num_string = (string)3;
  my $string : string = undef;

=head3 Type Castability to NumericObject

If the type of I<LEFT_OPERAND> is a L<numeric object type|/"Numeric Object Type"> and the types of I<RIGHT_OPERAND>s are the following cases:

If the type of I<RIGHT_OPERAND> is the same type of I<LEFT_OPERAND>, a L<numeric type|/"Numeric Type"> that is corresponding to the numeric object type, the L<any object type|/"Any Object Type"> C<object>, or the L<undef type|/"undef Type">, the castability is true.

The type of I<RIGHT_OPERAND> is other than above, the castability is false.

If the type of I<RIGHT_OPERAND> is a L<numeric type|/"Numeric Type">, the L<boxing conversion|/"Boxing Conversion"> is performed.

If the type of I<LEFT_OPERAND> is the type of I<RIGHT_OPERAND> is the L<any object type|/"Any Object Type"> C<object>, the L<runtime type checking|/"Runtime Type Assignability"> is performed.

=begin html

<table>
  <tr><th>Type Castability</th><th>To</th><th>From</th><th><a href="#Type-Conversion">Conversion or Type Checking</a></th></tr>
  <tr><td>True</td><td>NUMERIC_OBJECT_X</td><td>NUMERIC_OBJECT_X</td><td>None</td></tr>
  <tr><td>True</td><td>NUMERIC_OBJECT_X</td><td>NUMERIC_X</td><td><a href="#Boxing-Conversion">Boxing Conversion</td></a></tr>
  <tr><td>True</td><td>NUMERIC_OBJECT</td><td>object</td><td><a href="#Runtime-Type-Checking">Runtime type checking</a></td></tr>
  <tr><td>True</td><td>NUMERIC_OBJECT</td><td>undef</td><td>None</td></tr>
  <tr><td>False</td><td>NUMERIC_OBJECT</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

Examples:

  my $num_object = (Int)Int->new(3);
  my $num_object = (Int)3;
  my $num_object = (Int)undef;
  
  my $object : object = Int->new(3);
  my $num_object = (Int)$object;

=head3 Type Castability to Class

If the type of I<LEFT_OPERAND> is a L<class type|/"Class Type"> and the types of I<RIGHT_OPERAND>s are the following cases:

If the type of I<RIGHT_OPERAND> is the same type, the L<any object type|/"Any Object Type"> C<object>, an L<interface type|/"Interface Type"> or the L<undef type|/"undef Type">, the castability is true.

If the type of I<LEFT_OPERAND> is a super class of the type of right operand, the castability is true.

If the type of I<RIGHT_OPERAND> is a super class of the type of left operand, the castability is true.

Otherwise, the castability is false.

If the type of I<RIGHT_OPERAND> is the L<any object type|/"Any Object Type"> C<object> or an L<interface type|/"Interface Type">, the L<runtime type checking|/"Runtime Type Assignability"> is performed.

=begin html

<table>
  <tr><th>Type Castability</th><th>To</th><th>From</th><th><a href="#Type-Conversion">Conversion or Type Checking</a></th></tr>
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

=head3 Type Castability to Interface

If the type of I<LEFT_OPERAND> is an L<interface type|/"Interface Type">, and the types of I<RIGHT_OPERAND>s are the following cases:

If the type of I<RIGHT_OPERAND> is the same type, the L<any object type|/"Any Object Type"> C<object> , an L<interface type|/"Interface Type"> or the L<undef type|/"undef Type">, the castability is true.

If the type of I<RIGHT_OPERAND> is a L<class type|/"Class Type"> and the class has the interface of I<LEFT_OPERAND>, the castability is true.

Otherwise, the castability is false.

If the type of I<RIGHT_OPERAND> is the L<any object type|/"Any Object Type"> C<object>, an L<interface type|/"Interface Type">, the L<runtime type checking|/"Runtime Type Assignability"> is performed.

=begin html

<table>
  <tr><th>Type Castability</th><th>To</th><th>From</th><th><a href="#Type-Conversion">Conversion or Type Checking</a></th></tr>
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

=head3 Type Castability to Any Object

If the type of I<LEFT_OPERAND> is the L<any object type|/"Any Object Type"> and the types of I<RIGHT_OPERAND>s are the following cases:
 
If the type of I<RIGHT_OPERAND> is an L<object type|/"Object Type">, a L<numeric type|/"Numeric Type"> or the L<undef type|/"undef Type">, the castability is true.

Otherwise, the castability is false.

If the type of I<RIGHT_OPERAND> is a L<numeric type|/"Numeric Type">, the L<boxing conversion|/"Boxing Conversion"> is performed.

=begin html

<table>
  <tr><th>Type Castability</th><th>To</th><th>From</th><th><a href="#Type-Conversion">Conversion or Type Checking</a></th></tr>
  <tr><td>True</td><td>object</td><td>OBJECT_Y</td><td>None</td></tr>
  <tr><td>True</td><td>object</td><td>NUMERIC_X</td><td><a href="#Boxing-Conversion">Boxing Conversion</td></a></tr>
  <tr><td>True</td><td>object</td><td>undef</td><td>None</td></tr>
  <tr><td>False</td><td>object</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

Examples:

  my $object : object = Point->new;
  my $num_object : object = 3;
  my $object : object = undef;

=head3 Type Castability to Numeric Array

If the type of I<LEFT_OPERAND> is the L<byte[] type|/"byte[] Type"> and the type of I<RIGHT_OPERAND> is the L<string type|/"string Type">, the castability is true.

If the type of I<LEFT_OPERAND> is a L<numeric array type|/"Numeric Array Type"> and the types of I<RIGHT_OPERAND>s are the following cases:

If the type of I<RIGHT_OPERAND> is the same type of I<LEFT_OPERAND>, the L<any object type|/"Any Object Type"> C<obejct> or the L<undef type|/"undef Type">, the castability is true.

Otherwise, the castability is false.

If the type of I<LEFT_OPERAND> is the L<byte[] type|/"byte[] Type"> and the type of I<RIGHT_OPERAND> is the L<string type|/"string Type">, L<String-to-byte[] Conversion> is performed.

If the type of I<RIGHT_OPERAND> is the L<any object type|/"Any Object Type"> C<obejct>, the L<runtime type checking|/"Runtime Type Assignability"> is performed.

=begin html

<table>
  <tr><th>Type Castability</th><th>To</th><th>From</th><th><a href="#Type-Conversion">Conversion or Type Checking</a></th></tr>
  <tr><td>True</td><td>byte[]</td><td>string</td><td><a href="#String-to-byte[]-Type-Conversion">String-to-byte[] Conversion</a></td></tr>
  <tr><td>True</td><td>NUMERIC_X[]</td><td>NUMERIC_X[]</td><td>None</td></tr>
  <tr><td>True</td><td>NUMERIC[]</td><td>object</td><td><a href="#Runtime-Type-Checking">Runtime type checking</a></td></tr>
  <tr><td>True</td><td>NUMERIC[]</td><td>undef</td><td>None</td></tr>
  <tr><td>False</td><td>NUMERIC[]</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

Examples:
  
  my $bytes = (byte[])"abc";
  
  my $nums = (int[])new int[3];
  
  my $object : object = new int[3];
  my $nums = (int[])$object;
  
  my $nums = (int[])undef;

=head3 Type Castability to Multi-Numeric Array

If the type of I<LEFT_OPERAND> is a L<multi-numeric array type|/"Multi-Numeric Array Type"> and the types of I<RIGHT_OPERAND>s are the following cases:
 
If the type of I<RIGHT_OPERAND> is the same type of I<LEFT_OPERAND>, the L<any object type|/"Any Object Type"> C<obejct> or the L<undef type|/"undef Type">, the castability is true.

Otherwise, the castability is false.

If the type of I<RIGHT_OPERAND> is the L<any object type|/"Any Object Type"> C<obejct>, the L<runtime type checking|/"Runtime Type Assignability"> is performed.

=begin html

<table>
  <tr><th>Type Castability</th><th>To</th><th>From</th><th><a href="#Type-Conversion">Conversion or Type Checking</a></th></tr>
  <tr><td>True</td><td>MULNUM_X[]</td><td>MULNUM_X[]</td><td>None</td></tr>
  <tr><td>True</td><td>MULNUM_X[]</td><td>object</td><td><a href="#Runtime-Type-Checking">Runtime type checking</a></td></tr>
  <tr><td>True</td><td>MULNUM_X[]</td><td>undef</td><td>None</td></tr>
  <tr><td>False</td><td>MULNUM_X[]</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

Examples:

  my $nums = (Complex_2d[])new Complex_2d[3];

  my $object : object = new Complex_2d[3];
  my $nums = (Complex_2d[])$object;

  my $nums = (Complex_2d[])undef;

=head3 Type Castability to String Array

If the type of I<LEFT_OPERAND> is a L<string array type|/"String Array Type"> and the types of I<RIGHT_OPERAND>s are the following cases:
 
If the type of I<RIGHT_OPERAND> is the same type of I<LEFT_OPERAND>, the L<any object type|/"Any Object Type"> C<obejct>, the L<any object array type|/"Any Object Array Type"> C<obejct[]> or the L<undef type|/"undef Type">, the castability is true.

Otherwise, the castability is false.

If the type of I<RIGHT_OPERAND> is the L<any object type|/"Any Object Type"> C<obejct>, or the L<any object array type|/"Any Object Array Type"> C<obejct[]>, the L<runtime type checking|/"Runtime Type Assignability"> is performed.

=begin html

<table>
  <tr><th>Type Castability</th><th>To</th><th>From</th><th><a href="#Type-Conversion">Conversion or Type Checking</a></th></tr>
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

=head3 Type Castability to Class Array

If the type of I<LEFT_OPERAND> is a L<class array type|/"Class Array Type"> and the types of I<RIGHT_OPERAND>s are the following cases:

If the L<basic type|/"Basic Type"> of I<LEFT_OPERAND> is a super class of the L<basic type|/"Basic Type"> of I<RIGHT_OPERAND>, the castability is true.

If the L<basic type|/"Basic Type"> of I<RIGHT_OPERAND> is a super class of the L<basic type|/"Basic Type"> of I<LEFT_OPERAND>, the castability is true.

If the type of I<RIGHT_OPERAND> is the same type of I<LEFT_OPERAND>, the L<any object type|/"Any Object Type"> C<obejct>, the L<any object array type|/"Any Object Array Type"> C<obejct[]> or the L<undef type|/"undef Type">, the castability is true.

Otherwise, the castability is false.

If the type of I<RIGHT_OPERAND> is the L<any object type|/"Any Object Type"> C<obejct>, or the L<any object array type|/"Any Object Array Type"> C<obejct[]>, the L<runtime type checking|/"Runtime Type Assignability"> is performed.

=begin html

<table>
  <tr><th>Type Castability</th><th>To</th><th>From</th><th><a href="#Type-Conversion">Conversion or Type Checking</a></th></tr>
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

=head3 Type Castability to Interface Array

If the type of I<LEFT_OPERAND> is an L<interface array type|/"Interface Array Type"> and the types of I<RIGHT_OPERAND>s are the following cases:

If the type of I<RIGHT_OPERAND> is a L<class array type|/"Class Array Type"> and its L<basic type|/"Basic Type"> has the interface of the basic type of I<LEFT_OPERAND>, the castability is true.

If the type of I<RIGHT_OPERAND> is the same type of I<LEFT_OPERAND>, the castability is true.

If the type of I<RIGHT_OPERAND> is an differnt type of L<interface array type|/"Interface Array Type">, the castability is also true.

If the type of I<RIGHT_OPERAND> is the L<any object type|/"Any Object Type"> C<obejct>, the L<any object array type|/"Any Object Array Type"> C<obejct[]>  or the L<undef type|/"undef Type">, the castability is true.

Otherwise, the castability is false.

If the type of I<RIGHT_OPERAND> is an differnt type of  L<interface array type|/"Interface Array Type">, the L<runtime type checking|/"Runtime Type Assignability"> is performed.

If the type of I<RIGHT_OPERAND> is the L<any object type|/"Any Object Type"> C<obejct>, or the L<any object array type|/"Any Object Array Type"> C<obejct[]>, the L<runtime type checking|/"Runtime Type Assignability"> is performed.

=begin html

<table>
  <tr><th>Type Castability</th><th>To</th><th>From</th><th><a href="#Type-Conversion">Conversion or Type Checking</a></th></tr>
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

=head3 Type Castability to Any Object Array

If the type of I<LEFT_OPERAND> is the L<any object array type|/"Any Object Array Type"> C<object[]> and the types of I<RIGHT_OPERAND>s are the following cases:

If the type of I<RIGHT_OPERAND> is an L<object array type|/"Object Array Type"> or the L<undef type|/"undef Type">, the castability is true.

If the type of I<RIGHT_OPERAND> is an L<any object type|/"Any Object Type">, the castability is true.

Otherwise, the castability is false.

If the type of I<RIGHT_OPERAND> is an L<any object type|/"Any Object Type">, the L<runtime type checking|/"Runtime Type Assignability"> is performed.

=begin html

<table>
  <tr><th>Type Castability</th><th>To</th><th>From</th><th><a href="#Type-Conversion">Conversion or Type Checking</a></th></tr>
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
  
=head3 Type Castability to Multi-Dimensional Array

If the type of I<LEFT_OPERAND> is a L<multi-dimensional array type|/"Multi-Dimensional Array Type"> and  and the types of I<RIGHT_OPERAND>s are the following cases:

If the type of I<RIGHT_OPERAND> is the same type of I<LEFT_OPERAND> or the L<undef type|/"undef Type">, the castability is true.

If the type of I<RIGHT_OPERAND> is an L<any object type|/"Any Object Type">, the castability is true.

If the type dimesion of I<LEFT_OPERAND> is equal to the type dimension of I<RIGHT_OPERAND>, and the L<basic type|/"Basic Type"> of I<LEFT_OPERAND> is a super class of the L<basic type|/"Basic Type"> of I<RIGHT_OPERAND>, the castability is true.

If the type dimesion of I<LEFT_OPERAND> is equal to the type dimension of I<RIGHT_OPERAND>, and the L<basic type|/"Basic Type"> of I<RIGHT_OPERAND> is a super class of the L<basic type|/"Basic Type"> of I<LEFT_OPERAND>, the castability is true.

If the L<basic type|/"Basic Type"> of the type of I<LEFT_OPERAND> is an L<interface type|/"Interface Type"> and the L<basic type|/"Basic Type"> of the type of I<RIGHT_OPERAND> is a L<class type|/"Class Type"> and the dimension of the type of I<RIGHT_OPERAND> is the same as the dimension of the type left oerand and the L<basic type|/"Basic Type"> of the type of I<RIGHT_OPERAND> has the interface of the L<basic type|/"Basic Type"> of the type of I<LEFT_OPERAND> , the castability is true.

Otherwise, the castability is false.

=begin html

<table>
  <tr><th>Type Castability</th><th>To</th><th>From</th><th><a href="#Type-Conversion">Conversion or Type Checking</a></th></tr>
  <tr><td>True</td><td>ANY_X[]..[]</td><td>ANY_X[]..[]</td><td>None</td></tr>
  <tr><td>True</td><td>ANY_X[]..[]</td><td>object</td><td><a href="#Runtime-Type-Checking">Runtime type checking</a></td></tr>
  <tr><td>True</td><td>ANY_X[]..[]</td><td>object[]</td><td><a href="#Runtime-Type-Checking">Runtime type checking</a></td></tr>
  <tr><td>True</td><td>ANY_X[]..[]</td><td>undef</td><td>None</td></tr>
  <tr><td>True</td><td>SUPER_CLASS_X[]..[]</td><td>CLASS_Y[]..[]</td><td>None</td></tr>
  <tr><td>True</td><td>CLASS_X[]..[]</td><td>SUPER_CLASS_Y[]..[]</td><td><a href="#Runtime-Type-Checking">Runtime type checking</a></td></tr>
  <tr><td>True</td><td>INTERFACE_X[]..[]</td><td>INTERFACE_HAVING_Y[]..[]</td><td>None</td></tr>
  <tr><td>False</td><td>object[]</td><td>OTHER</td><td>None</td></tr>
</table>

=end html

(C<[]..[]> means two or more C<[]>)

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

=head2 Type Conversion

Type conversion is explained.

=head3 Explicite Type Conversion

The explicite type conversion is the L<type conversion|/"Type Conversion"> performed by a L<type cast|/"Type Cast"> expicitely.

Examples:
  
  # The explicte type conversion from long to int 
  my $num = (int)123L;
  
  # The explicte type conversion from byte[] to string
  my $num = (string)new byte[3];
  
  # The explicte type conversion from string to byte[]
  my $num = (byte[])"Hello";

=head3 Implicite Type Conversion

The implicite type conversion is the L<type conversion|/"Type Conversion"> performed implicitly when a value is assigned using L<assignment operator|/"Assignment Operator">, pass an argument to a method using a L<method call|/"Method Call">, or set a return value using the L<return statement|/"return Statement">.

See L<"Type Assignability"> if you know when implicite type conversion is performed.

Examples:
  
  # The implicite type conversion from int to double 
  my $num : double = 5;
  
  # The implicite type conversion from double to Double
  my $num_object : Double = 5.1;
  
  # The implicite type conversion from Double to double
  my $num : double = Double->new(5.1);
  
  # The implicite type conversion from int to string
  my $string : string = 4;

=head3 Integer Promotional Conversion

The integer promotional conversion is a L<type conversion|"Type Conversion"> to convert an L<integer type within int|/"Integer Type Within int"> to the int type using the L<numeric widening conversion|/"Numeric Widening Conversion">.

=head3 Numeric Widening Conversion

The numeric widening conversion is a L<type conversion|"Type Conversion"> from a small-order L<numeric type|/"Numeric Type"> to a large-order L<numeric type|/"Numeric Type">.

See also L<numeric types order|/"Numeric Type Order"> abount the order of numeric type.

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

The numeric widening conversion is performed in some of the L<type casts|/"Type Cast">, the index of the L<array access|/"The array Access">, the length of the L<creating array|/"Creating Array">, I<OPERAND> of the L<unary plus operator|/"Unary Plus Operator">, I<OPERAND> of the L<unary minus operator|/"Unary Minus Operator">, and the left and right operands of the L<shift operators|"Shift Operator">.

=head3 Numeric Narrowing Conversion

The numeric narrowing conversion is a L<conversion|"Type Conversion"> from a wide L<numeric type|/"Numeric Type"> to a narrow L<numeric type|/"Numeric Type">.

See also L<numeric types order|/"Numeric Type Order"> abount the order of numeric type.

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

=head3 Binary Numeric Conversion

The binary numeric conversion is a L<type conversion|/"Type Conversion"> to upgrade the type of I<LEFT_OPERAND> or I<RIGHT_OPERAND> of the binary operator that operands are L<numeric types|/"Numeric Type">.

The following rules apply in order.

1. If I<LEFT_OPERAND> or I<RIGHT_OPERAND> is the L<double type|/"double Type">, I<OPERAND> of the small type is converted to the big type using the L<numeric widening conversion|/"Numeric Widening Conversion">.

2. If I<LEFT_OPERAND> or I<RIGHT_OPERAND> is the L<float type|/"float Type">, I<OPERAND> of the small type is converted to the big type using the L<numeric widening conversion|/"Numeric Widening Conversion">.

3. If I<LEFT_OPERAND> or I<RIGHT_OPERAND> is the long type, I<OPERAND> of the small type is converted to the big type using the L<numeric widening conversion|/"Numeric Widening Conversion">.

4, Otherwise, both I<LEFT_OPERAND> and I<RIGHT_OPERAND> are converted to the int type using the L<numeric widening conversion|/"Numeric Widening Conversion">.

=head3 Numeric-to-String Conversion

The numeric-to-string conversion is a L<type conversion|/"Type Conversion"> from a L<numeric type|/"Numeric Type"> to the L<string type|/"string Type">.

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

=head3 String-to-byte[] Conversion

The String-to-byte[] conversion is a L<type conversion|/"Type Conversion"> from the L<string Type|/"string Type"> to L</"byte[] Type">.

  # The String-to-byte[] conversion
  my $string : string = "Hello";
  my $bytes : byte[] = (byte[])$string;

A new byte[] object is created and all characters in the string are copied to the elements of byte[] object.

=head3 byte[]-to-string Conversion

The byte[]-to-string conversion is a L<type conversion|/"Type Conversion"> from the L<byte[] type|/"byte[] type"> to the L<string Type|/"string Type">.

  # byte[]-to-string conversion
  my $bytes : byte[] = new byte[3];
  $bytes->[0] = 'a';
  $bytes->[1] = 'b';
  $bytes->[2] = 'c';
  my $string : string = (string)$bytes;

A new string is created and all elements in the C<byte[]> object are copied to the characters of the string.

=head3 Boxing Conversion

The boxing conversion is a L<type coversion|/"Type Conversion"> to convert the value of L<numeric type|/"Numeric Type"> to the corresponding L<numeric object type|/"Numeric Object Type">.

=head3 Unboxing Conversion

The unboxing conversion is a L<type coversion|/"Type Conversion"> to convert the value of the L<numeric object type|/"Numeric Object Type"> to the value of the corresponding L<numeric type|/"Numeric Type">.

=head3 Boolean Conversion

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

If the type is an L<integer type within int|/"Integer Type Within int">, the L<integer promotional conversion|/"Integer Promotional Conversion"> is performed on I<OPERAND>.

And the following operation in the C language is performed on I<OPERAND> .

  !!OPERAND

Compilation Errors:

The type of I<OPERAND> of the boolean conversion must be a L<numeric type|/"Numeric Type">, an L<object type|/"Object Type"> or an L<reference type|/"Reference Type"> or the L<undef type|/"undef Type">. Otherwise a compilation error occurs.

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

=head2 Runtime Type Assignability

The runtime type cheking is the type cheking that is performed at runtime.

The L<type cast|/"Type Cast"> operators that operand is an L<object type|/"object Type"> performe the runtime type checking by the rule of the runtime type assignability.

The runtime assignability is the assignability at runtime.

The L<isa operator|/"isa Operator"> checks the L<runtime assignability/"Runtime Type Assignability">

The runtime assignability is false, an exception is thrown.

If the type of the distribution is an L<object type|/"Object Type"> and the type of the source is L<undef|/"undef Type">, the runtime assignability is true.

If the type of the distribution is the same as the type of the source, the runtime assignability is true.

If the type of the distribution is the L<any object type|/"Any Object Type"> C<object> and the type of the source is an L<object type|/"Object Type">, the runtime assignability is true.

If the type of the distribution is the L<any object array type|/"Any Object Array Type"> C<object[]> and the type of the source is an L<object array type|/"Object Array Type">, the runtime assignability is true.

If the type of distribution is an L<class type|/"Class Type">, an L<class array type|/"Class Array Type">, an L<class multi-dimensional array type|/"Class Multi-Dumensional Array Type"> and the dimention of the type of the distribution is the same as the dimention of the type of the source and the basic type of distribution is a super class of the basic type of the source, the runtime assignability is true.

If the type of distribution is an L<interface type|/"Interface Type">, an L<interface array type|/"Interface Array Type">, an L<interface multi-dimensional array type|/"Interface Multi-Dumensional Array Type"> and the dimention of the type of the distribution is the same as the dimention of the type of the source and the basic type of distribution has the interface of the basic type of the source, the runtime assignability is true.

=begin html

<table>
  <tr><th>Runtime Type Assignability</th><th>To</th><th>From</th></tr>
  <tr><td>True</td><td>OBJECT_X</td><td>undef</td></tr>
  <tr><td>True</td><td>OBJECT_X</td><td>OBJECT_X</td></tr>
  <tr><td>True</td><td>object</td><td>OBJECT_Y</td></tr>
  <tr><td>True</td><td>object[]</td><td>OBJECT_ARRAY_Y</td></tr>
  <tr><td>True</td><td>SUPER_CLASS_X</td><td>CLASS_Y</td></tr>
  <tr><td>True</td><td>SUPER_CLASS_X[]</td><td>CLASS_Y[]</td></tr>
  <tr><td>True</td><td>SUPER_CLASS_X[]..[]</td><td>CLASS_Y[]..[]</td></tr>
  <tr><td>True</td><td>INTERFACE_X</td><td>INTERFACE_HAVING_Y</td></tr>
  <tr><td>True</td><td>INTERFACE_X[]</td><td>INTERFACE_HAVING_Y[]</td></tr>
  <tr><td>True</td><td>INTERFACE_X[]..[]</td><td>INTERFACE_HAVING_Y[]..[]</td></tr>
  <tr><td>False</td><td>OBJECT_X</td><td>OTHER</td></tr>
</table>

=end html

(C<[]..[]> means two or more C<[]>)

=head2 Type Comment

The type comment syntax is supported. The type comment can be written after C<of> keyword.

  TYPE of TYPE
  TYPE of TYPE1|TYPE2
  TYPE of TYPE1|TYPE2|TYPE3

The type comment can be used the type of the L<field decralation|/"Field Definition">, the L<class variable definition|/"Class Variable Definition">, the L<local variable declaration|/"Local Variable Declaration">, and the return value and the types of arguments of the L<method definition|/"Method Definition">.

  has points : List of Point;
  
  our $POINTS : List of Point;
  
  my $points : List of Point;
  
  static method foo : List of Point ($arg : List of Point) { ... }
  
  my $replace : object of string|Regex::Replacer;

Type comments have no meanings at runtime.

Compilation Errors:

If the type specified as the type comment is not found, a compilation error occurs.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
