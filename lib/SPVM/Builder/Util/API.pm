package SPVM::Builder::Util::API;

use strict;
use warnings;
use SPVM::Builder::Util;

sub create_make_rule_native { SPVM::Builder::Util::create_make_rule_native(@_) }

sub create_make_rule_precompile { SPVM::Builder::Util::create_make_rule_precompile(@_) }

sub create_default_config { SPVM::Builder::Util::create_default_config(@_) }

1;

=head1 Name

SPVM::Builder::Util::API - Builder Utility APIs

=head1 Description

The SPVM::Builder::Util::API module has the public utility functions to build SPVM native classes and SPVM precompilation classes.

=head1 Usage

  my $native_make_rule = SPVM::Builder::Util::API::create_make_rule_native('MyClass');
  
  my $precompile_make_rule = SPVM::Builder::Util::API::create_make_rule_precompile('MyClass');

=head1 Functions

=head2 create_make_rule_native

  my $make_rule = SPVM::Builder::Util::API::create_make_rule_native($class_name);

Creates a string of C<make> commands for generating a dynamic library for a L<native class|SPVM::Document::NativeClass> given the class name $class_name, and returns it.

A native class must have at least one method with L<native attribute|SPVM::Document::Language::Class/"Method Attributes">.

Examples:

  # Makefile.PL
  sub MY::postamble {
    
    my $make_rule = '';
    
    # Native compile make rule
    $make_rule .= SPVM::Builder::Util::API::create_make_rule_native('Foo');
    
    return $make_rule;
  }

=head2 create_make_rule_precompile

  my $make_rule = SPVM::Builder::Util::API::create_make_rule_precompile($class_name);

Creates a string of C<make> commands for generating a dynamic library for a precompilation class given the class name $class_name, and returns it.

A precompilation class must have at least one method with L<precompile attribute|SPVM::Document::Language::Class/"Method Attributes">.

Examples:

  # Makefile.PL
  sub MY::postamble {
    
    my $make_rule = '';
    
    # Precompile make rule
    $make_rule .= SPVM::Builder::Util::API::create_make_rule_precompile('Foo');
    
    return $make_rule;
  }

=head2 create_default_config

  my $config = SPVM::Builder::Util::API::create_default_config();

Creates a default config, and returns it. It is an L<SPVM::Builder::Config> object.

Currently the default config is created by the following operation.

  my $config = SPVM::Builder::Config->new_c99;

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
