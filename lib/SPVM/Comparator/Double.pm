package SPVM::Comparator::Double;

1;

=head1 NAME

SPVM::Comparator::Double - Comparator::Double in SPVM | a callback interface for double comparation

=head1 SYNOPSYS
  
  use Comparator::Double;
  
  my $comparator : Comparator::Double = method : int ($a : double, $b : double); {
    return $a <=> $b;
  };
  
  my $result = $comparator->(3, 5);

=head1 DESCRIPTION

L<Comparator::Double|SPVM::Comparator::Double> is a callback interface to compare two double values.

=head1 CALLBACK METHOD INTERFACE

  method : int ($a : double, $b : double);

This method must receive two numbers and return 1 if $a is more than $b, -1 if $x is less than $b, 0 if $a equals $b in the implementation.

This method is planned to be implemented in other classes.
