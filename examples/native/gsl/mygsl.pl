use strict;
use warnings;

use FindBin;
use lib "$FindBin::Bin/lib";
use lib "../../../lib";

die unless -d "../../../lib";

use SPVM 'MyGSL';

# Initialize SPVM


SPVM::MyGSL->stat;

=head2 GSL Installation from source
  
  curl -L https://ftp.gnu.org/gnu/gsl/gsl-2.6.tar.gz > gsl-2.6.tar.gz
  tar xfv gsl-2.6.tar.gz
  cd gsl-2.6
  ./configure
  make
  sudo make install
