=head1 Name

SPVM::Document::NativeAPI::Internal - Internal Native APIs

=head1 Description

The internal native APIs of L<SPVM> are the APIs for internal operations.

=head1 Usage

  SPVM_API_INTERNAL* api_internal = env->api->internal;

=head1 Native APIs

=head1 Native API IDs

  0 leave_scope_local
  1 inc_ref_count
  2 dec_ref_count
  3 lock_object
  4 unlock_object

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
