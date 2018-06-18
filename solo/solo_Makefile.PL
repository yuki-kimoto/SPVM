use strict;
use warnings;

my @c_source_files = grep { $_ ne 'SPVM.c' } glob '*.c';
my @object_files = map { $_ =~ s/\.c$/.o/; $_ } @c_source_files;

my $object_dir = 'solo';

my $CC = 'gcc';
my $CCFLAGS  = '-g -Wall -Wextra $(DEFINE) -std=c99';
my $LIBS = '-lm';
my $INC  = '-I. -Ilib/SPVM/Build';
my $OPTIMIZE = '-O';

my $CCCMD = "$CC $INC $CCFLAGS $OPTIMIZE";

my $makefile = <<"EOS";

all:
	make
	$CCCMD -o solo/spvm_main solo/spvm_main.c @object_files -lm

test:
	make
	$CCCMD -o solo/t/spvm_t_list solo/t/spvm_t_list.c spvm_list.o spvm_util_allocator.o -lm
	solo/t/spvm_t_list
	$CCCMD -o solo/t/spvm_t_hash solo/t/spvm_t_hash.c spvm_hash.o spvm_util_allocator.o spvm_hash_func.o -lm
	solo/t/spvm_t_hash

clean:
	rm -rf solo/spvm_main
EOS

my $makefile_file = 'solo/Makefile';

open my $fh, '>', $makefile_file
  or die "Can't open $makefile_file: $!";

print $fh $makefile;
