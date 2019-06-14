use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Lib::SPVM::Regex';

# Start objects count
my $start_memory_blocks_count = SPVM::memory_blocks_count();

# SPVM::Regex
{
  ok(TestCase::Lib::SPVM::Regex->match_start);
  ok(TestCase::Lib::SPVM::Regex->match_quantifier);
  ok(TestCase::Lib::SPVM::Regex->match_one_or_zero);
  ok(TestCase::Lib::SPVM::Regex->match_zero_more);
  ok(TestCase::Lib::SPVM::Regex->match_one_more);
  ok(TestCase::Lib::SPVM::Regex->match);
  ok(TestCase::Lib::SPVM::Regex->compile);
}

# All object is freed
my $end_memory_blocks_count = SPVM::memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
