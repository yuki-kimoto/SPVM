package SPVM::CallerInfo;

1;

=head1 Name

SPVM::CallerInfo - Information about a Caller

=head1 Description

L<CallerInfo|SPVM::CallerInfo> class in L<SPVM> represents information about a caller, such as the method name, the file name, and the line number.

=head1 Usage

  my $caller = CallerInfo->new;
  
  # Setters
  $caller->set_name("Foo#bar");
  $caller->set_file("Foo.spvm");
  $caller->set_line(10);
  
  # Getters
  my $name = $caller->name;
  my $file = $caller->file;
  my $line = $caller->line;

=head1 Details

This class is automatically loaded.

=head1 Fields

=head2 name

C<has name : rw string;>

The name of the caller. This is usually a method absolute name or a function name.

=head2 file

C<has file : rw string;>

The file name where the caller is located.

=head2 line

C<has line : rw int;>

The line number where the caller is located.

=head1 Class Methods

=head2 new

C<static method new : L<CallerInfo|SPVM::CallerInfo> ();>

Creates a new L<CallerInfo|SPVM::CallerInfo> object and returns it.

=head1 Copyright & License

Copyright (c) 2026 Yuki Kimoto

MIT License
