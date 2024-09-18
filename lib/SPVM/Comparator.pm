package SPVM::Comparator;

1;

=head1 Name

SPVM::Comparator - Interface Type for Object Comparation Callback

=head1 Usage
  
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
  
  my $point1 = Point->new(1, 2);
  my $point2 = Point->new(5, 6);
  my $result = $comparator->($point1, $point2);

=head1 Description

C<Comparator> is the interface type for the object comparation callback.

=head1 Interface Methods

C<required method : int ($object1 : object, $object2 : object);>

This method must receive two objects and return the following value.

If the first argument is greater than the second argument, returns 1. If the first argument is lower than the second argument, returns -1. If the first argument is equal to the second argument, returns 0.

=head1 Class Methods

=head2 default_comparator

C<static method default_comparator : L<Comparator|SPVM::Comparator> ();>

Returns a default comparator.

The implementation of the default comparator is

  method : int ($object1 : Comparable, $object2 : Comparable) {
      
      my $cmp = 0;
      if ($object1 && $object2) {
        $cmp = $object1->cmp($object1, $object2);
      }
      elsif ($object1) {
        $cmp = 1;
      }
      elsif ($object2 ) {
        $cmp = -1;
      }
      
      return $cmp;
    }
    
    return $default_comparator;
  }

If $object1 and $object2 are defined, the comparison is perfermed by L<Comparable#cmp|SPVM::Comparable/"cmp"> method in the class of $object1, and returns its return value.

If only $object1 is defined, returns 1.

If only $object2 is defined, returns -1.

If both $object1 and $object2 are not defined, returns 0.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
