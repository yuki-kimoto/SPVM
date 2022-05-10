# SPVM - SPVM Language

SPVM(Static Perl Virtual Machine) is a perl-ish static typed programing language. SPVM provides fast calculation, fast array operations, easy C/C++ binding, and creating executable files.

# Installing SPVM

Install SPVM.

```
cpanm SPVM
```

# Examples

Write a SPVM Module.


```
# lib/SPVM/MyMath.spvm
class MyMath {
  static method sum : int ($nums : int[]) {

    my $total = 0;
    for (my $i = 0; $i < @$nums; $i++) {
      $total += $nums->[$i];
    }

    return $total;
  }
}
```

Use the SPVM Module from Perl.

```
# sum.pl
use strict;
use warnings;
use FindBin;
use lib "$FindBin::Bin/lib";

use SPVM 'MyMath';

# Call method
my $total = SPVM::MyMath->sum([3, 6, 8, 9]);

print "$total\n";
```

# Documents

Documents of SPVM language.

https://metacpan.org/pod/SPVM


# Test Status

|                                                                            Tests                                                                             |
|--------------------------------------------------------------------------------------------------------------------------------------------------------------|
| [![linux](https://github.com/yuki-kimoto/SPVM/actions/workflows/linux.yml/badge.svg)](https://github.com/yuki-kimoto/SPVM/actions/workflows/linux.yml)       |
| [![macos](https://github.com/yuki-kimoto/SPVM/actions/workflows/macos.yml/badge.svg)](https://github.com/yuki-kimoto/SPVM/actions/workflows/macos.yml)       |
| [![windows](https://github.com/yuki-kimoto/SPVM/actions/workflows/windows.yml/badge.svg)](https://github.com/yuki-kimoto/SPVM/actions/workflows/windows.yml) |

