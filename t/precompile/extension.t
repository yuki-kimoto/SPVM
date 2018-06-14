use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Extension';
use SPVM 'TestCase::Extension2';

# Start objects count
my $start_objects_count = SPVM::get_objects_count();

# Native Exception
{
  ok(TestCase::Extension->native_use_strlen_test);
  ok(TestCase::Extension->call_void_sub_exception);
}

# Native Exception
{
  is(TestCase::Extension2->mul(2, 3), 6);
  is(TestCase::Extension2->one(), 1);
  ok(TestCase::Extension2->spvm_extension2());
  ok(TestCase::Extension2->spvm_extension2_binding());
}

# All object is freed
my $end_objects_count = SPVM::get_objects_count();
is($end_objects_count, $start_objects_count);
