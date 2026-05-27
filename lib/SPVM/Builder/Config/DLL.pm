package SPVM::Builder::Config::DLL;

use parent 'SPVM::Builder::Config::Linker';

use strict;
use warnings;

sub new {
  my $self = shift->SUPER::new(@_);
  
  $self->output_type('dynamic_lib');
  
  return $self;
}

1;

=head1 Name

SPVM::Builder::Config::DLL - Config for Dynamic Link Libraries

=head1 Description

L<SPVM::Builder::Config::DLL> creates a config to generate dynamic link libraries.

=head1 Usage

  use SPVM::Builder::Config::DLL;

  my $config = SPVM::Builder::Config::DLL->new
  
  $config;

=head1 Super Class

L<SPVM::Builder::Config::Linker>

=head1 Class Methods

=head2 new

  my $config = SPVM::Builder::Config::DLL->new(%fields);

Creates a new L<SPVM::Builder::Config::DLL> object by calling C<new> method in the super class with I<%fields>,
and sets C<output_type> field to C<"dynamic_lib">,
and returns the new object.
