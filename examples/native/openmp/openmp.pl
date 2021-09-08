use strict;
use warnings;

use FindBin;
use lib "$FindBin::Bin/lib";

use SPVM 'SPVM::MyOpenMP';

# Initialize SPVM


SPVM::MyOpenMP->test;
