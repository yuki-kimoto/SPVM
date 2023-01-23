package SPVM::ExchangeAPI;

use strict;
use warnings;

use Carp 'confess';

# Fields
sub env {
  my $self = shift;
  if (@_) {
    $self->{env} = $_[0];
    return $self;
  }
  else {
    return $self->{env};
  }
}

sub stack {
  my $self = shift;
  if (@_) {
    $self->{stack} = $_[0];
    return $self;
  }
  else {
    return $self->{stack};
  }
}

# Class Methods
sub new {
  my $class = shift;
  
  my $self = {
    @_
  };
  
  bless $self, ref $class || $class;
  
  return $self;
}

# Instance Methods
sub new_byte_array_from_string {
  my ($self, $string) = @_;
  
  utf8::encode($string);
  
  my $ret;
  eval { $ret = $self->new_byte_array_from_bin($string) };
  if ($@) { confess $@ }
  
  return $ret;
}

sub new_any_object_array {
  my ($self, $array_ref) = @_;
  
  my $type_name = 'object[]';
  
  my $array = $self->new_object_array($type_name, $array_ref);
  
  return $array;
}

sub new_object_array {
  my ($self, $type_name, $elems) = @_;
  
  my $basic_type_name;
  my $type_dimension = 0;
  if ($type_name =~ /^([a-zA-Z_0-9:]+)((\[\])+)$/) {
    $basic_type_name = $1;
    my $type_dimension_part = $2;
    
    while ($type_dimension_part =~ /\[/g) {
      $type_dimension++;
    }
  }
  
  unless ($type_dimension >= 1 && $type_dimension <= 255) {
    confess "Invalid type dimension";
  }
  unless (defined $basic_type_name) {
    confess "Invalid basic type name";
  }
  
  unless (defined $elems) {
    return undef;
  }
  
  # Check second argument
  unless (ref $elems eq 'ARRAY') {
    confess "The elements must be an array reference";
  }
  
  my $ret;
  if ($type_dimension == 1) {
    eval { $ret = $self->_xs_new_object_array($basic_type_name, $elems) };
    if ($@) { confess $@ }
  }
  else {
    eval { $ret = $self->_xs_new_muldim_array($basic_type_name, $type_dimension - 1, $elems) };
    if ($@) { confess $@ }
  }
  
  return $ret;
}

sub new_mulnum_array {
  my ($self, $type_name, $elems) = @_;
  
  my $basic_type_name;
  my $type_dimension = 0;
  if ($type_name =~ /^([a-zA-Z_0-9:]+)((\[\])+)$/) {
    $basic_type_name = $1;
    my $type_dimension_part = $2;
    
    while ($type_dimension_part =~ /\[/g) {
      $type_dimension++;
    }
  }
  
  unless ($type_dimension == 1) {
    confess "Invalid type dimension";
  }
  unless (defined $basic_type_name) {
    confess "Invalid basic type name";
  }

  unless (defined $elems) {
    return undef;
  }
  
  # Check second argument
  unless (ref $elems eq 'ARRAY') {
    confess "The elements must be an array reference";
  }
  
  my $ret;
  eval { $ret = $self->_xs_new_mulnum_array($basic_type_name, $elems) };
  if ($@) { confess $@ }
  
  return $ret;
}

sub new_mulnum_array_from_bin {
  my ($self, $type_name, $elems) = @_;
  
  my $basic_type_name;
  my $type_dimension = 0;
  if ($type_name =~ /^([a-zA-Z_0-9:]+)((\[\])+)$/) {
    $basic_type_name = $1;
    my $type_dimension_part = $2;
    
    while ($type_dimension_part =~ /\[/g) {
      $type_dimension++;
    }
  }
  
  unless ($type_dimension == 1) {
    confess "Invalid type dimension";
  }
  unless (defined $basic_type_name) {
    confess "Invalid basic type name";
  }

  unless (defined $elems) {
    return undef;
  }
  
  my $ret;
  eval { $ret = $self->_xs_new_mulnum_array_from_bin($basic_type_name, $elems) };
  if ($@) { confess $@ }
  
  return $ret;
}

sub set_exception {
  my ($self, $exception) = @_;
  
  if (defined $exception && !ref $exception) {
    $exception = $self->new_string($exception);
  }
  
  my $ret;
  eval { $ret = $self->_xs_set_exception($exception) };
  if ($@) { confess $@ }
  
  return $ret;
}

# other functions is implemented in SPVM.xs

sub new_byte_array { my $ret; eval { $ret =  &xs_new_byte_array(@_) }; if ($@) { confess $@ } $ret}
sub new_byte_array_unsigned { my $ret; eval { $ret =  &xs_new_byte_array_unsigned(@_) }; if ($@) { confess $@ } $ret}
sub new_byte_array_len { my $ret; eval { $ret =  &xs_new_byte_array_len(@_) }; if ($@) { confess $@ } $ret}
sub new_byte_array_from_bin { my $ret; eval { $ret =  &xs_new_byte_array_from_bin(@_) }; if ($@) { confess $@ } $ret}
sub new_short_array { my $ret; eval { $ret =  &xs_new_short_array(@_) }; if ($@) { confess $@ } $ret}
sub new_short_array_unsigned { my $ret; eval { $ret =  &xs_new_short_array_unsigned(@_) }; if ($@) { confess $@ } $ret}
sub new_short_array_len { my $ret; eval { $ret =  &xs_new_short_array_len(@_) }; if ($@) { confess $@ } $ret}
sub new_short_array_from_bin { my $ret; eval { $ret =  &xs_new_short_array_from_bin(@_) }; if ($@) { confess $@ } $ret}
sub new_int_array { my $ret; eval { $ret =  &xs_new_int_array(@_) }; if ($@) { confess $@ } $ret}
sub new_int_array_unsigned { my $ret; eval { $ret =  &xs_new_int_array_unsigned(@_) }; if ($@) { confess $@ } $ret}
sub new_int_array_len { my $ret; eval { $ret =  &xs_new_int_array_len(@_) }; if ($@) { confess $@ } $ret}
sub new_int_array_from_bin { my $ret; eval { $ret =  &xs_new_int_array_from_bin(@_) }; if ($@) { confess $@ } $ret}
sub new_long_array { my $ret; eval { $ret =  &xs_new_long_array(@_) }; if ($@) { confess $@ } $ret}
sub new_long_array_unsigned { my $ret; eval { $ret =  &xs_new_long_array_unsigned(@_) }; if ($@) { confess $@ } $ret}
sub new_long_array_len { my $ret; eval { $ret =  &xs_new_long_array_len(@_) }; if ($@) { confess $@ } $ret}
sub new_long_array_from_bin { my $ret; eval { $ret =  &xs_new_long_array_from_bin(@_) }; if ($@) { confess $@ } $ret}
sub new_double_array { my $ret; eval { $ret =  &xs_new_double_array(@_) }; if ($@) { confess $@ } $ret}
sub new_double_array_len { my $ret; eval { $ret =  &xs_new_double_array_len(@_) }; if ($@) { confess $@ } $ret}
sub new_double_array_from_bin { my $ret; eval { $ret =  &xs_new_double_array_from_bin(@_) }; if ($@) { confess $@ } $ret}
sub new_float_array { my $ret; eval { $ret =  &xs_new_float_array(@_) }; if ($@) { confess $@ } $ret}
sub new_float_array_len { my $ret; eval { $ret =  &xs_new_float_array_len(@_) }; if ($@) { confess $@ } $ret}
sub new_float_array_from_bin { my $ret; eval { $ret =  &xs_new_float_array_from_bin(@_) }; if ($@) { confess $@ } $ret}
sub new_string_array { my $ret; eval { $ret =  &xs_new_string_array(@_) }; if ($@) { confess $@ } $ret}
sub get_exception { my $ret; eval { $ret =  &xs_get_exception(@_) }; if ($@) { confess $@ } $ret}
sub string_object_to_string { my $ret; eval { $ret =  &xs_string_object_to_string(@_) }; if ($@) { confess $@ } $ret}
sub get_memory_blocks_count { my $ret; eval { $ret =  &xs_get_memory_blocks_count(@_) }; if ($@) { confess $@ } $ret}
sub call_method { my $ret; eval { $ret =  &xs_call_method(@_) }; if ($@) { confess $@ } $ret}
sub new_string { my $ret; eval { $ret =  &xs_new_string(@_) }; if ($@) { confess $@ } $ret}
sub new_string_from_bin { my $ret; eval { $ret =  &xs_new_string_from_bin(@_) }; if ($@) { confess $@ } $ret}
sub string_object_to_bin { my $ret; eval { $ret =  &xs_string_object_to_bin(@_) }; if ($@) { confess $@ } $ret}
sub array_length { my $ret; eval { $ret =  &xs_array_length(@_) }; if ($@) { confess $@ } $ret}
sub array_to_elems { my $ret; eval { $ret =  &xs_array_to_elems(@_) }; if ($@) { confess $@ } $ret}
sub array_to_bin { my $ret; eval { $ret =  &xs_array_to_bin(@_) }; if ($@) { confess $@ } $ret}
sub array_set { my $ret; eval { $ret =  &xs_array_set(@_) }; if ($@) { confess $@ } $ret}
sub array_get { my $ret; eval { $ret =  &xs_array_get(@_) }; if ($@) { confess $@ } $ret}
sub new_address_object { my $ret; eval { $ret =  &xs_new_address_object(@_) }; if ($@) { confess $@ } $ret}

1;

=head1 Name

SPVM::ExchangeAPI - SPVM Exchange API

=head1 Description

C<SPVM::ExchangeAPI> is APIs to convert Perl data structures to/from SPVM data structures, and call SPVM Method from Perl.

=head1 Usage

  my $api = SPVM::ExchangeAPI->new(env => $env, stack => $stack);
  my $int_array = $api->new_int_array([1, 2, 3]);

Getting an global ExchangeAPI object:

  my $api = SPVM::api();
  my $int_array = $api->new_int_array([1, 2, 3]);

=head1 Fields

=head2 env

  my $env = $api->env;

Gets the execution environment.

=head2 stack

  my $stack = $api->stack;

Gets the call stack.

=head1 Class Methods

  my $api = SPVM::ExchangeAPI->new(env => $env, stack => $stack);

Creates a new L<SPVM::ExchangeAPI> object.

Options:

=over 2

=item C<env>

An execution environment.

=item C<stack>

An stack.

=back

=head1 Instance Methods

=head2 new_byte_array

  my $spvm_nums = $api->new_byte_array([1, 2, 3]);

Convert a Perl array reference to a SPVM C<byte[]> array. Return value is L<SPVM::BlessedObject::Array> object which wraps the SPVM array.

If the first argument is a C<undef> value, the return value is a C<undef> value.

=head2 new_byte_array_len

  my $spvm_nums = $api->new_byte_array_len([1, 2, 3]);

Create a new SPVM C<byte[]> array with length. The values of elements is zeros. Return value is L<SPVM::BlessedObject::Array> object which wraps the SPVM array.

The lenght must be greater than or equal to zero. Otherwise an exception will occur.

=head2 new_byte_array_from_bin

  my $perl_binary = pack('c3', 97, 98, 99);
  my $spvm_byte_array = $api->new_byte_array_from_bin($perl_binary);

Convert a Perl Binary Data to SPVM byte[] object. Return value is L<SPVM::BlessedObject::Array> object which wraps the SPVM array.

Thg Perl binary data is interpreted as 8-bit signed integers. The created array length is automatically calcurated from the Perl binary data.

If the first argument is C<undef>, C<undef> is returned.

You can use simple ascii codes as Perl binary data.

  my $perl_binary ="abc";
  my $spvm_byte_array = $api->new_byte_array_from_bin($perl_binary);

or UTF-8 bytes.
  
  use utf8;
  my $perl_binary = encode('UTF-8', "あいう");
  my $spvm_string = $api->new_string_from_bin($perl_binary);

=head2 new_byte_array_from_string

  use utf8;
  my $spvm_byte_array = $api->new_byte_array_from_string("あいう");

Convert a decoded string to SPVM byte[] value using L<utf8::encode|utf8>. Return value is L<SPVM::BlessedObject::Array> object which wraps the SPVM array.

=head2 new_short_array

  my $spvm_nums = $api->new_short_array([1, 2, 3]);

Convert a Perl array reference to a SPVM C<short[]> array. Return value is L<SPVM::BlessedObject::Array> object which wraps the SPVM array.

If the first argument is a C<undef> value, the return value is a C<undef> value.

=head2 new_short_array_len

  my $spvm_nums = $api->new_short_array_len($length);

Create a new  a SPVM C<short[]> array with length. The values of elements is zeros. Return value is L<SPVM::BlessedObject::Array> object which wraps the SPVM array.

The lenght must be greater than or equal to zero. Otherwise an exception will occur.

=head2 new_short_array_from_bin

  my $perl_binary = pack('c3', 97, 98, 99);
  my $spvm_short_array = $api->new_short_array_from_bin($perl_binary);

Convert a Perl Binary Data to SPVM short[] object. Return value is L<SPVM::BlessedObject::Array> object which wraps the SPVM array.

Thg Perl binary data is interpreted as 16-bit signed integers. The created array length is automatically calcurated from the Perl binary data.

If the first argument is C<undef>, C<undef> is returned.

=head2 new_int_array

  my $spvm_nums = $api->new_int_array([1, 2, 3]);

Convert a Perl array reference to a SPVM C<int[]> array. Return value is L<SPVM::BlessedObject::Array> object which wraps the SPVM array.

If the first argument is a C<undef> value, the return value is a C<undef> value.

=head2 new_int_array_len

  my $spvm_nums = $api->new_int_array_len($length);

Create a new  a SPVM C<int[]> array with length. The values of elements is zeros. Return value is L<SPVM::BlessedObject::Array> object which wraps the SPVM array.

The lenght must be greater than or equal to zero. Otherwise an exception will occur.

=head2 new_int_array_from_bin

  my $perl_binary = pack('l3', 97, 98, 99);
  my $spvm_int_array = $api->new_int_array_from_bin($perl_binary);

Convert a Perl Binary Data to SPVM int[] object. Return value is L<SPVM::BlessedObject::Array> object which wraps the SPVM array.

Thg Perl binary data is interpreted as 8-bit signed integers. The created array length is automatically calcurated from the Perl binary data.

If the first argument is C<undef>, C<undef> is returned.

=head2 new_long_array

  my $spvm_nums = $api->new_long_array([1, 2, 3]);

Convert a Perl array reference to a SPVM C<long[]> array. Return value is L<SPVM::BlessedObject::Array> object which wraps the SPVM array.

If the first argument is a C<undef> value, the return value is a C<undef> value.

=head2 new_long_array_len

  my $spvm_nums = $api->new_long_array_len($length);

Create a new  a SPVM C<long[]> array with length. The values of elements is zeros. Return value is L<SPVM::BlessedObject::Array> object which wraps the SPVM array.

The lenght must be greater than or equal to zero. Otherwise an exception will occur.

=head2 new_long_array_from_bin

  my $perl_binary = pack('q3', 97, 98, 99);
  my $spvm_long_array = $api->new_long_array_from_bin($perl_binary);

Convert a Perl Binary Data to SPVM long[] object. Return value is L<SPVM::BlessedObject::Array> object which wraps the SPVM array.

Thg Perl binary data is longerpreted as 8-bit signed longegers. The created array length is automatically calcurated from the Perl binary data.

If the first argument is C<undef>, C<undef> is returned.

=head2 new_float_array

  my $spvm_nums = $api->new_float_array([1.2, 2.5, 3.3]);

Convert a Perl array reference to a SPVM C<float[]> array. Return value is L<SPVM::BlessedObject::Array> object which wraps the SPVM array.

If the first argument is a C<undef> value, the return value is a C<undef> value.

=head2 new_float_array_len

  my $spvm_nums = $api->new_float_array_len($length);

Create a new  a SPVM C<float[]> array with length. The values of elements is zeros. Return value is L<SPVM::BlessedObject::Array> object which wraps the SPVM array.

The lenght must be greater than or equal to zero. Otherwise an exception will occur.

=head2 new_float_array_from_bin

  my $perl_binary = pack('f3', 0.5, 1.5, 2.5);
  my $spvm_float_array = $api->new_float_array_from_bin($perl_binary);

Convert a Perl Binary Data to SPVM float[] object. Return value is L<SPVM::BlessedObject::Array> object which wraps the SPVM array.

Thg Perl binary data is floaterpreted as 8-bit signed floategers. The created array length is automatically calcurated from the Perl binary data.

If the first argument is C<undef>, C<undef> is returned.

=head2 new_double_array

  my $spvm_nums = $api->new_double_array([1.2, 2.5, 3.3]);

Convert a Perl array reference to a SPVM C<double[]> array. Return value is L<SPVM::BlessedObject::Array> object which wraps the SPVM array.

If the first argument is a C<undef> value, the return value is a C<undef> value.

=head2 new_double_array_len

  my $spvm_nums = $api->new_double_array_len($length);

Create a new  a SPVM C<double[]> array with length. The values of elements is zeros. Return value is L<SPVM::BlessedObject::Array> object which wraps the SPVM array.

The lenght must be greater than or equal to zero. Otherwise an exception will occur.

=head2 new_double_array_from_bin

  my $perl_binary = pack('f3', 0.5, 1.5, 2.5);
  my $spvm_double_array = $api->new_double_array_from_bin($perl_binary);

Convert a Perl Binary Data to SPVM double[] object. Return value is L<SPVM::BlessedObject::Array> object which wraps the SPVM array.

Thg Perl binary data is doubleerpreted as 8-bit signed doubleegers. The created array length is automatically calcurated from the Perl binary data.

If the first argument is C<undef>, C<undef> is returned.

=head2 new_string

  use utf8;
  my $spvm_string = $api->new_string("あいう");

Convert a Perl string to a SPVM string.

If the argument is C<undef>, C<undef> is returned.

=head2 new_string_from_bin

  my $perl_binary = pack('c3', 97, 98, 99);
  my $spvm_string = $api->new_string_from_bin($perl_binary);

Convert a Perl Binary Data to SPVM string object. Return value is L<SPVM::BlessedObject::String> object which wraps the SPVM string.

Thg Perl binary data is interpreted as 8-bit signed integers. The string length is automatically calcurated from the Perl binary data.

If the first argument is C<undef>, C<undef> is returned.

You can use simple ascii codes as Perl binary data.

  my $binary ="abc";
  my $spvm_string = $api->new_string_from_bin($perl_binary);

or UTF-8 bytes.

  use utf8;
  my $perl_binary = encode('UTF-8', "あいう");
  my $spvm_string = $api->new_string_from_bin($perl_binary);

=head2 new_any_object_array

  my $byte_array = $api->new_any_object_array(
    [SPVM::Byte->new(1), SPVM::Byte>new(2), SPVM::Byte->new(3)]
  );

The alias for the following code using L</"new_object_array">.

  my $spvm_array = $api->new_object_array('object[]', $perl_array_ref);

=head2 new_object_array

  my $byte_array = $api->new_object_array(
    "SPVM::Byte[]",
    [SPVM::Byte->new(1), SPVM::Byte>new(2), SPVM::Byte->new(3)]
  );

Convert a Perl array reference to a SPVM object array. Return value is L<SPVM::BlessedObject::Array> object which wraps the SPVM array.

The first argument is a SPVM array type name. If the type is non-existent, an exception occurs.

The second argument is a Perl array reference. Each element must be valid value or C<undef>. Otherwise an exception will occur.

Return value is L<SPVM::BlessedObject::Array> object which wraps the SPVM array.

You can also create multidimensional array.

  my $object1 = $api->new_int_array([1, 2, 3]);
  my $object2 = $api->new_int_array([4, 5, 6]);
  my $objects = $api->new_object_array("int[][]",[$object1, $object2]);

=head2 new_mulnum_array

Convert a Perl array references to SPVM multi-numeric array.

  my $perl_values = [
    {x => 0, y => 1, z => 2},
    {x => 3, y => 4, z => 5},
    {x => 6, y => 7, z => 8},
  ];
  my $spvm_mulnum_array = $api->new_mulnum_array("TestCase::Point_3i[]", $perl_values);

The first argument is a SPVM array type name. If the type is non-existent, an exception occurs.

The second argument is a Perl array of hash references. Each hash reference must be contain all fields of the multi-numeric value. Otherwise an exception will occur.

Return value is L<SPVM::BlessedObject::Array> object which wraps the SPVM array.

Examples:

  # new_mulnum_array - byte
  {
    my $values = [
      {x => 0, y => 1, z => 2},
      {x => 3, y => 4, z => 5},
      {x => 6, y => 7, z => 8},
    ];
    my $spvm_mulnum_array = $api->new_mulnum_array("TestCase::Point_3b[]", $values);
  }

  # new_mulnum_array - short
  {
    my $values = [
      {x => 0, y => 1, z => 2},
      {x => 3, y => 4, z => 5},
      {x => 6, y => 7, z => 8},
    ];
    my $spvm_mulnum_array = $api->new_mulnum_array("TestCase::Point_3s[]",$values);
  }

  # new_mulnum_array - int
  {
    my $values = [
      {x => 0, y => 1, z => 2},
      {x => 3, y => 4, z => 5},
      {x => 6, y => 7, z => 8},
    ];
    my $spvm_mulnum_array = $api->new_mulnum_array("TestCase::Point_3i[],$values);
  }

  # new_mulnum_array - long
  {
    my $values = [
      {x => 0, y => 1, z => 2},
      {x => 3, y => 4, z => 5},
      {x => 6, y => 7, z => 8},
    ];
    my $spvm_mulnum_array = $api->new_mulnum_array("TestCase::Point_3l[]", $values);
  }

  # new_mulnum_array - float
  {
    my $values = [
      {x => 0, y => 1, z => 2},
      {x => 3, y => 4, z => 5},
      {x => 6, y => 7, z => 8},
    ];
    my $spvm_mulnum_array = $api->new_mulnum_array("TestCase::Point_3f[]",$values);
  }

  # new_mulnum_array - double
  {
    my $values = [
      {x => 0, y => 1, z => 2},
      {x => 3, y => 4, z => 5},
      {x => 6, y => 7, z => 8},
    ];
    my $spvm_mulnum_array = $api->new_mulnum_array("TestCase::Point_3d[],"$values);
    ok(SPVM::TestCase::ExchangeAPI-spvm_new_mulnum_array_double($spvm_mulnum_array));
    my $out_values = $spvm_mulnum_array->to_elems;
    is_deeply($out_values, $values);
  }

=head2 new_mulnum_array_from_bin

  my $binary = pack('l9', ($INT_MIN, 1, 2), (3, 4, 5), (6, 7, 8));
  my $spvm_mulnum_array = $api->new_mulnum_array_from_bin("TestCase::Point_3i[]", $binary);

Convert Perl a binary data to SPVM Multi Numeric Array. Return value is L<SPVM::BlessedObject::Array> object which wraps the SPVM array.

The first argument is a multi-numeric array type of SPVM.

The second argument is the Perl packed binary data. The length of the created array is calcurated automatically.

Examples:
  
  # new_mulnum_array_from_bin - byte
  {
    my $binary = pack('c9', (0, 1, 2), (3, 4, 5), (6, 7, 8));
    my $spvm_mulnum_array = $api->new_mulnum_array_from_bin("TestCase::Point_3b[]", $binary);
  }

  # new_mulnum_array_from_bin - short
  {
    my $binary = pack('s9', (0, 1, 2), (3, 4, 5), (6, 7, 8);;
    my $spvm_mulnum_array = $api->new_mulnum_array_from_bin("TestCase::Point_3s[]", $binary);
  }

  # new_mulnum_array_from_bin - int
  {
    my $binary = pack('l9', (0, 1, 2), (3, 4, 5), (6, 7, 8));
    my $spvm_mulnum_array = $api->new_mulnum_array_from_bin("TestCase::Point_3i[]", $binary);
  }

  # new_mulnum_array_from_bin - long
  {
    my $binary = pack('q9', (0, 1, 2), (3, 4, 5), (6, 7, 8));
    my $spvm_mulnum_array = $api->new_mulnum_array_from_bin("TestCase::Point_3l[]", $binary);
  }

  # new_mulnum_array_from_bin - float
  {
    my $binary = pack('f9', (0, 1, 2), (3, 4, 5), (6, 7, 8));
    my $spvm_mulnum_array = $api->new_mulnum_array_from_bin("TestCase::Point_3f[]", $binary);
  }

  # new_mulnum_array_from_bin - double
  {
    my $binary = pack('d9', (0, 1, 2), (3, 4, 5), (6, 7, 8));
    my $spvm_mulnum_array = $api->new_mulnum_array_from_bin("TestCase::Point_3d[]", $binary);
  }

=head2 get_exception

  my $exception = $api->get_exception();

Get the exception of the SPVM runtime environment as L<SPVM::BlessedObject::String> object.

=head2 set_exception

Set a SPVM exception of the SPVM runtime environment.

The argument must be a L<SPVM::BlessedObject::String> object, a decoded string or C<undef>. Otherwise an exception will occur.

  $api->set_exception($api->new_string("abc"));
  $api->set_exception("abc");
  $api->set_exception(undef);

=head2 get_memory_blocks_count

  my $count = $api->get_memory_blocks_count();

Get the count of created memory blocks. SPVM runtime create a memory block on the heap when a object is created or new week reference is created.

You can check the memory leaks by this method.

  # First Memory Blocks Count
  my $start_memory_blocks_count = $api->get_memory_blocks_count();

  # Processing
  # ...

  # Last Memory Blocks Count
  my $end_memory_blocks_count = $api->get_memory_blocks_count();

  unless ($end_memory_blocks_count == $start_memory_blocks_count) {
    die"Memroy leak";
  }
