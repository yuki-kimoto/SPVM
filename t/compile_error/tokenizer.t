use strict;
use warnings;
use utf8;
use FindBin;

use SPVM::Builder;

use lib "$FindBin::Bin/../default/lib";
use lib "$FindBin::Bin/lib";

use MyTest qw(compile_not_ok_file compile_not_ok);

use Test::More;

# Class name
{
  {
    my $source = 'class myclass;';
    compile_not_ok($source, qr|The class name "myclass" must begin with an upper case character|);
  }
  {
    my $source = 'class Myclass::foo;';
    compile_not_ok($source, qr|The part names of the class "Myclass::foo" must begin with an upper case character|);
  }
  {
    my $source = 'class Myclass::Foo::bar;';
    compile_not_ok($source, qr|The part names of the class "Myclass::Foo::bar" must begin with an upper case character|);
  }
  {
    my $source = 'class Myclass__Foo;';
    compile_not_ok($source, qr|The class name "Myclass__Foo" can't constain "__"|);
  }
  {
    my $source = 'class Myclass::;';
    compile_not_ok($source, qr|The class name "Myclass::" can't end with "::"|);
  }
  {
    my $source = 'class MyClass::::Foo;';
    compile_not_ok($source, qr|The class name "MyClass::::Foo" can't contains "::::"|);
  }
  {
    my $source = 'class ::MyClass;';
    compile_not_ok($source, qr|The class name "::MyClass" can't begin with "::"|);
  }
  {
    my $source = 'class 6MyClass;';
    compile_not_ok($source, qr|The class name "6MyClass" can't begin with a number|);
  }
}

# Load class
{
  {
    my $source = 'class MyClass { use NotFoundClass; }';
    compile_not_ok($source, qr|\QFailed to load the class "NotFoundClass". The module file "NotFoundClass.spvm" is not found|);
  }
  
}
done_testing;
