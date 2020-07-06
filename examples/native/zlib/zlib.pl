use strict;
use warnings;

use FindBin;
use lib "$FindBin::Bin/lib";

BEGIN { $ENV{SPVM_BUILD_DIR} = "$ENV{HOME}/spvm_build" }

use SPVM 'MyZlib';

# Initialize SPVM


my $out_file = "$ENV{HOME}/tmp/output.gz";

MyZlib->test($out_file);
