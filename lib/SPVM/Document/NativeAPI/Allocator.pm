=head1 Name

SPVM::Document::NativeAPI::Allocator - SPVM Allocator Native APIs

=head1 Usage

  // Allocator API
  void* allocator_api = env->api->allocator;
  
  // New allocator
  void* allocator = allocator_api->new_object();
  
  // Free allocator
  allocator_api->free_object(allocator);

=head1 Description

SPVM Allocator Native APIs are the public APIs to alloc/free memories.

=head1 Ids Of Allocator Native APIs

Allocator native APIs have its IDs.

  0 new_object
  1 free_object

=head1 Allocator Native APIs

=head2 new_object

  void* (*new_object)(void);

Create a new allocator object.

=head2 free_object

  void (*free_object)(void* allocator);

Free an allocator object.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
