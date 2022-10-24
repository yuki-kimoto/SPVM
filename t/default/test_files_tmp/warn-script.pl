use lib "t/testlib";
use TestAuto;

use strict;
use warnings;
use FindBin;

use SPVM 'TestCase::Warn';



use TestFile;

SPVM::TestCase::Warn->test_warn_undef;