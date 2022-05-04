package SPVM::EqualityChecker;

1;

=head1 NAME

SPVM::EqualityChecker - A Callback Type to Check the Object Equality

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

  required method : int ($object1 : object, $object2 : object)

The implementation must receive two objects and if they are equals, return C<1>, otherwise return C<0>.
