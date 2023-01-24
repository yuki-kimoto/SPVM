package SPVM::ExchangeAPI;

use strict;
use warnings;

use SPVM::ExchangeAPI::Class;
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

sub class {
  my ($self, $class_name) = @_;
  
  my $class = SPVM::ExchangeAPI::Class->__new(__class_name => $class_name, __api => $self);
  
  return $class;
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

=encoding utf8

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

  my $sp_nums = $api->new_byte_array([1, 2, 3]);

Converts a Perl numeric array reference to a L<SPVM::BlessedObject::Array> object that has the value of the SPVM C<byte[]> type and returns it.

If the argument is C<undef>, returns C<undef>.

=head2 new_byte_array_len

  my $sp_nums = $api->new_byte_array_len($length);

Create a new L<SPVM::BlessedObject::Array> object that has the value of the SPVM C<byte[]> type with the length.

The length must be greater than or equal to C<0>. Otherwise an exception will occur.

=head2 new_byte_array_from_bin

  my $pl_binary = pack('c3', 97, 98, 99);
  my $sp_nums = $api->new_byte_array_from_bin($pl_binary);

Converts a Perl binary to a L<SPVM::BlessedObject::Array> object that has the value of the SPVM C<byte[]> type and returns it.

The Perl binary is interpreted as 8-bit signed integers. The length of the array is calcurated from the Perl binary.

If the argument is C<undef>, returns C<undef>.

Examples:
  
  # Convert Perl string to SPVM byte[]
  my $pl_binary ="abc";
  my $sp_nums = $api->new_byte_array_from_bin($pl_binary);

=head2 new_byte_array_from_string

  use utf8;
  my $sp_nums = $api->new_byte_array_from_string("あいう");

The same as the L</"new_byte_array_from_bin"> method. Any decoding is not performed.

=head2 new_short_array

  my $sp_nums = $api->new_short_array([1, 2, 3]);

Converts a Perl numeric array reference to a L<SPVM::BlessedObject::Array> object that has the value of the SPVM C<short[]> type and returns it.

If the argument is C<undef>, returns C<undef>.

=head2 new_short_array_len

  my $sp_nums = $api->new_short_array_len($length);

Create a new L<SPVM::BlessedObject::Array> object that has the value of the SPVM C<short[]> type with the length.

The length must be greater than or equal to C<0>. Otherwise an exception will occur.

=head2 new_short_array_from_bin

  my $pl_binary = pack('c3', 97, 98, 99);
  my $sp_nums = $api->new_short_array_from_bin($pl_binary);

Converts a Perl binary to a L<SPVM::BlessedObject::Array> object that has the value of the SPVM C<short[]> type and returns it.

The Perl binary is interpreted as 16-bit signed integers. The length of the array is calcurated from the Perl binary.

If the argument is C<undef>, returns C<undef>.

=head2 new_int_array

  my $sp_nums = $api->new_int_array([1, 2, 3]);

Converts a Perl numeric array reference to a L<SPVM::BlessedObject::Array> object that has the value of the SPVM C<int[]> type and returns it.

If the argument is C<undef>, returns C<undef>.

=head2 new_int_array_len

  my $sp_nums = $api->new_int_array_len($length);

Create a new L<SPVM::BlessedObject::Array> object that has the value of the SPVM C<int[]> type with the length.

The length must be greater than or equal to C<0>. Otherwise an exception will occur.

=head2 new_int_array_from_bin

  my $pl_binary = pack('l3', 97, 98, 99);
  my $sp_nums = $api->new_int_array_from_bin($pl_binary);

Converts a Perl binary to a L<SPVM::BlessedObject::Array> object that has the value of the SPVM C<int[]> type and returns it.

The Perl binary is interpreted as 32-bit signed integers. The length of the array is calcurated from the Perl binary.

If the argument is C<undef>, returns C<undef>.

=head2 new_long_array

  my $sp_nums = $api->new_long_array([1, 2, 3]);

Converts a Perl numeric array reference to a L<SPVM::BlessedObject::Array> object that has the value of the SPVM C<long[]> type and returns it.

If the argument is C<undef>, returns C<undef>.

=head2 new_long_array_len

  my $sp_nums = $api->new_long_array_len($length);

Create a new L<SPVM::BlessedObject::Array> object that has the value of the SPVM C<long[]> type with the length.

The length must be greater than or equal to C<0>. Otherwise an exception will occur.

=head2 new_long_array_from_bin

  my $pl_binary = pack('q3', 97, 98, 99);
  my $sp_nums = $api->new_long_array_from_bin($pl_binary);

Converts a Perl binary to a L<SPVM::BlessedObject::Array> object that has the value of the SPVM C<long[]> type and returns it.

The Perl binary is interpreted as 64-bit signed integers. The length of the array is calcurated from the Perl binary.

If the argument is C<undef>, returns C<undef>.

=head2 new_float_array

  my $sp_nums = $api->new_float_array([1.2, 2.5, 3.3]);

Converts a Perl numeric array reference to a L<SPVM::BlessedObject::Array> object that has the value of the SPVM C<float[]> type and returns it.

If the argument is C<undef>, returns C<undef>.

=head2 new_float_array_len

  my $sp_nums = $api->new_float_array_len($length);

Create a new L<SPVM::BlessedObject::Array> object that has the value of the SPVM C<float[]> type with the length.

The length must be greater than or equal to C<0>. Otherwise an exception will occur.

=head2 new_float_array_from_bin

  my $pl_binary = pack('f3', 0.5, 1.5, 2.5);
  my $sp_nums = $api->new_float_array_from_bin($pl_binary);

Converts a Perl binary to a L<SPVM::BlessedObject::Array> object that has the value of the SPVM C<float[]> type and returns it.

The Perl binary is interpreted as 32-bit floating point. The length of the array is calcurated from the Perl binary.

If the argument is C<undef>, returns C<undef>.

=head2 new_double_array

  my $sp_nums = $api->new_double_array([1.2, 2.5, 3.3]);

Converts a Perl numeric array reference to a L<SPVM::BlessedObject::Array> object that has the value of the SPVM C<double[]> type and returns it.

If the argument is C<undef>, returns C<undef>.

=head2 new_double_array_len

  my $sp_nums = $api->new_double_array_len($length);

Create a new L<SPVM::BlessedObject::Array> object that has the value of the SPVM C<double[]> type with the length.

The length must be greater than or equal to C<0>. Otherwise an exception will occur.

=head2 new_double_array_from_bin

  my $pl_binary = pack('f3', 0.5, 1.5, 2.5);
  my $sp_double_array = $api->new_double_array_from_bin($pl_binary);

Converts a Perl binary to a L<SPVM::BlessedObject::Array> object that has the value of the SPVM C<double[]> type and returns it.

The Perl binary is interpreted as 64-bit floating point. The length of the array is calcurated from the Perl binary.

If the argument is C<undef>, returns C<undef>.

=head2 new_string

  use utf8;
  my $sp_string = $api->new_string("あいう");

Converts a Perl string to a L<SPVM::BlessedObject::String> object. Any decoding is not performed.

If the argument is C<undef>, returns C<undef>.

=head2 new_string_from_bin

  my $pl_binary = pack('c3', 97, 98, 99);
  my $sp_string = $api->new_string_from_bin($pl_binary);

Converts a Perl binary to a L<SPVM::BlessedObject::String>.

The Perl binary is interpreted as 8-bit signed integers. The length of the string is calcurated from the Perl binary.

If the argument is C<undef>, returns C<undef>.

=head2 new_any_object_array

  my $byte_array = $api->new_any_object_array(
    [SPVM::Byte->new(1), SPVM::Byte>new(2), SPVM::Byte->new(3)]
  );

The alias for the following code using L</"new_object_array">.

  my $sp_array = $api->new_object_array('object[]', $pl_array);

=head2 new_object_array

  my $byte_array = $api->new_object_array(
    "SPVM::Byte[]",
    [SPVM::Byte->new(1), SPVM::Byte>new(2), SPVM::Byte->new(3)]
  );

Converts a Perl array reference to a SPVM L<SPVM::BlessedObject::Array> object that has the value of a object array type and returns it.

The first argument is a SPVM array type name. If the type doesn't exist, an exception will occur.

The second argument is a Perl array reference. Each element must be a L<SPVM::BlessedObject> object or C<undef>. Otherwise an exception will occur.

Examples:

  my $object1 = $api->new_int_array([1, 2, 3]);
  my $object2 = $api->new_int_array([4, 5, 6]);
  my $objects = $api->new_object_array("int[][]",[$object1, $object2]);

=head2 new_mulnum_array

Converts a Perl array reference to a L<SPVM::BlessedObject::String> object that has the value of a multi-numeric array type and returns it.

  my $pl_values = [
    {x => 0, y => 1, z => 2},
    {x => 3, y => 4, z => 5},
    {x => 6, y => 7, z => 8},
  ];
  my $sp_mulnum_array = $api->new_mulnum_array("TestCase::Point_3i[]", $pl_values);

The first argument is a SPVM array type name. If the type doesn't exist, an exception will occur.

The second argument is a Perl array of hash references. Each hash reference must be contain all fields of the multi-numeric typee. Otherwise an exception will occur.

=head2 new_mulnum_array_from_bin

  my $binary = pack('l9', (0, 1, 2), (3, 4, 5), (6, 7, 8));
  my $sp_mulnum_array = $api->new_mulnum_array_from_bin("TestCase::Point_3i[]", $binary);

Converts a Perl binary to a L<SPVM::BlessedObject::Array> object that has the value of a multi-numeric array type and returns it.

The first argument is a multi-numeric array type of SPVM.

The second argument is a Perl binary. The length of the array is calcurated from the Perl binary.

Examples:
  
  # new_mulnum_array_from_bin - byte
  {
    my $binary = pack('c9', (0, 1, 2), (3, 4, 5), (6, 7, 8));
    my $sp_mulnum_array = $api->new_mulnum_array_from_bin("TestCase::Point_3b[]", $binary);
  }

  # new_mulnum_array_from_bin - short
  {
    my $binary = pack('s9', (0, 1, 2), (3, 4, 5), (6, 7, 8);;
    my $sp_mulnum_array = $api->new_mulnum_array_from_bin("TestCase::Point_3s[]", $binary);
  }

  # new_mulnum_array_from_bin - int
  {
    my $binary = pack('l9', (0, 1, 2), (3, 4, 5), (6, 7, 8));
    my $sp_mulnum_array = $api->new_mulnum_array_from_bin("TestCase::Point_3i[]", $binary);
  }

  # new_mulnum_array_from_bin - long
  {
    my $binary = pack('q9', (0, 1, 2), (3, 4, 5), (6, 7, 8));
    my $sp_mulnum_array = $api->new_mulnum_array_from_bin("TestCase::Point_3l[]", $binary);
  }

  # new_mulnum_array_from_bin - float
  {
    my $binary = pack('f9', (0, 1, 2), (3, 4, 5), (6, 7, 8));
    my $sp_mulnum_array = $api->new_mulnum_array_from_bin("TestCase::Point_3f[]", $binary);
  }

  # new_mulnum_array_from_bin - double
  {
    my $binary = pack('d9', (0, 1, 2), (3, 4, 5), (6, 7, 8));
    my $sp_mulnum_array = $api->new_mulnum_array_from_bin("TestCase::Point_3d[]", $binary);
  }

=head2 get_exception

  my $exception = $api->get_exception();

Gets the exception of the SPVM runtime environment as L<SPVM::BlessedObject::String> object.

=head2 set_exception

Sets an exception.

The argument must be a Perl string, a L<SPVM::BlessedObject::String> object or C<undef>. Otherwise an exception will occur.

  $api->set_exception($api->new_string("abc"));
  $api->set_exception("abc");
  $api->set_exception(undef);

=head2 get_memory_blocks_count

  my $count = $api->get_memory_blocks_count();

Gets the count of memory blocks on the execution environment.

Examples:

  # First Memory Blocks Count
  my $start_memory_blocks_count = $api->get_memory_blocks_count();

  # Processing
  # ...

  # Last Memory Blocks Count
  my $end_memory_blocks_count = $api->get_memory_blocks_count();

  unless ($end_memory_blocks_count == $start_memory_blocks_count) {
    die"Memroy leak";
  }

=head2 call_method
  
  # Call an class method
  my $ret = $api->call_method($class_name, $method_name, @args);

  # Call an instance method
  my $ret = $api->call_method($invocant, $method_name, @args);

Calls an class method or an instance method with arguments and return the return value.

If the count of given arguments is less than the count of the arguments of the method, an exception will occur.

If the count of given arguments is more than the count of the arguments of the method, an exception will occur.

The arguments are converted by the rule of L</"Argument Conversion">.

The return value is converted by the rule of L</"Return Value Conversion">.

Examples:

  my $obj_int = $api->call_method("Int", "new", 1);
  $obj_int->set_value(5);
  my $value = $obj_int->value;

=head2 class

  my $class = $api->class('Int');

Creates a new L<SPVM::ExchangeAPI::Class> object.

Examples:

  $api->class('Int')->new(1);

=head1 Argument Conversion

The arguments given in the L</"call_method"> are converted to the values of SPVM in the following rules.

=head2 byte Argument

If the SPVM argument type is C<byte>, the following coversion is performed.

A Perl scalar is converted to a value of the SPVM C<byte> type using the L<SvIV|https://perldoc.perl.org/perlapi#SvIV> perlapi and a type cast to C<int8_t> in C<C Language>.

  (int8_t)SvIV(perl_scalar)

=head2 short Argument

If the SPVM argument type is C<short>, the following coversion is performed.

A Perl scalar is converted to a value of the SPVM C<short> type using the L<SvIV|https://perldoc.perl.org/perlapi#SvIV> perlapi and a type cast to C<int16_t> in C<C Language>.
  
  (int16_t)SvIV(perl_scalar)

=head2 int Argument

If the SPVM argument type is C<int>, the following coversion is performed.

A Perl scalar is converted to a value of the SPVM C<int> type using the L<SvIV|https://perldoc.perl.org/perlapi#SvIV> perlapi and a type cast to C<int32_t> in C<C Language>.

  (int32_t)SvIV(perl_scalar)

=head2 long Argument

If the SPVM argument type is C<long>, the following coversion is performed.

A Perl scalar is converted to a value of the SPVM C<long> type using the L<SvIV|https://perldoc.perl.org/perlapi#SvIV> perlapi and a type cast to C<int64_t> in C<C Language>.

  (int64_t)SvIV(perl_scalar)

=head2 float Argument

If the SPVM argument type is C<float>, the following coversion is performed.

A Perl scalar is converted to a value of the SPVM C<float> type using the L<SvNV|https://perldoc.perl.org/perlapi#SvNV> perlapi and a type cast to C<float> in C<C Language>.

  (float)SvNV(perl_scalar)

=head2 double Argument

If the SPVM argument type is C<double>, the following coversion is performed.

A Perl scalar is converted to a value of the SPVM C<double> type using the L<SvNV|https://perldoc.perl.org/perlapi#SvNV> perlapi and a type cast to C<double> in C<C Language>.

  (double)SvNV(perl_scalar)

=head2 string Argument

If the SPVM argument type is C<string>, the given Perl scalar is converted by the following rules.

If any of the following rules does not match, an exception will occur.

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

Perl can have SPVM string itself as L<SPVM::BlessedObject::String> object. This object is created by such as L</"new_string">, L</"new_string_from_bin">, or got as a return value of SPVM method.

If the given value is Perl C<undef>, it is converted to SPVM C<undef>

  # SPVM method definition
  class MyClass {
    static method foo : void ($value : string) { ... }
  }
  
  # Perl
  my $string = $api->new_string("あいう");
  SPVM::MyClass->foo($string);

=head2 Class Argument

No conversion occurs.

Perl can have SPVM class object itself as a object which inherits L<SPVM::BlessedObject::Class>. This object is created by a contructor such as SPVM::Int->new, SPVM::MyClassClass->new.

If the given value is Perl C<undef>, it is converted to SPVM C<undef>.

If class name is different, an exception will occur.

B<Example:>

  # SPVM method definition
  class MyClass {
    static method foo : void ($value : SPVM::Int) { ... }
  }
  
  # Perl
  my $value = SPVM::Int->new(5);
  SPVM::MyClass->foo($value);

=head2 Any Object Argument

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

=head2 Array Argument

Perl can have SPVM array itself as L<SPVM::BlessedObject::Array> object. This object is created by such as L</"new_byte_array">, L</"new_short_array">, L</"new_int_array">, L</"new_long_array">, L</"new_float_array">, L</"new_double_array">, or got as a return value of SPVM method.

B<Example:>

  # SPVM method definition
  class MyClass {
    static method foo : void ($values : int[]) { ... }
  }
  
  # Perl
  my $array = $api->new_int_array([1, 2, 3]);
  SPVM::MyClass->foo($array);

=head3 byte[] Argument

If the SPVM argument type is C<byte[]>, the Perl array reference is converted to SPVM array which type is C<byte[]>. Each element is converted to C<byte> value by L<the rule of Perl scalar to SPVM byte|"Perl Scalar to SPVM byte">. Perl C<undef> is coverted to SPVM C<undef>.

B<Example:>

  # SPVM method definition
  class MyClass {
    static method foo : void ($values : byte[]) { ... }
  }
  
  # Perl
  SPVM::MyClass->foo([1, 2, 3]);

=head3 short[] Argument

If the SPVM argument type is C<short[]>, the Perl array reference is converted to SPVM array which type is C<short[]>. Each element is converted to C<short> value by L<the rule of Perl Scalar to SPVM short|"Perl Scalar to SPVM short">. Perl C<undef> is coverted to SPVM C<undef>.

B<Example:>

  # SPVM method definition
  class MyClass {
    static method foo : void ($values : short[]) { ... }
  }
  
  # Perl
  SPVM::MyClass->foo([1, 2, 3]);

=head3 int[] Argument

If the SPVM argument type is C<int[]>, the Perl array reference is converted to SPVM array which type is C<int[]>. Each element is converted to C<int> value by L<the rule of Perl scalar to SPVM int|"Perl Scalar to SPVM int">. Perl C<undef> is coverted to SPVM C<undef>.

B<Example:>

  # SPVM method definition
  class MyClass {
    static method foo : void ($values : int[]) { ... }
  }
  
  # Perl
  SPVM::MyClass->foo([1, 2, 3]);

=head3 long[] Argument

If the SPVM argument type is C<long[]>, the Perl array reference is converted to SPVM array which type is C<long[]>. Each element is converted to C<long> value by L<the rule of Perl scalar to SPVM long|"Perl Scalar to SPVM long">. Perl C<undef> is coverted to SPVM C<undef>.

B<Example:>

  # SPVM method definition
  class MyClass {
    static method foo : void ($values : long[]) { ... }
  }
  
  # Perl
  SPVM::MyClass->foo([1, 2, 3]);

=head3 float[] Argument

If the SPVM argument type is C<float[]>, the Perl array reference is converted to SPVM array which type is C<float[]>. Each element is converted to C<float> value by L<the rule of Perl scalar to SPVM float|"Perl Scalar to SPVM float">. Perl C<undef> is coverted to SPVM C<undef>.

B<Example:>

  # SPVM method definition
  class MyClass {
    static method foo : void ($values : float[]) { ... }
  }
  
  # Perl
  SPVM::MyClass->foo([1.2, 2.3, 3.4]);

=head3 double[] Argument

If the SPVM argument type is C<double[]>, the Perl array reference is converted to SPVM array which type is C<double[]>. Each element is converted to C<double> value by L<the rule of Perl scalar to SPVM double|"Perl Scalar to SPVM double">. Perl C<undef> is coverted to SPVM C<undef>.

B<Example:>

  # SPVM method definition
  class MyClass {
    static method foo : void ($values : double[]) { ... }
  }
  
  # Perl
  SPVM::MyClass->foo([1.2, 2.3, 3.4]);

=head3 string[] Argument

If the SPVM argument type is C<string[]>, the Perl array reference is converted to SPVM array which type is C<string[]>. Each element is converted to C<string> value by L<the rule of Perl scalar to SPVM string|"Perl Scalar to SPVM string">. Perl C<undef> is coverted to SPVM C<undef>.

B<Example:>

  # SPVM method definition
  class MyClass {
    static method foo : void ($values : string[]) { ... }
  }
  
  # Perl
  SPVM::MyClass->foo(["あい", "うえ", "お"]);

=head3 Multi-Numeric Array Argument

If the SPVM argument type is an array of multi-numeric type, the given Perl array reference is converted to SPVM multi-numeric array which element type is multi-numeric type. Each element which is a hash reference is converted to multi-numeric type by L<the rule of Perl hash reference to SPVM multi-numeric type|"Perl hash reference to SPVM multi-numeric type">. Perl C<undef> is coverted to SPVM C<undef>.

B<Example:>

  # SPVM method definition
  class MyClass {
    static method foo : void ($values : Complex_2d[]) { ... }
  }
  
  # Perl
  SPVM::MyClass->foo([{re => 1.2, im => 2.3}, {re => 3.4, im => 4.5}]);

=head2 Multi-Numeric Argument

If the SPVM argument type is a multi-numeric type, the given argument is converted by the following rules.

=head3 Multi-Numeric byte

If the argument type is a multi-numeric byte type, the given argument is hash reference is converted to the value of SPVM multi-numeric byte type. If the given argument is different from a hash reference, an exception will occur. Each field is converted to C<byte> value by L<the rule of Perl scalar to SPVM byte|"Perl Scalar to SPVM byte">.

If a filed is missing, an exception will occur.

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

=head3 Multi-Numeric short Argument

If the argument type is a multi-numeric short type, the given argument is hash reference is converted to the value of SPVM multi-numeric short type. If the given argument is different from a hash reference, an exception will occur. Each field is converted to C<short> value by L<the rule of Perl scalar to SPVM short|"Perl Scalar to SPVM short">.

If a filed is missing, an exception will occur.

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

=head3 Multi-Numeric int Argument

If the argument type is a multi-numeric int type, the given argument is hash reference is converted to the value of SPVM multi-numeric int type. If the given argument is different from a hash reference, an exception will occur. Each field is converted to C<int> value by L<the rule of Perl scalar to SPVM int|"Perl Scalar to SPVM int">.

If a filed is missing, an exception will occur.

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

=head3 Multi-Numeric long Argument

If the argument type is a multi-numeric long type, the given argument is hash reference is converted to the value of SPVM multi-numeric long type. If the given argument is different from a hash reference, an exception will occur. Each field is converted to C<long> value by L<the rule of Perl scalar to SPVM long|"Perl Scalar to SPVM long">.

If a filed is missing, an exception will occur.

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

=head3 Multi-Numeric float Argument

If the argument type is a multi-numeric float type, the given argument is hash reference is converted to the value of SPVM multi-numeric float type. If the given argument is different from a hash reference, an exception will occur. Each field is converted to C<float> value by L<the rule of Perl scalar to SPVM float|"Perl Scalar to SPVM float">.

If a filed is missing, an exception will occur.

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

=head3 Multi-Numeric double Argument

If the argument type is a multi-numeric double type, the given argument is hash reference is converted to the value of SPVM multi-numeric double type. If the given argument is different from a hash reference, an exception will occur. Each field is converted to C<double> value by L<the rule of Perl scalar to SPVM double|"Perl Scalar to SPVM double">.

If a filed is missing, an exception will occur.

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

=head2 Numeric Reference Argument

If the SPVM argument type is numeric reference type, the given Perl reference is converted to SPVM numeric reference type in the following rules.

=head3 byte* Argument

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

=head3 short* Argument

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

=head3 int* Argument

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

=head3 long* Argument

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

=head3 float* Argument

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

=head3 double* Argument

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

=head2 Multi-Numeric Reference Argument

If the SPVM argument type is multi-numeric reference type, the given Perl reference is converted by the following rules.

=head3 Multi-Numeric byte Argument

If the SPVM argument type is multi-numeric byte reference type, the given Perl reference is converted to SPVM multi-numeric byte reference type.

The given reference must be a scalar reference of hash reference. Otherwise an exception will occur.

The each field of the hash of the given argument is converted to C<byte> value by L<the rule of Perl scalar to SPVM byte|"Perl Scalar to SPVM byte"> and the each filed of the return value is converted to Perl scalar by L<the rule of SPVM byte to Perl Scalar|"SPVM byte to Perl scalar">

If a field is missing, an exception will occur.

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

=head3 Multi-Numeric short Argument

If the SPVM argument type is multi-numeric short reference type, the given Perl reference is converted to SPVM multi-numeric short reference type.

The given reference must be a scalar reference of hash reference. Otherwise an exception will occur.

The each field of the hash of the given argument is converted to C<short> value by L<the rule of Perl scalar to SPVM short|"Perl Scalar to SPVM short"> and the each filed of the return value is converted to Perl scalar by L<the rule of SPVM short to Perl Scalar|"SPVM short to Perl scalar">

If a field is missing, an exception will occur.

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

=head3 Multi-Numeric int Argument

If the SPVM argument type is multi-numeric int reference type, the given Perl reference is converted to SPVM multi-numeric int reference type.

The given reference must be a scalar reference of hash reference. Otherwise an exception will occur.

The each field of the hash of the given argument is converted to C<int> value by L<the rule of Perl scalar to SPVM int|"Perl Scalar to SPVM int"> and the each filed of the return value is converted to Perl scalar by L<the rule of SPVM int to Perl Scalar|"SPVM int to Perl scalar">

If a field is missing, an exception will occur.

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

=head3 Multi-Numeric long Argument

If the SPVM argument type is multi-numeric long reference type, the given Perl reference is converted to SPVM multi-numeric long reference type.

The given reference must be a scalar reference of hash reference. Otherwise an exception will occur.

The each field of the hash of the given argument is converted to C<long> value by L<the rule of Perl scalar to SPVM long|"Perl Scalar to SPVM long"> and the each filed of the return value is converted to Perl scalar by L<the rule of SPVM long to Perl Scalar|"SPVM long to Perl scalar">

If a field is missing, an exception will occur.

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

=head3 Multi-Numeric float Argument

If the SPVM argument type is multi-numeric float reference type, the given Perl reference is converted to SPVM multi-numeric float reference type.

The given reference must be a scalar reference of hash reference. Otherwise an exception will occur.

The each field of the hash of the given argument is converted to C<float> value by L<the rule of Perl scalar to SPVM float|"Perl Scalar to SPVM float"> and the each filed of the return value is converted to Perl scalar by L<the rule of SPVM float to Perl Scalar|"SPVM float to Perl scalar">

If a field is missing, an exception will occur.

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

=head3 Multi-Numeric double Argument

If the SPVM argument type is multi-numeric double reference type, the given Perl reference is converted to SPVM multi-numeric double reference type.

The given reference must be a scalar reference of hash reference. Otherwise an exception will occur.

The each field of the hash of the given argument is converted to C<double> value by L<the rule of Perl scalar to SPVM double|"Perl Scalar to SPVM double"> and the each filed of the return value is converted to Perl scalar by L<the rule of SPVM double to Perl Scalar|"SPVM double to Perl scalar">

If a field is missing, an exception will occur.

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

A SPVM return value is converted to a Perl value by the following rules.

=head2 void Return Value

If the SPVM return type is the void type, the following conversion is performed.

SPVM void return value is converted to Perl C<undef>.

=head2 byte Return Value

If the SPVM return type is the long type, the following conversion is performed.

The SPVM byte value is converted to Perl scalar using the L<newSViv|https://perldoc.perl.org/perlapi#newSViv> perlapi.

=head2 short Return Value

If the SPVM return type is the long type, the following conversion is performed.

The SPVM short value is converted to Perl scalar using the L<newSViv|https://perldoc.perl.org/perlapi#newSViv> perlapi.

=head2 int Return Value

If the SPVM return type is the int type, the following conversion is performed.

The SPVM float value is converted to Perl scalar using the L<newSViv|https://perldoc.perl.org/perlapi#newSViv> perlapi.

=head2 long Return Value

If the SPVM return type is the long type, the following conversion is performed.

The SPVM float value is converted to Perl scalar using the L<newSViv|https://perldoc.perl.org/perlapi#newSViv> perlapi.

=head2 float Return Value

If the SPVM return type is the float type, the following conversion is performed.

The SPVM float value is converted to Perl scalar using the L<newSVnv|https://perldoc.perl.org/perlapi#newSVnv> perlapi.

=head2 double Return Value

If the SPVM return type is the double type, the following conversion is performed.

The SPVM double value is converted to Perl scalar using the L<newSVnv|https://perldoc.perl.org/perlapi#newSVnv> perlapi.

=head2 string Return Value

If the SPVM return type is the string type, the following conversion is performed.

If SPVM return value is C<undef>, it is converted to Perl C<undef>.

Otherwise a SPVM string is converted to a Perl L<SPVM::BlessedObject::String> object.

=head2 Multi-Numeric Return Value

If the SPVM return type is an multi-numeric type, the following conversion is performed.

The SPVM multi-numeric value is converted to Perl hash reference that has the field names of the multi-numeric type as the keys.

Each numeric field is converted by the rules of L</"byte Return Value">, L</"short Return Value">, L</"int Return Value">, L</"long Return Value">, L</"float Return Value">, L</"double Return Value">.

=head2 Array Return Value

If the SPVM return type is an array type, the following conversion is performed.

If SPVM return value is C<undef>, it is converted to Perl C<undef>.

Otherwise a SPVM array is converted to a Perl L<SPVM::BlessedObject::Array> object. 

=head2 Class Return Value

If the SPVM return type is a class type, the following conversion is performed.

If SPVM return value is C<undef>, it is converted to Perl C<undef>.

Otherwise a SPVM object is converted to a Perl L<SPVM::BlessedObject::Class> object.
