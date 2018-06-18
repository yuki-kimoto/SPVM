use strict;
use warnings;
use Config;
use Getopt::Long 'GetOptions';

use lib 'lib';
use SPVM::Build::Util;

my $debug_dump;
my $debug_yacc;
my $debug_object_count;

GetOptions(
  "--debug-dump" => \$debug_dump,
  "--debug-yacc" => \$debug_yacc,
  "--debug-object-count" => \$debug_object_count,
);

my $build_setting = SPVM::Build::Util::default_build_setting;
my $optimize = $build_setting->get_config('optimize');

my @defines;

if ($debug_dump) {
  push @defines, '-DSPVM_DEBUG_DUMP';
}
if ($debug_yacc) {
  push @defines, '-DSPVM_DEBUG_YACC';
}
if ($debug_object_count) {
  push @defines, '-DSPVM_DEBUG_OBJECT_COUNT';
}

my $ccflags = "$Config{ccflags} " . join(' ', @{$build_setting->get_extra_compiler_flags}, @defines);

my @c_source_files = grep { $_ ne 'SPVM.c' } glob '*.c';
my @object_files = map { $_ =~ s/\.c$/.o/; $_ } @c_source_files;

my $object_dir = 'solo';

my $cccmd = "gcc -I. -Ilib/SPVM/Build $ccflags -lm";

my $makefile = <<"EOS";

all:
	make
	$cccmd -o solo/spvm_main solo/spvm_main.c @object_files

test:
	make
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
