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

sub new_options {
  my ($self, $options) = @_;
  
  unless (ref $options eq 'HASH') {
    confess "The options must be a hash reference";
  }
  
  my $array_ref = [];
  for my $name (keys %$options) {
    my $obj_name = $self->new_string($name);
    my $value = $options->{$name};
    push @$array_ref, $obj_name, $value;
  }
  
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
sub dump { my $ret; eval { $ret =  &xs_dump(@_) }; if ($@) { confess $@ } $ret}

1;

=encoding utf8

=head1 Name

SPVM::ExchangeAPI - SPVM Exchange API

=head1 Description

C<SPVM::ExchangeAPI> is APIs to convert Perl data structures to/from SPVM data structures, and to call SPVM methods from Perl.

=head1 Usage

  my $api = SPVM::ExchangeAPI->new(env => $env, stack => $stack);
  my $int_array = $api->new_int_array([1, 2, 3]);

Getting an global C<ExchangeAPI> object:

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

=item C<env> : L<SPVM::Bulder::Env> | L<SPVM::BlessedObject::Class>

An execution environment.

=item C<stack> : L<SPVM::Bulder::Stack> | L<SPVM::BlessedObject::Class>

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

  my $sp_string = $api->new_string("あいう");

Converts a Perl string to a L<SPVM::BlessedObject::String> object. Any decoding is not performed.

If the argument is C<undef>, returns C<undef>.

=head2 new_string_from_bin

  my $pl_binary = pack('c3', 97, 98, 99);
  my $sp_string = $api->new_string_from_bin($pl_binary);

Converts a Perl binary to a L<SPVM::BlessedObject::String>.

The Perl binary is interpreted as 8-bit signed integers. The length of the string is calcurated from the Perl binary.

If the argument is C<undef>, returns C<undef>.

=head2 new_options

  my $byte_array = $api->new_options(
    [SPVM::Byte->new(1), SPVM::Byte>new(2), SPVM::Byte->new(3)]
  );

The alias for the following code using the L</"new_object_array"> method.

  my $sp_array = $api->new_object_array('object[]', $pl_array);

=head2 new_options

  my $options = $api->new_options({
    x => SPVM::Int->new(1),
    y => SPVM::Int->new(2)
  });

Creates options that type is C<object[]>.

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

Converts a Perl array reference to a L<SPVM::BlessedObject::Array> object that has the value of a multi-numeric array type and returns it.

  my $pl_values = [
    {x => 0, y => 1, z => 2},
    {x => 3, y => 4, z => 5},
    {x => 6, y => 7, z => 8},
  ];
  my $sp_mulnum_array = $api->new_mulnum_array("TestCase::Point_3i[]", $pl_values);

The first argument is a SPVM array type name. If the type doesn't exist, an exception will occur.

The second argument is a Perl array of a hash references. Each hash reference must be contain all fields of the multi-numeric typee. Otherwise an exception will occur.

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

  my $ret = $api->get_exception();

Returns the exception in the current thread stack.

Return Type:

L<SPVM::BlessedObject::String>|undef

=head2 set_exception

  $api->set_exception($message);

Sets an exception in the current thread stack.

Argument Types:

$message : L<SPVM::BlessedObject::String>|undef

Exceptions:

The $message must be a SPVM::BlessedObject::String object.

Examples:

  $api->set_exception($api->new_string("abc"));
  $api->set_exception(undef);

=head2 get_memory_blocks_count

  my $ret = $api->get_memory_blocks_count();

Returns the count of memory blocks on the execution environment.

Return Type:

number

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
  
  my $ret = $api->call_method($invocant, $method_name, @args);

Calls a class method or an instance method. If the $invocant is a string, a class method is called. If the $invocant is a L<SPVM::BlessedObject::Class>, an instance method is called.

The @args are converted by the rule of L</"Argument Conversion">.

The $method_name allows static method name such as C<Foo::bar>.

The return value is converted by the rule of L</"Return Value Conversion">.

Argument Types:

$invocant : string|L<SPVM::BlessedObject>

$method_name : string

@args : the list of the L<SPVM::BlessedObject> object of the argument types of the method (See also L</"Argument Conversion">)

Return Type:

L<SPVM::BlessedObject> of the return type of the method (See also L</"Return Value Conversion">)

Exceptions:

The exception message thrown by SPVM.

The $invocant must be a SPVM::BlessedObject::Class object

The static method call must be valid.

The \"%s\" method in the \"%s\" class is not found.

Too few arguments are passed to the \"%s\" method in the \"%s\" class.

Too many arguments are passed to the \"%s\" method in the \"%s\" class.

The %dth argument of the \"%s\" method in the \"%s\" class must be an interger reference

The %dth argument of the \"%s\" method in the \"%s\" class must be a floating-point reference

The %dth argument of the \"%s\" method in the \"%s\" class must be a scalar reference of a hash reference

The %dth argument of the \"%s\" field in the \"%s\" class is not found

The %dth argument of the \"%s\" method in the \"%s\" class must be a number

The %dth argument of the \"%s\" method in the \"%s\" class must be a SPVM::BlessedObject::String object

The %dth argument of the \"%s\" method in the \"%s\" class must be a SPVM::BlessedObject object

The %dth argument of the \"%s\" method in the \"%s\" class must be assinged to the argument type

The %dth argument of the \"%s\" method in the \"%s\" class must be a SPVM::BlessedObject::Class object

The \"%s\" field in the %dth argument must be defined. The field is defined in the \"%s\" class

The %dth argument of the \"%s\" method in the \"%s\" class must be a hash reference

The object must be assigned to the %s type of the %dth argument of the \"%s\" method in the \"%s\" class

The %dth argument of the \"%s\" method in the \"%s\" class must be a SPVM::BlessedObject::Array object

Examples:

  # Class method call
  my $obj_int = $api->call_method("Int", "new", 1);
  
  # Instance method call
  $api->call_method($obj_int, "set_value", 5);
  my $value = $api->call_method($obj_int, "value");
  
  # Call static instance method
  $api->call_method($object, "Foo::value");
  
=head2 class

  my $ret = $api->class($class_name);

Creates a new L<SPVM::ExchangeAPI::Class> object with the $class_name and returns it.

Examples:
  
  my $class = $api->class('Int');
  my $spvm_object = $class->new(1);

=head2 dump

  my $ret = $api->dump($object);

Generates the string by dumping a SPVM object using the L<dump|SPVM::Document::Language/"dump Operator"> operator and returns it.

Argument Types:

$object : L<SPVM::BlessedObject>|undef

Return Type:

L<SPVM::BlessedObject::String>

Exceptions:

The $object must be a SPVM::BlessedObject object.

=head1 Argument Conversion

The arguments in the L</"call_method"> are converted to the values of SPVM in the following rules.

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

If the SPVM argument type is C<string>, the Perl scalar is converted by the following rules.

If any of the following rules does not match, an exception will occur.

If the SPVM argument type is C<string>, the Perl non-ref scalar is converted to L<SPVM::BlessedObject::String> object.

The non-ref scalar value is assumed to a Perl decoded string, and is converted to UTF-8 bytes.

If the non-ref scalar value is Perl C<undef>, it is converted to Perl C<undef>.

And the following L</"Perl SPVM::BlessedObject::String to SPVM String"> conversion is contined.

Examples:

  # Converts a Perl scalar to string type
  SPVM::MyClass->foo("あいう");

Perl can have SPVM string itself as L<SPVM::BlessedObject::String> object. This object is created by such as L</"new_string">, L</"new_string_from_bin">, or got as a return value of SPVM method.

If the value is Perl C<undef>, it is converted to SPVM C<undef>

  # Converts a Perl scalar to string type
  my $string = $api->new_string("あいう");
  SPVM::MyClass->foo($string);

=head2 Class Argument

No conversion occurs.

Perl can have SPVM class object itself as a object which inherits L<SPVM::BlessedObject::Class>. This object is created by a contructor such as SPVM::Int->new, SPVM::MyClassClass->new.

If the value is Perl C<undef>, it is converted to SPVM C<undef>.

If class name is different, an exception will occur.

Examples:

  # Converts a Perl scalar to class type
  my $value = SPVM::Int->new(5);
  SPVM::MyClass->foo($value);

=head2 Any Object Argument

Perl can have SPVM object itself as a L<SPVM::BlessedObject> object. This object is created by a contructor or functions of exchange API such as SPVM::Int->new, SPVM::MyClassClass->new, $api->new_int_array.

If the value is Perl C<undef>, it is converted to SPVM C<undef>.

Examples:

  # Converts a Perl scalar to any object type
  my $value = SPVM::Int->new(5);
  SPVM::MyClass->foo($value);

=head2 Array Argument

=head3 byte[] Argument

If the SPVM argument type is C<byte[]>, a Perl value is converted by the following rule.

Perl C<undef> is coverted to SPVM C<undef>.

A Perl array reference is converted to a L<SPVM::BlessedObject::Array> object of the C<byte[]> type.

Each element is converted to a value of the C<byte> type by the conversion of L</"byte Argument">. 

Examples:

  # Converts a Perl array reference to byte[] type
  SPVM::MyClass->foo([1, 2, 3]);

=head3 short[] Argument

If the SPVM argument type is C<short[]>, a Perl value is converted by the following rule.

Perl C<undef> is coverted to SPVM C<undef>.

A Perl array reference is converted to a L<SPVM::BlessedObject::Array> object of the C<short[]> type.

Each element is converted to a value of the C<short> type by the conversion of L</"short Argument">. 

Examples:

  # Converts a Perl array reference to short[] type
  SPVM::MyClass->foo([1, 2, 3]);

=head3 int[] Argument

If the SPVM argument type is C<int[]>, a Perl value is converted by the following rule.

Perl C<undef> is coverted to SPVM C<undef>.

A Perl array reference is converted to a L<SPVM::BlessedObject::Array> object of the C<int[]> type.

Each element is converted to a value of the C<int> type by the conversion of L</"int Argument">. Perl C<undef> is coverted to SPVM C<undef>.

Examples:

  # Converts a Perl array reference to int[] type
  SPVM::MyClass->foo([1, 2, 3]);

=head3 long[] Argument

If the SPVM argument type is C<int[]>, a Perl value is converted by the following rule.

Perl C<undef> is coverted to SPVM C<undef>.

A Perl array reference is converted to a L<SPVM::BlessedObject::Array> object of the C<long[]> type.

Each element is converted to a value of the C<long> type by the conversion of L</"long Argument">. Perl C<undef> is coverted to SPVM C<undef>.

Examples:

  # Converts a Perl array reference to long[] type
  SPVM::MyClass->foo([1, 2, 3]);

=head3 float[] Argument

If the SPVM argument type is C<float[]>, a Perl value is converted by the following rule.

Perl C<undef> is coverted to SPVM C<undef>.

A Perl array reference is converted to a L<SPVM::BlessedObject::Array> object of the C<float[]> type.

Each element is converted to a value of the C<float> type by the conversion of L</"float Argument">. Perl C<undef> is coverted to SPVM C<undef>.

Examples:

  # Converts a Perl array reference to float[] type
  SPVM::MyClass->foo([1.2, 2.3, 3.4]);

=head3 double[] Argument

If the SPVM argument type is C<double[]>, a Perl value is converted by the following rule.

Perl C<undef> is coverted to SPVM C<undef>.

A Perl array reference is converted to a L<SPVM::BlessedObject::Array> object of the C<double[]> type.

Each element is converted to a value of the C<double> type by the conversion of L</"double Argument">. Perl C<undef> is coverted to SPVM C<undef>.

Examples:

  # Converts a Perl array reference to double[] type
  SPVM::MyClass->foo([1.2, 2.3, 3.4]);

=head3 string[] Argument

If the SPVM argument type is C<string[]>, a Perl value is converted by the following rule.

Perl C<undef> is coverted to SPVM C<undef>.

A Perl array reference is converted to a L<SPVM::BlessedObject::Array> object of the C<string[]> type.

Each element is converted to C<string> value by the conversion of L</"string Argument">. Perl C<undef> is coverted to SPVM C<undef>.

Examples:

  # Converts a Perl array reference to string[] type
  SPVM::MyClass->foo(["あい", "うえ", "お"]);

=head3 Multi-Numeric Array Argument

If the SPVM argument type is a multi-numeric Array, a Perl value is converted by the following rule.

Perl C<undef> is coverted to SPVM C<undef>.

A Perl array reference is converted to a L<SPVM::BlessedObject::Array> object of of a multi-numeric type.

Each element which is a hash reference is converted to multi-numeric type by the conversion of L</"Multi-Numeric Argument">. Perl C<undef> is coverted to SPVM C<undef>.

Examples:

  # Converts a Perl array reference of a hash reference to Complex_2d[] type
  SPVM::MyClass->foo([{re => 1.2, im => 2.3}, {re => 3.4, im => 4.5}]);

=head3 Other Array Argument

If the SPVM argument type is a other array type of the above, a Perl value is converted by the following rule.

Perl C<undef> is coverted to SPVM C<undef>.

A Perl array reference is converted to a L<SPVM::BlessedObject::Array> of the corresponding array type.

=head2 Multi-Numeric Argument

If the SPVM argument type is a multi-numeric type, a Perl value is converted by the following rule.

=head3 Multi-Numeric byte

If the argument type is a multi-numeric byte type, the argument is hash reference is converted to a value of SPVM multi-numeric byte type. If the argument is different from a hash reference, an exception will occur. Each field is converted to a value of the C<byte> type by the conversion of L</"byte Argument">.

If a field is not specified, an exception will occur.

Examples:

  # Converts a Perl hash reference to MyClassPoint_2b type
  SPVM::MyClass->foo({x => 1, y => 2});

=head3 Multi-Numeric short Argument

If the argument type is a multi-numeric short type, the argument is hash reference is converted to a value of SPVM multi-numeric short type. If the argument is different from a hash reference, an exception will occur. Each field is converted to a value of the C<short> type by the conversion of L</"short Argument">.

If a field is not specified, an exception will occur.

Examples:

  # Converts a Perl hash reference to MyClassPoint_2s type
  SPVM::MyClass->foo({x => 1, y => 2});

=head3 Multi-Numeric int Argument

If the argument type is a multi-numeric int type, the argument is hash reference is converted to a value of SPVM multi-numeric int type. If the argument is different from a hash reference, an exception will occur. Each field is converted to a value of the C<int> type by the conversion of L</"int Argument">.

If a field is not specified, an exception will occur.

Examples:

  # Converts a Perl hash reference to MyClassPoint_2i type
  SPVM::MyClass->foo({x => 1, y => 2});

=head3 Multi-Numeric long Argument

If the argument type is a multi-numeric long type, the argument is hash reference is converted to a value of SPVM multi-numeric long type. If the argument is different from a hash reference, an exception will occur. Each field is converted to a value of the C<long> type by the conversion of L</"long Argument">.

If a field is not specified, an exception will occur.

Examples:

  # Converts a Perl hash reference to MyClassPoint_2l type
  SPVM::MyClass->foo({x => 1, y => 2});

=head3 Multi-Numeric float Argument

If the argument type is a multi-numeric float type, the argument is hash reference is converted to a value of SPVM multi-numeric float type. If the argument is different from a hash reference, an exception will occur. Each field is converted to a value of the C<float> type by the conversion of L</"float Argument">.

If a field is not specified, an exception will occur.

Examples:

  # Converts a Perl hash reference to MyClassPoint_2f type
  SPVM::MyClass->foo({x => 1.2, y => 2.3});

=head3 Multi-Numeric double Argument

If the argument type is a multi-numeric double type, the argument is hash reference is converted to a value of SPVM multi-numeric double type. If the argument is different from a hash reference, an exception will occur. Each field is converted to a value of the C<double> type by the conversion of L</"double Argument">.

If a field is not specified, an exception will occur.

Examples:

  # Converts a Perl hash reference to MyClassPoint_2d type
  SPVM::MyClass->foo({x => 1.2, y => 2.3});

=head2 Numeric Reference Argument

=head3 byte Reference Argument

If the SPVM argument type is the C<byte> reference type, a Perl value is converted by the following rule.

A Perl reference is converted to a SPVM value of the byte reference type.

The value must be a scalar reference of a non-reference scalar. Otherwise an exception will occur.

The value is converted to a SPVM value of the C<byte> type by the conversion of L</"byte Argument">.

The value set by SPVM is converted to a Perl scalar by the conversion of L</"byte Return Value">

Examples:

  # Converts a Perl scalar reference to byte* type
  my $value = 23;
  SPVM::MyClass->foo(\$value);

=head3 short Reference Argument

If the SPVM argument type is the C<short> reference type, a Perl value is converted by the following rule.

A Perl reference is converted to a SPVM value of the short reference type.

The value must be a scalar reference of a non-reference scalar. Otherwise an exception will occur.

The value is converted to a SPVM value of the C<short> type by the conversion of L</"short Argument">.

The value set by SPVM is converted to a Perl scalar by the conversion of L</"short Return Value">

Examples:

  # Converts a Perl scalar reference to short* type
  my $value = 23;
  SPVM::MyClass->foo(\$value);

=head3 int Reference Argument

If the SPVM argument type is the C<int> reference type, a Perl value is converted by the following rule.

A Perl reference is converted to a SPVM value of the int reference type.

The value must be a scalar reference of a non-reference scalar. Otherwise an exception will occur.

The value is converted to a SPVM value of the C<int> type by the conversion of L</"int Argument">.

The value set by SPVM is converted to a Perl scalar by the conversion of L</"int Return Value">

Examples:

  # Converts a Perl scalar reference to int* type
  my $value = 23;
  SPVM::MyClass->foo(\$value);

=head3 long Reference Argument

If the SPVM argument type is the C<long> reference type, a Perl value is converted by the following rule.

A Perl reference is converted to a SPVM value of the long reference type.

The value must be a scalar reference of a non-reference scalar. Otherwise an exception will occur.

The value is converted to a SPVM value of the C<long> type by the conversion of L</"long Argument">.

The value set by SPVM is converted to a Perl scalar by the conversion of L</"long Return Value">

Examples:

  # Converts a Perl scalar reference to long* type
  my $value = 23;
  SPVM::MyClass->foo(\$value);

=head3 float Reference Argument

If the SPVM argument type is the C<float> reference type, a Perl value is converted by the following rule.

A Perl reference is converted to a SPVM value of the float reference type.

The value must be a scalar reference of a non-reference scalar. Otherwise an exception will occur.

The value is converted to a SPVM value of the C<float> type by the conversion of L</"float Argument">.

The value set by SPVM is converted to a Perl scalar by the conversion of L</"float Return Value">

Examples:

  # Converts a Perl scalar reference to float* type
  my $value = 23.5;
  SPVM::MyClass->foo(\$value);

=head3 double Reference Argument

If the SPVM argument type is the C<double> reference type, a Perl value is converted by the following rule.

A Perl reference is converted to a SPVM value of the double reference type.

The value must be a scalar reference of a non-reference scalar. Otherwise an exception will occur.

The value is converted to a SPVM value of the C<double> type by the conversion of L</"double Argument">.

The value set by SPVM is converted to a Perl scalar by the conversion of L</"double Return Value">

Examples:

  # Converts a Perl scalar reference to double* type
  my $value = 23.5;
  SPVM::MyClass->foo(\$value);

=head2 Multi-Numeric Reference Argument

=head3 Multi-Numeric byte Reference Argument

If the SPVM argument type is multi-numeric C<byte> reference type, a Perl value is converted by the following rule.

A Perl reference is converted to a SPVM multi-numeric C<byte> reference type.

The reference must be a scalar reference of a hash reference. Otherwise an exception will occur.

Each value of the hash is converted to a value of the C<byte> type by the conversion of L</"byte Argument">.

Each hash value set by SPVM is converted to a Perl number by the conversion of L</"byte Return Value">.

If a field is not specified, an exception will occur.

Examples:

  # Converts a Perl scalar reference of a hash reference to MyClassPoint_2b* type
  my $value = {x => 1, y => 2};
  SPVM::MyClass->foo(\$value);

=head3 Multi-Numeric short Reference Argument

If the SPVM argument type is multi-numeric C<short> reference type, a Perl value is converted by the following rule.

A Perl reference is converted to a SPVM multi-numeric C<short> reference type.

The reference must be a scalar reference of a hash reference. Otherwise an exception will occur.

Each value of the hash is converted to a value of the C<short> type by the conversion of L</"short Argument">.

Each hash value set by SPVM is converted to a Perl number by the conversion of L</"short Return Value">.

If a field is not specified, an exception will occur.

Examples:

  # Converts a Perl scalar reference of a hash reference to MyClassPoint_2s* type
  my $value = {x => 1, y => 2};
  SPVM::MyClass->foo(\$value);

=head3 Multi-Numeric int Reference Argument

If the SPVM argument type is multi-numeric C<int> reference type, a Perl value is converted by the following rule.

A Perl reference is converted to a SPVM multi-numeric C<int> reference type.

The reference must be a scalar reference of a hash reference. Otherwise an exception will occur.

Each value of the hash is converted to a value of the C<int> type by the conversion of L</"int Argument">.

Each hash value set by SPVM is converted to a Perl number by the conversion of L</"int Return Value">.

If a field is not specified, an exception will occur.

Examples:

  # Converts a Perl scalar reference of a hash reference to SPVM MyClassPoint_2i* type
  my $value = {x => 1, y => 2};
  SPVM::MyClass->foo(\$value);

=head3 Multi-Numeric long Reference Argument

If the SPVM argument type is multi-numeric C<long> reference type, a Perl value is converted by the following rule.

A Perl reference is converted to a SPVM multi-numeric C<long> reference type.

The reference must be a scalar reference of a hash reference. Otherwise an exception will occur.

Each value of the hash is converted to a value of the C<long> type by the conversion of L</"long Argument">.

Each hash value set by SPVM is converted to a Perl number by the conversion of L</"long Return Value">.

If a field is not specified, an exception will occur.

Examples:

  # Converts a Perl scalar reference of a hash reference to SPVM MyClassPoint_2l* type
  my $value = {x => 1, y => 2};
  SPVM::MyClass->foo(\$value);

=head3 Multi-Numeric float Reference Argument

If the SPVM argument type is multi-numeric C<float> reference type, a Perl value is converted by the following rule.

A Perl reference is converted to a SPVM multi-numeric C<float> reference type.

The reference must be a scalar reference of a hash reference. Otherwise an exception will occur.

Each value of the hash is converted to a value of the C<float> type by the conversion of L</"float Argument">.

Each hash value set by SPVM is converted to a Perl number by the conversion of L</"float Return Value">.

If a field is not specified, an exception will occur.

Examples:

  # Converts a Perl scalar reference of a hash reference to SPVM MyClassPoint_2f* type
  my $value = {x => 1,2, y => 2.3};
  SPVM::MyClass->foo(\$value);

=head3 Multi-Numeric double Reference Argument

If the SPVM argument type is multi-numeric C<double> reference type, a Perl value is converted by the following rule.

A Perl reference is converted to a SPVM multi-numeric C<double> reference type.

The reference must be a scalar reference of a hash reference. Otherwise an exception will occur.

Each value of the hash is converted to a value of the C<double> type by the conversion of L</"double Argument">.

Each hash value set by SPVM is converted to a Perl number by the conversion of L</"double Return Value">.

If a field is not specified, an exception will occur.

Examples:

  # Converts a Perl scalar reference of a hash reference to SPVM MyClassPoint_2d* type
  my $value = {x => 1.2, y => 2.3};
  SPVM::MyClass->foo(\$value);

=head1 Return Value Conversion

A SPVM return value is converted to a Perl value by the following rules.

=head2 void Return Value

If the SPVM return type is the void type, the following conversion is performed.

SPVM void return value is converted to Perl C<undef>.

=head2 byte Return Value

If the SPVM return type is the long type, the following conversion is performed.

The SPVM byte value is converted to a Perl scalar using the L<newSViv|https://perldoc.perl.org/perlapi#newSViv> perlapi.

=head2 short Return Value

If the SPVM return type is the long type, the following conversion is performed.

The SPVM short value is converted to a Perl scalar using the L<newSViv|https://perldoc.perl.org/perlapi#newSViv> perlapi.

=head2 int Return Value

If the SPVM return type is the int type, the following conversion is performed.

The SPVM float value is converted to a Perl scalar using the L<newSViv|https://perldoc.perl.org/perlapi#newSViv> perlapi.

=head2 long Return Value

If the SPVM return type is the long type, the following conversion is performed.

The SPVM float value is converted to a Perl scalar using the L<newSViv|https://perldoc.perl.org/perlapi#newSViv> perlapi.

=head2 float Return Value

If the SPVM return type is the float type, the following conversion is performed.

The SPVM float value is converted to a Perl scalar using the L<newSVnv|https://perldoc.perl.org/perlapi#newSVnv> perlapi.

=head2 double Return Value

If the SPVM return type is the double type, the following conversion is performed.

The SPVM double value is converted to a Perl scalar using the L<newSVnv|https://perldoc.perl.org/perlapi#newSVnv> perlapi.

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
