package SPVM::BaseObject;

sub DESTROY {
  my $self = shift;
  use Data::Dumper;
  warn Dumper $self;
}

1;
