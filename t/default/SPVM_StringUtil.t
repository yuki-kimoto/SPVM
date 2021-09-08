use strict;
use warnings;

use Test::More 'no_plan';

use lib "t/lib";
use TestAuto;
use TestFile;

use SPVM 'TestCase::Lib::StringUtil';

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# hex
{
  ok(SPVM::TestCase::Lib::StringUtil->test_hex);
}

# trim_ascii_space
{
  ok(SPVM::TestCase::Lib::StringUtil->test_trim_ascii_space);
}

# split
{
  ok(SPVM::TestCase::Lib::StringUtil->test_split);
}

# sprintf
{
  ok(SPVM::TestCase::Lib::StringUtil->test_sprintf_d);
  ok(SPVM::TestCase::Lib::StringUtil->test_sprintf_u);
  ok(SPVM::TestCase::Lib::StringUtil->test_sprintf_ld);
  ok(SPVM::TestCase::Lib::StringUtil->test_sprintf_lu);
  ok(SPVM::TestCase::Lib::StringUtil->test_sprintf_f);
  ok(SPVM::TestCase::Lib::StringUtil->test_sprintf_c);
  ok(SPVM::TestCase::Lib::StringUtil->test_sprintf_s);
  ok(SPVM::TestCase::Lib::StringUtil->test_sprintf_U);
  ok(SPVM::TestCase::Lib::StringUtil->test_sprintf_percent);
  ok(SPVM::TestCase::Lib::StringUtil->test_sprintf_all);
}

# to_int_with_base
{
  ok(SPVM::TestCase::Lib::StringUtil->test_to_int);
  ok(SPVM::TestCase::Lib::StringUtil->test_to_int_with_base);
  ok(SPVM::TestCase::Lib::StringUtil->test_to_long);
  ok(SPVM::TestCase::Lib::StringUtil->test_to_long_with_base);
  ok(SPVM::TestCase::Lib::StringUtil->test_to_float);
  ok(SPVM::TestCase::Lib::StringUtil->test_to_double);
}
# chompr
{
  ok(SPVM::TestCase::Lib::StringUtil->test_chompr);
}
# is_alnum
{
  ok(SPVM::TestCase::Lib::StringUtil->test_is_alnum);
}

# is_alpha
{
  ok(SPVM::TestCase::Lib::StringUtil->test_is_alpha);
}

# is_alpha
{
  ok(SPVM::TestCase::Lib::StringUtil->test_is_blank);
}

# is_cntrl
{
  ok(SPVM::TestCase::Lib::StringUtil->test_is_cntrl);
}

# is_digit
{
  ok(SPVM::TestCase::Lib::StringUtil->test_is_digit);
}

# is_graph
{
  ok(SPVM::TestCase::Lib::StringUtil->test_is_graph);
}

# is_lower
{
  ok(SPVM::TestCase::Lib::StringUtil->test_is_lower);
}

# is_print
{
  ok(SPVM::TestCase::Lib::StringUtil->test_is_print);
}

# is_print
{
  ok(SPVM::TestCase::Lib::StringUtil->test_is_print);
}

# is_punct
{
  ok(SPVM::TestCase::Lib::StringUtil->test_is_punct);
}

# is_space
{
  ok(SPVM::TestCase::Lib::StringUtil->test_is_space);
}

# is_upper
{
  ok(SPVM::TestCase::Lib::StringUtil->test_is_upper);
}

# is_xdigit
{
  ok(SPVM::TestCase::Lib::StringUtil->test_is_xdigit);
}

# to_lower
{
  ok(SPVM::TestCase::Lib::StringUtil->test_to_lower);
}

# to_upper
{
  ok(SPVM::TestCase::Lib::StringUtil->test_to_upper);
}

# is_perl_space
{
  ok(SPVM::TestCase::Lib::StringUtil->test_is_perl_space);
}

# is_perl_word
{
  ok(SPVM::TestCase::Lib::StringUtil->test_is_perl_word);
}
# uc
{
  ok(SPVM::TestCase::Lib::StringUtil->test_uc);
}

# lcfirst
{
  ok(SPVM::TestCase::Lib::StringUtil->test_lcfirst);
}

# lc
{
  ok(SPVM::TestCase::Lib::StringUtil->test_lc);
}

# index
{
  ok(SPVM::TestCase::Lib::StringUtil->test_index);
}

# rindex
{
  ok(SPVM::TestCase::Lib::StringUtil->test_rindex);
}

# join
{
  ok(SPVM::TestCase::Lib::StringUtil->test_join);
}

# copy_string
{
  # copy_string
  ok(SPVM::TestCase::Lib::StringUtil->test_copy_string);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
