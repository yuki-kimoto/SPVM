package SPVM::Native::Method;



1;

=head1 Name

SPVM::Native::Method - Information of Methods

=head1 Description

The Native::Method class of L<SPVM> has methods to manipulate information of methods.

=head1 Usage

  use Native::Method;

=head1 Instance Methods

=head2 get_index

  method get_index : int ();

Gets the index.

If a memory error occurs, an exception is thrown.

=head2 get_name

  method get_name : string ();

Gets the name.

If a memory error occurs, an exception is thrown.

=head2 get_return_basic_type

  method get_return_basic_type : Native::BasicType ();

Gets the L<Native::BasicType|SPVM::Native::BasicType> object of the return value.

If a memory error occurs, an exception is thrown.

=head2 get_return_type_dimension

  method get_return_type_dimension : int ();

Gets the type dimension of the return value.

If a memory error occurs, an exception is thrown.

=head2 get_return_type_flag

  method get_return_type_flag : int ();

Gets the type flag of the return value.

If a memory error occurs, an exception is thrown.

=head2 get_current_basic_type

  method get_current_basic_type : Native::BasicType ();

Gets the current L<Native::BasicType|SPVM::Native::BasicType> object that defines this method.

If a memory error occurs, an exception is thrown.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

