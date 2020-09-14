use strict;
use warnings;

use FindBin;
use lib "$FindBin::Bin/lib";

use SPVM 'MyComplex';

MyComplex->new_float_complex;

MyComplex->new_float_complex_func;

MyComplex->new_double_complex;

MyComplex->new_double_complex_func;

MyComplex->complex_float_operations;

MyComplex->complex_double_operations;

MyComplex->complex_float_array;

MyComplex->complex_double_array;

{
  my $z1 = {re => 1.7, im => 2.7};
  my $z2 = {re => 7.5, im => 2.5};

  my $z_ret = MyComplex->complex_call_from_perl($z1, $z2);

  print "($z_ret->{re}, $z_ret->{im})\n";
}
