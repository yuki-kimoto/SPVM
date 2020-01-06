use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Lib::SPVM::Webkit::JSON';

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# encode
{
  ok(TestCase::Lib::SPVM::Webkit::JSON->encode_null);
  ok(TestCase::Lib::SPVM::Webkit::JSON->encode_flat_hash);
  ok(TestCase::Lib::SPVM::Webkit::JSON->encode_flat_list);
  ok(TestCase::Lib::SPVM::Webkit::JSON->encode_int);
  ok(TestCase::Lib::SPVM::Webkit::JSON->encode_double);
  ok(TestCase::Lib::SPVM::Webkit::JSON->encode_bool);
  ok(TestCase::Lib::SPVM::Webkit::JSON->encode_string);
  ok(TestCase::Lib::SPVM::Webkit::JSON->encode_nested_hash);
}

# decode
{
  ok(TestCase::Lib::SPVM::Webkit::JSON->decode_null);
  ok(TestCase::Lib::SPVM::Webkit::JSON->decode_flat_hash);
  ok(TestCase::Lib::SPVM::Webkit::JSON->decode_flat_list);
  ok(TestCase::Lib::SPVM::Webkit::JSON->decode_double);
  ok(TestCase::Lib::SPVM::Webkit::JSON->decode_bool);
  ok(TestCase::Lib::SPVM::Webkit::JSON->decode_string);
  ok(TestCase::Lib::SPVM::Webkit::JSON->decode_nested_hash);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
