all:

CC     	 := gcc
CFLAGS 	 := -g -O -Wall -Wextra $(DEFINE)
LIBS   	 := -lm 
INCLUDE  := -I. -Ilib/SPVM/Build
DIRS     :=

OBJDIR := solo/objs
DIRS += $(OBJDIR) $(OBJDIR)/solo $(OBJDIR)/t
$(OBJDIR)/%.o: %.c | $(OBJDIR) $(OBJDIR)/solo $(OBJDIR)/t
	$(CC) -std=c99 $(CFLAGS) $(INCLUDE) -c -o $@ $<

# libspvm
libspvm_SRCS := $(wildcard *.c) spvm_yacc.c
libspvm_OBJS := $(libspvm_SRCS:%.c=$(OBJDIR)/%.o)
$(OBJDIR)/spvm_toke.o: spvm_toke.c spvm_yacc.h
$(OBJDIR)/spvm_yacc_util.o: spvm_yacc_util.c spvm_yacc.h
libspvm.a: $(libspvm_OBJS)
	$(AR) crs $@ $(libspvm_OBJS)
all: libspvm.a

# spvm
spvm_SRCS    := solo/spvm_main.c
spvm_OBJS    := $(spvm_SRCS:%.c=$(OBJDIR)/%.o)
spvm_LDFLAGS := $(LDFLAGS) -L .
spvm_LIBS    := -lspvm $(LIBS)
spvm: $(spvm_OBJS) libspvm.a
	$(CC) $(INCLUDE) -std=c99 -o $@ $(spvm_LDFLAGS) $(spvm_OBJS) $(spvm_LIBS)
all: spvm

# test (solo/t/spvm_t_*)
test_names := $(wildcard solo/t/spvm_t_*.c)
test_names := $(test_names:solo/t/spvm_t_%.c=spvm_t_%)

spvm_t_LDFLAGS := $(LDFLAGS) -L .
spvm_t_LIBS    := -lspvm $(LIBS)
$(OBJDIR)/solo/t/spvm_t_%: $(OBJDIR)/solo/t/spvm_t_%.o libspvm.a
	$(CC) $(spvm_t_LDFLAGS) -DDEBUG -o $@ $< $(spvm_t_LIBS)
spvm_t_%: $(OBJDIR)/solo/t/spvm_t_%
	./$<
.PRECIOUS: $(OBJDIR)/solo/t/spvm_t_%.o $(OBJDIR)/solo/t/spvm_t_%
test: $(test_names)

# misc
$(DIRS):
	mkdir -p $@

clean:
	-find $(OBJDIR) -name \*.o | xargs rm -rf
	-rm -rf libspvm.a $(generated_sources)
