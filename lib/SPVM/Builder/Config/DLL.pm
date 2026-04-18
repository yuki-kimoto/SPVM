package SPVM::Builder::Config::DLL;

use parent 'SPVM::Builder::Config::Exe';

use strict;
use warnings;

sub init {
  my ($self) = @_;
  
  $self->output_type('dynamic_lib');
}

1;

=head1 Name

SPVM::Builder::Config::DLL - Configuration for Dynamic Link Libraries

=head1 Description

L<SPVM::Builder::Config::DLL> is a class to manage configurations for generating dynamic link libraries.

=head1 Usage

  use SPVM::Builder::Config::DLL;

  my $config_global = SPVM::Builder::Config::Util::load_base_config(__FILE__);
  
  bless $config_global, SPVM::Builder::Config::DLL;
  
  $config_global->init;

  $config_global;

=head1 Super Class

L<SPVM::Builder::Config::Exe>

=head1 Instance Methods

=head2 init
  
  $config->init;

Initialize this instance. C<output_type> is set to C<"dynamic_lib">.

=cut
