use lib "t/lib";
use JITTestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Int';

# Start objects count
my $start_objects_count = SPVM::get_objects_count();

# SPVM::Int
{
  ok(SPVM::TestCase::Int->basic());
}


# All object is freed
my $end_objects_count = SPVM::get_objects_count();
is($end_objects_count, $start_objects_count);
