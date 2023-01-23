package SPVM::ExchangeAPI::Class;
use strict;
use warnings;

# Fields
sub __class_name {
  my $self = shift;
  if (@_) {
    $self->{__class_name} = $_[0];
    return $self;
  }
  else {
    return $self->{__class_name};
  }
}

sub __api {
  my $self = shift;
  if (@_) {
    $self->{__api} = $_[0];
    return $self;
  }
  else {
    return $self->{__api};
  }
}

# Class Methods
sub __new {
  my $class = shift;
  
  my $self = {@_};
  
  bless $self, ref $class || $class;
  
  return $self;
}

our $AUTOLOAD;
sub AUTOLOAD {
  my $self = shift;
  
  my $__class_name = $self->__class_name;
  
  my $method_name = $AUTOLOAD;
  $method_name =~ s/^SPVM::ExchangeAPI::Class:://;
  
  my $ret = $self->__api->call_method($__class_name, $method_name, @_);
  
  return $ret;
}
sub DESTROY {}

1;

=head1 Name

SPVM::ExchangeAPI::Class - Class Object

=head1 Description

C<SPVM::BlessedObject::Class> is a class object to call class methods.

=head1 Usage
  
  # The same as the Int->__new(1) in SPVM language
  my $class = SPVM::ExchangeAPI::Class->__new(__class_name => 'Int', __api => $api);
  my $value = $class->new(1);

Create a class object using the L<SPVM::ExchangeAPI|SPVM::ExchangeAPI/"class"> method in the L<SPVM::ExchangeAPI> class:

  my $class = $api->class('Int');
  $class->new(1);

=head1 Fields

=head2 __class_name

  my $__class_name = $self->__class_name;
  $self->__class_name($__class_name);

Gets and sets a class name.

=head2 __api

  my $api = $self->__api;
  $self->__api($api);

Gets and sets a L<SPVM::ExchangeAPI> object.

=head1 Class Methods

=head2 __new

  my $class = SPVM::ExchangeAPI::Class->__new(%options);

Creates a new C<SPVM::ExchangeAPI::Class> object.

Options:

=over 2

=item * C<__class_name> : string

A class name

=item * C<__api> : SPVM::ExchangeAPI

A L<SPVM::ExchangeAPI> object

=back

=head1 Instance Methods

=head2 AUTOLOAD

  $class->foo(@args);

Calls L<call_method|SPVM::ExchangeAPI/"call_method"> method in the L<SPVM::ExchangeAPI> class using the L</"__class_name"> field and the method name given in the C<AUTOLOAD> method.
