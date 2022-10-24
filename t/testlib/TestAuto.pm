package TestAuto;

use strict;
use warnings;

use FindBin;
use lib "t/testlib";
use File::Find;
use File::Basename 'basename', 'dirname';

sub import {
  my $test_dir;
  if ($FindBin::Bin =~ /t\/builder\b/) {
    $test_dir = 't/builder';
  }
  elsif ($FindBin::Bin =~ /t\/default\b/) {
    $test_dir = 't/default';
  }
  elsif ($FindBin::Bin =~ /t\/precompile\b/) {
    $test_dir = 't/precompile';
    $ENV{SPVM_TEST_PRECOMPILE} = 1;
  }
  elsif ($FindBin::Bin =~ /t\/spvmcc\b/) {
    $test_dir = 't/spvmcc';
  }
  else {
    die "\"$FindBin::Bin\" is an invalid test directory";
  }
  
  my $test_lib_dir = "$test_dir/lib";
  unshift @INC, $test_lib_dir;
  
  $ENV{SPVM_TEST_DIR} = $test_dir;
  $ENV{SPVM_BUILD_DIR} = "$test_dir/.spvm_build";
}

1;
