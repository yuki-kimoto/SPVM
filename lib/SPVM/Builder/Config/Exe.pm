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

sub global_ccflags_each {
  my $self = shift;
  if (@_) {
    $self->{global_ccflags_each} = $_[0];
    return $self;
  }
  else {
    return $self->{global_ccflags_each};
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

=head2 global_ccflags_each

  my $global_ccflags_each = $config->global_ccflags_each;
  $config->global_ccflags_each($global_ccflags_each);

Get and set a callback that returns the compiler flags for each source file. The call back receives L<SPVM::Bulder::Config> object and each source file and the class name.

The return values of C<global_ccflags> are added to all C<ccflags> of the compiler.

B<Examples:>
  
  $config->global_ccflags_each(sub {
    my ($config, $source_file, $class_name) = @_;
    
    my $config_global_ccflags = $config->global_ccflags;
    
    my $global_ccflags = [];
    # C source file
    if ($source_file =~ /\.c$/) {
      $global_ccflags = ['-DFoo', @$config_global_ccflags];
    }
    # C++ source file
    elsif ($source_file =~ /\.cpp$/) {
      $global_ccflags = ['-DBar', @$config_global_ccflags];
    }
    
    return $global_ccflags;
  });

C<global_ccflags_each> takes precedence over C<global_ccflags>.

=head2 global_optimize

  my $global_optimize = $config->global_optimize;
  $config->global_optimize($global_optimize);

Get and set global C<optimize> that replaces all C<optimize> of the compiler.

=head1 METHODS

Methods is inherited from L<SPVM::Builder::Config> and you can use the following ones.
