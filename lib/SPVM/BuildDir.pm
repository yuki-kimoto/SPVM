package SPVM::BuildDir;

use strict;
use warnings;

sub import {
  $ENV{SPVM_BUILD_DIR} = shift;
}

1;
