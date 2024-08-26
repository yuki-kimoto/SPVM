package SPVM::BlessedObject::Class;

use strict;
use warnings;
use Carp;

use base 'SPVM::BlessedObject';

use SPVM::ExchangeAPI;

our $AUTOLOAD;
sub AUTOLOAD {
  my $self = shift;
  
  my $method_name = $AUTOLOAD;
  
  # If the class method is not found, AUTOLOAD is called.
  unless (ref $self) {
    my $basic_type_name = $self;
    $basic_type_name =~ s/^SPVM:://;
    $method_name =~ s/^.*:://;
    
    Carp::confess("The \"$method_name\" method in the \"$basic_type_name\" class is not found");
  }
  
  # For a static instant method call
  $method_name =~ s/^SPVM:://;
  
  # For an instance method call
  $method_name =~ s/^BlessedObject::Class:://;
  
  my $ret = $self->__api->call_method($self, $method_name, @_);
  
  return $ret;
}

1;

=head1 Name

SPVM::BlessedObject::Class - SPVM Class

=head1 Description

The object of C<SPVM::BlessedObject::Class> class holds an instance of an SPVM class.

=head1 Usage

  use SPVM 'Point';
  
  my $point = SPVM::Point->new;
  $point->set_x(4);
  my $x = $point->x;
  $point->clear;

=head1 Instance Methods

=head2 AUTOLOAD
  
  # Instance method call
  my $ret = $blessed_object_class->foo(@args);
  
  # Static instance method call
  my $ret = $blessed_object_class->SPVM::MyClass::foo(@args);

Calls an SPVM instance method using L<SPVM::ExchangeAPI/"call_method"> with the arguments, and returns the return value.

The static instance method call is allowed.

If the class or the method is not found, an exception is thrown.

If the invocant cannnot be assigned to the class of the static method call, an exception is thrown.

Examples:

  use SPVM 'Point';
  
  # Creates an SPVM::BlessedObject::Class object of the Point class.
  my $point = Point->new;
  
  # Calls instance methods in the Point class.
  $point->set_x(4);
  my $x = $point->x;
  $point->clear;

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
