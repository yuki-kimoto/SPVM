package SPVM::Build::JIT;

use strict;
use warnings;
use Carp 'croak', 'confess';
use File::Spec;

use ExtUtils::CBuilder;
use Config;
use File::Copy 'move';
use File::Path 'mkpath', 'rmtree';

use File::Basename 'dirname', 'basename';

use SPVM::Build::SPVMInfo;

sub new {
  my $class = shift;
  
  my $self = {};
  
  return bless $self, $class;
}

sub compile_packages {
  my $self = shift;
  
  my $packages = SPVM::Build::SPVMInfo::get_packages();
  
}

sub create_jit_sub_name {
  my ($self, $sub_name) = @_;
  
  my $jit_sub_name = $sub_name;
  
  $jit_sub_name =~ s/:/_/g;
  
  $jit_sub_name = "SPVM_JITCODE_$jit_sub_name";
  
  return $jit_sub_name;
}


sub create_jit_sub_file_name {
  my ($self, $sub_name) = @_;
  
  my $jit_sub_file_name = $sub_name;
  
  $jit_sub_file_name =~ s/:/_/g;

  # In windows, upper case file name and lower case file name.
  # so If FOO and foo subroutine is exists, one overwrite another.
  # I want to prevent this. so '-' is appended to upper case character
  $jit_sub_file_name =~ s/([A-Z])/-$1/g;
  
  $jit_sub_file_name = "SPVM_JITCODE_$jit_sub_file_name";

  return $jit_sub_file_name;
}

sub compile_jit_sub_func {
  return $SPVM::BUILD->jit->compile_jit_sub(@_);
}

sub compile_jit_sub {
  my ($self, $sub_id, $sub_jitcode_source) = @_;
  
  my $sub_abs_name = SPVM::Build::SPVMInfo::get_sub_name($sub_id);
  my $jit_sub_name = $self->create_jit_sub_name($sub_abs_name);
  my $jit_sub_file_name = $self->create_jit_sub_file_name($sub_abs_name);
  
  # Build JIT code
  my $build_dir = $SPVM::BUILD_DIR;
  unless (defined $build_dir && -d $build_dir) {
    confess "SPVM build directory must be specified for JIT compile";
  }
  
  # Create build process directory
  my $build_process_dir = $SPVM::BUILD->create_build_process_dir;
  
  my $jit_source_file = "$build_process_dir/$jit_sub_file_name.c";
  my $jit_shared_lib_file = "$build_process_dir/$jit_sub_file_name.$Config{dlext}";
  
  # Compile JIT code
  open my $fh, '>', $jit_source_file
    or die "Can't create $jit_source_file";
  print $fh $sub_jitcode_source;
  close $fh;
  
  {
    my $source_file = $jit_source_file;
    
    # Source directory
    my $source_dir = dirname $source_file;
    
    # Object created directory
    my $object_dir = $source_dir;
    
    # Include directory
    my $include_dirs = [];
    
    # Default include path
    my $api_header_include_dir = $INC{"SPVM/Build/ExtUtil.pm"};
    $api_header_include_dir =~ s/\/Build\/ExtUtil\.pm$//;
    push @$include_dirs, $api_header_include_dir;
    
    my $cbuilder_config = {};
    
    # OPTIMIZE
    $cbuilder_config->{optimize} ||= $SPVM::BUILD->extutil->optimize;
    
    # Compile source files
    my $quiet = 1;
    my $cbuilder = ExtUtils::CBuilder->new(quiet => $quiet, config => $cbuilder_config);
    my $object_files = [];
    
    # Object file
    my $object_file = $source_file;
    $object_file =~ s/\.c$//;
    $object_file .= '.o';
    
    # Compile source file
    $cbuilder->compile(
      source => $source_file,
      object_file => $object_file,
      include_dirs => $include_dirs,
      extra_compiler_flags => $SPVM::BUILD->extutil->extra_compiler_flags
    );
    push @$object_files, $object_file;

    # JIT Subroutine names
    my $native_sub_name = $sub_abs_name;
    $native_sub_name =~ s/:/_/g;
    $native_sub_name = "SPVM_JITCODE_$native_sub_name";
    
    my $lib_file = $cbuilder->link(
      objects => $object_files,
      module_name => $jit_sub_file_name,
      dl_func_list => [$native_sub_name],
    );
  }
  
  my $sub_jit_address = $SPVM::BUILD->extutil->search_shared_lib_func_address($jit_shared_lib_file, $jit_sub_name);
  
  $self->bind_jitcode_sub($sub_abs_name, $sub_jit_address);
  
  my $success = 1;
  
  return $success;
}

1;
