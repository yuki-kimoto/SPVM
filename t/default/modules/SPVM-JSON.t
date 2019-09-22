use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::JSON';

# Start objects count
my $start_memory_blocks_count = SPVM::memory_blocks_count();

# encode
{
  ok(TestCase::JSON->encode_null);
  ok(TestCase::JSON->encode_flat_hash);
  ok(TestCase::JSON->encode_flat_list);
  ok(TestCase::JSON->encode_int);
  ok(TestCase::JSON->encode_double);
  ok(TestCase::JSON->encode_bool);
  ok(TestCase::JSON->encode_string);
  ok(TestCase::JSON->encode_nested_hash);
  ok(TestCase::JSON->test_format_name_separator);
  ok(TestCase::JSON->test_special_chars);
  ok(TestCase::JSON->test_map_inf_nan_to_undef);
}

# decode
{
  ok(TestCase::JSON->decode_null);
  ok(TestCase::JSON->decode_flat_hash);
  ok(TestCase::JSON->decode_flat_list);
  ok(TestCase::JSON->decode_int);
  ok(TestCase::JSON->decode_double);
  ok(TestCase::JSON->decode_bool);
  ok(TestCase::JSON->decode_string);
  ok(TestCase::JSON->decode_nested_hash);
}

# All object is freed
my $end_memory_blocks_count = SPVM::memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
