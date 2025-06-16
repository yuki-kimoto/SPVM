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

my $bench_count = 3000;
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

Benchmark: timing 3000 iterations of perl_sum, spvm_sum, spvm_sum_native, spvm_sum_precompile...
  perl_sum: 15 wallclock secs (14.79 usr +  0.00 sys = 14.79 CPU) @ 202.84/s (n=3000)
  spvm_sum:  9 wallclock secs ( 9.24 usr +  0.00 sys =  9.24 CPU) @ 324.68/s (n=3000)
spvm_sum_native:  0 wallclock secs ( 0.03 usr +  0.00 sys =  0.03 CPU) @ 100000.00/s (n=3000)
            (warning: too few iterations for a reliable count)
spvm_sum_precompile:  0 wallclock secs ( 0.03 usr +  0.00 sys =  0.03 CPU) @ 100000.00/s (n=3000)
            (warning: too few iterations for a reliable count)
                        Rate perl_sum spvm_sum spvm_sum_native spvm_sum_precompile
perl_sum               203/s       --     -38%           -100%               -100%
spvm_sum               325/s      60%       --           -100%               -100%
spvm_sum_native     100000/s   49200%   30700%              --                  0%
spvm_sum_precompile 100000/s   49200%   30700%              0%                  --

=cut
