package SPVM::Builder::API;

use strict;
use warnings;

use SPVM::Builder;

sub new {
  my $class = shift;
  
  my $self = {};
  
  my %options = @_;
  
  my $build_dir = $options{build_dir};
  
  my $builder = SPVM::Builder->new(build_dir => $build_dir);

  $self->{builder} = $builder;
  
  return bless $self, $class;
}

sub compile_spvm {
  my ($self, $class_name) = @_;
  
  my $builder = $self->{builder};
  
  my $success = $builder->compile_spvm($class_name, __FILE__, __LINE__);
  
  return $success;
}

sub get_error_messages {
  my ($self) = @_;
  
  my $builder = $self->{builder};
  
  my $error_messages = $builder->get_error_messages;
  
  return $error_messages;
}

sub get_class_names {
  my ($self) = @_;
  
  my $builder = $self->{builder};
  
  my $class_names = $builder->get_class_names;
  
  return $class_names;
}

sub get_method_names {
  my ($self, $class_name) = @_;
  
  my $builder = $self->{builder};
  
  my $method_names = $builder->get_class_names($class_name);
  
  return $method_names;
}

sub get_method_signature {
  my ($self, $class_name, $method_name) = @_;
  
  my $builder = $self->{builder};
  
  my $method_signature = $builder->get_method_signature($class_name, $method_name);
  
  return $method_signature;
}

sub build_shared_lib_dist_precompile {
  my ($self, $class_name) = @_;
  
  my $builder = $self->{builder};
  
  $builder->build_shared_lib_dist($class_name, 'precompile');
}

sub build_shared_lib_dist_native {
  my ($self, $class_name) = @_;
  
  my $builder = $self->{builder};

  $builder->build_shared_lib_dist($class_name, 'native');
}

1;

=head1 NAME

SPVM::Builder::API - SPVM Builder Public APIs

=head1 SYNOPSYS
  
  # Builder API
  my $api = SPVM::Builder::API->new(
    build_dir => '.spvm_build',
  );
  
  # Compile SPVM
  my $success = $api->compile_spvm('MyLib');
  unless ($success) {
    # Error message
    my $error_messages = $self->get_error_messages;
    for my $error_message (@$error_messages) {
      printf STDERR "[CompileError]$error_message\n";
    }
    exit 255;
  }
  
  # Class names
  my $class_names = $api->get_class_names;
  
  for my $class_name (@$class_names) {
    # Method names
    my $method_names = $api->get_method_names($class_name);
    
    for my $method_name (@$method_names) {
      # Method signature
      my $method_signature = $api->get_method_signature($class_name, $method_name);
      
      print "$class_name->$method_name: $method_signature\n";
    }
  }
  
=head1 DESCRIPTION

B<SPVM::Builder::API> is the public APIs of SPVM Builder. 

L<SPVM::Builder> is a private modules of L<SPVM>.

The names and arguments of the methods are changed without warnings in the future release.

However, the methods is useful to get the information of SPVM modules.

B<SPVM::Builder::API> provides the public APIs to call the methods. These APIs is public and stable.

=head1 METHODS

=head2 new

  # Builder API
  my $api = SPVM::Builder::API->new;

Create B<SPVM::Builder::API> object.

B<Options:>

=over 2

=item * build_dir

Build directory.

=back

=head2 compile_spvm

  # Compile SPVM
  my $success = $api->compile_spvm('MyLib');

Compile SPVM module. If succeeded, return true value, otherwise false value.

=head2 get_error_messages

  # Error message
  my $error_messages = $self->get_error_messages;

Get error messages of the compililation as array reference.

=head2 get_class_names

  # Class names
  my $class_names = $api->get_class_names;

Get class names as array reference.

=head2 get_method_names

  # Method names
  my $method_names = $api->get_method_names($class_name);

Get method names as array reference.

=head2 get_method_signature

  # Method signature
  my $method_signature = $api->get_method_signature($class_name, $method_name);

Get the method signature. The first argument is a class name. The second argument is a method name.

About method signatures, see L<SPVM::Document::LanguageSpecification>.

=head2 build_shared_lib_dist_precompile

  $api->build_shared_lib_dist_precompile($class_name)

Build a precompile shared library into C<blib/lib>.

=head2 build_shared_lib_dist_native

  $api->build_shared_lib_dist_native($class_name)

Build a native shared library into C<blib/lib>.
