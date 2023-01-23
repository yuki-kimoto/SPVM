package SPVM::ExchangeAPI;

use strict;
use warnings;

use Carp 'confess';

sub new {
  my $class = shift;
  
  my $self = {
    @_
  };
  
  bless $self, ref $class || $class;
  
  return $self;
}

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

sub new_byte_array_from_string {
  my ($self, $env, $stack, $string) = @_;
  
  utf8::encode($string);
  
  my $ret;
  eval { $ret = &new_byte_array_from_bin($env, $stack, $string) };
  if ($@) { confess $@ }
  
  return $ret;
}

sub new_any_object_array {
  my ($env, $stack, $array_ref) = @_;
  
  my $type_name = 'object[]';
  
  my $array = &new_object_array($env, $stack, $type_name, $array_ref);
  
  return $array;
}

sub new_object_array {
  my ($env, $stack, $type_name, $elems) = @_;
  
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
    confess "Invalid type dimension(first argument of SPVM::ExchangeAPI::new_object_array)";
  }
  unless (defined $basic_type_name) {
    confess "Invalid basic_type name(first argument of SPVM::ExchangeAPI::new_object_array)";
  }
  
  unless (defined $elems) {
    return undef;
  }
  
  # Check second argument
  unless (ref $elems eq 'ARRAY') {
    confess "Second argument of SPVM::new_object_array must be array reference";
  }
  
  my $ret;
  if ($type_dimension == 1) {
    eval { $ret = SPVM::ExchangeAPI::_xs_new_object_array($env, $stack, $basic_type_name, $elems) };
    if ($@) { confess $@ }
  }
  else {
    eval { $ret = SPVM::ExchangeAPI::_xs_new_muldim_array($env, $stack, $basic_type_name, $type_dimension - 1, $elems) };
    if ($@) { confess $@ }
  }
  
  return $ret;
}

sub new_mulnum_array {
  my ($self, $env, $stack, $type_name, $elems) = @_;
  
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
    confess "Invalid type dimension(first argument of SPVM::ExchangeAPI::new_mulnum_array)";
  }
  unless (defined $basic_type_name) {
    confess "Invalid basic_type name(first argument of SPVM::ExchangeAPI::new_mulnum_array)";
  }

  unless (defined $elems) {
    return undef;
  }
  
  # Check second argument
  unless (ref $elems eq 'ARRAY') {
    confess "Second argument of SPVM::new_mulnum_array must be array reference";
  }
  
  my $ret;
  eval { $ret = SPVM::ExchangeAPI::_xs_new_mulnum_array($self, $env, $stack, $basic_type_name, $elems) };
  if ($@) { confess $@ }
  
  return $ret;
}

sub new_mulnum_array_from_bin {
  my ($self, $env, $stack, $type_name, $elems) = @_;
  
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
    confess "Invalid type dimension(first argument of SPVM::ExchangeAPI::new_mulnum_array_from_bin)";
  }
  unless (defined $basic_type_name) {
    confess "Invalid basic_type name(first argument of SPVM::ExchangeAPI::new_mulnum_array_from_bin)";
  }

  unless (defined $elems) {
    return undef;
  }
  
  my $ret;
  eval { $ret = SPVM::ExchangeAPI::_xs_new_mulnum_array_from_bin($self, $env, $stack, $basic_type_name, $elems) };
  if ($@) { confess $@ }
  
  return $ret;
}

sub set_exception {
  my ($self, $env, $stack, $exception) = @_;
  
  if (defined $exception && !ref $exception) {
    $exception = SPVM::ExchangeAPI::new_string($env, $stack, $exception);
  }
  
  my $ret;
  eval { $ret = _xs_set_exception($self, $env, $stack, $exception) };
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

=head1 Functions

Function names is only listed.

See SPVM Exchange API about the details.

L<SPVM Exchange API|https://yuki-kimoto.github.io/spvmdoc-public/exchange-api.html>
