package SPVM::EqualityChecker::SameObject;

1;

=head1 NAME

SPVM::EqualityChecker::SameObject - EqualityChecker::SameObject in SPVM | a callback implementation of L<EqualityChecker|SPVM::EqualityChecker> to check if the memory addresses of the two objects are equal.

=head1 SYNOPSYS
  
  use EqualityChecker::SameObject;
  
  my $equality_checker = EqualityChecker::SameObject->new;
  
  my $point1 = Point->new(1, 2);
  my $point2 = $point1;
  my $point3 = Point->new(1, 2);
  
  # Equals
  my $is_equal = $equality_checker->($point1, $point2);
  
  # Not equals
  my $is_equal = $equality_checker->($point1, $point3);

=head1 DESCRIPTION

L<EqualityChecker::SameObject|SPVM::EqualityChecker::SameObject> is a callback implementation of L<EqualityChecker|SPVM::EqualityChecker> to check if the memory addresses of the two objects are equal.

=head1 STATIC METHODS

=head2 new

  sub new : EqualityChecker::SameObject ()

Create a new L<EqualityChecker::SameObject|SPVM::EqualityChecker::SameObject> object.

=head1 CALLBACK METHOD IMPLEMENTATION

  sub : int ($self : self, $object1 : object, $object2 : object)

If the address of the two objects are equal, return 1, otherwise return 0.
