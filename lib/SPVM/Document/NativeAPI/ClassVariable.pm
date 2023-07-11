=head1 Name

SPVM::Document::NativeAPI::ClassVariable - Class Variable Native APIs

=head1 Description

The class variable native APIs of L<SPVM> are the APIs to manipulate information of class variables.

=head1 Usage

  SPVM_API_CLASS_VAR* api_class_var = env->api->class_var;
  
  const char* class_var_name = api_class_var->get_name(runtime, class_var);

The C<class_var> is got by the L<get_class_var_by_index|SPVM::Document::NativeAPI::BasicType/"get_class_var_by_index"> and the L<get_class_var_by_name|SPVM::Document::NativeAPI::BasicType/"get_class_var_by_name"> basic type native API.

=head1 Native APIs

=head2 get_name

  const char* (*get_name)(void* runtime, void* class_var);

Returns the name of the class variable.

The C<runtime> argument is a L<runtime|SPVM::Document::NativeAPI::Runtime> object.

The C<class_var> argument is a L<class_var|SPVM::Document::NativeAPI::ClassVariable> object.

=head2 get_basic_type

  void* (*get_basic_type)(void* runtime, void* class_var);

Returns the L<basic type|SPVM::Document::NativeAPI::BasicType> of the class variable.

The C<runtime> argument is a L<runtime|SPVM::Document::NativeAPI::Runtime> object.

The C<class_var> argument is a L<class_var|SPVM::Document::NativeAPI::ClassVariable> object.

=head2 get_type_dimension

  int32_t (*get_type_dimension)(void* runtime, void* class_var);

Returns the type dimension of the class variable.

The C<runtime> argument is a L<runtime|SPVM::Document::NativeAPI::Runtime> object.

The C<class_var> argument is a L<class_var|SPVM::Document::NativeAPI::ClassVariable> object.

=head2 get_type_flag

  int32_t (*get_type_flag)(void* runtime, void* class_var);

Returns the type flag of the class variable.

The C<runtime> argument is a L<runtime|SPVM::Document::NativeAPI::Runtime> object.

The C<class_var> argument is a L<class_var|SPVM::Document::NativeAPI::ClassVariable> object.

=head2 get_current_basic_type

  void* (*get_current_basic_type)(void* runtime, void* class_var);

Returns the current L<basic type|SPVM::Document::NativeAPI::BasicType> of the class variable.

The C<runtime> argument is a L<runtime|SPVM::Document::NativeAPI::Runtime> object.

The C<class_var> argument is a L<class_var|SPVM::Document::NativeAPI::ClassVariable> object.

=head1 Native API IDs

  0 get_name
  1 get_basic_type
  2 get_type_dimension
  3 get_type_flag
  4 get_current_basic_type

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
