package SPVM::Short;

1;

=head1 Name

SPVM::Short - Short Class

=head1 Usage
  
  my $short_object = Short->new(5);
  my $short_value = $short_object->value;
  $short_object->set_value(10);

=head1 Description

C<Short> is the class to hold a value of the C<short> type.

This class is automatically loaded.

=head1 Fields

=head2 value

  has value : rw short;

The value.

=head1 Class Methods

=head2 new

  static method new : Short ($value : int);

Creates a new L<Short|SPVM::Short> object with a C<short> C<$value>.
