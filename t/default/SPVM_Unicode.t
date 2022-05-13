use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Lib::Unicode';



# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

{
  ok(SPVM::TestCase::Lib::Unicode->uchar);
  ok(SPVM::TestCase::Lib::Unicode->uchar_to_utf8);
  ok(SPVM::TestCase::Lib::Unicode->utf32_to_utf16);
  ok(SPVM::TestCase::Lib::Unicode->utf16_to_utf32);
  ok(SPVM::TestCase::Lib::Unicode->utf8_to_utf16);
  ok(SPVM::TestCase::Lib::Unicode->utf16_to_utf8);
  ok(SPVM::TestCase::Lib::Unicode->ERROR_INVALID_UTF8);
  ok(SPVM::TestCase::Lib::Unicode->is_unicode_scalar_value);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
