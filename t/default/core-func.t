use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use POSIX ();

use SPVM;

# Start objects count
my $start_objects_count = SPVM::get_objects_count();

# Constant integral functions
{
  is(SPVM::CORE->INT8_MAX, 127);
  is(SPVM::CORE->INT8_MIN, -128);
  is(SPVM::CORE->INT16_MAX, 32767);
  is(SPVM::CORE->INT16_MIN, -32768);
  is(SPVM::CORE->INT32_MAX, 2147483647);
  is(SPVM::CORE->INT32_MIN, -2147483648);
  is(SPVM::CORE->INT64_MAX, 9223372036854775807);
  is(SPVM::CORE->INT64_MIN, -9223372036854775808);
}

# Constant floating point number functions
{
  is(SPVM::CORE->FLT_MAX, POSIX::FLT_MAX());
  is(SPVM::CORE->FLT_MIN, POSIX::FLT_MIN());
  is(SPVM::CORE->DBL_MAX, POSIX::DBL_MAX());
  is(SPVM::CORE->DBL_MIN, POSIX::DBL_MIN());
}

# All object is freed
my $end_objects_count = SPVM::get_objects_count();
is($end_objects_count, $start_objects_count);

