package SPVM::Builder;

use strict;
use warnings;

use Carp 'confess';
use Scalar::Util 'weaken';
use File::Path 'mkpath';
use File::Basename 'dirname', 'basename';

use SPVM::Builder::CC;
use SPVM::Builder::Compiler;
use SPVM::Builder::Runtime;
use SPVM::Builder::Env;
use SPVM::Builder::Stack;

# This SPVM load is needed for SPVM::Builder XS method binding to Perl
# because SPVM::Builder XS method is loaded when SPVM is loaded
use SPVM();

# Fields
sub build_dir {
  my $self = shift;
  if (@_) {
    $self->{build_dir} = $_[0];
    return $self;
  }
  else {
    return $self->{build_dir};
  }
}

sub compiler {
  my $self = shift;
  if (@_) {
    $self->{compiler} = $_[0];
    return $self;
  }
  else {
    return $self->{compiler};
  }
}

sub module_dirs {
  my $self = shift;
  if (@_) {
    $self->{module_dirs} = $_[0];
    return $self;
  }
  else {
    return $self->{module_dirs};
  }
}

sub dynamic_lib_files {
  my $self = shift;
  if (@_) {
    $self->{dynamic_lib_files} = $_[0];
    return $self;
  }
  else {
    return $self->{dynamic_lib_files};
  }
}

sub new {
  my $class = shift;
  
  my $self = {
    module_dirs => [map { "$_/SPVM" } @INC],
    @_
  };
  
  bless $self, ref $class || $class;
  
  # Create the compiler
  my $compiler = SPVM::Builder::Compiler->new(
    module_dirs => $self->module_dirs
  );
  
  $self->compiler($compiler);
  
  $self->dynamic_lib_files({});
  
  return $self;
}

sub create_build_src_path {
  my ($self, $rel_file) = @_;
  
  my $build_dir = $self->build_dir;
  my $build_src_path = "$build_dir/work/src";
  if (defined $rel_file) {
    $build_src_path .= "/$rel_file";
  }
  
  return $build_src_path;
}

sub create_build_include_path {
  my ($self, $rel_file) = @_;
  
  my $build_dir = $self->build_dir;
  my $build_include_path = "$build_dir/work/include";
  if (defined $rel_file) {
    $build_include_path .= "/$rel_file";
  }
  
  return $build_include_path;
}

sub create_build_object_path {
  my ($self, $rel_file) = @_;
  
  my $build_dir = $self->build_dir;
  my $build_output_path = "$build_dir/work/object";
  if (defined $rel_file) {
    $build_output_path .= "/$rel_file";
  }
  
  return $build_output_path;
}

sub create_build_lib_path {
  my ($self, $rel_file) = @_;
  
  my $build_dir = $self->build_dir;
  my $build_lib_path = "$build_dir/work/lib";
  if (defined $rel_file) {
    $build_lib_path .= "/$rel_file";
  }
  
  return $build_lib_path;
}

sub build_dynamic_lib_dist {
  my ($self, $class_name, $category) = @_;
  
  # Create the compiler
  my $compiler = SPVM::Builder::Compiler->new(
    module_dirs => $self->module_dirs
  );
  
  my $runtime = $compiler->compile($class_name, __FILE__, __LINE__);
  unless ($runtime) {
    $compiler->print_error_messages(*STDERR);
    exit(255);
  }
  my $cc = SPVM::Builder::CC->new(
    build_dir => $self->{build_dir},
    builder => $self,
  );
  
  my $module_file = SPVM::Builder::Runtime->get_module_file($runtime, $class_name);
  my $dl_func_list = SPVM::Builder::Runtime->create_dl_func_list($runtime, $class_name, {category => $category});
  my $precompile_source = SPVM::Builder::Runtime->build_precompile_class_source($runtime, $class_name);
  
  $cc->build_dist($class_name, {category => $category, module_file => $module_file, dl_func_list => $dl_func_list, precompile_source => $precompile_source});
}

1;

=encoding utf8

=head1 Name

SPVM::Builder - Build SPVM program

=head1 Description

Build SPVM program. Compile SPVM source codes. Bind native and precompile methods. Generate Perl subrotuines correspoing to SPVM methods. After that, run SPVM program.
