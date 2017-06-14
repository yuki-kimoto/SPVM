# Before 'make install' is performed this script should be runnable with
# 'make test'. After 'make install' it should work as 'perl SPVM.t'

#########################

# change 'tests => 1' to 'tests => last_test_to_print';

use strict;
use warnings;

use Test::More 'no_plan';;
BEGIN { use_ok('SPVM') };

#########################

# Insert your test code below, the Test::More module is use()ed here so read
# its man page ( perldoc Test::More ) for help writing this test script.

use SPVM::Compiler;

my $file = 't/SPVM.t';

use SPVM 'Test'; my $use_test_line = __LINE__;
use SPVM 'std'; my $use_std_line = __LINE__;

my $compiler = SPVM::get_compiler;

is_deeply(
  $compiler->package_infos,
  [
    {name => 'Test', file => $file, line => $use_test_line},
    {name => 'std', file => $file, line => $use_std_line}
  ]
);

$compiler->compile;
