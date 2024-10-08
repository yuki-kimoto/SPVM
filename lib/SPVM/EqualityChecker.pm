package SPVM::EqualityChecker;

1;

=head1 Name

SPVM::EqualityChecker - Interface Type for Object Equality Checking Callback

=head1 Usage
  
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
  
  my $point1 = Point->new(1, 2);
  my $point2 = Point->new(5, 6);
  
  my $is_equal = $equality_checker->($point1, $point2);

=head1 Description

L<EqualityChecker|SPVM::EqualityChecker> is the interface type for the object equality checking callback.

=head1 Interface Methods

C<required method : int ($object1 : object, $object2 : object)>

The implementation must receive two objects and if they are equal, return 1. Otherwise, return 0.

=head1 Class Methods

=head2 default_equality_checker

C<static method default_equality_checker : L<EqualityChecker|SPVM::EqualityChecker> ();>

Returns a default default equality checker.

The implementation of the default equality checker is

  method : int ($object1 : EqualityCheckable, $object2 : EqualityCheckable) {
    
    my $eq = 0;
    if ($object1 && $object2) {
      $eq = $object1->eq($object1, $object2);
    }
    elsif ($object1) {
      $eq = 0;
    }
    elsif ($object2) {
      $eq = 0;
    }
    else {
      $eq = 1;
    }
    
    return $eq;
  };

If $object1 and $object2 are defined, the check of equality is perfermed by L<EqualityCheckable#eq|SPVM::EqualityCheckable/"eq"> method in the class of $object1, and returns its return value.

If only $object1 is defined, returns 0.

If only $object2 is defined, returns 0.

If both $object1 and $object2 are not defined, returns 1.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
