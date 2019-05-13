# SPVM - Static Perl Virtual Machine

SPVM is Static Perl Virtual Machine. Provide fast calculation & easy C/C++ Binding.

# Features

* Fast culcuration, Fast array operation, Small memory
* Perl syntax, Static typing, Switch syntax, Have language specification
* Enum, Type inference, Anon subroutine, Variable captures
* Array initialization, 
* Reference count GC, Weaken reference, Module system
* Exception, Package variable
* Object oriented, Inteface, Value type, Value array type, Reference type
* Easy way to C/C++ binding, Automatically Perl binding, C99 math functions
* Dynamic linking, Subroutine precompile, AOT compile(create exe file)
* Native API(C level api), C99 standard

# Examples

```
SPVM Module:

  # lib/MyMath.spvm
  package MyMath {
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
  
  use SPVM 'MyMath';
  
  # Call subroutine
  my $total = MyMath->sum([3, 6, 8, 9]);
  
  print $total . "\n";
```

# More imformation

SPVM document
  
https://metacpan.org/pod/SPVM

