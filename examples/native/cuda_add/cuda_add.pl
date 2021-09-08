use strict;
use warnings;

use FindBin;
use lib "$FindBin::Bin/lib";

use List::Util;
use SPVM 'MyAdd';

# 30 is max gpu paralel
my $length = 1_000_000;
my $nums1 = [1..$length];
my $nums2 = [1..$length];

my $nums1_pack = pack('f*', @$nums1);
my $nums2_pack = pack('f*', @$nums2);

{
  my $sp_nums1 = SPVM::new_float_array_from_bin($nums1_pack);
  my $sp_nums2 = SPVM::new_float_array_from_bin($nums2_pack);

  my $start_time = time;
  my $start_time_high = [gettimeofday];
  SPVM::MyAdd->add_cuda($sp_nums1, $sp_nums2);
}
