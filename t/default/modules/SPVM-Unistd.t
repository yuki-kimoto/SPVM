use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Lib::SPVM::Unistd';

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# SPVM::Int
{
  my $start_time = time;
  TestCase::Lib::SPVM::Unistd->test_sleep();
  my $proc_time = time - $start_time;
  if ($proc_time > 1) {
    ok(1);
  }
  else {
    ok(0);
  }
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
