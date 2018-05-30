# SPVM solo

This is test program to run SPVM solo.

# Development

For compile, bison command is needed.

## Run
    
   yacc/bison.sh && make -f solo/Makefile DEFINE=-DDEBUG && ./spvm TestCase

## Cleanup

  make -f solo/Makefile clean
  
## Test
    
  yacc/bison.sh && make -f solo/Makefile DEFINE=-DDEBUG test

## Build csource

  gcc -g -O -Ilib/SPVM -c -o solo/csource/spvm_csource.o solo/csource/spvm_csource.c
  
  # Once
  yacc/bison.sh && make -f solo/Makefile && ./spvm TestCase && gcc -g -O -Ilib/SPVM -c -o solo/csource/spvm_csource.o solo/csource/spvm_csource.c

  # Once with warnings
  yacc/bison.sh && make -f solo/Makefile && ./spvm TestCase && gcc -g -O -Wall -Wextra -Ilib/SPVM -c -o solo/csource/spvm_csource.o solo/csource/spvm_csource.c

# Contributors

* [akinomyoga](https://github.com/akinomyoga) (Koichi Murase)
* [NAGAYASU Shinya](https://github.com/nagayasu-shinya)
* [Reini Urban](https://github.com/rurban)
