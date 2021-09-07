use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';



# Test valid symbol name(Method Name, Field Name, Pakage Variable Name, Lexical Variable Name)
use SPVM 'SPVM::TestCase::SymbolName_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_';

ok(1);
