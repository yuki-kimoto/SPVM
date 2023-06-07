package SPVM::ExchangeAPI::Error;
use strict;
use warnings;

# Fields
sub code {
  my $self = shift;
  if (@_) {
    $self->{code} = $_[0];
    return $self;
  }
  else {
    return $self->{code};
  }
}

# Class Methods
sub new {
  my $error = shift;
  
  my $self = {
    code => 0,
    @_
  };
  
  bless $self, ref $error || $error;
  
  return $self;
}

1;

=head1 Name

SPVM::ExchangeAPI::Error - Error Code

=head1 Description

The SPVM::ExchangeAPI::Error class has methods to get and set an error code.

=head1 Usage
  
  my $error = SPVM::ExchangeAPI::Error->new;
  $error->code(2);
  my $die_error_code = $error->code;

=head1 Fields

=head2 code

  my $code = $error->code;
  $error->code($code);

Gets and sets an error code.

Examples:

  $error->code(2);
  my $code = $error->code;

=head1 Class Methods

=head2 new

  my $error = SPVM::ExchangeAPI::Error->new(%options);

Creates a new C<SPVM::ExchangeAPI::Error> object.

Options:

=over 2

=item * C<code>

An error code.

=back

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
