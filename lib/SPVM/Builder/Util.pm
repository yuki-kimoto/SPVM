package SPVM::Builder::Util;

use strict;
use warnings;
use Carp 'croak';
use Config;
use File::Path 'mkpath';
use Pod::Usage 'pod2usage';
use Getopt::Long 'GetOptionsFromArray';
use List::Util 'min';
use File::Basename 'dirname';

use SPVM::Builder::Config;

# SPVM::Builder::tUtil is used from Makefile.PL
# so this module must be wrote as pure per script, not contain XS and don't use any other SPVM modules except for SPVM::Builder::Config.

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

  return SPVM::Builder::Util::unindent($output);
}

sub getopt {
  my ($array, $opts) = map { ref $_[0] eq 'ARRAY' ? shift : $_ } \@ARGV, [];
  my $save = Getopt::Long::Configure(qw(default no_auto_abbrev no_ignore_case),
    @$opts);
  GetOptionsFromArray $array, @_;
  Getopt::Long::Configure($save);
}

sub get_dll_func_address {
  my ($dll_file, $dll_func_name) = @_;
  
  my $native_address;
  
  if ($dll_file) {
    my $dll_libref = DynaLoader::dl_load_file($dll_file);
    if ($dll_libref) {
      $native_address = DynaLoader::dl_find_symbol($dll_libref, $dll_func_name);
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

sub convert_module_file_to_dll_category_file {
  my ($module_file, $category) = @_;
  
  $module_file =~ s/\.[^.]+$//;
  my $dll_category_file .= "$module_file.$category.$Config{dlext}";
  
  return $dll_category_file;
}

sub convert_package_name_to_dll_category_rel_file {
  my ($package_name, $category) = @_;
  
  my $dlext = $Config{dlext};
  my $dll_category_rel_file = convert_package_name_to_rel_file_without_ext($package_name);
  $dll_category_rel_file .= ".$category.$dlext";
  
  return $dll_category_rel_file;
}

sub convert_package_name_to_rel_file {
  my ($package_name) = @_;
  
  my $rel_file = $package_name;
  $rel_file =~ s/::/\//;
  $rel_file .= '.spvm';
  
  return $rel_file;
}

sub convert_package_name_to_rel_dir {
  my ($package_name) = @_;
  
  my $rel_dir;
  if ($package_name =~ /::/) {
    my $rel_file = $package_name;
    $rel_file =~ s/::/\//;
    $rel_dir = dirname $rel_file;
  }
  else {
    $rel_dir = '';
  }
  
  return $rel_dir;
}

sub convert_package_name_to_category_rel_file_with_ext {
  my ($package_name, $category, $ext) = @_;
  
  my $rel_file_with_ext = $package_name;
  $rel_file_with_ext =~ s/::/\//;
  $rel_file_with_ext .= ".$category.$ext";
  
  return $rel_file_with_ext;
}

sub convert_package_name_to_rel_file_with_ext {
  my ($package_name, $ext) = @_;
  
  my $rel_file_with_ext = $package_name;
  $rel_file_with_ext =~ s/::/\//;
  $rel_file_with_ext .= ".$ext";
  
  return $rel_file_with_ext;
}

sub convert_package_name_to_rel_file_without_ext {
  my ($package_name) = @_;
  
  my $rel_file_without_ext = $package_name;
  $rel_file_without_ext =~ s/::/\//;
  
  return $rel_file_without_ext;
}

sub remove_package_part_from_file {
  my ($file, $package_name) = @_;
  
  $file =~ s/\.spvm$//;
  my $package_file = $package_name;
  $package_file =~ s/::/\//g;
  $file =~ s/$package_file$//;
  $file =~ s/[\\\/]$//;
  
  return $file;
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

  my $tmp_dir = "spvm_build/work/tmp";
  mkpath $tmp_dir;

  my $output_dir = 'blib/lib';
  
  my $package_rel_file = convert_package_name_to_rel_file($package_name);
  my $input_src_dir = "$input_dir/$package_rel_file";
  
  my $spvm_file = $package_rel_file;
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
  my $dll_rel_file = convert_package_name_to_dll_category_rel_file($package_name, $category);
  my $dll_file = "blib/lib/$dll_rel_file";
  
  # Get source files
  $make_rule
    .= "$target_name :: $dll_file\n\n";
  $make_rule
    .= "$dll_file :: @deps\n\n";
  $make_rule
    .= "\t$^X -Mblib -MSPVM::Builder -e \"SPVM::Builder->new(build_dir => 'spvm_build')->build_dll_${category}_dist('$package_name')\"\n\n";
  
  return $make_rule;
}

sub new_default_build_config {
  my $build_config = SPVM::Builder::Config->new;
  
  # Use default config
  my $default_config = {%Config};
  $build_config->replace_all_config($default_config);
  
  # Include directory
  my $include_dir = $INC{"SPVM/Builder/Util.pm"};
  $include_dir =~ s/\/Util\.pm$//;
  $include_dir .= '/include';
  $build_config->add_ccflags("-I$include_dir");

  # lib directory
  my $lib_dir = $INC{"SPVM/Builder/Util.pm"};
  $lib_dir =~ s/\/SPVM\/Builder\/Util.pm$//;
  $build_config->add_ccflags("-I$lib_dir");
  
  # math library
  $build_config->add_extra_linker_flags("-lm");
  
  # C99
  $build_config->set_std('c99');
  
  # Optimize
  $build_config->set_optimize('-O3');
  
  # Source exetension
  $build_config->set_src_ext('c');
  
  # I want to print warnings, but if gcc version is different, can't suppress no needed warning message.
  # so I dicide not to print warning in release version
  if ($ENV{SPVM_TEST_ENABLE_WARNINGS}) {
    $build_config->add_ccflags("-Wall -Wextra -Wno-unused-label -Wno-unused-function -Wno-unused-label -Wno-unused-parameter -Wno-unused-variable -Wno-missing-field-initializers");
  }
  
  return $build_config;
}

1;

=head1 NAME

SPVM::Builder::Util - Build Utilities

B<Create defaulgt build config>

  use SPVM::Builder::Util;

  my $build_config = SPVM::Builder::Util::new_default_build_config();

  $build_config->set_optimize('-O3');
  

B<Add Build shared object make rule in Makefile.PL>

  sub MY::postamble {

    my $make_rule = '';
    
    # Native compile make rule
    $make_rule .= SPVM::Builder::Util::create_make_rule_native('Foo');
    
    # Precompile make rule
    $make_rule .= SPVM::Builder::Util::create_make_rule_precompile('Foo');
    
    return $make_rule;
  }

=head1 DESCRIPTION

SPVM::Builder::Util is building utilities.

=head1 FUNCTIONS

=head2 new_default_build_config
  
  my $build_config = SPVM::Builder::Util::new_default_build_config;

Create defaulgt build config. This is L<SPVM::Builder::Config> object.

This function is used in native config file.

  # Foo.spvm.bconf
  use strict;
  use warnings;

  use SPVM::Builder::Util;

  my $build_config = SPVM::Builder::Util::new_default_build_config();

  $build_config->set_config(optimize => '-O2');

  $build_config;

=head2 create_make_rule_native

Create native compile make rule.

This is used in Makefile.PL of your distributed module.
  
  # Makefile.PL
  sub MY::postamble {

    my $make_rule = '';
    
    # Native compile make rule
    $make_rule .= SPVM::Builder::Util::create_make_rule_native('Foo');
    
    return $make_rule;
  }

=head2 create_make_rule_precompile

Create precompile make rule.

This is used in Makefile.PL of your distributed module.

  sub MY::postamble {

    my $make_rule = '';
    
    # Precompile make rule
    $make_rule .= SPVM::Builder::Util::create_make_rule_precompile('Foo');
    
    return $make_rule;
  }

