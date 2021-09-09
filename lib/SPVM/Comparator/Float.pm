package SPVM::Comparator::Float;

1;

=head1 NAME

SPVM::Comparator::Float - a callback interface for float comparation

=head1 SYNOPSYS
  
  use Comparator::Float;
  
  my $comparator : Comparator::Float = sub : int ($self : self, $a : float, $b : float); {
    return $a <=> $b;
  };
  
  my $result = $comparator->(3, 5);

=head1 DESCRIPTION

L<Comparator::Float|SPVM::Comparator::Float> is a callback interface to compare two float values.

=head1 CALLBACK METHOD INTERFACE

  sub : int ($self : self, $a : float, $b : float);

This method must receive two numbers and return 1 if $a is more than $b, -1 if $x is less than $b, 0 if $a equals $b in the implementation.

This method is planned to be implemented in other classes.
