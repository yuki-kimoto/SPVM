=head1 Name

SPVM::Document::NativeAPI::Argument - Argument Native APIs

=head1 Description

The argument native APIs of L<SPVM> are the APIs to get information of arguments.

=head1 Usage

  SPVM_API_ARG* api_arg = env->api->arg;
  
  # ...
  
  void* basic_type = api_arg->get_basic_type(env->runtime, arg);

The C<arg> is got by the L<get_arg_by_index|SPVM::Document::NativeAPI::Method/"get_arg_by_index"> method native API.

=head1 Native APIs

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

=head1 Native API IDs

  0 get_basic_type
  1 get_type_dimension
  2 get_type_flag

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
