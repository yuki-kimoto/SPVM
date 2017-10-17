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

# Contributors

* [akinomyoga](https://github.com/akinomyoga) (Koichi Murase)
* [NAGAYASU Shinya](https://github.com/nagayasu-shinya)
* [Reini Urban](https://github.com/rurban)
