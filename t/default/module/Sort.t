use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Module::Sort';

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# sort
{
  ok(SPVM::TestCase::Module::Sort->sort_byte);
  ok(SPVM::TestCase::Module::Sort->sort_double);
  ok(SPVM::TestCase::Module::Sort->sort_float);
  ok(SPVM::TestCase::Module::Sort->sort_int);
  ok(SPVM::TestCase::Module::Sort->sort_long);
  ok(SPVM::TestCase::Module::Sort->sort_object);
  ok(SPVM::TestCase::Module::Sort->sort_short);
  ok(SPVM::TestCase::Module::Sort->sort_string);
}
# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
