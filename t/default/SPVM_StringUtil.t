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

# strtoi
{
  ok(TestCase::Lib::SPVM::StringUtil->test_strtoi);
  ok(TestCase::Lib::SPVM::StringUtil->test_strtol);
  ok(TestCase::Lib::SPVM::StringUtil->test_strtof);
  ok(TestCase::Lib::SPVM::StringUtil->test_strtod);
}
# chomp_lf
{
  ok(TestCase::Lib::SPVM::StringUtil->test_chomp_lf);
}
# chomp_crlf
{
  ok(TestCase::Lib::SPVM::StringUtil->test_chomp_crlf);
}

# isalnum
{
  ok(TestCase::Lib::SPVM::StringUtil->test_isalnum);
}

# isalpha
{
  ok(TestCase::Lib::SPVM::StringUtil->test_isalpha);
}

# isalpha
{
  ok(TestCase::Lib::SPVM::StringUtil->test_isblank);
}

# iscntrl
{
  ok(TestCase::Lib::SPVM::StringUtil->test_iscntrl);
}

# isdigit
{
  ok(TestCase::Lib::SPVM::StringUtil->test_isdigit);
}

# isgraph
{
  ok(TestCase::Lib::SPVM::StringUtil->test_isgraph);
}

# islower
{
  ok(TestCase::Lib::SPVM::StringUtil->test_islower);
}

# isprint
{
  ok(TestCase::Lib::SPVM::StringUtil->test_isprint);
}

# isprint
{
  ok(TestCase::Lib::SPVM::StringUtil->test_isprint);
}

# ispunct
{
  ok(TestCase::Lib::SPVM::StringUtil->test_ispunct);
}

# isspace
{
  ok(TestCase::Lib::SPVM::StringUtil->test_isspace);
}

# isupper
{
  ok(TestCase::Lib::SPVM::StringUtil->test_isupper);
}

# isxdigit
{
  ok(TestCase::Lib::SPVM::StringUtil->test_isxdigit);
}

# tolower
{
  ok(TestCase::Lib::SPVM::StringUtil->test_tolower);
}

# toupper
{
  ok(TestCase::Lib::SPVM::StringUtil->test_toupper);
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

# replace
{
  ok(TestCase::Lib::SPVM::StringUtil->test_replace_all);
}

# replace
{
  ok(TestCase::Lib::SPVM::StringUtil->test_replace);
}

# index
{
  ok(TestCase::Lib::SPVM::StringUtil->test_index);
}

# rindex
{
  ok(TestCase::Lib::SPVM::StringUtil->test_rindex);
}

# contains
{
  ok(TestCase::Lib::SPVM::StringUtil->test_contains);
}

# join
{
  ok(TestCase::Lib::SPVM::StringUtil->test_join);
}

# copy_string
{
  # copy_string
  ok(TestCase::Lib::SPVM::StringUtil->test_copy_str);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
