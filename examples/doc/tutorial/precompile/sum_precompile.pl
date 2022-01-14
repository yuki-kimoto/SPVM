# sum_precompile.pl
use strict;
use warnings;
use FindBin;
use lib "$FindBin::Bin/lib";

use SPVM 'MyMath';

# Call precompile method
my $total_precompile = SPVM::MyMath->sum_precompile([3, 6, 8, 9]);

print "Total Precompile: $total_precompile\n";
