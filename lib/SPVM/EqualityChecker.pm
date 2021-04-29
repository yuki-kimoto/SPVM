package SPVM::EqualityChecker;

1;

=head1 NAME

SPVM::EqualityChecker - a callback interface to check the object equality

=head1 SYNOPSYS
  
  use SPVM::EqualityChecker;
  
  my $equality_checker : SPVM::EqualityChecker = sub : int ($self : self, $object1 : object, $object2 : object) {
    my $point1 = (SPVM::Point)$object1;
    my $point2 = (SPVM::Point)$object2;
    
    if ($point1->x == $point2->x && $point1->y == $point2->y) {
      return 1;
    }
    else {
      return 0;
    }
  };
  
  my $point1 = SPVM::Point->new(1, 2);
  my $point2 = SPVM::Point->new(5, 6);
  
  my $is_equal = $equality_checker->($point1, $point2);

=head1 DESCRIPTION

L<SPVM::EqualityChecker> is a callback interface to check the object equality.

=head1 CALLBACK METHOD INTERFACE

  sub : int ($self : self, $object1 : object, $object2 : object)

If the two objects are equals, return 1, otherwise return 0.

This method is planned to be implemented in other classes.
