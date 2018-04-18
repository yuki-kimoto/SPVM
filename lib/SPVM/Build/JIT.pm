package SPVM::Build::JIT;

use strict;
use warnings;
use Carp 'croak', 'confess';

use ExtUtils::CBuilder;
use Config;
use File::Copy 'move';
use File::Path 'mkpath';

use File::Basename 'dirname', 'basename';

1;
