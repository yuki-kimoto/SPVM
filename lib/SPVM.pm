use 5.008007;
package SPVM;
use strict;
use warnings;

use SPVM::Global;

our $VERSION = "0.989070";

require XSLoader;
XSLoader::load('SPVM', $VERSION);

sub import {
  my ($class, $class_name) = @_;
  
  my ($file, $line) = (caller)[1, 2];
  
  if (defined $class_name) {
    SPVM::Global::build_class($class_name, $file, $line);
  }
}

sub api { SPVM::Global::api() }

1;

=encoding utf8

=head1 Name

SPVM - SPVM Language

=head1 Description

SPVM is a statically typed programming language that has Perl-like syntax.

SPVM has not yet reached a stable release of version 1.0. For now, there is currently no policy to keep the L<backward compatibility|https://github.com/yuki-kimoto/SPVM/wiki/Backward-Compatibility>.

=head1 Usage

A class of SPVM:

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

Calling a SPVM method from Perl:

  # sum.pl
  use FindBin;
  use lib "$FindBin::Bin/lib";
  
  use SPVM 'MyMath';
  
  # Call method
  my $total = SPVM::MyMath->sum([3, 6, 8, 9]);

=head1 Features

=over2 

=item * L<Native threads|SPVM::Thread> and L<goroutines|SPVM::Go>.

=item * L<Generating an executable file|spvmcc>

=item * AOT(Ahead-of-time compilation) and JIT(Just-in-time compilation).

=item * Static types, type inference and L<static analysis|SPVM::Native::Compiler>.

=item * L<C/C++ binding|SPVM::Document::NativeClass> and L<resource system|SPVM::Document::Resource> for C/C++ libraries.

=item * L<Perl binding for SPVM methods|SPVM::ExchangeAPI>.

=item * L<Perl-like syntax|SPVM::Document::Language> with class syntax.

=item * L<High performance|https://github.com/yuki-kimoto/SPVM/wiki/Benchmark>

=back

=head1 Documents

=over 2

=item * L<Tutorial|https://github.com/yuki-kimoto/SPVM/wiki/Tutorial> - SPVM Tutorial

=item * L<Language Specification|SPVM::Document::Language> - SPVM Language Specification

=item * L<Standard Modules|SPVM::Document::Modules> - SPVM Standard Modules

=item * L<ExchangeAPI|SPVM::ExchangeAPI> - Exchange APIs

=item * L<Native Class|SPVM::Document::NativeClass> - Native Class

=item * L<Native APIs|SPVM::Document::NativeAPI> - Native APIs

=item * L<Resource|SPVM::Document::Resource> - Resource

=item * L<spvmcc> - Creating Executable File

=item * L<spvmdist> - Creating SPVM Distribution

=item * L<Benchmark|https://github.com/yuki-kimoto/SPVM/wiki/Benchmark> - SPVM Performance Benchmarks

=back

=head1 Loading SPVM Class
  
  # Load a SPVM class
  use SPVM 'SomeClass';
  
  # Load only SPVM module
  use SPVM ();

The C<use> statement loads a L<SPVM> class.

A SPVM class is loaded and is bound to a Perl module.

The bound Perl class name is prefixed with C<SPVM::>.

Exceptions:

If the SPVM module cannot be loaded, an exception is thrown.

Examples:

  use SPVM 'Int';
  
  my $int_object = SPVM::Int->new(3);
  my $value = $int_object->value.

=head1 Functions

=head2 api

  my $api = SPVM::api();

Gets the global L<SPVM::ExchangeAPI> object for this Perl interpreter.

=head1 Environment Variables

If an environment variable is an empty string, it is treated as an undefined value.

=head2 SPVM_BUILD_DIR

A directory for files generated by the compiler and linker.

C source codes for precompilation, dynamic link libraries and object files are stored into this directory.

These files are output when attempting to build a module containing methods with the C<native> attribute or the C<precompile> attribute.

If these files are output and the directory given by the C<SPVM_BUILD_DIR> environment variable does not exist, an exception is thrown.
Examples:

  # bash
  export SPVM_BUILD_DIR=~/.spvm_build
  
  # csh
  setenv SPVM_BUILD_DIR ~/.spvm_build

=head2 SPVM_CC_DEBUG

If the C<SPVM_CC_DEBUG> environement variable is a true value of Perl, debug messages and messages from the L<SPVM native class|SPVM::Document::NativeClass> compiler and linker are printed to stderr.

=head2 SPVM_CC_QUIET

If the C<SPVM_CC_QUIET> environement variable is a true value of Perl, messages the L<SPVM native class|SPVM::Document::NativeClass> compiler and linker are not printed to stderr.

If it is defined and a false value of Perl, the messages are printed.

This setting has a higher priority than the L<quiet|SPVM::Builder::Config/"quiet"> field of the L<SPVM::Builder::Config> module.

=head2 SPVM_CC_FORCE

If the C<SPVM_CC_FORCE> environement variable is a true value of Perl, the compilation and link by the L<SPVM native class|SPVM::Document::NativeClass> compiler and linker are forced.

This setting has a higher priority than the L<force|SPVM::Builder::Config/"force"> field of the L<SPVM::Builder::Config> module.

=head1 Repository

L<SPVM - Github|https://github.com/yuki-kimoto/SPVM>

=head1 Author

Yuki Kimoto E<lt>kimoto.yuki@gmail.comE<gt>

=head1 Core Developers

motiE<lt>motohiko.ave@gmail.comE<gt>

=head1 Contributors

=over 2

=item * Mohammad S Anwar

=item * akinomyoga

=item * NAGAYASU Shinya

=item * Reini Urban

=item * chromatic

=item * Kazutake Hiramatsu

=item * Yasuaki Omokawa

=item * Suman Khanal

=item * L<Ryunosuke Murakami|https://github.com/ryun0suke22>

=item * L<Yoshiyuki Itoh|https://github.com/YoshiyukiItoh>

=item * L<Tore Aursand|https://github.com/toreau>

=item * L<greengorcer|https://github.com/greengorcer>

=back

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

=cut
