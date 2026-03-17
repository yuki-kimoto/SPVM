package SPVM::Builder::Config::Base;

use strict;
use warnings;
use SPVM::Builder::Util;
use SPVM::Builder::Accessor 'has';

# Base Fields
my $base_fields = [qw(
  class_name
  file
  category
  is_jit
  is_resource
  quiet
  force
  long_option_sep
)];

# Accessors generation for base fields
has($base_fields);

sub new {
  my $class = shift;
  
  my $self = {@_};
  
  bless $self, ref $class || $class;
  
  # SPVM::Builder::Util::check_option_names($self, $self->option_names);
  
  # file
  $self->file(undef);

  # force (default is undef)
  
  # quiet (default is undef)

  # category
  unless (defined $self->{category}) {
    $self->category('native');
  }

  # long_option_sep
  unless (defined $self->{long_option_sep}) {
    $self->long_option_sep("=");
  }

  # is_jit, is_resource are normally set via constructor if needed
  
  return $self;
}

# Instance Methods related to Base functionality
sub option_names {
  my ($self) = @_;
  
  return $base_fields;
}

sub create_option {
  my ($self, $name, $value) = @_;
  
  # Extract the option name without leading hyphens or slashes to check its length
  my $pure_name = $name;
  $pure_name =~ s/^[\-\/]+//;
  
  if (length $pure_name <= 1) {
    return $self->create_option_short($name, $value);
  }
  else {
    return $self->create_option_long($name, $value);
  }
}

# Connect directly (e.g. -oFILE, -I/path)
sub create_option_short {
  my ($self, $name, $value) = @_;
  
  return "$name$value";
}

# Connect using long_option_sep (e.g. --prefix=/usr, -out:FILE)
sub create_option_long {
  my ($self, $name, $value) = @_;
  
  my $sep = $self->long_option_sep;
  
  return "$name$sep$value";
}

1;

=head1 Name

SPVM::Builder::Config - Config for Compiling and Linking Native Classes

=head1 Description

The SPVM::Builder::Config class has methods to get and set config for compiling and linking L<native classes|SPVM::Document::NativeClass>.

=head1 Fields

=head2 class_name

  my $class_name = $config->class_name;
  $config->class_name($class_name);

Gets and sets C<class_name> field, the name of the class configured by this config.

This field is automatically set and users nomally do not change it.

=head2 file

  my $file = $config->file;
  $config->file($file);

Gets and sets C<file> field, the file path of this config.

This field is set by L</"load_config"> method and users should not set it.

=head2 category

  my $category = $config->category;
  $config->category($category);

Gets and sets C<category> field.

If this field is C<precompile>, this config is for precompilation.

If this field is C<native>, this config is for a native class.

This field is automatically set and users nomally do not change it.

=head2 is_resource

  my $is_resource = $config->is_resource;
  $config->is_resource($is_resource);

Gets and sets C<is_resource> field.

If this field is true, this config is for a L<resource|SPVM::Document::Resource> class.

=head2 force

  my $force = $config->force;
  $config->force($force);

Gets and sets C<force> field.

If this field is a true value, the compilation and linking are forced.

If this field is a false value except for undef, the compilation and linking are performed following the rule of the L<dependency resolution|SPVM::Document::NativeClass/"Dependency Resolution">.

If this field is undef, this config does not specify whether the compilation and linking are perfomed.

=head2 quiet

  my $quiet = $config->quiet;
  $config->quiet($quiet);

Gets and sets C<quiet> field.

If this field is a true value, the messages from the compiler and the linker are output to C<stderr>.

If this field is a false value except for undef, the messages from the compiler and the linker are not output.

If this field is undef, this config does specify whether the messages from the compiler and the linker are output.

=head2 long_option_sep

  my $long_option_sep = $config->long_option_sep;
  $config->long_option_sep($long_option_sep);

Gets and sets C<long_option_sep> field, a string that is a separator between an option name and its value.

=head1 Class Methods

=head2 new

  my $config = SPVM::Builder::Config->new(%fields);

Creates a new C<SPVM::Builder::Config> object with L<fields|/"Fields">, and returns it.

Default settings for the GCC or Clang compiler are performed.

Field Default Values:

=over 2

=item * L</"file">

This value is set automatically.

=item * L</"category">

  "native"

=item * L</"long_option_sep">

  "="

=back

=head1 Instance Methods

=head2 create_option

  my $option = $config->create_option("-std", "c11");

Builds a command line option from the option name and the value.

If the length of the option name (excluding leading C<-> and C</>) is 1, the option name and the value are connected without a separator.

  # Results in "-Ic:/path"
  my $option = $config->create_option("-I", "c:/path");

If the length of the option name is greater than 1, they are connected using L</"long_option_sep">.

  # Results in "-std=c11" (if long_option_sep is "=")
  my $option = $config->create_option("-std", "c11");

This method is useful for supporting different compiler conventions such as GCC/Clang and MSVC.

=head2 create_option_short

  my $option = $config->create_option_short("-I", "c:/path");

Builds a command line option by connecting the option name and the value directly without a separator.

  # Results in "-Ic:/path"
  my $option = $config->create_option_short("-I", "c:/path");

  # Results in "-Foc:/path" (Useful for MSVC even if the option name length > 1)
  my $option = $config->create_option_short("-Fo", "c:/path");

=head2 create_option_long

  my $option = $config->create_option_long("-std", "c11");

Builds a command line option by connecting the option name and the value using L</"long_option_sep">.

  # Results in "-std=c11" (if long_option_sep is "=")
  my $option = $config->create_option_long("-std", "c11");

  # Results in "-out:c:/path" (if long_option_sep is ":")
  my $option = $config->create_option_long("-out", "c:/path");

=cut
