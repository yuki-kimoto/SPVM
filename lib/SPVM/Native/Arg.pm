package SPVM::Native::Arg;



1;

=head1 Name

SPVM::Native::Arg - Information of Arguments

=head1 Description

The Native::Arg class of L<SPVM> has methods to manipulate information of arguments.

=head1 Usage

  my $runtime = Native->get_current_runtime;
  
  my $basic_type = $runtime->get_basic_type_by_name("Point");
  
  my $method = $basic_type->get_method_by_name("new");
  
  my $arg = $method->get_arg_by_index(0);
  
  my $arg_index = $arg->get_index;

=head1 Instance Methods

=head2 get_index

C<method get_index : int ();>

Returns the index of this argument.

=head2 get_basic_type

C<method get_basic_type : L<Native::BasicType|SPVM::Native::BasicType> ();>

Return the L<basic type|SPVM::Native::BasicType> of this argument.

=head2 get_type_dimension

C<method get_type_dimension : int ();>

Returns the type dimension of this argument.

=head2 get_type_flag

C<method get_type_flag : int ();>

Returns the type flag of this argument.

=head2 is_optional

C<method is_optional : int ();>

If this argument is an optional argument, returns 1, otherwise returns 0.

=head2 get_default_value_byte

C<method get_default_value_byte : byte ();>

Returns the default value of the optional argument I<arg> of the C<byte> type.

=head2 get_default_value_short

C<method get_default_value_short : short ();>

Returns the default value of the optional argument I<arg> of the C<short> type.

=head2 get_default_value_int

C<method get_default_value_int : int ();>

Returns the default value of the optional argument I<arg> of the C<int> type.

=head2 get_default_value_long

C<method get_default_value_long : long ();>

Returns the default value of the optional argument I<arg> of the C<long> type.

=head2 get_default_value_float

C<method get_default_value_float : float ();>

Returns the default value of the optional argument I<arg> of the C<float> type.

=head2 get_default_value_double

C<method get_default_value_double : double ();>

Returns the default value of the optional argument I<arg> of the C<double> type.

=head2 get_default_value_object

C<method get_default_value_object : object ();>

Returns the default value of the optional argument I<arg> of an object type.

=head2 See Also

=over 2

=item * L<Native::Method|SPVM::Native::Method>

=item * L<Native::BasicType|SPVM::Native::BasicType>

=item * L<Native::Runtime|SPVM::Native::Runtime>

=item * L<Native|SPVM::Native>

=back

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

