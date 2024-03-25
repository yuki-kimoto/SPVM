use lib "t/testlib";
use TestAuto;

use strict;
use warnings;
use utf8;

use Test::More;

use SPVM 'TestCase::Operator::String';



# Start objects count
my $start_memory_blocks_count = SPVM::api->get_memory_blocks_count();

# String access, make_read_only, is_read_only
{
  ok(SPVM::TestCase::Operator::String->string_access);
}

{
  ok(SPVM::TestCase::Operator::String->string_length);
  ok(SPVM::TestCase::Operator::String->basic);
  ok(SPVM::TestCase::Operator::String->new_string_len);
}

# All object is freed
my $end_memory_blocks_count = SPVM::api->get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
