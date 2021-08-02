=encoding utf8

=head1 NAME

SPVM::Document::ExchangeAPI - SPVM Exchange API

=head1 DESCRIPTION

SPVM Exchange API is APIs to convert Perl data structures to/from SPVM data structures, and call SPVM Method from Perl.

=head1 SPVM EXCHANGE API

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

Convert a Perl array reference to to a SPVM C<byte[]> array. Return value is L<SPVM::BlessedObject::Array> object which wraps the SPVM array.

If the first argument is a C<undef> value, the return value is a C<undef> value.

=head2 SPVM::new_short_array

  my $spvm_nums = SPVM::new_short_array([1, 2, 3]);

Convert a Perl array reference to to a SPVM C<short[]> array. Return value is L<SPVM::BlessedObject::Array> object which wraps the SPVM array.

If the first argument is a C<undef> value, the return value is a C<undef> value.

=head2 SPVM::new_int_array

  my $spvm_nums = SPVM::new_int_array([1, 2, 3]);

Convert a Perl array reference to to a SPVM C<int[]> array. Return value is L<SPVM::BlessedObject::Array> object which wraps the SPVM array.

If the first argument is a C<undef> value, the return value is a C<undef> value.

=head2 SPVM::new_long_array

  my $spvm_nums = SPVM::new_long_array([1, 2, 3]);

Convert a Perl array reference to to a SPVM C<long[]> array. Return value is L<SPVM::BlessedObject::Array> object which wraps the SPVM array.

If the first argument is a C<undef> value, the return value is a C<undef> value.

=head2 SPVM::new_float_array

  my $spvm_nums = SPVM::new_float_array([1.2, 2.5, 3.3]);

Convert a Perl array reference to to a SPVM C<float[]> array. Return value is L<SPVM::BlessedObject::Array> object which wraps the SPVM array.

If the first argument is a C<undef> value, the return value is a C<undef> value.

=head2 SPVM::new_double_array

  my $spvm_nums = SPVM::new_double_array([1.2, 2.5, 3.3]);

Convert a Perl array reference to to a SPVM C<double[]> array. Return value is L<SPVM::BlessedObject::Array> object which wraps the SPVM array.

If the first argument is a C<undef> value, the return value is a C<undef> value.

=head2 SPVM::new_object_array

  my $byte_array = SPVM::new_object_array(
    "SPVM::Byte[]",
    [SPVM::Byte->new(1), SPVM::Byte>new(2), SPVM::Byte->new(3)]
  );

Convert a Perl array reference to to a SPVM object array. Return value is L<SPVM::BlessedObject::Array> object which wraps the SPVM array.

=begin html

<h4 id="exchange-api-perl-array-ref-to-spvm-object-array">Convert Perl Array Reference to SPVM Array Object - SPVM::new_object_array</h4>
  <p>
    To convert Perl Array References to SPVM Object Array, use the SPVM::new_object_array function.
  </p>
<pre>
my $byte_array = SPVM::new_object_array(
  "SPVM::Byte[]",
  [SPVM::Byte->new(1), SPVM::Byte>new(2), SPVM::Byte->new(3)]
);
</pre>
  <p>
    The first argument specifies the type name. It must be an array type that is an element of the base type that exists. Otherwise, an Exception is raised.
  </p>
  <p>
    The second argument is Perl Array Reference. The element must be an object that inherits "SPVM::Data" representing the object type of the SPVM, or an Undefined Value. Otherwise, an Exception is raised.
  </p>
  <p>
    The return value is an "SPVM::Data::Array" object that represents the array type of the SPVM.
  </p>
  <p>
    You can also generate multidimensional arrays.
  </p>
<pre>
my $object1 = SPVM::new_int_array([1, 2, 3]);
my $object2 = SPVM::new_int_array([4, 5, 6]);
my $oarray = SPVM::new_object_array("int[][]",[$object1, $object2]);
</pre>

<h4 id="exchange-api-perl-array-ref-to-spvm-value-array">Convert Perl Array Reference to SPVM Multi Numeric Array - SPVM::new_mulnum_array</h4>
  <p>
    To convert Perl Array References to SPVM Multi Numeric Array, use the SPVM::new_mulnum_array function.
  </p>
<pre>
my $perl_datas = [
  {x => 0, y => 1, z => 2},
  {x => 3, y => 4, z => 5},
  {x => 6, y => 7, z => 8},
];
my $spvm_mulnum_array = SPVM::new_mulnum_array("TestCase::Point_3i[],$values);
</pre>
  <p>
    The first argument specifies the array type of the value of the SPVM.
  </p>
  <p>
    The second argument is Array Reference with a hash reference on the element. The key of the hash reference must contain the values of all fields of multiNumeric Type. Otherwise, an Exception is raised.
  </p>
  <p>
    The return value is an "SPVM::Data::Array" object that represents the array type of the Value of SPVM.
  </p>
  <p>
    The values in the hash reference is converted by the <a href="#exchange-api-rule-perl-scalar-to-spvm-numeric">Rule to Convert Perl scalar data by</a> Rule that convert scalar values to SPVM Numeric Value.
  </p>
  <p>
    There are some samples.
  </p>
<pre>
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

</pre>

<h4 id="exchange-api-perl-binary-to-spvm-byte-array">Convert Perl Binary Data to SPVM byte[] value - SPVM::new_byte_array_from_bin</h4>
  <p>
    To convert Perl Binary Data to the byte[] value of SPVM, use the SPVM::new_byte_array_from_bin function.
  </p>
<pre>
my $perl_binary = pack('c3', 97, 98, 99);
my $spvm_byte_array = SPVM::new_byte_array_from_bin($perl_binary);
</pre>
  <p>
    The first argument takes Perl Binary Data.
  </p>
  <p>
    Binary columns are interpreted as 8-bit signed integers arranged in byte order in the execution environment. The length is the length when interpreted as an 8-bit signed integer.
  </p>
  <p>
    The return value is the SPVM::Data::Array object that represents the "byte[] value" of SPVM.
  </p>
  <p>
    If the first argument is an Undefined Value, an Undefined Value is returned.
  </p>
  <p>
    The sample above also has the same meaning as: Binary columns can be a sequence of 8-bit signed integers, using a pack or a string that is not perl decode.
  </p>
<pre>
my $binary ="abc";
my $spvm_byte_array = SPVM::new_byte_array_from_bin($perl_binary);
</pre>

<h4 id="exchange-api-perl-binary-to-spvm-string">Convert Perl Binary Data to SPVM string - SPVM::new_string_from_bin</h4>

<p>
    To convert Perl Binary Data to SPVM string types, use the SPVM::new_string_from_bin function.
  </p>
<pre>
my $perl_binary = pack('c3', 97, 98, 99);
my $spvm_byte_array = SPVM::new_string_from_bin($perl_binary);
</pre>
  <p>
    The first argument takes Perl Binary Data.
  </p>
  <p>
    Binary columns are interpreted as 8-bit signed integers arranged in byte order in the execution environment. The length is the length when interpreted as an 8-bit signed integer.
  </p>
  <p>
    The return value is the SPVM::Data::Array object that represents the "byte[] value" of SPVM. The string type of SPVM is treated as a byte[] value at run time.
  </p>
  <p>
    If the first argument is an Undefined Value, an Undefined Value is returned.
  </p>
  <p>
    The sample above also has the same meaning as: Binary columns can be a sequence of 8-bit signed integers, using a pack or a string that is not perl decode.
  </p>
<pre>
my $binary ="abc";
my $spvm_byte_array = SPVM::new_byte_array_from_bin($perl_binary);
</pre>

<p>
    This function is actually an alias for <a href="#exchange-api-perl-binary-to-spvm-byte-array">SPVM::new_byte_array_from_bin</a>.
  </p>
  
<h4 id="exchange-api-perl-binary-to-spvm-short-array">Convert Perl Binary Data to SPVM short[] value - SPVM::new_short_array_from_bin</h4>
  <p>
    To convert Perl Binary Data to the short[] value of SPVM, use the SPVM::new_short_array_from_bin function.
  </p>
<pre>
my $perl_binary = pack('s3', 97, 98, 99);
my $spvm_short_array = SPVM::new_short_array_from_bin($perl_binary);
</pre>
  <p>
    The first argument takes Perl Binary Data.
  </p>
  <p>
    Binary columns are interpreted as a 16-bit signed integer sequence arranged in byte order in the execution environment. The length is the length when interpreted as a 16-bit signed integer.
  </p>
  <p>
    The return value is the SPVM::Data::Array object that represents the "short[]" type of SPVM.
  </p>
  <p>
    If the first argument is an Undefined Value, an Undefined Value is returned.
  </p>

<h4 id="exchange-api-perl-binary-to-spvm-int-array">Convert Perl Binary Data to SPVM int[] value - SPVM::new_int_array_from_bin</h4>
  <p>
    To convert Perl Binary Data to the SPVM int[] value, use the SPVM::new_int_array_from_bin function.
  </p>
<pre>
my $perl_binary = pack('l3', 97, 98, 99);
my $spvm_int_array = SPVM::new_int_array_from_bin($perl_binary);
</pre>
  <p>
    The first argument takes Perl Binary Data.
  </p>
  <p>
    Binary columns are interpreted as a 32-bit signed integer sequence arranged in byte order in the execution environment. The length is the length when interpreted as a 32-bit signed integer.
  </p>
  <p>
    The return value is the SPVM::Data::Array object that represents the "int[] value" of SPVM.
  </p>
  <p>
    If the first argument is an Undefined Value, an Undefined Value is returned.
  </p>

<h4 id="exchange-api-perl-binary-to-spvm-long-array">Convert Perl Binary Data to SPVM long[] value - SPVM::new_long_array_from_bin</h4>
  <p>
    To convert Perl Binary Data to the SPMV long[] value, use the SPVM::new_long_array_from_bin function.
  </p>
<pre>
my $perl_binary = pack('q3', 97, 98, 99);
my $spvm_long_array = SPVM::new_long_array_from_bin($perl_binary);
</pre>
  <p>
    The first argument takes Perl Binary Data.
  </p>
  <p>
    Binary columns are interpreted as a 64-bit signed integer sequence arranged in byte order in the execution environment. The length is the length when interpreted as a 64-bit signed integer.
  </p>
  <p>
    The return value is the SPVM::Data::Array object that represents the "long[]" type of SPVM.
  </p>
  <p>
    If the first argument is an Undefined Value, an Undefined Value is returned.
  </p>

<h4 id="exchange-api-perl-binary-to-spvm-float-array">Convert Perl Binary Data to SPVM float[] value - SPVM::new_float_array_from_bin</h4>
  <p>
    To convert Perl Binary Data to the SPVM float[] value, use the SPVM::new_float_array_from_bin function.
  </p>
<pre>
my $perl_binary = pack('f3', 0.5, 1.5, 2.5);
my $spvm_float_array = SPVM::new_float_array_from_bin($perl_binary);
</pre>
  <p>
    The first argument takes Perl Binary Data.
  </p>
  <p>
    Binary columns are interpreted as 32-bit floating-point sequences arranged in byte order in the execution environment. The length is the length when interpreted as a 32-bit floating point.
  </p>
  <p>
    The return value is the SPVM::Data::Array object that represents the "float[] value" of SPVM.
  </p>
  <p>
    If the first argument is an Undefined Value, an Undefined Value is returned.
  </p>

<h4 id="exchange-api-perl-binary-to-spvm-double-array">Convert Perl Binary Data to SPVM double[] value - SPVM::new_double_array_from_bin</h4>
  <p>
    To convert Perl Binary Data to the double[] type of SPVM, use the SPVM::new_double_array_from_bin function.
  </p>
<pre>
my $perl_binary = pack('f3', 0.5, 1.5, 2.5);
my $spvm_double_array = SPVM::new_double_array_from_bin($perl_binary);
</pre>
  <p>
    The first argument takes Perl Binary Data.
  </p>
  <p>
    Binary columns are interpreted as 32-bit floating-point sequences arranged in byte order in the execution environment. The length is the length when interpreted as a 32-bit floating point.
  </p>
  <p>
    The return value is the SPVM::Data::Array object that represents the "double[] type" of SPVM.
  </p>
  <p>
    If the first argument is an Undefined Value, an Undefined Value is returned.
  </p>

<h4 id="exchange-api-perl-binary-to-spvm-value-array">Convert Perl Binary Data to SPVM Multi Numeric Array - SPVM::new_mulnum_array_from_bin</h4>
  <p>
    To convert Perl Binary Data to SPVM Multi Numeric Array, use the SPVM::new_mulnum_array_from_bin function.
  </p>
<pre>
my $binary = pack('l9', ($INT_MIN, 1, 2), (3, 4, 5), (6, 7, 8));
my $spvm_mulnum_array = SPVM::new_mulnum_array_from_bin("TestCase::Point_3i[],"$binary);
</pre>
  <p>
    The first argument specifies the Perl packed binaries. The length of the binary is multiplied by the number of multinumeric fields and the field width, which must be disdivided. Otherwise, an Exception is raised.
  </p>
  <p>
    The second argument specifies the array type of the value of the SPVM.
  </p>
  <p>
    The return value is an "SPVM::Data::Array" object that represents the array type of the Value of SPVM. The length of the returned array is the length of the binary, multiplied by the number of multinumeric fields and the field width, divided.
  </p>
  <p>
    There are some samples.
  </p>
<pre>
# new_mulnum_array_from_bin - byte
{
  my $binary = pack('c9', (0, 1, 2), (3, 4, 5), (6, 7, 8));
  my $spvm_mulnum_array = SPVM::new_mulnum_array_from_bin("TestCase::Point_3b[]", $binary);
}

# new_mulnum_array_from_bin - short
{
  my $binary = pack('s9', (0, 1, 2), (3, 4, 5), (6, 7, 8);;
  my $spvm_mulnum_array = SPVM::new_mulnum_array_from_bin("TestCase::Point_3s[]",$binary);
}

# new_mulnum_array_from_bin - int
{
  my $binary = pack('l9', (0, 1, 2), (3, 4, 5), (6, 7, 8));
  my $spvm_mulnum_array = SPVM::new_mulnum_array_from_bin("TestCase::Point_3i[],"$binary);
}

# new_mulnum_array_from_bin - long
{
  my $binary = pack('q9', (0, 1, 2), (3, 4, 5), (6, 7, 8));
  my $spvm_mulnum_array = SPVM::new_mulnum_array_from_bin("TestCase::Point_3l[]", $binary);
}

# new_mulnum_array_from_bin - float
{
  my $binary = pack('f9', (0, 1, 2), (3, 4, 5), (6, 7, 8));
  my $spvm_mulnum_array = SPVM::new_mulnum_array_from_bin("TestCase::Point_3f[],"$binary);
}

# new_mulnum_array_from_bin - double
{
  my $binary = pack('d9', (0, 1, 2), (3, 4, 5), (6, 7, 8));
  my $spvm_mulnum_array = SPVM::new_mulnum_array_from_bin("TestCase::Point_3d[],"$binary);
}
</pre>
  
<p>
    The first argument specifies the array type of the value of the SPVM.
  </p>
  <p>
    The second argument is Array Reference with a hash reference on the element. The key of the hash reference must contain the values of all fields of multiNumeric Type. Otherwise, an Exception is raised.
  </p>

  <h4 id = "exchange-api-perl-string-to-spvm-byte-array">Convert Perl string to SPVM byte[] value - SPVM::new_byte_array_from_string</h4>
  <p>
    To convert Perl string to SPVM byte[] value, use SPVM::new_byte_array_from_string function. A Perl string here refers to a decoded string.
  </p>
<pre>
use utf8;
my $spvm_byte_array = SPVM::new_byte_array_from_string("aiueo");
</pre>
  <p>
    It receives a Perl string as the first argument. A Perl string here refers to a decoded string.
  </p>
  <p>
    The length is the length when counting the byte string as UTF-8.
  </p>
  <p>
    The return value is a "SPVM::Data::Array" object that represents the "byte[]" type of SPVM.
  </p>
  <p>
    If the first argument is an Undefined Value, the Undefined Value will be returned.
  </p>

  <h4 id= "exchange-api-perl-string-to-spvm-string">Perl Convert string to SPVM string - SPVM::new_string</h4>
  <p>
    To convert perl strings to SPVM string types, use the SPVM::new_string function. Perl strings refer to decoded strings here.
  </p>
<pre>
use utf8;
my $spvm_string = SPVM::new_string("Aiueo");
</pre>
  <p>
    The first argument takes a Perl string.
  </p>
  <p>
    The length is utf-8, the length of the byte sequence counted.
  </p>
  <p>
    The return value is the SPVM::Data::Array object that represents the "byte[] value" of SPVM. The string type of SPVM is treated as a byte[] value at run time.
  </p>
  <p>
    If the first argument is an Undefined Value, an Undefined Value is returned.
  </p>
  <p>
    This function is actually an alias for <a href="#exchange-api-perl-string-to-spvm-byte-array">SPVM::new_byte_array_from_string</a>.
  </p>

<h3 id="exchange-api-spvm-value-to-perl-data">Convert SPVM Value to Perl Data</h3>
  <ul class="toc">
    <li><a href="#exchange-api-spvm-array-length">Get SPVM Array Length - length</a></li>
    <li><a href="#exchange-api-spvm-array-to-perl-binary">Convert SPVM Array to Perl Binary Data - to_bin</a></li>
    <li><a href="#exchange-api-spvm-string-to-perl-string">Convert SPVM strings to Perl strings - to_string</a></li>
    <li><a href="#exchange-api-spvm-string-array-to-perl-string-string-array-ref">Convert SPVM string Array into perl string Array Reference - to_strings</a></li>
  </ul>

<h4 id="exchange-api-spvm-array-length">Get SPVM Array Length - length</h4>
  <p>
    Get SPVM Array Length
  </p>

<pre>
my $length = $spvm_array->length;
</pre>

<h4 id="exchange-api-spvm-array-to-perl-array-ref">Convert SPVM Array to Perl Array Reference - to_elems</h4>
  <p>
    To convert SPVM Array to Perl Array Reference, use the SPVM::Data::Array to_elems method.
  </p>
<pre>
my $perl_array_ref = $spvm_array->to_elems;
</pre>
  <p>
    If the elements of the SPVM Array are Numeric Types, the <a href="#exchange-api-rule-spvm-numeric-to-perl-scalar">SPVM Numeric Value is converted by the</a> Rule that convert Numeric Types of Perl to Perl scalar datas.
  </p>
  <p>
    If the element of the SPVM Array is an object type, the corresponding SPVM::Data or its subclass is created.
  </p>
  <p>
    If the elements of the SPVM Array are multiNumeric Types, a hash reference is created with the key and value of the field. The value is converted by a rule that converts the Numeric Type of <a href="#exchange-api-rule-spvm-numeric-to-perl-scalar">SPVM to Perl scalar datas</a>.
  </p>
  <p>
    If the elements of the SPVM Array are Undefined Values, they is converted to undefined Perl values.
  </p>

<h4 id="exchange-api-spvm-array-to-perl-binary">Convert SPVM Array to Perl Binary Data - to_bin</h4>
  <p>
    To convert SPVM Array to Perl Binary Data, use the SPVM::Data::Array to_bin method.
  </p>
<pre>
my $perl_binary = $spvm_array->to_bin;
</pre>
  <p>
    If the SPVM Array is a numeric array type or a value array type, the binary representation in SPVM is copied directly into the scalar variable.
  </p>
  <p>
    If the Array of SPVM is of any other type, an Exception is raised.
  </p>

<h4 id="exchange-api-spvm-string-to-perl-string">Convert SPVM string to Perl string - to_string</h4>
  <p>
    To convert SPVM string to a Perl string, use the SPVM::Data::Array to_string method.
  </p>
<pre>
my $perl_string = $spvm_string->to_string;
</pre>
  <p>
    If the SPVM type is of byte[] or string type, it is converted to a string decoded by Perl UTF-8.
  </p>
  <p>
    If the Data in SPVM is an Undefined Value, it is converted to an Undefined Value in Perl.
  </p>
  <p>
    If the Data in SPVM is of a type other than the above, an Exception is raised.
  </p>

<h4 id="exchange-api-spvm-string-array-to-perl-string-string-string-array-ref">Convert SPVM string Array to Perl Array Reference that element is string - to_strings</h4>
  <p>
    To convert SPVM string Array to Perl Array Reference that element is string, use the SPVM::Data::Array to_strings method.
  </p>
<pre>
my $perl_array_ref = $spvm_string_array->to_strings;
</pre>
  <p>
    If the SPVM type is of byte[]], or string[], it is converted to a reference for an array of perl UTF-8 decoded strings.
  </p>
  <p>
    If an element of the SPVM Array type is an Undefined Value, it is converted to an Undefined Value in Perl.
  </p>
  <p>
    If the Data in SPVM is of a type other than the above, an Exception is raised.
  </p>

<h3 id="exchange-api-call-spvm-sub">Call SPVM Method</h3>
  
<ul class="toc">
  <li><a href="#exchange-api-call-spvm-sub-use-Module">Load SPVM Module</a></li>
  <li><a href="#exchange-api-call-spvm-sub-sub-call">Call Method</a></li>
  <li><a href="#exchange-api-call-spvm-sub-method-call">Call Method</a></li>
  <li><a href="#exchange-api-call-spvm-sub-convert-argument">Argument Type Conversion</a></li>
  <li><a href="#exchange-api-call-spvm-sub-convert-return-value">Return Value Type Conversion</a></li>
</ul>
  
<h4 id="exchange-api-call-spvm-sub-use-Module">Load SPVM Module</h4>
<p>
The SPVM Module can be loaded from Perl as follows: The Module name and search Rule are the same as Perl, except that the extension is "spvm".
</p>

<pre>
# script.pl
use SPVM 'Foo';
</pre>

  <p>
    Suppose the following Foo.spvm is placed on the Module search path.
  </p>

<pre>
# Foo.spvm
package Foo {
  sub sum : int ($x1: int, $x2: int) {
    return $x1 + $x2;
  }
}
</pre>

  <h4 id = "exchange-api-call-spvm-sub-sub-call">Call Method</h4>
  <p>
    In order to call a Method, the SPVM Module must be loaded by <a href="#exchange-api-call-spvm-sub-use-Module">Load SPVM Module</a>.
  </p>
  
<pre>
# script.pl
use SPVM 'Foo';
</pre>

  <p>
    Suppose the following Foo.spvm is placed on the Module search path.
  </p>

<pre>
# Foo.spvm
package Foo {
  sub sum : int ($x1: int, $x2: int) {
    return $x1 + $x2;
  }
}
</pre>

  <p>
    SPVM Method are wrapped in Perl Method and can be called using Perl class Call Method.
  </p>

<pre>
# script.pl
use SPVM 'Foo';

my $total = Foo->sum(1, 2);
</pre>
  <p>
    If the number of arguments does not match the number of arguments of the SPVM Method, an Exception will be thrown.
  </p>
  <p>
    The Perl value passed as an argument is converted to the SPVM value by <a href="#exchange-api-call-spvm-sub-convert-argument">Argument Type Conversion</a>.
  </p>
  <p>
    If the converted type does not match the argument type of the SPVM Method, an Exception is thrown.
  </p>
  <p>
    The return value is transformed by the conversion on the return value.
  </p>
  <p>
    SPVM Exception is converted to Perl Exception.
  </p>

  <h4 id = "exchange-api-call-spvm-sub-method-call">Call Method</h4>
  <p>
    In order to call the method, the SPVM Module must be loaded by <a href="#exchange-api-call-spvm-sub-use-Module">Load SPVM Module</a>.
  </p>
  
<pre>
# script.pl
use SPVM 'Foo';
</pre>

  <p>
    Suppose the following Foo.spvm is placed on the Module search path.
  </p>

<pre>
# Foo.spvm
package Foo {
  sub new : Foo () {
    return new Foo;
  }

  sub sum : int ($self: self, $x1: int, $x2: int) (
    return $x1 + $x2;
  }
}
</pre>

  <p>
    SPVM Method are wrapped in Perl Method and can be called using Perl Call Method.
  </p>

<pre>
# script.pl
use SPVM 'Foo';

my $foo = Foo->new;

my $total = $foo->sum(1, 2);
</pre>
  <p>
    If the number of arguments does not match the number of arguments of the SPVM Method, an Exception will be thrown.
  </p>
  <p>
    The Perl value passed as an argument is converted to the SPVM value by <a href="#exchange-api-call-spvm-sub-convert-argument">Argument Type Conversion</a>.
  </p>
  <p>
    If the converted type does not match the argument type of the SPVM Method, an Exception is thrown.
  </p>
  <p>
    The return value is transformed by the conversion on the return value.
  </p>
  <p>
    SPVM Exception is converted to Perl Exception.
  </p>

  <h4 id = "exchange-api-call-spvm-sub-convert-argument">Argument Type Conversion</h4>

  <h5>Numeric Type</h5>
  <p>
    If the argument type of the SPVM Method definition is a Numeric Type, the argument value is <a href="#exchange-api-rule-perl-scalar-to-spvm-numeric">Perl scalar data. It is converted</a> to SPVM number by the Rule to Convert to SPVM number types.
  </p>
<pre>
# SPVM Method definition
package Foo {
  sub call_byte : void ($num: byte);
  sub call_short : void ($num: short);
  sub call_int : void ($num: int);
  sub call_long : void ($num: long);
  sub call_float : void ($num: float);
  sub call_double : void ($num: double);
}

# Call from Perl
Foo->call_byte(23);
Foo->call_short(23);
Foo->call_int(23);
Foo->call_long(23);
Foo->call_float(2.3);
Foo->call_double(2.3);
</pre>

  <h5>Multi Numeric Type</h5>
  <p>
    If the argument type in the SPVM Method definition was a Multi Numeric Type, the argument value must be a hash reference and the key must contain all Multi Numeric field names. Otherwise, an Exception will be raised. The value of the hash reference is <a href="#exchange-api-rule-perl-scalar-to-spvm-numeric">The rule that converts the scalar value of Perl to the Numeric Type of SPVM</a> Is converted to a value.
  </p>
<pre>
# SPVM Method definition
package Foo {
  sub call_complex_float : void ($z: SPVM::Complex_2f);
  sub call_complex_double : void ($z: SPVM::Complex_2d);
}

# Call from Perl
Foo->call_complex_float({re => 2.3, im => 5.6});
Foo->call_complex_double({re => 2.3, im => 5.6});
</pre>
  
  <h5>Numeric Reference Type</h5>
  <p>
    If the argument type in the SPVM Method definition was a Numeric Reference Type, the argument value must be a scalar reference. Otherwise, an Exception will be raised.
  </p>
<pre>
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
</pre>
<p>
    If the argument type in the SPVM Method definition was a Multi Numeric Reference Type, the argument value is a hash reference reference and the key contains all Multi Numeric field names. is needed. Otherwise, an Exception will be raised.
  </p>
  <p>
    If the argument type of the SPVM Method definition is a numeric array type, the Perl Array Reference is converted to the corresponding Perl SPVM::Data::Array object. The value of the element is <a href="#exchange-api-rule-perl-scalar-to-spvm-numeric">The rule that converts the scalar value of Perl to the Numeric Type of SPVM</a> Will be converted to. The argument is a string,
  </p>
  <p>
    If the argument type of the SPVM Method definition is a byte[] value, the Perl decoded string is encoded in UTF-8 and represents byte[] Perl's SPVM::Data: Converted to a: Array object.
  </p>
  <p>
    If the argument type of the SPVM Method definition is an object type and the value passed to the argument is an Undefined Value, it is converted to the SPVM Undefined Value.
  </p>
  <p>
    If the argument type of the SPVM Method definition is a string compatible type and the value passed to the argument is a scalar value that is not a reference, it is encoded in UTF-8 and represents the SPVM byte[] value. Converts to a Perl SPVM::Data::Array object.
  </p>
  <p>
    If the argument type of the SPVM Method definition is a string compatible array type and the value passed to the argument is Array Reference and the first element is a scalar value that is not a reference, SPVM byte[] Converted to a Perl SPVM::Data::Array object representing[]. If the element has an Undefined Value, it is converted to SPVM Undefined Value, otherwise it is encoded to UTF-8 and converted to SPVM byte[] value.
  </p>
  <p>
    If the argument type of the SPVM Method definition is a byte[] value and the value passed to the argument is Array Reference, convert it to a Perl SPVM::Data::Array object that represents byte[]. Will be done. The element value is converted by the <a href="#exchange-api-rule-perl-scalar-to-spvm-numeric">Rule to Convert Perl scalar data ​​to SPVM Numeric Value</a>.
  </p>
  <p>
    If the argument type of the SPVM Method definition is a short[] value and the value passed to the argument is Array Reference, convert it to a Perl SPVM::Data::Array object that represents a short[]. Will be done. The element value is converted by the <a href="#exchange-api-rule-perl-scalar-to-spvm-numeric">Rule to Convert Perl scalar data ​​to SPVM Numeric Value</a>.
  </p>
  <p>
    If the argument type of the SPVM Method definition is int[] value and the value passed to the argument is Array Reference, convert it to a Perl SPVM::Data::Array object that represents int[] Will be done. The element value is converted by the <a href="#exchange-api-rule-perl-scalar-to-spvm-numeric">Rule to Convert Perl scalar data ​​to SPVM Numeric Value</a>.
  </p>
  <p>
    If the argument type of the SPVM Method definition is a long[] type and the value passed to the argument is Array Reference, convert it to a Perl SPVM::Data::Array object representing long[]. Will be done. The element value is converted by the <a href="#exchange-api-rule-perl-scalar-to-spvm-numeric">Rule to Convert Perl scalar data ​​to SPVM Numeric Value</a>.
  </p>
  <p>
    If the argument type of the SPVM Method definition is float[] value and the value passed to the argument is Array Reference, convert it to a Perl SPVM::Data::Array object that represents float[]. Will be done. The element value is converted by the <a href="#exchange-api-rule-perl-scalar-to-spvm-numeric">Rule to Convert Perl scalar data ​​to SPVM Numeric Value</a>.
  </p>
  <p>
    If the argument type of the SPVM Method definition is double[] type and the value passed to the argument is Array Reference, convert it to a Perl SPVM::Data::Array object that represents double[]. Will be done. The element value is converted by the <a href="#exchange-api-rule-perl-scalar-to-spvm-numeric">Rule to Convert Perl scalar data ​​to SPVM Numeric Value</a>.
  </p>
  <p>
    If the argument type of the SPVM Method definition is an object[] type and the value passed to the argument is Array Reference, convert it to a Perl SPVM::Data::Array object that represents object[]. Will be done. If the element value is an Undefined Value, it is converted to SPVM undefined, and if it is a non-reference scalar value, it is encoded to UTF-8 and converted to SPVM byte[] value. If it is SPVM::Data object, it will not be converted. Otherwise, an Exception will be raised.
  </p>
  
  <h4 id = "exchange-api-call-spvm-sub-convert-return-value">Return Value Type Conversion</h4>
  <p>
    If the return value is a Numeric Type of SPVM, <a href="#exchange-api-rule-spvm-numeric-to-perl-scalar">Rule to Convert the Numeric Type of SPVM to a scalar value of Perl It is converted to a Perl scalar data by</a>.
  </p>
  <p>
    If the return value is a SPVM Multi Numeric Type, it will be converted to a hash reference. The key is the SPVM Multi Numeric field name and the value is <a href="#exchange-api-rule-spvm-numeric-to-perl-scalar">SPVM Numeric Value is converted to Perl scalar data. The value is converted to a Perl scalar data by the rule</a>.
  </p>
  <p>
    If the return value is an Undefined Value for the SPVM object type, it will be converted to a Perl Undefined Value.
  </p>
  <p>
    If the return value is SPVM Array type(including generic object array type), it will be converted to the corresponding Perl SPVM::Data::Array object.
  </p>
  <p>
    If the return value is an object type other than the SPVM Array type, it will be converted to the corresponding Perl SPVM::Data object.
  </p>
  
  <h3 id = "exchange-api-utility">Utility Functions</h3>
  <ul class = "toc">
    <li><a href="#exchange-api-utility-exception">Get SPVM Exception - SPVM::exception</a></li>
    <li><a href="#exchange-api-utility-set_exception">SPVM Exception - SPVM::set_exception</a></li>
    <li><a href="#exchange-api-utility-memory_blocks_count">Get number of allocated memory blocks-memory_blocks_count</a></li>
  </ul>
  
  <h4 id = "exchange-api-utility-exception">Get SPVM Exception - SPVM::exception</h4>
  <p>
    Gets the SPVM exception. If the string is not undef, it is considered as UTF-8 and is the decoded string.
  </p>
<pre>
my $exception = SPVM::exception();
</pre>


<h4 id="exchange-api-utility-set_exception">Set SPVM Exception - SPVM::set_exception</h4>
  <p>
    Sets the SPVM exception. The argument specifies the decoded string or undef.
  </p>
<pre>
SPVM::set_exception("Aiu");
SPVM::set_exception(undef);
</pre>

<h4 id="exchange-api-utility-memory_blocks_count">Get Number of Allocated Memory Blocks Count - SPVM::get_memory_blocks_count</h4>
  <p>
    you can use memory_blocks_count function to get the number of reserved memory blocks.
  </p>
<pre>
my $count = SPVM::get_memory_blocks_count();
</pre>
  <p>
    The SPVM runtime reserves memory from the heap when creating Object and creating new week references. The memory reserved by a single memory retrieval operation is called a memory block.
  </p>
  <p>
    SPVM has a reference count GC, and usually you don't need to be aware of memory storage and release, but when you write a Method natively, you might want to make sure that there is no memory leak in your trial.
  </p>
<pre>
# First Memory Blocks Count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# Processing
# ...

# Last Memory Blocks Count
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();

$end_memory_blocks_count == $start_memory_blocks_count) {
  die"Memroy leak";
}
</pre>

<h3 id="exchange-api-rule-perl-scalar-to-spvm-numeric">Rule to Convert Perl scalar data to SPVM Numeric Value</h3>

<p>
    The Rule to Convert Perl scalar data to SPVM Numeric Value are defined below.
  </p>
  <p>
    Conversion Rule are written in C. SvIV and SvNV are functions defined in perlapi. int8_t, int16_t, int32_t, int64_t, float, double are the types defined in C99.
  </p>

<p>
    <b>Convert Perl scalar data to SPVM byte value</b>
  </p>
  
<pre>
(int8_t)SvIV(perl_scalar_data)
</pre>

<p>
    <b>Convert Perl scalar data to SPVM short value</b>
  </p>
<pre>
(int16_t)SvIV(perl_scalar_data)
</pre>

<p>
    <b>Convert Perl scalar data to SPVM int value</b>
  </p>
<pre>
(int32_t)SvIV(perl_scalar_data)
</pre>

<p>
    <b>Convert Perl scalar data to SPVM long value</b>
  </p>
<pre>
(int64_t)SvIV(perl_scalar_data)
</pre>

<p>
    <b>Convert Perl scalar data to SPVM float value</b>
  </p>
<pre>
(float)SvNV(perl_scalar_data)
</pre>

<p>
    <b>Convert Perl scalar data to SPVM double value</b>
  </p>
<pre>
(double)SvNV(perl_scalar_data)
</pre>

<h3 id="exchange-api-rule-spvm-numeric-to-perl-scalar">Rule to Convert SPVM Numeric Value to Perl scalar data</h3>

<p>
    The Rule to Convert Perl scalar data to SPVM Numeric Value are defined below.
  </p>
  <p>
    Conversion Rule are written in C. newSViv and newSVnv are functions defined in perlapi. int8_t, int16_t, int32_t, int64_t, float, double are the types defined in C99.      
  </p>

<p>
    <b>Convert SPVM byte value to Perl scalar data</b>
  </p>
  
<pre>
int8_t spvm_byte_value;
newSViv(spvm_byte_value)
</pre>

<p>
    <b>Convert SPVM short value to Perl scalar data</b>
  </p>
<pre>
int16_t spvm_short_value;
newSViv(spvm_short_value)
</pre>

<p>
    <b>Convert SPVM int value to Perl scalar data</b>
  </p>
<pre>
int32_t spvm_int_value;
newSViv(spvm_int_value)
</pre>

<p>
    <b>Convert SPVM long value to Perl scalar data</b>
  </p>
<pre>
int64_t spvm_long_value;
newSViv(spvm_long_value)
</pre>

<p>
    <b>Convert SPVM float value to Perl scalar data</b>
  </p>
<pre>
float spvm_float_value;
newSVnv(spvm_float_value)
</pre>

<p>
    <b>Convert SPVM double value to Perl scalar data</b>
  </p>
<pre>
double spvm_double_value;
newSVnv(spvm_double_value)
</pre>

=end html
