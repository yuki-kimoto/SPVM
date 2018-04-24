package SPVM::EnableJIT;

use strict;
use warnings;

sub import {
  $ENV{SPVM_ENABLE_JIT} = 1;
}

1;
