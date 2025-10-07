use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Literal::FloatingPoint';



# Start objects count
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count;

# decimal
{
  ok(SPVM::TestCase::Literal::FloatingPoint->decimal_notation);
}

# Hex Literal
{
  ok(SPVM::TestCase::Literal::FloatingPoint->hex_notation);
}

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
