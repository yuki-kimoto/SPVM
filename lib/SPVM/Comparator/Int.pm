package SPVM::Comparator::Int;

1;

=head1 Name

SPVM::Comparator::Int - Interface Type for int Comparation Callback

=head1 Synopsys
  
  use Comparator::Int;
  
  my $comparator = (Comparator::Int)method : int ($a : int, $b : int); {
    return $a <=> $b;
  };
  
  my $result = $comparator->(3, 5);

=head1 Description

L<Comparator::Int|SPVM::Comparator::Int> is the interface type for the int comparation callback.

=head1 Interface Methods

  required method : int ($a : int, $b : int);

This method must receive two values that types are C<int> and return the following value.

If the first argument is greater than the second argument, returns C<1>. If the first argument is lower than the second argument, returns C<-1>. If the first argument is equal to the second argument, returns C<0>.
