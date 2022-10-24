package TestAuto;

use strict;
use warnings;

use FindBin;
use lib "t/testlib";
use File::Find;
use File::Basename 'basename', 'dirname';

sub import {
  my $test_dir;

  my $test_dir_builder_base = '00_builder';
  my $test_dir_syntax_base = '01_syntax';
  my $test_dir_vm_base = '02_vm';
  my $test_dir_precompile_base = '03_precompile';
  my $test_dir_spvmcc_base = '04_spvmcc';
  my $test_dir_spvmdist_base = '05_spvmdist';

  $ENV{SPVM_TEST_DIR_BUILDER_BASE} = $test_dir_builder_base;
  $ENV{SPVM_TEST_DIR_SYNTAX_BASE} = $test_dir_syntax_base;
  $ENV{SPVM_TEST_DIR_VM_BASE} = $test_dir_vm_base;
  $ENV{SPVM_TEST_DIR_PRECOMPILE_BASE} = $test_dir_precompile_base;
  $ENV{SPVM_TEST_DIR_SPVMCC_BASE} = $test_dir_spvmcc_base;
  $ENV{SPVM_TEST_DIR_SPVMDIST_BASE} = $test_dir_spvmdist_base;

  my $test_dir_builder = "t/$test_dir_builder_base";
  my $test_dir_syntax = "t/$test_dir_syntax_base";
  my $test_dir_vm = "t/$test_dir_vm_base";
  my $test_dir_precompile = "t/$test_dir_precompile_base";
  my $test_dir_spvmcc = "t/$test_dir_spvmcc_base";
  my $test_dir_spvmdist = "t/$test_dir_spvmdist_base";

  $ENV{SPVM_TEST_DIR_BUILDER} = $test_dir_builder;
  $ENV{SPVM_TEST_DIR_SYNTAX} = $test_dir_syntax;
  $ENV{SPVM_TEST_DIR_VM} = $test_dir_vm;
  $ENV{SPVM_TEST_DIR_PRECOMPILE} = $test_dir_precompile;
  $ENV{SPVM_TEST_DIR_SPVMCC} = $test_dir_spvmcc;
  $ENV{SPVM_TEST_DIR_SPVMDIST} = $test_dir_spvmdist;
  
  if ($FindBin::Bin =~ /t\/$test_dir_builder_base\b/) {
    $test_dir = $test_dir_builder;
  }
  elsif ($FindBin::Bin =~ /t\/$test_dir_syntax_base\b/) {
    $test_dir = $test_dir_syntax;
  }
  elsif ($FindBin::Bin =~ /t\/$test_dir_vm_base\b/) {
    $test_dir = $test_dir_vm;
  }
  elsif ($FindBin::Bin =~ /t\/$test_dir_precompile_base\b/) {
    $test_dir = $test_dir_precompile;
    $ENV{SPVM_TEST_PRECOMPILE} = 1;
  }
  elsif ($FindBin::Bin =~ /t\/$test_dir_spvmcc_base\b/) {
    $test_dir = $test_dir_spvmcc;
  }
  elsif ($FindBin::Bin =~ /t\/$test_dir_spvmdist_base\b/) {
    $test_dir = $test_dir_spvmdist;
  }
  elsif ($FindBin::Bin =~ /t\/utils\b/) {
    $test_dir = 't/utils';
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
