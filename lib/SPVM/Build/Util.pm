package SPVM::Build::Util;

use strict;
use warnings;
use Carp 'croak';
use Config;
use File::Basename 'dirname', 'basename';
use File::Path 'mkpath';

use SPVM::Build::Setting;

# SPVM::Build::tUtil is used from Makefile.PL
# so this module must be wrote as pure per script, not contain XS and don't use any other SPVM modules except for SPVM::Build::Config.

sub get_shared_lib_func_address {
  my ($shared_lib_file, $shared_lib_func_name) = @_;
  
  my $native_address;
  
  if ($shared_lib_file) {
    my $dll_libref = DynaLoader::dl_load_file($shared_lib_file);
    if ($dll_libref) {
      $native_address = DynaLoader::dl_find_symbol($dll_libref, $shared_lib_func_name);
    }
    else {
      return;
    }
  }
  else {
    return;
  }
  
  return $native_address;
}

sub convert_module_path_to_shared_lib_path {
  my ($module_path, $category) = @_;
  
  my $module_dir = dirname $module_path;
  my $base_name = basename $module_path;
  $base_name =~ s/\.[^.]+$//;
  
  my $shared_lib_path .= "$module_dir/$base_name.$category/$base_name.$Config{dlext}";
  
  return $shared_lib_path;
}

sub remove_package_part_from_path {
  my ($path, $package_name) = @_;
  
  $path =~ s/\.spvm$//;
  my $package_path = $package_name;
  $package_path =~ s/::/\//g;
  $path =~ s/$package_path$//;
  
  return $path;
}

sub create_make_rule_native {
  my $package_name = shift;
  
  create_package_make_rule($package_name, 'native');
}

sub create_make_rule_precompile {
  my $package_name = shift;
  
  create_package_make_rule($package_name, 'precompile');
}

sub create_package_make_rule {
  my ($package_name, $category) = @_;
  
  my $make_rule;
  
  # dynamic section
  $make_rule
  = "dynamic :: ";

  my $package_name_under_score = $package_name;
  $package_name_under_score =~ s/:/_/g;
  
  my $target_name = "spvm_${category}_$package_name_under_score ";
  $make_rule
    .= "$target_name ";
  $make_rule .= "\n\n";
  
  my $module_base_name = $package_name;
  $module_base_name =~ s/^.+:://;
  
  my $input_dir = 'lib';

  my $work_dir = "spvm_build/work";
  mkpath $work_dir;

  my $output_dir = 'blib/lib';
  
  my $package_path = convert_package_name_to_path($package_name, $category);
  my $input_src_dir = "$input_dir/$package_path";
  
  my $spvm_file = $package_path;
  $spvm_file =~ s/\.[^\.]+$//;
  $spvm_file .= '.spvm';
  $spvm_file = "$input_dir/$spvm_file";
  
  # Dependency files
  my @deps;
  
  # Dependency c source files
  push @deps, grep { $_ ne '.' && $_ ne '..' } glob "$input_src_dir/*";
  
  # Dependency module file
  push @deps, $spvm_file;
  
  # Shared library file
  my $shared_lib_rel_file = convert_package_name_to_shared_lib_rel_file($package_name, $category);
  my $shared_lib_file = "blib/lib/$shared_lib_rel_file";
  
  # Get source files
  $make_rule
    .= "$target_name :: $shared_lib_file\n\n";
  $make_rule
    .= "$shared_lib_file :: @deps\n\n";
  $make_rule
    .= "\t$^X -Mblib -MSPVM::Build -e \"SPVM::Build->new(build_dir => 'spvm_build')->create_shared_lib_${category}_dist('$package_name')\"\n\n";
  
  return $make_rule;
}

sub convert_package_name_to_path {
  my ($package_name, $category) = @_;
  
  my $module_base_name = $package_name;
  $module_base_name =~ s/^.+:://;
  
  my $shared_lib_rel_dir = $package_name;
  $shared_lib_rel_dir =~ s/::/\//g;
  $shared_lib_rel_dir = "$shared_lib_rel_dir.$category";
  
  return $shared_lib_rel_dir;
}

sub convert_package_name_to_shared_lib_rel_file {
  my ($package_name, $category) = @_;
  
  my $dlext = $Config{dlext};
  
  my $module_base_name = $package_name;
  $module_base_name =~ s/^.+:://;
  
  my $package_path = convert_package_name_to_path($package_name, $category);
  my $shared_lib_rel_file = "$package_path/$module_base_name.$dlext";
  
  return $shared_lib_rel_file;
}

sub convert_package_name_to_shared_lib_dir {
  my ($lib_dir, $package_name, $category) = @_;
  
  # Shared library file
  my $shared_lib_rel_dir = convert_package_name_to_path($package_name, $category);
  my $shared_lib_dir = "$lib_dir/$shared_lib_rel_dir";
  
  return $shared_lib_dir;
}

sub new_core_build_setting {
  my $build_setting = SPVM::Build::Setting->new;
  
  $build_setting->set_std('c99');

  # I want to print warnings, but if gcc version is different, can't suppress no needed warning message.
  # so I dicide not to print warning in release version
  if ($ENV{SPVM_TEST_ENABLE_WARNINGS}) {
    $build_setting->add_extra_compiler_flag("-Wall -Wextra -Wno-unused-label -Wno-unused-function -Wno-unused-label -Wno-unused-parameter -Wno-unused-variable");
  }
  
  # Config
  $build_setting->set_config(optimize => '-O3');
  
  return $build_setting;
}

sub new_build_setting {
  my $build_setting = SPVM::Build::Setting->new;
  
  $build_setting->set_std('c99');
  
  $build_setting->add_extra_compiler_flag("-Wall -Wextra");
  
  # Config
  $build_setting->set_config(optimize => '-O3');
  
  return $build_setting;
}

1;

