package SPVM::Builder::CallerInfo;
use strict;
use warnings;

# Fields
sub line {
  my $self = shift;
  if (@_) {
    $self->{line} = $_[0];
    return $self;
  }
  else {
    return $self->{line};
  }
}

sub file {
  my $self = shift;
  if (@_) {
    $self->{file} = $_[0];
    return $self;
  }
  else {
    return $self->{file};
  }
}

sub method_abs_name {
  my $self = shift;
  if (@_) {
    $self->{method_abs_name} = $_[0];
    return $self;
  }
  else {
    return $self->{method_abs_name};
  }
}

# Class Methods
sub new {
  my $error = shift;
  
  my $self = {
    line => 0,
    file => undef,
    method_abs_name => undef,
    @_
  };
  
  bless $self, ref $error || $error;
  
  return $self;
}

1;

=head1 Name

SPVM::ExchangeAPI::Options - Options Code

=head1 Description

The SPVM::ExchangeAPI::Options class has methods to get and set options.

=head1 Usage
  
  my $error = SPVM::ExchangeAPI::Options->new;

=head1 Fields

=head2 line

  my $line = $error->line;
  $error->line($line);

Gets and sets a line number.

Examples:

  $error->line(10);
  my $line = $error->line;

=head2 file

  my $file = $error->file;
  $error->file($file);

Gets and sets a file path.

Examples:

  $error->file("TestCase.spvm");
  my $file = $error->file;

=head2 method_abs_name

  my $method_abs_name = $error->method_abs_name;
  $error->method_abs_name($method_abs_name);

Gets and sets a method absolute name.

Examples:

  $error->method_abs_name("TestCase#foo");
  my $method_abs_name = $error->method_abs_name;

=head1 Class Methods

=head2 new

  my $error = SPVM::ExchangeAPI::Options->new(%options);

Creates a new C<SPVM::ExchangeAPI::Options> object.

Options:

=over 2

=item * C<line>

A line number.

=item * C<file>

A file path.

=item * C<method_abs_name>

A method absolute name.

=back

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
