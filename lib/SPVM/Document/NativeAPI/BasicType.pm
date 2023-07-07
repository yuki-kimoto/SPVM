=head1 Name

SPVM::Document::NativeAPI::BasicType - SPVM Basic Type Native APIs

=head1 Description

SPVM Basic Type Native APIs are the APIs for basic types.

=head1 Usage

  SPVM_ENV_BASIC_TYPE* basic_type_api = env->api->basic_type;
  
  void* basic_type = basic_type_api->new_instance();
  
  basic_type_api->free_instance(basic_type);

=head1 Native APIs

=head2 new_instance

  void* (*new_instance)();

Creates a new basic type object.

=head2 free_instance

  void (*free_instance)(void* basic_type);

Frees a basic type object.

=head1 Native API IDs

  0 new_instance
  1 free_instance

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
