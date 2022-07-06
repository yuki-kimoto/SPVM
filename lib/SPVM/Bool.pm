package SPVM::Bool;

1;

=head1 Name

SPVM::Bool - Bool object

=head1 Usage

  use Bool;
  
  my $true = Bool->TRUE;
  my $false = Bool->FALSE;
  
  my $true_value = $true->value;
  my $false_value = $false->value;

=head1 Description

L<Bool|SPVM::Bool> object stores a C<long> value.

This object is immutable and its value cannot be changed.

L<Bool|SPVM::Bool> is automatically loaded just after the program starts.

=head1 Class Methods

=head2 TRUE

  static method TRUE : Bool ()

true singleton. This is created by INIT block when the program start.

=head2 FALSE

  static method FALSE : Bool ()

false singleton. This is created by INIT block when the program start.

=head1 Instance Methods

=head2 value

  method value : int ()

Return a C<int> value.

If L<Bool|SPVM::Bool> object express true, this method return C<1>.

If L<Bool|SPVM::Bool> object express false, this method return C<1>.

=head1 Bool Context

the object of Bool class is different behavior in bool context.

If the C<value> of Bool object is 1, it is evaluated as true.

  if (Bool->TRUE) {
    # Run
  }

If the C<value> of Bool object is 0, it is evaluated as false.

  if (Bool->FALSE) {
    # Not run
  }

=head1 Keywords

C<true> keyword means Bool->TRUE. C<false> keyword means Bool->FALSE.

  if (true) {
    # Run
  }

  if (false) {
    # Not run
  }
