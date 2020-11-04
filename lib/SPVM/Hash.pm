package SPVM::Hash;

1;

=head1 NAME

SPVM::Hash - Key-Values Stored Data Structrue

=head1 SYNOPSYS
  
  use SPVM::Hash;
  
  # Book Data
  my $book = SPVM::Hash->new;
  
  $book->set_int(id => 4);
  $book->set(name => "Perl");
  $book->set_int(price => 300);
  
  my $id = $book->get_int("id");
  my $name = $book->get("name");
  my $price = $book->get_int("price");
  
  # Option Data
  my $opt = SPVM::Hash->new;
  $opt->set_int(limit => 10);
  $opt->set(caption => "Perl is Good Plain Old Language");
  $opt->set_double(rate => 0.95);
  
=head1 DESCRIPTION

L<SPVM::Hash> is Key-Values Stored Data Structrue.

=head1 STATIC METHODS

=head2 new

    sub new : SPVM::Hash ()

Create a new L<SPVM::Hash> object.

=head1 INSTANCE METHODS
