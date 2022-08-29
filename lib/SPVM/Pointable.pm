package SPVM::Pointable;

1;

=head1 Name

SPVM::Pointable - Pointable

=head1 Usage
  
  use Point3D;
  use Pointable;
  
  my $point3d = Point3D->new;
  
  my $pointable = $point3d;
  
  $pointable->clear;

=head1 Description

C<Pointable> is a class for pointable classes.

=head1 Instance Methods

=head2 pointable

  required method pointable : int ();

This is L<Pointable|SPVM::Pointable> object.

=head2 clear

  method clear : void ()

Clear the coordinates.
