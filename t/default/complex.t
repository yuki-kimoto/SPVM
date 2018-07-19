use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Complex';

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

{
  ok(TestCase::Complex->test_cadd());
  ok(TestCase::Complex->test_cadd_min());
  ok(TestCase::Complex->test_new_fcomplex());
  ok(TestCase::Complex->test_new_dcomplex());
  ok(TestCase::Complex->test_new_fcomplex_array());
  ok(TestCase::Complex->test_new_dcomplex_array());
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
