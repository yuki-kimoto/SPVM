=head1 Name

SPVM::Document::NativeAPI::ClassVariable - Class Variable Native APIs

=head1 Description

The class variable native APIs in L<SPVM> are the APIs to get definition information of class variables.

=head1 Usage

  SPVM_API_CLASS_VAR* api_class_var = env->api->class_var;
  
  void* basic_type = env->get_basic_type(env, stack, "Foo");
  
  void* class_var = env->api->basic_type->get_class_var_by_name(env->runtime, basic_type, "$VAR");
  
  const char* class_var_name = api_class_var->get_name(env->runtime, class_var);

=head1 Native APIs

=head2 get_name

C<const char* (*get_name)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* class_var|SPVM::Document::NativeAPI::ClassVariable>);>

Returns the name of the class variable.

=head2 get_index

C<int32_t (*get_index)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* class_var|SPVM::Document::NativeAPI::ClassVariable>);>

Returns the index of the class variable.

The C<class_var> argument is a L<class_var|SPVM::Document::NativeAPI::ClassVar> object.

=head2 get_basic_type

C<void* (*get_basic_type)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* class_var|SPVM::Document::NativeAPI::ClassVariable>);>

Returns the L<basic type|SPVM::Document::NativeAPI::BasicType> of the class variable.

=head2 get_type_dimension

C<int32_t (*get_type_dimension)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* class_var|SPVM::Document::NativeAPI::ClassVariable>);>

Returns the type dimension of the class variable.

=head2 get_type_flag

C<int32_t (*get_type_flag)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* class_var|SPVM::Document::NativeAPI::ClassVariable>);>

Returns the L<type flag ID|SPVM::Document::NativeAPI/"Type Flag IDs"> of the class variable.

=head2 get_current_basic_type

C<void* (*get_current_basic_type)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* class_var|SPVM::Document::NativeAPI::ClassVariable>);>

Returns the L<basic type|SPVM::Document::NativeAPI::BasicType> the class variable I<class_var> is defined.

=head1 Native API IDs

  0 get_name
  1 get_index
  2 get_basic_type
  3 get_type_dimension
  4 get_type_flag
  5 get_current_basic_type

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
