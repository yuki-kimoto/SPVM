package SPVM::Compiler;



1;

=head1 Name

SPVM::Compiler - Compiler

=head1 Description

C<SPVM::Compiler> is the C<Compiler> class in the L<SPVM> language. It compiles SPVM source codes and builds the runtime.

The instance of the L<Runtime|SPVM::Runtime> class is build by the L</"build_runtime"> method in this class.

=head1 Usage

  use Compiler;
  
  my $compiler = Compiler->new;
  
  $compiler->add_include_dir("lib");
  
  $compiler->set_start_file(__FILE__);
  
  {
    my $basic_type_name = "Foo";
    $compiler->set_start_line(__LINE__ + 1);
    my $success = $compiler->compile($basic_type_name);
    unless ($success) {
      my $error_messages = $compiler->get_error_messages;
      for my $error_message (@$error_messages) {
        warn "$error_message";
      }
      die "Can't compile the \"$basic_type_name\" class";
    }
  }
  
  {
    my $basic_type_name = "Bar";
    $compiler->set_start_line(__LINE__ + 1);
    my $success = $compiler->compile($basic_type_name);
    unless ($success) {
      my $error_messages = $compiler->get_error_messages;
      for my $error_message (@$error_messages) {
        warn "$error_message";
      }
      die "Can't compile the \"$basic_type_name\" class";
    }
  }
  
  my $runtime = $compiler->build_runtime;

=head1 Pointer

The C<Compiler> class is a L<pointer class|SPVM::Document::Language/"Pointer Class">.

Its insntace has a pointer to a L<compiler|SPVM::Document::NativeAPI::Compiler> object.

=head1 Class Methods

=head2 new

  native static method new : Compiler ();

Creates a new C<Compiler> object and returns it.

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

  native method compile : int ($basic_type_name : string);

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

=head1 See Also

=head2 Runtime

The instance of the L<Runtime|SPVM::Runtime> class is build by the L</"build_runtime"> method in this class.

=head1 Copyright & License

Copyright 2023-2023 Yuki Kimoto, all rights reserved.

This program is free software; you can redistribute it and/or modify it
under the same terms as Perl itself.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
