use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'SPVM::TestCase::Literal::String';



# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# String literal
{
  ok(SPVM::TestCase::Literal::String->raw_escape);
  ok(SPVM::TestCase::Literal::String->var_expansion);
  ok(SPVM::TestCase::Literal::String->characters);
  ok(SPVM::TestCase::Literal::String->escape);
  ok(SPVM::TestCase::Literal::String->escape_ascii);
  ok(SPVM::TestCase::Literal::String->escape_unicode);
  ok(SPVM::TestCase::Literal::String->edge_case);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
