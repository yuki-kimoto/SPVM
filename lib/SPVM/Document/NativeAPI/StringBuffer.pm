=head1 Name

SPVM::Document::NativeAPI::StringBuffer - SPVM String Buffer Native APIs

=head1 Synopsys

  // String Buffer API
  void* string_buffer_api = env->api->string_buffer;
  
  // New string_buffer
  void* string_buffer = string_buffer_api->new_string_buffer();
  
  // Free string_buffer
  string_buffer_api->free_string_buffer(string_buffer);

=head1 Description

SPVM String Buffer Native APIs are the public APIs for string buffers.

=head1 Ids Of String Buffer Native APIs

String buffer native APIs have its IDs.

  0 new_string_buffer_tmp
  1 free_string_buffer
  2 get_value
  3 get_length

=head1 String Buffer Native APIs

=head2 new_string_buffer_tmp

  void* (*new_string_buffer_tmp)();

Create a new temporary string buffer object.

=head2 free_string_buffer

  void (*free_string_buffer)(void* string_buffer);

Free the string buffer object.

=head2 get_value

  const char* (*get_value)(void* string_buffer);

Get the bytes of the string value of the string buffer object.

=head2 get_length

  int32_t (*get_length)(void* string_buffer);

Get the length of the string value of the string buffer object.
