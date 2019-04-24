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

sub new_str {
  my ($env, $string) = @_;
  
  my $bin = encode('UTF-8', $string);

  return SPVM::ExchangeAPI::new_str_from_bin($env, $bin);
}


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
  
  SPVM::ExchangeAPI::_new_varray_from_bin($env, $basic_type_name, $elems);
}

sub hash {
  my ($env, $hash) = @_;
  
  my $spvm_hash = SPVM::Hash->new;
  for my $key (%$hash) {
    my $value = $hash->{$key};
    $spvm_hash->set($key => $value);
  }
}

sub list {
  my ($env, $list) = @_;
  
  my $spvm_list = SPVM::List->new;
  for my $value (@$list) {
    $spvm_list->push($value);
  }
}

# other functions is implemented in SPVM.xs

1;

=head1 NAME

SPVM::ExchangeAPI - Base class of Exchange API

