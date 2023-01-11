=head1 Name

SPVM::Document::NativeAPI::Compiler - SPVM Compiler Native APIs

=head1 Usage

  // New compiler
  void* compiler = env->api->compiler->new_object();
  
  // @INC
  env->api->compiler->add_module_dir(compiler, "lib");
  
  // Compile SPVM
  env->api->compiler->set_start_file(compiler, __FILE__);
  env->api->compiler->get_start_line(compiler, __LINE__ + 1);
  int32_t status = env->api->compiler->compile(compiler, "MyClass");
  
  // Free compiler
  env->api->compiler->free_object(compiler);

=head1 Description

SPVM compiler native APIs are the public APIs to use compile SPVM modules.

=head1 Ids Of Compiler Native APIs

Compiler native APIs have its IDs.

  0  new_object
  1  free_object
  2  set_start_line
  3  get_start_line
  4  set_start_file
  5  get_start_file
  6  add_module_dir
  7  get_module_dirs_length
  8  get_module_dir
  9  compile
  10 get_error_messages_length
  11 get_error_message
  12 create_runtime_codes
  13 clear_module_dirs

=head1 Compiler Native APIs

=head2 new_object
  
  void* (*new_object)();

Creates a compiler object.

=head2 free_object
  
  void (*free_object)(void* compiler);

Frees a compiler.

=head2 set_start_line
  
  void (*set_start_line)(void* compiler, int32_t start_line);

Sets the start line of the caller.

=head2 get_start_line
  
  int32_t (*get_start_line)(void* compiler);

Gets the start line of the caller.

=head2 set_start_file
  
  void (*set_start_file)(void* compiler, const char* start_file);

Set the start file of the caller. C<start_file> is copied.

=head2 get_start_file
  
  const char* (*get_start_file)(void* compiler);

Gets the start file of the caller.

=head2 add_module_dir
  
  void (*add_module_dir)(void* compiler, const char* module_dir);

Adds a module searching directory. C<module_dir> is copied.

=head2 get_module_dirs_length
  
  int32_t (*get_module_dirs_length)(void* compiler);

Gets the length of the module searching directories.

=head2 get_module_dir

  const char* (*get_module_dir)(void* compiler, int32_t index);

Gets a searching directory.

=head2 compile
  
  int32_t (*compile)(void* compiler, const char* class_name);

Compile SPVM classes.

=head2 get_error_messages_length
  
  int32_t (*get_error_messages_length)(void* compiler);

Gets the length of the compilation error messages.

=head2 get_error_message
  
  const char* (*get_error_message)(void* compiler, int32_t index);

Gets the compiler error messages.

=head2 create_runtime_codes

  int32_t* (*create_runtime_codes)(void* compiler, void* allocator);

Creates SPVM 32bit codes using a L<allocator|SPVM::Document::NativeAPI::Allocator> object and returns the address.

=head2 clear_module_dirs
  
  void (*clear_module_dirs)(SPVM_COMPILER* compiler);

Clear the module searching directories. The module searching directories are freed.
