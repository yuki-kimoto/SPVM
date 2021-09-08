use strict;
use warnings;

use FindBin;
use lib "$FindBin::Bin/lib";

use SPVM 'SPVM::BindCLib';

my $total = SPVM::BindCLib->sum([1, 2, 3, 4]);

print "Total: $total\n";
