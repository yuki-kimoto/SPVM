package SPVM::Builder::CompileInfo;

use strict;
use warnings;
use Config;
use Carp 'confess';
use File::Basename 'dirname';
use SPVM::Builder::Accessor 'has';

# Fields
has [qw(
  config
  source_rel_file
  output_file
  category
  dependent_files
  link_info
  command_hash
  start_time
)];

# Class methods
sub new {
  my $class = shift;
  
  my $self = {
    dependent_files => [],
    @_,
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
  
  my $cc = $config->cc;
  my $output_file = $self->output_file;
  my $source_file = $self->source_file;
  
  my $compile_command_args = $self->create_ccflags;
  
  # Get output option name
  my $cc_output_option_name = $config->cc_output_option_name;
  
  # Build command
  my @compile_command;
  
  push @compile_command, ($cc, '-c');
  
  unless ($no_output_option) {
    # Build output option
    my $output_option = $config->create_option_short($cc_output_option_name, $output_file);
  
    push @compile_command, $output_option;
  }
  
  push @compile_command, (@$compile_command_args, $source_file);
  
  return \@compile_command;
}

sub create_ccflags {
  my ($self) = @_;
  
  my $config = $self->config;
  
  my $class_name = $config->class_name;
  
  my $config_category = $config->category;
  
  my @compile_command_args;
  
  my $std = $config->std;
  if (length $std) {
    push @compile_command_args, $config->create_option("-std", $std);
  }
  
  my $field_names = $config->get_cc_system_field_names;
  my $output_type = $config->output_type;

  for my $field_name (@$field_names) {
    if ($field_name eq 'position_independent_code_ccflags') {
      if ($output_type eq 'dynamic_lib') {
        push @compile_command_args, grep { length $_ } @{$config->$field_name};
      }
    }
    else {
      push @compile_command_args, grep { length $_ } @{$config->$field_name};
    }
  }
  
  my $optimize = $config->optimize;
  
  my $config_global = $config->config_global;
  
  if (length $optimize) {
    push @compile_command_args, split(/ +/, $optimize);
  }
  
  # include directories
  {
    my @all_include_dirs;
    
    # SPVM core native directory
    my $spvm_core_include_dir = $config->spvm_core_include_dir;
    if (length $spvm_core_include_dir) {
      push @all_include_dirs, $spvm_core_include_dir;
    }
    
    # include directories
    my $include_dirs = $config->include_dirs;
    push @all_include_dirs, grep { length $_ } @$include_dirs;
    
    # Native include directory
    my $native_include_dir = $config->native_include_dir;
    if (length $native_include_dir) {
      push @all_include_dirs, $native_include_dir;
    }
    
    # Resource include directories
    my $resource_names = $config->get_resource_names;
    for my $resource_name (@$resource_names) {
      my $resource = $config->get_resource($resource_name);
      my $config = $resource->config;
      my $resource_include_dir = $config->native_include_dir;
      if (length $resource_include_dir) {
        push @all_include_dirs, $resource_include_dir;
      }
    }
    
    my @all_include_dirs_args = map { "-I$_" } @all_include_dirs;
    
    push @compile_command_args, @all_include_dirs_args;
  }
  
  return \@compile_command_args;
}

sub to_command {
  my ($self) = @_;

  my $compile_command = $self->create_command;
  
  my @quoted_parts;
  for my $part (@$compile_command) {
    push @quoted_parts, $self->_quote_literal($part);
  }
  
  my $compile_command_string = join(' ', @quoted_parts);
  
  return $compile_command_string;
}

sub _quote_literal {
  my ($self, $string) = @_;

  if ($^O eq 'MSWin32') {
    if (length $string && $string !~ /[ \t\n\x0b"|<>%]/) {
      return $string;
    }

    $string =~ s{(\\*)(?="|\z)}{$1$1}g;
    $string =~ s{"}{\\"}g;

    return qq{"$string"};
  }
  else {
    if (length $string && $string !~ /[^a-zA-Z0-9,._+@%\/-]/) {
      return $string;
    }

    $string =~ s{'}{'\\''}g;

    return "'$string'";
  }
}

sub source_file {
  my $self = shift;
  
  my $cc_input_dir = $self->config->cc_input_dir;
  my $source_rel_file = $self->source_rel_file;
  
  my $source_file = "$cc_input_dir/$source_rel_file";
  
  return $source_file;
}

1;

=head1 Name

SPVM::Builder::CompileInfo - Compiler Information

=head1 Description

The SPVM::Builder::CompileInfo class has methods to manipulate compiler information.

=head1 Fields

=head2 config

  my $config = $compile_info->config;
  $compile_info->config($config);

Gets and sets the C<config> field, a L<SPVM::Builder::Config> object.

=head2 output_file

  my $output_file = $compile_info->output_file;
  $compile_info->output_file($output_file);

Gets and sets the C<output_file> field, an output file.

=head2 category

  my $category = $config->category;
  $config->category($category);

Gets and sets the C<category> field.

These are C<native_class>, C<native_source>, C<precompile_class>, C<spvm>, C<spvm_core>.

=head2 dependent_files

  my $dependent_files = $compile_info->dependent_files;
  $compile_info->dependent_files($dependent_files);

Gets and sets the C<dependent_files> field, an array reference of the dependent files of the source file.

If this field is defined, these files are added to the dependency list of the C<ninja> build rule.

=head2 link_info

  my $link_info = $compile_info->link_info;
  $compile_info->link_info($link_info);

Gets and sets the C<link_info> field, an L<SPVM::Builder::LinkInfo> object.

This field is a weak reference to the L<SPVM::Builder::LinkInfo> object that this compilation task belongs to.

=head2 command_hash

  my $command_hash = $compile_info->command_hash;
  $compile_info->command_hash($command_hash);

Gets and sets the C<command_hash> field, a SHA-1 hash string that uniquely identifies the compilation task.

This hash ensures the consistency of the compilation. It is generated from the following information:

=over 2

=item * The compilation command itself.

=item * The compiler version.

=item * The SPVM version-specific headers.

=item * The information of the dependent files.

=back

If any of these change, the hash will change, triggering a re-compilation in the C<ninja> build system.

=head1 Class Methods

=head2 new

  my $compile_info = SPVM::Builder::CompileInfo->new(%fields);

Creates a new L<SPVM::Builder::CompileInfo> object given L</"Fields">.

=back

Exceptions:

The "config" field must be defined.

=head1 Instance Methods

=head2 create_command

  my $compile_command = $compile_info->create_command;

Creates an array reference of the compilation command, and returns it.

Return Value Examples:

  [qw(cc -o foo.o -c -O2 -Ipath/include foo.c)]

=head2 create_ccflags

  my $config_args = $compile_info->create_ccflags;

Creates n array reference of the compilation options, and returns it.

The source file L<"source_file"> and the output file L</"output_file"> are not contained.

Return Value Examples:

  [qw(-O2 -Ipath/include)]

=head2 to_command

  my $compile_command_string = $compile_info->to_command;

Converts the array reference of the compilation command returned by the L</"create_command"> method into a single string that can be executed in a shell (such as C<sh> or C<bash>) or the Windows Command Prompt (C<cmd.exe>).

Each argument is automatically and appropriately quoted only when necessary (e.g., containing spaces or special characters) according to the operating system (OS) to ensure it can be safely executed as a command line.

Return Value Examples:

=over 2

=item * On UNIX/Linux (Only strings with special characters like C<=> or spaces are quoted):

  gcc -c -o foo.o -O2 '-std=c99' -Ipath/include foo.c

=item * On Windows (Only strings with characters like spaces or C<"> are quoted):

  gcc -c -o foo.o -O2 -std=c99 -Ipath/include foo.c

=back

=cut

=head2 source_file

  my $source_file = $compile_info->source_file;
  $compile_info->source_file($source_file);

Gets the source file path from C<config->cc_input_dir> and C</"source_rel_file">.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
