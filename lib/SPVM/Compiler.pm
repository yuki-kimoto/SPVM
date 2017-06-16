package SPVM::Compiler;

use Object::Simple -base;

use Carp 'croak';

has 'package_infos';
has 'include_paths';
has 'compiler';

sub new {
  my $self = shift->SUPER::new(@_);
  
  $self->package_infos([]);
  $self->include_paths([]);
  
  return $self;
}

sub create_spvm_subs {
  my $self = shift;
  
  my $sub_infos = $self->get_sub_infos;

  use Data::Dumper;
  warn Dumper $sub_infos;
  
  for my $sub_info (@$sub_infos) {
    my $abs_name = $sub_info->{abs_name};
    my $arg_resolved_type_ids = $sub_info->{arg_resolved_type_ids};
    my $return_resolved_type_id = $sub_info->{return_resolved_type_id};
    my $constant_pool_index = $sub_info->{constant_pool_index};
    
    warn Dumper [$abs_name, $arg_resolved_type_ids, $return_resolved_type_id, $constant_pool_index];
    
    my $sub_define = "sub SPVM::$abs_name { 5 }";
    
    # Define SPVM subroutine
    eval $sub_define;
    
    if ($@) {
      croak "Can't define SVPM subroutine \"$abs_name\"";
    }
  }
}

1;
