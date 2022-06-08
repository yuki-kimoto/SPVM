package SPVM::Builder::Config::Exe;

use strict;
use warnings;
use Carp 'confess';

use SPVM::Builder::Util;

use base 'SPVM::Builder::Config';

sub new {
  my ($self, %options) = @_;
  
  unless (defined $options{ldflags}) {
    $options{ldflags} = [];
  }
  
  $self = $self->SUPER::new(%options);
  
  return $self;
}

sub global_cc_each {
  my $self = shift;
  if (@_) {
    $self->{global_cc_each} = $_[0];
    return $self;
  }
  else {
    return $self->{global_cc_each};
  }
}

sub global_ccflags_each {
  my $self = shift;
  if (@_) {
    $self->{global_ccflags_each} = $_[0];
    return $self;
  }
  else {
    return $self->{global_ccflags_each};
  }
}

sub global_optimize_each {
  my $self = shift;
  if (@_) {
    $self->{global_optimize_each} = $_[0];
    return $self;
  }
  else {
    return $self->{global_optimize_each};
  }
}

sub no_precompile {
  my $self = shift;
  if (@_) {
    $self->{no_precompile} = $_[0];
    return $self;
  }
  else {
    return $self->{no_precompile};
  }
}

sub no_compiler_api {
  my $self = shift;
  if (@_) {
    $self->{no_compiler_api} = $_[0];
    return $self;
  }
  else {
    return $self->{no_compiler_api};
  }
}

sub dynamic_lib {
  my $self = shift;
  if (@_) {
    $self->{dynamic_lib} = $_[0];
    return $self;
  }
  else {
    return $self->{dynamic_lib};
  }
}


sub static_lib {
  my $self = shift;
  if (@_) {
    $self->{static_lib} = $_[0];
    return $self;
  }
  else {
    return $self->{static_lib};
  }
}

sub is_exe { 1 }

1;

=head1 NAME

SPVM::Builder::Config::Exe - Configurations of creating excutable files.

=head1 DESCRIPTION

SPVM::Builder::Config::Exe is configuration of creating excutable files of L<spvmcc>.

=head1 FIELDS

Fields of B<SPVM::Builder::Config::Exe>.

Fields are inherited from L<SPVM::Builder::Config> and you can use the following fields.

=head2 global_cc_each

  my $global_cc_each = $config->global_cc_each;
  $config->global_cc_each($global_cc_each);

Get and set a global callback that returns the compiler name for each source file. The call back receives L<SPVM::Bulder::Config> object and optional arguments as a hash reference.

B<Optional Arguments:>

=over 2

=item * source_file

Each source file.

=item * class_name

The class name

=item * cc

The compiler name that is the value after the process of the process of L<cc> or L<cc_each> of L<SPVM::Builder::Config>.

=back

B<Examples:>
  
  $config->global_cc_each(sub {
    my ($config, $args) = @_;

    # Source file
    my $source_file = $args->{source_file};
    
    # Class name
    my $class_name = $args->{class_name}

    # The compiler name
    my $cc = $args->{cc};
    
    my $global_cc;
    # C source file
    if ($source_file =~ /\.c$/) {
      $global_cc = 'clang';
    }
    # C++ source file
    elsif ($source_file =~ /\.cpp$/) {
      $global_cc = 'clang++';
    }
    
    return $global_cc;
  });

=head2 global_ccflags_each

  my $global_ccflags_each = $config->global_ccflags_each;
  $config->global_ccflags_each($global_ccflags_each);

Get and set a callback that returns the compiler flags for each source file. The call back receives L<SPVM::Bulder::Config> object and optional arguments as a hash reference.

B<Optional Arguments:>

=over 2

=item * source_file

Each source file.

=item * class_name

The class name

=item * cc

The compiler name that is the value after the process of the process of L<cc> or L<cc_each> of L<SPVM::Builder::Config>.

=item * ccflags

The compiler flags that is the value after the process of the process of L<ccflags> or L<ccflags_each> of L<SPVM::Builder::Config>.

=back

B<Examples:>
  
  $config->global_ccflags_each(sub {
    my ($config, $args) = @_;

    # Source file
    my $source_file = $args->{source_file};
    
    # Class name
    my $class_name = $args->{class_name}

    # The compiler name
    my $cc = $args->{cc};

    # The compiler name
    my $ccflags = $args->{ccflags};
    
    my $global_ccflags = [];
    # C source file
    if ($source_file =~ /\.c$/) {
      $global_ccflags = ['-DFoo', @$ccflags];
    }
    # C++ source file
    elsif ($source_file =~ /\.cpp$/) {
      $global_ccflags = ['-DBar', @$ccflags];
    }
    
    return $global_ccflags;
  });

=head2 global_optimize_each

  my $global_optimize_each = $config->global_optimize_each;
  $config->global_optimize_each($global_optimize_each);

Get and set a callback that returns the compiler flags for each source file. The call back receives L<SPVM::Bulder::Config> object and optional arguments as a hash reference.

B<Optional Arguments:>

=over 2

=item * source_file

Each source file.

=item * class_name

The class name

=item * cc

The compiler name that is the value after the process of the process of L<cc> or L<cc_each> of L<SPVM::Builder::Config>.

=item * optimize

The value of optimize that is the value after the process of the process of L<optimize> or L<optimize_each> of L<SPVM::Builder::Config>.

=back

B<Examples:>
  
  $config->global_optimize_each(sub {
    my ($config, $args) = @_;

    # Source file
    my $source_file = $args->{source_file};
    
    # Class name
    my $class_name = $args->{class_name}

    # The compiler name
    my $cc = $args->{cc};

    # The compiler name
    my $optimize = $args->{optimize};
    
    my $global_optimize;
    # C source file
    if ($source_file =~ /\.c$/) {
      $global_optimize = '-O3';
    }
    # C++ source file
    elsif ($source_file =~ /\.cpp$/) {
      $global_optimize = '-O3';
    }
    
    return $global_optimize;
  });

=head2 no_precompile

  my $no_precompile = $config->no_precompile;
  $config->no_precompile($no_precompile);

If C<no_precompile> is a true value, precompiling is not performed.

=head2 no_compiler_api

  my $no_compiler_api = $config->no_compiler_api;
  $config->no_compiler_api($no_compiler_api);

If C<no_compiler_api> is a true value, the source codes of the L<compiler native APIs|SPVM::Document::NativeAPI::Compiler> and the L<precompile native APIs|SPVM::Document::NativeAPI::Precompile> is not linked.

=head2 dynamic_lib

  my $dynamic_lib = $config->dynamic_lib;
  $config->dynamic_lib($dynamic_lib);

If C<dynamic_lib> is a true value, a dynamic library is created instead of a executable file.

A dynamic library means a shared library C<foo.so> on C<Linux/UNIX>, a Mach-O Dynamic Library C<foo.dylib> on C<Mac>, a dynamic link library C<foo.dll> on C<Windows>.

=head2 static_lib

  my $static_lib = $config->static_lib;
  $config->static_lib($static_lib);

If C<static_lib> is a true value, a static library C<foo.a> on C<Linux/UNIX> is created instead of a executable file.

=head1 METHODS

Methods of B<SPVM::Builder::Config::Exe>.

Methods are inherited from L<SPVM::Builder::Config> and you can use the following methods.

=head2 is_exe

  my $is_exe = $config->is_exe;

Check this config is used for creating executalbe file. Always 1.
