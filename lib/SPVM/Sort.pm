package SPVM::Sort;

1;

=encoding utf8

=head1 Name

SPVM::Sort - Sorting Functions

=head1 Synopsys

  # Sort a byte array in-place by asc order
  my $nums = [(byte)2, 3, 1];
  Sort->sort_byte($nums, 0, scalar @$nums, method : int ($a : byte, $b : byte) {
    return $a <=> $b;
  });

  # Sort short array in-place by asc order
  my $nums = [(short)2, 3, 1];
  Sort->sort_short($nums, 0, scalar @$nums, method : int ($a : short, $b : short) {
    return $a <=> $b;
  });

  # Sort int array in-place by asc order
  my $nums = [2, 3, 1];
  Sort->sort_int($nums, 0, scalar @$nums, method : int ($a : int, $b : int) {
    return $a <=> $b;
  });

  # Sort long array in-place by asc order
  my $nums = [(long)2, 3, 1];
  Sort->sort_long($nums, 0, scalar @$nums, method : int ($a : long, $b : long) {
    return $a <=> $b;
  });

  # Sort float array in-place by asc order
  my $nums = [(float)2, 3, 1];
  Sort->sort_float($nums, 0, scalar @$nums, method : int ($a : float, $b : float) {
    return $a <=> $b;
  });

  # Sort double array in-place by asc order
  my $nums = [(double)2, 3, 1];
  Sort->sort_double($nums, 0, scalar @$nums, method : int ($a : double, $b : double) {
    return $a <=> $b;
  });

  # Sort string array in-place by asc order
  my $nums = ["11", "1", "2", undef, ""];
  Sort->sort_string($nums, 0, scalar @$nums, method : int ($a : string, $b : string) {
    return $a cmp $b;
  });

  # Sort object array in-place by asc order
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

=head1 Description

C<Sort> provides sorting functions. The sorting algorithm is a stable merge sort.

=head1 Class Methods

=head2 sort_byte

    static method sort_byte : void ($values : byte[], $offset : int, $length : int, $comparator : Comparator::Byte)

Sort the elements of C<byte> array in-place with the offset, the length, and the L<Comparator::Byte|SPVM::Comparator::Byte> comparator.

The values must be defined. Otherwise an exception will be thrown.

The offset must be more than or equal to C<0>. Otherwise an exception will be thrown.

The length must be more than or equal to C<0>. Otherwise an exception will be thrown.

The offset + length must be less than or equal to the length of the values. Otherwise an exception will be thrown.

=head2 sort_byte_asc
    
  static method sort_byte_asc : void ($values : byte[], $offset : int, $length : int)

Alias for the following code.

  Sort->sort_byte($values, $offset, $length, method : int ($a : byte, $b : byte) { return $a <=> $b; });

=head2 sort_byte_desc

  static method sort_byte_desc : void ($values : byte[], $offset : int, $length : int)

Alias for the following code.

  Sort->sort_byte($values, $offset, $length, method : int ($a : byte, $b : byte) { return $b <=> $a; });

=head2 sort_double

    static method sort_double : void ($values : double[], $offset : int, $length : int, $comparator : Comparator::Double)

Sort the elements of C<double> array in-place with the offset, the length, and the L<Comparator::Double|SPVM::Comparator::Double> comparator.

The values must be defined. Otherwise an exception will be thrown.

The offset must be more than or equal to C<0>. Otherwise an exception will be thrown.

The length must be more than or equal to C<0>. Otherwise an exception will be thrown.

The offset + length must be less than or equal to the length of the values. Otherwise an exception will be thrown.

=head2 sort_double_asc
    
  static method sort_double_asc : void ($values : double[], $offset : int, $length : int)

Alias for the following code.

  Sort->sort_double($values, $offset, $length, method : int ($a : double, $b : double) { return $a <=> $b; });

=head2 sort_double_desc

  static method sort_double_desc : void ($values : double[], $offset : int, $length : int)

Alias for the following code.

  Sort->sort_double($values, $offset, $length, method : int ($a : double, $b : double) { return $b <=> $a; });

=head2 sort_float

    static method static method sort_float : void ($values : float[], $offset : int, $length : int, $comparator : Comparator::Float)

Sort the elements of float array in-place with the offset, the length, and the L<Comparator::Float|SPVM::Comparator::Float> comparator.

The values must be defined. Otherwise an exception will be thrown.

The offset must be more than or equal to C<0>. Otherwise an exception will be thrown.

The length must be more than or equal to C<0>. Otherwise an exception will be thrown.

The offset + length must be less than or equal to the length of the values. Otherwise an exception will be thrown.

=head2 sort_float_asc
    
  static method sort_float_asc : void ($values : float[], $offset : int, $length : int)

Alias for the following code.

  Sort->sort_float($values, $offset, $length, method : int ($a : float, $b : float) { return $a <=> $b; });

=head2 sort_float_desc

  static method sort_float_desc : void ($values : float[], $offset : int, $length : int)

Alias for the following code.

  Sort->sort_float($values, $offset, $length, method : int ($a : float, $b : float) { return $b <=> $a; });

=head2 sort_int

    static method sort_int : void ($values : int[], $offset : int, $length : int, $comparator : Comparator::Int)

Sort the elements of C<int> array in-place with the offset, the length, and the L<Comparator::Int|SPVM::Comparator::Int> comparator.

The values must be defined. Otherwise an exception will be thrown.

The offset must be more than or equal to C<0>. Otherwise an exception will be thrown.

The length must be more than or equal to C<0>. Otherwise an exception will be thrown.

The offset + length must be less than or equal to the length of the values. Otherwise an exception will be thrown.

=head2 sort_int_asc
    
  static method sort_int_asc : void ($values : int[], $offset : int, $length : int)

Alias for the following code.

  Sort->sort_int($values, $offset, $length, method : int ($a : int, $b : int) { return $a <=> $b; });

=head2 sort_int_desc

  static method sort_int_desc : void ($values : int[], $offset : int, $length : int)

Alias for the following code.

  Sort->sort_int($values, $offset, $length, method : int ($a : int, $b : int) { return $b <=> $a; });

=head2 sort_long

    static method sort_long : void ($values : long[], $offset : int, $length : int, $comparator : Comparator::Long)

Sort the elements of long array in-place with the offset, the length, and the L<Comparator::Long|SPVM::Comparator::Long> comparator.

The values must be defined. Otherwise an exception will be thrown.

The offset must be more than or equal to C<0>. Otherwise an exception will be thrown.

The length must be more than or equal to C<0>. Otherwise an exception will be thrown.

The offset + length must be less than or equal to the length of the values. Otherwise an exception will be thrown.

=head2 sort_long_asc
    
  static method sort_long_asc : void ($values : long[], $offset : int, $length : int)

Alias for the following code.

  Sort->sort_long($values, $offset, $length, method : int ($a : long, $b : long) { return $a <=> $b; });

=head2 sort_long_desc

  static method sort_long_desc : void ($values : long[], $offset : int, $length : int)

Alias for the following code.

  Sort->sort_long($values, $offset, $length, method : int ($a : long, $b : long) { return $b <=> $a; });

=head2 sort_object

    static method sort_object : void ($objs : object[], $offset : int, $length : int, $comparator : Comparator)

Sort the elements of object array in-place with the offset, the length, and the L<Comparator|SPVM::Comparator> comparator.

The values must be defined. Otherwise an exception will be thrown.

The offset must be more than or equal to C<0>. Otherwise an exception will be thrown.

The length must be more than or equal to C<0>. Otherwise an exception will be thrown.

The offset + length must be less than or equal to the length of the values. Otherwise an exception will be thrown.

=head2 sort_short

    static method sort_short : void ($values : short[], $offset : int, $length : int, $comparator : Comparator::Short)

Sort the elements of short array in-place with the offset, the length, and the L<Comparator::Short|SPVM::Comparator::Short> comparator.

The values must be defined. Otherwise an exception will be thrown.

The offset must be more than or equal to C<0>. Otherwise an exception will be thrown.

The length must be more than or equal to C<0>. Otherwise an exception will be thrown.

The offset + length must be less than or equal to the length of the values. Otherwise an exception will be thrown.

=head2 sort_short_asc
    
  static method sort_short_asc : void ($values : short[], $offset : int, $length : int)

Alias for the following code.

  Sort->sort_short($values, $offset, $length, method : int ($a : short, $b : short) { return $a <=> $b; });

=head2 sort_short_desc

  static method sort_short_desc : void ($values : short[], $offset : int, $length : int)

Alias for the following code.

  Sort->sort_short($values, $offset, $length, method : int ($a : short, $b : short) { return $b <=> $a; });

=head2 sort_string

    static method sort_string : void ($values : string[], $offset : int, $length : int, $comparator : Comparator::Double)

Sort the elements of C<string> array in-place with the offset, the length, and the L<Comparator::String|SPVM::Comparator::String> comparator.

The values must be defined. Otherwise an exception will be thrown.

The offset must be more than or equal to C<0>. Otherwise an exception will be thrown.

The length must be more than or equal to C<0>. Otherwise an exception will be thrown.

The offset + length must be less than or equal to the length of the values. Otherwise an exception will be thrown.

=head2 sort_string_asc
    
  static method sort_string_asc : void ($values : string[], $offset : int, $length : int)

Alias for the following code.

  Sort->sort_string($values, $offset, $length, method : int ($a : string, $b : string) { return $a cmp $b; });

=head2 sort_string_desc

  static method sort_string_desc : void ($values : string[], $offset : int, $length : int)

Alias for the following code.

  Sort->sort_string($values, $offset, $length, method : int ($a : string, $b : string) { return $b cmp $a; });

