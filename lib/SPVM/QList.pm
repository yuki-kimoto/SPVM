package SPVM::QList;

1;

=head1 Name

SPVM::QList - List with O(1) deque

=head1 Usage
  
  use QList;
  
  # Create an object list
  my $list = QList->new;
  my $list = QList->new([(object)Byte->new(1), Int->new(2), Long->new(3)]);

  # Create a Int list
  my $list = QList->new([Int->new(1), Int->new(2), Int->new(3)]);
  
  # Create an object list with length
  my $list = QList->new_len([], 3);

  # Create a Int list with length
  my $list = QList->new_len(new Int[0], 3);

  # Get list length
  my $length = $list->length;
  
  # Push object value
  $list->push(Int->new(3));

  # Pop object value.
  my $element = $list->pop;

  # Unshift object value.
  $list->unshift(Int->new(3));
  
  # Shift object value.
  my $element = $list->shift;
  
  # Set object value.
  $list->set(2, Int->new(3));
  
  # Get object value.
  my $element = $list->get(2);

  # Insert object value
  $list->insert(1, Int->new(3));

  # Remove object value
  my $element = $list->remove(1);

  # Convert QList to object array.
  my $int_array = $list->to_array;

  # Convert QList to Int array.
  my $int_array = (Int[])$list->to_array;

=head1 Description

QList class in L<SPVM> is L<List|SPVM::List> class with O(1) deque

=head1 Details

=head2 O(1) deque

L</"shift"> method is O(1) instead of L<List|SPVM::List> class.

=head1 Super Class

L<List|SPVM::List>

=head1 Class methods

=head2 new

C<static method new : L<QList|SPVM::QList> ($array : object[] = undef, $capacity : int = -1);>

=head2 new_len

C<static method new_len : L<QList|SPVM::QList> ($proto_array : object[], $length : int, $capacity : int = -1);>

=head1 Instance methods

=head2 get

C<method get : element ($index : int);>

Same as L<List#get|SPVM::List/"get"> method.

=head2 set

C<method set : void ($index : int, $element : object);>

Same as L<List#set|SPVM::List/"set"> method.

=head2 shift

C<method shift : element ();>

Same as L<List#shift|SPVM::List/"shift"> method.

=head2 to_array

C<method to_array : element[] ();>

Same as L<List#to_array|SPVM::List/"to_array"> method.

=head2 unshift

C<method unshift : void ($element : object);>

Same as L<List#unshift|SPVM::List/"unshift"> method.

=head2 clone

C<method clone : L<QList|SPVM::QList> ();>

Same as L<List#clone|SPVM::List/"clone"> method.

=head2 get_array

C<method get_array : element[] ();>

Always throw an exception.

Exceptions:

Cannot get the internal array in QList object.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
