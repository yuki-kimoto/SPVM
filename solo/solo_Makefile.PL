use strict;
use warnings;
use Config;

use lib 'lib';
use SPVM::Builder::Util;
use SPVM::Builder::Config;
use Getopt::Long 'GetOptions';
use File::Basename 'basename';

GetOptions(
  "DEFINE=s" => \my @defines,
  "OPTIMIZE=s" => \my $optimize,
);

unless (defined $optimize) {
  $optimize = '-O3';
}

# Add -D
@defines = map { "-D$_" } @defines;

# CCFLAGS
my $ccflags .= '-std=gnu99';

# INC
my $inc = '-Ilib/SPVM/Builder/include';

my $object_dir = 'solo';

my $cccmd = "cc -c @defines $ccflags $optimize $inc";
my $ldcmd = "cc ";

my $spvm_core_source_file_names = SPVM::Builder::Util::get_spvm_core_source_file_names();

my @source_files = map { "lib/SPVM/Builder/src/$_" } @$spvm_core_source_file_names;

my @object_files = map { my $object_file = basename $_; $object_file =~ s/\.c$/.o/; "solo/work/$object_file" } @source_files;

my @cccmds = map { "$cccmd -o $object_files[$_] $source_files[$_]" } (0 .. @source_files - 1);
push @cccmds, "$cccmd -o solo/work/myexe.o solo/myexe.c";

my $makefile = <<"EOS";

all:
\tmkdir -p solo/work
EOS

$makefile .= join("\n", map { "\t$_" } @cccmds) . "\n";

$makefile .= <<"EOS";
\t$ldcmd -o solo/work/myexe solo/work/myexe.o @object_files

clean:
\trm -rf solo/work
\trm -rf solo/Makefile
EOS

my $makefile_file = 'solo/Makefile';

open my $fh, '>', $makefile_file
  or die "Can't open $makefile_file: $!";

print $fh $makefile;
