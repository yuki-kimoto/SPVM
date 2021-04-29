package SPVM::Hash;

1;

=head1 NAME

SPVM::Hash - Hash Data Structure

=head1 SYNOPSYS
  
  use SPVM::Hash;
  
  # Create hash
  my $book = SPVM::Hash->new({});
  
  $book->set_int(id => 4);
  $book->set_string(name => "Perl");
  $book->set_double(price => 3000.0);
  
  my $id = (int)$book->get_int("id");
  my $name = (string)$book->get_string("name");
  my $price = (double)$book->get_double("price");
  
  # Create hash with key value pairs
  my $book = SPVM::Hash->new({id => 4, name => "Perl", price => 3000.0});

=head1 DESCRIPTION

L<SPVM::Hash> is Hash Data Structure. This is generally called associative array.

=head1 STATIC METHODS

=head2 new

    sub new : SPVM::Hash ($key_values : oarray)

Create a new L<SPVM::Hash> object with key value pairs.

  # Create hash
  my $book = SPVM::Hash->new({});

  # Create hash with key value pairs
  my $book = SPVM::Hash->new({id => 4, name => "Perl"});

=head1 INSTANCE METHODS

=head2 count

  count : int ($self : self)

Count keys.

=head2 copy

  copy : SPVM::Hash ($self : self)

Copy hash.

This is not deep copy. Address of keys and values is copied into new hash.

=head2 delete

  delete : object ($self : self, $key : string)

Delete a key value pair. Deleted value is returned.

=head2 exists

  exists : int ($self : self, $key : string)

Specify the key and check if the value exists. If exists, return 1, otherwise 0.

=head2 keys

  keys : string[] ($self : self)

Get keys. This method do not copy the strings.

=head2 values

  values : object[] ($self : self)

Get values.

=head2 get

  get : object ($self : self, $key : string)

Get a value.

=head2 get_byte

  get_byte : byte ($self : self, $name : string)

Set value with a key. the value is converted to byte type.

=head2 get_short

  get_short : short ($self : self, $name : string)

Set value with a key. the value is converted to short type.
  
=head2 get_int

  get_int : int ($self : self, $name : string)

Set value with a key. the value is converted to int type.
  
=head2 get_long

  get_long : long ($self : self, $name : string)

Set value with a key. the value is converted to long type.

=head2 get_float

  get_float : float ($self : self, $name : string)

Set value with a key. the value is converted to float type.
  
=head2 get_double

  get_double : double ($self : self, $name : string)

Set value with a key. the value is converted to double type.

=head2 set
  
  set : void ($self : self, $key : string, $val : object)

Set key value pair.

=head2 set_byte

  set_byte : void ($self : self, $name : string, $value : byte)

Set key and value pair. byte value is converted to L<SPVM::Byte> object.

=head2 set_short

  set_short : void ($self : self, $name : string, $value : short)

Set key and value pair. short value is converted to L<SPVM::Short> object.

=head2 set_int

  set_int : void ($self : self, $name : string, $value : int)

Set key and value pair. int value is converted to L<SPVM::Int> object.

=head2 set_long

  set_long : void ($self : self, $name : string, $value : long)

Set key and value pair. long value is converted to L<SPVM::Long> object.

=head2 set_float

  set_float : void ($self : self, $name : string, $value : float)

Set key and value pair. float value is converted to L<SPVM::Float> object.

=head2 set_double

  set_double : void ($self : self, $name : string, $value : double)

Set key and value pair. double value is converted to L<SPVM::Double> object.

=head2 set_string

  set_string : void ($self : self, $name : string, $value : string)

Set key and value pair with string value.

