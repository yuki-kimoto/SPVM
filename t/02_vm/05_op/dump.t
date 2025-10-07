use lib "t/testlib";
use TestAuto;

use strict;
use warnings;
use utf8;

use Devel::Peek;

use Test::More;

use SPVM 'TestCase::Operator::Dump';

# Start objects count
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count;

# dump
{
  is(SPVM::TestCase::Operator::Dump->dump_string, '"Hello"');
  is(SPVM::TestCase::Operator::Dump->dump_string_utf8, '"あいう"');
  is(SPVM::TestCase::Operator::Dump->dump_string_non_utf8, '"\\x{00}\\x{01}\x{09}"');
  is(SPVM::TestCase::Operator::Dump->dump_undef, 'undef');
  like(SPVM::TestCase::Operator::Dump->dump_byte_array, qr/^\s*\[\s*1\s*,\s*2,\s*\]\s*/s);
  like(SPVM::TestCase::Operator::Dump->dump_byte_array, qr/\s*:\s*byte\[\]/);
  like(SPVM::TestCase::Operator::Dump->dump_short_array, qr/^\s*\[\s*1\s*,\s*2,\s*\]\s*/s);
  like(SPVM::TestCase::Operator::Dump->dump_short_array, qr/\s*:\s*short\[\]/);
  like(SPVM::TestCase::Operator::Dump->dump_int_array, qr/^\s*\[\s*1\s*,\s*2,\s*\]\s*/s);
  like(SPVM::TestCase::Operator::Dump->dump_int_array, qr/\s*:\s*int\[\]/);
  like(SPVM::TestCase::Operator::Dump->dump_long_array, qr/^\s*\[\s*1\s*,\s*2,\s*\]\s*/s);
  like(SPVM::TestCase::Operator::Dump->dump_long_array, qr/\s*:\s*long\[\]/);
  like(SPVM::TestCase::Operator::Dump->dump_float_array, qr/^\s*\[\s*1\.2\s*,\s*2\.4,\s*\]\s*/s);
  like(SPVM::TestCase::Operator::Dump->dump_float_array, qr/\s*:\s*float\[\]/);
  like(SPVM::TestCase::Operator::Dump->dump_double_array, qr/^\s*\[\s*1\.2\s*,\s*2\.4,\s*\]\s*/s);
  like(SPVM::TestCase::Operator::Dump->dump_double_array, qr/\s*:\s*double\[\]/);

  like(SPVM::TestCase::Operator::Dump->dump_multi_numeric_byte_array, qr/\s*\[\s*\{\s*x\s*=>\s*1\s*,\s*y\s*=>\s*2\s*,\s*z\s*=>\s*3,\s*}\s*,\s*{\s*x\s*=>\s*4\s*,\s*y\s*=>\s*5\s*,\s*z\s*=>\s*6,\s*},\s*\]\s*/s);
  like(SPVM::TestCase::Operator::Dump->dump_multi_numeric_byte_array, qr/\s*:\s*TestCase::Point_3b\[\]/);
  like(SPVM::TestCase::Operator::Dump->dump_multi_numeric_short_array, qr/\s*\[\s*\{\s*x\s*=>\s*1\s*,\s*y\s*=>\s*2\s*,\s*z\s*=>\s*3,\s*}\s*,\s*{\s*x\s*=>\s*4\s*,\s*y\s*=>\s*5\s*,\s*z\s*=>\s*6,\s*},\s*\]\s*/s);
  like(SPVM::TestCase::Operator::Dump->dump_multi_numeric_short_array, qr/\s*:\s*TestCase::Point_3s\[\]/);
  like(SPVM::TestCase::Operator::Dump->dump_multi_numeric_int_array, qr/\s*\[\s*\{\s*x\s*=>\s*1\s*,\s*y\s*=>\s*2\s*,\s*z\s*=>\s*3,\s*}\s*,\s*{\s*x\s*=>\s*4\s*,\s*y\s*=>\s*5\s*,\s*z\s*=>\s*6,\s*},\s*\]\s*/s);
  like(SPVM::TestCase::Operator::Dump->dump_multi_numeric_int_array, qr/\s*:\s*TestCase::Point_3i\[\]/);
  like(SPVM::TestCase::Operator::Dump->dump_multi_numeric_long_array, qr/\s*\[\s*\{\s*x\s*=>\s*1\s*,\s*y\s*=>\s*2\s*,\s*z\s*=>\s*3,\s*}\s*,\s*{\s*x\s*=>\s*4\s*,\s*y\s*=>\s*5\s*,\s*z\s*=>\s*6,\s*},\s*\]\s*/s);
  like(SPVM::TestCase::Operator::Dump->dump_multi_numeric_long_array, qr/\s*:\s*TestCase::Point_3l\[\]/);

  like(SPVM::TestCase::Operator::Dump->dump_string_array, qr/^\s*\[\s*"abc"\s*,\s*"def"\s*,\s*undef,\s*\]\s*/s);
  like(SPVM::TestCase::Operator::Dump->dump_string_array, qr/\s*:\s*string\[\]/);

  like(SPVM::TestCase::Operator::Dump->dump_string_array_of_array, qr/^\s*\[\s*\[\s*"abc"\s*,\s*"def"\s*,\s*undef,\s*\]\s*[^,]*?,\s*\[\s*"a"\s*,\s*"b",\s*\]\s*[^\]]*\]/s);
  like(SPVM::TestCase::Operator::Dump->dump_string_array_of_array, qr/\s*:\s*string\[\]\[\]/);

  like(SPVM::TestCase::Operator::Dump->dump_object, qr/TestCase::Operator::DumpTest1 \(.+\) \{\s+string_value => "a",\s+int_array\s+=>\s+\[\s+1,\s+2,\s+3,\s+\]\s+:\s+int\[\]\(.+\),\s+object_value\s+=>\s+TestCase::Operator::DumpTest1\s+\(.+\)\s+\{\s+\s+string_value\s+=>\s+undef,\s+\s+int_array\s+=>\s+undef,\s+\s+object_value\s+=>\s+undef,\s+\s+double_value\s+=>\s+0,\s+\s+long_value\s+=>\s+0,\s+\s+float_value\s+=>\s+0,\s+\s+int_value\s+=>\s+0,\s+\s+short_value\s+=>\s+0,\s+\s+byte_value\s+=>\s+0,\s+\s+\},\s+\s+double_value\s+=>\s+1\.2,\s+\s+long_value\s+=>\s+4,\s+\s+float_value\s+=>\s+1\.1,\s+\s+int_value\s+=>\s+3,\s+\s+short_value\s+=>\s+2,\s+\s+byte_value\s+=>\s+1,\s+\}/s);

  like(SPVM::TestCase::Operator::Dump->dump_object_reuse, qr/object_value\s*=>\s*REUSE_OBJECT/);
  like(SPVM::TestCase::Operator::Dump->dump_object_reuse, qr/REUSE_OBJECT\([^\)]*\)\s*,/);

  like(SPVM::TestCase::Operator::Dump->dump_object_reuse_weaken, qr/object_value\s*=>\s*REUSE_OBJECT/);
  like(SPVM::TestCase::Operator::Dump->dump_object_reuse_weaken, qr/REUSE_OBJECT\([^\)]*\)\s*,/);
  
  {
    my $expected_q = quotemeta '"\x{02}\x{8E}?A\x{95}\x{E3}\x{09}XT\x{17}_\x{C0} \x{E9}"';
    
    like(SPVM::TestCase::Operator::Dump->dump_binary, qr/$expected_q/);
  }
}

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
