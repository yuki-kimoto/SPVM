use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase';
use SPVM 'TestCase::Object';



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

# Create object
{
  # Check object count at least 1 to check object count system itself
  {
    my $object = SPVM::TestCase->new();
    my $memory_blocks_count = SPVM::get_memory_blocks_count();
    ok($memory_blocks_count > 0);
  }
}

# Field
{
  ok(SPVM::TestCase::Object->get_field_chain);
  ok(SPVM::TestCase::Object->core_func_name_field_name());
  ok(SPVM::TestCase::Object->reserved_word_field_name());
  ok(SPVM::TestCase::Object->object_field_set_and_get());
}

# Field
{
  ok(SPVM::TestCase::Object->object_field_set_and_get());
  ok(SPVM::TestCase::Object->object_field_set_and_get_again());
}

{
  ok(SPVM::TestCase::Object->object_field_initialized_zero());
}

# Destructor
{
  ok(SPVM::TestCase::Object->destructor());
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
