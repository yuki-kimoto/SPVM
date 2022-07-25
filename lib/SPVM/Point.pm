package SPVM::Point;

1;

=head1 Name

SPVM::Point - Point

=head1 Usage

  use Point;
  
  my $point = Point->new;
  my $point = Point->new_xy(1, 2);

  $point->set_x(1);
  $point->set_y(2);
  
  my $x = $point->x;
  my $y = $point->y;
  
  my $point_string = $point->to_string;

=head1 Description

C<Point> is a class for a point.

=head1 Interfaces

C<Point> class has the following interfaces.

=over 2

=item * L<Stringable|SPVM::Stringable>

=item * L<Cloneable|SPVM::Cloneable>

=back

=head1 Fields

=head2 x

  has x : rw int;

C<x>.

=head2 y

  has y : rw int;

C<y>.

=head1 Class Methods

=head2 new

  method new : Point ()

Create a new C<Point> object.

=head2 new_xy

  method new_xy : Point ($x : int, $y : int)

Create a new C<Point> object with L</"x"> and L</"y">.

=head1 Instance Methods

=head2 clear

  method clear : void ()

Set L</"x"> and L</"y"> to C<0>.

=head2 cloneable_clone

  method cloneable_clone : object ()

Create a new C<Point> object that clones myself.

=head2 to_string

  method to_string : string ();

Stringify the C<Point> object as the following format.

  (1,2)
