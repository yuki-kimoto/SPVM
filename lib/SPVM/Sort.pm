package SPVM::Sort;

use SPVM 'SPVM::Sort';

1;

=head1 NAME

SPVM::Sort - Sort functions

=head1 SYNOPSYS
  
  use SPVM::Sort;
  
  # Sort byte array itself by asc order
  my $nums = [(byte)2, 3, 1];
  SPVM::Sort::sortb($nums);

  # Sort short array itself by asc order
  my $nums = [(short)2, 3, 1];
  SPVM::Sort::sorts($nums);

  # Sort int array itself by asc order
  my $nums = [2, 3, 1];
  SPVM::Sort::sorti($nums);

  # Sort long array itself by asc order
  my $nums = [(long)2, 3, 1];
  SPVM::Sort::sortl($nums);

  # Sort float array itself by asc order
  my $nums = [(float)2, 3, 1];
  SPVM::Sort::sortf($nums);

  # Sort double array itself by asc order
  my $nums = [(double)2, 3, 1];
  SPVM::Sort::sortd($nums);

  # Sort string array itself by asc order
  my $nums = [(string)"abc", "def", "ghi"];
  SPVM::Sort::sortd($nums);
  
  # Sort object array itself by asc order
  my $comparator = sub : int ($self : self, $object1 : object, $object2 : object) {
    my $minimal1 = (TestCase::Minimal)$object1;
    my $minimal2 = (TestCase::Minimal)$object2;
    
    my $x1 = $minimal1->{x};
    my $x2 = $minimal2->{x};
    
    if ($x1 > $x2) {
      return 1;
    }
    elsif ($x1 < $x2) {
      return -1;
    }
    else {
      return 0;
    }
  };
  
  my $minimals = new TestCase::Minimal[3];
  $minimals->[0] = TestCase::Minimal->new;
  $minimals->[0]{x} = 3;
  $minimals->[1] = TestCase::Minimal->new;
  $minimals->[1]{x} = 1;
  $minimals->[2] = TestCase::Minimal->new;
  $minimals->[2]{x} = 2;
  
  SPVM::Sort::sort_obj($minimals, $comparator);

=head1 DESCRIPTION

L<SPVM::Sort> defines sort functions

=head1 CLASS METHODS

=head2 sortb

    sub sortb : void ($nums : byte[])

Sort byte array itself by asc order.

  my $nums = [(byte)2, 3, 1];
  SPVM::Sort::sortb($nums);

=head2 sorts

    sub sorts : void ($nums : short[])

  my $nums = [(short)2, 3, 1];
  SPVM::Sort::sorts($nums);

Sort short array itself by asc order.

=head2 sorti

    sub sorti : void ($nums : int[])

Sort int array itself by asc order.

  my $nums = [2, 3, 1];
  SPVM::Sort::sorti($nums);

=head2 sortl

    sub sortl : void ($nums : long[])

Sort long array itself by asc order.

  my $nums = [(long)2, 3, 1];
  SPVM::Sort::sortl($nums);

=head2 sortf

    sub sub sortf : void ($nums : float[])

Sort float array itself by asc order.

  my $nums = [(float)2, 3, 1];
  SPVM::Sort::sortf($nums);

=head2 sortd

    sub sortd : void ($nums : double[])

Sort double array itself by asc order.

  my $nums = [(double)2, 3, 1];
  SPVM::Sort::sortd($nums);

=head2 sortstr

    sub sortstr : void ($strs : string[])

Sort string array itself by asc order. All string element must be not undef. otherwise exception occur.

  my $nums = [(string)"abc", "def", "ghi"];
  SPVM::Sort::sortd($nums);

=head2 sorto

    sub sorto : void ($objs : oarray, $comparator : SPVM::Comparator)

Sort object array itself which element fits L<SPVM::Comparator> by asc order.

Object array must fit oarray type.

  my $minimals = new TestCase::Minimal[3];
  $minimals->[0] = TestCase::Minimal->new;
  $minimals->[0]{x} = 3;
  $minimals->[1] = TestCase::Minimal->new;
  $minimals->[1]{x} = 1;
  $minimals->[2] = TestCase::Minimal->new;
  $minimals->[2]{x} = 2;
  
  SPVM::Sort::sort_obj($minimals, sub : int ($self : self, $object1 : object, $object2 : object) {
    my $minimal1 = (TestCase::Minimal)$object1;
    my $minimal2 = (TestCase::Minimal)$object2;
    
    my $x1 = $minimal1->{x};
    my $x2 = $minimal2->{x};
    
    if ($x1 > $x2) {
      return 1;
    }
    elsif ($x1 < $x2) {
      return -1;
    }
    else {
      return 0;
    }
  });
