package SPVM::Builder::Config::Exe;

use parent 'SPVM::Builder::Config::Linker';

use strict;
use warnings;

sub new {
  my $class = shift;
  
  my $self = $class->SUPER::new(
    output_type => 'exe',
    @_,
  );
  
  return $self;
}

1;

=head1 Name

SPVM::Builder::Config::Exe - Configuration for Executable Files

=head1 Description

L<SPVM::Builder::Config::Exe> is a class to manage configurations for generating executable files.

This class inherits from L<SPVM::Builder::Config::Global> and sets the C<output_type> field to C<exe> by default.

=head1 Super Class

L<SPVM::Builder::Config::Linker>

=head1 Methods

=head2 new

  my $config = SPVM::Builder::Config::Exe->new(%options);

Creates a new L<SPVM::Builder::Config::Exe> object. The C<output_type> field is set to C<exe>.

=cut
