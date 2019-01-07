use lib "t/lib";
use TestAuto;

use strict;
use warnings;
use utf8;

use Test::More 'no_plan';

use SPVM 'TestCase::Concat';

# Start objects count
my $start_memory_blocks_count = SPVM::memory_blocks_count();

# Concat
{
  ok(TestCase::Concat->concat_empty_string);
  ok(TestCase::Concat->concat_bytes);
  ok(TestCase::Concat->concat_string);
  ok(TestCase::Concat->concat_left_is_number);
  ok(TestCase::Concat->concat_right_is_number);
}

# Concat exception
{
  ok(TestCase::Concat->concat_left_is_undef);
  ok(TestCase::Concat->concat_right_is_undef);
}

# All object is freed
my $end_memory_blocks_count = SPVM::memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
