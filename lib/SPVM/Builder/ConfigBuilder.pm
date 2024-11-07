package SPVM::Builder::ConfigBuilder;

use strict;
use warnings;
use Carp ();

sub new {
  my $class = shift;
  
  my $self = {
    @_
  };
  
  return bless $self, ref $class || $class;
}

sub build_config { Carp::confess("Not yet implemented.") }

1;

=head1 Name

SPVM::Builder::ConfigBuilder - Config Builder

=head1 Description

SPVM::Builder::ConfigBuilder class is the base class of a config builder.

=head1 Usage

  package SPVM::MyClass::ConfigBuilder;
  
  use base 'SPVM::Builder::ConfigBuilder';
  
  sub build_config {
    my ($self, $config) = @_;
    
    # Build config
  }
  
  1;

=head1 Class Methods

=head2 new

  my $config_builder = SPVM::Builder::ConfigBuilder->new(%options);

Create a new object blessed by the class name of the invocant and returns it.

=head1 Instance Methods

=head2 build_config

  $config_builder->build_config($config);

Builds the config $config.

$config is a L<SPVM::Builder::Config> object.

This method must be implemented in a child class.

=head1 Examples

=over 2

=item * L<SPVM::Net::SSLeay::ConfigBuilder>

=back

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
