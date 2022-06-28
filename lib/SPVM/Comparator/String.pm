package SPVM::Comparator::String;

1;

=head1 Name

SPVM::Comparator::String - Interface Type for String Comparation Callback

=head1 Synopsys
  
  use Comparator::String;
  
  my $comparator = (Comparator::String)method : int ($a : string, $b : string); {
    return $a cmp $b;
  };
  
  my $result = $comparator->(3, 5);

=head1 Description

L<Comparator::String|SPVM::Comparator::String> is the interface type for the string comparation callback.

=head1 Interface Methods

  required method : int ($a : string, $b : string);

This method must receive two values that types are C<string> and return the following value.

If the first argument is greater than the second argument, returns C<1>. If the first argument is lower than the second argument, returns C<-1>. If the first argument is equal to the second argument, returns C<0>.
