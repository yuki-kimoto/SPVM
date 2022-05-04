package SPVM::Comparator::Double;

1;

=head1 NAME

SPVM::Comparator::Double - A Callback Type for double Comparation

=head1 SYNOPSYS
  
  use Comparator::Double;
  
  my $comparator : Comparator::Double = method : int ($a : double, $b : double); {
    return $a <=> $b;
  };
  
  my $result = $comparator->(3, 5);

=head1 DESCRIPTION

L<Comparator::Double|SPVM::Comparator::Double> is a callback type to compare two double values.

=head1 CALLBACK METHOD

  required method : int ($a : double, $b : double);

The implementation must receive two numbers and return 1 if $a is more than $b, -1 if $x is less than $b, 0 if $a equals $b in the implementation.
