use lib "t/lib";
use JITTestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase';

# Start objects count
my $start_objects_count = SPVM::get_objects_count();

# Enumeration
{
  ok(SPVM::TestCase::enum_byte());
  ok(SPVM::TestCase::enum_short());
  ok(SPVM::TestCase::enum_int());
  ok(SPVM::TestCase::enum_long());
  ok(SPVM::TestCase::enum_float());
  ok(SPVM::TestCase::enum_double());

  is(SPVM::TestCase::INT_VALUE(), 127);

=pod
  is(SPVM::TestCase::BYTE_MIN(), -128);
  is(SPVM::TestCase::SHORT_MAX(), 32767);
  is(SPVM::TestCase::SHORT_MIN(), -32768);
  is(SPVM::TestCase::INT_MAX(), 2147483647);
  is(SPVM::TestCase::INT_MIN(), -2147483648);
  is(SPVM::TestCase::LONG_MAX(), 9223372036854775807);
  is(SPVM::TestCase::LONG_MIN(), -9223372036854775808);
=cut

}

# All object is freed
my $end_objects_count = SPVM::get_objects_count();
is($end_objects_count, $start_objects_count);
