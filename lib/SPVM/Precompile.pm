package SPVM::Precompile;

use strict;
use warnings;

sub import {
  my ($class, $package_name) = @_;
  
  # Enable runtime precompile
  push @SPVM::PRECOMPILE_PACKAGE_NAMES, $package_name;
}

1;

=encoding UTF-8

=head1 NAME

SPVM::Precompile - Compile SPVM module to machine code in runtime

=head1 SYNOPSIS

  use SPVM::Precompile 'Point';
