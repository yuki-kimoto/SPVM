package SPVM::JIT;

1;

=encoding utf8

=head1 Name

SPVM::JIT - Abstract Base Class for Just-In-Time Compilation

=head1 Description

C<JIT> class in L<SPVM> is an abstract base class that defines the interface for JIT (Just-In-Time) compilation.

To use JIT features, you must use a child class that implements the methods in this class, such as C<JIT::TCC>.

=head1 Usage

  use JIT::TCC;
  
  # Use a child class like JIT::TCC
  my $jit = JIT::TCC->new;
  
  # Compile a pre-compiled C source code
  my $source = "SPVMPRECOMPILE__MyClass__add(SPVM_ENV* env, SPVM_VALUE* stack) { /* ... */ }";
  $jit->compile($source);
  
  # Get method address
  my $address = $jit->get_address("MyClass", "add");

=head1 Details

This class provides an interface to compile pre-compiled C source code into machine code at runtime. 

The "pre-compiled C source code" typically refers to C code that has been generated or processed by SPVM before being passed to the JIT engine. By using JIT, you can execute these dynamic C codes for high-performance computing or runtime library integration.

This class is an abstract class. The L</"compile"> and L</"get_address"> methods must be implemented in a child class.

=head1 Instance Methods

=head2 compile

C<method compile : void ($source : string);>

An abstract method that compiles the given pre-compiled C source code into machine code. In a child class, this method must be implemented. If an error occurs during compilation, an exception is thrown.

=head2 get_address

C<method get_address : L<Address|SPVM::Address> ($class_name : string, $method_name : string);>

An abstract method that returns the memory address of a method defined by the given class name and method name. In a child class, this method must be implemented. If the method is not found, an exception is thrown.

=head1 Copyright & License

Copyright (c) 2026 Yuki Kimoto

MIT License
