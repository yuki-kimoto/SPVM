use lib "t/lib";
use JITTestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::TypeUtil';

# Start objects count
my $start_objects_count = SPVM::get_objects_count();

# SPVM::TypeUtil
{
  ok(SPVM::TestCase::TypeUtil->byte_constant());
  ok(SPVM::TestCase::TypeUtil->short_constant());
  ok(SPVM::TestCase::TypeUtil->int_constant());
}

{
  # Check not Inf or NaN in Perl value
  like(SPVM::TypeUtil->FLT_MAX(), qr/[0-9]/);
  like(SPVM::TypeUtil->FLT_MIN(), qr/[0-9]/);
}

# All object is freed
my $end_objects_count = SPVM::get_objects_count();
is($end_objects_count, $start_objects_count);
