=head1 Name

SPVM::Document::NativeAPI::Field - Field Native APIs

=head1 Description

The field native APIs of L<SPVM> are the APIs to get information of fields

=head1 Usage

  SPVM_API_FIELD* api_field = env->api->field;
  
  const char* name = api_field->get_name(runtime, field);

The C<field> is got by the L<get_field|SPVM::Document::NativeAPI::BasicType/"get_field"> and the L<get_field_by_name|SPVM::Document::NativeAPI::BasicType/"get_class_var_by_name"> basic type native API.

=head1 Native APIs

=head2 get_name

  const char* (*get_name)(void* runtime, void* field);

Returns the name of the field.

The C<runtime> argument is a L<runtime|SPVM::Document::NativeAPI::Runtime> object.

The C<field> argument is a L<field|SPVM::Document::NativeAPI::Field> object.

=head2 get_index

  int32_t (*get_index)(void* runtime, void* field);

Returns the index of the field.

The C<runtime> argument is a L<runtime|SPVM::Document::NativeAPI::Runtime> object.

The C<field> argument is a L<field|SPVM::Document::NativeAPI::Field> object.

=head2 get_offset

  int32_t (*get_offset)(void* runtime, void* field);

Returns the offset of the field.

The C<runtime> argument is a L<runtime|SPVM::Document::NativeAPI::Runtime> object.

The C<field> argument is a L<field|SPVM::Document::NativeAPI::Field> object.

=head2 get_basic_type

  void* (*get_basic_type)(void* runtime, void* field);

Returns the L<basic type|SPVM::Document::NativeAPI::BasicType> of the field.

The C<runtime> argument is a L<runtime|SPVM::Document::NativeAPI::Runtime> object.

The C<field> argument is a L<field|SPVM::Document::NativeAPI::Field> object.

=head2 get_type_dimension

  int32_t (*get_type_dimension)(void* runtime, void* field);

Returns the type dimension of the field.

The C<runtime> argument is a L<runtime|SPVM::Document::NativeAPI::Runtime> object.

The C<field> argument is a L<field|SPVM::Document::NativeAPI::Field> object.

=head2 get_type_flag

  int32_t (*get_type_flag)(void* runtime, void* field);

Returns the type flag of the field.

The C<runtime> argument is a L<runtime|SPVM::Document::NativeAPI::Runtime> object.

The C<field> argument is a L<field|SPVM::Document::NativeAPI::Field> object.

=head2 get_current_basic_type

  void* (*get_current_basic_type)(void* runtime, void* field);

Returns the current L<basic type|SPVM::Document::NativeAPI::BasicType> of the field.

The C<runtime> argument is a L<runtime|SPVM::Document::NativeAPI::Runtime> object.

The C<field> argument is a L<field|SPVM::Document::NativeAPI::Field> object.

=head1 Native API IDs

  0 get_name
  1 get_index
  2 get_offset
  3 get_basic_type
  4 get_type_dimension
  5 get_type_flag
  6 get_current_basic_type

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
