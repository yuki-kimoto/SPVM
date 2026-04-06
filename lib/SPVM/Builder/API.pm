package SPVM::Builder::API;

use strict;
use warnings;

use SPVM::Builder;

sub new {
  my $class = shift;
  
  my $self = {};
  
  my %options = @_;
  
  my $builder = SPVM::Builder->new(%options);
  
  $self->{builder} = $builder;
  
  return bless $self, $class;
}

sub build_dynamic_lib_dist_precompile {
  my ($self, $class_name, $options) = @_;
  
  my $builder = $self->{builder};
  
  $builder->build_dynamic_lib_dist_precompile($class_name, $options);
}

sub build_dynamic_lib_dist_native {
  my ($self, $class_name, $options) = @_;
  
  my $builder = $self->{builder};
  
  $builder->build_dynamic_lib_dist_native($class_name, $options);
}

sub build_parallel_dynamic_lib_dist {
  my ($self, $options) = @_;
  
  my $builder = $self->{builder};
  
  $builder->build_parallel_dynamic_lib_dist($options);
}

1;

=head1 Name

SPVM::Builder::API - Builder APIs

=head1 Description

SPVM::Builder::API class has the public methods to build SPVM native classes and SPVM precompilation classes.

=head1 Usage
  
  my $builder = SPVM::Builder::API->new(
    build_dir => '.spvm_build',
  );
  
  $builder->build_dynamic_lib_dist_precompile('MyClass');
  
  $builder->build_dynamic_lib_dist_native('MyClass');

=head1 Class Methods

=head2 new

  my $builder = SPVM::Builder::API->new(%options);

Creates a new L<SPVM::Builder::API> object, and returns it.

Options:

=over 2

=item * C<build_dir>

A build directory.

=item * C<optimize>

The optimization level for the compiler.

=back

=head1 Instance Methods

=head2 build_dynamic_lib_dist_precompile

  $builder->build_dynamic_lib_dist_precompile($class_name)
  $builder->build_dynamic_lib_dist_precompile($class_name, $options)

Generates a dynamic library for a L<native class|SPVM::Document::NativeClass> given by the class name $class_name, and copies it into the C<blib/lib> directory.

A native class must have at least one method with L<native attribute|SPVM::Document::Language::Class/"Method Attributes">.

Options:

$options is a hash reference. This is optional.

=over 2

=item * C<force>

If this option is a true value, the compilation and link are forced.

=item * C<optimize>

The optimization level for the compiler (e.g., C<O2>, C<O3>, C<O0>).

=back

=head2 build_dynamic_lib_dist_native

  $builder->build_dynamic_lib_dist_native($class_name)
  $builder->build_dynamic_lib_dist_native($class_name, $options)

Generates a dynamic library for a precompilation class $class_name that has C<native> methods, and copies it into the C<blib/lib> directory.

A precompilation class must have at least one method with L<precompile attribute|SPVM::Document::Language::Class/"Method Attributes">.

Options:

$options is a hash reference. This is optional.

=over 2

=item * C<force>

If this option is a true value, the compilation and link are forced.

=item * C<optimize>

The optimization level for the compiler (e.g., C<O2>, C<O3>, C<O0>).

=back

=head2 build_parallel_dynamic_lib_dist

  $builder->build_parallel_dynamic_lib_dist($options)

Generates dynamic libraries for multiple native classes and precompile classes in parallel, and copies them into the C<blib/lib> directory.

Options:

C<$options> is a hash reference.

=over 2

=item * C<native_classes>

An array reference of native class names to be built.

=item * C<precompile_classes>

An array reference of precompile class names to be built.

=item * C<build_file>

A JSON configuration file path.

The configuration is loaded from this file and then overridden by the other options in C<$options>.

This file can contain the same build options as those passed directly to the method, such as C<native_classes> and C<precompile_classes>.

Using this file is highly recommended to avoid command-line length limits, especially on Windows environments, when dealing with a large number of classes.

The JSON format must be a hash at the top level. For example:

  {
    "native_classes" : ["Array", "Hash"],
    "precompile_classes" : ["Array"]
  }

=item * C<force>

If this option is a true value, the compilation and link are forced.

=item * C<optimize>

The optimization level for the compiler (e.g., C<O2>, C<O3>, C<O0>).

=item * C<jobs>

The number of parallel jobs. The default value is the number of CPU cores.

=back
