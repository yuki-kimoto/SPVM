package SPVM::Builder::Config::Exe;

use strict;
use warnings;
use Carp 'confess';

use SPVM::Builder::Util;
use SPVM::Builder::Util::API;

# Super Class
use base 'SPVM::Builder::Config';

# Fields
sub global_before_compile_cbs {
  my $self = shift;
  if (@_) {
    $self->{global_before_compile_cbs} = $_[0];
    return $self;
  }
  else {
    return $self->{global_before_compile_cbs};
  }
}

sub config_spvm {
  my $self = shift;
  if (@_) {
    $self->{config_spvm} = $_[0];
    return $self;
  }
  else {
    return $self->{config_spvm};
  }
}

sub ccflags_all {
  my $self = shift;
  if (@_) {
    $self->{ccflags_all} = $_[0];
    return $self;
  }
  else {
    return $self->{ccflags_all};
  }
}

sub ccflags_spvm {
  my $self = shift;
  if (@_) {
    $self->{ccflags_spvm} = $_[0];
    return $self;
  }
  else {
    return $self->{ccflags_spvm};
  }
}

sub ccflags_native {
  my $self = shift;
  if (@_) {
    $self->{ccflags_native} = $_[0];
    return $self;
  }
  else {
    return $self->{ccflags_native};
  }
}

sub ccflags_native_class {
  my $self = shift;
  my $class_name = shift;
  
  unless (defined $class_name) {
    confess "The class name \$class_name must be defined.";
  }
  
  if (@_) {
    $self->{ccflags_native_class}{$class_name} = $_[0];
    return $self;
  }
  else {
    return $self->{ccflags_native_class}{$class_name};
  }
}

sub ccflags_precompile {
  my $self = shift;
  if (@_) {
    $self->{ccflags_precompile} = $_[0];
    return $self;
  }
  else {
    return $self->{ccflags_precompile};
  }
}

sub defines_all {
  my $self = shift;
  if (@_) {
    $self->{defines_all} = $_[0];
    return $self;
  }
  else {
    return $self->{defines_all};
  }
}

sub defines_spvm {
  my $self = shift;
  if (@_) {
    $self->{defines_spvm} = $_[0];
    return $self;
  }
  else {
    return $self->{defines_spvm};
  }
}

sub defines_native {
  my $self = shift;
  if (@_) {
    $self->{defines_native} = $_[0];
    return $self;
  }
  else {
    return $self->{defines_native};
  }
}

sub defines_native_class {
  my $self = shift;
  my $class_name = shift;
  
  unless (defined $class_name) {
    confess "The class name \$class_name must be defined.";
  }
  
  if (@_) {
    $self->{defines_native_class}{$class_name} = $_[0];
    return $self;
  }
  else {
    return $self->{defines_native_class}{$class_name};
  }
}

sub defines_precompile {
  my $self = shift;
  if (@_) {
    $self->{defines_precompile} = $_[0];
    return $self;
  }
  else {
    return $self->{defines_precompile};
  }
}

sub optimize_all {
  my $self = shift;
  if (@_) {
    $self->{optimize_all} = $_[0];
    return $self;
  }
  else {
    return $self->{optimize_all};
  }
}

sub optimize_spvm {
  my $self = shift;
  if (@_) {
    $self->{optimize_spvm} = $_[0];
    return $self;
  }
  else {
    return $self->{optimize_spvm};
  }
}

sub optimize_native {
  my $self = shift;
  if (@_) {
    $self->{optimize_native} = $_[0];
    return $self;
  }
  else {
    return $self->{optimize_native};
  }
}

sub optimize_native_class {
  my $self = shift;
  my $class_name = shift;
  
  unless (defined $class_name) {
    confess "The class name \$class_name must be defined.";
  }
  
  if (@_) {
    $self->{optimize_native_class}{$class_name} = $_[0];
    return $self;
  }
  else {
    return $self->{optimize_native_class}{$class_name};
  }
}

sub optimize_precompile {
  my $self = shift;
  if (@_) {
    $self->{optimize_precompile} = $_[0];
    return $self;
  }
  else {
    return $self->{optimize_precompile};
  }
}

# Class Methods
sub new {
  my $self = shift;
  
  my %fields = (
    output_type => 'exe',
    global_before_compile_cbs => [],
    config_spvm => SPVM::Builder::Util::API::create_default_config(),
    ccflags_all => [],
    ccflags_spvm => [],
    ccflags_native => [],
    ccflags_native_class => {},
    ccflags_precompile => [],
    defines_all => [],
    defines_spvm => [],
    defines_native => [],
    defines_native_class => {},
    defines_precompile => [],
    optimize_native_class => {},
    @_,
  );
  
  $self = $self->SUPER::new(%fields);
  
  return $self;
}

# Instance Methods
sub add_global_before_compile_cb {
  my ($self, @global_before_compile_cbs) = @_;
  
  push @{$self->{global_before_compile_cbs}}, @global_before_compile_cbs;
}

sub add_ccflag_all {
  my ($self, @ccflags_all) = @_;
  
  push @{$self->{ccflags_all}}, @ccflags_all;
}

sub add_ccflag_spvm {
  my ($self, @ccflags_spvm) = @_;
  
  push @{$self->{ccflags_spvm}}, @ccflags_spvm;
}

sub add_ccflag_native {
  my ($self, @ccflags_native) = @_;
  
  push @{$self->{ccflags_native}}, @ccflags_native;
}

sub add_ccflag_native_class {
  my ($self, $class_name, @ccflags_native_class) = @_;
  
  unless (defined $self->{ccflags_native_class}{$class_name}) {
    $self->{ccflags_native_class}{$class_name} = [];
  }
  
  push @{$self->{ccflags_native_class}{$class_name}}, @ccflags_native_class;
}

sub add_ccflag_precompile {
  my ($self, @ccflags_precompile) = @_;
  
  push @{$self->{ccflags_precompile}}, @ccflags_precompile;
}

sub add_define_all {
  my ($self, @defines_all) = @_;
  
  push @{$self->{defines_all}}, @defines_all;
}

sub add_define_spvm {
  my ($self, @defines_spvm) = @_;
  
  push @{$self->{defines_spvm}}, @defines_spvm;
}

sub add_define_native {
  my ($self, @defines_native) = @_;
  
  push @{$self->{defines_native}}, @defines_native;
}

sub add_define_native_class {
  my ($self, $class_name, @defines_native_class) = @_;
  
  unless (defined $self->{defines_native_class}{$class_name}) {
    $self->{defines_native_class}{$class_name} = []
  }
  
  push @{$self->{defines_native_class}{$class_name}}, @defines_native_class;
}

sub add_define_precompile {
  my ($self, @defines_precompile) = @_;
  
  push @{$self->{defines_precompile}}, @defines_precompile;
}

1;

=head1 Name

SPVM::Builder::Config::Exe - Excutable File Config

=head1 Description

The SPVM::Builder::Config::Exe class has methods to manipulate the config for the excutable file generated by L<spvmcc> command.

=head1 Usage

  use SPVM::Builder::Config::Exe;
  
  my $config_exe = SPVM::Builder::Config::Exe->new_gnu99;

=head1 Super Class

=over 2

=item * L<SPVM::Builder::Config>

=back

=head1 Fields

=head2 global_before_compile_cbs

  my $global_before_compile_cbs = $config_exe->global_before_compile_cbs;
  $config_exe->global_before_compile_cbs($global_before_compile_cbs);

Gets and sets the C<global_before_compile_cbs> field, an array reference of callbacks that work globally called just before the compile command L</"cc"> is executed.

This affects all compilations.

=head2 config_spvm

  my $config_exe_spvm = $config_exe->config_spvm;
  $config_exe->config_spvm($config_exe_spvm);

Gets and sets the C<config_spvm> field, an L<SPVM::Builder::Config> object for SPVM core source files.

This field is automatically set and users nomally do not change it.

=head2 ccflags_all

  my $ccflags_all = $config->ccflags_all;
  $config->ccflags_all($ccflags_all);

Gets and sets C<ccflags> field, an array reference containing arugments of the compiler L</"cc"> in all compilation.

=head2 ccflags_spvm

  my $ccflags_spvm = $config->ccflags_spvm;
  $config->ccflags_spvm($ccflags_spvm);

Gets and sets C<ccflags_spvm> field, an array reference containing arugments of the compiler L</"cc"> in compilations of SPVM source code and a bootstrap source file.

=head2 ccflags_native

  my $ccflags_native = $config->ccflags_native;
  $config->ccflags_native($ccflags_native);

Gets and sets C<ccflags_native> field, an array reference containing arugments of the compiler L</"cc"> in compilation of all native class source file(such as MyClass.c) and all native source files(such as MyClass.native/src/mysource.c>.

=head2 ccflags_native_class

  my $ccflags_native_class = $config->ccflags_native_class($class_name);
  $config->ccflags_native_class($class_name, $ccflags_native);

Gets and sets the value of C<ccflags_native_class> field's class name key $class_name, an array reference containing arugments of the compiler L</"cc"> in compilation of native class source file(such as MyClass.c) and all native source files(such as MyClass.native/src/mysource.c> in $class_name.

=head2 ccflags_precompile

  my $ccflags_precompile = $config->ccflags_precompile;
  $config->ccflags_precompile($ccflags_precompile);

Gets and sets C<ccflags_precompile> field, an array reference containing arugments of the compiler L</"cc"> in compilation for precompilation.

=head2 defines_all

  my $defines_all = $config->defines_all;
  $config->defines_all($defines_all);

Gets and sets C<defines> field, an array reference containing the value of C<-D> arugments of the compiler L</"cc"> in all compilation.

=head2 defines_spvm

  my $defines_spvm = $config->defines_spvm;
  $config->defines_spvm($defines_spvm);

Gets and sets C<defines_spvm> field, an array reference containing the value of C<-D> arugments of the compiler L</"cc"> in compilations of SPVM source code and a bootstrap source file.

=head2 defines_native

  my $defines_native = $config->defines_native;
  $config->defines_native($defines_native);

Gets and sets C<defines_native> field, an array reference containing the value of C<-D> arugments of the compiler L</"cc"> in compilation of all native class source file(such as MyClass.c) and all native source files(such as MyClass.native/src/mysource.c>.

=head2 defines_native_class

  my $defines_native_class = $config->defines_native_class($class_name);
  $config->defines_native_class($class_name, $defines_native);

Gets and sets the value of C<defines_native_class> field's class name key $class_name, an array reference containing the value of C<-D> arugments of the compiler L</"cc"> in compilation of native class source file(such as MyClass.c) and all native source files(such as MyClass.native/src/mysource.c> in $class_name.

=head2 defines_precompile

  my $defines_precompile = $config->defines_precompile;
  $config->defines_precompile($defines_precompile);

Gets and sets C<defines_precompile> field, an array reference containing the value of C<-D> arugments of the compiler L</"cc"> in compilation for precompilation.

=head2 optimize_all

  my $optimize_all = $config->optimize_all;
  $config->optimize_all($optimize_all);

Gets and sets C<optimize> field, an arugment of the compiler L</"cc"> for optimization in all compilation.

=head2 optimize_spvm

  my $optimize_spvm = $config->optimize_spvm;
  $config->optimize_spvm($optimize_spvm);

Gets and sets C<optimize_spvm> field, an arugment of the compiler L</"cc"> for optimization in compilations of SPVM source code and a bootstrap source file.

=head2 optimize_native

  my $optimize_native = $config->optimize_native;
  $config->optimize_native($optimize_native);

Gets and sets C<optimize_native> field, an arugment of of the compiler L</"cc"> for optimization in compilation of all native class source file(such as MyClass.c) and all native source files(such as MyClass.native/src/mysource.c>.

=head2 optimize_native_class

  my $optimize_native_class = $config->optimize_native_class($class_name);
  $config->optimize_native_class($class_name, $optimize_native);

Gets and sets the value of C<optimize_native_class> field's class name key $class_name, an arugments of the compiler L</"cc"> for optimization in compilation of native class source file(such as MyClass.c) and all native source files(such as MyClass.native/src/mysource.c> in $class_name.

=head2 optimize_precompile

  my $optimize_precompile = $config->optimize_precompile;
  $config->optimize_precompile($optimize_precompile);

Gets and sets C<optimize_precompile> field, an arugment of of the compiler L</"cc"> for optimization in compilation for precompilation.

=head1 Methods

=head2 new

  my $config_exe = SPVM::Builder::Config::Exe->new(%fields);

Create a new L<SPVM::Builder::Config::Exe> object with L</"Fields"> and fields of its super classes.

This method calls the C<new> method of its L<super class|/"Inheritance"> given %fields with field default values applied.

Field Default Values:

=over 2

=item * L<output_type|SPVM::Builder::Config/"output_type">

  "exe"

=item * L</"global_before_compile_cbs">

  []

=item * L</"config_spvm">

The return value of the L<create_default_config|SPVM::Builder::Util::API/"create_default_config"> function of C<SPVM::Builder::Util::API> class.

=item * Other Fields

  undef

=back

=head2 add_global_before_compile_cb

  $config_exe->add_global_before_compile_cb(@global_before_compile_cbs);

Adds @global_before_compile_cbs to the end of L</"global_before_compile_cbs"> field.

Examples:

  $config_exe->add_global_before_compile_cb(sub {
    my ($config, $compile_info) = @_;
    
    my $cc_command = $compile_info->to_command;
    
    # Do something
  });

=head2 add_ccflag_all

  $config->add_ccflag_all(@ccflags_all);

Adds @ccflags_all to the end of L</"ccflags_all"> field.

=head2 add_ccflag_spvm

  $config->add_ccflag_spvm(@ccflags_spvm);

Adds @ccflags_spvm to the end of L</"ccflags_spvm"> field.

=head2 add_ccflag_native

  $config->add_ccflag_native(@ccflags_native);

Adds @ccflags_native to the end of L</"ccflags_native"> field.

=head2 add_ccflag_native_class

  $config->add_ccflag_native_class($class_name, @ccflags_native_class);

Adds @ccflags_native_class to the end of L</"ccflags_native_class"> field's key $class_name.

=head2 add_ccflag_precompile

  $config->add_ccflag_precompile(@ccflags_precompile);

Adds @ccflags_precompile to the end of L</"ccflags_precompile"> field.

=head2 add_define_all

  $config->add_define_all(@defines_all);

Adds @defines_all to the end of L</"defines_all"> field.

=head2 add_define_spvm

  $config->add_define_spvm(@defines_spvm);

Adds @defines_spvm to the end of L</"defines_spvm"> field.

=head2 add_define_native

  $config->add_define_native(@defines_native);

Adds @defines_native to the end of L</"defines_native"> field.

=head2 add_define_native_class

  $config->add_define_native_class($class_name, @defines_native_class);

Adds @defines_native_class to the end of L</"defines_native_class"> field's key $class_name.

=head2 add_define_precompile

  $config->add_define_precompile(@defines_precompile);

Adds @defines_precompile to the end of L</"defines_precompile"> field.

=head1 Copyright & License

Copyright (c) 2023 Yuki Kimoto

MIT License
