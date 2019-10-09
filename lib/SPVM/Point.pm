package SPVM::Point;

use SPVM 'SPVM::Point';

1;

=head1 NAME

SPVM::Point - a example class for easy description

=head1 SYNOPSYS
  
  use SPVM::Point;
  
  my $point = SPVM::Point->new(1, 2);
  my $x = $point->x;
  my $y = $point->y;

=head1 DESCRIPTION

L<SPVM::Point> is a example class for easy description.

=head1 CLASS METHODS

  sub new : SPVM::Point ($x : int, $y : int)

Create a new L<SPVM::Point> object.

=head1 INSTANCE METHODS

=head2 x

  sub x : int ()

Get x value.

=head2 y

  sub y : int ()

Get y value.
