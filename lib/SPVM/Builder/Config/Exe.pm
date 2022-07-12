package SPVM::Builder::Config::Exe;

use strict;
use warnings;
use Carp 'confess';

use SPVM::Builder::Util;

use base 'SPVM::Builder::Config';

sub new {
  my ($self, %options) = @_;
  
  unless (defined $options{output_type}) {
    $options{output_type} = 'exe';
  }
  
  $self = $self->SUPER::new(%options);

  return $self;
}

sub global_before_compile {
  my $self = shift;
  if (@_) {
    $self->{global_before_compile} = $_[0];
    return $self;
  }
  else {
    return $self->{global_before_compile};
  }
}

sub no_precompile {
  my $self = shift;
  if (@_) {
    $self->{no_precompile} = $_[0];
    return $self;
  }
  else {
    return $self->{no_precompile};
  }
}

sub no_compiler_api {
  my $self = shift;
  if (@_) {
    $self->{no_compiler_api} = $_[0];
    return $self;
  }
  else {
    return $self->{no_compiler_api};
  }
}

1;

=head1 Name

SPVM::Builder::Config::Exe - Configurations of creating excutable files.

=head1 Usage

  use SPVM::Builder::Config::Exe;
  
  my $config = SPVM::Builder::Config::Exe->new_gnu99;

=head1 Description

SPVM::Builder::Config::Exe is configuration of creating excutable files of L<spvmcc>.

=head1 Field Methods

Fields of B<SPVM::Builder::Config::Exe>.

Fields are inherited from L<SPVM::Builder::Config> and you can use the following fields.

=head2 no_precompile

  my $no_precompile = $config->no_precompile;
  $config->no_precompile($no_precompile);

If C<no_precompile> is a true value, precompiling is not performed.

=head2 no_compiler_api

  my $no_compiler_api = $config->no_compiler_api;
  $config->no_compiler_api($no_compiler_api);

If C<no_compiler_api> is a true value, the source codes of the L<compiler native APIs|SPVM::Document::NativeAPI::Compiler> and the L<precompile native APIs|SPVM::Document::NativeAPI::Precompile> is not linked.

=head1 Methods

Methods of B<SPVM::Builder::Config::Exe>.

Methods are inherited from L<SPVM::Builder::Config> and you can use the following methods.

=head2 new

  my $config = SPVM::Builder::Config::Exe->new;

Create a new C<SPVM::Builder::Config::Exe> object.

This is same as L<SPVM::Builder::Config/"new">, but set C<output_type> field to C<exe>.
