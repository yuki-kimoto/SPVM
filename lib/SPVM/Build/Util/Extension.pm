package SPVM::Build::Util::Extension;

use strict;
use warnings;
use Carp 'croak', 'confess';

use ExtUtils::CBuilder;
use Config;
use File::Copy 'move';
use File::Path 'mkpath';

use File::Basename 'dirname', 'basename';

# SPVM::Build::Util::Extension is used from Makefile.PL
# so SPVM::Build::Util::Extension must be wrote as pure per script, not contain XS.

1;
