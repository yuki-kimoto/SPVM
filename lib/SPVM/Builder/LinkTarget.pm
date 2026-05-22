package SPVM::Builder::LinkTarget;

use strict;
use warnings;
use Config;
use Carp 'confess';
use File::Basename 'dirname';
use SPVM::Builder::Accessor 'has';

# Fields
my $field_names = [qw(
  config
  compile_infos
)];
has $field_names;

# Class Methods
sub new {
  my $class = shift;
  
  my $self = {
    compile_infos => [],
    @_
  };
  
  bless $self, ref $class || $class;
  
  SPVM::Builder::Util::check_option_names($self, $field_names);
  
  return $self;
}

1;

=head1 Name

SPVM::Builder::LinkTarget - Link Information

=head1 Description

SPVM::Builder::LinkTarget class manages information for a link target.

=head1 Usage

  my $link_target = SPVM::Builder::LinkTarget->new(%fields);

=head1 Fields

=head2 config

  my $config = $command_info->config;
  $command_info->config($config);

Gets and sets the C<config> field, a L<SPVM::Builder::Config> object.

=head2 compile_infos

  my $compile_infos = $link_target->compile_infos;
  $link_target->compile_infos($compile_infos);

Gets and sets the C<compile_infos> field, an array reference of L<SPVM::Builder::ObjectFileInfo> objects.


=head1 Class Methods

=head2 new

  my $link_target = SPVM::Builder::LinkTarget->new(%fields);

Creates a new C<SPVM::Builder::LinkTarget> object given L</"Fields">, and returns it.

Field Default Values:

=over 2

=item * L</"compile_infos">

[]

=back

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
