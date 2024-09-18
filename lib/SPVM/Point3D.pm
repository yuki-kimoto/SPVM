package SPVM::Point3D;

1;

=head1 Name

SPVM::Point3D - Point 3D

=head1 Usage

  use Point3D;
  
  my $point = Point3D->new;
  my $point = Point3D->new(1, 2, 3);

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

  has z : ro int;

C<z>.

=head1 Class Methods

=head2 new

C<static method new : L<Point3D|SPVM::Point3D> ($x : int = 0, $y : int = 0, $z : int = 0);>

Creates a new C<Point3D> object with $x, $y, $z.

=head1 Instance Methods

C<Point3D> inherits the instance methods of L<Point|SPVM::Point/"Instance Methods">.

=head2 init

  protected method init : Point3D ($x : int = 0, $y : int = 0, $z : int = 0)

Initializes L</"x">, L</"y">, and L</"z">.

=head2 clear

C<method clear : void ();>

Sets L<x|SPVM::Point/"x">, L<y|SPVM::Point/"y">, and L</"z"> to 0.

=head2 clone

C<method clone : L<Point3D|SPVM::Point3D> ();>

Creates a new C<Point3D> object that clones myself.

=head2 to_string

C<method to_string : string ();>

Stringifies C<Point3D> object as the following format.

  (1,2,3)

=head2 eq

C<method eq : int ($a : Point, $b : Point);>

If $a is equal to $b, returns 1, otherwise returns 0.

Implementation:

If $a and $b is defined and L</"x"> and L</"y"> fields in $a are equals to L</"x"> and L</"y"> fields in $b, returns 1.

If only $a is not defined, returns 0.

If only $b is not defined, returns 0.

If both $a and $b is not defined, returns 1.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
