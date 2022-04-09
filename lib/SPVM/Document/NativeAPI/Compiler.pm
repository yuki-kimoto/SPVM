=head1 NAME

SPVM::Document::NativeAPI::Compiler - SPVM Compiler Native APIs

=head1 SYNOPSYS

  // Compiler API
  void* compiler_api = env->api->compiler;
  
  // New compiler
  void* compiler = compiler_api->new_compiler();
  
  // Compile SPVM
  int32_t status = compiler_api->compile_spvm(compiler, "MyClass");
  
  // Free compiler
  compiler_api->free_compiler(compiler);

=head1 DESCRIPTION

SPVM compiler native APIs are the public APIs to use compile SPVM modules.

=head1 List of Compiler Native APIs

=head2 new_compiler
  
  void* (*new_compiler)();

New a SVPM compiler.

=head2 free_compiler
  
  void (*free_compiler)(void* compiler);

Free a compiler.

=head2 set_start_line
  
  void (*set_start_line)(void* compiler, int32_t start_line);

Set the start line of the compiler.

=head2 get_start_line
  
  int32_t (*get_start_line)(void* compiler);

Get the start line of the compiler.

=head2 set_start_file
  
  void (*set_start_file)(void* compiler, const char* start_file);

Set the start file of the compiler.

=head2 get_start_file
  
  const char* (*get_start_file)(void* compiler);

Get the start file of the compiler.

=head2 add_module_dir
  
  void (*add_module_dir)(void* compiler, const char* module_dir);

Add a module searching directory of the compiler.

=head2 get_module_dirs_length
  
  int32_t (*get_module_dirs_length)(void* compiler);

Get the length of the module searching directories of the compiler.

=head2 get_module_dir

  const char* (*get_module_dir)(void* compiler, int32_t module_dir_id);

Get a searching directories of the compiler with the index.

=head2 compile_spvm
  
  int32_t (*compile_spvm)(void* compiler, const char* class_name);

Compile the SPVM class.

=head2 get_error_messages_length
  
  int32_t (*get_error_messages_length)(void* compiler);

Get the length of the compiler error messages.

=head2 get_error_message
  
  const char* (*get_error_message)(void* compiler, int32_t index);

Get a compiler error messages with the index.

=head2 get_class_id
  
  int32_t (*get_class_id)(void* compiler, const char* class_name);

Get class ID with the class name.

If the class doesn't found, return a negative value.

=head2 get_classes_length
  
  int32_t (*get_classes_length)(void* compiler);

Get the length of classes that is compiled by the compiler.

=head2 get_class_name
  
  const char* (*get_class_name)(void* compiler, int32_t class_id);

Get the class name with the class id.

=head2 is_anon_class
  
  int32_t (*is_anon_class)(void* compiler, int32_t class_id);

If the class is an anon class, return C<1>, otherwise return C<0>.

=head2 get_methods_length
  
  int32_t (*get_methods_length)(void* compiler, int32_t class_id);

Get the length of methods of the class.

=head2 get_method_id
  
  int32_t (*get_method_id)(void* compiler, int32_t class_id, int32_t method_index_of_class);

Get the method id with the class id and the method index of the class.

If the method doesn't found, return a negative value.

=head2 get_method_id_by_name
  
  int32_t (*get_method_id_by_name)(void* compiler, const char* class_name, const char* method_name);

Get the method id with the class name and the method name.

If the method doesn't found, return a negative value.

=head2 get_method_name
  
  const char* (*get_method_name)(void* compiler, int32_t method_id);

Get the method name with the method ID.

=head2 get_method_signature
  
  const char* (*get_method_signature)(void* compiler, int32_t method_id);

Get the method signature with the method ID.

=head2 is_anon_method
  
  int32_t (*is_anon_method)(void* compiler, int32_t method_id);

Get the method name with the method ID.

=head2 is_init_block_method
  
  int32_t (*is_init_block_method)(void* compiler, int32_t method_id);

If the method is the method of C<INIT> block, return C<1>, otherwise return C<0>.

=head2 is_native_method
  
  int32_t (*is_native_method)(void* compiler, int32_t method_id);

If the method is a native method, return C<1>, otherwise return C<0>.

=head2 is_precompile_method
  
  int32_t (*is_precompile_method)(void* compiler, int32_t method_id);

If the method is a precompile method, return C<1>, otherwise return C<0>.

=head2 build_runtime

  void* (*build_runtime)(void* compiler);

Build runtime information.

