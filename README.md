# SPVM - Static Perl Virtual Machine

Static Perl Virtual Machine. Fast calculation, fast array operation, and easy C/C++ Binding.

# Features

* Fast calculation, Fast array operation, Small memory
* Perl syntax, Static typing, Switch syntax, Have language specification
* Enum, Type inference, Anon method, Variable captures
* Array initialization, 
* Reference count GC, Weaken reference, Module system
* Exception, Package variable
* Object oriented, Inteface, Value type, Value array type, Reference type
* Easy way to C/C++ binding, Automatically Perl binding, C99 math functions
* Dynamic linking, Method precompile, AOT compile(create exe file)
* Native API(C level api), C99 standard

# Examples

```
SPVM Module:

  # lib/SPVM/MyMath.spvm
  package SPVM::MyMath {
    sub sum : int ($nums : int[]) {
      
      my $total = 0;
      for (my $i = 0; $i < @$nums; $i++) {
        $total += $nums->[$i];
      }
      
      return $total;
    }
  }
```

Use SPVM Module from Perl

```
  use FindBin;
  use lib "$FindBin::Bin/lib";
  
  use SPVM 'SPVM::MyMath';
  
  # Call method
  my $total = SPVM::MyMath->sum([3, 6, 8, 9]);
  
  print $total . "\n";
```

# More imformation

SPVM Document

https://yuki-kimoto.github.io/spvmdoc-public/

SPVM CPAN

https://metacpan.org/pod/SPVM

