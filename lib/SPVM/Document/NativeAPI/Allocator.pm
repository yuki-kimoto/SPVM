=head1 Name

SPVM::Document::NativeAPI::Allocator - SPVM Allocator Native APIs

=head1 Usage

  // Allocator API
  SPVM_API_ALLOCATOR* allocator_api = env->api->allocator;
  
  // New allocator
  void* allocator = allocator_api->new_instance();
  
  // Free allocator
  allocator_api->free_instance(allocator);

=head1 Description

SPVM Allocator Native APIs are the APIs to allocate and free memories.

=head1 IDs of Allocator Native APIs

Allocator native APIs have its IDs.

  0 new_instance
  1 free_instance

=head1 Allocator Native APIs

=head2 new_instance

  void* (*new_instance)(void);

Creates a new allocator object.

=head2 free_instance

  void (*free_instance)(void* allocator);

Frees an allocator object.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
