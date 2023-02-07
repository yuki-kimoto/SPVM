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
  
  unless (ref $self) {
    my $class_name = $self;
    $class_name =~ s/^SPVM:://;
    $method_name =~ s/^.*:://;
    
    Carp::confess("The \"$method_name\" method in the \"$class_name\" class is not defined");
  }
  
  $method_name =~ s/^SPVM:://;
  $method_name =~ s/^BlessedObject::Class:://;
  
  my $ret = $self->api->call_method($self, $method_name, @_);
  
  return $ret;
}

1;

=head1 Name

SPVM::BlessedObject::Class - Class based blessed object

=head1 Description

SPVM::BlessedObject::Class is class based blessed object.

This object contains class based SPVM object.

You can call all methods declaraed in the class.

=head1 Usage

  # lib/SPVM/Point.spvm
  class Point {
    haz x : int;
    haz y : int;
    
    static method new : Point ($x : int, $y : int) {
      my $self = new Point;
      
      $self->{x} = $x;
      $self->{y} = $y;
      
      return $self;
    }
    
    method clear : void () {
      $self->{x} = 0;
      $self->{y} = 0;
    }
    
    method set_x : void ($value : int) {
      $self->{x} = $value;
    }
    
    method x () {
      return $self->{x};
    }
  }
  
  # main.pl
  use FindBin;
  use lib "$FindBin::lib";
  use SPVM 'Point';
  
  my $point = Point->new;
  $point->set_x(4);
  my $x = $point->x;
  $point->clear;
