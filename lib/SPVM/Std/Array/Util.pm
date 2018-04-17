package SPVM::Array::Util;

1;

=head1 NAME

SPVM::Std::Arrays - Standard Array Utility

=head1 CONSTANT FUNCTIONS

=head1 FUNCTIONS

=head2 copy_bytes

  sub copy_bytes : byte[] ($original : byte[], $new_length : int);

Copies the specified array, truncating or padding with zeros (if necessary) so the copy has the specified length. For all indices that are valid in both the original array and the copy, the two arrays will contain identical values. For any indices that are valid in the copy but not the original, the copy will contain (byte)0. Such indices will exist if and only if the specified length is greater than that of the original array.

B<Parameters:>

$original - the array to be copied

$new_length - the length of the copy to be returned

B<Returns:>

a copy of the original array, truncated or padded with zeros to obtain the specified length

B<Throws:>

if $new_length is negative

if $original is null

=head2 copy_shorts

  sub copy_shorts : short[] ($original : short[], $new_length : int)

Copies the specified array, truncating or padding with zeros (if necessary) so the copy has the specified length. For all indices that are valid in both the original array and the copy, the two arrays will contain identical values. For any indices that are valid in the copy but not the original, the copy will contain (short)0. Such indices will exist if and only if the specified length is greater than that of the original array.

B<Parameters:>

$original - the array to be copied

$new_length - the length of the copy to be returned

B<Returns:>

a copy of the original array, truncated or padded with zeros to obtain the specified length

B<Throws:>

if newLength is negative
if original is null

=head2 copy_ints

  sub copy_ints : int[] ($original : int[], $new_length : int)

Copies the specified array, truncating or padding with zeros (if necessary) so the copy has the specified length. For all indices that are valid in both the original array and the copy, the two arrays will contain identical values. For any indices that are valid in the copy but not the original, the copy will contain 0. Such indices will exist if and only if the specified length is greater than that of the original array.

B<Parameters:>

$original - the array to be copied

$new_length - the length of the copy to be returned

B<Returns:>

a copy of the original array, truncated or padded with zeros to obtain the specified length

B<Throws:>

if newLength is negative

if original is null

=head2 copy_longs

  sub copy_longs : long[] ($original : long[], $new_length : int)
                            
Copies the specified array, truncating or padding with zeros (if necessary) so the copy has the specified length. For all indices that are valid in both the original array and the copy, the two arrays will contain identical values. For any indices that are valid in the copy but not the original, the copy will contain 0L. Such indices will exist if and only if the specified length is greater than that of the original array.

B<Parameters:>

$original - the array to be copied

$new_length - the length of the copy to be returned

B<Returns:>

a copy of the original array, truncated or padded with zeros to obtain the specified length

B<Throws:>

if newLength is negative

if original is null

=head2 copy_floats

  sub copy_floats : float[] ($original : float[], $new_length : int)
  
Copies the specified array, truncating or padding with zeros (if necessary) so the copy has the specified length. For all indices that are valid in both the original array and the copy, the two arrays will contain identical values. For any indices that are valid in the copy but not the original, the copy will contain 0f. Such indices will exist if and only if the specified length is greater than that of the original array.

B<Parameters:>

$original - the array to be copied

$new_length - the length of the copy to be returned

B<Returns:>

a copy of the original array, truncated or padded with zeros to obtain the specified length

B<Throws:>

if newLength is negative

if original is null

=head2 copy_doubles

  sub copy_doubles : double[] ($original : double[], $new_length : int)
                              
Copies the specified array, truncating or padding with zeros (if necessary) so the copy has the specified length. For all indices that are valid in both the original array and the copy, the two arrays will contain identical values. For any indices that are valid in the copy but not the original, the copy will contain 0d. Such indices will exist if and only if the specified length is greater than that of the original array.

B<Parameters:>

$original - the array to be copied

$new_length - the length of the copy to be returned

B<Returns:>

a copy of the original array, truncated or padded with zeros to obtain the specified length

B<Throws:>

if newLength is negative

if original is null
