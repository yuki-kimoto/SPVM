=head1 Name

SPVM::Document::Language::Types - Types in the SPVM Language

=head1 Description

This document describes types in the SPVM language.

=head1 Data

This section describes data.

A data is called value.

=head2 Number

The value of L<numeric types|/"Numeric Types"> is called number.

Normally, numbers are created by L<numeric literals|SPVM::Document::Language::Tokenization/"Numeric Literals">.

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

A character created by L<character literal|SPVM::Document::Language::Tokenization/"Character Literal"> is a number of byte type.
  
  # A number of byte type created by a character literal
  my $char = 'a';

See the following section operations for numbers.

=over

=item * L<Numeric Operators|SPVM::Document::Language::Operators/"Numeric Operators">

=item * L<Numeric Comparison Operators|SPVM::Document::Language::Operators/"Numeric Comparison Operators">

=back

=head3 Internal Representation of Negative Integers

Negative integers are represented by L<two's complement|https://en.wikipedia.org/wiki/Two%27s_complement>.

=head2 String

The value of L<string type|/"string Type"> is called string.

A string consists of characters of the C<byte> type.

A string has its length.

A string is an L<object|/"Object">.

Normally, a string is created by a L<string literal|SPVM::Document::Language::Tokenization/"String Literal"> or L<new_string_len operator|SPVM::Document::Language::Operators/"new_string_len Operator">.
  
  # A string created by a string literal
  my $string = "Hello";
  my $char = $string->[0];
  
  # A mutable string created by new_string_len operator
  my $string = new_string_len 3;
  $string->[0] = 'a';

See the following sections about operations for strings.

=over 2

=item * L<length Operator|SPVM::Document::Language::Operators/"length Operator">

=item * L<String Concatenation Operator|SPVM::Document::Language::Operators/"String Concatenation Operator">

=item * L<Character Get Operation|SPVM::Document::Language::Operators/"Character Get Operation">

=item * L<Character Set Operation|SPVM::Document::Language::Operators/"Character Set Operation">

=item * L<new_string_len Operator|SPVM::Document::Language::Operators/"new_string_len Operator">

=item * L<make_read_only Operator|SPVM::Document::Language::Operators/"make_read_only Operator">

=item * L<is_read_only Operator|SPVM::Document::Language::Operators/"is_read_only Operator">

=item * L<String Comparison Operators|SPVM::Document::Language::Operators/"String Comparison Operators">

=item * L<copy Operator|SPVM::Document::Language::Operators/"copy Operator">

=back

=head3 Sting Native Level Representation

At L<native level|SPVM::Document::NativeClass>, the character just after the last character of the string is set to C<\0>, so the characters in the string can be used as a C language string.

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

Normally, an array is created by L<new Operator|SPVM::Document::Language::Operators/"Creating an Array"> and an L<array initialization|SPVM::Document::Language::Operators/"Array Initialization">.
  
  # An array created by new operator
  my $numbers = new int[3];
  $numbergers->[0] = 1;
  
  my $strings = new string[3];
  
  my $objects = new Point[3];
  
  my $mulnum_numbers = new Complex_2d[3];
  
  # An array created by an array initialization
  my $numbers = [1, 2, 3];

All elements of an array can be got by L<for statement|SPVM::Document::Language::Statements/"for Statement">.

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

=item * L<Array Element Get Operation|SPVM::Document::Language::Operators/"Array Element Get Operation">

=item * L<Array Element Set Operation|SPVM::Document::Language::Operators/"Array Element Set Operation">

=back

=head2 Object

The value of an L<object type|/"Object Types"> is called object.

A L<string|/"String"> is an object.

An L<array|/"Array"> is an object.

An objcet of L<class type|/"Class Types"> has its fields. A field is a L<number|/"Number"> or an L<object|/"Object">.

Normally, an object is created by L<new|SPVM::Document::Language::Operators/"new"> operator.

  # An object created by new operator
  my $point = new Point;

When an object is created, memory for the object is allocated in heap memory.

Created objects are destroyed by L<garbage collection|SPVM::Document::Language::GarbageCollection>.

See the following sections about operations for objects.

=over 2

=item * L<new Operator|SPVM::Document::Language::Operators/"new Operator">

=item * L<dump Operator|SPVM::Document::Language::Operators/"dump Operator">

=item * L<Field Get Operation|SPVM::Document::Language::Operators/"Field Get Operation">

=item * L<Field Set Operation|SPVM::Document::Language::Operators/"Field Set Operation">

=item * L<isa Operator|SPVM::Document::Language::Operators/"isa Operator">

=item * L<is_type Operator|SPVM::Document::Language::Operators/"is_type Operator">

=item * L<type_name Operator|SPVM::Document::Language::Operators/"type_name Operator">

=back

=head3 Object Native Level Representation

At L<native level|SPVM::Document::NativeClass>, an object is a memory address.

  void* obj_point = stack[0].oval;

=head2 Undefined Value

The value of L<undef type|/"undef Type"> is called undefined value.

An undefined value means the value is undefined.

An undefined value is created by L<undef|SPVM::Document::Language::Operators/"undef Operator"> operator.

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

=item * L<Multi-Numeric Field Get Operation|SPVM::Document::Language::Operators/"Multi-Numeric Field Get Operation">

=item * L<Multi-Numeric Field Set Operation|SPVM::Document::Language::Operators/"Multi-Numeric Field Set Operation">

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

=item * L<Referenced Value Get Operation|SPVM::Document::Language::Operators/"Referenced Value Get Operation">

=item * L<Referenced Value Set Operation|SPVM::Document::Language::Operators/"Referenced Value Set Operation">

=item * L<Reference Operator|SPVM::Document::Language::Operators/"Reference Operator">

=item * L<Dereference Operator|SPVM::Document::Language::Operators/"Dereference Operator">

=item * L<Referenced Multi-Numeric Field Get Operation|SPVM::Document::Language::Operators/"Referenced Multi-Numeric Field Get Operation">

=item * L<Referenced Multi-Numeric Field Set Operation|SPVM::Document::Language::Operators/"Referenced Multi-Numeric Field Set Operation">

=back

=head3 Reference Native Level Representation

At L<native level|SPVM::Document::NativeClass>, a reference is a memory address.

  int32_t* num_ref = stack[0].iref;

=head1 Types

This section describes types.

=head2 Numeric Types

This section describes numeric types.

=head3 Integer Types

This section describes integer types.

An interger type is a L<numeric type|/"Numeric Types">.

=head4 byte Type

The C<byte> type is the type for a signed 8-bit integer.

  byte

The C<byte> type is an L<integer type|/"Integer Types">.

=head4 short Type

The C<short> type is the type for a signed 16-bit integer.

  short

The C<short> type is an L<integer type|/"Integer Types">.

=head4 int Type

The C<int> type is the type for a signed 32-bit integer.

  int

The C<int> type is an L<integer type|/"Integer Types">.

=head4 long Type

The C<long> type is the type for a signed 64-bit integer.

  long

The C<long> type is an L<integer type|/"Integer Types">.

=head3 Floating Point Types

This section describes floating point types.

A floating point type is a L<numeric type|/"Numeric Types">.

=head4 float Type

The C<float> type is the type for 32bit floating point.

  float

The C<float> type is a L<floating point type|/"Floating Point Types">.

=head4 double Type

The C<double> type is the type for 64bit floating point.

  double

The C<double> type is a L<floating point type|/"Floating Point Types">.

=head3 Numeric Types Order

L<numeric types|/"Numeric Types"> have its order.

The order is C<byte>, C<short>, C<int>, C<long>, C<float>, C<double> from smallest to largest.

=head2 Object Types

This section lists object types.

=head3 string Type

The C<string> type is the type for L<strings|/"String">.

  string

The C<string> type is an L<object type|/"Object Types">.

The C<string> type can be qualified with L<mutable type qualifier|/"mutable Type Qualifier">.

  mutable string

=head3 Class Types

A class type is the type for a L<class|SPVM::Document::Language::Class/"Class">.

A class type is defined by L<class definition|SPVM::Document::Language::Class/"Class Definition">.

  class CLASS_TYPE {
  
  }

An object can be created from a class by a L<new operator|SPVM::Document::Language::Operators/"new Operator">.

Note that an L<interface type|/"Interface Types"> and a L<multi-numeric type|/"Multi-Numeric Types"> is not a class type although these types are defined by L<class definition|SPVM::Document::Language::Class/"Class Definition">.

=head4 Numeric Object Types

A numeric object type is a L<class type|/"Class Types"> that owns the corresponding field of a L<numeric type|/"Numeric Types">.

The List of Numeric Object Types:

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

=head3 Interface Types

An interface type is a type for an L<interface|SPVM::Document::Language::Class/"Interface">.

An interface type is defined by an L<interface definition|SPVM::Document::Language::Class/"Interface Definition">.

  class INTERFACE_TYPE : interface_t {
    
  }

=head3 Any Object Type

Any object type C<object> is the type to which any L<object type|/"Object Types"> can be assigned.

  object

Examples:

  # Examples of any object type
  my $object: object = new Foo;

=head2 Basic Types

A basic type is a type whose type dimension is 0 and that can be an element of an array.

The List of Basic Types:

=over 2

=item * L<Numeric types|/"Numeric Types">

=item * L<Multi-numeric types|/"Multi-Numeric Types">

=item * L<Class types|/"Class Types">

=item * L<Interface types|/"Interface Types">

=item * L<any object type|/"Any Object Type">

=item * L<string type|/"string Type">

=back

=head2 undef Type

The undef type is the type of an L<undefined value|/"Undefined Value">.

=head2 void Type

The C<void> type is the type that represents a method defined by a L<method definition|SPVM::Document::Language::Class/"Method Definition"> does not return a return value.

  void

=head2 Array Types

An array type is a type for an L<array|/"Array">. An array type consists of a L<basic type|/"Basic Types"> and a type dimension such as C<[]>, C<[][]>.

  BASIC_TYPE[]..

(C<[]..> means one more C<[]>)

Examples:

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

An array type is an L<object type|/"Object Types">.

Compilation Errors:

The dimesion is less than or equal to 255. Otherwise, a compilation error occurs.

=head3 Numeric Array Types

A numeric array type is an L<array type|/"Array Types"> of a L<numeric type|/"Numeric Types">.

The List of Numeric Array Types:

  byte[]
  short[]
  int[]
  long[]
  float[]
  double[]

=head3 Object Array Types

An object array type is an L<array type|/"Array Types"> of an L<object type|/"Object Types">.

Examples:

  Point[]
  Point[][]
  Stringable[]
  string[]
  object[]

=head3 String Array Type

The string array type is L<array type|/"Array Types"> L<string type|/"string Type">.

  string[]

=head3 Class Array Types

A class array type is an L<array type|/"Array Types"> of a L<class type|/"Class Types">.

Examples:
  
  Int[]
  Point[]

=head3 Interface Array Types

An interface array type is an L<array type|/"Array Types"> of an L<interface type|/"Interface Types">.

Examples:

  Stringable[]
  Cloneable[]

=head3 Multi-Dimensional Array Types

A multi-dimensional array type is an L<array type|/"Array Types"> of an L<array type|/"Array Types">.

Examples:

  int[][]
  Int[][]
  string[][][]
  object[][]

A multi-dimensional array is created by the syntax of L<creating a multi-dimensional array|SPVM::Document::Language::Operators/"Creating a Multi-Dimensional Array"> of the C<new> operator.

=head3 Multi-Numeric Array Types

A multi-numeric array type is an L<array type|/"Array Types"> of a L<multi-numeric type|"Multi-Numeric Types">.

Examples:

  Complex_2d[]
  Complex_2f[]

=head3 Any Object Array Type

The any object array type C<object[]> is L<array type|/"Array Types"> to which any L<object array type|/"Object Array Types"> can be assigned.

  object[]

=head2 Multi-Numeric Types

A multi-numeric type is a type for a L<multi-numeric number|/"Multi-Numeric Number">.

A multi-numeric type is defined by a L<multi-numeric type definition|SPVM::Document::Language::Class/"Multi-Numeric Type Definition">.

  class MULNUM_TYPE : mulnum_t {
    
  }

=head2 Reference Types

A reference type is a type for a L<reference|/"Reference">.

  TYPE*

A reference type consists of a type followed by C<*>.

I<TYPE> must be a L<numeric type|/"Numeric Types"> or a L<multi-numeric type|/"Multi-Numeric Types">.

=head3 Numeric Reference Types

A numeric reference type is a reference type of a L<numeric type|/"Numeric Types">.

The List of Numeric Reference Types:

  byte*
  short*
  int*
  long*
  float*
  double*

=head3 Multi-Numeric Reference Types

A multi-numeric reference types is a reference type of a L<multi-numeric type|/"Multi-Numeric Types">.

  MULNUM_TYPE*

Examples:

  Complex_2d*
  Complex_2f*

=head2 Type Qualifiers

A type qualifier qualify a type.

  QUALIFIER TYPE

The I<QUALIFIER> qualified the type I<TYPE>.

=head3 mutable Type Qualifier

The C<mutable> type qualifier qualifies string type.

  mutable string;

The string of string type with the C<mutable> type qualifier is able to be L<set a character|SPVM::Document::Language::Operators/"Character Set Operation">.

  my $string = (mutable string)copy "abc";
  $string->[0] = 'd';

=head2 Type Initial Value

The value of a type is initialized by its type initial value.

The List of Type Initial Values:

=begin html

<table>
  <tr>
    <th>
      <b>Types</b>
   </th>
    <th>
      Type Initial Values
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
      0 (All bits are 0)
    </td>
  </tr>
  <tr>
    <td>
      <b>double</b>
    </td>
    <td>
      0 (All bits are 0)
    </td>
  </tr>
  <tr>
    <td>
      <b><a href="#Object-Types">Object Types</a></b>
    </td>
    <td>
      undef
    </td>
  </tr>
  <tr>
    <td>
      <b><a href="#Multi-Numeric-Types">Multi-Numeric Types</a></b>
    </td>
    <td>
      All fields are set to 0 (All bits are 0)
    </td>
  </tr>
</table>

=end html

=head2 Type Width

The type width is the length of L<runtime stack|SPVM::Document::NativeClass/"Runtime Stack"> of the type.

If the type is a L<multi-numeric type|/"Multi-Numeric Types">, the type width is the length of the fields, owhterwise it is 1.

=head2 Union Type

A union type expresses the logical OR of types.

  TYPE1|TYPE2|TYPEn

A union type is treated as any object type C<object>.

Examples:

  my $union = (string|string[])undef;
  
  method : foo ($union : string|string[]) {
    
  }
  
=head2 Generic Type

The generic type is

  TYPE of ELEMENT_TYPE

I<TYPE> is a L<type|SPVM::Document::Language::Types/"Types">.

I<ELEMENT_TYPE> is a L<type|SPVM::Document::Language::Types/"Types">.

A generic type is treated as C<TYPE>. C<ELEMETN_TYPE> is ignored in compilation time type checks.

C<ELEMETN_TYPE> is only used for the type cast for C<element> type.

Examples:

  # Examples of generic types
  has points : List of Point;
  
  has hash_of_list_of_point : Hash of List of Point;
  
  our $POINTS : List of Point;
  
  my $points : List of Point;
  
  static method foo : List of Point ($arg : List of Point) { ... }
  
  my $replace : object of string|Regex::Replacer;

Compilation Errors:

If the type specified as the generic type is not found, a compilation error occurs.

=head2 element Type

The C<element> type is the type that represents a method defined by a L<method definition|SPVM::Document::Language::Class/"Method Definition"> return an element type of a L<generic type|/"Generic Type">.

  element

Examples:

  class MyList {
    
    has array : object[];
    
    static method new : MyList ($objects : object[]) {
      
      my $self = new MyList;
      
      $self->{array} = $objects;
      
      return $self;
    }
    
    method get : element ($index : int) {
      
      return $self->{array}->[$index];
      
    }
  }
  
  my $list = (MyList of string)MyList->new(["a", "b"]);
  
  # $elem is casted to string type implicitly becuase get method returns element type.
  my $elem = $list->get(0);

=head2 element[] Type

The C<element[]> type is the type that represents a method defined by a L<method definition|SPVM::Document::Language::Class/"Method Definition"> return an element type of a L<generic type|/"Generic Type">.

  element[]

Examples:

  class MyList {
    
    has array : object[];
    
    static method new : MyList ($objects : object[]) {
      
      my $self = new MyList;
      
      $self->{array} = $objects;
      
      return $self;
    }
    
    method get_array : element[] () {
      
      return $self->{array};
    }
  }
  
  my $list = (MyList of string)MyList->new(["a", "b"]);
  
  # $array is casted to string[] type implicitly becuase get_array method returns element[] type.
  my $array = $list->get_array;
  
=head1 Assignment Requirement

The assignment requirement is the requirement whether one type is able to be assigned to another type.

What does it mean to assign one type to another type?

Typically, it is sufficient to consider a case where a value of a type I<TYPE_FROM> is assigned to a variable of a type I<TYPE_TO>.

  my $value : TYPE_FROM;
  my $var : TYPE_TO = $value;

Abstracting this, type-to-type assignment is defined.

  TYPE_TO = TYPE_FROM

Note that this is a concept, not an actual syntax.

Some assinments perform a data conversion.

In the following description, the word "Type" is omitted when it is obvious.

=head2 Assignment Requirement to Numeric

=head3 Assignment Requirement from Numeric to Numeric

To Larger:

=begin html

<table>
  <tr><th>Assignment Requirement<br>Satisfaction</th><th>To</th><th>From</th><th>Data Conversion</th></tr>
  <tr><td>Yes</td><td>byte</td><td>byte</td><td>No</td></tr>
  <tr><td>Yes</td><td>short</td><td>short</td><td>No</td></tr>
  <tr><td>Yes</td><td>int</td><td>int</td><td>No</td></tr>
  <tr><td>Yes</td><td>long</td><td>long</td><td>No</td></tr>
  <tr><td>Yes</td><td>float</td><td>float</td><td>No</td></tr>
  <tr><td>Yes</td><td>double</td><td>double</td><td>No</td></tr>
  <tr><td>Yes</td><td>short</td><td>byte</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Numeric-Widening-Conversion">Numeric Widening Conversion</a></td></tr>
  <tr><td>Yes</td><td>int</td><td>byte</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Numeric-Widening-Conversion">Numeric Widening Conversion</a></td></tr>
  <tr><td>Yes</td><td>long</td><td>byte</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Numeric-Widening-Conversion">Numeric Widening Conversion</a></td></tr>
  <tr><td>Yes</td><td>float</td><td>byte</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Numeric-Widening-Conversion">Numeric Widening Conversion</a></td></tr>
  <tr><td>Yes</td><td>double</td><td>byte</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Numeric-Widening-Conversion">Numeric Widening Conversion</a></td></tr>
  <tr><td>Yes</td><td>int</td><td>short</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Numeric-Widening-Conversion">Numeric Widening Conversion</a></td></tr>
  <tr><td>Yes</td><td>long</td><td>short</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Numeric-Widening-Conversion">Numeric Widening Conversion</a></td></tr>
  <tr><td>Yes</td><td>float</td><td>short</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Numeric-Widening-Conversion">Numeric Widening Conversion</a></td></tr>
  <tr><td>Yes</td><td>double</td><td>short</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Numeric-Widening-Conversion">Numeric Widening Conversion</a></td></tr>
  <tr><td>Yes</td><td>long</td><td>int</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Numeric-Widening-Conversion">Numeric Widening Conversion</a></td></tr>
  <tr><td>Yes</td><td>float</td><td>int</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Numeric-Widening-Conversion">Numeric Widening Conversion</a></td></tr>
  <tr><td>Yes</td><td>double</td><td>int</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Numeric-Widening-Conversion">Numeric Widening Conversion</a></td></tr>
  <tr><td>Yes</td><td>float</td><td>long</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Numeric-Widening-Conversion">Numeric Widening Conversion</a></td></tr>
  <tr><td>Yes</td><td>double</td><td>long</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Numeric-Widening-Conversion">Numeric Widening Conversion</a></td></tr>
  <tr><td>Yes</td><td>double</td><td>float</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Numeric-Widening-Conversion">Numeric Widening Conversion</a></td></tr>
</table>

=end html

To Smaller:

=begin html

<table>
  <tr><th>Assignment Requirement<br>Satisfaction</th><th>To</th><th>From</th><th>Data Conversion</th></tr>
  <tr><td>Conditional Yes</td><td>byte</td><td>short</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Numeric-Narrowing-Conversion">Numeric Narrowing Conversion</a></td></tr>
  <tr><td>Conditional Yes</td><td>byte</td><td>int</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Numeric-Narrowing-Conversion">Numeric Narrowing Conversion</a></td></tr>
  <tr><td>Conditional Yes</td><td>byte</td><td>long</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Numeric-Narrowing-Conversion">Numeric Narrowing Conversion</a></td></tr>
  <tr><td>No</td><td>byte</td><td>float</td><td>No</td></tr>
  <tr><td>No</td><td>byte</td><td>double</td><td>No</td></tr>
  <tr><td>Conditional Yes</td><td>short</td><td>int</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Numeric-Narrowing-Conversion">Numeric Narrowing Conversion</a></td></tr>
  <tr><td>Conditional Yes</td><td>short</td><td>long</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Numeric-Narrowing-Conversion">Numeric Narrowing Conversion</a></td></tr>
  <tr><td>No</td><td>short</td><td>float</td><td>No</td></tr>
  <tr><td>No</td><td>short</td><td>double</td><td>No</td></tr>
  <tr><td>Conditional Yes</td><td>int</td><td>long</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Numeric-Narrowing-Conversion">Numeric Narrowing Conversion</a></td></tr>
  <tr><td>No</td><td>int</td><td>float</td><td>No</td></tr>
  <tr><td>No</td><td>int</td><td>double</td><td>No</td></tr>
  <tr><td>No</td><td>long</td><td>float</td><td>No</td></tr>
  <tr><td>No</td><td>long</td><td>double</td><td>No</td></tr>
  <tr><td>Conditional Yes</td><td>float</td><td>double</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Numeric-Narrowing-Conversion">Numeric Narrowing Conversion</a></td></td></tr>
</table>

=end html

"Conditional Yes" means the followings.

For Integral Types:

If the value of I<TYPE_FROM> is represented by an L<interger literal|SPVM::Document::Language::Tokenization/"Integer Literals"> and between the max and minimal value of the type of I<TYPE_TO>, Yes, otherwize No.

For Floating Point types:

If the value of I<TYPE_FROM> is represented by a L<floating point literal|SPVM::Document::Language::Tokenization/"Floating Point Literals">, Yes, otherwize No.

=head3 Assignment Requirement from NumericObject to Numeric

=begin html

<table>
  <tr><th>Assignment Requirement<br>Satisfaction</th><th>To</th><th>From</th><th>Data Conversion</th></tr>
  <tr><td>Yes</td><td>byte</td><td>Byte</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Unboxing-Conversion">Unboxing Conversion</a></td></tr>
  <tr><td>Yes</td><td>short</td><td>Short</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Unboxing-Conversion">Unboxing Conversion</a></td></tr>
  <tr><td>Yes</td><td>int</td><td>Int</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Unboxing-Conversion">Unboxing Conversion</a></td></tr>
  <tr><td>Yes</td><td>long</td><td>Long</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Unboxing-Conversion">Unboxing Conversion</a></td></tr>
  <tr><td>Yes</td><td>float</td><td>Float</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Unboxing-Conversion">Unboxing Conversion</a></td></tr>
  <tr><td>Yes</td><td>double</td><td>Double</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Unboxing-Conversion">Unboxing Conversion</a></td></tr>
</table>

=end html

=head3 Assignment Requirement from Any Object to Numeric

=begin html

<table>
  <tr><th>Assignment Requirement<br>Satisfaction</th><th>To</th><th>From</th><th>Data Conversion</th></tr>
  <tr><td>Yes</td><td>byte</td><td>Any Object <code>object</code></td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Unboxing-Conversion">Unboxing Conversion</a></td></tr>
  <tr><td>Yes</td><td>short</td><td>Any Object <code>object</code></td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Unboxing-Conversion">Unboxing Conversion</a></td></tr>
  <tr><td>Yes</td><td>int</td><td>Any Object <code>object</code></td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Unboxing-Conversion">Unboxing Conversion</a></td></tr>
  <tr><td>Yes</td><td>long</td><td>Any Object <code>object</code></td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Unboxing-Conversion">Unboxing Conversion</a></td></tr>
  <tr><td>Yes</td><td>float</td><td>Any Object <code>object</code></td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Unboxing-Conversion">Unboxing Conversion</a></td></tr>
  <tr><td>Yes</td><td>double</td><td>Any Object <code>object</code></td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Unboxing-Conversion">Unboxing Conversion</a></td></tr>
</table>

=end html

=head3 Assignment Requirement from Other to Numeric

=begin html

<table>
  <tr><th>Assignment Requirement<br>Satisfaction</th><th>To</th><th>From</th><th>Data Conversion</th></tr>
  <tr><td>No</td><td>NumericX</td><td>Other</td><td>No</a></tr>
</table>

=end html

I<NumericX> is a L<numeric type|"Numeric Types">.

=head2 Assignment Requirement to Multi-Numeric

=begin html

<table>
  <tr><th>Assignment Requirement<br>Satisfaction</th><th>To</th><th>From</th><th>Data Conversion</th></tr>
  <tr><td>Yes</td><td>Multi-NumericX</td><td>Multi-NumericX</td><td>No</td></tr>
  <tr><td>No</td><td>Multi-NumericX</td><td>Other</td><td>No</td></tr>
</table>

=end html

I<Multi-NumericX> is a L<multi-numeric type|/"Multi-Numeric Types">.

=head2 Assignment Requirement to Referenece

=begin html

<table>
  <tr><th>Assignment Requirement<br>Satisfaction</th><th>To</th><th>From</th><th>Data Conversion</th></tr>
  <tr><td>Yes</td><td>ReferenceX</td><td>ReferenceX</td><td>No</td></tr>
  <tr><td>Yes</td><td>ReferenceX</td><td>undef</td><td>No</td></tr>
  <tr><td>No</td><td>ReferenceX</td><td>Other</td><td>No</td></tr>
</table>

=end html

I<ReferenceX> is a L<reference type|/"Reference Types">.

=head2 Assignment Requirement to String

=begin html

<table>
  <tr><th>Assignment Requirement<br>Satisfaction</th><th>To</th><th>From</th><th>Data Conversion</th></tr>
  <tr><td>Yes</td><td>string</td><td>string</td><td>No</td></tr>
  <tr><td>Yes</td><td>string</td><td>mutable string</td><td>No</td></tr>
  <tr><td>Yes</td><td>mutable string</td><td>mutable string</td><td>No</td></tr>
  <tr><td>No</td><td>mutable string</td><td>string</td><td>No</td></tr>
  <tr><td>Yes</td><td>string</td><td>string</td><td>No</td></tr>
  <tr><td>Yes</td><td>string</td><td>NumericX</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Numeric-to-String-Conversion">Numeric-to-String Conversion</a></td></tr>
  <tr><td>Yes</td><td>string</td><td>undef</td><td>No</td></tr>
  <tr><td>No</td><td>string</td><td>Other</td><td>No</td></tr>
</table>

=end html

I<NumericX> is a L<numeric type|"Numeric Types">.

=head2 Assignment Requirement to NumericObject

=begin html

<table>
  <tr><th>Assignment Requirement<br>Satisfaction</th><th>To</th><th>From</th><th>Data Conversion</th></tr>
  <tr><td>Yes</td><td>NumericObjectX</td><td>NumericObjectX</td><td>No</td></tr>
  <tr><td>Yes</td><td>NumericObjectX</td><td>NumericX</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Boxing-Conversion">Boxing Conversion</a></td></tr>
  <tr><td>Yes</td><td>NumericObjectX</td><td>undef</td><td>No</td></tr>
  <tr><td>No</td><td>NumericObjectX</td><td>Other</td><td>No</td></tr>
</table>

=end html

I<NumericObjectX> is a L<numeric object type|"Numeric Object Types">.

I<NumericX> is a L<numeric type|"Numeric Types">.

=head2 Assignment Requirement to Class

=begin html

<table>
  <tr><th>Assignment Requirement<br>Satisfaction</th><th>To</th><th>From</th><th>Data Conversion</th></tr>
  <tr><td>Yes</td><td>ClassX</td><td>ClassX</td><td>No</td></tr>
  <tr><td>Yes</td><td>ClassX</td><td>undef</td><td>No</td></tr>
  <tr><td>Yes</td><td>SuperClassX</td><td>ClassX</td><td>No</td></tr>
  <tr><td>No</td><td>ClassX</td><td>Other</td><td>No</td></tr>
</table>

=end html

I<ClassX> is a L<class type|"Class Types">.

I<SuperClassX> is a super class of I<ClassX>.

=head2 Assignment Requirement to Interface

=begin html

<table>
  <tr><th>Assignment Requirement<br>Satisfaction</th><th>To</th><th>From</th><th>Data Conversion</th></tr>
  <tr><td>Yes</td><td>InterfaceX</td><td>InterfaceX</td><td>No</td></tr>
  <tr><td>Yes</td><td>InterfaceX</td><td>InterfaceSatisfiedX</td><td>No</td></tr>
  <tr><td>Yes</td><td>InterfaceX</td><td>undef</td><td>No</td></tr>
  <tr><td>No</td><td>InterfaceX</td><td>Other</td><td>No</td></tr>
</table>

=end html

I<InterfaceX> is a an L<interface type|"Interface Types">.

I<InterfaceSatisfiedX> is a L<class type|"Class Types"> or an L<interface type|"Interface Types"> that satisfied L<interface requirement|/"Interface Requirement"> of I<InterfaceX>.

=head2 Assignment Requirement to Any Object

=begin html

<table>
  <tr><th>Assignment Requirement<br>Satisfaction</th><th>To</th><th>From</th><th>Data Conversion</th></tr>
  <tr><td>Yes</td><td>Any Object <code>object</code></td><td>ObjectX</td><td>No</td></tr>
  <tr><td>Yes</td><td>Any Object <code>object</code></td><td>NumericX</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Boxing-Conversion">Boxing Conversion</a></td></tr>
  <tr><td>Yes</td><td>Any Object <code>object</code></td><td>undef</td><td>No</td></tr>
  <tr><td>Yes</td><td>Any Object <code>object</code></td><td>void</td><td>No</td></tr>
  <tr><td>No</td><td>Any Object <code>object</code></td><td>Other</td><td>No</td></tr>
</table>

=end html

I<ObjectX> is an L<object type|"Object Types">.

I<NumericX> is a L<numeric type|"Numeric Types">.

=head2 Assignment Requirement to undef

=begin html

<table>
  <tr><th>Assignment Requirement<br>Satisfaction</th><th>To</th><th>From</th><th>Data Conversion</th></tr>
  <tr><td>No</td><td>undef</td><td>X</td><td>No</td></tr>
</table>

=end html

I<X> is a type.

=head2 Assignment Requirement to void

=begin html

<table>
  <tr><th>Assignment Requirement<br>Satisfaction</th><th>To</th><th>From</th><th>Data Conversion</th></tr>
  <tr><td>Yes</td><td>void</td><td>void</td><td>No</td></tr>
  <tr><td>No</td><td>void</td><td>X</td><td>No</td></tr>
</table>

=end html

I<X> is a type.

=head2 Assignment Requirement to Numeric Array

=begin html

<table>
  <tr><th>Assignment Requirement<br>Satisfaction</th><th>To</th><th>From</th><th>Data Conversion</th></tr>
  <tr><td>Yes</td><td>NumericX[]</td><td>NumericX[]</td><td>No</td></tr>
  <tr><td>Yes</td><td>NumericX[]</td><td>undef</td><td>No</td></tr>
  <tr><td>No</td><td>NumericX[]</td><td>Other</td><td>No</td></tr>
</table>

=end html

I<NumericX> is a L<numeric type|"Numeric Types">.

=head2 Assignment Requirement to Multi-Numeric Array

=begin html

<table>
  <tr><th>Assignment Requirement<br>Satisfaction</th><th>To</th><th>From</th><th>Data Conversion</th></tr>
  <tr><td>Yes</td><td>Multi-NumericX[]</td><td>Multi-NumericX[]</td><td>No</td></tr>
  <tr><td>Yes</td><td>Multi-NumericX[]</td><td>undef</td><td>No</td></tr>
  <tr><td>No</td><td>Multi-NumericX[]</td><td>Other</td><td>No</td></tr>
</table>

=end html

I<Multi-NumericX> is a L<multi-numeric type|/"Multi-Numeric Types">.

=head2 Assignment Requirement to String Array

=begin html

<table>
  <tr><th>Assignment Requirement<br>Satisfaction</th><th>To</th><th>From</th><th>Data Conversion</th></tr>
  <tr><td>Yes</td><td>string[]</td><td>string[]</td><td>No</td></tr>
  <tr><td>Yes</td><td>string[]</td><td>undef</td><td>No</td></tr>
  <tr><td>No</td><td>string[]</td><td>Other</td><td>No</td></tr>
</table>

=end html

=head2 Assignment Requirement to Class Array

=begin html

<table>
  <tr><th>Assignment Requirement<br>Satisfaction</th><th>To</th><th>From</th><th>Data Conversion</th></tr>
  <tr><td>Yes</td><td>ClassX[]</td><td>ClassX[]</td><td>No</td></tr>
  <tr><td>Yes</td><td>SuperClassX[]</td><td>ClassX[]</td><td>No</td></tr>
  <tr><td>Yes</td><td>ClassX[]</td><td>undef</td><td>No</td></tr>
  <tr><td>No</td><td>ClassX[]</td><td>Other</td><td>No</td></tr>
</table>

=end html

I<ClassX> is a L<class type|"Class Types">.

I<SuperClassX> is a super class of I<ClassX>.

=head2 Assignment Requirement to Interface Array

=begin html

<table>
  <tr><th>Assignment Requirement<br>Satisfaction</th><th>To</th><th>From</th><th>Data Conversion</th></tr>
  <tr><td>Yes</td><td>InterfaceX[]</td><td>InterfaceX[]</td><td>No</td></tr>
  <tr><td>Yes</td><td>InterfaceX[]</td><td>InterfaceSatisfiedX[]</td><td>No</td></tr>
  <tr><td>Yes</td><td>InterfaceX[]</td><td>undef</td><td>No</td></tr>
  <tr><td>No</td><td>InterfaceX[]</td><td>Other</td><td>No</td></tr>
</table>

=end html

I<InterfaceX> is a an L<interface type|"Interface Types">.

I<InterfaceSatisfiedX> is a L<class type|"Class Types"> or an L<interface type|"Interface Types"> that satisfied L<interface requirement|/"Interface Requirement"> of I<InterfaceX>.

=head2 Assignment Requirement to Any Object Array

=begin html

<table>
  <tr><th>Assignment Requirement<br>Satisfaction</th><th>To</th><th>From</th><th>Data Conversion</th></tr>
  <tr><td>Yes</td><td>Any Object Array <code>object[]</code></td><td>ObjectX[]..</td><td>No</td></tr>
  <tr><td>Yes</td><td>Any Object Array <code>object[]</code></td><td>undef</td><td>No</td></tr>
  <tr><td>No</td><td>Any Object Array <code>object[]</code></td><td>Other</td><td>No</td></tr>
</table>

=end html

I<ObjectX> is an L<object type|"Object Types">.

C<[]..> is one or more C<[]>.

=head2 Assignment Requirement to Multi-Dimensional Array

=begin html

<table>
  <tr><th>Assignment Requirement<br>Satisfaction</th><th>To</th><th>From</th><th>Data Conversion</th></tr>
  <tr><td>Yes</td><td>X[]..D</td><td>X[]..D</td><td>No</td></tr>
  <tr><td>Yes</td><td>X[]..D</td><td>undef</td><td>No</td></tr>
  <tr><td>Yes</td><td>SuperClassX[]..D</td><td>ClassX[]..D</td><td>No</td></tr>
  <tr><td>Yes</td><td>InterfaceX[]..D</td><td>InterfaceSatisfiedX[]..D</td><td>No</td></tr>
  <tr><td>No</td><td>X[]..D</td><td>Other</td><td>No</td></tr>
</table>

=end html

I<X> is a type.

C<[]..> is one or more C<[]>.

I<D> means its type dimension that is greater than or eausl to 2.

I<X[]..D> is a multi-dimensional array.

I<ClassX> is a L<class type|"Class Types">.

I<SuperClassX> is a super class of I<ClassX>.

I<InterfaceX> is a an L<interface type|"Interface Types">.

I<InterfaceSatisfiedX> is a L<class type|"Class Types"> or an L<interface type|"Interface Types"> that satisfied L<interface requirement|/"Interface Requirement"> of I<InterfaceX>.

=head1 Cast Requirement

The cast requirement is the requirement whether one type is able to be cast to another type.

What does it mean to cast one type to another type?

Typically, it is sufficient to consider a case where a value of a type I<TYPE_FROM> is casted to I<TYPE_TO>.

  my $value : TYPE_FROM;
  (TYPE_TO)$value;

Abstracting this, type-to-type cast is defined.

  (TYPE_TO)TYPE_FROM

Note that this is a concept, not an actual syntax.

Some type casts perform a data conversion.

Some type casts perform a data check.

In the following description, the word "Type" is omitted when it is obvious.

=head2 Cast Requirement to Numeric

=head3 Cast Requirement from Numeric to Numeric

To Larger:

=begin html

<table>
  <tr><th>Cast Requirement<br>Satisfaction</th><th>To</th><th>From</th><th>Data Conversion</th><th>Data Check</th></tr>
  <tr><td>Yes</td><td>byte</td><td>byte</td><td>No</td><td>No</td></tr>
  <tr><td>Yes</td><td>short</td><td>short</td><td>No</td><td>No</td></tr>
  <tr><td>Yes</td><td>int</td><td>int</td><td>No</td><td>No</td></tr>
  <tr><td>Yes</td><td>long</td><td>long</td><td>No</td><td>No</td></tr>
  <tr><td>Yes</td><td>float</td><td>float</td><td>No</td><td>No</td></tr>
  <tr><td>Yes</td><td>double</td><td>double</td><td>No</td><td>No</td></tr>
  <tr><td>Yes</td><td>short</td><td>byte</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Numeric-Widening-Conversion">Numeric Widening Conversion</a></td><td>No</td></tr>
  <tr><td>Yes</td><td>int</td><td>byte</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Numeric-Widening-Conversion">Numeric Widening Conversion</a></td><td>No</td></tr>
  <tr><td>Yes</td><td>long</td><td>byte</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Numeric-Widening-Conversion">Numeric Widening Conversion</a></td><td>No</td></tr>
  <tr><td>Yes</td><td>float</td><td>byte</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Numeric-Widening-Conversion">Numeric Widening Conversion</a></td><td>No</td></tr>
  <tr><td>Yes</td><td>double</td><td>byte</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Numeric-Widening-Conversion">Numeric Widening Conversion</a></td><td>No</td></tr>
  <tr><td>Yes</td><td>int</td><td>short</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Numeric-Widening-Conversion">Numeric Widening Conversion</a></td><td>No</td></tr>
  <tr><td>Yes</td><td>long</td><td>short</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Numeric-Widening-Conversion">Numeric Widening Conversion</a></td><td>No</td></tr>
  <tr><td>Yes</td><td>float</td><td>short</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Numeric-Widening-Conversion">Numeric Widening Conversion</a></td><td>No</td></tr>
  <tr><td>Yes</td><td>double</td><td>short</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Numeric-Widening-Conversion">Numeric Widening Conversion</a></td><td>No</td></tr>
  <tr><td>Yes</td><td>long</td><td>int</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Numeric-Widening-Conversion">Numeric Widening Conversion</a></td><td>No</td></tr>
  <tr><td>Yes</td><td>float</td><td>int</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Numeric-Widening-Conversion">Numeric Widening Conversion</a></td><td>No</td></tr>
  <tr><td>Yes</td><td>double</td><td>int</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Numeric-Widening-Conversion">Numeric Widening Conversion</a></td><td>No</td></tr>
  <tr><td>Yes</td><td>float</td><td>long</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Numeric-Widening-Conversion">Numeric Widening Conversion</a></td><td>No</td></tr>
  <tr><td>Yes</td><td>double</td><td>long</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Numeric-Widening-Conversion">Numeric Widening Conversion</a></td><td>No</td></tr>
  <tr><td>Yes</td><td>double</td><td>float</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Numeric-Widening-Conversion">Numeric Widening Conversion</a></td><td>No</td></tr>
</table>

=end html

To Smaller:

=begin html

<table>
  <tr><th>Cast Requirement<br>Satisfaction</th><th>To</th><th>From</th><th>Data Conversion</th><th>Data Check</th></tr>
  <tr><td>Yes</td><td>byte</td><td>short</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Numeric-Narrowing-Conversion">Numeric Narrowing Conversion</a></td><td>No</td></tr>
  <tr><td>Yes</td><td>byte</td><td>int</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Numeric-Narrowing-Conversion">Numeric Narrowing Conversion</a></td><td>No</td></tr>
  <tr><td>Yes</td><td>byte</td><td>long</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Numeric-Narrowing-Conversion">Numeric Narrowing Conversion</a></td><td>No</td></tr>
  <tr><td>Yes</td><td>byte</td><td>float</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Numeric-Narrowing-Conversion">Numeric Narrowing Conversion</a></td><td>No</td></tr>
  <tr><td>Yes</td><td>byte</td><td>double</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Numeric-Narrowing-Conversion">Numeric Narrowing Conversion</a></td><td>No</td></tr>
  <tr><td>Yes</td><td>short</td><td>int</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Numeric-Narrowing-Conversion">Numeric Narrowing Conversion</a></td><td>No</td></tr>
  <tr><td>Yes</td><td>short</td><td>long</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Numeric-Narrowing-Conversion">Numeric Narrowing Conversion</a></td><td>No</td></tr>
  <tr><td>Yes</td><td>short</td><td>float</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Numeric-Narrowing-Conversion">Numeric Narrowing Conversion</a></td><td>No</td></tr>
  <tr><td>Yes</td><td>short</td><td>double</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Numeric-Narrowing-Conversion">Numeric Narrowing Conversion</a></td><td>No</td></tr>
  <tr><td>Yes</td><td>int</td><td>long</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Numeric-Narrowing-Conversion">Numeric Narrowing Conversion</a></td><td>No</td></tr>
  <tr><td>Yes</td><td>int</td><td>float</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Numeric-Narrowing-Conversion">Numeric Narrowing Conversion</a></td><td>No</td></tr>
  <tr><td>Yes</td><td>int</td><td>double</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Numeric-Narrowing-Conversion">Numeric Narrowing Conversion</a></td><td>No</td></tr>
  <tr><td>Yes</td><td>long</td><td>float</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Numeric-Narrowing-Conversion">Numeric Narrowing Conversion</a></td><td>No</td></tr>
  <tr><td>Yes</td><td>long</td><td>double</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Numeric-Narrowing-Conversion">Numeric Narrowing Conversion</a></td><td>No</td></tr>
  <tr><td>Yes</td><td>float</td><td>double</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Numeric-Narrowing-Conversion">Numeric Narrowing Conversion</a></td><td>No</td></tr>
</table>

=end html

=head3 Cast Requirement from NumericObject to Numeric

=begin html

<table>
  <tr><th>Cast Requirement<br>Satisfaction</th><th>To</th><th>From</th><th>Data Conversion</th><th>Data Check</th></tr>
  <tr><td>Yes</td><td>byte</td><td>Byte</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Unboxing-Conversion">Unboxing Conversion</a></td><td>No</td></tr>
  <tr><td>Yes</td><td>short</td><td>Short</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Unboxing-Conversion">Unboxing Conversion</a></td><td>No</td></tr>
  <tr><td>Yes</td><td>int</td><td>Int</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Unboxing-Conversion">Unboxing Conversion</a></td><td>No</td></tr>
  <tr><td>Yes</td><td>long</td><td>Long</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Unboxing-Conversion">Unboxing Conversion</a></td><td>No</td></tr>
  <tr><td>Yes</td><td>float</td><td>Float</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Unboxing-Conversion">Unboxing Conversion</a></td><td>No</td></tr>
  <tr><td>Yes</td><td>double</td><td>Double</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Unboxing-Conversion">Unboxing Conversion</a></td><td>No</td></tr>
</table>

=end html

=head3 Cast Requirement from Any Object to Numeric

=begin html

<table>
  <tr><th>Cast Requirement<br>Satisfaction</th><th>To</th><th>From</th><th>Data Conversion</th><th>Data Check</th></tr>
  <tr><td>Yes</td><td>NumericX</td><td>Any Object <code>object</code></td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Unboxing-Conversion">Unboxing Conversion</a></td><td>No</td></tr>
</table>

=end html

I<NumericX> is a L<numeric type|"Numeric Types">.

=head3 Cast Requirement from Other to Numeric

=begin html

<table>
  <tr><th>Cast Requirement<br>Satisfaction</th><th>To</th><th>From</th><th>Data Conversion</th><th>Data Check</th></tr>
  <tr><td>No</td><td>NumericX</td><td>Other</td><td>No</td><td>No</td></tr>
</table>

=end html

I<NumericX> is a L<numeric type|"Numeric Types">.

=head2 Cast Requirement to Multi-Numeric

=begin html

<table>
  <tr><th>Cast Requirement<br>Satisfaction</th><th>To</th><th>From</th><th>Data Conversion</th><th>Data Check</th></tr>
  <tr><td>Yes</td><td>Multi-NumericX</td><td>Multi-NumericX</td><td>No</td><td>No</td></tr>
  <tr><td>No</td><td>Multi-NumericX</td><td>Other</td><td>No</td><td>No</td></tr>
</table>

=end html

I<Multi-NumericX> is a L<multi-numeric type|/"Multi-Numeric Types">.

=head2 Cast Requirement to Referenece

=begin html

<table>
  <tr><th>Cast Requirement<br>Satisfaction</th><th>To</th><th>From</th><th>Data Conversion</th><th>Data Check</th></tr>
  <tr><td>Yes</td><td>ReferenceX</td><td>ReferenceX</td><td>No</td><td>No</td></tr>
  <tr><td>Yes</td><td>ReferenceX</td><td>undef</td><td>No</td><td>No</td></tr>
  <tr><td>No</td><td>ReferenceX</td><td>Other</td><td>No</td><td>No</td></tr>
</table>

=end html

I<ReferenceX> is a L<reference type|/"Reference Types">.

=head2 Cast Requirement to String

=begin html

<table>
  <tr><th>Cast Requirement<br>Satisfaction</th><th>To</th><th>From</th><th>Data Conversion</th><th>Data Check</th></tr>
  <tr><td>Yes</td><td>string</td><td>string</td><td>No</td><td>No</td></tr>
  <tr><td>Yes</td><td>string</td><td>mutable string</td><td>No</td><td>No</td></tr>
  <tr><td>Yes</td><td>mutable string</td><td>mutable string</td><td>No</td><td>No</td></tr>
  <tr><td>Yes</td><td>mutable string</td><td>string</td><td>No</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#is_read_only-Operator">is_read_only Operator</a></td></tr>
  <tr><td>Yes</td><td>string</td><td>string</td><td>No</td><td>No</td></tr>
  <tr><td>Yes</td><td>string</td><td>NumericX</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Numeric-to-String-Conversion">Numeric-to-String Conversion</a></td><td>No</td></tr>
  <tr><td>Yes</td><td>string</td><td>Any Object <code>object</code></td><td>No</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#isa-Operator">isa Operator</a></td></tr>
  <tr><td>Yes</td><td>string</td><td>undef</td><td>No</td><td>No</td></tr>
  <tr><td>No</td><td>string</td><td>Other</td><td>No</td><td>No</td></tr>
</table>

=end html

I<NumericX> is a L<numeric type|"Numeric Types">.

=head2 Cast Requirement to NumericObject

=begin html

<table>
  <tr><th>Cast Requirement<br>Satisfaction</th><th>To</th><th>From</th><th>Data Conversion</th><th>Data Check</th></tr>
  <tr><td>Yes</td><td>NumericObjectX</td><td>NumericObjectX</td><td>No</td><td>No</td></tr>
  <tr><td>Yes</td><td>NumericObjectX</td><td>NumericX</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Boxing-Conversion">Boxing Conversion</a></td><td>No</td></tr>
  <tr><td>Yes</td><td>NumericObjectX</td><td>Any Object <code>object</code></td><td>No</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#isa-Operator">isa Operator</a></td></tr>
  <tr><td>Yes</td><td>NumericObjectX</td><td>undef</td><td>No</td><td>No</td></tr>
  <tr><td>No</td><td>NumericObjectX</td><td>Other</td><td>No</td><td>No</td></tr>
</table>

=end html

I<NumericObjectX> is a L<numeric object type|"Numeric Object Types">.

I<NumericX> is a L<numeric type|"Numeric Types">.

=head2 Cast Requirement to Class

=begin html

<table>
  <tr><th>Cast Requirement<br>Satisfaction</th><th>To</th><th>From</th><th>Data Conversion</th><th>Data Check</th></tr>
  <tr><td>Yes</td><td>ClassX</td><td>ClassX</td><td>No</td><td>No</td></tr>
  <tr><td>Yes</td><td>SuperClassX</td><td>ClassX</td><td>No</td><td>No</td></tr>
  <tr><td>Yes</td><td>ClassX</td><td>SuperClassX</td><td>No</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#isa-Operator">isa Operator</a></td></tr>
  <tr><td>Yes</td><td>ClassX</td><td>InterfaceX</td><td>No</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#isa-Operator">isa Operator</a></td></tr>
  <tr><td>Yes</td><td>ClassX</td><td>Any Object <code>object</code></td><td>No</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#isa-Operator">isa Operator</a></td></tr>
  <tr><td>Yes</td><td>ClassX</td><td>undef</td><td>No</td><td>No</td></tr>
  <tr><td>No</td><td>ClassX</td><td>Other</td><td>No</td><td>No</td></tr>
</table>

=end html

I<ClassX> is a L<class type|"Class Types">.

I<SuperClassX> is a super class of I<ClassX>.

I<InterfaceX> is a an L<interface type|"Interface Types">.

=head2 Cast Requirement to Interface

=begin html

<table>
  <tr><th>Cast Requirement<br>Satisfaction</th><th>To</th><th>From</th><th>Data Conversion</th><th>Data Check</th></tr>
  <tr><td>Yes</td><td>InterfaceX</td><td>InterfaceX</td><td>No</td><td>No</td></tr>
  <tr><td>Yes</td><td>InterfaceX</td><td>InterfaceSatisfiedX</td><td>No</td><td>No</td></tr>
  <tr><td>Yes</td><td>InterfaceX</td><td>InterfaceY</td><td>No</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#isa-Operator">isa Operator</a></td></tr>
  <tr><td>Yes</td><td>InterfaceX</td><td>Any Object <code>object</code></td><td>No</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#isa-Operator">isa Operator</a></td></tr>
  <tr><td>Yes</td><td>InterfaceX</td><td>undef</td><td>No</td><td>No</td></tr>
  <tr><td>No</td><td>InterfaceX</td><td>Other</td><td>No</td><td>No</td></tr>
</table>

=end html

I<ClassX> is a L<class type|"Class Types">.

I<SuperClassX> is a super class of I<ClassX>.

I<InterfaceX> is a an L<interface type|"Interface Types">.

I<InterfaceY> is a an L<interface type|"Interface Types">.

I<InterfaceSatisfiedX> is a L<class type|"Class Types"> or an L<interface type|"Interface Types"> that satisfied L<interface requirement|/"Interface Requirement"> of I<InterfaceX>.

=head2 Cast Requirement to Any Object

=begin html

<table>
  <tr><th>Cast Requirement<br>Satisfaction</th><th>To</th><th>From</th><th>Data Conversion</th><th>Data Check</th></tr>
  <tr><td>Yes</td><td>Any Object <code>object</code></td><td>ObjectX</td><td>No</td><td>No</td></tr>
  <tr><td>Yes</td><td>Any Object <code>object</code></td><td>NumericX</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#Boxing-Conversion">Boxing Conversion</a></td><td>No</td></tr>
  <tr><td>Yes</td><td>Any Object <code>object</code></td><td>undef</td><td>No</td><td>No</td></tr>
  <tr><td>No</td><td>Any Object <code>object</code></td><td>Other</td><td>No</td><td>No</td></tr>
</table>

=end html

I<ObjectX> is an L<object type|"Object Types">.

I<NumericX> is a L<numeric type|"Numeric Types">.

=head2 Cast Requirement to Numeric Array

=begin html

<table>
  <tr><th>Cast Requirement<br>Satisfaction</th><th>To</th><th>From</th><th>Data Conversion</th><th>Data Check</th></tr>
  <tr><td>Yes</td><td>byte[]</td><td>string</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#String-to-byte[]-Conversion">String-to-byte[] Conversion</a></td><td>No</td></tr>
  <tr><td>Yes</td><td>NumericX[]</td><td>NumericX[]</td><td>No</td><td>No</td></tr>
  <tr><td>Yes</td><td>NumericX[]</td><td>Any Object <code>object</code></td><td>No</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#isa-Operator">isa Operator</a></td></tr>
  <tr><td>Yes</td><td>NumericX[]</td><td>undef</td><td>No</td><td>No</td></tr>
  <tr><td>No</td><td>NumericX[]</td><td>Other</td><td>No</td><td>No</td></tr>
</table>

=end html

I<NumericX> is a L<numeric type|"Numeric Types">.

=head2 Cast Requirement to Multi-Numeric Array

=begin html

<table>
  <tr><th>Cast Requirement<br>Satisfaction</th><th>To</th><th>From</th><th>Data Conversion</th><th>Data Check</th></tr>
  <tr><td>Yes</td><td>Multi-NumericX[]</td><td>Multi-NumericX[]</td><td>No</td><td>No</td></tr>
  <tr><td>Yes</td><td>Multi-NumericX[]</td><td>Any Object <code>object</code></td><td>No</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#isa-Operator">isa Operator</a></td></tr>
  <tr><td>Yes</td><td>Multi-NumericX[]</td><td>undef</td><td>No</td><td>No</td></tr>
  <tr><td>No</td><td>Multi-NumericX[]</td><td>Other</td><td>No</td><td>No</td></tr>
</table>

=end html

I<Multi-NumericX> is a L<multi-numeric type|/"Multi-Numeric Types">.

=head2 Cast Requirement to String Array

=begin html

<table>
  <tr><th>Cast Requirement<br>Satisfaction</th><th>To</th><th>From</th><th>Data Conversion</th><th>Data Check</th></tr>
  <tr><td>Yes</td><td>string[]</td><td>string[]</td><td>No</td><td>No</td></tr>
  <tr><td>Yes</td><td>string[]</td><td>Any Object <code>object</code></td><td>No</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#isa-Operator">isa Operator</a></td></tr>
  <tr><td>Yes</td><td>string[]</td><td>Any Object Array <code>object[]</code></td><td>No</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#isa-Operator">isa Operator</a></td></tr>
  <tr><td>Yes</td><td>string[]</td><td>undef</td><td>No</td><td>No</td></tr>
  <tr><td>No</td><td>string[]</td><td>Other</td><td>No</td><td>No</td></tr>
</table>

=end html

=head2 Cast Requirement to Class Array

=begin html

<table>
  <tr><th>Cast Requirement<br>Satisfaction</th><th>To</th><th>From</th><th>Data Conversion</th><th>Data Check</th></tr>
  <tr><td>Yes</td><td>ClassX[]</td><td>ClassX[]</td><td>No</td><td>No</td></tr>
  <tr><td>Yes</td><td>SuperClassX[]</td><td>ClassX[]</td><td>No</td><td>No</td></tr>
  <tr><td>Yes</td><td>ClassX[]</td><td>SuperClassX[]</td><td>No</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#isa-Operator">isa Operator</a></td></tr>
  <tr><td>Yes</td><td>ClassX[]</td><td>Any Object <code>object</code></td><td>No</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#isa-Operator">isa Operator</a></td></tr>
  <tr><td>Yes</td><td>ClassX[]</td><td>Any Object Array <code>object[]</code></td><td>No</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#isa-Operator">isa Operator</a></td></tr>
  <tr><td>Yes</td><td>ClassX[]</td><td>undef</td><td>No</td><td>No</td></tr>
  <tr><td>No</td><td>ClassX[]</td><td>Other</td><td>No</td><td>No</td></tr>
</table>

=end html

I<ClassX> is a L<class type|"Class Types">.

I<SuperClassX> is a super class of I<ClassX>.

=head2 Cast Requirement to Interface Array

=begin html

<table>
  <tr><th>Cast Requirement<br>Satisfaction</th><th>To</th><th>From</th><th>Data Conversion</th><th>Data Check</th></tr>
  <tr><td>Yes</td><td>InterfaceX[]</td><td>InterfaceX[]</td><td>No</td><td>No</td></tr>
  <tr><td>Yes</td><td>InterfaceX[]</td><td>InterfaceSatisfiedX[]</td><td>No</td><td>No</td></tr>
  <tr><td>Yes</td><td>InterfaceX[]</td><td>InterfaceY[]</td><td>No</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#isa-Operator">isa Operator</a></td></tr>
  <tr><td>Yes</td><td>InterfaceX[]</td><td>Any Object <code>object</code></td><td>No</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#isa-Operator">isa Operator</a></td></tr>
  <tr><td>Yes</td><td>InterfaceX[]</td><td>Any Object Array <code>object[]</code></td><td>No</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#isa-Operator">isa Operator</a></td></tr>
  <tr><td>Yes</td><td>InterfaceX[]</td><td>undef</td><td>No</td><td>No</td></tr>
  <tr><td>No</td><td>InterfaceX[]</td><td>Other</td><td>No</td><td>No</td></tr>
</table>

=end html

I<ClassX> is a L<class type|"Class Types">.

I<SuperClassX> is a super class of I<ClassX>.

I<InterfaceX> is a an L<interface type|"Interface Types">.

I<InterfaceY> is a an L<interface type|"Interface Types">.

I<InterfaceSatisfiedX> is a L<class type|"Class Types"> or an L<interface type|"Interface Types"> that satisfied L<interface requirement|/"Interface Requirement"> of I<InterfaceX>.

=head2 Cast Requirement to Any Object Array

=begin html

<table>
  <tr><th>Cast Requirement<br>Satisfaction</th><th>To</th><th>From</th><th>Data Conversion</th><th>Data Check</th></tr>
  <tr><td>Yes</td><td>Any Object Array <code>object[]</code></td><td>ObjectX[]..</td><td>No</td><td>No</td></tr>
  <tr><td>Yes</td><td>Any Object Array <code>object[]</code></td><td>undef</td><td>No</td><td>No</td></tr>
  <tr><td>Yes</td><td>Any Object Array <code>object[]</code></td><td>Any Object <code>object</code></td><td>No</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#isa-Operator">isa Operator</a></td></tr>
  <tr><td>No</td><td>Any Object Array <code>object[]</code></td><td>Other</td><td>No</td><td>No</td></tr>
</table>

=end html

I<ObjectX> is an L<object type|"Object Types">.

C<[]..> is one or more C<[]>.

=head2 Cast Requirement to Multi-Dimensional Array

=begin html

<table>
  <tr><th>Cast Requirement<br>Satisfaction</th><th>To</th><th>From</th><th>Data Conversion</th><th>Data Check</th></tr>
  <tr><td>Yes</td><td>X[]..D</td><td>X[]..D</td><td>No</td><td>No</td></tr>
  <tr><td>Yes</td><td>X[]..D</td><td>Any Object <code>object</code></td><td>No</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#isa-Operator">isa Operator</a></td></tr>
  <tr><td>Yes</td><td>X[]..D</td><td>Any Object Array <code>object[]</code></td><td>No</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#isa-Operator">isa Operator</a></td></tr>
  <tr><td>Yes</td><td>X[]..D</td><td>undef</td><td>No</td><td>No</td></tr>
  <tr><td>Yes</td><td>SuperClassX[]..</td><td>ClassX[]..D</td><td>No</td><td>No</td></tr>
  <tr><td>Yes</td><td>ClassX[]..</td><td>SuperClassX[]..D</td><td>No</td><td><a href="https://metacpan.org/pod/SPVM::Document::Language::Operators#isa-Operator">isa Operator</a></td></tr>
  <tr><td>Yes</td><td>InterfaceX[]..D</td><td>InterfaceSatisfiedX[]..D</td><td>No</td><td>No</td></tr>
  <tr><td>No</td><td>Any Object Array <code>object[]</code></td><td>Other</td><td>No</td><td>No</td></tr>
</table>

=end html

I<X> is a type.

C<[]..> is one or more C<[]>.

I<D> means its type dimension that is greater than or eausl to 2.

I<X[]..D> is a multi-dimensional array.

I<ClassX> is a L<class type|"Class Types">.

I<SuperClassX> is a super class of I<ClassX>.

I<InterfaceX> is a an L<interface type|"Interface Types">.

I<InterfaceSatisfiedX> is a L<class type|"Class Types"> or an L<interface type|"Interface Types"> that satisfied L<interface requirement|/"Interface Requirement"> of I<InterfaceX>.

=head1 Interface Requirement

The interface requirement is the requirement whether an L<object type|"Object Types"> is able to be assigned to an L<interface type|"Interface Types">.

  INTERFACE_TYPE_TO = OBJECT_TYPE_FROM

This is the same concept as type-to-type assignment explained in L<Assignment Requirement|/"Assignment Requirement">.

I<INTERFACE_TYPE_TO> must be an L<interface type|"Interface Types">.

I<OBJECT_TYPE_FROM> must be a L<class type|"Class Types"> or an L<interface type|"Interface Types">.

The following check is performed on every instance method of I<OBJECT_TYPE_FROM>.

If an instance method of I<INTERFACE_TYPE_TO> has the C<required> method attribute, I<OBJECT_TYPE_FROM> or one of its super classes must have a method with the same name.

If I<OBJECT_TYPE_FROM> or one of its super classes has an instance method(this is named I<METHOD_FROM>) with the same name as an instance method of I<INTERFACE_TYPE_TO>,
I<METHOD_FROM> must be an instance method and satisfy L<interface method requirement|/"Interface Method Requirement">.

=head2 Interface Method Requirement

The interface method requirement is the requirement whether a method is able to be assigned to an interface method.

  INTERFACE_METHOD_TO = METHOD_FROM

This is a concept that converts the type-to-type assignment explained in L<Assignment Requirement|/"Assignment Requirement"> to method-to-method assignment.

I<INTERFACE_METHOD_TO> must be an instance method.

I<METHOD_FROM> must be an instance method.

The length of the arguments of the method of the I<INTERFACE_METHOD_TO> type must be greater than or equal to the length of the required arguments the method of the I<INSTANT_METHOD_TYPE_FROM> type.

The every argument other than at 0 index of the method of the I<INSTANT_METHOD_TYPE_FROM> must satisfy L<assignment requirement|/"Assignment Requirement"> to the argument as the same index of the method of the I<INTERFACE_METHOD_TO> without a data conversion and with interface exactly matched.

The return type of the method of the I<INSTANT_METHOD_TYPE_FROM> must must satisfy L<assignment requirement|/"Assignment Requirement"> to the return type of the method of the I<INTERFACE_METHOD_TO> without a data conversion and with interface exactly matched.

=head1 See Also

=over 2

=item * L<SPVM::Document::Language::Class>

=item * L<SPVM::Document::Language::Operators>

=item * L<SPVM::Document::Language::Statements>

=item * L<SPVM::Document::Language>

=item * L<SPVM::Document>

=back

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
