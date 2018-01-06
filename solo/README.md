# SPVM solo

This is test program to run SPVM solo.

# Development

For compile, bison command is needed.

## Run
    
   yacc/bison.sh && make -f solo/Makefile DEFINE=-DDEBUG && ./spvm TestCase

## Cleanup

  yacc/bison.sh && make -f solo/Makefile cleanup
  
## Test
    
  yacc/bison.sh && make -f solo/Makefile DEFINE=-DDEBUG test

## Build jitcode

  gcc -g -O -Ilib/SPVM -c -o solo/jitcode/spvm_jitcode.o solo/jitcode/spvm_jitcode.c
  
  # Once
  yacc/bison.sh && make -f solo/Makefile && ./spvm TestCase && gcc -g -O -Ilib/SPVM -c -o solo/jitcode/spvm_jitcode.o solo/jitcode/spvm_jitcode.c

  # Once with warnings
  yacc/bison.sh && make -f solo/Makefile && ./spvm TestCase && gcc -g -O -Wall -Wextra -Ilib/SPVM -c -o solo/jitcode/spvm_jitcode.o solo/jitcode/spvm_jitcode.c


# Contributors

* [akinomyoga](https://github.com/akinomyoga) (Koichi Murase)
* [NAGAYASU Shinya](https://github.com/nagayasu-shinya)
* [Reini Urban](https://github.com/rurban)
