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
  
  $builder->build_parallel_dynamic_lib_dist({
    native_classes => ['MyClass'],
    precompile_classes => ['MyClass'],
  });

=head1 Class Methods

=head2 new

  my $builder = SPVM::Builder::API->new(%options);

Creates a new L<SPVM::Builder::API> object, and returns it.

Options:

=over 2

=item * C<build_dir>

A build directory.

=item * C<output_dir>

A output directory.

=item * C<jobs>

The number of parallel jobs. The default value is the number of CPU cores.

=back

=head1 Instance Methods

=head2 build_parallel_dynamic_lib_dist

  $builder->build_parallel_dynamic_lib_dist($options);

Generates dynamic libraries for multiple native classes and precompile classes in parallel, and copies them into the C<blib/lib> directory.

Options:

C<$options> is a hash reference.

=over 2

=item * C<native_classes>

An array reference of native class names to be built.

=item * C<native_classes_file>

A path to a text file containing native class names to be built. The file must contain one class name per line. If both C<native_classes> and this option are specified, they are merged.

=item * C<precompile_classes>

An array reference of precompile class names to be built.

=item * C<precompile_classes_file>

A path to a text file containing precompile class names to be built. The file must contain one class name per line. If both C<precompile_classes> and this option are specified, they are merged.

=item * C<ccflags>

An array reference of extra compiler flags.

=item * C<defines>

An array reference of macro definitions. Each definition is passed to the compiler with the C<-D> prefix.

=item * C<ldflags>

An array reference of extra linker flags.

=item * C<build_type>

The build type for the compiler and linker. This option follows the standard CMake build types.

Options:

=over 2

=item * C<Debug>

For debugging. Optimization is disabled and debug symbols are enabled.

=item * C<Release>

For production. High optimization and no debug symbols.

=item * C<RelWithDebInfo>

For production with debug symbols. High optimization with debug symbols.

=item * C<MinSizeRel>

For production, optimized for binary size.

=back

If this option is specified, it overrides the C<optimize> option and sets appropriate flags for both the compiler and the linker to match CMake's behavior.

=back
