use strict;
use warnings;
use utf8;

use FindBin;
use lib "$FindBin::Bin/lib";

use SPVM::Builder::API;

SPVM::Builder::API::build_parallel({precompile_classes => ['TestCase::CompileError::ForTest']});
