package SPVM::Compiler;

use Object::Simple -base;

use Carp 'croak';

has 'package_infos';
has 'include_paths';
has 'compiler';

# XS subroutine
# get_sub_infos

sub new {
  my $self = shift->SUPER::new(@_);
  
  $self->package_infos([]);
  $self->include_paths([]);
  
  return $self;
}

sub build_spvm_subs {
  my $self = shift;
  
  my $sub_infos = $SPVM::sub_table;

  use Data::Dumper;
  warn Dumper $sub_infos;
  
  for my $constant_pool_index (keys %$sub_infos) {
    my $sub_info = $sub_infos->{$constant_pool_index};
    my $abs_name = $sub_info->{abs_name};
    my $arg_resolved_type_ids = $sub_info->{arg_resolved_type_ids};
    my $return_resolved_type_id = $sub_info->{return_resolved_type_id};

    my $sub;
    $sub .= "sub SPVM::$abs_name {\n";
    $sub .= "  SPVM::Runtime::call_sub(\$SPVM::runtime, $constant_pool_index, \@_);\n";
    $sub .= "  5;\n";
    $sub .= "}";
    
    # Define SPVM subroutine
    eval $sub;
    
    if ($@) {
      croak "Can't define SVPM subroutine \"$abs_name\"\n$sub";
    }
  }
}

1;
