use lib "t/lib";
use JITTestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase';

# Start objects count
my $start_objects_count = SPVM::get_objects_count();

# logical not
{
  ok(SPVM::TestCase->logical_not_true());
  ok(SPVM::TestCase->logical_not_false());
}

# logical or
{
  ok(SPVM::TestCase->logical_or_both_true());
  ok(SPVM::TestCase->logical_or_left_true());
  ok(SPVM::TestCase->logical_or_right_true());
  ok(SPVM::TestCase->logical_or_both_false());
}

# logical and
{
  ok(SPVM::TestCase->logical_and_both_true());
  ok(SPVM::TestCase->logical_and_left_true());
  ok(SPVM::TestCase->logical_and_right_true());
  ok(SPVM::TestCase->logical_and_both_false());
}

# All object is freed
my $end_objects_count = SPVM::get_objects_count();
is($end_objects_count, $start_objects_count);
