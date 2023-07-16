package SPVM::Native::Compiler;



1;

=head1 Name

SPVM::Native::Compiler - Native::Compiler

=head1 Description

C<SPVM::Native::Compiler> is the C<Native::Compiler> class in the L<SPVM> language. It compiles SPVM source codes and builds the runtime.

The instance of the L<Native::Runtime|SPVM::Native::Runtime> class is build by the L</"get_runtime"> method in this class.

=head1 Usage

  use Native::Compiler;
  
  my $compiler = Native::Compiler->new;
  
  $compiler->add_include_dir("lib");
  
  $compiler->set_start_file(__FILE__);
  
  {
    my $module_name = "Foo";
    $compiler->set_start_line(__LINE__ + 1);
    my $success = $compiler->compile($module_name);
    unless ($success) {
      my $error_messages = $compiler->get_error_messages;
      for my $error_message (@$error_messages) {
        warn "$error_message";
      }
      die "Can't compile the \"$module_name\" basic type";
    }
  }
  
  {
    my $module_name = "Bar";
    $compiler->set_start_line(__LINE__ + 1);
    my $success = $compiler->compile($module_name);
    unless ($success) {
      my $error_messages = $compiler->get_error_messages;
      for my $error_message (@$error_messages) {
        warn "$error_message";
      }
      die "Can't compile the \"$module_name\" basic type";
    }
  }
  
  my $runtime = $compiler->get_runtime;

=head1 Pointer

The C<Native::Compiler> class is a L<pointer class|SPVM::Document::Language/"Pointer Class">.

Its insntace has a pointer to a L<compiler|SPVM::Document::NativeAPI::Native::Compiler> object.

=head1 Class Methods

=head2 new

  native static method new : Native::Compiler ();

Creates a new C<Native::Compiler> object and returns it.

=head1 Instance Methods

=head2 add_include_dir

  native method add_include_dir : void ($include_dir : string);

Adds a class directory to search for classes.

=head2 set_start_file

  native method set_start_file : void ($start_file : string);

Sets the name of the file to start the compiling by the L</"compile"> method.

=head2 set_start_line

  native method set_start_line : void ($start_line : int);

Sets the line to start compiling by the L</"compile"> method.

=head2 compile

  native method compile : int ($module_name : string);

Compiles the specified class and the classes that are load in the specified class. 

Returns 1 on success, 0 on failure.

This method can be called multiple times.

=head2 get_error_messages

  native method get_error_messages : string[] ();

Returns compilation error messages in this compiling by the L</"compile"> method.

=head2 get_runtime

  native method get_runtime : Native::Runtime ();

Returns the runtime.

The return value is a L<Native::Runtime|SPVM::Native::Runtime> object.

=head1 See Also

=head2 Native::Runtime

The instance of the L<Native::Runtime|SPVM::Native::Runtime> class is build by the L</"get_runtime"> method in this class.

=head1 Copyright & License

Copyright 2023-2023 Yuki Kimoto, all rights reserved.

This program is free software; you can redistribute it and/or modify it
under the same terms as Perl itself.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License