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

Returns the basic type ID.

If a memory error occurs, an exception is thrown.

=head2 get_name

  method get_name : string ();

Returns the basic type name.

If a memory error occurs, an exception is thrown.

=head2 get_class_dir

  method get_class_dir : string ();

Returns the module directory.

If a memory error occurs, an exception is thrown.

=head2 get_rel_file

  method get_rel_file : string ();

Returns the module relative file path.

If a memory error occurs, an exception is thrown.

=head2 get_parent

  method get_parent : Native::BasicType ();

Returns the parent L<Native::BasicType|SPVM::Native::BasicType> object.

If a memory error occurs, an exception is thrown.

=head2 get_category

  method get_category : int ();

Returns the category.

If a memory error occurs, an exception is thrown.

=head2 get_version_string

  method get_version_string : string ();

Returns the version string.

If a memory error occurs, an exception is thrown.

=head2 is_pointer

  method is_pointer : int ();

If the basic type is a pointer class, returns 1. Otherwise returns 0.

If a memory error occurs, an exception is thrown.

=head2 is_anon

  method is_anon : int ();

If the basic type is anon basic type, returns 1. Otherwise returns 0.

If a memory error occurs, an exception is thrown.

=head2 get_class_var_by_index

  method get_class_var_by_index : Native::ClassVar ($class_var_index : int);

Gets a L<class variable|Native::ClassVar> object by an index.

If a memory error occurs, an exception is thrown.

=head2 get_class_var_by_name

  method get_class_var_by_name : Native::ClassVar ($class_var_name : string);

Gets a L<class variable|Native::ClassVar> object by a name.

If a memory error occurs, an exception is thrown.

=head2 get_class_vars_length

  method get_class_vars_length : int ();

Gets the length of the class variables.

If a memory error occurs, an exception is thrown.

=head2 get_field_by_index

  method get_field_by_index : Native::Field ($field_index : int);

Gets a L<field|Native::Field> object by an index.

If a memory error occurs, an exception is thrown.

=head2 get_field_by_name

  method get_field_by_name : Native::Field ($field_name : string);

Gets a L<field|Native::Field> object by a name.

If a memory error occurs, an exception is thrown.

=head2 get_fields_length

  method get_fields_length : int ();

Gets the length of the fields.

If a memory error occurs, an exception is thrown.

=head2 get_method_by_index

  method get_method_by_index : Native::Method ($method_index : int);

Gets a L<method|Native::Method> object by an index.

If a memory error occurs, an exception is thrown.

=head2 get_method_by_name

  method get_method_by_name : Native::Method ($method_name : string);

Gets a L<method|Native::Method> object by a name.

If a memory error occurs, an exception is thrown.

=head2 get_methods_length

  method get_methods_length : int ();

Gets the length of the methods.

If a memory error occurs, an exception is thrown.

=head2 

  method get_anon_basic_type_by_index : Native::BasicType ($anon_basic_type_index : int);

Gets a anon L<basic type|SPVM::Native::BasicType> object defined in this basic type by an index.

If a memory error occurs, an exception is thrown.

=head2 

  method get_anon_basic_types_length : int ();
  
Gets the length of the anon basic types defined in this basic type.

If a memory error occurs, an exception is thrown.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

