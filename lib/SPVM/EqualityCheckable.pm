package SPVM::EqualityCheckable;

1;

=head1 NAME

SPVM::EqualityCheckable - EqualityCheckable in SPVM | a interface type to check the object equality

=head1 SYNOPSYS
  
  class Point {
    implement EqualityCheckable;

    method equals : int ($object1 : object, $object2 : object) {
      my $point1 = (Point)$object1;
      my $point2 = (Point)$object2;
      
      if ($point1->x == $point2->x && $point1->y == $point2->y) {
        return 1;
      }
      else {
        return 0;
      }
    };
  }
  
=head1 DESCRIPTION

L<EqualityCheckable|SPVM::EqualityCheckable> is a interface type to check the object equality.

=head1 CALLBACK METHOD

  method equals : int ($object1 : object, $object2 : object);

The implementation must receive two objects and if they are equals, return C<1>, otherwise return C<0>.
