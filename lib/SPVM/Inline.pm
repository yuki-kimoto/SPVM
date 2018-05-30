package SPVM::Inline;

use strict;
use warnings;

sub import {
  my ($class, $package_name) = @_;
  
  # Enable runtime Inline compile
  push @SPVM::INLINE_PACKAGE_NAMES, $package_name;
}

1;

=encoding UTF-8

=head1 NAME

SPVM::Inline - Compile native subroutines in runtime

=head1 SYNOPSIS

  use SPVM::Inline 'Point';
