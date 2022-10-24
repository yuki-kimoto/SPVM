use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Inline';



# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# Inline constant sub
{
  ok(SPVM::TestCase::Inline->constant_method);
  ok(SPVM::TestCase::Inline->constant_method_return_double == 0.25);
}

# Inline new
{
  ok(SPVM::TestCase::Inline->new_inline);
  ok(SPVM::TestCase::Inline->new);
  is(ref SPVM::TestCase::Inline->new, "SPVM::TestCase::Inline");
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
