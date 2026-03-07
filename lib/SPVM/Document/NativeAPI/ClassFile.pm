=head1 Name

SPVM::Document::NativeAPI::ClassFile - Class File Native APIs

=head1 Description

The class file native APIs of L<SPVM> are the APIs to get and set class file information.

=head1 Usage
  
  SPVM_API_CLASS_FILE* api_class_file = env->api->class_file;
  
  SPVM_NATIVE_COMPILER* compiler = env->api->compiler->new_instance();
  
  SPVM_NATIVE_CLASS_FILE* class_file = env->api->compiler->get_class_file(compiler, "MyClass");
  
  const char* class_name = api_class_file->get_class_name(compiler, class_file);

=head1 Native APIs

=head2 get_class_name

C<const char* (*get_class_name)(L<SPVM_NATIVE_COMPILER* compiler|SPVM::Document::NativeAPI::Compiler>, L<SPVM_NATIVE_CLASS_FILE* class_file|SPVM::Document::NativeAPI::ClassFile>);>

Returns the class name of the class file I<class_file>.

=head2 get_file

C<const char* (*get_file)(L<SPVM_NATIVE_COMPILER* compiler|SPVM::Document::NativeAPI::Compiler>, L<SPVM_NATIVE_CLASS_FILE* class_file|SPVM::Document::NativeAPI::ClassFile>);>

Returns the file path for display. This is a field of the class file I<class_file>.

=head2 set_file

C<void (*set_file)(L<SPVM_NATIVE_COMPILER* compiler|SPVM::Document::NativeAPI::Compiler>, L<SPVM_NATIVE_CLASS_FILE* class_file|SPVM::Document::NativeAPI::ClassFile>, const char* file);>

Copies I<file> and sets it to the file path for display. This is a field of the class file I<class_file>.

=head2 get_dir

C<const char* (*get_dir)(L<SPVM_NATIVE_COMPILER* compiler|SPVM::Document::NativeAPI::Compiler>, L<SPVM_NATIVE_CLASS_FILE* class_file|SPVM::Document::NativeAPI::ClassFile>);>

Returns the directory where the class is loaded. This is a field of the class file I<class_file>.

=head2 set_dir

C<void (*set_dir)(L<SPVM_NATIVE_COMPILER* compiler|SPVM::Document::NativeAPI::Compiler>, L<SPVM_NATIVE_CLASS_FILE* class_file|SPVM::Document::NativeAPI::ClassFile>, const char* dir);>

Copies the directory path I<dir>, and sets it to the directory where the class is loaded. This is a field of the class file I<class_file>.

=head2 get_rel_file

C<const char* (*get_rel_file)(L<SPVM_NATIVE_COMPILER* compiler|SPVM::Document::NativeAPI::Compiler>, L<SPVM_NATIVE_CLASS_FILE* class_file|SPVM::Document::NativeAPI::ClassFile>);>

Returns the relative file path of the class file I<class_file>.

=head2 set_rel_file

C<void (*set_rel_file)(L<SPVM_NATIVE_COMPILER* compiler|SPVM::Document::NativeAPI::Compiler>, L<SPVM_NATIVE_CLASS_FILE* class_file|SPVM::Document::NativeAPI::ClassFile>, const char* rel_file);>

Copies I<rel_file> and sets it to the relative file path of the class file I<class_file>.

=head2 get_content

C<const char* (*get_content)(L<SPVM_NATIVE_COMPILER* compiler|SPVM::Document::NativeAPI::Compiler>, L<SPVM_NATIVE_CLASS_FILE* class_file|SPVM::Document::NativeAPI::ClassFile>);>

Returns the content of the class file I<class_file>.

=head2 set_content

C<void (*set_content)(L<SPVM_NATIVE_COMPILER* compiler|SPVM::Document::NativeAPI::Compiler>, L<SPVM_NATIVE_CLASS_FILE* class_file|SPVM::Document::NativeAPI::ClassFile>, const char* content);>

Copies the content I<content> and sets it to the content of the class file I<class_file>.

=head2 get_content_length

C<int32_t (*get_content_length)(L<SPVM_NATIVE_COMPILER* compiler|SPVM::Document::NativeAPI::Compiler>, L<SPVM_NATIVE_CLASS_FILE* class_file|SPVM::Document::NativeAPI::ClassFile>);>

Returns the length of the content of the class file I<class_file>.

=head2 set_content_length

C<void (*set_content_length)(L<SPVM_NATIVE_COMPILER* compiler|SPVM::Document::NativeAPI::Compiler>, L<SPVM_NATIVE_CLASS_FILE* class_file|SPVM::Document::NativeAPI::ClassFile>, int32_t content_length);>

Sets I<content_length> to the length of the content of the class file I<class_file>.

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

=head1 See Also

=over 2

=item * L<SPVM::Document::NativeAPI>

=item * L<SPVM::Document::NativeAPI::Compiler>

=item * L<SPVM::Document::NativeClass>

=item * L<SPVM::Document>

=back

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
