use strict;
use warnings;

use FindBin;
use lib "$FindBin::Bin/lib";

use SPVM 'MyEigen';

# Initialize SPVM


SPVM::MyEigen->test;

=head1 Eigen installation

=head2 Eigen Installation from source
  
  mkdir -p lib/SPVM/MyEigen.native
  mkdir -p lib/SPVM/MyEigen.native/include
  
  curl -L http://bitbucket.org/eigen/eigen/get/3.3.7.tar.gz > eigen-eigen-323c052e1731.tar.gz
  tar xfv eigen-eigen-323c052e1731.tar.gz
  rsync -av eigen-eigen-323c052e1731/Eigen lib/SPVM/MyEigen.native/include
