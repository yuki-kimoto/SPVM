package SPVM::Native::Runtime;



1;

=head1 Name

SPVM::Native::Runtime - Native::Runtime

=head1 Description

C<SPVM::Native::Runtime> is the C<Native::Runtime> class in the L<SPVM> language. 

The instance has the runtime information such as operation codes, classes, methods, fields, class variables, constant strings.

This class provides only the minimal methods to get the information of classes and methods.

An instance of the C<Native::Runtime> class is build by the L<get_runtime|SPVM::Native::Compiler/"get_runtime"> method in the L<Native::Compiler|SPVM::Native::Compiler> class.

=head1 Usage

  use Native::Runtime;
  
  my $runtime = $compiler->get_runtime;
  
  my $stack = $env->new_stack;

=head1 Pointer

The C<Native::Runtime> class is a L<pointer class|SPVM::Document::Language/"Pointer Class">.

Its insntace has a pointer to a L<runtime|SPVM::Document::NativeAPI::Native::Runtime> object.

=head1 Instance Methods

=head2 get_basic_types_length

C<method get_basic_types_length : int ();>

Returns the length of the all basic types in the runtime.

=head2 get_basic_type_by_id

C<method get_basic_type_by_id : L<Native::BasicType|SPVM::Native::BasicType> ($id : int);>

Returns a L<Native::BasicType|SPVM::Native::BasicType> object by a basic type ID.

Exceptions:

If The basic type cannot be found, an exception is throen.

=head2 get_basic_type_by_name

C<method get_basic_type_by_name : L<Native::BasicType|SPVM::Native::BasicType> ($name : string);>

Returns a L<Native::BasicType|SPVM::Native::BasicType> object by a basic type name.

Exceptions:

If The basic type cannot be found, an exception is throen.

=head2 build_precompile_class_source

C<method build_precompile_class_source : string ($basic_type : L<Native::BasicType|SPVM::Native::BasicType>);>

Builds the C source code of the class that contains C<precompile> methods and returns it.

=head2 build_precompile_method_source

C<method method build_precompile_method_source : string ($method : L<Native::Method|SPVM::Native::Method>);>

Builds the C source code of a C<precompile> method and returns it.

=head2 get_compiler

C<method get_compiler : L<Native::Compiler|SPVM::Native::Compiler> ();>

Gets the compiler that built this runtime.

=head2 new_env

C<static method new_env : L<Native::Env|SPVM::Native::Env> ();>

Creates a new L<Native::Env|SPVM::Native::Env> ojbect, and returns it.

=head2 get_basic_type_names

C<method get_basic_type_names : string[] ();>

Gets all basic type names owned by the runtime, and return it.

=head2 get_method_names

C<method get_method_names : string[] ($class_name : string);>

Returns all method names owned by the class given the class name $class_name.

=head2 get_field_names

C<method get_field_names : string[] ($class_name : string);>

Returnsall field names owned by the class given the class name $class_name.

=head2 get_class_var_names

C<method get_class_var_names : string[] ($class_name : string);>

Returnsall class variable names owned by the class given the class name $class_name.

=head2 get_method_by_name

C<method get_method_by_name : L<Native::Method|SPVM::Native::Method> ($class_name : string, $method_name : string);>

Gets a method given the class name $class_name and the method name $method_name, returns it.

=head2 get_field_by_name

C<method get_field_by_name : L<Native::Field|SPVM::Native::Field> ($class_name : string, $field_name : string);>

Gets a field given the class name $class_name and the method name $method_name, returns it.

=head2 get_class_var_by_name

C<method get_class_var_by_name : L<Native::ClassVar|SPVM::Native::ClassVar> ($class_name : string, $class_var_name : string);>

Gets a class variable given the class name $class_name and the method name $method_name, returns it.

=head2 get_basic_types

C<method get_basic_types : L<Native::BasicType|SPVM::Native::BasicType>[] ($options : object[] = undef);>

Returns basic types.

=head1 See Also

=head2 Native::Compiler

The L<get_runtime|SPVM::Native::Compiler/"get_runtime"> method in the L<Native::Compiler|SPVM::Native::Compiler> class builds a rutnime.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
