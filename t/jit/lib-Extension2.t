use lib "t/lib";
use JITTestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Extension2';

# Start objects count
my $start_objects_count = SPVM::get_objects_count();

# Native Exception
{
  is(SPVM::TestCase::Extension2::mul(2, 3), 6);
  is(SPVM::TestCase::Extension2::one(), 1);
  ok(SPVM::TestCase::Extension2::spvm_extension2());
  ok(SPVM::TestCase::Extension2::spvm_extension2_binding());
}

# All object is freed
my $end_objects_count = SPVM::get_objects_count();
is($end_objects_count, $start_objects_count);
