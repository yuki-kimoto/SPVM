=head1 Name

SPVM::Document::NativeAPI::Method - SPVM Method Native APIs

=head1 Description

SPVM Method Native APIs are the APIs for methods.

=head1 Usage

  SPVM_ENV_METHOD* method_api = env->api->method;
  
  void* method = method_api->new_instance();
  
  method_api->free_instance(method);

=head1 Method Native APIs

=head2 new_instance

  void* (*new_instance)();

Creates a new method object.

=head2 free_instance

  void (*free_instance)(void* method);

Frees a method object.

=head1 Native API IDs

  0 new_instance
  1 free_instance

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
