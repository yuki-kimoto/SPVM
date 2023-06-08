package SPVM::ExchangeAPI::Error;
use strict;
use warnings;

# Fields
sub id {
  my $self = shift;
  if (@_) {
    $self->{id} = $_[0];
    return $self;
  }
  else {
    return $self->{id};
  }
}

# Class Methods
sub new {
  my $error = shift;
  
  my $self = {
    id => 0,
    @_
  };
  
  bless $self, ref $error || $error;
  
  return $self;
}

1;

=head1 Name

SPVM::ExchangeAPI::Error - Error Code

=head1 Description

The SPVM::ExchangeAPI::Error class has methods to get and set an error id.

=head1 Usage
  
  my $error = SPVM::ExchangeAPI::Error->new;
  $error->id(2);
  my $die_error_id = $error->id;

=head1 Fields

=head2 id

  my $id = $error->id;
  $error->id($id);

Gets and sets an error id.

Examples:

  $error->id(2);
  my $id = $error->id;

=head1 Class Methods

=head2 new

  my $error = SPVM::ExchangeAPI::Error->new(%options);

Creates a new C<SPVM::ExchangeAPI::Error> object.

Options:

=over 2

=item * C<id>

An error id.

=back

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
