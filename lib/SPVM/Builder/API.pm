package SPVM::Builder::API;

use strict;
use warnings;

use SPVM::Builder;
use SPVM::Builder::CC;

sub build_parallel_dynamic_lib_dist {
  my ($options) = @_;
  
  my @new_option_names = (
    'build_dir',
    'output_dir',
    'jobs',
  );
  
  my @build_parallel_option_names = (
    'native_classes',
    'native_classes_file',
    'precompile_classes',
    'precompile_classes_file',
    'config_global_file',
  );
  
  my @all_option_names = (@new_option_names, @build_parallel_option_names);
  SPVM::Builder::Util::check_option_names($options, \@all_option_names);
  
  my %is_new_option = map { $_ => 1 } @new_option_names;
  
  my $new_options = {};
  my $build_parallel_options = {};
  
  if ($options) {
    for my $key (keys %$options) {
      if ($is_new_option{$key}) {
        $new_options->{$key} = $options->{$key};
      }
      else {
        $build_parallel_options->{$key} = $options->{$key};
      }
    }
  }
  
  my $builder = SPVM::Builder->new(%$new_options);
  my $builder_cc = SPVM::Builder::CC->new(builder => $builder);
  $builder_cc->build_parallel_dynamic_lib_dist($build_parallel_options);
}

1;

=head1 Name

SPVM::Builder::API - Builder APIs

=head1 Description

SPVM::Builder::API class has the public methods to build SPVM native classes and SPVM precompilation classes.

=head1 Usage
  
  SPVM::Builder::API::build_parallel({
    build_dir => '.spvm_build',
    native_classes => ['MyClass'],
    precompile_classes => ['MyClass'],
  });

=head1 Functions

=head2 build_parallel_dynamic_lib_dist

  SPVM::Builder::API::build_parallel_dynamic_lib_dist($options);

Generates dynamic libraries for multiple native classes and precompile classes in parallel, and copies them into the C<blib/lib> directory.

C<$options> is a hash reference.

=head2 Options

=over 2

=item * C<build_dir>

A build directory.

=item * C<output_dir>

A output directory.

=item * C<jobs>

The number of parallel jobs. The default value is the number of CPU cores.

=item * C<config_global_file>

A global configuration file path. If it is defined, the file is loaded as an L<SPVM::Builder::Config::Global> object and applied globally during the build process.

=item * C<native_classes>

An array reference of native class names to be built.

=item * C<native_classes_file>

A path to a text file containing native class names to be built. The file must contain one class name per line. If both C<native_classes> and this option are specified, they are merged.

=item * C<precompile_classes>

An array reference of precompile class names to be built.

=item * C<precompile_classes_file>

A path to a text file containing precompile class names to be built. The file must contain one class name per line. If both C<precompile_classes> and this option are specified, they are merged.

=back

If this option is specified, it overrides the C<optimize> option and sets appropriate flags for both the compiler and the linker to match CMake's behavior.

=back
