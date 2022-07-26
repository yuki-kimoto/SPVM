use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Module::Array';

use TestFile;

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# Array
{
  ok(SPVM::TestCase::Module::Array->copy_byte);
  ok(SPVM::TestCase::Module::Array->copy_double);
  ok(SPVM::TestCase::Module::Array->copy_float);
  ok(SPVM::TestCase::Module::Array->copy_int);
  ok(SPVM::TestCase::Module::Array->copy_long);
  ok(SPVM::TestCase::Module::Array->copy_object);
  ok(SPVM::TestCase::Module::Array->copy_object_address);
  ok(SPVM::TestCase::Module::Array->copy_range_byte);
  ok(SPVM::TestCase::Module::Array->copy_range_double);
  ok(SPVM::TestCase::Module::Array->copy_range_float);
  ok(SPVM::TestCase::Module::Array->copy_range_int);
  ok(SPVM::TestCase::Module::Array->copy_range_long);
  ok(SPVM::TestCase::Module::Array->copy_range_object);
  ok(SPVM::TestCase::Module::Array->copy_range_object_address);
  ok(SPVM::TestCase::Module::Array->copy_range_short);
  ok(SPVM::TestCase::Module::Array->copy_range_string);
  ok(SPVM::TestCase::Module::Array->copy_range_string_address);
  ok(SPVM::TestCase::Module::Array->copy_short);
  ok(SPVM::TestCase::Module::Array->copy_string);
  ok(SPVM::TestCase::Module::Array->copy_string_address);
  ok(SPVM::TestCase::Module::Array->dump_byte);
  ok(SPVM::TestCase::Module::Array->dump_double);
  ok(SPVM::TestCase::Module::Array->dump_float);
  ok(SPVM::TestCase::Module::Array->dump_int);
  ok(SPVM::TestCase::Module::Array->dump_long);
  ok(SPVM::TestCase::Module::Array->dump_object);
  ok(SPVM::TestCase::Module::Array->dump_short);
  ok(SPVM::TestCase::Module::Array->dump_string);
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
  ok(SPVM::TestCase::Module::Array->memcpy_object);
  ok(SPVM::TestCase::Module::Array->memcpy_object_address);
  ok(SPVM::TestCase::Module::Array->memcpy_short);
  ok(SPVM::TestCase::Module::Array->memcpy_string);
  ok(SPVM::TestCase::Module::Array->memcpy_string_address);
  ok(SPVM::TestCase::Module::Array->memmove_byte);
  ok(SPVM::TestCase::Module::Array->memmove_double);
  ok(SPVM::TestCase::Module::Array->memmove_float);
  ok(SPVM::TestCase::Module::Array->memmove_int);
  ok(SPVM::TestCase::Module::Array->memmove_long);
  ok(SPVM::TestCase::Module::Array->memmove_object);
  ok(SPVM::TestCase::Module::Array->memmove_object_address);
  ok(SPVM::TestCase::Module::Array->memmove_short);
  ok(SPVM::TestCase::Module::Array->memmove_string);
  ok(SPVM::TestCase::Module::Array->memmove_string_address);
  ok(SPVM::TestCase::Module::Array->memset_byte);
  ok(SPVM::TestCase::Module::Array->memset_double);
  ok(SPVM::TestCase::Module::Array->memset_float);
  ok(SPVM::TestCase::Module::Array->memset_int);
  ok(SPVM::TestCase::Module::Array->memset_long);
  ok(SPVM::TestCase::Module::Array->memset_object);
  ok(SPVM::TestCase::Module::Array->memset_short);
  ok(SPVM::TestCase::Module::Array->memset_string);
  ok(SPVM::TestCase::Module::Array->new_proto);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
