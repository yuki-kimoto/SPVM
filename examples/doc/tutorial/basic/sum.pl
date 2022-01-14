use strict;
use warnings;
use FindBin;
use lib "$FindBin::Bin/lib";

use SPVM 'MyMath';

# Call method
my $total = SPVM::MyMath->sum([3, 6, 8, 9]);

print "Total: $total\n";

# Call method with packed data
my $nums_packed = pack('l*', 3, 6, 8, 9);
my $sv_nums = SPVM::new_int_array_from_bin($nums_packed);
my $total_packed = SPVM::MyMath->sum($sv_nums);

print "Total Packed: $total_packed\n";
