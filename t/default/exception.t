use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Exception';



use File::Basename 'basename';

my $file = basename $0;

# Exception
{
  eval { TestCase::Exception->exception_zero_divide_int() }; my $line = __LINE__;
  like($@, qr|\Q0 division|);
  like($@, qr/\Q$file/);
  like($@, qr/$line/);
  like($@, qr/179/);
  like($@, qr|Exception\.spvm|);
}

# Exception
{
  {
    ok(TestCase::Exception->exception_eval_call_spvm_method());
  }
  
  {
    eval { TestCase::Exception->exception_call_stack() };
    like($@, qr/Error/);
    like($@, qr/exception_die_return_int/);
    like($@, qr/exception_call_stack/);
  }

  {
    eval { TestCase::Exception->exception_die_return_byte() };
    like($@, qr/Error/);
    like($@, qr/exception_die_return_byte/);
  }
  {
    eval { TestCase::Exception->exception_die_return_short() };
    like($@, qr/Error/);
  }
  {
    eval { TestCase::Exception->exception_die_return_int() };
    like($@, qr/Error/);
    like($@, qr/exception_die_return_int/);
    like($@, qr/Exception\.spvm/);
  }
  {
    eval { TestCase::Exception->exception_die_return_long() };
    like($@, qr/Error/);
  }
  {
    eval { TestCase::Exception->exception_die_return_float() };
    like($@, qr/Error/);
  }
  {
    eval { TestCase::Exception->exception_die_return_double() };
    like($@, qr/Error/);
  }
  {
    eval { TestCase::Exception->exception_die_return_void() };
    like($@, qr/Error/);
  }
  {
    ok(TestCase::Exception->exception_die_return_int_eval_catch());
  }
  {
    eval { TestCase::Exception->exception_die_return_object() };
    like($@, qr/Error/);
  }
}

eval { TestCase->eval_block_stack_check() };
ok($@);

# Set field exception
{
  ok(TestCase::Exception->exception_set_field_object_undef());
}

# Get field exception
{
  ok(TestCase::Exception->exception_get_field_object_undef());
}

