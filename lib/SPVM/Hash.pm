package SPVM::Hash;

1;

=head1 Name

SPVM::Hash - Hash (Associative Array)

=head1 Description

The Hash class of L<SPVM> has methods to manipulate hashes(associative arrays).

=head1 Usage
  
  use Hash;
  
  my $book = Hash->new;
  my $book = Hash->new({});
  my $book = Hash->new({id => 4, name => "Perl", price => 3000.0});
  
  $book->set_int(id => 4);
  $book->set_string(name => "Perl");
  $book->set_double(price => 3000.0);
  $book->set(point => Point->new(1, 2));
  
  my $id = $book->get_int("id");
  my $name = $book->get_string("name");
  my $price = $book->get_double("price");
  my $point = $book->get("point");

=head2 Details

The hash function is C<siphash-1-3>.

=head1 Interfaces

=over 2

=item * L<Cloneable|SPVM::Cloneable>

=back

=hdead1 Fields

=head2 keys_length

  has keys_length : ro int;

The length of the keys in the hash.

=head1 Class Methods

=head2 new

  static method new : Hash ($key_values : object[] = undef);

Creates a new L<Hash|SPVM::Hash> object given key-value pairs $key_values.

Examples:

  my $book = Hash->new;
  my $book = Hash->new({});
  my $book = Hash->new({id => 4, name => "Perl"});

=head1 Instance Methods

=head2 copy

  method copy : Hash ();

Creates a new L<Hash|SPVM::Hash> object, and copies the keys and values of the current hash to the new hash, and returns it.

This is not deep copy. The keys are got by the L</"keys"> method. The values are got by the L</"get"> method.

=head2 clone

   method clone : Hash ();

The alias for the L</"copy">.

=head2 delete

  method delete : object ($key : string);

Deletes a key value pair. Deleted value is returned.

=head2 exists

  method exists : int ($key : string);

Specify the key and check if the value exists. If exists, return 1, otherwise 0.

=head2 keys

  method keys : string[] ();

Gets keys. This method do not copy the strings.

=head2 values

  method values : object[] ();

Gets all the values contained in this hash.

=head2 get

  method get : object ($key : string);

Gets the value corresponding to key $key, and returns it.

=head2 get_byte

  method get_byte : int ($key : string);

Gets the value corresponding to key $key, and casts it to the byte type, and returns it as the int type.

Exceptions:

The value of the $key must be a L<Byte|SPVM::Byte> object. Otherwise an exception is thrown.

=head2 get_short

  method get_short : int ($key : string);

Gets the value corresponding to key $key, and casts it to the short type, and returns it as the int type.

Exceptions:

The value of the $key must be a L<Short|SPVM::Short> object. Otherwise an exception is thrown.

=head2 get_string

  method get_string : string ($key : string)

Gets the value corresponding to key $key, and casts it to the string type, and returns it.

Exceptions:

The value of the $key must be a string. Otherwise an exception is thrown.

=head2 get_int

  method get_int : int ($key : string);

Gets the value corresponding to key $key, and casts it to the int type, and returns it.

Exceptions:

The value of the $key must be a L<Int|SPVM::Int> object. Otherwise an exception is thrown.

=head2 get_long

  method get_long : long ($key : string);

Gets the value corresponding to key $key, and casts it to the long type, and returns it.

Exceptions:

The value of the $key must be a L<Long|SPVM::Long> object. Otherwise an exception is thrown.

=head2 get_float

  method get_float : float ($key : string);

Gets the value corresponding to key $key, and casts it to the float type, and returns it.

Exceptions:

The value of the $key must be a L<Float|SPVM::Float> object. Otherwise an exception is thrown.

=head2 get_double

  method get_double : double ($key : string);

Gets the value corresponding to key $key, and casts it to the double type, and returns it.

Exceptions:

The value of the $key must be a L<Double|SPVM::Double> object. Otherwise an exception is thrown.

=head2 set
  
  method set : void ($key : string, $val : object);

Sets the object $value with the $key.

=head2 set_byte

  method set_byte : void ($key : string, $value : int);

Sets the C<byte> $value with the $key. the $value is converted to L<Byte|SPVM::Byte> object.

=head2 set_short

  method set_short : void ($key : string, $value : int);

Sets the C<short> $value with the $key. the $value is converted to L<Short|SPVM::Short> object.

=head2 set_int

  method set_int : void ($key : string, $value : int);

Sets the C<int> $value with the $key. the $value is converted to L<Int|SPVM::Int> object.

=head2 set_long

  method set_long : void ($key : string, $value : long);

Sets the C<long> $value with the $key. the $value is converted to L<Long|SPVM::Long> object.

=head2 set_float

  method set_float : void ($key : string, $value : float);

Sets the C<float> $value with the $key. the $value is converted to L<Float|SPVM::Float> object.

=head2 set_double

  method set_double : void ($key : string, $value : double);

Sets the C<double> $value with the $key. the $value is converted to L<Double|SPVM::Double> object.

=head2 set_string

  method set_string : void ($key : string, $value : string);

Sets the string $value with the $key.

=head2 to_array

  method to_array : object[] ($sort : int = 0);

Converts the hash to an array.

If $sort is a true value, the keys are sorted by the asc order.

=head2 delete_or_default_byte

  method delete_or_default_byte : int ($key : string, $default : int) {

If the $key exists, the value is deleted and returned with the type cast to C<byte> type.

If not, the $default value with the type cast to C<byte> type is returned.

=head2 delete_or_default_short

  method delete_or_default_short : int ($key : string, $default : int) {

If the $key exists, the value is deleted and returned with the type cast to C<short> type.

If not, the $default value with the type cast to C<short> type is returned.

=head2 delete_or_default_int

  method delete_or_default_int : int ($key : string, $default : int) {

If the $key exists, the value is deleted and returned with the type cast to C<int> type.

If not, the $default value is returned.

=head2 delete_or_default_long

  method delete_or_default_long : long ($key : string, $default : long) {

If the $key exists, the value is deleted and returned with the type cast to C<long> type.

If not, the $default value is returned.

=head2 delete_or_default_float

  method delete_or_default_float : float ($key : string, $default : float) {

If the $key exists, the value is deleted and returned with the type cast to C<float> type.

If not, the $default value is returned.

=head2 delete_or_default_double

  method delete_or_default_double : double ($key : string, $default : double) {

If the $key exists, the value is deleted and returned with the type cast to C<double> type.

If not, the $default value is returned.

=head2 delete_or_default_string

  method delete_or_default_string : string ($key : string, $default : string) {

If the $key exists, the value is deleted and returned with the type cast to C<string> type.

If not, the $default value is returned.

=head2 delete_or_default

  method delete_or_default : object ($key : string, $default : object) {

If the $key exists, the value is deleted and returned.

If not, the $default value is returned.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
