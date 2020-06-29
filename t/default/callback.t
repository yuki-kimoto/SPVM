use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Callback';

UNITCHECK { SPVM::init() }

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

{
  ok(TestCase::Callback->basic);
  ok(TestCase::Callback->comparator);
  ok(TestCase::Callback->capture);
  ok(TestCase::Callback->capture_var_high_precidence_than_package_var);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

