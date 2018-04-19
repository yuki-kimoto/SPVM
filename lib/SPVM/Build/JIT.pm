package SPVM::Build::JIT;

use strict;
use warnings;
use Carp 'croak', 'confess';

use ExtUtils::CBuilder;
use Config;
use File::Copy 'move';
use File::Path 'mkpath';

use File::Basename 'dirname', 'basename';

use SPVM::Build::SPVMInfo;

sub new {
  my $class = shift;
  
  my $self = {};
  
  return bless $self, $class;
}

sub compile_jitcode {
  my ($self, $source_file) = @_;
  
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
  
  # OPTIMIZE default is -O3
  $cbuilder_config->{optimize} ||= '-O3';
  
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
    extra_compiler_flags => '-std=c99' . ' -Wall -Wextra -Wno-unused-label -Wno-unused-function -Wno-unused-label -Wno-unused-parameter -Wno-unused-variable'
  );
  push @$object_files, $object_file;

  # JIT Subroutine names
  my $sub_names = SPVM::Build::SPVMInfo::get_sub_names();
  my @jit_sub_names;
  for my $abs_name (@$sub_names) {
    my $jit_sub_name = $abs_name;
    $jit_sub_name =~ s/:/_/g;
    $jit_sub_name = "SPVM_JITCODE_$jit_sub_name";
    push @jit_sub_names, $jit_sub_name;
  }
  
  my $lib_file = $cbuilder->link(
    objects => $object_files,
    module_name => 'SPVM::JITCode',
    dl_func_list => ['SPVM_JITCODE_call_sub', @jit_sub_names],
    extra_linker_flags => ''
  );
  
  return $lib_file;
}

sub create_jit_sub_name {
  my ($self, $sub_name) = @_;
  
  my $jit_sub_name = $sub_name;
  
  $jit_sub_name =~ s/:/_/g;
  
  $jit_sub_name = "SPVM_JITCODE_$jit_sub_name";
  
  return $jit_sub_name;
}

sub compile_jit_sub_func {
  return __PACKAGE__->new->compile_jit_sub(@_);
}

sub compile_jit_sub {
  my ($self, $sub_id, $sub_jitcode_source) = @_;
  
  my $sub_abs_name = SPVM::Build::SPVMInfo::get_sub_name($sub_id);
  my $jit_sub_name = $self->create_jit_sub_name($sub_abs_name);
  
  # Build JIT code
  my $jit_source_dir = $SPVM::TMP_DIR;
  my $jit_source_file = "$jit_source_dir/$jit_sub_name.c";
  my $jit_shared_lib_file = "$jit_source_dir/$jit_sub_name.$Config{dlext}";
  
  # Compile JIT code
  open my $fh, '>', $jit_source_file
    or die "Can't create $jit_source_file";
  print $fh $sub_jitcode_source;
  close $fh;
  
  $self->compile_jitcode($jit_source_file);
  
  my $sub_jit_address = SPVM::Build::ExtUtil->new->search_shared_lib_func_address($jit_shared_lib_file, $jit_sub_name);
  
  $self->bind_jitcode_sub($sub_abs_name, $sub_jit_address);
  
  my $success = 1;
  
  return $success;
}

1;
