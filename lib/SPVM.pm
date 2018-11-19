package SPVM;

use 5.008007;
use strict;
use warnings;

use DynaLoader;
use File::Basename 'basename', 'dirname';

use SPVM::Data;
use SPVM::Data::Array;
use SPVM::Data::Package;
use SPVM::Data::String;

use SPVM::Builder;
use SPVM::ExchangeAPI;

use Encode 'encode', 'decode';

use Carp 'confess';

our $VERSION = '0.0391';

my $SPVM_ENV;
my $BUILDER;

require XSLoader;
XSLoader::load('SPVM', $VERSION);

sub import {
  my ($class, $package_name) = @_;
  
  unless ($BUILDER) {
    my $build_dir = $ENV{SPVM_BUILD_DIR};
    if (defined $build_dir) {
      # Remove traling slash
      $build_dir = File::Spec->catdir(File::Spec->splitdir($build_dir));
    }
    $BUILDER = SPVM::Builder->new(build_dir => $build_dir);
  }

  # Add package informations
  if (defined $package_name) {
    my ($file, $line) = (caller)[1, 2];
    my $package_info = {
      name => $package_name,
      file => $file,
      line => $line
    };
    push @{$BUILDER->{package_infos}}, $package_info;
  }
}

# Compile SPVM source code just after compile-time of Perl
CHECK {
  if ($BUILDER) {
    my $compile_success = $BUILDER->build_spvm();
    unless ($compile_success) {
      exit(255);
    }
    
    # Set env
    $SPVM_ENV = $BUILDER->{env};
  }
}


sub set_exception_undef { SPVM::ExchangeAPI::set_exception_undef($SPVM_ENV, @_) }
sub get_memory_blocks_count { SPVM::ExchangeAPI::get_memory_blocks_count($SPVM_ENV, @_) }
sub call_sub { SPVM::ExchangeAPI::call_sub($SPVM_ENV, @_) }

sub new_byte_array { SPVM::ExchangeAPI::new_byte_array($SPVM_ENV, @_) }
sub new_byte_array_from_binary { SPVM::ExchangeAPI::new_byte_array_from_binary($SPVM_ENV, @_) }
sub new_byte_array_from_string { SPVM::ExchangeAPI::new_byte_array_from_string($SPVM_ENV, @_) }

sub new_short_array { SPVM::ExchangeAPI::new_short_array($SPVM_ENV, @_) }
sub new_short_array_from_binary { SPVM::ExchangeAPI::new_short_array_from_binary($SPVM_ENV, @_) }

sub new_int_array { SPVM::ExchangeAPI::new_int_array($SPVM_ENV, @_) }
sub new_int_array_from_binary { SPVM::ExchangeAPI::new_int_array_from_binary($SPVM_ENV, @_) }

sub new_long_array { SPVM::ExchangeAPI::new_long_array($SPVM_ENV, @_) }
sub new_long_array_from_binary { SPVM::ExchangeAPI::new_long_array_from_binary($SPVM_ENV, @_) }

sub new_float_array { SPVM::ExchangeAPI::new_float_array($SPVM_ENV, @_) }
sub new_float_array_from_binary { SPVM::ExchangeAPI::new_float_array_from_binary($SPVM_ENV, @_) }

sub new_double_array { SPVM::ExchangeAPI::new_double_array($SPVM_ENV, @_) }
sub new_double_array_from_binary { SPVM::ExchangeAPI::new_double_array_from_binary($SPVM_ENV, @_) }

sub new_string { SPVM::ExchangeAPI::new_string($SPVM_ENV, @_) }
sub new_string_from_binary { SPVM::ExchangeAPI::new_string_from_binary($SPVM_ENV, @_) }

sub new_object_array { SPVM::ExchangeAPI::new_object_array($SPVM_ENV, @_) }
sub new_multi_array { SPVM::ExchangeAPI::new_multi_array($SPVM_ENV, @_) }
sub new_value_array { SPVM::ExchangeAPI::new_value_array($SPVM_ENV, @_) }
sub new_value_array_from_binary { SPVM::ExchangeAPI::new_value_array_from_binary($SPVM_ENV, @_) }

1;

=encoding UTF-8

=head1 NAME

SPVM - Static Perl Virtual Machine. Fast calcuration & Easy C/C++ Binding

=head1 SYNOPSIS

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

Use SPVM Module from Perl
  
  use FindBin;
  use lib "$FindBin::Bin/lib";
  
  use SPVM 'MyMath';
  
  # New int array
  my $sp_nums = SPVM::new_int_array([3, 6, 8, 9]);
  
  # Call subroutine
  my $total = MyMath->sum($sp_nums);
  
  print $total . "\n";

=head1 DESCRIPTION

SPVM is Static Perl Virtual Machine. Provide fast calcuration & easy C/C++ Binding.

B<Features:>

=over 4

=item * B<Fast culcuration>, B<Fast array operation>, B<Small memory>

=item * B<Perl syntax>, B<Static typing>, B<Switch syntax>, B<Have language specification>

=item * B<Enum>, B<Type inference>, B<Anon subroutine>, B<Variable captures>

=item * B<Array initialization>, 

=item * B<Reference count GC>, B<Weaken reference>, B<Module system>

=item * B<Exception>, B<Package variable>

=item * B<Object oriented>, B<Inteface>, B<Value type>, B<Value array type>, B<Reference type>

=item * B<Easy way to C/C++ binding>, B<Automatically Perl binding>, B<C99 math functions>

=item * B<Dynamic linking>, B<Subroutine precompile>, B<AOT compile(create exe file)>

=item * B<Native API(C level api)>, B<C99 standard>

=back

=head1 EXAMPLES

=head2 How to use SPVM from Perl

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

Use SPVM Module from Perl
  
  use FindBin;
  use lib "$FindBin::Bin/lib";
  
  use SPVM 'MyMath';
  
  # New int array
  my $sp_nums = SPVM::new_int_array([3, 6, 8, 9]);
  
  # Call subroutine
  my $total = MyMath->sum($sp_nums);
  
  print $total . "\n";

See also L<SPVM::Document::ExchangeAPI>.

=head2 C Extension using SPVM

SPVM Module:

  # lib/MyMathNative.spvm
  package MyMathNative {
    
    # Sub Declaration
    native sub sum int ($nums : int[]);
  }

C Source File;

  // lib/MyMathNative.native/MyMathNative.c
  #include <spvm_native.h>

  int32_t SPVM_NATIVE_MyMathNative__sum(SPVM_ENV* env, SPVM_VALUE* stack) {
    
    // First argument
    void* sp_nums = stack[0].oval;
    
    // Array length
    int32_t length = env->get_array_length(env, sp_nums);
    
    // Elements pointer
    int32_t* nums = env->get_int_array_elements(env, sp_nums);
    
    // Culcurate total
    int32_t total = 0;
    {
      int32_t i;
      for (i = 0; i < length; i++) {
        total += nums[i];
      }
    }
    
    // Return value is set to stack[0]
    stack[0].ival = total;
    
    // If function success, return SPVM_SUCCESS
    return SPVM_SUCCESS;
  }

Use Extension Module from Perl:

  use FindBin;
  use lib "$FindBin::Bin/lib";
  
  # Use SPVM module
  use SPVM 'MyMathNative';
  
  # New SPVM int array
  my $sp_nums = SPVM::new_int_array([3, 6, 8, 9]);
  
  # Call SPVM subroutine
  my $total = MyMathNative->sum($sp_nums);
  
  print $total . "\n";

See also L<SPVM::Document::Extension>, L<SPVM::Document::NativeInterface>.

=head1 STANDARD FUNCTIONS

L<SPVM::CORE> - Standard Functions

  print, warn, time

=head1 STANDARD MODULES

L<SPVM::Byte>, L<SPVM::Short>, L<SPVM::Int>, L<SPVM::Long>, L<SPVM::Float>, L<SPVM::Double>, L<SPVM::Bool>

=head1 SPVM Perl API

L<SPVM::Document::ExchangeAPI>

=head1 Native Interface

L<SPVM::Document::NativeInterface>

=head1 Language

L<SPVM::Document::Language>

=head1 NOTE

B<SPVM is before 1.0 under development! I will change implementation and specification without warnings.>

=head1 SUPPORT

If you have problems or find bugs, comment to GitHub Issue.

L<SPVM(GitHub)|https://github.com/yuki-kimoto/SPVM>.

=head1 AUTHOR

Yuki Kimoto E<lt>kimoto.yuki@gmail.com<gt>

=head1 CORE DEVELOPER

moti<lt>motohiko.ave@gmail.com<gt>

=head1 CONTRIBUTERS

akinomyoga, NAGAYASU Shinya, Reini Urban, chromatic, Kazutake Hiramatsu

=head1 COPYRIGHT & LICENSE

MIT License

Copyright (c) [2018] [Yuki Kimoto]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

=cut
