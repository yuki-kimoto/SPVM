=head1 Name

SPVM::Document::NativeAPI::Argument - SPVM Argument Native APIs

=head1 Description

SPVM Argument Native APIs are the APIs for arguments.

=head1 Usage

  SPVM_API_Arg* api_arg = env->api->arg;
  
  void* arg_basic_type = api_arg->get_basic_type(arg);
  
=head1 Native APIs

=head2 get_basic_type

  void* (*get_basic_type)(void* runtime, void* arg);

=head2 get_type_dimension

  int32_t (*get_type_dimension)(void* runtime, void* arg);

=head2 get_type_flag

  int32_t (*get_type_flag)(void* runtime, void* arg);

=head1 Native API IDs

  0 get_basic_type
  1 get_type_dimension
  2 get_type_flag

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
