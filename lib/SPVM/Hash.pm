package SPVM::Hash;

1;

=head1 NAME

SPVM::Hash - Hash Data Structure

=head1 SYNOPSYS
  
  use Hash;
  
  # Create hash
  my $book = Hash->new;
  my $book = Hash->new({});
  my $book = Hash->new({id => 4, name => "Perl", price => 3000.0});
  
  $book->set_int(id => 4);
  $book->set_string(name => "Perl");
  $book->set_double(price => 3000.0);
  
  my $id = (int)$book->get_int("id");
  my $name = (string)$book->get_string("name");
  my $price = (double)$book->get_double("price");
  
=head1 DESCRIPTION

L<Hash|SPVM::Hash> is Hash Data Structure. This is generally called associative array.

=head1 CLASS METHODS

=head2 new

  static method new : Hash ($key_values : object[]...)

Create a new L<Hash|SPVM::Hash> object with key value pairs.

  my $book = Hash->new;
  my $book = Hash->new({});
  my $book = Hash->new({id => 4, name => "Perl"});

=head1 INSTANCE METHODS

=head2 count

  count : int ()

Count keys.

=head2 copy

  copy : Hash ()

Copy hash.

This is not deep copy. Address of keys and values is copied into new hash.

=head2 delete

  delete : object ($key : string)

Delete a key value pair. Deleted value is returned.

=head2 exists

  exists : int ($key : string)

Specify the key and check if the value exists. If exists, return 1, otherwise 0.

=head2 keys

  keys : string[] ()

Get keys. This method do not copy the strings.

=head2 values

  values : object[] ()

Get values.

=head2 get

  get : object ($key : string)

Get a value.

=head2 get_byte

  get_byte : byte ($name : string)

Get value with a key. the value is converted to byte type.

=head2 get_short

  get_short : short ($name : string)

Get value with a key. the value is converted to short type.
  
=head2 get_int

  get_int : int ($name : string)

Get value with a key. the value is converted to int type.
  
=head2 get_long

  get_long : long ($name : string)

Get value with a key. the value is converted to long type.

=head2 get_float

  get_float : float ($name : string)

Get value with a key. the value is converted to float type.
  
=head2 get_double

  get_double : double ($name : string)

Get value with a key. the value is converted to double type.

=head2 set
  
  set : void ($key : string, $val : object)

Set key value pair.

=head2 set_byte

  set_byte : void ($name : string, $value : byte)

Set key and value pair. byte value is converted to L<Byte|SPVM::Byte> object.

=head2 set_short

  set_short : void ($name : string, $value : short)

Set key and value pair. short value is converted to L<Short|SPVM::Short> object.

=head2 set_int

  set_int : void ($name : string, $value : int)

Set key and value pair. int value is converted to L<Int|SPVM::Int> object.

=head2 set_long

  set_long : void ($name : string, $value : long)

Set key and value pair. long value is converted to L<Long|SPVM::Long> object.

=head2 set_float

  set_float : void ($name : string, $value : float)

Set key and value pair. float value is converted to L<Float|SPVM::Float> object.

=head2 set_double

  set_double : void ($name : string, $value : double)

Set key and value pair. double value is converted to L<Double|SPVM::Double> object.

=head2 set_string

  set_string : void ($name : string, $value : string)

Set key and value pair with string value.

