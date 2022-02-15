package SPVM::Cloneable;

1;

=head1 NAME

SPVM::Cloneable - A Interface Type to Clone a Object

=head1 SYNOPSYS
  
  class Point {
    implement Cloneable;
    
    method clone : object ($object : object) {
      my $point = (Point)$object;
      
      my $new_point = Point->new($point->x, $point->y);
      
      return $new_point;
    }
  }

=head1 DESCRIPTION

L<Cloneable|SPVM::Cloneable> is a callback interface to clone a object.

=head1 INTERFACE METHODS

Interface methods.

=head2 clone

  method clone : object ($object : object);

The implementation must receive a object and return the cloned object.
