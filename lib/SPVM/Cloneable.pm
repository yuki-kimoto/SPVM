package SPVM::Cloneable;

1;

=head1 NAME

SPVM::Cloneable - A Interface Type to Clone a Object

=head1 SYNOPSYS
  
  class Point {
    interface Cloneable;
    
    method cloneable_clone : object () {
      my $new_point = Point->new($self->x, $self->y);
      
      return $new_point;
    }
  }

=head1 DESCRIPTION

L<Cloneable|SPVM::Cloneable> is a callback interface to clone a object.

=head1 INTERFACE METHODS

Interface methods.

=head2 cloneable_clone

  method cloneable_clone : object ();

The implementation must return the cloned object.
