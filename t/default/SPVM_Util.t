use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Lib::SPVM::Util';
use SPVM 'SPVM::Util';
use POSIX();
use TestFile;



# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

my $BYTE_MAX = 127;
my $BYTE_MIN = -128;
my $SHORT_MAX = 32767;
my $SHORT_MIN = -32768;
my $INT_MAX = 2147483647;
my $INT_MIN = -2147483648;
my $LONG_MAX = 9223372036854775807;
my $LONG_MIN = -9223372036854775808;
my $FLOAT_PRECICE = 16384.5;
my $DOUBLE_PRECICE = 65536.5;

# Positive infinity(unix like system : inf, Windows : 1.#INF)
my $POSITIVE_INFINITY = 9**9**9;

my $NaN = 9**9**9 / 9**9**9;

my $nan_re = qr/(nan|ind)/i;

use SPVM 'TestCase::Lib::SPVM::Util';
use SPVM 'SPVM::Util';

# join
{
  ok(TestCase::Lib::SPVM::Util->test_joino);
}

# split
{
  ok(TestCase::Lib::SPVM::Util->test_split);
}

# sprintf
{
  ok(TestCase::Lib::SPVM::Util->test_sprintf_d);
  ok(TestCase::Lib::SPVM::Util->test_sprintf_u);
  ok(TestCase::Lib::SPVM::Util->test_sprintf_ld);
  ok(TestCase::Lib::SPVM::Util->test_sprintf_lu);
  ok(TestCase::Lib::SPVM::Util->test_sprintf_f);
  ok(TestCase::Lib::SPVM::Util->test_sprintf_c);
  ok(TestCase::Lib::SPVM::Util->test_sprintf_s);
  ok(TestCase::Lib::SPVM::Util->test_sprintf_U);
  ok(TestCase::Lib::SPVM::Util->test_sprintf_percent);
  ok(TestCase::Lib::SPVM::Util->test_sprintf_all);
}

# copy_oarray
{
  ok(TestCase::Lib::SPVM::Util->test_copy_oarray);
}

# equals_oarray
{
  ok(TestCase::Lib::SPVM::Util->test_equals_oarray);
}

# strtoi
{
  ok(TestCase::Lib::SPVM::Util->test_strtoi);
  ok(TestCase::Lib::SPVM::Util->test_strtol);
  ok(TestCase::Lib::SPVM::Util->test_strtof);
  ok(TestCase::Lib::SPVM::Util->test_strtod);
}
# chomp_lf
{
  ok(TestCase::Lib::SPVM::Util->test_chomp_lf);
}
# chomp_crlf
{
  ok(TestCase::Lib::SPVM::Util->test_chomp_crlf);
}

# isalnum
{
  ok(TestCase::Lib::SPVM::Util->test_isalnum);
}

# isalpha
{
  ok(TestCase::Lib::SPVM::Util->test_isalpha);
}

# isalpha
{
  ok(TestCase::Lib::SPVM::Util->test_isblank);
}

# iscntrl
{
  ok(TestCase::Lib::SPVM::Util->test_iscntrl);
}

# isdigit
{
  ok(TestCase::Lib::SPVM::Util->test_isdigit);
}

# isgraph
{
  ok(TestCase::Lib::SPVM::Util->test_isgraph);
}

# islower
{
  ok(TestCase::Lib::SPVM::Util->test_islower);
}

# isprint
{
  ok(TestCase::Lib::SPVM::Util->test_isprint);
}

# isprint
{
  ok(TestCase::Lib::SPVM::Util->test_isprint);
}

# ispunct
{
  ok(TestCase::Lib::SPVM::Util->test_ispunct);
}

# isspace
{
  ok(TestCase::Lib::SPVM::Util->test_isspace);
}

# isupper
{
  ok(TestCase::Lib::SPVM::Util->test_isupper);
}

# isxdigit
{
  ok(TestCase::Lib::SPVM::Util->test_isxdigit);
}

# tolower
{
  ok(TestCase::Lib::SPVM::Util->test_tolower);
}

# toupper
{
  ok(TestCase::Lib::SPVM::Util->test_toupper);
}

# is_perl_space
{
  ok(TestCase::Lib::SPVM::Util->test_is_perl_space);
}

# is_perl_word
{
  ok(TestCase::Lib::SPVM::Util->test_is_perl_word);
}

# crand
{
  ok(TestCase::Lib::SPVM::Util->test_crand);
}

# rand
{
  ok(TestCase::Lib::SPVM::Util->test_rand);
}

# srand
SKIP: {
  if ($^O eq 'openbsd') {
    skip "openbsd srand don't fllow POSIX", 6;
  }
  
  {
    ok(TestCase::Lib::SPVM::Util->test_srand);
  }
}

# RAND_MAX
{
  ok(TestCase::Lib::SPVM::Util->test_RAND_MAX);
}

# uc
{
  ok(TestCase::Lib::SPVM::Util->test_uc);
}

# lcfirst
{
  ok(TestCase::Lib::SPVM::Util->test_lcfirst);
}

# lc
{
  ok(TestCase::Lib::SPVM::Util->test_lc);
}

# replace
{
  ok(TestCase::Lib::SPVM::Util->test_replace_all);
}

# replace
{
  ok(TestCase::Lib::SPVM::Util->test_replace);
}

# memmoveb
{
  ok(TestCase::Lib::SPVM::Util->test_memmoveb);
}

# memcpyb
{
  ok(TestCase::Lib::SPVM::Util->test_memcpyb);
}

# index
{
  ok(TestCase::Lib::SPVM::Util->test_index);
}

# rindex
{
  ok(TestCase::Lib::SPVM::Util->test_rindex);
}

# contains
{
  ok(TestCase::Lib::SPVM::Util->test_contains);
}

# new_object_array_proto
{
  # sliceb
  ok(TestCase::Lib::SPVM::Util->test_new_object_array_proto);
}

# slice
{
  # sliceb
  ok(TestCase::Lib::SPVM::Util->test_sliceb);

  # slices
  ok(TestCase::Lib::SPVM::Util->test_slices);

  # slicei
  ok(TestCase::Lib::SPVM::Util->test_slicei);

  # slicel
  ok(TestCase::Lib::SPVM::Util->test_slicel);

  # slicef
  ok(TestCase::Lib::SPVM::Util->test_slicef);

  # sliced
  ok(TestCase::Lib::SPVM::Util->test_sliced);

  # sliced
  ok(TestCase::Lib::SPVM::Util->test_sliceo);
}

# reverse
{
  # reverseb
  ok(TestCase::Lib::SPVM::Util->test_reverseb);

  # reverses
  ok(TestCase::Lib::SPVM::Util->test_reverses);

  # reversei
  ok(TestCase::Lib::SPVM::Util->test_reversei);

  # reversel
  ok(TestCase::Lib::SPVM::Util->test_reversel);

  # reversef
  ok(TestCase::Lib::SPVM::Util->test_reversef);

  # reversed
  ok(TestCase::Lib::SPVM::Util->test_reversed);

  # reversed
  ok(TestCase::Lib::SPVM::Util->test_reverseo);
}

# join
{
  ok(TestCase::Lib::SPVM::Util->test_join);
  ok(TestCase::Lib::SPVM::Util->test_joinb);
  ok(TestCase::Lib::SPVM::Util->test_joins);
  ok(TestCase::Lib::SPVM::Util->test_joini);
  ok(TestCase::Lib::SPVM::Util->test_joinl);
  ok(TestCase::Lib::SPVM::Util->test_joinf);
  ok(TestCase::Lib::SPVM::Util->test_joind);
}

# E
{
  ok(TestCase::Lib::SPVM::Util->test_E);
}

# PI
{
  ok(TestCase::Lib::SPVM::Util->test_PI);
}

# equals
{
  # equals_barray
  ok(TestCase::Lib::SPVM::Util->test_equals_barray);

  # equals_sarray
  ok(TestCase::Lib::SPVM::Util->test_equals_sarray);

  # equals_iarray
  ok(TestCase::Lib::SPVM::Util->test_equals_iarray);

  # equeals_larray
  ok(TestCase::Lib::SPVM::Util->test_equals_larray);

  # equals_farray
  ok(TestCase::Lib::SPVM::Util->test_equals_farray);

  # equals_darray
  ok(TestCase::Lib::SPVM::Util->test_equals_darray);

  # equals_strarray
  ok(TestCase::Lib::SPVM::Util->test_equals_strarray);
}

# Copy
{
  # copy_str
  ok(TestCase::Lib::SPVM::Util->test_copy_str);

  # copy_barray
  ok(TestCase::Lib::SPVM::Util->test_copy_barray);

  # copy_sarray
  ok(TestCase::Lib::SPVM::Util->test_copy_sarray);

  # copy_iarray
  ok(TestCase::Lib::SPVM::Util->test_copy_iarray);

  # copy_larray
  ok(TestCase::Lib::SPVM::Util->test_copy_larray);

  # copy_farray
  ok(TestCase::Lib::SPVM::Util->test_copy_farray);

  # copy_darray
  ok(TestCase::Lib::SPVM::Util->test_copy_darray);

  # copy_strarray
  ok(TestCase::Lib::SPVM::Util->test_copy_strarray);
}

# Constant integral functions
{
  is(SPVM::Util->INT8_MAX, 127);
  is(SPVM::Util->INT8_MIN, -128);
  is(SPVM::Util->INT16_MAX, 32767);
  is(SPVM::Util->INT16_MIN, -32768);
  is(SPVM::Util->INT32_MAX, 2147483647);
  is(SPVM::Util->INT32_MIN, -2147483648);
  is(SPVM::Util->INT64_MAX, 9223372036854775807);
  is(SPVM::Util->INT64_MIN, -9223372036854775808);
}

# Constant floating point number functions
{
  is(SPVM::Util->FLT_MAX, POSIX::FLT_MAX);
  is(SPVM::Util->FLT_MIN, POSIX::FLT_MIN);
  is(SPVM::Util->DBL_MAX, POSIX::DBL_MAX);
  is(SPVM::Util->DBL_MIN, POSIX::DBL_MIN);
}

{
  ok(TestCase::Lib::SPVM::Util->test_byte_constant);
  ok(TestCase::Lib::SPVM::Util->test_short_constant);
  ok(TestCase::Lib::SPVM::Util->test_int_constant);
}

{
  is(SPVM::Util->INT8_MAX, $BYTE_MAX);
  is(SPVM::Util->INT8_MIN, $BYTE_MIN);
  is(SPVM::Util->INT16_MAX, $SHORT_MAX);
  is(SPVM::Util->INT16_MIN, $SHORT_MIN);
  is(SPVM::Util->INT32_MAX, $INT_MAX);
  is(SPVM::Util->INT32_MIN, $INT_MIN);
  is(SPVM::Util->INT64_MAX, $LONG_MAX);
  is(SPVM::Util->INT64_MIN, $LONG_MIN);
}
{
  # Check not Inf or NaN in Perl value
  like(SPVM::Util->FLT_MAX(), qr/[0-9]/);
  like(SPVM::Util->FLT_MIN(), qr/[0-9]/);
}

# getenv
=pod
{
  # TODO: Windows compatibility
  $ENV{SPVM_ENV_NAME} = "SPVM_ENV_VALUE";
  ok(TestCase::Lib::SPVM::Util->test_getenv);
}
=cut

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
