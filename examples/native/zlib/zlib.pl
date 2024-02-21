use strict;
use warnings;

use FindBin;
use lib "$FindBin::Bin/lib";

use SPVM 'MyZlib';

my $out_file = "$ENV{HOME}/tmp/output.gz";

SPVM::MyZlib->test($out_file);
