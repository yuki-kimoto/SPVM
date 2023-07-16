package SPVM::Native::ClassVar;



1;

=head1 Name

SPVM::Native::ClassVar - Information of Class Variables

=head1 Description

The Native::ClassVar class of L<SPVM> has methods to manipulate information of class variables.

=head1 Usage

  use Native::ClassVar;

=head1 Instance Methods

=head2 get_index

  method get_index : int ();

Gets the index.

If a memory error occurs, an exception is thrown.

=head2 get_name

  method get_name : string ();

Gets the name.

If a memory error occurs, an exception is thrown.

=head2 get_basic_type

  method get_basic_type : Native::BasicType ();

Gets the L<Native::BasicType|SPVM::Native::BasicType> object.

If a memory error occurs, an exception is thrown.

=head2 get_type_dimension

  method get_type_dimension : int ();

Gets the type dimension.

If a memory error occurs, an exception is thrown.

=head2 get_type_flag

  method get_type_flag : int ();

Gets the type flag.

If a memory error occurs, an exception is thrown.

=head2 get_current_basic_type

  method get_current_basic_type : Native::BasicType ();

Gets the current L<Native::BasicType|SPVM::Native::BasicType> object that defines this class variable.

If a memory error occurs, an exception is thrown.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

