package SPVM::Native::Arg;



1;

=head1 Name

SPVM::Native::Arg - Information of Arguments

=head1 Description

The Native::Arg class of L<SPVM> has methods to manipulate information of arguments.

=head1 Usage

  use Native::Arg;

=head1 Instance Methods

=head2 get_index

  method get_index : int ();

Gets the index.

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

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

