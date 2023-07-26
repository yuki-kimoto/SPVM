=head1 Name

SPVM::Document::NativeAPI::Compiler - Compiler Native APIs

=head1 Usage

  void* compiler = env->api->compiler->new_instance();
  
  env->api->compiler->add_include_dir(compiler, "lib");
  
  env->api->compiler->set_start_file(compiler, __FILE__);
  env->api->compiler->get_start_line(compiler, __LINE__ + 1);
  int32_t status = env->api->compiler->compile(compiler, "MyClass");
  
  env->api->compiler->free_instance(compiler);

=head1 Description

The compiler native APIs of L<SPVM> are the APIs to compile SPVM modules.

=head1 Compiler Native APIs

=head2 new_instance
  
  void* (*new_instance)(void);

Creates a compiler object.

=head2 free_instance
  
  void (*free_instance)(void* compiler);

Frees a compiler.

=head2 get_start_line
  
  int32_t (*get_start_line)(void* compiler);

Gets the start line.

=head2 set_start_line
  
  void (*set_start_line)(void* compiler, int32_t start_line);

Sets a start line.

=head2 get_start_file
  
  const char* (*get_start_file)(void* compiler);

Gets the start file.

=head2 set_start_file
  
  void (*set_start_file)(void* compiler, const char* start_file);

Set a start file.

=head2 get_include_dirs_length
  
  int32_t (*get_include_dirs_length)(void* compiler);

Gets the length of the directories for searching modules.

=head2 get_include_dir

  const char* (*get_include_dir)(void* compiler, int32_t index);

Gets a directory for searching modules by an index.

=head2 add_include_dir
  
  void (*add_include_dir)(void* compiler, const char* include_dir);

Adds a directory for searching modules.

=head2 clear_include_dirs
  
  void (*clear_include_dirs)(SPVM_COMPILER* compiler);

Clears the directories for searching modules.

=head2 add_module_file

  void (*add_module_file)(void* compiler, const char* module_name);

Adds a L<module file|SPVM::Document::NativeAPI::ModuleFile> object for a module.

If the module file already exists, nothing is performed.

=head2 delete_module_file

  void (*delete_module_file)(void* compiler, const char* module_name);
  
Deletes a L<module file|SPVM::Document::NativeAPI::ModuleFile> object for a module.

=head2 get_module_file

  void* (*get_module_file)(void* compiler, const char* module_name);

Gets the L<module file|SPVM::Document::NativeAPI::ModuleFile> object for a module.

=head2 set_module_file

  void (*set_module_file)(void* compiler, const char* module_name, void* module_file);

Sets a L<module file|SPVM::Document::NativeAPI::ModuleFile> object for a module.

=head2 compile
  
  int32_t (*compile)(void* compiler, const char* module_name);

Compiles SPVM modules.

=head2 get_error_messages_length
  
  int32_t (*get_error_messages_length)(void* compiler);

Gets the length of the compilation error messages.

=head2 get_error_message
  
  const char* (*get_error_message)(void* compiler, int32_t index);

Gets a compiler error message by an index.

=head2 get_runtime

  void* (*get_runtime)(void* compiler);

Gets the runtime.

=head1 Compiler Native API IDs

  0 new_instance 
  1 free_instance 
  2 get_start_line 
  3 set_start_line 
  4 get_start_file 
  5 set_start_file 
  6 get_include_dirs_length 
  7 get_include_dir 
  8 add_include_dir 
  9 clear_include_dirs 
  10 get_module_file 
  11 set_module_file 
  12 compile 
  13 get_error_message 
  14 get_error_messages_length 
  15 get_runtime 

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
