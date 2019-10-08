package SPVM::Comparator;

use SPVM 'SPVM::Comparator';

1;

=head1 NAME

SPVM::Comparator - a callback type for comparation

=head1 SYNOPSYS
  
  use SPVM::Comparator;
  
  my $comparator : SPVM::Comparator = sub compare : int ($self : self, $x1 : object, $x2 : object); {
    return $x1 > $x2;
  };
  
  my $result = $comparator->compare;

=head1 DESCRIPTION

L<SPVM::Comparator> is a callback type to compare objects.

=head1 INSTANCE METHODS

=head2 compare

  sub compare : int ($self : self, $x1 : object, $x2 : object);
