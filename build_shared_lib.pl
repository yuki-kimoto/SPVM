use strict;
use warnings;

use FindBin;
use lib "$FindBin::Bin/lib";

use SPVM::Build;

my $module = shift;

SPVM::Build::build_shared_lib($module);

