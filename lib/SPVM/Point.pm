package SPVM::Point;

1;

=head1 NAME

SPVM::Point - Point object

=head1 SYNOPSYS
  
  use Point;
  
  my $point = Point->new;
  my $point = Point->new_xy(1, 2);

  $point->set_x(1);
  $point->set_y(2);
  
  my $x = $point->x;
  my $y = $point->y;

=head1 DESCRIPTION

L<Point|SPVM::Point> object represents a point.

=head1 CLASS METHODS

=head2 new

  method new : Point ()

Create a new C<Point> object.

=head2 new_xy

  method new_xy : Point ($x : int, $y : int);

Create a new C<Point> object with x and y.

=head1 INSTANCE METHODS

=head2 x

  method x : int ()

Get C<x> field.

=head2 set_x

  void set_x : int ($x : int)

Set C<x> field.

=head2 y

  method y : int ();

Get C<y> field.

=head2 set_y

  void set_y : int ($y : int)

Set C<y> field.
