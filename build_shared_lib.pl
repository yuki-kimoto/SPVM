use strict;
use warnings;

use Getopt::Long 'GetOptions';

use FindBin;
use lib "$FindBin::Bin/lib";
use SPVM::Build;

my $object_dir;
GetOptions('object_dir=s' => \$object_dir);

# Module name
my $module_name = shift;

# Build shared library
my $shared_lib_file = SPVM::Build::build_shared_lib(
  module_name => $module_name,
  module_dir => 'lib',
  source_dir => 'lib_native',
  object_dir => $object_dir
);

SPVM::Build::move_shared_lib_to_blib($shared_lib_file, $module_name);
