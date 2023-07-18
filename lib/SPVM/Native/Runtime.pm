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

  method get_basic_types_length : int ();

Returns the length of the all basic types in the runtime.

=head2 get_basic_type_by_id

  method get_basic_type_by_id : Native::BasicType ($id : int);

Returns a L<Native::BasicType|SPVM::Native::BasicType> object by a basic type ID.

Exceptions:

If The basic type cannot be found, an exception is throen.

=head2 get_basic_type_by_name

  method get_basic_type_by_name : Native::BasicType ($name : string);

Returns a L<Native::BasicType|SPVM::Native::BasicType> object by a basic type name.

Exceptions:

If The basic type cannot be found, an exception is throen.

=head2 build_precompile_module_source

  method build_precompile_module_source : string ($basic_type : Native::BasicType);

Builds the C source code of the class that contains C<precompile> methods and returns it.

=head2 build_precompile_method_source

  method method build_precompile_method_source : string ($method : Native::Method);

Builds the C source code of a C<precompile> method and returns it.

=head1 See Also

=head2 Native::Compiler

The L<get_runtime|SPVM::Native::Compiler/"get_runtime"> method in the L<Native::Compiler|SPVM::Native::Compiler> class builds a rutnime.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
