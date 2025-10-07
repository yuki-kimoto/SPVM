use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Module::Point3D';

use Devel::Peek;

# Start objects count
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count;

# Point3D
{
  ok(SPVM::TestCase::Module::Point3D->super_class);
  ok(SPVM::TestCase::Module::Point3D->interfaces);
  ok(SPVM::TestCase::Module::Point3D->fields);
  ok(SPVM::TestCase::Module::Point3D->new);
  ok(SPVM::TestCase::Module::Point3D->clear);
  ok(SPVM::TestCase::Module::Point3D->to_string);
  ok(SPVM::TestCase::Module::Point3D->extra);
  ok(SPVM::TestCase::Module::Point3D->eq);
}

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
