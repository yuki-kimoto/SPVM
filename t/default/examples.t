use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Examples';

use SPVM 'TestCase::ModuleContainsMultiClass';

use Devel::Peek;

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

{
  # OK if segfault don't occur
  SPVM::TestCase::Examples->new_only_field_object;
  ok(1);
}

# This test case is a module contains multi classs
{
  my $outputs_length = 4;
  my $inputs_length = 3;
  my $weights_mat = SPVM::TestCase::ModuleContainsMultiClass->mat_new_zero($outputs_length, $inputs_length);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
