use strict;
use warnings;

use FindBin;
use lib "$FindBin::Bin/lib";

use SPVM 'MyOpenMP';

# Initialize SPVM
UNITCHECK { SPVM::init() }

MyOpenMP->test;
