use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Lib::SPVM::Sort';



# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# sort
{
  ok(TestCase::Lib::SPVM::Sort->sort_byte);
  ok(TestCase::Lib::SPVM::Sort->sort_short);
  ok(TestCase::Lib::SPVM::Sort->sort_int);
  ok(TestCase::Lib::SPVM::Sort->sort_long);
  ok(TestCase::Lib::SPVM::Sort->sort_float);
  ok(TestCase::Lib::SPVM::Sort->sort_double);
  ok(TestCase::Lib::SPVM::Sort->sort_object);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
