use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Module::Array';

use TestFile;

my $api = SPVM::api();

# Start objects count
my $start_memory_blocks_count = $api->get_memory_blocks_count;

# Array
{
  ok(SPVM::TestCase::Module::Array->copy_byte);
  ok(SPVM::TestCase::Module::Array->copy_double);
  ok(SPVM::TestCase::Module::Array->copy_float);
  ok(SPVM::TestCase::Module::Array->copy_int);
  ok(SPVM::TestCase::Module::Array->copy_long);
  ok(SPVM::TestCase::Module::Array->copy_object);
  ok(SPVM::TestCase::Module::Array->copy_object_address);
  ok(SPVM::TestCase::Module::Array->copy_short);
  ok(SPVM::TestCase::Module::Array->copy_string);
  ok(SPVM::TestCase::Module::Array->copy_string_address);
  ok(SPVM::TestCase::Module::Array->dump_unsigned_byte);
  ok(SPVM::TestCase::Module::Array->dump_unsigned_int);
  ok(SPVM::TestCase::Module::Array->dump_unsigned_long);
  ok(SPVM::TestCase::Module::Array->dump_unsigned_short);
  ok(SPVM::TestCase::Module::Array->equals_byte);
  ok(SPVM::TestCase::Module::Array->equals_double);
  ok(SPVM::TestCase::Module::Array->equals_float);
  ok(SPVM::TestCase::Module::Array->equals_int);
  ok(SPVM::TestCase::Module::Array->equals_long);
  ok(SPVM::TestCase::Module::Array->equals_object);
  ok(SPVM::TestCase::Module::Array->equals_object_address);
  ok(SPVM::TestCase::Module::Array->equals_short);
  ok(SPVM::TestCase::Module::Array->equals_string);
  ok(SPVM::TestCase::Module::Array->equals_string_address);
  ok(SPVM::TestCase::Module::Array->memcpy_byte);
  ok(SPVM::TestCase::Module::Array->memcpy_double);
  ok(SPVM::TestCase::Module::Array->memcpy_float);
  ok(SPVM::TestCase::Module::Array->memcpy_int);
  ok(SPVM::TestCase::Module::Array->memcpy_long);
  ok(SPVM::TestCase::Module::Array->memcpy_object_address);
  ok(SPVM::TestCase::Module::Array->memcpy_short);
  ok(SPVM::TestCase::Module::Array->memcpy_string_address);
  ok(SPVM::TestCase::Module::Array->memmove_byte);
  ok(SPVM::TestCase::Module::Array->memmove_double);
  ok(SPVM::TestCase::Module::Array->memmove_float);
  ok(SPVM::TestCase::Module::Array->memmove_int);
  ok(SPVM::TestCase::Module::Array->memmove_long);
  ok(SPVM::TestCase::Module::Array->memmove_object_address);
  ok(SPVM::TestCase::Module::Array->memmove_short);
  ok(SPVM::TestCase::Module::Array->memmove_string_address);
  ok(SPVM::TestCase::Module::Array->memset_byte);
  ok(SPVM::TestCase::Module::Array->memset_double);
  ok(SPVM::TestCase::Module::Array->memset_float);
  ok(SPVM::TestCase::Module::Array->memset_int);
  ok(SPVM::TestCase::Module::Array->memset_long);
  ok(SPVM::TestCase::Module::Array->memset_object);
  ok(SPVM::TestCase::Module::Array->memset_short);
  ok(SPVM::TestCase::Module::Array->memset_string);
  ok(SPVM::TestCase::Module::Array->merge_byte);
  ok(SPVM::TestCase::Module::Array->merge_double);
  ok(SPVM::TestCase::Module::Array->merge_float);
  ok(SPVM::TestCase::Module::Array->merge_int);
  ok(SPVM::TestCase::Module::Array->merge_long);
  ok(SPVM::TestCase::Module::Array->merge_object);
  ok(SPVM::TestCase::Module::Array->merge_short);
  ok(SPVM::TestCase::Module::Array->merge_string);
  ok(SPVM::TestCase::Module::Array->new_proto);
  ok(SPVM::TestCase::Module::Array->new_proto_any);
  ok(SPVM::TestCase::Module::Array->shuffle_object);
  ok(SPVM::TestCase::Module::Array->repeat_string);
  ok(SPVM::TestCase::Module::Array->copy_object_with_proto);
  ok(SPVM::TestCase::Module::Array->copy_object_address_with_proto);
  ok(SPVM::TestCase::Module::Array->to_object_array_byte);
  ok(SPVM::TestCase::Module::Array->to_object_array_short);
  ok(SPVM::TestCase::Module::Array->to_object_array_int);
  ok(SPVM::TestCase::Module::Array->to_object_array_long);
  ok(SPVM::TestCase::Module::Array->to_object_array_float);
  ok(SPVM::TestCase::Module::Array->to_object_array_double);
  ok(SPVM::TestCase::Module::Array->to_array_byte);
  ok(SPVM::TestCase::Module::Array->to_array_short);
  ok(SPVM::TestCase::Module::Array->to_array_int);
  ok(SPVM::TestCase::Module::Array->to_array_long);
  ok(SPVM::TestCase::Module::Array->to_array_float);
  ok(SPVM::TestCase::Module::Array->to_array_double);
  ok(SPVM::TestCase::Module::Array->new_array_proto_element);
  ok(SPVM::TestCase::Module::Array->equals);
  ok(SPVM::TestCase::Module::Array->copy_any_numeric);
  ok(SPVM::TestCase::Module::Array->shuffle_any_numeric);
  ok(SPVM::TestCase::Module::Array->shuffle);
  ok(SPVM::TestCase::Module::Array->repeat);
}

$api->destroy_runtime_permanent_vars;

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
