package JITTestAuto;

use strict;
use warnings;

use FindBin;
use lib "t/lib";

sub import {
  if ($FindBin::Bin =~ /\/jit$/) {
    $ENV{SPVM_TEST_LIB_DIR} = "t/jit/lib";
    $ENV{SPVM_ENABLE_JIT} = 1;
    $ENV{SPVM_BUILD_DIR} = 'spvm_build';
    push @INC, $ENV{SPVM_TEST_LIB_DIR};
  }
  else {
    $ENV{SPVM_TEST_LIB_DIR} = "t/default/lib";
    $ENV{SPVM_BUILD_DIR} = 'spvm_build';
    push @INC, $ENV{SPVM_TEST_LIB_DIR};
  }
}

1;

=pod

=DESCRITPION

if test scritp file is in jit directory, jit test is automatically on.
