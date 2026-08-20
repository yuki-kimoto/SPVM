use lib "t/lib";
use TestAuto;
use TestUtil::MyLib;
use lib "$FindBin::Bin/../02_vm/lib";

use strict;
use warnings;

use Test::More;
use File::Temp();

BEGIN {
  use File::Path 'mkpath';
  my $tmp_dir = '.tmp/link_to';
  mkpath $tmp_dir;
  $ENV{SPVM_BUILD_DIR} = $tmp_dir;
}
use SPVM 'TestCase::NativeAPILinkTo';

# Start objects count
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count;

{
  ok(SPVM::TestCase::NativeAPILinkTo->basic);
}

# Clear exception
$api->destroy_runtime_permanent_vars;

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
