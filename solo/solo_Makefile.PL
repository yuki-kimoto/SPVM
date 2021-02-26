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

# OPTIMIZE
my $optimize = '-O3';

# CCFLAGS
my $ccflags = $Config{ccflags};
$ccflags .= ' -std=c99';
# I want to print warnings, but if gcc version is different, can't suppress no needed warning message.
# so I dicide not to print warning in release version
if ($ENV{SPVM_TEST_ENABLE_WARNINGS}) {
  $ccflags .= ' -Wall -Wextra -Wno-unused-label -Wno-unused-function -Wno-unused-label -Wno-unused-parameter -Wno-unused-variable -Wno-missing-field-initializers';
}

# INC
my $inc = '-Ilib/SPVM/Builder/include';

my $src_dir = "lib/SPVM/Builder/src";
my @csource_files = glob "$src_dir/*.c";
my @object_files = map { my $object_file = $_; $object_file =~ s/\.c$/.o/; $object_file } @csource_files;

my $object_dir = 'solo';

my $cccmd = "cc -c @defines $ccflags $optimize $inc";
my $ldcmd = "cc ";

my $makefile = <<"EOS";

all:
	$cccmd -o solo/main.o solo/spvm_boot.c
	$ldcmd -o solo/main -lm -o solo/main solo/main.o @object_files
	mkdir -p solo/SPVM

clean:
	rm -rf solo/main
	rm -rf solo/main.o
	rm -rf solo/Makefile
	rm -rf solo/SPVM
EOS

my $makefile_file = 'solo/Makefile';

open my $fh, '>', $makefile_file
  or die "Can't open $makefile_file: $!";

print $fh $makefile;
