package SPVM::Builder::Util;

use strict;
use warnings;
use Carp 'confess';
use Config;
use File::Path 'mkpath';
use Pod::Usage 'pod2usage';
use Getopt::Long 'GetOptionsFromArray';
use List::Util 'min';
use File::Basename 'dirname';

# SPVM::Builder::Util is used from Makefile.PL
# so this module must be wrote as pure perl script, not contain XS functions and don't use any other SPVM modules.

sub create_cfunc_name {
  my ($package_name, $method_name, $category) = @_;
  
  my $prefix = 'SP' . uc($category) . '__';
  
  # Precompile Method names
  my $method_abs_name_under_score = "${package_name}::$method_name";
  $method_abs_name_under_score =~ s/:/_/g;
  my $cfunc_name = "$prefix$method_abs_name_under_score";
  
  return $cfunc_name;
}

sub load_config {
  my ($config_file) = @_;
  
  open my $config_fh, '<', $config_file
    or confess "Can't open $config_file: $!";
  my $config_content = do { local $/; <$config_fh> };
  my $bconf = eval "$config_content";
  if (my $messge = $@) {
    confess "Can't parse config file \"$config_file\": $@";
  }
  
  return $bconf;
}

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

sub convert_module_file_to_shared_lib_file {
  my ($module_file, $category) = @_;
  
  my $dlext = $Config{dlext};
  $module_file =~ s/\.[^.]+$//;
  my $shared_lib_category_file = $module_file;
  $shared_lib_category_file .= $category eq 'native' ? ".$dlext" : ".$category.$dlext";
  
  return $shared_lib_category_file;
}

sub convert_package_name_to_shared_lib_rel_file {
  my ($package_name, $category) = @_;
  
  my $dlext = $Config{dlext};
  my $shared_lib_category_rel_file = convert_package_name_to_rel_file($package_name);
  $shared_lib_category_rel_file .= $category eq 'native' ? ".$dlext" : ".$category.$dlext";
  
  return $shared_lib_category_rel_file;
}

sub convert_package_name_to_category_rel_file {
  my ($package_name, $category, $ext) = @_;
  
  my $rel_file_with_ext = $package_name;
  $rel_file_with_ext =~ s/::/\//g;
  $rel_file_with_ext .= $category eq 'native' ? "" : ".$category";
  if (defined $ext) {
    $rel_file_with_ext .= ".$ext";
  }
  
  return $rel_file_with_ext;
}

sub convert_package_name_to_rel_dir {
  my ($package_name) = @_;
  
  my $rel_dir;
  if ($package_name =~ /::/) {
    my $rel_file = $package_name;
    $rel_file =~ s/::/\//g;
    $rel_dir = dirname $rel_file;
  }
  else {
    $rel_dir = '';
  }
  
  return $rel_dir;
}

sub convert_package_name_to_rel_file {
  my ($package_name, $ext) = @_;
  
  my $rel_file_with_ext = $package_name;
  $rel_file_with_ext =~ s/::/\//g;
  
  if (defined $ext) {
    $rel_file_with_ext .= ".$ext";
  }
  
  return $rel_file_with_ext;
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

  unless ($package_name =~ /^SPVM::/) {
    $package_name = "SPVM::$package_name";
  }
  
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
  
  my $src_dir = 'lib';

  my $package_rel_file = convert_package_name_to_rel_file($package_name, 'spvm');
  
  my $noext_file = $package_rel_file;
  $noext_file =~ s/\.[^\.]+$//;
  
  my $spvm_file = $noext_file;
  $spvm_file .= '.spvm';
  $spvm_file = "$src_dir/$spvm_file";
  
  my $native_c_file = $noext_file;
  $native_c_file .= '.c';
  $native_c_file = "$src_dir/$native_c_file";

  my $config_file = $noext_file;
  $config_file .= '.config';
  $config_file = "$src_dir/$config_file";

  # Dependency files
  my @deps;
  
  # Dependency c source files
  push @deps, grep { $_ ne '.' && $_ ne '..' } glob "$src_dir/$package_rel_file/*";
  
  # Dependency module file
  if ($category eq 'native') {
    push @deps, $spvm_file, $native_c_file, $config_file;
  }
  elsif ($category eq 'precompile') {
    push @deps, $spvm_file;
  }
  
  # Shared library file
  my $shared_lib_rel_file = convert_package_name_to_shared_lib_rel_file($package_name, $category);
  my $shared_lib_file = "blib/lib/$shared_lib_rel_file";
  
  # Get source files
  $make_rule
    .= "$target_name :: $shared_lib_file\n\n";
  $make_rule
    .= "$shared_lib_file :: @deps\n\n";
  $make_rule
    .= "\t$^X -Mblib -MSPVM::Builder -e \"SPVM::Builder->new(build_dir => '.spvm_build')->build_shared_lib_dist('$package_name', '$category')\"\n\n";
  
  return $make_rule;
}

1;

=head1 NAME

SPVM::Builder::Util - Build Utilities

=head1 DESCRIPTION

SPVM::Builder::Util is building utilities.

=head1 FUNCTIONS

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

