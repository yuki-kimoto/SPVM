package SPVM::Point;

1;

=head1 Name

SPVM::Point - Point

=head1 Usage

  use Point;
  
  my $point = Point->new;
  my $point = Point->new(1, 2);

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

=item * L<Cloneable|SPVM::Point::Interface>

=back

=head1 Fields

=head2 x

  has x : rw protected int;

C<x>.

=head2 y

  has y : rw protected int;

C<y>.

=head1 Class Methods

=head2 new

  static method new : Point ($x = 0 : int, $y = 0 : int)

Create a new C<Point> object with L</"x"> and L</"y">.

=head1 Instance Methods

=head2 init

  protected method init : Point ($x = 0 : int, $y = 0 : int)

Initialize L</"x"> and L</"y">.

=head2 has_interfaces

  method has_interfaces : int ();

Return C<1>.

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
