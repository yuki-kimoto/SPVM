=head1 NAME

SPVM::Document::NativeAPI::Runtime - SPVM Runtime Native APIs

=head1 SYNOPSYS

  // Runtime API
  void* runtime_api = env->api->runtime;
  
  // New runtime
  void* runtime = runtime_api->new_runtime();
  
  // Free runtime
  runtime_api->free_runtime(runtime);

=head1 DESCRIPTION

SPVM runtime native APIs are the public APIs to use compile SPVM modules.

=head1 List of Runtime Native APIs

=head2 new_runtime

=head2 get_native_method_address
  
  void* (*get_native_method_address)(void* runtime, int32_t method_id);

Get the native method address.

=head2 get_precompile_method_address
  
  void* (*get_precompile_method_address)(void* runtime, int32_t method_id);

Get the precompile method address.

=head2 set_native_method_address
  
  void (*set_native_method_address)(void* runtime, int32_t method_id, void* address);

Set the native method address.

=head2 set_precompile_method_address
  
  void (*set_precompile_method_address)(void* runtime, int32_t method_id, void* address);

Set the precompile method address.

=head2 get_method_id_by_name

  int32_t (*get_method_id_by_name)(void* runtime, const char* class_name, const char* method_name);

Get the method ID by the class name and method name. If the method does not exists, a negative value is returned.

=head2 get_method_id_by_name

  int32_t (*get_method_id_by_name)(void* runtime, const char* class_name, const char* method_name);

Get the method ID by the class name and method name. If the method does not exists, a negative value is returned.

=head2 get_constant_string_value

  const char* (*get_constant_string_value)(void* runtime, int32_t string_id, int32_t* string_length);

Get the value and length of the string with the string ID. 
