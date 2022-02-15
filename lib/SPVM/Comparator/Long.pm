package SPVM::Comparator::Long;

1;

=head1 NAME

SPVM::Comparator::Long - A Callback Type for long Comparation

=head1 SYNOPSYS
  
  use Comparator::Long;
  
  my $comparator : Comparator::Long = method : int ($a : long, $b : long); {
    return $a <=> $b;
  };
  
  my $result = $comparator->(3, 5);

=head1 DESCRIPTION

L<Comparator::Long|SPVM::Comparator::Long> is a callback type to compare two long values.

=head1 CALLBACK METHOD

  method : int ($a : long, $b : long);

The implementation must receive two numbers and return 1 if $a is more than $b, -1 if $x is less than $b, 0 if $a equals $b in the implementation.
