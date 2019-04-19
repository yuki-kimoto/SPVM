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

my $build_config = SPVM::Builder::Config->new_default;
$optimize ||= $build_config->get_config('optimize');

my $ccflags = $build_config->get_ccflags . " " . $build_config->get_extra_compiler_flags;

my $lddlflags = $build_config->get_lddlflags . " " . $build_config->get_extra_linker_flags;

my $src_dir = "lib/SPVM/Builder/src";
my @csource_files = glob "$src_dir/*.c";
my @object_files = map { my $object_file = $_; $object_file =~ s/\.c$/.o/; $object_file } @csource_files;

my $object_dir = 'solo';

my $cccmd = "cc -c @defines $ccflags $optimize";
my $ldcmd = "cc ";

my @shared_libs;
unless (grep { $_ eq '-DSPVM_DONT_USE_CORE_LIB' } @defines) {
  @shared_libs = (
    'blib/lib/SPVM/CORE.so',
    'blib/lib/SPVM/CORE.precompile.so',
    'blib/lib/SPVM/FileHandle.so',
  )
}

my $makefile = <<"EOS";

all:
	$cccmd -o solo/main.o solo/main.c
	$ldcmd -o solo/main -lm -o solo/main solo/main.o @object_files @shared_libs

test:
	$cccmd -o solo/t/spvm_t_list solo/t/spvm_t_list.c spvm_list.o spvm_util_allocator.o
	solo/t/spvm_t_list
	$cccmd -o solo/t/spvm_t_hash solo/t/spvm_t_hash.c spvm_hash.o spvm_util_allocator.o spvm_hash_func.o
	solo/t/spvm_t_hash

clean:
	rm -rf solo/main
EOS

my $makefile_file = 'solo/Makefile';

open my $fh, '>', $makefile_file
  or die "Can't open $makefile_file: $!";

print $fh $makefile;
