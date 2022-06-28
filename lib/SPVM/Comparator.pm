package SPVM::Comparator;

1;

=head1 Name

SPVM::Comparator - Interface Type for Object Comparation Callback

=head1 Synopsys
  
  use Comparator;
  use Point;
  
  my $comparator = (Comparator)method : int ($object1 : object, $object2 : object); {
    my $point1 = (Point)$object1;
    my $point2 = (Point)$object2;
    
    if ($point1->x > $point2->x) {
      return 1;
    }
    elsif ($point1->x < $point2->x) {
      return -1;
    }
    else {
      return 0;
    }
  };
  
  my $point1 = Point->new_xy(1, 2);
  my $point2 = Point->new_xy(5, 6);
  my $result = $comparator->($point1, $point2);

=head1 Description

C<Comparator> is the interface type for the object comparation callback.

=head1 Interface Methods

  required method : int ($object1 : object, $object2 : object);

This method must receive two objects and return the following value.

If the first argument is greater than the second argument, returns C<1>. If the first argument is lower than the second argument, returns C<-1>. If the first argument is equal to the second argument, returns C<0>.
