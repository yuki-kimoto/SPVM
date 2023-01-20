package SPVM::Runtime;



1;

=head1 Name

SPVM::Runtime - Runtime

=head1 Description

C<SPVM::Runtime> is the C<Runtime> class in the L<SPVM> language. 

The instance has the runtime information such as operation codes, classes, methods, fields, class variables, constant strings.

This class provides only the minimal methods to get the information of classes and methods.

An instance of the C<Runtime> class is build by the L<build_runtime|SPVM::Compiler/"build_runtime"> method in the L<Compiler|SPVM::Compiler> class.

A execution environemt is build by the L<build_env|/"build_env"> method in this class.

=head1 Usage

  use Runtime;
  
  my $runtime = $compiler->build_runtime;
  
  my $class_names = $runtime->get_class_names;
  
  my $method_names = $runtime->get_method_names("Foo");
  
  my $env = $runtime->build_env;
  
  my $stack = $env->build_stack;

=head1 Pointer

The C<Runtime> class is a L<pointer class|SPVM::Document::Language/"Pointer Class">.

Its insntace has a pointer to a L<runtime|SPVM::Document::NativeAPI::Runtime> object.

=head1 Instance Methods

=head2 get_runtime_codes

  method get_runtime_codes : int[] ();

Gets the runtime codes and returns it.

=head2 get_classes_length

  method get_classes_length : int ();

Gets the length of the classes and returns it.

=head2 get_class_names

  method get_class_names : string[] ();

Gets the class names and returns it.

=head2 get_parent_class_name

  method get_parent_class_name : string ($class_name : string);

Gets the parent class name and returns it.

=head2 

  method get_method_names : string[] ($class_name : string, $options = undef : object[]);

Gets method names and returns it.

=head2 get_module_file

  method get_module_file : string ($class_name : string);

Gets the module file name and returns it.

=head2 build_precompile_class_source

  method build_precompile_class_source : string ($class_name : string);

Builds the C source code of the class that contains C<precompile> methods and return it.

=head2 get_anon_class_names

  method get_anon_class_names : string ($class_name : string);

Gets the anon class names and returns it.

=head2 get_method_is_class_method

  method get_method_is_class_method : int ($class_name : string, $method_name : string);

Checks if the method is a class method. If it is so, returns C<1>, otherwise returns C<0>.

=head2 build_precompile_method_source

  method build_precompile_method_source : string ($class_name : string, $method_name : string);

Builds the C source code of a C<precompile> method and return it.

=head2 get_native_method_address

  method get_native_method_address : Address ($class_name : string, $method_name : string);

Gets the address of a C<native> method and returns it.

The return type is the L<Address|SPVM::Address> class.

=head2 set_native_method_address

  method set_native_method_address : string ($class_name : string, $method_name : string, $address : Address);

Sets the address of a C<native> method.

The address is the L<Address|SPVM::Address> class.

=head2 get_precompile_method_address

  method get_precompile_method_address : Address ($class_name : string, $method_name : string);

Gets the address of a C<precompile> method and returns it.

The return type is the L<Address|SPVM::Address> class.

=head2 set_precompile_method_address

  method set_precompile_method_address : string ($class_name : string, $method_name : string, $address : Address);

Sets the address of a C<precompile> method.

The address is the L<Address|SPVM::Address> class.

=head2 build_env

  method build_env : Env ();

Builds an execution environemnt and returns it.

The return type is the L<Env|SPVM::Env> class.

=head2 DESTROY

  method DESTROY : void ();

The destructor.

=head1 See Also

=head2 Compiler

The L<build_runtime|SPVM::Compiler/"build_runtime"> method in the L<Compiler|SPVM::Compiler> class builds a rutnime.

=head2 Env

The instance of the L<Env|SPVM::Env> class is build by the L</"build_env"> method in this class.

=head1 Copyright & License

Copyright 2023-2023 Yuki Kimoto, all rights reserved.

This program is free software; you can redistribute it and/or modify it
under the same terms as Perl itself.
