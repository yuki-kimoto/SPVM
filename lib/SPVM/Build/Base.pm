package SPVM::Build::Base;

# SPVM::Build::PPtUtil is used from Makefile.PL
# so this module must be wrote as pure per script, not contain XS and don't use any other SPVM modules.

use strict;
use warnings;
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
  my $class = shift;
  
  my $self = {};
  
  $self->{extra_compiler_flags} = SPVM::Build::Util::default_extra_compiler_flags();
  $self->{optimize} = SPVM::Build::Util::default_optimize();
  
  return bless $self, $class;
}

sub category {
  my $self = shift;
  
  $self->{category};
}

sub extra_compiler_flags {
  my $self = shift;
  
  return $self->{extra_compiler_flags};
}

sub optimize {
  my $self = shift;
  
  return $self->{optimize};
}

sub create_build_shared_lib_make_rule {
  my ($self, $package_name) = @_;
  
  my $make_rule;
  
  # dynamic section
  $make_rule
  = "dynamic :: ";

  my $package_name_under_score = $package_name;
  $package_name_under_score =~ s/:/_/g;
  
  $make_rule
    .= "shared_lib_$package_name_under_score ";
  $make_rule .= "\n\n";
  
  my $module_base_name = $package_name;
  $module_base_name =~ s/^.+:://;
  
  my $src_dir = $package_name;
  $src_dir =~ s/::/\//g;
  $src_dir = "lib/$src_dir." . $self->category;
  
  # Dependency
  my @deps = grep { $_ ne '.' && $_ ne '..' } glob "$src_dir/*";
  
  # Shared library file
  my $shared_lib_bilb_file = SPVM::Build::Util::convert_package_name_to_shared_lib_bilb_file($package_name, $self->category);
  
  # Get source files
  my $module_category = $self->category;
  $module_category = ucfirst $module_category;
  $make_rule
    .= "shared_lib_$package_name_under_score :: $shared_lib_bilb_file\n\n";
  $make_rule
    .= "$shared_lib_bilb_file :: @deps\n\n";
  $make_rule
    .= "\tperl -Ilib -MSPVM::Build::$module_category -e \"SPVM::Build::$module_category->new->build_shared_lib_dist('$package_name')\"\n\n";
  
  return $make_rule;
}

sub build_shared_lib {
  my ($self, %opt) = @_;
  
  # Source directory
  my $input_dir_new = $opt{input_dir};
  
  # Package name
  my $package_name = $opt{package_name};
  
  # Object created directory
  my $output_dir = $opt{output_dir};
  
  my $sub_names = $opt{sub_names};
  
  # Quiet output
  my $quiet = defined $opt{quiet} ? $opt{quiet} : 0;
 
  my $module_base_name = $package_name;
  $module_base_name =~ s/^.+:://;
  
  my $input_dir = $opt{input_dir};
  
  unless (defined $output_dir && -d $output_dir) {
    confess "SPVM build directory must be specified for " . $self->category . " build";
  }
  
  # Correct source files
  my $src_files = [];
  my @valid_exts = ('c', 'C', 'cpp', 'i', 's', 'cxx', 'cc');
  for my $src_file (glob "$input_dir/*") {
    if (grep { $src_file =~ /\.$_$/ } @valid_exts) {
      push @$src_files, $src_file;
    }
  }
  
  # Config
  my $config_file = "$input_dir/$module_base_name.config";
  my $config;
  if (-f $config_file) {
    $config = do $config_file
      or confess "Can't parser $config_file: $!$@";
  }
  
  # Include directory
  my $include_dirs = [];
  
  # Default include path
  my $env_header_include_dir = $INC{"SPVM/Build/Native.pm"};
  $env_header_include_dir =~ s/\/Build\/Native\.pm$//;
  push @$include_dirs, $env_header_include_dir;
  
  push @$include_dirs, $input_dir;
  
  # CBuilder config
  my $cbuilder_config = {};
  
  # Convert ExtUitls::MakeMaker config to ExtUtils::CBuilder config
  if ($config) {
    # CBuilder config name which compatible with ExtUtils::MakeMaker
    my @cbuilder_config_names_compatible = qw(
      optimize
      cc
      ccflags
      ld
      lddlflags
    );
    for my $cbuilder_name (@cbuilder_config_names_compatible) {
      my $makemaker_name = uc $cbuilder_name;
      
      if (defined $config->{$makemaker_name}) {
        $cbuilder_config->{$cbuilder_name} = delete $config->{$makemaker_name};
      }
    }
  }
  
  # Include directory
  if (defined $config->{INC}) {
    my $inc = delete $config->{INC};
    
    my @include_dirs_tmp = split /\s+/, $inc;
    for my $include_dir_tmp (reverse @include_dirs_tmp) {
      if ($include_dir_tmp =~ s/^-I//) {
        unshift @$include_dirs, $include_dir_tmp;
      }
      else {
        confess "Invalid include option \"$inc\"";
      }
    }
  }
  
  # Shared library
  my $extra_linker_flags = '';
  if (defined $config->{LIBS}) {
    my $libs = delete $config->{LIBS};
    
    if (ref $libs eq 'ARRAY') {
      $libs = join(' ', @$libs);
    }
    
    $extra_linker_flags .= $libs;
  }
  
  my @keys = keys %$config;
  if (@keys) {
    confess "$keys[0] is not supported option";
  }
  
  # OPTIMIZE
  $cbuilder_config->{optimize} ||= $self->optimize;
  
  # Compile source files
  my $cbuilder = ExtUtils::CBuilder->new(quiet => $quiet, config => $cbuilder_config);
  my $object_files = [];
  for my $src_file (@$src_files) {
    # Object file
    my $object_file = $package_name;
    $object_file =~ s/:/_/g;
    my $src_file_under_score = $src_file;
    $src_file_under_score =~ s/^.+\///;
    $src_file_under_score =~ s/[^a-zA-Z0-9]/_/g;
    $object_file = "$output_dir/${object_file}____$src_file_under_score.o";
    
    # Compile source file
    $cbuilder->compile(
      source => $src_file,
      object_file => $object_file,
      include_dirs => $include_dirs,
      extra_compiler_flags => $self->extra_compiler_flags
    );
    push @$object_files, $object_file;
  }
  
  my $dlext = $Config{dlext};
  
  my $cfunc_names = [];
  for my $sub_name (@$sub_names) {
    my $cfunc_name = "${package_name}::$sub_name";
    $cfunc_name =~ s/:/_/g;
    push @$cfunc_names, $cfunc_name;
  }
  
  # This is dummy to suppress boot strap function
  # This is bad hack
  unless (@$cfunc_names) {
    push @$cfunc_names, '';
  }
  
  my $shared_lib_file = $cbuilder->link(
    objects => $object_files,
    package_name => $package_name,
    dl_func_list => $cfunc_names,
    extra_linker_flags => $extra_linker_flags
  );
  
  return $shared_lib_file;
}

sub build_shared_lib_dist {
  my ($self, $package_name) = @_;
  
  my $input_dir = $self->input_dir_dist($package_name);
  
  my $package_load_path = SPVM::Build::Util::create_package_load_path('lib', $package_name);
  my $sub_names = $self->get_sub_names_from_module_file($package_load_path);
  
  # Build shared library
  my $shared_lib_file = $self->build_shared_lib(
    package_name => $package_name,
    input_dir => $input_dir,
    output_dir => '.',
    sub_names => $sub_names,
  );
  
  # Create shared lib blib directory
  my $shared_lib_blib_dir = SPVM::Build::Util::convert_package_name_to_shared_lib_blib_dir($package_name, $self->category);
  mkpath $shared_lib_blib_dir;
  
  # shared lib blib file
  my $shared_lib_blib_file = SPVM::Build::Util::convert_package_name_to_shared_lib_bilb_file($package_name, $self->category);
  
  # Move shared library file to blib directory
  move($shared_lib_file, $shared_lib_blib_file)
    or die "Can't move $shared_lib_file to $shared_lib_blib_file";
}

sub build_shared_lib_runtime {
  my ($self, $package) = @_;
  
  my $package_id = $package->{id};
  my $package_name = $package->{name};
  
  my $input_dir = SPVM::Build::SPVMInfo::get_package_load_path($package_name);
  my $category = $self->category;
  $input_dir =~ s/\.spvm$/.$category/;
  
  # Output directory
  my $output_dir = $SPVM::BUILD_DIR;
  unless (defined $output_dir && -d $output_dir) {
    confess "SPVM build directory must be specified for runtime " . $self->category . " build";
  }

  my $module_dir = SPVM::Build::SPVMInfo::get_package_load_path($package_name);
  $module_dir =~ s/\.spvm$//;
  
  my $package_name_slash = $package_name;
  $package_name_slash =~ s/::/\//g;
  
  $module_dir =~ s/$package_name_slash$//;
  $module_dir =~ s/\/$//;
  
  my $subs = $self->get_subs_from_package_id($package_id);
  my $sub_names = [map { $_->{name} } @$subs];
  
  my $shared_lib_file = $self->build_shared_lib(
    package_name => $package_name,
    input_dir => $input_dir,
    output_dir => $output_dir,
    quiet => 1,
    sub_names => $sub_names
  );
  
  return $shared_lib_file;
}

sub bind_subs {
  my ($self, $shared_lib_path, $subs) = @_;
  
  for my $sub (@$subs) {
    my $sub_name = $sub->{name};
    next if $sub_name =~ /^CORE::/;
    my $sub_name_spvm = "SPVM::$sub_name";

    my $cfunc_name = $self->create_cfunc_name($sub_name);
    my $cfunc_address = SPVM::Build::Util::get_shared_lib_func_address($shared_lib_path, $cfunc_name);

    unless ($cfunc_address) {
      my $sub_name_c = $sub_name_spvm;
      $sub_name_c =~ s/:/_/g;
      confess "Can't find function address of $sub_name_spvm(). Native function name must be $sub_name_c";
    }
    $self->bind_sub($sub_name, $cfunc_address);
  }
}

sub get_installed_shared_lib_path {
  my ($self, $package_name) = @_;
  
  my $package_name_with_spvm = $package_name;
  $package_name_with_spvm =~ s/SPVM:://;
  my @package_name_parts = split(/::/, $package_name_with_spvm);
  my $module_load_path = SPVM::Build::SPVMInfo::get_package_load_path($package_name_with_spvm);
  
  my $shared_lib_path = SPVM::Build::Util::convert_module_path_to_shared_lib_path($module_load_path, $self->category);
  
  return $shared_lib_path;
}

sub build_and_bind {
  my $self = shift;
  
  my $packages = SPVM::Build::SPVMInfo::get_packages();
  for my $package (@$packages) {
    my $package_id = $package->{id};
    my $package_name = $package->{name};
    
    next if $package_name eq "CORE";
    
    my $subs = $self->get_subs_from_package_id($package_id);
    if (@$subs) {
      my $installed_shared_lib_path = $self->get_installed_shared_lib_path($package_name);
      
      # Shared library is already installed in distribution directory
      if (-f $installed_shared_lib_path) {
        $self->bind_subs($installed_shared_lib_path, $subs);
      }
      # Shared library is not installed, so try runtime build
      else {
        # Try runtime compile
        my $runtime_shared_lib_path = $self->build_shared_lib_runtime($package);
        $self->bind_subs($runtime_shared_lib_path, $subs);
      }
    }
  }
}

1;
