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

# Unexpected Charater
{
  {
    no utf8;
    my $source = "class MyClass { \xFE }";
    
    warn utf8::is_utf8 $source;
    
    compile_not_ok($source, q|Use of the character code "FE" is not allowed in source code.|);
  }
  
  {
    my $source = "class MyClass { \xFE }";
    
    warn utf8::is_utf8 $source;
    
    compile_not_ok($source, q|Use of the character code "FE" is not allowed in source code.|);
  }
}

done_testing;
