package SPVM::Cloner;

1;

=head1 Name

SPVM::Cloner - Interface Type for the Callback to Clone a Object

=head1 Usage
  
  use Cloner;
  use Point;
  
  my $cloner = (Cloner)method : object ($object : object) {
    my $point = (Point)$object;
    
    my $cloned_point = Point->new($point->x, $point->y);
    
    return $cloned_point;
  };
  
  my $point = Point->new(1, 2);
  my $cloned_point = $cloner->($point);

=head1 Description

L<Cloner|SPVM::Cloner> is the interface type for the callback to clone an object.

=head1 Interface Methodss

C<required method : object ($object : object);>

The implementation must receive an object and return the cloned object.

=head1 Class Methods

C<static method default_cloner : L<Cloner|SPVM::Cloner> ();>

Returns a default cloner.

The implementation of the default cloner is

  method : object ($object : Cloneable) {
  
    my $clone = (object)undef;
    
    if ($object) {
      $clone = $object->clone;
    }
    
    return $clone;
  };

If the object $object is undef, returns undef, ohterwise calls L<Cloneable#clone|SPVM::Cloneable/"clone"> method and its return value.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
