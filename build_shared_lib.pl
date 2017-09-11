use strict;
use warnings;

use FindBin;
use lib "$FindBin::Bin/lib";

use SPVM::Build;

my $module_name = shift;

my $shared_lib_file = SPVM::Build::build_shared_lib(
  module_name => $module_name,
  module_dir => 'lib'
);
