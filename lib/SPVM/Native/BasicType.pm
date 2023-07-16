package SPVM::Native::BasicType;



1;

=head1 Name

SPVM::Native::BasicType - Information of Basic Types

=head1 Description

The Native::BasicType class of L<SPVM> has methods to manipulate information of basic types.

=head1 Usage

  use Native::BasicType;

=head1 Instance Methods

=head2 get_id

  method get_id : int ();

Gets the basic type ID.

If a memory error occurs, an exception is thrown.

=head2 get_name

  method get_name : string ();

Gets the basic type name.

If a memory error occurs, an exception is thrown.

=head2 get_module_dir

  method get_module_dir : string ();

Gets the module directory.

If a memory error occurs, an exception is thrown.

=head2 get_rel_file

  method get_rel_file : string ();

Gets the module relative file path.

If a memory error occurs, an exception is thrown.

=head2 get_parent

  method get_parent : Native::BasicType ();

Gets the parent L<Native::BasicType|SPVM::Native::BasicType> object.

If a memory error occurs, an exception is thrown.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

