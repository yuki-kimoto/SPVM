=head1 Name

SPVM::Document::NativeAPI::Allocator - Allocator Native APIs

=head1 Description

The allocator native APIs in L<SPVM> are the APIs for memory allocators.

=head1 Usage

  SPVM_API_ALLOCATOR* api_allocator = env->api->allocator;
  
  void* allocator = api_allocator->new_instance();
  
  api_allocator->free_instance(allocator);

=head1 Native APIs

=head2 new_instance

C<void* (*new_instance)(void);>

Creates a new L<memory allocator|SPVM::Document::NativeAPI::Allocator> and returns it.

=head2 free_instance

C<void (*free_instance)(L<void* allocator|SPVM::Document::NativeAPI::Allocator>);>

Frees the memory allocator I<allocator>.

=head1 Native API IDs

  0 new_instance
  1 free_instance

=head1 See Also

=over 2

=item * L<SPVM::Document::NativeAPI>

=item * L<SPVM::Document::NativeAPI::StringBuffer>

=item * L<SPVM::Document::NativeClass>

=item * L<SPVM::Document>

=back

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
