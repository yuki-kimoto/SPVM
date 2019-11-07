package SPVM::ExchangeAPI;

use strict;
use warnings;

use Encode 'encode', 'decode';
use Carp 'confess';

sub to_str {
  my $bin = SPVM::ExchangeAPI::to_bin(@_);
  
  my $string = decode('UTF-8', $bin);
  
  return $string;
}

sub to_strs {
  my $elems = SPVM::ExchangeAPI::to_elems(@_);
  
  my $strs = [];
  
  for (my $i = 0; $i < @$elems; $i++) {
    my $elem = $elems->[$i];
    if (defined $elem) {
      $strs->[$i] = $elem->to_str;
    }
    else {
      $strs->[$i] = undef;
    }
  }
  
  return $strs;
}

sub new_barray_from_str {
  my ($env, $string) = @_;
  
  my $bin = encode('UTF-8', $string);
  
  return SPVM::ExchangeAPI::new_barray_from_bin($env, $bin);
}

sub new_str { SPVM::ExchangeAPI::new_barray_from_str(@_) }

sub new_str_from_bin { SPVM::ExchangeAPI::new_barray_from_bin(@_) }

sub new_oarray {
  my ($env, $type_name, $elems) = @_;
  
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
    confess "Invalid type dimension(first argument of SPVM::ExchangeAPI::new_oarray)";
  }
  unless (defined $basic_type_name) {
    confess "Invalid basic_type name(first argument of SPVM::ExchangeAPI::new_oarray)";
  }
  
  unless (defined $elems) {
    return undef;
  }
  
  # Check second argument
  unless (ref $elems eq 'ARRAY') {
    confess "Second argument of SPVM::new_oarray must be array reference";
  }
  
  if ($type_dimension == 1) {
    SPVM::ExchangeAPI::_new_oarray($env, $basic_type_name, $elems);
  }
  else {
    SPVM::ExchangeAPI::_new_marray($env, $basic_type_name, $type_dimension - 1, $elems);
  }
}

sub new_varray {
  my ($env, $type_name, $elems) = @_;
  
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
    confess "Invalid type dimension(first argument of SPVM::ExchangeAPI::new_varray)";
  }
  unless (defined $basic_type_name) {
    confess "Invalid basic_type name(first argument of SPVM::ExchangeAPI::new_varray)";
  }

  unless (defined $elems) {
    return undef;
  }
  
  # Check second argument
  unless (ref $elems eq 'ARRAY') {
    confess "Second argument of SPVM::new_varray must be array reference";
  }
  
  SPVM::ExchangeAPI::_new_varray($env, $basic_type_name, $elems);
}

sub new_varray_from_bin {
  my ($env, $type_name, $elems) = @_;
  
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
    confess "Invalid type dimension(first argument of SPVM::ExchangeAPI::new_varray_from_bin)";
  }
  unless (defined $basic_type_name) {
    confess "Invalid basic_type name(first argument of SPVM::ExchangeAPI::new_varray_from_bin)";
  }

  unless (defined $elems) {
    return undef;
  }
  
  SPVM::ExchangeAPI::_new_varray_from_bin($env, $basic_type_name, $elems);
}

sub set_exception {
  my ($env, $exception) = @_;
  
  $exception = encode('UTF-8', $exception);
  
  _set_exception($env, $exception);
}

sub get_exception {
  my ($env) = @_;
  
  my $exception = _get_exception($env);
  
  $exception = decode('UTF-8', $exception);
  
  return $exception;
}

# other functions is implemented in SPVM.xs

1;

=head1 NAME

SPVM::ExchangeAPI - SPVM Exchange API

=head1 Functions

=head2 call_sub

=head2 memory_blocks_count

=head2 new_barray

=head2 new_barray_from_bin

=head2 new_barray_from_str

=head2 new_darray

=head2 new_darray_from_bin

=head2 new_farray

=head2 new_farray_from_bin

=head2 new_iarray

=head2 new_iarray_from_bin

=head2 new_larray

=head2 new_larray_from_bin

=head2 new_oarray

=head2 new_sarray

=head2 new_sarray_from_bin

=head2 new_str

=head2 new_str_from_bin

=head2 new_varray

=head2 new_varray_from_bin

=head2 set_exception

=head2 to_bin

=head2 to_elems

=head2 to_str

=head2 to_strs
