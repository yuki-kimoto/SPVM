package SPVM::Scope::Guard;

1;

=head1 Name

SPVM::Scope::Guard - Executing Handler at End of Scope

=head1 Usage
  
  use Scope::Guard;
  
  # Executing the handler at the end of the scope
  {
    my $guard = Scope::Guard->new(method : void () {
      print "End of Scope\n";
    });
    
    print "Foo";
  }
  
  # With a capture
  {
    my $value = 1;
    my $guard = Scope::Guard->new([$value : int] method : void () {
      print "$value\n";
    });
    
    print "Foo";
  }

=head1 Description

C<Scope::Guard> provides a feature to execue a hander at the end of the scope.

=head1 Fields

=head2 handler

  has handler : ro Scope::Guard::Handler;

A handler. The type is L<Scope::Guard::Handler|SPVM::Scope::Guard::Handler>.

=head1 Class Methods

=head2 new

  static method new : Scope::Guard ($handler : Scope::Guard::Handler);

Creates a new C<Scope::Guard> object and returns it.

The $handler is set to the L</"handler"> field.

The $handler is a L<Scope::Guard::Handler|SPVM::Scope::Guard::Handler> object.

Exceptions:

The $handler must be defined. Otherwize an exception is thrown.

=head1 Instance Methods

=head2 DESTROY

  method DESTROY : void ();

Executes the L</"handler">.

=head1 See Also

=head2 Scope::Guard

C<SPVM::Scope::Guard> is a port of Perl's L<Scope::Guard> to L<SPVM>.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
