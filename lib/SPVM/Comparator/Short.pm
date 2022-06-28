package SPVM::Comparator::Short;

1;

=head1 Name

SPVM::Comparator::Short - Interface Type for short Comparation Callback

=head1 Synopsys
  
  use Comparator::Short;
  
  my $comparator = (Comparator::Short)method : int ($a : short, $b : short); {
    return $a <=> $b;
  };
  
  my $result = $comparator->(3, 5);

=head1 Description

L<Comparator::Short|SPVM::Comparator::Short> is the interface type for the short comparation callback.

=head1 Interface Methods

  required method : int ($a : short, $b : short);

This method must receive two values that types are C<short> and return the following value.

If the first argument is greater than the second argument, returns C<1>. If the first argument is lower than the second argument, returns C<-1>. If the first argument is equal to the second argument, returns C<0>.
