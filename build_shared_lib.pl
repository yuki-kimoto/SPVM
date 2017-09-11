use strict;
use warnings;

use FindBin;
use lib "$FindBin::Bin/lib";

use SPVM::Util;

my $module = shift;

SPVM::Util::build_shared_lib($module);
