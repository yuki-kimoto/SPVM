package SPVM::Native::Runtime::Info;



1;

=head1 Name

SPVM::Native::Runtime::Info - Information of A Runtime

=head1 Description

The Native::Runtime::Info class in L<SPVM> has methods to get information of a runtime.

=head1 Usage

  use Native::Runtime::Info;
  
  my $runtime_info = Native::Runtime::Info->new($runtime);

=head1 Fields

=head2 runtime

C<has runtime : L<Native::Runtime|SPVM::Native::Runtime>;>

The runtime.

=head1 Class Methods

C<static method new : Native::Runtime::Info ($runtime : L<Native::Runtime|SPVM::Native::Runtime>);>

=head1 Instance Methods

=head2 get_basic_type_names

C<method get_basic_type_names : string[] ();>

Gets all basic type names owned by the runtime, and return it.

=head2 get_class_names

C<method get_class_names : string[] ();>

Gets all basic type names by defined C<class> keyword owned by the runtime, and return it.

These contains the names of interface types and multi-numeric types.

=head2 get_method_names

C<method get_method_names : string[] ($class_name : string);>

Returns all method names owned by the class given the class name $class_name.

=head2 get_field_names

C<method get_field_names : string[] ($class_name : string);>

Returnsall field names owned by the class given the class name $class_name.

=head2 get_class_var_names

C<method get_class_var_names : string[] ($class_name : string);>

Returnsall class variable names owned by the class given the class name $class_name.

=head2 get_method

C<method get_method : L<Native::Method|SPVM::Native::Method> ($class_name : string, $method_name : string);>

Gets a method given the class name $class_name and the method name $method_name, returns it.

=head2 get_field

C<method get_field : L<Native::Field|SPVM::Native::Field> ($class_name : string, $field_name : string);>

Gets a field given the class name $class_name and the method name $method_name, returns it.

=head2 get_class_var

C<method get_class_var : L<Native::ClassVar|SPVM::Native::ClassVar> ($class_name : string, $class_var_name : string);>

Gets a class variable given the class name $class_name and the method name $method_name, returns it.

=head1 Copyright & License

Copyright (c) 2024 Yuki Kimoto

MIT License

