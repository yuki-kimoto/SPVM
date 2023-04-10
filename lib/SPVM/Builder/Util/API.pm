package SPVM::Builder::Util::API;

use strict;
use warnings;
use SPVM::Builder::Util;

sub create_make_rule_native { SPVM::Builder::Util::create_make_rule_native(@_) }

sub create_make_rule_precompile { SPVM::Builder::Util::create_make_rule_precompile(@_) }

sub create_default_config { SPVM::Builder::Util::create_default_config(@_) }

1;

=head1 Name

SPVM::Builder::Util::API - Public Functions for SPVM Builder Utilities

=head1 Description

The SPVM::Builder::Util::API module has public utility functions for the SPVM builder L<SPVM::Builder>.

=head1 Usage

  my $native_make_rule = SPVM::Builder::Util::API::create_make_rule_native('Foo');
  
  my $precompile_make_rule = SPVM::Builder::Util::API::create_make_rule_precompile('Foo');

=head1 Functions

=head2 create_make_rule_native

  my $make_rule = SPVM::Builder::Util::API::create_make_rule_native($class_name);

Creates a rule written by C<make> commands to generate a dynamic library for the class $class_name that contains native methods, and returns the rule.

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

Creates a rule written by C<make> commands to generate a dynamic library for the class $class_name that contains precompiled methods, and returns the rule.

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

Creates a default config, and returns it. The config is a L<SPVM::Builder::Config> object.

The current implementation is the following one.

  my $config = SPVM::Builder::Config->new_c99(file_optional => 1);

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
