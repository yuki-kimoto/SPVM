=head1 NAME

SPVM::Document::NativeAPI::StringBuffer - SPVM String Buffer Native APIs

=head1 SYNOPSYS

  // String Buffer API
  void* string_buffer_api = env->api->string_buffer;
  
  // New string_buffer
  void* string_buffer = string_buffer_api->new_string_buffer();
  
  // Free string_buffer
  string_buffer_api->free_string_buffer(string_buffer);

=head1 DESCRIPTION

SPVM String Buffer Native APIs are the public APIs to manipulate string buffers.

=head1 List of String Buffer Native APIs

