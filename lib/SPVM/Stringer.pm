package SPVM::Stringer;

1;

=head1 Name

SPVM::Stringer -  Interface Type for Stringing Callback

=head1 Usage
  
  use Stringer;
  use Point;
  
  my $stringer = (Stringer)method : string ($object : object) {
    my $point = (Point)$object;

    my $string = $point->to_string;
    
    return $string;
  };
  
  my $point = Point->new_xy(1, 2);
  my $string = $stringer->($point);

=head1 Description

L<Stringer|SPVM::Stringer> is the interface type for the stringing callback.

=head1 Interface Methods

  required method : string ($object : object)

The implementation must receive a object and return the string that represents the object.
