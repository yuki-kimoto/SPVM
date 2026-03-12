package TestAuto;

use strict;
use warnings;

use FindBin;
use File::Temp;

my $BUILD_DIR;
sub import {
  my $test_dir;

  my $test_dir_vm_base = '02_vm';
  my $test_dir_precompile_base = '03_precompile';

  my $test_dir_vm = "t/$test_dir_vm_base";
  my $test_dir_precompile = "t/$test_dir_precompile_base";

  if ($FindBin::Bin =~ /t\/$test_dir_vm_base\b/) {
    $test_dir = $test_dir_vm;
  }
  elsif ($FindBin::Bin =~ /t\/$test_dir_precompile_base\b/) {
    $test_dir = $test_dir_precompile;
  }
  
  unless ($test_dir) {
    $test_dir = $BUILD_DIR = File::Temp->newdir;
  }
  
  $ENV{SPVM_BUILD_DIR} = "$test_dir/.spvm_build";
}

1;
