package SPVM::Comparator;

use SPVM 'SPVM::Comparator';

1;

=head1 NAME

SPVM::Comparator - a callback type for comparation

=head1 SYNOPSYS
  
  use SPVM::Comparator;
  
  my $comparator : SPVM::Comparator = sub : int ($self : self, $x1 : object, $x2 : object); {
    return $x1 > $x2;
  };
  
  my $result = $comparator->();

=head1 DESCRIPTION

L<SPVM::Comparator> is a callback type to compare objects.

=head1 CALLBACK METHOD

=head2 compare

  sub : int ($self : self, $x1 : object, $x2 : object);
