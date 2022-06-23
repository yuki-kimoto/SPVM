class Point3D extends Point {
  
  has z : rw int;
  
  static method new : Point () {
    return new Point3D;
  }
  
  static method new_xyz : Point ($x : int, $y : int, $z : int) {
    my $self = Point3D->new;
    
    $self->set_x($x);
    $self->set_y($y);
    $self->set_z($z);
    
    return $self;
  }
  
  method clear : void () {
    $self->{x} = 0;
    $self->{y} = 0;
  }
  
  method to_string : string () {
    my $x = $self->x;
    my $y = $self->y;
    my $z = $self->z;
    
    my $string = "($x,$y,$z)";
    
    return $string;
  }
  
  method cloneable_clone : object () {
    my $self_clone = Point->new_xyz($self->x, $self->y, $self->z);
    
    return $self_clone;
  }
}
