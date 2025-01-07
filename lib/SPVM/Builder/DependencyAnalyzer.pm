package SPVM::Builder::DependencyAnalyzer;

use strict;
use warnings;
use Carp 'confess';
use JSON::PP;
use File::Basename 'basename';

use SPVM::Builder;
use SPVM::Builder::CC;
use SPVM::Builder::Util;

use SPVM::Builder::ScriptInfo;

sub dump_resource_info {
  my ($class, $script_name) = @_;
  
  my $info = SPVM::Builder::ScriptInfo->new(script_name => $script_name);
  
  my $class_names = [grep { $info->is_resource_loader($_) } @{$info->get_class_names}];
  
  my $resource_info = "";
  
  for my $class_name (@$class_names) {
    my $config_file = $info->get_config_file($class_name);
    
    $resource_info .= <<"EOS";
[$class_name]
# $config_file
# Loaded Resources:
EOS
    
    for my $resource_name (@{$info->get_config($class_name)->get_resource_names}) {
      $resource_info .= "#    $resource_name\n";
    }
    
    my $config_content = $info->get_config_content($class_name);
    
    $resource_info .= "$config_content\n";
  }
  
  return $resource_info;
}

sub dump_dependency {
  my ($class, $script_name) = @_;
  
  my $info = SPVM::Builder::ScriptInfo->new(script_name => $script_name);
  
  my $runtime = $info->runtime;
  
  my $class_names = $info->get_class_names;
  
  my $dependency_infos = [];
  
  for my $class_name (sort @$class_names) {
    
    my $basic_type = $runtime->get_basic_type_by_name($class_name);
    
    my $version_string = $basic_type->get_version_string;
    
    my $dependency_info = "$class_name";
    
    if (length $version_string) {
      $dependency_info .= " $version_string";
    }
    
    push @$dependency_infos, $dependency_info;
  }
  
  my $dependency = join("\x0A", @$dependency_infos) . "\x0A";
  
  return $dependency;
}

sub dump_dependency_cpan {
  my ($class, $script_name) = @_;
  
  my $info = SPVM::Builder::ScriptInfo->new(script_name => $script_name);
  
  my $runtime = $info->runtime;
  
  my $class_names = $info->get_class_names;
  
  my $dependency_infos = [];
  
  for my $class_name (sort @$class_names) {
    
    my $basic_type = $runtime->get_basic_type_by_name($class_name);
    
    my $version_string = $basic_type->get_version_string;
    
    my $dependency_info;
    
    if ($class_name eq "SPVM") {
      $dependency_info = "SPVM";
    }
    else {
      $dependency_info = "SPVM::$class_name";
    }
    
    if (length $version_string) {
      $dependency_info .= " $version_string";
    }
    
    push @$dependency_infos, $dependency_info;
  }
  
  my $spvm_version_string = $runtime->get_spvm_version_string;
  
  unshift @$dependency_infos, "SPVM $spvm_version_string";
  
  my $dependency_cpan = join("\x0A", @$dependency_infos) . "\x0A";
  
  return $dependency_cpan;
}

1;

=head1 Name

SPVM::Builder::DependencyAnalyzer - Utility for Analyzing Class Dependencies

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
