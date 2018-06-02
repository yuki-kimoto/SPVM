package SPVM::Build::Precompile;

use strict;
use warnings;
use base 'SPVM::Build::Base';

use Carp 'croak', 'confess';
use File::Spec;

use SPVM::Build::Util;

use ExtUtils::CBuilder;
use Config;
use File::Copy 'move';
use File::Path 'mkpath', 'rmtree';

use File::Basename 'dirname', 'basename';

use SPVM::Build::SPVMInfo;
use SPVM::Build::Util;

sub new {
  my $self = shift->SUPER::new(@_);

  $self->{category} = 'precompile';
  
  return $self;
}

sub get_sub_names_from_module_file {
  my ($self, $module_file) = @_;
  
  return SPVM::Build::Util::get_precompile_sub_names_from_module_file($module_file);
}

sub get_subs_from_package_id {
  my ($self, $package_id) = @_;
  
  return SPVM::Build::SPVMInfo::get_precompile_subs_from_package_id($package_id);;
}

sub create_cfunc_name {
  my ($self, $sub_name) = @_;

  # Precompile Subroutine names
  my $cfunc_name = $sub_name;
  $cfunc_name =~ s/:/_/g;
  $cfunc_name = "SPVM_BUILD_PRECOMPILE_$cfunc_name";
  
  return $cfunc_name;
}

sub create_shared_lib_file_name {
  my ($self, $package_name) = @_;
  
  # Build Precompile code
  my $output_dir = $SPVM::BUILD_DIR;
  unless (defined $output_dir && -d $output_dir) {
    confess "SPVM build directory must be specified for precompile";
  }
  
  my $package_file_name = $package_name;
  $package_file_name =~ s/::/__/g;
  
  my $shared_lib_file_name = "$output_dir/$package_file_name.precompile/$package_file_name.$Config{dlext}";
  
  return $shared_lib_file_name;
}

sub build_shared_lib_runtime {
  my ($self, $package) = @_;

  my $package_id = $package->{id};
  my $package_name = $package->{name};

  # Output directory
  my $build_dir = $SPVM::BUILD_DIR;
  unless (defined $build_dir && -d $build_dir) {
    confess "SPVM build directory must be specified for runtime " . $self->category . " build";
  }

  my $package_file_name = $package_name;
  $package_file_name =~ s/::/__/g;
  my $output_dir = "$build_dir/$package_file_name." . $self->category;
  mkpath $output_dir;

  my $input_dir = $output_dir;
  
  my $subs = $self->get_subs_from_package_id($package->{id});
  my $sub_names = [map { $_->{name} } @$subs];

  my $csource_source = '';
  for my $sub_name (@$sub_names) {
    my $sub_csource_source = $self->build_csource($sub_name);
    $csource_source .= "$sub_csource_source\n";
  }
  my $source_file = "$input_dir/$package_file_name.c";

  # Get old csource source
  my $old_csource_source;
  if (-f $source_file) {
    open my $fh, '<', $source_file
      or die "Can't open $source_file";
    $old_csource_source = do { local $/; <$fh> };
  }
  else {
    $old_csource_source = '';
  }

  # Compile Precompile code
  open my $fh, '>', $source_file
    or die "Can't create $source_file";
  print $fh $csource_source;
  close $fh;
  
  if ($csource_source ne $old_csource_source) {
    $self->build_shared_lib(
      package_name => $package_name,
      input_dir => $input_dir,
      output_dir => $output_dir,
      quiet => 1,
      sub_names => $sub_names,
    );
  }
  
  return $self->create_shared_lib_file_name($package_name);
}

sub build_shared_lib {
  my ($self, %opt) = @_;
  
  my $package_name = $opt{package_name};
  my $sub_names = $opt{sub_names};
  my $output_dir = $opt{output_dir};
  my $input_dir = $opt{input_dir};
  
  # Build Precompile code
  unless (defined $output_dir && -d $output_dir) {
    confess "SPVM build directory must be specified for precompile";
  }
  
  my $package_file_name = $package_name;
  $package_file_name =~ s/::/__/g;
  
  # Include directory
  my $include_dirs = [];
  
  # Default include path
  my $env_header_include_dir = $INC{"SPVM/Build/Base.pm"};
  $env_header_include_dir =~ s/\/Build\/Base\.pm$//;
  push @$include_dirs, $env_header_include_dir;
  
  my $cbuilder_config = {};
  
  # OPTIMIZE
  $cbuilder_config->{optimize} ||= $self->optimize;
  
  # Compile source files
  my $quiet = 1;
  my $cbuilder = ExtUtils::CBuilder->new(quiet => $quiet, config => $cbuilder_config);
  my $object_files = [];
  
  # Object file
  my ($source_file) = glob "$input_dir/*.c";
  my $object_file = "$output_dir/" . basename($source_file);
  $object_file =~ s/\.c$//;
  $object_file .= '.o';
 
  # Compile source file
  $cbuilder->compile(
    source => $source_file,
    object_file => $object_file,
    include_dirs => $include_dirs,
    extra_compiler_flags => $self->extra_compiler_flags
  );
  push @$object_files, $object_file;
  
  my $cfunc_names = [map { $self->create_cfunc_name($_) } @$sub_names];
  my $lib_file = $cbuilder->link(
    objects => $object_files,
    module_name => $package_file_name,
    dl_func_list => $cfunc_names,
  );
  
  return $self->create_shared_lib_file_name($package_name);
}

1;
