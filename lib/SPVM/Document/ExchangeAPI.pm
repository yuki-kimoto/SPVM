=encoding utf8

=head1 Name

SPVM::Document::ExchangeAPI - SPVM Exchange API

=head1 Description

SPVM Exchange API is APIs to convert Perl data structures to/from SPVM data structures, and call SPVM Method from Perl.

=head1 Loading SPVM Module

If you load SVPM module from Perl, use the following syntax.

  use SPVM 'Foo';

Suppose the following C<SPVM/Foo.spvm> is placed on a module search path.

  # SPVM/Foo.spvm
  class Foo {
    static method sum : int ($x1 : int, $x2 : int) {
      return $x1 + $x2;
    }
  }

If you load SPVM C<Foo::Bar> module, do the following.

  use SPVM 'Foo::Bar';

Suppose the following C<SPVM/Foo/Bar.spvm> is placed on a module search path.

  # SPVM/Foo/Bar.spvm
  class Foo::Bar {
    static method sum : int ($x1 : int, $x2 : int) {
      return $x1 + $x2;
    }
  }

C<use SPVM MODULE_NAME> compile the SPVM module and the dependent modules.

Note that at this point a SPVM runtime has not yet been created.

A default SPVM runtime is created the first time you call a method of SPVM module or call a function or method of the Exchange API.

=head1 Calling SPVM Method

The method of SPVM module can be called from Perl directory.

=head2 Calling SPVM Class Method

Let's call SPVM class method from Perl.

  use SPVM 'Foo';

  my $total = SPVM::Foo->sum(1, 2);

The definition of C<Foo> module is the following.

  # SPVM/Foo.spvm
  class Foo {
    static method sum : int ($x1 : int, $x2 : int) {
      return $x1 + $x2;
    }
  }

If the number of arguments does not match the number of arguments of the SPVM method, an exception occurs.

The Perl values of the arguments are converted to the SPVM values by the rule of argument convertion.

If the type is non-conforming, an exception occurs.

The SPVM return value is converted to a Perl return value by the rule of return value convertion.

The SPVM exception is converted to a Perl exception.

=head2 Calling SPVM Instance Method

Let's call SPVM instance method from Perl.

  use SPVM 'Foo';

  my $foo = SPVM::Foo->new;

  my $total = $foo->sum(1, 2);

The definition of C<Foo> module is the following.

  # SPVM/Foo.spvm
  class Foo {
    static method new : Foo () {
      return new Foo;
    }

    method sum : int ($x1 : int, $x2 : int) (
      return $x1 + $x2;
    }
  }

=head1 Argument Conversion

Perl arguments are converted to SPVM arguments in the following rules.

=head2 Argument general exception

If the count of given arguments is less than the count of the arguments of the method, an exception occurs.

If the count of given arguments is more than the count of the arguments of the method, an exception occurs.

=head2 Perl Scalar to SPVM byte

If the SPVM argument type is C<byte>, Perl scalar is converted to SPVM C<byte> value using L<SvIV of perlapi|https://perldoc.perl.org/perlapi#SvIV>

The conversion logic is

  (int8_t)SvIV(perl_scalar)

B<Example:>

  # SPVM method definition
  class MyClass {
    static method foo : void ($value : byte) { ... }
  }
  
  # Perl
  SPVM::MyClass->foo(12);

=head2 Perl Scalar to SPVM short

If the SPVM argument type is C<short>, Perl scalar is converted to SPVM C<short> value using L<SvIV of perlapi|https://perldoc.perl.org/perlapi#SvIV>

The conversion logic is
  
  (int16_t)SvIV(perl_scalar)

B<Example:>

  # SPVM method definition
  class MyClass {
    static method foo : void ($value : short) { ... }
  }
  
  # Perl
  SPVM::MyClass->foo(12);

=head2 Perl Scalar to SPVM int

If the SPVM argument type is C<int>, Perl scalar is converted to SPVM C<int> value using L<SvIV of perlapi|https://perldoc.perl.org/perlapi#SvIV>

The conversion logic is

  (int32_t)SvIV(perl_scalar)

B<Example:>

  # SPVM method definition
  class MyClass {
    static method foo : void ($value : int) { ... }
  }
  
  # Perl
  SPVM::MyClass->foo(12);

=head2 Perl Scalar to SPVM long

If the SPVM argument type is C<long>, Perl scalar is converted to SPVM C<long> value using L<SvIV of perlapi|https://perldoc.perl.org/perlapi#SvIV>

The conversion logic is

  (int64_t)SvIV(perl_scalar)

B<Example:>

  # SPVM method definition
  class MyClass {
    static method foo : void ($value : long) { ... }
  }
  
  # Perl
  SPVM::MyClass->foo(12);

=head2 Perl Scalar to SPVM float

If the SPVM argument type is C<float>, Perl scalar is converted to SPVM C<float> value using L<SvNV of perlapi|https://perldoc.perl.org/perlapi#SvIV>

The conversion logic is

  (float)SvNV(perl_scalar)

B<Example:>

  # SPVM method definition
  class MyClass {
    static method foo : void ($value : float) { ... }
  }
  
  # Perl
  SPVM::MyClass->foo(1.2);

=head2 Perl Scalar to SPVM double

If the SPVM argument type is C<double>, Perl scalar is converted to SPVM C<double> value using L<SvNV of perlapi|https://perldoc.perl.org/perlapi#SvIV>

The conversion logic is

  (double)SvNV(perl_scalar)

B<Example:>

  # SPVM method definition
  class MyClass {
    static method foo : void ($value : double) { ... }
  }
  
  # Perl
  SPVM::MyClass->foo(1.2);

=head2 Perl Scalar to SPVM String

If the SPVM argument type is C<string>, the given Perl scalar is converted by the following rules.

If any of the following rules does not match, an exception occurs.

=head3 Perl Non-Reference Scalar to SPVM String

If the SPVM argument type is C<string>, the given Perl non-ref scalar is converted to L<SPVM::BlessedObject::String> object.

The given non-ref scalar value is assumed to a Perl decoded string, and is converted to UTF-8 bytes.

If the given non-ref scalar value is Perl C<undef>, it is converted to Perl C<undef>.

And the following L</"Perl SPVM::BlessedObject::String to SPVM String"> conversion is contined.

B<Example:>

  # SPVM method definition
  class MyClass {
    static method foo : void ($value : string) { ... }
  }
  
  # Perl
  SPVM::MyClass->foo("あいう");

=head3 Perl SPVM::BlessedObject::String to SPVM String

No conversion occurs.

Perl can have SPVM string itself as L<SPVM::BlessedObject::String> object. This object is created by such as L</"new_string">, L</"new_string_from_bin">, or got as a return value of SPVM method.

If the given value is Perl C<undef>, it is converted to SPVM C<undef>

  # SPVM method definition
  class MyClass {
    static method foo : void ($value : string) { ... }
  }
  
  # Perl
  my $string = $api->new_string("あいう");
  SPVM::MyClass->foo($string);

=head2 Perl SPVM::BlessedObject::Class to SPVM Class

No conversion occurs.

Perl can have SPVM class object itself as a object which inherits L<SPVM::BlessedObject::Class>. This object is created by a contructor such as SPVM::Int->new, SPVM::MyClassClass->new.

If the given value is Perl C<undef>, it is converted to SPVM C<undef>.

If class name is different, an exception occurs.

B<Example:>

  # SPVM method definition
  class MyClass {
    static method foo : void ($value : SPVM::Int) { ... }
  }
  
  # Perl
  my $value = SPVM::Int->new(5);
  SPVM::MyClass->foo($value);

=head2 Perl SPVM::BlessedObject to SPVM Any Object

No conversion occurs.

Perl can have SPVM object itself as a L<SPVM::BlessedObject> object. This object is created by a contructor or functions of exchange API such as SPVM::Int->new, SPVM::MyClassClass->new, $api->new_int_array.

If the given value is Perl C<undef>, it is converted to SPVM C<undef>.

B<Example:>

  # SPVM method definition
  class MyClass {
    static method foo : void ($value : object) { ... }
  }
  
  # Perl
  my $value = SPVM::Int->new(5);
  SPVM::MyClass->foo($value);

=head2 Perl Array Reference to SPVM Array

A Perl array reference is converted to a SPVM array by the following rules.

=head3 Perl Array Reference to SPVM byte Array

If the SPVM argument type is C<byte[]>, the Perl array reference is converted to SPVM array which type is C<byte[]>. Each element is converted to C<byte> value by L<the rule of Perl scalar to SPVM byte|"Perl Scalar to SPVM byte">. Perl C<undef> is coverted to SPVM C<undef>.

B<Example:>

  # SPVM method definition
  class MyClass {
    static method foo : void ($values : byte[]) { ... }
  }
  
  # Perl
  SPVM::MyClass->foo([1, 2, 3]);

=head3 Perl Array Reference to SPVM short Array

If the SPVM argument type is C<short[]>, the Perl array reference is converted to SPVM array which type is C<short[]>. Each element is converted to C<short> value by L<the rule of Perl Scalar to SPVM short|"Perl Scalar to SPVM short">. Perl C<undef> is coverted to SPVM C<undef>.

B<Example:>

  # SPVM method definition
  class MyClass {
    static method foo : void ($values : short[]) { ... }
  }
  
  # Perl
  SPVM::MyClass->foo([1, 2, 3]);

=head3 Perl Array Reference to SPVM int Array

If the SPVM argument type is C<int[]>, the Perl array reference is converted to SPVM array which type is C<int[]>. Each element is converted to C<int> value by L<the rule of Perl scalar to SPVM int|"Perl Scalar to SPVM int">. Perl C<undef> is coverted to SPVM C<undef>.

B<Example:>

  # SPVM method definition
  class MyClass {
    static method foo : void ($values : int[]) { ... }
  }
  
  # Perl
  SPVM::MyClass->foo([1, 2, 3]);

=head3 Perl Array Reference to SPVM long Array

If the SPVM argument type is C<long[]>, the Perl array reference is converted to SPVM array which type is C<long[]>. Each element is converted to C<long> value by L<the rule of Perl scalar to SPVM long|"Perl Scalar to SPVM long">. Perl C<undef> is coverted to SPVM C<undef>.

B<Example:>

  # SPVM method definition
  class MyClass {
    static method foo : void ($values : long[]) { ... }
  }
  
  # Perl
  SPVM::MyClass->foo([1, 2, 3]);

=head3 Perl Array Reference to SPVM float Array

If the SPVM argument type is C<float[]>, the Perl array reference is converted to SPVM array which type is C<float[]>. Each element is converted to C<float> value by L<the rule of Perl scalar to SPVM float|"Perl Scalar to SPVM float">. Perl C<undef> is coverted to SPVM C<undef>.

B<Example:>

  # SPVM method definition
  class MyClass {
    static method foo : void ($values : float[]) { ... }
  }
  
  # Perl
  SPVM::MyClass->foo([1.2, 2.3, 3.4]);

=head3 Perl Array Reference to SPVM double Array

If the SPVM argument type is C<double[]>, the Perl array reference is converted to SPVM array which type is C<double[]>. Each element is converted to C<double> value by L<the rule of Perl scalar to SPVM double|"Perl Scalar to SPVM double">. Perl C<undef> is coverted to SPVM C<undef>.

B<Example:>

  # SPVM method definition
  class MyClass {
    static method foo : void ($values : double[]) { ... }
  }
  
  # Perl
  SPVM::MyClass->foo([1.2, 2.3, 3.4]);

=head3 Perl Array Reference to SPVM String Array

If the SPVM argument type is C<string[]>, the Perl array reference is converted to SPVM array which type is C<string[]>. Each element is converted to C<string> value by L<the rule of Perl scalar to SPVM string|"Perl Scalar to SPVM string">. Perl C<undef> is coverted to SPVM C<undef>.

B<Example:>

  # SPVM method definition
  class MyClass {
    static method foo : void ($values : string[]) { ... }
  }
  
  # Perl
  SPVM::MyClass->foo(["あい", "うえ", "お"]);

=head3 Perl Array Reference to SPVM Multi-Numeric Array

If the SPVM argument type is an array of multi-numeric type, the given Perl array reference is converted to SPVM multi-numeric array which element type is multi-numeric type. Each element which is a hash reference is converted to multi-numeric type by L<the rule of Perl hash reference to SPVM multi-numeric type|"Perl hash reference to SPVM multi-numeric type">. Perl C<undef> is coverted to SPVM C<undef>.

B<Example:>

  # SPVM method definition
  class MyClass {
    static method foo : void ($values : Complex_2d[]) { ... }
  }
  
  # Perl
  SPVM::MyClass->foo([{re => 1.2, im => 2.3}, {re => 3.4, im => 4.5}]);

=head2 Perl SPVM::BlessedObject::Array to SPVM Array

No conversion occurs.

Perl can have SPVM array itself as L<SPVM::BlessedObject::Array> object. This object is created by such as L</"new_byte_array">, L</"new_short_array">, L</"new_int_array">, L</"new_long_array">, L</"new_float_array">, L</"new_double_array">, or got as a return value of SPVM method.

B<Example:>

  # SPVM method definition
  class MyClass {
    static method foo : void ($values : int[]) { ... }
  }
  
  # Perl
  my $array = $api->new_int_array([1, 2, 3]);
  SPVM::MyClass->foo($array);

=head2 Perl Hash Reference to SPVM Multi-Numeric

If the SPVM argument type is a multi-numeric type, the given argument is converted by the following rules.

=head3 Perl Hash Reference to SPVM multi-numeric byte

If the argument type is a multi-numeric byte type, the given argument is hash reference is converted to the value of SPVM multi-numeric byte type. If the given argument is different from a hash reference, an exception occurs. Each field is converted to C<byte> value by L<the rule of Perl scalar to SPVM byte|"Perl Scalar to SPVM byte">.

If a filed is missing, an exception occurs.

B<Example:>

  # SPVM multi-numeric type and method definition
  class MyClassPoint_2b {
    has x : byte;
    has y : byte;
  }
  class MyClass {
    static method foo : void ($value : MyClassPoint_2b);
  }

  # Perl
  SPVM::MyClass->foo({x => 1, y => 2});

=head3 Perl Hash Reference to SPVM Multi-Numeric short

If the argument type is a multi-numeric short type, the given argument is hash reference is converted to the value of SPVM multi-numeric short type. If the given argument is different from a hash reference, an exception occurs. Each field is converted to C<short> value by L<the rule of Perl scalar to SPVM short|"Perl Scalar to SPVM short">.

If a filed is missing, an exception occurs.

B<Example:>

  # SPVM multi-numeric type and method definition
  class MyClassPoint_2s {
    has x : short;
    has y : short;
  }
  class MyClass {
    static method foo : void ($value : MyClassPoint_2s);
  }

  # Perl
  SPVM::MyClass->foo({x => 1, y => 2});

=head3 Perl Hash Reference to SPVM Multi-Numeric int

If the argument type is a multi-numeric int type, the given argument is hash reference is converted to the value of SPVM multi-numeric int type. If the given argument is different from a hash reference, an exception occurs. Each field is converted to C<int> value by L<the rule of Perl scalar to SPVM int|"Perl Scalar to SPVM int">.

If a filed is missing, an exception occurs.

B<Example:>

  # SPVM multi-numeric type and method definition
  class MyClassPoint_2i {
    has x : int;
    has y : int;
  }
  class MyClass {
    static method foo : void ($value : MyClassPoint_2i);
  }

  # Perl
  SPVM::MyClass->foo({x => 1, y => 2});

=head3 Perl Hash Reference to SPVM Multi-Numeric long

If the argument type is a multi-numeric long type, the given argument is hash reference is converted to the value of SPVM multi-numeric long type. If the given argument is different from a hash reference, an exception occurs. Each field is converted to C<long> value by L<the rule of Perl scalar to SPVM long|"Perl Scalar to SPVM long">.

If a filed is missing, an exception occurs.

B<Example:>

  # SPVM multi-numeric type and method definition
  class MyClassPoint_2l {
    has x : long;
    has y : long;
  }
  class MyClass {
    static method foo : void ($value : MyClassPoint_2l);
  }

  # Perl
  SPVM::MyClass->foo({x => 1, y => 2});

=head3 Perl Hash Reference to SPVM Multi-Numeric float

If the argument type is a multi-numeric float type, the given argument is hash reference is converted to the value of SPVM multi-numeric float type. If the given argument is different from a hash reference, an exception occurs. Each field is converted to C<float> value by L<the rule of Perl scalar to SPVM float|"Perl Scalar to SPVM float">.

If a filed is missing, an exception occurs.

B<Example:>

  # SPVM multi-numeric type and method definition
  class MyClassPoint_2f {
    has x : float;
    has y : float;
  }
  class MyClass {
    static method foo : void ($value : MyClassPoint_2f);
  }

  # Perl
  SPVM::MyClass->foo({x => 1.2, y => 2.3});

=head3 Perl Hash Reference to SPVM Multi-Numeric double

If the argument type is a multi-numeric double type, the given argument is hash reference is converted to the value of SPVM multi-numeric double type. If the given argument is different from a hash reference, an exception occurs. Each field is converted to C<double> value by L<the rule of Perl scalar to SPVM double|"Perl Scalar to SPVM double">.

If a filed is missing, an exception occurs.

B<Example:>

  # SPVM multi-numeric type and method definition
  class MyClassPoint_2d {
    has x : double;
    has y : double;
  }
  class MyClass {
    static method foo : void ($value : MyClassPoint_2d);
  }

  # Perl
  SPVM::MyClass->foo({x => 1.2, y => 2.3});

=head2 Perl Reference to SPVM Numeric Reference

If the SPVM argument type is numeric reference type, the given Perl reference is converted to SPVM numeric reference type in the following rules.

=head3 Perl Reference to SPVM byte Reference

If the SPVM argument type is byte reference type, the given Perl reference is converted to SPVM byte reference type.

The given value must be a scalar reference which referenced value is non-ref scalar. Otherwise an exception will occur.

The given value is converted to C<byte> value by L<the rule of Perl scalar to SPVM byte|"Perl Scalar to SPVM byte"> and return value is converted to Perl scalar by L<the rule of SPVM byte to Perl Scalar|"SPVM byte to Perl scalar">

B<Example:>

  # SPVM method definition
  class MyClass {
    static method foo : void ($value : byte*);
  }

  # Perl
  my $value = 23;
  SPVM::MyClass->foo(\$value);

=head3 Perl Reference to SPVM short Reference

If the SPVM argument type is short reference type, the given Perl reference is converted to SPVM short reference type.

The given value must be a scalar reference which referenced value is non-ref scalar. Otherwise an exception will occur.

The given value is converted to C<short> value by L<the rule of Perl scalar to SPVM short|"Perl Scalar to SPVM short"> and return value is converted to Perl scalar by L<the rule of SPVM short to Perl Scalar|"SPVM short to Perl scalar">

B<Example:>

  # SPVM method definition
  class MyClass {
    static method foo : void ($value : short*);
  }

  # Perl
  my $value = 23;
  SPVM::MyClass->foo(\$value);

=head3 Perl Reference to SPVM int Reference

If the SPVM argument type is int reference type, the given Perl reference is converted to SPVM int reference type.

The given value must be a scalar reference which referenced value is non-ref scalar. Otherwise an exception will occur.

The given value is converted to C<int> value by L<the rule of Perl scalar to SPVM int|"Perl Scalar to SPVM int"> and return value is converted to Perl scalar by L<the rule of SPVM int to Perl Scalar|"SPVM int to Perl scalar">

B<Example:>

  # SPVM method definition
  class MyClass {
    static method foo : void ($value : int*);
  }

  # Perl
  my $value = 23;
  SPVM::MyClass->foo(\$value);

=head3 Perl Reference to SPVM long Reference

If the SPVM argument type is long reference type, the given Perl reference is converted to SPVM long reference type.

The given value must be a scalar reference which referenced value is non-ref scalar. Otherwise an exception will occur.

The given value is converted to C<long> value by L<the rule of Perl scalar to SPVM long|"Perl Scalar to SPVM long"> and return value is converted to Perl scalar by L<the rule of SPVM long to Perl Scalar|"SPVM long to Perl scalar">

B<Example:>

  # SPVM method definition
  class MyClass {
    static method foo : void ($value : long*);
  }

  # Perl
  my $value = 23;
  SPVM::MyClass->foo(\$value);

=head3 Perl Reference to SPVM float Reference

If the SPVM argument type is float reference type, the given Perl reference is converted to SPVM float reference type.

The given value must be a scalar reference which referenced value is non-ref scalar. Otherwise an exception will occur.

The given value is converted to C<float> value by L<the rule of Perl scalar to SPVM float|"Perl Scalar to SPVM float"> and return value is converted to Perl scalar by L<the rule of SPVM float to Perl Scalar|"SPVM float to Perl scalar">

B<Example:>

  # SPVM method definition
  class MyClass {
    static method foo : void ($value : float*);
  }

  # Perl
  my $value = 23.5;
  SPVM::MyClass->foo(\$value);

=head3 Perl Reference to SPVM double Reference

If the SPVM argument type is double reference type, the given Perl reference is converted to SPVM double reference type.

The given value must be a scalar reference which referenced value is non-ref scalar. Otherwise an exception will occur.

The given value is converted to C<double> value by L<the rule of Perl scalar to SPVM double|"Perl Scalar to SPVM double"> and return value is converted to Perl scalar by L<the rule of SPVM double to Perl Scalar|"SPVM double to Perl scalar">

B<Example:>

  # SPVM method definition
  class MyClass {
    static method foo : void ($value : double*);
  }

  # Perl
  my $value = 23.5;
  SPVM::MyClass->foo(\$value);

=head2 Perl Reference to SPVM Multi-Numeric Reference

If the SPVM argument type is multi-numeric reference type, the given Perl reference is converted by the following rules.

=head3 Perl Reference to SPVM multi-numeric byte reference

If the SPVM argument type is multi-numeric byte reference type, the given Perl reference is converted to SPVM multi-numeric byte reference type.

The given reference must be a scalar reference of hash reference. Otherwise an exception will occur.

The each field of the hash of the given argument is converted to C<byte> value by L<the rule of Perl scalar to SPVM byte|"Perl Scalar to SPVM byte"> and the each filed of the return value is converted to Perl scalar by L<the rule of SPVM byte to Perl Scalar|"SPVM byte to Perl scalar">

If a field is missing, an exception occurs.

B<Example:>

  # SPVM multi-numeric type and method definition
  class MyClassPoint_2b {
    has x : byte;
    has y : byte;
  }
  class MyClass {
    static method foo : void ($value : MyClassPoint_2b);
  }

  # Perl
  my $value = {x => 1, y => 2};
  SPVM::MyClass->foo(\$value);

=head3 Perl Reference to SPVM Multi-Numeric short Reference

If the SPVM argument type is multi-numeric short reference type, the given Perl reference is converted to SPVM multi-numeric short reference type.

The given reference must be a scalar reference of hash reference. Otherwise an exception will occur.

The each field of the hash of the given argument is converted to C<short> value by L<the rule of Perl scalar to SPVM short|"Perl Scalar to SPVM short"> and the each filed of the return value is converted to Perl scalar by L<the rule of SPVM short to Perl Scalar|"SPVM short to Perl scalar">

If a field is missing, an exception occurs.

B<Example:>

  # SPVM multi-numeric type and method definition
  class MyClassPoint_2s {
    has x : short;
    has y : short;
  }
  class MyClass {
    static method foo : void ($value : MyClassPoint_2s);
  }

  # Perl
  my $value = {x => 1, y => 2};
  SPVM::MyClass->foo(\$value);

=head3 Perl Reference to SPVM Multi-Numeric int Reference

If the SPVM argument type is multi-numeric int reference type, the given Perl reference is converted to SPVM multi-numeric int reference type.

The given reference must be a scalar reference of hash reference. Otherwise an exception will occur.

The each field of the hash of the given argument is converted to C<int> value by L<the rule of Perl scalar to SPVM int|"Perl Scalar to SPVM int"> and the each filed of the return value is converted to Perl scalar by L<the rule of SPVM int to Perl Scalar|"SPVM int to Perl scalar">

If a field is missing, an exception occurs.

B<Example:>

  # SPVM multi-numeric type and method definition
  class MyClassPoint_2i {
    has x : int;
    has y : int;
  }
  class MyClass {
    static method foo : void ($value : MyClassPoint_2i);
  }

  # Perl
  my $value = {x => 1, y => 2};
  SPVM::MyClass->foo(\$value);

=head3 Perl Reference to SPVM Multi-Numeric long Reference

If the SPVM argument type is multi-numeric long reference type, the given Perl reference is converted to SPVM multi-numeric long reference type.

The given reference must be a scalar reference of hash reference. Otherwise an exception will occur.

The each field of the hash of the given argument is converted to C<long> value by L<the rule of Perl scalar to SPVM long|"Perl Scalar to SPVM long"> and the each filed of the return value is converted to Perl scalar by L<the rule of SPVM long to Perl Scalar|"SPVM long to Perl scalar">

If a field is missing, an exception occurs.

B<Example:>

  # SPVM multi-numeric type and method definition
  class MyClassPoint_2l {
    has x : long;
    has y : long;
  }
  class MyClass {
    static method foo : void ($value : MyClassPoint_2l);
  }

  # Perl
  my $value = {x => 1, y => 2};
  SPVM::MyClass->foo(\$value);

=head3 Perl Reference to SPVM Multi-Numeric float Reference

If the SPVM argument type is multi-numeric float reference type, the given Perl reference is converted to SPVM multi-numeric float reference type.

The given reference must be a scalar reference of hash reference. Otherwise an exception will occur.

The each field of the hash of the given argument is converted to C<float> value by L<the rule of Perl scalar to SPVM float|"Perl Scalar to SPVM float"> and the each filed of the return value is converted to Perl scalar by L<the rule of SPVM float to Perl Scalar|"SPVM float to Perl scalar">

If a field is missing, an exception occurs.

B<Example:>

  # SPVM multi-numeric type and method definition
  class MyClassPoint_2f {
    has x : float;
    has y : float;
  }
  class MyClass {
    static method foo : void ($value : MyClassPoint_2f);
  }

  # Perl
  my $value = {x => 1,2, y => 2.3};
  SPVM::MyClass->foo(\$value);

=head3 Perl Reference to SPVM Multi-Numeric double Reference

If the SPVM argument type is multi-numeric double reference type, the given Perl reference is converted to SPVM multi-numeric double reference type.

The given reference must be a scalar reference of hash reference. Otherwise an exception will occur.

The each field of the hash of the given argument is converted to C<double> value by L<the rule of Perl scalar to SPVM double|"Perl Scalar to SPVM double"> and the each filed of the return value is converted to Perl scalar by L<the rule of SPVM double to Perl Scalar|"SPVM double to Perl scalar">

If a field is missing, an exception occurs.

B<Example:>

  # SPVM multi-numeric type and method definition
  class MyClassPoint_2d {
    has x : double;
    has y : double;
  }
  class MyClass {
    static method foo : void ($value : MyClassPoint_2d);
  }

  # Perl
  my $value = {x => 1.2, y => 2.3};
  SPVM::MyClass->foo(\$value);

=head1 Return Value Conversion

a SPVM return value is converted to a Perl value by the following rules.

=head2 SPVM void to Perl undef

SPVM void return value is converted to Perl C<undef>. This is only for specification and has no meaning.

=head2 SPVM byte to Perl Scalar

SPVM byte value(same type as int8_t of C language) is converted to Perl scalar by L<newSViv function of perlapi|https://perldoc.perl.org/perlapi#newSViv>.

  int8_t spvm_byte_value = VALUE;
  SV* perl_scalar = newSViv(spvm_byte_value);

=head2 SPVM short to Perl Scalar

SPVM short value(same type as int16_t of C language) is converted to Perl scalar by L<newSViv function of perlapi|https://perldoc.perl.org/perlapi#newSViv>.

  int16_t spvm_short_value = VALUE;
  SV* perl_scalar = newSViv(spvm_short_value);

=head2 SPVM int to Perl Scalar

SPVM int value(same type as int32_t of C language) is converted to Perl scalar by L<newSViv function of perlapi|https://perldoc.perl.org/perlapi#newSViv>.

  int32_t spvm_int_value = VALUE;
  SV* perl_scalar = newSViv(spvm_int_value);

=head2 SPVM long to Perl Scalar

SPVM long value(same type as int64_t of C language) is converted to Perl scalar by L<newSViv function of perlapi|https://perldoc.perl.org/perlapi#newSViv>.

  int64_t spvm_long_value = VALUE;
  SV* perl_scalar = newSViv(spvm_long_value);

=head2 SPVM float to Perl Scalar

SPVM float value(same type as float of C language) is converted to Perl scalar by L<newSVnv function of perlapi|https://perldoc.perl.org/perlapi#newSVnv>.

  float spvm_float_value = VALUE;
  SV* perl_scalar = newSVnv(spvm_float_value);

=head2 SPVM double to Perl Scalar

SPVM double value(same type as double of C language) is converted to Perl scalar by L<newSVnv function of perlapi|https://perldoc.perl.org/perlapi#newSVnv>.

  double spvm_double_value = VALUE;
  SV* perl_scalar = newSVnv(spvm_double_value);

=head2 SPVM String to Perl String

SPVM String is converted to a Perl decoded string. If SPVM C<undef> is returned, it is converted to Perl C<undef>.

=head2 SPVM Object to Perl Object

a SPVM object(not contain array) is converted to a Perl object which class name is same as SPVM class name and inherits L<SPVM::BlessedObject::Class>.

=head2 SPVM Multi-Numeric to Perl Hash Reference

SPVM multi-numeric value is converted to Perl hash reference which keys is the field names of multi-numeric type. The rules of number convertions of the field of multi-numeric value is same as above the numeric convertions(byte, short, int, long, float, double).

=head2 SPVM Array to Perl SPVM::BlessedObject::Array

a SPVM array is converted to a Perl L<SPVM::BlessedObject::Array> object. If SPVM return value is C<undef>, it is converted to Perl C<undef>.

=head2 SPVM Object to Perl Object

a SPVM object is converted to a Perl object which class name is same as SPVM class name and inherits L<SPVM::BlessedObject::Class>.

