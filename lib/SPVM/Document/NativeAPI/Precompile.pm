=head1 Name

SPVM::Document::NativeAPI::Precompile - SPVM Precompile Native APIs

=head1 Usage

  // Precompile API
  void* precompile_api = env->api->precompile;
  
  // New precompile
  void* precompile = precompile_api->new_precompile();
  
  // Free precompile
  precompile_api->free_precompile(precompile);

=head1 Description

SPVM Precompile Native APIs are public APIs to create precompile-source.

=head1 Ids Of Precompile Native APIs

Precompile native APIs have its IDs.

  0 new_precompile
  1 free_precompile
  2 set_runtime
  3 get_runtime
  4 create_precompile_source

=head1 Precompile Native APIs

=head2 new_precompile

  void* (*new_precompile)();

New a precompile object.

=head2 free_precompile
  
  void (*free_precompile)(void* precompile);

Free a precompile object.

=head2 set_runtime

  void (*set_runtime)(void* precompile, void* runtime);

Set a runtime to the precompile object.

=head2 get_runtime

  void* (*get_runtime)(void* precompile);

Get the runtime from the precompile object.

=head2 create_precompile_source

  void (*create_precompile_source)(void* precompile, void* string_buffer, const char* class_name);

Create precompile-source. The created source is saved to L<string buffer|SPVM::Document::NativeAPI::StringBuffer> object.
