use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Exception';



use File::Basename 'basename';

my $file = basename $0;

# Exception
{
  eval { SPVM::TestCase::Exception->exception_zero_divide_int() }; my $line = __LINE__;
  my $error = $@;
  my $die_line = SPVM::TestCase::Exception->ZERO_DIVIDE_INT_LINE;
  ok($die_line > 0);
  like($error, qr|\Q0 division|);
  like($error, qr/\Q$file/);
  like($error, qr/$line/);
  like($error, qr/$die_line/);
  like($error, qr|Exception\.spvm|);
}

# Exception
{
  {
    ok(SPVM::TestCase::Exception->exception_eval_call_spvm_method());
  }
  
  {
    eval { SPVM::TestCase::Exception->exception_call_stack() };
    like($@, qr/Error/);
    like($@, qr/exception_die_return_int/);
    like($@, qr/exception_call_stack/);
  }

  {
    eval { SPVM::TestCase::Exception->exception_die_return_byte() };
    like($@, qr/Error/);
    like($@, qr/exception_die_return_byte/);
  }
  {
    eval { SPVM::TestCase::Exception->exception_die_return_short() };
    like($@, qr/Error/);
  }
  {
    eval { SPVM::TestCase::Exception->exception_die_return_int() };
    like($@, qr/Error/);
    like($@, qr/exception_die_return_int/);
    like($@, qr/Exception\.spvm/);
  }
  {
    eval { SPVM::TestCase::Exception->exception_die_return_long() };
    like($@, qr/Error/);
  }
  {
    eval { SPVM::TestCase::Exception->exception_die_return_float() };
    like($@, qr/Error/);
  }
  {
    eval { SPVM::TestCase::Exception->exception_die_return_double() };
    like($@, qr/Error/);
  }
  {
    eval { SPVM::TestCase::Exception->exception_die_return_void() };
    like($@, qr/Error/);
  }
  {
    ok(SPVM::TestCase::Exception->exception_die_return_int_eval_catch());
  }
  {
    eval { SPVM::TestCase::Exception->exception_die_return_object() };
    like($@, qr/Error/);
  }
}

eval { SPVM::TestCase->eval_block_stack_check() };
ok($@);

# Set field exception
{
  ok(SPVM::TestCase::Exception->exception_set_field_object_undef());
}

# Get field exception
{
  ok(SPVM::TestCase::Exception->exception_get_field_object_undef());
}

# Exception - callback
{
  eval { SPVM::TestCase::Exception->exception_callback() };
  my $error = $@;
  my $callback_die_line = SPVM::TestCase::Exception->CALLBACK_DIE_LINE;
  ok($callback_die_line > 0);
  like($error, qr/Comparator Error/);
  like($error, qr|TestCase/Exception\.spvm line $callback_die_line|);
}

# die statement
{
  ok(SPVM::TestCase::Exception->die);
}

done_testing;
