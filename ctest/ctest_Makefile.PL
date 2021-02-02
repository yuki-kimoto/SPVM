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

my $src_dir = "lib/SPVM/Builder/src";
my @csource_files = glob "$src_dir/*.c";
my @object_files = map { my $object_file = $_; $object_file =~ s/\.c$/.o/; $object_file } @csource_files;

my $object_dir = 'ctest';

my $cccmd = "cc -c @defines $ccflags $optimize";
my $ldcmd = "cc ";

my $makefile = <<"EOS";

all:
	$cccmd -o ctest/spvm_list.o $src_dir/spvm_list.c
	$cccmd -o ctest/spvm_hash.o $src_dir/spvm_hash.c
	$cccmd -o ctest/spvm_hash_func.o $src_dir/spvm_hash_func.c
	$cccmd -o ctest/spvm_util_allocator.o $src_dir/spvm_util_allocator.c
	$ldcmd -o ctest/t/spvm_t_list ctest/t/spvm_t_list.c ctest/spvm_list.o ctest/spvm_util_allocator.o
	$ldcmd -o ctest/t/spvm_t_hash ctest/t/spvm_t_hash.c ctest/spvm_hash.o ctest/spvm_util_allocator.o ctest/spvm_hash_func.o

test:
	ctest/t/spvm_t_list
	ctest/t/spvm_t_hash

clean:
	rm -f ctest/t/spvm_t_list
	rm -f ctest/t/spvm_t_hash
	rm -f ctest/spvm_list.o
	rm -f ctest/spvm_hash.o
	rm -f ctest/spvm_hash_func.o
	rm -f ctest/spvm_util_allocator.o
	rm -f ctest/Makefile
EOS

my $makefile_file = 'ctest/Makefile';

open my $fh, '>', $makefile_file
  or die "Can't open $makefile_file: $!";

print $fh $makefile;
