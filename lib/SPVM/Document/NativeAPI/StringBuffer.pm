=head1 Name

SPVM::Document::NativeAPI::StringBuffer - String Buffer Native APIs

=head1 Description

The string buffer native APIs in L<SPVM> are the APIs for string buffers

=head1 Usage

  SPVM_API_STRING_BUFFER* string_buffer_api = env->api->string_buffer;
  
  SPVM_API_ALLOCATOR* api_allocator = env->api->allocator;
  
  void* allocator = api_allocator->new_instance();
  
  int32_t capacity = 100;
  
  void* string_buffer = string_buffer_api->new_instance(allocator, capacity);
  
  string_buffer_api->free_instance(string_buffer);
  
  api_allocator->free_instance(allocator);

=head1 Native APIs

=head2 new_instance

C<void* (*new_instance)(L<void* allocator|SPVM::Document::NativeAPI::Allocator>, int32_t capacity);>

Creates a new L<string buffer|SPVM::Document::NativeAPI::StringBuffer> given its capacity I<capacity>, and returns it.

=head2 free_instance

C<void (*free_instance)(L<void* string_buffer|SPVM::Document::NativeAPI::StringBuffer>);>

Frees the string buffer I<string_buffer>.

=head2 get_string

C<const char* (*get_string)(L<void* string_buffer|SPVM::Document::NativeAPI::StringBuffer>);>

Returns the string stored in the string buffer I<string_buffer>.

=head2 get_length

C<int32_t (*get_length)(L<void* string_buffer|SPVM::Document::NativeAPI::StringBuffer>);>

Returns the length of the string stored in the string buffer I<string_buffer>.

=head1 Native API IDs

  0 new_instance
  1 free_instance
  2 get_string
  3 get_length

=head1 See Also

=over 2

=item * L<SPVM::Document::NativeAPI>

=item * L<SPVM::Document::NativeAPI::Allocator>

=item * L<SPVM::Document::NativeClass>

=item * L<SPVM::Document>

=back

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
