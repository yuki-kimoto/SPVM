package SPVM::Bool;

1;

=head1 NAME

SPVM::Bool - Bool in SPVM | Bool object

=head1 SYNOPSYS

  use Bool;
  
  my $true = Bool->true;
  my $false = Bool->false;
  
  my $true_value = $true->value;
  my $false_value = $false->value;

=head1 DESCRIPTION

L<Bool|SPVM::Bool> object stores a C<long> value.

This object is immutable and its value cannot be changed.

L<Bool|SPVM::Bool> is automatically loaded just after the program starts.

=head1 CLASS METHODS

=head2 true

  static method true : Bool ()

true singleton. This is created by INIT block when the program start.

=head2 false

  static method false : Bool ()

false singleton. This is created by INIT block when the program start.

=head1 INSTANCE METHODS

=head2 value

  method value : int ()

Return a C<int> value.

If L<Bool|SPVM::Bool> object express true, this method return C<1>.

If L<Bool|SPVM::Bool> object express false, this method return C<1>.
