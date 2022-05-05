package SPVM::Comparator::Int;

1;

=head1 NAME

SPVM::Comparator::Int - A Callback Type for int Comparation

=head1 SYNOPSYS
  
  use Comparator::Int;
  
  my $comparator : Comparator::Int = method : int ($a : int, $b : int); {
    return $a <=> $b;
  };
  
  my $result = $comparator->(3, 5);

=head1 DESCRIPTION

L<Comparator::Int|SPVM::Comparator::Int> is an interface type for the callback to compare two int values.

=head1 INTERFACE METHOD

  required method : int ($a : int, $b : int);

The implementation must receive two numbers and return 1 if $a is more than $b, -1 if $x is less than $b, 0 if $a equals $b in the implementation.
