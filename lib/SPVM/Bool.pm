package SPVM::Bool;

1;

=head1 Name

SPVM::Bool - Bool Object

=head1 Description

The Bool class of L<SPVM> has methods to manipulate a bool object.

This class is a L<default loaded class|SPVM::Document::Language/"Default Loaded Classes">.

The L<boolean conversion|SPVM::Document::Language/"Boolean Conversion"> of an instance of this class returns the the L</"value"> field.

The instance of this class is immutable.

=head1 Usage

  use Bool;
  
  my $true = Bool->new_true;
  my $false = Bool->new_false;
  
  my $true_value = $true->value;
  my $false_value = $false->value;

=head1 Fiedls

=head2 value

  has value : ro int;

Returns a value.

=head1 Class Methods

=head2 new_true

  static method new_true : Bool ();

Create a new L<Bool> object which L</"value"> field is set to 1.

=head2 new_false

  static method new_false : Bool ();

Create a new L<Bool> object which L</"value"> field is set to 0.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
