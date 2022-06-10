use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;


use FindBin;
use lib "$FindBin::Bin/lib";

use SPVM 'TestCase::Remainder';



# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# Spec tests
{
  # Remainder - Operation
  {
    ok(SPVM::TestCase::Remainder->remainder_byte_byte);
    ok(SPVM::TestCase::Remainder->remainder_short_short);
    ok(SPVM::TestCase::Remainder->remainder_int_byte);
    ok(SPVM::TestCase::Remainder->remainder_int_short);
    ok(SPVM::TestCase::Remainder->remainder_byte_int);
    ok(SPVM::TestCase::Remainder->remainder_short_int);
    ok(SPVM::TestCase::Remainder->remainder_int_int);
    ok(SPVM::TestCase::Remainder->remainder_long_long);
  }

  # Divide Unsinged operator
  {
    ok(SPVM::TestCase::Remainder->remainder_unsigned_int);
    ok(SPVM::TestCase::Remainder->remainder_unsigned_long);
  }
}

# Optional tests
{
  ok(SPVM::TestCase::Remainder->remainder());
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
