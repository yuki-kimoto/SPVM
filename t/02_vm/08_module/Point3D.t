use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Module::Point3D';

use Devel::Peek;

# Start objects count
my $start_memory_blocks_count = SPVM::api->get_memory_blocks_count();

# Point3D
{
  ok(SPVM::TestCase::Module::Point3D->super_class);
  ok(SPVM::TestCase::Module::Point3D->interfaces);
  ok(SPVM::TestCase::Module::Point3D->fields);
  ok(SPVM::TestCase::Module::Point3D->new);
  ok(SPVM::TestCase::Module::Point3D->clear);
  ok(SPVM::TestCase::Module::Point3D->to_string);
  ok(SPVM::TestCase::Module::Point3D->extra);
}

# All object is freed
my $end_memory_blocks_count = SPVM::api->get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
