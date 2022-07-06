package SPVM::Builder::Util::API;

use strict;
use warnings;
use SPVM::Builder::Util;

sub create_make_rule_native { SPVM::Builder::Util::create_make_rule_native(@_) }
sub create_make_rule_precompile { SPVM::Builder::Util::create_make_rule_precompile(@_) }

1;

=head1 Name

SPVM::Builder::Util::API - Public APIs of the utility of SPVM Builder

=head1 Usage
    
  # Create native make rule
  my $native_make_rule
    = SPVM::Builder::Util::API::create_make_rule_native('Foo');
  
  # Create precompile make rule
  my $precompile_make_rule
    = SPVM::Builder::Util::API::create_make_rule_precompile('Foo');

=head1 Description

B<SPVM::Builder::Util::API> is the public APIs of the utilities of SPVM Builder. 

L<SPVM::Builder::Util> is a private modules of L<SPVM>.

The names and arguments of the functions are changed without warnings in the future release.

However, the functions is useful to create the content of Makefile.

B<SPVM::Builder::Util::API> provides the public APIs to call the functions of L<SPVM::Builder::Util>. These APIs is public and stable.

=head1 Functions

=head2 create_make_rule_native

Create native compile make rule.

This is used in Makefile.PL of your distributed module.
  
  # Makefile.PL
  sub MY::postamble {

    my $make_rule = '';
    
    # Native compile make rule
    $make_rule .= SPVM::Builder::Util::API::create_make_rule_native('Foo');
    
    return $make_rule;
  }

=head2 create_make_rule_precompile

Create precompile make rule.

This is used in Makefile.PL of your distributed module.

  sub MY::postamble {

    my $make_rule = '';
    
    # Precompile make rule
    $make_rule .= SPVM::Builder::Util::API::create_make_rule_precompile('Foo');
    
    return $make_rule;
  }
