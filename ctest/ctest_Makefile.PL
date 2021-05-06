use strict;
use warnings;
use Config;

use lib 'lib';
use SPVM::Builder::Util;
use SPVM::Builder::Config;
use Getopt::Long 'GetOptions';

my @defines;
my $optimize;

GetOptions(
  "--DEFINE=s" => \@defines,
  "--OPTIMIZE=s" => \$optimize,
);

# Add -D
@defines = map { "-D$_" } @defines;

# Add -
if ($optimize) {
  $optimize = "$optimize";
}

my $build_config = SPVM::Builder::Config->new_c99;
$optimize ||= $build_config->get_config('optimize');

my $ccflags = $build_config->get_ccflags;

my $header_dir = "../lib/SPVM/Builder/include";
my $src_dir = "../lib/SPVM/Builder/src";

my $object_dir = 'ctest';

my $cccmd = "cc -c @defines $ccflags $optimize";
my $ldcmd = "cc ";

my $makefile = <<"EOS";

all:
	$cccmd -I $header_dir $src_dir/spvm_list.c
	$cccmd -I $header_dir t/test_spvm_list.c
	$ldcmd -o test_spvm_list test_spvm_list.o spvm_list.o 
	$cccmd -I $header_dir $src_dir/spvm_hash.c
	$cccmd -I $header_dir t/test_spvm_hash.c
	$ldcmd -o test_spvm_hash test_spvm_hash.o spvm_hash.o 

test:
	./test_spvm_list
	./test_spvm_hash

clean:
	rm *.o
	rm -f test_spvm_list
	rm -f test_spvm_hash
	rm -f Makefile
EOS

my $makefile_file = 'Makefile';

open my $fh, '>', $makefile_file
  or die "Can't open $makefile_file: $!";

print $fh $makefile;
