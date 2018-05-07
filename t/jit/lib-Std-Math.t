use lib "t/lib";
use JITTestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Std::Math';

# Start objects count
my $start_objects_count = SPVM::get_objects_count();

# Call subroutine
{
  ok(SPVM::TestCase::Std::Math->sin());
  ok(SPVM::TestCase::Std::Math->cos());
  ok(SPVM::TestCase::Std::Math->tan());
}

# All object is freed
my $end_objects_count = SPVM::get_objects_count();
is($end_objects_count, $start_objects_count);
