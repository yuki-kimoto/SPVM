use strict;
use warnings;

use FindBin;
use lib "$FindBin::Bin/lib";

use SPVM 'SPVM::MyZlib';

# Initialize SPVM


my $out_file = "$ENV{HOME}/tmp/output.gz";

SPVM::MyZlib->test($out_file);
