use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;



# Test valid symbol name(Method Name, Field Name, Pakage Variable Name, Local Variable Name)
use SPVM 'TestCase::SymbolName_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_';

ok(1);

done_testing;
