# SPVM - Fast calculation, GC, static typing, VM with perlish syntax

Do you need **faster Perl**? SPVM provides fast calculation to Perl.

- **Fast calculation** - The Perl's biggest weak point is the calculation performance. SPVM provides fast calculations.
- **GC** - You don't need to care about freeing memory
- **Static typing** - Static typing for performance
- **VM** - Byte codes are generated so that you can run them on SPVM language
- **Perlish syntax** - SPVM syntax is very similar to Perl
- **Perl module** - SPVM function can be called from Perl itself (Not yet implemented).

This is now under **developing**.

# SPVM examples

```
package Main {

  sub main () : int {
    my $num1 = 2;
    my $num2 = 5;
    
    my $num3 = sum($num1, $num2);
    
    std::println_int($num3);
    
    return 0;
  }

  sub sum ($num1 : int, $num2 : int) : int {
    my $num3 = $num1 + $num2;
    
    return $num3;
  }
}
```

## Run

    make
    ./spvm Main

Output:


    7

# SPVM specification

## Type

### Numeric type

Numeric types are `byte`, `short`, `int`, `long`, `float`, `double`.

    byte    signed integer          1byte
    short   signed integer          2byte
    int     signed integer          4byte
    long    signed integer          8byte
    float   floating-point number   4byte
    double  floating-point number   8byte

Declaration

    my $value : byte;
    my $value : short;
    my $value : int;
    my $value : long;
    my $value : float;
    my $value : double;

### Reference type

Reference types are `array` and `object`.

**Object type**

    ClassName

Declaration

    my $object : ClassName;

**Array type**

    byte[]   byte array
    short[]  short array
    int[]    int array array
    long[]   long array
    float[]  float array
    doube[]  double array
    ClassName[] object array

Declaration

    my $values : byte[];
    my $values : short[];
    my $values : int[];
    my $values : long[];
    my $values : float[];
    my $values : double[];
    my $values : ClassName[];

## Type inference

If the type of right value is known, the type of left value is automatically decided.
    
    # Type of $value2 is byte.
    my $value1 : byte;
    my $value2 = $value1;
    
    # Type of $values2 is int[]
    my $values1 = new int[3];
    my $values2 = $values1;
    
    # Type of $object2 is ClassName
    my $object1 = new ClassName
    my $object2 = $object1;

## Constant

### Constant type

Type of constant default integral value is `int`.
    
    # int type
    1;
    3;

Type of constant default floating-point value is `double`.

    # double
    1.2
    5.3
    
Type of constant is specified by type specifier.
    
    # long
    3L
    
    # float
    3.2f
    
    # double
    3.2d

## Name

### Package name

Package name is a conbination of alphabets, numbers, and `::`. Numbers should not appear as the first character. `_` can't be used in class name.
    
    # OK
    Foo
    Foo::Bar
    Foo1::Bar1
    
    # Not OK
    1Foo
    Foo::2Bar
    Foo_Bar;

### Subroutine name

Subroutine name is a conbination of alphabets, numbers, and `_` separaters. continual `_`(For example `__`) can't be used in subroutine name.

    # OK
    foo
    foo1
    foo_bar
    
    # Not OK
    1foo
    foo__bar

### Field name

Field name is a conbination of alphabets, numbers, and `_` separaters. continual `_`(For example `__`) can't be used in field name.

    # OK
    foo
    foo1
    foo_bar
    
    # Not OK
    1foo
    foo__bar

### Absolute name

Absolute name is combination of package name and subroutine name, or package name and field name.

    ClassName1::foo
    ClassName1::ClassName2::foo_bar

## Limitation

- Object can't have object and array of object

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
