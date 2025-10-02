package SPVM::Native::Compiler;



1;

=head1 Name

SPVM::Native::Compiler - Native::Compiler

=head1 Description

C<SPVM::Native::Compiler> is C<Native::Compiler> class in L<SPVM> language. It compiles SPVM source codes and builds the runtime.

The instance of L<Native::Runtime|SPVM::Native::Runtime> class is build by L</"get_runtime"> method in this class.

=head1 Usage

  use Native::Compiler;
  
  my $compiler = Native::Compiler->new;
  
  $compiler->add_include_dir("lib");
  
  $compiler->set_start_file(__FILE__);
  
  {
    my $basic_type_name = "Foo";
    $compiler->set_start_line(__LINE__ + 1);
    $compiler->compile($basic_type_name);
  }
  
  {
    my $basic_type_name = "Bar";
    $compiler->set_start_line(__LINE__ + 1);
    $compiler->compile($basic_type_name);
  }
  
  my $runtime = $compiler->get_runtime;

=head1 Pointer

The C<Native::Compiler> class is a L<pointer class|SPVM::Document::Language/"Pointer Class">.

Its insntace has a pointer to a L<compiler|SPVM::Document::NativeAPI::Native::Compiler> object.

=head1 Class Methods

=head2 new

C<static method new : L<Native::Compiler|SPVM::Native::Compiler> ();>

Creates a new C<Native::Compiler> object and returns it.

=head1 Instance Methods

=head2 get_include_dirs_length

C<method get_include_dirs_length : int ();>

Returns the length of the class search directories.

=head2 get_include_dir

C<method get_include_dir : string ($index : int);>

Returns a class search directory at the index $index.

=head2 add_include_dir

C<method add_include_dir : void ($include_dir : string);>

Adds a class search directory at the tail of the current class search directories.

=head2 prepend_include_dir

C<method prepend_include_dir : void ($include_dir : string);>

Adds a class search directory at the head of the current class search directories.

=head2 clear_include_dirs

C<method clear_include_dirs : void ();>

Removes all class search directories.

=head2 set_start_file

C<method set_start_file : void ($start_file : string);>

Sets the name of the file to start the compiling by L</"compile"> method.

=head2 set_start_line

C<method set_start_line : void ($start_line : int);>

Sets the line to start compiling by L</"compile"> method.

=head2 compile

C<method compile : void ($class_name : string);>

Compiles a class given by the class name $class_name.

This method can be called multiple times.

Exceptions:

If compilation errors occurred, an exception is thrown set eval_errro_id to the basic type ID of L<Error::Compile|SPVM::Error::Compile> class.

=head2 get_error_messages

C<method get_error_messages : string[] ();>

Returns compilation error messages in this compiling by L</"compile"> method.

=head2 get_runtime

C<method get_runtime : L<Native::Runtime|SPVM::Native::Runtime> ();>

Returns the runtime.

The return value is a L<Native::Runtime|SPVM::Native::Runtime> object.

=head2 get_class_file

C<method get_class_file : L<Native::ClassFile|SPVM::Native::ClassFile> ($class_name : string);>

Gets a L<Native::ClassFile> object by a class name, and returns it.

=head2 compile_anon_class

C<native method compile_anon_class : string ($source : string);>

Compiles a anon class, and return the generated anon class name.


This method can be called multiple times. 
Exceptions:

If compilation errors occurred, an exception is thrown set eval_errro_id to the basic type ID of L<Error::Compile|SPVM::Error::Compile> class.

Examples:
  
  use Native;
  use Native::Compiler;
  use Native::MethodCall;
  
  my $compiler = Native->get_current_compiler;
  
  my $source = <<'EOS';
  class {
    use Fn;
    static method sum : int ($num1 : int, $num2 : int) {
      return $num1 + $num2;
    }
  }
  EOS
  $compiler->set_start_file(__FILE__);
  $compiler->set_start_line(__LINE__ + 1);
  my $anon_class_name = $compiler->compile_anon_class($source);;
  
  my $ret = Native::MethodCall->call_class_method($anon_class_name, "sum", [(object)1, 2]);;
  
  say $ret->(Int)->value;

=head2 compile_script

C<native method compile_script : string ($source : string);>

Same as L</"compile_anon_class">.

Eamples:

  my $source = <<'EOS';
  use Fn;
  my $var = 1;
  say $var;
  EOS

=head1 See Also

=head2 Native::Runtime

The instance of L<Native::Runtime|SPVM::Native::Runtime> class is build by L</"get_runtime"> method in this class.

=head1 Copyright & License

Copyright 2023-2023 Yuki Kimoto, all rights reserved.

This program is free software; you can redistribute it and/or modify it
under the same terms as Perl itself.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
