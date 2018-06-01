package SPVM::Build::Native;

# SPVM::Build::PPtUtil is used from Makefile.PL
# so this module must be wrote as pure per script, not contain XS and don't use any other SPVM modules.

use strict;
use warnings;
use base 'SPVM::Build::Base';

use Carp 'croak', 'confess';

use SPVM::Build::Util;
use SPVM::Build::SPVMInfo;

use ExtUtils::CBuilder;
use Config;
use File::Copy 'move';
use File::Path 'mkpath';
use DynaLoader;

use File::Basename 'dirname', 'basename';

sub new {
  my $self = shift->SUPER::new(@_);

  $self->{category} = 'native';
  
  return $self;
}

sub get_sub_names_from_module_file {
  my ($self, $module_file) = @_;
  
  return SPVM::Build::Util::get_native_sub_names_from_module_file($module_file);
}

sub get_subs_from_package_id {
  my ($self, $package_id) = @_;
  
  return SPVM::Build::SPVMInfo::get_native_subs_from_package_id($package_id);;
}

sub create_cfunc_name {
  my ($self, $sub_name) = @_;

  my $sub_name_spvm = "SPVM::$sub_name";

  my $cfunc_name = $sub_name_spvm;
  $cfunc_name =~ s/:/_/g;
  
  return $cfunc_name;
}

sub input_dir_dist {
  my ($self, $package_name) = @_;
  
  my $input_dir = SPVM::Build::Util::create_package_load_path('lib', $package_name);
  my $category = $self->category;
  $input_dir =~ s/\.spvm$/.$category/;
  
  return $input_dir;
}

1;
