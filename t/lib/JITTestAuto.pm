package JITTestAuto;

use strict;
use warnings;

use FindBin;

sub import {
  
  if ($FindBin::Bin =~ /\/jit$/) {
    $ENV{SPVM_JIT_COUNT} = 1;
  }
}

1;

=pod

=DESCRITPION

if test scritp file is in jit directory, jit test is automatically on.
