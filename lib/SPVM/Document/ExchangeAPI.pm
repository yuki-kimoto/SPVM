=encoding utf8

=head1 NAME

SPVM::Document::ExchangeAPI - SPVM Exchange API

=head1 DESCRIPTION

SPVM Exchange API is APIs to convert Perl data structures to/from SPVM data structures, and call SPVM Method from Perl.

=head1 LOAD SPVM MODULE

If you load SVPM module from Perl, use the following syntax.

  use SPVM 'Foo';

Suppose the following C<Foo.spvm> is placed on a module search path.

  # Foo.spvm
  package Foo {
    sub sum : int ($x1: int, $x2: int) {
      return $x1 + $x2;
    }
  }

If you load C<Foo::Bar> module, do the following.

  use SPVM 'Foo::Bar';

Suppose the following C<Foo/Bar.spvm> is placed on a module search path.

  # Foo/Bar.spvm
  package Foo::Bar {
    sub sum : int ($x1: int, $x2: int) {
      return $x1 + $x2;
    }
  }

C<use SPVM MODULE_NAME> compile the SPVM module and the dependent modules.

Note that at this point a SPVM runtime has not yet been created.

A default SPVM runtime is created the first time you call a method of SPVM module or call a function or method of the Exchange API.

=head1 CALL SPVM METHOD

The method of SPVM module can be called from Perl directory.

=head2 CALL STATIC METHOD

Let's call SPVM static method from Perl.

  use SPVM 'Foo';

  my $total = Foo->sum(1, 2);

The definition of C<Foo> module is the following.

  # Foo.spvm
  package Foo {
    sub sum : int ($x1: int, $x2: int) {
      return $x1 + $x2;
    }
  }

If the number of arguments does not match the number of arguments of the SPVM method, an exception occurs.

The Perl values of the arguments are converted to the SPVM values by the rule of argument convertion.

If the type is non-conforming, an exception occurs.

The SPVM return value is converted to a Perl return value by the rule of return value convertion.

The SPVM exception is converted to a Perl exception.

=head2 CALL INSTANCE METHOD

Let's call SPVM instance method from Perl.

  use SPVM 'Foo';

  my $foo = Foo->new;

  my $total = $foo->sum(1, 2);

The definition of C<Foo> module is the following.

  # Foo.spvm
  package Foo {
    sub new : Foo () {
      return new Foo;
    }

    sub sum : int ($self: self, $x1: int, $x2: int) (
      return $x1 + $x2;
    }
  }

=head2 ARGUMENT CONVERSION

Perl arguments are converted to SPVM arguments in the following rules.

=head3 Perl scalar to SPVM byte

If the SPVM argument type is C<byte>, Perl scalar is converted to SPVM C<byte> value using L<SvIV of perlapi|https://perldoc.perl.org/perlapi#SvIV>

  (int8_t)SvIV(perl_scalar)

=head3 Perl scalar to SPVM short

If the SPVM argument type is C<short>, Perl scalar is converted to SPVM C<short> value using L<SvIV of perlapi|https://perldoc.perl.org/perlapi#SvIV>
  
  (int16_t)SvIV(perl_scalar)

=head3 Perl scalar to SPVM int

If the SPVM argument type is C<int>, Perl scalar is converted to SPVM C<int> value using L<SvIV of perlapi|https://perldoc.perl.org/perlapi#SvIV>

  (int32_t)SvIV(perl_scalar)

=head3 Perl scalar to SPVM long

If the SPVM argument type is C<long>, Perl scalar is converted to SPVM C<long> value using L<SvIV of perlapi|https://perldoc.perl.org/perlapi#SvIV>

  (int64_t)SvIV(perl_scalar)

=head3 Perl scalar to SPVM float

If the SPVM argument type is C<float>, Perl scalar is converted to SPVM C<float> value using L<SvNV of perlapi|https://perldoc.perl.org/perlapi#SvIV>

  (float)SvNV(perl_scalar)

=head3 Perl scalar to SPVM double

If the SPVM argument type is C<double>, Perl scalar is converted to SPVM C<double> value using L<SvNV of perlapi|https://perldoc.perl.org/perlapi#SvIV>

  (double)SvNV(perl_scalar)

=head3 Perl value to SPVM string

=head4 Perl scalar to SPVM string

If the SPVM argument type is C<string>, the Perl scalar is converted to SPVM C<string> value.

The scalar value must be non-ref scalar, otherwise a exception occurs.

The scalar value is assumed to a Perl decoded string, and is converted to a SPVM C<string>.

=head4 string object to SPVM string

A string object which package name is L<SPVM::BlessedObject::String> is converted to a SPVM C<string>.

=head4 other to SPVM string

If the Perl value is not the avobe things, a exception occurs.

=head3 Perl array reference to SPVM array

A Perl array reference is converted to a SPVM array by the following rules.

=head4 Perl array reference to SPVM byte array

If the SPVM argument type is C<byte[]>, the Perl array reference is converted to SPVM array which type is C<byte[]>. Each element is converted to C<byte> value by L<the rule of Perl scalar to SPVM byte|"Perl scalar to SPVM byte">. If the Perl C<undef> is coverted to SPVM C<undef>.



=head3 Perl Hash reference to SPVM Multi Numeric Type

If the argument type in the SPVM Method definition was a Multi Numeric Type, the argument value must be a hash reference and the key must contain all Multi Numeric field names. Otherwise, an Exception will be raised. The value of the hash reference is <a href="#exchange-api-rule-perl-scalar-to-spvm-numeric">The rule that converts the scalar value of Perl to the Numeric Type of SPVM</a> Is converted to a value.

  # SPVM Method definition
  package Foo {
    sub call_complex_float : void ($z: SPVM::Complex_2f);
    sub call_complex_double : void ($z: SPVM::Complex_2d);
  }

  # Call from Perl
  Foo->call_complex_float({re => 2.3, im => 5.6});
  Foo->call_complex_double({re => 2.3, im => 5.6});
  
=head3 Perl Refernce to SPVM Numeric Reference Type

If the argument type in the SPVM Method definition was a Numeric Reference Type, the argument value must be a scalar reference. Otherwise, an Exception will be raised.

  # SPVM Method definition
  package Foo {
    sub call_byte_ref : void ($num: byte&);
    sub call_short_ref : void ($num: short&);
    sub call_int_ref : void ($num: int&);
    sub call_long_ref : void ($num: long&);
    sub call_float_ref : void ($num: float&);
    sub call_double_ref : void ($num: double&);
  }

  # Call from Perl
  my $num_byte = 23;
  Foo->call_byte_ref(\$num_byte);

  my $num_short = 23;
  Foo->call_short_ref(\$num_short);

  my $num_int = 23;
  Foo->call_int_ref(\$num_int);

  my $num_long = 23;
  Foo->call_long_ref(\$num_long);

  my $num_float = 23;
  Foo->call_float_ref(\$num_float);

  my $num_double = 23;
  Foo->call_double_ref(\$num_double);

If the argument type in the SPVM Method definition was a Multi Numeric Reference Type, the argument value is a hash reference reference and the key contains all Multi Numeric field names. is needed. Otherwise, an Exception will be raised.

If the argument type of the SPVM Method definition is an object type and the value passed to the argument is an Undefined Value, it is converted to the SPVM Undefined Value.

If the argument type of the SPVM Method definition is a byte[] value and the value passed to the argument is Array Reference, convert it to a Perl L<SPVM::BlessedObject::Array> object that represents byte[]. Will be done. The element value is converted by the <a href="#exchange-api-rule-perl-scalar-to-spvm-numeric">Rule to Convert Perl scalar data ​​to SPVM Numeric Value</a>.

If the argument type of the SPVM Method definition is a short[] value and the value passed to the argument is Array Reference, convert it to a Perl L<SPVM::BlessedObject::Array> object that represents a short[]. Will be done. The element value is converted by the <a href="#exchange-api-rule-perl-scalar-to-spvm-numeric">Rule to Convert Perl scalar data ​​to SPVM Numeric Value</a>.

If the argument type of the SPVM Method definition is int[] value and the value passed to the argument is Array Reference, convert it to a Perl L<SPVM::BlessedObject::Array> object that represents int[] Will be done. The element value is converted by the <a href="#exchange-api-rule-perl-scalar-to-spvm-numeric">Rule to Convert Perl scalar data ​​to SPVM Numeric Value</a>.

If the argument type of the SPVM Method definition is a long[] type and the value passed to the argument is Array Reference, convert it to a Perl L<SPVM::BlessedObject::Array> object representing long[]. Will be done. The element value is converted by the <a href="#exchange-api-rule-perl-scalar-to-spvm-numeric">Rule to Convert Perl scalar data ​​to SPVM Numeric Value</a>.

If the argument type of the SPVM Method definition is float[] value and the value passed to the argument is Array Reference, convert it to a Perl L<SPVM::BlessedObject::Array> object that represents float[]. Will be done. The element value is converted by the <a href="#exchange-api-rule-perl-scalar-to-spvm-numeric">Rule to Convert Perl scalar data ​​to SPVM Numeric Value</a>.

If the argument type of the SPVM Method definition is double[] type and the value passed to the argument is Array Reference, convert it to a Perl L<SPVM::BlessedObject::Array> object that represents double[]. Will be done. The element value is converted by the <a href="#exchange-api-rule-perl-scalar-to-spvm-numeric">Rule to Convert Perl scalar data ​​to SPVM Numeric Value</a>.

If the argument type of the SPVM Method definition is an object[] type and the value passed to the argument is Array Reference, convert it to a Perl L<SPVM::BlessedObject::Array> object that represents object[]. Will be done. If the element value is an Undefined Value, it is converted to SPVM undefined, and if it is a non-reference scalar value, it is encoded to UTF-8 and converted to SPVM byte[] value. If it is SPVM::Data object, it will not be converted. Otherwise, an Exception will be raised.

  
=head2 RETURN VALUE CONVERSION

a SPVM return value is converted to a Perl value by the following rules.

=head3 SPVM void to Perl undef

SPVM void return value is converted to Perl C<undef>. This is only for specification and has no meaning.

=head3 SPVM byte value to Perl scalar

SPVM byte value(same type as int8_t of C language) is converted to Perl scalar by L<newSViv function of perlapi|https://perldoc.perl.org/perlapi#newSViv>.

  int8_t spvm_byte_value = VALUE;
  SV* perl_scalar = newSViv(spvm_byte_value);

=head3 SPVM short value to Perl scalar

SPVM short value(same type as int16_t of C language) is converted to Perl scalar by L<newSViv function of perlapi|https://perldoc.perl.org/perlapi#newSViv>.

  int16_t spvm_short_value = VALUE;
  SV* perl_scalar = newSViv(spvm_short_value);

=head3 SPVM int value to Perl scalar

SPVM int value(same type as int32_t of C language) is converted to Perl scalar by L<newSViv function of perlapi|https://perldoc.perl.org/perlapi#newSViv>.

  int32_t spvm_int_value = VALUE;
  SV* perl_scalar = newSViv(spvm_int_value);

=head3 SPVM long value to Perl scalar

SPVM long value(same type as int64_t of C language) is converted to Perl scalar by L<newSViv function of perlapi|https://perldoc.perl.org/perlapi#newSViv>.

  int64_t spvm_long_value = VALUE;
  SV* perl_scalar = newSViv(spvm_long_value);

=head3 SPVM float value to Perl scalar

SPVM float value(same type as float of C language) is converted to Perl scalar by L<newSVnv function of perlapi|https://perldoc.perl.org/perlapi#newSVnv>.

  float spvm_float_value = VALUE;
  SV* perl_scalar = newSVnv(spvm_float_value);

=head3 SPVM double value to Perl scalar

SPVM double value(same type as double of C language) is converted to Perl scalar by L<newSVnv function of perlapi|https://perldoc.perl.org/perlapi#newSVnv>.

  double spvm_double_value = VALUE;
  SV* perl_scalar = newSVnv(spvm_double_value);

=head3 SPVM string to Perl string

SPVM string is converted to a Perl decoded string. If SPVM C<undef> is returned, it is converted to Perl C<undef>.

=head3 SPVM object to Perl object

a SPVM object(not contain array) is converted to a Perl object which class name is same as SPVM class name and inherits L<SPVM::BlessedObject::Package>.

=head3 SPVM multi numeric value to Perl hash reference

SPVM multi numeric value is converted to Perl hash reference which keys is the field names of multi numeric type. The rules of number convertions of the field of multi numeric value is same as above the numeric convertions(byte, short, int, long, float, double).

=head3 SPVM array to Perl array object

a SPVM array is converted to a Perl L<SPVM::BlessedObject::Array> object. If SPVM return value is C<undef>, it is converted to Perl C<undef>.

=head3 SPVM object to Perl object

a SPVM object is converted to a Perl object which package name is same as SPVM package name and inherits L<SPVM::BlessedObject::Package>.

=head1 FUNCTIONS AND METHODS

Funtions and methods which create SPVM datas and convert SVPM datas to/from Perl data.

=head2 SPVM::Byte->new

  my $spvm_byte = SPVM::Byte->new(98);

Convert a Perl scalar data to a L<SPVM::Byte> object. Return value is B<SPVM::Byte> object which inherits L<SPVM::BlessedObject::Package>.

=head2 SPVM::Short->new

  my $spvm_short = SPVM::Short->new(9800);

Convert a Perl scalar data to a L<SPVM::Short> object. Return value is B<SPVM::Short> object which inherits L<SPVM::BlessedObject::Package>.

=head2 SPVM::Int->new

  my $spvm_int = SPVM::Int->new(100000);

Convert a Perl scalar data to a L<SPVM::Int> object. Return value is B<SPVM::Int> object which inherits L<SPVM::BlessedObject::Package>.

=head2 SPVM::Long->new

  my $spvm_long = SPVM::Long->new(98);

Convert a Perl scalar data to a L<SPVM::Long> object. Return value is B<SPVM::Long> object which inherits L<SPVM::BlessedObject::Package>.

=head2 SPVM::Float->new

  my $spvm_float = SPVM::Float->new(2.5);Rule to Convert 

Convert a Perl scalar data to a L<SPVM::Float> object. Return value is B<SPVM::Float> object which inherits L<SPVM::BlessedObject::Package>.

=head2 SPVM::Double->new

  my $spvm_double = SPVM::Double->new(2.5);

Convert a Perl scalar data to a L<SPVM::Double> object. Return value is B<SPVM::Double> object which inherits L<SPVM::BlessedObject::Package>.

=head2 SPVM::new_byte_array

  my $spvm_nums = SPVM::new_byte_array([1, 2, 3]);

Convert a Perl array reference to a SPVM C<byte[]> array. Return value is L<SPVM::BlessedObject::Array> object which wraps the SPVM array.

If the first argument is a C<undef> value, the return value is a C<undef> value.

=head2 SPVM::new_byte_array_len

  my $spvm_nums = SPVM::new_byte_array_len([1, 2, 3]);

Create a new SPVM C<byte[]> array with length. The values of elements is zeros. Return value is L<SPVM::BlessedObject::Array> object which wraps the SPVM array.

The lenght must be more than or equals to zero, otherwise a exception occurs.

=head2 SPVM::new_byte_array_from_bin

  my $perl_binary = pack('c3', 97, 98, 99);
  my $spvm_byte_array = SPVM::new_byte_array_from_bin($perl_binary);

Convert a Perl Binary Data to SPVM byte[] object. Return value is L<SPVM::BlessedObject::Array> object which wraps the SPVM array.

Thg Perl binary data is interpreted as 8-bit signed integers. The created array length is automatically calcurated from the Perl binary data.

If the first argument is C<undef>, C<undef> is returned.

You can use simple ascii codes as Perl binary data.

  my $perl_binary ="abc";
  my $spvm_byte_array = SPVM::new_byte_array_from_bin($perl_binary);

or UTF-8 bytes.
  
  use utf8;
  my $perl_binary = encode('UTF-8', "あいう");
  my $spvm_string = SPVM::new_string_from_bin($perl_binary);

=head2 SPVM::new_byte_array_from_string

  use utf8;
  my $spvm_byte_array = SPVM::new_byte_array_from_string("あいう");

Convert a Perl string to SPVM byte[] value. Return value is L<SPVM::BlessedObject::Array> object which wraps the SPVM array.

=head2 SPVM::new_short_array

  my $spvm_nums = SPVM::new_short_array([1, 2, 3]);

Convert a Perl array reference to a SPVM C<short[]> array. Return value is L<SPVM::BlessedObject::Array> object which wraps the SPVM array.

If the first argument is a C<undef> value, the return value is a C<undef> value.

=head2 SPVM::new_short_array_len

  my $spvm_nums = SPVM::new_short_array_len($length);

Create a new  a SPVM C<short[]> array with length. The values of elements is zeros. Return value is L<SPVM::BlessedObject::Array> object which wraps the SPVM array.

The lenght must be more than or equals to zero, otherwise a exception occurs.

=head2 SPVM::new_short_array_from_bin

  my $perl_binary = pack('c3', 97, 98, 99);
  my $spvm_short_array = SPVM::new_short_array_from_bin($perl_binary);

Convert a Perl Binary Data to SPVM short[] object. Return value is L<SPVM::BlessedObject::Array> object which wraps the SPVM array.

Thg Perl binary data is interpreted as 16-bit signed integers. The created array length is automatically calcurated from the Perl binary data.

If the first argument is C<undef>, C<undef> is returned.

=head2 SPVM::new_int_array

  my $spvm_nums = SPVM::new_int_array([1, 2, 3]);

Convert a Perl array reference to a SPVM C<int[]> array. Return value is L<SPVM::BlessedObject::Array> object which wraps the SPVM array.

If the first argument is a C<undef> value, the return value is a C<undef> value.

=head2 SPVM::new_int_array_len

  my $spvm_nums = SPVM::new_int_array_len($length);

Create a new  a SPVM C<int[]> array with length. The values of elements is zeros. Return value is L<SPVM::BlessedObject::Array> object which wraps the SPVM array.

The lenght must be more than or equals to zero, otherwise a exception occurs.

=head2 SPVM::new_int_array_from_bin

  my $perl_binary = pack('l3', 97, 98, 99);
  my $spvm_int_array = SPVM::new_int_array_from_bin($perl_binary);

Convert a Perl Binary Data to SPVM int[] object. Return value is L<SPVM::BlessedObject::Array> object which wraps the SPVM array.

Thg Perl binary data is interpreted as 8-bit signed integers. The created array length is automatically calcurated from the Perl binary data.

If the first argument is C<undef>, C<undef> is returned.

=head2 SPVM::new_long_array

  my $spvm_nums = SPVM::new_long_array([1, 2, 3]);

Convert a Perl array reference to a SPVM C<long[]> array. Return value is L<SPVM::BlessedObject::Array> object which wraps the SPVM array.

If the first argument is a C<undef> value, the return value is a C<undef> value.

=head2 SPVM::new_long_array_len

  my $spvm_nums = SPVM::new_long_array_len($length);

Create a new  a SPVM C<long[]> array with length. The values of elements is zeros. Return value is L<SPVM::BlessedObject::Array> object which wraps the SPVM array.

The lenght must be more than or equals to zero, otherwise a exception occurs.

=head2 SPVM::new_long_array_from_bin

  my $perl_binary = pack('q3', 97, 98, 99);
  my $spvm_long_array = SPVM::new_long_array_from_bin($perl_binary);

Convert a Perl Binary Data to SPVM long[] object. Return value is L<SPVM::BlessedObject::Array> object which wraps the SPVM array.

Thg Perl binary data is longerpreted as 8-bit signed longegers. The created array length is automatically calcurated from the Perl binary data.

If the first argument is C<undef>, C<undef> is returned.

=head2 SPVM::new_float_array

  my $spvm_nums = SPVM::new_float_array([1.2, 2.5, 3.3]);

Convert a Perl array reference to a SPVM C<float[]> array. Return value is L<SPVM::BlessedObject::Array> object which wraps the SPVM array.

If the first argument is a C<undef> value, the return value is a C<undef> value.

=head2 SPVM::new_float_array_len

  my $spvm_nums = SPVM::new_float_array_len($length);

Create a new  a SPVM C<float[]> array with length. The values of elements is zeros. Return value is L<SPVM::BlessedObject::Array> object which wraps the SPVM array.

The lenght must be more than or equals to zero, otherwise a exception occurs.

=head2 SPVM::new_float_array_from_bin

  my $perl_binary = pack('f3', 0.5, 1.5, 2.5);
  my $spvm_float_array = SPVM::new_float_array_from_bin($perl_binary);

Convert a Perl Binary Data to SPVM float[] object. Return value is L<SPVM::BlessedObject::Array> object which wraps the SPVM array.

Thg Perl binary data is floaterpreted as 8-bit signed floategers. The created array length is automatically calcurated from the Perl binary data.

If the first argument is C<undef>, C<undef> is returned.

=head2 SPVM::new_double_array

  my $spvm_nums = SPVM::new_double_array([1.2, 2.5, 3.3]);

Convert a Perl array reference to a SPVM C<double[]> array. Return value is L<SPVM::BlessedObject::Array> object which wraps the SPVM array.

If the first argument is a C<undef> value, the return value is a C<undef> value.

=head2 SPVM::new_double_array_len

  my $spvm_nums = SPVM::new_double_array_len($length);

Create a new  a SPVM C<double[]> array with length. The values of elements is zeros. Return value is L<SPVM::BlessedObject::Array> object which wraps the SPVM array.

The lenght must be more than or equals to zero, otherwise a exception occurs.

=head2 SPVM::new_double_array_from_bin

  my $perl_binary = pack('f3', 0.5, 1.5, 2.5);
  my $spvm_double_array = SPVM::new_double_array_from_bin($perl_binary);

Convert a Perl Binary Data to SPVM double[] object. Return value is L<SPVM::BlessedObject::Array> object which wraps the SPVM array.

Thg Perl binary data is doubleerpreted as 8-bit signed doubleegers. The created array length is automatically calcurated from the Perl binary data.

If the first argument is C<undef>, C<undef> is returned.

=head2 SPVM::new_string

  use utf8;
  my $spvm_string = SPVM::new_string("あいう");

Convert a Perl string to a SPVM string.

If the argument is C<undef>, C<undef> is returned.

=head2 SPVM::new_string_from_bin

  my $perl_binary = pack('c3', 97, 98, 99);
  my $spvm_string = SPVM::new_string_from_bin($perl_binary);

Convert a Perl Binary Data to SPVM string object. Return value is L<SPVM::BlessedObject::String> object which wraps the SPVM string.

Thg Perl binary data is interpreted as 8-bit signed integers. The string length is automatically calcurated from the Perl binary data.

If the first argument is C<undef>, C<undef> is returned.

You can use simple ascii codes as Perl binary data.

  my $binary ="abc";
  my $spvm_string = SPVM::new_string_from_bin($perl_binary);

or UTF-8 bytes.

  use utf8;
  my $perl_binary = encode('UTF-8', "あいう");
  my $spvm_string = SPVM::new_string_from_bin($perl_binary);

=head2 SPVM::new_object_array

  my $byte_array = SPVM::new_object_array(
    "SPVM::Byte[]",
    [SPVM::Byte->new(1), SPVM::Byte>new(2), SPVM::Byte->new(3)]
  );

Convert a Perl array reference to a SPVM object array. Return value is L<SPVM::BlessedObject::Array> object which wraps the SPVM array.

The first argument is a SPVM array type name. If the type is non-existent, an exception occurs.

The second argument is a Perl array reference. Each element must be valid value or C<undef>, otherwise an exception occurs.

Return value is L<SPVM::BlessedObject::Array> object which wraps the SPVM array.

You can also create multidimensional array.

  my $object1 = SPVM::new_int_array([1, 2, 3]);
  my $object2 = SPVM::new_int_array([4, 5, 6]);
  my $oarray = SPVM::new_object_array("int[][]",[$object1, $object2]);

=head2 SPVM::new_mulnum_array

Convert a Perl array references to SPVM multi numeric array.

  my $perl_values = [
    {x => 0, y => 1, z => 2},
    {x => 3, y => 4, z => 5},
    {x => 6, y => 7, z => 8},
  ];
  my $spvm_mulnum_array = SPVM::new_mulnum_array("TestCase::Point_3i[]", $perl_values);

The first argument is a SPVM array type name. If the type is non-existent, an exception occurs.

The second argument is a Perl array of hash references. Each hash reference must be contain all fields of the multi numeric value, otherwise an exception occurs.

Return value is L<SPVM::BlessedObject::Array> object which wraps the SPVM array.

B<Examples:>

  # new_mulnum_array - byte
  {
    my $values = [
      {x => 0, y => 1, z => 2},
      {x => 3, y => 4, z => 5},
      {x => 6, y => 7, z => 8},
    ];
    my $spvm_mulnum_array = SPVM::new_mulnum_array("TestCase::Point_3b[]", $values);
  }

  # new_mulnum_array - short
  {
    my $values = [
      {x => 0, y => 1, z => 2},
      {x => 3, y => 4, z => 5},
      {x => 6, y => 7, z => 8},
    ];
    my $spvm_mulnum_array = SPVM::new_mulnum_array("TestCase::Point_3s[]",$values);
  }

  # new_mulnum_array - int
  {
    my $values = [
      {x => 0, y => 1, z => 2},
      {x => 3, y => 4, z => 5},
      {x => 6, y => 7, z => 8},
    ];
    my $spvm_mulnum_array = SPVM::new_mulnum_array("TestCase::Point_3i[],$values);
  }

  # new_mulnum_array - long
  {
    my $values = [
      {x => 0, y => 1, z => 2},
      {x => 3, y => 4, z => 5},
      {x => 6, y => 7, z => 8},
    ];
    my $spvm_mulnum_array = SPVM::new_mulnum_array("TestCase::Point_3l[]", $values);
  }

  # new_mulnum_array - float
  {
    my $values = [
      {x => 0, y => 1, z => 2},
      {x => 3, y => 4, z => 5},
      {x => 6, y => 7, z => 8},
    ];
    my $spvm_mulnum_array = SPVM::new_mulnum_array("TestCase::Point_3f[]",$values);
  }

  # new_mulnum_array - double
  {
    my $values = [
      {x => 0, y => 1, z => 2},
      {x => 3, y => 4, z => 5},
      {x => 6, y => 7, z => 8},
    ];
    my $spvm_mulnum_array = SPVM::new_mulnum_array("TestCase::Point_3d[],"$values);
    ok(TestCase::ExchangeAPI-spvm_new_mulnum_array_double($spvm_mulnum_array));
    my $out_values = $spvm_mulnum_array->to_elems;
    is_deeply($out_values, $values);
  }

=head2 SPVM::new_mulnum_array_from_bin

  my $binary = pack('l9', ($INT_MIN, 1, 2), (3, 4, 5), (6, 7, 8));
  my $spvm_mulnum_array = SPVM::new_mulnum_array_from_bin("TestCase::Point_3i[]", $binary);

Convert Perl a binary data to SPVM Multi Numeric Array. Return value is L<SPVM::BlessedObject::Array> object which wraps the SPVM array.

The first argument is a multi numeric array type of SPVM.

The second argument is the Perl packed binary data. The length of the created array is calcurated automatically.

B<Examples:>
  
  # new_mulnum_array_from_bin - byte
  {
    my $binary = pack('c9', (0, 1, 2), (3, 4, 5), (6, 7, 8));
    my $spvm_mulnum_array = SPVM::new_mulnum_array_from_bin("TestCase::Point_3b[]", $binary);
  }

  # new_mulnum_array_from_bin - short
  {
    my $binary = pack('s9', (0, 1, 2), (3, 4, 5), (6, 7, 8);;
    my $spvm_mulnum_array = SPVM::new_mulnum_array_from_bin("TestCase::Point_3s[]", $binary);
  }

  # new_mulnum_array_from_bin - int
  {
    my $binary = pack('l9', (0, 1, 2), (3, 4, 5), (6, 7, 8));
    my $spvm_mulnum_array = SPVM::new_mulnum_array_from_bin("TestCase::Point_3i[]", $binary);
  }

  # new_mulnum_array_from_bin - long
  {
    my $binary = pack('q9', (0, 1, 2), (3, 4, 5), (6, 7, 8));
    my $spvm_mulnum_array = SPVM::new_mulnum_array_from_bin("TestCase::Point_3l[]", $binary);
  }

  # new_mulnum_array_from_bin - float
  {
    my $binary = pack('f9', (0, 1, 2), (3, 4, 5), (6, 7, 8));
    my $spvm_mulnum_array = SPVM::new_mulnum_array_from_bin("TestCase::Point_3f[]", $binary);
  }

  # new_mulnum_array_from_bin - double
  {
    my $binary = pack('d9', (0, 1, 2), (3, 4, 5), (6, 7, 8));
    my $spvm_mulnum_array = SPVM::new_mulnum_array_from_bin("TestCase::Point_3d[]", $binary);
  }

=head2 $spvm_array->length

  my $length = $spvm_array->length;

Get the length of SPVM array. $spvm_array means a  L<SPVM::BlessedObject::Array> object.

=head2 $spvm_array->to_elems

  my $perl_array_ref = $spvm_array->to_elems;

Convert a SPVM array to Perl a array reference.

If the SPVM array is numeric array type, the element of the Perl array is numeric value.

If the SPVM array is object array type, the element of the Perl array is a object which inherits L<SPVM::BlessedObject> or C<undef>.

If the SPVM array is multi numeric array type, the element of the Perl array is a hash reference.

=head2 $spvm_array->to_bin

  my $perl_binary = $spvm_array->to_bin;

Convert a SPVM Array to Perl binary data.

If the SPVM array is a numeric array type or a multi numeric type, the binary representation of SPVM is copied directly into a scalar variable.

If the Array of SPVM is of any other type, an exception occurs.

=head2 $spvm_data->to_string

Convert a SPVM string or a SPVM byte[] array to a Perl string(a decoded string).

If the type is other one, an exception occurs.

=head2 $spvm_array->to_strings

<pre>
my $perl_array_ref = $spvm_string_array->to_strings;
</pre>

Convert a SPVM string array to a Perl array reference which the element is a string(decoded string) or C<undef>. Return value is L<SPVM::BlessedObject::Array> object which wraps the SPVM array.

If the SPVM data type is not a string array, an exception occurs.

=head2 SPVM::get_exception

<pre>
my $exception = SPVM::get_exception();
</pre>

Gets the SPVM exception of the default SPVM runtime as a decoded string.

=head2 SPVM::set_exception

Set a SPVM exception of the default SPVM runtime. The argument must be a decoded string or C<undef>. There is one exception per runtime. Perl starts a default SPVM runtime when a first SVPM method is called.

<pre>
SPVM::set_exception("Aiu");
SPVM::set_exception(undef);
</pre>

=head2 SPVM::get_memory_blocks_count

  my $count = SPVM::get_memory_blocks_count();

Get the count of created memory blocks. SPVM runtime create a memory block on the heap when a object is created or new week reference is created.

You can check the memory leaks by this method.

  # First Memory Blocks Count
  my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

  # Processing
  # ...

  # Last Memory Blocks Count
  my $end_memory_blocks_count = SPVM::get_memory_blocks_count();

  unless ($end_memory_blocks_count == $start_memory_blocks_count) {
    die"Memroy leak";
  }
