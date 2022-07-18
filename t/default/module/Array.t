use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Lib::Array';

use TestFile;

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# Copy
{
  # copy_byte
  ok(SPVM::TestCase::Lib::Array->copy_byte);

  # copy_short
  ok(SPVM::TestCase::Lib::Array->copy_short);

  # copy_int
  ok(SPVM::TestCase::Lib::Array->copy_int);

  # copy_long
  ok(SPVM::TestCase::Lib::Array->copy_long);

  # copy_float
  ok(SPVM::TestCase::Lib::Array->copy_float);

  # copy_double
  ok(SPVM::TestCase::Lib::Array->copy_double);

  # copy_string
  ok(SPVM::TestCase::Lib::Array->copy_string);
  
  # copy_object
  ok(SPVM::TestCase::Lib::Array->copy_object);
}

# copy_range
{
  # copy_range_byte
  ok(SPVM::TestCase::Lib::Array->copy_range_byte);

  # copy_range_short
  ok(SPVM::TestCase::Lib::Array->copy_range_short);

  # copy_range_int
  ok(SPVM::TestCase::Lib::Array->copy_range_int);

  # copy_range_long
  ok(SPVM::TestCase::Lib::Array->copy_range_long);

  # copy_range_float
  ok(SPVM::TestCase::Lib::Array->copy_range_float);

  # copy_range_double
  ok(SPVM::TestCase::Lib::Array->copy_range_double);

  # copy_range_double
  ok(SPVM::TestCase::Lib::Array->copy_range_string);

  # copy_range_double
  ok(SPVM::TestCase::Lib::Array->copy_range_object);
}

# dump array
{
  # dump_object
  ok(SPVM::TestCase::Lib::Array->dump_byte);
  ok(SPVM::TestCase::Lib::Array->dump_short);
  ok(SPVM::TestCase::Lib::Array->dump_int);
  ok(SPVM::TestCase::Lib::Array->dump_long);
  ok(SPVM::TestCase::Lib::Array->dump_float);
  ok(SPVM::TestCase::Lib::Array->dump_double);
  ok(SPVM::TestCase::Lib::Array->dump_unsigned_byte);
  ok(SPVM::TestCase::Lib::Array->dump_unsigned_short);
  ok(SPVM::TestCase::Lib::Array->dump_unsigned_int);
  ok(SPVM::TestCase::Lib::Array->dump_unsigned_long);
  ok(SPVM::TestCase::Lib::Array->dump_string);
  ok(SPVM::TestCase::Lib::Array->dump_object);
}

# equals
{
  # equals_byte
  ok(SPVM::TestCase::Lib::Array->equals_byte);

  # equals_short
  ok(SPVM::TestCase::Lib::Array->equals_short);

  # equals_int
  ok(SPVM::TestCase::Lib::Array->equals_int);

  # equeals_long
  ok(SPVM::TestCase::Lib::Array->equals_long);

  # equals_float
  ok(SPVM::TestCase::Lib::Array->equals_float);

  # equals_double
  ok(SPVM::TestCase::Lib::Array->equals_double);

  # equals_string
  ok(SPVM::TestCase::Lib::Array->equals_string);

  # equals_object
  ok(SPVM::TestCase::Lib::Array->equals_object);
}

# memcpy
{
  ok(SPVM::TestCase::Lib::Array->memcpy_byte);
  ok(SPVM::TestCase::Lib::Array->memcpy_short);
  ok(SPVM::TestCase::Lib::Array->memcpy_int);
  ok(SPVM::TestCase::Lib::Array->memcpy_long);
  ok(SPVM::TestCase::Lib::Array->memcpy_float);
  ok(SPVM::TestCase::Lib::Array->memcpy_double);
  ok(SPVM::TestCase::Lib::Array->memcpy_object);
}

# memmove_numeric
{
  ok(SPVM::TestCase::Lib::Array->memmove_byte);
  ok(SPVM::TestCase::Lib::Array->memmove_short);
  ok(SPVM::TestCase::Lib::Array->memmove_int);
  ok(SPVM::TestCase::Lib::Array->memmove_long);
  ok(SPVM::TestCase::Lib::Array->memmove_float);
  ok(SPVM::TestCase::Lib::Array->memmove_double);
  ok(SPVM::TestCase::Lib::Array->memmove_object);
}

# memset 
{
  ok(SPVM::TestCase::Lib::Array->memset_byte);
  ok(SPVM::TestCase::Lib::Array->memset_short);
  ok(SPVM::TestCase::Lib::Array->memset_int);
  ok(SPVM::TestCase::Lib::Array->memset_long);
  ok(SPVM::TestCase::Lib::Array->memset_float);
  ok(SPVM::TestCase::Lib::Array->memset_double);
  ok(SPVM::TestCase::Lib::Array->memset_object);
}

# new_proto
{
  # copy_range_byte
  ok(SPVM::TestCase::Lib::Array->new_proto);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
