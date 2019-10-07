package SPVM::Cloner;

use SPVM 'SPVM::Cloner';

1;

=head1 NAME

SPVM::Cloner - a callback class for objectification

=head1 SYNOPSYS
  
  use SPVM::Cloner;
  
  my $cloner : SPVM::Cloner = sub clone : object ($self : self, $obj : object) {
    return "Hello";
  };
  
  my $message = $cloner->clone;

=head1 DESCRIPTION

L<SPVM::Cloner> is a callback type to clone object.

=head1 INSTANCE METHODS

=head2 clone

  sub clone : object ($self : self, $obj : object);
