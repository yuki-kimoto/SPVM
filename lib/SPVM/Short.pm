package SPVM::Short;

1;

=head1 NAME

SPVM::Short - Short object

=head1 SYNOPSYS

  my $short_object = SPVM::Short->new(5);
  my $short_value = $short_object->val;

=head1 DESCRIPTION

Short object.

=head1 CONSTRUCTOR

=head2 new

  sub new : SPVM::Short ($value : short)

Create L<SPVM::Short> object with specified C<short> value.

=head1 METHODS

=head2 val

  sub val : short ($self : self)

Get C<short> value.
