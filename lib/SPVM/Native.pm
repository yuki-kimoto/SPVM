package SPVM::Native;



1;

=head1 Name

SPVM::Native - Getting the current native environment, stack, runtime, compiler.

=head1 Description

The Native class of L<SPVM> has methods to get the current native environment, stack, runtime, compiler.

=head1 Usage

  use Native;

=head1 Class Methods

=head2 get_current_stack

C<static method get_current_stack : L<Native::Stack|SPVM::Native::Stack> ();>

Returns the current execution stack.

=head2 get_current_env

C<static get_current_env : L<Native::Env|SPVM::Native::Env> ();>

Returns the current execution environemnt.

=head2 get_current_runtime

C<static method get_current_runtime : L<Native::Runtime|SPVM::Native::Runtime> ();>

Returns the current runtime.

=head2 get_current_compiler

C<static method get_current_compiler : L<Native::Compiler|SPVM::Native::Compiler> ();>

Returns the current compiler.

=head2 check_bootstrap_method

C<static method check_bootstrap_method : void ($basic_type_name : string);>

Check the bootstrap method in the basic type $basic_type_name.

=head2 use

C<static method use : void (static method use : void ($class_name : string, $file : string = undef, $line : int = -1));>

Compiles the class $class_name using the compiler of the current runtime.

=head2 use_anon_class

C<static method use_anon_class : string ($source : string, $file : string = undef, $line : int = -1);>

Compiles the anon class source $source using the compiler of the current runtime.

=head2 eval

C<static method eval : object ($eval_source : string);>

This method emulates L<Perl's string eval|https://perldoc.perl.org/functions/eval#String-eval>.

This method creates the following source code.

  "
  class {
  static method eval : object () {
  #line 1
  $eval_source
  }
  }
  "

And calls L</"compile_anon_class"> given this source code and gets the anon class name.

And calls L<call_class_method|SPVM::Native::MethodCall/"call_class_method"> in the Native::MethodCall class.

  Native::MethodCall->call_class_method($anon_class_name, "eval");

Examples:

  my $value = (Int)Native->eval("my $total = 1 + 2; return $total;");
  say $value->value;

=head2 inc

C<static method inc : string[] ();>

Returns the current serach directories of the class search directories of the compiler of the current runtime.

=head2 set_inc

C<static method set_inc : void ($include_dirs : string[]);>

Set the current serach directories $include_dirs to the class search directories of the compiler of the current runtime.

=head2 push_inc

C<static method push_inc : void ($include_dir : string);>

Add the class search directory $include_dir at the tail of the class search directories of the compiler of the current runtime.

=head2 unshift_inc

C<static method unshift_inc : void ($include_dir : string);>

Add the class search directory $include_dir at the head of the class search directories of the compiler of the current runtime.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License

