use lib "t/testlib";
use TestAuto;
use lib "t/02_vm/lib";

use strict;
use warnings;

use Test::More;

use SPVM::Builder::Info;

my $class_name = 'TestCase::UseResource::Basic';

my $builder_info = SPVM::Builder::Info->new(class_name => $class_name);

my $resource_loader_class_names = $builder_info->get_resource_loader_class_names;

is_deeply($resource_loader_class_names, ['TestCase::UseResource::Basic']);

my $config_content = $builder_info->get_config_content($class_name);

like($config_content, qr/use_resource.+TestCase::Resource::Mylib1/);

my $resource_names = $builder_info->get_resource_names($class_name);

is_deeply($resource_names, ['TestCase::Resource::Mylib1']);

ok(1);

done_testing;
