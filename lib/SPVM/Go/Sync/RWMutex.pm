package SPVM::Go::Sync::RWMutex;



1;

=head1 Name

SPVM::Go::Sync::RWMutex - Mutex

=head1 Description

Go::Sync::RWMutex class of L<SPVM> has methods to manipulate mutex.

=head1 Usage

  use Go::Sync::RWMutex;
  
  my $mutex = Go::Sync::RWMutex->new;
  
  $mutex->lock;
  
  $mutex->unlock;

=head1 Class Methods

  static method new : Go::Sync::RWMutex ();

=head1 Instance Methods

=head2 DESTROY

  method DESTROY : void ();

=head2 lock

  method lock : void ();

=head2 unlock

  method unlock : void ();

=head2 r_lock

  method r_lock : void ();

=head2 r_unlock

  method r_unlock : void ();

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

