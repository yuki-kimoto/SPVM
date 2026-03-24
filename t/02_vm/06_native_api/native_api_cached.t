use lib "t/lib";
use TestAuto;
use TestUtil::MyLib;

use strict;
use warnings;
use Config;

use FindBin;

use Test::More;

use SPVM;

my $test_dir = "$FindBin::Bin/..";
my $build_dir = $ENV{SPVM_BUILD_DIR};

my $compile_native_api_prgoram = "$^X -Mblib $FindBin::Bin/compile_native_api.pl";

my $class_file = "$test_dir/lib/SPVM/TestCase/NativeAPI.spvm";
unless (-f $class_file) {
  die 'Unexpected error';
}

my $config_file = "$test_dir/lib/SPVM/TestCase/NativeAPI.config";
unless (-f $config_file) {
  die 'Unexpected error';
}

my $native_class_file = "$test_dir/lib/SPVM/TestCase/NativeAPISrc.c";
unless (-f $native_class_file) {
  die 'Unexpected error';
}

my $native_header_file = "$test_dir/lib/SPVM/TestCase/NativeAPISrc.native/include/baz/baz.h";
unless (-f $native_header_file) {
  die 'Unexpected error';
}

my $resource_config_file = "$test_dir/lib/SPVM/TestCase/Resource/Mylib1.config";
unless (-f $resource_config_file) {
  die 'Unexpected error';
}

my $resource_native_header_file = "$test_dir/lib/SPVM/TestCase/Resource/Mylib1.native/include/mylib1_source1.h";
unless (-f $resource_native_header_file) {
  die 'Unexpected error';
}

my $native_src_file = "$test_dir/lib/SPVM/TestCase/NativeAPISrc.native/src/baz/baz.c";
unless (-f $native_src_file) {
  die 'Unexpected error';
}

ok(-f "$ENV{SPVM_BUILD_DIR}/.ninja_log");

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

  # Native object file is cached
  my $native_object_file_mtime = (stat $native_object_file)[9];
  is($native_object_file_mtime, $start_native_object_file_mtime);

  my $precompile_object_file_mtime = (stat $precompile_object_file)[9];
  if ($ENV{SPVM_TEST_PRECOMPILE}) {
    is($precompile_object_file_mtime, $start_precompile_object_file_mtime);
  }

  # Native shared_lib file is cached
  my $native_shared_lib_file_mtime = (stat $native_shared_lib_file)[9];
  is($native_shared_lib_file_mtime, $start_native_shared_lib_file_mtime);

  my $precompile_shared_lib_file_mtime = (stat $precompile_shared_lib_file)[9];
  if ($ENV{SPVM_TEST_PRECOMPILE}) {
    is($precompile_shared_lib_file_mtime, $start_precompile_shared_lib_file_mtime);
  }
}

=pod TODO

# Update native class file
{
  my $native_object_file;
  my $start_native_object_file_mtime;
  $native_object_file = "$build_dir/work/object/SPVM/TestCase/NativeAPISrc.o";
  $start_native_object_file_mtime = (stat $native_object_file)[9];

  my $native_shared_lib_file;
  my $start_native_shared_lib_file_mtime;
   $native_shared_lib_file = "$build_dir/work/lib/SPVM/TestCase/NativeAPISrc.$Config{dlext}";
   $start_native_shared_lib_file_mtime = (stat $native_shared_lib_file)[9];

  # Update src file
  my $now = time;
  system($compile_native_api_prgoram) == 0 or die;

  # Native object file is compiled
  my $native_object_file_mtime = (stat $native_object_file)[9];
  isnt($native_object_file_mtime, $start_native_object_file_mtime);
  
  # Native shared_lib file is linked
  my $native_shared_lib_file_mtime = (stat $native_shared_lib_file)[9];
  isnt($native_shared_lib_file_mtime, $start_native_shared_lib_file_mtime);
}

# Update native src file
{
  my $native_src_object_file;
  my $start_native_src_object_file_mtime;
  $native_src_object_file = "$build_dir/work/object/SPVM/TestCase/NativeAPISrc.native/baz/baz.o";
  $start_native_src_object_file_mtime = (stat $native_src_object_file)[9];
  
  my $native_shared_lib_file;
  my $start_native_shared_lib_file_mtime;
  $native_shared_lib_file = "$build_dir/work/lib/SPVM/TestCase/NativeAPISrc.$Config{dlext}";
  $start_native_shared_lib_file_mtime = (stat $native_shared_lib_file)[9];
  
  # Update src file
  my $now = time;
  system($compile_native_api_prgoram) == 0 or die;
  
  # Native object file is cached
  my $native_src_object_file_mtime = (stat $native_src_object_file)[9];
  isnt($native_src_object_file_mtime, $start_native_src_object_file_mtime);
  
  # Native shared_lib file is cached
  my $native_shared_lib_file_mtime = (stat $native_shared_lib_file)[9];
  isnt($native_shared_lib_file_mtime, $start_native_shared_lib_file_mtime);
}

# Update native header file
{
  my $native_object_file;
  my $start_native_object_file_mtime;
  $native_object_file = "$build_dir/work/object/SPVM/TestCase/NativeAPISrc.o";
  $start_native_object_file_mtime = (stat $native_object_file)[9];
  
  my $native_src_object_file;
  my $start_native_src_object_file_mtime;
  $native_src_object_file = "$build_dir/work/object/SPVM/TestCase/NativeAPISrc.native/baz/baz.o";
  $start_native_src_object_file_mtime = (stat $native_src_object_file)[9];
  
  my $native_shared_lib_file;
  my $start_native_shared_lib_file_mtime;
  $native_shared_lib_file = "$build_dir/work/lib/SPVM/TestCase/NativeAPISrc.$Config{dlext}";
  $start_native_shared_lib_file_mtime = (stat $native_shared_lib_file)[9];
  
  # Update src file
  my $now = time;
  system($compile_native_api_prgoram) == 0 or die;
  
  # Native class object file is cached
  my $native_object_file_mtime = (stat $native_object_file)[9];
  isnt($native_object_file_mtime, $start_native_object_file_mtime);
  
  # Native object file is cached
  my $native_src_object_file_mtime = (stat $native_src_object_file)[9];
  isnt($native_src_object_file_mtime, $start_native_src_object_file_mtime);
  
  # Native shared_lib file is cached
  my $native_shared_lib_file_mtime = (stat $native_shared_lib_file)[9];
  isnt($native_shared_lib_file_mtime, $start_native_shared_lib_file_mtime);
}

# Update resource native header file
{
  my $native_object_file;
  my $start_native_object_file_mtime;
  $native_object_file = "$build_dir/work/object/SPVM/TestCase/NativeAPISrc.o";
  $start_native_object_file_mtime = (stat $native_object_file)[9];
  
  my $native_shared_lib_file;
  my $start_native_shared_lib_file_mtime;
  $native_shared_lib_file = "$build_dir/work/lib/SPVM/TestCase/NativeAPISrc.$Config{dlext}";
  $start_native_shared_lib_file_mtime = (stat $native_shared_lib_file)[9];
  
  # Update src file
  my $now = time;
  system($compile_native_api_prgoram) == 0 or die;
  
  # Native class object file is cached
  my $native_object_file_mtime = (stat $native_object_file)[9];
  isnt($native_object_file_mtime, $start_native_object_file_mtime);
  
  # Native shared_lib file is cached
  my $native_shared_lib_file_mtime = (stat $native_shared_lib_file)[9];
  isnt($native_shared_lib_file_mtime, $start_native_shared_lib_file_mtime);
}

# Config force option
{

  my $native_object_file;
  my $start_native_object_file_mtime;
  $native_object_file = "$build_dir/work/object/SPVM/TestCase/NativeAPISrc.o";
  $start_native_object_file_mtime = (stat $native_object_file)[9];

  my $native_src_object_file;
  my $start_native_src_object_file_mtime;
  $native_src_object_file = "$build_dir/work/object/SPVM/TestCase/NativeAPISrc.native/baz/baz.o";
  $start_native_src_object_file_mtime = (stat $native_src_object_file)[9];

  my $native_shared_lib_file;
  my $start_native_shared_lib_file_mtime;
   $native_shared_lib_file = "$build_dir/work/lib/SPVM/TestCase/NativeAPISrc.$Config{dlext}";
   $start_native_shared_lib_file_mtime = (stat $native_shared_lib_file)[9];

  # Update src file
  $ENV{SPVM_TEST_CONFIG_FORCE} = 1;
  system($compile_native_api_prgoram) == 0 or die;

  # Native object file is cached
  my $native_object_file_mtime = (stat $native_object_file)[9];
  isnt($native_object_file_mtime, $start_native_object_file_mtime);

  # Native object file is cached
  my $native_src_object_file_mtime = (stat $native_src_object_file)[9];
  isnt($native_src_object_file_mtime, $start_native_src_object_file_mtime);
  
  # Native shared_lib file is cached
  my $native_shared_lib_file_mtime = (stat $native_shared_lib_file)[9];
  isnt($native_shared_lib_file_mtime, $start_native_shared_lib_file_mtime);
}

=cut

# SPVM_CC_FORCE environment variable
{

  my $native_object_file;
  my $start_native_object_file_mtime;
  $native_object_file = "$build_dir/work/object/SPVM/TestCase/NativeAPISrc.o";
  $start_native_object_file_mtime = (stat $native_object_file)[9];

  my $native_src_object_file;
  my $start_native_src_object_file_mtime;
  $native_src_object_file = "$build_dir/work/object/SPVM/TestCase/NativeAPISrc.native/src/baz/baz.o";
  $start_native_src_object_file_mtime = (stat $native_src_object_file)[9];

  my $native_shared_lib_file;
  my $start_native_shared_lib_file_mtime;
   $native_shared_lib_file = "$build_dir/work/lib/SPVM/TestCase/NativeAPISrc.$Config{dlext}";
   $start_native_shared_lib_file_mtime = (stat $native_shared_lib_file)[9];

  # Update src file
  $ENV{SPVM_CC_FORCE} = 1;
  system($compile_native_api_prgoram) == 0 or die;

  # Native object file is cached
  my $native_object_file_mtime = (stat $native_object_file)[9];
  isnt($native_object_file_mtime, $start_native_object_file_mtime);

  # Native object file is cached
  my $native_src_object_file_mtime = (stat $native_src_object_file)[9];
  isnt($native_src_object_file_mtime, $start_native_src_object_file_mtime);
  
  # Native shared_lib file is cached
  my $native_shared_lib_file_mtime = (stat $native_shared_lib_file)[9];
  isnt($native_shared_lib_file_mtime, $start_native_shared_lib_file_mtime);
}

done_testing;
