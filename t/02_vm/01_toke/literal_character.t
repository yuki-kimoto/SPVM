use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Literal::Character';



# Start objects count
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count;

# Character literal
{
  ok(SPVM::TestCase::Literal::Character->character_literal);
  ok(SPVM::TestCase::Literal::Character->character_literal_octal);
  ok(SPVM::TestCase::Literal::Character->character_literal_hex);
}

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
