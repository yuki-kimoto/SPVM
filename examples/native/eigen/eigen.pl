use strict;
use warnings;

use FindBin;
use lib "$FindBin::Bin/lib";

use SPVM 'Eigen';

Eigen->test;

=head1 Eigen installation

=head2 Eigen Installation from source
  
  mkdir spvm_build
  mkdir spvm_build/src
  mkdir spvm_build/include

  curl -L http://bitbucket.org/eigen/eigen/get/3.3.7.tar.gz > spvm_build/src/eigen-eigen-323c052e1731.tar.gz
  tar xf spvm_build/src/eigen-eigen-323c052e1731.tar.gz
  rsync -a eigen-eigen-323c052e1731/Eigen spvm_build/include
