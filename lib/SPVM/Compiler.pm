package SPVM::Compiler;

use Object::Simple -base;

use Carp 'croak';

has 'object';

# XS subroutine
# get_sub_table

sub new {
  my $self = shift->SUPER::new(@_);
  
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
    $sub .= "  SPVM::call_sub($constant_pool_index, \@_);\n";
    $sub .= "}";
    
    # Define SPVM subroutine
    eval $sub;
    
    if ($@) {
      croak "Can't define SVPM subroutine \"$abs_name\"\n$sub";
    }
  }
}

1;
