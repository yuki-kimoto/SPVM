package SPVM::Comparator::Float;

1;

=head1 NAME

SPVM::Comparator::Float - a callback type for float comparation

=head1 SYNOPSYS
  
  use SPVM::Comparator::Float;
  
  my $comparator : SPVM::Comparator::Float = sub : int ($self : self, $a : float, $b : float); {
    return $a <=> $b;
  };
  
  my $result = $comparator->(3, 5);

=head1 DESCRIPTION

L<SPVM::Comparator> is a callback type to compare two numbers.

=head1 CALLBACK METHOD

  sub : int ($self : self, $a : float, $b : float);

This method should receive two numbers and return 1 if $a is more than $b, -1 if $x is lass than $b, 0 if $a equals $b in the implementation.
