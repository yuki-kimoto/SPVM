package SPVM::Comparator::Long;

1;

=head1 NAME

SPVM::Comparator::Long - Interface Type for long Comparation Callback

=head1 SYNOPSYS
  
  use Comparator::Long;
  
  my $comparator = (Comparator::Long)method : int ($a : long, $b : long); {
    return $a <=> $b;
  };
  
  my $result = $comparator->(3, 5);

=head1 DESCRIPTION

L<Comparator::Long|SPVM::Comparator::Long> is the interface type for the long comparation callback.

=head1 INTERFACE METHODS

  required method : int ($a : long, $b : long);

This method must receive two values that types are C<long> and return the following value.

If the first argument is greater than the second argument, returns C<1>. If the first argument is lower than the second argument, returns C<-1>. If the first argument is equal to the second argument, returns C<0>.
