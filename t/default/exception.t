use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase';
use File::Basename 'basename';

my $file = basename $0;

# Exception
{
  eval { TestCase->exception_zero_divide_int() }; my $line = __LINE__;
  like($@, qr|\Q0 division|);
  like($@, qr/\Q$file/);
  like($@, qr/$line/);
}

# Exception
{
  {
    ok(TestCase->exception_eval_call_sub());
  }
  
  {
    eval { TestCase->exception_call_stack() };
    like($@, qr/Error/);
    like($@, qr/exception_croak_return_int/);
    like($@, qr/exception_call_stack/);
  }

  {
    eval { TestCase->exception_croak_return_byte() };
    like($@, qr/Error/);
    like($@, qr/exception_croak_return_byte/);
  }
  {
    eval { TestCase->exception_croak_return_short() };
    like($@, qr/Error/);
  }
  {
    eval { TestCase->exception_croak_return_int() };
    like($@, qr/Error/);
    like($@, qr/exception_croak_return_int/);
    like($@, qr/TestCase\.spvm/);
  }
  {
    eval { TestCase->exception_croak_return_long() };
    like($@, qr/Error/);
  }
  {
    eval { TestCase->exception_croak_return_float() };
    like($@, qr/Error/);
  }
  {
    eval { TestCase->exception_croak_return_double() };
    like($@, qr/Error/);
  }
  {
    eval { TestCase->exception_croak_return_void() };
    like($@, qr/Error/);
  }
  {
    ok(TestCase->exception_croak_return_int_eval_catch());
  }
  {
    eval { TestCase->exception_croak_return_object() };
    like($@, qr/Error/);
  }
}

eval { TestCase->eval_block_stack_check() };
ok($@);
