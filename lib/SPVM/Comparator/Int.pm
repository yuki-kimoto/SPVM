package SPVM::Comparator::Int;

1;

=head1 NAME

SPVM::Comparator::Int - a callback interface for int comparation

=head1 SYNOPSYS
  
  use SPVM::Comparator::Int;
  
  my $comparator : SPVM::Comparator::Int = sub : int ($self : self, $a : int, $b : int); {
    return $a <=> $b;
  };
  
  my $result = $comparator->(3, 5);

=head1 DESCRIPTION

L<SPVM::Comparator::Int> is a callback interface to compare two int values.

=head1 CALLBACK METHOD INTERFACE

  sub : int ($self : self, $a : int, $b : int);

This method must receive two numbers and return 1 if $a is more than $b, -1 if $x is less than $b, 0 if $a equals $b in the implementation.

This method is planned to be implemented in other classes.
