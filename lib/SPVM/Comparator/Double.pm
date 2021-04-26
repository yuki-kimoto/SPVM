package SPVM::Comparator::Double;

1;

=head1 NAME

SPVM::Comparator::Double - a callback type for double comparation

=head1 SYNOPSYS
  
  use SPVM::Comparator::Double;
  
  my $comparator : SPVM::Comparator::Double = sub : int ($self : self, $a : double, $b : double); {
    return $a <=> $b;
  };
  
  my $result = $comparator->(3, 5);

=head1 DESCRIPTION

L<SPVM::Comparator> is a callback type to compare two numbers.

=head1 CALLBACK METHOD

  sub : int ($self : self, $a : double, $b : double);

This method should receive two numbers and return 1 if $a is more than $b, -1 if $x is less than $b, 0 if $a equals $b in the implementation.
