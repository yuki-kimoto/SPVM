use lib "t/lib";
use TestAuto;

use strict;
use warnings;
use utf8;

use Test::More;

use SPVM 'TestCase::Concat';



# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# Concat
{
  ok(SPVM::TestCase::Concat->concat_empty_string);
  ok(SPVM::TestCase::Concat->concat_string);
  ok(SPVM::TestCase::Concat->concat_left_is_number);
  ok(SPVM::TestCase::Concat->concat_right_is_number);
}

# Concat exception
{
  ok(SPVM::TestCase::Concat->concat_left_is_undef);
  ok(SPVM::TestCase::Concat->concat_right_is_undef);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
