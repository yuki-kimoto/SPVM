package SPVM::Compiler;

use Object::Simple -base;

use Carp 'croak';

has 'package_infos';
has 'include_paths';
has 'compiler';

# XS subroutine
# get_sub_table

sub new {
  my $self = shift->SUPER::new(@_);
  
  $self->package_infos([]);
  $self->include_paths([]);
  
  return $self;
}

sub build_spvm_subs {
  my $self = shift;
  
  my $sub_table = $SPVM::SUB_TABLE;

  for my $constant_pool_index (keys %$sub_table) {
    my $sub_info = $sub_table->{$constant_pool_index};
    
    my ($abs_name, $arg_resolved_type_ids, $return_resolved_type_id) = @$sub_info;
    
    my $sub;
    $sub .= "sub SPVM::$abs_name {\n";
    $sub .= "  SPVM::Runtime::call_sub(\$SPVM::RUNTIME, \$SPVM::SUB_TABLE, $constant_pool_index, \@_);\n";
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
