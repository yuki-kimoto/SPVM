use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::ClassVar';

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# Class variable relative name
{
  my $start_memory_blocks_count = SPVM::get_memory_blocks_count();
  ok(SPVM::TestCase::ClassVar->class_var_name);
  my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
  is($start_memory_blocks_count, $end_memory_blocks_count);
}

# Class variable
{
  my $start_memory_blocks_count = SPVM::get_memory_blocks_count();
  ok(SPVM::TestCase::ClassVar->class_var);
  ok(SPVM::TestCase::ClassVar->class_var_other_class);
  my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
  is($start_memory_blocks_count, $end_memory_blocks_count);
}

# Accessor
{
  ok(SPVM::TestCase::ClassVar->accessor);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
