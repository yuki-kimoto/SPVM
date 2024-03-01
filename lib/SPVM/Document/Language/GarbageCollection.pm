=head1 Name

SPVM::Document::Language::GarbageCollection - Garbage Collection in SPVM Language

=head1 Description

This document describes garbage collection in SPVM language.

=head1 Garbage Collection

=head2 Reference Count GC

Garbage collection in SPVM is a reference counted GC.

The object is destroyed when its reference count reaches 0.

The reference count of an object assigned by the L<assignment operator|SPVM::Document::Language::Operators/"assignment Operator"> is incremented by 1.
  
  # The reference count is incremented by 1
  my $object = Point->new;

The reference count of an object whose assignment is removed by an assignment operator is decreased by 1.

  # The reference count is decremented by 1
  $object = undef;

Reference counts incremented by assignments to local variables are decremented at the end of its scope.

  {
    # The reference count is incremented by 1
    my $object = Point->new;
    
    # The reference count of $object is decremented by 1 at the end of this scope
  }

=head2 Scope

A scope is the part surrounded by a L<scope block|SPVM::Document::Language::Class/"Scope Block">.

  # Scope block
  {
    # Beginning of scope
    
    my $point = Point->new;
    
    # End of scope
  }

=head3 Entering Scope

The entering scope operation is the operation at the start of a L<scope block|SPVM::Document::Language::Class/"Scope Block">.

Memorizes the current top position of the L<mortal stack|/"Mortal Stack">.

=head3 Mortal Stack

The mortal stack is the stack that stores objects that are decremented by 1 at the end of the scope.

Local variables of the object type are pushed to the mortal stack at the same time as its declaration.

=head3 Leaving Scope

The leaving scope operation is the operation at the end of a L<scope block|SPVM::Document::Language::Class/"Scope Block">.

Reference count of the objects from the top position memorized by the L<entering scope|/"Entering Scope"> operation to the current top position of the L<mortal stack|/"Mortal Stack"> are decremented by 1.

=head2 Weak Reference

SPVM supports weak references. Weak references are used to avoid circular references.

This is an example that objects have circular references.

  {
    my $foo = new Foo;
    my $bar = new Bar;
    
    $foo->{bar} = $bar;
    $bar->{foo} = $foo;
  }

The L<weaken operator|SPVM::Document::Language::Operators/"weaken Operator"> converts a reference to a weak reference.

  {
    my $foo = new Foo;
    my $bar = new Bar;
    
    $foo->{bar} = $bar;
    $bar->{foo} = $foo;
    
    weaken $foo->{bar};
  }

If a reference is convertd to a weak reference, the reference count of the referenced object is decremented by 1.

And the weaken flag of the field trun on, and the back reference from the field is added to the referenced object.

The L<isweak operator|SPVM::Document::Language::Operators/"isweak Operator"> checks if the weaken flag of the field turn on.

  my $isweak = isweaken $foo->{bar};

The L<unweaken operator|SPVM::Document::Language::Operators/"unweaken Operator"> converts a weak reference to a reference.

  unweaken $foo->{bar};

If a weak reference is convertd to a reference, the reference count of the referenced object is incremented by 1.

And the weaken flag of the field trun off, and the back reference from the field is removed from the referenced object.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
