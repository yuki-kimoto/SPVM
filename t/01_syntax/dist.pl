use strict;
use warnings;
use utf8;

use FindBin;
use lib "$FindBin::Bin/lib";

use SPVM::Builder::API;

SPVM::Builder::API::build_parallel_dynamic_lib_dist({precompile_classes => ['TestCase::CompileError::ForTest']});
