package SPVM::Point3D;

1;

=head1 Name

SPVM::Point3D - Point 3D

=head1 Synopsys

  use Point3D;
  
  my $point = Point3D->new;
  my $point = Point3D->new_xyz(1, 2, 3);

  $point->set_x(1);
  $point->set_y(2);
  $point->set_z(3);
  
  my $x = $point->x;
  my $y = $point->y;
  my $y = $point->z;
  
  my $point_string = $point->to_string;

=head1 Description

C<Point3D> is a class for a point 3D.

=head1 Super Class

L<Point|SPVM::Point> is the super class of C<Point3D>.

=head1 Interfaces

C<Point3D> inherits the interfaces of L<Point|SPVM::Point>.

=head1 Class Methods

=head2 new

  method new : Point3D ()

Create a new C<Point3D> object.

=head2 new_xyz

  method new_xyz : Point3D ($x : int, $y : int, $z : int)

Create a new C<Point3D> object with x, y, and z.

=head1 Instance Methods

C<Point3D> inherits the methods of L<Point|SPVM::Point>, and implements the following methods.

=head2 z

  method z : int ()

Get C<z> field.

=head2 set_z

  void set_z : int ($z : int)

Set C<x> field.

=head2 to_string

  method to_string : string ();

Convert the C<Point3D> object to a string as the following.

  (1,2,3)

=head2 cloneable_clone

  method cloneable_clone : object ()

Clone a C<Point3D> object by create a new C<Point3D> object and C<x>, C<y>, C<z> fields are copied to the new object.
