package SPVM::EqualityChecker;

1;

=head1 NAME

SPVM::EqualityChecker - Interface Type for Object Equality Checking Callback

=head1 SYNOPSYS
  
  use EqualityChecker;
  use Point;
  
  my $equality_checker = (EqualityChecker)method : int ($object1 : object, $object2 : object) {
    my $point1 = (Point)$object1;
    my $point2 = (Point)$object2;
    
    if ($point1->x == $point2->x && $point1->y == $point2->y) {
      return 1;
    }
    else {
      return 0;
    }
  };
  
  my $point1 = Point->new_xy(1, 2);
  my $point2 = Point->new_xy(5, 6);
  
  my $is_equal = $equality_checker->($point1, $point2);

=head1 DESCRIPTION

L<EqualityChecker|SPVM::EqualityChecker> is the interface type for the object equality checking callback.

=head1 INTERFACE METHODS

  required method : int ($object1 : object, $object2 : object)

The implementation must receive two objects and if they are equal, return C<1>, otherwise return C<0>.
