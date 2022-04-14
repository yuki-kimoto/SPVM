=head1 NAME

SPVM::Document::NativeAPI::Allocator - SPVM Allocator Native APIs

=head1 SYNOPSYS

  // Allocator API
  void* allocator_api = env->api->allocator;
  
  // New allocator
  void* allocator = allocator_api->new_allocator();
  
  // Free allocator
  allocator_api->free_allocator(allocator);

=head1 DESCRIPTION

SPVM Allocator Native APIs are the public APIs to alloc/free memories.

=head1 List of Allocator Native APIs

