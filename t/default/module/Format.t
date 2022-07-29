use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::Module::Format';

use SPVM 'Format';

use TestFile;

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

# sprintf
{
  ok(SPVM::TestCase::Module::Format->sprintf_d);
  ok(SPVM::TestCase::Module::Format->sprintf_u);
  ok(SPVM::TestCase::Module::Format->sprintf_ld);
  ok(SPVM::TestCase::Module::Format->sprintf_lu);
  ok(SPVM::TestCase::Module::Format->sprintf_f);
  ok(SPVM::TestCase::Module::Format->sprintf_g);
  ok(SPVM::TestCase::Module::Format->sprintf_c);
  ok(SPVM::TestCase::Module::Format->sprintf_s);
  ok(SPVM::TestCase::Module::Format->sprintf_percent);
  ok(SPVM::TestCase::Module::Format->sprintf_x);
  ok(SPVM::TestCase::Module::Format->sprintf_X);
  ok(SPVM::TestCase::Module::Format->sprintf_lx);
  ok(SPVM::TestCase::Module::Format->sprintf_lX);
  ok(SPVM::TestCase::Module::Format->sprintf_all);
  like(SPVM::TestCase::Module::Format->sprintf_p_value, qr/^(0(x|X))?[0-9a-fA-F]+$/);
  
  # Extra
  {
    # %d
    {
      is(sprintf("%d", 1), SPVM::Format->sprintf("%d", SPVM::new_any_object_array([SPVM::Int->new(1)])));
      is(sprintf("%0100d", 1), SPVM::Format->sprintf("%0100d", SPVM::new_any_object_array([SPVM::Int->new(1)])));
      is(sprintf("%03d", 1), SPVM::Format->sprintf("%03d", SPVM::new_any_object_array([SPVM::Int->new(1)])));
      is(sprintf("%+3d", 1), SPVM::Format->sprintf("%+3d", SPVM::new_any_object_array([SPVM::Int->new(1)])));
      is(sprintf("%-3d", 1), SPVM::Format->sprintf("%-3d", SPVM::new_any_object_array([SPVM::Int->new(1)])));
      is(sprintf("%03d", 1111), SPVM::Format->sprintf("%03d", SPVM::new_any_object_array([SPVM::Int->new(1111)])));
      is(sprintf("%+3d", 1111), SPVM::Format->sprintf("%+3d", SPVM::new_any_object_array([SPVM::Int->new(1111)])));
      is(sprintf("%-3d", 1111), SPVM::Format->sprintf("%-3d", SPVM::new_any_object_array([SPVM::Int->new(1111)])));
      is(sprintf("%03d", 111), SPVM::Format->sprintf("%03d", SPVM::new_any_object_array([SPVM::Int->new(111)])));
      is(sprintf("%+3d", 111), SPVM::Format->sprintf("%+3d", SPVM::new_any_object_array([SPVM::Int->new(111)])));
      is(sprintf("%-3d", 111), SPVM::Format->sprintf("%-3d", SPVM::new_any_object_array([SPVM::Int->new(111)])));
    }
    
    # %ld
    {
      is(sprintf("%lld", 1), SPVM::Format->sprintf("%ld", SPVM::new_any_object_array([SPVM::Long->new(1)])));
      is(sprintf("%0100lld", 1), SPVM::Format->sprintf("%0100ld", SPVM::new_any_object_array([SPVM::Long->new(1)])));
      is(sprintf("%03lld", 1), SPVM::Format->sprintf("%03ld", SPVM::new_any_object_array([SPVM::Long->new(1)])));
      is(sprintf("%+3lld", 1), SPVM::Format->sprintf("%+3ld", SPVM::new_any_object_array([SPVM::Long->new(1)])));
      is(sprintf("%-3lld", 1), SPVM::Format->sprintf("%-3ld", SPVM::new_any_object_array([SPVM::Long->new(1)])));
      is(sprintf("%03lld", 1111), SPVM::Format->sprintf("%03ld", SPVM::new_any_object_array([SPVM::Long->new(1111)])));
      is(sprintf("%+3lld", 1111), SPVM::Format->sprintf("%+3ld", SPVM::new_any_object_array([SPVM::Long->new(1111)])));
      is(sprintf("%-3lld", 1111), SPVM::Format->sprintf("%-3ld", SPVM::new_any_object_array([SPVM::Long->new(1111)])));
      is(sprintf("%03lld", 111), SPVM::Format->sprintf("%03ld", SPVM::new_any_object_array([SPVM::Long->new(111)])));
      is(sprintf("%+3lld", 111), SPVM::Format->sprintf("%+3ld", SPVM::new_any_object_array([SPVM::Long->new(111)])));
      is(sprintf("%-3lld", 111), SPVM::Format->sprintf("%-3ld", SPVM::new_any_object_array([SPVM::Long->new(111)])));
    }
    
    # %u
    {
      is(sprintf("%u", 1), SPVM::Format->sprintf("%u", SPVM::new_any_object_array([SPVM::Int->new(1)])));
      is(sprintf("%0100u", 1), SPVM::Format->sprintf("%0100u", SPVM::new_any_object_array([SPVM::Int->new(1)])));
      is(sprintf("%03u", 1), SPVM::Format->sprintf("%03u", SPVM::new_any_object_array([SPVM::Int->new(1)])));
      is(sprintf("%+3u", 1), SPVM::Format->sprintf("%+3u", SPVM::new_any_object_array([SPVM::Int->new(1)])));
      is(sprintf("%-3u", 1), SPVM::Format->sprintf("%-3u", SPVM::new_any_object_array([SPVM::Int->new(1)])));
      is(sprintf("%03u", 1111), SPVM::Format->sprintf("%03u", SPVM::new_any_object_array([SPVM::Int->new(1111)])));
      is(sprintf("%+3u", 1111), SPVM::Format->sprintf("%+3u", SPVM::new_any_object_array([SPVM::Int->new(1111)])));
      is(sprintf("%-3u", 1111), SPVM::Format->sprintf("%-3u", SPVM::new_any_object_array([SPVM::Int->new(1111)])));
      is(sprintf("%03u", 111), SPVM::Format->sprintf("%03u", SPVM::new_any_object_array([SPVM::Int->new(111)])));
      is(sprintf("%+3u", 111), SPVM::Format->sprintf("%+3u", SPVM::new_any_object_array([SPVM::Int->new(111)])));
      is(sprintf("%-3u", 111), SPVM::Format->sprintf("%-3u", SPVM::new_any_object_array([SPVM::Int->new(111)])));
      is(sprintf("%u", -1 & 0xFFFFFFFF), SPVM::Format->sprintf("%u", SPVM::new_any_object_array([SPVM::Int->new(-1)])));
      is(sprintf("%0100u", -1 & 0xFFFFFFFF), SPVM::Format->sprintf("%0100u", SPVM::new_any_object_array([SPVM::Int->new(-1)])));
      is(sprintf("%03u", -1 & 0xFFFFFFFF), SPVM::Format->sprintf("%03u", SPVM::new_any_object_array([SPVM::Int->new(-1)])));
      is(sprintf("%+3u", -1 & 0xFFFFFFFF), SPVM::Format->sprintf("%+3u", SPVM::new_any_object_array([SPVM::Int->new(-1)])));
      is(sprintf("%-3u", -1 & 0xFFFFFFFF), SPVM::Format->sprintf("%-3u", SPVM::new_any_object_array([SPVM::Int->new(-1)])));
      is(sprintf("%03u", -1111 & 0xFFFFFFFF), SPVM::Format->sprintf("%03u", SPVM::new_any_object_array([SPVM::Int->new(-1111)])));
      is(sprintf("%+3u", -1111 & 0xFFFFFFFF), SPVM::Format->sprintf("%+3u", SPVM::new_any_object_array([SPVM::Int->new(-1111)])));
      is(sprintf("%-3u", -1111 & 0xFFFFFFFF), SPVM::Format->sprintf("%-3u", SPVM::new_any_object_array([SPVM::Int->new(-1111)])));
      is(sprintf("%03u", -111 & 0xFFFFFFFF), SPVM::Format->sprintf("%03u", SPVM::new_any_object_array([SPVM::Int->new(-111)])));
      is(sprintf("%+3u", -111 & 0xFFFFFFFF), SPVM::Format->sprintf("%+3u", SPVM::new_any_object_array([SPVM::Int->new(-111)])));
      is(sprintf("%-3u", -111 & 0xFFFFFFFF), SPVM::Format->sprintf("%-3u", SPVM::new_any_object_array([SPVM::Int->new(-111)])));
    }
    
    # %x
    {
      is(sprintf("%x", 1), SPVM::Format->sprintf("%x", SPVM::new_any_object_array([SPVM::Int->new(1)])));
      is(sprintf("%0100x", 1), SPVM::Format->sprintf("%0100x", SPVM::new_any_object_array([SPVM::Int->new(1)])));
      is(sprintf("%03x", 1), SPVM::Format->sprintf("%03x", SPVM::new_any_object_array([SPVM::Int->new(1)])));
      is(sprintf("%+3x", 1), SPVM::Format->sprintf("%+3x", SPVM::new_any_object_array([SPVM::Int->new(1)])));
      is(sprintf("%-3x", 1), SPVM::Format->sprintf("%-3x", SPVM::new_any_object_array([SPVM::Int->new(1)])));
      is(sprintf("%03x", 1111), SPVM::Format->sprintf("%03x", SPVM::new_any_object_array([SPVM::Int->new(1111)])));
      is(sprintf("%+3x", 1111), SPVM::Format->sprintf("%+3x", SPVM::new_any_object_array([SPVM::Int->new(1111)])));
      is(sprintf("%-3x", 1111), SPVM::Format->sprintf("%-3x", SPVM::new_any_object_array([SPVM::Int->new(1111)])));
      is(sprintf("%03x", 111), SPVM::Format->sprintf("%03x", SPVM::new_any_object_array([SPVM::Int->new(111)])));
      is(sprintf("%+3x", 111), SPVM::Format->sprintf("%+3x", SPVM::new_any_object_array([SPVM::Int->new(111)])));
      is(sprintf("%-3x", 111), SPVM::Format->sprintf("%-3x", SPVM::new_any_object_array([SPVM::Int->new(111)])));
      is(sprintf("%x", -1 & 0xFFFFFFFF), SPVM::Format->sprintf("%x", SPVM::new_any_object_array([SPVM::Int->new(-1)])));
      is(sprintf("%0100x", -1 & 0xFFFFFFFF), SPVM::Format->sprintf("%0100x", SPVM::new_any_object_array([SPVM::Int->new(-1)])));
      is(sprintf("%03x", -1 & 0xFFFFFFFF), SPVM::Format->sprintf("%03x", SPVM::new_any_object_array([SPVM::Int->new(-1)])));
      is(sprintf("%+3x", -1 & 0xFFFFFFFF), SPVM::Format->sprintf("%+3x", SPVM::new_any_object_array([SPVM::Int->new(-1)])));
      is(sprintf("%-3x", -1 & 0xFFFFFFFF), SPVM::Format->sprintf("%-3x", SPVM::new_any_object_array([SPVM::Int->new(-1)])));
      is(sprintf("%03x", -1111 & 0xFFFFFFFF), SPVM::Format->sprintf("%03x", SPVM::new_any_object_array([SPVM::Int->new(-1111)])));
      is(sprintf("%+3x", -1111 & 0xFFFFFFFF), SPVM::Format->sprintf("%+3x", SPVM::new_any_object_array([SPVM::Int->new(-1111)])));
      is(sprintf("%-3x", -1111 & 0xFFFFFFFF), SPVM::Format->sprintf("%-3x", SPVM::new_any_object_array([SPVM::Int->new(-1111)])));
      is(sprintf("%03x", -111 & 0xFFFFFFFF), SPVM::Format->sprintf("%03x", SPVM::new_any_object_array([SPVM::Int->new(-111)])));
      is(sprintf("%+3x", -111 & 0xFFFFFFFF), SPVM::Format->sprintf("%+3x", SPVM::new_any_object_array([SPVM::Int->new(-111)])));
      is(sprintf("%-3x", -111 & 0xFFFFFFFF), SPVM::Format->sprintf("%-3x", SPVM::new_any_object_array([SPVM::Int->new(-111)])));
    }
    
    # %X
    eval 'sprintf("%X", 1)';
    if ($@) {
      warn "Skip %X"
    }
    else {
      is(sprintf("%X", 1), SPVM::Format->sprintf("%X", SPVM::new_any_object_array([SPVM::Int->new(1)])));
      is(sprintf("%0100X", 1), SPVM::Format->sprintf("%0100X", SPVM::new_any_object_array([SPVM::Int->new(1)])));
      is(sprintf("%03X", 1), SPVM::Format->sprintf("%03X", SPVM::new_any_object_array([SPVM::Int->new(1)])));
      is(sprintf("%+3X", 1), SPVM::Format->sprintf("%+3X", SPVM::new_any_object_array([SPVM::Int->new(1)])));
      is(sprintf("%-3X", 1), SPVM::Format->sprintf("%-3X", SPVM::new_any_object_array([SPVM::Int->new(1)])));
      is(sprintf("%03X", 1111), SPVM::Format->sprintf("%03X", SPVM::new_any_object_array([SPVM::Int->new(1111)])));
      is(sprintf("%+3X", 1111), SPVM::Format->sprintf("%+3X", SPVM::new_any_object_array([SPVM::Int->new(1111)])));
      is(sprintf("%-3X", 1111), SPVM::Format->sprintf("%-3X", SPVM::new_any_object_array([SPVM::Int->new(1111)])));
      is(sprintf("%03X", 111), SPVM::Format->sprintf("%03X", SPVM::new_any_object_array([SPVM::Int->new(111)])));
      is(sprintf("%+3X", 111), SPVM::Format->sprintf("%+3X", SPVM::new_any_object_array([SPVM::Int->new(111)])));
      is(sprintf("%-3X", 111), SPVM::Format->sprintf("%-3X", SPVM::new_any_object_array([SPVM::Int->new(111)])));
      is(sprintf("%X", -1 & 0xFFFFFFFF), SPVM::Format->sprintf("%X", SPVM::new_any_object_array([SPVM::Int->new(-1)])));
      is(sprintf("%0100X", -1 & 0xFFFFFFFF), SPVM::Format->sprintf("%0100X", SPVM::new_any_object_array([SPVM::Int->new(-1)])));
      is(sprintf("%03X", -1 & 0xFFFFFFFF), SPVM::Format->sprintf("%03X", SPVM::new_any_object_array([SPVM::Int->new(-1)])));
      is(sprintf("%+3X", -1 & 0xFFFFFFFF), SPVM::Format->sprintf("%+3X", SPVM::new_any_object_array([SPVM::Int->new(-1)])));
      is(sprintf("%-3X", -1 & 0xFFFFFFFF), SPVM::Format->sprintf("%-3X", SPVM::new_any_object_array([SPVM::Int->new(-1)])));
      is(sprintf("%03X", -1111 & 0xFFFFFFFF), SPVM::Format->sprintf("%03X", SPVM::new_any_object_array([SPVM::Int->new(-1111)])));
      is(sprintf("%+3X", -1111 & 0xFFFFFFFF), SPVM::Format->sprintf("%+3X", SPVM::new_any_object_array([SPVM::Int->new(-1111)])));
      is(sprintf("%-3X", -1111 & 0xFFFFFFFF), SPVM::Format->sprintf("%-3X", SPVM::new_any_object_array([SPVM::Int->new(-1111)])));
      is(sprintf("%03X", -111 & 0xFFFFFFFF), SPVM::Format->sprintf("%03X", SPVM::new_any_object_array([SPVM::Int->new(-111)])));
      is(sprintf("%+3X", -111 & 0xFFFFFFFF), SPVM::Format->sprintf("%+3X", SPVM::new_any_object_array([SPVM::Int->new(-111)])));
      is(sprintf("%-3X", -111 & 0xFFFFFFFF), SPVM::Format->sprintf("%-3X", SPVM::new_any_object_array([SPVM::Int->new(-111)])));
    }
    
    # %lu
    {
      is(sprintf("%llu", 1), SPVM::Format->sprintf("%lu", SPVM::new_any_object_array([SPVM::Long->new(1)])));
      is(sprintf("%0100llu", 1), SPVM::Format->sprintf("%0100lu", SPVM::new_any_object_array([SPVM::Long->new(1)])));
      is(sprintf("%03llu", 1), SPVM::Format->sprintf("%03lu", SPVM::new_any_object_array([SPVM::Long->new(1)])));
      is(sprintf("%+3llu", 1), SPVM::Format->sprintf("%+3lu", SPVM::new_any_object_array([SPVM::Long->new(1)])));
      is(sprintf("%-3llu", 1), SPVM::Format->sprintf("%-3lu", SPVM::new_any_object_array([SPVM::Long->new(1)])));
      is(sprintf("%03llu", 1111), SPVM::Format->sprintf("%03lu", SPVM::new_any_object_array([SPVM::Long->new(1111)])));
      is(sprintf("%+3llu", 1111), SPVM::Format->sprintf("%+3lu", SPVM::new_any_object_array([SPVM::Long->new(1111)])));
      is(sprintf("%-3llu", 1111), SPVM::Format->sprintf("%-3lu", SPVM::new_any_object_array([SPVM::Long->new(1111)])));
      is(sprintf("%03llu", 111), SPVM::Format->sprintf("%03lu", SPVM::new_any_object_array([SPVM::Long->new(111)])));
      is(sprintf("%+3llu", 111), SPVM::Format->sprintf("%+3lu", SPVM::new_any_object_array([SPVM::Long->new(111)])));
      is(sprintf("%-3llu", 111), SPVM::Format->sprintf("%-3lu", SPVM::new_any_object_array([SPVM::Long->new(111)])));
      # 18446744073709551615 means 0xFFFFFFFF_FFFFFFFF
      is(sprintf("%llu", -1 & 18446744073709551615), SPVM::Format->sprintf("%lu", SPVM::new_any_object_array([SPVM::Long->new(-1)])));
      is(sprintf("%0100llu", -1 & 18446744073709551615), SPVM::Format->sprintf("%0100lu", SPVM::new_any_object_array([SPVM::Long->new(-1)])));
      is(sprintf("%03llu", -1 & 18446744073709551615), SPVM::Format->sprintf("%03lu", SPVM::new_any_object_array([SPVM::Long->new(-1)])));
      is(sprintf("%+3llu", -1 & 18446744073709551615), SPVM::Format->sprintf("%+3lu", SPVM::new_any_object_array([SPVM::Long->new(-1)])));
      is(sprintf("%-3llu", -1 & 18446744073709551615), SPVM::Format->sprintf("%-3lu", SPVM::new_any_object_array([SPVM::Long->new(-1)])));
      is(sprintf("%03llu", -1111 & 18446744073709551615), SPVM::Format->sprintf("%03lu", SPVM::new_any_object_array([SPVM::Long->new(-1111)])));
      is(sprintf("%+3llu", -1111 & 18446744073709551615), SPVM::Format->sprintf("%+3lu", SPVM::new_any_object_array([SPVM::Long->new(-1111)])));
      is(sprintf("%-3llu", -1111 & 18446744073709551615), SPVM::Format->sprintf("%-3lu", SPVM::new_any_object_array([SPVM::Long->new(-1111)])));
      is(sprintf("%03llu", -111 & 18446744073709551615), SPVM::Format->sprintf("%03lu", SPVM::new_any_object_array([SPVM::Long->new(-111)])));
      is(sprintf("%+3llu", -111 & 18446744073709551615), SPVM::Format->sprintf("%+3lu", SPVM::new_any_object_array([SPVM::Long->new(-111)])));
      is(sprintf("%-3llu", -111 & 18446744073709551615), SPVM::Format->sprintf("%-3lu", SPVM::new_any_object_array([SPVM::Long->new(-111)])));
    }
    
    # %lx
    {
      is(sprintf("%llx", 1), SPVM::Format->sprintf("%lx", SPVM::new_any_object_array([SPVM::Long->new(1)])));
      is(sprintf("%0100llx", 1), SPVM::Format->sprintf("%0100lx", SPVM::new_any_object_array([SPVM::Long->new(1)])));
      is(sprintf("%03llx", 1), SPVM::Format->sprintf("%03lx", SPVM::new_any_object_array([SPVM::Long->new(1)])));
      is(sprintf("%+3llx", 1), SPVM::Format->sprintf("%+3lx", SPVM::new_any_object_array([SPVM::Long->new(1)])));
      is(sprintf("%-3llx", 1), SPVM::Format->sprintf("%-3lx", SPVM::new_any_object_array([SPVM::Long->new(1)])));
      is(sprintf("%03llx", 1111), SPVM::Format->sprintf("%03lx", SPVM::new_any_object_array([SPVM::Long->new(1111)])));
      is(sprintf("%+3llx", 1111), SPVM::Format->sprintf("%+3lx", SPVM::new_any_object_array([SPVM::Long->new(1111)])));
      is(sprintf("%-3llx", 1111), SPVM::Format->sprintf("%-3lx", SPVM::new_any_object_array([SPVM::Long->new(1111)])));
      is(sprintf("%03llx", 111), SPVM::Format->sprintf("%03lx", SPVM::new_any_object_array([SPVM::Long->new(111)])));
      is(sprintf("%+3llx", 111), SPVM::Format->sprintf("%+3lx", SPVM::new_any_object_array([SPVM::Long->new(111)])));
      is(sprintf("%-3llx", 111), SPVM::Format->sprintf("%-3lx", SPVM::new_any_object_array([SPVM::Long->new(111)])));
      # 18446744073709551615 means 0xFFFFFFFF_FFFFFFFF
      is(sprintf("%llx", -1 & 18446744073709551615), SPVM::Format->sprintf("%lx", SPVM::new_any_object_array([SPVM::Long->new(-1)])));
      is(sprintf("%0100llx", -1 & 18446744073709551615), SPVM::Format->sprintf("%0100lx", SPVM::new_any_object_array([SPVM::Long->new(-1)])));
      is(sprintf("%03llx", -1 & 18446744073709551615), SPVM::Format->sprintf("%03lx", SPVM::new_any_object_array([SPVM::Long->new(-1)])));
      is(sprintf("%+3llx", -1 & 18446744073709551615), SPVM::Format->sprintf("%+3lx", SPVM::new_any_object_array([SPVM::Long->new(-1)])));
      is(sprintf("%-3llx", -1 & 18446744073709551615), SPVM::Format->sprintf("%-3lx", SPVM::new_any_object_array([SPVM::Long->new(-1)])));
      is(sprintf("%03llx", -1111 & 18446744073709551615), SPVM::Format->sprintf("%03lx", SPVM::new_any_object_array([SPVM::Long->new(-1111)])));
      is(sprintf("%+3llx", -1111 & 18446744073709551615), SPVM::Format->sprintf("%+3lx", SPVM::new_any_object_array([SPVM::Long->new(-1111)])));
      is(sprintf("%-3llx", -1111 & 18446744073709551615), SPVM::Format->sprintf("%-3lx", SPVM::new_any_object_array([SPVM::Long->new(-1111)])));
      is(sprintf("%03llx", -111 & 18446744073709551615), SPVM::Format->sprintf("%03lx", SPVM::new_any_object_array([SPVM::Long->new(-111)])));
      is(sprintf("%+3llx", -111 & 18446744073709551615), SPVM::Format->sprintf("%+3lx", SPVM::new_any_object_array([SPVM::Long->new(-111)])));
      is(sprintf("%-3llx", -111 & 18446744073709551615), SPVM::Format->sprintf("%-3lx", SPVM::new_any_object_array([SPVM::Long->new(-111)])));
    }
    
    # %lX
    eval 'sprintf("%lX", 1)';
    if ($@) {
      warn "Skip: %lX"
    }
    else {
      is(sprintf("%llX", 1), SPVM::Format->sprintf("%lX", SPVM::new_any_object_array([SPVM::Long->new(1)])));
      is(sprintf("%0100llX", 1), SPVM::Format->sprintf("%0100lX", SPVM::new_any_object_array([SPVM::Long->new(1)])));
      is(sprintf("%03llX", 1), SPVM::Format->sprintf("%03lX", SPVM::new_any_object_array([SPVM::Long->new(1)])));
      is(sprintf("%+3llX", 1), SPVM::Format->sprintf("%+3lX", SPVM::new_any_object_array([SPVM::Long->new(1)])));
      is(sprintf("%-3llX", 1), SPVM::Format->sprintf("%-3lX", SPVM::new_any_object_array([SPVM::Long->new(1)])));
      is(sprintf("%03llX", 1111), SPVM::Format->sprintf("%03lX", SPVM::new_any_object_array([SPVM::Long->new(1111)])));
      is(sprintf("%+3llX", 1111), SPVM::Format->sprintf("%+3lX", SPVM::new_any_object_array([SPVM::Long->new(1111)])));
      is(sprintf("%-3llX", 1111), SPVM::Format->sprintf("%-3lX", SPVM::new_any_object_array([SPVM::Long->new(1111)])));
      is(sprintf("%03llX", 111), SPVM::Format->sprintf("%03lX", SPVM::new_any_object_array([SPVM::Long->new(111)])));
      is(sprintf("%+3llX", 111), SPVM::Format->sprintf("%+3lX", SPVM::new_any_object_array([SPVM::Long->new(111)])));
      is(sprintf("%-3llX", 111), SPVM::Format->sprintf("%-3lX", SPVM::new_any_object_array([SPVM::Long->new(111)])));
      # 18446744073709551615 means 0xFFFFFFFF_FFFFFFFF
      is(sprintf("%llX", -1 & 18446744073709551615), SPVM::Format->sprintf("%lX", SPVM::new_any_object_array([SPVM::Long->new(-1)])));
      is(sprintf("%0100llX", -1 & 18446744073709551615), SPVM::Format->sprintf("%0100lX", SPVM::new_any_object_array([SPVM::Long->new(-1)])));
      is(sprintf("%03llX", -1 & 18446744073709551615), SPVM::Format->sprintf("%03lX", SPVM::new_any_object_array([SPVM::Long->new(-1)])));
      is(sprintf("%+3llX", -1 & 18446744073709551615), SPVM::Format->sprintf("%+3lX", SPVM::new_any_object_array([SPVM::Long->new(-1)])));
      is(sprintf("%-3llX", -1 & 18446744073709551615), SPVM::Format->sprintf("%-3lX", SPVM::new_any_object_array([SPVM::Long->new(-1)])));
      is(sprintf("%03llX", -1111 & 18446744073709551615), SPVM::Format->sprintf("%03lX", SPVM::new_any_object_array([SPVM::Long->new(-1111)])));
      is(sprintf("%+3llX", -1111 & 18446744073709551615), SPVM::Format->sprintf("%+3lX", SPVM::new_any_object_array([SPVM::Long->new(-1111)])));
      is(sprintf("%-3llX", -1111 & 18446744073709551615), SPVM::Format->sprintf("%-3lX", SPVM::new_any_object_array([SPVM::Long->new(-1111)])));
      is(sprintf("%03llX", -111 & 18446744073709551615), SPVM::Format->sprintf("%03lX", SPVM::new_any_object_array([SPVM::Long->new(-111)])));
      is(sprintf("%+3llX", -111 & 18446744073709551615), SPVM::Format->sprintf("%+3lX", SPVM::new_any_object_array([SPVM::Long->new(-111)])));
      is(sprintf("%-3llX", -111 & 18446744073709551615), SPVM::Format->sprintf("%-3lX", SPVM::new_any_object_array([SPVM::Long->new(-111)])));
    }
    
    # %f
    {
      is(sprintf("%f", 1.5), SPVM::Format->sprintf("%f", SPVM::new_any_object_array([SPVM::Double->new(1.5)])));
      is(sprintf("%.100f", 1.5), SPVM::Format->sprintf("%.100f", SPVM::new_any_object_array([SPVM::Double->new(1.5)])));
      is(sprintf("%.3f", 1.5), SPVM::Format->sprintf("%.3f", SPVM::new_any_object_array([SPVM::Double->new(1.5)])));
      is(sprintf("%+3f", 1.5), SPVM::Format->sprintf("%+3f", SPVM::new_any_object_array([SPVM::Double->new(1.5)])));
      is(sprintf("%-3f", 1.5), SPVM::Format->sprintf("%-3f", SPVM::new_any_object_array([SPVM::Double->new(1.5)])));
      is(sprintf("%.3f", 1111.5), SPVM::Format->sprintf("%.3f", SPVM::new_any_object_array([SPVM::Double->new(1111.5)])));
      is(sprintf("%+3f", 1111.5), SPVM::Format->sprintf("%+3f", SPVM::new_any_object_array([SPVM::Double->new(1111.5)])));
      is(sprintf("%-3f", 1111.5), SPVM::Format->sprintf("%-3f", SPVM::new_any_object_array([SPVM::Double->new(1111.5)])));
      is(sprintf("%.3f", 111.5), SPVM::Format->sprintf("%.3f", SPVM::new_any_object_array([SPVM::Double->new(111.5)])));
      is(sprintf("%+3f", 111.5), SPVM::Format->sprintf("%+3f", SPVM::new_any_object_array([SPVM::Double->new(111.5)])));
      is(sprintf("%-3f", 111.5), SPVM::Format->sprintf("%-3f", SPVM::new_any_object_array([SPVM::Double->new(111.5)])));
      
      is(sprintf("%f", 1.5), SPVM::Format->sprintf("%f", SPVM::new_any_object_array([SPVM::Float->new(1.5)])));
      is(sprintf("%.100f", 1.5), SPVM::Format->sprintf("%.100f", SPVM::new_any_object_array([SPVM::Float->new(1.5)])));
      is(sprintf("%.3f", 1.5), SPVM::Format->sprintf("%.3f", SPVM::new_any_object_array([SPVM::Float->new(1.5)])));
      is(sprintf("%+3f", 1.5), SPVM::Format->sprintf("%+3f", SPVM::new_any_object_array([SPVM::Float->new(1.5)])));
      is(sprintf("%-3f", 1.5), SPVM::Format->sprintf("%-3f", SPVM::new_any_object_array([SPVM::Float->new(1.5)])));
      is(sprintf("%.3f", 1111.5), SPVM::Format->sprintf("%.3f", SPVM::new_any_object_array([SPVM::Float->new(1111.5)])));
      is(sprintf("%+3f", 1111.5), SPVM::Format->sprintf("%+3f", SPVM::new_any_object_array([SPVM::Float->new(1111.5)])));
      is(sprintf("%-3f", 1111.5), SPVM::Format->sprintf("%-3f", SPVM::new_any_object_array([SPVM::Float->new(1111.5)])));
      is(sprintf("%.3f", 111.5), SPVM::Format->sprintf("%.3f", SPVM::new_any_object_array([SPVM::Float->new(111.5)])));
      is(sprintf("%+3f", 111.5), SPVM::Format->sprintf("%+3f", SPVM::new_any_object_array([SPVM::Float->new(111.5)])));
      is(sprintf("%-3f", 111.5), SPVM::Format->sprintf("%-3f", SPVM::new_any_object_array([SPVM::Float->new(111.5)])));
    }
    
    # %g
    {
      is(sprintf("%g", 1.5), SPVM::Format->sprintf("%g", SPVM::new_any_object_array([SPVM::Double->new(1.5)])));
      is(sprintf("%g", 1.5), SPVM::Format->sprintf("%g", SPVM::new_any_object_array([SPVM::Float->new(1.5)])));
    }
    
    # %s
    {
      is(sprintf("%s", 1.5), SPVM::Format->sprintf("%s", SPVM::new_any_object_array([SPVM::new_string(1.5)])));
      is(sprintf("%.100s", 1.5), SPVM::Format->sprintf("%.100s", SPVM::new_any_object_array([SPVM::new_string(1.5)])));
      is(sprintf("%.3s", 1.5), SPVM::Format->sprintf("%.3s", SPVM::new_any_object_array([SPVM::new_string(1.5)])));
      is(sprintf("%+3s", 1.5), SPVM::Format->sprintf("%+3s", SPVM::new_any_object_array([SPVM::new_string(1.5)])));
      is(sprintf("%-3s", 1.5), SPVM::Format->sprintf("%-3s", SPVM::new_any_object_array([SPVM::new_string(1.5)])));
      is(sprintf("%.3s", 1111.5), SPVM::Format->sprintf("%.3s", SPVM::new_any_object_array([SPVM::new_string(1111.5)])));
      is(sprintf("%+3s", 1111.5), SPVM::Format->sprintf("%+3s", SPVM::new_any_object_array([SPVM::new_string(1111.5)])));
      is(sprintf("%-3s", 1111.5), SPVM::Format->sprintf("%-3s", SPVM::new_any_object_array([SPVM::new_string(1111.5)])));
      is(sprintf("%.3s", 111.5), SPVM::Format->sprintf("%.3s", SPVM::new_any_object_array([SPVM::new_string(111.5)])));
      is(sprintf("%+3s", 111.5), SPVM::Format->sprintf("%+3s", SPVM::new_any_object_array([SPVM::new_string(111.5)])));
      is(sprintf("%-3s", 111.5), SPVM::Format->sprintf("%-3s", SPVM::new_any_object_array([SPVM::new_string(111.5)])));
    }
    
    # %c
    {
      my $code_point_a = ord('a');
      my $code_point_unicode_a = ord('あ');
      
      is(sprintf("%c", $code_point_a), SPVM::Format->sprintf("%c", SPVM::new_any_object_array([SPVM::Byte->new($code_point_a)])));
      is(sprintf("%0100c", $code_point_a), SPVM::Format->sprintf("%0100c", SPVM::new_any_object_array([SPVM::Byte->new($code_point_a)])));
      is(sprintf("%03c", $code_point_a), SPVM::Format->sprintf("%03c", SPVM::new_any_object_array([SPVM::Byte->new($code_point_a)])));
      is(sprintf("%+3c", $code_point_a), SPVM::Format->sprintf("%+3c", SPVM::new_any_object_array([SPVM::Byte->new($code_point_a)])));
      is(sprintf("%-3c", $code_point_a), SPVM::Format->sprintf("%-3c", SPVM::new_any_object_array([SPVM::Byte->new($code_point_a)])));
      
      is(sprintf("%c", $code_point_a), SPVM::Format->sprintf("%c", SPVM::new_any_object_array([SPVM::Int->new($code_point_a)])));
      is(sprintf("%0100c", $code_point_a), SPVM::Format->sprintf("%0100c", SPVM::new_any_object_array([SPVM::Int->new($code_point_a)])));
      is(sprintf("%03c", $code_point_a), SPVM::Format->sprintf("%03c", SPVM::new_any_object_array([SPVM::Int->new($code_point_a)])));
      is(sprintf("%+3c", $code_point_a), SPVM::Format->sprintf("%+3c", SPVM::new_any_object_array([SPVM::Int->new($code_point_a)])));
      is(sprintf("%-3c", $code_point_a), SPVM::Format->sprintf("%-3c", SPVM::new_any_object_array([SPVM::Int->new($code_point_a)])));
      is(sprintf("%c", $code_point_unicode_a), SPVM::Format->sprintf("%c", SPVM::new_any_object_array([SPVM::Int->new($code_point_unicode_a)])));
      is(sprintf("%c", $code_point_unicode_a), SPVM::Format->sprintf("%c", SPVM::new_any_object_array([SPVM::Int->new($code_point_unicode_a)])));
    }
  }
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
