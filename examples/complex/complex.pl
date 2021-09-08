use strict;
use warnings;

use FindBin;
use lib "$FindBin::Bin/lib";

use SPVM 'SPVM::MyComplex';

SPVM::MyComplex->new_float_complex;

SPVM::MyComplex->new_float_complex_func;

SPVM::MyComplex->new_double_complex;

SPVM::MyComplex->new_double_complex_func;

SPVM::MyComplex->complex_float_operations;

SPVM::MyComplex->complex_double_operations;

SPVM::MyComplex->complex_float_array;

SPVM::MyComplex->complex_double_array;

{
  my $z1 = {re => 1.7, im => 2.7};
  my $z2 = {re => 7.5, im => 2.5};

  my $z_ret = SPVM::MyComplex->complex_call_from_perl($z1, $z2);

  print "($z_ret->{re}, $z_ret->{im})\n";
}
