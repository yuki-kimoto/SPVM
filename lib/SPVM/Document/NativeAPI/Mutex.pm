=head1 Name

SPVM::Document::NativeAPI::Mutex - Mutex Native APIs

=head1 Description

The mutex native APIs in L<SPVM> are the APIs for mutex.

=head1 Usage

  SPVM_API_MUTEX* api_mutex = env->api->mutex;
  
  void* mutex = api_mutex->new_instance();
  
  api_mutex->lock(env, stack, mutex);
  
  api_mutex->unlock(env, stack, mutex);
  
  api_mutex->free_instance(mutex);

=head1 Details

These APIs implements read-write locks in Linux and UNIX and L<slim reader/writer (SRW) locks|https://learn.microsoft.com/en-us/windows/win32/sync/slim-reader-writer--srw--locks> in Windows.

=head1 Native APIs

=head2 new_instance

C<void* (*new_instance)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">);>

Creates a new mutex and initialize it, and returns it.

=head2 free_instance

C<void (*free_instance)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* mutex);>

Destroys the mutex I<mutex> and frees it.

=head2 lock

C<void (*lock)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* mutex);>

Locks the mutex I<mutex>.

Calls the L<pthread_rwlock_wrlock|https://linux.die.net/man/3/pthread_rwlock_wrlock> function in Linux and UNIX.

Calls L<AcquireSRWLockExclusive|https://learn.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-acquiresrwlockexclusive> function in Windows.

=head2 unlock

C<void (*unlock)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* mutex);>

Unlocks the mutex I<mutex>.

Calls the L<pthread_rwlock_unlock|https://linux.die.net/man/3/pthread_rwlock_unlock> function in Linux and UNIX.

Calls L<ReleaseSRWLockExclusive|https://learn.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-releasesrwlockexclusive> function in Windows.

=head2 reader_lock

C<void (*reader_lock)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* mutex);>

Locks the mutex I<mutex> for reading.

Calls the L<pthread_rwlock_rdlock|https://linux.die.net/man/3/pthread_rwlock_rdlock> function in Linux and UNIX.

Calls L<AcquireSRWLockShared|https://learn.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-acquiresrwlockshared> function in Windows.

=head2 reader_unlock

C<void (*reader_unlock)(L<SPVM_ENV* env|SPVM::Document::NativeClass/"Runtime Environment">, L<SPVM_VALUE* stack|SPVM::Document::NativeClass/"Runtime Stack">, void* mutex);>

Unlocks the mutex I<mutex> for reading.

Calls the L<pthread_rwlock_unlock|https://linux.die.net/man/3/pthread_rwlock_unlock> function in Linux and UNIX.

Calls L<ReleaseSRWLockShared|https://learn.microsoft.com/en-us/windows/win32/api/synchapi/nf-synchapi-releasesrwlockshared> function in Windows.

=head1 Native API IDs

  0 new_instance
  1 free_instance
  2 lock
  3 unlock
  4 reader_lock
  5 reader_unlock

=head1 See Also

=over 2

=item * L<SPVM::Document::NativeAPI>

=item * L<SPVM::Document::NativeClass>

=item * L<SPVM::Document>

=back

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
