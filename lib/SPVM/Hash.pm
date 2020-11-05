package SPVM::Hash;

1;

=head1 NAME

SPVM::Hash - Key-Values Stored Data Structrue

=head1 SYNOPSYS
  
  use SPVM::Hash;
  
  # Book Data
  my $book = SPVM::Hash->new;
  
  $book->set_int(id => 4);
  $book->set(name => "Perl");
  $book->set_int(price => 300);
  
  my $id = $book->get_int("id");
  my $name = $book->get("name");
  my $price = $book->get_int("price");
  
  # Option Data
  my $opt = SPVM::Hash->new;
  $opt->set_int(limit => 10);
  $opt->set(caption => "Perl is Good Plain Old Language");
  $opt->set_double(rate => 0.95);
  
=head1 DESCRIPTION

L<SPVM::Hash> is Key-Values Stored Data Structrue.

=head1 STATIC METHODS

=head2 new

    sub new : SPVM::Hash ()

Create a new L<SPVM::Hash> object.

=head1 INSTANCE METHODS

=head2 count : int ($self : self)

Count keys.
  
=head2 set : void ($self : self, $key : string, $val : object)
  
Set key value pair.

=head2 get : object ($self : self, $key : string)

Get value.

=head2 exists : int ($self : self, $key : string)

Check the value existance of a key.

=head2 delete : object ($self : self, $key : string)

Delete key and value pair.
  
=head2 keys : string[] ($self : self)

Get keys.

=head2 values : object[] ($self : self)

Get values.

=head2 copy : SPVM::Hash ($self : self)

Copy hash.

=head2 set_byte : void ($self : self, $name : string, $value : byte)

Set key and value pair. byte value is converted to SPVM::Byte object.

=head2 set_short : void ($self : self, $name : string, $value : short)

Set key and value pair. short value is converted to SPVM::Short object.

=head2 set_int : void ($self : self, $name : string, $value : int)
  
Set key and value pair. int value is converted to SPVM::Int object.

=head2 set_long : void ($self : self, $name : string, $value : long)

Set key and value pair. long value is converted to SPVM::Long object.

=head2 set_float : void ($self : self, $name : string, $value : float)

Set key and value pair. float value is converted to SPVM::Float object.

=head2 set_double : void ($self : self, $name : string, $value : double)

Set key and value pair. double value is converted to SPVM::Double object.

=head2 get_byte : byte ($self : self, $name : string)

Set value with a key. the value is converted to byte type.

=head2 get_short : short ($self : self, $name : string)

Set value with a key. the value is converted to short type.
  
=head2 get_int : int ($self : self, $name : string)

Set value with a key. the value is converted to int type.
  
=head2 get_long : long ($self : self, $name : string)

Set value with a key. the value is converted to long type.

=head2 get_float : float ($self : self, $name : string)

Set value with a key. the value is converted to float type.
  
=head2 get_double : double ($self : self, $name : string)

Set value with a key. the value is converted to double type.
