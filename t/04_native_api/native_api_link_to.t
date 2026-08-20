use lib "t/lib";
use TestAuto;
use TestUtil::MyLib;
use lib "$FindBin::Bin/../02_vm/lib";

use strict;
use warnings;

use Test::More;
use File::Temp();
use File::Find;
use File::Basename;
use Config;

BEGIN {
  my $tmp_dir = File::Temp->newdir;
  $ENV{SPVM_BUILD_DIR} = $tmp_dir;
}
use SPVM 'TestCase::NativeAPILinkTo';

# Start objects count
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count;

{
  ok(SPVM::TestCase::NativeAPILinkTo->basic);
}

my $has_native_api_dlext = 0;
my $has_native_api_link_to_dlext = 0;

find(
  sub {
    my $file = $_;
    if (-f $file) {
      my $basename = basename($file);
      if ($basename eq "NativeAPI.$Config{dlext}") {
        $has_native_api_dlext = 1;
      }
      elsif ($basename eq "NativeAPILinkTo.$Config{dlext}") {
        $has_native_api_link_to_dlext = 1;
      }
    }
  },
  $ENV{SPVM_BUILD_DIR}
);

ok($has_native_api_dlext, "NativeAPI.$Config{dlext} exists.");
ok(!$has_native_api_link_to_dlext, "NativeAPILinkTo.$Config{dlext} does not exist.");

# Clear exception
$api->destroy_runtime_permanent_vars;

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
