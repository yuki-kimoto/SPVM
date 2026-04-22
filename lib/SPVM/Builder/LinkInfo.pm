package SPVM::Builder::LinkInfo;

use parent 'SPVM::Builder::CommandInfo';

use strict;
use warnings;
use Config;
use Carp 'confess';
use File::Basename 'dirname';
use SPVM::Builder::Accessor 'has';

# Fields
has [qw(
  object_file_infos
  dl_func_list
)];

# Class Methods
sub new {
  my $class = shift;
  
  my $self = {
    object_file_infos => [],
    dl_func_list => [],
    @_
  };
  
  bless $self, $class;
  
  my $config = $self->config;
  
  unless ($config) {
    confess("The \"config\" field must be defined.");
  }
  
  $self->config($config->clone);
  
  return $self;
}

# Instance Methods
sub create_command {
  my ($self, $options) = @_;
  
  $options //= {};
  
  my $no_output_option = $options->{no_output_option};
  
  my $config = $self->config;
  
  my $ld = $config->ld;
  
  my $output_file = $config->output_file;
  my $object_file_infos = $self->object_file_infos;
  my $object_file_names = [map { $_->to_string; } @$object_file_infos];
  
  my $ldflags = $self->create_ldflags;
  
  # Get output option name
  my $ld_output_option_name = $config->ld_output_option_name;
  
  # Build command
  my @link_command;
  push @link_command, ($ld);
  
  unless ($no_output_option) {
    # Build output option
    my $output_option = $config->create_option($ld_output_option_name, $output_file);
    
    push @link_command, $output_option;
  }
  
  push @link_command, (@$object_file_names, @$ldflags);
  
  return \@link_command;
}

sub create_ldflags {
  my ($self) = @_;
  
  my $config = $self->config;
  
  my @merged_ldflags;
  
  if (length $config->ld_optimize) {
    push @merged_ldflags, split(/ +/, $config->ld_optimize);
  }
  
  my $ldflags = $config->ldflags;
  push @merged_ldflags, grep { length $_ } @{$config->ldflags};
  
  my $ld_system_field_names = $config->get_ld_system_field_names;
  my $output_type = $config->output_type;
  for my $ld_system_field_name (@$ld_system_field_names) {
    push @merged_ldflags, grep { length $_ } @{$config->$ld_system_field_name};
  }
  
  my $lib_dirs = $config->lib_dirs;
  push @merged_ldflags, map {
    $config->create_option($config->lib_dir_option_name, SPVM::Builder::Util::quote_literal($_))
  }
  grep { length $_ } @$lib_dirs;
  
  my $libs = $config->libs;
  my @lib_ldflags;
  for (my $i = 0; $i < @$libs; $i++) {
    my $lib = $libs->[$i];
    $lib = ref $lib ? $lib : SPVM::Builder::LibInfo->new(name => $lib, config => $config);
    $libs->[$i] = $lib;
    my $lib_ldflags = $lib->create_ldflags;
    push @lib_ldflags, @$lib_ldflags;
  }
  
  push @merged_ldflags, @lib_ldflags;
  
  return \@merged_ldflags;
}

1;

=head1 Name

SPVM::Builder::LinkInfo - Link Information

=head1 Description

SPVM::Builder::LinkInfo class manages information for a link.

=head1 Usage

  my $link_info = SPVM::Builder::LinkInfo->new(%fields);

=head1 Super Class

L<SPVM::Builder::CommandInfo>

=head1 Fields

=head2 object_file_infos

  my $object_file_infos = $link_info->object_file_infos;
  $link_info->object_file_infos($object_file_infos);

Gets and sets the C<object_file_infos> field, an array reference of L<SPVM::Builder::ObjectFileInfo> objects.

=head2 dl_func_list

  my $dl_func_list = $link_info->dl_func_list;
  $link_info->dl_func_list($dl_func_list);

Gets and sets the C<dl_func_list> field. It is an array reference of function names to be exported from a dynamic library for Windows.

=head1 Class Methods

=head2 new

  my $link_info = SPVM::Builder::LinkInfo->new(%fields);

Creates a new C<SPVM::Builder::LinkInfo> object given L</"Fields">, and returns it.

Field Default Values:

=over 2

=item * L</"object_file_infos">

[]

=back

Exceptions:

L<"config"|SPVM::Builder::CommandInfo/"config"> field must be defined.

=head1 Instance Methods

=head2 create_command

  my $link_command = $link_info->create_command;
  my $link_command_no_output = $link_info->create_command({no_output_option => 1});

Creates an array reference of the link command, and returns it.

If the C<no_output_option> option is a true value, the output option (e.g. C<-o dylib.so>) is not added to the command.

Return Value Examples:

  [qw(cc -o dylib.so foo.o bar.o -shared -O2 -Llibdir -lz)]

  # With no_output_option => 1
  [qw(cc foo.o bar.o -shared -O2 -Llibdir -lz)]

=head2 create_ldflags

  my $ldflags = $link_info->create_ldflags;

Creates an array reference of the linker options, and returns it.

The output file L<"output_file"|SPVM::Builder::CommandInfo/"output_file"> and the object files L</"object_file_infos"> are not contained.

Return Value Examples:

  [qw(-shared -O2 -Llibdir -lz)]

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
