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
my @csource_files = glob "$src_dir/*.c";
my @object_files = map { my $object_file = $_; $object_file =~ s/\.c$/.o/; $object_file } @csource_files;

my $object_dir = 'ctest';

my $cccmd = "cc -c @defines $ccflags $optimize";
my $ldcmd = "cc ";

my $makefile = <<"EOS";

all:
	$cccmd -I $header_dir -o spvm_list.o $src_dir/spvm_list.c
	$cccmd -I $header_dir -o spvm_hash.o $src_dir/spvm_hash.c

test:
	t/spvm_t_list
	t/spvm_t_hash

clean:
	rm -f t/spvm_t_list
	rm -f t/spvm_t_hash
	rm -f spvm_list.o
	rm -f spvm_hash.o
	rm -f Makefile
EOS

my $makefile_file = 'Makefile';

open my $fh, '>', $makefile_file
  or die "Can't open $makefile_file: $!";

print $fh $makefile;
