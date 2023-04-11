package SPVM::Builder;

use strict;
use warnings;

use Carp 'confess';
use Scalar::Util 'weaken';
use File::Path 'mkpath';
use File::Basename 'dirname', 'basename';

use SPVM ();

use SPVM::Builder::CC;
use SPVM::Builder::Compiler;
use SPVM::Builder::Runtime;
use SPVM::Builder::Env;
use SPVM::Builder::Stack;

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

sub class_paths {
  my $self = shift;
  if (@_) {
    $self->{class_paths} = $_[0];
    return $self;
  }
  else {
    return $self->{class_paths};
  }
}

sub new {
  my $class = shift;
  
  my $self = {
    class_paths => [map { "$_/SPVM" } @INC],
    @_
  };
  
  bless $self, ref $class || $class;
  
  return $self;
}

sub build_dynamic_lib_dist {
  my ($self, $class_name, $category) = @_;
  
  # Create the compiler
  my $compiler = SPVM::Builder::Compiler->new(
    class_paths => $self->class_paths
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
  
  my $class_file = $runtime->get_class_file($class_name);
  my $method_names = $runtime->get_method_names($class_name, $category);
  my $anon_class_names = $runtime->get_anon_class_names($class_name);
  my $precompile_source = $runtime->build_precompile_class_source($class_name);
  my $dl_func_list = SPVM::Builder::Util::create_dl_func_list($class_name, $method_names, $anon_class_names, {category => $category});
  
  $cc->build_dist($class_name, {category => $category, class_file => $class_file, dl_func_list => $dl_func_list, precompile_source => $precompile_source});
}

1;

=encoding utf8

=head1 Name

SPVM::Builder - Build SPVM program

=head1 Description

Build SPVM program. Compile SPVM source codes. Bind native and precompile methods. Generate Perl subrotuines correspoing to SPVM methods. After that, run SPVM program.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
