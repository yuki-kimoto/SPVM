use lib "t/lib";
use TestAuto;

use strict;
use warnings;
use Devel::Peek;

use Test::More 'no_plan';


use FindBin;
use lib "$FindBin::Bin/lib";

use SPVM 'TestCase::Dump';

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# dump
{
  is(TestCase::Dump->dump_string, '"Hello"');
  is(TestCase::Dump->dump_undef, 'undef');
  like(TestCase::Dump->dump_byte_array, qr/^\s*\[\s*1\s*,\s*2\s*\]\s*/s);
  like(TestCase::Dump->dump_byte_array, qr/\s*:\s*byte\[\]/);
  like(TestCase::Dump->dump_short_array, qr/^\s*\[\s*1\s*,\s*2\s*\]\s*/s);
  like(TestCase::Dump->dump_short_array, qr/\s*:\s*short\[\]/);
  like(TestCase::Dump->dump_int_array, qr/^\s*\[\s*1\s*,\s*2\s*\]\s*/s);
  like(TestCase::Dump->dump_int_array, qr/\s*:\s*int\[\]/);
  like(TestCase::Dump->dump_long_array, qr/^\s*\[\s*1\s*,\s*2\s*\]\s*/s);
  like(TestCase::Dump->dump_long_array, qr/\s*:\s*long\[\]/);
  like(TestCase::Dump->dump_float_array, qr/^\s*\[\s*1\.2\s*,\s*2\.4\s*\]\s*/s);
  like(TestCase::Dump->dump_float_array, qr/\s*:\s*float\[\]/);
  like(TestCase::Dump->dump_double_array, qr/^\s*\[\s*1\.2\s*,\s*2\.4\s*\]\s*/s);
  like(TestCase::Dump->dump_double_array, qr/\s*:\s*double\[\]/);

  like(TestCase::Dump->dump_multi_numeric_byte_array, qr/\s*\[\s*\{\s*x\s*=>\s*1\s*,\s*y\s*=>\s*2\s*,\s*z\s*=>\s*3\s*}\s*,\s*{\s*x\s*=>\s*4\s*,\s*y\s*=>\s*5\s*,\s*z\s*=>\s*6\s*}\s*\]\s*/s);
  like(TestCase::Dump->dump_multi_numeric_byte_array, qr/\s*:\s*TestCase::Point_3b\[\]/);
  like(TestCase::Dump->dump_multi_numeric_short_array, qr/\s*\[\s*\{\s*x\s*=>\s*1\s*,\s*y\s*=>\s*2\s*,\s*z\s*=>\s*3\s*}\s*,\s*{\s*x\s*=>\s*4\s*,\s*y\s*=>\s*5\s*,\s*z\s*=>\s*6\s*}\s*\]\s*/s);
  like(TestCase::Dump->dump_multi_numeric_short_array, qr/\s*:\s*TestCase::Point_3s\[\]/);
  like(TestCase::Dump->dump_multi_numeric_int_array, qr/\s*\[\s*\{\s*x\s*=>\s*1\s*,\s*y\s*=>\s*2\s*,\s*z\s*=>\s*3\s*}\s*,\s*{\s*x\s*=>\s*4\s*,\s*y\s*=>\s*5\s*,\s*z\s*=>\s*6\s*}\s*\]\s*/s);
  like(TestCase::Dump->dump_multi_numeric_int_array, qr/\s*:\s*TestCase::Point_3i\[\]/);
  like(TestCase::Dump->dump_multi_numeric_long_array, qr/\s*\[\s*\{\s*x\s*=>\s*1\s*,\s*y\s*=>\s*2\s*,\s*z\s*=>\s*3\s*}\s*,\s*{\s*x\s*=>\s*4\s*,\s*y\s*=>\s*5\s*,\s*z\s*=>\s*6\s*}\s*\]\s*/s);
  like(TestCase::Dump->dump_multi_numeric_long_array, qr/\s*:\s*TestCase::Point_3l\[\]/);

  like(TestCase::Dump->dump_string_array, qr/^\s*\[\s*"abc"\s*,\s*"def"\s*,\s*undef\s*\]\s*/s);
  like(TestCase::Dump->dump_string_array, qr/\s*:\s*string\[\]/);

  like(TestCase::Dump->dump_string_array_of_array, qr/^\s*\[\s*\[\s*"abc"\s*,\s*"def"\s*,\s*undef\s*\]\s*[^,]*?,\s*\[\s*"a"\s*,\s*"b"\s*\]\s*[^\]]*\]/s);
  like(TestCase::Dump->dump_string_array_of_array, qr/\s*:\s*string\[\]\[\]/);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
