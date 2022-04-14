package SPVM::Comparator;

1;

=head1 NAME

SPVM::Comparator - A Callback Type for Object Comparation

=head1 SYNOPSYS
  
  use Comparator;
  
  my $comparator : Comparator = method : int ($object1 : object, $object2 : object); {
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
  
  my $point1 = Point->new(1, 2);
  my $point2 = Point->new(5, 6);
  my $result = $comparator->($point1, $point2);

=head1 DESCRIPTION

L<Comparator|SPVM::Comparator> is a callback type to compare two objects.

=head1 CALLBACK METHOD

  method : int ($object1 : object, $object2 : object);

This method must receive two objects and return 1 if $object1 is more than $object2, -1 if $x is less than $object2, 0 if $object1 equals $object2 in the implementation.
