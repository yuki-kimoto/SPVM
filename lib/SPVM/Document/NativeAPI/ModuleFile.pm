=head1 Name

SPVM::Document::NativeAPI::ModuleFile - Module File Native APIs

=head1 Description

The module file native APIs of L<SPVM> are the APIs to manipulate module files.

=head1 Usage

  void* mdoule_file = env->api->module_file->new_instance(compiler);

=head1 Native APIs

=head2 new_instance

  void* (*new_instance)(void* compiler);

Creates a new module file object and returns it.

=head2 get_module_name

  const char* (*get_module_name)(void* compiler, void* module_file);

Returns the module name.

=head2 set_module_name

  void (*set_module_name)(void* compiler, void* module_file, void* module_name);

Sets a module name.

=head2 get_file

  const char* (*get_file)(void* compiler, void* module_file);

Returns the file.

=head2 set_file

  void (*set_file)(void* compiler, void* module_file, void* file);

Sets a file.

=head2 get_dir

  const char* (*get_dir)(void* compiler, void* module_file);

Returns the directory.

=head2 set_dir

  void (*set_dir)(void* compiler, void* module_file, void* dir);

Sets a directory.

=head2 get_rel_file

  const char* (*get_rel_file)(void* compiler, void* module_file);

Returns the relative file.

=head2 set_rel_file

  void (*set_rel_file)(void* compiler, void* module_file, void* rel_file);

Sets a relative file.

=head2 get_content

  const char* (*get_content)(void* compiler, void* module_file);

Returns the content.

=head2 set_content

  void (*set_content)(void* compiler, void* module_file, void* content);

Sets a content.

=head2 get_content_length

  int32_t (*get_content_length)(void* compiler, void* module_file);

Returns the length of the content.

=head2 set_content_length

  void (*set_content_length)(void* compiler, void* module_file, int32_t content_length);

Sets the length of a content.

=head1 Native API IDs

  0  new_instance
  1  get_module_name
  2  set_module_name
  3  get_file
  4  set_file
  5  get_dir
  6  set_dir
  7  get_rel_file
  8  set_rel_file
  9  get_content
  10  set_content
  11  get_content_length
  12  set_content_length

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
