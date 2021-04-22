package SPVM::Comparator::Object;

1;

=head1 NAME

SPVM::Comparator::Object - a callback type for comparation

=head1 SYNOPSYS
  
  use SPVM::Comparator::Object;
  
  my $comparator : SPVM::Comparator::Object = sub : int ($self : self, $object1 : object, $object2 : object); {
    my $point1 = (SPVM::Point)$object1;
    my $point2 = (SPVM::Point)$object2;
    
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
  
  my $point1 = SPVM::Point->new(1, 2);
  my $point2 = SPVM::Point->new(5, 6);
  my $result = $comparator->($point1, $point2);

=head1 DESCRIPTION

L<SPVM::Comparator::Object> is a callback type to compare objects.

=head1 CALLBACK METHOD

  sub : int ($self : self, $object1 : object, $object2 : object);

This method should receive two objects and return 1 if $object1 is more than $object2, -1 if $x is lass than $object2, 0 if $object1 equals $object2 in the implementation.
