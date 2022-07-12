package SPVM::Builder::Config::Exe;

use strict;
use warnings;
use Carp 'confess';

use SPVM::Builder::Util;

use base 'SPVM::Builder::Config';

sub new {
  my ($self, %options) = @_;
  
  unless (defined $options{output_type}) {
    $options{output_type} = 'exe';
  }
  
  $self = $self->SUPER::new(%options);

  return $self;
}

sub global_before_compile {
  my $self = shift;
  if (@_) {
    $self->{global_before_compile} = $_[0];
    return $self;
  }
  else {
    return $self->{global_before_compile};
  }
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

1;

=head1 Name

SPVM::Builder::Config::Exe - Configurations of creating excutable files.

=head1 Usage

  use SPVM::Builder::Config::Exe;
  
  my $config = SPVM::Builder::Config::Exe->new_gnu99;

=head1 Description

SPVM::Builder::Config::Exe is configuration of creating excutable files of L<spvmcc>.

=head1 Field Methods

Fields of B<SPVM::Builder::Config::Exe>.

Fields are inherited from L<SPVM::Builder::Config> and you can use the following fields.

=head2 global_before_compile

  my $global_before_compile = $config->global_before_compile;
  $config->global_before_compile($global_before_compile);

Get and set a callback that is called before each compile.

The call back receives L<SPVM::Bulder::Config> object and L<SPVM::Builder::CompileInfo> object.

B<Examples:>
  
  $config->global_before_compile(sub {
    my ($config, $compile_info) = @_;

    # Source file
    my $source_file = $compile_info->source_file;
    
    # Class name
    my $class_name = $compile_info->class_name;

    # The compiler name
    my $cc = $compile_info->cc;
    
    my $global_cc;
    # C source file
    if ($source_file =~ /\.c$/) {
      $compile_info->cc('clang');
    }
    # C++ source file
    elsif ($source_file =~ /\.cpp$/) {
      $compile_info->cc('clang++');
    }
  });

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

=head1 Methods

Methods of B<SPVM::Builder::Config::Exe>.

Methods are inherited from L<SPVM::Builder::Config> and you can use the following methods.

=head2 new

  my $config = SPVM::Builder::Config::Exe->new;

Create a new C<SPVM::Builder::Config::Exe> object.

This is same as L<SPVM::Builder::Config/"new">, but set C<output_type> field to C<exe>.
