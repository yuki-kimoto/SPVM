package SPVM::Builder::Config::DLL;

use parent 'SPVM::Builder::Config::Global';

use strict;
use warnings;

sub new {
  my $class = shift;
  
  my $self = $class->SUPER::new(
    output_type => 'dynamic_lib',
    @_,
  );
  
  return $self;
}

1;

=head1 Name

SPVM::Builder::Config::DLL - Configuration for Dynamic Link Libraries

=head1 Description

L<SPVM::Builder::Config::DLL> is a class to manage configurations for generating dynamic link libraries.

This class inherits from L<SPVM::Builder::Config::Global> and sets the C<output_type> field to C<dynamic_lib> by default.

=head1 Inheritance

L<SPVM::Builder::Config::Global> E<lt>- L<SPVM::Builder::Config> E<lt>- L<SPVM::Builder::Config::Linker> E<lt>- L<SPVM::Builder::Config::Base>

=head1 Methods

=head2 new

  my $config = SPVM::Builder::Config::DLL->new(%options);

Creates a new L<SPVM::Builder::Config::DLL> object. The C<output_type> field is set to C<dynamic_lib>.

=cut
