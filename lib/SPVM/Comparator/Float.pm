package SPVM::Comparator::Float;

1;

=head1 Name

SPVM::Comparator::Float - Interface Type for float Comparation Callback

=head1 Usage
  
  use Comparator::Float;
  
  my $comparator = (Comparator::Float)method : int ($a : float, $b : float); {
    return $a <=> $b;
  };
  
  my $result = $comparator->(3, 5);

=head1 Description

L<Comparator::Float|SPVM::Comparator::Float> is the interface type for the float comparation callback.

=head1 Interface Methods

  required method : int ($a : float, $b : float);

This method must receive two values that types are C<float> and return the following value.

If the first argument is greater than the second argument, returns 1. If the first argument is lower than the second argument, returns -1. If the first argument is equal to the second argument, returns 0.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
