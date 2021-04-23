package SPVM::ArrayUtil;

1;

=head1 NAME

SPVM::ArrayUtil - Array Utilities

=head1 SYNOPSYS
  
  use SPVM::ArrayUtil;

  # Copy a byte array
  {
    my $nums = [(byte)1, 2, 3];
    my $nums_copy = copy_byte_array($nums);
  }

  # Copy a short array
  {
    my $nums = [(short)1, 2, 3];
    my $nums_copy = copy_short_array($nums);
  }

  # Copy a int array
  {
    my $nums = [1, 2, 3];
    my $nums_copy = copy_int_array($nums);
  }

  # Copy a long array
  {
    my $nums = [(long)1, 2, 3];
    my $nums_copy = copy_long_array($nums);
  }

  # Copy a float array
  {
    my $nums = [1.5f, 2.5f, 3.5f];
    my $nums_copy = copy_float_array($nums);
  }

  # Copy a double array
  {
    my $nums = [1.5, 2.5, 3.5];
    my $nums_copy = copy_double_array($nums);
  }
  
  # Copy a string array
  {
    my $strs = ["abc", "def", "ghi"]
    my $strs_copy = copy_string_array($strs);
  }
  
  # Check if the two byte arrays equal
  {
    my $nums1 = [(byte)1, 2];
    my $nums2 = [(byte)1, 2];
    my $ret = equals_byte_array($nums1, $nums2);
  }

  # Check if the two short arrays equal
  {
    my $nums1 = [(short)1, 2];
    my $nums2 = [(short)1, 2];
    my $ret = equals_short_array($nums1, $nums2);
  }

  # Check if the two int arrays equal
  {
    my $nums1 = [(int)1, 2];
    my $nums2 = [(int)1, 2];
    my $ret = equals_int_array($nums1, $nums2);
  }

  # Check if the two long arrays equal
  {
    my $nums1 = [(long)1, 2];
    my $nums2 = [(long)1, 2];
    my $ret = equals_long_array($nums1, $nums2);
  }

  # Check if the two float arrays equal
  {
    my $nums1 = [(float)1, 2];
    my $nums2 = [(float)1, 2];
    my $ret = equals_float_array($nums1, $nums2);
  }

  # Check if the two double arrays equal
  {
    my $nums1 = [(double)1, 2];
    my $nums2 = [(double)1, 2];
    my $ret = equals_double_array($nums1, $nums2);
  }

  # Check if the two string arrays equal
  {
    my $strs1 = ["abc", "def"];
    my $strs2 = ["abc", "def"];
    my $ret = equals_string_array($strs1, $strs2);
  }
  
  # Copy object array
  my $objects = [(object)SPVM::Int->new(1), SPVM::Int->new(2), SPVM::Int->new(3)];
  my $objects_copy = copy_object_array($objects, sub : object ($self : self, $obj : object) {
    my $int_obj = (SPVM::Int)$obj;
    my $new_int_obj = SPVM::Int->new($int_obj->value);
    return $new_int_obj;
  });
  
=head1 DESCRIPTION

Array Utilities.

=head1 STATIC METHODS

=head2 copy_object_array

  sub copy_object_array : object[] ($objects : object[], $cloner : SPVM::Cloner)

Copy object array. You must specify a L<SPVM::Cloner> object to copy each element.

=head2 copy_byte_array

  sub copy_byte_array : byte[] ($nums : byte[])

Copy a byte array.

If the array is undefined, a exception occurs.

=head2 copy_short_array

  sub copy_short_array : short[] ($nums : short[])

Copy a short array.

If the array is undefined, a exception occurs.
  
=head2 copy_int_array

  sub copy_int_array : int[] ($nums : int[])

Copy a int array.

If the array is undefined, a exception occurs.
  
=head2 copy_long_array

  sub copy_long_array : long[] ($nums : long[])

Copy a long array.

If the array is undefined, a exception occurs.

=head2 copy_float_array

  sub copy_float_array : float[] ($nums : float[])

Copy a float array.

If the array is undefined, a exception occurs.

=head2 copy_double_array

  sub copy_double_array : double[] ($nums : double[])

Copy a double array.

If the array is undefined, a exception occurs.

=head2 equals_object_array

  sub sub equals_object_array : int ($objs1 : oarray, $objs2 : oarray, $equality_checker : SPVM::EqualityChecker)

Check equality of two objects. You must sepecify a L<SPVM::EqualityChecker> object to check the equality of each element.

$objs1 and $objs2 and $equality_checker must be defined, otherwise a exception occur.

Return 1 if the length of $objs1 and $objs2 is same and all element is same, otherwise return 0.

=head2 copy_string_array

  sub copy_string_array : string[] ($strings : string[])

Copy a string array.

If the array is undefined, a exception occurs.

=head2 equals_byte_array

  sub equals_byte_array : int ($nums1 : byte[], $nums2 : byte[])

Check if two byte arrays equal.

If at least one of the arrays is undefined, a excetpion occurs.

=head2 equals_short_array

  sub equals_short_array : int ($nums1 : short[], $nums2 : short[])

Check if two short arrays equal.

If at least one of the arrays is undefined, a excetpion occurs.

=head2 equals_int_array

  sub equals_int_array : int ($nums1 : int[], $nums2 : int[])

Check if two int arrays equal.

If at least one of the arrays is undefined, a excetpion occurs.

=head2 equals_long_array

  sub equals_long_array : int ($nums1 : long[], $nums2 : long[])

Check if two long arrays equal.

If at least one of the arrays is undefined, a excetpion occurs.

=head2 equals_float_array

  sub equals_float_array : int ($nums1 : float[], $nums2 : float[])

Check if two float arrays equal.

If at least one of the arrays is undefined, a excetpion occurs.

=head2 equals_double_array

  sub equals_double_array : int ($nums1 : double[], $nums2 : double[])

Check if two double arrays equal.

If at least one of the arrays is undefined, a excetpion occurs.

=head2 equals_string_array

  sub equals_string_array : int ($strs1 : double[], $strs2 : double[])

Check if two string arrays equal.

If at least one of the arrays is undefined, a excetpion occurs.

=head2 dump_array_byte

  sub dump_array_byte : string ($nums : byte[])
  
Convert the elements in the byte array to string and join them with "," and surround it with "[" and "]", and return it.

If byte array is undef, return undef.

=head2 dump_array_short

  sub dump_array_short : string ($nums : short[])
  
Convert the elements in the short array to string and join them with "," and surround it with "[" and "]".

For Easy-to-read spaces and line breaks are inserted.

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

For Easy-to-read spaces and line breaks are inserted.

If byte array is undef, return undef.

=head2 dump_array_unsigned_int

  sub dump_array_unsigned_int : string ($nums : int[])
  
Convert the elements in the int array to string interpreting as an unsigned 32bit integer and join them with "," and surround it with "[" and "]", and return it.

If byte array is undef, return undef.

=head2 dump_array_unsigned_long

  sub dump_array_unsigned_long : string ($nums : long[])
  
Convert the elements in the long array to string interpreting as an unsigned 64bit integer and join them with "," and surround it with "[" and "]", and return it.

If byte array is undef, return undef.

=head2 dump_array_float

  sub dump_array_float : string ($nums : float[])
  
Convert the elements in the float array to string and join them with "," and surround it with "[" and "]", and return it.

If byte array is undef, return undef.

=head2 dump_array_double

  sub dump_array_double : string ($nums : double[])
  
Convert the elements in the double array to string and join them with "," and surround it with "[" and "]", and return it.

If byte array is undef, return undef.

=head2 memcpy_byte

  sub memcpy_byte : void ($dest_data : byte[], $dest_offset : int, $src_data : byte[], $src_offset : int, $length : int)

Copy source byte array to destination byte array with the each offset and a length.

If source data range and destination data overlap, the result is not guaranteed.

If source byte array or destination array is undef, a exception occurs.

If source byte array or destination array is undef, a exception occurs.

If length is nagative, a exception occurs.

If copy is not in the valid rainge, a exception occurs.

=head2 memcpy_short

  sub memcpy_short : void ($dest_data : short[], $dest_offset : int, $src_data : short[], $src_offset : int, $length : int)

Copy source short array to destination short array with the each offset and a length.

If source data range and destination data overlap, the result is not guaranteed.

If source short array or destination array is undef, a exception occurs.

If source short array or destination array is undef, a exception occurs.

If length is nagative, a exception occurs.

If copy is not in the valid rainge, a exception occurs.

=head2 memcpy_int
  
  sub memcpy_int : void ($dest_data : int[], $dest_offset : int, $src_data : int[], $src_offset : int, $length : int)

Copy source int array to destination int array with the each offset and a length.

If source data range and destination data overlap, the result is not guaranteed.

If source int array or destination array is undef, a exception occurs.

If source int array or destination array is undef, a exception occurs.

If length is nagative, a exception occurs.

If copy is not in the valid rainge, a exception occurs.

=head2 memcpy_long
  
  sub memcpy_long : void ($dest_data : long[], $dest_offset : int, $src_data : long[], $src_offset : int, $length : int)

Copy source long array to destination long array with the each offset and a length.

If source data range and destination data overlap, the result is not guaranteed.

If source long array or destination array is undef, a exception occurs.

If source long array or destination array is undef, a exception occurs.

If length is nagative, a exception occurs.

If copy is not in the valid rainge, a exception occurs.

=head2 memcpy_float
  
  sub memcpy_float : void ($dest_data : float[], $dest_offset : int, $src_data : float[], $src_offset : int, $length : int)

Copy source float array to destination float array with the each offset and a length.

If source data range and destination data overlap, the result is not guaranteed.

If source float array or destination array is undef, a exception occurs.

If source float array or destination array is undef, a exception occurs.

If length is nagative, a exception occurs.

If copy is not in the valid rainge, a exception occurs.

=head2 memcpy_double
  
  sub memcpy_double : void ($dest_data : double[], $dest_offset : int, $src_data : double[], $src_offset : int, $length : int)

Copy source double array to destination double array with the each offset and a length.

If source data range and destination data overlap, the result is not guaranteed.

If source double array or destination array is undef, a exception occurs.

If source double array or destination array is undef, a exception occurs.

If length is nagative, a exception occurs.

If copy is not in the valid rainge, a exception occurs.

=head2 memmove_byte

  sub memmove_byte : void ($dest_data : byte[], $dest_offset : int, $src_data : byte[], $src_offset : int, $length : int)

Copy source byte array to destination byte array with the each offset and a length.

Even if source data range and destination data overlap, the result is guaranteed.

If source byte array or destination array is undef, a exception occurs.

If source byte array or destination array is undef, a exception occurs.

If length is nagative, a exception occurs.

If copy is not in the valid rainge, a exception occurs.

=head2 memmove_short

  sub memmove_short : void ($dest_data : short[], $dest_offset : int, $src_data : short[], $src_offset : int, $length : int)

Copy source short array to destination short array with the each offset and a length.

Even if source data range and destination data overlap, the result is guaranteed.

If source short array or destination array is undef, a exception occurs.

If source short array or destination array is undef, a exception occurs.

If length is nagative, a exception occurs.

If copy is not in the valid rainge, a exception occurs.

=head2 memmove_int
  
  sub memmove_int : void ($dest_data : int[], $dest_offset : int, $src_data : int[], $src_offset : int, $length : int)

Copy source int array to destination int array with the each offset and a length.

Even if source data range and destination data overlap, the result is guaranteed.

If source int array or destination array is undef, a exception occurs.

If source int array or destination array is undef, a exception occurs.

If length is nagative, a exception occurs.

If copy is not in the valid rainge, a exception occurs.

=head2 memmove_long
  
  sub memmove_long : void ($dest_data : long[], $dest_offset : int, $src_data : long[], $src_offset : int, $length : int)

Copy source long array to destination long array with the each offset and a length.

Even if source data range and destination data overlap, the result is guaranteed.

If source long array or destination array is undef, a exception occurs.

If source long array or destination array is undef, a exception occurs.

If length is nagative, a exception occurs.

If copy is not in the valid rainge, a exception occurs.

=head2 memmove_float
  
  sub memmove_float : void ($dest_data : float[], $dest_offset : int, $src_data : float[], $src_offset : int, $length : int)

Copy source float array to destination float array with the each offset and a length.

Even if source data range and destination data overlap, the result is guaranteed.

If source float array or destination array is undef, a exception occurs.

If source float array or destination array is undef, a exception occurs.

If length is nagative, a exception occurs.

If copy is not in the valid rainge, a exception occurs.

=head2 memmove_double
  
  sub memmove_double : void ($dest_data : double[], $dest_offset : int, $src_data : double[], $src_offset : int, $length : int)

Copy source double array to destination double array with the each offset and a length.

Even if source data range and destination data overlap, the result is guaranteed.

If source double array or destination array is undef, a exception occurs.

If source double array or destination array is undef, a exception occurs.

If length is nagative, a exception occurs.

If copy is not in the valid rainge, a exception occurs.

=head2 new_object_array_proto

  sub new_object_array_proto : oarray ($proto_array : oarray, $length : int)

Create a new generic object array as the same type as the given array.

=head2 slice_byte

=head2 slice_short

=head2 slice_int

=head2 slice_long

=head2 slice_float

=head2 slice_double

