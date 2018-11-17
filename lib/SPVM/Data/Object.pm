package SPVM::Data::Object;

use base 'SPVM::Data';

1;

=head1 NAME

SPVM::Data::Object - SPVM object

=head1 DESCRIPTION

SPVM::Data::Object is wrapper of SPVM object.

You can call all methods of SPVM object.

An example:

  # lib/Point.spvm
  package Point {
    haz x : int;
    haz y : int;
    
    sub new : Point ($x : int, $y : int) {
      my $self = new Point;
      
      $self->{x} = $x;
      $self->{y} = $y;
      
      return $self;
    }
    
    sub clear : void ($self : self) {
      $self->{x} = 0;
      $self->{y} = 0;
    }
    
    sub set_x : void ($self : self, $value : int) {
      $self->{x} = $value;
    }
    
    sub get_x ($self : self) {
      return $self->{x};
    }
  }
  
  # main.pl
  use FindBin;
  use lib "$FindBin::lib";
  use SPVM 'Point';
  
  my $point = Point->new;
  $point->set_x(4);
  my $x = $point->get_x;
  $point->clear;
