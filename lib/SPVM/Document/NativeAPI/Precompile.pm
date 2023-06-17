=head1 Name

SPVM::Document::NativeAPI::Precompile - SPVM Precompile Native APIs

=head1 Usage

  // Precompile Native API
  void* precompile_api = env->api->precompile;
  
  // New precompile
  void* precompile = precompile_api->new_object();
  
  // Free precompile
  precompile_api->free_object(precompile);

=head1 Description

SPVM Precompile Native APIs are public APIs to create precompile-source.

=head1 Ids Of Precompile Native APIs

Precompile native APIs have its IDs.

  0 new_object
  1 free_object
  2 set_runtime
  3 get_runtime
  4 build_source
  5 build_method_source

=head1 Precompile Native APIs

=head2 new_object

  void* (*new_object)();

Creates a new Precompile Native API object.

=head2 free_object
  
  void (*free_object)(void* precompile);

Frees a Precompile Native API object.

=head2 set_runtime

  void (*set_runtime)(void* precompile, void* runtime);

Sets a runtime to the Precompile Native API object.

=head2 get_runtime

  void* (*get_runtime)(void* precompile);

Gets the runtime from the Precompile Native API object.

=head2 build_source

  void (*build_source)(void* precompile, void* string_buffer, const char* basic_type_name);

Builds a precompiled class source. The content is added at the end of the buffer of L<string buffer|SPVM::Document::NativeAPI::StringBuffer> object.

=head2 build_method_source

  void (*build_method_source)(void* precompile, void* string_buffer, const char* basic_type_name, const char* method_name);

Builds a precompiled method source. The content is added at the end of the buffer of L<string buffer|SPVM::Document::NativeAPI::StringBuffer> object.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
