package SPVM::Build::Util;

use strict;
use warnings;
use Carp 'croak';
use Config;
use File::Basename 'dirname', 'basename';
use File::Path 'mkpath';
use Pod::Usage 'pod2usage';
use Getopt::Long 'GetOptionsFromArray';
use List::Util 'min';

use SPVM::Build::Config;

# SPVM::Build::tUtil is used from Makefile.PL
# so this module must be wrote as pure per script, not contain XS and don't use any other SPVM modules except for SPVM::Build::Config.

sub unindent {
  my $str = shift;
  my $min = min map { m/^([ \t]*)/; length $1 || () } split "\n", $str;
  $str =~ s/^[ \t]{0,$min}//gm if $min;
  return $str;
}

sub extract_usage {
  my $file = @_ ? "$_[0]" : (caller)[1];

  open my $handle, '>', \my $output;
  pod2usage -exitval => 'noexit', -input => $file, -output => $handle;
  $output =~ s/^.*\n|\n$//;
  $output =~ s/\n$//;

  return SPVM::Build::Util::unindent($output);
}

sub getopt {
  my ($array, $opts) = map { ref $_[0] eq 'ARRAY' ? shift : $_ } \@ARGV, [];
  my $save = Getopt::Long::Configure(qw(default no_auto_abbrev no_ignore_case),
    @$opts);
  GetOptionsFromArray $array, @_;
  Getopt::Long::Configure($save);
}

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
    .= "\t$^X -Mblib -MSPVM::Build -e \"SPVM::Build->new(build_dir => 'spvm_build')->build_shared_lib_${category}_dist('$package_name')\"\n\n";
  
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

sub new_default_build_config {
  my $build_config = SPVM::Build::Config->new;
  
  # Use default config
  my $default_config = {%Config};
  $build_config->replace_all_config($default_config);
  
  # Include directory
  my $include_dir = $INC{"SPVM/Build/Util.pm"};
  $include_dir =~ s/\/Util\.pm$//;
  $include_dir .= '/include';
  $build_config->add_ccflags("-I$include_dir");

  # lib directory
  my $lib_dir = $INC{"SPVM/Build/Util.pm"};
  $lib_dir =~ s/\/SPVM\/Build\/Util.pm$//;
  $build_config->add_ccflags("-I$lib_dir");
  
  # C99
  $build_config->set_std('c99');
  
  # Optimize
  $build_config->set_optimize('-O3');
  
  # I want to print warnings, but if gcc version is different, can't suppress no needed warning message.
  # so I dicide not to print warning in release version
  if ($ENV{SPVM_TEST_ENABLE_WARNINGS}) {
    $build_config->add_ccflags("-Wall -Wextra -Wno-unused-label -Wno-unused-function -Wno-unused-label -Wno-unused-parameter -Wno-unused-variable");
  }
  
  return $build_config;
}

1;

=head1 NAME

SPVM::Build::Util - Build Utilities

B<Create defaulgt build config>

  use SPVM::Build::Util;

  my $build_config = SPVM::Build::Util::new_default_build_config();

  $build_config->set_optimize('-O3');
  

B<Add Build shared library make rule in Makefile.PL>

  sub MY::postamble {

    my $make_rule = '';
    
    # Native compile make rule
    $make_rule .= SPVM::Build::Util::create_make_rule_native('Foo');
    
    # Precompile make rule
    $make_rule .= SPVM::Build::Util::create_make_rule_precompile('Foo');
    
    return $make_rule;
  }

=head1 DESCRIPTION

SPVM::Build::Util is building utilities.

=head1 FUNCTIONS

=head2 new_default_build_config
  
  my $build_config = SPVM::Build::Util::new_default_build_config;

Create defaulgt build config. This is L<SPVM::Build::Config> object.

This function is used in native config file.

  # Foo.native/Foo.config
  use strict;
  use warnings;

  use SPVM::Build::Util;

  my $build_config = SPVM::Build::Util::new_default_build_config();

  $build_config->set_config(optimize => '-O2');

  $build_config;

=head2 create_make_rule_native

Create native compile make rule.

This is used in Makefile.PL of your distributed module.
  
  # Makefile.PL
  sub MY::postamble {

    my $make_rule = '';
    
    # Native compile make rule
    $make_rule .= SPVM::Build::Util::create_make_rule_native('Foo');
    
    return $make_rule;
  }

=head2 create_make_rule_precompile

Create precompile make rule.

This is used in Makefile.PL of your distributed module.

  sub MY::postamble {

    my $make_rule = '';
    
    # Precompile make rule
    $make_rule .= SPVM::Build::Util::create_make_rule_precompile('Foo');
    
    return $make_rule;
  }

