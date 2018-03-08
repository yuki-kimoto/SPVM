package JITTestAuto;

use strict;
use warnings;

use FindBin;
use lib "t/lib";

sub import {
  if ($FindBin::Bin =~ /\/jit$/) {
    $ENV{SPVM_JIT_MODE} = 'all';
    push @INC, "t/jit/lib"
  }
  else {
    push @INC, "t/default/lib"
  }
}

1;

=pod

=DESCRITPION

if test scritp file is in jit directory, jit test is automatically on.
