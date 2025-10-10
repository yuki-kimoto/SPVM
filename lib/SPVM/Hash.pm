package SPVM::Hash;

1;

=head1 Name

SPVM::Hash - Hash (Associative Array)

=head1 Description

The Hash class of L<SPVM> has methods to manipulate hashes(associative arrays).

=head1 Usage
  
  use Hash;
  
  my $book = Hash->new;
  my $book = Hash->new({id => 4, name => "Perl", price => 3000.0});
  
  $book->set_int(id => 4);
  $book->set_string(name => "Perl");
  $book->set_double(price => 3000.0);
  $book->set(point => Point->new(1, 2));
  
  my $id = $book->get("id")->(int);
  my $name = $book->get("name")->(string);
  my $price = $book->get("price")->(double);
  my $point = $book->get("point")->(Point);
  
  # Use hash access syntax
  $book->{"id"} = 4;
  $book->{"name"} = "Perl";
  $book->{"price"} = 3000.0;
  $book->{"point"} = Point->new(1, 2);
  
  my $id = $book->{"id"}->(int);
  my $name = $book->{"name"}->(string);
  my $price = $book->{"price"}->(double);
  my $point = $book->{"point"}->(Point);
  
=head1 Details

The hash function is C<siphash-1-3>.

=head1 Interfaces

=over 2

=item * L<Cloneable|SPVM::Cloneable>

=back

=head1 Fields

=head2 keys_length

  has keys_length : ro int;

The length of the keys in the hash.

=head1 Class Methods

=head2 new

C<static method new : L<Hash|SPVM::Hash> ($key_values : object[] = undef);>

Creates a new L<Hash|SPVM::Hash> object given key-value pairs $key_values.

Examples:

  my $book = Hash->new;
  my $book = Hash->new({});
  my $book = Hash->new({id => 4, name => "Perl"});

=head2 new_from_keys

C<static method new_from_keys : void ($keys : string[], $value : object);>

Creates a new hash with the keys $keys and the value $value shared by all keys, and returns the new hash.

Exceptions:

The keys $keys must be defined. Otherwise an exception is thrown.

=head1 Instance Methods

=head2 copy

C<method copy : L<Hash|SPVM::Hash> ();>

Creates a new L<Hash|SPVM::Hash> object, and copies the keys and values of the current hash to the new hash, and returns it.

This is not deep copy. The keys are got by L</"keys"> method. The values are got by L</"get"> method.

=head2 clone

C<method clone : L<Hash|SPVM::Hash> ();>

The alias for L</"copy"> method.

=head2 delete

C<method delete : element ($key : string);>

Deletes the key and value given by the key $key.

The deleted value is returned.

Exceptions:

The key $key must be defined. Otherwise, an exception is thrown.

=head2 exists

C<method exists : int ($key : string);>

Checks if the value specified by the key $key exists. If it exists, returns 1. Otherwise returns 0.

=head2 keys

C<method keys : string[] ();>

Gets the keys in the hash. This method does not copy the strings.

=head2 values

C<method values : object[] ();>

Gets all the values in the hash.

=head2 get

C<method get : element ($key : string);>

Gets the value specifed by the key $key, and returns it.

If the value does not exist, returns undef.

Exceptions:

The key $key must be defined. Otherwise, an exception is thrown.

=head2 weaken

C<method weaken : void ($key : string));>

Enables a weaken reference of the field that stores the value specifed by the key $key if the value exists.

Exceptions:

The key $key must be defined. Otherwise, an exception is thrown.

=head2 unweaken

C<method unweaken : void ($key : string);>

Disables a weaken reference of the field that stores the value specifed by the key $key if the value exists.

Exceptions:

The key $key must be defined. Otherwise, an exception is thrown.

=head2 isweak

C<method isweak : int ($key : string)>

If the field that stores the value specifed by the key $key is weakened, returns 1, otherwise returns 0.

Exceptions:

The key $key must be defined. Otherwise, an exception is thrown.

=head2 get_byte

C<method get_byte : int ($key : string);>

Gets the value specifed by the key $key using the L<"get"> method, and casts it to byte type, and casts it to int type, and returns it.

Exceptions:

The type of the value for the key must be L<Byte|SPVM::Byte>. Otherwise, an exception is thrown.

=head2 get_short

C<method get_short : int ($key : string);>

Gets the value specifed by the key $key using the L<"get"> method, and casts it to int value, and returns it.

Exceptions:

The type of the value for the key must be L<Short|SPVM::Short> or L<Byte|SPVM::Byte>. Otherwise, an exception is thrown.

=head2 get_int

C<method get_int : int ($key : string);>

Gets the value specifed by the key $key using the L<"get"> method, and casts it to int value, and returns it.

Exceptions:

The type of the value for the key must be L<Int|SPVM::Int>, L<Short|SPVM::Short>, or L<Byte|SPVM::Byte>. Otherwise, an exception is thrown.

=head2 get_long

C<method get_long : long ($key : string);>

Gets the value specifed by the key $key using the L<"get"> method, and casts it to long value, and returns it.

Exceptions:

The type of the value for the key must be L<Long|SPVM::Long>, L<Int|SPVM::Int>, L<Short|SPVM::Short>, or L<Byte|SPVM::Byte>. Otherwise, an exception is thrown.

=head2 get_float

C<method get_float : float ($key : string);>

Gets the value specifed by the key $key using the L<"get"> method, and casts it to float type, and returns it.

Exceptions:

The type of the value for the key must be L<Float|SPVM::Float>. Otherwise, an exception is thrown.

=head2 get_double

C<method get_double : double ($key : string);>

Gets the value specifed by the key $key using the L<"get"> method, and casts it to double type, and returns it.

Exceptions:

The type of the value for the key must be L<Double|SPVM::Double>. Otherwise, an exception is thrown.

=head2 get_string

C<method get_string : string ($key : string)>

Gets the value specifed by the key $key using the L<"get"> method, and casts it to string type, and returns it.

Exceptions:

The type of the value for the key must be string type. Otherwise, an exception is thrown.

=head2 set
  
C<method set : void ($key : string, $value : object);>

Sets $value to the hash by the key $key.

Exceptions:

The key $key must be defined. Otherwise, an exception is thrown.

=head2 set_byte

C<method set_byte : void ($key : string, $value : int);>

The value $value is converted to a L<Byte|SPVM::Byte> object, and sets it to the hash by the key $key using the L<"set"> method. 

=head2 set_short

C<method set_short : void ($key : string, $value : int);>

The value $value is converted to a L<Short|SPVM::Short> object, and sets it to the hash by the key $key using the L<"set"> method. 

=head2 set_int

C<method set_int : void ($key : string, $value : int);>

The value $value is converted to an L<Int|SPVM::Int> object, and sets it to the hash by the key $key using the L<"set"> method.  

=head2 set_long

C<method set_long : void ($key : string, $value : long);>

The value $value is converted to a L<Long|SPVM::Long> object, and sets it to the hash by the key $key using the L<"set"> method. 

=head2 set_float

C<method set_float : void ($key : string, $value : float);>

The value $value is converted to a L<Float|SPVM::Float> object, and sets it to the hash by the key $key using the L<"set"> method. 

=head2 set_double

C<method set_double : void ($key : string, $value : double);>

The value $value is converted to a L<Double|SPVM::Double> object, and sets it to the hash by the key $key using the L<"set"> method. 

=head2 set_string

C<method set_string : void ($key : string, $value : string);>

Sets the string $value to the hash by the key $key using the L<"set"> method. 

=head2 to_array

C<method to_array : object[] ($sort : int = 0);>

Converts all the key-value pairs in the hash to an array, and returns it.

If the option $sort is a positive value, the keys are sorted by ascendant order.

If the option $sort is a negative value, the keys are sorted by decendant order.

=head2 to_options

C<method to_options : object[] ($sort : int = 0);>

Same as L</"to_array"> method, but enables options flag using C<enable_options> operator.

=head2 get_or_default_byte

C<method get_or_default_byte : int ($key : string, $default : int;>

If the value specified by the key $key exists, this method calls L</"get_byte"> method
, and returns the return value of L</"get_byte"> method.

If the value specified by the key $key does not exists, returns the default value $default.

=head2 get_or_default_short

C<method get_or_default_short : int ($key : string, $default : int;>

If the value specified by the key $key exists, this method calls L</"get_short"> method
, and returns the return value of L</"get_short"> method.

If the value specified by the key $key does not exists, returns the default value $default.

=head2 get_or_default_int

C<method get_or_default_int : int ($key : string, $default : int;>

If the value specified by the key $key exists, this method calls L</"get_int"> method
, and returns the return value of L</"get_int"> method.

If the value specified by the key $key does not exists, returns the default value $default.

=head2 get_or_default_long

C<method get_or_default_long : long ($key : string, $default : long;>

If the value specified by the key $key exists, this method calls L</"get_long"> method
, and returns the return value of L</"get_long"> method.

If the value specified by the key $key does not exists, returns the default value $default.

=head2 get_or_default_float

C<method get_or_default_float : float ($key : string, $default : float;>

If the value specified by the key $key exists, this method calls L</"get_float"> method
, and returns the return value of L</"get_float"> method.

If the value specified by the key $key does not exists, returns the default value $default.

=head2 get_or_default_double

C<method get_or_default_double : double ($key : string, $default : double;>

If the value specified by the key $key exists, this method calls L</"get_double"> method
, and returns the return value of L</"get_double"> method.

If the value specified by the key $key does not exists, returns the default value $default.

=head2 get_or_default_string

C<method get_or_default_string : string ($key : string, $default : string;>

If the value specified by the key $key exists, this method calls L</"get_string"> method
, and returns the return value of L</"get_string"> method.

If the value specified by the key $key does not exists, returns the default value $default.

=head2 get_or_default

C<method get_or_default : element ($key : string, $default : object;>

If the value specified by the key $key exists, this method calls L</"get"> method
, and returns the return value of L</"get"> method.

If the value specified by the key $key does not exists, returns the default value $default.

=head2 delete_or_default_byte

C<method delete_or_default_byte : int ($key : string, $default : int;>

If the value specified by the key $key exists, this method calls L</"get_byte"> method
and L</"delete"> method, and returns the return value of L</"get_byte"> method.

If the value specified by the key $key does not exists, returns the default value $default.

=head2 delete_or_default_short

C<method delete_or_default_short : int ($key : string, $default : int;>

If the value specified by the key $key exists, this method calls L</"get_short"> method
and L</"delete"> method, and returns the return value of L</"get_short"> method.

If the value specified by the key $key does not exists, returns the default value $default.

=head2 delete_or_default_int

C<method delete_or_default_int : int ($key : string, $default : int;>

If the value specified by the key $key exists, this method calls L</"get_int"> method
and L</"delete"> method, and returns the return value of L</"get_int"> method.

If the value specified by the key $key does not exists, returns the default value $default.

=head2 delete_or_default_long

C<method delete_or_default_long : long ($key : string, $default : long;>

If the value specified by the key $key exists, this method calls L</"get_long"> method
and L</"delete"> method, and returns the return value of L</"get_long"> method.

If the value specified by the key $key does not exists, returns the default value $default.

=head2 delete_or_default_float

C<method delete_or_default_float : float ($key : string, $default : float;>

If the value specified by the key $key exists, this method calls L</"get_float"> method
and L</"delete"> method, and returns the return value of L</"get_float"> method.

If the value specified by the key $key does not exists, returns the default value $default.

=head2 delete_or_default_double

C<method delete_or_default_double : double ($key : string, $default : double;>

If the value specified by the key $key exists, this method calls L</"get_double"> method
and L</"delete"> method, and returns the return value of L</"get_double"> method.

If the value specified by the key $key does not exists, returns the default value $default.

=head2 delete_or_default_string

C<method delete_or_default_string : string ($key : string, $default : string;>

If the value specified by the key $key exists, this method calls L</"get_string"> method
and L</"delete"> method, and returns the return value of L</"get_string"> method.

If the value specified by the key $key does not exists, returns the default value $default.

=head2 delete_or_default

C<method delete_or_default : element ($key : string, $default : object;>

If the value specified by the key $key exists, this method calls L</"get"> method
and L</"delete"> method, and returns the return value of L</"get"> method.

If the value specified by the key $key does not exists, returns the default value $default.

=head2 merge

C<method merge : void ($hash : Hash);>

Merges the hash $hash into the current hash.

=head2 merge_options

C<method merge_options : void ($options : object[]);>
  
Merges the options $options into the current hash.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
