use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM::Builder::Info;

my $class_name = 'TestCase::UseResource::Basic';

my $builder_info = SPVM::Builder::Info->new(class_name => $class_name);

ok(1);

done_testing;
