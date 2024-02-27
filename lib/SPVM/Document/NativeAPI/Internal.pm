=head1 Name

SPVM::Document::NativeAPI::Internal - Internal Native APIs

=head1 Description

The internal native APIs in L<SPVM> are the APIs for internal operations.

These APIs are used for the implementation of the SPVM language, so they should not be used.

=head1 Usage

  SPVM_API_INTERNAL* api_internal = env->api->internal;

=head1 Native APIs

=head2 get_ref_count

C<int32_t (*get_ref_count)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* object);>

Returns the reference count of the object I<object>.

=head2 inc_ref_count

C<void (*inc_ref_count)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* object);>

Increments the reference count of the object I<object>.

=head2 dec_ref_count

C<void (*dec_ref_count)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* object);>

Decrements the reference count of the object I<object>.

=head2 leave_scope_local

C<void (*leave_scope_local)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void** object_vars, int32_t* mortal_stack, int32_t* mortal_stack_top_ptr, int32_t original_mortal_stack_top);>

Performs a leaveing scope operation for local variables given object variables I<object_vars>, the mortal stack I<mortal_stack>, the address of the top of the mortal stack I<mortal_stack_top_ptr>, and the original top of the mortal stack I<original_mortal_stack_top>.

The value referenced by I<mortal_stack_top_ptr> is updated.

=head1 Native API IDs

  0 get_ref_count
  1 inc_ref_count
  2 dec_ref_count
  3 leave_scope_local

=head1 See Also

=over 2

=item * L<SPVM::Document::NativeAPI>

=item * L<SPVM::Document::NativeClass>

=item * L<SPVM::Document>

=back

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
