=head1 Name

SPVM::Document::NativeAPI::Argument - Argument Native APIs

=head1 Description

The argument native APIs of L<SPVM> are the APIs to manipulate information of arguments.

=head1 Usage

  SPVM_API_ARG* api_arg = env->api->arg;
  
  # ...
  
  void* basic_type = api_arg->get_basic_type(env->runtime, arg);

The C<arg> is got by the L<get_arg_by_index|SPVM::Document::NativeAPI::Method/"get_arg_by_index"> method native API.

=head1 Native APIs

=head2 get_name

  const char* (*get_name)(void* runtime, void* arg);

Returns the name of the argument.

The C<runtime> argument is a L<runtime|SPVM::Document::NativeAPI::Runtime> object.

The C<arg> argument is a L<arg|SPVM::Document::NativeAPI::Argument> object.

=head2 get_index

  int32_t (*get_index)(void* runtime, void* arg);

Returns the index of the argument.

The C<runtime> argument is a L<runtime|SPVM::Document::NativeAPI::Runtime> object.

The C<arg> argument is a L<arg|SPVM::Document::NativeAPI::Argument> object.

=head2 get_basic_type

  void* (*get_basic_type)(void* runtime, void* arg);

Returns the L<basic type|SPVM::Document::NativeAPI::BasicType> of the argument.

The C<runtime> argument is a L<runtime|SPVM::Document::NativeAPI::Runtime> object.

The C<arg> argument is a L<arg|SPVM::Document::NativeAPI::Arg> object.

=head2 get_type_dimension

  int32_t (*get_type_dimension)(void* runtime, void* arg);

Returns the type dimention of the argument.

The C<runtime> argument is a L<runtime|SPVM::Document::NativeAPI::Runtime> object.

The C<arg> argument is a L<arg|SPVM::Document::NativeAPI::Arg> object.

=head2 get_type_flag

  int32_t (*get_type_flag)(void* runtime, void* arg);

Returns the type flag of the argument.

The C<runtime> argument is a L<runtime|SPVM::Document::NativeAPI::Runtime> object.

The C<arg> argument is a L<arg|SPVM::Document::NativeAPI::Arg> object.

=head2 get_stack_index

  int32_t (*get_stack_index)(void* runtime, void* arg);

Gets the stack index of the argument.

=head1 Native API IDs

  0 get_name
  1 get_index
  2 get_basic_type
  3 get_type_dimension
  4 get_type_flag
  5 get_stack_index

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
