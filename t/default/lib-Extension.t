use lib "t/lib";
use JITTestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Extension';

# Native Exception
{
  ok(SPVM::TestCase::Extension::call_void_sub_exception());
  ok(SPVM::TestCase::Extension::call_byte_sub_exception());
  ok(SPVM::TestCase::Extension::call_short_sub_exception());
  ok(SPVM::TestCase::Extension::call_int_sub_exception());
  ok(SPVM::TestCase::Extension::call_long_sub_exception());
  ok(SPVM::TestCase::Extension::call_float_sub_exception());
  ok(SPVM::TestCase::Extension::call_double_sub_exception());
  ok(SPVM::TestCase::Extension::call_object_sub_exception());
}

