package SPVM::Sync::Mutex;



1;

=head1 Name

SPVM::Sync::Mutex - Mutex

=head1 Description

The Sync::Mutex class in L<SPVM> has methods to manipulate mutex.

=head1 Usage

  use Sync::Mutex;
  
  my $mutex = Sync::Mutex->new;
  
  $mutex->lock;
  
  $mutex->unlock;

=head1 Class Methods

C<static method new : L<Sync::Mutex|SPVM::Sync::Mutex> ();>

Creates a new L<Sync::Mutex|SPVM::Sync::Mutex> object, initializes it by calling the L<new_instance|SPVM::Document::NativeAPI::Mutex/"new_instance"> mutex native API, and returns it.

=head1 Instance Methods

=head2 DESTROY

C<method DESTROY : void ();>

Destroys this instance by calling the L<free_instance|SPVM::Document::NativeAPI::Mutex/"free_instance"> mutex native API

=head2 lock

C<method lock : void ();>

Locks this mutex by calling the L<lock|SPVM::Document::NativeAPI::Mutex/"lock"> mutex native API.

=head2 unlock

C<method unlock : void ();>

UnLocks this mutex by calling the L<unlock|SPVM::Document::NativeAPI::Mutex/"unlock"> mutex native API.

=head2 reader_lock

C<method reader_lock : void ();>

Locks this mutex for reading by calling the L<reader_lock|SPVM::Document::NativeAPI::Mutex/"reader_lock"> mutex native API.

=head2 reader_unlock

C<method reader_unlock : void ();>

UnLocks this mutex locked by the L</"reader_lock"> method by calling the L<reader_unlock|SPVM::Document::NativeAPI::Mutex/"reader_unlock"> mutex native API.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

