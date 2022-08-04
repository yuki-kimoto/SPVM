use strict;
use warnings;
use utf8;
use FindBin;

use SPVM::Builder;

use lib "$FindBin::Bin/../default/lib";
use lib "$FindBin::Bin/lib";

use MyTest qw(compile_not_ok_file compile_not_ok);

use Test::More;
# switch statement
{
  {
    my $source = 'class Tmp { use Fn; static method main : void () { switch (1) { case Fn->INT32_MAX: {} } }}';
    compile_not_ok($source, qr/The operand of the case statement must be a constant value/);
  }
  {
    my $source = 'class Tmp { use Fn; static method main : void () { switch (1) { case 1: {} case 1: {} } }}';
    compile_not_ok($source, qr/The value of the case statement can't be duplicated/);
  }
  
  
}


done_testing;
