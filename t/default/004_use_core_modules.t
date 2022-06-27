use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use FindBin;
use lib "$FindBin::Bin/lib";

use SPVM 'Array1';

use SPVM 'Array';
use SPVM 'Bool';
use SPVM 'ByteList';
use SPVM 'Byte';
use SPVM 'DoubleList';
use SPVM 'Double';
use SPVM 'FloatList';
use SPVM 'Float';
use SPVM 'Fn';
use SPVM 'Format';
use SPVM 'Hash';
use SPVM 'IntList';
use SPVM 'Int';
use SPVM 'List';
use SPVM 'LongList';
use SPVM 'Long';
use SPVM 'Point3D';
use SPVM 'Point';
use SPVM 'ShortList';
use SPVM 'Short';
use SPVM 'Sort';
use SPVM 'StringBuffer';
use SPVM 'StringList';
use SPVM 'Time';

ok(1);

done_testing;
