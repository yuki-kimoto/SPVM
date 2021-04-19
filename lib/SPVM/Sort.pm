package SPVM::Sort;

1;

=head1 NAME

SPVM::Sort - Sort functions

=head1 SYNOPSYS
  
  use SPVM::Sort;
  
  # Sort byte array itself by asc order
  my $nums = [(byte)2, 3, 1];
  SPVM::Sort::sortb($nums, 0, scalar @$nums, sub : int ($self : self, $a : byte, $b : byte) {
    return $a <=> $b;
  });

  # Sort short array itself by asc order
  my $nums = [(short)2, 3, 1];
  SPVM::Sort::sorts($nums, 0, scalar @$nums, sub : int ($self : self, $a : short, $b : short) {
    return $a <=> $b;
  });

  # Sort int array itself by asc order
  my $nums = [2, 3, 1];
  SPVM::Sort::sorti($nums, 0, scalar @$nums, sub : int ($self : self, $a : int, $b : int) {
    return $a <=> $b;
  });

  # Sort long array itself by asc order
  my $nums = [(long)2, 3, 1];
  SPVM::Sort::sortl($nums, 0, scalar @$nums, sub : int ($self : self, $a : long, $b : long) {
    return $a <=> $b;
  });

  # Sort float array itself by asc order
  my $nums = [(float)2, 3, 1];
  SPVM::Sort::sortf($nums, 0, scalar @$nums, sub : int ($self : self, $a : float, $b : float) {
    return $a <=> $b;
  });

  # Sort double array itself by asc order
  my $nums = [(double)2, 3, 1];
  SPVM::Sort::sortd($nums, 0, scalar @$nums, sub : int ($self : self, $a : double, $b : double) {
    return $a <=> $b;
  });

  # Sort object array itself by asc order
  my $minimals = new TestCase::Minimal[3];
  $minimals->[0] = TestCase::Minimal->new;
  $minimals->[0]{x} = 3;
  $minimals->[0]{y} = 5;
  $minimals->[1] = TestCase::Minimal->new;
  $minimals->[1]{x} = 3;
  $minimals->[1]{y} = 7;
  $minimals->[2] = TestCase::Minimal->new;
  $minimals->[2]{x} = 2;
  $minimals->[2]{y} = 9;
  SPVM::Sort::sort_obj($minimals, 0, scalar @$minimals, sub : int ($self : self, $object1 : object, $object2 : object) {
    my $minimal1 = (TestCase::Minimal)$object1;
    my $minimal2 = (TestCase::Minimal)$object2;
    
    return $minimal1->{x} <=> $minimal2->{x} || $minimal1->{y} <=> $minimal2->{y};
  };

=head1 DESCRIPTION

L<SPVM::Sort> defines sort functions

=head1 STATIC METHODS

=head2 sortb

    sub sortb : void ($nums : byte[], $offset : int, $length : int, $comparator : SPVM::Comparator::Byte)

Sort byte array itself with a offset, a length, and a L<SPVM::Comparator::Byte> comparator.

Array must be not undef. Otherwise a exception occurs.

Offset must be more than or equals to 0. Otherwise a exception occurs.

Length must be more than or equals to 0. Otherwise a exception occurs.

Offset + Length must be in the array range. Otherwise a exception occurs.

=head2 sorts

    sub sorts : void ($nums : short[], $offset : int, $length : int, $comparator : SPVM::Comparator::Short)

Sort short array itself with a offset, a length, and a L<SPVM::Comparator::Short> comparator.

Array must be not undef. Otherwise a exception occurs.

Offset must be more than or equals to 0. Otherwise a exception occurs.

Length must be more than or equals to 0. Otherwise a exception occurs.

Offset + Length must be in the array range. Otherwise a exception occurs.

=head2 sorti

    sub sorti : void ($nums : int[], $offset : int, $length : int, $comparator : SPVM::Comparator::Int)

Sort int array itself with a offset, a length, and a L<SPVM::Comparator::Int> comparator.

Array must be not undef. Otherwise a exception occurs.

Offset must be more than or equals to 0. Otherwise a exception occurs.

Length must be more than or equals to 0. Otherwise a exception occurs.

Offset + Length must be in the array range. Otherwise a exception occurs.

=head2 sortl

    sub sortl : void ($nums : long[], $offset : int, $length : int, $comparator : SPVM::Comparator::Long)

Sort long array itself with a offset, a length, and a L<SPVM::Comparator::Long> comparator.

Array must be not undef. Otherwise a exception occurs.

Offset must be more than or equals to 0. Otherwise a exception occurs.

Length must be more than or equals to 0. Otherwise a exception occurs.

Offset + Length must be in the array range. Otherwise a exception occurs.

=head2 sortf

    sub sub sortf : void ($nums : float[], $offset : int, $length : int, $comparator : SPVM::Comparator::Float)

Sort float array itself with a offset, a length, and a L<SPVM::Comparator::Float> comparator.

Array must be not undef. Otherwise a exception occurs.

Offset must be more than or equals to 0. Otherwise a exception occurs.

Length must be more than or equals to 0. Otherwise a exception occurs.

Offset + Length must be in the array range. Otherwise a exception occurs.

=head2 sortd

    sub sortd : void ($nums : double[], $offset : int, $length : int, $comparator : SPVM::Comparator::Double)

Sort double array itself with a offset, a length, and a L<SPVM::Comparator::Double> comparator.

Array must be not undef. Otherwise a exception occurs.

Offset must be more than or equals to 0. Otherwise a exception occurs.

Length must be more than or equals to 0. Otherwise a exception occurs.

Offset + Length must be in the array range. Otherwise a exception occurs.

=head2 sorto

    sub sorto : void ($objs : oarray, $offset : int, $length : int, $comparator : SPVM::Comparator::Object)

Sort object array itself with a offset, a length, and a L<SPVM::Comparator::Object> comparator.

Array must be not undef. Otherwise a exception occurs.

Offset must be more than or equals to 0. Otherwise a exception occurs.

Length must be more than or equals to 0. Otherwise a exception occurs.

Offset + Length must be in the array range. Otherwise a exception occurs.
