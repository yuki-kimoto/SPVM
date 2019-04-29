use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::LexicalVar';

# Start objects count
my $start_memory_blocks_count = SPVM::memory_blocks_count();

# Array
{
  ok(TestCase::LexicalVar->var_brace);
  ok(TestCase::LexicalVar->var_expansion);
  ok(TestCase::LexicalVar->lexical_var_upper_case);
}

# All object is freed
my $end_memory_blocks_count = SPVM::memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
