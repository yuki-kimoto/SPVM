package SPVM::Sort;

1;

=encoding utf8

=head1 Name

SPVM::Sort - Sorting Functions

=head1 Usage

  # Sort a byte array in-place by asc order
  my $array = [(byte)2, 3, 1];
  Sort->sort_byte($array, method : int ($a : int, $b : int) {
    return $a <=> $b;
  });

  # Sort short array in-place by asc order
  my $array = [(short)2, 3, 1];
  Sort->sort_short($array, method : int ($a : int, $b : int) {
    return $a <=> $b;
  });

  # Sort int array in-place by asc order
  my $array = [2, 3, 1];
  Sort->sort_int($array, method : int ($a : int, $b : int) {
    return $a <=> $b;
  });

  # Sort long array in-place by asc order
  my $array = [(long)2, 3, 1];
  Sort->sort_long($array, method : int ($a : long, $b : long) {
    return $a <=> $b;
  });

  # Sort float array in-place by asc order
  my $array = [(float)2, 3, 1];
  Sort->sort_float($array, method : int ($a : float, $b : float) {
    return $a <=> $b;
  });

  # Sort double array in-place by asc order
  my $array = [(double)2, 3, 1];
  Sort->sort_double($array, method : int ($a : double, $b : double) {
    return $a <=> $b;
  });

  # Sort string array in-place by asc order
  my $array = ["11", "1", "2", undef, ""];
  Sort->sort_string($array, method : int ($a : string, $b : string) {
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
  Sort->sort_object($minimals, method : int ($object1 : object, $object2 : object) {
    my $minimal1 = (TestCase::Minimal)$object1;
    my $minimal2 = (TestCase::Minimal)$object2;
    
    return $minimal1->{x} <=> $minimal2->{x} || $minimal1->{y} <=> $minimal2->{y};
  };

=head1 Description

C<Sort> provides sorting functions. The sorting algorithm is a stable merge sort.

=head1 Class Methods

=head2 sort_byte

C<static method sort_byte : void ($array : byte[], $comparator : L<Comparator::Int|SPVM::Comparator::Int>, $offset : int = 0, $length : int = -1);>

Sorts the range of the elements of C<byte> $array in-place.

The sorted range is from $offset to the position proceeded by $length.

If the length is less than 0, the length to the end of the string is calculated from the length of the array and the offset.

The L<Comparator::Int|SPVM::Comparator::Int> comparator is used to compare each element.

Exceptions:

$array must be defined.

$offset must be greater than or equal to 0.

$comparator must be defined.

$offset + length must be less than or equal to the length of $elements.

=head2 sort_byte_asc

C<method sort_byte_asc : void ($array : byte[], $offset : int = 0, $length : int = -1);>

The alias for the following code using L</"sort_byte">

  Sort->sort_byte($array, method : int ($a : int, $b : int) { return $a <=> $b; }, $offset, $length);

=head2 sort_byte_desc

C<static method sort_byte_desc : void ($array : byte[], $offset : int = 0, $length : int = -1);>

The alias for the following code using L</"sort_byte">

  Sort->sort_byte($array, method : int ($a : int, $b : int) { return $b <=> $a; }, $offset, $length);

=head2 sort_double

C<static method sort_double : void ($array : double[], $comparator : L<Comparator::Double|SPVM::Comparator::Double>, $offset : int = 0, $length : int = -1);>

Sorts the range of the elements of C<double> $array in-place.

The sorted range is from $offset to the position proceeded by $length.

If the length is less than 0, the length to the end of the string is calculated from the length of the array and the offset.

The L<Comparator::Double|SPVM::Comparator::Double> comparator is used to compare each element.

Exceptions:

$array must be defined.

$offset must be greater than or equal to 0.

$comparator must be defined.

$offset + length must be less than or equal to the length of $elements.

=head2 sort_double_asc

C<static method sort_double_asc : void ($array : double[], $offset : int = 0, $length : int = -1);>

The alias for the following code using L</"sort_double">

  Sort->sort_double($array, method : int ($a : double, $b : double) { return $a <=> $b; }, $offset, $length);

=head2 sort_double_desc

C<static method sort_double_desc : void ($array : double[], $offset : int = 0, $length : int = -1);>

The alias for the following code using L</"sort_double">

  Sort->sort_double($array, method : int ($a : double, $b : double) { return $b <=> $a; }, $offset, $length);

=head2 sort_float

C<static method sort_float : void ($array : float[], $comparator : L<Comparator::Float|SPVM::Comparator::Float>, $offset : int = 0, $length : int = -1);>

Sorts the range of the elements of C<float> $array in-place.

The sorted range is from $offset to the position proceeded by $length.

If the length is less than 0, the length to the end of the string is calculated from the length of the array and the offset.

The L<Comparator::Float|SPVM::Comparator::Float> comparator is used to compare each element.

Exceptions:

$array must be defined.

$offset must be greater than or equal to 0.

$comparator must be defined.

$offset + length must be less than or equal to the length of $elements.

=head2 sort_float_asc

C<static method sort_float_asc : void ($array : float[], $offset : int = 0, $length : int = -1);>

The alias for the following code using L</"sort_float">

  Sort->sort_float($array, method : int ($a : float, $b : float) { return $a <=> $b; }, $offset, $length);

=head2 sort_float_desc

C<static method sort_float_desc : void ($array : float[], $offset : int = 0, $length : int = -1);>

The alias for the following code using L</"sort_float">

  Sort->sort_float($array, method : int ($a : float, $b : float) { return $b <=> $a; }, $offset, $length);

=head2 sort_float

C<static method sort_float : void ($array : float[], $comparator : L<Comparator::Float|SPVM::Comparator::Float>, $offset : int = 0, $length : int = -1);>

Sorts the range of the elements of C<float> $array in-place.

The sorted range is from $offset to the position proceeded by $length.

If the length is less than 0, the length to the end of the string is calculated from the length of the array and the offset.

The L<Comparator::Float|SPVM::Comparator::Float> comparator is used to compare each element.

Exceptions:

$array must be defined.

$offset must be greater than or equal to 0.

$comparator must be defined.

$offset + length must be less than or equal to the length of $elements.

=head2 sort_float_asc

C<static method sort_float_asc : void ($array : float[], $offset : int = 0, $length : int = -1);>

The alias for the following code using L</"sort_float">

  Sort->sort_float($array, method : int ($a : float, $b : float) { return $a <=> $b; }, $offset, $length);

=head2 sort_float_desc

C<static method sort_float_desc : void ($array : float[], $offset : int = 0, $length : int = -1);>

The alias for the following code using L</"sort_float">

  Sort->sort_float($array, method : int ($a : float, $b : float) { return $b <=> $a; }, $offset, $length);

=head2 sort_int

C<static method sort_int : void ($array : int[], $comparator : L<Comparator::Int|SPVM::Comparator::Int>, $offset : int = 0, $length : int = -1);>

Sorts the range of the elements of C<int> $array in-place.

The sorted range is from $offset to the position proceeded by $length.

If the length is less than 0, the length to the end of the string is calculated from the length of the array and the offset.

The L<Comparator::Int|SPVM::Comparator::Int> comparator is used to compare each element.

Exceptions:

$array must be defined.

$offset must be greater than or equal to 0.

$comparator must be defined.

$offset + length must be less than or equal to the length of $elements.

=head2 sort_int_asc

C<static method sort_int_asc : void ($array : int[], $offset : int = 0, $length : int = -1);>

The alias for the following code using L</"sort_int">

  Sort->sort_int($array, method : int ($a : int, $b : int) { return $a <=> $b; }, $offset, $length);

=head2 sort_int_desc

C<static method sort_int_desc : void ($array : int[], $offset : int = 0, $length : int = -1);>

The alias for the following code using L</"sort_int">

  Sort->sort_int($array, method : int ($a : int, $b : int) { return $b <=> $a; }, $offset, $length);

=head2 sort_long

C<static method sort_long : void ($array : long[], $comparator : L<Comparator::Long|SPVM::Comparator::Long>, $offset : int = 0, $length : int = -1);>

Sorts the range of the elements of C<long> $array in-place.

The sorted range is from $offset to the position proceeded by $length.

If the length is less than 0, the length to the end of the string is calculated from the length of the array and the offset.

The L<Comparator::Long|SPVM::Comparator::Long> comparator is used to compare each element.

Exceptions:

$array must be defined.

$offset must be greater than or equal to 0.

$comparator must be defined.

$offset + length must be less than or equal to the length of $elements.

=head2 sort_long_asc

C<method sort_long_asc : void ($array : long[], $offset : int = 0, $length : int = -1);>

The alias for the following code using L</"sort_long">

  Sort->sort_long($array, method : int ($a : long, $b : long) { return $a <=> $b; }, $offset, $length);

=head2 sort_long_desc

C<static method sort_long_desc : void ($array : long[], $offset : int = 0, $length : int = -1);>

The alias for the following code using L</"sort_long">

  Sort->sort_long($array, method : int ($a : long, $b : long) { return $b <=> $a; }, $offset, $length);

=head2 sort_object

C<static method sort_object : void ($array : object[], $comparator : L<Comparator|SPVM::Comparator>, $offset : int = 0, $length : int = -1);>

Sorts the range of the elements of object array in-place.

The sorted range is from $offset to the position proceeded by $length.

If the length is less than 0, the length to the end of the string is calculated from the length of the array and the offset.

The L<Comparator|SPVM::Comparator> comparator is used to compare each element.

Exceptions:

$offset must be greater than or equal to 0.

$comparator must be defined.

$offset + length must be less than or equal to the length of $elements.

=head2 sort_short

C<static method sort_short : void ($array : short[], $comparator : L<Comparator::Int|SPVM::Comparator::Int>, $offset : int = 0, $length : int = -1);>

Sorts the range of the elements of C<short> $array in-place.

The sorted range is from $offset to the position proceeded by $length.

If the length is less than 0, the length to the end of the string is calculated from the length of the array and the offset.

The L<Comparator::Int|SPVM::Comparator::Int> comparator is used to compare each element.

Exceptions:

$array must be defined.

$offset must be greater than or equal to 0.

$comparator must be defined.

$offset + length must be less than or equal to the length of $elements.

=head2 sort_short_asc

C<static method sort_short_asc : void ($array : short[], $offset : int = 0, $length : int = -1);>

The alias for the following code using L</"sort_short">

  Sort->sort_short($array, method : int ($a : short, $b : short) { return $a <=> $b; }, $offset, $length);

=head2 sort_short_desc

C<static method sort_short_desc : void ($array : short[], $offset : int = 0, $length : int = -1);>

The alias for the following code using L</"sort_short">

  Sort->sort_short($array, method : int ($a : int, $b : int) { return $b <=> $a; }, $offset, $length);

=head2 sort_string

C<static method sort_string : void ($array : string[], $comparator : L<Comparator::String|SPVM::Comparator::String>, $offset : int = 0, $length : int = -1);>

Sorts the range of the elements of C<string> $array in-place.

The sorted range is from $offset to the position proceeded by $length.

If the length is less than 0, the length to the end of the string is calculated from the length of the array and the offset.

The L<Comparator::Int|SPVM::Comparator::Int> comparator is used to compare each element.

Exceptions:

$array must be defined.

$offset must be greater than or equal to 0.

$comparator must be defined.

$offset + length must be less than or equal to the length of $elements.

=head2 sort_string_asc

C<static method sort_string_asc : void ($array : string[], $offset : int = 0, $length : int = -1);>

The alias for the following code using L</"sort_string">

  Sort->sort_string($array, method : int ($a : string, $b : string) { return $a cmp $b; }, $offset, $length);

=head2 sort_string_desc

C<static method sort_string_desc : void ($array : string[], $offset : int = 0, $length : int = -1);>

The alias for the following code using L</"sort_string">

  Sort->sort_string($array, method : int ($a : string, $b : string) { return $b cmp $a; }, $offset, $length);

=head2 sort_options_asc

C<static method sort_options_asc : void ($options : object[]);>

Sorts $options by the dictionaly asc order of the key.

Exceptions:

$options must be defined. Otherwise an exception is thrown.

The length of $options must be an even number. Otherwise an exception is thrown.

The key of $options must be defined. Otherwise an exception is thrown.

The key of $options must be string type. Otherwise an exception is thrown.

Examples:

  Sort->sort_options({key2 => 1, key3 => 2, key1 => 3});

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
