# SPVM solo

This is test program to run SPVM solo.

# Development

For compile, bison command is needed.

## Run
   # Debug mode
   yacc/bison.sh && make -f solo/Makefile DEFINE=-DDEBUG && ./spvm TestCase
   
   # Normal mode
   yacc/bison.sh && make -f solo/Makefile && ./spvm TestCase

## Cleanup

  make -f solo/Makefile clean
  
## Test
    
  yacc/bison.sh && make -f solo/Makefile DEFINE=-DDEBUG test

# Contributors

* [akinomyoga](https://github.com/akinomyoga) (Koichi Murase)
* [NAGAYASU Shinya](https://github.com/nagayasu-shinya)
* [Reini Urban](https://github.com/rurban)
