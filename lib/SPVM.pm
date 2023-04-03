use 5.008007;
package SPVM;
use strict;
use warnings;

use Carp 'cluck';

use SPVM::Builder;
use SPVM::Global;

our $VERSION = '0.9670';

require XSLoader;
XSLoader::load('SPVM', $VERSION);

sub import {
  my ($class, $class_name) = @_;

  my ($file, $line) = (caller)[1, 2];
  
  if (defined $class_name) {
    SPVM::Global::build_class($class_name, $file, $line);
    SPVM::Global::bind_to_perl($class_name);
  }
}

sub api {
  unless ($SPVM::Global::API) {
    SPVM::Global::init_api();
  }
  return $SPVM::Global::API;
}

1;

=encoding utf8

=head1 Name

SPVM - SPVM Language

=head1 Caution

C<SPVM> is not yet 1.0 release. It is quite often changed without warnings until I feel that the implementation is good enough.

=head1 Usage

Creating SPVM Module:

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

Calling SPVM methods from Perl:

  # sum.pl
  use strict;
  use warnings;
  use FindBin;
  use lib "$FindBin::Bin/lib";

  use SPVM 'MyMath';

  # Call method
  my $total = SPVM::MyMath->sum([3, 6, 8, 9]);

  print "$total\n";

=head1 Description

B<SPVM> (Static Perl Virtual Machine) is a perl-ish static typed programing language. SPVM provides fast calculation, fast array operations, easy C/C++ binding, and creating executable files.

=head1 Loading Module

If you load SVPM module from Perl, use the following syntax.

  use SPVM 'Foo';

Suppose the following C<SPVM/Foo.spvm> is placed on a module search path.

  # SPVM/Foo.spvm
  class Foo {
    static method sum : int ($x1 : int, $x2 : int) {
      return $x1 + $x2;
    }
  }

If you load SPVM C<Foo::Bar> module, do the following.

  use SPVM 'Foo::Bar';

Suppose the following C<SPVM/Foo/Bar.spvm> is placed on a module search path.

  # SPVM/Foo/Bar.spvm
  class Foo::Bar {
    static method sum : int ($x1 : int, $x2 : int) {
      return $x1 + $x2;
    }
  }

C<use SPVM MODULE_NAME> compile the SPVM module and the dependent modules.

Note that at this point a SPVM runtime has not yet been created.

A default SPVM runtime is created the first time you call a method of SPVM module or call a function or method of the Exchange API.

=head1 Class Method Call

Let's call SPVM class method from Perl.

  use SPVM 'Foo';

  my $total = SPVM::Foo->sum(1, 2);

The definition of C<Foo> module is the following.

  # SPVM/Foo.spvm
  class Foo {
    static method sum : int ($x1 : int, $x2 : int) {
      return $x1 + $x2;
    }
  }

If the number of arguments does not match the number of arguments of the SPVM method, an exception occurs.

The Perl values of the arguments are converted to the SPVM values by the rule of argument convertion.

If the type is non-conforming, an exception occurs.

The SPVM return value is converted to a Perl return value by the rule of return value convertion.

The SPVM exception is converted to a Perl exception.

=head1 Instance Method Call

Let's call SPVM instance method from Perl.

  use SPVM 'Foo';

  my $foo = SPVM::Foo->new;

  my $total = $foo->sum(1, 2);

The definition of C<Foo> module is the following.

  # SPVM/Foo.spvm
  class Foo {
    static method new : Foo () {
      return new Foo;
    }

    method sum : int ($x1 : int, $x2 : int) (
      return $x1 + $x2;
    }
  }

=head1 Exchange API

Exchange API is APIs to convert Perl data structures to/from SPVM data structures and to call SPVM methods from Perl.

=head2 api

  my $api = SPVM::api();

Gets the global L<SPVM::ExchangeAPI> object.

=head1 Document

SPVM documents.

=head2 Tutorial

SPVM Tutorial.

=over 2

=item * L<Tutorial|SPVM::Document::Tutorial>

=back

=head2 Language Specification

SPVM Language Specification.

=over 2

=item * L<Language Specification|SPVM::Document::Language>

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

=head2 Native Module

The native module is the module that is implemented by native language such as the C language or C<C++>.

=over 2

=item * L<Native Method|SPVM::Document::NativeModule>

=back

=head2 Native APIs

SPVM native APIs are public APIs that are used in native language sources such as the C language or C<C++>.

=over 2

=item * L<Native APIs|SPVM::Document::NativeAPI>

=back

=head2 Resource

A resource is a L<native module|SPVM::Document::NativeModule> that contains a set of sources and headers of native language such as the C language or C<C++>.

=over 2

=item * L<Resource|SPVM::Document::Resource>

=back

=head2 Creating Executable File

C<spvmcc> is the compiler and linker to create the executable file from SPVM source codes.

=over 2

=item * L<spvmcc>

=back

=head2 Creating SPVM Distribution

C<spvmdist> is the command to create SPVM distribution.

=over 2

=item * L<spvmdist>

=back

=head2 Benchmark

SPVM performance benchmarks.

=over 2

=item * L<Benchmark|SPVM::Document::Benchmark>

=back

=head1 Environment Variables

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

=head1 Repository

L<Github|https://github.com/yuki-kimoto/SPVM>

=head1 Bug Report

L<GitHub Issue|https://github.com/yuki-kimoto/SPVM/issues>

=head1 Support

L<Github Discussions|https://github.com/yuki-kimoto/SPVM/discussions>

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
