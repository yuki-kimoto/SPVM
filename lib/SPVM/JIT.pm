package SPVM::JIT;

use strict;
use warnings;

sub import {
  my ($class, $package_name) = @_;
  
  # Enable runtime JIT compile
  push @SPVM::JIT_PACKAGE_NAMES, $package_name;
}

1;

=encoding UTF-8

=head1 NAME

SPVM::JIT - Compile SPVM module to machine code in runtime

=head1 SYNOPSIS

  use SPVM::JIT 'Point';
