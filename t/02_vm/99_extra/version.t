use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM;
use SPVM::Builder::Util;
use SPVM 'Fn';

my $api = SPVM::api();

# Start objects count
my $start_memory_blocks_count = $api->get_memory_blocks_count;

# Version
{
  like($SPVM::VERSION, qr|[\d\._]+|);
  
  # The version of the SPVM language is written in SPVM.pm and lib/SPVM/Builder/include/spvm_api.h
  # because of resolving CPAN module dependencies.
  # These versions must be same.
  my $spvm_version_in_spvm_api_header = SPVM::Builder::Util::get_spvm_version_string;
  is($SPVM::VERSION, $spvm_version_in_spvm_api_header);
}

# Major and minor version number
{
  for my $miner_version (0 .. 999) {
    
    # 1.000000, 1.001000, etc
    ok(SPVM::Fn->to_double(sprintf("1.%03d000", $miner_version)) == SPVM::Fn->to_double(sprintf("1.%03d", $miner_version)));
    
    # 1.000001, 1.001001, etc
    ok(SPVM::Fn->to_double(sprintf("1.%03d001", $miner_version)) > SPVM::Fn->to_double(sprintf("1.%03d", $miner_version)));
  }
}

# All object is freed
$api->destroy_runtime_permanent_vars;
my $end_memory_blocks_count = $api->get_memory_blocks_count;
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
