package SPVM::EqualityChecker;

1;

=head1 NAME

SPVM::EqualityChecker - EqualityChecker in SPVM | a callback type to check the object equality

=head1 SYNOPSYS
  
  use EqualityChecker;
  
  my $equality_checker : EqualityChecker = method : int ($object1 : object, $object2 : object) {
    my $point1 = (Point)$object1;
    my $point2 = (Point)$object2;
    
    if ($point1->x == $point2->x && $point1->y == $point2->y) {
      return 1;
    }
    else {
      return 0;
    }
  };
  
  my $point1 = Point->new(1, 2);
  my $point2 = Point->new(5, 6);
  
  my $is_equal = $equality_checker->($point1, $point2);

=head1 DESCRIPTION

L<EqualityChecker|SPVM::EqualityChecker> is a callback type to check the object equality.

=head1 CALLBACK METHOD

  method : int ($object1 : object, $object2 : object)

If the two objects are equals, return 1, otherwise return 0.

This method will be implemented as a anon method.
