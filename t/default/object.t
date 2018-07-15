use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase';

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
    my $object = TestCase->new();
    my $memory_blocks_count = SPVM::get_memory_blocks_count();
    ok($memory_blocks_count > 0);
  }

  # Create object
  {
    my $object = TestCase->new();
    $object->set_x_int_array(SPVM::new_int_array([$INT_MAX, $INT_MAX]));
    $object->set_x_string(SPVM::new_byte_array_bin("abc"));
    ok(TestCase->spvm_object_set_object($object));
  }
  # Create object
  {
    my $object = TestCase->new();
    $object->set_x_byte($BYTE_MAX);
    $object->set_x_short($SHORT_MAX);
    $object->set_x_int($INT_MAX);
    $object->set_x_long($LONG_MAX);
    $object->set_x_float($FLOAT_PRECICE);
    $object->set_x_double($DOUBLE_PRECICE);
    $object->set_x_int_array(SPVM::new_int_array([1, 2, 3, 4]));
    $object->set_x_string(SPVM::new_byte_array_string("Hello"));
    my $minimal = TestCase::Minimal->new;
    $minimal->set_x(3);
    $object->set_minimal($minimal);
    
    ok(TestCase->spvm_object_set($object));
    
    is($object->get_x_byte,$BYTE_MAX);
    is($object->get_x_short, $SHORT_MAX);
    is($object->get_x_int, $INT_MAX);
    is($object->get_x_long, $LONG_MAX);
    is($object->get_x_float, $FLOAT_PRECICE);
    is($object->get_x_double, $DOUBLE_PRECICE);
    is($object->get_minimal->get_x, 3);
  }
}

# Field
{
  ok(TestCase->object_field_set_and_get());
}

# Field
{
  ok(TestCase->object_field_set_and_get());
  ok(TestCase->object_field_set_and_get_again());
}

{
  ok(TestCase->object_field_initialized_zero());
}

# Get object from freelist
{
  ok(TestCase->get_object_from_freelist());
}

# Destructor
{
  ok(TestCase->destructor());
}

# isa
{
  ok(TestCase->isa_basic());
}


# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
