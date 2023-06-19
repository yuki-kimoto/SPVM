package SPVM::ExchangeAPI::Class;
use strict;
use warnings;

# Fields
sub __basic_type_name {
  my $self = shift;
  if (@_) {
    $self->{__basic_type_name} = $_[0];
    return $self;
  }
  else {
    return $self->{__basic_type_name};
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
  
  my $__basic_type_name = $self->__basic_type_name;
  
  my $method_name = $AUTOLOAD;
  $method_name =~ s/^SPVM::ExchangeAPI::Class:://;
  
  my $ret = $self->__api->call_method($__basic_type_name, $method_name, @_);
  
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
  my $class = SPVM::ExchangeAPI::Class->__new(__basic_type_name => 'Int', __api => $api);
  my $value = $class->new(1);

Create a class object using the L<SPVM::ExchangeAPI|SPVM::ExchangeAPI/"class"> method in the L<SPVM::ExchangeAPI> class:

  my $class = $api->class('Int');
  $class->new(1);

=head1 Fields

=head2 __basic_type_name

  my $__basic_type_name = $self->__basic_type_name;
  $self->__basic_type_name($__basic_type_name);

Gets and sets a basic type name.

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

=item * C<__basic_type_name> : string

A basic type name

=item * C<__api> : SPVM::ExchangeAPI

A L<SPVM::ExchangeAPI> object

=back

=head1 Instance Methods

=head2 AUTOLOAD

  $class->foo(@args);

Calls L<call_method|SPVM::ExchangeAPI/"call_method"> method in the L<SPVM::ExchangeAPI> class using the L</"__basic_type_name"> field and the method name given in the C<AUTOLOAD> method.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
