use lib "t/testlib";
use TestAuto;

use strict;
use warnings;
use utf8;

use Test::More;

use SPVM 'TestCase::Operator::String';



# Start objects count
my $api = SPVM::api();

my $start_memory_blocks_count = $api->get_memory_blocks_count;

# Character access, make_read_only, is_read_only, make_fixed_length, is_fixed_length
{
  ok(SPVM::TestCase::Operator::String->string_access);
}

# All object is freed
$api->set_exception(undef);
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
