# SPVM - Fast Calculation and Easy C/C++ Binding with perlish syntax and static typing

SPVM provide Fast Culcuration and Easy way to Bind C/C++ Language to Perl.

SPVM is before 1.0 under development! I will change implementation and specification without warnings.

## Usage

### Fast Array Operation using SPVM.

SPVM Module:

    # lib/SPVM/MyMath.spvm
    package MyMath {
      
      # Sub Declaration
      sub sum ($nums : int[]) : int {
        
        # Culcurate total
        my $total = 0;
        for (my $i = 0; $i < @$nums; $i++) {
          $total += $nums->[$i];
        }
        
        return $total;
      }
    }

Use SPVM Module from Perl
  
    use FindBin;
    use lib "$FindBin::Bin/lib";
    
    # Use SPVM module
    use SPVM 'MyMath';
    
    # New SPVM int array
    my $sp_nums = SPVM::new_int_array([3, 6, 8, 9]);
    
    # Call SPVM subroutine
    my $total = SPVM::MyMath::sum($sp_nums);
    
    print $total . "\n";

If you know more SPVM syntax, see [lib/SPVM/Document/Specification.pod].

If you know more Functions to convert Perl Data to SPVM Data, see [lib/SPVM/Document/Functions.pod].

### C Extension using SPVM

SPVM Module:

    # lib/SPVM/MyMathNative.spvm
    package MyMathNative {
      
      # Sub Declaration
      sub sum ($nums : int[]) : native int;
    }

C Source File;

  // lib/SPVM/MyMathNative.native/MyMathNative.c
  #include <spvm_api.h>

  int32_t SPVM__MyMathNative__sum(SPVM_API* api, SPVM_API_VALUE* args) {
    
    // First argument
    SPVM_API_OBJECT* sp_nums = args[0].object_value;
    
    // Array length
    int32_t length = api->get_array_length(api, sp_nums);
    
    // Elements pointer
    int32_t* nums = api->get_int_array_elements(api, sp_nums);
    
    // Culcurate total
    int32_t total = 0;
    {
      int32_t i;
      for (i = 0; i < length; i++) {
        total += nums[i];
      }
    }
    
    return total;
  }

Use Extension Module from Perl:

    use FindBin;
    use lib "$FindBin::Bin/lib";
    
    # Use SPVM module
    use SPVM 'MyMathNative';
    
    # New SPVM int array
    my $sp_nums = SPVM::new_int_array([3, 6, 8, 9]);
    
    # Call SPVM subroutine
    my $total = SPVM::MyMathNative::sum($sp_nums);
    
    print $total . "\n";

If you know more SPVM Extension, see [lib/SPVM/Document/Extension.pod].

If you know the APIs to manipulate SPVM data, see [lib/SPVM/Document/NativeAPI.pod].

# Contributors

* [akinomyoga](https://github.com/akinomyoga) (Koichi Murase)
* [NAGAYASU Shinya](https://github.com/nagayasu-shinya)
* [Reini Urban](https://github.com/rurban)
* [chromatic](https://github.com/chromatic)
* [Kazutake Hiramatsu](https://github.com/kazhiramatsu)
