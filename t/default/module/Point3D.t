use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Module::Point3D';

use SPVM 'TestCase::ModuleContainsMultiClass';

use Devel::Peek;

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# Point3D
{
  ok(SPVM::TestCase::Module::Point3D->clear);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
