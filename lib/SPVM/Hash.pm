package SPVM::Hash;

1;

=head1 Name

SPVM::Hash - Hash Data Structure

=head1 Usage
  
  use Hash;
  
  # Create hash
  my $book = Hash->new;
  my $book = Hash->new({});
  my $book = Hash->new({id => 4, name => "Perl", price => 3000.0});
  
  $book->set_int(id => 4);
  $book->set_string(name => "Perl");
  $book->set_double(price => 3000.0);
  
  my $id = (int)$book->get_int("id");
  my $key = (string)$book->get_string("name");
  my $price = (double)$book->get_double("price");
  
=head1 Description

C<Hash> is Hash Data Structure. This is generally called associative array.

The hash function is C<siphash-1-3>.

=head1 Interfaces

=over 2

=item * L<Cloneable|SPVM::Cloneable>

=back

=head1 Class Methods

=head2 new

  static method new : Hash ($key_values = undef : object[]);

Create a new L<Hash|SPVM::Hash> object with key value pairs.

  my $book = Hash->new;
  my $book = Hash->new({});
  my $book = Hash->new({id => 4, name => "Perl"});

=head1 Instance Methods

=head2 count

  count : int ()

Counts keys in the hash.

=head2 copy

  copy : Hash ()

Copies hash.

This is not deep copy. Address of keys and values is copied into new hash.

=head2 clone

   method clone : Hash ();

The alias for the L</"copy">.

=head2 delete

  delete : object ($key : string)

Deletes a key value pair. Deleted value is returned.

=head2 exists

  exists : int ($key : string)

Specify the key and check if the value exists. If exists, return 1, otherwise 0.

=head2 keys

  keys : string[] ()

Gets keys. This method do not copy the strings.

=head2 values

  values : object[] ()

Gets values.

=head2 get

  get : object ($key : string)

Gets a value.

=head2 get_byte

  get_byte : int ($key : string)

Gets the value with a C<$key> from a L<Byte|SPVM::Byte> object.

=head2 get_short

  get_short : int ($key : string)

Gets the value with a C<$key> from a L<Short|SPVM::Short> object.
  
=head2 get_int

  get_int : int ($key : string)

Gets the value with a C<$key> from a L<Int|SPVM::Int> object.
  
=head2 get_long

  get_long : long ($key : string)

Gets the value with a C<$key> from a L<Long|SPVM::Long> object.

=head2 get_float

  get_float : float ($key : string)

Gets the value with a C<$key> from a L<Float|SPVM::Float> object.
  
=head2 get_double

  get_double : double ($key : string)

Gets the value with a C<$key> from a L<Double|SPVM::Double> object.

=head2 set
  
  set : void ($key : string, $val : object)

Sets the object C<$value> with the C<$key>.

=head2 set_byte

  set_byte : void ($key : string, $value : int)

Sets the C<byte> C<$value> with the C<$key>. the C<$value> is converted to L<Byte|SPVM::Byte> object.

=head2 set_short

  set_short : void ($key : string, $value : int)

Sets the C<short> C<$value> with the C<$key>. the C<$value> is converted to L<Short|SPVM::Short> object.

=head2 set_int

  set_int : void ($key : string, $value : int)

Sets the C<int> C<$value> with the C<$key>. the C<$value> is converted to L<Int|SPVM::Int> object.

=head2 set_long

  set_long : void ($key : string, $value : long)

Sets the C<long> C<$value> with the C<$key>. the C<$value> is converted to L<Long|SPVM::Long> object.

=head2 set_float

  set_float : void ($key : string, $value : float)

Sets the C<float> C<$value> with the C<$key>. the C<$value> is converted to L<Float|SPVM::Float> object.

=head2 set_double

  set_double : void ($key : string, $value : double)

Sets the C<double> C<$value> with the C<$key>. the C<$value> is converted to L<Double|SPVM::Double> object.

=head2 set_string

  set_string : void ($key : string, $value : string)

Sets the string C<$value> with the C<$key>.
