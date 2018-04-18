package SPVM;

use 5.008007;
use strict;
use warnings;

use Config;
use DynaLoader;
use File::Basename 'basename', 'dirname';
use File::Temp ();

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
use SPVM::Perl::Object::Package::String;

use SPVM::Build::ExtUtil;
use SPVM::Build::JIT;
use SPVM::Build::Inline;

use Encode 'encode';

use Carp 'confess';

our $VERSION = '0.0325';

our $COMPILER;
our $API;
our @PACKAGE_INFOS;
our %PACKAGE_INFO_SYMTABLE;
our $SPVM_BUILD;

require XSLoader;
XSLoader::load('SPVM', $VERSION);

$SPVM_BUILD = SPVM::Build::ExtUtil->new;

sub import {
  my ($class, $package_name) = @_;
  
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

sub get_shared_lib_file {
  my $package_name = shift;
  
  my $package_name2 = $package_name;
  $package_name2 =~ s/SPVM:://;
  my @package_name_parts = split(/::/, $package_name2);
  my $package_load_path = get_package_load_path($package_name2);
  my $dll_file = $package_load_path;
  $dll_file =~ s/\.[^.]+$//;
  $dll_file .= ".native/$package_name_parts[-1].$Config{dlext}";
  
  return $dll_file;
}

sub bind_native_subs {
  my $native_func_names = get_native_sub_names();
  for my $native_func_name (@$native_func_names) {
    my $native_func_name_spvm = "SPVM::$native_func_name";
    my $native_address = get_sub_native_address($native_func_name_spvm);
    unless ($native_address) {
      my $native_func_name_c = $native_func_name_spvm;
      $native_func_name_c =~ s/:/_/g;
      confess "Can't find native address of $native_func_name_spvm(). Native function name must be $native_func_name_c";
    }
    bind_native_sub($native_func_name, $native_address);
  }
}

sub get_sub_native_address {
  my $sub_abs_name = shift;
  
  my $package_name;
  my $sub_name;
  if ($sub_abs_name =~ /^(?:(.+)::)(.+)$/) {
    $package_name = $1;
    $sub_name = $2;
  }
  
  my $dll_package_name = $package_name;
  my $shared_lib_file = get_shared_lib_file($dll_package_name);
  
  my $shared_lib_func_name = $sub_abs_name;
  $shared_lib_func_name =~ s/:/_/g;
  my $native_address = search_shared_lib_func_address($shared_lib_file, $shared_lib_func_name);
  
  # Try inline compile
  unless ($native_address) {
    
    my $module_name = $package_name;
    $module_name =~ s/^SPVM:://;
    my $module_dir = get_package_load_path($module_name);
    $module_dir =~ s/\.spvm$//;
    
    my $module_name_slash = $package_name;
    $module_name_slash =~ s/::/\//g;
    
    $module_dir =~ s/$module_name_slash$//;
    $module_dir =~ s/\/$//;
    
    my $shared_lib_file;
    
    my $tmp_dir = File::Temp->newdir;
    eval {
      $shared_lib_file = $SPVM::SPVM_BUILD->build_shared_lib(
        module_dir => $module_dir,
        module_name => "SPVM::$module_name",
        object_dir => $tmp_dir->dirname,
        inline => 1
      );
    };
    
    if ($@) {
      return;
    }
    else {
      $native_address = search_shared_lib_func_address($shared_lib_file, $shared_lib_func_name);
    }
  }
  
  return $native_address;
}

sub search_shared_lib_func_address {
  my ($shared_lib_file, $shared_lib_func_name) = @_;
  
  my $native_address;
  
  if ($shared_lib_file) {
    my $dll_libref = DynaLoader::dl_load_file($shared_lib_file);
    if ($dll_libref) {
      $native_address = DynaLoader::dl_find_symbol($dll_libref, $shared_lib_func_name);
    }
    else {
      return;
    }
  }
  else {
    return;
  }
  
  return $native_address;
}


# Compile SPVM source code just after compile-time of Perl
CHECK {
  unless ($ENV{SPVM_NO_COMPILE}) {
    my $compile_success = compile_spvm();
    unless ($compile_success) {
      croak("SPVM compile error");
    }
  }
}

sub compile_spvm {
  
  # Compile SPVM source code
  my $compile_success = compile();
  
  if ($compile_success) {
    # Build opcode
    build_opcode();
    
    # Build run-time
    build_runtime();
    
    # Bind native subroutines
    bind_native_subs();
    
    # Build SPVM subroutines
    build_spvm_subs();
  }
  
  return $compile_success;
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

sub new_byte_array_data {
  my $data = shift;
  
  my $length = length $data;
  
  my $array = SPVM::Perl::Object::Array::Byte->new_len($length);
  
  $array->set_data($data);
  
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
  my $data = Encode::encode('UTF-8', $string);
  
  my $array = SPVM::new_byte_array_data($data);
  
  return $array;
}

sub new_short_array_data {
  my $data = shift;
  
  my $byte_length = length $data;
  
  unless ($byte_length % 2 == 0) {
    confess("data byte length must be divide by 2(SPVM::new_short_array_data())");
  }
  
  my $length = int($byte_length / 2);
  
  my $array = SPVM::Perl::Object::Array::Short->new_len($length);
  
  $array->set_data($data);
  
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

sub new_int_array_data {
  my $data = shift;
  
  my $byte_length = length $data;
  
  unless ($byte_length % 4 == 0) {
    confess("data byte length must be divide by 4(SPVM::new_int_array_data())");
  }
  
  my $length = int($byte_length / 4);
  
  my $array = SPVM::Perl::Object::Array::Int->new_len($length);
  
  $array->set_data($data);
  
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

sub new_long_array_data {
  my $data = shift;
  
  my $byte_length = length $data;
  
  unless ($byte_length % 8 == 0) {
    confess("data byte length must be divide by 8(SPVM::new_long_array_data())");
  }
  
  my $length = $byte_length / 8;
  
  my $array = SPVM::Perl::Object::Array::Long->new_len($length);
  
  $array->set_data($data);
  
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

sub new_float_array_data {
  my $data = shift;
  
  my $byte_length = length $data;
  
  unless ($byte_length % 4 == 0) {
    confess("data byte length must be divide by 4(SPVM::new_float_array_data())");
  }
  
  my $length = $byte_length / 4;
  
  my $array = SPVM::Perl::Object::Array::Float->new_len($length);
  
  $array->set_data($data);
  
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

sub new_double_array_data {
  my $data = shift;
  
  my $byte_length = length $data;
  
  unless ($byte_length % 8 == 0) {
    confess("data byte length must be divide by 8(SPVM::new_double_array_data())");
  }
  
  my $length = $byte_length / 8;
  
  my $array = SPVM::Perl::Object::Array::Double->new_len($length);
  
  $array->set_data($data);
  
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

my $package_name_h = {};

sub build_spvm_subs {
  my $sub_names = get_sub_names();
  
  for my $abs_name (@$sub_names) {
    # Define SPVM subroutine
    no strict 'refs';
    
    # Declare package
    my ($package_name, $sub_name) = $abs_name =~ /^(?:(.+)::)(.+)/;
    $package_name = "SPVM::$package_name";
    unless ($package_name_h->{$package_name}) {
      
      my $code = "package $package_name; our \@ISA = ('SPVM::Perl::Object::Package');";
      eval $code;
      
      if (my $error = $@) {
        confess $error;
      }
      $package_name_h->{$package_name} = 1;
    }
    
    # Declare subroutine
    *{"SPVM::$abs_name"} = sub {
      
      my $return_value;
      eval { $return_value = SPVM::call_sub("$abs_name", @_) };
      my $error = $@;
      if ($error) {
        confess $error;
      }
      $return_value;
    };
  }
}

1;

=encoding UTF-8

=head1 NAME

SPVM - Fast Calculation and Easy C/C++ Binding with perlish syntax and static typing

B<SPVM is before 1.0 under development! I will change implementation and specification without warnings.>

=head1 SYNOPSIS

=head2 Fast Array Operation using SPVM.

SPVM Module:

  # lib/SPVM/MyMath.spvm
  package MyMath {
    # Standard functions
    use Std;
    
    # Sub Declaration
    sub sum : int ($nums : int[]) {
      
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
  my $total = SPVM::MyMath->sum($sp_nums);
  
  print $total . "\n";

If you know more SPVM syntax, see L<SPVM::Document::Specification>.

If you know more Functions to convert Perl Data to SPVM Data, see L<SPVM::Document::DataConversionAPI>.

=head2 C Extension using SPVM

SPVM Module:

  # lib/SPVM/MyMathNative.spvm
  package MyMathNative {
    
    # Sub Declaration
    native sub sum int ($nums : int[]);
  }

C Source File;

  // lib/SPVM/MyMathNative.inline/MyMathNative.c
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
  my $total = SPVM::MyMathNative->sum($sp_nums);
  
  print $total . "\n";

If you know more SPVM Extension, see L<SPVM::Document::Extension>.

If you know the APIs to manipulate SPVM data, see L<SPVM::Document::NativeAPI>.

=head1 DESCRIPTION

SPVM provide Fast Culcuration and Easy way to Bind C/C++ Language to Perl.

=over 4

=item *

B<Fast calculation> - The Perl's biggest weak point is the calculation performance. SPVM provides fast calculations.

=item *

B<GC> - You don't need to care about freeing memory

=item *

B<Static typing> - Static typing for performance

=item *

B<VM> - Byte codes are generated so that you can run them on SPVM language

=item *

B<Perlish syntax> - SPVM syntax is very similar to Perl

=item *

B<Perl module> - SPVM function can be called from Perl itself.

=back

=head1 SPVM Tutorial

L<SPVM> is a language which is similar with Perl. SPVM is very similar to Perl, and you can write same syntax of Perl in most part.

L<SPVM> communicate with Perl. You can call SPVM function directory from Perl.

L<SPVM> is very fast and provide array data structure. Now SPVM array operation is about 6x faster.

=head2 SPVM module

At first, you can write SPVM module. 

  # lib/SPVM/MyModule1.spvm
  package MyModule1 {
    has x : int;
    has y : int;

    sub sum : int ($x : int, $y : int) {

      my $total = $x + $y;

      return $total;
    }
  }

This is same as Perl except SPVM have static type and C<has> keyword.

You can define field by C<has> keyword, and specify static type by C<: type>.

  has x : int;

You can specify argument types and return type to subroutine by C<: type>.

  sub sum : int ($x : int, $y : int) {

    my $total = $x + $y;

    return $total;
  }

Let's save this file by the following name

  lib/SPVM/MyModule1.spvm

If package name is C<MyModule1>, file name must be C<SPVM/MyModule1.spvm>.

Extension is C<spvm>. And you create C<SPVM> directory.

C<lib> is normal directory.

=head2 Call SPVM subroutine

Next you can use SPVM subroutine from Perl.

  use FindBin;
  use lib "$FindBin::Bin/lib";

  use SPVM 'MyModule1';

  my $total = SPVM::MyModule1::sum(3, 5);
  print $total . "\n";

At first, you add library path by L<FindBin> and L<lib> module.

  use FindBin;
  use lib "$FindBin::Bin/lib";

Next, use SPVM module. C<MyModule1> is loaded.

  use SPVM 'MyModule1';

And call SPVM subroutine. If SPVM subroutine absolute name is C<MyModule1::sum>, you can call this subroutine by C<SPVM::MyModule1::sum>.

  my $total = SPVM::MyModule1::sum(3, 5);
  print $total . "\n";

=head1 Document

=head2 SPVM Functions

L<SPVM::Document::DataConversionAPI> - SPVM data convertion functions.

List of SPVM functions:

=over 2

=item * new_byte_array

=item * new_byte_array_data

=item * new_byte_array_string

=item * new_short_array

=item * new_int_array

=item * new_long_array

=item * new_float_array

=item * new_double_array

=item * new_object_array_len

=item * new_object

=back

If you know Detail of SPVM Function, see L<SPVM::Document::DataConversionAPI>.

=head2 SPVM Specification

L<SPVM::Document::Specification> - SPVM Specification

=head2 SPVM Native Interface

L<SPVM::Document::NativeAPI> - SPVM Native Interface.

Native API is C level API. You can write programing logic using C language and SPVM Native API.

=head2 SPVM Standard Function

L<SPVM::Document::Functions> - SPVM Standard Functions

=head2 SPVM Standard Module

L<SPVM::Document::Modules> - SPVM Standard Modules

=head2 SPVM FAQ

L<SPVM::Document::FAQ> - Oftten asked question.

=head2 SUPPORT

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
