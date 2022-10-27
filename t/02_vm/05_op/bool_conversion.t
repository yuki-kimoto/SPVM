use lib "t/testlib";
use TestAuto;

use strict;
use warnings;
use utf8;

use Test::More;

use SPVM 'TestCase::ComparisonOperator';



# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# Spec tests
{
  # Bool conversion
  {
    ok(SPVM::TestCase::ComparisonOperator->bool_true_byte);
    ok(SPVM::TestCase::ComparisonOperator->bool_true_short);
    ok(SPVM::TestCase::ComparisonOperator->bool_true_int);
    ok(SPVM::TestCase::ComparisonOperator->bool_true_long);
    ok(SPVM::TestCase::ComparisonOperator->bool_true_float);
    ok(SPVM::TestCase::ComparisonOperator->bool_true_double);
    ok(SPVM::TestCase::ComparisonOperator->bool_true_object);
    ok(SPVM::TestCase::ComparisonOperator->bool_true_ref);

    ok(SPVM::TestCase::ComparisonOperator->bool_false_byte);
    ok(SPVM::TestCase::ComparisonOperator->bool_false_short);
    ok(SPVM::TestCase::ComparisonOperator->bool_false_int);
    ok(SPVM::TestCase::ComparisonOperator->bool_false_long);
    ok(SPVM::TestCase::ComparisonOperator->bool_false_float);
    ok(SPVM::TestCase::ComparisonOperator->bool_false_double);
    ok(SPVM::TestCase::ComparisonOperator->bool_false_object);

    ok(SPVM::TestCase::ComparisonOperator->bool_else);
    ok(SPVM::TestCase::ComparisonOperator->bool_elsif);
    ok(SPVM::TestCase::ComparisonOperator->bool_elsbool_2);
    ok(SPVM::TestCase::ComparisonOperator->bool_duplicate);
  }
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
