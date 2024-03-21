=head1 Name

SPVM::Document::NativeAPI::Field - Field Native APIs

=head1 Description

The field native APIs in L<SPVM> are the APIs to get definition information for fields.

=head1 Usage

  SPVM_API_FIELD* api_field = env->api->field;
  
  void* basic_type = env->get_basic_type(env, stack, "Foo");
  
  void* field = env->api->basic_type->get_field_by_name(env->runtime, basic_type, "value");
  
  const char* field_name = api_field->get_name(env->runtime, field);

=head1 Native APIs

=head2 get_name

C<const char* (*get_name)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* field|SPVM::Document::NativeAPI::Field>);>

Returns the name of the field I<field>.

=head2 get_index

C<int32_t (*get_index)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* field|SPVM::Document::NativeAPI::Field>);>

Returns the index of the field I<field>.

=head2 get_offset

C<int32_t (*get_offset)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* field|SPVM::Document::NativeAPI::Field>);>

Returns the byte offset of the field I<field>. The byte offset is the position in bytes where the field is allocated in its belonging class.

=head2 get_basic_type

C<void* (*get_basic_type)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* field|SPVM::Document::NativeAPI::Field>);>

Returns the L<basic type|SPVM::Document::NativeAPI::BasicType> of the field I<field>.

=head2 get_type_dimension

C<int32_t (*get_type_dimension)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* field|SPVM::Document::NativeAPI::Field>);>

Returns the type dimension of the field I<field>.

=head2 get_type_flag

C<int32_t (*get_type_flag)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* field|SPVM::Document::NativeAPI::Field>);>

Returns the L<type flag ID|SPVM::Document::NativeAPI/"Type Flag IDs"> of the field I<field>.

=head2 get_current_basic_type

C<void* (*get_current_basic_type)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* field|SPVM::Document::NativeAPI::Field>);>

Returns the L<basic type|SPVM::Document::NativeAPI::BasicType> that owns the field I<field>.

=head1 Native API IDs

  0 get_name
  1 get_index
  2 get_offset
  3 get_basic_type
  4 get_type_dimension
  5 get_type_flag
  6 get_current_basic_type

=head1 See Also

=over 2

=item * L<SPVM::Document::NativeAPI>

=item * L<SPVM::Document::NativeClass>

=item * L<SPVM::Document>

=back

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
