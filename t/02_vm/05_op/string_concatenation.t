use lib "t/testlib";
use TestAuto;

use strict;
use warnings;
use utf8;

use Test::More;

use SPVM 'TestCase::Operator::Concat';



# Start objects count
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count;

# Concat
{
  ok(SPVM::TestCase::Operator::Concat->concat_empty_string);
  ok(SPVM::TestCase::Operator::Concat->concat_string);
  ok(SPVM::TestCase::Operator::Concat->concat_left_is_number);
  ok(SPVM::TestCase::Operator::Concat->concat_right_is_number);
}

# Concat exception
{
  ok(SPVM::TestCase::Operator::Concat->concat_left_is_undef);
  ok(SPVM::TestCase::Operator::Concat->concat_right_is_undef);
}

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
