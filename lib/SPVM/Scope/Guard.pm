package SPVM::Scope::Guard;

1;

=head1 Name

SPVM::Scope::Guard - Executing Callback at End of Scope

=head1 Usage
  
  use Scope::Guard;
  
  # Executing the callback at the end of the scope
  {
    Scope::Guard->new(method : void () {
      print "End of Scope\n";
    });
    
    print "Foo";
  }
  
  # With field definitions
  {
    my $value = 1;
    Scope::Guard->new([$value : int] method : void () {
      print "$value\n";
    });
    
    print "Foo";
  }

=head1 Description

The Scope::Guard class has the methods to execute a callback at the end of the scope.

=head1 Fields

=head2 callback

C<has callback : ro L<Callback|SPVM::Callback>;>

A callback called at the end of the scope.

=head1 Class Methods

=head2 new

C<static method new : L<Scope::Guard|SPVM::Scope::Guard> ($callback : L<Callback|SPVM::Callback>);>

Creates a new C<Scope::Guard> object and returns it.

$callback is set to L</"callback"> field.

Exceptions:

$callback must be defined. Otherwise an exception is thrown.

=head1 Instance Methods

=head2 DESTROY

C<method DESTROY : void ();>

Executes the L</"callback">.

=head1 See Also

=head2 Scope::Guard

C<SPVM::Scope::Guard> is a port of Perl's L<Scope::Guard> to L<SPVM>.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
