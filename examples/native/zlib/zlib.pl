use strict;
use warnings;

use FindBin;
use lib "$FindBin::Bin/lib";

BEGIN { $ENV{SPVM_BUILD_DIR} = "$ENV{HOME}/spvm_build" }

use SPVM 'MyZlib';

my $out_file = "$ENV{HOME}/tmp/output.gz";

MyZlib->test(SPVM::new_str($out_file));
