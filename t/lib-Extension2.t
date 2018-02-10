use lib "t/lib";
use JITTestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Extension2';

# Native Exception
{
  is(SPVM::TestCase::Extension2::mul(2, 3), 6);
  is(SPVM::TestCase::Extension2::one(), 1);
}
