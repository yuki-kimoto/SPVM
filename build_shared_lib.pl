use strict;
use warnings;

use FindBin;
use lib "$FindBin::Bin/lib";
use SPVM::Build;

# Module name
my $module_name = shift;

SPVM::Build->new->build_shared_lib_blib($module_name);
