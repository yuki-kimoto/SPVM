package SPVM::Webkit::JSON::Bool;

1;

=head1 NAME

SPVM::Webkit::JSON::Bool - JSON Bool

=head1 SYNOPSYS

  my $json_true = SPVM::Webkit::JSON::Bool->TRUE;
  my $json_false = SPVM::Webkit::JSON::Bool->FALSE;
  
  my $bool_value = $bool_object_true->val;

=head1 METHODS

=head2 TRUE

  sub TRUE : SPVM::Webkit::JSON::Bool ()

Get L<SPVM::Webkit::JSON::Bool> object with true value.

=head2 FALSE

  sub FALSE : SPVM::Webkit::JSON::Bool ()

Get L<SPVM::Webkit::JSON::Bool> object with false value.

=head1 METHODS

=head2 val

  sub val : int ($self : self)

If Bool object has true value, return 1, else return 0.
