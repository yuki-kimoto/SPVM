use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Statement::Unless';

# Start objects count
my $start_memory_blocks_count = SPVM::api->get_memory_blocks_count();

# unless Statement
{
  ok(SPVM::TestCase::Statement::Unless->true_condition);
  ok(SPVM::TestCase::Statement::Unless->false_condition);
  ok(SPVM::TestCase::Statement::Unless->elsif);
  ok(SPVM::TestCase::Statement::Unless->else);
}

# All object is freed
my $end_memory_blocks_count = SPVM::api->get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
