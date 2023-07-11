=head1 Name

SPVM::Document::NativeAPI::Runtime - Runtime Native APIs

=head1 Description

The runtime native APIs of L<SPVM> are the APIs to manipulate information of runtime.

=head1 Usage

  SPVM_API_RUNTIME* runtime_api = env->api->runtime;
  
  void* runtime = runtime_api->new_instance();
  
  env->api->runtime->free_instance(runtime);

=head1 Runtime Native APIs

=head2 new_instance

  void* (*new_instance)(void);

Creates a new runtime object and returns it.

=head2 free_instance

  void (*free_instance)(void* runtime);

Frees a runtime object.

=head2 get_object_header_size

  int32_t (*get_object_header_size)(void* runtime);

=head2 get_object_ref_count_offset

  int32_t (*get_object_ref_count_offset)(void* runtime);

=head2 get_object_length_offset

  int32_t (*get_object_length_offset)(void* runtime);

=head2 get_basic_type_by_id

  void* (*get_basic_type_by_id)(void* runtime, int32_t basic_type_id);

=head2 get_basic_type_by_name

  void* (*get_basic_type_by_name)(void* runtime, const char* basic_type_name);

=head2 get_basic_types_length

  int32_t (*get_basic_types_length)(void* runtime);

=head2 is_object_type

  int32_t (*is_object_type)(void* runtime, void* basic_type, int32_t type_dimension, int32_t flag);

=head2 can_assign

  int32_t (*can_assign)(void* runtime, void* dist_basic_type, int32_t dist_type_dimension, int32_t dist_type_flag, void* src_basic_type, int32_t src_type_dimension, int32_t src_type_flag);

=head2 build_precompile_module_source

  void (*build_precompile_module_source)(void* runtime, void* string_buffer, const char* module_name);

=head2 build_precompile_method_source

  void (*build_precompile_method_source)(void* runtime, void* string_buffer, const char* module_name, const char* method_name);
  
=head1 Native API IDs

  0 new_instance
  1 free_instance
  2 get_object_header_size
  3 get_object_ref_count_offset
  4 get_object_length_offset
  6 get_basic_type_by_name
  7 get_basic_types_length
  8 is_object_type
  9 can_assign
  10 build_precompile_module_source
  11 build_precompile_method_source

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
