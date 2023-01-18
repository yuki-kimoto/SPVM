package SPVM::BlessedObject::Class;

use strict;
use warnings;

use base 'SPVM::BlessedObject';

use SPVM::ExchangeAPI;

our $AUTOLOAD;
sub AUTOLOAD {
  my $self = shift;
  
  my $method_name = $AUTOLOAD;
  $method_name =~ s/^SPVM::BlessedObject::Class:://;
  
  my $ret = SPVM::ExchangeAPI::call_method($self->env, $self->stack, $self, $method_name, @_);
  
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
