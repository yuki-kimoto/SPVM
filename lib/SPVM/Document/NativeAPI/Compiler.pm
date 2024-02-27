=head1 Name

SPVM::Document::NativeAPI::Compiler - Compiler Native APIs

=head1 Usage

  SPVM_API_COMPILER* api_compiler = env->api->compiler;
  
  void* compiler = api_compiler->new_instance();
  
  api_compiler->add_include_dir(compiler, "lib");
  
  api_compiler->set_start_file(compiler, __FILE__);
  api_compiler->get_start_line(compiler, __LINE__ + 1);
  int32_t status = api_compiler->compile(compiler, "MyClass");
  
  api_compiler->free_instance(compiler);

=head1 Description

The compiler native APIs in L<SPVM> are the APIs for SPVM compilers.

=head1 Compiler Native APIs

=head2 new_instance

C<void* (*new_instance)(void);>

Creates a L<compiler|SPVM::Document::NativeAPI::Compiler> and returns it.

=head2 free_instance

C<void (*free_instance)(L<void* compiler|SPVM::Document::NativeAPI::Compiler>);>

Frees a compiler.

=head2 get_start_line

C<int32_t (*get_start_line)(L<void* compiler|SPVM::Document::NativeAPI::Compiler>);>

Returns the start line.

=head2 set_start_line

C<void (*set_start_line)(L<void* compiler|SPVM::Document::NativeAPI::Compiler>, int32_t start_line);>

Sets the start line I<start_line>.

=head2 get_start_file

C<const char* (*get_start_file)(L<void* compiler|SPVM::Document::NativeAPI::Compiler>);>

Returns the start file.

=head2 set_start_file

C<void (*set_start_file)(L<void* compiler|SPVM::Document::NativeAPI::Compiler>, const char* start_file);>

Set the start file I<start_file>.

=head2 get_include_dirs_length

C<int32_t (*get_include_dirs_length)(L<void* compiler|SPVM::Document::NativeAPI::Compiler>);>

Returns the length of the class searching directories.

=head2 get_include_dir

C<const char* (*get_include_dir)(L<void* compiler|SPVM::Document::NativeAPI::Compiler>, int32_t index);>

Returns a class searching directory given the index I<index>, and returns it.

=head2 add_include_dir
  
C<void (*add_include_dir)(L<void* compiler|SPVM::Document::NativeAPI::Compiler>, const char* include_dir);>

Adds the class searching directory I<include_dir> at the end of class searching directories.

=head2 prepend_include_dir
  
C<void (*prepend_include_dir)(L<void* compiler|SPVM::Document::NativeAPI::Compiler>, const char* include_dir);>

Prepends the class searching directory I<include_dir>.

=head2 clear_include_dirs
  
C<void (*clear_include_dirs)(SPVM_COMPILER* compiler);>

Removes all class searching directories.

=head2 add_class_file

C<void (*add_class_file)(L<void* compiler|SPVM::Document::NativeAPI::Compiler>, const char* class_name);>

Creates the L<class file|SPVM::Document::NativeAPI::ClassFile> for the class given by I<class_name>, and sets it.

If the class file already exists, nothing is performed.

=head2 delete_class_file

C<void (*delete_class_file)(L<void* compiler|SPVM::Document::NativeAPI::Compiler>, const char* class_name);>
  
Removes the L<class file|SPVM::Document::NativeAPI::ClassFile> for the class given by I<class_name>.

=head2 get_class_file

C<void* (*get_class_file)(L<void* compiler|SPVM::Document::NativeAPI::Compiler>, const char* class_name);>

Returns the L<class file|SPVM::Document::NativeAPI::ClassFile> for the class given by I<class_name>.

=head2 compile
  
C<int32_t (*compile)(L<void* compiler|SPVM::Document::NativeAPI::Compiler>, const char* class_name);>

Compiles a SPVM class. Classes loaded in the class and loaded classes are also compiled. The L<runtime|/"get_runtime"> is updated.

If the compilation is successful, returns 0, otherwise returns a non-zero value.

This native API can be called repeatedly to compile other classes.

=head2 get_error_messages_length
  
C<int32_t (*get_error_messages_length)(L<void* compiler|SPVM::Document::NativeAPI::Compiler>);>

Returns the length of the compilation error messages.

=head2 get_error_message
  
C<const char* (*get_error_message)(L<void* compiler|SPVM::Document::NativeAPI::Compiler>, int32_t index);>

Returns the compiler error message given the index I<index>.

=head2 get_runtime

C<void* (*get_runtime)(L<void* compiler|SPVM::Document::NativeAPI::Compiler>);>

Returns the L<runtime|SPVM::Document::NativeAPI::Runtime>.

=head2 compile_anon_class
  
C<int32_t (*compile_anon_class)(L<void* compiler|SPVM::Document::NativeAPI::Compiler>, const char* source, const char** anon_basic_type_name_ptr);>

Compiles a SPVM anon class given the source code I<source>. Classes loaded in the class and loaded classes are also compiled. The L<runtime|/"get_runtime"> is updated.

If the compilation is successful, returns 0, otherwise returns a non-zero value.

The generated anon class name is set to I<anon_basic_type_name_ptr>.

This native API can be called repeatedly to compile other classes.

=head1 Native API IDs

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
  10 add_class_file
  11 delete_class_file
  12 get_class_file
  13 compile
  14 get_error_message
  15 get_error_messages_length
  16 get_runtime
  17 prepend_include_dir

=head1 See Also

=over 2

=item * L<SPVM::Document::NativeAPI>

=item * L<SPVM::Document::NativeAPI::ClassFile>

=item * L<SPVM::Document::NativeAPI::Runtime>

=item * L<SPVM::Document::NativeClass>

=item * L<SPVM::Document>

=back

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
