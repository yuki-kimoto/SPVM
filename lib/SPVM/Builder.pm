package SPVM::Builder;

use strict;
use warnings;

use Carp 'confess';
use Scalar::Util 'weaken';
use File::Path 'mkpath';
use File::Basename 'dirname', 'basename';

use SPVM::Builder::CC;
use SPVM::Builder::Runtime;

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

sub runtime {
  my $self = shift;
  if (@_) {
    $self->{runtime} = $_[0];
    return $self;
  }
  else {
    return $self->{runtime};
  }
}

sub native_env {
  my $self = shift;
  if (@_) {
    $self->{native_env} = $_[0];
    return $self;
  }
  else {
    return $self->{native_env};
  }
}

sub native_stack {
  my $self = shift;
  if (@_) {
    $self->{native_stack} = $_[0];
    return $self;
  }
  else {
    return $self->{native_stack};
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
  $self->create_compiler;
  
  $self->dynamic_lib_files({});
  
  return $self;
}

sub print_error_messages {
  my ($self, $fh) = @_;

  my $error_messages = $self->get_error_messages;
  for my $error_message (@$error_messages) {
    printf $fh "[CompileError]$error_message\n";
  }
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

sub get_dynamic_lib_file_dist {
  my ($self, $class_name, $category) = @_;

  my $module_module_file = $self->get_module_file($class_name);
  
  my $dynamic_lib_file = SPVM::Builder::Util::convert_module_file_to_dynamic_lib_file($module_module_file, $category);
  
  return $dynamic_lib_file;
}

sub build_dynamic_lib_dist {
  my ($self, $class_name, $category) = @_;

  my $compile_success = $self->compile($class_name, __FILE__, __LINE__);
  unless ($compile_success) {
    $self->print_error_messages(*STDERR);
    exit(255);
  }

  my $cc_native = SPVM::Builder::CC->new(
    build_dir => $self->{build_dir},
    builder => $self,
  );
  
  $cc_native->build_dist($class_name, {category => $category});
}

sub bind_methods {
  my ($self, $dynamic_lib_file, $class_name, $category) = @_;

  my $method_names = $self->get_method_names($class_name, $category);
  if (@$method_names) {
    my $method_infos = [];
    for my $method_name (@$method_names) {
      my $method_info = {};
      $method_info->{class_name} = $class_name;
      $method_info->{method_name} = $method_name;
      push @$method_infos, $method_info;
    }
    
    # Add anon class sub names if precompile
    if ($category eq 'precompile') {
      my $anon_class_names = $self->get_anon_class_names($class_name);
      for my $anon_class_name (@$anon_class_names) {
        my $method_info = {};
        $method_info->{class_name} = $anon_class_name;
        $method_info->{method_name} = "";
        push @$method_infos, $method_info;
      }
    }
    
    for my $method_info (@$method_infos) {
      my $class_name = $method_info->{class_name};
      my $method_name = $method_info->{method_name};

      my $cfunc_address;
      if ($dynamic_lib_file) {
        my $dynamic_lib_libref = DynaLoader::dl_load_file($dynamic_lib_file);
        
        if ($dynamic_lib_libref) {

          my $cfunc_name = SPVM::Builder::Util::create_cfunc_name($class_name, $method_name, $category);
          $cfunc_address = DynaLoader::dl_find_symbol($dynamic_lib_libref, $cfunc_name);
          unless ($cfunc_address) {
            my $dl_error = DynaLoader::dl_error();
            my $error = <<"EOS";
Can't find native function \"$cfunc_name\" corresponding to ${class_name}->$method_name in \"$dynamic_lib_file\"

You must write the following definition.
--------------------------------------------------
#include <spvm_native.h>

int32_t $cfunc_name(SPVM_ENV* env, SPVM_VALUE* stack) {
  
  return 0;
}
--------------------------------------------------

$dl_error
EOS
            confess $error;
          }
        }
        else {
          my $dl_error = DynaLoader::dl_error();
          confess "The DynaLoader::dl_load_file function failed:Can't load the \"$dynamic_lib_file\" file for the $category methods in the $class_name class: $dl_error";
        }
      }
      else {
        confess "DLL file is not specified";
      }
      
      if ($category eq 'native') {
        $self->set_native_method_address($class_name, $method_name, $cfunc_address);
      }
      elsif ($category eq 'precompile') {
        $self->set_precompile_method_address($class_name, $method_name, $cfunc_address);
      }
    }
  }
}

sub build_precompile_class_source_file {
  my ($self, $class_name, $options) = @_;
  
  # Config
  my $config = $options->{config};
  
  # Force
  my $force = $options->{force};
  
  # Output - Precompile C source file
  my $output_dir = $options->{output_dir};
  my $source_rel_file = SPVM::Builder::Util::convert_class_name_to_rel_file($class_name, 'precompile.c');
  my $source_file = "$output_dir/$source_rel_file";
  
  # Check if generating is needed
  my $module_file = $self->get_module_file($class_name);
  my $spvm_module_dir = $INC{'SPVM/Builder.pm'};
  $spvm_module_dir =~ s/\.pm$//;
  $spvm_module_dir .= '/src';
  my $spvm_precompile_soruce_file = "$spvm_module_dir/spvm_precompile.c";
  unless (-f $spvm_precompile_soruce_file) {
    confess "Can't find $spvm_precompile_soruce_file";
  }
  my $need_generate = SPVM::Builder::Util::need_generate({
    force => $force,
    output_file => $source_file,
    input_files => [$module_file, $spvm_precompile_soruce_file],
  });
  
  # Generate precompile C source file
  if ($need_generate) {
    my $precompile_source = SPVM::Builder::Runtime->build_precompile_class_source($self->runtime, $class_name);
    mkpath dirname $source_file;
    open my $fh, '>', $source_file
      or die "Can't create $source_file";
    print $fh $precompile_source;
    close $fh;
  }
}

1;

=encoding utf8

=head1 Name

SPVM::Builder - Build SPVM program

=head1 Description

Build SPVM program. Compile SPVM source codes. Bind native and precompile methods. Generate Perl subrotuines correspoing to SPVM methods. After that, run SPVM program.
