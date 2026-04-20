package SPVM::Builder::Config::DLL;

use parent 'SPVM::Builder::Config::Exe';

use strict;
use warnings;

sub new {
  my $self = shift->SUPER::new(@_);
  
  $self->init;
  
  return $self;
}

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
  
  $config_global = SPVM::Builder::Config::DLL->new_with_config($config_global);
  
  $config_global->init;

  $config_global;

=head1 Super Class

L<SPVM::Builder::Config::Exe>

=head1 Class Methods

=head2 new

  my $config_global = SPVM::Builder::Config::DLL->new(%fields);

Creates a new L<SPVM::Builder::Config::DLL> object by calling C<new> method in the super class with I<%fields>, and calls L</"init"> method with I<%fields>.

=head1 Instance Methods

=head2 init
  
  $config_global->init(%fields);

Initialize this instance. C<output_type> is set to C<"dynamic_lib">.
