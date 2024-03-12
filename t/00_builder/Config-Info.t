use lib "t/testlib";
use TestAuto;
use lib "t/02_vm/lib";

use strict;
use warnings;

use Test::More;

use SPVM::Builder::Config::Info;

my $class_name = 'TestCase::UseResource::Basic';

# get_class_names
{
  my $builder_info = SPVM::Builder::Config::Info->new(class_name => $class_name);
  
  my $class_names = $builder_info->get_class_names;
  
  ok(grep { $_ eq 'TestCase::UseResource::Basic' } @$class_names);
  
  ok(grep { $_ eq 'Int' } @$class_names);
}

# is_resource_loader
{
  my $builder_info = SPVM::Builder::Config::Info->new(class_name => $class_name);
  
  my $resource_loader_class_names = [grep { $builder_info->is_resource_loader($_) } @{$builder_info->get_class_names}];
  
  is_deeply($resource_loader_class_names, ['TestCase::UseResource::Basic']);
}

# has_config_file
{
  my $builder_info = SPVM::Builder::Config::Info->new(class_name => $class_name);
  
  ok($builder_info->has_config_file('TestCase::UseResource::Basic'));
  
  ok(!$builder_info->has_config_file('Byte'));
}

# get_config_file
{
  my $builder_info = SPVM::Builder::Config::Info->new(class_name => $class_name);
  
  my $config_file = $builder_info->get_config_file($class_name);
  
  my $class_rel_file = $class_name;
  $class_rel_file =~ s|::|/|g;
  
  like($config_file, qr/$class_rel_file\.config/);
}

# get_config_content
{
  my $builder_info = SPVM::Builder::Config::Info->new(class_name => $class_name);
  
  my $config_content = $builder_info->get_config_content($class_name);
  
  like($config_content, qr/use_resource.+TestCase::Resource::Mylib1/);
}

# get_config
{
  my $builder_info = SPVM::Builder::Config::Info->new(class_name => $class_name);
  
  my $config = $builder_info->get_config($class_name);
  
  ok($config->isa('SPVM::Builder::Config'));
  
  my $config_resource_names = $config->get_resource_names($class_name);
  
  is_deeply($config_resource_names, ['TestCase::Resource::Mylib1']);
}

ok(1);

done_testing;
