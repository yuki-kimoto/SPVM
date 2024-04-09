=head1 Name

SPVM::Document::Language::Class - Class Definition in the SPVM Language

=head1 Description

This document describes class definition in the SPVM language.

=head1 Class

A class defines its L<class type|SPVM::Document::Language::Types/"Class Type">, its L<class variables|/"Class Variable">, its L<fields|/"Field"> and its L<methods|/"Method">.

The object can be created from a class using L<new operator|/"Creating a Object">.

=head2 Class Definition

The C<class> keyword defines a class. A class has a L<class block|/"Class Block">.
  
  # Class definition
  class CLASS_NAME {
  
  }

The class name must follow the naming rule of the L<class name|/"Class Name">.

Examples:

  # Class definition
  class Point {
  
  }

L<Class attributes|/"Class Attributes"> are written after C<:>.

  class CLASS_NAME : CLASS_ATTRIBUTE {
  
  }
  
  class CLASS_NAME : CLASS_ATTRIBUTE1 CLASS_ATTRIBUTE2 CLASS_ATTRIBUTE3 {
  
  }

Compilation Errors:

If more than one class is defined in a class file, a compilation error occurs.

Examples:

  # Class attributes
  class Point : public {
  
  }

  class Point : public pointer {
  
  }

=head2 Version Declaration

The C<version> keyword declares the version string of a module.

  version VERSION_STRING;

The operand VERSION_STRING is a version string.

A version string is the string type.

It is composed of numbers C<0-9>, C<.>. 

The following checks are performed.

The version string is saved to the version information of the module.

Compilation Errors:

If the version string has already been declared, a compilation error occurs.

A character in a version string must be a number or C<.>. Otherwise a compilation error occurs.

The number of C<.> in a version string must be less than or equal to 1. Otherwise a compilation error occurs.

A version string must begin with a number. Otherwise a compilation error occurs.

A version string must end with a number. Otherwise a compilation error occurs.

The number of C<.> in a version string must be less than or equal to 1. Otherwise a compilation error occurs.

The length of characters after C<.> in a version string must be divisible by 3. Otherwise a compilation error occurs.

A version number must be able to be parsed by the C<strtod> C function. Otherwise a compilation error occurs.

Examples:
  
  class Foo {
    version "1";
  }
  
  class Foo {
    version "20080903";
  }
  
  class Foo {
    version "1.001";
  }
  
  class Foo {
    version "10.001003";
  }
  
=head3 Version String

The version string is the string represented version of a module.

It is declared by the L<version declaration|/"Version Declaration">.

=head3 Version Number

The version number is a floating point number created by the following way.

A L<version string/"Version Declaration"> is converted to a floating point number by the C<strtod> C function.

=head2 Class Attributes

The list of class attributes.

=begin html

<table>
  <tr>
    <th>
      Class Attributes
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
      This class is public. In other classes, this class can be used as I<OPERAND> of <a href="#Creating-Object">new operator</a>.
    </td>
  </tr>
  <tr>
    <td>
      <b>private</b>
    </td>
    <td>
      This class is private. In other classes, this class cannot be used as I<OPERAND> of <a href="#Creating-Object">new operator</a>. This is default.
    </td>
  </tr>
  <tr>
    <td>
      <b>protected</b>
    </td>
    <td>
      This class is protected. In other classes except for the child classes, this class cannot be used as I<OPERAND> of <a href="#Creating-Object">new operator</a>.
    </td>
  </tr>
  <tr>
    <td>
      <b>interface_t</b>
    </td>
    <td>
      This class is an <a href="#Interface-Type">interface type</a>. The class definition is interpreted as an <a href="#Interface-Definiton">interface definiton</a>.
    </td>
  </tr>
  <tr>
    <td>
      <b>mulnum_t</b>
    </td>
    <td>
      This class is a <a href="#Multi-Numeric-Type">multi-numeric type</a>. The class definition is interpreted as an <a href="#Multi-Numeric-Type-Definiton">multi-numeric type definiton</a>.
    </td>
  </tr>
  <tr>
    <td>
      <b>pointer</b>
    </td>
    <td>
      The class is a <a href="#Pointer-Class">pointer class</a>.
    </td>
  </tr>
  <tr>
    <td>
      <b>precompile</b>
    </td>
    <td>
      Perform <a href="#Precompiled-Method">precompile</a> to all methods in this class, except for getter methods, setter methods, and enumurations. 
    </td>
  </tr>
</table>

=end html

Compilation Errors:

Only one of class attributes C<private>, C<protected> or C<public> can be specified. Otherwise a compilation error occurs.

If more than one of C<interface_t>, C<mulnum_t>, and C<pointer> are specified, a compilation error occurs.

=head3 Pointer Class

The pointer class is the L<class|/"Class"> that has the L<class attribute|/"Class Attributes"> C<pointer>.

  # Pointer Class
  class Foo : pointer {
  
  }

The type of a pointer class is the L<class type|SPVM::Document::Language::Types/"Class Type">.

An object of a pointer class has the pointer to a native address.

=head2 Anon Class

The anon class is the class that do not has its class name.

  class {
  
  }

But internally an anon class has its name, such as C<eval::anon::0>.

An anon class is also defined by the anon method.

A anon class for an anon method has its unique L<class name|/"Class Name"> corresponding to the class name, the line number and the position of columns the anon class is defined.

A anon class for an anon method has the same access control as its outmost class.

A anon class for an anon method has the same alias names as its outmost class.

L<Examples:>
  
  # Anon class
  class {
    static method sum : int ($num1 : int, $num2 : int) {
      return $num1 + $num2;
    }
  }
  
  # Anon method
  class Foo::Bar {
    method sum : void () {
      my $anon_method = method : string () {
        
      }
   }
  }
  
  # The name of the anon class
  Foo::Bar::anon::3::23;

=head2 Outmost Class

An outmost class is the outmost defined class.

The outmost class is C<Foo::Bar> in the following example.

  class Foo::Bar {
    static method baz : void () {
      my $outmost_class_name = __PACKAGE__;
      
      my $cb = method : void () {
        my $outmost_class_name = __PACKAGE__;
      };
    }
  }

=head2 Class File Name

A class must be written in the following class file.

Change C<::> to C</>. Add ".spvm" at the end.

  SPVM/Foo.spvm
  SPVM/Foo/Bar.spvm
  SPVM/Foo/Bar/Baz.spvm

=head2 use Statement

The C<use> statemenet loads a class.

  use Foo;

Classes are loaded at compile-time.

The C<use> statemenet must be defined directly under the L<class definition|/"Class Definition">.

  class Foo {
    use Foo;
  }

Compilation Errors:

If the class does not exist, a compilation error occurs.

=head2 alias Statement

The C<alias> statemenet creates an alias name for a class name.
  
  # Create alias
  alias Foo::Bar as FB;

FB is used as Foo::Bar alias in L<class method calls|Class Method Call>.

  # This means Foo::Bar->sum(1, 2);
  FB->sum(1, 2);

C<alias> syntax must be defined directly under the L<class definition|/"Class Definition">.

  class Foo {
    alias Foo::Bar as FB;
  }

You can create an alias at the same time as loading a class by the C<use> statement.
  
  use Foo::Bar as FB;

=head2 require Statement

If the C<require> statement that loads a class only if it exists in the class path, and if it does not exist, the block does not exist.

It was designed to implement a part of features of "#ifdef" in the C language.

  if (require Foo) {
  
  }

if C<require> Statement can be followed by else Statement. 

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

=head2 allow Statement

Private methods, private fields, and private class variables cannot be accessed except from the current class.

A private class cannot be I<OPERAND> of the L<new operator|SPVM::Document::Language::Operators/"Creating a Object"> except from the current class.

The C<allow> statemenet allows the private access from the other classes.

  allow CLASS_NAME;

The C<allow> statemenet must be defined directory under the L<class definition|/"Class Definition">.
  
The class that is I<OPERAND> of the C<allow> statemenet is loaded by the same way as the L<use statement|/"use Statement">.

Examples:

  # Allowing private access
  class Foo {
    allow Bar;
  }

=head2 interface Statement

The C<interface> statement guarantees the following things.

  interface INTERFACE_NAME;

1. If the class has methods that are definied the the L<interface|/"Interface Definition">, each method must have the L<Method Compatibility|method compatibility> of each interface method in the L<interface definition|/"Interface Definition">.

2. The class must have methods that defined as required interface methods in the the L<interface|/"Interface Definition">.

Compilation Errors:

If not, a compilation error occurs.

Examples:

  class Point {
    interface Stringable;
    
    method to_string : string () {
      my $x = $self->x;
      my $y = $self->y;
      
      my $string = "($x,$y)";
      
      return $string;
    }
  }
  
  my $stringable = (Stringable)Point->new(1, 2);
  my $string = $stringable->to_string;

=head2 Inheritance

A class inherits a class using the C<extends> keyword.

  class CLASS_NAME extends PARENT_CLASS_NAME {
    
  }

The parts of the definitions of the fields of the all super classes are copied to the class.

The copied parts of the definitions are the field name, the type, the access controll.

The the definitions of the interfaces of the all super classes are copied to the class.

The copied order is from the beginning of the super class at the top level to the current class.

The class can call instance methods of the super classes. The searching order is from the current class to the super class at the top level.

Compilation Errors:

The parant class must be a L<class type|SPVM::Document::Language::Types/"Class Type">. Otherwise a compilation error occurs.

The name of the parant class must be different from the name of the class. Otherwise a compilation error occurs.

The all super classes must be different from its own class. Otherwise a compilation error occurs.

The field that name is the same as the field of the super class cannnot be defined. Otherwise a compilation error occurs.

Examples:

  class Point3D extends Point {
    
    has z : rw protected int;
    
    static method new : Point3D ($x : int = 0, $y : int = 0, $z : int = 0) {
      my $self = new Point3D;
      
      $self->{x} = $x;
      $self->{y} = $y;
      $self->{z} = $z;
      
      return $self;
    }
    
    method clear : void () {
      $self->SUPER::clear;
      $self->{z} = 0;
    }
    
    method to_string : string () {
      my $x = $self->x;
      my $y = $self->y;
      my $z = $self->z;
      
      my $string = "($x,$y,$z)";
      
      return $string;
    }
    
    method clone : object () {
      my $self_clone = Point3D->new($self->x, $self->y, $self->z);
      
      return $self_clone;
    }
  }

=head2 Interface

The interface syntax is described.

=head3 Interface Definition

An interface is defined using a L<class definition|/"Class Definition"> with a L<class attribute/"Class Attributes"> C<interface_t>.

  class Stringable: interface_t {
    required method to_string : string ();
    method foo : int ($num : long);
  }

An interface can have interface methods. An interface method does not need its method block.

An interface can have required interface methods by using the L<method attribute|/"Method Attributes"> C<required>.

The type of the interface is the L<interface type|SPVM::Document::Language::Types/"Interface Type">.

An interface can have L<interface statements|/"interface Statement">.

  class TestCase::Pointable : interface_t {
    interface Stringable;
    
    method x : int ();
    method y : int();
    method to_string : string ();
  }

An interface method can have its method block.

  class Stringable: interface_t {
    method to_string : string ();
    method call_to_string : string () {
      return "foo " . $self->to_string;
    }
  }

This method is only called by the static instance method call.

  $self->Stringable::call_to_string;

Compilation Errors:

An interface cannnot have L<field definitions|/"Field Definition">. If so, an compilation error occurs.

An interface cannnot have L<class variable definitions|/"Class Variable Definition">. If so, an compilation error occurs.

=head2 Duck Typing

The duck typing is supported.

  class Stringable: interface_t {
    method to_string : string ();
  }

  class Point {
    
    method to_string : string () {
      my $x = $self->x;
      my $y = $self->y;
      
      my $string = "($x,$y)";
      
      return $string;
    }
  }
  
  my $stringable = (Stringable)Point->new(1, 2);
  my $string = $stringable->to_string;

The Point class have no interfaces, but An object of the Point class can be assigned to a Stringable interface
because the to_string method in the Point class has the method compatibility of the to_string method in the Strigable interface.

=head3 Interface Requirement

(TODO)

This section describes assignment requirements used to check a return type and argument types for L<interface requirement|SPVM::Document::Language::Class/"Interface Requirement">.

=head2 Multi-Numeric Type Definition

A L<multi-numeric type|SPVM::Document::Language::Types/"Multi-Numeric Types"> is defined by the L<class definition|/"Class Definition"> that has the C<mulnum_t> L<class attribute|/"Class Attribute">.

  # Continuous two 64bit floating point
  class Complex_2d : mulnum_t {
    re : double;
    im : double;
  }

The type of a field must be a L<numeric type|SPVM::Document::Language::Types/"Numeric Types">.

The types of all fields must be the same types.

The length of the fields must be less than or equal to 255.

=head3 Multi-Numeric Type Suffix

The multi-numeric type must end with the following suffix.

  _[FieldsLength][TypeSuffix]

The List of the Multi-Numeric Type Suffix:

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

The length of the fields in the suffix must be the same as the length of the fields.

The type suffix in the suffix must correspond to the L<numeric type|SPVM::Document::Language::Types/"Numeric Types"> that is explained in the L<multi-numeric type suffix|/"Multi-Numeric Types Suffix">.

See the L<multi-numeric type field access|/"Multi-Numeric Types Field Access"> to get and set the field of the multi-numeric type.

=head2 Default Loaded Classes

The following classes are loaded by default. These classes are deeply related to the features of SPVM language itself, such as L<type conversion|SPVM::Document::Language::Types/"Type Conversions">.

=over 2

=item * L<Byte|SPVM::Byte>

=item * L<Short|SPVM::Short>

=item * L<Int|SPVM::Int>

=item * L<Long|SPVM::Long>

=item * L<Float|SPVM::Float>

=item * L<Double|SPVM::Double>

=item * L<Bool|SPVM::Bool>

=item * L<Error|SPVM::Error>

=item * L<Error::System|SPVM::Error::System>

=item * L<Error::NotSupported|SPVM::Error::NotSupported>

=item * L<Error::Compile|SPVM::Error::Compile>

=item * L<CommandInfo|SPVM::CommandInfo>

=item * L<Address|SPVM::Address>

=back

=head2 Enumeration

The enumeration is the syntx to defines constant values of the int type.

=head3 Enumeration Definition

The C<enum> keyword defines an enumeration. An enumeration has definitions of constant values.

  # Enumeration Definition
  enum {
    FLAG1,
    FLAG2,
    FLAG3
  }

An enumeration must be defined directly under the L<class definition|/"Class Definition">.

  class Foo {
    enum {
      FLAG1,
      FLAG2,
      FLAG3
    }
  }

The name given to an enumeration value must be a L<method name|/"Method Name">.

The first enumeration value is 0. The next enumeration value is incremented by 1, and this is continued in the same way.

In the above example, C<FLAG1> is 0, C<FALG2> is 1, and C<FLAG3> is 2.

The type of an enumeration value is the int type.

C<,> after the last enumeration value can be allowed.

  enum {
    FLAG1,
    FLAG2,
    FLAG3,
  }

An enumeration value can be set by C<=> explicitly.

  enum {
    FLAG1,
    FLAG2 = 4,
    FLAG3,
  }

In the above example, C<FLAG1> is 0, C<FALG2> is 4, and C<FLAG3> is 5.

An enumeration value is got by the L<class method call|SPVM::Document::Language::Operators/"Class Method Call">.

  Foo->FLAG1

Compilation Errors:

If an enumeration definition is invalid, a compilation error occurs.

Examples:

  class Foo {
    enum {
      FLAG1,
      FLAG2,
      FLAG3,
    }
  }

=head3 Enumeration Attributes

Attributes can be specified to an enumeration definition.

  private enum {
    FLAG1,
    FLAG2 = 4,
    FLAG3,
  }

B<The list of enumeration attributes:>

=begin html

<table>
  <tr>
    <th>
      Attributes
   </th>
    <th>
      Descriptions
   </th>
  </tr>
  <tr>
    <td>
      <b>private</b>
    </td>
    <td>
      This enumeration is private. Each value of this enumeration can not be accessed from other classes.
    </td>
  </tr>
  <tr>
    <td>
      <b>protected</b>
    </td>
    <td>
      This enumeration is protected. Each value of this enumeration can not be accessed from other classes except for the child classes.
    </td>
  </tr>
  <tr>
    <td>
      <b>public</b>
    </td>
    <td>
      This enumeration is public. Each value of this enumeration can be accessed from other classes. This is default setting.
    </td>
  </tr>
</table>

=end html

Compilation Errors:

Only one of enumeration attributes C<private>, C<protected> or C<public> can be specified. Otherwise a compilation error occurs.

=head2 Class Variable

A class variable is a global variable that has the name space.

=head3 Class Variable Definition

C<our> keyword defines a class variable.

  our CLASS_VARIABLE_NAME : TYPE;

A Class variable must be defined directly under the L<class definition|/"Class Definition">.

The type must be a L<numeric type|SPVM::Document::Language::Types/"Numeric Type"> or an L<object type|SPVM::Document::Language::Types/"Object Types">.

L<Class variable attributes|/"Class Variable Attributes"> can be specified.

  our CLASS_VARIABLE_NAME : ATTRIBUTE TYPE;
  our CLASS_VARIABLE_NAME : ATTRIBUTE1 ATTRIBUTE2 ATTRIBUTE3 TYPE;

Compilation Errors:

The class variable mame must follow the rule defined in the L<class variable name|/"Class Variable Name">, and must not contain C<::>. Otherwise a compilation error occurs.

If a class name with the same name is defined, a compilation error occurs.

Examples:

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

=head3 Class Variable Attributes

The list of class variable attributes.

=begin html

<table>
  <tr>
    <th>
      Class Variable Attributes
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
      The class variable is public. The class variable can be accessed from other classes.
    </td>
  </tr>
  <tr>
    <td>
      <b>private</b>
    </td>
    <td>
      The class variable is private. The class variable cannnot be accessed from other classes. This is default setting.
    </td>
  </tr>
  <tr>
    <td>
      <b>protected</b>
    </td>
    <td>
      The class variable is protected. The class variable cannnot be accessed from other classes except for the child classes.
    </td>
  </tr>
  <tr>
    <td>
      <b>ro</b>
    </td>
    <td>
      The class variable has its <a href="#Class-Variable-Getter-Method">getter method</a>.
    </td>
  </tr>
  <tr>
    <td>
      <b>wo</b>
    </td>
    <td>
      The class variable has its <a href="#Class-Variable-Setter-Method">setter method</a>.
    </td>
  </tr>
  <tr>
    <td>
      <b>rw</b>
    </td>
    <td>
      The class variable has its <a href="#Class-Variable-Getter-Method">getter method</a> and <a href="#Class-Variable-Setter-Method">setter method</a>.
    </td>
  </tr>
</table>

=end html

Compilation Errors:

Only one of class variable attributes C<private>, C<protected> or C<public> can be specified. Otherwise a compilation error occurs.

If more than one of C<ro>, C<wo>, and C<rw> are specified, a compilation error occurs

=head4 Class Variable Getter Method

A class variable getter method is a method to perform the operation of the L<getting a class variable|SPVM::Document::Language::Operators/"Getting a Class Variable">.

It has no arguments. The return type is the same as the type of the class variable except that the type of the field is the L<byte type|SPVM::Document::Language::Types/"byte Type"> or the L<short type|short Type>.

If the type of the class variable is the L<byte type|SPVM::Document::Language::Types/"byte Type"> or the L<short type|short Type>, the return type is the int type.

It is defined by the C<ro> or C<rw> L<class variable attributes|/"Class Variable Attributes">.

It is a method that name is the same as the class variable name removing C<$>. For example, if the class variable name is $FOO, its getter method name is C<FOO>.

Examples:

  # Class variable getter method
  class Foo {
    our $NUM : ro int;
    
    static method main : void {
      my $num = Foo->NUM;
    }
  }

=head4 Class Variable Setter Method

A class variable setter method is a method to perform the operation of the L<setting a class variable|SPVM::Document::Language::Operators/"Setting a Class Variable">.

The return type is the L<void type|SPVM::Document::Language::Types/"void Type">.

It has an argument that type is the same as the type of the class variableexcept that the type of the field is the L<byte type|SPVM::Document::Language::Types/"byte Type"> or the L<short type|short Type>.

If the type of the class variable is the L<byte type|SPVM::Document::Language::Types/"byte Type"> or the L<short type|short Type>, the argument type is the int type.

It is defined by the C<wo>  or C<rw> L<class variable attributes|/"Class Variable Attributes">.

It is a method that name is the same as the class variable name removing C<$> and adding C<SET_> to the beginning. For example, if the class variable name is $FOO, its setter method name is C<SET_FOO>.

Examples:

  # Class variable setter method
  class Foo {
    our $NUM : wo int;
    
    static method main : void {
      Foo->SET_NUM(3);
    }
  }

=head2 Field

Fields are the data that an object has.

=head3 Field Definition

The C<has> keyword defines a field.
  
  # The field definition
  has FIELD_NAME : OPT_ATTRIBUTES TYPE;
  
  # An examples
  has name : string;
  has age : protected int;
  has max : protected rw int

The field is defined directly under the L<class block|/"Class Block">.

  class MyClass {
    has name : string;
  }

L<Field attributes|/"Field Attributes"> can be specified.

Compilation Errors:

The field definition needs the L<type|SPVM::Document::Language::Types/"Types">. The type must be a L<numeric type|SPVM::Document::Language::Types/"Numeric Type"> or an L<object type|SPVM::Document::Language::Types/"Object Types">. Otherwise a compilation error occurs.

The field names must follows the rule of the L<field name|/"Field Name">. Otherwise a compilation error occurs.

Field names cannot be duplicated. If so, a compilation error occurs.

=head3 Field Attributes

The list of field attributes.

=begin html

<table>
  <tr>
    <th>
      Field Attributes
   </th>
    <th>
      Descriptions
   </th>
  </tr>
  <tr>
    <td>
      <b>private</b>
    </td>
    <td>
      This field is private. This field cannnot be accessed from other class. This is default setting.
    </td>
  </tr>
  <tr>
    <td>
      <b>protected</b>
    </td>
    <td>
      This field is protected. This field cannnot be accessed from other class except for the child classes.
    </td>
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
      <b>ro</b>
    </td>
    <td>
      This field has its getter method. The getter method name is the same as the field name. For example, If the field names is <code>foo</code>, The getter method name is C<foo>.
    </td>
  </tr>
  <tr>
    <td>
      <b>wo</b>
    </td>
    <td>
      This field has its setter method. The setter method name is the same as field names adding <code>set_</code> to top. For example, If the field names is <code>foo</code>, The setter method name is <code>set_foo</code>.
    </td>
  </tr>
  <tr>
    <td>
      <b>rw</b>
    </td>
    <td>
      This field has its getter method and its setter method.
    </td>
  </tr>
</table>

=end html

A field getter method is an L<instance method|/"Instance Method">. It has no arguments. The return type of a field getter method is the same as its field type, except for the C<byte> and C<short> type.

If the type of the field is the C<byte> or C<short> type, The return type of a field getter method is the C<int> type.

A field setter method is an L<instance method|/"Instance Method">. It has an argument. The type of the argument is the same as the field type. The return type is the L<void type|SPVM::Document::Language::Types/"void Type">.

If the type of the field is the C<byte> or C<short> type, The argument type of a field setter method is the C<int> type.

Compilation Errors:

Only one of field attributes C<private>, C<protected> or C<public> can be specified. Otherwise a compilation error occurs.

If more than one of C<ro>, C<wo>, and C<rw> are specified at the same time, a compilation error occurs

Examples:

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

=head4 Field Getter Method

A field getter method is a method to perform the operation of the L<getting a field|SPVM::Document::Language::Operators/"Getting a Field">.

It has no arguments. The return type is the same as the type of the field except that the type of the field is the L<byte type|SPVM::Document::Language::Types/"byte Type"> or the L<short type|short Type>.

If the type of the field is the L<byte type|SPVM::Document::Language::Types/"byte Type"> or the L<short type|short Type>, the return type is the int type.

It is defined by the C<ro> or C<rw> L<field attributes|/"Field Attributes">.

It is a method that name is the same as the field name.

Examples:

  # Field getter method
  class Foo {
    has num : ro int;
    
    static method new {
      return new Foo;
    }
    
    static method main : void {
      my $foo = Foo->new;
      
      my $num = $foo->num;
    }
  }

=head4 Field Setter Method

A field setter method is a method to perform the operation of the L<setting a field|SPVM::Document::Language::Operators/"Setting a Field">.

The return type is the L<void type|SPVM::Document::Language::Types/"void Type">.

It has an argument that type is the same as the type of the fieldexcept that the type of the field is the L<byte type|SPVM::Document::Language::Types/"byte Type"> or the L<short type|short Type>.

If the type of the field is the L<byte type|SPVM::Document::Language::Types/"byte Type"> or the L<short type|short Type>, the argument type is the int type.

It is defined by the C<wo>  or C<rw> L<field attributes|/"Field Attributes">.

It is a method that name is the same as the field name, but prepend C<set_> to it. For example, if the field name is C<foo>, its setter method name is C<set_foo>.

Examples:

  # Field setter method
  class Foo {
    has num : wo int;
    
    static method new {
      return new Foo;
    }
    
    static method main : void {
      my $foo = Foo->new;
      
      $foo->set_num(3);
    }
  }

=head2 Method

=head3 Method Definition

The C<method> keyword defines a class method or an instance method.
  
  # Static method
  static method METHOD_NAME : RETURN_TYPE (ARG_NAME1 : ARG_TYPE1, ARG_NAME2 : ARG_TYPE2, ...) {
    
  }

  # Instance method
  method METHOD_NAME : RETURN_TYPE (ARG_NAME1 : ARG_TYPE1, ARG_NAME2 : ARG_TYPE2, ...) {
    
  }

Methods must be defined directly under the L<class definition|/"Class Definition">.

Method names must be follow the rule of L</"Method Name">.

The argument names must be follow the rule of L</"Local Variable Name">.

The minimal length of arguments is 0. The max length of arguments is 255.

Defined methods can be called using L</"Method Call"> syntax.

A method can have L<method attributes|/"Method Attributes">.

  ATTRIBUTES static method METHOD_NAME : RETURN_TYPE (ARG_NAME1 : ARG_TYPE1, ARG_NAME2 : ARG_TYPE2, ...) {
  
  }

A method has L</"Method Block"> except for the case that the method has the C<native> L<method attributes|/"Method Attributes">. 

Compilation Errors:

The types of the arguments must be a L<numeric type|SPVM::Document::Language::Types/"Numeric Type">, the L<multi-numeric type|SPVM::Document::Language::Types/"Multi-Numeric Type">, an L<object type|SPVM::Document::Language::Types/"Object Types">, or a L<reference type|SPVM::Document::Language::Types/"Reference Type">. Otherwise a compilation error occurs.

The type of the return value must be the L<void type|SPVM::Document::Language::Types/"void Type">, a L<numeric type|SPVM::Document::Language::Types/"Numeric Type">, the L<multi-numeric type|SPVM::Document::Language::Types/"Multi-Numeric Type"> or an L<object type|SPVM::Document::Language::Types/"Object Types">. Otherwise a compilation error occurs.

=head4 Optional Arguments

The optional argument is the syntax to specify optional arguments.

  static method METHOD_NAME : RETURN_TYPE (ARG_NAME1 : ARG_TYPE1, ARG_NAME2 : ARG_TYPE2 = DEFAULT_VALUE) {
  
  }
  
  # Deprecated
  static method METHOD_NAME : RETURN_TYPE (ARG_NAME1 : ARG_TYPE1, ARG_NAME2 = DEFAULT_VALUE : ARG_TYPE2) {
  
  }

Examples:

  static method substr ($string : string, $offset : int, $length : int = -1) {
    # ...
  }
  
  my $string = "abc";
  my $offset = 1;
  my $substr = &substr($string, $offset);
  
  # This is the same as the following code
  my $string = "abc";
  my $offset = 1;
  my $length = -1;
  my $substr = &substr($string, $offset, $length);
  
=head3 Class Method

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

=head3 Instance Method

An instance method is defined without the C<static> keyword.

  method add_chunk : void ($chunk : string) {
    # ...
  }

An instance method can be called from the object.
  
  # Call an instance method
  my $point = Point->new;
  $point->set_x(3);

=head3 Method Attributes

Method attributes are attributes used in a L<method definition|/"Method Definition">.

=begin html

<table>
  <tr>
    <th>
      Method Attributes
   </th>
    <th>
      Descriptions
   </th>
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
      <b>protected</b>
    </td>
    <td>
      This method is protected. This method can not be accessed from other classes except for the child classes.
    </td>
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

If C<native> and C<precompile> attributes cannnot used together.

C<required> can be only used in a method of a L<interface|/"Interface">.

Compilation Errors:

Only one of method attributes C<private>, C<protected> or C<public> can be specified. Otherwise a compilation error occurs.

If the specifed attribute is not found or the way to specify is invalid, a compilation error occurs.

Examples:
  
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

=head3 INIT Block

The C<INIT> block defines a C<INIT> method to be executed just after the program starts.

  INIT {
    
  }

The C<INIT> block must be defined directly under the L<class definition|/"Class Definition">.

  class Foo {
    INIT {
      
    }
  }

Zero or more L<statements|SPVM::Document::Language::Statements/"Statements"> can be written in a C<INIT> block.

  INIT {
    my $foo = 1 + 1;
    my $bar;
  }

The L<return statement|SPVM::Document::Language::Statements/"return Statement"> cannot be written in C<INIT> block.

If a C<INIT> block is not defined in a class, a default empty C<INIT> block is defined.

An C<INIT> block is editted.

If a parent class exists, the INIT block of the parent class is called at the beginning of the INIT block.

If classes are used by the L<use statement|/"use Statement">, the L<interface statement|/"interface Statement">, and the L<allow statement|/"allow Statement">, The INIT blocks in the classes are called in order after the above calling.
  
  # Before Editting
  class MyClass extends ParentClass {
    use Foo;
    use Bar;
    
    INIT {
      $POINT = Point->new(1, 2);
    }
  }

  # After Editting
  class MyClass extends ParentClass {
    use Point;
    use Fn;
    
    INIT {
      ParentClass->INIT;
      Point->INIT;
      Fn->INIT;
      
      $POINT = Point->new(1, 2);
    }
  }

An C<INIT> block is automatically called only once.

The execution order of C<INIT> blocks is not guaranteed. The INIT blocks in the L<default loaded class/"Default Loaded Classes"> are called before INIT blocks of user defined classes.

Examples:

  class Foo {
    use Point;
    
    our $NUM : int;
    our $STRING : string;
    our $POINT : Point;
    
    # INIT block
    INIT {
      $NUM = 3;
      $STRING = "abc";
      
      $POINT = Point->new(1, 2);
    }
  }

=head3 Destructor

A L<class|/"Class"> can have a destructor.

  method DESTROY : void () {
  
  }

The destructor is the method that is called when the object is destroyed by the L<garbage collection|SPVM::Document::Language::GarbageCollection/"Garbage Collection">.

The name of the destructor must be C<DESTROY>.

A destructor cannnot have its arguments.

The retrun type must be L<void type|SPVM::Document::Language::Types/"void Type">.

A destructor must be an L<instance method|/"Instance Method">.

If an L<exception|SPVM::Document::Language::ExceptionHandling/"Exception Handling"> occurs in the destructor, the exception is not thrown. Instead, a warnings message is printed to C<STDERR>.

Compilation Errors:

If the definition of the destructor is invalid, a compilation error occurs.

Examples:
  
  # Destructor
  class Foo {
    method DESTROY : void () {
      print "DESTROY";
    }
  }

The child class inherits the destructor of the parent class if the destructor of the current class doesn't eixst.

=head3 Method Override

An instance method in a parent class can be overridden by an instance method with the same name in a child class.

  class ChildClass extends ParentClass {
    # Method Override
    method clear : void () {
      # ...
    }
  }

  class ParentClass {
    
    method clear : void () {
      # ...
    }
  }

The overridding method in the child class must satisfy the L<interface requirement|/"Interface Requirement"> to the parent method.

Compilation Errors:

The overridding method in the child class must satisfy the L<interface requirement|/"Interface Requirement"> to the parent method, otherwise a compilation error occurs.

=head3 Anon Method

The anon method operator defines an L<anon calss|SPVM::Document::Language::Class/"Anon Class"> that has an anon instance method.

And this operator creates an object which type is the anon class by the L<new/"new Operator"> operator, and returns it.
  
  # Anon method
  method : TYPE  (VAR1 : TYPE1, VAR2 : TYPE2, ...) {
  
  }

The way to define the method is the same as the L<method definition|SPVM::Document::Language::Class/"Method Definition">.

Examples:
  
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

The above example is the same as the following codes.
  
  # Foo/Bar.spvm
  class Foo::Bar {
    method some_method : void () {
      my $comparator = (Comparator)new Foo::Bar::anon::3::31;
    }
  }
  
  # Foo/Bar/anon/3/31.spvm
  class Foo::Bar::anon::3::31 : public {
    method : int ($x1 : object, $x2 : object) {
      my $point1 = (Point)$x1;
      my $point2 = (Point)$x2;
      
      return $point1->x <=> $point2->x;
    }
  }

=head4 Anon Method Field Definition

The anon method field definition is the syntax to define the field of the anon class of the anon method.

  # Anon method field definitions
  [has FIELD_NAME : TYPE1, has FIELD_NAME : TYPE2, ...] ANON_METHOD_DEFINITION
  
  # Anon method field definitions with field default values
  [has FIELD_NAME : TYPE1 = OPERAND1, has FIELD_NAME : TYPE2 = OPERAND2, ...] ANON_METHOD_DEFINITION
  
  [VAR1 : TYPE1, VAR2 : TYPE2, ...] ANON_METHOD_DEFINITION
  
Examples:

  class Foo::Bar {
    method some_method : void () {
      my $foo = 1;
      my $bar = 5L;
      
      my $comparator = (Comparator)[has foo : int = $foo, has bar : long = $bar] method : int ($x1 : object, $x2 : object) {
        my $foo = $self->{foo};
        my $bar = $self->{bar};
        
        print "$foo\n";
        print "$bar\n";
      };
    }
  }

Same as avobe but more simple:

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

The above example is the same as the following codes.

  # Foo/Bar.spvm
  class Foo::Bar {
    method some_method : void () {
      # Externally defined local variables
      my $foo = 1;
      my $bar = 5L;
      
      my $anon = new Foo::Bar::anon::5::61;
      $anon->{foo} = $foo;
      $anon->{bar} = $bar;
      
      my $comparator = (Comparator)$anon;
    }
  }
  
  # Foo/Bar/anon/5/61.spvm
  class Foo::Bar::anon::5::61 : public {
    has foo : public int;
    has bar : public long;
    
    method : int ($x1 : object, $x2 : object) {
      my $foo = $self->{foo};
      my $bar = $self->{bar};
      
      print "$foo\n";
      print "$bar\n";
    }
  }

=head3 Native Method

A native method is the method that is written by native languages such as the C language, C<C++>.

A native method is defined by the C<native> L<method attribute|/"Method Attributes">.

  native sum : int ($num1 : int, $num2 : int);

A native method doesn't have its L<method block|/"Method Block">.

About the way to write native methods, please see L<SPVM Native Class|SPVM::Document::NativeClass> and L<SPVM Native API|SPVM::Document::NativeAPI>.

=head3 Precompilation Method

If the class has the C<precompile> L<class attribute|/"Class Attributes">, the methods of the class are precompiled.

The source code of each precompiled method is translated to C source code and is compiled to the machine code such as C<MyMath.o>.

And it is linked to a shared library such as C<MyMath.so> on Linux/Unix, C<MyMath.dll> on Windows, or C<MyMath.dylib> on Mac.

And each function in the shared library is bind to the SPVM method.

Precompiled methods need the L<build directory|SPVM/"SPVM_BUILD_DIR"> such as C<~/.spvm_build> to compile and link them.

=head3 Bootstrap Method

A bootstrap method is the methods where the program start.

  void main : void () {
    
  }

The method name is C<main>.

The return type is the void type.

It has no arguments.

=head2 Method Implementation

Normally a method has a method block. L<Statements|SPVM::Document::Language::Statements/"Statements"> can be written in a method block.
  
  # Method implementation
  static method foo : int ($num1 : int, $num2 : int) {
    
    my $total = $num1 + $num2;
    
    return $total;
  }

=head3 Local Variable

A local variable is a variable that has a L<scope|SPVM::Document::Language::GarbageCollection/"Scope">.

=head3 Local Variable Declaration

B<Local Variable> is a variable that is declared in L</"Scope Block">.  Local Variable has the L<scope|SPVM::Document::Language::GarbageCollection/"Scope">. This is the same as Local Variable in C Language.

The local variable is declared using B<my> L</"Keyword">.

  my LOCAL_VARIABLE_NAME : TYPE;

The local variable name must be follow the rule of L</"Local Variable Name">.

the L<type|SPVM::Document::Language::Types/"Types"> must be specified. Type must be a L<numeric type|SPVM::Document::Language::Types/"Numeric Type">, an L<object type|SPVM::Document::Language::Types/"Object Types">, the L<multi-numeric type|SPVM::Document::Language::Types/"Multi-Numeric Type">, or a L<reference type|SPVM::Document::Language::Types/"Reference Type">.

  # Local Variable Declaration Examples
  my $var : int;
  my $var : Point;
  my $var : Complex_2d;
  my $var : int*;

The local variable is initialized by L<type initial value|SPVM::Document::Language::Types/"Type Initial Value">.

  # Initialized by 0
  my $num : int;
  
  # Initialized by 0
  my $num : double;
  
  # Initialized by undef
  my $point : Point;
  
  # x is initialized by 0. y is initialized by 0.
  my $z : Complex_2d;

The initialization of the local variable can be written at the same time as the local variable declaration.

  # Initialized by 1
  my $num : int = 1;
  
  # Initialized by 2.5
  my $num : double = 2.5;
  
  # Initialized by Point object
  my $point : Point = new Point;

The L<type|SPVM::Document::Language::Types/"Types"> can be omitted using the L<type inference|SPVM::Document::Language::Types/"Type Inference">, 

  # Type inference - int
  my $num = 1;
  
  # Type inference - double
  my $num = 1.0;

The local variable declaration returns the value of the local variable. The return type is the type of the local variable.

  my $ppp = my $bar = 4;
  
  if (my $bar = 1) {
  
  }
  
  while (my $bar = 1) {
  
  }

See the L<scope|SPVM::Document::Language::GarbageCollection/"Scope"> about the scope of the local variable.

=head3 Type Inference

If the type of the local variable declaration is ommited, the type of the right operand of the assignment operator is set to it. This is called type inference.

  # int
  my $num = 1;
  
  # double
  my $num = 1.0;
  
  # Foo
  my $foo = new Foo;

=head3 Local Variable Access

The local variable access has the following syntax.

  $var

I<$var> is a L<local variable name|SPVM::Document::Language::Tokenization/"Local Variable Name">.

If local variables with the same name are declared in different scopes, the local variable declared in the inner scope is accessed.

If a class variable with the same name as a local variable is defined, the local variable is accessed.

See also L</"Getting a Local Variable"> and L</"Setting a Local Variable"> about the way to set and set a local variable.

Compilation Errors:

I<$var> must be a valid local variable name, otherwise a compilation error occurs.

The declaration of I<$var> must exists before I<$var>, otherwise a compilation error occurs.

=head3 Class Variable Access

The class variable access has the following syntax.

  $VAR

I<$VAR> is a L<class variable name|SPVM::Document::Language::Tokenization/"Class Variable Name">.

If the class name is ommited, the class is set to the L<outmost class|/"Outmost Class">.

See also L</"Getting a Class Variable"> and L</"Setting a Class Variable"> about the way to set and set a class variable.

Compilation Errors:

I<$VAR> must be a valid class variable name, otherwise a compilation error occurs.

The class specified by I<$VAR> must be loaded, otherwise a compilation error occurs.

The class variable relative name specified by I<$VAR> must be defined in the class specified by I<$VAR>, otherwise a compilation error occurs.

The L<outmost class|/"Outmost Class"> must be allowed access to I<$VAR>, otherwise a compilation error occurs.

=head3 Element Access

The element access has the following syntax.

  ARRAY->[INDEX]

The type of the array I<ARRAY> is an array type.

The type of the index I<INDEX> is an L<integer type|SPVM::Document::Language::Types/"Integer Types"> within int.

See also L</"Getting an Array Element"> and L</"Setting an Array Element"> about the way to set and set an array element.

Compilation Errors:

I<ARRAY> must be an array type, otherwise a compilation error occurs.

I<INDEX> must be an L<integer type|SPVM::Document::Language::Types/"Integer Types"> within int, otherwise a compilation error occurs.

=head3 Character Access

The character access has the following syntax.

  STRING->[INDEX]

The type of the string I<STRING> is the string type.

The type of the index I<INDEX> is an L<integer type|SPVM::Document::Language::Types/"Integer Types"> within int.

See also L</"Getting a Character"> and L</"Setting a Character"> about the way to set and set a character of a string.

Compilation Errors:

I<STRING> must be the string type, otherwise a compilation error occurs.

I<INDEX> must be an L<integer type|SPVM::Document::Language::Types/"Integer Types"> within int, otherwise a compilation error occurs.

=head3 Field Access

The field access has the following syntax.

  INVOCANT->{FIELD_NAME}

I<INVOCANT> is an object of a L<class type|SPVM::Document::Language::Types/"Class Type">, a value of a L<multi-numeric type|SPVM::Document::Language::Types/"Multi-Numeric Type">, a value of a L<multi-numeric reference type|SPVM::Document::Language::Types/"Multi-Numeric Reference Type">.

I<FIELD_NAME> is a L<field name|SPVM::Document::Language::Tokenization/"Field Name">.

Compilation Errors:

I<INVOCANT> must be an object of a L<class type|SPVM::Document::Language::Types/"Class Type">, a value of a L<multi-numeric type|SPVM::Document::Language::Types/"Multi-Numeric Type">, a value of a L<multi-numeric reference type|SPVM::Document::Language::Types/"Multi-Numeric Reference Type">, otherwise a compilation error occurs.

Depending on the type of I<INVOCANT>, there are the following field access.

=head4 Field Access for Class Types

See L</"Getting a Field"> and L</"Setting a Field"> to get and set the value of the field of the class type.

Compilation Errors:

If the type of I<INVOCANT> is a class type, the field specified by I<FIELD_NAME> must be defined in the class, or its super classes, otherwise a compilation error occurs.

=head4 Field Access for Multi-Numeric Types

See L</"Getting a Multi-Numeric Field"> and L</"Setting a Multi-Numeric Field"> to get and set the value of the field of the L<multi-numeric type|SPVM::Document::Language::Types/"Multi-Numeric Type">.

Compilation Errors:

If the type of I<INVOCANT> is a multi-numeric type, the field specified by I<FIELD_NAME> must be defined in the multi-numeric type, otherwise a compilation error occurs.

=head4 Field Access for Multi-Numeric Reference Types

See L</"Getting a Referenced Multi-Numeric Field"> and L</"Setting a Referenced Multi-Numeric Field"> to get and set the value of the field referenced by the L<multi-numeric reference type|SPVM::Document::Language::Types/"Multi-Numeric Reference Type">.

Compilation Errors:

If the type of I<INVOCANT> is a multi-numeric reference type, the field specified by I<FIELD_NAME> must be defined in the multi-numeric type referenced by the multi-numeric reference type, otherwise a compilation error occurs.

=head2 Block

A block is the part enclosed by C<{> and C<}>.

=head3 Class Block

A class block is a block used in a class definition.
  
  # Class block
  class Point {
  
  }

=head3 Enumeration Block

An enumeration block is a block used in a enumeration definition.

  # Enumeration block
  enum {
    ONE,
    TWO,
  }

=head3 Scope Block

The scope block has its L<scope|SPVM::Document::Language::GarbageCollection/"Scope">. Zero or more L<statements|SPVM::Document::Language::Statements/"Statements"> are written in a scope block.

=head4 Simple Block

The simple block is a L<scope block|/"Scope Block">.

  # Simple block
  {
    1;
  }

The simple block must have at least one statements. Otherwise it is intepreted as the L<array initialization|SPVM::Document::Language::Operators/"The array Initialization">.

=head4 Method Block

The method block is a L<scope block|/"Scope Block">.

  # Method block
  static method foo : int () {
  
  }

The block of C<INIT> method is a method block.

  INIT {
    
  }

=head4 eval Block

The C<eval> block is a L<scope block|/"Scope Block">.

  # eval block
  eval {
  
  }

=head4 if Block

The C<if> block is a L<scope block|/"Scope Block">.

  # if block
  if (CONDITION) {
  
  }

=head4 elsif Block

The C<elsif> block is a L<scope block|/"Scope Block">.

  # elsif block
  elsif (CONDITION) {
  
  }

=head4 else Block

The C<else> block is a L<scope block|/"Scope Block">.

  # else block
  else {
  
  }

=head4 for Block

The C<for> block is a L<scope block|/"Scope Block">.

  # for Block 
  for (my $i = 0; $i < 3; $i++) {
  
  }

=head4 while Block

The C<while> block is a L<scope block|/"Scope Block">.

  # while block
  while (CONDITION) {
  
  }

=head4 switch Block

The C<switch> block is a L<scope block|/"Scope Block">.
  
  # switch block
  switch (CONDITION) {
  
  }

=head4 case Block

The C<case> block is a L<scope block|/"Scope Block">.
  
  # case block
  switch (CONDITION) {
    case CASE_VALUE1: {
      # ...
    }
  }

=head4 default Block

The C<default> block is a L<scope block|/"Scope Block">.
  
  # default block
  switch (CONDITION) {
    default: {
      # ...
    }
  }

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
