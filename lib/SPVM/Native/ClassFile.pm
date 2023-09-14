package SPVM::Native::ClassFile;



1;

=head1 Name

SPVM::Native::ClassFile - Information of Class Files

=head1 Description

The Native::ClassFile class of L<SPVM> has methods to manipulate information of class files

=head1 Usage

  use Native::ClassFile;

=head1 Instance Methods

=head2 get_class_name

C<method get_class_name : string ();>

Returns the class name.

If a memory error occurs, an exception is thrown.

=head2 get_file

C<method get_file : string ();>

Returns the file.

If a memory error occurs, an exception is thrown.

=head2 set_file

C<method set_file : void ($file : string);>

Sets the file.

If a memory error occurs, an exception is thrown.

=head2 get_dir

C<method get_dir : string ();>

Returns the directory.

If a memory error occurs, an exception is thrown.

=head2 set_dir

C<method set_dir : void ($dir : string);>

Sets the directory.

If a memory error occurs, an exception is thrown.

=head2 get_rel_file

C<method get_rel_file : string ();>

Returns the relative file.

If a memory error occurs, an exception is thrown.

=head2 set_rel_file

C<method set_rel_file : void ($rel_file : string);>

Ss the relative file.

If a memory error occurs, an exception is thrown.

=head2 get_content

C<method get_content : string ();>

Returns the content.

If a memory error occurs, an exception is thrown.

=head2 set_content

C<method set_content : void ($content : string);>

Sets the content.

If a memory error occurs, an exception is thrown.

=head2 get_content_length

C<method get_content_length : int ();>

Returns the length of the content.

If a memory error occurs, an exception is thrown.

=head2 set_content_length

C<method set_content_length : void ($content_length : int);>
  
Sets the length of the content.

If a memory error occurs, an exception is thrown.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

