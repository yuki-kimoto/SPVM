=head1 Name

SPVM::Document::NativeAPI::Argument - Argument Native APIs

=head1 Description

The argument native APIs in L<SPVM> are the APIs to get definition information for arguments.

=head1 Usage

  SPVM_API_ARG* api_arg = env->api->arg;
  
  SPVM_API_METHOD* api_method = env->api->method;
  
  void* basic_type = env->get_basic_type(env, stack, "Foo");
  
  void* method = env->api->basic_type->get_method_by_name(env->runtime, basic_type, "get");
  
  void* arg = api_method->get_arg_by_index(env->runtime, method, 0);
  
  void* arg_basic_type = api_arg->get_basic_type(env->runtime, arg);

=head1 Native APIs

=head2 get_name

C<const char* (*get_name)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* arg|SPVM::Document::NativeAPI::Argument>);>

Returns the name of the argument I<arg>.

=head2 get_index

C<int32_t (*get_index)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* arg|SPVM::Document::NativeAPI::Argument>);>

Returns the index of the argument I<arg>.

=head2 get_basic_type

C<void* (*get_basic_type)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* arg|SPVM::Document::NativeAPI::Argument>);>

Returns the L<basic type|SPVM::Document::NativeAPI::BasicType> of the argument I<arg>.

=head2 get_type_dimension

C<int32_t (*get_type_dimension)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* arg|SPVM::Document::NativeAPI::Argument>);>

Returns the type dimention of the argument I<arg>.

=head2 get_type_flag

C<int32_t (*get_type_flag)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* arg|SPVM::Document::NativeAPI::Argument>);>

Returns the L<type flag ID|SPVM::Document::NativeAPI/"Type Flag IDs"> of the argument I<arg>.

=head2 get_stack_index

C<int32_t (*get_stack_index)(L<void* runtime|SPVM::Document::NativeAPI::Runtime>, L<void* arg|SPVM::Document::NativeAPI::Argument>);>

Returns the stack index of the argument I<arg>. The stack index is the position in a L<runtime stack|SPVM::Document::NativeClass/"Runtime Stack">.

=head1 Native API IDs

  0 get_name
  1 get_index
  2 get_basic_type
  3 get_type_dimension
  4 get_type_flag
  5 get_stack_index

=head1 See Aloso

=over 2

=item * L<SPVM::Document::NativeAPI>

=item * L<SPVM::Document::NativeAPI::Method>

=item * L<SPVM::Document::NativeClass>

=item * L<SPVM::Document>

=back

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
