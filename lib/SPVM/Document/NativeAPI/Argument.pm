=head1 Name

SPVM::Document::NativeAPI::Argument - SPVM Argument Native APIs

=head1 Description

SPVM Argument Native APIs are the APIs for arguments.

=head1 Usage

  SPVM_ENV_Arg* arg_api = env->api->arg;
  
  void* arg = arg_api->new_instance();
  
  arg_api->free_instance(arg);

=head1 Native APIs

=head2 new_instance

  void* (*new_instance)();

Creates a new argument object.

=head2 free_instance

  void (*free_instance)(void* arg);

Frees an argument object.

=head1 Native API IDs

  0 new_instance
  1 free_instance

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
