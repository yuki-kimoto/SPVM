package SPVM::StringList;

use SPVM 'SPVM::StringList';

1;

=head1 NAME

SPVM::StringList - Continuous dynamic string array

=head1 SYNOPSYS
  
  use SPVM::StringList;
  
  # Create a string list
  my $string_list = SPVM::StringList->new;

  # Create a string list with array
  my $string_list = SPVM::StringList->newa(["abc", "def", "ghi"]);
  
  # Get list length
  my $length = $string_list->length;
  
  # Push string value
  $string_list->push("abc");

  # Pop string value.
  my $string_value = $string_list->pop;

  # Unshift string value.
  $string_list->unshift("abc");
  
  # Shift string value.
  my $string_value = $string_list->shift;
  
  # Set string value.
  $string_list->set(2, "abc");

  # Get string value.
  my $string_value = $string_list->get(2);

  # Insert string value
  $string_list->insert(1, "abc");

  # Remove string value
  my $string_value = $string_list->remove(1);

  # Convert SPVM::StringList to string array.
  my $string_array = $string_list->to_array;

=head1 DESCRIPTION

L<SPVM::StringList> is continuous dynamic string array.

=head1 CLASS METHODS

=head2 new

    sub new : SPVM::StringList ()

Create a new L<SPVM::StringList> object.

=head2 newa

    sub newa : SPVM::StringList ($array : string[])

Create a new L<SPVM::StringList> object with specific C<string> array.

=head1 INSTANCE METHODS

=head2 length
  
  sub length : int ()

Get list length.

=head2 push
  
  sub push : void ($self : self, $value : string)

Appending the value to the end of list.

=head2 pop

  sub pop : string ($self : self)

Pops and returns the last value of the list, shortening the array by one element
If there are no elements in the list, exception occur.

=head2 unshift

  sub unshift : void ($self : self, $value : string)

Appending the value to the top of list.

=head2 shift

  sub shift : string ($self : self)

Shifts the first value of the list off and returns it, shortening
the array by 1 and moving everything down.
If there are no elements in the list, exception occur.

=head2 set

  sub set : void ($self : self, $index : int, $value : string)

Set the value with index.

=head2 get

  sub get : string ($self : self, $index : int)

Get the value with index.

=head2 insert

  sub insert : void ($self : self, $index : int, $value : string)

Insert a element to the specific index.

=head2 remove

  sub remove : string ($self : self, $index : int)

=head2 to_array

  sub to_array : string[] ($self : self)

Convert L<SPVM::StringList> to string array.
