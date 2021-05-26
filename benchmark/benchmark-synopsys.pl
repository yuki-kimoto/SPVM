use strict;
use warnings;
use FindBin;
use lib "$FindBin::Bin/lib";
use Benchmark qw/timethese cmpthese/;

use SPVM 'MyMath';

# Initialize SPVM

use strict;
use warnings;
use FindBin;
use lib "$FindBin::Bin/lib";
use Benchmark qw/timethese cmpthese/;

use SPVM 'MyMath';
use SPVM 'MyMathPrecompile';
use SPVM 'MyMathNative';

my $bench_count = 10000;
my $loop_count = 100000;
my $result = timethese($bench_count, {
  perl5_28_sum => sub {
    perl_sum($loop_count);
  },
  spvm_sum => sub {
    MyMath->spvm_sum($loop_count);
  },
  spvm_sum_precompile => sub {
    MyMathPrecompile->spvm_sum($loop_count);
  },
  spvm_sum => sub {
    MyMathNative->spvm_sum($loop_count);
  },
});

cmpthese $result;

sub perl_sum {
  my ($loop_count) = @_;
  
  my $total = 0;
  for (my $i = 0; $i < $loop_count; $i++) {
    $total += $i;
  }
  
  return $total;
}

=head1 Benchmark result

  Benchmark: timing 10000 iterations of perl5_28_sum, spvm_sum, spvm_sum_native, spvm_sum_precompile...
  perl5_28_sum: 49 wallclock secs (48.96 usr +  0.02 sys = 48.98 CPU) @ 204.16/s (n=10000)
    spvm_sum: 27 wallclock secs (26.75 usr +  0.00 sys = 26.75 CPU) @ 373.83/s (n=10000)
  spvm_sum_native:  0 wallclock secs ( 0.41 usr +  0.00 sys =  0.41 CPU) @ 24390.24/s (n=10000)
  spvm_sum_precompile:  1 wallclock secs ( 0.42 usr +  0.00 sys =  0.42 CPU) @ 23809.52/s (n=10000)
                         Rate perl5_28_sum spvm_sum spvm_sum_precompile spvm_sum_native
  perl5_28_sum          204/s           --     -45%                -99%            -99%
  spvm_sum              374/s          83%       --                -98%            -98%
  spvm_sum_precompile 23810/s       11562%    6269%                  --             -2%
  spvm_sum_native     24390/s       11846%    6424%                  2%              --

