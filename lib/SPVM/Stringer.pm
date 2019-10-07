package SPVM::Stringer;

use SPVM 'SPVM::Stringer';

1;

=head1 NAME

SPVM::Stringer - a callback class for stringification

=head1 SYNOPSYS
  
  use SPVM::Stringer;
  
  my $stringer : SPVM::Stringer = sub to_str : string ($self : self) {
    return "Hello";
  };
  
  my $message = $stringer->to_str;

=head1 DESCRIPTION

L<SPVM::Stringer> is a callback type to stringify a object.

=head1 INSTANCE METHODS

=head2 to_str

  sub to_str : string ($self : self);
