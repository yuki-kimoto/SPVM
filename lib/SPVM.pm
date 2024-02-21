use 5.008007;
package SPVM;
use strict;
use warnings;

use SPVM::Global;

our $VERSION = "0.989078";

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

=head2 One Liner

Run a one liner.

  # Hello World!
  spvm -e 'say "Hello World!";';

Run a one liner with loading a class.

  # foo,bar,baz
  spvm -M Fn -e 'say Fn->join(",", ["foo", "bar", "baz"]);'

=head2 Executing A SPVM Program

Write a SPVM program.

  # lib/SPVM/HelloWorld.spvm
  class HelloWorld {
    static method main : void () {
      
      say "Hello World!";
    }
  }

Run the SPVM program.

  spvm -I lib/SPVM HelloWorld

=head2 Generating An Executable File

Generate an executable file.

  spvmcc -B ~/.spvm_build -o ./hello --no-config -I lib/SPVM HelloWorld

Run the executable file.

  ./hello

=head2 Calling A SPVM Method from Perl

Write a SPVM program.

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

Write a Perl program calling a SPVM method.

  # sum.pl
  use FindBin;
  use lib "$FindBin::Bin/lib";
  
  use SPVM 'MyMath';
  
  my $total = SPVM::MyMath->sum([3, 6, 8, 9]);
  
  print "$total\n";

Run the Perl program.

  # Run
  perl sum.pl

=head1 Features

=over 2

=item * L<Native threads|SPVM::Thread> and L<goroutines|SPVM::Go>.

=item * L<Executing SPVM programs|spvm>

=item * L<Generating an executable file|spvmcc>

=item * AOT(Ahead-of-time compilation) and JIT(Just-in-time compilation).

=item * Static types, type inference and L<static analysis|SPVM::Native::Compiler>.

=item * L<C and C++ binding|SPVM::Document::NativeClass> and L<resource system|SPVM::Document::Resource> for C and C++ libraries.

=item * L<Perl binding for SPVM methods|SPVM::ExchangeAPI>.

=item * L<Perl-like syntax|SPVM::Document::Language> with class syntax.

=item * L<High performance|https://github.com/yuki-kimoto/SPVM/wiki/Benchmark>

=back

=head1 Tutorial

=over 2

=item * L<Tutorial|https://github.com/yuki-kimoto/SPVM/wiki/Tutorial> - SPVM Tutorial

=back

=head1 Documents

=over 2

=item * L<Language Specification|SPVM::Document::Language> - SPVM Language Specification

=item * L<Standard Modules|SPVM::Document::Modules> - SPVM Standard Modules

=item * L<ExchangeAPI|SPVM::ExchangeAPI> - Exchange APIs

=item * L<ExchangeAPI|SPVM::ExchangeAPI> - Exchange APIs

=item * L<Native Class|SPVM::Document::NativeClass> - Native Class

=item * L<Environment Variables|SPVM::Document::EnvironmentVariables> - Environment Variables

=item * L<Resource|SPVM::Document::Resource> - Resource

=item * L<spvm> - Executing SPVM Programs

=item * L<spvmcc> - Creating Executable File

=item * L<spvmdist> - Creating SPVM Distribution

=item * L<Benchmark|https://github.com/yuki-kimoto/SPVM/wiki/Benchmark> - SPVM Performance Benchmarks

=back

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
