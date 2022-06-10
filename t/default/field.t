use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Field';

my $BYTE_MAX = 127;
my $BYTE_MIN = -128;
my $SHORT_MAX = 32767;
my $SHORT_MIN = -32768;
my $INT_MAX = 2147483647;
my $INT_MIN = -2147483648;
my $LONG_MAX = 9223372036854775807;
my $LONG_MIN = -9223372036854775808;
my $FLOAT_PRECICE = 16384.5;
my $DOUBLE_PRECICE = 65536.5;

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# Field name
{
  ok(SPVM::TestCase::Field->get_and_set_filed_same_name_as_keyword);
}

# Field access
{
  ok(SPVM::TestCase::Field->get_field_chain);
  ok(SPVM::TestCase::Field->core_func_name_field_name());
  ok(SPVM::TestCase::Field->object_field_set_and_get());
  ok(SPVM::TestCase::Field->object_field_set_and_get());
  ok(SPVM::TestCase::Field->object_field_set_and_get_again());
  ok(SPVM::TestCase::Field->object_field_initialized_zero());
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
