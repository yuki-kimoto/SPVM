use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Complex';

# Start objects count
my $start_memory_blocks_count = SPVM::memory_blocks_count();

{
  ok(TestCase::Complex->test_cadd());
  ok(TestCase::Complex->test_cadd_min());
  ok(TestCase::Complex->test_csub());
  ok(TestCase::Complex->test_csub_min());
  ok(TestCase::Complex->test_cmul());
  ok(TestCase::Complex->test_cmul_min());
  ok(TestCase::Complex->test_caddf());
  ok(TestCase::Complex->test_caddf_min());
  ok(TestCase::Complex->test_csubf());
  ok(TestCase::Complex->test_csubf_min());
  ok(TestCase::Complex->test_cmulf());
  ok(TestCase::Complex->test_cmulf_min());
  ok(TestCase::Complex->test_cdivf());
  ok(TestCase::Complex->test_cdivf_min());
  ok(TestCase::Complex->test_complexf());
  ok(TestCase::Complex->test_complex());
  ok(TestCase::Complex->test_complex_farray());
  ok(TestCase::Complex->test_complex_array());
}

# All object is freed
my $end_memory_blocks_count = SPVM::memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
