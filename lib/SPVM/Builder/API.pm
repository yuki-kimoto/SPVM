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
  my ($self, $class_name) = @_;
  
  my $builder = $self->{builder};
  
  $builder->build_dynamic_lib_dist($class_name, 'precompile');
}

sub build_dynamic_lib_dist_native {
  my ($self, $class_name) = @_;
  
  my $builder = $self->{builder};

  $builder->build_dynamic_lib_dist($class_name, 'native');
}

1;

=head1 Name

SPVM::Builder::API - SPVM Builder Public APIs

=head1 Usage
  
  # Builder API
  my $api = SPVM::Builder::API->new(
    build_dir => '.spvm_build',
  );
  
  $api->build_dynamic_lib_dist_precompile('MyClass');
  $api->build_dynamic_lib_dist_native('MyClass');
  
=head1 Description

B<SPVM::Builder::API> is the public APIs of SPVM Builder. 

L<SPVM::Builder> is a private modules of L<SPVM>.

The names and arguments of the methods are changed without warnings in the future release.

However, the methods is useful to get the information of SPVM modules.

B<SPVM::Builder::API> provides the public APIs to call the methods. These APIs is public and stable.

=head1 Methods

=head2 new

  # Builder API
  my $api = SPVM::Builder::API->new;

Create B<SPVM::Builder::API> object.

B<Options:>

=over 2

=item * build_dir

Build directory.

=back

=head2 build_dynamic_lib_dist_precompile

  $api->build_dynamic_lib_dist_precompile($class_name)

Build a precompile dymamic library and copy it to C<blib/lib>.

=head2 build_dynamic_lib_dist_native

  $api->build_dynamic_lib_dist_native($class_name)

Build a native dynamic library and copy it into C<blib/lib>.

