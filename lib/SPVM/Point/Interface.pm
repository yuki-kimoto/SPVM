package SPVM::Point::Interface;

1;

=head1 Name

SPVM::Point::Interface - Point Interface

=head1 Usage
  
  use Point;
  use Point3D;
  use Point::Interface;
  
  my $point = (Point)Point3D->new;
  
  my $point_interface = $point;
  
  $point_interface->clear;

=head1 Description

C<Point::Interface> is a class for has_interfaces classes.

=head1 Instance Methods

=head2 has_interfaces

  required method has_interfaces : int ();

This class has some interfaces.

=head2 clear

  method clear : void ();

Clear the coordinates.
