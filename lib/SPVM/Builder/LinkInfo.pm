package SPVM::Builder::LinkInfo;

use strict;
use warnings;
use Config;
use Carp 'confess';
use File::Basename 'dirname';

# Fields
sub config {
  my $self = shift;
  if (@_) {
    $self->{config} = $_[0];
    return $self;
  }
  else {
    return $self->{config};
  }
}

sub object_files {
  my $self = shift;
  if (@_) {
    $self->{object_files} = $_[0];
    return $self;
  }
  else {
    return $self->{object_files};
  }
}

sub no_generate {
  my $self = shift;
  if (@_) {
    $self->{no_generate} = $_[0];
    return $self;
  }
  else {
    return $self->{no_generate};
  }
}

# Class Methods
sub new {
  my $class = shift;
  
  my $self = {@_};
  
  bless $self, $class;
  
  my $config = $self->config;
  
  unless ($config) {
    confess("The \"config\" field must be defined.");
  }
  
  unless (defined $self->object_files) {
    $self->object_files([]);
  }
  
  $self->config($config->clone);
  
  return $self;
}

# Instance Methods
sub create_command {
  my ($self) = @_;
  
  my $config = $self->config;
  
  my $ld = $config->ld;
  my $output_file = $config->output_file;
  my $object_files = $self->object_files;
  my $object_file_names = [map { $_->to_string; } @$object_files];
  
  my $ldflags = $self->create_ldflags;
  
  # ldflags must be after object files to resolve symbol names properly
  my @link_command = ($ld, '-o', $output_file, @$object_file_names, @$ldflags);
  
  return \@link_command;
}

sub create_ldflags {
  my ($self) = @_;
  
  my $config = $self->config;
  
  my @merged_ldflags;
  
  if (length $config->ld_optimize) {
    push @merged_ldflags, split(/ +/, $config->ld_optimize);
  }
  
  my $output_type = $config->output_type;
  if ($output_type eq 'dynamic_lib') {
    push @merged_ldflags, grep { length $_ } @{$config->dynamic_lib_ldflags};
  }
  
  my $ldflags = $config->ldflags;
  push @merged_ldflags, grep { length $_ } @{$config->ldflags};
  
  push @merged_ldflags, grep { length $_ } @{$config->thread_ldflags};
  
  push @merged_ldflags, grep { length $_ } @{$config->libcpp_ldflags};
  
  push @merged_ldflags, grep { length $_ } @{$config->warn_ldflags};
  
  push @merged_ldflags, grep { length $_ } @{$config->debug_ldflags};
  
  # bcrypt_ldflags
  # Add bcrypt_ldflags only when the output type is 'exe'
  if ($output_type eq 'exe') {
    push @merged_ldflags, grep { length $_ } @{$config->bcrypt_ldflags};
  }
  
  my $lib_dirs = $config->lib_dirs;
  push @merged_ldflags, map { $config->build_option($config->lib_dir_option_name, $_) } grep { length $_ } @$lib_dirs;
  
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
  my ($self) = @_;
  
  my $link_command = $self->create_command;
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

=head1 Fields

=head2 config

  my $config = $link_info->config;
  $link_info->config($config);

Gets and sets the C<config> field, an L<SPVM::Builder::Config> object.

=head2 output_file

  my $output_file = $link_info->output_file;
  $link_info->output_file($output_file);

Gets and sets the C<output_file> field, an output file.

=head2 object_files

  my $object_files = $link_info->object_files;
  $link_info->object_files($object_files);

Gets and sets the C<object_files> field, an array reference of L<SPVM::Builder::ObjectFileInfo> objects.

=head2 no_generate

  my $no_generate = $link_info->no_generate;
  $link_info->no_generate($no_generate);

Gets and sets the C<no_generate> field. If this field is a true value, the output file is not generated.

=head1 Class Methods

=head2 new

  my $link_info = SPVM::Builder::LinkInfo->new(%fields);

Creates a new C<SPVM::Builder::LinkInfo> object given L</"Fields">.

Field Default Values:

=over 2

=item * L</"output_file">

undef

=item * L</"object_files">

[]

=item * L</"no_generate">

undef

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

=head2 to_command

  my $link_command_string = $link_info->to_command;

Joins all elements of the return value of L</"create_command"> method with a space, and returns it.

Return Value Examples:

  "cc -o dylib.so foo.o bar.o -shared -O2 -Llibdir -lz"

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
