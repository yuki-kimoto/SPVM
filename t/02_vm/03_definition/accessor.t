use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Accessor';

# Start objects count
my $start_memory_blocks_count = SPVM::api->get_memory_blocks_count();

# Accessor 
{
  ok(SPVM::TestCase::Accessor->field_accessor);
  ok(SPVM::TestCase::Accessor->class_var_accessor);
}

# All object is freed
my $end_memory_blocks_count = SPVM::api->get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);



done_testing;
