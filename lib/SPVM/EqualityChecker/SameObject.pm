package SPVM::EqualityChecker::SameObject;

1;

=head1 NAME

SPVM::EqualityChecker::SameObject - a equality checker to check the equality of adresses of two object.

=head1 SYNOPSYS
  
  use SPVM::EqualityChecker::SameObject;
  
  my $equality_checker : SPVM::EqualityChecker = SPVM::EqualityChecker::SameObject->new;
  
  my $point1 = SPVM::Point->new(1, 2);
  my $point2 = SPVM::Point->new(5, 6);
  
  my $is_equal = $equality_checker->($point1, $point2);

=head1 DESCRIPTION

L<SPVM::EqualityChecker::SameObject> is a equality checker to check the equality of adresses of two object.

=head1 STATIC METHODS

=head2 new

  sub new : SPVM::EqualityChecker::SameObject ()

Create a new L<SPVM::EqualityChecker::SameObject> object.

=head1 INSTANCE METHODS

=head2 ANON

  sub : int ($self : self, $obj1 : object, $obj2 : object)

This method receive tow objects and return 1 if the address of the two object equals, return 0 if not.
