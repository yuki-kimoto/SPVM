package SPVM;

use 5.008007;
use strict;
use warnings;

use DynaLoader;
use File::Basename 'basename', 'dirname';

use SPVM::Perl::Object;
use SPVM::Perl::Object::Array;
use SPVM::Perl::Object::Array::Byte;
use SPVM::Perl::Object::Array::Short;
use SPVM::Perl::Object::Array::Int;
use SPVM::Perl::Object::Array::Long;
use SPVM::Perl::Object::Array::Float;
use SPVM::Perl::Object::Array::Double;
use SPVM::Perl::Object::Array::Object;
use SPVM::Perl::Object::Package;

use SPVM::Build;

use Encode 'encode';

use Carp 'confess';

our $VERSION = '0.0340';

our $COMPILER;
our $API;
our @PACKAGE_INFOS;
our %PACKAGE_INFO_SYMTABLE;
our $BUILD_DIR;
our $INITIALIZED;
our $BUILD;
our @JIT_PACKAGE_NAMES;

require XSLoader;
XSLoader::load('SPVM', $VERSION);

sub import {
  my ($class, $package_name) = @_;
  
  unless ($INITIALIZED) {
    $BUILD = SPVM::Build->new;
    $BUILD_DIR = $ENV{SPVM_BUILD_DIR};
    if (defined $BUILD_DIR) {
      # Remove traling slash
      $BUILD_DIR = File::Spec->catdir(File::Spec->splitdir($BUILD_DIR));
    }
    
    $INITIALIZED = 1;
  }

  # Add package informations
  if (defined $package_name) {
    unless ($SPVM::PACKAGE_INFO_SYMTABLE{$package_name}) {
      my ($file, $line) = (caller)[1, 2];

      my $package_info = {
        name => $package_name,
        file => $file,
        line => $line
      };
      push @SPVM::PACKAGE_INFOS, $package_info;
      
      $SPVM::PACKAGE_INFO_SYMTABLE{$package_name} = 1;
      
      return $package_info;
    }
  }
  
  return;
}

# Compile SPVM source code just after compile-time of Perl
CHECK {
  
  unless ($ENV{SPVM_NO_COMPILE}) {
    my $compile_success = $BUILD->compile_spvm();
    unless ($compile_success) {
      croak("SPVM compile error");
    }
  }
}

sub new_byte_array_len {
  my $length = shift;
  
  my $array = SPVM::Perl::Object::Array::Byte->new_len($length);
  
  return $array;
}

sub new_byte_array {
  my $elements = shift;
  
  return undef unless defined $elements;
  
  if (ref $elements ne 'ARRAY') {
    confess "Argument must be array reference";
  }
  
  my $length = @$elements;
  
  my $array = SPVM::Perl::Object::Array::Byte->new_len($length);
  
  $array->set_elements($elements);
  
  return $array;
}

sub new_short_array {
  my $elements = shift;

  return undef unless defined $elements;

  if (ref $elements ne 'ARRAY') {
    confess "Argument must be array reference";
  }
  
  my $length = @$elements;
  
  my $array = SPVM::Perl::Object::Array::Short->new_len($length);
  
  $array->set_elements($elements);
  
  return $array;
}

sub new_byte_array_bin {
  my $bin = shift;
  
  my $length = length $bin;
  
  my $array = SPVM::Perl::Object::Array::Byte->new_len($length);
  
  $array->set_bin($bin);
  
  return $array;
}


sub new_short_array_len {
  my $length = shift;
  
  my $array = SPVM::Perl::Object::Array::Short->new_len($length);
  
  return $array;
}

sub new_byte_array_string {
  my $string = shift;
  
  # Encode internal string to UTF-8 string
  my $bin = Encode::encode('UTF-8', $string);
  
  my $array = SPVM::new_byte_array_bin($bin);
  
  return $array;
}

sub new_short_array_bin {
  my $bin = shift;
  
  my $byte_length = length $bin;
  
  unless ($byte_length % 2 == 0) {
    confess("bin byte length must be divide by 2(SPVM::new_short_array_bin())");
  }
  
  my $length = int($byte_length / 2);
  
  my $array = SPVM::Perl::Object::Array::Short->new_len($length);
  
  $array->set_bin($bin);
  
  return $array;
}

sub new_int_array_len {
  my $length = shift;
  
  my $array = SPVM::Perl::Object::Array::Int->new_len($length);
  
  return $array;
}

sub new_int_array {
  my $elements = shift;

  return undef unless defined $elements;

  if (ref $elements ne 'ARRAY') {
    confess "Argument must be array reference";
  }
  
  my $length = @$elements;
  
  my $array = SPVM::Perl::Object::Array::Int->new_len($length);
  
  $array->set_elements($elements);
  
  return $array;
}

sub new_int_array_bin {
  my $bin = shift;
  
  my $byte_length = length $bin;
  
  unless ($byte_length % 4 == 0) {
    confess("bin byte length must be divide by 4(SPVM::new_int_array_bin())");
  }
  
  my $length = int($byte_length / 4);
  
  my $array = SPVM::Perl::Object::Array::Int->new_len($length);
  
  $array->set_bin($bin);
  
  return $array;
}

sub new_long_array_len {
  my $length = shift;
  
  my $array = SPVM::Perl::Object::Array::Long->new_len($length);
  
  return $array;
}

sub new_long_array {
  my $elements = shift;

  return undef unless defined $elements;

  if (ref $elements ne 'ARRAY') {
    confess "Argument must be array reference";
  }
  
  my $length = @$elements;
  
  my $array = SPVM::Perl::Object::Array::Long->new_len($length);
  
  $array->set_elements($elements);
  
  return $array;
}

sub new_long_array_bin {
  my $bin = shift;
  
  my $byte_length = length $bin;
  
  unless ($byte_length % 8 == 0) {
    confess("bin byte length must be divide by 8(SPVM::new_long_array_bin())");
  }
  
  my $length = $byte_length / 8;
  
  my $array = SPVM::Perl::Object::Array::Long->new_len($length);
  
  $array->set_bin($bin);
  
  return $array;
}

sub new_float_array_len {
  my $length = shift;
  
  my $array = SPVM::Perl::Object::Array::Float->new_len($length);
  
  return $array;
}

sub new_float_array {
  my $elements = shift;

  return undef unless defined $elements;

  if (ref $elements ne 'ARRAY') {
    confess "Argument must be array reference";
  }
  
  my $length = @$elements;
  
  my $array = SPVM::Perl::Object::Array::Float->new_len($length);
  
  $array->set_elements($elements);
  
  return $array;
}

sub new_float_array_bin {
  my $bin = shift;
  
  my $byte_length = length $bin;
  
  unless ($byte_length % 4 == 0) {
    confess("bin byte length must be divide by 4(SPVM::new_float_array_bin())");
  }
  
  my $length = $byte_length / 4;
  
  my $array = SPVM::Perl::Object::Array::Float->new_len($length);
  
  $array->set_bin($bin);
  
  return $array;
}

sub new_double_array_len {
  my $length = shift;
  
  my $array = SPVM::Perl::Object::Array::Double->new_len($length);
  
  return $array;
}

sub new_double_array {
  my $elements = shift;
  
  return undef unless defined $elements;
  
  if (ref $elements ne 'ARRAY') {
    confess "Argument must be array reference";
  }
  
  my $length = @$elements;
  
  my $array = SPVM::Perl::Object::Array::Double->new_len($length);
  
  $array->set_elements($elements);
  
  return $array;
}

sub new_double_array_bin {
  my $bin = shift;
  
  my $byte_length = length $bin;
  
  unless ($byte_length % 8 == 0) {
    confess("bin byte length must be divide by 8(SPVM::new_double_array_bin())");
  }
  
  my $length = $byte_length / 8;
  
  my $array = SPVM::Perl::Object::Array::Double->new_len($length);
  
  $array->set_bin($bin);
  
  return $array;
}

sub new_object_array_len {
  my ($type_name, $length) = @_;
  
  my $array = SPVM::Perl::Object::Array::Object->new_len($type_name, $length);
  
  return $array;
}

sub new_object {
  my $package_name = shift;
  
  my $object = SPVM::Perl::Object::Package->new($package_name);
  
  return $object;
}

1;

=encoding UTF-8

=head1 NAME

SPVM - Fast array and numeric operation, and provide easy way to C/C++ Binding

B<SPVM is before 1.0 under development! I will change implementation and specification without warnings.>

Curent SPVM version is 0.3 serieses. This means implementation is finshed by 30% of version 1.0.

=head1 SYNOPSIS

  package MyMath {
    sub sum : int ($nums : int[]) {
      
      my $total = 0;
      for (my $i = 0; $i < @$nums; $i++) {
        $total += $nums->[$i];
      }
      
      return $total;
    }
  }

=head1 DESCRIPTION

SPVM provide B<fast array and numeric operation>.

SPVM provide B<easy way to Bind C/C++ Language to Perl>.

=head1 FEATURES

=over 4

=item *

B<Fast array operation>, B<Fast numeric operation>, B<Static typing>, B<Virtual machine>, B<JIT>, B<Pre compile>

=item *

B<Perlish syntax>, B<Easy way to C/C++ binding>, B<C99 math functions>

=back

=head1 EXAMPLES

=head2 How to use SPVM from Perl

SPVM Module:

  # lib/SPVM/MyMath.spvm
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
  my $total = SPVM::MyMath->sum($sp_nums);
  
  print $total . "\n";

See also L<SPVM::Document::PerlAPI>.

=head2 C Extension using SPVM

SPVM Module:

  # lib/SPVM/MyMathNative.spvm
  package MyMathNative {
    
    # Sub Declaration
    native sub sum int ($nums : int[]);
  }

C Source File;

  // lib/SPVM/MyMathNative.inline/MyMathNative.c
  #include <spvm_native.h>

  int32_t SPVM__MyMathNative__sum(SPVM_ENV* env, SPVM_VALUE* args) {
    
    // First argument
    void* sp_nums = args[0].oval;
    
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
  my $total = SPVM::MyMathNative->sum($sp_nums);
  
  print $total . "\n";

See also L<SPVM::Document::Extension>, L<SPVM::Document::NativeAPI>.

=head1 STANDARD FUNCTIONS

L<SPVM::Document::Functions>

print, warn, time

=head1 STANDARD MODULES

L<SPVM::CORE>, L<SPVM::Byte>, L<SPVM::Short>, L<SPVM::Int>, L<SPVM::Long>, L<SPVM::Float>, L<SPVM::Double>, L<SPVM::Bool>,
L<SPVM::Math>, L<SPVM::IO>, L<SPVM::TypeUtil>

=head1 PERL API

L<SPVM::Document::PerlAPI>

=head1 Native API

L<SPVM::Document::NativeAPI>

=head1 Specification

L<SPVM::Document::Specification>

=head1 SUPPORT

If you have problems or find bugs, comment to GitHub Issue.

L<SPVM(GitHub)|https://github.com/yuki-kimoto/SPVM>.

=head1 AUTHOR

Yuki Kimoto E<lt>kimoto.yuki@gmail.com<gt>

=head1 CONTRIBUTERS

=over 4

=item *

L<akinomyoga|https://github.com/akinomyoga> (Koichi Murase)

=item *

L<[NAGAYASU Shinya|https://github.com/nagayasu-shinya>

=item *

L<Reini Urban|https://github.com/rurban>

=item *

L<chromatic|https://github.com/chromatic>

=item *

L<Kazutake Hiramatsu|https://github.com/kazhiramatsu>

=back

=head1 COPYRIGHT AND LICENSE

Copyright (C) 2017-2018 by Yuki Kimoto

MIT License

=cut
