=head1 Name

SPVM::Document::NativeAPI::StringBuffer - SPVM String Buffer Native APIs

=head1 Usage

  // String Buffer API
  void* string_buffer_api = env->api->string_buffer;
  
  // New string_buffer
  void* string_buffer = string_buffer_api->new_string_buffer();
  
  // Free string_buffer
  string_buffer_api->free_instance(string_buffer);

=head1 Description

SPVM String Buffer Native APIs are the public APIs for string buffers.

=head1 Ids Of String Buffer Native APIs

String buffer native APIs have its IDs.

  0 new_instance
  1 free_instance
  2 get_value
  3 get_length

=head1 String Buffer Native APIs

=head2 new_instance

  void* (*new_instance)(void* allocator, int32_t capacity);

Create a new temporary string buffer object.

=head2 free_instance

  void (*free_instance)(void* string_buffer);

Free the string buffer object.

=head2 get_value

  const char* (*get_value)(void* string_buffer);

Get the bytes of the string value of the string buffer object.

=head2 get_length

  int32_t (*get_length)(void* string_buffer);

Get the length of the string value of the string buffer object.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
