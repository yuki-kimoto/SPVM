package SPVM::Builder::Config::Exe;

use strict;
use warnings;

use base 'SPVM::Builder::Config';

sub new {
  my $self = shift->SUPER::new(@_);
  
  # global_ccflags
  unless (defined $self->{global_ccflags}) {
    $self->global_ccflags([]);
  }
  
  return $self;
}

sub global_optimize {
  my $self = shift;
  if (@_) {
    $self->{global_optimize} = $_[0];
    return $self;
  }
  else {
    return $self->{global_optimize};
  }
}

sub global_ccflags {
  my $self = shift;
  if (@_) {
    $self->{global_ccflags} = $_[0];
    return $self;
  }
  else {
    return $self->{global_ccflags};
  }
}

sub add_global_ccflags {
  my ($self, @global_ccflags) = @_;
  
  push @{$self->{global_ccflags}}, @global_ccflags;
}

1;

=head1 NAME

SPVM::Builder::Config::Exe - Configurations of creating excutable files.

=head1 DESCRIPTION

SPVM::Builder::Config::Exe is configuration of creating excutable files of L<spvmcc>.

=head1 FIELDS

Fields is inherited from L<SPVM::Builder::Config> and you can use the following ones.

=head2 global_ccflags

  my $global_ccflags = $config->global_ccflags;
  $config->global_ccflags($global_ccflags);

Get and set global C<ccflags> that is added to all C<ccflags> of the compiler.

B<Default:>

  []
  
=head2 global_optimize

  my $global_optimize = $config->global_optimize;
  $config->global_optimize($global_optimize);

Get and set global C<optimize> that replaces all C<optimize> of the compiler.

=head1 METHODS

Methods is inherited from L<SPVM::Builder::Config> and you can use the following ones.
