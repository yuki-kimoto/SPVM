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

C<method get_id : int ();>

Returns the basic type ID.

If a memory error occurs, an exception is thrown.

=head2 get_name

C<method get_name : string ();>

Returns the basic type name.

If a memory error occurs, an exception is thrown.

=head2 get_class_dir

C<method get_class_dir : string ();>

Returns the module directory.

If a memory error occurs, an exception is thrown.

=head2 get_rel_file

C<method get_rel_file : string ();>

Returns the module relative file path.

If a memory error occurs, an exception is thrown.

=head2 get_parent

C<method get_parent : L<Native::BasicType|SPVM::Native::BasicType> ();>

Returns the parent L<Native::BasicType|SPVM::Native::BasicType> object.

If a memory error occurs, an exception is thrown.

=head2 get_category

C<method get_category : int ();>

Returns the category.

If a memory error occurs, an exception is thrown.

=head2 get_version_string

C<method get_version_string : string ();>

Returns the version string.

If a memory error occurs, an exception is thrown.

=head2 is_pointer

C<method is_pointer : int ();>

If the basic type is a pointer class, returns 1. Otherwise returns 0.

If a memory error occurs, an exception is thrown.

=head2 is_anon

C<method is_anon : int ();>

If the basic type is anon basic type, returns 1. Otherwise returns 0.

If a memory error occurs, an exception is thrown.

=head2 get_class_var_by_index

C<method get_class_var_by_index : L<Native::ClassVar|SPVM::Native::ClassVar> ($class_var_index : int);>

Gets a L<class variable|Native::ClassVar> object by an index.

If a memory error occurs, an exception is thrown.

=head2 get_class_var_by_name

C<method get_class_var_by_name : L<Native::ClassVar|SPVM::Native::ClassVar> ($class_var_name : string);>

Gets a L<class variable|Native::ClassVar> object by a name.

If a memory error occurs, an exception is thrown.

=head2 get_class_vars_length

C<method get_class_vars_length : int ();>

Gets the length of the class variables.

If a memory error occurs, an exception is thrown.

=head2 get_field_by_index

C<method get_field_by_index : L<Native::Field|SPVM::Native::Field> ($field_index : int);>

Gets a L<field|Native::Field> object by an index.

If a memory error occurs, an exception is thrown.

=head2 get_field_by_name

C<method get_field_by_name : L<Native::Field|SPVM::Native::Field> ($field_name : string);>

Gets a L<field|Native::Field> object by a name.

If a memory error occurs, an exception is thrown.

=head2 get_fields_length

C<method get_fields_length : int ();>

Gets the length of the fields.

If a memory error occurs, an exception is thrown.

=head2 get_method_by_index

C<method get_method_by_index : L<Native::Method|SPVM::Native::Method> ($method_index : int);>

Gets a L<method|Native::Method> object by an index.

If a memory error occurs, an exception is thrown.

=head2 get_method_by_name

C<method get_method_by_name : L<Native::Method|SPVM::Native::Method> ($method_name : string);>

Gets a L<method|Native::Method> object by a name.

If a memory error occurs, an exception is thrown.

=head2 get_methods_length

C<method get_methods_length : int ();>

Gets the length of the methods.

If a memory error occurs, an exception is thrown.

=head2 get_anon_basic_type_by_index

C<method get_anon_basic_type_by_index : L<Native::BasicType|SPVM::Native::BasicType> ($anon_basic_type_index : int);>

Gets a anon L<basic type|SPVM::Native::BasicType> object defined in this basic type by an index.

If a memory error occurs, an exception is thrown.

=head2 get_anon_basic_types_length

C<method get_anon_basic_types_length : int ();>
  
Gets the length of the anon basic types defined in this basic type.

If a memory error occurs, an exception is thrown.

=head2 get_methods

C<method get_methods :  L<Native::Method|SPVM::Native::Method>[] ($options : object[] = undef);>

Returns methods.

=head2 get_fields

C<method get_fields : L<Native::Field|SPVM::Native::Field>[] ($options : object[] = undef);>

Returns fields.

=head2 get_class_vars

C<method get_class_vars : L<Native::ClassVar|SPVM::Native::ClassVar>[] ($options : object[] = undef);>

Returns class variables.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

