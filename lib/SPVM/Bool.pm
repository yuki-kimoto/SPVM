package SPVM::Bool;

1;

=head1 Name

SPVM::Bool - A Boolean value as An Object

=head1 Description

The Bool class in L<SPVM> represents a boolean value as an object.

=head1 Usage

  use Bool;
  
  my $true = Bool->TRUE;
  my $false = Bool->FALSE;
  
  my $true_value = $true->value;
  my $false_value = $false->value;

=head1 Details

This class is immutable.

This class is automatically loaded.

The Bool object is different behavior in bool context.

If L</"value"> field is 1, it is evaluated as true.

  if (Bool->TRUE) {
    # Run
  }

If L</"value"> field is 0, it is evaluated as false.

  if (Bool->FALSE) {
    # Not run
  }

The C<true> keyword is the same as C<Bool-E<gt>TRUE>.

  if (true) {
    # Run
  }

The C<false> keyword is the same as C<Bool-E<gt>FALSE>.
 
  if (false) {
    # Not run
  }

=head1 Fields

=head2 value

C<has value : ro byte;>

The value.

=head1 Class Methods

=head2 TRUE

C<static method TRUE : L<Bool|SPVM::Bool> ();>

Returns the true singleton object.

=head2 FALSE

C<static method FALSE : L<Bool|SPVM::Bool> ();>

Returns the false singleton object.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
