package SPVM::Native;

use strict;
use warnings;

sub import {
  my ($class, $package_name) = @_;
  
  # Enable runtime Native compile
  push @SPVM::NATIVE_PACKAGE_NAMES, $package_name;
}

1;

=encoding UTF-8

=head1 NAME

SPVM::Native - Compile native subroutines in runtime

=head1 SYNOPSIS

  use SPVM::Native 'Point';
