=head1 Name

SPVM::Document::NativeAPI::StringBuffer - String Buffer Native APIs

=head1 Description

The string buffer native APIs of L<SPVM> are the APIs to manipulate string buffers

=head1 Usage

  SPVM_API_STRING_BUFFER* string_buffer_api = env->api->string_buffer;
  
  void* string_buffer = string_buffer_api->new_instance();
  
  string_buffer_api->free_instance(string_buffer);

=head1 Native APIs

=head2 new_instance

  void* (*new_instance)(void* allocator, int32_t capacity);

Creates a new string buffer object and returns it.

The C<allocator> argument is an L<allocator|SPVM::Document::NativeAPI::Allocator> object.

The C<capacity> argument is the capacity of the string buffer.

=head2 free_instance

  void (*free_instance)(void* string_buffer);

Frees a string buffer object.

=head2 get_string

  const char* (*get_string)(void* string_buffer);

Gets the string in the string buffer object.

=head2 get_length

  int32_t (*get_length)(void* string_buffer);

Gets the length of the string in the string buffer object.

=head1 Native API IDs

  0 new_instance
  1 free_instance
  2 get_string
  3 get_length

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
