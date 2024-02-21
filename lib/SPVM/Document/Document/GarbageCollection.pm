=head1 Name

SPVM::Document::Language::GarbageCollection - Garbage Collection in SPVM Language

=head1 Description

This document describes garbage collection in SPVM language.

=head1 Garbage Collection

=head2 Reference Count GC

The object is destroyed when the reference count becomes 0.

If the object is an Array that has Object Type values ​​as elements, the reference count of all Array elements that are not Undefined Value is decremented by 1 before Garbage Collection

When an object is a L<class type|/"Class Type"> and has a field of Object Type, the reference count of the objects owned by all fields of Object Type that are not Undefined Value is decremented by 1 before Garbage Collection. If Weak Reference is set to the object saved in Field, Weak Reference is destroyed before the reference count is decremented by 1.

When the object has Back references of Weak Reference, Undefined Value is assigned to all fields registered as back References and all back References are deleted.

The above process is done recursively.

=head2 Weak Reference

Weak Reference is a reference that does not increase the reference count. Weak Reference can be used to solve the problem of circular references.

SPVM has GC of the reference count Type. In the GC of the reference count Type, the object is automatically destroyed when the reference count becomes 0, but when the circular reference occurs, the reference count does not become 0 and the object is automatically destroyed. not.

This is an example when the field of the object is circularly referenced.

  {
    my $foo = new Foo;
    my $bar = new Bar;
  
    $foo->{bar} = $bar;
    $bar->{foo} = $foo;
  }

In this case, both objects are not destroyed when the Scope ends. This is because a circular reference has occurred and the reference count does not become 0.

Weak Reference is a function to correctly destroy objects when a circular reference occurs in a programming language that has the reference count GC.

In such a case, it is possible to release correctly by setting one Field to Weak Reference using the L<weaken operator/"weaken Operator">.

  {
    my $foo = new Foo;
    my $bar = new Bar;
  
    $foo->{bar} = $bar;
    $bar->{foo} = $foo;
  
    weaken $foo->{bar};
  }

Before the weaken statement is executed, $foo has the reference count of 2 and $bar has the reference count of 2.

If there is no weaken statement, the reference count of $foo and the reference count of $bar will not be 0 and will not be destroyed even if the scope ends.

When a weaken statement is executed, $foo has the reference count of 2 and $bar has the reference count of 1.

When the Scope ends, the reference count of $bar is decremented by 1 and becomes 0, so it is destroyed correctly.

Even if there are 3 circular references, you can release them correctly by setting Weak Reference in 1 Field.

  {
    my $foo = new Foo;
    my $bar = new Bar;
    my $baz = new Baz;
  
    $foo->{bar} = $bar;
    $bar->{baz} = $baz;
    $baz->{foo} = $foo;
  
    weaken $foo->{bar};
  }

As a syntax related to Weak Reference, Weak Reference can be destroyed the L<weaken operator/"weaken Operator">, and it can be confirmed whether Field is Weak Reference the L<isweak operator|/"isweak Operator">.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
