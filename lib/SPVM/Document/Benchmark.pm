=head1 NAME

SPVM::Document::Benchmark - SPVM Performance Benchmark

=head1 DESCRIPTION

SPVM Performance Benchmark.

=head1 BENCHMARK

=head2 for loop addition

for loop addition benchmark.

=head3 Benchmark Result

=begin html

<table>
  <tr>
    <th>SPVM</th><td><b style="color:red">83%</b> faster than Perl 5.28</td>
  </tr>
  <tr>
    <th>SPVM precompile</th><td><b style="color:red">11562%</b> faster than Perl 5.28</td>
  </tr>
  <tr>
    <th>SPVM native(C lang)</th><td><b style="color:red">11846%</b> faster than Perl 5.28</td>
  </tr>
</table>

=end html

Benchmark raw output


  Benchmark: timing 10000 iterations of perl5_28_sum, spvm_sum, spvm_sum, spvm_sum_precompile...
  perl5_28_sum: 49 wallclock secs (48.96 usr +  0.02 sys = 48.98 CPU) @ 204.16/s (n=10000)
    spvm_sum: 27 wallclock secs (26.75 usr +  0.00 sys = 26.75 CPU) @ 373.83/s (n=10000)
  spvm_sum:  0 wallclock secs ( 0.41 usr +  0.00 sys =  0.41 CPU) @ 24390.24/s (n=10000)
  spvm_sum_precompile:  1 wallclock secs ( 0.42 usr +  0.00 sys =  0.42 CPU) @ 23809.52/s (n=10000)
                         Rate perl5_28_sum spvm_sum spvm_sum_precompile spvm_sum
  perl5_28_sum          204/s           --     -45%                -99%            -99%
  spvm_sum              374/s          83%       --                -98%            -98%
  spvm_sum_precompile 23810/s       11562%    6269%                  --             -2%
  spvm_sum     24390/s       11846%    6424%                  2%              --


=head3 Benchmark program

  B<benchmark-synopsys.pl>

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
      SPVM::MyMath->spvm_sum($loop_count);
    },
    spvm_sum_precompile => sub {
      SPVM::MyMathPrecompile->spvm_sum($loop_count);
    },
    spvm_sum => sub {
      SPVM::MyMathNative->spvm_sum($loop_count);
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

B<SPVM/MyMath.spvm>

  class MyMath {
    static method spvm_sum : int ($loop_count : int) {
      
      my $total = 0;
      for (my $i = 0; $i < $loop_count; $i++) {
        $total += $i;
      }
      
      return $total;
    }
  }

B<SPVM/MyMathPrecompile.spvm>

  class MyMathPrecompile : precompile {
    static method spvm_sum : int ($loop_count : int) {
      
      my $total = 0;
      for (my $i = 0; $i < $loop_count; $i++) {
        $total += $i;
      }
      
      return $total;
    }
  }

B<SPVM/MyMathNative.spvm>

  class MyMathNative {
    native static method spvm_sum : int ($loop_count : int);
  }

B<SPVM/MyMath.config>

  use strict;
  use warnings;

  use SPVM::Builder::Config;

  my $config = SPVM::Builder::Config->new_c99(file => __FILE__);

  $config;

B<SPVM/MyMathNative.c>

  #include "spvm_native.h"

  int32_t SPVM__MyMathNative__spvm_sum(SPVM_ENV* env, SPVM_VALUE* stack) {
    
    int32_t loop_count = stack[0].ival;

    int32_t total = 0;
    for (int32_t i = 0; i < loop_count; i++) {
      total += i;
    }
    
    stack[0].ival = total;
    
    return 0;
  }
