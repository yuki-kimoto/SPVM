use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Extension';

# Start objects count
my $start_objects_count = SPVM::get_objects_count();

# Native Exception
{
  ok(TestCase::Extension->native_use_strlen_test);
  ok(TestCase::Extension->call_void_sub_exception);
}

# All object is freed
my $end_objects_count = SPVM::get_objects_count();
is($end_objects_count, $start_objects_count);
