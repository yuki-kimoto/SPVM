use lib "t/lib";
use JITTestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Float';

# Start objects count
my $start_objects_count = SPVM::get_objects_count();

# SPVM::Float
{
  ok(SPVM::TestCase::Float::basic());
}

# All object is freed
my $end_objects_count = SPVM::get_objects_count();
is($end_objects_count, $start_objects_count);
