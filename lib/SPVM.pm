package SPVM;
use strict;
use warnings;

use SPVM::Global;

our $VERSION = "0.990093";

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

SPVM - The SPVM Language

=begin html

<img src="https://github.com/yuki-kimoto/SPVM/raw/master/logo/spvm_logo.jpg" width="80px" alt="SPVM cat">

=end html

=head1 Description

SPVM is a statically typed programming language that has Perl-like syntax.

SPVM has not yet reached a stable release of version 1.0. For now, there is currently no policy to keep the L<backward compatibility|https://github.com/yuki-kimoto/SPVM/wiki/Backward-Compatibility>.

=head1 Usage

=head2 One Liner

Run a one liner using L<spvm> command.

  # Hello World!
  spvm -e 'say "Hello World!";';

Run a one liner with loading a class.

  # foo,bar,baz
  spvm -M Fn -e 'say Fn->join(",", ["foo", "bar", "baz"]);'

=head2 Executing An SPVM Program

Write a L<SPVM class|SPVM::Document::Language::Class> named C<hello.spvm> to print "Hello World!" using L<say operator|SPVM::Document::Language::Operators/"say Operator">.

  # hello.spvm
  class {
    static method main : void () {
      
      say "Hello World!";
    }
  }

This class is an L<anon class|SPVM::Document::Language::Class/"Anon Class"> and has C<main> method that is an L<bootstrap method|SPVM::Document::Language::Class/"Bootstrap Method">.

Run the SPVM program using L<spvm> command.

  spvm hello.spvm

=head2 Generating An Executable File

Generate an executable file using L<spvmcc> command.

  spvmcc -B ~/.spvm_build -o ./hello --no-config hello.spvm

Run the executable file.

  ./hello

=head2 Calling An SPVM Method from Perl

Write an SPVM class.

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

Write a Perl program calling an SPVM method using L<exchange APIs|SPVM::ExchangeAPI>.

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

=item * L<SPVM Tutorial|https://github.com/yuki-kimoto/SPVM/wiki/Tutorial>

=back

=head1 Documents

L<All SPVM Documents|SPVM::Document>

=over 2

=item * L<Language Specification|SPVM::Document::Language>

=over 2

=item * L<Lexical Tokenization|SPVM::Document::Language::Tokenization>

=item * L<Syntax Parsing|SPVM::Document::Language::SyntaxParsing>

=item * L<Class Definition|SPVM::Document::Language::Class>

=item * L<Types|SPVM::Document::Language::Types>

=item * L<Statements|SPVM::Document::Language::Statements>

=item * L<Operators|SPVM::Document::Language::Operators>

=item * L<Exception Handling|SPVM::Document::Language::ExceptionHandling>

=item * L<Garbage Collection|SPVM::Document::Language::GarbageCollection>

=item * L<System Setting|SPVM::Document::Language::System>

=back

=item * L<Native Classes|SPVM::Document::NativeClass>

=item * L<Native Class Config|SPVM::Builder::Config>

=item * L<Native APIs|SPVM::Document::NativeAPI>

=over 2

=item * L<Runtime Native APIs|SPVM::Document::NativeAPI::Runtime>

=item * L<Basic Type Native APIs|SPVM::Document::NativeAPI::BasicType>

=item * L<Class Variable Native APIs|SPVM::Document::NativeAPI::ClassVariable>

=item * L<Field Native APIs|SPVM::Document::NativeAPI::Field>

=item * L<Method Native APIs|SPVM::Document::NativeAPI::Method>

=item * L<Argument Native APIs|SPVM::Document::NativeAPI::Argument>

=item * L<Type Native APIs|SPVM::Document::NativeAPI::Type>

=item * L<Compiler Native APIs|SPVM::Document::NativeAPI::Compiler>

=item * L<Class File Native APIs|SPVM::Document::NativeAPI::ClassFile>

=item * L<String Buffer Native APIs|SPVM::Document::NativeAPI::StringBuffer>

=item * L<Allocatord Native APIs|SPVM::Document::NativeAPI::Allocator>

=item * L<Mutex Native APIs|SPVM::Document::NativeAPI::Mutex>

=item * L<Internal Native APIs|SPVM::Document::NativeAPI::Internal>

=back

=item * L<Resources|SPVM::Document::Resource>

=item * L<Environment Variables|SPVM::Document::EnvironmentVariables>

=back

=head1 Exchange APIs

=over 2

=item * L<Exchange APIs|SPVM::ExchangeAPI>

=back

=head1 Builder APIs

=over 2

=item * L<Builder APIs|SPVM::Builder::API>

=item * L<Builder Utility APIs|SPVM::Builder::Util::API>

=item * L<Config Builder|SPVM::Builder::ConfigBuilder>

=item * L<SPVM Script Information|SPVM::Builder::ProgramInfo>

=back

=head1 Commands

=over 2

=item * L<spvm - Executing SPVM Programs|spvm>

=item * L<spvmcc - Generating Executable Files|spvmcc>

=item * L<spvmdist - Distributing SPVM Modules|spvmdist>

=item * L<spvmdeps - Class Dependencies Analyzer|spvmdeps>

=back

=head1 Modules

=over 2

=item * L<Standard Modules|SPVM::Document::Modules>

=item * L<CPAN Modules|https://github.com/yuki-kimoto/SPVM/wiki/CPAN-Modules>

=back

=head1 Examples

=over 2

=item * L<SPVM Test Cases|https://github.com/yuki-kimoto/SPVM/tree/doc/t/02_vm/lib/SPVM/TestCase>

=item * L<Binding C/C++ Libraries|https://github.com/yuki-kimoto/SPVM/tree/doc/examples/native>

=back

=head1 Wiki

=over 2

=item * L<Wiki|https://github.com/yuki-kimoto/SPVM/wiki>

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
