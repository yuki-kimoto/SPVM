use lib "t/lib";
use JITTestAuto;

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
my $FLOAT_MAX = POSIX::FLT_MAX();
my $FLOAT_MIN = POSIX::FLT_MIN();
my $DOUBLE_MAX = POSIX::DBL_MAX();
my $DOUBLE_MIN = POSIX::DBL_MIN();
my $FLOAT_PRECICE = 16384.5;
my $DOUBLE_PRECICE = 65536.5;

# Start objects count
my $start_objects_count = SPVM::get_objects_count();

# Create object
{
  # Create object
  {
    my $object = SPVM::TestCase::new();
    $object->set_x_int_array(SPVM::new_int_array([$INT_MAX, $INT_MAX]));
    $object->set_x_string(SPVM::new_byte_array_data("abc"));
    ok(SPVM::TestCase::spvm_object_set_object($object));
  }
  # Create object
  {
    my $object = SPVM::TestCase::new();
    $object->set_x_byte($BYTE_MAX);
    $object->set_x_short($SHORT_MAX);
    $object->set_x_int($INT_MAX);
    $object->set_x_long($LONG_MAX);
    $object->set_x_float($FLOAT_PRECICE);
    $object->set_x_double($DOUBLE_PRECICE);
    $object->set_x_int_array(SPVM::new_int_array([1, 2, 3, 4]));
    $object->set_x_string(SPVM::new_byte_array_string("Hello"));
    my $minimal = SPVM::TestCase::Minimal::new();
    $minimal->set_x(3);
    $object->set_minimal($minimal);
    
    ok(SPVM::TestCase::spvm_object_set($object));
    
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
  ok(SPVM::TestCase::object_field_set_and_get());
}

# Set field exception
{
  ok(SPVM::TestCase::set_field_exception_object_undef());
}

# Get field exception
{
  ok(SPVM::TestCase::get_field_exception_object_undef());
}

# Field
{
  ok(SPVM::TestCase::object_field_set_and_get());
  ok(SPVM::TestCase::object_field_set_and_get_again());
}

{
  ok(SPVM::TestCase::object_field_initialized_zero());
}

# Get object from freelist
{
  ok(SPVM::TestCase::get_object_from_freelist());
}

# Destructor
{
  ok(SPVM::TestCase::destructor());
}

# isa
{
  ok(SPVM::TestCase::isa_basic());
}

# All object is freed
my $end_objects_count = SPVM::get_objects_count();
is($end_objects_count, $start_objects_count);
