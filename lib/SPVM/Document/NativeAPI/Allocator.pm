=head1 Name

SPVM::Document::NativeAPI::Allocator - Allocator Native APIs

=head1 Description

The allocator native APIs are the APIs to manipulate memory allocators.

=head1 Usage

  SPVM_API_ALLOCATOR* api_allocator = env->api->allocator;
  
  void* allocator = api_allocator->new_instance();
  
  api_allocator->free_instance(allocator);

=head1 Native APIs

=head2 new_instance

  void* (*new_instance)(void);

Creates a new allocator object.

=head2 free_instance

  void (*free_instance)(void* allocator);

Frees an allocator object.

=head1 Native API IDs

  0 new_instance
  1 free_instance

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
