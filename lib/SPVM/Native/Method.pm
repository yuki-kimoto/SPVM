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

C<method get_index : int ();>

Returns the index.

If a memory error occurs, an exception is thrown.

=head2 get_name

C<method get_name : string ();>

Returns the name.

If a memory error occurs, an exception is thrown.

=head2 get_return_basic_type

C<method get_return_basic_type : L<Native::BasicType|SPVM::Native::BasicType> ();>

Returns the L<Native::BasicType|SPVM::Native::BasicType> object of the return value.

If a memory error occurs, an exception is thrown.

=head2 get_return_type_dimension

C<method get_return_type_dimension : int ();>

Returns the type dimension of the return value.

If a memory error occurs, an exception is thrown.

=head2 get_return_type_flag

C<method get_return_type_flag : int ();>

Returns the type flag of the return value.

If a memory error occurs, an exception is thrown.

=head2 get_current_basic_type

C<method get_current_basic_type : L<Native::BasicType|SPVM::Native::BasicType> ();>

Returns the current L<Native::BasicType|SPVM::Native::BasicType> object that defines this method.

If a memory error occurs, an exception is thrown.

=head2 get_arg_by_index

C<method get_arg_by_index : L<Native::Arg|SPVM::Native::Arg> ($arg_index : int);>

Gets a L<arg|Native::Arg> object by an index, and returns it.

If a memory error occurs, an exception is thrown.

=head2 get_args_length

C<method get_args_length : int ();>

Returns the length of the arguments.

If a memory error occurs, an exception is thrown.

=head2 get_required_args_length

C<method get_required_args_length : int ();>

Returns the length of the required arguments.

If a memory error occurs, an exception is thrown.

=head2 is_class_method

C<method is_class_method : int ();>

If the method is class method, returns 1. Otherwise returns 0.

If a memory error occurs, an exception is thrown.

=head2 is_anon

C<method is_anon : int ();>

If the method is anon method, returns 1. Otherwise returns 0.

If a memory error occurs, an exception is thrown.

=head2 is_native

C<method is_native : int ();>

If the method is native method, returns 1. Otherwise returns 0.

If a memory error occurs, an exception is thrown.

=head2 is_precompile

C<method is_precompile : int ();>

If the method is precompiled method, returns 1. Otherwise returns 0.

If a memory error occurs, an exception is thrown.

=head2 is_enum

C<method is_enum : int ();>

If the method is enumeration, returns 1. Otherwise returns 0.

If a memory error occurs, an exception is thrown.

=head2 get_native_address

C<method get_native_address : L<Address|SPVM::Address> ();>

Gets the native L<address|SPVM::Address>.

If a memory error occurs, an exception is thrown.

=head2 set_native_address

C<method set_native_address : void ($address : L<Address|SPVM::Address>);>

Sets the native L<address|SPVM::Address>.

If a memory error occurs, an exception is thrown.

=head2 get_precompile_address

C<method get_precompile_address : L<Address|SPVM::Address> ();>

Gets the precompiled L<address|SPVM::Address>.

If a memory error occurs, an exception is thrown.

=head2 set_precompile_address

C<method set_precompile_address : void ($address : L<Address|SPVM::Address>);>

Sets the precompiled L<address|SPVM::Address>.

If a memory error occurs, an exception is thrown.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

