=head1 Name

SPVM::Document::NativeAPI::Type - Type Native APIs

=head1 Description

The type native APIs of L<SPVM> are the APIs to manipulate types.

=head1 Usage

  SPVM_API_TYPE* api_type = env->api->type;

=head1 Native APIs

=head2 can_assign

  int32_t (*can_assign)(void* runtime, void* dist_basic_type, int32_t dist_type_dimension, int32_t dist_type_flag, void* src_basic_type, int32_t src_type_dimension, int32_t src_type_flag);

If a source type can be assigned to a dist type, returns 1. Otherwise returns 0.

The C<runtime> argument is a runtime object.

The C<dist_basic_type> argument is a L<basic type|SPVM::Document::NativeAPI::BasicType> object.

The C<src_basic_type> argument is a L<basic type|SPVM::Document::NativeAPI::BasicType> object.

=head2 get_type_width

  int32_t (*get_type_width)(void* runtime, void* basic_type, int32_t dimension, int32_t flag);

=head2 get_type_width

  int32_t (*get_type_width)(void* runtime, void* basic_type, int32_t dimension, int32_t flag);

Gets the width of a type.

=head2 is_object_type

  int32_t (*is_object_type)(void* runtime, void* basic_type, int32_t type_dimension, int32_t flag);

If the type is object type, returns 1. Otherwise returns 0.

The C<runtime> argument is a runtime object.

The C<basic_type> argument is a L<basic type|SPVM::Document::NativeAPI::BasicType> object.

=head2 is_any_object_type

  int32_t (*is_any_object_type)(void* runtime, void* basic_type, int32_t type_dimension, int32_t flag);

If the type is any object type, returns 1. Otherwise returns 0.

The C<runtime> argument is a runtime object.

The C<basic_type> argument is a L<basic type|SPVM::Document::NativeAPI::BasicType> object.

=head2 is_object_array_type

  int32_t (*is_object_array_type)(void* runtime, void* basic_type, int32_t dimension, int32_t flag);

If the type is object array type, returns 1. Otherwise returns 0.

The C<runtime> argument is a runtime object.

The C<basic_type> argument is a L<basic type|SPVM::Document::NativeAPI::BasicType> object.

=head2 is_any_object_array_type

  int32_t (*is_any_object_array_type)(void* runtime, void* basic_type, int32_t type_dimension, int32_t flag);

If the type is any object array type, returns 1. Otherwise returns 0.

The C<runtime> argument is a runtime object.

The C<basic_type> argument is a L<basic type|SPVM::Document::NativeAPI::BasicType> object.

=head1 Native API IDs

  0 can_assign
  1 get_type_width
  2 is_object_type
  3 is_any_object_type
  4 is_object_array_type
  5 is_any_object_array_type

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
