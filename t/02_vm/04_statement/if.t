use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::If';

# Start objects count
my $start_memory_blocks_count = SPVM::api->get_memory_blocks_count();

# Conditional Branch
#   if Statement
#   elsif Statement
#   else Statement
#   unless Statement
{
  ok(SPVM::TestCase::If->condition_types());
  ok(SPVM::TestCase::If->condition_true());
  ok(SPVM::TestCase::If->condition_false());
  ok(SPVM::TestCase::If->elsif_condition_true());
  ok(SPVM::TestCase::If->elsif_condition_false());
  ok(SPVM::TestCase::If->elsif_only());
  ok(SPVM::TestCase::If->else_only());
  ok(SPVM::TestCase::If->condition_my());
}

# All object is freed
my $end_memory_blocks_count = SPVM::api->get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
