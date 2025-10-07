use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Module::Packer';



# Start objects count
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count;

# SPVM::Packer
{
  ok(SPVM::TestCase::Module::Packer->new);
  ok(SPVM::TestCase::Module::Packer->pack_unpack_string);
  ok(SPVM::TestCase::Module::Packer->pack_unpack_numeric_object);
  ok(SPVM::TestCase::Module::Packer->pack_unpack_numeric_array);
  ok(SPVM::TestCase::Module::Packer->pack_unpack_big_endian);
  ok(SPVM::TestCase::Module::Packer->pack_unpack_little_endian);
  ok(SPVM::TestCase::Module::Packer->pack_unpack_specifiers);
  ok(SPVM::TestCase::Module::Packer->pack_exceptions);
  ok(SPVM::TestCase::Module::Packer->unpack_exceptions);
  ok(SPVM::TestCase::Module::Packer->pack_unpack_hex_string);
}

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
