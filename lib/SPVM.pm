package SPVM;

use 5.008007;
use strict;
use warnings;

use DynaLoader;
use File::Basename 'basename', 'dirname';

use SPVM::Data;
use SPVM::Data::Array;

use SPVM::Build;

use Encode 'encode';

use Carp 'confess';

our $VERSION = '0.0362';

our $ENV;
our $BUILD;

require XSLoader;
XSLoader::load('SPVM', $VERSION);

sub import {
  my ($class, $package_name) = @_;
  
  unless ($BUILD) {
    my $build_dir = $ENV{SPVM_BUILD_DIR};
    if (defined $build_dir) {
      # Remove traling slash
      $build_dir = File::Spec->catdir(File::Spec->splitdir($build_dir));
    }
    $BUILD = SPVM::Build->new(build_dir => $build_dir);
  }

  # Add package informations
  if (defined $package_name) {
    my ($file, $line) = (caller)[1, 2];
    my $package_info = {
      name => $package_name,
      file => $file,
      line => $line
    };
    push @{$BUILD->{package_infos}}, $package_info;
  }
}

# Compile SPVM source code just after compile-time of Perl
CHECK {
  if ($BUILD) {
    my $compile_success = $BUILD->build_spvm();
    unless ($compile_success) {
      die "SPVM compile error";
    }
  }
}

sub new_byte_array {
  my $elements = shift;
  
  return undef unless defined $elements;
  
  if (ref $elements ne 'ARRAY') {
    confess "Argument must be array reference";
  }
  
  my $length = @$elements;
  
  my $array = SPVM::new_byte_array_len($length);
  
  $array->set_elements($elements);
  
  return $array;
}

sub new_byte_array_string {
  my $string = shift;
  
  # Encode internal string to UTF-8 string
  my $bin = Encode::encode('UTF-8', $string);
  
  my $length = length $bin;
  
  my $array = SPVM::new_byte_array_len($length);
  $array->set_bin($bin);
  
  return $array;
}

sub new_short_array {
  my $elements = shift;

  return undef unless defined $elements;

  if (ref $elements ne 'ARRAY') {
    confess "Argument must be array reference";
  }
  
  my $length = @$elements;
  
  my $array = SPVM::new_short_array_len($length);
  
  $array->set_elements($elements);
  
  return $array;
}

sub new_int_array {
  my $elements = shift;

  return undef unless defined $elements;

  if (ref $elements ne 'ARRAY') {
    confess "Argument must be array reference";
  }
  
  my $length = @$elements;
  
  my $array = SPVM::new_int_array_len($length);
  
  $array->set_elements($elements);
  
  return $array;
}

sub new_long_array {
  my $elements = shift;

  return undef unless defined $elements;

  if (ref $elements ne 'ARRAY') {
    confess "Argument must be array reference";
  }
  
  my $length = @$elements;
  
  my $array = SPVM::new_long_array_len($length);
  
  $array->set_elements($elements);
  
  return $array;
}

sub new_float_array {
  my $elements = shift;

  return undef unless defined $elements;

  if (ref $elements ne 'ARRAY') {
    confess "Argument must be array reference";
  }
  
  my $length = @$elements;
  
  my $array = SPVM::new_float_array_len($length);
  
  $array->set_elements($elements);
  
  return $array;
}

sub new_double_array {
  my $elements = shift;
  
  return undef unless defined $elements;
  
  if (ref $elements ne 'ARRAY') {
    confess "Argument must be array reference";
  }
  
  my $length = @$elements;
  
  my $array = SPVM::new_double_array_len($length);
  
  $array->set_elements($elements);
  
  return $array;
}

sub new_object_array {
  my ($package_name, $elements) = @_;
  
  return undef unless defined $elements;
  
  if (ref $elements ne 'ARRAY') {
    confess "Argument must be array reference";
  }
  
  my $length = @$elements;
  
  my $array = SPVM::new_object_array_len($package_name, $length);
  
  $array->set_elements($elements);
  
  return $array;
}

sub new_value_t_array {
  my ($package_name, $elements) = @_;
  
  return undef unless defined $elements;
  
  if (ref $elements ne 'ARRAY') {
    confess "Argument must be array reference";
  }
  
  my $length = @$elements;
  
  my $array = SPVM::new_value_t_array_len($package_name, $length);

  $array->set_elements($elements);
  
  return $array;
}

sub new_object {
  my $package_name = shift;
  
  my $object = SPVM::Data::Package->new($package_name);
  
  return $object;
}

1;

=encoding UTF-8

=head1 NAME

SPVM - Fast array and numeric operation, and provide easy way to C/C++ Binding

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

B<Fast array operation>, B<Fast numeric operation>, B<Static typing>, B<Virtual machine>, B<Precompile>, B<Pre compile>

=item *

B<Perlish syntax>, B<Easy way to C/C++ binding>, B<C99 math functions>

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

See also L<SPVM::Document::PerlAPI>.

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

L<SPVM::Document::Functions>

print, warn, time

=head1 STANDARD MODULES

L<SPVM::CORE>, L<SPVM::Byte>, L<SPVM::Short>, L<SPVM::Int>, L<SPVM::Long>, L<SPVM::Float>, L<SPVM::Double>, L<SPVM::Bool>

=head1 SPVM Perl API

L<SPVM::Document::PerlAPI>

=head1 Native Interface

L<SPVM::Document::NativeInterface>

=head1 Language

L<SPVM::Document::Language>

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

=head1 NOTE

B<SPVM is before 1.0 under development! I will change implementation and specification without warnings.>

Curent SPVM version is 0.3 serieses. This means implementation is finshed by 30% of version 1.0.

=head1 COPYRIGHT & LICENSE

Copyright 2017-2018 Yuki Kimoto, all rights reserved.

This program is free software; you can redistribute it and/or modify it
under the same terms as Perl itself.

=cut
