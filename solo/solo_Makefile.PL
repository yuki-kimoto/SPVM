use strict;
use warnings;

my @c_source_files = grep { $_ ne 'SPVM.c' } glob '*.c';

my $makefile = <<"EOS";

all:

CC     	 := gcc
CCFLAGS  := -g -Wall -Wextra \$(DEFINE) -std=c99
LIBS   	 := -lm 
INC  := -I. -Ilib/SPVM/Build
OPTIMIZE := -O

CCCMD = \$(CC) \$(INC) \$(CCFLAGS) \$(OPTIMIZE)

OBJDIR := solo/objs
\$(OBJDIR)/%.o: %.c | \$(OBJDIR) \$(OBJDIR)/solo \$(OBJDIR)/t
	\$(CCCMD) -c -o \$@ \$<

# libspvm
libspvm_SRCS := @c_source_files
libspvm_OBJS := \$(libspvm_SRCS:%.c=\$(OBJDIR)/%.o)
\$(OBJDIR)/spvm_toke.o: spvm_toke.c spvm_yacc.h
\$(OBJDIR)/spvm_yacc_util.o: spvm_yacc_util.c spvm_yacc.h
libspvm.a: \$(libspvm_OBJS)
	\$(AR) crs \$@ \$(libspvm_OBJS)
all: libspvm.a

# spvm
spvm_SRCS    := solo/spvm_main.c
spvm_OBJS    := \$(spvm_SRCS:%.c=\$(OBJDIR)/%.o)
spvm_LDFLAGS := \$(LDFLAGS) -L .
spvm_LIBS    := -lspvm \$(LIBS)
spvm: \$(spvm_OBJS) libspvm.a
	\$(CCCMD) -o \$@ \$(spvm_LDFLAGS) \$(spvm_OBJS) \$(spvm_LIBS)
all: spvm


test:
	gcc -I. -Ilib/SPVM/Build -g -Wall -Wextra  -std=c99 -O -c -o spvm_util_allocator.o spvm_util_allocator.c
	gcc -I. -Ilib/SPVM/Build -g -Wall -Wextra  -std=c99 -O -c -o spvm_list.o spvm_list.c
	gcc -I. -Ilib/SPVM/Build -g -Wall -Wextra  -std=c99 -O -c -o solo/objs/solo/t/spvm_t_list.o solo/t/spvm_t_list.c
	gcc -I. -Ilib/SPVM/Build -g -Wall -Wextra  -std=c99 -O  -L . -DDEBUG -o solo/objs/solo/t/spvm_t_list solo/objs/solo/t/spvm_t_list.o spvm_list.o spvm_util_allocator.o -lm
	solo/objs/solo/t/spvm_t_list
	gcc -I. -Ilib/SPVM/Build -g -Wall -Wextra  -std=c99 -O -c -o spvm_hash_func.o spvm_hash_func.c
	gcc -I. -Ilib/SPVM/Build -g -Wall -Wextra  -std=c99 -O -c -o spvm_hash.o spvm_hash.c
	gcc -I. -Ilib/SPVM/Build -g -Wall -Wextra  -std=c99 -O -c -o solo/objs/solo/t/spvm_t_hash.o solo/t/spvm_t_hash.c
	gcc -I. -Ilib/SPVM/Build -g -Wall -Wextra  -std=c99 -O  -L . -DDEBUG -o solo/objs/solo/t/spvm_t_hash solo/objs/solo/t/spvm_t_hash.o spvm_hash.o spvm_util_allocator.o spvm_hash_func.o -lm
	solo/objs/solo/t/spvm_t_hash

clean:
	find \$(OBJDIR) -name \*.o | xargs rm -rf
	rm -rf libspvm.a \$(generated_sources)
EOS

my $makefile_file = 'solo/Makefile';

open my $fh, '>', $makefile_file
  or die "Can't open $makefile_file: $!";

print $fh $makefile;

