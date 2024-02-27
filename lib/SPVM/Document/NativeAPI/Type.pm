=head1 Name

SPVM::Document::NativeAPI::Type - Type Native APIs

=head1 Description

The type native APIs in L<SPVM> are the APIs to get type information.

=head1 Usage

  SPVM_API_TYPE* api_type = env->api->type;

=head1 Native APIs

=head2 can_assign

C<int32_t (*can_assign)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* dist_basic_type|SPVM::Document::NativeAPI::BasicType>, int32_t dist_type_dimension, int32_t dist_type_flag, L<void* src_basic_type|SPVM::Document::NativeAPI::BasicType>, int32_t src_type_dimension, int32_t src_type_flag);>

If the source type given by I<src_basic_type>, I<src_type_dimension>, and I<src_type_flag> can be assigned to the dist type given by I<dist_basic_type>, I<dist_type_dimension>, and I<dist_type_flag> , returns 1, otherwise returns 0.

=head2 get_type_width

C<int32_t (*get_type_width)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* basic_type|SPVM::Document::NativeAPI::BasicType>, int32_t type_dimension, int32_t type_flag);>

Returns the L<type width|SPVM::Document::Language::Types/"Type Width"> of the type given by I<basic_type>, I<type_dimension>, and I<type_flag>.

=head2 is_object_type

C<int32_t (*is_object_type)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* basic_type|SPVM::Document::NativeAPI::BasicType>, int32_t type_dimension, int32_t type_flag);>

If the type given by I<basic_type>, I<type_dimension>, and I<type_flag> is an object type, returns 1, otherwise returns 0.

=head2 is_any_object_type

C<int32_t (*is_any_object_type)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* basic_type|SPVM::Document::NativeAPI::BasicType>, int32_t type_dimension, int32_t type_flag);>

If the type given by I<basic_type>, I<type_dimension>, and I<type_flag> is the any object type C<objct>, returns 1, otherwise returns 0.

=head2 is_object_array_type

C<int32_t (*is_object_array_type)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* basic_type|SPVM::Document::NativeAPI::BasicType>, int32_t type_dimension, int32_t type_flag);>

If the type given by I<basic_type>, I<type_dimension>, and I<type_flag> is an object array type, returns 1, otherwise returns 0.

=head2 is_any_object_array_type

C<int32_t (*is_any_object_array_type)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* basic_type|SPVM::Document::NativeAPI::BasicType>, int32_t type_dimension, int32_t type_flag);>

If the type given by I<basic_type>, I<type_dimension>, and I<type_flag> is the any object array type C<objct[]>, returns 1, otherwise returns 0.

=head1 Native API IDs

  0 can_assign
  1 get_type_width
  2 is_object_type
  3 is_any_object_type
  4 is_object_array_type
  5 is_any_object_array_type

=head1 See Also

=over 2

=item * L<SPVM::Document::NativeAPI>

=item * L<SPVM::Document::NativeAPI::BasicType>

=item * L<SPVM::Document::NativeClass>

=item * L<SPVM::Document>

=back

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
