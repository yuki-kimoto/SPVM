package SPVM::EqualityChecker::Address;

1;

=head1 Name

SPVM::EqualityChecker::Address - a callback implementation of L<EqualityChecker|SPVM::EqualityChecker> to check if the memory addresses of the two objects are equal.

=head1 Usage
  
  use EqualityChecker::Address;
  
  my $equality_checker = EqualityChecker::Address->new;
  
  my $point1 = Point->new(1, 2);
  my $point2 = $point1;
  my $point3 = Point->new(1, 2);
  
  # Equals
  my $is_equal = $equality_checker->($point1, $point2);
  
  # Not equals
  my $is_equal = $equality_checker->($point1, $point3);

=head1 Description

L<EqualityChecker::Address|SPVM::EqualityChecker::Address> is a callback implementation of L<EqualityChecker|SPVM::EqualityChecker> to check if the memory addresses of the two objects are equal.

=head1 Class Methods

=head2 new

  static method new : EqualityChecker::Address ();

Create a new L<EqualityChecker::Address|SPVM::EqualityChecker::Address> object.

=head1 Interface Method Implementation

  method : int ($object1 : object, $object2 : object);

If the address of the two objects are equal, return 1, otherwise return 0.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
