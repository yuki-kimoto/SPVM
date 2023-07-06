=head1 Name

SPVM::Document::NativeAPI::Compiler - SPVM Compiler Native APIs

=head1 Usage

  // New compiler
  void* compiler = env->api->compiler->new_instance();
  
  // @INC
  env->api->compiler->add_include_dir(compiler, "lib");
  
  // Compile SPVM
  env->api->compiler->set_start_file(compiler, __FILE__);
  env->api->compiler->get_start_line(compiler, __LINE__ + 1);
  int32_t status = env->api->compiler->compile(compiler, "MyClass");
  
  // Free compiler
  env->api->compiler->free_instance(compiler);

=head1 Description

SPVM Compiler Native APIs are the APIs to compile SPVM modules.

=head1 IDs of Compiler Native APIs

Compiler native APIs have its IDs.

  0  new_instance
  1  free_instance
  2  set_start_line
  3  get_start_line
  4  set_start_file
  5  get_start_file
  6  add_include_dir
  7  get_include_dirs_length
  8  get_include_dir
  9  compile
  10 get_error_messages_length
  11 get_error_message
  12 create_runtime_codes
  13 clear_include_dirs
  14 get_module_file
  15 add_module_file
  16 build_runtime
  
=head1 Compiler Native APIs

=head2 new_instance
  
  void* (*new_instance)(void);

Creates a compiler object.

=head2 free_instance
  
  void (*free_instance)(void* compiler);

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

=head2 add_include_dir
  
  void (*add_include_dir)(void* compiler, const char* include_dir);

Adds a class searching directory. C<include_dir> is copied.

=head2 get_include_dirs_length
  
  int32_t (*get_include_dirs_length)(void* compiler);

Gets the length of the class searching directories.

=head2 get_include_dir

  const char* (*get_include_dir)(void* compiler, int32_t index);

Gets a searching directory.

=head2 compile
  
  int32_t (*compile)(void* compiler, const char* basic_type_name);

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

=head2 clear_include_dirs
  
  void (*clear_include_dirs)(SPVM_COMPILER* compiler);

Clear the class searching directories. The class searching directories are freed.

=head2 get_module_file

  void* (*get_module_file)(void* compiler, const char* module_name);

=head2 add_module_file

  void (*add_module_file)(void* compiler, const char* module_name, void* module_file);

=head2 build_runtime

void* (*build_runtime)(void* compiler);

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
