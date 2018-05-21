package SPVM::JIT;

use 5.008007;
use strict;
use warnings;

use SPVM;

sub import {
  my ($class, $package_name) = @_;
  
  # Enable runtime JIT compile
  push @SPVM::JIT_MODULES, $package_name;
}

1;

=encoding UTF-8

=head1 NAME

SPVM::JIT - Compile SPVM module to machine code in runtime

=head1 SYNOPSIS

  use SPVM::JIT 'Point';

=head1 COPYRIGHT AND LICENSE

Copyright (C) 2017-2018 by Yuki Kimoto

MIT License

=cut
