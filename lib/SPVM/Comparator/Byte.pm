package SPVM::Comparator::Byte;

1;

=head1 Name

SPVM::Comparator::Byte - Interface Type for byte Comparation Callback

=head1 Usage
  
  use Comparator::Byte;
  
  my $comparator = (Comparator::Byte)method : int ($a : byte, $b : byte); {
    return $a <=> $b;
  };
  
  my $result = $comparator->(3, 5);

=head1 Description

L<Comparator::Byte|SPVM::Comparator::Byte> is the interface type for the byte comparation callback.

=head1 Interface Methods

  required method : int ($a : byte, $b : byte);

This method must receive two values that types are C<byte> and return the following value.

If the first argument is greater than the second argument, returns C<1>. If the first argument is lower than the second argument, returns C<-1>. If the first argument is equal to the second argument, returns C<0>.
