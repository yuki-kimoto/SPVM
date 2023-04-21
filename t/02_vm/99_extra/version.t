use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM;
use SPVM::Builder::Util;

my $api = SPVM::api();

# Start objects count
my $start_memory_blocks_count = $api->get_memory_blocks_count();

# Version
{
  like($SPVM::VERSION, qr|[\d\._]+|);
  
  # The version of the SPVM language is written in SPVM.pm and lib/SPVM/Builder/include/spvm_api.h
  # because of resolving CPAN module dependencies.
  # These versions must be same.
  my $spvm_version_in_spvm_api_header = SPVM::Builder::Util::get_spvm_version_string;
  is($SPVM::VERSION, $spvm_version_in_spvm_api_header);
}

# All object is freed
my $end_memory_blocks_count = $api->get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
