use strict;
use warnings;

my @c_source_files = grep { $_ ne 'SPVM.c' } glob '*.c';

my $object_dir = 'solo/objs';

my $CC = 'gcc';
my $CCFLAGS  = '-g -Wall -Wextra $(DEFINE) -std=c99';
my $LIBS = '-lm';
my $INC  = '-I. -Ilib/SPVM/Build';
my $OPTIMIZE = '-O';

my $CCCMD = "$CC $INC $CCFLAGS $OPTIMIZE";

my $makefile = <<"EOS";

all:


$object_dir/%.o: %.c | $object_dir $object_dir/solo $object_dir/t
	$CCCMD -c -o \$\@ \$<

# libspvm
libspvm_SRCS := @c_source_files
libspvm_OBJS := \$(libspvm_SRCS:%.c=$object_dir/%.o)
$object_dir/spvm_toke.o: spvm_toke.c spvm_yacc.h
$object_dir/spvm_yacc_util.o: spvm_yacc_util.c spvm_yacc.h
libspvm.a: \$(libspvm_OBJS)
	\$(AR) crs \$\@ \$(libspvm_OBJS)
all: libspvm.a

# spvm
spvm_SRCS    := solo/spvm_main.c
spvm_OBJS    := \$(spvm_SRCS:%.c=$object_dir/%.o)
spvm: \$(spvm_OBJS) libspvm.a
	$CCCMD -o \$\@  -L . \$(spvm_OBJS) -lspvm $LIBS
all: spvm


test:
	gcc $CCCMD -c -o spvm_util_allocator.o spvm_util_allocator.c
	gcc $CCCMD -c -o spvm_list.o spvm_list.c
	gcc $CCCMD -c -o solo/objs/solo/t/spvm_t_list.o solo/t/spvm_t_list.c
	gcc $CCCMD  -L . -DDEBUG -o solo/objs/solo/t/spvm_t_list solo/objs/solo/t/spvm_t_list.o spvm_list.o spvm_util_allocator.o -lm
	solo/objs/solo/t/spvm_t_list
	gcc $CCCMD -c -o spvm_hash_func.o spvm_hash_func.c
	gcc $CCCMD -c -o spvm_hash.o spvm_hash.c
	gcc $CCCMD -c -o solo/objs/solo/t/spvm_t_hash.o solo/t/spvm_t_hash.c
	gcc $CCCMD  -L . -DDEBUG -o solo/objs/solo/t/spvm_t_hash solo/objs/solo/t/spvm_t_hash.o spvm_hash.o spvm_util_allocator.o spvm_hash_func.o -lm
	solo/objs/solo/t/spvm_t_hash

clean:
	find $object_dir -name \*.o | xargs rm -rf
	rm -rf libspvm.a
EOS

my $makefile_file = 'solo/Makefile';

open my $fh, '>', $makefile_file
  or die "Can't open $makefile_file: $!";

print $fh $makefile;

