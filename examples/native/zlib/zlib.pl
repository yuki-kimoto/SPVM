use strict;
use warnings;

use FindBin;
use lib "$FindBin::Bin/lib";

BEGIN { $ENV{SPVM_BUILD_DIR} = "$ENV{HOME}/spvm_build" }

use SPVM 'MyZlib';

MyZlib->test;
