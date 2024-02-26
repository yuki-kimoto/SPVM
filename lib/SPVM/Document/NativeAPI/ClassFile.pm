=head1 Name

SPVM::Document::NativeAPI::ClassFile - Class File Native APIs

=head1 Description

The class file native APIs of L<SPVM> are the APIs to get and set class file information.

=head1 Usage
  
  SPVM_API_CLASS_FILE* api_class_file = env->api->class_file;
  
  void* class_file = env->api->compiler->get_class_file(compiler, "MyClass");
  
  const char* class_name = api_class_file->get_class_name(compiler, class_file);

=head1 Native APIs

=head2 get_class_name

  const char* (*get_class_name)(void* compiler, void* class_file);

Returns the class name.

=head2 get_file

  const char* (*get_file)(void* compiler, void* class_file);

Returns the file path for display.

=head2 set_file

  void (*set_file)(void* compiler, void* class_file, const char* file);

Copies the file path I<file> for display and sets it.

=head2 get_dir

  const char* (*get_dir)(void* compiler, void* class_file);

Returns the directory where the class is loaded.

=head2 set_dir

  void (*set_dir)(void* compiler, void* class_file, const char* dir);

Copies the directory path I<dir> where the class is loaded and sets it.

=head2 get_rel_file

  const char* (*get_rel_file)(void* compiler, void* class_file);

Returns the relative file path of the class.

=head2 set_rel_file

  void (*set_rel_file)(void* compiler, void* class_file, const char* rel_file);

Copies a relative file path I<rel_file> of the class and sets it.

=head2 get_content

  const char* (*get_content)(void* compiler, void* class_file);

Returns the content.

=head2 set_content

  void (*set_content)(void* compiler, void* class_file, const char* content);

Copies a content I<content> and sets it.

=head2 get_content_length

  int32_t (*get_content_length)(void* compiler, void* class_file);

Returns the length of the content.

=head2 set_content_length

  void (*set_content_length)(void* compiler, void* class_file, int32_t content_length);

Sets the length of a content.

=head1 Native API IDs

  0 get_class_name
  1 get_file
  2 set_file
  3 get_dir
  4 set_dir
  5 get_rel_file
  6 set_rel_file
  7 get_content
  8 set_content
  9 get_content_length
  10 set_content_length

=head1 See Aloso

=over 2

=item * L<SPVM::Document::NativeAPI>

=item * L<SPVM::Document::NativeAPI::Compiler>

=item * L<SPVM::Document::NativeClass>

=item * L<SPVM::Document>

=back

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
