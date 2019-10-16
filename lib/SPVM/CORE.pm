=head1 NAME

SPVM::CORE - SPVM core functions

=head2 DESCRIPTION

SPVM::CORE is SPVM core functions.

=head2 SYNOPSYS
  
  # Cut a newline
  {
    my $ret = chompr("abc\n");
  }
  
  # Create a new float complex array
  {
    my $re_values = [1.5f, 2.5f, 3.5f];
    my $im_values = [5.5f, 6.5f, 7.5f];
    my $farray = complex_farray($re_values, $im_values);
  }

  # Create a new double complex array
  {
    my $re_values = [1.5, 2.5, 3.5];
    my $im_values = [5.5, 6.5, 7.5];
    my $farray = complex_darray($re_values, $im_values);
  }
  
  # Create a new float complex value
  {
    my $z = complexf(1.5f, 2.5f);
  }

  # Create a new double complex value
  {
    my $z = complexd(1.5f, 2.5f);
  }
  
  # Copy a byte array
  {
    my $nums = [(byte)1, 2, 3];
    my $nums_copy = copy_barray($nums);
  }

  # Copy a string
  {
    my $str = "abc";
    my $str_copy = copy_str($str);
  }

  # Copy a short array
  {
    my $nums = [(short)1, 2, 3];
    my $nums_copy = copy_sarray($nums);
  }

  # Copy a int array
  {
    my $nums = [1, 2, 3];
    my $nums_copy = copy_iarray($nums);
  }

  # Copy a long array
  {
    my $nums = [(long)1, 2, 3];
    my $nums_copy = copy_larray($nums);
  }

  # Copy a float array
  {
    my $nums = [1.5f, 2.5f, 3.5f];
    my $nums_copy = copy_farray($nums);
  }

  # Copy a double array
  {
    my $nums = [1.5, 2.5, 3.5];
    my $nums_copy = copy_darray($nums);
  }
  
  # Copy a string array
  {
    my $strs = ["abc", "def", "ghi"]
    my $strs_copy = copy_strarray($strs);
  }
  
  # Check if the two byte arrays equal
  {
    my $nums1 = [(byte)1, 2];
    my $nums2 = [(byte)1, 2];
    my $ret = equals_barray($nums1, $nums2);
  }

  # Check if the two short arrays equal
  {
    my $nums1 = [(short)1, 2];
    my $nums2 = [(short)1, 2];
    my $ret = equals_sarray($nums1, $nums2);
  }

  # Check if the two int arrays equal
  {
    my $nums1 = [(int)1, 2];
    my $nums2 = [(int)1, 2];
    my $ret = equals_iarray($nums1, $nums2);
  }

  # Check if the two long arrays equal
  {
    my $nums1 = [(long)1, 2];
    my $nums2 = [(long)1, 2];
    my $ret = equals_larray($nums1, $nums2);
  }

  # Check if the two float arrays equal
  {
    my $nums1 = [(float)1, 2];
    my $nums2 = [(float)1, 2];
    my $ret = equals_farray($nums1, $nums2);
  }

  # Check if the two double arrays equal
  {
    my $nums1 = [(double)1, 2];
    my $nums2 = [(double)1, 2];
    my $ret = equals_darray($nums1, $nums2);
  }

  # Check if the two string arrays equal
  {
    my $strs1 = ["abc", "def"];
    my $strs2 = ["abc", "def"];
    my $ret = equals_strarray($strs1, $strs2);
  }
  
  # Search substr
  {
    my $found_pos = index("pppabcde", "bcd", 2);
  }

  # print a string to STDOUT
  {
    print("Hello\n");
  }

  # print a string to STDERR
  {
    # print a string to STDERR
    warn("Hello\n");
    
    # print a string to STDERR with line number
    warn("Hello");
  }

=head1 CLASS METHODS

=head2 chompr

  sub chompr : string ($string : string)

Copy the string and remove the newline "\n" from the end of string and return it.

=head2 complex_farray

  sub complex_farray : SPVM::Complex_2f[] ($re_values : float[], $im_values : float[])

Create a new array of L<SPVM::Complex_2f> with real values and imaginary values.

=head2 complex_darray

  sub complex_darray : SPVM::Complex_2d[] ($re_values : double[], $im_values : double[])

Create a new array of L<SPVM::Complex_2d> with real values and imaginary values.

=head2 complexf

  sub complexf : SPVM::Complex_2f ($re : float, $im : float)

Return a new value of L<SPVM::Complex_2f>.

=head2 complexd

sub complexd : SPVM::Complex_2d ($re : double, $im : double)

Return a new value of L<SPVM::Complex_2d>.

=head2 copy_barray

  sub copy_barray : byte[] ($nums : byte[])

Copy a byte array.

If the array is undefined, a exception occurs.

=head2 copy_str

  sub copy_str : string ($string : string)

Copy a string.

If the array is undefined, a exception occurs.

=head2 copy_sarray

  sub copy_sarray : short[] ($nums : short[])

Copy a short array.

If the array is undefined, a exception occurs.
  
=head2 copy_iarray

  sub copy_iarray : int[] ($nums : int[])

Copy a int array.

If the array is undefined, a exception occurs.
  
=head2 copy_larray

  sub copy_larray : long[] ($nums : long[])

Copy a long array.

If the array is undefined, a exception occurs.

=head2 copy_farray

  sub copy_farray : float[] ($nums : float[])

Copy a float array.

If the array is undefined, a exception occurs.

=head2 copy_darray

  sub copy_darray : double[] ($nums : double[])

Copy a double array.

If the array is undefined, a exception occurs.

=head2 copy_strarray

  sub copy_strarray : string[] ($strings : string[])

Copy a string array.

If the array is undefined, a exception occurs.

=head2 equals_barray

  sub equals_barray : int ($nums1 : byte[], $nums2 : byte[])

Check if two byte arrays equal.

If at least one of the arrays is undefined, a excetpion occurs.

=head2 equals_sarray

  sub equals_sarray : int ($nums1 : short[], $nums2 : short[])

Check if two short arrays equal.

If at least one of the arrays is undefined, a excetpion occurs.

=head2 equals_iarray

  sub equals_iarray : int ($nums1 : int[], $nums2 : int[])

Check if two int arrays equal.

If at least one of the arrays is undefined, a excetpion occurs.

=head2 equals_larray

  sub equals_larray : int ($nums1 : long[], $nums2 : long[])

Check if two long arrays equal.

If at least one of the arrays is undefined, a excetpion occurs.

=head2 equals_farray

  sub equals_farray : int ($nums1 : float[], $nums2 : float[])

Check if two float arrays equal.

If at least one of the arrays is undefined, a excetpion occurs.

=head2 equals_darray

  sub equals_darray : int ($nums1 : double[], $nums2 : double[])

Check if two double arrays equal.

If at least one of the arrays is undefined, a excetpion occurs.

=head2 equals_strarray

  sub equals_strarray : int ($strs1 : double[], $strs2 : double[])

Check if two string arrays equal.

If at least one of the arrays is undefined, a excetpion occurs.

=head2 E

  sub E : double ()

Get a napier number.

=head2 get_type_name

  sub get_type_name : string ($obj : object)

Get the type name of the object.

=head2 index

  sub index : int ($str : string, $substr : string, $posision : int)

index function searches for one string within another.
It returns the position of the first occurrence of $substr in $str at or after $position. If $position is omitted, starts
searching from the beginning of the string. $position before the
beginning of the string or after its end is treated as if it were
the beginning or the end, respectively. $position and the return
value are based at zero. If the substring is not found, "index"
returns -1.
            
=head2 INT8_MIN

B<sub INT8_MIN : byte ()>

Wapper of INT8_MIN of C99 cstdint library.

=head2 INT8_MAX

B<INT8_MAX : byte ()>

Wapper of INT8_MAX of C99 cstdint library.

=head2 INT16_MIN

B<sub INT16_MIN : short ()>

Wapper of INT16_MIN of C99 cstdint library.

=head2 INT16_MAX

B<sub INT16_MAX : short ()>

Wapper of INT16_MAX of C99 cstdint library.

=head2 INT32_MIN

B<sub INT32_MIN : int ()>

Wapper of INT32_MIN of C99 cstdint library.

=head2 INT32_MAX

B<sub INT32_MAX : int ()>

Wapper of INT32_MAX of C99 cstdint library.

=head2 INT64_MIN

B<sub INT64_MIN : long ()>

Wapper of INT64_MIN of C99 cstdint library.

=head2 INT64_MAX

B<sub INT64_MAX : long ()>

Wapper of INT64_MAX of C99 cstdint library.

=head2 FLT_MIN

B<sub FLT_MIN : float ()>

Wapper of FLT_MIN of C99 float library.

=head2 FLT_MAX

B<sub FLT_MAX : float ()>

Wapper of FLT_MAX of C99 float library.

=head2 DBL_MIN

B<sub DBL_MIN : double ()>

Wapper of DBL_MIN of C99 float library.

=head2 DBL_MAX

B<sub DBL_MAX : double ()>

Wapper of DBL_MAX of C99 float library.

=head2 isalnum

  sub isalnum : int ($char : int)

If character is alphanumeric('A'-'Z', 'a'-'z', '0'-'9'), return 1. If not, return 0.

=head2 isalpha

  sub isalpha : int ($char : int)

If character is alphabetic('A'-'Z', 'a'-'z'), return 1. If not, return 0.

=head2 isblank

  sub isblank : int ($char : int)

If character is blank(' ', '\t'), return 1. If not, return 0.

=head2 iscntrl

  sub iscntrl : int ($char : int)

If character is a control character(0x00-0x1F, 0x7F), return 1. If not, return 0.

=head2 isdigit

  sub isdigit : int ($char : int)

If character is decimal digit ('0'～'9'), return 1. If not, return 0.

=head2 isgraph

  sub isgraph : int ($char : int)

If character has graphical representation(0x21-0x7E), return 1. If not, return 0.

=head2 islower

  sub islower : int ($char : int)

If character is lowercase letter('a'-'z'), return 1. If not, return 0.

=head2 isprint

  sub isprint : int ($char : int)

If character is printable(0x20-0x7E), return 1. If not, return 0.

=head2 ispunct

  sub ispunct : int ($char : int)

If character is a punctuation character(0x21-0x2f, 0x3a-0x40, 0x5b-0x60, 0x7b-0x7e), return 1. If not, return 0.

=head2 isspace

  sub isspace : int ($char : int)

If character is a white-space(' ',  '\t', '\n', '\v', '\f', '\r'), return 1. If not return 0.

=head2 

  sub isupper : int ($char : int)

Check if character is uppercase letter

=head2 

  sub isxdigit : int ($char : int)

Check if character is hexadecimal digit

=head2 

  sub tolower : int ($char : int)

Convert uppercase letter to lowercase

=head2 

  sub toupper : int ($char : int)

=head2 

  sub is_perl_space : int ($char : int)

Convert lowercase letter to uppercase

=head2 

  sub is_perl_word : int ($char : int)

=head2 print

Print string to stdout.

  sub print : void ($string : string);

=head2 warn

Print string with file name and line number to stderr. line break is added to end of string.

  sub warn : void ($string : string);
  
