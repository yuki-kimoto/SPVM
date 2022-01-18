use lib "t/lib";
use TestAuto;

use strict;
use warnings;
use Config;

use Test::More;

use FindBin;

my $compile_native_api_prgoram = "$^X -Mblib $FindBin::Bin/compile_native_api.pl";

my $config_file = "$FindBin::Bin/lib/SPVM/TestCase/NativeAPI.config";
unless (-f $config_file) {
  die "Can't find file \"$config_file\"";
}

system($compile_native_api_prgoram) == 0 or die;

# Native object files and shared library files is cached.
{
  my $native_object_file;
  my $start_native_object_file_mtime;
  $native_object_file = "$FindBin::Bin/.spvm_build/work/object/SPVM/TestCase/NativeAPI.o";
  $start_native_object_file_mtime = (stat $native_object_file)[9];

  my $precompile_object_file;
  my $start_precompile_object_file_mtime;
  $precompile_object_file = "$FindBin::Bin/.spvm_build/work/object/SPVM/TestCase/NativeAPI.precompile.o";
  if ($ENV{SPVM_TEST_PRECOMPILE}) {
   ok(-f $precompile_object_file);
   $start_precompile_object_file_mtime = (stat $precompile_object_file)[9];
  }

  my $native_shared_lib_file;
  my $start_native_shared_lib_file_mtime;
   $native_shared_lib_file = "$FindBin::Bin/.spvm_build/work/lib/SPVM/TestCase/NativeAPI.$Config{dlext}";
   $start_native_shared_lib_file_mtime = (stat $native_shared_lib_file)[9];

  my $precompile_shared_lib_file;
  my $start_precompile_shared_lib_file_mtime;
   $precompile_shared_lib_file = "$FindBin::Bin/.spvm_build/work/lib/SPVM/TestCase/NativeAPI.precompile.$Config{dlext}";
   if ($ENV{SPVM_TEST_PRECOMPILE}) {
     ok(-f $precompile_shared_lib_file);
     $start_precompile_shared_lib_file_mtime = (stat $precompile_shared_lib_file)[9];
   }

  # Just before this test, native_api.t must be run.
  system($compile_native_api_prgoram) == 0 or die;

  # Naative object file is cached
  my $native_object_file_mtime = (stat $native_object_file)[9];
  is($native_object_file_mtime, $start_native_object_file_mtime);

  my $precompile_object_file_mtime = (stat $precompile_object_file)[9];
  if ($ENV{SPVM_TEST_PRECOMPILE}) {
    is($precompile_object_file_mtime, $start_precompile_object_file_mtime);
  }

  # Naative shared_lib file is cached
  my $native_shared_lib_file_mtime = (stat $native_shared_lib_file)[9];
  is($native_shared_lib_file_mtime, $start_native_shared_lib_file_mtime);

  my $precompile_shared_lib_file_mtime = (stat $precompile_shared_lib_file)[9];
  if ($ENV{SPVM_TEST_PRECOMPILE}) {
    is($precompile_shared_lib_file_mtime, $start_precompile_shared_lib_file_mtime);
  }
}

# Update native config files
{
  my $native_object_file;
  my $start_native_object_file_mtime;
  $native_object_file = "$FindBin::Bin/.spvm_build/work/object/SPVM/TestCase/NativeAPI.o";
  $start_native_object_file_mtime = (stat $native_object_file)[9];

  my $native_shared_lib_file;
  my $start_native_shared_lib_file_mtime;
   $native_shared_lib_file = "$FindBin::Bin/.spvm_build/work/lib/SPVM/TestCase/NativeAPI.$Config{dlext}";
   $start_native_shared_lib_file_mtime = (stat $native_shared_lib_file)[9];

  # Update mtime of config file and compile
  my $cur_time = time;
  utime $cur_time, $cur_time, $config_file or die;
  system($compile_native_api_prgoram) == 0 or die;

  # Naative object file is recompiled
  my $native_object_file_mtime = (stat $native_object_file)[9];
  isnt($native_object_file_mtime, $start_native_object_file_mtime);

  # Naative shared_lib file is recompiled
  my $native_shared_lib_file_mtime = (stat $native_shared_lib_file)[9];
  isnt($native_shared_lib_file_mtime, $start_native_shared_lib_file_mtime);
}

done_testing;
