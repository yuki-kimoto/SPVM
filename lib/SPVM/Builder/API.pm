package SPVM::Builder::API;

use strict;
use warnings;

use SPVM::Builder;

sub new {
  my $class = shift;
  
  my $self = {};

  my $builder = SPVM::Builder->new;

  $self->{builder} = $builder;
  
  return bless $self, $class;
}

sub compile_spvm {
  my ($self, $class_name) = @_;
  
  my $builder = $self->{builder};
  
  my $succcess = $builder->compile_spvm($class_name, __FILE__, __LINE__);
  
  return $success;
}

sub get_error_messages {
  my ($self) = @_;
  
  my $builder = $self->{builder};
  
  my $error_messages = $builder->get_error_messages
  
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

1;

=head1 NAME

SPVM::Builder::API - SPVM Builder Public APIs

=head1 SYNOPSYS
  
  # Builder API
  my $api = SPVM::Builder::API->new;
  
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

=head2 compile_spvm

=head2 get_error_messages

=head2 get_class_names

=head2 get_method_names

=head2 get_method_signature

