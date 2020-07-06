use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Lib::SPVM::Unicode';



# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

{
  ok(TestCase::Lib::SPVM::Unicode->uchar);
  ok(TestCase::Lib::SPVM::Unicode->uchar_to_utf8);
  ok(TestCase::Lib::SPVM::Unicode->utf32_to_utf16);
  ok(TestCase::Lib::SPVM::Unicode->utf16_to_utf32);
  ok(TestCase::Lib::SPVM::Unicode->utf8_to_utf16);
  ok(TestCase::Lib::SPVM::Unicode->utf16_to_utf8);
  ok(TestCase::Lib::SPVM::Unicode->ERROR_INVALID_UTF8);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
