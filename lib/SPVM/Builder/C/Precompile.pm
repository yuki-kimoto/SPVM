package SPVM::Builder::C::Precompile;

use strict;
use warnings;
use base 'SPVM::Builder::C';

use Carp 'croak', 'confess';
use File::Spec;

use ExtUtils::CBuilder;
use Config;
use File::Copy 'move';
use File::Path 'mkpath', 'rmtree';

use File::Basename 'dirname', 'basename';

use SPVM::Builder;
use SPVM::Builder::Util;

sub new {
  my $self = shift->SUPER::new(@_);

  $self->{category} = 'precompile';
  
  return $self;
}

sub create_csource {
  my ($self, $package_name, $sub_names, $opt) = @_;
  
  my $input_dir = $opt->{input_dir};

  my $work_dir = $opt->{work_dir};
  mkpath $work_dir;
  
  my $output_dir = $opt->{output_dir};
  
  my $is_cached_ref = $opt->{is_cached};
  
  my $package_path = SPVM::Builder::Util::convert_package_name_to_path($package_name, $self->category);
  my $work_src_dir = "$work_dir/$package_path";
  mkpath $work_src_dir;
  
  my $module_base_name = $package_name;
  $module_base_name =~ s/^.+:://;
  
  my $source_file = "$work_src_dir/$module_base_name.c";

  # Get old csource source
  my $old_package_csource;
  if (-f $source_file) {
    open my $fh, '<', $source_file
      or die "Can't open $source_file";
    $old_package_csource = do { local $/; <$fh> };
  }
  else {
    $old_package_csource = '';
  }
  
  # Create c source file
  my $package_csource = $self->build_package_csource($package_name, $sub_names);
  open my $fh, '>', $source_file
    or die "Can't create $source_file";
  print $fh $package_csource;
  close $fh;
  
  if ($package_csource ne $old_package_csource) {
    $$is_cached_ref = 0;
  }
  else {
    $$is_cached_ref = 1;
  }
}

1;
