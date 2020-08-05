use strict;
use warnings;

use FindBin;
use lib "$FindBin::Bin/lib";

use SPVM 'MyMatrix';

MyMatrix->add_float_matrix;

MyMatrix->sub_float_matrix;

MyMatrix->scamul_float_matrix;

MyMatrix->mul_float_matrix;
