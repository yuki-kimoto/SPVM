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

sub build_dynamic_lib_dist_precompile {
  my ($self, $basic_type_name) = @_;
  
  my $builder = $self->{builder};
  
  $builder->build_dynamic_lib_dist_precompile($basic_type_name);
}

sub build_dynamic_lib_dist_native {
  my ($self, $basic_type_name) = @_;
  
  my $builder = $self->{builder};
  
  $builder->build_dynamic_lib_dist_native($basic_type_name);
}

1;

=head1 Name

SPVM::Builder::API - Defining Public Functions of SPVM::Builder

=head1 Description

The SPVM::Builder::API class defines the public methods of the L<SPVM::Builder> class.

=head1 Usage
  
  my $builder = SPVM::Builder::API->new(
    build_dir => '.spvm_build',
  );
  
  $builder->build_dynamic_lib_dist_precompile('MyClass');
  $builder->build_dynamic_lib_dist_native('MyClass');

=head1 Class Methods

=head2 new

  my $builder = SPVM::Builder::API->new(%options);

Creates a new L<SPVM::Builder::API> object.

Options:

=over 2

=item * C<build_dir>

The building directory.

=back

=head1 Instance Methods

=head2 build_dynamic_lib_dist_precompile

  $builder->build_dynamic_lib_dist_precompile($basic_type_name)

Generates a dynamic library for a class $basic_type_name that has C<precompile> methods, and copies it to the C<blib/lib> directory.

=head2 build_dynamic_lib_dist_native

  $builder->build_dynamic_lib_dist_native($basic_type_name)

Generates a dynamic library for a class $basic_type_name that has C<native> methods, and copies it to the C<blib/lib> directory.
