package SPVM::Build::CC;

use strict;
use warnings;
use Carp 'croak', 'confess';

use SPVM::Build::Util;

use Getopt::Long 'GetOptions';

use ExtUtils::CBuilder;
use File::Copy 'move';
use File::Path 'mkpath';
use DynaLoader;

use File::Basename 'dirname', 'basename';

sub create_exe_file {
  
}

1;
