package SPVM::Sort;

1;

=encoding utf8

=head1 NAME

SPVM::Sort - Sorting Functions

=head1 SYNOPSYS

  # Sort byte array itself by asc order
  my $nums = [(byte)2, 3, 1];
  Sort->sort_byte($nums, 0, scalar @$nums, method : int ($a : byte, $b : byte) {
    return $a <=> $b;
  });

  # Sort short array itself by asc order
  my $nums = [(short)2, 3, 1];
  Sort->sort_short($nums, 0, scalar @$nums, method : int ($a : short, $b : short) {
    return $a <=> $b;
  });

  # Sort int array itself by asc order
  my $nums = [2, 3, 1];
  Sort->sort_int($nums, 0, scalar @$nums, method : int ($a : int, $b : int) {
    return $a <=> $b;
  });

  # Sort long array itself by asc order
  my $nums = [(long)2, 3, 1];
  Sort->sort_long($nums, 0, scalar @$nums, method : int ($a : long, $b : long) {
    return $a <=> $b;
  });

  # Sort float array itself by asc order
  my $nums = [(float)2, 3, 1];
  Sort->sort_float($nums, 0, scalar @$nums, method : int ($a : float, $b : float) {
    return $a <=> $b;
  });

  # Sort double array itself by asc order
  my $nums = [(double)2, 3, 1];
  Sort->sort_double($nums, 0, scalar @$nums, method : int ($a : double, $b : double) {
    return $a <=> $b;
  });

  # Sort string array itself by asc order
  my $nums = ["11", "1", "2", undef, ""];
  Sort->sort_double($nums, 0, scalar @$nums, method : int ($a : double, $b : double) {
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
  Sort->sort_object($minimals, 0, scalar @$minimals, method : int ($object1 : object, $object2 : object) {
    my $minimal1 = (TestCase::Minimal)$object1;
    my $minimal2 = (TestCase::Minimal)$object2;
    
    return $minimal1->{x} <=> $minimal2->{x} || $minimal1->{y} <=> $minimal2->{y};
  };

=head1 DESCRIPTION

C<Sort> provides sorting functions.

=head1 Class Methods

=head2 sort_byte

    static method sort_byte : void ($values : byte[], $offset : int, $length : int, $comparator : Comparator::Byte)

Sort byte array itself with a offset, a length, and a L<Comparator::Byte|SPVM::Comparator::Byte> comparator.

Array must be not undef. Otherwise an exception occurs.

Offset must be more than or equals to 0. Otherwise an exception occurs.

Length must be more than or equals to 0. Otherwise an exception occurs.

Offset + Length must be in the array range. Otherwise an exception occurs.

=head2 sort_double

    static method sort_double : void ($values : double[], $offset : int, $length : int, $comparator : Comparator::Double)

Sort double array itself with a offset, a length, and a L<Comparator::Double|SPVM::Comparator::Double> comparator.

Array must be not undef. Otherwise an exception occurs.

Offset must be more than or equals to 0. Otherwise an exception occurs.

Length must be more than or equals to 0. Otherwise an exception occurs.

Offset + Length must be in the array range. Otherwise an exception occurs.

=head2 sort_float

    static method static method sort_float : void ($values : float[], $offset : int, $length : int, $comparator : Comparator::Float)

Sort float array itself with a offset, a length, and a L<Comparator::Float|SPVM::Comparator::Float> comparator.

Array must be not undef. Otherwise an exception occurs.

Offset must be more than or equals to 0. Otherwise an exception occurs.

Length must be more than or equals to 0. Otherwise an exception occurs.

Offset + Length must be in the array range. Otherwise an exception occurs.

=head2 sort_int

    static method sort_int : void ($values : int[], $offset : int, $length : int, $comparator : Comparator::Int)

Sort int array itself with a offset, a length, and a L<Comparator::Int|SPVM::Comparator::Int> comparator.

Array must be not undef. Otherwise an exception occurs.

Offset must be more than or equals to 0. Otherwise an exception occurs.

Length must be more than or equals to 0. Otherwise an exception occurs.

Offset + Length must be in the array range. Otherwise an exception occurs.

=head2 sort_long

    static method sort_long : void ($values : long[], $offset : int, $length : int, $comparator : Comparator::Long)

Sort long array itself with a offset, a length, and a L<Comparator::Long|SPVM::Comparator::Long> comparator.

Array must be not undef. Otherwise an exception occurs.

Offset must be more than or equals to 0. Otherwise an exception occurs.

Length must be more than or equals to 0. Otherwise an exception occurs.

Offset + Length must be in the array range. Otherwise an exception occurs.

=head2 sort_object

    static method sort_object : void ($objs : object[], $offset : int, $length : int, $comparator : Comparator)

Sort object array itself with a offset, a length, and a L<Comparator|SPVM::Comparator> comparator.

Array must be not undef. Otherwise an exception occurs.

Offset must be more than or equals to 0. Otherwise an exception occurs.

Length must be more than or equals to 0. Otherwise an exception occurs.

Offset + Length must be in the array range. Otherwise an exception occurs.

=head2 sort_short

    static method sort_short : void ($values : short[], $offset : int, $length : int, $comparator : Comparator::Short)

Sort short array itself with a offset, a length, and a L<Comparator::Short|SPVM::Comparator::Short> comparator.

Array must be not undef. Otherwise an exception occurs.

Offset must be more than or equals to 0. Otherwise an exception occurs.

Length must be more than or equals to 0. Otherwise an exception occurs.

Offset + Length must be in the array range. Otherwise an exception occurs.

=head2 sort_string

    static method sort_string : void ($values : string[], $offset : int, $length : int, $comparator : Comparator::Double)

Sort string array itself with a offset, a length, and a L<Comparator::String|SPVM::Comparator::String> comparator.

Array must be not undef. Otherwise an exception occurs.

Offset must be more than or equals to 0. Otherwise an exception occurs.

Length must be more than or equals to 0. Otherwise an exception occurs.

Offset + Length must be in the array range. Otherwise an exception occurs.

