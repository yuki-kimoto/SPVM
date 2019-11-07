use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM::StringBuffer;

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

{
  my $buffer = SPVM::StringBuffer->new;
  $buffer->push("abc");
  $buffer->push("def");
  my $str = $buffer->to_str;
  is($str, "abcdef");
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
