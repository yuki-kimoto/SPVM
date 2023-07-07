=head1 Name

SPVM::Document::NativeAPI::ClassVariable - SPVM Class Variable Native APIs

=head1 Description

SPVM Class Variable Native APIs are the APIs for class variables.

=head1 Usage

  SPVM_ENV_ClassVar* class_var_api = env->api->class_var;
  
  void* class_var = class_var_api->new_instance();
  
  class_var_api->free_instance(class_var);

=head1 Native APIs

=head2 new_instance

  void* (*new_instance)();

Creates a new class variable object.

=head2 free_instance

  void (*free_instance)(void* class_var);

Frees a class variable object.

=head1 Native API IDs

  0 new_instance
  1 free_instance

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
