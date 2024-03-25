use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Operator::Modulo';

# Start objects count
my $start_memory_blocks_count = SPVM::api->get_memory_blocks_count();

# Spec tests
{
  # Modulo - Operation
  {
    ok(SPVM::TestCase::Operator::Modulo->modulo_byte_byte);
    ok(SPVM::TestCase::Operator::Modulo->modulo_short_short);
    ok(SPVM::TestCase::Operator::Modulo->modulo_int_byte);
    ok(SPVM::TestCase::Operator::Modulo->modulo_int_short);
    ok(SPVM::TestCase::Operator::Modulo->modulo_byte_int);
    ok(SPVM::TestCase::Operator::Modulo->modulo_short_int);
    ok(SPVM::TestCase::Operator::Modulo->modulo_int_int);
    ok(SPVM::TestCase::Operator::Modulo->modulo_long_long);
  }

  # Divide Unsinged operator
  {
    ok(SPVM::TestCase::Operator::Modulo->modulo_unsigned_int);
    ok(SPVM::TestCase::Operator::Modulo->modulo_unsigned_long);
  }
}

# Optional tests
{
  ok(SPVM::TestCase::Operator::Modulo->modulo());
}

# All object is freed
my $end_memory_blocks_count = SPVM::api->get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
