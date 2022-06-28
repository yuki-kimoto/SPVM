package SPVM::EqualityChecker::SameObject;

1;

=head1 Name

SPVM::EqualityChecker::SameObject - a callback implementation of L<EqualityChecker|SPVM::EqualityChecker> to check if the memory addresses of the two objects are equal.

=head1 Synopsys
  
  use EqualityChecker::SameObject;
  
  my $equality_checker = EqualityChecker::SameObject->new;
  
  my $point1 = Point->new(1, 2);
  my $point2 = $point1;
  my $point3 = Point->new(1, 2);
  
  # Equals
  my $is_equal = $equality_checker->($point1, $point2);
  
  # Not equals
  my $is_equal = $equality_checker->($point1, $point3);

=head1 Description

L<EqualityChecker::SameObject|SPVM::EqualityChecker::SameObject> is a callback implementation of L<EqualityChecker|SPVM::EqualityChecker> to check if the memory addresses of the two objects are equal.

=head1 Class Methods

=head2 new

  static method new : EqualityChecker::SameObject ()

Create a new L<EqualityChecker::SameObject|SPVM::EqualityChecker::SameObject> object.

=head1 Interface Method IMPLEMENTATION

  method : int ($object1 : object, $object2 : object)

If the address of the two objects are equal, return 1, otherwise return 0.
