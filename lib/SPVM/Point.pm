package SPVM::Point;

1;

=head1 Name

SPVM::Point - Point

=head1 Usage

  use Point;
  
  my $point = Point->new;
  my $point = Point->new(1, 2);

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

  has x : ro int;

C<x>.

=head2 y

  has y : ro int;

C<y>.

=head1 Class Methods

=head2 new

  static method new : Point ($x : int = 0, $y : int = 0);

Create a new C<Point> object with $x and $y.

=head1 Instance Methods

=head2 init

  protected method init : Point ($x : int = 0, $y : int = 0)

Initializes L</"x"> and L</"y">.

=head2 clear

  method clear : void ();

Sets L</"x"> and L</"y"> to 0.

=head2 clone

  method clone : Point ();

Creates a new C<Point> object that clones myself.

=head2 to_string

  method to_string : string ();

Stringifies the C<Point> object as the following format.

  (1,2)

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
