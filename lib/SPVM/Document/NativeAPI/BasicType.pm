=head1 Name

SPVM::Document::NativeAPI::BasicType - Basic Type Native APIs

=head1 Description

The basic type native APIs in L<SPVM> are the APIs to get definition information of basic types.

=head1 Usage

  int32_t error_id
  
  SPVM_API_BASIC_TYPE* api_basic_type = env->api->basic_type;
  
  void* basic_type = env->get_basic_type(env, stack, "Int");
  
  const char* basic_type_name = api_basic_type->get_name(env->runtime, basic_type);

=head1 Native APIs

=head2 get_name

C<const char* (*get_name)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* basic_type|SPVM::Document::NativeAPI::BasicType>);>

Returns the name of the basic type.

=head2 get_id

C<int32_t (*get_id)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* basic_type|SPVM::Document::NativeAPI::BasicType>);>

Returns the ID of the basic type.

=head2 get_category

C<int32_t (*get_category)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* basic_type|SPVM::Document::NativeAPI::BasicType>);>

Returns the L<base type category ID|SPVM::Document::NativeAPI/"Basic Type Category IDs"> of the basic type.

=head2 get_parent

C<void* (*get_parent)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* basic_type|SPVM::Document::NativeAPI::BasicType>);>

Returns the parent L<basic type|SPVM::Document::NativeAPI::BasicType> object of the basic type I<basic_type>.

=head2 get_version_string

C<const char* (*get_version_string)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* basic_type|SPVM::Document::NativeAPI::BasicType>);>

Returns the version string of the basic type.

=head2 get_class_dir

C<const char* (*get_class_dir)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* basic_type|SPVM::Document::NativeAPI::BasicType>);>

Returns the class directory of the basic type.

=head2 get_class_rel_file

C<const char* (*get_class_rel_file)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* basic_type|SPVM::Document::NativeAPI::BasicType>);>

Returns the class relative file of the basic type.

=head2 is_pointer

C<int32_t (*is_pointer)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* basic_type|SPVM::Document::NativeAPI::BasicType>);>

If the basic type is a pointer class, returns 1. Otherwise returns 0.

=head2 is_anon

C<int32_t (*is_anon)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* basic_type|SPVM::Document::NativeAPI::BasicType>);>

If the basic type is an anon class, returns 1. Otherwise returns 0.

=head2 get_class_var_by_index

C<void* (*get_class_var_by_index)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* basic_type|SPVM::Document::NativeAPI::BasicType>, int32_t class_var_index);>

Gets a L<class variable|SPVM::Document::NativeAPI::ClassVariable> defined in the basic type I<basic_type> given a class variable index I<class_var_index>, and returns it.

=head2 get_class_var_by_name

C<void* (*get_class_var_by_name)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* basic_type|SPVM::Document::NativeAPI::BasicType>, const char* class_var_name);>

Gets a L<class variable|SPVM::Document::NativeAPI::ClassVariable> defined in the basic type I<basic_type> given a class variable name I<class_var_name>, and returns it.

=head2 get_class_vars_length

C<int32_t (*get_class_vars_length)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* basic_type|SPVM::Document::NativeAPI::BasicType>);>

Returns the length of the class variables defined in the basic type I<basic_type>.

=head2 get_field_by_index

C<void* (*get_field_by_index)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* basic_type|SPVM::Document::NativeAPI::BasicType>, int32_t field_index);>

Gets a L<field|SPVM::Document::NativeAPI::Field> defined in the basic type I<basic_type> given a field index I<field_index>, and returns it.

=head2 get_field_by_name

C<void* (*get_field_by_name)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* basic_type|SPVM::Document::NativeAPI::BasicType>, const char* field_name);>

Gets a L<field|SPVM::Document::NativeAPI::Field> defined in the basic type I<basic_type> given a field name I<field_name>, and returns it.

=head2 get_fields_length

C<int32_t (*get_fields_length)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* basic_type|SPVM::Document::NativeAPI::BasicType>);>

Returns the length of the fields defined in the basic type I<basic_type>.

=head2 get_method_by_index

C<void* (*get_method_by_index)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* basic_type|SPVM::Document::NativeAPI::BasicType>, int32_t method_index);>

Gets a L<method|SPVM::Document::NativeAPI::Method> defined in the basic type I<basic_type> given a method index I<method_index>, and returns it.

=head2 get_method_by_name

C<void* (*get_method_by_name)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* basic_type|SPVM::Document::NativeAPI::BasicType>, const char* method_name);>

Gets a L<method|SPVM::Document::NativeAPI::Method> defined in the basic type I<basic_type> given a method name I<method_name>, and returns it.

=head2 get_methods_length

C<int32_t (*get_methods_length)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* basic_type|SPVM::Document::NativeAPI::BasicType>);>

Returns the length of the methods defined in the basic type I<basic_type>.

=head2 get_anon_basic_type_by_index

C<void* (*get_anon_basic_type_by_index)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* basic_type|SPVM::Document::NativeAPI::BasicType>, int32_t anon_basic_type_index);>

Gets a anon L<basic type|SPVM::Document::NativeAPI::BasicType> defined in the basic type I<basic_type> given an anon basic type index, and returns it.

=head2 get_anon_basic_types_length

C<int32_t (*get_anon_basic_types_length)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* basic_type|SPVM::Document::NativeAPI::BasicType>);>

Returns the length of the anon basic types defined in the basic type I<basic_type>.

=head2 has_interface

C<int32_t (*has_interface)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* basic_type|SPVM::Document::NativeAPI::BasicType>, L<void* interface_basic_type|SPVM::Document::NativeAPI::BasicType>);>

If the basic type I<basic_type> has an interface I<interface_basic_type>, returns 1. Otherwise returns 0.

=head2 is_super_class

C<int32_t (*is_super_class)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* super_basic_type|SPVM::Document::NativeAPI::BasicType>, L<void* child_basic_type|SPVM::Document::NativeAPI::BasicType>);>

If I<super_basic_type> is a super class of I<child_basic_type>, returns 1. Otherwise returns 0.

=head2 get_file

C<const char* (*get_file)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* basic_type|SPVM::Document::NativeAPI::BasicType>);>

Returns the file path of the basic type.

This can be changed by a file directive.

  #file /tempaltes/foo.html.ep
  class Foo {
  
  }

=head1 Native API IDs

  0 get_name
  1 get_id
  2 get_category
  3 get_parent
  4 get_version_string
  5 get_class_dir
  6 get_class_rel_file
  7 is_pointer
  8 is_anon
  9 get_class_var_by_index
  10 get_class_var_by_name
  11 get_class_vars_length
  12 get_field_by_index
  13 get_field_by_name
  14 get_fields_length
  15 get_method_by_index
  16 get_method_by_name
  17 get_methods_length
  18 get_anon_basic_type_by_index
  19 get_anon_basic_types_length
  20 has_interface
  21 is_super_class
  22 get_file

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
