use lib "t/lib";
use TestAuto;

use strict;
use warnings;
use Config;

use Test::More;
use Time::HiRes 'sleep';

use FindBin;

my $build_dir = $ENV{SPVM_BUILD_DIR};

# Wait 2 seconds because the time in 1 secend is not detected.
my $wait_time = 1.1;

my $compile_native_api_prgoram = "$^X -Mblib $FindBin::Bin/compile_native_api.pl";

my $module_file = "$FindBin::Bin/lib/SPVM/TestCase/NativeAPI.spvm";
unless (-f $module_file) {
  die 'Unexpected error';
}

my $config_file = "$FindBin::Bin/lib/SPVM/TestCase/NativeAPI.config";
unless (-f $config_file) {
  die 'Unexpected error';
}

my $native_module_file = "$FindBin::Bin/lib/SPVM/TestCase/NativeAPI2.c";
unless (-f $native_module_file) {
  die 'Unexpected error';
}

my $native_header_file = "$FindBin::Bin/lib/SPVM/TestCase/NativeAPI2.native/include/baz/baz.h";
unless (-f $native_header_file) {
  die 'Unexpected error';
}

my $native_src_file = "$FindBin::Bin/lib/SPVM/TestCase/NativeAPI2.native/src/baz/baz.c";
unless (-f $native_src_file) {
  die 'Unexpected error';
}

system($compile_native_api_prgoram) == 0 or die;

# Native object files and shared library files is cached.
{
  my $native_object_file;
  my $start_native_object_file_mtime;
  $native_object_file = "$build_dir/work/object/SPVM/TestCase/NativeAPI.o";
  $start_native_object_file_mtime = (stat $native_object_file)[9];

  my $precompile_object_file;
  my $start_precompile_object_file_mtime;
  $precompile_object_file = "$build_dir/work/object/SPVM/TestCase/NativeAPI.precompile.o";
  if ($ENV{SPVM_TEST_PRECOMPILE}) {
   ok(-f $precompile_object_file);
   $start_precompile_object_file_mtime = (stat $precompile_object_file)[9];
  }

  my $native_shared_lib_file;
  my $start_native_shared_lib_file_mtime;
   $native_shared_lib_file = "$build_dir/work/lib/SPVM/TestCase/NativeAPI.$Config{dlext}";
   $start_native_shared_lib_file_mtime = (stat $native_shared_lib_file)[9];

  my $precompile_shared_lib_file;
  my $start_precompile_shared_lib_file_mtime;
   $precompile_shared_lib_file = "$build_dir/work/lib/SPVM/TestCase/NativeAPI.precompile.$Config{dlext}";
   if ($ENV{SPVM_TEST_PRECOMPILE}) {
     ok(-f $precompile_shared_lib_file);
     $start_precompile_shared_lib_file_mtime = (stat $precompile_shared_lib_file)[9];
   }

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

# Update config file
{
  my $native_object_file;
  my $start_native_object_file_mtime;
  $native_object_file = "$build_dir/work/object/SPVM/TestCase/NativeAPI.o";
  $start_native_object_file_mtime = (stat $native_object_file)[9];

  my $native_shared_lib_file;
  my $start_native_shared_lib_file_mtime;
   $native_shared_lib_file = "$build_dir/work/lib/SPVM/TestCase/NativeAPI.$Config{dlext}";
   $start_native_shared_lib_file_mtime = (stat $native_shared_lib_file)[9];

  # Update config file
  sleep $wait_time;
  my $now = time;
  utime $now, $now, $config_file;
  system($compile_native_api_prgoram) == 0 or die;

  # Naative object file is cached
  my $native_object_file_mtime = (stat $native_object_file)[9];
  isnt($native_object_file_mtime, $start_native_object_file_mtime);

  # Naative shared_lib file is cached
  my $native_shared_lib_file_mtime = (stat $native_shared_lib_file)[9];
  isnt($native_shared_lib_file_mtime, $start_native_shared_lib_file_mtime);
}

# Update module file
{
  my $native_object_file;
  my $start_native_object_file_mtime;
  $native_object_file = "$build_dir/work/object/SPVM/TestCase/NativeAPI.o";
  $start_native_object_file_mtime = (stat $native_object_file)[9];

  my $precompile_object_file;
  my $start_precompile_object_file_mtime;
  $precompile_object_file = "$build_dir/work/object/SPVM/TestCase/NativeAPI.precompile.o";
  if ($ENV{SPVM_TEST_PRECOMPILE}) {
   ok(-f $precompile_object_file);
   $start_precompile_object_file_mtime = (stat $precompile_object_file)[9];
  }

  my $native_shared_lib_file;
  my $start_native_shared_lib_file_mtime;
   $native_shared_lib_file = "$build_dir/work/lib/SPVM/TestCase/NativeAPI.$Config{dlext}";
   $start_native_shared_lib_file_mtime = (stat $native_shared_lib_file)[9];

  my $precompile_shared_lib_file;
  my $start_precompile_shared_lib_file_mtime;
   $precompile_shared_lib_file = "$build_dir/work/lib/SPVM/TestCase/NativeAPI.precompile.$Config{dlext}";
   if ($ENV{SPVM_TEST_PRECOMPILE}) {
     ok(-f $precompile_shared_lib_file);
     $start_precompile_shared_lib_file_mtime = (stat $precompile_shared_lib_file)[9];
   }

  # Update module file
  sleep $wait_time;
  my $now = time;
  utime $now, $now, $module_file;
  system($compile_native_api_prgoram) == 0 or die;

  # Naative object file is cached
  my $native_object_file_mtime = (stat $native_object_file)[9];
  isnt($native_object_file_mtime, $start_native_object_file_mtime);

  my $precompile_object_file_mtime = (stat $precompile_object_file)[9];
  if ($ENV{SPVM_TEST_PRECOMPILE}) {
    isnt($precompile_object_file_mtime, $start_precompile_object_file_mtime);
  }

  # Naative shared_lib file is cached
  my $native_shared_lib_file_mtime = (stat $native_shared_lib_file)[9];
  isnt($native_shared_lib_file_mtime, $start_native_shared_lib_file_mtime);

  my $precompile_shared_lib_file_mtime = (stat $precompile_shared_lib_file)[9];
  if ($ENV{SPVM_TEST_PRECOMPILE}) {
    isnt($precompile_shared_lib_file_mtime, $start_precompile_shared_lib_file_mtime);
  }
}

# Update native module file
{
  my $native_object_file;
  my $start_native_object_file_mtime;
  $native_object_file = "$build_dir/work/object/SPVM/TestCase/NativeAPI2.o";
  $start_native_object_file_mtime = (stat $native_object_file)[9];

  my $native_shared_lib_file;
  my $start_native_shared_lib_file_mtime;
   $native_shared_lib_file = "$build_dir/work/lib/SPVM/TestCase/NativeAPI2.$Config{dlext}";
   $start_native_shared_lib_file_mtime = (stat $native_shared_lib_file)[9];

  # Update src file
  sleep $wait_time;
  my $now = time;
  utime $now, $now, $native_module_file;
  system($compile_native_api_prgoram) == 0 or die;

  # Native object file is cached
  my $native_object_file_mtime = (stat $native_object_file)[9];
  isnt($native_object_file_mtime, $start_native_object_file_mtime);
  
  # Naative shared_lib file is cached
  my $native_shared_lib_file_mtime = (stat $native_shared_lib_file)[9];
  isnt($native_shared_lib_file_mtime, $start_native_shared_lib_file_mtime);
}

# Update native src file
{
  my $native_src_object_file;
  my $start_native_src_object_file_mtime;
  $native_src_object_file = "$build_dir/work/object/SPVM/TestCase/NativeAPI2.native/baz/baz.o";
  $start_native_src_object_file_mtime = (stat $native_src_object_file)[9];

  my $native_shared_lib_file;
  my $start_native_shared_lib_file_mtime;
   $native_shared_lib_file = "$build_dir/work/lib/SPVM/TestCase/NativeAPI2.$Config{dlext}";
   $start_native_shared_lib_file_mtime = (stat $native_shared_lib_file)[9];

  # Update src file
  sleep $wait_time;
  my $now = time;
  utime $now, $now, $native_src_file;
  system($compile_native_api_prgoram) == 0 or die;

  # Native object file is cached
  my $native_src_object_file_mtime = (stat $native_src_object_file)[9];
  isnt($native_src_object_file_mtime, $start_native_src_object_file_mtime);
  
  # Naative shared_lib file is cached
  my $native_shared_lib_file_mtime = (stat $native_shared_lib_file)[9];
  isnt($native_shared_lib_file_mtime, $start_native_shared_lib_file_mtime);
}

# Update native header file
{

  my $native_object_file;
  my $start_native_object_file_mtime;
  $native_object_file = "$build_dir/work/object/SPVM/TestCase/NativeAPI2.o";
  $start_native_object_file_mtime = (stat $native_object_file)[9];

  my $native_src_object_file;
  my $start_native_src_object_file_mtime;
  $native_src_object_file = "$build_dir/work/object/SPVM/TestCase/NativeAPI2.native/baz/baz.o";
  $start_native_src_object_file_mtime = (stat $native_src_object_file)[9];

  my $native_shared_lib_file;
  my $start_native_shared_lib_file_mtime;
   $native_shared_lib_file = "$build_dir/work/lib/SPVM/TestCase/NativeAPI2.$Config{dlext}";
   $start_native_shared_lib_file_mtime = (stat $native_shared_lib_file)[9];

  # Update src file
  sleep $wait_time;
  my $now = time;
  utime $now, $now, $native_header_file;
  system($compile_native_api_prgoram) == 0 or die;

  # Native object file is cached
  my $native_object_file_mtime = (stat $native_object_file)[9];
  isnt($native_object_file_mtime, $start_native_object_file_mtime);

  # Native object file is cached
  my $native_src_object_file_mtime = (stat $native_src_object_file)[9];
  isnt($native_src_object_file_mtime, $start_native_src_object_file_mtime);
  
  # Naative shared_lib file is cached
  my $native_shared_lib_file_mtime = (stat $native_shared_lib_file)[9];
  isnt($native_shared_lib_file_mtime, $start_native_shared_lib_file_mtime);
}

# Config force option
{

  my $native_object_file;
  my $start_native_object_file_mtime;
  $native_object_file = "$build_dir/work/object/SPVM/TestCase/NativeAPI2.o";
  $start_native_object_file_mtime = (stat $native_object_file)[9];

  my $native_src_object_file;
  my $start_native_src_object_file_mtime;
  $native_src_object_file = "$build_dir/work/object/SPVM/TestCase/NativeAPI2.native/baz/baz.o";
  $start_native_src_object_file_mtime = (stat $native_src_object_file)[9];

  my $native_shared_lib_file;
  my $start_native_shared_lib_file_mtime;
   $native_shared_lib_file = "$build_dir/work/lib/SPVM/TestCase/NativeAPI2.$Config{dlext}";
   $start_native_shared_lib_file_mtime = (stat $native_shared_lib_file)[9];

  # Update src file
  sleep $wait_time;
  $ENV{SPVM_TEST_CONFIG_FORCE} = 1;
  system($compile_native_api_prgoram) == 0 or die;

  # Native object file is cached
  my $native_object_file_mtime = (stat $native_object_file)[9];
  isnt($native_object_file_mtime, $start_native_object_file_mtime);

  # Native object file is cached
  my $native_src_object_file_mtime = (stat $native_src_object_file)[9];
  isnt($native_src_object_file_mtime, $start_native_src_object_file_mtime);
  
  # Naative shared_lib file is cached
  my $native_shared_lib_file_mtime = (stat $native_shared_lib_file)[9];
  isnt($native_shared_lib_file_mtime, $start_native_shared_lib_file_mtime);
}

# SPVM_CC_FORCE environment variable
{

  my $native_object_file;
  my $start_native_object_file_mtime;
  $native_object_file = "$build_dir/work/object/SPVM/TestCase/NativeAPI2.o";
  $start_native_object_file_mtime = (stat $native_object_file)[9];

  my $native_src_object_file;
  my $start_native_src_object_file_mtime;
  $native_src_object_file = "$build_dir/work/object/SPVM/TestCase/NativeAPI2.native/baz/baz.o";
  $start_native_src_object_file_mtime = (stat $native_src_object_file)[9];

  my $native_shared_lib_file;
  my $start_native_shared_lib_file_mtime;
   $native_shared_lib_file = "$build_dir/work/lib/SPVM/TestCase/NativeAPI2.$Config{dlext}";
   $start_native_shared_lib_file_mtime = (stat $native_shared_lib_file)[9];

  # Update src file
  sleep $wait_time;
  $ENV{SPVM_CC_FORCE} = 1;
  system($compile_native_api_prgoram) == 0 or die;

  # Native object file is cached
  my $native_object_file_mtime = (stat $native_object_file)[9];
  isnt($native_object_file_mtime, $start_native_object_file_mtime);

  # Native object file is cached
  my $native_src_object_file_mtime = (stat $native_src_object_file)[9];
  isnt($native_src_object_file_mtime, $start_native_src_object_file_mtime);
  
  # Naative shared_lib file is cached
  my $native_shared_lib_file_mtime = (stat $native_shared_lib_file)[9];
  isnt($native_shared_lib_file_mtime, $start_native_shared_lib_file_mtime);
}

done_testing;
