package SPVM::Builder::Util::API;

use strict;
use warnings;
use SPVM::Builder::Util;

sub create_make_rule_native { SPVM::Builder::Util::create_make_rule_native(@_) }
sub create_make_rule_precompile { SPVM::Builder::Util::create_make_rule_precompile(@_) }

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

Creates a rule written by C<make> commands to generate a dynamic library for a class that contains native methods.

Examples:

  # Makefile.PL
  sub MY::postamble {
    
    my $make_rule = '';
    
    # Native compile make rule
    $make_rule .= SPVM::Builder::Util::API::create_make_rule_native('Foo');
    
    return $make_rule;
  }

=head2 create_make_rule_precompile

Creates a rule written by C<make> commands to generate a dynamic library for a class that contains precompiled methods.

Examples:

  # Makefile.PL
  sub MY::postamble {
    
    my $make_rule = '';
    
    # Precompile make rule
    $make_rule .= SPVM::Builder::Util::API::create_make_rule_precompile('Foo');
    
    return $make_rule;
  }

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
