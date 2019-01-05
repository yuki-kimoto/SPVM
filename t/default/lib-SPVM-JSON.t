use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::JSON';

# Start objects count
my $start_memory_blocks_count = SPVM::memory_blocks_count();

# SPVM::JSON
{
  ok(TestCase::JSON->test_empty);
  ok(TestCase::JSON->test_flat_hash);
  ok(TestCase::JSON->test_flat_list);
  ok(TestCase::JSON->test_digits_int);
  ok(TestCase::JSON->test_digits_long);
  ok(TestCase::JSON->test_digits_double);
  ok(TestCase::JSON->test_nest_object);
  ok(TestCase::JSON->test_spaces);
  ok(TestCase::JSON->test_pretty_name_separator);
  ok(TestCase::JSON->test_pretty_line_feed);
  ok(TestCase::JSON->test_pretty_indent);
}


# All object is freed
my $end_memory_blocks_count = SPVM::memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
