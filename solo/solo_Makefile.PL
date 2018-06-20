use strict;
use warnings;
use Config;

use lib 'lib';
use SPVM::Build::Util;

my $build_setting = SPVM::Build::Util::default_build_setting;
my $optimize = $build_setting->get_config('optimize');

my $ccflags = "$Config{ccflags} " . join(' ', @{$build_setting->get_extra_compiler_flags});

my @c_source_files = grep { $_ ne 'SPVM.c' } glob '*.c';
my @object_files = map { $_ =~ s/\.c$/.o/; $_ } @c_source_files;

my $object_dir = 'solo';

my $cccmd = "gcc -I. -Ilib/SPVM/Build $ccflags -lm";

my $makefile = <<"EOS";

all:
	$cccmd -o solo/spvm_main solo/spvm_main.c @object_files

test:
	$cccmd -o solo/t/spvm_t_list solo/t/spvm_t_list.c spvm_list.o spvm_util_allocator.o
	solo/t/spvm_t_list
	$cccmd -o solo/t/spvm_t_hash solo/t/spvm_t_hash.c spvm_hash.o spvm_util_allocator.o spvm_hash_func.o
	solo/t/spvm_t_hash

clean:
	rm -rf solo/spvm_main
EOS

my $makefile_file = 'solo/Makefile';

open my $fh, '>', $makefile_file
  or die "Can't open $makefile_file: $!";

print $fh $makefile;
