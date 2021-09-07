use lib "t/lib";
use TestAuto;

use strict;
use warnings;
use Devel::Peek;

use Test::More 'no_plan';


use FindBin;
use lib "$FindBin::Bin/lib";

use SPVM 'SPVM::TestCase::Dump';

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# dump
{
  is(SPVM::TestCase::Dump->dump_string, '"Hello"');
  is(SPVM::TestCase::Dump->dump_undef, 'undef');
  like(SPVM::TestCase::Dump->dump_byte_array, qr/^\s*\[\s*1\s*,\s*2\s*\]\s*/s);
  like(SPVM::TestCase::Dump->dump_byte_array, qr/\s*:\s*byte\[\]/);
  like(SPVM::TestCase::Dump->dump_short_array, qr/^\s*\[\s*1\s*,\s*2\s*\]\s*/s);
  like(SPVM::TestCase::Dump->dump_short_array, qr/\s*:\s*short\[\]/);
  like(SPVM::TestCase::Dump->dump_int_array, qr/^\s*\[\s*1\s*,\s*2\s*\]\s*/s);
  like(SPVM::TestCase::Dump->dump_int_array, qr/\s*:\s*int\[\]/);
  like(SPVM::TestCase::Dump->dump_long_array, qr/^\s*\[\s*1\s*,\s*2\s*\]\s*/s);
  like(SPVM::TestCase::Dump->dump_long_array, qr/\s*:\s*long\[\]/);
  like(SPVM::TestCase::Dump->dump_float_array, qr/^\s*\[\s*1\.2\s*,\s*2\.4\s*\]\s*/s);
  like(SPVM::TestCase::Dump->dump_float_array, qr/\s*:\s*float\[\]/);
  like(SPVM::TestCase::Dump->dump_double_array, qr/^\s*\[\s*1\.2\s*,\s*2\.4\s*\]\s*/s);
  like(SPVM::TestCase::Dump->dump_double_array, qr/\s*:\s*double\[\]/);

  like(SPVM::TestCase::Dump->dump_multi_numeric_byte_array, qr/\s*\[\s*\{\s*x\s*=>\s*1\s*,\s*y\s*=>\s*2\s*,\s*z\s*=>\s*3\s*}\s*,\s*{\s*x\s*=>\s*4\s*,\s*y\s*=>\s*5\s*,\s*z\s*=>\s*6\s*}\s*\]\s*/s);
  like(SPVM::TestCase::Dump->dump_multi_numeric_byte_array, qr/\s*:\s*SPVM::TestCase::Point_3b\[\]/);
  like(SPVM::TestCase::Dump->dump_multi_numeric_short_array, qr/\s*\[\s*\{\s*x\s*=>\s*1\s*,\s*y\s*=>\s*2\s*,\s*z\s*=>\s*3\s*}\s*,\s*{\s*x\s*=>\s*4\s*,\s*y\s*=>\s*5\s*,\s*z\s*=>\s*6\s*}\s*\]\s*/s);
  like(SPVM::TestCase::Dump->dump_multi_numeric_short_array, qr/\s*:\s*SPVM::TestCase::Point_3s\[\]/);
  like(SPVM::TestCase::Dump->dump_multi_numeric_int_array, qr/\s*\[\s*\{\s*x\s*=>\s*1\s*,\s*y\s*=>\s*2\s*,\s*z\s*=>\s*3\s*}\s*,\s*{\s*x\s*=>\s*4\s*,\s*y\s*=>\s*5\s*,\s*z\s*=>\s*6\s*}\s*\]\s*/s);
  like(SPVM::TestCase::Dump->dump_multi_numeric_int_array, qr/\s*:\s*SPVM::TestCase::Point_3i\[\]/);
  like(SPVM::TestCase::Dump->dump_multi_numeric_long_array, qr/\s*\[\s*\{\s*x\s*=>\s*1\s*,\s*y\s*=>\s*2\s*,\s*z\s*=>\s*3\s*}\s*,\s*{\s*x\s*=>\s*4\s*,\s*y\s*=>\s*5\s*,\s*z\s*=>\s*6\s*}\s*\]\s*/s);
  like(SPVM::TestCase::Dump->dump_multi_numeric_long_array, qr/\s*:\s*SPVM::TestCase::Point_3l\[\]/);

  like(SPVM::TestCase::Dump->dump_string_array, qr/^\s*\[\s*"abc"\s*,\s*"def"\s*,\s*undef\s*\]\s*/s);
  like(SPVM::TestCase::Dump->dump_string_array, qr/\s*:\s*string\[\]/);

  like(SPVM::TestCase::Dump->dump_string_array_of_array, qr/^\s*\[\s*\[\s*"abc"\s*,\s*"def"\s*,\s*undef\s*\]\s*[^,]*?,\s*\[\s*"a"\s*,\s*"b"\s*\]\s*[^\]]*\]/s);
  like(SPVM::TestCase::Dump->dump_string_array_of_array, qr/\s*:\s*string\[\]\[\]/);

  like(SPVM::TestCase::Dump->dump_object, qr/{\s*byte_value\s*=>\s*1\s*,\s*short_value\s*=>\s*2\s*,\s*int_value\s*=>\s*3\s*,\s*long_value\s*=>\s*4\s*,\s*float_value\s*=>\s*1\.1\s*,\s*double_value\s*=>\s*1\.2,\s*string_value\s*=>\s*"a"\s*,\s*int_array\s*=>\s*\[\s*1\s*,\s*2\s*,\s*3\s*\].[^,]*,\s*object_value\s*=>\s*{[^}]*}[^}]*}/);
  like(SPVM::TestCase::Dump->dump_object, qr/\s*:\s*SPVM::TestCase::DumpTest1/);

  like(SPVM::TestCase::Dump->dump_object_reuse, qr/object_value\s*=>\s*REUSE_OBJECT/);
  like(SPVM::TestCase::Dump->dump_object_reuse, qr/REUSE_OBJECT\([^\)]*\)\s*,/);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
