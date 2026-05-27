package SPVM::Builder::Config::Exe;

use parent 'SPVM::Builder::Config::Linker';

use strict;
use warnings;

sub new {
  my $self = shift->SUPER::new(@_);
  
  $self->output_type('exe');
  
  return $self;
}

1;

=head1 Name

SPVM::Builder::Config::Exe - Config for Executable Files

=head1 Description

L<SPVM::Builder::Config::Exe> creates a config to generate executable files.

=head1 Usage

  use SPVM::Builder::Config::Exe;

  my $config = SPVM::Builder::Config::Exe->new
  
  $config;

=head1 Super Class

L<SPVM::Builder::Config::Linker>

=head1 Class Methods

=head2 new

  my $config = SPVM::Builder::Config::Exe->new(%options);

Creates a new L<SPVM::Builder::Config::Exe> object by calling C<new> method in the super class with I<%fields>,
and sets C<output_type> field to C<"exe">,
and returns the new object.
