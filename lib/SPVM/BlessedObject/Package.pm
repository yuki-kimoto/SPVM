package SPVM::BlessedObject::Package;

use base 'SPVM::BlessedObject';

1;

=head1 NAME

SPVM::BlessedObject::Package - Package based blessed object

=head1 DESCRIPTION

SPVM::BlessedObject::Package is package based blessed object.

This object contains package based SPVM object.

You can call all methods declaraed in the package.

=head1 SYNOPSYS

  # lib/SPVM/Point.spvm
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
    
    sub x ($self : self) {
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
