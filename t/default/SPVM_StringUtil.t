use strict;
use warnings;

use Test::More 'no_plan';

use lib "t/lib";
use TestAuto;
use TestFile;

use SPVM 'TestCase::Lib::SPVM::StringUtil';

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# split
{
  ok(TestCase::Lib::SPVM::StringUtil->test_split);
}

# sprintf
{
  ok(TestCase::Lib::SPVM::StringUtil->test_sprintf_d);
  ok(TestCase::Lib::SPVM::StringUtil->test_sprintf_u);
  ok(TestCase::Lib::SPVM::StringUtil->test_sprintf_ld);
  ok(TestCase::Lib::SPVM::StringUtil->test_sprintf_lu);
  ok(TestCase::Lib::SPVM::StringUtil->test_sprintf_f);
  ok(TestCase::Lib::SPVM::StringUtil->test_sprintf_c);
  ok(TestCase::Lib::SPVM::StringUtil->test_sprintf_s);
  ok(TestCase::Lib::SPVM::StringUtil->test_sprintf_U);
  ok(TestCase::Lib::SPVM::StringUtil->test_sprintf_percent);
  ok(TestCase::Lib::SPVM::StringUtil->test_sprintf_all);
}

# to_int_with_base
{
  ok(TestCase::Lib::SPVM::StringUtil->test_to_int);
  ok(TestCase::Lib::SPVM::StringUtil->test_to_int_with_base);
  ok(TestCase::Lib::SPVM::StringUtil->test_to_long);
  ok(TestCase::Lib::SPVM::StringUtil->test_to_long_with_base);
  ok(TestCase::Lib::SPVM::StringUtil->test_to_float);
  ok(TestCase::Lib::SPVM::StringUtil->test_to_double);
}
# chompr
{
  ok(TestCase::Lib::SPVM::StringUtil->test_chompr);
}
# is_alnum
{
  ok(TestCase::Lib::SPVM::StringUtil->test_is_alnum);
}

# is_alpha
{
  ok(TestCase::Lib::SPVM::StringUtil->test_is_alpha);
}

# is_alpha
{
  ok(TestCase::Lib::SPVM::StringUtil->test_is_blank);
}

# is_cntrl
{
  ok(TestCase::Lib::SPVM::StringUtil->test_is_cntrl);
}

# is_digit
{
  ok(TestCase::Lib::SPVM::StringUtil->test_is_digit);
}

# is_graph
{
  ok(TestCase::Lib::SPVM::StringUtil->test_is_graph);
}

# is_lower
{
  ok(TestCase::Lib::SPVM::StringUtil->test_is_lower);
}

# is_print
{
  ok(TestCase::Lib::SPVM::StringUtil->test_is_print);
}

# is_print
{
  ok(TestCase::Lib::SPVM::StringUtil->test_is_print);
}

# is_punct
{
  ok(TestCase::Lib::SPVM::StringUtil->test_is_punct);
}

# is_space
{
  ok(TestCase::Lib::SPVM::StringUtil->test_is_space);
}

# is_upper
{
  ok(TestCase::Lib::SPVM::StringUtil->test_is_upper);
}

# is_xdigit
{
  ok(TestCase::Lib::SPVM::StringUtil->test_is_xdigit);
}

# to_lower
{
  ok(TestCase::Lib::SPVM::StringUtil->test_to_lower);
}

# to_upper
{
  ok(TestCase::Lib::SPVM::StringUtil->test_to_upper);
}

# is_perl_space
{
  ok(TestCase::Lib::SPVM::StringUtil->test_is_perl_space);
}

# is_perl_word
{
  ok(TestCase::Lib::SPVM::StringUtil->test_is_perl_word);
}
# uc
{
  ok(TestCase::Lib::SPVM::StringUtil->test_uc);
}

# lcfirst
{
  ok(TestCase::Lib::SPVM::StringUtil->test_lcfirst);
}

# lc
{
  ok(TestCase::Lib::SPVM::StringUtil->test_lc);
}

# index
{
  ok(TestCase::Lib::SPVM::StringUtil->test_index);
}

# rindex
{
  ok(TestCase::Lib::SPVM::StringUtil->test_rindex);
}

# join
{
  ok(TestCase::Lib::SPVM::StringUtil->test_join);
}

# copy_string
{
  # copy_string
  ok(TestCase::Lib::SPVM::StringUtil->test_copy_string);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
