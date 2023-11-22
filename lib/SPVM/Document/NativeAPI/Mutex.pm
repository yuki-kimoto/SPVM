=head1 Name

SPVM::Document::NativeAPI::Mutex - Mutex Native APIs

=head1 Description

The mutex native APIs of L<SPVM> are the APIs to manipulate mutex.

=head1 Usage

  SPVM_API_MUTEX* api_mutex = env->api->mutex;
  
  void* mutex = api_mutex->new_instance();
  
  api_mutex->free_instance(mutex);

=head1 Native APIs

=head2 new_instance

  void* (*new_instance)(SPVM_ENV* env, SPVM_VALUE* stack);

Creates a new mutex object and returns it.

=head2 free_instance

  void (*free_instance)(SPVM_ENV* env, SPVM_VALUE* stack, void* mutex);

Frees a mutex object.

=head2 lock

  void (*lock)(SPVM_ENV* env, SPVM_VALUE* stack, void* mutex);

=head2 unlock

  void (*unlock)(SPVM_ENV* env, SPVM_VALUE* stack, void* mutex);

=head2 reader_lock

  void (*reader_lock)(SPVM_ENV* env, SPVM_VALUE* stack, void* mutex);

=head2 reader_unlock

  void (*reader_unlock)(SPVM_ENV* env, SPVM_VALUE* stack, void* mutex);

=head1 Native API IDs

  0 new_instance
  1 free_instance
  2 lock
  3 unlock
  4 reader_lock
  5 reader_unlock

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
