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

C<has capacity : ro int;>

The capacity. This is the length of the internally reserved characters to extend the length of the string buffer.

=head2 length

C<has length : ro int;>

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

=head2 replace

C<method replace : void ($offset : int, $length : int, $replace : string);>

Replace the characters of the range specified by $offset and $length in the buffer with $replace string.

Exceptions:

$offset must be greater than or equal to 0. Otherwise an exception is thrown.

$offset + $length must be less than or equal to the length of the string buffer. Otherwise an exception is thrown.

=head2 reserve

C<method reserve : void ($new_capacity : int);>

Reserves the characters that size is $new_capacity.

If $new_capacity is greater than the capacity of the string buffer, the capacity of the string buffer is extended to $new_capacity.

Exceptions:

$new_capacity must be greater than or equal to 0. Otherwise an exception is thrown.

=head2 to_string

C<method to_string : string ();>

Creates a new string with the length of the buffer and copies all characters in the buffer into the new string, and returns it.

=head2 get_string_unsafe

C<method get_string_unsafe : string ();>

Gets the internally string. 

This buffer is unsafe because it continues to point to the old string if the internal string is extended.

=head2 set_length

C<method set_length : void ($length : int);>

Sets L</"length"> fields.

If the length $length is greater than L</"length"> field, the characters of the exceeding part are filled with "\0".

=head2 set

C<method set : void ($string : string);>

Sets the string $string.

=head2 clone

C<method clone ();>

Clones this string buffer and returns it.

=head2 cmp

C<method cmp : int ($a : L<StringBuffer|SPVM::StringBuffer>, $b : L<StringBuffer|SPVM::StringBuffer>);>

Compares two L<StringBuffer|SPVM::StringBuffer> and returns its result.

The result is equal to the return value of C<cmp> operator given C<$a-E<gt>to_string> or undef(if $a is undef) and C<$b-E<gt>to_string> or undef(if $b is undef).

=head2 eq

C<method eq : int ($a : L<StringBuffer|SPVM::StringBuffer>, $b : L<StringBuffer|SPVM::StringBuffer>);>

Checks if $a is equal to $b, and returns its result.

Implementation:

If $a and $b is defined, calls L</"cmp"> method. If the return value is 0, returns 1, otherwise 0.

If only $a is not defined, returns 0.

If only $b is not defined, returns 0.

If both $a and $b is not defined, returns 1.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
