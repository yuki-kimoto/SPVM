=head1 Name

SPVM::Document::NativeAPI::BasicType - Basic Type Native APIs

=head1 Description

The basic type native APIs are the APIs to manipulate information of basic types.

=head1 Usage

  SPVM_API_BASIC_TYPE* api_basic_type = env->api->basic_type;
  
  const char* basic_type_name = api_basic_type->get_name(runtime, basic_type);

The C<class_var> is got by the L<get_basic_type_by_id|SPVM::Document::NativeAPI::Runtime/"get_basic_type_by_id"> and the L<get_basic_type_by_name|SPVM::Document::NativeAPI::Runtime/"get_basic_type_by_name"> runtime native API.

=head1 Native APIs

=head2 get_name

  const char* (*get_name)(void* runtime, void* basic_type);

Returns the name of the basic type.

The C<runtime> argument is a L<runtime|SPVM::Document::NativeAPI::Runtime> object.

The C<basic_type> argument is a basic type object.

=head2 get_id

  int32_t (*get_id)(void* runtime, void* basic_type);

Returns the ID of the basic type.

The C<runtime> argument is a L<runtime|SPVM::Document::NativeAPI::Runtime> object.

The C<basic_type> argument is a basic type object.

=head2 get_category

  int32_t (*get_category)(void* runtime, void* basic_type);

Returns the category of the basic type.

The C<runtime> argument is a L<runtime|SPVM::Document::NativeAPI::Runtime> object.

The C<basic_type> argument is a basic type object.

=head2 get_parent

  void* (*get_parent)(void* runtime, void* basic_type);

Returns the parent L<basic type|SPVM::Document::NativeAPI::BasicType> object of the basic type.

The C<runtime> argument is a L<runtime|SPVM::Document::NativeAPI::Runtime> object.

The C<basic_type> argument is a basic type object.

=head2 get_version_string

  const char* (*get_version_string)(void* runtime, void* basic_type);

Returns the version string of the basic type.

The C<runtime> argument is a L<runtime|SPVM::Document::NativeAPI::Runtime> object.

The C<basic_type> argument is a basic type object.

=head2 get_class_dir

  const char* (*get_class_dir)(void* runtime, void* basic_type);

Returns the class directory of the basic type.

The C<runtime> argument is a L<runtime|SPVM::Document::NativeAPI::Runtime> object.

The C<basic_type> argument is a basic type object.

=head2 get_class_rel_file

  const char* (*get_class_rel_file)(void* runtime, void* basic_type);

Returns the class relative file of the basic type.

The C<runtime> argument is a L<runtime|SPVM::Document::NativeAPI::Runtime> object.

The C<basic_type> argument is a basic type object.

=head2 is_pointer

  int32_t (*is_pointer)(void* runtime, void* basic_type);

If the basic type is a pointer class, returns 1. Otherwise returns 0.

The C<runtime> argument is a L<runtime|SPVM::Document::NativeAPI::Runtime> object.

The C<basic_type> argument is a basic type object.

=head2 is_anon

  int32_t (*is_anon)(void* runtime, void* basic_type);

If the basic type is an anon class, returns 1. Otherwise returns 0.

The C<runtime> argument is a L<runtime|SPVM::Document::NativeAPI::Runtime> object.

The C<basic_type> argument is a basic type object.

=head2 get_class_var_by_index

  void* (*get_class_var_by_index)(void* runtime, void* basic_type, int32_t class_var_index);

Gets a class variable by a class variable index, and returns it.

The C<runtime> argument is a L<runtime|SPVM::Document::NativeAPI::Runtime> object.

The C<basic_type> argument is a basic type object.

=head2 get_class_var_by_name

  void* (*get_class_var_by_name)(void* runtime, void* basic_type, const char* class_var_name);

Gets a class variable by a class variable name, and returns it.

The C<runtime> argument is a L<runtime|SPVM::Document::NativeAPI::Runtime> object.

The C<basic_type> argument is a basic type object.

=head2 get_class_vars_length

  int32_t (*get_class_vars_length)(void* runtime, void* basic_type);

Returns the length of the class variables of the basic type.

The C<runtime> argument is a L<runtime|SPVM::Document::NativeAPI::Runtime> object.

The C<basic_type> argument is a basic type object.

=head2 get_field_by_index

  void* (*get_field_by_index)(void* runtime, void* basic_type, int32_t field_index);

Gets a field by a field index, and returns it.

The C<runtime> argument is a L<runtime|SPVM::Document::NativeAPI::Runtime> object.

The C<basic_type> argument is a basic type object.

=head2 get_field_by_name

  void* (*get_field_by_name)(void* runtime, void* basic_type, const char* field_name);

Gets a field by a field name, and returns it.

The C<runtime> argument is a L<runtime|SPVM::Document::NativeAPI::Runtime> object.

The C<basic_type> argument is a basic type object.

=head2 get_fields_length

  int32_t (*get_fields_length)(void* runtime, void* basic_type);

Returns the length of the fields of the basic type.

The C<runtime> argument is a L<runtime|SPVM::Document::NativeAPI::Runtime> object.

The C<basic_type> argument is a basic type object.

=head2 get_method_by_index

  void* (*get_method_by_index)(void* runtime, void* basic_type, int32_t method_index);

Gets a method by a method index, and returns it.

The C<runtime> argument is a L<runtime|SPVM::Document::NativeAPI::Runtime> object.

The C<basic_type> argument is a basic type object.

=head2 get_method_by_name

  void* (*get_method_by_name)(void* runtime, void* basic_type, const char* method_name);

Gets a method by a method name, and returns it.

The C<runtime> argument is a L<runtime|SPVM::Document::NativeAPI::Runtime> object.

The C<basic_type> argument is a basic type object.

=head2 get_methods_length

  int32_t (*get_methods_length)(void* runtime, void* basic_type);

Returns the length of the methods of the basic type.

The C<runtime> argument is a L<runtime|SPVM::Document::NativeAPI::Runtime> object.

The C<basic_type> argument is a basic type object.

=head2 get_anon_basic_type_by_index

  void* (*get_anon_basic_type_by_index)(void* runtime, void* basic_type, int32_t anon_basic_type_index);

Gets a anon basic type used by the basic type by an anon basic type index, and returns it.

The C<runtime> argument is a L<runtime|SPVM::Document::NativeAPI::Runtime> object.

The C<basic_type> argument is a basic type object.

=head2 get_anon_basic_types_length

    int32_t (*get_anon_basic_types_length)(void* runtime, void* basic_type);

Returns the length of the anon basic types used by the basic type.

The C<runtime> argument is a L<runtime|SPVM::Document::NativeAPI::Runtime> object.

The C<basic_type> argument is a basic type object.

=head2 has_interface

  int32_t (*has_interface)(void* runtime, void* basic_type, void* interface_basic_type);

If a basic type C<basic_type> has an interface C<interface_basic_type>, returns 1. Otherwise returns 0.

The C<runtime> argument is a L<runtime|SPVM::Document::NativeAPI::Runtime> object.

The C<basic_type> argument is a basic type object.

The C<interface_basic_type> argument is a basic type object.

=head2 is_super_class

  int32_t (*is_super_class)(void* runtime, void* super_basic_type, void* child_basic_type);

If a basic type C<super_basic_type> is a super class of a basic type C<child_basic_type>, returns 1. Otherwise returns 0.

The C<runtime> argument is a L<runtime|SPVM::Document::NativeAPI::Runtime> object.

The C<super_basic_type> argument is a basic type object.

The C<child_basic_type> argument is a basic type object.

=head2 get_file

C<const char* (*get_file)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* basic_type|SPVM::Document::NativeAPI::BasicType>);>

Returns the file path of the basic type.

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
