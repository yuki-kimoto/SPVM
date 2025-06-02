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

my $bench_count = 1000;
my $loop_count = 100000;
my $result = timethese($bench_count, {
  perl_sum => sub {
    perl_sum($loop_count);
  },
  spvm_sum => sub {
    SPVM::MyMath->spvm_sum($loop_count);
  },
  spvm_sum_precompile => sub {
    SPVM::MyMath->spvm_sum_precompile($loop_count);
  },
  spvm_sum_native => sub {
    SPVM::MyMath->spvm_sum_native($loop_count);
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

=pod a result

Benchmark: timing 1000 iterations of perl_sum, spvm_sum, spvm_sum_native, spvm_sum_precompile...
  perl_sum:  5 wallclock secs ( 4.98 usr +  0.00 sys =  4.98 CPU) @ 200.80/s (n=1000)
  spvm_sum:  4 wallclock secs ( 3.45 usr +  0.00 sys =  3.45 CPU) @ 289.86/s (n=1000)
spvm_sum_native:  0 wallclock secs ( 0.01 usr +  0.00 sys =  0.01 CPU) @ 100000.00/s (n=1000)
            (warning: too few iterations for a reliable count)
spvm_sum_precompile:  0 wallclock secs ( 0.01 usr +  0.00 sys =  0.01 CPU) @ 100000.00/s (n=1000)
            (warning: too few iterations for a reliable count)
                        Rate perl_sum spvm_sum spvm_sum_precompile spvm_sum_native
perl_sum               201/s       --     -31%               -100%           -100%
spvm_sum               290/s      44%       --               -100%           -100%
spvm_sum_precompile 100000/s   49700%   34400%                  --              0%
spvm_sum_native     100000/s   49700%   34400%                  0%              -

=cut
