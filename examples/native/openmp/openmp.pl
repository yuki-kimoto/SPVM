use strict;
use warnings;

use FindBin;
use lib "$FindBin::Bin/lib";

use SPVM 'MyOpenMP';

SPVM::MyOpenMP->test;
