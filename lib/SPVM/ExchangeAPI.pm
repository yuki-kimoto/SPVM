package SPVM::ExchangeAPI;

use strict;
use warnings;

use SPVM::ExchangeAPI::Class;
use SPVM::ExchangeAPI::Error;
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

sub new_any_object_array {
  my ($self, $array_ref) = @_;
  
  my $type_name = 'object[]';
  
  my $array = $self->new_object_array($type_name, $array_ref);
  
  return $array;
}

sub new_options {
  my ($self, $options) = @_;
  
  unless (ref $options eq 'HASH') {
    confess "The \$options must be a hash reference";
  }
  
  my $array_ref = [];
  for my $name (keys %$options) {
    my $obj_name = $self->new_string($name);
    my $value = $options->{$name};
    if (defined $value && !$value->isa('SPVM::BlessedObject')) {
      confess "The value of the \$options must be a SPVM::BlessedObject object";
    }
    push @$array_ref, $obj_name, $value;
  }
  
  my $array = $self->new_any_object_array($array_ref);
  
  return $array;
}

sub new_object_array {
  my ($self, $type_name, $array) = @_;
  
  my $basic_type_name;
  my $type_dimension = 0;
  if ($type_name =~ /^([a-zA-Z_0-9:]+)((\[\])+)$/) {
    $basic_type_name = $1;
    my $type_dimension_part = $2;
    
    while ($type_dimension_part =~ /\[/g) {
      $type_dimension++;
    }
  }
  
  unless (defined $basic_type_name) {
    confess "The bacic type of the type \$type_name is not found";
  }
  
  unless ($type_dimension >= 1) {
    confess "The dimension of the type \$type_name must be 1";
  }
  
  my $ret;
  eval { $ret = $self->_xs_new_object_array($basic_type_name, $array) };
  if ($@) { confess $@ }
  
  return $ret;
}

sub new_muldim_array {
  my ($self, $type_name, $array) = @_;
  
  my $basic_type_name;
  my $type_dimension = 0;
  if ($type_name =~ /^([a-zA-Z_0-9:]+)((\[\])+)$/) {
    $basic_type_name = $1;
    my $type_dimension_part = $2;
    
    while ($type_dimension_part =~ /\[/g) {
      $type_dimension++;
    }
  }
  
  unless (defined $basic_type_name) {
    confess "The bacic type of the type \$type_name is not found";
  }
  
  unless ($type_dimension >= 2 && $type_dimension <= 255) {
    confess "The dimension of the type \$type_name must be greater than or equal to 1 and less than or equal to 255";
  }
  
  unless (defined $array) {
    return undef;
  }
  
  unless (ref $array eq 'ARRAY') {
    confess "The $array must be an array reference";
  }
  
  my $ret;
  eval { $ret = $self->_xs_new_muldim_array($basic_type_name, $type_dimension, $array) };
  if ($@) { confess $@ }
  
  return $ret;
}

sub new_mulnum_array {
  my ($self, $type_name, $array) = @_;
  
  my $basic_type_name;
  my $type_dimension = 0;
  if ($type_name =~ /^([a-zA-Z_0-9:]+)((\[\])+)$/) {
    $basic_type_name = $1;
    my $type_dimension_part = $2;
    
    while ($type_dimension_part =~ /\[/g) {
      $type_dimension++;
    }
  }
  
  unless (defined $basic_type_name) {
    confess "The bacic type of the type \$type_name is not found";
  }
  
  unless ($type_dimension == 1) {
    confess "The dimension of the type \$type_name must be 1";
  }
  
  unless (defined $array) {
    return undef;
  }
  
  unless (ref $array eq 'ARRAY') {
    confess "The \$array must be an array reference";
  }
  
  my $ret;
  eval { $ret = $self->_xs_new_mulnum_array($basic_type_name, $array) };
  if ($@) { confess $@ }
  
  return $ret;
}

sub new_mulnum_array_from_bin {
  my ($self, $type_name, $binary) = @_;
  
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
    confess "The dimension of the type \$type_name must be 1";
  }
  unless (defined $basic_type_name) {
    confess "The bacic type of the type \$type_name is not found";
  }

  unless (defined $binary) {
    return undef;
  }
  
  my $ret;
  eval { $ret = $self->_xs_new_mulnum_array_from_bin($basic_type_name, $binary) };
  if ($@) { confess $@ }
  
  return $ret;
}

sub class {
  my ($self, $class_name) = @_;
  
  my $class = SPVM::ExchangeAPI::Class->__new(__class_name => $class_name, __api => $self);
  
  return $class;
}

sub new_error {
  my ($self) = @_;
  
  my $error = SPVM::ExchangeAPI::Error->new(code => 0);
  
  return $error;
}

# other functions is implemented in SPVM.xs

sub new_string { my $ret; eval { $ret =  &_xs_new_string(@_) }; if ($@) { confess $@ } $ret}
sub new_address_object { my $ret; eval { $ret =  &_xs_new_address_object(@_) }; if ($@) { confess $@ } $ret}
sub new_byte_array { my $ret; eval { $ret =  &_xs_new_byte_array(@_) }; if ($@) { confess $@ } $ret}
sub new_byte_array_unsigned { my $ret; eval { $ret =  &_xs_new_byte_array_unsigned(@_) }; if ($@) { confess $@ } $ret}
sub new_byte_array_len { my $ret; eval { $ret =  &_xs_new_byte_array_len(@_) }; if ($@) { confess $@ } $ret}
sub new_byte_array_from_bin { my $ret; eval { $ret =  &_xs_new_byte_array_from_bin(@_) }; if ($@) { confess $@ } $ret}
sub new_short_array { my $ret; eval { $ret =  &_xs_new_short_array(@_) }; if ($@) { confess $@ } $ret}
sub new_short_array_unsigned { my $ret; eval { $ret =  &_xs_new_short_array_unsigned(@_) }; if ($@) { confess $@ } $ret}
sub new_short_array_len { my $ret; eval { $ret =  &_xs_new_short_array_len(@_) }; if ($@) { confess $@ } $ret}
sub new_short_array_from_bin { my $ret; eval { $ret =  &_xs_new_short_array_from_bin(@_) }; if ($@) { confess $@ } $ret}
sub new_int_array { my $ret; eval { $ret =  &_xs_new_int_array(@_) }; if ($@) { confess $@ } $ret}
sub new_int_array_unsigned { my $ret; eval { $ret =  &_xs_new_int_array_unsigned(@_) }; if ($@) { confess $@ } $ret}
sub new_int_array_len { my $ret; eval { $ret =  &_xs_new_int_array_len(@_) }; if ($@) { confess $@ } $ret}
sub new_int_array_from_bin { my $ret; eval { $ret =  &_xs_new_int_array_from_bin(@_) }; if ($@) { confess $@ } $ret}
sub new_long_array { my $ret; eval { $ret =  &_xs_new_long_array(@_) }; if ($@) { confess $@ } $ret}
sub new_long_array_unsigned { my $ret; eval { $ret =  &_xs_new_long_array_unsigned(@_) }; if ($@) { confess $@ } $ret}
sub new_long_array_len { my $ret; eval { $ret =  &_xs_new_long_array_len(@_) }; if ($@) { confess $@ } $ret}
sub new_long_array_from_bin { my $ret; eval { $ret =  &_xs_new_long_array_from_bin(@_) }; if ($@) { confess $@ } $ret}
sub new_double_array { my $ret; eval { $ret =  &_xs_new_double_array(@_) }; if ($@) { confess $@ } $ret}
sub new_double_array_len { my $ret; eval { $ret =  &_xs_new_double_array_len(@_) }; if ($@) { confess $@ } $ret}
sub new_double_array_from_bin { my $ret; eval { $ret =  &_xs_new_double_array_from_bin(@_) }; if ($@) { confess $@ } $ret}
sub new_float_array { my $ret; eval { $ret =  &_xs_new_float_array(@_) }; if ($@) { confess $@ } $ret}
sub new_float_array_len { my $ret; eval { $ret =  &_xs_new_float_array_len(@_) }; if ($@) { confess $@ } $ret}
sub new_float_array_from_bin { my $ret; eval { $ret =  &_xs_new_float_array_from_bin(@_) }; if ($@) { confess $@ } $ret}
sub new_string_array { my $ret; eval { $ret =  &_xs_new_string_array(@_) }; if ($@) { confess $@ } $ret}
sub dump { my $ret; eval { $ret =  &_xs_dump(@_) }; if ($@) { confess $@ } $ret}
sub get_exception { my $ret; eval { $ret =  &_xs_get_exception(@_) }; if ($@) { confess $@ } $ret}
sub set_exception { my $ret; eval { $ret =  &_xs_set_exception(@_) }; if ($@) { confess $@ } $ret}
sub get_memory_blocks_count { my $ret; eval { $ret =  &_xs_get_memory_blocks_count(@_) }; if ($@) { confess $@ } $ret}
sub call_method { my $ret; eval { $ret =  &_xs_call_method(@_) }; if ($@) { confess $@ } $ret}

1;

=encoding utf8

=head1 Name

SPVM::ExchangeAPI - SPVM Exchange API

=head1 Description

C<SPVM::ExchangeAPI> is APIs to convert Perl data structures to/from SPVM data structures, and to call SPVM methods from Perl.

=head1 Usage
  
  use SPVM ();
  my $api = SPVM::api();
  my $spvm_int_array = $api->new_int_array([1, 2, 3]);
  my $perl_array_ref = $spvm_int_array->to_array;
  
  my $spvm_string = $api->new_string("abc");
  my $perl_string = $spvm_string->to_string;
  
  use SPVM 'Int';
  my $int_object = Int->new(4);
  my $value = $int_object->value;

=head1 Fields

=head2 env

  my $env = $api->env;

Gets the current execution environment.

=head2 stack

  my $stack = $api->stack;

Gets the current call stack.

=head1 Class Methods

  my $api = SPVM::ExchangeAPI->new(env => $env, stack => $stack);

Creates a new L<SPVM::ExchangeAPI> object.

Options:

=over 2

=item C<env>

An execution environment.

C<env> must be a L<SPVM::Bulder::Env> or L<SPVM::BlessedObject::Class> object of the L<Env|SPVM::Env> class.
  
=item C<stack>

An call stack.

C<stack> must be a L<SPVM::Bulder::Stack> or L<SPVM::BlessedObject::Class> object of the L<Stack|SPVM::Stack> class.

=back

=head2 new_string

  my $spvm_string = $api->new_string($string);

Converts the Perl scalar $string to a SPVM string using perlapi L<SvPV|https://perldoc.perl.org/perlapi#SvPV>, and returns the object that converts it to a L<SPVM::BlessedObject::String> object.

If the $string is undef, returns undef.

If the $string is a L<SPVM::BlessedObject::String> object, returns itself.

Exceptions:

The $string must be a non-reference scalar or a SPVM::BlessedObject::String object or undef. Otherwise an exception is thrown.

Examples:

  my $spvm_string = $api->new_string("abc");
  
  my $spvm_string = $api->new_string("あいう");

=head2 new_byte_array
  
  my $spvm_array = $api->new_byte_array($array);

Converts the Perl array reference $array to a SPVM byte array, and returns the object that converts it to a L<SPVM::BlessedObject::Array> object.

Each element is converted by the conversion of L</"byte Type Argument">.

If the $array is undef, returns undef.

If the $array is a L<SPVM::BlessedObject::Array> object, returns itself.

Exceptions:

The $array must be an array reference or a SPVM::BlessedObject::Array object of the byte[] type or undef. Otherwise an exception is thrown.

Examples:

  my $spvm_array = $api->new_byte_array([1, 2, 3]);

=head2 new_byte_array_unsigned
  
  my $spvm_array = $api->new_byte_array_unsigned($array);

The same as the L</"new_byte_array"> method, but each element is converted by the L<SvUV|https://perldoc.perl.org/perlapi#SvUV> perlapi and a type cast to C<uint8_t> in the C language.

  (int8_t)(uint8_t)SvUV(perl_scalar);

=head2 new_byte_array_len

  my $spvm_array= $api->new_byte_array_len($length);

Creates a SPVM byte array with the length $length, and returns the object that converts it to a L<SPVM::BlessedObject::Array> object.

Exceptions:

The $length must be greater than or equal to 0. Otherwise an exception is thrown.

Examples:
  
  my $length = 10;
  my $spvm_array = $api->new_byte_array_len($length);

=head2 new_byte_array_from_bin

  my $spvm_array = $api->new_byte_array_from_bin($binary);

Converts the binary date $binary to a SPVM byte array, and returns the object that converts it to a L<SPVM::BlessedObject::Array> object.

The binary data is interpreted as 8-bit signed integer. The length of the array is calcurated from the $binary.

Exceptions:

The $binary must be defined. Otherwise an exception is thrown.

Examples:

  my $binary = pack('c*', 97, 98, 99);
  my $spvm_array = $api->new_byte_array_from_bin($binary);

  my $string = "abc";
  my $spvm_array = $api->new_byte_array_from_bin($string);
  
  my $string = "あいう";
  my $spvm_array = $api->new_byte_array_from_bin($string);

=head2 new_short_array
  
  my $spvm_array = $api->new_short_array($array);

Converts the Perl array reference $array to a SPVM short array, and returns the object that converts it to a L<SPVM::BlessedObject::Array> object.

Each element is converted by the conversion of L</"short Type Argument">.

If the $array is undef, returns undef.

If the $array is a L<SPVM::BlessedObject::Array> object, returns itself.

Exceptions:

The $array must be an array reference or a SPVM::BlessedObject::Array object of the short[] type or undef. Otherwise an exception is thrown.

Examples:

  my $spvm_array = $api->new_short_array([1, 2, 3]);

=head2 new_short_array_unsigned
  
  my $spvm_array = $api->new_short_array_unsigned($array);

The same as the L</"new_short_array"> method, but each element is converted by the L<SvUV|https://perldoc.perl.org/perlapi#SvUV> perlapi and a type cast to C<uint16_t> in the C language.

  (int16_t)(uint16_t)SvUV(perl_scalar);

=head2 new_short_array_len

  my $spvm_array = $api->new_short_array_len($length);

Creates a SPVM short array with the length $length, and returns the object that converts it to a L<SPVM::BlessedObject::Array> object.

Exceptions:

The $length must be greater than or equal to 0. Otherwise an exception is thrown.

Examples:
  
  my $length = 10;
  my $spvm_array = $api->new_short_array_len($length);

=head2 new_short_array_from_bin

  my $spvm_array = $api->new_short_array_from_bin($binary);

Converts the binary date $binary to a SPVM short array, and returns the object that converts it to a L<SPVM::BlessedObject::Array> object.

The binary data is interpreted as 16-bit signed integer. The length of the array is calcurated from the $binary.

Exceptions:

The $binary must be defined. Otherwise an exception is thrown.

The length of the $binary must be divisible by 2. Otherwise an exception is thrown.

Examples:

  my $binary = pack('s*', 97, 98, 99);
  my $spvm_array = $api->new_short_array_from_bin($binary);

=head2 new_int_array
  
  my $spvm_array = $api->new_int_array($array);

Converts the Perl array reference $array to a SPVM int array, and returns the object that converts it to a L<SPVM::BlessedObject::Array> object.

Each element is converted by the conversion of L</"int Type Argument">.

If the $array is undef, returns undef.

If the $array is a L<SPVM::BlessedObject::Array> object, returns itself.

Exceptions:

The $array must be an array reference or a SPVM::BlessedObject::Array object of the int[] type or undef. Otherwise an exception is thrown.

Examples:

  my $spvm_array = $api->new_int_array([1, 2, 3]);

=head2 new_long_array_unsigned
  
  my $spvm_array = $api->new_long_array_unsigned($array);

The same as the L</"new_long_array"> method, but each element is converted by the L<SvUV|https://perldoc.perl.org/perlapi#SvUV> perlapi and a type cast to C<uint32_t> in the C language.

  (int32_t)(uint32_t)SvUV(perl_scalar);

=head2 new_int_array_len

  my $spvm_array = $api->new_int_array_len($length);

Creates a SPVM int array with the length $length, and returns the object that converts it to a L<SPVM::BlessedObject::Array> object.

Exceptions:

The $length must be greater than or equal to 0. Otherwise an exception is thrown.

Examples:
  
  my $length = 10;
  my $spvm_array = $api->new_int_array_len($length);

=head2 new_int_array_from_bin

  my $spvm_array = $api->new_int_array_from_bin($binary);

Converts the binary date $binary to a SPVM int array, and returns the object that converts it to a L<SPVM::BlessedObject::Array> object.

The binary data is interpreted as 32-bit signed integer. The length of the array is calcurated from the $binary.

Exceptions:

The $binary must be defined. Otherwise an exception is thrown.

The length of the $binary must be divisible by 4. Otherwise an exception is thrown.

Examples:

  my $binary = pack('l*', 97, 98, 99);
  my $spvm_array = $api->new_int_array_from_bin($binary);

=head2 new_long_array
  
  my $spvm_array = $api->new_long_array($array);

Converts the Perl array reference $array to a SPVM long array, and returns the object that converts it to a L<SPVM::BlessedObject::Array> object. Each element is converted by the conversion of L</"long Type Argument">.

If the $array is undef, returns undef.

Exceptions:

The $array must be an array reference or a SPVM::BlessedObject::Array object of the long[] type or undef. Otherwise an exception is thrown.

Examples:

  my $spvm_array = $api->new_long_array([1, 2, 3]);

=head2 new_long_array_unsigned
  
  my $spvm_array = $api->new_long_array_unsigned($array);

The same as the L</"new_long_array"> method, but each element is converted by the L<SvUV|https://perldoc.perl.org/perlapi#SvUV> perlapi and a type cast to C<uint64_t> in the C language.

  (int64_t)(uint64_t)SvUV(perl_scalar);

=head2 new_long_array_len

  my $spvm_array = $api->new_long_array_len($length);

Creates a SPVM byte array with the length $length, and returns the object that converts it to a L<SPVM::BlessedObject::Array> object.

Exceptions:

The $length must be greater than or equal to 0. Otherwise an exception is thrown.

Examples:
  
  my $length = 10;
  my $spvm_array = $api->new_long_array_len($length);

=head2 new_long_array_from_bin

  my $spvm_array = $api->new_long_array_from_bin($binary);

Converts the binary date $binary to a SPVM long array, and returns the object that converts it to a L<SPVM::BlessedObject::Array> object.

The binary data is interpreted as 64-bit signed integer. The length of the array is calcurated from the $binary.

Exceptions:

The $binary must be defined. Otherwise an exception is thrown.

The length of the $binary must be divisible by 8. Otherwise an exception is thrown.

Examples:

  my $binary = pack('q*', 97, 98, 99);
  my $spvm_array = $api->new_long_array_from_bin($binary);

=head2 new_float_array
  
  my $spvm_array = $api->new_float_array($array);

Converts the Perl array reference $array to a SPVM float array, and returns the object that converts it to a L<SPVM::BlessedObject::Array> object.

Each element is converted by the conversion of L</"float Type Argument">.

If the $array is undef, returns undef.

If the $array is a L<SPVM::BlessedObject::Array> object, returns itself.

Exceptions:

The $array must be an array reference or a SPVM::BlessedObject::Array object of the float[] type or undef. Otherwise an exception is thrown.

Examples:

  my $spvm_array = $api->new_float_array([1, 2, 3]);

=head2 new_float_array_len

  my $spvm_array = $api->new_float_array_len($length);

Creates a SPVM byte array with the length $length, and returns the object that converts it to a L<SPVM::BlessedObject::Array> object.

Exceptions:

The $length must be greater than or equal to 0. Otherwise an exception is thrown.

Examples:
  
  my $length = 10;
  my $spvm_array = $api->new_float_array_len($length);

=head2 new_float_array_from_bin

  my $spvm_array = $api->new_float_array_from_bin($binary);

Converts the binary date $binary to a SPVM float array, and returns the object that converts it to a L<SPVM::BlessedObject::Array> object.

The binary data is interpreted as 32-bit floating point. The length of the array is calcurated from the $binary.

Exceptions:

The $binary must be defined. Otherwise an exception is thrown.

The length of the $binary must be divisible by 4. Otherwise an exception is thrown.

Examples:

  my $binary = pack('f*', 97.1, 98.2, 99.3);
  my $spvm_array = $api->new_float_array_from_bin($binary);

=head2 new_double_array
  
  my $spvm_array = $api->new_double_array($array);

Converts the Perl array reference $array to a SPVM double array, and returns the object that converts it to a L<SPVM::BlessedObject::Array> object.

Each element is converted by the conversion of L</"double Type Argument">.

Exceptions:

The $array must be an array reference or a SPVM::BlessedObject::Array object of the double[] type or undef. Otherwise an exception is thrown.

Examples:

  my $spvm_array = $api->new_double_array([1, 2, 3]);

=head2 new_double_array_len

  my $spvm_array = $api->new_double_array_len($length);

Creates a SPVM byte array with the length $length, and returns the object that converts it to a L<SPVM::BlessedObject::Array> object.

Exceptions:

The $length must be greater than or equal to 0. Otherwise an exception is thrown.

Examples:
  
  my $length = 10;
  my $spvm_array = $api->new_double_array_len($length);

=head2 new_double_array_from_bin

  my $spvm_array = $api->new_double_array_from_bin($binary);

Converts the binary date $binary to a SPVM double array, and returns the object that converts it to a L<SPVM::BlessedObject::Array> object.

The binary data is interpreted as 64-bit floating point. The length of the array is calcurated from the $binary.

Exceptions:

The $binary must be defined. Otherwise an exception is thrown.

The length of the $binary must be divisible by 8. Otherwise an exception is thrown.

Examples:

  my $binary = pack('d*', 97.1, 98.2, 99.3);
  my $spvm_array = $api->new_double_array_from_bin($binary);

=head2 new_string_array
  
  my $spvm_array = $api->new_string_array($array);

Converts the Perl array reference $array to a SPVM string array, and returns the object that converts it to a L<SPVM::BlessedObject::Array> object. Each element is converted by the L</"new_string"> method.

If the $array is undef, returns undef.

If the $array is a L<SPVM::BlessedObject::Array> object, returns itself.

Exceptions:

If the $array is a reference other than the array reference, an exception is thrown.

If the $array is a L<SPVM::BlessedObject::Array> object, the assignability to the C<string[]> type is checked. If it is assignable, returns itself, otherwise an exception is thrown.

Examples:

  my $spvm_array = $api->new_string_array(["foo", "bar", "baz"]);
  
  my $spvm_array = $api->new_string_array(["あい", "うえ", "お"]);

=head2 new_any_object_array

  my $byte_array = $api->new_any_object_array(
    [SPVM::Byte->new(1), SPVM::Byte>new(2), SPVM::Byte->new(3)]
  );

The alias for the following code using the L</"new_object_array"> method.

  my $spvm_array = $api->new_object_array('object[]', $array);

=head2 new_options

  my $spvm_any_object_array = $api->new_options($options);

Converts the Perl hash reference $options to a SPVM C<object[]> value, and returns the object that converts it to a L<SPVM::BlessedObject::Array> object.

Each key of the $options is converted to a L<SPVM::BlessedObject::String> object using the L</"new_string"> method.

Exceptions:

The value of the $options must be a L<SPVM::BlessedObject> object. Otherwise an exception is thrown.

The $options must be a hash reference. Otherwise an exception is thrown.

Examples:

  my $options = $api->new_options({
    x => SPVM::Int->new(1),
    y => SPVM::Int->new(2)
  });

=head2 new_object_array

  my $spvm_object_array = $api->new_object_array($type_name, $array);

Converts the Perl array reference $array to a value of the SPVM array(1-dimensional) type $type_name, and returns the object that converts it to a L<SPVM::BlessedObject::Array> object.

If the $array is undef, it is converted to SPVM undef.

If the $array is a L<SPVM::BlessedObject::Array> object, returns itself.

Exceptions:

If the $array is a reference other than the array reference, an exception is thrown.

If the $array is a L<SPVM::BlessedObject::Array> object, the assignability to the $type is checked. If it is not assignable, an exception is thrown.

If the bacic type of the type $type_name is not found, an exception is thrown.

The dimension of the $type_name must be 1. Otherwise an exception is thrown.

The assignability of the element to the element type of the $type_name is checked. If it is not assignable, an exception is thrown.

Examples:
  
  my $point1 = SPVM::Point->new;
  my $point2 = SPVM::Point->new;
  my $objects = $api->new_object_array("Point[]", [$point1, $point2]);

=head2 new_muldim_array

  my $spvm_object_array = $api->new_muldim_array($type_name, $array);

Converts the Perl array reference $array to a value of the SPVM multi-dimensional array type $type_name, and returns the object that converts it to a L<SPVM::BlessedObject::Array> object.

If the $array is undef, it is converted to SPVM undef.

If the $array is a L<SPVM::BlessedObject::Array> object, returns itself.

Exceptions:

If the $array is a reference other than the array reference, an exception is thrown.

If the $array is a L<SPVM::BlessedObject::Array> object, the assignability to the $type is checked. If it is not assignable, an exception is thrown.

If the bacic type of the type $type_name is not found, an exception is thrown.

The dimension of the $type_name must be greater than or equal to 2 and less than or equal to 255. Otherwise an exception is thrown.

The assignability of the element to the element type of the $type_name is checked. If it is not assignable, an exception is thrown.

Examples:

  my $object1 = $api->new_int_array([1, 2, 3]);
  my $object2 = $api->new_int_array([4, 5, 6]);
  my $objects = $api->new_muldim_array("int[][]", [$object1, $object2]);

=head2 new_mulnum_array

  my $spvm_mulnum_array = $api->new_mulnum_array($type_name, $array);

Converts the Perl array reference of hash references $array to the SPVM multi-numeric array type $type_name, and returns the object that converts it to a L<SPVM::BlessedObject::Array> object.

Each element of the $array must be a hash reference. Otherwise an exception is thrown.
Each value of the hash reference is coverted by the conversion of L</"byte Type Argument">, L</"short Type Argument">, L</"int Type Argument">, L</"long Type Argument">, L</"float Type Argument">, L</"double Type Argument"> corresponding to the numeric type of the the element of the $type.

Exceptions:

All fields of the element type of the $type_name must be defined. Otherwise an exception is thrown.

If the bacic type of the type $type_name is not found, an exception is thrown.

The dimension of the type $type_name must be 1. Otherwise an exception is thrown.

The $array must be an array reference. Otherwise an exception is thrown.

Examples:

  my $values = [
    {x => 0, y => 1, z => 2},
    {x => 3, y => 4, z => 5},
    {x => 6, y => 7, z => 8},
  ];
  my $spvm_mulnum_array = $api->new_mulnum_array("TestCase::Point_3i[]", $values);

=head2 new_mulnum_array_from_bin

  my $spvm_mulnum_array = $api->new_mulnum_array_from_bin($type_name, $binary);

Converts the binary data $binary to a SPVM multi-numeric array type $type_name, and returns the object that converts it to a L<SPVM::BlessedObject::Array> object.

Exceptions:

If the bacic type of the type $type_name is not found, an exception is thrown.

The dimension of the type $type_name must be 1. Otherwise an exception is thrown.

The $binary must be an array reference. Otherwise an exception is thrown.

The length of the $binary must be divisible by the length of fields * the byte size of the element type. Otherwise an exception is thrown.

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

  my $message = $api->get_exception();

Returns the exception of the current thread variables as a L<SPVM::BlessedObject::String> object.

If the exception is not set, undef is returned.

=head2 set_exception

  $api->set_exception($message);

Sets a message given by the $message to the exception of the current thread variables.

The $message is converted to the SPVM string using the L</"new_string"> method.

Exceptions:

Exceptions thrown by the L</"new_string"> method are thrown.

Examples:

  $api->set_exception("Error");
  $api->set_exception(undef);

=head2 get_memory_blocks_count

  my $count = $api->get_memory_blocks_count();

Returns the count of memory blocks on the current execution environment.

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

=head2 class

  my $class = $api->class($class_name);

Creates a new L<SPVM::ExchangeAPI::Class> object with the class name $class_name, and returns it.

Examples:
  
  my $class = $api->class('Int');
  my $spvm_object = $class->new(1);

=head2 dump

  my $dump = $api->dump($object);

Converts the SPVM object $object to a dumped string using the L<dump|SPVM::Document::Language/"dump Operator"> operator, and returns it.

Exceptions:

The $object must be a SPVM::BlessedObject object. Otherwise an exception is thrown.

=head2 error

  my $error = $api->new_error;

Creates a new L<SPVM::ExchangeAPI::Error> object, and returns it.

The error code is set to 0.

=head2 call_method
  
  my $ret = $api->call_method($invocant, $method_name, @args);
  
  my $ret = $api->call_method($invocant, $method_name, @args, $error);

Calls a class method or an instance method. If the invocant $invocant is a string, a class method is called. If the invocant $invocant is a L<SPVM::BlessedObject::Class>, an instance method is called.

Each of the arguments @args are converted by the rule of L</"Argument Conversion">.

The method name $method_name allows a static method name such as C<Foo::bar>.

The return value is converted by the rule of L</"Return Value Conversion">.

If a L<SPVM::ExchangeAPI::Error> object is passed to the last of the arguments, and if an exception is thrown from a SPVM method, the error code is set to the C<code> field of the object.

Exceptions:

If the $invocant is a SPVM::BlessedObject, the $invocant must be a SPVM::BlessedObject::Class object. Otherwise an exception is thrown.

The static method call must be valid. Otherwise an exception is thrown.

If the M method in the C class is not found, an exception is thrown.

If too few arguments are passed to the M method in the C class, an exception is thrown.

If too many arguments are passed to the M method in the C class, an exception is thrown.

If the L<argument conversion/"Argument Conversion"> fails, an exception is thrown.

If the calling method throws an exception, the exception is thrown.

Examples:

  # Class method call
  my $obj_int = $api->call_method("Int", "new", 1);
  
  # Instance method call
  $api->call_method($obj_int, "set_value", 5);
  my $value = $api->call_method($obj_int, "value");
  
  # Call static instance method
  $api->call_method($object, "Foo::value");

Easy Ways:

Calling class methods can be made easier using the L<SPVM class loading|SPVM/"Loading Module"> feature.

  use SPVM 'Int';
  my $int_object = Int->new(4);

Instance method calls can be made easier using L<SPVM::BlessedObject::Class>.

  my $value = $int_object->value;

=head1 Argument Conversion

Each argument passed to the L</"call_method"> method are converted to a SPVM value according to the SPVM type before it passed to a SPVM method.

=head2 byte Type Argument

A Perl scalar is converted to a value of the SPVM C<byte> type by the L<SvIV|https://perldoc.perl.org/perlapi#SvIV> perlapi and a type cast to C<int8_t> in the C language.

  (int8_t)SvIV(perl_scalar)

Exceptions:

The argument must be a non-reference scalar. Otherwise an exception is thrown.

=head2 short Type Argument

A Perl scalar is converted to a value of the SPVM C<short> type by the L<SvIV|https://perldoc.perl.org/perlapi#SvIV> perlapi and a type cast to C<int16_t> in the C language.
  
  (int16_t)SvIV(perl_scalar)

Exceptions:

The argument must be a non-reference scalar. Otherwise an exception is thrown.

=head2 int Type Argument

A Perl scalar is converted to a value of the SPVM C<int> type by the L<SvIV|https://perldoc.perl.org/perlapi#SvIV> perlapi and a type cast to C<int32_t> in the C language.

  (int32_t)SvIV(perl_scalar)

Exceptions:

The argument must be a non-reference scalar. Otherwise an exception is thrown.

Examples:

  my $int_object = SPVM::Int->new(10);

=head2 long Type Argument

A Perl scalar is converted to a value of the SPVM C<long> type by the L<SvIV|https://perldoc.perl.org/perlapi#SvIV> perlapi and a type cast to C<int64_t> in the C language.

  (int64_t)SvIV(perl_scalar)

Exceptions:

The argument must be a non-reference scalar. Otherwise an exception is thrown.

Examples:

  my $long_object = SPVM::Long->new(10);

=head2 float Type Argument

A Perl scalar is converted to a value of the SPVM C<float> type by the L<SvNV|https://perldoc.perl.org/perlapi#SvNV> perlapi and a type cast to C<float> in the C language.

  (float)SvNV(perl_scalar)

Exceptions:

The argument must be a non-reference scalar. Otherwise an exception is thrown.

Examples:

  my $float_object = SPVM::Float->new(10.5);

=head2 double Type Argument

A Perl scalar is converted to a value of the SPVM C<double> type by the L<SvNV|https://perldoc.perl.org/perlapi#SvNV> perlapi and a type cast to C<double> in the C language.

  (double)SvNV(perl_scalar)

Exceptions:

The argument must be a non-reference scalar. Otherwise an exception is thrown.

Examples:

  my $double_object = SPVM::Double->new(10.5);

=head2 string Type Argument

A Perl scalar is converted to a value of the SPVM C<string> type by the L</"new_string"> method.

Exceptions:

Exceptions thrown by the L</"new_string"> method are thrown.

Examples:
  
  my $substr = SPVM::Fn->substr("abcde", 0, 3);

=head2 Any Object Type Argument

No conversion is performed.

Exceptions:

The argument must be a SPVM::BlessedObject object or undef. Otherwise an exception is thrown.

=head2 Class Type Argument

No conversion is performed.

Exceptions:

The argument must be a SPVM::BlessedObject::Class object of a Z assignable type or undef. Otherwise an exception is thrown.

=head2 Interaface Type Argument

No conversion is performed.

Exceptions:

The argument must be a SPVM::BlessedObject::Class object of a Z assignable type or undef. Otherwise an exception is thrown.

=head2 Multi-Numeric Type Argument

=head3 Multi-Numeric byte

Converts a hash reference containing field names and its values of the multi-numeric byte type to a value of the multi-numeric byte type.

Each field value is coverted by the conversion of L</"byte Type Argument">.

Exceptions:

The argument must be a hash reference. Otherwise an exception is thrown.

If a field is not found, an exception is thrown.

Examples:

  # Converts a Perl hash reference to MyClassPoint_2b type
  SPVM::MyClass->foo({x => 1, y => 2});

=head3 Multi-Numeric short Type Argument

Converts a hash reference containing field names and its values of the multi-numeric short type to a value of the multi-numeric short type.

Each field value is coverted by the conversion of L</"short Type Argument">.

Exceptions:

The argument must be a hash reference. Otherwise an exception is thrown.

If a field is not found, an exception is thrown.

Examples:

  # Converts a Perl hash reference to MyClassPoint_2s type
  SPVM::MyClass->foo({x => 1, y => 2});

=head3 Multi-Numeric int Type Argument

Converts a hash reference containing field names and its values of the multi-numeric int type to a value of the multi-numeric int type.

Each field value is coverted by the conversion of L</"int Type Argument">.

Exceptions:

The argument must be a hash reference. Otherwise an exception is thrown.

If a field is not found, an exception is thrown.

Examples:

  # Converts a Perl hash reference to MyClassPoint_2i type
  SPVM::MyClass->foo({x => 1, y => 2});

=head3 Multi-Numeric long Type Argument

Converts a hash reference containing field names and its values of the multi-numeric long type to a value of the multi-numeric long type.

Each field value is coverted by the conversion of L</"long Type Argument">.

Exceptions:

The argument must be a hash reference. Otherwise an exception is thrown.

If a field is not found, an exception is thrown.

Examples:

  # Converts a Perl hash reference to MyClassPoint_2l type
  SPVM::MyClass->foo({x => 1, y => 2});

=head3 Multi-Numeric float Type Argument

Converts a hash reference containing field names and its values of the multi-numeric float type to a value of the multi-numeric float type.

Each field value is coverted by the conversion of L</"float Type Argument">.

Exceptions:

The argument must be a hash reference. Otherwise an exception is thrown.

If a field is not found, an exception is thrown.

Examples:

  # Converts a Perl hash reference to MyClassPoint_2f type
  SPVM::MyClass->foo({x => 1.2, y => 2.3});

=head3 Multi-Numeric double Type Argument

Converts a hash reference containing field names and its values of the multi-numeric double type to a value of the multi-numeric double type.

Each field value is coverted by the conversion of L</"double Type Argument">.

Exceptions:

The argument must be a hash reference. Otherwise an exception is thrown.

If a field is not found, an exception is thrown.

Examples:

  # Converts a Perl hash reference to MyClassPoint_2d type
  SPVM::MyClass->foo({x => 1.2, y => 2.3});

=head2 Numeric Reference Type Argument

=head3 byte Reference Type Argument

A Perl reference is converted to a value of the SPVM byte reference type.

The referenced value is converted to a value of the SPVM C<byte> type by the conversion of L</"byte Type Argument">.

After returning from the SPVM method, the referenced value is converted to a Perl scalar by the conversion of L</"byte Type Return Value">

Exceptions:

The argument must be a scalar reference. Otherwise an exception is thrown.

Examples:

  # Converts a Perl scalar reference to byte* type
  my $value = 23;
  SPVM::MyClass->foo(\$value);

=head3 short Reference Type Argument

A Perl reference is converted to a value of the SPVM short reference type.

The referenced value is converted to a value of the SPVM C<short> type by the conversion of L</"short Type Argument">.

After returning from the SPVM method, the referenced value is converted to a Perl scalar by the conversion of L</"short Type Return Value">

Exceptions:

The argument must be a scalar reference. Otherwise an exception is thrown.

Examples:

  # Converts a Perl scalar reference to short* type
  my $value = 23;
  SPVM::MyClass->foo(\$value);

=head3 int Reference Type Argument

A Perl reference is converted to a value of the SPVM int reference type.

The referenced value is converted to a value of the SPVM C<int> type by the conversion of L</"int Type Argument">.

After returning from the SPVM method, the referenced value is converted to a Perl scalar by the conversion of L</"int Type Return Value">

Exceptions:

The argument must be a scalar reference. Otherwise an exception is thrown.

Examples:

  # Converts a Perl scalar reference to int* type
  my $value = 23;
  SPVM::MyClass->foo(\$value);

=head3 long Reference Type Argument

A Perl reference is converted to a value of the SPVM long reference type.

The referenced value is converted to a value of the SPVM C<long> type by the conversion of L</"long Type Argument">.

After returning from the SPVM method, the referenced value is converted to a Perl scalar by the conversion of L</"long Type Return Value">

Exceptions:

The argument must be a scalar reference. Otherwise an exception is thrown.

Examples:

  # Converts a Perl scalar reference to long* type
  my $value = 23;
  SPVM::MyClass->foo(\$value);

=head3 float Reference Type Argument

A Perl reference is converted to a value of the SPVM float reference type.

The referenced value is converted to a value of the SPVM C<float> type by the conversion of L</"float Type Argument">.

After returning from the SPVM method, the referenced value is converted to a Perl scalar by the conversion of L</"float Type Return Value">

Exceptions:

The argument must be a scalar reference. Otherwise an exception is thrown.

Examples:

  # Converts a Perl scalar reference to float* type
  my $value = 23.5;
  SPVM::MyClass->foo(\$value);

=head3 double Reference Type Argument

A Perl reference is converted to a value of the SPVM double reference type.

The referenced value is converted to a value of the SPVM C<double> type by the conversion of L</"double Type Argument">.

After returning from the SPVM method, the referenced value is converted to a Perl scalar by the conversion of L</"double Type Return Value">

Exceptions:

The argument must be a scalar reference. Otherwise an exception is thrown.

Examples:

  # Converts a Perl scalar reference to double* type
  my $value = 23.5;
  SPVM::MyClass->foo(\$value);

=head2 Multi-Numeric Reference Type Argument

=head3 Multi-Numeric byte Reference Type Argument

A Perl reference is converted to a SPVM multi-numeric C<byte> reference type.

Each field is converted to a value of the SPVM C<byte> type by the conversion of L</"byte Type Argument">.

After returning from the SPVM method, each field value is converted to a Perl scalar by the conversion of L</"byte Type Return Value">.

Exceptions:

The reference must be a scalar reference to a hash reference. Otherwise an exception is thrown.

If a field is not found, an exception is thrown.

Examples:

  # Converts a Perl scalar reference to a hash reference to the MyClassPoint_2b* type
  my $value = {x => 1, y => 2};
  SPVM::MyClass->foo(\$value);

=head3 Multi-Numeric short Reference Type Argument

A Perl reference is converted to a SPVM multi-numeric C<short> reference type.

Each field is converted to a value of the SPVM C<short> type by the conversion of L</"short Type Argument">.

After returning from the SPVM method, each field value is converted to a Perl scalar by the conversion of L</"short Type Return Value">.

Exceptions:

The reference must be a scalar reference to a hash reference. Otherwise an exception is thrown.

If a field is not found, an exception is thrown.

Examples:

  # Converts a Perl scalar reference to a hash reference to the MyClassPoint_2s* type
  my $value = {x => 1, y => 2};
  SPVM::MyClass->foo(\$value);

=head3 Multi-Numeric int Reference Type Argument

A Perl reference is converted to a SPVM multi-numeric C<int> reference type.

Each field is converted to a value of the SPVM C<int> type by the conversion of L</"int Type Argument">.

After returning from the SPVM method, each field value is converted to a Perl scalar by the conversion of L</"int Type Return Value">.

Exceptions:

The reference must be a scalar reference to a hash reference. Otherwise an exception is thrown.

If a field is not found, an exception is thrown.

Examples:

  # Converts a Perl scalar reference to a hash reference to the SPVM MyClassPoint_2i* type
  my $value = {x => 1, y => 2};
  SPVM::MyClass->foo(\$value);

=head3 Multi-Numeric long Reference Type Argument

A Perl reference is converted to a SPVM multi-numeric C<long> reference type.

Each field is converted to a value of the SPVM C<long> type by the conversion of L</"long Type Argument">.

After returning from the SPVM method, each field value is converted to a Perl scalar by the conversion of L</"long Type Return Value">.

Exceptions:

The reference must be a scalar reference to a hash reference. Otherwise an exception is thrown.

If a field is not found, an exception is thrown.

Examples:

  # Converts a Perl scalar reference to a hash reference to the SPVM MyClassPoint_2l* type
  my $value = {x => 1, y => 2};
  SPVM::MyClass->foo(\$value);

=head3 Multi-Numeric float Reference Type Argument

A Perl reference is converted to a SPVM multi-numeric C<float> reference type.

Each field is converted to a value of the SPVM C<float> type by the conversion of L</"float Type Argument">.

After returning from the SPVM method, each field value is converted to a Perl scalar by the conversion of L</"float Type Return Value">.

Exceptions:

The reference must be a scalar reference to a hash reference. Otherwise an exception is thrown.

If a field is not found, an exception is thrown.

Examples:

  # Converts a Perl scalar reference to a hash reference to the SPVM MyClassPoint_2f* type
  my $value = {x => 1,2, y => 2.3};
  SPVM::MyClass->foo(\$value);

=head3 Multi-Numeric double Reference Type Argument

A Perl reference is converted to a SPVM multi-numeric C<double> reference type.

Each field is converted to a value of the SPVM C<double> type by the conversion of L</"double Type Argument">.

After returning from the SPVM method, each field value is converted to a Perl scalar by the conversion of L</"double Type Return Value">.

Exceptions:

The reference must be a scalar reference to a hash reference. Otherwise an exception is thrown.

If a field is not found, an exception is thrown.

Examples:

  # Converts a Perl scalar reference to a hash reference to the SPVM MyClassPoint_2d* type
  my $value = {x => 1.2, y => 2.3};
  SPVM::MyClass->foo(\$value);

=head2 Array Type Argument

=head3 byte[] Type Argument

A Perl array reference(or undef) is converted to a value of the C<byte[]> type by the L</"new_byte_array"> method.

Exceptions:

Exceptions thrown by the L</"new_byte_array"> method are thrown.

Examples:

  # Converts a Perl array reference to the byte[] type
  SPVM::MyClass->foo([1, 2, 3]);

=head3 short[] Type Argument

A Perl array reference(or undef) is converted to a value of the C<short[]> type by the L</"new_short_array"> method.

Exceptions:

Exceptions thrown by the L</"new_short_array"> method are thrown.

Examples:

  # Converts a Perl array reference to the short[] type
  SPVM::MyClass->foo([1, 2, 3]);

=head3 int[] Type Argument

A Perl array reference(or undef) is converted to a value of the C<int[]> type by the L</"new_int_array"> method.

Exceptions:

Exceptions thrown by the L</"new_int_array"> method are thrown.

Examples:

  # Converts a Perl array reference to the int[] type
  SPVM::MyClass->foo([1, 2, 3]);

=head3 long[] Type Argument

A Perl array reference(or undef) is converted to a value of the C<long[]> type by the L</"new_long_array"> method.

Exceptions:

Exceptions thrown by the L</"new_long_array"> method are thrown.

Examples:

  # Converts a Perl array reference to the long[] type
  SPVM::MyClass->foo([1, 2, 3]);

=head3 float[] Type Argument

A Perl array reference(or undef) is converted to a value of the C<float[]> type by the L</"new_float_array"> method.

Exceptions:

Exceptions thrown by the L</"new_float_array"> method are thrown.

Examples:

  # Converts a Perl array reference to float[] type
  SPVM::MyClass->foo([1.2, 2.3, 3.4]);

=head3 double[] Type Argument

A Perl array reference(or undef) is converted to a value of the C<double[]> type by the L</"new_double_array"> method.

Exceptions:

Exceptions thrown by the L</"new_double_array"> method are thrown.

Examples:

  # Converts a Perl array reference to the double[] type
  SPVM::MyClass->foo([1.2, 2.3, 3.4]);

=head3 string[] Type Argument

A Perl array reference(or undef) is converted to a value of the C<string[]> type by the L</"new_string_array"> method.

Exceptions:

Exceptions thrown by the L</"new_string_array"> method are thrown.

Examples:

  # Converts a Perl array reference to the string[] type
  SPVM::MyClass->foo(["あい", "うえ", "お"]);

=head3 Any Object Array Type Argument

A Perl array reference(or undef) is converted to a value of the C<object[]> type by the L</"new_object_array"> method.

Exceptions:

Exceptions thrown by the L</"new_object_array"> method are thrown.

=head3 Class Array Type Argument

A Perl array reference(or undef) is converted to a value of the class type by the L</"new_object_array"> method.

Exceptions:

Exceptions thrown by the L</"new_object_array"> method are thrown.

=head3 Interface Array Type Argument

A Perl array reference(or undef) is converted to a value of the interface type by the L</"new_object_array"> method.

Exceptions:

Exceptions thrown by the L</"new_object_array"> method are thrown.

=head3 Multi-Numeric Array Type Argument

A Perl array reference(or undef) is converted to a value of the multi-numeric array type by the L</"new_mulnum_array"> method.

Exceptions:

Exceptions thrown by the L</"new_mulnum_array"> method are thrown.

Examples:

  # Converts a Perl array reference of a hash reference to the Complex_2d[] type
  SPVM::MyClass->foo([{re => 1.2, im => 2.3}, {re => 3.4, im => 4.5}]);

=head3 Multi-Dimensional Array Type Argument

A Perl array reference(or undef) is converted to a value of the multi-dimensional array type by the L</"new_muldim_array"> method.

Exceptions:

Exceptions thrown by the L</"new_muldim_array"> method are thrown.

=head1 Return Value Conversion

A SPVM return value is converted to a Perl value according to the SPVM type.

=head2 void Type Return Value

The SPVM void return value is converted to Perl undef.

=head2 byte Type Return Value

A value of the SPVM byte type is converted to a Perl scalar using the L<newSViv|https://perldoc.perl.org/perlapi#newSViv> perlapi.

=head2 short Type Return Value

A value of the SPVM short type is converted to a Perl scalar using the L<newSViv|https://perldoc.perl.org/perlapi#newSViv> perlapi.

=head2 int Type Return Value

A value of the SPVM float type is converted to a Perl scalar using the L<newSViv|https://perldoc.perl.org/perlapi#newSViv> perlapi.

=head2 long Type Return Value

A value of the SPVM float type is converted to a Perl scalar using the L<newSViv|https://perldoc.perl.org/perlapi#newSViv> perlapi.

=head2 float Type Return Value

A value of the SPVM float type is converted to a Perl scalar using the L<newSVnv|https://perldoc.perl.org/perlapi#newSVnv> perlapi.

=head2 double Type Return Value

A value of the SPVM double type is converted to a Perl scalar using the L<newSVnv|https://perldoc.perl.org/perlapi#newSVnv> perlapi.

=head2 string Type Return Value

If the SPVM return value is undef, it is converted to Perl undef.

Otherwise it is converted to a L<SPVM::BlessedObject::String> object.

=head2 Multi-Numeric Type Return Value

The value of the SPVM multi-numeric type is converted to a Perl hash reference that has the field names of the multi-numeric type as the keys.

Each field value is converted by the conversion of L</"byte Type Return Value">, L</"short Type Return Value">, L</"int Type Return Value">, L</"long Type Return Value">, L</"float Type Return Value">, L</"double Type Return Value"> according to the multi-numeric type.

=head2 Any Object Type Return Value

If the SPVM return value is undef, it is converted to Perl undef.

If the type of the return value is an array type, it is converted to a L<SPVM::BlessedObject::Array> object.

If the type of the return value is an string type, it is converted to a L<SPVM::BlessedObject::String> object.

Otherwise it is converted to a L<SPVM::BlessedObject::Class> object.

=head2 Class Type Return Value

If the SPVM return value is undef, it is converted to Perl undef.

Otherwise it is converted to a L<SPVM::BlessedObject::Class> object.

=head2 Interface Type Return Value

If the SPVM return value is undef, it is converted to Perl undef.

Otherwise it is converted to a L<SPVM::BlessedObject::Class> object.

=head2 Array Type Return Value

If the SPVM return value is undef, it is converted to Perl undef.

Otherwise it is converted to a L<SPVM::BlessedObject::Array> object. 
