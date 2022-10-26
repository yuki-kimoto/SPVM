use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Move';

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# init
{
  {
    ok(SPVM::TestCase::Move->move_constant_byte);
    ok(SPVM::TestCase::Move->move_constant_int);
    ok(SPVM::TestCase::Move->move_constant_long);
    ok(SPVM::TestCase::Move->move_constant_float);
    ok(SPVM::TestCase::Move->move_constant_double);
    ok(SPVM::TestCase::Move->move_byte);
    ok(SPVM::TestCase::Move->move_short);
    ok(SPVM::TestCase::Move->move_int);
    ok(SPVM::TestCase::Move->move_long);
    ok(SPVM::TestCase::Move->move_float);
    ok(SPVM::TestCase::Move->move_double);
  }
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);



done_testing;
