use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use FindBin;

my $native_object_file;
my $start_native_object_file_mtime;
BEGIN {
 $native_object_file = "$FindBin::Bin/.spvm_build/work/object/SPVM/TestCase/NativeAPI.o";
 $start_native_object_file_mtime = (stat $native_object_file)[9];
}

my $precompile_object_file;
my $start_precompile_object_file_mtime;
BEGIN {
 $precompile_object_file = "$FindBin::Bin/.spvm_build/work/object/SPVM/TestCase/NativeAPI.precompile.o";
 if ($ENV{SPVM_TEST_PRECOMPILE}) {
   ok(-f $precompile_object_file);
   $start_precompile_object_file_mtime = (stat $precompile_object_file)[9];
 }
}

# Just before this test, native_api.t must be run.

use SPVM 'TestCase::NativeAPI';

# Naative object file is cached
my $native_object_file_mtime = (stat $native_object_file)[9];
is($native_object_file_mtime, $start_native_object_file_mtime);

my $precompile_object_file_mtime = (stat $precompile_object_file)[9];
if ($ENV{SPVM_TEST_PRECOMPILE}) {
  is($precompile_object_file_mtime, $start_precompile_object_file_mtime);
}

done_testing;
