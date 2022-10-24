use lib "t/testlib";
use TestAuto;

use strict;
use warnings;
use utf8;

use SPVM::Builder;

my $test_dir;
my $test_dir_vm;
my $build_dir;

BEGIN {
  $test_dir = $ENV{SPVM_TEST_DIR};
  $test_dir_vm = $ENV{SPVM_TEST_DIR_VM};
  $build_dir = $ENV{SPVM_BUILD_DIR};
}

use lib "$test_dir_vm/lib";
use lib "$test_dir/lib";

use MyTest qw(compile_not_ok_file compile_not_ok);

use Test::More;
# switch statement
{
  {
    my $source = 'class Tmp { use Fn; static method main : void () { switch (1) { case Fn->INT32_MAX: {} } }}';
    compile_not_ok($source);
  }
  {
    my $source = 'class Tmp { use Fn; static method main : void () { switch (1) { case 1: {} case 1: {} } }}';
    compile_not_ok($source);
  }
  
  
}


done_testing;
