package SPVM::Builder;

our $VERSION = '0.9682';

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

require XSLoader;
XSLoader::load('SPVM', $VERSION);

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

sub new {
  my $class = shift;
  
  my $self = {
    module_dirs => [map { "$_/SPVM" } @INC],
    @_
  };
  
  bless $self, ref $class || $class;
  
  return $self;
}

sub build_dynamic_lib_dist {
  my ($self, $class_name, $category) = @_;
  
  # Create the compiler
  my $compiler = SPVM::Builder::Compiler->new(
    module_dirs => $self->module_dirs
  );
  
  my $success = $compiler->compile($class_name, __FILE__, __LINE__);
  unless ($success) {
    $compiler->print_error_messages(*STDERR);
    exit(255);
  }
  my $runtime = $compiler->build_runtime;
  my $cc = SPVM::Builder::CC->new(
    build_dir => $self->{build_dir},
  );
  
  my $module_file = $runtime->get_module_file($class_name);
  my $method_names = $runtime->get_method_names($class_name, $category);
  my $anon_class_names = $runtime->get_anon_class_names($class_name);
  my $precompile_source = SPVM::Builder::Runtime->build_precompile_class_source($runtime, $class_name);
  my $dl_func_list = SPVM::Builder::Util::create_dl_func_list($class_name, $method_names, $anon_class_names, {category => $category});
  
  $cc->build_dist($class_name, {category => $category, module_file => $module_file, dl_func_list => $dl_func_list, precompile_source => $precompile_source});
}

1;

=encoding utf8

=head1 Name

SPVM::Builder - Build SPVM program

=head1 Description

Build SPVM program. Compile SPVM source codes. Bind native and precompile methods. Generate Perl subrotuines correspoing to SPVM methods. After that, run SPVM program.
