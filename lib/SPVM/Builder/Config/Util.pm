package SPVM::Builder::Config::Util;

use strict;
use warnings;
use File::Basename 'fileparse';
use Carp 'confess';

sub load_config {
  my ($config_file) = @_;
  
  unless (-f $config_file) {
    confess("Config file \"$config_file\" must exist");
  }
  
  my $config;
  {
    open my $fh, '<', $config_file
      or confess("Config file \"$config_file\" can't found: $!");
    
    my $config_content = do { local $/; <$fh> };
    
    $config = &_eval_config_content($config_content, $config_file);
  }
  
  if ($@) {
    confess("Config file \"$config_file\" can't be parsed: $@");
  }
  
  unless (defined $config && $config->isa('SPVM::Builder::Config::Linker')) {
    confess("Config file must be an SPVM::Builder::Config::Linker object.");
  }
  
  push @{$config->loaded_config_files}, $config_file;
  
  $config->file($config_file);
  
  return $config;
}

sub load_mode_config {
  my ($config_file, $mode, $options) = @_;
  
  $options //= {};
  
  my $mode_config_file = &remove_ext_from_config_file($config_file);
  if (defined $mode) {
    $mode_config_file .= ".$mode";
  }
  $mode_config_file .= ".config";
  
  unless (-f $mode_config_file) {
    confess("Can't find the config file '$mode_config_file'");
  }
  
  my $config = &load_config($mode_config_file);
  
  if (defined $mode) {
    $config->mode($mode);
  }
  
  return $config;
}

sub load_base_config {
  my ($config_file, $args) = @_;
  
  my $config = &load_mode_config($config_file, undef, $args);
  
  return $config;
}

sub _eval_config_content {
  my ($config_content, $config_file) = @_;

  $config_content = <<"EOS";
use strict;
use warnings;
use utf8;
use SPVM::Builder::Config::Util;
use SPVM::Builder::Config;
use SPVM::Builder::Config::Exe;
use SPVM::Builder::Config::DLL;
# line 1 "$config_file"
$config_content
EOS

  return eval $config_content;
}
sub remove_ext_from_config_file {
  my ($config_file) = @_;
  
  my ($config_base_name, $config_dir) = fileparse $config_file;
  
  $config_base_name =~ s/(\.[^\.]+)?\.config$//;
  
  my $config_file_without_ext = "$config_dir$config_base_name";
  
  return $config_file_without_ext;
}

sub load_config_global {
  my ($config_global_file) = @_;

  unless (-f $config_global_file) {
    confess("Config file '$config_global_file' must exist");
  }

  my $config_global;
  {
    open my $fh, '<', $config_global_file
      or confess("Config file '$config_global_file' can't be opened: $!");

    my $config_content = do { local $/; <$fh> };

    # Prepare and eval config content for global
    $config_global = &_eval_config_global_content($config_content, $config_global_file);
  }

  if ($@) {
    confess("Config file '$config_global_file' can't be parsed: $@");
  }

  # Verify object type
  unless (defined $config_global && $config_global->isa('SPVM::Builder::Config::Global')) {
    confess("Config file must be an SPVM::Builder::Config::Global object.");
  }

  return $config_global;
}

sub _eval_config_global_content {
  my ($config_global_content, $config_global_file) = @_;

  $config_global_content = <<"EOS";
use strict;
use warnings;
use utf8;
use SPVM::Builder::Config::Util;
use SPVM::Builder::Config::Global;
# line 1 "$config_global_file"
$config_global_content
EOS

  return eval $config_global_content;
}

1;

=head1 Name

SPVM::Builder::Config::Util - Config Utilities

=head1 Description

SPVM::Builder::Config::Util module has utilities for L<SPVM::Builder::Config> class.

=head1 Functions

=head2 load_config

  my $config = SPVM::Builder::Config::Util::load_config($config_file);

Loads the config file $config_file and returns an L<SPVM::Builder::Config::Base> object.

Examples:

  my $config = SPVM::Builder::Config::Util::load_config($config_file);

L<file|SPVM::Builder::Config::Base/"file"> field of the returned config object is set to $config_file.

=head2 load_mode_config

  my $config = SPVM::Builder::Config::Util::load_mode_config($config_file, $mode);

Loads the mode config from the config file $config_file and the mode $mode and returns an L<SPVM::Builder::Config::Base> object.

$config_file is a config file path, such as C<path/MyClass.config> and C<path/MyClass.debug.config>.

A mode config file is a config file with a mode.

  # Mode config file
  MyClass.debug.config

The mode config file path such as C<path/MyClass.$mode.config> is created from $config_file and $mode.

L<mode|SPVM::Builder::Config::Base/"mode"> field of the returned config object is set to $mode.

This function calls L</"load_config"> function internally.

See also L<SPVM::Builder::Config::Base/"Config Mode">.

Examples:

  my $config = SPVM::Builder::Config::Util::load_mode_config(__FILE__, "debug");

=head2 load_base_config

  my $config = SPVM::Builder::Config::Util::load_base_config($config_file);

Loads the base config from the config file $config_file and returns an L<SPVM::Builder::Config::Base> object.

A base config file is the config file that removes its mode. If $config_file is C<path/MyClass.debug.config>, the base config file is C<path/MyClass.config>.

This function calls L</"load_mode_config"> function internally.

Examples:

  my $config = SPVM::Builder::Config::Util::load_base_config(__FILE__);

=head2 remove_ext_from_config_file

  my $config_file_without_ext = SPVM::Builder::Config::Util::remove_ext_from_config_file($config_file);

Removes the all extension from the config file path $config_file and returns it.

=head2 load_config_global

  my $config_global = SPVM::Builder::Config::Util::load_config_global($config_global_file);

Loads the global config from the config file $config_global_file and returns an L<SPVM::Builder::Config::Global> object.

Examples:

  my $config_global = SPVM::Builder::Config::Util::load_config_global($config_global_file);

