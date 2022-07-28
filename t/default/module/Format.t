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
  
  # Extra
  {
    # %d
    {
      is(sprintf("%d", 1), SPVM::Format->sprintf("%d", SPVM::new_object_array('object[]', [SPVM::Int->new(1)])));
      is(sprintf("%0100d", 1), SPVM::Format->sprintf("%0100d", SPVM::new_object_array('object[]', [SPVM::Int->new(1)])));
      is(sprintf("%03d", 1), SPVM::Format->sprintf("%03d", SPVM::new_object_array('object[]', [SPVM::Int->new(1)])));
      is(sprintf("%+3d", 1), SPVM::Format->sprintf("%+3d", SPVM::new_object_array('object[]', [SPVM::Int->new(1)])));
      is(sprintf("%-3d", 1), SPVM::Format->sprintf("%-3d", SPVM::new_object_array('object[]', [SPVM::Int->new(1)])));
      is(sprintf("%03d", 1111), SPVM::Format->sprintf("%03d", SPVM::new_object_array('object[]', [SPVM::Int->new(1111)])));
      is(sprintf("%+3d", 1111), SPVM::Format->sprintf("%+3d", SPVM::new_object_array('object[]', [SPVM::Int->new(1111)])));
      is(sprintf("%-3d", 1111), SPVM::Format->sprintf("%-3d", SPVM::new_object_array('object[]', [SPVM::Int->new(1111)])));
      is(sprintf("%03d", 111), SPVM::Format->sprintf("%03d", SPVM::new_object_array('object[]', [SPVM::Int->new(111)])));
      is(sprintf("%+3d", 111), SPVM::Format->sprintf("%+3d", SPVM::new_object_array('object[]', [SPVM::Int->new(111)])));
      is(sprintf("%-3d", 111), SPVM::Format->sprintf("%-3d", SPVM::new_object_array('object[]', [SPVM::Int->new(111)])));
    }
    
    # %ld
    {
      is(sprintf("%ld", 1), SPVM::Format->sprintf("%ld", SPVM::new_object_array('object[]', [SPVM::Long->new(1)])));
      is(sprintf("%0100ld", 1), SPVM::Format->sprintf("%0100ld", SPVM::new_object_array('object[]', [SPVM::Long->new(1)])));
      is(sprintf("%03ld", 1), SPVM::Format->sprintf("%03ld", SPVM::new_object_array('object[]', [SPVM::Long->new(1)])));
      is(sprintf("%+3ld", 1), SPVM::Format->sprintf("%+3ld", SPVM::new_object_array('object[]', [SPVM::Long->new(1)])));
      is(sprintf("%-3ld", 1), SPVM::Format->sprintf("%-3ld", SPVM::new_object_array('object[]', [SPVM::Long->new(1)])));
      is(sprintf("%03ld", 1111), SPVM::Format->sprintf("%03ld", SPVM::new_object_array('object[]', [SPVM::Long->new(1111)])));
      is(sprintf("%+3ld", 1111), SPVM::Format->sprintf("%+3ld", SPVM::new_object_array('object[]', [SPVM::Long->new(1111)])));
      is(sprintf("%-3ld", 1111), SPVM::Format->sprintf("%-3ld", SPVM::new_object_array('object[]', [SPVM::Long->new(1111)])));
      is(sprintf("%03ld", 111), SPVM::Format->sprintf("%03ld", SPVM::new_object_array('object[]', [SPVM::Long->new(111)])));
      is(sprintf("%+3ld", 111), SPVM::Format->sprintf("%+3ld", SPVM::new_object_array('object[]', [SPVM::Long->new(111)])));
      is(sprintf("%-3ld", 111), SPVM::Format->sprintf("%-3ld", SPVM::new_object_array('object[]', [SPVM::Long->new(111)])));
    }
    
    # %u
    {
      is(sprintf("%u", 1), SPVM::Format->sprintf("%u", SPVM::new_object_array('object[]', [SPVM::Int->new(1)])));
      is(sprintf("%0100u", 1), SPVM::Format->sprintf("%0100u", SPVM::new_object_array('object[]', [SPVM::Int->new(1)])));
      is(sprintf("%03u", 1), SPVM::Format->sprintf("%03u", SPVM::new_object_array('object[]', [SPVM::Int->new(1)])));
      is(sprintf("%+3u", 1), SPVM::Format->sprintf("%+3u", SPVM::new_object_array('object[]', [SPVM::Int->new(1)])));
      is(sprintf("%-3u", 1), SPVM::Format->sprintf("%-3u", SPVM::new_object_array('object[]', [SPVM::Int->new(1)])));
      is(sprintf("%03u", 1111), SPVM::Format->sprintf("%03u", SPVM::new_object_array('object[]', [SPVM::Int->new(1111)])));
      is(sprintf("%+3u", 1111), SPVM::Format->sprintf("%+3u", SPVM::new_object_array('object[]', [SPVM::Int->new(1111)])));
      is(sprintf("%-3u", 1111), SPVM::Format->sprintf("%-3u", SPVM::new_object_array('object[]', [SPVM::Int->new(1111)])));
      is(sprintf("%03u", 111), SPVM::Format->sprintf("%03u", SPVM::new_object_array('object[]', [SPVM::Int->new(111)])));
      is(sprintf("%+3u", 111), SPVM::Format->sprintf("%+3u", SPVM::new_object_array('object[]', [SPVM::Int->new(111)])));
      is(sprintf("%-3u", 111), SPVM::Format->sprintf("%-3u", SPVM::new_object_array('object[]', [SPVM::Int->new(111)])));
      is(sprintf("%u", -1 & 0xFFFFFFFF), SPVM::Format->sprintf("%u", SPVM::new_object_array('object[]', [SPVM::Int->new(-1)])));
      is(sprintf("%0100u", -1 & 0xFFFFFFFF), SPVM::Format->sprintf("%0100u", SPVM::new_object_array('object[]', [SPVM::Int->new(-1)])));
      is(sprintf("%03u", -1 & 0xFFFFFFFF), SPVM::Format->sprintf("%03u", SPVM::new_object_array('object[]', [SPVM::Int->new(-1)])));
      is(sprintf("%+3u", -1 & 0xFFFFFFFF), SPVM::Format->sprintf("%+3u", SPVM::new_object_array('object[]', [SPVM::Int->new(-1)])));
      is(sprintf("%-3u", -1 & 0xFFFFFFFF), SPVM::Format->sprintf("%-3u", SPVM::new_object_array('object[]', [SPVM::Int->new(-1)])));
      is(sprintf("%03u", -1111 & 0xFFFFFFFF), SPVM::Format->sprintf("%03u", SPVM::new_object_array('object[]', [SPVM::Int->new(-1111)])));
      is(sprintf("%+3u", -1111 & 0xFFFFFFFF), SPVM::Format->sprintf("%+3u", SPVM::new_object_array('object[]', [SPVM::Int->new(-1111)])));
      is(sprintf("%-3u", -1111 & 0xFFFFFFFF), SPVM::Format->sprintf("%-3u", SPVM::new_object_array('object[]', [SPVM::Int->new(-1111)])));
      is(sprintf("%03u", -111 & 0xFFFFFFFF), SPVM::Format->sprintf("%03u", SPVM::new_object_array('object[]', [SPVM::Int->new(-111)])));
      is(sprintf("%+3u", -111 & 0xFFFFFFFF), SPVM::Format->sprintf("%+3u", SPVM::new_object_array('object[]', [SPVM::Int->new(-111)])));
      is(sprintf("%-3u", -111 & 0xFFFFFFFF), SPVM::Format->sprintf("%-3u", SPVM::new_object_array('object[]', [SPVM::Int->new(-111)])));
    }

    # %lu
    {
      is(sprintf("%lu", 1), SPVM::Format->sprintf("%lu", SPVM::new_object_array('object[]', [SPVM::Long->new(1)])));
      is(sprintf("%0100lu", 1), SPVM::Format->sprintf("%0100lu", SPVM::new_object_array('object[]', [SPVM::Long->new(1)])));
      is(sprintf("%03lu", 1), SPVM::Format->sprintf("%03lu", SPVM::new_object_array('object[]', [SPVM::Long->new(1)])));
      is(sprintf("%+3lu", 1), SPVM::Format->sprintf("%+3lu", SPVM::new_object_array('object[]', [SPVM::Long->new(1)])));
      is(sprintf("%-3lu", 1), SPVM::Format->sprintf("%-3lu", SPVM::new_object_array('object[]', [SPVM::Long->new(1)])));
      is(sprintf("%03lu", 1111), SPVM::Format->sprintf("%03lu", SPVM::new_object_array('object[]', [SPVM::Long->new(1111)])));
      is(sprintf("%+3lu", 1111), SPVM::Format->sprintf("%+3lu", SPVM::new_object_array('object[]', [SPVM::Long->new(1111)])));
      is(sprintf("%-3lu", 1111), SPVM::Format->sprintf("%-3lu", SPVM::new_object_array('object[]', [SPVM::Long->new(1111)])));
      is(sprintf("%03lu", 111), SPVM::Format->sprintf("%03lu", SPVM::new_object_array('object[]', [SPVM::Long->new(111)])));
      is(sprintf("%+3lu", 111), SPVM::Format->sprintf("%+3lu", SPVM::new_object_array('object[]', [SPVM::Long->new(111)])));
      is(sprintf("%-3lu", 111), SPVM::Format->sprintf("%-3lu", SPVM::new_object_array('object[]', [SPVM::Long->new(111)])));
      is(sprintf("%lu", -1 & 0xFFFFFFFF_FFFFFFFF), SPVM::Format->sprintf("%lu", SPVM::new_object_array('object[]', [SPVM::Long->new(-1)])));
      is(sprintf("%0100lu", -1 & 0xFFFFFFFF_FFFFFFFF), SPVM::Format->sprintf("%0100lu", SPVM::new_object_array('object[]', [SPVM::Long->new(-1)])));
      is(sprintf("%03lu", -1 & 0xFFFFFFFF_FFFFFFFF), SPVM::Format->sprintf("%03lu", SPVM::new_object_array('object[]', [SPVM::Long->new(-1)])));
      is(sprintf("%+3lu", -1 & 0xFFFFFFFF_FFFFFFFF), SPVM::Format->sprintf("%+3lu", SPVM::new_object_array('object[]', [SPVM::Long->new(-1)])));
      is(sprintf("%-3lu", -1 & 0xFFFFFFFF_FFFFFFFF), SPVM::Format->sprintf("%-3lu", SPVM::new_object_array('object[]', [SPVM::Long->new(-1)])));
      is(sprintf("%03lu", -1111 & 0xFFFFFFFF_FFFFFFFF), SPVM::Format->sprintf("%03lu", SPVM::new_object_array('object[]', [SPVM::Long->new(-1111)])));
      is(sprintf("%+3lu", -1111 & 0xFFFFFFFF_FFFFFFFF), SPVM::Format->sprintf("%+3lu", SPVM::new_object_array('object[]', [SPVM::Long->new(-1111)])));
      is(sprintf("%-3lu", -1111 & 0xFFFFFFFF_FFFFFFFF), SPVM::Format->sprintf("%-3lu", SPVM::new_object_array('object[]', [SPVM::Long->new(-1111)])));
      is(sprintf("%03lu", -111 & 0xFFFFFFFF_FFFFFFFF), SPVM::Format->sprintf("%03lu", SPVM::new_object_array('object[]', [SPVM::Long->new(-111)])));
      is(sprintf("%+3lu", -111 & 0xFFFFFFFF_FFFFFFFF), SPVM::Format->sprintf("%+3lu", SPVM::new_object_array('object[]', [SPVM::Long->new(-111)])));
      is(sprintf("%-3lu", -111 & 0xFFFFFFFF_FFFFFFFF), SPVM::Format->sprintf("%-3lu", SPVM::new_object_array('object[]', [SPVM::Long->new(-111)])));
    }

  }
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
