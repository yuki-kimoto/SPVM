package SPVM::Builder::DependencyAnalyzer;

use strict;
use warnings;
use Carp 'confess';
use JSON::PP ();
use File::Basename 'basename';

use SPVM::Builder;
use SPVM::Builder::CC;
use SPVM::Builder::Util;

use SPVM::Builder::ScriptInfo;

# Fields
sub script_name {
  my $self = shift;
  if (@_) {
    $self->{script_name} = $_[0];
    return $self;
  }
  else {
    return $self->{script_name};
  }
}

sub with_version {
  my $self = shift;
  if (@_) {
    $self->{with_version} = $_[0];
    return $self;
  }
  else {
    return $self->{with_version};
  }
}

# Class Methods
sub new {
  my $class = shift;
  
  my $self = {
    @_,
  };
  
  return bless $self, ref $class || $class;
}

sub to_lines {
  my ($class, $array) = @_;
  
  my $lines = '';
  
  for my $elem (@$array) {
    $lines .= "$elem\x0A";
  }
  
  return $lines;
}

# Instance Methods
sub dump_resource_info {
  my ($self) = @_;
  
  my $script_name = $self->{script_name};
  
  my $script_info = SPVM::Builder::ScriptInfo->new(script_name => $script_name);
  
  my $class_names = [grep { $script_info->is_resource_loader($_) } @{$script_info->get_class_names}];
  
  my $resource_info = "";
  
  for my $class_name (@$class_names) {
    my $config_file = $script_info->get_config_file($class_name);
    
    $resource_info .= <<"EOS";
[$class_name]
# $config_file
# Loaded Resources:
EOS
    
    for my $resource_name (@{$script_info->get_config($class_name)->get_resource_names}) {
      $resource_info .= "#    $resource_name\n";
    }
    
    my $config_content = $script_info->get_config_content($class_name);
    
    $resource_info .= "$config_content\n";
  }
  
  return $resource_info;
}

sub to_class_infos {
  my ($self) = @_;
  
  my $script_name = $self->{script_name};
  
  my $script_info = SPVM::Builder::ScriptInfo->new(script_name => $script_name);
  
  my $runtime = $script_info->runtime;
  
  my $class_names = $script_info->get_class_names;
  
  my $class_infos = [];
  
  for my $class_name (sort @$class_names) {
    
    my $basic_type = $runtime->get_basic_type_by_name($class_name);
    
    my $class_info = {};
    
    $class_info->{class_name} = $class_name;
    
    my $version_string = $basic_type->get_version_string;
    
    my $basic_type_in_version_from = $basic_type->get_basic_type_in_version_from;
    
    if (defined $version_string) {
      $class_info->{version} = $version_string;
    }
    elsif ($basic_type_in_version_from) {
      my $basic_type_name_in_version_from = $basic_type_in_version_from->get_name;
      $class_info->{version_from} = $basic_type_name_in_version_from;
    }
    
    push @$class_infos, $class_info;
  }
  
  return $class_infos;
}

sub to_json {
  my ($self) = @_;
  
  my $script_name = $self->{script_name};
  
  my $with_version = $self->{with_version};
  
  my $script_info = SPVM::Builder::ScriptInfo->new(script_name => $script_name);
  
  my $class_infos = $self->to_class_infos;
  
  my $class_names = [];
  
  my $json = "[\x0A";
  
  for (my $i = 0; $i < @$class_infos; $i++) {
    my $class_info = $class_infos->[$i];
    
    my $class_name = $class_info->{class_name};
    
    my $version = $class_info->{version};
    
    my $version_from = $class_info->{version_from};
    
    $json .= "  {";
    
    $json .= "\"class_name\":\"$class_name\"";
    if ($with_version) {
      if (defined $version) {
        $json .= ",\"version\":\"$version\"";
      }
      elsif ($version_from) {
        $json .= ",\"version_from\":\"$version_from\"";
      }
    }
    $json .= "}";
    
    if ($i < @$class_infos - 1) {
      $json .= ",";
    }
    
    $json .= "\x0A";
  }
  
  $json .= "]\x0A";
  
  return $json;
}

sub to_class_names {
  my ($self) = @_;
  
  my $script_name = $self->{script_name};
  
  my $with_version = $self->{with_version};
  
  my $script_info = SPVM::Builder::ScriptInfo->new(script_name => $script_name);
  
  my $class_infos = $self->to_class_infos;
  
  my $class_names = [];
  
  for my $class_info (@$class_infos) {
    
    my $class_name_only = $class_info->{class_name};
    
    my $version = $class_info->{version};
    
    my $version_from = $class_info->{version_from};
    
    my $class_name = "$class_name_only";
    
    if ($with_version) {
      if (defined $version) {
        $class_name .= " $version";
      }
      elsif ($version_from) {
        $class_name .= " (version_from $version_from)";
      }
    }
    
    push @$class_names, $class_name;
  }
  
  return $class_names;
}

sub to_cpanm_commands {
  my ($self) = @_;
  
  my $script_name = $self->{script_name};
  
  my $with_version = $self->{with_version};
  
  my $script_info = SPVM::Builder::ScriptInfo->new(script_name => $script_name);
  
  my $class_infos = $self->to_class_infos;
  
  my $cpanm_commands = [];
  
  for my $class_info (@$class_infos) {
    
    my $class_name = $class_info->{class_name};
    
    my $version = $class_info->{version};
    
    if (defined $version) {
      my $cpanm_command = "cpanm ";
      
      if ($class_name eq "SPVM") {
        $cpanm_command .= "SPVM";
      }
      else {
        $cpanm_command .= "SPVM::$class_name";
      }
      
      if ($with_version) {
        if (defined $version) {
          $cpanm_command .= "\@$version";
        }
      }
      
      push @$cpanm_commands, $cpanm_command;
    }
  }
  
  return $cpanm_commands;
}

1;

=head1 Name

SPVM::Builder::DependencyAnalyzer - Utility for Analyzing Class Dependencies

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
