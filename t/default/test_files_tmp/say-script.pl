use lib "t/testlib";
use TestAuto;

use strict;
use warnings;
use FindBin;

use SPVM 'TestCase::Say';



use TestFile;

SPVM::TestCase::Say->test_say_undef;