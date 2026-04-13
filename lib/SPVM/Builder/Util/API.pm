package SPVM::Builder::Util::API;

use strict;
use warnings;
use SPVM::Builder::Util;

sub create_make_rule_native { SPVM::Builder::Util::create_make_rule_native(@_) }

sub create_make_rule_precompile { SPVM::Builder::Util::create_make_rule_precompile(@_) }

sub create_make_rule_parallel { SPVM::Builder::Util::create_make_rule_parallel(@_) }

sub create_default_config { SPVM::Builder::Util::create_default_config(@_) }

sub get_cpu_count { SPVM::Builder::Util::get_cpu_count(@_) }

1;

=head1 Name

SPVM::Builder::Util::API - Builder Utility APIs

=head1 Description

The SPVM::Builder::Util::API module has the public utility functions to build SPVM native classes and SPVM precompilation classes.

=head1 Usage

  my $native_make_rule = SPVM::Builder::Util::API::create_make_rule_native('MyClass');
  
  my $precompile_make_rule = SPVM::Builder::Util::API::create_make_rule_precompile('MyClass');

=head1 Functions

=head2 create_make_rule_native

  my $make_rule = SPVM::Builder::Util::API::create_make_rule_native($class_name, $options);

Creates a string of C<make> commands for generating a dynamic library for a L<native class|SPVM::Document::NativeClass> given the class name $class_name, and returns it.

A native class must have at least one method with L<native attribute|SPVM::Document::Language::Class/"Method Attributes">.

C<$options> is a hash reference. The available options are the same as those for L</create_make_rule_parallel>.

Note that the following option is automatically set:

=over 2

=item * C<native_classes>

This option is automatically set to C<[$class_name]>.

=back

Examples:

  # Makefile.PL
  sub MY::postamble {
    
    my $make_rule = '';
    
    # Native compile make rule
    $make_rule .= SPVM::Builder::Util::API::create_make_rule_native('Foo');
    
    return $make_rule;
  }

=head2 create_make_rule_precompile

  my $make_rule = SPVM::Builder::Util::API::create_make_rule_precompile($class_name, $options);

Creates a string of C<make> commands for generating a dynamic library for a precompilation class given the class name $class_name, and returns it.

A precompilation class must have at least one method with L<precompile attribute|SPVM::Document::Language::Class/"Method Attributes">.

C<$options> is a hash reference. The available options are the same as those for L</create_make_rule_parallel>.

Note that the following option is automatically set:

=over 2

=item * C<precompile_classes>

This option is automatically set to C<[$class_name]>.

=back

Examples:

  # Makefile.PL
  sub MY::postamble {
    
    my $make_rule = '';
    
    # Precompile make rule
    $make_rule .= SPVM::Builder::Util::API::create_make_rule_precompile('Foo');
    
    return $make_rule;
  }

=head2 create_default_config

  my $config = SPVM::Builder::Util::API::create_default_config();

Creates a default config, and returns it. It is an L<SPVM::Builder::Config> object.

Currently the default config is created by the following operation.

  my $config = SPVM::Builder::Config->new_c99;

=head2 get_cpu_count

  my $cpu_count = SPVM::Builder::Util::API::get_cpu_count();

Returns the number of CPU cores on the current system.

This function detects the available CPU count in a platform-independent way (Windows, Linux, macOS, etc.). 

If the CPU count cannot be determined, it returns 1.

=head2 create_make_rule_parallel

  my $make_rule = SPVM::Builder::Util::API::create_make_rule_parallel($options);

Creates a string of C<make> commands for generating dynamic libraries for multiple native classes and precompile classes in parallel, and returns it.

C<$options> is a hash reference.

Options:

The following options are the same as those for L<SPVM::Builder::API/build_parallel_dynamic_lib_dist>:

=over 2

=item * C<native_classes>

=item * C<precompile_classes>

=item * C<build_file>

=item * C<optimize>

=item * C<jobs>

=back

The following options are specific to this method:

=over 2

=item * C<dependent_files>

An array reference of dependency file paths for the C<make> target. These files are treated as normal dependencies.

  $options->{dependent_files} = ['SPVM.xs'];

=item * C<order_only_dependent_files>

An array reference of order-only dependency file paths for the C<make> target. These files must exist before the target is built, but their modification times do not trigger a rebuild.

  $options->{order_only_dependent_files} = ['$(INST_DYNAMIC)'];

=back

Examples:

  # Makefile.PL
  sub MY::postamble {
    
    my $make_rule = '';
    
    # Parallel build make rule
    $make_rule .= SPVM::Builder::Util::API::create_make_rule_parallel({
      native_classes => [
        'Foo',
        'Bar',
      ],
      precompile_classes => [
        'Baz',
      ],
      optimize => 'O3',
      dependent_files => ['SPVM.xs'],
      order_only_dependent_files => ['$(INST_DYNAMIC)'],
    });
    
    return $make_rule;
  }

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
