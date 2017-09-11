use strict;
use warnings;

use FindBin;
use lib "$FindBin::Bin/lib";

use SPVM::Util;

my @modules = ('SPVM::std', 'SPVM::Math');

for my $module (@modules) {
  SPVM::Util::build_shared_lib($module);
}
