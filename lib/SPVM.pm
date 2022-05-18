package SPVM;

our $VERSION = '0.9516_02';

use 5.008007;
use strict;
use warnings;

use DynaLoader;
use File::Basename 'basename', 'dirname';

use SPVM::BlessedObject;
use SPVM::BlessedObject::Array;
use SPVM::BlessedObject::Class;
use SPVM::BlessedObject::String;
use FindBin;

use SPVM::Builder;
use SPVM::ExchangeAPI;

use Carp 'confess';

# INIT and CHECK block can't be used because SPVM supports dynamic module loading.
# For the reason, this variable is needed.
my $SPVM_INITED;

my $BUILDER;

require XSLoader;
XSLoader::load('SPVM', $VERSION);

my $loaded_spvm_modules = {};

sub import {
  my ($class, $class_name) = @_;
  
  unless (defined $class_name) {
    return;
  }
  
  my ($file, $line) = (caller)[1, 2];

  unless ($BUILDER) {
    my $build_dir = $ENV{SPVM_BUILD_DIR};
    $BUILDER = SPVM::Builder->new(build_dir => $build_dir, include_dirs => [@INC]);
  }

  # Add class informations
  my $build_success;
  if (defined $class_name) {

    my $start_classes_length = $BUILDER->get_classes_length;

    # Compile SPVM source code and create runtime env
    my $compile_success = $BUILDER->compile_spvm($class_name, $file, $line);

    unless ($compile_success) {
      $BUILDER->print_error_messages(*STDERR);
      exit(255);
    }

    # Build runtime information
    $BUILDER->build_runtime;

    # Class names added at this compilation
    my $added_class_names = [];
    my $class_names = $BUILDER->get_class_names;
    for (my $i = $start_classes_length; $i < @$class_names; $i++) {
      my $added_class_name =  $class_names->[$i];
      push @$added_class_names, $added_class_name;
    }
    
    # Bind SPVM method to Perl
    bind_to_perl($BUILDER, $added_class_names);

    # Set addresses of native methods and precompile methods
    for my $added_class_name (@$added_class_names) {
      next if $added_class_name =~ /::anon/;
      
      # Build Precompile classs - Compile C source codes and link them to SPVM precompile method
      $BUILDER->build_and_bind_shared_lib($added_class_name, 'precompile');
      
      # Build native classs - Compile C source codes and link them to SPVM native method
      $BUILDER->build_and_bind_shared_lib($added_class_name, 'native');
    }
  }
}

sub init {
  unless ($SPVM_INITED) {
    if (my $builder = $BUILDER) {
      
      # Prepare runtime environment
      $builder->prepare_env;

      # Set native method addresses
      for my $class_name (keys %{$builder->native_address_info}) {
        my $address_of_methods = $builder->native_address_info->{$class_name};
        for my $method_name (keys %$address_of_methods) {
          my $address = $address_of_methods->{$method_name};
          $builder->set_native_method_address($class_name, $method_name, $address);
        }
      }

      # Set precompile method addresses
      for my $class_name (keys %{$builder->precompile_address_info}) {
        my $address_of_methods = $builder->precompile_address_info->{$class_name};
        for my $method_name (keys %$address_of_methods) {
          my $address = $address_of_methods->{$method_name};
          $builder->set_precompile_method_address($class_name, $method_name, $address);
        }
      }

      # Call INIT blocks
      $builder->call_init_blocks;
    }
    $SPVM_INITED = 1;
  }
}

my $class_name_h = {};
my $binded_class_name_h = {};
sub bind_to_perl {
  my ($builder, $added_class_names) = @_;

  for my $class_name (@$added_class_names) {
    next if $class_name =~ /::anon/;

    my $perl_class_name = "SPVM::$class_name";
    
    unless ($class_name_h->{$class_name}) {
    
      my $code = "package $perl_class_name; our \@ISA = ('SPVM::BlessedObject::Class');";
      eval $code;

      if (my $error = $@) {
        confess $error;
      }
      $class_name_h->{$class_name} = 1;
    }

    my $method_names = $builder->get_method_names($class_name);

    for my $method_name (@$method_names) {
      # Destrutor is skip
      if ($method_name eq 'DESTROY') {
        next;
      }
      # Anon method is skip
      elsif (length $method_name == 0) {
        next;
      }


      my $perl_method_abs_name = "${perl_class_name}::$method_name";

      # Define Perl method
      no strict 'refs';
      *{"$perl_method_abs_name"} = sub {
        SPVM::init() unless $SPVM_INITED;

        my $return_value;
        eval { $return_value = SPVM::call_spvm_method($class_name, $method_name, @_) };
        my $error = $@;
        if ($error) {
          confess $error;
        }
        $return_value;
      };
    }
  }
}

sub new_byte_array {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_byte_array($BUILDER->{env}, @_);
}

sub new_byte_array_unsigned {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_byte_array_unsigned($BUILDER->{env}, @_);
}

sub new_byte_array_len {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_byte_array_len($BUILDER->{env}, @_);
}

sub new_byte_array_from_bin {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_byte_array_from_bin($BUILDER->{env}, @_);
}
sub new_byte_array_from_string {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_byte_array_from_string($BUILDER->{env}, @_);
}

sub new_short_array {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_short_array($BUILDER->{env}, @_);
}

sub new_short_array_unsigned {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_short_array_unsigned($BUILDER->{env}, @_);
}

sub new_short_array_len {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_short_array_len($BUILDER->{env}, @_);
}

sub new_short_array_from_bin {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_short_array_from_bin($BUILDER->{env}, @_);
}
sub new_int_array {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_int_array($BUILDER->{env}, @_);
}

sub new_int_array_unsigned {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_int_array_unsigned($BUILDER->{env}, @_);
}

sub new_int_array_len {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_int_array_len($BUILDER->{env}, @_);
}

sub new_int_array_from_bin {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_int_array_from_bin($BUILDER->{env}, @_);
}
sub new_long_array {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_long_array($BUILDER->{env}, @_);
}

sub new_long_array_unsigned {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_long_array_unsigned($BUILDER->{env}, @_);
}

sub new_long_array_len {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_long_array_len($BUILDER->{env}, @_);
}

sub new_long_array_from_bin {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_long_array_from_bin($BUILDER->{env}, @_);
}
sub new_float_array {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_float_array($BUILDER->{env}, @_);
}
sub new_float_array_len {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_float_array_len($BUILDER->{env}, @_);
}

sub new_float_array_from_bin {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_float_array_from_bin($BUILDER->{env}, @_);
}
sub new_double_array {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_double_array($BUILDER->{env}, @_);
}

sub new_double_array_len {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_double_array_len($BUILDER->{env}, @_);
}

sub new_double_array_from_bin {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_double_array_from_bin($BUILDER->{env}, @_);
}
sub new_string {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_string($BUILDER->{env}, @_);
}

sub new_string_from_bin {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_string_from_bin($BUILDER->{env}, @_);
}

sub new_object_array {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_object_array($BUILDER->{env}, @_);
}

sub new_mulnum_array {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_mulnum_array($BUILDER->{env}, @_);
}

sub new_mulnum_array_from_bin {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_mulnum_array_from_bin($BUILDER->{env}, @_);
}

sub new_string_array {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::new_string_array($BUILDER->{env}, @_);
}

sub get_exception {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::get_exception($BUILDER->{env}, @_);
}

sub set_exception {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::set_exception($BUILDER->{env}, @_);
}

sub get_memory_blocks_count {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::get_memory_blocks_count($BUILDER->{env}, @_);
}

sub call_spvm_method {
  SPVM::init() unless $SPVM_INITED;
  SPVM::ExchangeAPI::call_spvm_method($BUILDER->{env}, @_);
}

1;

=encoding utf8

=head1 NAME

SPVM - SPVM Language

=head1 CAUTHION

B<C<SPVM> is not yet 1.0 release. C<SPVM> is quit often changed without warnings until I feel the implementation is enough good.>

=head1 SYNOPSIS

Write a SPVM Module:

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

Call the SPVM method from Perl:

  # sum.pl
  use strict;
  use warnings;
  use FindBin;
  use lib "$FindBin::Bin/lib";

  use SPVM 'MyMath';

  # Call method
  my $total = SPVM::MyMath->sum([3, 6, 8, 9]);

  print "$total\n";

=head1 DESCRIPTION

B<SPVM>(Static Perl Virtual Machine) is a perl-ish static typed programing language. SPVM provides fast calculation, fast array operations, easy C/C++ binding, and creating executable files.

=head1 DOCUMENT

SPVM documents.

=head2 Tutorial

SPVM Tutorial.

=over 2

=item * L<Tutorial|SPVM::Document::Tutorial>

=back

=head2 Language Specification

SPVM Language Specification.

=over 2

=item * L<Language Specification|SPVM::Document::LanguageSpecification>

=back

=head2 Standard Modules

SPVM Standard Modules.

=over 2

=item * L<Standard Modules|SPVM::Document::Modules>

=back

=head2 Exchange APIs

SPVM Exchange APIs is functions to convert between Perl data structures and SPVM data structures.

=over 2

=item * L<ExchangeAPI|SPVM::Document::ExchangeAPI>

=back

=head2 Native Method

Native methods are the methods that implementations are writen by native language such as C<C language> or C<C++>.

=over 2

=item * L<Native Method|SPVM::Document::NativeMethod>

=back

=head2 Native APIs

SPVM native APIs are public APIs that are used in native language sources such as C<C language> or C<C++>.

=over 2

=item * L<Native APIs|SPVM::Document::NativeAPI>

=back

=head2 Creating Executable File

C<spvmcc> is the compiler and linker to create the executable file from SPVM source codes.

=over 2

=item * L<spvmcc>

=back

=head2 Creating SPVM Modules

C<spvmgenlib> is the command to create SPVM native modules.

=over 2

=item * L<spvmgenlib>

=back

=head2 Benchmark

SPVM performance benchmarks.

=over 2

=item * L<Benchmark|SPVM::Document::Benchmark>

=back

=head1 ENVIRONMENT VARIABLES

=head2 SPVM_BUILD_DIR

SPVM building directory to build C<precompile> and C<native> methods. If the C<SPVM_BUILD_DIR> environment variable is not set, the building of C<precompile> and C<native> methods fails.

B<bash:>

  export SPVM_BUILD_DIR=~/.spvm_build

B<csh:>

  setenv SPVM_BUILD_DIR ~/.spvm_build

=head2 SPVM_CC_DEBUG

Print debug messages of L<SPVM::Builder::CC> to stderr.

=head2 SPVM_CC_FORCE

Force the compilation and the link of L<SPVM::Builder::CC>.

=head1 REPOSITORY

L<Github|https://github.com/yuki-kimoto/SPVM>

=head1 BUG REPORT

L<GitHub Issue|https://github.com/yuki-kimoto/SPVM/issues>

=head1 SUPPORT

L<Github Discussions|https://github.com/yuki-kimoto/SPVM/discussions>

=head1 AUTHOR

Yuki Kimoto E<lt>kimoto.yuki@gmail.comE<gt>

=head1 CORE DEVELOPERS

motiE<lt>motohiko.ave@gmail.comE<gt>

=head1 CONTRIBUTORS

=over 2

=item * Mohammad S Anwar

=item * akinomyoga

=item * NAGAYASU Shinya

=item * Reini Urban

=item * chromatic

=item * Kazutake Hiramatsu

=item * Yasuaki Omokawa

=item * Suman Khanal

=back

=head1 COPYRIGHT & LICENSE

Copyright 2018-2022 Yuki Kimoto, all rights reserved.

This program is free software; you can redistribute it and/or modify it
under the same terms as Perl itself.

=cut
