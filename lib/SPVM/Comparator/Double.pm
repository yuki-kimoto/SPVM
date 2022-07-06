package SPVM::Comparator::Double;

1;

=head1 Name

SPVM::Comparator::Double - Interface Type for double Comparation Callback

=head1 Usage
  
  use Comparator::Double;
  
  my $comparator = (Comparator::Double)method : int ($a : double, $b : double); {
    return $a <=> $b;
  };
  
  my $result = $comparator->(3, 5);

=head1 Description

L<Comparator::Double|SPVM::Comparator::Double> is the interface type for the double comparation callback.

=head1 Interface Methods

  required method : int ($a : double, $b : double);

This method must receive two values that types are C<double> and return the following value.

If the first argument is greater than the second argument, returns C<1>. If the first argument is lower than the second argument, returns C<-1>. If the first argument is equal to the second argument, returns C<0>.
