use lib "t/lib";
use JITTestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Extension';

# Start objects count
my $start_objects_count = SPVM::get_objects_count();

# Native Exception
{
  ok(SPVM::TestCase::Extension::call_void_sub_exception());
  ok(SPVM::TestCase::Extension::call_byte_sub_exception());
  ok(SPVM::TestCase::Extension::call_short_sub_exception());
  ok(SPVM::TestCase::Extension::call_int_sub_exception());
  ok(SPVM::TestCase::Extension::call_long_sub_exception());
  ok(SPVM::TestCase::Extension::call_float_sub_exception());
  ok(SPVM::TestCase::Extension::call_double_sub_exception());
  ok(SPVM::TestCase::Extension::call_object_sub_exception());
  ok(SPVM::TestCase::Extension::spvm_extension());
  ok(SPVM::TestCase::Extension::spvm_extension_add_int_array());
}

# All object is freed
my $end_objects_count = SPVM::get_objects_count();
is($end_objects_count, $start_objects_count);
