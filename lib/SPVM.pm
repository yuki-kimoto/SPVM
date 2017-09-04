package SPVM;

use 5.008007;
use strict;
use warnings;

use Config;

use SPVM::BaseObject;
use SPVM::Object;
use SPVM::Array;
use SPVM::Array::Byte;
use SPVM::Array::Short;
use SPVM::Array::Int;
use SPVM::Array::Long;
use SPVM::Array::Float;
use SPVM::Array::Double;
use SPVM::String;
use SPVM::Array::Object;
use File::Temp 'tempdir';
use ExtUtils::CBuilder;


use Encode 'encode';

use Carp 'confess';

our $VERSION = '0.0254';

our $COMPILER;
our @PACKAGE_INFOS;
our %PACKAGE_INFO_SYMTABLE;
our $API;
our $INLINE_DLL_FILE;

our @PACKAGE_INFOS_INLINE;

sub import {
  my ($class, $package_name) = @_;
  
  # Add package infomations
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
  
  return undef;
}

sub _get_dll_file {
  my $package_name = shift;
  
  # DLL file name
  my $dlext = $Config{dlext};
  my $dll_base_name = $package_name;
  $dll_base_name =~ s/^.*:://;
  my $dll_file_tail = 'auto/' . $package_name . '/' . $dll_base_name;
  $dll_file_tail =~ s/::/\//g;
  my $dll_file;
  for my $dl_shared_object (@DynaLoader::dl_shared_objects) {
    my $dl_shared_object_no_ext = $dl_shared_object . '.ppp';
    # remove .so, xs.dll .dll, etc
    while ($dl_shared_object_no_ext =~ s/\.[^\/\.]+$//) {
      1;
    }
    if ($dl_shared_object_no_ext =~ /\Q$dll_file_tail\E$/) {
      $dll_file = $dl_shared_object;
      last;
    }
  }
  
  return $dll_file;
}

sub search_native_address {
  my ($dll_file, $sub_abs_name) = @_;
  
  my $native_address;
  
  if ($dll_file) {
    my $dll_libref = DynaLoader::dl_load_file($dll_file);
    if ($dll_libref) {
      my $sub_abs_name_c = $sub_abs_name;
      $sub_abs_name_c =~ s/:/_/g;
      $native_address = DynaLoader::dl_find_symbol($dll_libref, $sub_abs_name_c);
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

sub get_sub_native_address {
  my $sub_abs_name = shift;
  
  my $native_address;
  
  my $package_name;
  my $sub_name;
  if ($sub_abs_name =~ /^(?:(.+)::)(.+)$/) {
    $package_name = $1;
    $sub_name = $2;
  }
  
  my $dll_file;
  my $dll_package_name = $package_name;
  while (1) {
    $dll_file = _get_dll_file($dll_package_name);
    $native_address = search_native_address($dll_file, $sub_abs_name);
    
    if ($native_address) {
      last;
    }
    else {
      if ($dll_package_name =~ /::/) {
        $dll_package_name =~ s/::[^:]+$//;
      }
      else {
        last;
      }
    }
  }
  
  # Search inline dll
  unless ($native_address) {
    my $dll_file = $INLINE_DLL_FILE;
    $native_address = search_native_address($dll_file, $sub_abs_name);
  }
  
  return $native_address;
}

sub bind_native_subs {
  my $native_sub_names = get_native_sub_names();
  for my $native_sub_name (@$native_sub_names) {
    my $native_sub_name_spvm = "SPVM::$native_sub_name";
    my $native_address = get_sub_native_address($native_sub_name_spvm);
    unless ($native_address) {
      confess "Can't find native address($native_sub_name())";
    }
    bind_native_sub($native_sub_name, $native_address);
  }
}

sub compile_inline_native_subs {
  
  my $temp_dir = tempdir;
  my $native_src_file = "$temp_dir/inline_native.c";
  open my $native_src_fh, '>>', $native_src_file
    or die "Can't open $native_src_file:$!";
    
  # my $inline_files = get_inline_files();
  
  for my $package_info (@SPVM::PACKAGE_INFOS_INLINE) {
    
    my $src = "$temp_dir/inline_native.c";
    
    my $package_name = $package_info->{name};
    
    my $spvm_file = get_use_package_path($package_name);
    
    open my $spvm_fh, '<', $spvm_file
      or confess "Can't open $spvm_file: $!";
    
    my $spvm_content = do { local $/; <$spvm_fh> };
    
    my $native_src;
    if ($spvm_content =~ /__NATIVE__(.*)$/sm) {
      $native_src = $1;
    }
    
    print $native_src_fh "$native_src\n";
  }
  close $native_src_fh;
  
  my $api_header_include_dir = $INC{"SPVM.pm"};
  $api_header_include_dir =~ s/\.pm$//;
  
  my $cbuilder = ExtUtils::CBuilder->new;
  my $obj_file = $cbuilder->compile(
    source => $native_src_file,
    include_dirs => [$api_header_include_dir]
  );
  my $lib_file = $cbuilder->link(objects => $obj_file);
  
  $INLINE_DLL_FILE = $lib_file;
}

# Compile SPVM source code just after compile-time of Perl
CHECK {
  require XSLoader;
  XSLoader::load('SPVM', $VERSION);
  
  # Compile SPVM source code
  compile();
  
  # Build run-time
  build_runtime();
  
  # Free compiler
  free_compiler();
  
  # Compile inline native subroutine
  compile_inline_native_subs();
  
  # Bind native subroutines
  bind_native_subs();
  
  # Build SPVM subroutine
  build_spvm_subs();
}

sub new_string_raw {
  my $string = shift;
  
  my $array = SPVM::String->new_raw($string);
  
  return $array;
}

sub new_string {
  my $string = shift;
  
  $string = Encode::encode('UTF-8', $string);
  
  my $array = SPVM::String->new_raw($string);
  
  return $array;
}

sub new_byte_array {
  my $elements = shift;
  
  if (ref $elements ne 'ARRAY') {
    confess "Argument must be array reference";
  }
  
  my $length = @$elements;
  
  my $array = SPVM::Array::Byte->new($length);
  
  $array->set_elements($elements);
  
  return $array;
}

sub new_byte_array_len {
  my $length = shift;
  
  my $array = SPVM::Array::Byte->new($length);
  
  return $array;
}

sub new_short_array {
  my $elements = shift;
  
  if (ref $elements ne 'ARRAY') {
    confess "Argument must be array reference";
  }
  
  my $length = @$elements;
  
  my $array = SPVM::Array::Short->new($length);
  
  $array->set_elements($elements);
  
  return $array;
}

sub new_short_array_len {
  my $length = shift;
  
  my $array = SPVM::Array::Short->new($length);
  
  return $array;
}

sub new_int_array {
  my $elements = shift;
  
  if (ref $elements ne 'ARRAY') {
    confess "Argument must be array reference";
  }
  
  my $length = @$elements;
  
  my $array = SPVM::Array::Int->new($length);
  
  $array->set_elements($elements);
  
  return $array;
}

sub new_int_array_len {
  my $length = shift;
  
  my $array = SPVM::Array::Int->new($length);
  
  return $array;
}

sub new_long_array {
  my $elements = shift;
  
  if (ref $elements ne 'ARRAY') {
    confess "Argument must be array reference";
  }
  
  my $length = @$elements;
  
  my $array = SPVM::Array::Long->new($length);
  
  $array->set_elements($elements);
  
  return $array;
}

sub new_long_array_len {
  my $length = shift;
  
  my $array = SPVM::Array::Long->new($length);
  
  return $array;
}

sub new_float_array {
  my $elements = shift;
  
  if (ref $elements ne 'ARRAY') {
    confess "Argument must be array reference";
  }
  
  my $length = @$elements;
  
  my $array = SPVM::Array::Float->new($length);
  
  $array->set_elements($elements);
  
  return $array;
}

sub new_float_array_len {
  my $length = shift;
  
  my $array = SPVM::Array::Float->new($length);
  
  return $array;
}

sub new_double_array {
  my $elements = shift;
  
  if (ref $elements ne 'ARRAY') {
    confess "Argument must be array reference";
  }
  
  my $length = @$elements;
  
  my $array = SPVM::Array::Double->new($length);
  
  $array->set_elements($elements);
  
  return $array;
}

sub new_double_array_len {
  my $length = shift;
  
  my $array = SPVM::Array::Double->new($length);
  
  return $array;
}

sub new_object_array_len {
  my ($type_name, $length) = @_;
  
  my $array = SPVM::Array::Object->new($type_name, $length);
  
  return $array;
}

sub new_object {
  my $package_name = shift;
  
  my $object = SPVM::Object->new_object($package_name);
  
  return $object;
}

sub build_spvm_subs {
  my $sub_names = get_sub_names();
  
  for my $abs_name (@$sub_names) {
    # Define SPVM subroutine
    no strict 'refs';
    *{"SPVM::$abs_name"} = sub {
      my $return_value;
      eval { $return_value = SPVM::call_sub("$abs_name", @_) };
      my $error = $@;
      if ($error) {
        $error = Encode::decode('UTF-8', $error);
        confess $error;
      }
      $return_value;
    };
  }
}

# Preloaded methods go here.

1;
__END__
=encoding UTF-8

=head1 NAME

SPVM - Fast calculation, GC, static typing, VM with perlish syntax

B<SPVM is under development! I will change implementation and specification without warnings.>

=head1 SYNOPSIS

  use FindBin;
  use lib "$FindBin::Bin/lib";

  use SPVM 'MyModule2';

  my $total = SPVM::MyModule2::foo(3, 5);
  print $total . "\n";

Module file

  # lib/SPVM/MyModule1.spvm
  package MyModule1 {
    has x : int;
    has y : int;

    sub sum ($a : int, $b : int) : int {

      my $total = $a + $b;

      return $total;
    }
  }

  # lib/SPVM/MyModule2.spvm
  use MyModule1;
  package MyModule2 {

    sub foo ($a : int, $b : int) : int {

      my $total = ($a * $b) + MyModule1::sum(2, 4);

      return $total;
    }
  }

If you want to know more syntax, see C<solo/SPVM/Test.spvm>.

If you want to know SPVM language, see C<solo/README.md>

=head1 DESCRIPTION

Do you need B<faster Perl>? SPVM provides fast calculation to Perl.

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

SPVM only work on the Perl which support 64 bit integer.

=head1 DOCUMENT

=over 2

=item 1

L<SPVM::Document::Tutorial> - SPVM Tutorial

=item 2

L<SPVM::Document::PerlAPI> - API to exchange Perl value to SPVM value.

=item 3

L<SPVM::Document::Spec> - SPVM Specification

=item 4

L<SPVM::Document::FAQ> - SPVM Specification

=back

=head1 DON'T PANIC!

We are constantly working on new documentation. Follow us on
L<GitHub|https://github.com/yuki-kimoto/SPVM> or join the official IRC channel C<#perl11>
on C<irc.perl.org> to get all the latest updates.

=head2 SUPPORT

If you have any questions the documentation might not yet answer, don't
hesitate to ask on the the official IRC
channel C<#perl11> on C<irc.perl.org>
(L<chat now!|https://chat.mibbit.com/?channel=%23perl11&server=irc.perl.org>).

You can see #perl11 log.

L<http://irclog.perlgeek.de/perl11/>

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

Copyright (C) 2017 by Yuki Kimoto

This library is free software; you can redistribute it and/or modify
it under the same terms as Perl itself, either Perl version 5.16.3 or,
at your option, any later version of Perl 5 you may have available.

=cut
