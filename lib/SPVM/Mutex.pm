package SPVM::Mutex;



1;

=head1 Name

SPVM::Mutex - Short Description

=head1 Description

Mutex class of L<SPVM> has methods to manipulate mutex.

=head1 Usage

  use Mutex;
  
  my $mutex = Mutex->new;
  
  $mutex->lock;
  
  $mutex->unlock;

=head1 Class Methods

  static method new : Mutex ();

=head1 Instance Methods

=head2 DESTROY

  method DESTROY : void ();

=head2 lock

  method lock : void ();

=head2 unlock

  method unlock : void ();

=head2 reader_lock

  method reader_lock : void ();

=head2 reader_unlock

  method reader_unlock : void ();

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

