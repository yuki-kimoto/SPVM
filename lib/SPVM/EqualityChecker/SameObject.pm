package SPVM::EqualityChecker::SameObject;

1;

=head1 NAME

SPVM::EqualityChecker::SameObject - a callback implementation of L<SPVM::EqualityChecker> to check if the memory addresses of the two objects are equal.

=head1 SYNOPSYS
  
  use SPVM::EqualityChecker::SameObject;
  
  my $equality_checker = SPVM::EqualityChecker::SameObject->new;
  
  my $point1 = SPVM::Point->new(1, 2);
  my $point2 = $point1;
  my $point3 = SPVM::Point->new(1, 2);
  
  # Equals
  my $is_equal = $equality_checker->($point1, $point2);
  
  # Not equals
  my $is_equal = $equality_checker->($point1, $point3);

=head1 DESCRIPTION

L<SPVM::EqualityChecker::SameObject> is a callback implementation of L<SPVM::EqualityChecker> to check if the memory addresses of the two objects are equal.

=head1 STATIC METHODS

=head2 new

  sub new : SPVM::EqualityChecker::SameObject ()

Create a new L<SPVM::EqualityChecker::SameObject> object.

=head1 CALLBACK METHOD IMPLEMENTATION

  sub : int ($self : self, $obj1 : object, $obj2 : object)

If the address of the two objects are equal, return 1, otherwise return 0.
