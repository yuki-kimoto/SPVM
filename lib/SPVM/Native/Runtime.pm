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
  
  my $method_names = $runtime->get_method_names("Foo");
  
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

=head2 get_basic_type_name

  method get_basic_type_name : string[] ();

Gets the all basic type names in the runtime and returns it.

=head2 get_basic_type_parent_name

  method get_basic_type_parent_name : string ($basic_type_name : string);

Gets the parent basic type name and returns it.

=head2 get_method_names

  method get_method_names : string[] ($basic_type_name : string, $options : object[] = undef);

Gets method names and returns it.

Options:

The options are key-value pairs. The key is the C<string> type.

=over 2

=item * C<native> : Int

Gets only C<native> methods if this option is true.

=item * C<precompile> : Int

Gets only C<precompile> methods if this option is true.

=item * C<enum> : Int

Get only C<enum> methods if this option is true.

=back

=head2 get_module_file

  method get_module_file : string ($basic_type_name : string);

Gets the module file name and returns it.

=head2 build_precompile_module_source

  method build_precompile_module_source : string ($basic_type : Native::BasicType);

Builds the C source code of the class that contains C<precompile> methods and returns it.

=head2 get_method_is_class_method

  method get_method_is_class_method : int ($basic_type_name : string, $method_name : string);

Checks if the method is a class method. If it is so, returns 1, otherwise returns 0.

=head2 build_precompile_method_source

  method method build_precompile_method_source : string ($method : Native::Method);

Builds the C source code of a C<precompile> method and returns it.

=head2 get_native_method_address

  method get_native_method_address : Address ($basic_type_name : string, $method_name : string);

Gets the address of a C<native> method and returns it.

The return type is the L<Address|SPVM::Address> class.

=head2 set_native_method_address

  method set_native_method_address : string ($basic_type_name : string, $method_name : string, $address : Address);

Sets the address of a C<native> method.

The address is the L<Address|SPVM::Address> class.

=head2 get_precompile_method_address

  method get_precompile_method_address : Address ($basic_type_name : string, $method_name : string);

Gets the address of a C<precompile> method and returns it.

The return type is the L<Address|SPVM::Address> class.

=head2 set_precompile_method_address

  method set_precompile_method_address : string ($basic_type_name : string, $method_name : string, $address : Address);

Sets the address of a C<precompile> method.

The address is the L<Address|SPVM::Address> class.

=head1 See Also

=head2 Native::Compiler

The L<get_runtime|SPVM::Native::Compiler/"get_runtime"> method in the L<Native::Compiler|SPVM::Native::Compiler> class builds a rutnime.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
