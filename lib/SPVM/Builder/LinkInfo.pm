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
  compile_infos
  object_files
  dl_func_list
)];

# Class Methods
sub new {
  my $class = shift;
  
  my $self = {
    object_files => [],
    compile_infos => [],
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
  my $object_files = $self->object_files;
  my $object_file_names = [map { $_->to_string; } @$object_files];
  
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
  
  my $field_names = $config->get_ld_system_field_names;
  my $output_type = $config->output_type;
  for my $field_name (@$field_names) {
    
    my $add;
    if ($field_name =~ /^dynamic_lib_(?:.+_)?ldflags$/) {
      if ($output_type eq 'dynamic_lib') {
        $add = 1;
      }
    }
    elsif ($field_name =~ /^exe_(?:.+_)?ldflags$/) {
      if ($output_type eq 'exe') {
        $add = 1;
      }
    }
    else {
      $add = 1;
    }
    
    if ($add) {
      push @merged_ldflags, grep { length $_ } @{$config->$field_name};
    }
  }
  
  my $lib_dirs = $config->lib_dirs;
  push @merged_ldflags, map { $config->create_option($config->lib_dir_option_name, $_) } grep { length $_ } @$lib_dirs;
  
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

sub to_command {
  my ($self, $options) = @_;
  
  my $link_command = $self->create_command($options);
  my $link_command_string = "@$link_command";
  
  return $link_command_string;
}

1;

=head1 Name

SPVM::Builder::LinkInfo - Linker Information

=head1 Description

The SPVM::Builder::LinkInfo class has methods to manipulate linker information.

=head1 Usage

  my $link_info = SPVM::Builder::LinkInfo->new(%fields);
  my $link_command = $link_info->to_command;

=head1 Super Class

L<SPVM::Builder::CommandInfo>

=head1 Fields

=head2 object_files

  my $object_files = $link_info->object_files;
  $link_info->object_files($object_files);

Gets and sets the C<object_files> field, an array reference of L<SPVM::Builder::ObjectFileInfo> objects.

=head2 compile_infos

  my $compile_infos = $link_info->compile_infos;
  $link_info->compile_infos($compile_infos);

Gets and sets the C<compile_infos> field, an array reference of L<SPVM::Builder::CompileInfo> objects.

=head1 Class Methods

=head2 new

  my $link_info = SPVM::Builder::LinkInfo->new(%fields);

Creates a new C<SPVM::Builder::LinkInfo> object given L</"Fields">.

Field Default Values:

=over 2

=item * L</"object_files">

[]

=item * L</"compile_infos">

[]

=back

Exceptions:

The "config" field must be defined.

=head1 Instance Methods

=head2 create_command

  my $link_command = $link_info->create_command;

Creates an array reference of the link command, and returns it.

Return Value Examples:

  [qw(cc -o dylib.so foo.o bar.o -shared -O2 -Llibdir -lz)]

=head2 create_ldflags

  my $ldflags = $link_info->create_ldflags;

Creates an array reference of the linker options, and returns it.

The output file L</"output_file"> and the object files L</"object_files"> are not contained.

Return Value Examples:

  [qw(-shared -O2 -Llibdir -lz)]

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
