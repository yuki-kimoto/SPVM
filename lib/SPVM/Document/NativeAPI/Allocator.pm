=head1 Name

SPVM::Document::NativeAPI::Allocator - SPVM Allocator Native APIs

=head1 Usage

  // Allocator API
  void* allocator_api = env->api->allocator;
  
  // New allocator
  void* allocator = allocator_api->new_allocator();
  
  // Free allocator
  allocator_api->free_allocator(allocator);

=head1 Description

SPVM Allocator Native APIs are the public APIs to alloc/free memories.

=head1 Ids Of Allocator Native APIs

Allocator native APIs have its IDs.

  0 new_allocator
  1 free_allocator

=head1 Allocator Native APIs

=head2 new_allocator

  void* (*new_allocator)();

Create a new allocator object.

=head2 free_allocator

  void (*free_allocator)(void* allocator);

Free an allocator object.
