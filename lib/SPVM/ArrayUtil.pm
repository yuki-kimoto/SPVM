package SPVM::ArrayUtil;

1;

=head1 NAME

SPVM::ArrayUtil - Array Utilities

=head1 SYNOPSYS
  
  use SPVM::ArrayUtil;

  # Copy a byte array
  {
    my $nums = [(byte)1, 2, 3];
    my $nums_copy = SPVM::ArrayUtil->copy_array_byte($nums);
  }

  # Copy a short array
  {
    my $nums = [(short)1, 2, 3];
    my $nums_copy = SPVM::ArrayUtil->copy_array_short($nums);
  }

  # Copy a int array
  {
    my $nums = [1, 2, 3];
    my $nums_copy = SPVM::ArrayUtil->copy_array_int($nums);
  }

  # Copy a long array
  {
    my $nums = [(long)1, 2, 3];
    my $nums_copy = SPVM::ArrayUtil->copy_array_long($nums);
  }

  # Copy a float array
  {
    my $nums = [1.5f, 2.5f, 3.5f];
    my $nums_copy = SPVM::ArrayUtil->copy_array_float($nums);
  }

  # Copy a double array
  {
    my $nums = [1.5, 2.5, 3.5];
    my $nums_copy = SPVM::ArrayUtil->copy_array_double($nums);
  }
  
  # Copy a string array
  {
    my $strs = ["abc", "def", "ghi"]
    my $strs_copy = SPVM::ArrayUtil->copy_array_string($strs);
  }
  
  # Check if the two byte arrays equal
  {
    my $nums1 = [(byte)1, 2];
    my $nums2 = [(byte)1, 2];
    my $ret = SPVM::ArrayUtil->equals_array_byte($nums1, $nums2);
  }

  # Check if the two short arrays equal
  {
    my $nums1 = [(short)1, 2];
    my $nums2 = [(short)1, 2];
    my $ret = SPVM::ArrayUtil->equals_array_short($nums1, $nums2);
  }

  # Check if the two int arrays equal
  {
    my $nums1 = [(int)1, 2];
    my $nums2 = [(int)1, 2];
    my $ret = SPVM::ArrayUtil->equals_array_int($nums1, $nums2);
  }

  # Check if the two long arrays equal
  {
    my $nums1 = [(long)1, 2];
    my $nums2 = [(long)1, 2];
    my $ret = SPVM::ArrayUtil->equals_array_long($nums1, $nums2);
  }

  # Check if the two float arrays equal
  {
    my $nums1 = [(float)1, 2];
    my $nums2 = [(float)1, 2];
    my $ret = SPVM::ArrayUtil->equals_array_float($nums1, $nums2);
  }

  # Check if the two double arrays equal
  {
    my $nums1 = [(double)1, 2];
    my $nums2 = [(double)1, 2];
    my $ret = SPVM::ArrayUtil->equals_array_double($nums1, $nums2);
  }

  # Check if the two string arrays equal
  {
    my $strs1 = ["abc", "def"];
    my $strs2 = ["abc", "def"];
    my $ret = SPVM::ArrayUtil->equals_array_string($strs1, $strs2);
  }
  
  # Copy object array
  my $objects = [(object)SPVM::Int->new(1), SPVM::Int->new(2), SPVM::Int->new(3)];
  my $objects_copy = SPVM::ArrayUtil->copy_array_object($objects, sub : object ($self : self, $obj : object) {
    my $int_obj = (SPVM::Int)$obj;
    my $new_int_obj = SPVM::Int->new($int_obj->value);
    return $new_int_obj;
  });

  # Sort byte array itself by asc order
  my $nums = [(byte)2, 3, 1];
  SPVM::Sort->sort_byte($nums, 0, scalar @$nums, sub : int ($self : self, $a : byte, $b : byte) {
    return $a <=> $b;
  });

  # Sort short array itself by asc order
  my $nums = [(short)2, 3, 1];
  SPVM::Sort->sort_short($nums, 0, scalar @$nums, sub : int ($self : self, $a : short, $b : short) {
    return $a <=> $b;
  });

  # Sort int array itself by asc order
  my $nums = [2, 3, 1];
  SPVM::Sort->sort_int($nums, 0, scalar @$nums, sub : int ($self : self, $a : int, $b : int) {
    return $a <=> $b;
  });

  # Sort long array itself by asc order
  my $nums = [(long)2, 3, 1];
  SPVM::Sort->sort_long($nums, 0, scalar @$nums, sub : int ($self : self, $a : long, $b : long) {
    return $a <=> $b;
  });

  # Sort float array itself by asc order
  my $nums = [(float)2, 3, 1];
  SPVM::Sort->sort_float($nums, 0, scalar @$nums, sub : int ($self : self, $a : float, $b : float) {
    return $a <=> $b;
  });

  # Sort double array itself by asc order
  my $nums = [(double)2, 3, 1];
  SPVM::Sort->sort_double($nums, 0, scalar @$nums, sub : int ($self : self, $a : double, $b : double) {
    return $a <=> $b;
  });

  # Sort string array itself by asc order
  my $nums = ["11", "1", "2", undef, ""];
  SPVM::Sort->sort_double($nums, 0, scalar @$nums, sub : int ($self : self, $a : double, $b : double) {
    return $a <=> $b;
  });

  # Sort object array itself by asc order
  my $minimals = new SPVM::TestCase::Minimal[3];
  $minimals->[0] = SPVM::TestCase::Minimal->new;
  $minimals->[0]{x} = 3;
  $minimals->[0]{y} = 5;
  $minimals->[1] = SPVM::TestCase::Minimal->new;
  $minimals->[1]{x} = 3;
  $minimals->[1]{y} = 7;
  $minimals->[2] = SPVM::TestCase::Minimal->new;
  $minimals->[2]{x} = 2;
  $minimals->[2]{y} = 9;
  SPVM::Sort->sort_object$minimals, 0, scalar @$minimals, sub : int ($self : self, $object1 : object, $object2 : object) {
    my $minimal1 = (SPVM::TestCase::Minimal)$object1;
    my $minimal2 = (SPVM::TestCase::Minimal)$object2;
    
    return $minimal1->{x} <=> $minimal2->{x} || $minimal1->{y} <=> $minimal2->{y};
  };

=head1 DESCRIPTION

Array Utilities.

=head1 STATIC METHODS

=head2 copy_array_byte

  sub copy_array_byte : byte[] ($nums : byte[])

Copy a byte array.

If the array is undef, return undef.

=head2 copy_array_short

  sub copy_array_short : short[] ($nums : short[])

Copy a short array.

If the array is undef, return undef.
  
=head2 copy_array_int

  sub copy_array_int : int[] ($nums : int[])

Copy a int array.

If the array is undef, return undef.
  
=head2 copy_array_long

  sub copy_array_long : long[] ($nums : long[])

Copy a long array.

If the array is undef, return undef.

=head2 copy_array_float

  sub copy_array_float : float[] ($nums : float[])

Copy a float array.

If the array is undef, return undef.

=head2 copy_array_double

  sub copy_array_double : double[] ($nums : double[])

Copy a double array.

If the array is undef, return undef.

=head2 copy_array_string

  sub copy_array_string : string[] ($strings : string[])

Copy a string array.

If the array is undef, return undef.

=head2 copy_array_object

  sub copy_array_object : object[] ($objects : object[], $cloner : SPVM::Cloner)

Copy a object array with a L<SPVM::Cloner> callback implemetation.

If the array is undef, return undef.

=head2 equals_array_byte

  sub equals_array_byte : int ($nums1 : byte[], $nums2 : byte[])

Check if two byte arrays equal.

If at least one of the arrays is undef, a excetpion occurs.

=head2 equals_array_short

  sub equals_array_short : int ($nums1 : short[], $nums2 : short[])

Check if two short arrays equal.

If at least one of the arrays is undef, a excetpion occurs.

=head2 equals_array_int

  sub equals_array_int : int ($nums1 : int[], $nums2 : int[])

Check if two int arrays equal.

If at least one of the arrays is undef, a excetpion occurs.

=head2 equals_array_long

  sub equals_array_long : int ($nums1 : long[], $nums2 : long[])

Check if two long arrays equal.

If at least one of the arrays is undef, a excetpion occurs.

=head2 equals_array_float

  sub equals_array_float : int ($nums1 : float[], $nums2 : float[])

Check if two float arrays equal.

If at least one of the arrays is undef, a excetpion occurs.

=head2 equals_array_double

  sub equals_array_double : int ($nums1 : double[], $nums2 : double[])

Check if two double arrays equal.

If at least one of the arrays is undef, a excetpion occurs.

=head2 equals_array_string

  sub equals_array_string : int ($strs1 : double[], $strs2 : double[])

Check if two string arrays equal.

If at least one of the arrays is undef, a excetpion occurs.

=head2 equals_array_object

  sub sub equals_array_object : int ($objs1 : oarray, $objs2 : oarray, $equality_checker : SPVM::EqualityChecker)

Check equality of two objects. You must sepecify a L<SPVM::EqualityChecker> object to check the equality of each element.

$objs1 and $objs2 and $equality_checker must be defined, otherwise a exception occur.

Return 1 if the length of $objs1 and $objs2 is same and all element is same, otherwise return 0.

=head2 dump_array_byte

  sub dump_array_byte : string ($nums : byte[])
  
Convert the elements in the byte array to string and join them with "," and surround it with "[" and "]", and return it.

For readability spaces and line breaks are inserted.

If byte array is undef, return undef.

=head2 dump_array_short

  sub dump_array_short : string ($nums : short[])
  
Convert the elements in the short array to string and join them with "," and surround it with "[" and "]".

For readability spaces and line breaks are inserted.

If byte array is undef, return undef.

=head2 dump_array_int

  sub dump_array_int : string ($nums : int[])
  
Convert the elements in the int array to string and join them with "," and surround it with "[" and "]", and return it.

If byte array is undef, return undef.

=head2 dump_array_long

  sub dump_array_long : string ($nums : long[])
  
Convert the elements in the long array to string and join them with "," and surround it with "[" and "]", and return it.

If byte array is undef, return undef.

=head2 dump_array_unsigned_byte

  sub dump_array_unsigned_byte : string ($nums : byte[])
  
Convert the elements in the byte array to string interpreting as an unsigned 8bit integer and join them with "," and surround it with "[" and "]", and return it.

If byte array is undef, return undef.

=head2 dump_array_unsigned_short

  sub dump_array_unsigned_short : string ($nums : short[])
  
Convert the elements in the short array to string interpreting as an unsigned 16bit integer and join them with "," and surround it with "[" and "]".

For readability spaces and line breaks are inserted.

If byte array is undef, return undef.

=head2 dump_array_unsigned_int

  sub dump_array_unsigned_int : string ($nums : int[])
  
Convert the elements in the int array to string interpreting as an unsigned 32bit integer and join them with "," and surround it with "[" and "]", and return it.

If byte array is undef, return undef.

=head2 dump_array_unsigned_long

  sub dump_array_unsigned_long : string ($nums : long[])
  
Convert the elements in the long array to string interpreting as an unsigned 64bit integer and join them with "," and surround it with "[" and "]", and return it.

For readability spaces and line breaks are inserted.

If byte array is undef, return undef.

=head2 dump_array_float

  sub dump_array_float : string ($nums : float[])
  
Convert the elements in the float array to string and join them with "," and surround it with "[" and "]", and return it.

For readability spaces and line breaks are inserted.

If byte array is undef, return undef.

=head2 dump_array_double

  sub dump_array_double : string ($nums : double[])
  
Convert the elements in the double array to string and join them with "," and surround it with "[" and "]", and return it.

For readability spaces and line breaks are inserted.

If byte array is undef, return undef.

=head2 dump_array_string

  sub dump_array_string : string ($strings : string[])
  
Join the strings in the array with "," and surround it with "[" and "]", and return it.

For readability spaces and line breaks are inserted.

If string array is undef, return undef.

=head2 dump_array_object

  sub dump_array_object : string ($objects : oarray, $stringer : SPVM::Stringer)
  
Convert the elements in the object array to string by a C<SPVM::Stringer> callback implementation and join them with "," and surround it with "[" and "]", and return it.

For readability spaces and line breaks are inserted.

If string array is undef, return undef.

=head2 memcpy_byte

  sub memcpy_byte : void ($dest : byte[], $dest_offset : int, $source : byte[], $source_offset : int, $length : int)

Copy source byte array to destination byte array with the each offset and a length.

If source data range and destination data overlap, the result is not guaranteed.

Destnation must be defined, otherwise a exception occurs.

Source must be defined, otherwise a exception occurs.

Length must be more than or equals to 0, otherwise a exception occurs.

Destnation offset + length must be within the range of the destnation array, otherwise a exception occurs.

Source offset + length must be within the range of the source array, otherwise a exception occurs.

=head2 memcpy_short

  sub memcpy_short : void ($dest : short[], $dest_offset : int, $source : short[], $source_offset : int, $length : int)

Copy source short array to destination short array with the each offset and a length.

If source data range and destination data overlap, the result is not guaranteed.

Destnation must be defined, otherwise a exception occurs.

Source must be defined, otherwise a exception occurs.

Length must be more than or equals to 0, otherwise a exception occurs.

Destnation offset + length must be within the range of the destnation array, otherwise a exception occurs.

Source offset + length must be within the range of the source array, otherwise a exception occurs.

=head2 memcpy_int
  
  sub memcpy_int : void ($dest : int[], $dest_offset : int, $source : int[], $source_offset : int, $length : int)

Copy source int array to destination int array with the each offset and a length.

Destnation must be defined, otherwise a exception occurs.

Source must be defined, otherwise a exception occurs.

Length must be more than or equals to 0, otherwise a exception occurs.

Destnation offset + length must be within the range of the destnation array, otherwise a exception occurs.

Source offset + length must be within the range of the source array, otherwise a exception occurs.

=head2 memcpy_long
  
  sub memcpy_long : void ($dest : long[], $dest_offset : int, $source : long[], $source_offset : int, $length : int)

Copy source long array to destination long array with the each offset and a length.

If source data range and destination data overlap, the result is not guaranteed.

Destnation must be defined, otherwise a exception occurs.

Source must be defined, otherwise a exception occurs.

Length must be more than or equals to 0, otherwise a exception occurs.

Destnation offset + length must be within the range of the destnation array, otherwise a exception occurs.

Source offset + length must be within the range of the source array, otherwise a exception occurs.

=head2 memcpy_float
  
  sub memcpy_float : void ($dest : float[], $dest_offset : int, $source : float[], $source_offset : int, $length : int)

Copy source float array to destination float array with the each offset and a length.

If source data range and destination data overlap, the result is not guaranteed.

Destnation must be defined, otherwise a exception occurs.

Source must be defined, otherwise a exception occurs.

Length must be more than or equals to 0, otherwise a exception occurs.

Destnation offset + length must be within the range of the destnation array, otherwise a exception occurs.

Source offset + length must be within the range of the source array, otherwise a exception occurs.

=head2 memcpy_double
  
  sub memcpy_double : void ($dest : double[], $dest_offset : int, $source : double[], $source_offset : int, $length : int)

Copy source double array to destination double array with the each offset and a length.

If source data range and destination data overlap, the result is not guaranteed.

Destnation must be defined, otherwise a exception occurs.

Source must be defined, otherwise a exception occurs.

Length must be more than or equals to 0, otherwise a exception occurs.

Destnation offset + length must be within the range of the destnation array, otherwise a exception occurs.

Source offset + length must be within the range of the source array, otherwise a exception occurs.

=head2 memmove_byte

  sub memmove_byte : void ($dest : byte[], $dest_offset : int, $source : byte[], $source_offset : int, $length : int)

Copy source byte array to destination byte array with the each offset and a length.

Even if source data range and destination data overlap, the result is guaranteed.

Destnation must be defined, otherwise a exception occurs.

Source must be defined, otherwise a exception occurs.

Length must be more than or equals to 0, otherwise a exception occurs.

Destnation offset + length must be within the range of the destnation array, otherwise a exception occurs.

Source offset + length must be within the range of the source array, otherwise a exception occurs.

=head2 memmove_short

  memmove_short : void ($dest : short[], $dest_offset : int, $source : short[], $source_offset : int, $length : int)

Copy source short array to destination short array with the each offset and a length.

Even if source data range and destination data overlap, the result is guaranteed.

Destnation must be defined, otherwise a exception occurs.

Source must be defined, otherwise a exception occurs.

Length must be more than or equals to 0, otherwise a exception occurs.

Destnation offset + length must be within the range of the destnation array, otherwise a exception occurs.

Source offset + length must be within the range of the source array, otherwise a exception occurs.

=head2 memmove_int
  
  memmove_int : void ($dest : int[], $dest_offset : int, $source : int[], $source_offset : int, $length : int)

Copy source int array to destination int array with the each offset and a length.

Even if source data range and destination data overlap, the result is guaranteed.

Destnation must be defined, otherwise a exception occurs.

Source must be defined, otherwise a exception occurs.

Length must be more than or equals to 0, otherwise a exception occurs.

Destnation offset + length must be within the range of the destnation array, otherwise a exception occurs.

Source offset + length must be within the range of the source array, otherwise a exception occurs.

=head2 memmove_long
  
  memmove_long : void ($dest : long[], $dest_offset : int, $source : long[], $source_offset : int, $length : int)

Copy source long array to destination long array with the each offset and a length.

Even if source data range and destination data overlap, the result is guaranteed.

Destnation must be defined, otherwise a exception occurs.

Source must be defined, otherwise a exception occurs.

Length must be more than or equals to 0, otherwise a exception occurs.

Destnation offset + length must be within the range of the destnation array, otherwise a exception occurs.

Source offset + length must be within the range of the source array, otherwise a exception occurs.

=head2 memmove_float
  
  sub memmove_float : void ($dest : float[], $dest_offset : int, $source : float[], $source_offset : int, $length : int)

Copy source float array to destination float array with the each offset and a length.

Even if source data range and destination data overlap, the result is guaranteed.

Destnation must be defined, otherwise a exception occurs.

Source must be defined, otherwise a exception occurs.

Length must be more than or equals to 0, otherwise a exception occurs.

Destnation offset + length must be within the range of the destnation array, otherwise a exception occurs.

Source offset + length must be within the range of the source array, otherwise a exception occurs.

=head2 memmove_double
  
  memmove_double : void ($dest : double[], $dest_offset : int, $source : double[], $source_offset : int, $length : int)

Copy source double array to destination double array with the each offset and a length.

Even if source data range and destination data overlap, the result is guaranteed.

Destnation must be defined, otherwise a exception occurs.

Source must be defined, otherwise a exception occurs.

Length must be more than or equals to 0, otherwise a exception occurs.

Destnation offset + length must be within the range of the destnation array, otherwise a exception occurs.

Source offset + length must be within the range of the source array, otherwise a exception occurs.

=head2 new_array_proto

  sub new_array_proto : oarray ($proto_array : oarray, $length : int)

Create a new generic object array as the same type as the given array.

=head2 copy_array_range_byte

  sub copy_array_range_byte : byte[] ($nums : byte[], $offset : int, $length : int)
  
Slice elements in the byte array with the start offset and the length.

Array must be defined, otherwise a exception occurs.

Offset must be in the array range, otherwise a exception occurs.

Length must be more than or equals to 0, othrewise a exception occurs.

Offset + length must not be in the array range, othrewise a exception occurs.

=head2 copy_array_range_short

  sub copy_array_range_short : short[] ($nums : short[], $offset : int, $length : int)

Slice elements in the short array with the start offset and the length.

Array must be defined, otherwise a exception occurs.

Offset must be in the array range, otherwise a exception occurs.

Length must be more than or equals to 0, othrewise a exception occurs.

Offset + length must not be in the array range, othrewise a exception occurs.

=head2 copy_array_range_int

  sub copy_array_range_int : int[] ($nums : int[], $offset : int, $length : int)

Slice elements in the int array with the start offset and the length.

Array must be defined, otherwise a exception occurs.

Offset must be in the array range, otherwise a exception occurs.

Length must be more than or equals to 0, othrewise a exception occurs.

Offset + length must not be in the array range, othrewise a exception occurs.

=head2 copy_array_range_long

  sub copy_array_range_long : long[] ($nums : long[], $offset : int, $length : int)

Slice elements in the long array with the start offset and the length.

Array must be defined, otherwise a exception occurs.

Offset must be in the array range, otherwise a exception occurs.

Length must be more than or equals to 0, othrewise a exception occurs.

Offset + length must not be in the array range, othrewise a exception occurs.

=head2 copy_array_range_float

  sub copy_array_range_float : float[] ($nums : float[], $offset : int, $length : int)

Slice elements in the float array with the start offset and the length.

Array must be defined, otherwise a exception occurs.

Offset must be in the array range, otherwise a exception occurs.

Length must be more than or equals to 0, othrewise a exception occurs.

Offset + length must not be in the array range, othrewise a exception occurs.

=head2 copy_array_range_double

  sub copy_array_range_double : double[] ($nums : double[], $offset : int, $length : int)

Slice elements in the double array with the start offset and the length.

Array must be defined, otherwise a exception occurs.

Offset must be in the array range, otherwise a exception occurs.

Length must be more than or equals to 0, othrewise a exception occurs.

Offset + length must not be in the array range, othrewise a exception occurs.

=head2 copy_array_range_string
  
  sub copy_array_range_string : string[] ($strings : string[], $offset : int, $length : int)

Slice elements in the string array with the start offset and the length.

Array must be defined, otherwise a exception occurs.

Offset must be in the array range, otherwise a exception occurs.

Length must be more than or equals to 0, othrewise a exception occurs.

Offset + length must not be in the array range, othrewise a exception occurs.

=head2 copy_array_range_object

  sub copy_array_range_object : oarray ($elems : oarray, $offset : int, $length : int)

Slice elements in the object array with the start offset and the length.

Array must be defined, otherwise a exception occurs.

Offset must be in the array range, otherwise a exception occurs.

Length must be more than or equals to 0, othrewise a exception occurs.

Offset + length must not be in the array range, othrewise a exception occurs.

=head2 sort_byte

    sub sort_byte : void ($nums : byte[], $offset : int, $length : int, $comparator : SPVM::Comparator::Byte)

Sort byte array itself with a offset, a length, and a L<SPVM::Comparator::Byte> comparator.

Array must be not undef. Otherwise a exception occurs.

Offset must be more than or equals to 0. Otherwise a exception occurs.

Length must be more than or equals to 0. Otherwise a exception occurs.

Offset + Length must be in the array range. Otherwise a exception occurs.

=head2 sort_short

    sub sort_short : void ($nums : short[], $offset : int, $length : int, $comparator : SPVM::Comparator::Short)

Sort short array itself with a offset, a length, and a L<SPVM::Comparator::Short> comparator.

Array must be not undef. Otherwise a exception occurs.

Offset must be more than or equals to 0. Otherwise a exception occurs.

Length must be more than or equals to 0. Otherwise a exception occurs.

Offset + Length must be in the array range. Otherwise a exception occurs.

=head2 sort_int

    sub sort_int : void ($nums : int[], $offset : int, $length : int, $comparator : SPVM::Comparator::Int)

Sort int array itself with a offset, a length, and a L<SPVM::Comparator::Int> comparator.

Array must be not undef. Otherwise a exception occurs.

Offset must be more than or equals to 0. Otherwise a exception occurs.

Length must be more than or equals to 0. Otherwise a exception occurs.

Offset + Length must be in the array range. Otherwise a exception occurs.

=head2 sort_long

    sub sort_long : void ($nums : long[], $offset : int, $length : int, $comparator : SPVM::Comparator::Long)

Sort long array itself with a offset, a length, and a L<SPVM::Comparator::Long> comparator.

Array must be not undef. Otherwise a exception occurs.

Offset must be more than or equals to 0. Otherwise a exception occurs.

Length must be more than or equals to 0. Otherwise a exception occurs.

Offset + Length must be in the array range. Otherwise a exception occurs.

=head2 sort_float

    sub sub sort_float : void ($nums : float[], $offset : int, $length : int, $comparator : SPVM::Comparator::Float)

Sort float array itself with a offset, a length, and a L<SPVM::Comparator::Float> comparator.

Array must be not undef. Otherwise a exception occurs.

Offset must be more than or equals to 0. Otherwise a exception occurs.

Length must be more than or equals to 0. Otherwise a exception occurs.

Offset + Length must be in the array range. Otherwise a exception occurs.

=head2 sort_double

    sub sort_double : void ($nums : double[], $offset : int, $length : int, $comparator : SPVM::Comparator::Double)

Sort double array itself with a offset, a length, and a L<SPVM::Comparator::Double> comparator.

Array must be not undef. Otherwise a exception occurs.

Offset must be more than or equals to 0. Otherwise a exception occurs.

Length must be more than or equals to 0. Otherwise a exception occurs.

Offset + Length must be in the array range. Otherwise a exception occurs.

=head2 sort_string

    sub sort_string : void ($nums : string[], $offset : int, $length : int, $comparator : SPVM::Comparator::Double)

Sort string array itself with a offset, a length, and a L<SPVM::Comparator::String> comparator.

Array must be not undef. Otherwise a exception occurs.

Offset must be more than or equals to 0. Otherwise a exception occurs.

Length must be more than or equals to 0. Otherwise a exception occurs.

Offset + Length must be in the array range. Otherwise a exception occurs.

=head2 sort_object

    sub sort_object : void ($objs : oarray, $offset : int, $length : int, $comparator : SPVM::Comparator::Object)

Sort object array itself with a offset, a length, and a L<SPVM::Comparator::Object> comparator.

Array must be not undef. Otherwise a exception occurs.

Offset must be more than or equals to 0. Otherwise a exception occurs.

Length must be more than or equals to 0. Otherwise a exception occurs.

Offset + Length must be in the array range. Otherwise a exception occurs.
