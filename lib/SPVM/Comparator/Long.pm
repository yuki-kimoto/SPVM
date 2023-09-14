package SPVM::Comparator::Long;

1;

=head1 Name

SPVM::Comparator::Long - Interface Type for long Comparation Callback

=head1 Usage
  
  use Comparator::Long;
  
  my $comparator = (Comparator::Long)method : int ($a : long, $b : long); {
    return $a <=> $b;
  };
  
  my $result = $comparator->(3, 5);

=head1 Description

L<Comparator::Long|SPVM::Comparator::Long> is the interface type for the long comparation callback.

=head1 Interface Methods

C<required method : int ($a : long, $b : long);>

This method must receive two values that types are C<long> and return the following value.

If the first argument is greater than the second argument, returns 1. If the first argument is lower than the second argument, returns -1. If the first argument is equal to the second argument, returns 0.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
