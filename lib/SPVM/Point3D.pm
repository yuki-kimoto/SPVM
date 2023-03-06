package SPVM::Point3D;

1;

=head1 Name

SPVM::Point3D - Point 3D

=head1 Usage

  use Point3D;
  
  my $point = Point3D->new;
  my $point = Point3D->new(1, 2, 3);

  $point->set_x(1);
  $point->set_y(2);
  $point->set_z(3);
  
  my $x = $point->x;
  my $y = $point->y;
  my $z = $point->z;
  
  my $point_string = $point->to_string;

=head1 Description

C<Point3D> is a class for a point 3D.

=head1 Super Class

L<Point|SPVM::Point> is the super class of C<Point3D>.

=head1 Fields

C<Point3D> inherits the fields of L<Point|SPVM::Point/"Fields">.

=head2 z

  has z : rw protected int;

C<z>.

=head1 Class Methods

=head2 new

  static method new : Point3D ($x = 0 : int, $y = 0 : int, $z = 0 : int);

Creates a new C<Point3D> object with $x, $y, $z.

=head1 Instance Methods

C<Point3D> inherits the instance methods of L<Point|SPVM::Point/"Instance Methods">.

=head2 init

  protected method init : Point3D ($x = 0 : int, $y = 0 : int, $z = 0 : int)

Initializes L</"x">, L</"y">, and L</"z">.

=head2 clear

  method clear : void ();

Sets L<x|SPVM::Point/"x">, L<y|SPVM::Point/"y">, and L</"z"> to C<0>.

=head2 clone

  method clone : Point3D ();

Creates a new C<Point3D> object that clones myself.

=head2 to_string

  method to_string : string ();

Stringifies the C<Point3D> object as the following format.

  (1,2,3)

