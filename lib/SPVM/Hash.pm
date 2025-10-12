package SPVM::Hash;

1;

=head1 Name

SPVM::Hash - Hash (Associative Array)

=head1 Description

Hash class in L<SPVM> represents hashes(associative arrays).

=head1 Usage
  
  use Hash;
  
  my $book = Hash->new;
  my $book = Hash->new({id => 4, name => "Perl", price => 3000.0});
  
  $book->set(id => 4);
  $book->set(name => "Perl");
  $book->set(price => 3000.0);
  $book->set(point => Point->new(1, 2));
  
  my $id = $book->get("id")->(int);
  my $name = $book->get("name")->(string);
  my $price = $book->get("price")->(double);
  my $point = $book->get("point")->(Point);
  
  if ($hash->exists("id")) {
    
  }
  
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

=head2 set
  
C<method set : void ($key : string, $value : object);>

Sets $value to the hash by the key $key.

Exceptions:

The key $key must be defined. Otherwise, an exception is thrown.

=head2 to_array

C<method to_array : object[] ($sort : int = 0);>

Converts all the key-value pairs in the hash to an array, and returns it.

If the option $sort is a positive value, the keys are sorted by ascendant order.

If the option $sort is a negative value, the keys are sorted by decendant order.

=head2 to_options

C<method to_options : object[] ($sort : int = 0);>

Same as L</"to_array"> method, but enables options flag using C<enable_options> operator.

=head2 get_or_default

C<method get_or_default : element ($key : string, $default : object;>

If the value specified by the key $key exists, this method calls L</"get"> method
, and returns the return value of L</"get"> method.

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
