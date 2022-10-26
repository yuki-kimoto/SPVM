use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Init';

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# init
{
  {
    ok(SPVM::TestCase::Init->init_byte);
    ok(SPVM::TestCase::Init->init_short);
    ok(SPVM::TestCase::Init->init_int);
    ok(SPVM::TestCase::Init->init_long);
    ok(SPVM::TestCase::Init->init_float);
    ok(SPVM::TestCase::Init->init_double);
    ok(SPVM::TestCase::Init->init_mulnum_byte);
    ok(SPVM::TestCase::Init->init_mulnum_short);
    ok(SPVM::TestCase::Init->init_mulnum_int);
    ok(SPVM::TestCase::Init->init_mulnum_long);
    ok(SPVM::TestCase::Init->init_mulnum_float);
    ok(SPVM::TestCase::Init->init_mulnum_double);
    ok(SPVM::TestCase::Init->init_object);
  }
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);



done_testing;
