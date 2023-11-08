=head1 Name

SPVM::Document::NativeAPI::Internal - Internal Native APIs

=head1 Description

The internal native APIs of L<SPVM> are the APIs for internal operations.

=head1 Usage

  SPVM_API_INTERNAL* api_internal = env->api->internal;

=head1 Native APIs

=head2 get_ref_count

  int32_t (*get_ref_count)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);

Gets the reference count of the object.

=head2 inc_ref_count

  void (*inc_ref_count)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);

Increments the reference count of the object.

=head2 dec_ref_count

  void (*dec_ref_count)(SPVM_ENV* env, SPVM_VALUE* stack, void* object);

Decrements the reference count of the object.

=head2 leave_scope_local

  void (*leave_scope_local)(SPVM_ENV* env, SPVM_VALUE* stack, void** object_vars, int32_t* mortal_stack, int32_t* mortal_stack_top_ptr, int32_t original_mortal_stack_top);

Leaves scope.

=head1 Native API IDs

  0 get_ref_count
  1 inc_ref_count
  2 dec_ref_count
  3 leave_scope_local

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
