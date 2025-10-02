# Developers Note

## make

### Tests

```
perl Makefile.PL
make
make test
```

### Unit Tests

```
make && perl -Mblib t/02_vm/05_op/comparison_operator.t
```

### Cleanup

```
make clean
```

### Create MANIFEST

```
perl Makefile.PL
rm MANIFEST
make manifest
```

### Create distribution

```
perl Makefile.PL
make disttest
make dist
```

### Install SPVM

```
make install
```

## Solo Tests

### SPVM solo test command using spvm command

```
# Normal run
yacc/bison.sh && perl Makefile.PL --no-build-spvm-modules && make && perl -Mblib blib/script/spvm -I solo/lib/SPVM solo/script/myapp.spvm foo bar

# Debug run
yacc/bison.sh && perl Makefile.PL --no-build-spvm-modules --OPTIMIZE="-O0 -g" && make && perl -Mblib blib/script/spvm -I solo/lib/SPVM solo/script/myapp.spvm foo bar

# Debug run - Print memory count
yacc/bison.sh && perl Makefile.PL --no-build-spvm-modules --OPTIMIZE="-O0 -g" --DEFINE=SPVM_DEBUG_MEMORY && make && perl -Mblib blib/script/spvm -I solo/lib/SPVM solo/script/myapp.spvm foo bar

# Debug run - Print AST, package information, operaion codes
yacc/bison.sh && perl Makefile.PL --no-build-spvm-modules --OPTIMIZE="-O0 -g" --DEFINE=SPVM_DEBUG_COMPILE && make && perl -Mblib blib/script/spvm -I solo/lib/SPVM solo/script/myapp.spvm foo bar

# Debug run - Print yacc result
yacc/bison.sh && perl Makefile.PL --no-build-spvm-modules --DEFINE=SPVM_DEBUG_YACC --DEFINE=SPVM_DEBUG_COMPILE && make && perl -Mblib blib/script/spvm -I solo/lib/SPVM solo/script/myapp.spvm foo bar
```

### SPVM solo test command using spvmcc command

```
# Normal run
make && perl -Mblib blib/script/spvmcc -B solo/.spvm_build -I solo/lib/SPVM -o solo/.spvm_build/work/myapp -f --no-config solo/script/myapp.spvm && ./solo/.spvm_build/work/myapp foo bar

# Debug run
make && perl -Mblib blib/script/spvmcc -B solo/.spvm_build -I solo/lib/SPVM -o solo/.spvm_build/work/myapp --optimize "-O0 -g" -f --no-config solo/script/myapp.spvm && ./solo/.spvm_build/work/myapp foo bar

# Debug run - Print memory count
make && perl -Mblib blib/script/spvmcc -B solo/.spvm_build -I solo/lib/SPVM -o solo/.spvm_build/work/myapp --define-spvm SPVM_DEBUG_MEMORY -f solo/script/myapp.spvm && ./solo/.spvm_build/work/myapp foo bar

# Debug run - Print memory count using config file
make && perl -Mblib blib/script/spvmcc -B solo/.spvm_build -I solo/lib/SPVM -o solo/.spvm_build/work/myapp --mode debug_memory_count -f solo/script/myapp.spvm && ./solo/.spvm_build/work/myapp foo bar
```

### Cleanup

```
rm solo/.spvm_build/work/myapp
```

### See batcktrace of core dump

```
# Compilation for debug
perl Makefile.PL --OPTIMIZE="-O0 -g" && make

# Compiliation time stack trace
gdb perl core

# Runtime stack trace
gdb solo/.spvm_build/work/myapp core

bt
```
      
If core file is not output, set the following.

```
ulimit -c unlimited
```

Check memory with valgrind

```
valgrind --leak-check=full --track-origins=yes perl -Mblib t/02_vm/05_op/reference.t
```

## Portability Note
  
SPVM is run on various environments.
Main compiler targets is gcc, clang, MinGW.
Main OS targets is Linux/Unix, Windows(MinGW), macOS.
To keep maxmam portability in SPVM, I follow the following rule.
  
- Don't use realloc function.
- Don't use global variables.
- Don't use inline keyword in places other than spvm_implement.h.
- Use -std=gnu99 flag when native classes are compiled.
- Use fgetc function instead of getc function.
- Don't use error numbers defined in error.h.
- Don't contain os dependency features(for example unistd.h, windows.h), but only spvm_mutex.c uses Windows-specific functionality to implement mutexes portable.
- Default loaded module(such as Byte, Short) must not have native and precompile attributes.
- Avoid using Feature_test_macros(such as _XOPEN_SOURCE, _POSIX_SOURCE, _POSIX_C_SOURCE) as possible, but only spvm_strerror.c uses _POSIX_C_SOURCE to implement portable and thread-safe strerror.
- Do not invoke system calls. System calls are implemented in CPAN modules, such as SPVM::Sys. Currently the only exception to this is mutexes. This is necessary to make the assignment operation thread-safe.
- Don't create temporary files(this means don't use File::Temp) for SPVM JIT compilation. DLL files are opened in runtime, Windows dll file can't be removed if DLL files are opened.
- Newlines in source codes are LF.

## Coding Guide Line

- use int8_t, int16_t, int32_t, int64_t instead of byte, short, int, long, _Bool.
- char is used for only character.
- char[] is used for only string.
- constant value is defined by enum { } syntax.
- constant name is ,for example, SPVM_TYPE_C_FLAG_REF. all character is upper case or under score. need _C_ between package name and constant base name
- fix all warnings before CPAN release
- Tab is 2 space.

## Utilities

### Gets SPVM Core Perl module files

```
find lib | grep -P '(Builder|BlessedObject|ExchangeAPI|Global|SPVM\.pm)' | grep '\.pm' | perl -p -e 's|lib/||' | sort
```

### Gets SPVM header files

```
find lib | grep Builder | grep -P '\.h$' | perl -p -e 's|lib/SPVM/Builder/include/||' | sort
```

### Gets SPVM source files

```
find lib | grep Builder | grep -P '\.c$' | perl -p -e 's|lib/SPVM/Builder/src/||' | sort
```

### Gets SPVM Compilation and Rintime module files

```
find lib | grep -P '(Native\b)' | grep -P '\.(spvm|c)$' | perl -p -e 's|lib/||' | sort
```

### Print config 

```
# All config
perl -MConfig -MData::Dumper -e 'local $Data::Dumper::Sortkeys = 1; print Dumper \%Config;'

# ivsize
perl -MConfig -MData::Dumper -e 'local $Data::Dumper::Sortkeys = 1; print Dumper \%Config;' | grep ivsize

# myuname
perl -MConfig -MData::Dumper -e 'local $Data::Dumper::Sortkeys = 1; print Dumper \%Config;' | grep myuname

# make
perl -MConfig -MData::Dumper -e 'local $Data::Dumper::Sortkeys = 1; print Dumper \%Config;' | grep make

# dlext
perl -MConfig -MData::Dumper -e 'local $Data::Dumper::Sortkeys = 1; print Dumper \%Config;' | grep dlext
```

## Gets all keywords

```
perl -n -e 'if (/strcmp\s*\(\s*symbol_name\s*,\s*"(.+?)"/) { print "$1\n" } ' lib/SPVM/Builder/src/spvm_toke.c
```
    
### Gets the definition of syntax parsing

```
perl -n -e 'if (/^(%token|%type|%right|%nonassoc|%left|[a-zA-Z]|\s+:|\s+\|)(.+)/) { my $line = "$1$2"; if ($line =~ /^[a-zA-Z]/) { print "\n"; } print "$line\n" } ' yacc/spvm_yacc.y
```

### Gets the links of SPVM modules for POD

```
find lib | grep -P '\.pm$' | grep -v 'lib/SPVM.pm$' | perl -p -e 's/\.pm$//' | sort | grep -v -P '^lib/SPVM(\.pm|/(Global|ExchangeAPI|Document|Builder|BlessedObject|Dist))' | perl -p -e 'chomp;s|lib/SPVM/||; s|/|::|g; $_ = "=item * L<SPVM::$_|SPVM::$_>\n\n";'
```

## spvmdist

### Creates a SPVM distribution

```
spvmdist --user-name="Yuki Kimoto" --user-email="kimoto.yuki@gmail.com"  Foo
```

### Create only class files

```
spvmdist --version_from Foo --only-lib-files --user-name="Yuki Kimoto" --user-email="kimoto.yuki@gmail.com" Foo::Bar lib
```

