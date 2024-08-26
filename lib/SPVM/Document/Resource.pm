=head1 Name

SPVM::Document::Resource - Resource

=head1 Resource

A resource in L<SPVM> is a L<native class|SPVM::Document::NativeClass> that contains L<header files|SPVM::Document::NativeClass/"Native Header Files"> and L<source files|SPVM::Document::NativeClass/"Native Source Files"> writen by native languages such as the C language or C++. A resource must have its L<config file|SPVM::Document::NativeClass/"Native Config File">. A resource does not need to have a L<native class file|SPVM::Document::NativeClass/"Native Class">.

=head2 Resource Class

The following is an example of a resource.

C<SPVM/Resource/MyResource.config>

  my $config = SPVM::Builder::Config->new_gnu99(file => __FILE__);
  
  my @source_files = ("myresource.c");
  $config->add_source_file(@source_files);
  
  $config;

Native header files:

  SPVM/Resource/MyResource.native/include/myresource.h

Native source files:

  SPVM/Resource/MyResource.native/src/myresource.c

=head2 Resource User Class

A native class can include native header files of a resource and add the object files generated by native source files of a resource to the object files for the linker using L<SPVM::Builder::Config#use_resource|SPVM::Builder::Config/"use_resource">.

C<SPVM/MyClass.config>

  my $config = SPVM::Builder::Config->new_gnu99(file => __FILE__);
  
  $config->use_resource("Resource::MyResource");
  
  $config;

C<SPVM/MyClass.c>

  #include "myresource.h"

=head1 Examples

See L<Resource::Zlib|https://github.com/yuki-kimoto/SPVM-Resource-Zlib> as an example of resources.

=head1 Distribution

A distribution for a resource can be generated by L<spvmdist> command with C<--resource> option.

  # C
  spvmdist --resource Resource::Foo

  # C++
  spvmdist --resource --native c++ Resource::Foo

=head1 See Also

L<Resource Modules|https://github.com/yuki-kimoto/SPVM/wiki/CPAN-Modules#resource-modules>

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
