=head1 Name

SPVM::Document::NativeAPI::Field - SPVM Field Native APIs

=head1 Description

SPVM Field Native APIs are the APIs for string buffers.

=head1 Usage

  SPVM_ENV_FIELD* field_api = env->api->field;
  
  void* field = field_api->new_instance();
  
  field_api->free_instance(field);

=head1 IDs of Field Native APIs

The field native APIs have its IDs.

  0 new_instance
  1 free_instance

=head1 Field Native APIs

=head2 new_instance

  void* (*new_instance)();

Creates a new string buffer object with an L<allocator|SPVM::Document::NativeAPI::Allocator> and a capacity.

=head2 free_instance

  void (*free_instance)(void* field);

Frees a string buffer object.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
