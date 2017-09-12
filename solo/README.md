# SPVM solo

This is test program to run SPVM solo.

# Development

For compile, bison command is needed.

## Run
    
   yacc/bison.sh && make -f solo/Makefile DEFINE=-DDEBUG && ./spvm Test

## Test
    
    make -f solo/Makefile test

## Types

Use the following types in source codes. This is defined in the standard header `<stdint.h>`.

    _Bool
    uint8_t
    int8_t
    int16_t
    int32_t
    int64_t
    float
    double

# Contributors

* [akinomyoga](https://github.com/akinomyoga) (Koichi Murase)
* [NAGAYASU Shinya](https://github.com/nagayasu-shinya)
* [Reini Urban](https://github.com/rurban)
