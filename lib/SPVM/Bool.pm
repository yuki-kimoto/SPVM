package SPVM::Bool;

1;

=head1 NAME

SPVM::Bool - Bool Utility

=head1 SYNOPSYS

  my $bool_object_true = SPVM::Bool->new_true;
  my $bool_object_false = SPVM::Bool->new_false;
  
  my $bool_value = $bool_object_true->val;

=head1 CONSTRUCTOR

=head2 new_true

  sub new_true : SPVM::Bool ()

Create L<SPVM::Bool> object with true value.

=head2 new_false

  sub new_false : SPVM::Bool ()

Create L<SPVM::Bool> object with false value.

=head1 METHODS

=head2 val

  sub val : int ($self : self)

If Bool object has true value, return 1, else return 0.

