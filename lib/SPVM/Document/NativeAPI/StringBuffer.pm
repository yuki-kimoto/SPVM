=head1 Name

SPVM::Document::NativeAPI::StringBuffer - SPVM String Buffer Native APIs

=head1 Usage

  // String Buffer API
  SPVM_ENV_STRING_BUFFER* string_buffer_api = env->api->string_buffer;
  
  // New string_buffer
  void* string_buffer = string_buffer_api->new_instance();
  
  // Free string_buffer
  string_buffer_api->free_instance(string_buffer);

=head1 Description

SPVM String Buffer Native APIs are the APIs for string buffers.

=head1 IDs of String Buffer Native APIs

String buffer native APIs have its IDs.

  0 new_instance
  1 free_instance
  2 get_string
  3 get_length

=head1 String Buffer Native APIs

=head2 new_instance

  void* (*new_instance)(void* allocator, int32_t capacity);

Creates a new string buffer object with an L<allocator|SPVM::Document::NativeAPI::Allocator> and a capacity.

=head2 free_instance

  void (*free_instance)(void* string_buffer);

Frees a string buffer object.

=head2 get_string

  const char* (*get_string)(void* string_buffer);

Gets the string saved in the string buffer object.

=head2 get_length

  int32_t (*get_length)(void* string_buffer);

Gets the length of the string in the string buffer object.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
