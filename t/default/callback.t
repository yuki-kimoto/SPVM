use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Callback';



# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

{
  ok(SPVM::TestCase::Callback->basic);
  ok(SPVM::TestCase::Callback->comparator);
  ok(SPVM::TestCase::Callback->capture);
  ok(SPVM::TestCase::Callback->capture_var_high_precidence_than_class_var);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);


done_testing;
