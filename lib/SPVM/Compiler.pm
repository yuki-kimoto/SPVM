package SPVM::Compiler;



1;

=head1 Name

SPVM::Compiler - Compiler

=head1 Description

C<SPVM::Compiler> is C<Compiler> class in L<SPVM>. It compiles SPVM source codes and build the runtime.

=head1 Usage

  use Compiler;
  
  my $compiler = Compiler->new;
  
  $compiler->add_module_dir("lib");
  
  $compiler->set_start_file(__FILE__);
  
  {
    my $class_name = "Foo";
    $compiler->set_start_line(__LINE__ + 1);
    my $success = $compiler->compile($class_name);
    unless ($success) {
      my $error_messages = $compiler->get_error_messages;
      for my $error_message (@$error_messages) {
        warn "$error_message";
      }
      die "Can't compile the \"$class_name\" class";
    }
  }
  
  {
    my $class_name = "Bar";
    $compiler->set_start_line(__LINE__ + 1);
    my $success = $compiler->compile($class_name);
    unless ($success) {
      my $error_messages = $compiler->get_error_messages;
      for my $error_message (@$error_messages) {
        warn "$error_message";
      }
      die "Can't compile the \"$class_name\" class";
    }
  }
  
  my $runtime = $compiler->build_runtime;

=head1 Pointer

C<Compiler> is a L<pointer class|SPVM::Document::Language/"Pointer Class">.

The insntace has the pointer to a L<compiler|SPVM::Document::NativeAPI::Compiler> object.

=head1 Class Methods

=head2 new

  native static method new : Compiler ();

Creates a new C<Compiler> object and returns it.

=head1 Instance Methods

=head2 add_module_dir

  native method add_module_dir : void ($module_dir : string);

Adds a module directory to search for classes.

=head2 set_start_file

  native method set_start_file : void ($start_file : string);

Sets the name of the file to start the compiling by the L</"compile"> method.

=head2 set_start_line

  native method set_start_line : void ($start_line : int);

Sets the line to start compiling by the L</"compile"> method.

=head2 compile

  native method compile : int ($class_name : string);

Compiles the specified class and the classes that are load in the specified class. 

Returns 1 on success, 0 on failure.

This method can be called multiple times.

=head2 get_error_messages

  native method get_error_messages : string[] ();

Returns compilation error messages in this compiling by the L</"compile"> method.

=head2 build_runtime

  native method build_runtime : Runtime ();

Builds the runtime and returns it.

The return value is a L<Runtime|SPVM::Runtime> object.

=head1 Copyright & License

Copyright 2023-2023 Yuki Kimoto, all rights reserved.

This program is free software; you can redistribute it and/or modify it
under the same terms as Perl itself.
