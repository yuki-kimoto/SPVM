package SPVM::PerlAPI;

use strict;
use warnings;

use Carp 'croak', 'confess';
use Encode 'decode';

sub new_object_array {
  my ($env, $package_name, $elements) = @_;
  
  return undef unless defined $elements;
  
  if (ref $elements ne 'ARRAY') {
    confess "Argument must be array reference";
  }
  
  my $length = @$elements;
  
  my $array = SPVM::PerlAPI::new_object_array_len($env, $package_name, $length);
  
  SPVM::set_array_elements($array, $elements);
  
  return $array;
}

sub new_value_t_array {
  my ($env, $package_name, $elements) = @_;
  
  return undef unless defined $elements;
  
  if (ref $elements ne 'ARRAY') {
    confess "Argument must be array reference";
  }
  
  my $length = @$elements;
  
  my $array = SPVM::PerlAPI::new_value_t_array_len($env, $package_name, $length);

  SPVM::set_array_elements($array, $elements);
  
  return $array;
}

sub new_object {
  my ($env, $package_name) = @_;
  
  my $object = SPVM::Data::Package->new($package_name);
  
  return $object;
}

sub new_byte_array {
  my ($env, $elements) = @_;
  
  return undef unless defined $elements;
  
  if (ref $elements ne 'ARRAY') {
    confess "Argument must be array reference";
  }
  
  my $length = @$elements;
  
  my $array = SPVM::PerlAPI::new_byte_array_len($env, $length);
  
  SPVM::set_array_elements($array, $elements);
  
  return $array;
}

sub new_byte_array_from_binary {
  my ($env, $binary) = @_;
  
  my $length = length $binary;
  
  my $array = SPVM::PerlAPI::new_byte_array_len($env, $length);
  SPVM::set_array_elements_bin($array, $binary);
  
  return $array;
}

sub new_short_array {
  my ($env, $elements) = @_;

  return undef unless defined $elements;

  if (ref $elements ne 'ARRAY') {
    confess "Argument must be array reference";
  }
  
  my $length = @$elements;
  
  my $array = SPVM::PerlAPI::new_short_array_len($env, $length);
  
  SPVM::set_array_elements($array, $elements);
  
  return $array;
}

sub new_short_array_from_binary {
  my ($env, $binary) = @_;
  
  my $length = length $binary;
  
  my $array = SPVM::PerlAPI::new_short_array_len($env, $length);
  SPVM::set_array_elements_bin($array, $binary);
  
  return $array;
}

sub new_int_array {
  my ($env, $elements) = @_;

  return undef unless defined $elements;

  if (ref $elements ne 'ARRAY') {
    confess "Argument must be array reference";
  }
  
  my $length = @$elements;
  
  my $array = SPVM::PerlAPI::new_int_array_len($env, $length);
  
  SPVM::set_array_elements($array, $elements);
  
  return $array;
}

sub new_int_array_from_binary {
  my ($env, $binary) = @_;
  
  my $length = length $binary;
  
  my $array = SPVM::PerlAPI::new_int_array_len($env, $length);
  SPVM::set_array_elements_bin($array, $binary);
  
  return $array;
}

sub new_long_array {
  my ($env, $elements) = @_;

  return undef unless defined $elements;

  if (ref $elements ne 'ARRAY') {
    confess "Argument must be array reference";
  }
  
  my $length = @$elements;
  
  my $array = SPVM::PerlAPI::new_long_array_len($env, $length);
  
  SPVM::set_array_elements($array, $elements);
  
  return $array;
}

sub new_long_array_from_binary {
  my ($env, $binary) = @_;
  
  my $length = length $binary;
  
  my $array = SPVM::PerlAPI::new_long_array_len($env, $length);
  SPVM::set_array_elements_bin($array, $binary);
  
  return $array;
}

sub new_float_array {
  my ($env, $elements) = @_;

  return undef unless defined $elements;

  if (ref $elements ne 'ARRAY') {
    confess "Argument must be array reference";
  }
  
  my $length = @$elements;
  
  my $array = SPVM::PerlAPI::new_float_array_len($env, $length);
  
  SPVM::set_array_elements($array, $elements);
  
  return $array;
}

sub new_float_array_from_binary {
  my ($env, $binary) = @_;
  
  my $length = length $binary;
  
  my $array = SPVM::PerlAPI::new_float_array_len($env, $length);
  SPVM::set_array_elements_bin($array, $binary);
  
  return $array;
}

sub new_double_array {
  my ($env, $elements) = @_;
  
  return undef unless defined $elements;
  
  if (ref $elements ne 'ARRAY') {
    confess "Argument must be array reference";
  }
  
  my $length = @$elements;
  
  my $array = SPVM::PerlAPI::new_double_array_len($env, $length);
  
  SPVM::set_array_elements($array, $elements);
  
  return $array;
}

sub new_double_array_from_binary {
  my ($env, $binary) = @_;
  
  my $length = length $binary;
  
  my $array = SPVM::PerlAPI::new_double_array_len($env, $length);
  SPVM::set_array_elements_bin($array, $binary);
  
  return $array;
}

sub get_array_elements_string {
  my ($env, $array) = @_;
  
  my $bin = SPVM::get_array_elements_bin($array);
  
  my $string = decode('UTF-8', $bin);
  
  return $string;
}


1;
