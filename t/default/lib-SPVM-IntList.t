use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Lib::SPVM::IntList';

# Start objects count
my $start_memory_blocks_count = SPVM::memory_blocks_count();

# SPVM::IntList
{
  ok(TestCase::Lib::SPVM::IntList->push);
  ok(TestCase::Lib::SPVM::IntList->pop);
  ok(TestCase::Lib::SPVM::IntList->new_with_array);
  ok(TestCase::Lib::SPVM::IntList->unshift);

=pod
  ok(TestCase::Lib::SPVM::IntList->length);
  ok(TestCase::Lib::SPVM::IntList->shift);
  ok(TestCase::Lib::SPVM::IntList->set);
  ok(TestCase::Lib::SPVM::IntList->get);
  ok(TestCase::Lib::SPVM::IntList->to_array);
=cut
}

# All object is freed
my $end_memory_blocks_count = SPVM::memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
