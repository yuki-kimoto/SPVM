use strict;
use warnings;
use utf8;

use FindBin;
use lib "$FindBin::Bin/lib";

use SPVM::Builder::API;

my $api = SPVM::Builder::API->new;

$api->build_shared_lib_dist_precompile('TestCase::CompileError::ForTest');
