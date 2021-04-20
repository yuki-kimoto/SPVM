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
  ok(TestCase::Lib::SPVM::Sort->sortb);
  ok(TestCase::Lib::SPVM::Sort->sorts);
  ok(TestCase::Lib::SPVM::Sort->sorti);
  ok(TestCase::Lib::SPVM::Sort->sortl);
  ok(TestCase::Lib::SPVM::Sort->sortf);
  ok(TestCase::Lib::SPVM::Sort->sortd);
  ok(TestCase::Lib::SPVM::Sort->sorto);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
