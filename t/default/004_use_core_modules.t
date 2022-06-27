use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use FindBin;
use lib "$FindBin::Bin/lib";

use SPVM 'Array1';

use Data::Dumper;
my @source_files = glob '.spvm_build/work/src/SPVM/*';
my @object_files = glob '.spvm_build/work/object/SPVM/*';
my @dynamic_lib_files = glob 'blib/lib/SPVM/*';
warn Dumper {
  source_files => \@source_files,
  object_files => \@object_files,
  dynamic_lib_files => \@dynamic_lib_files,
};

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
