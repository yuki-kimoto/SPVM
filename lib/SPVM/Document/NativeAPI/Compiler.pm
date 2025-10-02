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

Creates a new L<compiler|SPVM::Document::NativeAPI::Compiler> and returns it.

=head2 free_instance

C<void (*free_instance)(L<void* compiler|SPVM::Document::NativeAPI::Compiler>);>

Frees the compiler I<compiler>.

=head2 get_start_line

C<int32_t (*get_start_line)(L<void* compiler|SPVM::Document::NativeAPI::Compiler>);>

Returns the value of the C<start_line> field. The starting line for an exception call stack is stored to this field.

=head2 set_start_line

C<void (*set_start_line)(L<void* compiler|SPVM::Document::NativeAPI::Compiler>, int32_t start_line);>

Sets I<start_line> to the C<start_line> field.

=head2 get_start_file

C<const char* (*get_start_file)(L<void* compiler|SPVM::Document::NativeAPI::Compiler>);>

Returns the value of the C<start_file> field. The starting file path for an exception call stack is stored to this field.

=head2 set_start_file

C<void (*set_start_file)(L<void* compiler|SPVM::Document::NativeAPI::Compiler>, const char* start_file);>

Sets I<start_file> to the C<start_file> field.

=head2 get_include_dirs_length

C<int32_t (*get_include_dirs_length)(L<void* compiler|SPVM::Document::NativeAPI::Compiler>);>

Returns the length of the class search directories.

=head2 get_include_dir

C<const char* (*get_include_dir)(L<void* compiler|SPVM::Document::NativeAPI::Compiler>, int32_t index);>

Searches a class search directory given the index I<index>.

If it is found, returns it. Otherwise, returns C<NULL>.

=head2 add_include_dir
  
C<void (*add_include_dir)(L<void* compiler|SPVM::Document::NativeAPI::Compiler>, const char* include_dir);>

Adds I<include_dir> at the end of the class search directories.

=head2 clear_include_dirs
  
C<void (*clear_include_dirs)(SPVM_COMPILER* compiler);>

Removes all class search directories.

=head2 add_class_file

C<void (*add_class_file)(L<void* compiler|SPVM::Document::NativeAPI::Compiler>, const char* class_name);>

Creates the L<class file|SPVM::Document::NativeAPI::ClassFile> for the class given by I<class_name>, and adds it to the symbol table of the compiler I<compiler>.

If the class file already exists, nothing is performed.

=head2 delete_class_file

C<void (*delete_class_file)(L<void* compiler|SPVM::Document::NativeAPI::Compiler>, const char* class_name);>
  
Removes the L<class file|SPVM::Document::NativeAPI::ClassFile> for the class given by the class name I<class_name>.

=head2 get_class_file

C<void* (*get_class_file)(L<void* compiler|SPVM::Document::NativeAPI::Compiler>, const char* class_name);>

Returns the L<class file|SPVM::Document::NativeAPI::ClassFile> for the class given by the class name I<class_name>.

=head2 compile
  
C<int32_t (*compile)(L<void* compiler|SPVM::Document::NativeAPI::Compiler>, const char* class_name);>

Compiles the SPVM class given by the class name I<class_name>. Classes loaded by the class and classes subsequently loaded are also compiled.

The L<runtime|/"get_runtime"> is build.

If the compilation is successful, returns 0. Otherwise, returns a non-zero value.

This native API can be called repeatedly to compile other classes.

=head2 get_error_messages_length
  
C<int32_t (*get_error_messages_length)(L<void* compiler|SPVM::Document::NativeAPI::Compiler>);>

Returns the length of the compilation error messages.

=head2 get_error_message

C<const char* (*get_error_message)(L<void* compiler|SPVM::Document::NativeAPI::Compiler>, int32_t index);>

Searches the compiler error message given the index I<index>.

If it is found, returns it. Otherwise, returns C<NULL>.

=head2 get_runtime

C<void* (*get_runtime)(L<void* compiler|SPVM::Document::NativeAPI::Compiler>);>

Returns the L<runtime|SPVM::Document::NativeAPI::Runtime> that is build by the compiler I<compiler>.

=head2 prepend_include_dir
  
C<void (*prepend_include_dir)(L<void* compiler|SPVM::Document::NativeAPI::Compiler>, const char* include_dir);>

Prepends I<include_dir> to the class search directory.

=head2 compile_anon_class
  
C<int32_t (*compile_anon_class)(L<void* compiler|SPVM::Document::NativeAPI::Compiler>, const char* source, const char** anon_basic_type_name_ptr);>

Compiles an SPVM anon class given the source code I<source>. Classes loaded by the class and classes subsequently loaded are also compiled.

The L<runtime|/"get_runtime"> is build.

If the compilation is successful, returns 0. Otherwise, returns a non-zero value.

The generated anon class name is set to the value referenced by I<anon_basic_type_name_ptr>.

This native API can be called repeatedly to compile other classes.

Examples:

  const char* source = "
    class {
      use Fn;
      
      static method main : void () {
        my $var = 1;
        
        say $var;
      }
    }
  ";

=head2 compile_script

C<int32_t (*compile_script)(L<void* compiler|SPVM::Document::NativeAPI::Compiler>, const char* source, const char** anon_basic_type_name_ptr);>

Same as L</"compile_anon_class">.

Examples:

  const char* source = "
    use Fn;
    
    my $var = 1;
    
    say $var;
  ";

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
  18 compile_anon_class
  19 compile_script

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
