use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase';



# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# Package variable relative name
{
  my $start_memory_blocks_count = SPVM::get_memory_blocks_count();
  ok(SPVM::TestCase->package_var_rel_name());
  my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
  is($start_memory_blocks_count, $end_memory_blocks_count);
}

# Package variable
{
  my $start_memory_blocks_count = SPVM::get_memory_blocks_count();
  ok(SPVM::TestCase->package_var());
  ok(SPVM::TestCase->package_var_other_package());
  my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
  is($start_memory_blocks_count, $end_memory_blocks_count);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
