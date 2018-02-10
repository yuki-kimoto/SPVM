use lib "t/lib";
use JITTestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase';

# Start objects count
my $start_objects_count = SPVM::get_objects_count();

# Extension 
{
  ok(SPVM::TestCase::spvm_extension());
  ok(SPVM::TestCase::spvm_extension_add_int_array());
  ok(SPVM::TestCase::spvm_extension2());
  ok(SPVM::TestCase::spvm_extension2_binding());
}

# All object is freed
my $end_objects_count = SPVM::get_objects_count();
is($end_objects_count, $start_objects_count);
