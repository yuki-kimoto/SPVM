use lib "t/testlib";
use TestAuto;

use strict;
use warnings;
use utf8;
use FindBin;

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

# SPVM compile error
{
  my $command = "$^X -Mblib $FindBin::Bin/perl_program.pl 2>&1";
  my $output = `$command 2>&1`;
  like($output, qr/CompileError/);
}

# SPVM dist compile error
{
  my $command = "$^X -Mblib $FindBin::Bin/dist.pl 2>&1";
  my $output = `$command 2>&1`;
  like($output, qr/CompileError/);
}


done_testing;
