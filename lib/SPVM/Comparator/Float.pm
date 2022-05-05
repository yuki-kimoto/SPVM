package SPVM::Comparator::Float;

1;

=head1 NAME

SPVM::Comparator::Float - A Callback Type for float Comparation

=head1 SYNOPSYS
  
  use Comparator::Float;
  
  my $comparator : Comparator::Float = method : int ($a : float, $b : float); {
    return $a <=> $b;
  };
  
  my $result = $comparator->(3, 5);

=head1 DESCRIPTION

L<Comparator::Float|SPVM::Comparator::Float> is an interface type for the callback to compare two float values.

=head1 INTERFACE METHOD

  required method : int ($a : float, $b : float);

The implementation must receive two numbers and return 1 if $a is more than $b, -1 if $x is less than $b, 0 if $a equals $b in the implementation.
