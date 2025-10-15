package SPVM::StringBuffer;

1;

=head1 Name

SPVM::StringBuffer - String Buffers

=head1 Description

The StringBuffer class in L<SPVM> has methods to manipulate string buffers.

=head1 Usage
  
  use StringBuffer;
  
  # new
  my $buffer = StringBuffer->new;
  
  my $buffer = StringBuffer->new("abc");
  
  # push string
  $buffer->push("def");
  
  # Convert to the string
  my $string = $buffer->to_string;

=head1 Details

=head2 Internal Data Structure

The L</"string"> stored in a StringBuffer object always starts at index 0.

The charactors in the range that is greater than or equal to L</"length"> field and less than L</"capacity"> field are filled with "\0".

=head1 Interfaces

=over 2

=item * L<Cloneable|SPVM::Cloneable>

=item * L<Comparable|SPVM::Comparable>

=item * L<EqualityCheckable|SPVM::EqualityCheckable>

=back

=head1 Fields

=head2 capacity

C<has capacity : virtual ro int;>

The capacity. This is the length of the internally reserved characters to extend the length of the string buffer.

=head2 length

C<has length : virtual ro int;>

The length of the string buffer.

=head2 string

C<has string : mutable string;>

The internal string stored in the StringBuffer object.

=head1 Class Methods

=head2 new

C<static method new : L<StringBuffer|SPVM::StringBuffer> ($string : string = undef, $capacity : int = -1);>

Creates a new C<StringBuffer> object using L</"new_len">.

The passed $length to L</"new_len"> is the length of $string. If the string is undef, it is 0.

$string is copied to the value of the the created string buffer.

=head2 new_len

C<static method new_len : L<StringBuffer|SPVM::StringBuffer> ($length : int, $capacity : int = -1);>

Creates a new C<StringBuffer> object with $length and $capacity.

If $capacity is less than 0, $capacity is set to an appropriate value.

If $length is greater than $capacity, $capacity is set to $length.

Exceptions:

$length must be greater than or equal to 0. Otherwise an exception is thrown.

=head2 new_ref

C<static method new_ref : L<StringBuffer|SPVM::StringBuffer> ($string : mutable string);>

Creates a new L<StringBuffer|SPVM::StringBuffer> object, and set L</"string"> field to the string $string, and return the new object.

Exceptions:

The array $array must be defined. Otherwise an exception is thrown.

=head1 Instance Methods

=head2 push

C<method push : void ($string : string, $offset : int = 0, $length : int = -1);>

Adds a $string from $offset to the position proceeded by $length after the end of the string in the string buffer.

Exceptions:

$string must be defined. Otherwise an exception is thrown.

$offset must be greater than or equal to 0. Otherwise an exception is thrown.

$offset + $length must be less than or equal to the length of $string. Otherwise an exception is thrown.

=head2 push_char

C<method push_char : void ($char : int);>

Adds Ascii $char after the end of the string in the string buffer.

=head2 reserve

C<method reserve : void ($new_capacity : int);>

Reserves the characters that size is $new_capacity.

If $new_capacity is greater than the capacity of the string buffer, the capacity of the string buffer is extended to $new_capacity.

Exceptions:

$new_capacity must be greater than or equal to 0. Otherwise an exception is thrown.

=head2 to_string

C<method to_string : string ();>

Creates a new string with the length of the buffer and copies all characters in the buffer into the new string, and returns it.

=head2 get_string

C<method get_string : string ();>

Returns the internal L</"string">. 

=head2 set_length

C<method set_length : void ($length : int);>

Sets L</"length"> fields.

If the length $length is greater than L</"length"> field, the characters of the exceeding part are filled with "\0".

=head2 set

C<method set : void ($string : string);>

Sets the string $string.

=head2 compare_string

C<method compare_string : int ($string : string);>

The return value is the same as the return value of C<cmp> operator given C<$self-E<gt>to_string> and $string.

=head2 equals_string

C<method equals_string : int ($string : string);>

If the string contained in the StringBuffer instance is equal to the string $string, returns 1, otherwise returns 0.

=head2 clone

C<method clone ();>

Clones this string buffer and returns it.

This method is a method implementation for L<Cloneable|SPVM::Cloneable> interface.

=head2 cmp

C<method cmp : int ($a : L<StringBuffer|SPVM::StringBuffer>, $b : L<StringBuffer|SPVM::StringBuffer>);>

Compares two L<StringBuffer|SPVM::StringBuffer> and returns its result.

The return value is the same as the return value of C<cmp> operator given C<$a-E<gt>to_string> or undef(if $a is undef) and C<$b-E<gt>to_string> or undef(if $b is undef).

This method is a method implementation for L<Comparable|SPVM::Comparable> interface.

=head2 eq

C<method eq : int ($a : L<StringBuffer|SPVM::StringBuffer>, $b : L<StringBuffer|SPVM::StringBuffer>);>

Checks if $a is equal to $b, and returns its result.

Implementation:

If $a and $b is defined, calls L</"cmp"> method. If the return value is 0, returns 1, otherwise 0.

If only $a is not defined, returns 0.

If only $b is not defined, returns 0.

If both $a and $b is not defined, returns 1.

This method is a method implementation for L<EqualityCheckable|SPVM::EqualityCheckable> interface.

=head2 substr

C<method substr : string ($offset : int, $length : int = -1, $replacement : string = undef);>

Calls L<Fn#substr|SPVM::Fn/"substr"> method given the value of L</"string"> field, $offset, $length, and returns its return value.

If the replacement string $replacement is specified, also calls L</"replace"> method.

Exceptions:

The offset $offset + the length $length must be less than or equal to the value of length field. Otherwise an exception is thrown.

Exceptions thrown by L<Fn#substr|SPVM::Fn/"substr"> method could be thrown.

=head2 index

C<method index : int ($substring : string, $begin : int = 0, $end : int = -1);>

Calls L<Fn#index|SPVM::Fn/"index"> method given L</"string"> field, $substring, $bigen, $end, and retunrs its return value.

If $end is less than 0, it is set to the value of L</"length"> field.

Exceptions:

The begin $begin must be between 0 and the length of string field. Otherwise an exception is thrown.

The end $end must be less than or equal to the length of string field. Otherwise an exception is thrown.

Exceptions thrown by L<Fn#index|SPVM::Fn/"index"> method could be thrown.

=head2 contains

C<static method contains : int ($substring : string, $begin : int = 0, $end : int = -1);>

Checks if L</"string"> field contains $substring.

Implementation:

The alias for the following code using L</"index"> method.

  my $ret = $self->index($substring, $begin, $end) >= 0;

Exceptions:

Exceptions thrown by L</"index"> method could be thrown.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
