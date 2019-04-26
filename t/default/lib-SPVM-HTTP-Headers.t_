use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Lib::SPVM::HTTP::Headers';

# Start objects count
my $start_memory_blocks_count = SPVM::memory_blocks_count();

# SPVM::HTTP::Headers
{
  ok(TestCase::Lib::SPVM::HTTP::Headers->test_new_with);
  ok(TestCase::Lib::SPVM::HTTP::Headers->test_new_with_when_not_lowercase_key);
  ok(TestCase::Lib::SPVM::HTTP::Headers->test_set);
  ok(TestCase::Lib::SPVM::HTTP::Headers->test_append_to_buffer);
}

# All object is freed
my $end_memory_blocks_count = SPVM::memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
