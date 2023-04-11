use 5.008007;
package SPVM;
use strict;
use warnings;

use Carp 'cluck';

use SPVM::Builder;
use SPVM::Global;

our $VERSION = '0.9704';

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

=head1 Description

SPVM is a statically typed programming language with the syntax of Perl.

SPVM has not yet reached a stable release of version 1.0. For now, L<backward compatibility|https://github.com/yuki-kimoto/SPVM/wiki/Backward-Compatibility> of methods and features will not be kept.

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

Calling SPVM methods from Perl:

  # sum.pl
  use FindBin;
  use lib "$FindBin::Bin/lib";
  
  use SPVM 'MyMath';
  
  # Call method
  my $total = SPVM::MyMath->sum([3, 6, 8, 9]);

=head1 Document

=item * L<Tutorial|https://github.com/yuki-kimoto/SPVM/wiki/Tutorial> - SPVM Tutorial

=item * L<Language Specification|SPVM::Document::Language> - SPVM Language Specification

=item * L<Standard Modules|SPVM::Document::Modules> - SPVM Standard Modules

=item * L<ExchangeAPI|SPVM::Document::ExchangeAPI> - Exchange APIs

=item * L<Native Method|SPVM::Document::NativeClass> - Native Class

=item * L<Native APIs|SPVM::Document::NativeAPI> - Native APIs

=item * L<Resource|SPVM::Document::Resource> - Resource

=item * L<spvmcc> - Creating Executable File

=item * L<spvmdist> - Creating SPVM Distribution

=item * L<Benchmark|SPVM::Document::Benchmark> - SPVM Performance Benchmarks

=back

=head1 Exchange API

Exchange API is APIs to convert Perl data structures to/from SPVM data structures and to call SPVM methods from Perl.

=head2 api

  my $api = SPVM::api();

Gets the global L<SPVM::ExchangeAPI> object for this Perl interpreter.

=head1 Environment Variables

=head2 SPVM_BUILD_DIR

SPVM building directory to build C<precompile> and C<native> methods. If the C<SPVM_BUILD_DIR> environment variable is not set, the building of C<precompile> and C<native> methods fails.

B<bash:>

  export SPVM_BUILD_DIR=~/.spvm_build

B<csh:>

  setenv SPVM_BUILD_DIR ~/.spvm_build

=head2 SPVM_CC_DEBUG

Prints debug messages of the L<SPVM::Builder::CC> class to stderr.

=head2 SPVM_CC_FORCE

Forces the compilation and the link by the L<SPVM::Builder::CC> class.

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
