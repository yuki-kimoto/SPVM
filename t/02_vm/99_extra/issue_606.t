use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

my $warn;

BEGIN {
  $SIG{__WARN__} = sub {
    $warn = $_[0];
  };
}

use SPVM 'Point3D';
use SPVM::Point3D;

# https://github.com/yuki-kimoto/SPVM/issues/606

# Start objects count
my $api = SPVM::api();
my $start_memory_blocks_count = $api->get_memory_blocks_count;

ok(!$warn);

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
