=head1 Name

SPVM::Document::NativeAPI::Precompile - SPVM Precompilation Native APIs

=head1 Usage

  // Precompilation Native API
  SPVM_ENV_PRECOMPILE* precompile_api = env->api->precompile;
  
  // New precompilation instance
  void* precompile = precompile_api->new_instance();
  
  // Free precompilation instance
  precompile_api->free_instance(precompile);

=head1 Description

SPVM Precompilation Native APIs are the APIs to create C source codes for precompilation.

=head1 IDs of Precompile Native APIs

Precompile native APIs have its IDs.

  0 new_instance
  1 free_instance
  2 set_runtime
  3 get_runtime
  4 build_module_source
  5 build_method_source

=head1 Precompile Native APIs

=head2 new_instance

  void* (*new_instance)(void);

Creates a new Precompile Native API object.

=head2 free_instance
  
  void (*free_instance)(void* precompile);

Frees a Precompile Native API object.

=head2 set_runtime

  void (*set_runtime)(void* precompile, void* runtime);

Sets a L<runtime|SPVM::Document::NativeAPI::Runtime> object.

=head2 get_runtime

  void* (*get_runtime)(void* precompile);

Gets the L<runtime|SPVM::Document::NativeAPI::Runtime> object.

=head2 build_module_source

  void (*build_module_source)(void* precompile, void* string_buffer, const char* module_name);

Builds a C source code of a module for precompilation. The content is added at the end of the string of a L<string buffer|SPVM::Document::NativeAPI::StringBuffer> object.

=head2 build_method_source

  void (*build_method_source)(void* precompile, void* string_buffer, const char* module_name, const char* method_name);

Builds a C source code of a method. The content is added at the end of the string of a L<string buffer|SPVM::Document::NativeAPI::StringBuffer> object.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
